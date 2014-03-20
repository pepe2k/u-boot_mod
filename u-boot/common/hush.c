/* vi: set sw=4 ts=4: */
/*
 * sh.c -- a prototype Bourne shell grammar parser
 *      Intended to follow the original Thompson and Ritchie
 *      "small and simple is beautiful" philosophy, which
 *      incidentally is a good match to today's BusyBox.
 *
 * Copyright (C) 2000,2001  Larry Doolittle  <larry@doolittle.boa.org>
 *
 * Credits:
 *      The parser routines proper are all original material, first
 *      written Dec 2000 and Jan 2001 by Larry Doolittle.
 *      The execution engine, the builtins, and much of the underlying
 *      support has been adapted from busybox-0.49pre's lash,
 *      which is Copyright (C) 2000 by Lineo, Inc., and
 *      written by Erik Andersen <andersen@lineo.com>, <andersee@debian.org>.
 *      That, in turn, is based in part on ladsh.c, by Michael K. Johnson and
 *      Erik W. Troan, which they placed in the public domain.  I don't know
 *      how much of the Johnson/Troan code has survived the repeated rewrites.
 * Other credits:
 *      simple_itoa() was lifted from boa-0.93.15
 *      b_addchr() derived from similar w_addchar function in glibc-2.2
 *      setup_redirect(), redirect_opt_num(), and big chunks of main()
 *        and many builtins derived from contributions by Erik Andersen
 *      miscellaneous bugfixes from Matt Kraai
 *
 * There are two big (and related) architecture differences between
 * this parser and the lash parser.  One is that this version is
 * actually designed from the ground up to understand nearly all
 * of the Bourne grammar.  The second, consequential change is that
 * the parser and input reader have been turned inside out.  Now,
 * the parser is in control, and asks for input as needed.  The old
 * way had the input reader in control, and it asked for parsing to
 * take place as needed.  The new way makes it much easier to properly
 * handle the recursion implicit in the various substitutions, especially
 * across continuation lines.
 *
 * Bash grammar not implemented: (how many of these were in original sh?)
 *      $@ (those sure look like weird quoting rules)
 *      $_
 *      ! negation operator for pipes
 *      &> and >& redirection of stdout+stderr
 *      Brace Expansion
 *      Tilde Expansion
 *      fancy forms of Parameter Expansion
 *      aliases
 *      Arithmetic Expansion
 *      <(list) and >(list) Process Substitution
 *      reserved words: case, esac, select, function
 *      Here Documents ( << word )
 *      Functions
 * Major bugs:
 *      job handling woefully incomplete and buggy
 *      reserved word execution woefully incomplete and buggy
 * to-do:
 *      port selected bugfixes from post-0.49 busybox lash - done?
 *      finish implementing reserved words: for, while, until, do, done
 *      change { and } from special chars to reserved words
 *      builtins: break, continue, eval, return, set, trap, ulimit
 *      test magic exec
 *      handle children going into background
 *      clean up recognition of null pipes
 *      check setting of global_argc and global_argv
 *      control-C handling, probably with longjmp
 *      follow IFS rules more precisely, including update semantics
 *      figure out what to do with backslash-newline
 *      explain why we use signal instead of sigaction
 *      propagate syntax errors, die on resource errors?
 *      continuation lines, both explicit and implicit - done?
 *      memory leak finding and plugging - done?
 *      more testing, especially quoting rules and redirection
 *      document how quoting rules not precisely followed for variable assignments
 *      maybe change map[] to use 2-bit entries
 *      (eventually) remove all the printf's
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <malloc.h>         /* malloc, free, realloc*/
#include <linux/ctype.h>    /* isalpha, isdigit */
#include <common.h>        /* readline */
#include <hush.h>
#include <command.h>        /* find_cmd */
/*cmd_boot.c*/
extern int do_bootd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]); /* do_bootd */

#ifdef CFG_HUSH_PARSER
#define SPECIAL_VAR_SYMBOL 03

DECLARE_GLOBAL_DATA_PTR;

#define EXIT_SUCCESS 0
#define EOF -1
#define syntax() syntax_err()
#define xstrdup strdup
#define error_msg printf

typedef enum {
	PIPE_SEQ = 1, PIPE_AND = 2, PIPE_OR = 3, PIPE_BG = 4,
} pipe_style;

/* might eventually control execution */
typedef enum {
	RES_NONE = 0,
	RES_IF = 1,
	RES_THEN = 2,
	RES_ELIF = 3,
	RES_ELSE = 4,
	RES_FI = 5,
	RES_FOR = 6,
	RES_WHILE = 7,
	RES_UNTIL = 8,
	RES_DO = 9,
	RES_DONE = 10,
	RES_XXXX = 11,
	RES_IN = 12,
	RES_SNTX = 13
} reserved_style;
#define FLAG_END   (1<<RES_NONE)
#define FLAG_IF    (1<<RES_IF)
#define FLAG_THEN  (1<<RES_THEN)
#define FLAG_ELIF  (1<<RES_ELIF)
#define FLAG_ELSE  (1<<RES_ELSE)
#define FLAG_FI    (1<<RES_FI)
#define FLAG_FOR   (1<<RES_FOR)
#define FLAG_WHILE (1<<RES_WHILE)
#define FLAG_UNTIL (1<<RES_UNTIL)
#define FLAG_DO    (1<<RES_DO)
#define FLAG_DONE  (1<<RES_DONE)
#define FLAG_IN    (1<<RES_IN)
#define FLAG_START (1<<RES_XXXX)

/* This holds pointers to the various results of parsing */
struct p_context {
	struct child_prog *child;
	struct pipe *list_head;
	struct pipe *pipe;
	reserved_style w;
	int old_flag; /* for figuring out valid reserved words */
	struct p_context *stack;
	int type; /* define type of parser : ";$" common or special symbol */
/* How about quoting status? */
};

struct child_prog {
	char **argv; /* program name and arguments */
	int argc; /* number of program arguments */
	struct pipe *group; /* if non-NULL, first in group or subshell */
	int sp; /* number of SPECIAL_VAR_SYMBOL */
	int type;
};

