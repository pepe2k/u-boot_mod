/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>

#if defined(CFG_HUSH_PARSER)
#include <hush.h>
#endif

#if defined(CONFIG_SILENT_CONSOLE)
DECLARE_GLOBAL_DATA_PTR;
#endif

static char *delete_char(char *buffer, char *p, int *colp, int *np, int plen);
static int parse_line(char *, char *[]);

char console_buffer[CFG_CBSIZE];	/* console I/O buffer  */
static char erase_seq[] = "\b \b";	/* erase sequence      */
static char tab_seq[] = "        ";	/* used to expand TABs */

/*
 * Watch for 'delay' seconds for autoboot stop or autoboot delay string.
 * returns: 0 -  no key string, allow autoboot
 *          1 - got key string, abort
 */
#if defined(CONFIG_BOOTDELAY) &&\
	   (CONFIG_BOOTDELAY >= 0)
static __inline__ int abortboot(int bootdelay)
{
	int abort = 0;
	char stopc;

#if defined(CONFIG_SILENT_CONSOLE)
	if (gd->flags & GD_FLG_SILENT) {
		/* Restore serial console */
		console_assign(stdout, "serial");
		console_assign(stderr, "serial");
	}
#endif

	if (bootdelay > 0) {
#if defined(CONFIG_MENUPROMPT)
		printf(CONFIG_MENUPROMPT, bootdelay);
#else
		printf("Hit any key to stop booting: %2d ", bootdelay);
#endif

		while ((bootdelay > 0) && (!abort)) {
			int i;

			--bootdelay;

			/* delay 100 * 10ms */
			for (i = 0; !abort && i < 100; ++i) {
				/* we got a key press */
				if (tstc()) {
					stopc = getc();
#if defined(CONFIG_AUTOBOOT_STOP_CHAR)
					if (stopc == CONFIG_AUTOBOOT_STOP_CHAR) {
#else
					if (stopc != 0) {
#endif
						abort = 1;
						bootdelay = 0;
						break;
					}
				}
				udelay(10000);
			}
			printf("\b\b%d ", bootdelay);
		}
		printf("\n\n");
	}

#if defined(CONFIG_SILENT_CONSOLE)
	if (abort) {
		/* Permanently enable normal console output */
		gd->flags &= ~(GD_FLG_SILENT);
	} else if (gd->flags & GD_FLG_SILENT) {
		/* Restore silent console */
		console_assign(stdout, "nulldev");
		console_assign(stderr, "nulldev");
	}
#endif

	return abort;
}
#endif /* CONFIG_BOOTDELAY && CONFIG_BOOTDELAY >= 0 */

/*
 * =========
 * Main loop
 * =========
 */
void main_loop(void)
{
	char *bootcmd;

#if defined(CONFIG_BTN_RECOVERY_SCRIPT)
	int stop_boot;
	char *c;
#endif

#ifndef CFG_HUSH_PARSER
	static char lastcommand[CFG_CBSIZE] = { 0, };
	int flag, len;
	int rc = 1;
#endif

#if defined(CONFIG_BOOTDELAY) &&\
	   (CONFIG_BOOTDELAY >= 0)
	int bootdelay;
	char *s;
#endif

#if defined(CFG_HUSH_PARSER)
	u_boot_hush_start();
#endif

	/* Get boot command */
	bootcmd = getenv("bootcmd");

#if defined(CONFIG_BOOTCOMMAND)
	if (!bootcmd)
		setenv("bootcmd", CONFIG_BOOTCOMMAND);

	bootcmd = getenv("bootcmd");
#endif

/* Recovery mode before normal boot */
#if defined(CONFIG_BTN_RECOVERY_SCRIPT)
	if (reset_button_status()) {
		#if defined(CONFIG_SILENT_CONSOLE)
		if (gd->flags & GD_FLG_SILENT) {
			/* Restore serial console */
			console_assign(stdout, "serial");
			console_assign(stderr, "serial");
		}

		/* Enable normal console output */
		gd->flags &= ~(GD_FLG_SILENT);
		#endif

		run_command("run recovery", 0);

		/* Should we stop booting after recovery mode? */
		c = getenv("stop_boot");
		stop_boot = c ? (int)simple_strtol(c, NULL, 10) : 0;

		if (stop_boot)
			bootcmd = NULL;
	}
#endif /* CONFIG_RECOVERY_MODE */

#if defined(CONFIG_BOOTDELAY) &&\
	   (CONFIG_BOOTDELAY >= 0)
	/* Get boot delay (seconds) */
	s = getenv("bootdelay");
	bootdelay = s ? (int)simple_strtol(s, NULL, 10) : CONFIG_BOOTDELAY;

	if (bootdelay >= 0 && bootcmd && !abortboot(bootdelay)) {
		/* Try to boot */
	#ifndef CFG_HUSH_PARSER
		run_command(bootcmd, 0);
	#else
		parse_string_outer(bootcmd, FLAG_PARSE_SEMICOLON |
					    FLAG_EXIT_FROM_LOOP);
	#endif
	}
#else
	if (bootcmd) {
		/* Try to boot */
	#ifndef CFG_HUSH_PARSER
		run_command(bootcmd, 0);
	#else
		parse_string_outer(bootcmd, FLAG_PARSE_SEMICOLON |
					    FLAG_EXIT_FROM_LOOP);
	#endif
	}
#endif /* CONFIG_BOOTDELAY && CONFIG_BOOTDELAY >= 0 */

	/* Main loop for monitor command processing */
#if defined(CFG_HUSH_PARSER)
	parse_file_outer();

	/* This point is never reached */
	for (;;)
		;
#else
	for (;;) {
		len = readline(CFG_PROMPT);

		/* Assume no special flags for now */
		flag = 0;

		if (len > 0)
			strcpy(lastcommand, console_buffer);
		else if (len == 0)
			flag |= CMD_FLAG_REPEAT;

		if (len == -1)
			puts("<INTERRUPT>\n");
		else
			rc = run_command(lastcommand, flag);

		/* Invalid command or not repeatable, forget it */
		if (rc <= 0)
			lastcommand[0] = 0;
	}
#endif /* CFG_HUSH_PARSER */
}

/*
 * Prompt for input and read a line.
 * If  CONFIG_BOOT_RETRY_TIME is defined and retry_time >= 0,
 * time out when time goes past endtime (timebase time in ticks).
 * Return:	number of read characters
 *		-1 if break
 *		-2 if timed out
 */
int readline(const char * const prompt)
{
	char *p = console_buffer;
	int plen = 0;	/* prompt length     */
	int n = 0;	/* buffer index      */
	int col;	/* output column cnt */
	char c;

	/* Print prompt */
	if (prompt) {
		plen = strlen(prompt);
		puts(prompt);
	}
	col = plen;

	for (;;) {
		c = getc();

		/* Special character handling */
		switch (c) {
		/* Enter */
		case '\r':
		case '\n':
			*p = '\0';
			puts("\r\n");
			return p - console_buffer;
		/* NULL */
		case '\0':
			continue;
		/* ^C - break */
		case 0x03:
			/* discard input */
			console_buffer[0] = '\0';
			return -1;
		/* ^U - erase line */
		case 0x15:
			while (col > plen) {
				puts(erase_seq);
				--col;
			}

			p = console_buffer;
			n = 0;

			continue;
		/* ^W - erase word */
		case 0x17:
			p = delete_char(console_buffer, p, &col, &n, plen);
			while ((n > 0) && (*p != ' '))
				p = delete_char(console_buffer, p, &col, &n, plen);

			continue;
		/* ^H  - backspace */
		/* DEL - backspace */
		case 0x08:
		case 0x7F:
			p = delete_char(console_buffer, p, &col, &n, plen);
			continue;
		/* Must be a normal character then */
		default:
			if (n < CFG_CBSIZE - 2) {
				if (c == '\t') {
					/* Expand TABs */
					puts(tab_seq + (col & 07));
					col += 8 - (col & 07);
				} else {
					/* Echo input */
					++col;
					putc(c);
				}

				*p++ = c;
				++n;
			} else {
				/* Buffer full */
				putc('\a');
			}
		}
	}
}

static char *delete_char(char *buffer,
			 char *p,
			 int *colp,
			 int *np,
			 int plen)
{
	char *s;

	if (*np == 0)
		return p;

	if (*(--p) == '\t') {
		/* Will retype the whole line */
		while (*colp > plen) {
			puts(erase_seq);
			(*colp)--;
		}

		for (s = buffer; s < p; ++s) {
			if (*s == '\t') {
				puts(tab_seq + ((*colp) & 07));
				*colp += 8 - ((*colp) & 07);
			} else {
				++(*colp);
				putc(*s);
			}
		}
	} else {
		puts(erase_seq);
		(*colp)--;
	}

	(*np)--;
	return p;
}

int parse_line(char *line, char *argv[])
{
	int nargs = 0;

	while (nargs < CFG_MAXARGS) {
		/* Skip any white space */
		while ((*line == ' ') || (*line == '\t'))
			++line;

		/* End of line, no more args */
		if (*line == '\0') {
			argv[nargs] = NULL;
			return nargs;
		}

		/* Begin of argument string */
		argv[nargs++] = line;

		/* Find end of string */
		while (*line && (*line != ' ') && (*line != '\t'))
			++line;

		/* End of line, no more args */
		if (*line == '\0') {
			argv[nargs] = NULL;
			return nargs;
		}

		/* Terminate current arg */
		*line++ = '\0';
	}

	printf_err("too many args (max. %d)\n", CFG_MAXARGS);

	return nargs;
}

static void process_macros(const char *input, char *output)
{
	const char *varname_start = NULL;
	int inputcnt = strlen(input);
	int outputcnt = CFG_CBSIZE;
	char c, prev;
	int state = 0;	/* 0 = waiting for '$'
			   1 = waiting for '(' or '{'
			   2 = waiting for ')' or '}'
			   3 = waiting for ''' */

	/* Previous character */
	prev = '\0';

	while (inputcnt && outputcnt) {
		c = *input++;
		inputcnt--;

		if (state != 3) {
			/* Remove one level of escape characters */
			if ((c == '\\') && (prev != '\\')) {
				if (inputcnt-- == 0)
					break;

				prev = c;
				c = *input++;
			}
		}

		switch(state){
		/* Waiting for (unescaped) $ */
		case 0:
			if ((c == '\'') && (prev != '\\')) {
				state = 3;
				break;
			}

			if ((c == '$') && (prev != '\\')) {
				state++;
			} else {
				*(output++) = c;
				outputcnt--;
			}

			break;
		/* Waiting for ( */
		case 1:
			if (c == '(' || c == '{') {
				state++;
				varname_start = input;
			} else {
				state = 0;
				*(output++) = '$';
				outputcnt--;

				if (outputcnt) {
					*(output++) = c;
					outputcnt--;
				}
			}

			break;
		/* Waiting for ) */
		case 2:
			if (c == ')' || c == '}') {
				int envcnt = input - varname_start - 1;	/* Varname # of chars */
				char envname[CFG_CBSIZE], *envval;
				int i;

				/* Get the varname */
				for (i = 0; i < envcnt; i++)
					envname[i] = varname_start[i];

				envname[i] = 0;

				/* Get its value */
				envval = getenv(envname);

				/* Copy into the line if it exists */
				if (envval != NULL) {
					while ((*envval) && outputcnt) {
						*(output++) = *(envval++);
						outputcnt--;
					}
				}

				/* Look for another '$' */
				state = 0;
			}

			break;
		/* Waiting for ' */
		case 3:
			if ((c == '\'') && (prev != '\\')) {
				state = 0;
			} else {
				*(output++) = c;
				outputcnt--;
			}

			break;
		}

		prev = c;
	}

	if (outputcnt)
		*output = 0;
}

/*
 * returns:
 *	1  - command executed, repeatable
 *	0  - command executed but not repeatable, interrupted commands are
 *	     always considered not repeatable
 *	-1 - not executed (unrecognized, bootd recursion or too many args)
 *           (If cmd is NULL or "" or longer than CFG_CBSIZE-1 it is
 *           considered unrecognized)
 *
 * WARNING:
 *
 * We must create a temporary copy of the command since the command we get
 * may be the result from getenv(), which returns a pointer directly to
 * the environment data, which may change magicly when the command we run
 * creates or modifies environment variables (like "bootp" does).
 */

int run_command(const char *cmd, int flag){
	cmd_tbl_t *cmdtp;
	char *argv[CFG_MAXARGS + 1];	/* NULL terminated                    */
	char cmdbuf[CFG_CBSIZE];	/* Working copy of cmd                */
	char *token;			/* Start of token in cmdbuf           */
	char *sep; 			/* End of token (separator) in cmdbuf */
	char finaltoken[CFG_CBSIZE];
	char *str = cmdbuf;
	int argc, inquotes;
	int repeatable = 1;
	int rc = 0;

	/* Forget any previous Control-C */
	clear_ctrlc();

	/* Empty command */
	if (!cmd || !*cmd)
		return -1;

	if (strlen(cmd) >= CFG_CBSIZE) {
		printf_err("command too long!\n");
		return -1;
	}

	strcpy(cmdbuf, cmd);

	/* Process separators and check for invalid repeatable commands */
	while (*str) {
		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for (inquotes = 0, sep = str; *sep; sep++) {
			if ((*sep == '\'') && (*(sep - 1) != '\\'))
				inquotes = !inquotes;

			if(!inquotes && (*sep == ';')
				     && (sep != str) && (*(sep - 1) != '\\'))
				break;
		}

		/* Limit the token to data between separators */
		token = str;

		if (*sep) {
			/* Start of command for next pass */
			str = sep + 1;
			*sep = '\0';
		} else {
			/* No more commands for next pass */
			str = sep;
		}

		/* Find macros in this token and replace them */
		process_macros(token, finaltoken);

		/* Extract arguments */
		if ((argc = parse_line(finaltoken, argv)) == 0) {
			/* No command at all */
			rc = -1;
			continue;
		}

		/* Look up command in command table */
		if ((cmdtp = find_cmd(argv[0])) == NULL) {
			printf_err("unknown command '%s' - try 'help'\n", argv[0]);
			puts("\n");

			/* Give up after bad command */
			rc = -1;
			continue;
		}

		/* Found - check max args */
		if (argc > cmdtp->maxargs) {
			print_cmd_help(cmdtp);

			/* Give up if too many args */
			rc = -1;
			continue;
		}

		/* OK - call function to do the command */
		if ((cmdtp->cmd)(cmdtp, flag, argc, argv) != 0)
			rc = -1;

		repeatable &= cmdtp->repeatable;

		/* Did the user stop this? If stopped then not repeatable */
		if (had_ctrlc())
			return(0);
	}

	return rc ? rc : repeatable;
}

#if defined(CONFIG_CMD_RUN)
int do_run(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		print_cmd_help(cmdtp);
		return 1;
	}

	for (i=1; i<argc; ++i) {
		char *arg;

		if ((arg = getenv(argv[i])) == NULL) {
			printf_err("'%s' not defined\n", argv[i]);
			return 1;
		}

	#ifndef CFG_HUSH_PARSER
		if (run_command(arg, flag) == -1)
			return 1;
	#else
		if (parse_string_outer(arg, FLAG_PARSE_SEMICOLON |
					    FLAG_EXIT_FROM_LOOP) != 0)
			return 1;
	#endif
	}

	return 0;
}
#endif /* CONFIG_CMD_RUN */
