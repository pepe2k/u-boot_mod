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

/* #define	DEBUG	*/

#include <common.h>
#include <command.h>

#ifdef CFG_HUSH_PARSER
#include <hush.h>
#endif

#ifdef CONFIG_SILENT_CONSOLE
DECLARE_GLOBAL_DATA_PTR;
#endif

extern int reset_button_status(void);
extern void all_led_on(void);
extern void all_led_off(void);
extern int NetLoopHttpd(void);

#define MAX_DELAY_STOP_STR 32

static char *delete_char(char *buffer, char *p, int *colp, int *np, int plen);
static int parse_line(char *, char *[]);
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
static int abortboot(int);
#endif

char console_buffer[CFG_CBSIZE]; /* console I/O buffer	*/
static char erase_seq[] = "\b \b"; /* erase sequence	*/
static char tab_seq[] = "        "; /* used to expand TABs	*/

/***************************************************************************
 * Watch for 'delay' seconds for autoboot stop or autoboot delay string.
 * returns: 0 -  no key string, allow autoboot
 *          1 - got key string, abort
 */
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
static __inline__ int abortboot(int bootdelay){
	char stopc;
	int abort = 0;

#ifdef CONFIG_SILENT_CONSOLE
	if(gd->flags & GD_FLG_SILENT){
		/* Restore serial console */
		console_assign(stdout, "serial");
		console_assign(stderr, "serial");
	}
#endif

	if(bootdelay > 0){
#ifdef CONFIG_MENUPROMPT
		printf(CONFIG_MENUPROMPT, bootdelay);
#else
		printf("Hit any key to stop autoboot: %d ", bootdelay);
#endif

		while((bootdelay > 0) && (!abort)){
			int i;

			--bootdelay;

			/* delay 100 * 10ms */
			for(i = 0; !abort && i < 100; ++i){
				/* we got a key press	*/
				if(tstc()){
					stopc = getc();
#ifdef CONFIG_AUTOBOOT_STOP_CHAR
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

#ifdef CONFIG_SILENT_CONSOLE
	if(abort){
		/* permanently enable normal console output */
		gd->flags &= ~(GD_FLG_SILENT);
	} else if(gd->flags & GD_FLG_SILENT){
		/* Restore silent console */
		console_assign(stdout, "nulldev");
		console_assign(stderr, "nulldev");
	}
#endif

	return(abort);
}
#endif	/* CONFIG_BOOTDELAY >= 0  */

/****************************************************************************/

void main_loop(void){
#ifndef CFG_HUSH_PARSER
	static char lastcommand[CFG_CBSIZE] = { 0, };
	int len;
	int rc = 1;
	int flag;
#endif
	int counter = 0;

#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	char *s;
	int bootdelay;
#endif /* defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0) */

#ifdef CFG_HUSH_PARSER
	u_boot_hush_start();
#endif

#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	// get boot delay (seconds)
	s = getenv("bootdelay");
	bootdelay = s ? (int)simple_strtol(s, NULL, 10) : CONFIG_BOOTDELAY;

	// get boot command
	s = getenv("bootcmd");

#if !defined(CONFIG_BOOTCOMMAND)
#error "CONFIG_BOOTCOMMAND not defined!"
#endif

	if(!s){
		setenv("bootcmd", CONFIG_BOOTCOMMAND);
	}

	s = getenv("bootcmd");

	// are we going to run web failsafe mode, U-Boot console, U-Boot netconsole or just boot command?
	if(reset_button_status()){

#ifdef CONFIG_SILENT_CONSOLE
		if(gd->flags & GD_FLG_SILENT){
			/* Restore serial console */
			console_assign(stdout, "serial");
			console_assign(stderr, "serial");
		}

		/* enable normal console output */
		gd->flags &= ~(GD_FLG_SILENT);
#endif

		// wait 0,5s
		milisecdelay(500);

		printf("Press reset button for at least:\n- %d sec. to run web failsafe mode\n- %d sec. to run U-Boot console\n- %d sec. to run U-Boot netconsole\n\n",
				CONFIG_DELAY_TO_AUTORUN_HTTPD,
				CONFIG_DELAY_TO_AUTORUN_CONSOLE,
				CONFIG_DELAY_TO_AUTORUN_NETCONSOLE);

		printf("Reset button is pressed for: %2d ", counter);

		while(reset_button_status()){

			// LED ON and wait 0,15s
			all_led_on();
			milisecdelay(150);

			// LED OFF and wait 0,85s
			all_led_off();
			milisecdelay(850);

			counter++;

			// how long the button is pressed?
			printf("\b\b\b%2d ", counter);

			if(!reset_button_status()){
				break;
			}

			if(counter >= CONFIG_MAX_BUTTON_PRESSING){
				break;
			}
		}

		all_led_off();

		if(counter > 0){

			// run web failsafe mode
			if(counter >= CONFIG_DELAY_TO_AUTORUN_HTTPD && counter < CONFIG_DELAY_TO_AUTORUN_CONSOLE){
				printf("\n\nButton was pressed for %d sec...\nHTTP server is starting for firmware update...\n\n", counter);
				NetLoopHttpd();
				bootdelay = -1;
			} else if(counter >= CONFIG_DELAY_TO_AUTORUN_CONSOLE && counter < CONFIG_DELAY_TO_AUTORUN_NETCONSOLE){
				printf("\n\nButton was pressed for %d sec...\nStarting U-Boot console...\n\n", counter);
				bootdelay = -1;
			} else if(counter >= CONFIG_DELAY_TO_AUTORUN_NETCONSOLE){
				printf("\n\nButton was pressed for %d sec...\nStarting U-Boot netconsole...\n\n", counter);
				bootdelay = -1;
				run_command("startnc", 0);
			} else {
				printf("\n\n## Error: button wasn't pressed long enough!\nContinuing normal boot...\n\n");
			}

		} else {
			printf("\n\n## Error: button wasn't pressed long enough!\nContinuing normal boot...\n\n");
		}

	}

	if(bootdelay >= 0 && s && !abortboot(bootdelay)){

		// try to boot
#ifndef CFG_HUSH_PARSER
			run_command(s, 0);
#else
			parse_string_outer(s, FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP);
#endif

		// something goes wrong!
		printf("\n## Error: failed to execute 'bootcmd'!\nHTTP server is starting for firmware update...\n\n");
		NetLoopHttpd();
	}
#endif	/* CONFIG_BOOTDELAY */

	/*
	 * Main Loop for Monitor Command Processing
	 */
#ifdef CFG_HUSH_PARSER
	parse_file_outer();
	/* This point is never reached */
	for (;;);
#else
	for(;;){
		len = readline(CFG_PROMPT);

		flag = 0; /* assume no special flags for now */
		if(len > 0){
			strcpy(lastcommand, console_buffer);
		} else if(len == 0){
			flag |= CMD_FLAG_REPEAT;
		}

		if(len == -1){
			puts("<INTERRUPT>\n");
		} else {
			rc = run_command(lastcommand, flag);
		}

		if(rc <= 0){
			/* invalid command or not repeatable, forget it */
			lastcommand[0] = 0;
		}
	}
#endif /* CFG_HUSH_PARSER */
}

/****************************************************************************/

/*
 * Prompt for input and read a line.
 * If  CONFIG_BOOT_RETRY_TIME is defined and retry_time >= 0,
 * time out when time goes past endtime (timebase time in ticks).
 * Return:	number of read characters
 *		-1 if break
 *		-2 if timed out
 */
int readline(const char * const prompt){
	char *p = console_buffer;
	int n = 0; /* buffer index		*/
	int plen = 0; /* prompt length	*/
	int col; /* output column cnt	*/
	char c;

	/* print prompt */
	if(prompt){
		plen = strlen(prompt);
		puts(prompt);
	}
	col = plen;

	for(;;){
		c = getc();

		/*
		 * Special character handling
		 */
		switch(c){
			case '\r': /* Enter		*/
			case '\n':
				*p = '\0';
				puts("\r\n");
				return(p - console_buffer);

			case '\0': /* nul			*/
				continue;

			case 0x03: /* ^C - break		*/
				console_buffer[0] = '\0'; /* discard input */
				return(-1);

			case 0x15: /* ^U - erase line	*/
				while(col > plen){
					puts(erase_seq);
					--col;
				}
				p = console_buffer;
				n = 0;
				continue;

			case 0x17: /* ^W - erase word 	*/
				p = delete_char(console_buffer, p, &col, &n, plen);
				while((n > 0) && (*p != ' ')){
					p = delete_char(console_buffer, p, &col, &n, plen);
				}
				continue;

			case 0x08: /* ^H  - backspace	*/
			case 0x7F: /* DEL - backspace	*/
				p = delete_char(console_buffer, p, &col, &n, plen);
				continue;

			default:
				/*
				 * Must be a normal character then
				 */
				if(n < CFG_CBSIZE - 2){
					if(c == '\t'){ /* expand TABs		*/
						puts(tab_seq + (col & 07));
						col += 8 - (col & 07);
					} else {
						++col; /* echo input		*/
						putc(c);
					}
					*p++ = c;
					++n;
				} else { /* Buffer full		*/
					putc('\a');
				}
		}
	}
}

/****************************************************************************/

static char * delete_char(char *buffer, char *p, int *colp, int *np, int plen){
	char *s;

	if(*np == 0){
		return(p);
	}

	if(*(--p) == '\t'){ /* will retype the whole line	*/
		while(*colp > plen){
			puts(erase_seq);
			(*colp)--;
		}
		for(s = buffer; s < p; ++s){
			if(*s == '\t'){
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
	return(p);
}

/****************************************************************************/

int parse_line(char *line, char *argv[]){
	int nargs = 0;

	while(nargs < CFG_MAXARGS){

		/* skip any white space */
		while((*line == ' ') || (*line == '\t')){
			++line;
		}

		if(*line == '\0'){ /* end of line, no more args	*/
			argv[nargs] = NULL;
			return(nargs);
		}

		argv[nargs++] = line; /* begin of argument string	*/

		/* find end of string */
		while(*line && (*line != ' ') && (*line != '\t')){
			++line;
		}

		if(*line == '\0'){ /* end of line, no more args	*/
			argv[nargs] = NULL;
			return(nargs);
		}

		*line++ = '\0'; /* terminate current arg	 */
	}

	printf("## Error: too many args (max. %d)\n", CFG_MAXARGS);

	return(nargs);
}

/****************************************************************************/

static void process_macros(const char *input, char *output){
	char c, prev;
	const char *varname_start = NULL;
	int inputcnt = strlen(input);
	int outputcnt = CFG_CBSIZE;
	int state = 0; /* 0 = waiting for '$'	*/
	/* 1 = waiting for '(' or '{' */
	/* 2 = waiting for ')' or '}' */
	/* 3 = waiting for '''  */

	prev = '\0'; /* previous character	*/

	while(inputcnt && outputcnt){
		c = *input++;
		inputcnt--;

		if(state != 3){
			/* remove one level of escape characters */
			if((c == '\\') && (prev != '\\')){
				if(inputcnt-- == 0){
					break;
				}

				prev = c;
				c = *input++;
			}
		}

		switch(state){
			case 0: /* Waiting for (unescaped) $	*/
				if((c == '\'') && (prev != '\\')){
					state = 3;
					break;
				}
				if((c == '$') && (prev != '\\')){
					state++;
				} else {
					*(output++) = c;
					outputcnt--;
				}
				break;
			case 1: /* Waiting for (	*/
				if(c == '(' || c == '{'){
					state++;
					varname_start = input;
				} else {
					state = 0;
					*(output++) = '$';
					outputcnt--;

					if(outputcnt){
						*(output++) = c;
						outputcnt--;
					}
				}
				break;
			case 2: /* Waiting for )	*/
				if(c == ')' || c == '}'){
					int i;
					char envname[CFG_CBSIZE], *envval;
					int envcnt = input - varname_start - 1; /* Varname # of chars */

					/* Get the varname */
					for(i = 0; i < envcnt; i++){
						envname[i] = varname_start[i];
					}
					envname[i] = 0;

					/* Get its value */
					envval = getenv(envname);

					/* Copy into the line if it exists */
					if(envval != NULL){
						while((*envval) && outputcnt){
							*(output++) = *(envval++);
							outputcnt--;
						}
					}
					/* Look for another '$' */
					state = 0;
				}
				break;
			case 3: /* Waiting for '	*/
				if((c == '\'') && (prev != '\\')){
					state = 0;
				} else {
					*(output++) = c;
					outputcnt--;
				}
				break;
		}
		prev = c;
	}

	if(outputcnt){
		*output = 0;
	}
}

/****************************************************************************
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
	char cmdbuf[CFG_CBSIZE]; /* working copy of cmd		*/
	char *token; /* start of token in cmdbuf	*/
	char *sep; /* end of token (separator) in cmdbuf */
	char finaltoken[CFG_CBSIZE];
	char *str = cmdbuf;
	char *argv[CFG_MAXARGS + 1]; /* NULL terminated	*/
	int argc, inquotes;
	int repeatable = 1;
	int rc = 0;

	clear_ctrlc(); /* forget any previous Control C */

	if(!cmd || !*cmd){
		return(-1); /* empty command */
	}

	if(strlen(cmd) >= CFG_CBSIZE){
		puts("## Error: command too long!\n");
		return(-1);
	}

	strcpy(cmdbuf, cmd);

	/* Process separators and check for invalid
	 * repeatable commands
	 */
	while(*str){

		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for(inquotes = 0, sep = str; *sep; sep++){
			if((*sep == '\'') && (*(sep - 1) != '\\')){
				inquotes = !inquotes;
			}

			if(!inquotes && (*sep == ';') && (sep != str) && (*(sep - 1) != '\\')){
				break;
			}
		}

		/*
		 * Limit the token to data between separators
		 */
		token = str;
		if(*sep){
			str = sep + 1; /* start of command for next pass */
			*sep = '\0';
		} else {
			str = sep; /* no more commands for next pass */
		}

		/* find macros in this token and replace them */
		process_macros(token, finaltoken);

		/* Extract arguments */
		if((argc = parse_line(finaltoken, argv)) == 0){
			rc = -1; /* no command at all */
			continue;
		}

		/* Look up command in command table */
		if((cmdtp = find_cmd(argv[0])) == NULL){
			printf("## Error: unknown command '%s' - try 'help'\n\n", argv[0]);
			rc = -1; /* give up after bad command */
			continue;
		}

		/* found - check max args */
		if(argc > cmdtp->maxargs){
#ifdef CFG_LONGHELP
			if(cmdtp->help != NULL){
				printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
			} else {
				printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
			}
#else
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
			rc = -1;
			continue;
		}

		/* OK - call function to do the command */
		if((cmdtp->cmd)(cmdtp, flag, argc, argv) != 0){
			rc = -1;
		}

		repeatable &= cmdtp->repeatable;

		/* Did the user stop this? */
		if(had_ctrlc()){ /* if stopped then not repeatable */
			return(0);
		}
	}

	return(rc ? rc : repeatable);
}

/****************************************************************************/

#if (CONFIG_COMMANDS & CFG_CMD_RUN)
int do_run(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	int i;

	if(argc < 2){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	for(i=1; i<argc; ++i){
		char *arg;

		if((arg = getenv(argv[i])) == NULL){
			printf("## Error: \"%s\" not defined\n", argv[i]);
			return(1);
		}
#ifndef CFG_HUSH_PARSER
		if(run_command(arg, flag) == -1){
			return(1);
		}
#else
		if (parse_string_outer(arg, FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0){
			return(1);
		}
#endif /* CFG_HUSH_PARSER */
	}

	return(0);
}
#endif	/* CFG_CMD_RUN */