struct pipe {
	int num_progs; /* total number of programs in job */
	struct child_prog *progs; /* array of commands in pipe */
	struct pipe *next; /* to track background commands */
	pipe_style followup; /* PIPE_BG, PIPE_SEQ, PIPE_OR, PIPE_AND */
	reserved_style r_mode; /* supports if, for, while, until */
};

struct variables {
	char *name;
	char *value;
	int flg_export;
	int flg_read_only;
	struct variables *next;
};

/* globals, connect us to the outside world
 * the first three support $?, $#, and $1 */
unsigned int last_return_code;
int nesting_level;

/* "globals" within this file */
static uchar *ifs;
static char map[256];
static int flag_repeat = 0;
static int do_repeat = 0;
static struct variables *top_vars = NULL;

#define B_CHUNK (100)
#define B_NOSPAC 1

typedef struct {
	char *data;
	int length;
	int maxlen;
	int quote;
	int nonnull;
} o_string;
#define NULL_O_STRING {NULL,0,0,0,0}
/* used for initialization:
 o_string foo = NULL_O_STRING; */

/* I can almost use ordinary FILE *.  Is open_memstream() universally
 * available?  Where is it documented? */
struct in_str {
	const char *p;
	int __promptme;
	int promptmode;
	int (*get)(struct in_str *);
	int (*peek)(struct in_str *);
};
#define b_getch(input) ((input)->get(input))
#define b_peek(input) ((input)->peek(input))

/* This should be in utility.c */
#ifdef DEBUG_SHELL
#define debug_printf printf             /* U-Boot debug flag */
#else
static inline void debug_printf(const char *format, ...) {
}
#endif
#define final_printf debug_printf

static void syntax_err(void) {
	printf("## Error: syntax error!\n");
}

static void *xmalloc(size_t size);
static void *xrealloc(void *ptr, size_t size);

/*   o_string manipulation: */
static int b_check_space(o_string *o, int len);
static int b_addchr(o_string *o, int ch);
static void b_reset(o_string *o);
static int b_addqchr(o_string *o, int ch, int quote);

/*  in_str manipulations: */
static int static_get(struct in_str *i);
static int static_peek(struct in_str *i);
static int file_get(struct in_str *i);
static int file_peek(struct in_str *i);
static void setup_file_in_str(struct in_str *i);
static void setup_string_in_str(struct in_str *i, const char *s);

/*  "run" the final data structures: */
static char *indenter(int i);
static int free_pipe_list(struct pipe *head, int indent);
static int free_pipe(struct pipe *pi, int indent);

/*  really run the final data structures: */
static int run_list_real(struct pipe *pi);
static int run_pipe_real(struct pipe *pi);

/*   variable assignment: */
static int is_assignment(const char *s);

/*   data structure manipulation: */
static void initialize_context(struct p_context *ctx);
static int done_word(o_string *dest, struct p_context *ctx);
static int done_command(struct p_context *ctx);
static int done_pipe(struct p_context *ctx, pipe_style type);

/*   primary string parsing: */
static char *lookup_param(char *src);
static char *make_string(char **inp);
static int handle_dollar(o_string *dest, struct p_context *ctx,
		struct in_str *input);
static int parse_stream(o_string *dest, struct p_context *ctx,
		struct in_str *input0, int end_trigger);

/*   setup: */
static int parse_stream_outer(struct in_str *inp, int flag);

/*     local variable support */
static char **make_list_in(char **inp, char *name);
static char *insert_var_value(char *inp);
static char *get_local_var(const char *var);
static int set_local_var(const char *s, int flg_export);

static int b_check_space(o_string *o, int len) {
	/* It would be easy to drop a more restrictive policy
	 * in here, such as setting a maximum string length */
	if (o->length + len > o->maxlen) {
		char *old_data = o->data;
		/* assert (data == NULL || o->maxlen != 0); */
		o->maxlen += max(2 * len, B_CHUNK);
		o->data = realloc(o->data, 1 + o->maxlen);
		if (o->data == NULL) {
			free(old_data);
		}
	}
	return o->data == NULL;
}

static int b_addchr(o_string *o, int ch) {
	debug_printf("b_addchr: %c %d %p\n", ch, o->length, o);
	if (b_check_space(o, 1))
		return B_NOSPAC;
	o->data[o->length] = ch;
	o->length++;
	o->data[o->length] = '\0';
	return 0;
}

static void b_reset(o_string *o) {
	o->length = 0;
	o->nonnull = 0;
	if (o->data != NULL)
		*o->data = '\0';
}

static void b_free(o_string *o) {
	b_reset(o);
	free(o->data);
	o->data = NULL;
	o->maxlen = 0;
}

/* My analysis of quoting semantics tells me that state information
 * is associated with a destination, not a source.
 */
static int b_addqchr(o_string *o, int ch, int quote) {
	if (quote && strchr("*?[\\", ch)) {
		int rc;
		rc = b_addchr(o, '\\');
		if (rc)
			return rc;
	}
	return b_addchr(o, ch);
}

/* belongs in utility.c */
char *simple_itoa(unsigned int i) {
	/* 21 digits plus null terminator, good for 64-bit or smaller ints */
	static char local[22];
	char *p = &local[21];
	*p-- = '\0';
	do {
		*p-- = '0' + i % 10;
		i /= 10;
	} while (i > 0);
	return p + 1;
}

static int static_get(struct in_str *i) {
	int ch = *i->p++;
	if (ch == '\0')
		return EOF;
	return ch;
}

static int static_peek(struct in_str *i) {
	return *i->p;
}

static void get_user_input(struct in_str *i) {
	extern char console_buffer[CFG_CBSIZE];
	int n;
	static char the_command[CFG_CBSIZE];

#ifdef CONFIG_BOOT_RETRY_TIME
#  ifdef CONFIG_RESET_TO_RETRY
	extern int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
#  else
#	error "This currently only works with CONFIG_RESET_TO_RETRY enabled"
#  endif
	reset_cmd_timeout();
#endif
	i->__promptme = 1;
	if (i->promptmode == 1) {
		n = readline(CFG_PROMPT);
	} else {
		n = readline(CFG_PROMPT_HUSH_PS2);
	}
#ifdef CONFIG_BOOT_RETRY_TIME
	if (n == -2) {
		puts("\nTimeout waiting for command\n");
#  ifdef CONFIG_RESET_TO_RETRY
		do_reset(NULL, 0, 0, NULL);
#  else
#	error "This currently only works with CONFIG_RESET_TO_RETRY enabled"
#  endif
	}
#endif
	if (n == -1) {
		flag_repeat = 0;
		i->__promptme = 0;
	}
	n = strlen(console_buffer);
	console_buffer[n] = '\n';
	console_buffer[n + 1] = '\0';
	if (had_ctrlc())
		flag_repeat = 0;
	clear_ctrlc();
	do_repeat = 0;
	if (i->promptmode == 1) {
		if (console_buffer[0] == '\n' && flag_repeat == 0) {
			strcpy(the_command, console_buffer);
		} else {
			if (console_buffer[0] != '\n') {
				strcpy(the_command, console_buffer);
				flag_repeat = 1;
			} else {
				do_repeat = 1;
			}
		}
		i->p = the_command;
	} else {
		if (console_buffer[0] != '\n') {
			if (strlen(the_command) + strlen(console_buffer) < CFG_CBSIZE) {
				n = strlen(the_command);
				the_command[n - 1] = ' ';
				strcpy(&the_command[n], console_buffer);
			} else {
				the_command[0] = '\n';
				the_command[1] = '\0';
				flag_repeat = 0;
			}
		}
		if (i->__promptme == 0) {
			the_command[0] = '\n';
			the_command[1] = '\0';
		}
		i->p = console_buffer;
	}
}

/* This is the magic location that prints prompts
 * and gets data back from the user */
static int file_get(struct in_str *i) {
	int ch;

	ch = 0;
	/* If there is data waiting, eat it up */
	if (i->p && *i->p) {
		ch = *i->p++;
	} else {
		/* need to double check i->file because we might be doing something
		 * more complicated by now, like sourcing or substituting. */
		while (!i->p || strlen(i->p) == 0) {
			get_user_input(i);
		}

		i->promptmode = 2;

		if (i->p && *i->p) {
			ch = *i->p++;
		}
		debug_printf("b_getch: got a %d\n", ch);
	}

	return ch;
}

/* All the callers guarantee this routine will never be
 * used right after a newline, so prompting is not needed.
 */
static int file_peek(struct in_str *i) {
	return *i->p;
}

static void setup_file_in_str(struct in_str *i) {
	i->peek = file_peek;
	i->get = file_get;
	i->__promptme = 1;
	i->promptmode = 1;
	i->p = NULL;
}

static void setup_string_in_str(struct in_str *i, const char *s) {
	i->peek = static_peek;
	i->get = static_get;
	i->__promptme = 1;
	i->promptmode = 1;
	i->p = s;
}

/* run_pipe_real() starts all the jobs, but doesn't wait for anything
 * to finish.  See checkjobs().
 *
 * return code is normally -1, when the caller has to wait for children
 * to finish to determine the exit status of the pipe.  If the pipe
 * is a simple builtin command, however, the action is done by the
 * time run_pipe_real returns, and the exit code is provided as the
 * return value.
 *
 * The input of the pipe is always stdin, the output is always
 * stdout.  The outpipe[] mechanism in BusyBox-0.48 lash is bogus,
 * because it tries to avoid running the command substitution in
 * subshell, when that is in fact necessary.  The subshell process
 * now has its stdout directed to the input of the appropriate pipe,
 * so this routine is noticeably simpler.
 */
static int run_pipe_real(struct pipe *pi) {
	int i;
	int nextin;
	int flag = do_repeat ? CMD_FLAG_REPEAT : 0;
	struct child_prog *child;
	cmd_tbl_t *cmdtp;
	char *p;
# if __GNUC__
	/* Avoid longjmp clobbering */
	(void) &i;
	(void) &nextin;
	(void) &child;
# endif

	nextin = 0;

	/* Check if this is a simple builtin (not part of a pipe).
	 * Builtins within pipes have to fork anyway, and are handled in
	 * pseudo_exec.  "echo foo | read bar" doesn't work on bash, either.
	 */
	if (pi->num_progs == 1)
		child = &(pi->progs[0]);
	if (pi->num_progs == 1 && child->group) {
		int rcode;
		debug_printf("non-subshell grouping\n");
		rcode = run_list_real(child->group);
		return rcode;
	} else if (pi->num_progs == 1 && pi->progs[0].argv != NULL) {
		for (i = 0; is_assignment(child->argv[i]); i++) { /* nothing */
		}
		if (i != 0 && child->argv[i] == NULL) {
			/* assignments, but no command: set the local environment */
			for (i = 0; child->argv[i] != NULL; i++) {

				/* Ok, this case is tricky.  We have to decide if this is a
				 * local variable, or an already exported variable.  If it is
				 * already exported, we have to export the new value.  If it is
				 * not exported, we need only set this as a local variable.
				 * This junk is all to decide whether or not to export this
				 * variable. */
				int export_me = 0;
				char *name, *value;
				name = xstrdup(child->argv[i]);
				debug_printf("Local environment set: %s\n", name);
				value = strchr(name, '=');
				if (value)
					*value = 0;
				free(name);
				p = insert_var_value(child->argv[i]);
				set_local_var(p, export_me);
				if (p != child->argv[i])
					free(p);
			}
			return EXIT_SUCCESS; /* don't worry about errors in set_local_var() yet */
		}
		for (i = 0; is_assignment(child->argv[i]); i++) {
			p = insert_var_value(child->argv[i]);
			set_local_var(p, 0);
			if (p != child->argv[i]) {
				child->sp--;
				free(p);
			}
		}
		if (child->sp) {
			char * str = NULL;

			str = make_string((child->argv + i));
			parse_string_outer(str, FLAG_EXIT_FROM_LOOP | FLAG_REPARSING);
			free(str);
			return last_return_code;
		}

		/* check ";", because ,example , argv consist from
		 * "help;flinfo" must not execute
		 */
		if (strchr(child->argv[i], ';')) {
			printf("## Error: unknown command '%s' - try 'help' or use 'run' command\n", child->argv[i]);
			return -1;
		}

		/* Look up command in command table */
		if ((cmdtp = find_cmd(child->argv[i])) == NULL) {
			printf("## Error: unknown command '%s' - try 'help'\n", child->argv[i]);
			return -1; /* give up after bad command */
		} else {
			int rcode;
#if (CONFIG_COMMANDS & CFG_CMD_BOOTD)
			extern int do_bootd (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

			/* avoid "bootd" recursion */
			if (cmdtp->cmd == do_bootd) {
				if (flag & CMD_FLAG_BOOTD) {
					printf ("## Error: 'bootd' recursion detected!\n");
					return -1;
				} else {
					flag |= CMD_FLAG_BOOTD;
				}
			}
#endif	/* CFG_CMD_BOOTD */
			/* found - check max args */
			if ((child->argc - i) > cmdtp->maxargs) {
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
				return -1;
			}
			child->argv += i; /* XXX horrible hack */
			/* OK - call function to do the command */
			rcode = (cmdtp->cmd)(cmdtp, flag, child->argc - i, &child->argv[i]);

			if (!cmdtp->repeatable)
				flag_repeat = 0;

			child->argv -= i; /* XXX restore hack so free() can work right */

			return rcode;
		}
	}
	return -1;
}

static int run_list_real(struct pipe *pi) {
	char *save_name = NULL;
	char **list = NULL;
	char **save_list = NULL;
	struct pipe *rpipe;
	int flag_rep = 0;
	int rcode = 0, flag_skip = 1;
	int flag_restore = 0;
	int if_code = 0, next_if_code = 0; /* need double-buffer to handle elif */
	reserved_style rmode, skip_more_in_this_rmode = RES_XXXX;
	/* check syntax for "for" */
	for (rpipe = pi; rpipe; rpipe = rpipe->next) {
		if ((rpipe->r_mode == RES_IN || rpipe->r_mode == RES_FOR)
				&& (rpipe->next == NULL)) {
			syntax();
			flag_repeat = 0;
			return 1;
		}
		if ((rpipe->r_mode == RES_IN
				&& (rpipe->next->r_mode == RES_IN
						&& rpipe->next->progs->argv != NULL))
				|| (rpipe->r_mode == RES_FOR && rpipe->next->r_mode != RES_IN)) {
			syntax();
			flag_repeat = 0;
			return 1;
		}
	}
	for (; pi; pi = (flag_restore != 0) ? rpipe : pi->next) {
		if (pi->r_mode == RES_WHILE || pi->r_mode == RES_UNTIL
				|| pi->r_mode == RES_FOR) {
			/* check Ctrl-C */
			ctrlc();
			if ((had_ctrlc())) {
				return 1;
			}
			flag_restore = 0;
			if (!rpipe) {
				flag_rep = 0;
				rpipe = pi;
			}
		}
		rmode = pi->r_mode;
		debug_printf("rmode=%d  if_code=%d  next_if_code=%d skip_more=%d\n",
				rmode, if_code, next_if_code, skip_more_in_this_rmode);
		if (rmode == skip_more_in_this_rmode && flag_skip) {
			if (pi->followup == PIPE_SEQ)
				flag_skip = 0;
			continue;
		}
		flag_skip = 1;
		skip_more_in_this_rmode = RES_XXXX;
		if (rmode == RES_THEN || rmode == RES_ELSE)
			if_code = next_if_code;
		if (rmode == RES_THEN && if_code)
			continue;
		if (rmode == RES_ELSE && !if_code)
			continue;
		if (rmode == RES_ELIF && !if_code)
			break;
		if (rmode == RES_FOR && pi->num_progs) {
			if (!list) {
				/* if no variable values after "in" we skip "for" */
				if (!pi->next->progs->argv)
					continue;
				/* create list of variable values */
				list = make_list_in(pi->next->progs->argv, pi->progs->argv[0]);
				save_list = list;
				save_name = pi->progs->argv[0];
				pi->progs->argv[0] = NULL;
				flag_rep = 1;
			}
			if (!(*list)) {
				free(pi->progs->argv[0]);
				free(save_list);
				list = NULL;
				flag_rep = 0;
				pi->progs->argv[0] = save_name;
				continue;
			} else {
				/* insert new value from list for variable */
				if (pi->progs->argv[0])
					free(pi->progs->argv[0]);
				pi->progs->argv[0] = *list++;
			}
		}
		if (rmode == RES_IN)
			continue;
		if (rmode == RES_DO) {
			if (!flag_rep)
				continue;
		}
		if ((rmode == RES_DONE)) {
			if (flag_rep) {
				flag_restore = 1;
			} else {
				rpipe = NULL;
			}
		}
		if (pi->num_progs == 0)
			continue;
		rcode = run_pipe_real(pi);
		debug_printf("run_pipe_real returned %d\n", rcode);
		if (rcode < -1) {
			last_return_code = -rcode - 2;
			return -2; /* exit */
		}
		last_return_code = (rcode == 0) ? 0 : 1;

		if (rmode == RES_IF || rmode == RES_ELIF)
			next_if_code = rcode; /* can be overwritten a number of times */
		if (rmode == RES_WHILE)
			flag_rep = !last_return_code;
		if (rmode == RES_UNTIL)
			flag_rep = last_return_code;
		if ((rcode == EXIT_SUCCESS && pi->followup == PIPE_OR)
				|| (rcode != EXIT_SUCCESS && pi->followup == PIPE_AND))
			skip_more_in_this_rmode = rmode;
	}
	return rcode;
}

/* broken, of course, but OK for testing */
static char *indenter(int i) {
	static char blanks[] = "                                    ";
	return &blanks[sizeof(blanks) - i - 1];
}

/* return code is the exit status of the pipe */
static int free_pipe(struct pipe *pi, int indent) {
	char **p;
	struct child_prog *child;
	int a, i, ret_code = 0;
	char *ind = indenter(indent);

	for (i = 0; i < pi->num_progs; i++) {
		child = &pi->progs[i];
		final_printf("%s  command %d:\n", ind, i);
		if (child->argv) {
			for (a = 0, p = child->argv; *p; a++, p++) {
				final_printf("%s   argv[%d] = %s\n", ind, a, *p);
			}
			for (a = child->argc; a >= 0; a--) {
				free(child->argv[a]);
			}
			free(child->argv);
			child->argc = 0;
			child->argv = NULL;
		} else if (child->group) {
			ret_code = free_pipe_list(child->group, indent + 3);
			final_printf("%s   end group\n", ind);
		} else {
			final_printf("%s   (nil)\n", ind);
		}
	}
	free(pi->progs); /* children are an array, they get freed all at once */
	pi->progs = NULL;
	return ret_code;
}

static int free_pipe_list(struct pipe *head, int indent) {
	int rcode = 0; /* if list has no members */
	struct pipe *pi, *next;
	char *ind = indenter(indent);
	for (pi = head; pi; pi = next) {
		final_printf("%s pipe reserved mode %d\n", ind, pi->r_mode);
		rcode = free_pipe(pi, indent);
		final_printf("%s pipe followup code %d\n", ind, pi->followup);
		next = pi->next;
		pi->next = NULL;
		free(pi);
	}
	return rcode;
}

/* Select which version we will use */
static int run_list(struct pipe *pi) {
	int rcode = run_list_real(pi);

	/* free_pipe_list has the side effect of clearing memory
	 * In the long run that function can be merged with run_list_real,
	 * but doing that now would hobble the debugging effort. */
	free_pipe_list(pi, 0);
	return rcode;
}

static char *get_dollar_var(char ch);

/* This is used to get/check local shell variables */
static char *get_local_var(const char *s) {
	struct variables *cur;

	if (!s)
		return NULL;

	if (*s == '$')
		return get_dollar_var(s[1]);

	for (cur = top_vars; cur; cur = cur->next)
		if (strcmp(cur->name, s) == 0)
			return cur->value;
	return NULL;
}

/* This is used to set local shell variables
 flg_export==0 if only local (not exporting) variable
 flg_export==1 if "new" exporting environ
 flg_export>1  if current startup environ (not call putenv()) */
static int set_local_var(const char *s, int flg_export) {
	char *name, *value;
	int result = 0;
	struct variables *cur;

	/* might be possible! */
	if (!isalpha(*s))
		return -1;

	name = strdup(s);

	if (getenv(name) != NULL) {
		printf("## Error: there is a global environment variable with the same name!\n");
		free(name);
		return -1;
	}

	/* Assume when we enter this function that we are already in
	 * NAME=VALUE format.  So the first order of business is to
	 * split 's' on the '=' into 'name' and 'value' */
	value = strchr(name, '=');
	if (value == 0 && ++value == 0) {
		free(name);
		return -1;
	}
	*value++ = 0;

	for (cur = top_vars; cur; cur = cur->next) {
		if (strcmp(cur->name, name) == 0)
			break;
	}

	if (cur) {
		if (strcmp(cur->value, value) == 0) {
			if (flg_export > 0 && cur->flg_export == 0)
				cur->flg_export = flg_export;
			else
				result++;
		} else {
			if (cur->flg_read_only) {
				error_msg("%s: readonly variable", name);
				result = -1;
			} else {
				if (flg_export > 0 || cur->flg_export > 1)
					cur->flg_export = 1;
				free(cur->value);

				cur->value = strdup(value);
			}
		}
	} else {
		cur = malloc(sizeof(struct variables));
		if (!cur) {
			result = -1;
		} else {
			cur->name = strdup(name);
			if (cur->name == 0) {
				free(cur);
				result = -1;
			} else {
				struct variables *bottom = top_vars;
				cur->value = strdup(value);
				cur->next = 0;
				cur->flg_export = flg_export;
				cur->flg_read_only = 0;
				while (bottom->next)
					bottom = bottom->next;
				bottom->next = cur;
			}
		}
	}

	free(name);

	return result;
}

static int is_assignment(const char *s) {
	if (s == NULL)
		return 0;

	if (!isalpha(*s))
		return 0;
	++s;
	while (isalnum(*s) || *s == '_')
		++s;
	return *s == '=';
}

struct pipe *new_pipe(void) {
	struct pipe *pi;
	pi = xmalloc(sizeof(struct pipe));
	pi->num_progs = 0;
	pi->progs = NULL;
	pi->next = NULL;
	pi->followup = 0; /* invalid */
	pi->r_mode = RES_NONE;
	return pi;
}

static void initialize_context(struct p_context *ctx) {
	ctx->pipe = NULL;
	ctx->child = NULL;
	ctx->list_head = new_pipe();
	ctx->pipe = ctx->list_head;
	ctx->w = RES_NONE;
	ctx->stack = NULL;
	ctx->old_flag = 0;
	done_command(ctx); /* creates the memory for working child */
}

/* normal return is 0
 * if a reserved word is found, and processed, return 1
 * should handle if, then, elif, else, fi, for, while, until, do, done.
 * case, function, and select are obnoxious, save those for later.
 */
struct reserved_combo {
	char *literal;
	int code;
	long flag;
};
/* Mostly a list of accepted follow-up reserved words.
 * FLAG_END means we are done with the sequence, and are ready
 * to turn the compound list into a command.
 * FLAG_START means the word must start a new compound list.
 */
static struct reserved_combo reserved_list[] = { { "if", RES_IF, FLAG_THEN
		| FLAG_START }, { "then", RES_THEN, FLAG_ELIF | FLAG_ELSE | FLAG_FI }, {
		"elif", RES_ELIF, FLAG_THEN }, { "else", RES_ELSE, FLAG_FI }, { "fi",
		RES_FI, FLAG_END }, { "for", RES_FOR, FLAG_IN | FLAG_START }, { "while",
		RES_WHILE, FLAG_DO | FLAG_START }, { "until", RES_UNTIL, FLAG_DO
		| FLAG_START }, { "in", RES_IN, FLAG_DO }, { "do", RES_DO, FLAG_DONE },
		{ "done", RES_DONE, FLAG_END } };
#define NRES (sizeof(reserved_list)/sizeof(struct reserved_combo))

int reserved_word(o_string *dest, struct p_context *ctx) {
	struct reserved_combo *r;
	for (r = reserved_list; r < reserved_list + NRES; r++) {
		if (strcmp(dest->data, r->literal) == 0) {
			debug_printf("found reserved word %s, code %d\n", r->literal,
					r->code);
			if (r->flag & FLAG_START) {
				struct p_context *new = xmalloc(sizeof(struct p_context));
				debug_printf("push stack\n");
				if (ctx->w == RES_IN || ctx->w == RES_FOR) {
					syntax();
					free(new);
					ctx->w = RES_SNTX;
					b_reset(dest);
					return 1;
				}
				*new = *ctx; /* physical copy */
				initialize_context(ctx);
				ctx->stack = new;
			} else if (ctx->w == RES_NONE
					|| !(ctx->old_flag & (1 << r->code))) {
				syntax();
				ctx->w = RES_SNTX;
				b_reset(dest);
				return 1;
			}
			ctx->w = r->code;
			ctx->old_flag = r->flag;
			if (ctx->old_flag & FLAG_END) {
				struct p_context *old;
				debug_printf("pop stack\n");
				done_pipe(ctx, PIPE_SEQ);
				old = ctx->stack;
				old->child->group = ctx->list_head;
				*ctx = *old; /* physical copy */
				free(old);
			}
			b_reset(dest);
			return 1;
		}
	}
	return 0;
}

/* normal return is 0.
 * Syntax or xglob errors return 1. */
static int done_word(o_string *dest, struct p_context *ctx) {
	struct child_prog *child = ctx->child;
	char *str, *s;
	int argc, cnt;

	debug_printf("done_word: %s %p\n", dest->data, child);
	if (dest->length == 0 && !dest->nonnull) {
		debug_printf("  true null, ignored\n");
		return 0;
	}
	if (child->group) {
		syntax();
		return 1; /* syntax error, groups and arglists don't mix */
	}
	if (!child->argv && (ctx->type & FLAG_PARSE_SEMICOLON)) {
		debug_printf("checking %s for reserved-ness\n", dest->data);
		if (reserved_word(dest, ctx))
			return ctx->w == RES_SNTX;
	}
	for (cnt = 1, s = dest->data; s && *s; s++) {
		if (*s == '\\')
			s++;
		cnt++;
	}
	str = malloc(cnt);
	if (!str)
		return 1;
	if (child->argv == NULL) {
		child->argc = 0;
	}
	argc = ++child->argc;
	child->argv = realloc(child->argv, (argc + 1) * sizeof(*child->argv));
	if (child->argv == NULL)
		return 1;
	child->argv[argc - 1] = str;
	child->argv[argc] = NULL;
	for (s = dest->data; s && *s; s++, str++) {
		if (*s == '\\')
			s++;
		*str = *s;
	}

	*str = '\0';

	b_reset(dest);

	if (ctx->w == RES_FOR) {
		done_word(dest, ctx);
		done_pipe(ctx, PIPE_SEQ);
	}
	return 0;
}

/* The only possible error here is out of memory, in which case
 * xmalloc exits. */
static int done_command(struct p_context *ctx) {
	/* The child is really already in the pipe structure, so
	 * advance the pipe counter and make a new, null child.
	 * Only real trickiness here is that the uncommitted
	 * child structure, to which ctx->child points, is not
	 * counted in pi->num_progs. */
	struct pipe *pi = ctx->pipe;
	struct child_prog *prog = ctx->child;

	if (prog && prog->group == NULL && prog->argv == NULL) {
		debug_printf("done_command: skipping null command\n");
		return 0;
	} else if (prog) {
		pi->num_progs++;
		debug_printf("done_command: num_progs incremented to %d\n",
				pi->num_progs);
	} else {
		debug_printf("done_command: initializing\n");
	}
	pi->progs = xrealloc(pi->progs, sizeof(*pi->progs) * (pi->num_progs + 1));

	prog = pi->progs + pi->num_progs;
	prog->argv = NULL;
	prog->group = NULL;
	prog->sp = 0;
	ctx->child = prog;
	prog->type = ctx->type;

	/* but ctx->pipe and ctx->list_head remain unchanged */
	return 0;
}

static int done_pipe(struct p_context *ctx, pipe_style type) {
	struct pipe *new_p;
	done_command(ctx); /* implicit closure of previous command */
	debug_printf("done_pipe, type %d\n", type);
	ctx->pipe->followup = type;
	ctx->pipe->r_mode = ctx->w;
	new_p = new_pipe();
	ctx->pipe->next = new_p;
	ctx->pipe = new_p;
	ctx->child = NULL;
	done_command(ctx); /* set up new pipe to accept commands */
	return 0;
}

/* basically useful version until someone wants to get fancier,
 * see the bash man page under "Parameter Expansion" */
static char *lookup_param(char *src) {
	char *p;

	if (!src)
		return NULL;

	p = getenv(src);
	if (!p)
		p = get_local_var(src);

	return p;
}

static char *get_dollar_var(char ch) {
	static char buf[40];

	buf[0] = '\0';
	switch (ch) {
	case '?':
		sprintf(buf, "%u", (unsigned int) last_return_code);
		break;
	default:
		return NULL;
	}
	return buf;
}

/* return code: 0 for OK, 1 for syntax error */
static int handle_dollar(o_string *dest, struct p_context *ctx,
		struct in_str *input) {
	int advance = 0;
	int ch = input->peek(input); /* first character after the $ */
	debug_printf("handle_dollar: ch=%c\n", ch);
	if (isalpha(ch)) {
		b_addchr(dest, SPECIAL_VAR_SYMBOL);
		ctx->child->sp++;
		while (ch = b_peek(input), isalnum(ch) || ch == '_') {
			b_getch(input);
			b_addchr(dest, ch);
		}
		b_addchr(dest, SPECIAL_VAR_SYMBOL);
	} else
		switch (ch) {
		case '?':
			ctx->child->sp++;
			b_addchr(dest, SPECIAL_VAR_SYMBOL);
			b_addchr(dest, '$');
			b_addchr(dest, '?');
			b_addchr(dest, SPECIAL_VAR_SYMBOL);
			advance = 1;
			break;
		case '{':
			b_addchr(dest, SPECIAL_VAR_SYMBOL);
			ctx->child->sp++;
			b_getch(input);
			/* XXX maybe someone will try to escape the '}' */
			while (ch = b_getch(input), ch != EOF && ch != '}') {
				b_addchr(dest, ch);
			}
			if (ch != '}') {
				syntax();
				return 1;
			}
			b_addchr(dest, SPECIAL_VAR_SYMBOL);
			break;
		default:
			b_addqchr(dest, '$', dest->quote);
		}
	/* Eat the character if the flag was set.  If the compiler
	 * is smart enough, we could substitute "b_getch(input);"
	 * for all the "advance = 1;" above, and also end up with
	 * a nice size-optimized program.  Hah!  That'll be the day.
	 */
	if (advance)
		b_getch(input);
	return 0;
}

/* return code is 0 for normal exit, 1 for syntax error */
int parse_stream(o_string *dest, struct p_context *ctx, struct in_str *input,
		int end_trigger) {
	unsigned int ch, m;
	int next;

	/* Only double-quote state is handled in the state variable dest->quote.
	 * A single-quote triggers a bypass of the main loop until its mate is
	 * found.  When recursing, quote state is passed in via dest->quote. */

	debug_printf("parse_stream, end_trigger=%d\n", end_trigger);
	while ((ch = b_getch(input)) != EOF) {
		m = map[ch];
		if (input->__promptme == 0)
			return 1;

		next = (ch == '\n') ? 0 : b_peek(input);

		debug_printf("parse_stream: ch=%c (%d) m=%d quote=%d - %c\n",
				ch >= ' ' ? ch : '.', ch, m, dest->quote,
				ctx->stack == NULL ? '*' : '.');

		if (m == 0 || ((m == 1 || m == 2) && dest->quote)) {
			b_addqchr(dest, ch, dest->quote);
		} else {
			if (m == 2) { /* unquoted IFS */
				if (done_word(dest, ctx)) {
					return 1;
				}
				/* If we aren't performing a substitution, treat a newline as a
				 * command separator.  */
				if (end_trigger != '\0' && ch == '\n')
					done_pipe(ctx, PIPE_SEQ);
			}
			if (ch == end_trigger && !dest->quote && ctx->w == RES_NONE) {
				debug_printf("leaving parse_stream (triggered)\n");
				return 0;
			}
			if (m != 2)
				switch (ch) {
				case '#':
					if (dest->length == 0 && !dest->quote) {
						while (ch = b_peek(input), ch != EOF && ch != '\n') {
							b_getch(input);
						}
					} else {
						b_addqchr(dest, ch, dest->quote);
					}
					break;
				case '\\':
					if (next == EOF) {
						syntax();
						return 1;
					}
					b_addqchr(dest, '\\', dest->quote);
					b_addqchr(dest, b_getch(input), dest->quote);
					break;
				case '$':
					if (handle_dollar(dest, ctx, input) != 0)
						return 1;
					break;
				case '\'':
					dest->nonnull = 1;
					while (ch = b_getch(input), ch != EOF && ch != '\'') {
						if (input->__promptme == 0)
							return 1;
						b_addchr(dest, ch);
					}
					if (ch == EOF) {
						syntax();
						return 1;
					}
					break;
				case '"':
					dest->nonnull = 1;
					dest->quote = !dest->quote;
					break;
				case ';':
					done_word(dest, ctx);
					done_pipe(ctx, PIPE_SEQ);
					break;
				case '&':
					done_word(dest, ctx);
					if (next == '&') {
						b_getch(input);
						done_pipe(ctx, PIPE_AND);
					} else {
						syntax_err();
						return 1;
					}
					break;
				case '|':
					done_word(dest, ctx);
					if (next == '|') {
						b_getch(input);
						done_pipe(ctx, PIPE_OR);
					} else {
						/* we could pick up a file descriptor choice here
						 * with redirect_opt_num(), but bash doesn't do it.
						 * "echo foo 2| cat" yields "foo 2". */
						syntax_err();
						return 1;
					}
					break;
				default:
					syntax(); /* this is really an internal logic error */
					return 1;
				}
		}
	}
	/* complain if quote?  No, maybe we just finished a command substitution
	 * that was quoted.  Example:
	 * $ echo "`cat foo` plus more"
	 * and we just got the EOF generated by the subshell that ran "cat foo"
	 * The only real complaint is if we got an EOF when end_trigger != '\0',
	 * that is, we were really supposed to get end_trigger, and never got
	 * one before the EOF.  Can't use the standard "syntax error" return code,
	 * so that parse_stream_outer can distinguish the EOF and exit smoothly. */
	debug_printf("leaving parse_stream (EOF)\n");
	if (end_trigger != '\0')
		return -1;
	return 0;
}

void mapset(const unsigned char *set, int code) {
	const unsigned char *s;
	for (s = set; *s; s++)
		map[*s] = code;
}

void update_ifs_map(void) {
	/* char *ifs and char map[256] are both globals. */
	ifs = (uchar *) getenv("IFS");
	if (ifs == NULL)
		ifs = (uchar *) " \t\n";
	/* Precompute a list of 'flow through' behavior so it can be treated
	 * quickly up front.  Computation is necessary because of IFS.
	 * Special case handling of IFS == " \t\n" is not implemented.
	 * The map[] array only really needs two bits each, and on most machines
	 * that would be faster because of the reduced L1 cache footprint.
	 */
	memset(map, 0, sizeof(map)); /* most characters flow through always */
	mapset((uchar *) "\\$'\"", 3); /* never flow through */
	mapset((uchar *) ";&|#", 1); /* flow through if quoted */
	mapset(ifs, 2); /* also flow through if quoted */
}

/* most recursion does not come through here, the exeception is
 * from builtin_source() */
int parse_stream_outer(struct in_str *inp, int flag) {

	struct p_context ctx;
	o_string temp = NULL_O_STRING;
	int rcode;
	int code = 0;
	do {
		ctx.type = flag;
		initialize_context(&ctx);
		update_ifs_map();
		if (!(flag & FLAG_PARSE_SEMICOLON) || (flag & FLAG_REPARSING))
			mapset((uchar *) ";$&|", 0);
		inp->promptmode = 1;
		rcode = parse_stream(&temp, &ctx, inp, '\n');
		if (rcode == 1)
			flag_repeat = 0;
		if (rcode != 1 && ctx.old_flag != 0) {
			syntax();
			flag_repeat = 0;
		}
		if (rcode != 1 && ctx.old_flag == 0) {
			done_word(&temp, &ctx);
			done_pipe(&ctx, PIPE_SEQ);
			code = run_list(ctx.list_head);
			if (code == -2) { /* exit */
				b_free(&temp);
				code = 0;
				/* XXX hackish way to not allow exit from main loop */
				if (inp->peek == file_peek) {
					printf("## Error: exit not allowed from main input shell!\n");
					continue;
				}
				break;
			}
			if (code == -1)
				flag_repeat = 0;
		} else {
			if (ctx.old_flag != 0) {
				free(ctx.stack);
				b_reset(&temp);
			}
			if (inp->__promptme == 0)
				printf("<INTERRUPT>\n");
			inp->__promptme = 1;
			temp.nonnull = 0;
			temp.quote = 0;
			inp->p = NULL;
			free_pipe_list(ctx.list_head, 0);
		}
		b_free(&temp);
	} while (rcode != -1 && !(flag & FLAG_EXIT_FROM_LOOP)); /* loop on syntax errors, return on EOF */

	return (code != 0) ? 1 : 0;
}

int parse_string_outer(char *s, int flag) {
	struct in_str input;
	char *p = NULL;
	int rcode;

	if (!s || !*s)
		return 1;

	if (!(p = strchr(s, '\n')) || *++p) {
		p = xmalloc(strlen(s) + 2);
		strcpy(p, s);
		strcat(p, "\n");
		setup_string_in_str(&input, p);
		rcode = parse_stream_outer(&input, flag);
		free(p);
		return rcode;
	} else {
		setup_string_in_str(&input, s);
		return parse_stream_outer(&input, flag);
	}
}

int parse_file_outer(void) {
	int rcode;
	struct in_str input;
	setup_file_in_str(&input);
	rcode = parse_stream_outer(&input, FLAG_PARSE_SEMICOLON);
	return rcode;
}

static void u_boot_hush_reloc(void) {
	unsigned long addr;
	struct reserved_combo *r;

	for (r = reserved_list; r < reserved_list + NRES; r++) {
		addr = (ulong) (r->literal) + gd->reloc_off;
		r->literal = (char *) addr;
	}
}

int u_boot_hush_start(void) {
	if (top_vars == NULL) {
		top_vars = malloc(sizeof(struct variables));
		top_vars->name = "HUSH_VERSION";
		top_vars->value = "0.01";
		top_vars->next = 0;
		top_vars->flg_export = 0;
		top_vars->flg_read_only = 1;
		u_boot_hush_reloc();
	}
	return 0;
}

static void *xmalloc(size_t size) {
	void *p = NULL;

	if (!(p = malloc(size))) {
		printf("## Error: memory not allocated!\n");
		for (;;)
			;
	}
	return p;
}

static void *xrealloc(void *ptr, size_t size) {
	void *p = NULL;

	if (!(p = realloc(ptr, size))) {
		printf("## Error: memory not allocated!\n");
		for (;;)
			;
	}
	return p;
}

static char *insert_var_value(char *inp) {
	int res_str_len = 0;
	int len;
	int done = 0;
	char *p, *p1, *res_str = NULL;

	while ((p = strchr(inp, SPECIAL_VAR_SYMBOL))) {
		if (p != inp) {
			len = p - inp;
			res_str = xrealloc(res_str, (res_str_len + len));
			strncpy((res_str + res_str_len), inp, len);
			res_str_len += len;
		}
		inp = ++p;
		p = strchr(inp, SPECIAL_VAR_SYMBOL);
		*p = '\0';
		if ((p1 = lookup_param(inp))) {
			len = res_str_len + strlen(p1);
			res_str = xrealloc(res_str, (1 + len));
			strcpy((res_str + res_str_len), p1);
			res_str_len = len;
		}
		*p = SPECIAL_VAR_SYMBOL;
		inp = ++p;
		done = 1;
	}
	if (done) {
		res_str = xrealloc(res_str, (1 + res_str_len + strlen(inp)));
		strcpy((res_str + res_str_len), inp);
		while ((p = strchr(res_str, '\n'))) {
			*p = ' ';
		}
	}
	return (res_str == NULL) ? inp : res_str;
}

static char **make_list_in(char **inp, char *name) {
	int len, i;
	int name_len = strlen(name);
	int n = 0;
	char **list;
	char *p1, *p2, *p3;

	/* create list of variable values */
	list = xmalloc(sizeof(*list));
	for (i = 0; inp[i]; i++) {
		p3 = insert_var_value(inp[i]);
		p1 = p3;
		while (*p1) {
			if ((*p1 == ' ')) {
				p1++;
				continue;
			}
			if ((p2 = strchr(p1, ' '))) {
				len = p2 - p1;
			} else {
				len = strlen(p1);
				p2 = p1 + len;
			}
			/* we use n + 2 in realloc for list,because we add
			 * new element and then we will add NULL element */
			list = xrealloc(list, sizeof(*list) * (n + 2));
			list[n] = xmalloc(2 + name_len + len);
			strcpy(list[n], name);
			strcat(list[n], "=");
			strncat(list[n], p1, len);
			list[n++][name_len + len + 1] = '\0';
			p1 = p2;
		}
		if (p3 != inp[i])
			free(p3);
	}
	list[n] = NULL;
	return list;
}

/* Make new string for parser */
static char * make_string(char ** inp) {
	char *p;
	char *str = NULL;
	int n;
	int len = 2;

	for (n = 0; inp[n]; n++) {
		p = insert_var_value(inp[n]);
		str = xrealloc(str, (len + strlen(p)));
		if (n) {
			strcat(str, " ");
		} else {
			*str = '\0';
		}
		strcat(str, p);
		len = strlen(str) + 3;
		if (p != inp[n])
			free(p);
	}
	len = strlen(str);
	*(str + len) = '\n';
	*(str + len + 1) = '\0';
	return str;
}

#endif /* CFG_HUSH_PARSER */
/****************************************************************************/
