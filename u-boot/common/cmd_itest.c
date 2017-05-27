/*
 * (C) Copyright 2003
 * Tait Electronics Limited, Christchurch, New Zealand
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file provides a shell like 'test' function to return
 * true/false from an integer or string compare of two memory
 * locations or a location and a scalar/literal.
 * A few parts were lifted from bash 'test' command
 */

#include <common.h>
#include <config.h>
#include <command.h>

#if defined(CONFIG_CMD_ITEST) ||\
    defined(CONFIG_CMD_SETEXPR)

extern int cmd_get_data_size(char* arg, int default_size);

static ulong evalexp(char *s, int w)
{
	ulong *p;
	ulong l = 0;

	/*
	 * If the parameter starts with a * then
	 * assume is a pointer to the value we want
	 */
	if (s[0] == '*') {
		p = (ulong *)simple_strtoul(&s[1], NULL, 16);
		l = *p;
	} else {
		l = simple_strtoul(s, NULL, 16);
	}

	if (w < 4)
		return l & ((1 << (w * 8)) - 1);
	else
		return l;
}
#endif /* CONFIG_CMD_ITEST || CONFIG_CMD_SETEXPR */

#if defined(CONFIG_CMD_SETEXPR)
int do_setexpr(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong a, b, value;
	char buf[16];
	int w;

	/*
	 * We take 3, 5, or 6 arguments:
	 * 3 : setexpr name value
	 * 5 : setexpr name val1 op val2
	 *     setexpr name [g]sub r s
	 * 6 : setexpr name [g]sub r s t
	 */

	/* > 6 already tested by max command args */
	if ((argc < 3) || (argc == 4)) {
		print_cmd_help(cmdtp);
		return 1;
	}

	w = cmd_get_data_size(argv[0], 4);

	a = evalexp(argv[2], w);

	/* Plain assignment: "setexpr name value" */
	if (argc == 3) {
		sprintf(buf, "%X", a);
		setenv(argv[1], buf);
		return 0;
	}

	/* Standard operators: "setexpr name val1 op val2" */
	if (argc != 5) {
		print_cmd_help(cmdtp);
		return 1;
	}

	if (strlen(argv[3]) != 1) {
		print_cmd_help(cmdtp);
		return 1;
	}

	b = evalexp(argv[4], w);

	switch (argv[3][0]) {
	case '|':
		value = a | b;
		break;
	case '&':
		value = a & b;
		break;
	case '+':
		value = a + b;
		break;
	case '^':
		value = a ^ b;
		break;
	case '-':
		value = a - b;
		break;
	case '*':
		value = a * b;
		break;
	case '/':
		value = a / b;
		break;
	case '%':
		value = a % b;
		break;
	default:
		printf_err("invalid op\n");
		return 1;
	}

	sprintf(buf, "%X", value);
	setenv(argv[1], buf);

	return 0;
}

U_BOOT_CMD(setexpr, 6, 0, do_setexpr, "set env variable as the result of eval expr\n",
	"[.b, .w, .l] name [*]val1 <op> [*]val2\n"
	"\t- set env variable 'name' to the result of the evaluated\n"
	"\t  expr specified by <op> (can be &, |, ^, +, -, *, /, %)\n"
	"\t  size argument is only meaningful if val1 and/or val2 are memory addresses (*)\n"
	"setexpr[.b, .w, .l] name [*]val\n"
	"\t- load a 'val' into 'name' variable");
#endif /* CONFIG_CMD_SETEXPR */

#if defined(CONFIG_CMD_ITEST)

#define EQ	0
#define NE	1
#define LT	2
#define GT	3
#define LE	4
#define GE	5

struct op_tbl_s {
	char *op;	/* Operator string */
	int opcode;	/* Internal representation of opcode */
};

typedef struct op_tbl_s op_tbl_t;

op_tbl_t op_table [] = {
	{ "-lt", LT },
	{ "<"  , LT },
	{ "-gt", GT },
	{ ">"  , GT },
	{ "-eq", EQ },
	{ "==" , EQ },
	{ "-ne", NE },
	{ "!=" , NE },
	{ "<>" , NE },
	{ "-ge", GE },
	{ ">=" , GE },
	{ "-le", LE },
	{ "<=" , LE },
};

#define op_tbl_size (sizeof(op_table)/sizeof(op_table[0]))


static char *evalstr(char *s)
{
	/*
	 * If the parameter starts with a * then
	 *assume a string pointer else its a literal
	 */
	if (s[0] == '*')
		return (char *)simple_strtoul(&s[1], NULL, 16);
	else
		return s;
}

static int stringcomp(char *s, char *t, int op)
{
	int n, p;
	char *l, *r;

	l = evalstr(s);
	r = evalstr(t);

	/* We'll do a compare based on the length of the shortest string */
	n = min(strlen(l), strlen(r));

	p = strncmp(l, r, n);

	switch (op) {
	case EQ:
		return p == 0;
	case NE:
		return p != 0;
	case LT:
		return p < 0;
	case GT:
		return p > 0;
	case LE:
		return p <= 0;
	case GE:
		return p >= 0;
	}

	return 0;
}

static int arithcomp(char *s, char *t, int op, int w)
{
	ulong l, r;

	l = evalexp(s, w);
	r = evalexp(t, w);

	switch (op) {
	case EQ:
		return l == r;
	case NE:
		return l != r;
	case LT:
		return l < r;
	case GT:
		return l > r;
	case LE:
		return l <= r;
	case GE:
		return l >= r;
	}

	return 0;
}

static int binary_test(char *op, char *arg1, char *arg2, int w)
{
	int len, i;
	op_tbl_t *optp;

	len = strlen(op);

	for (optp = (op_tbl_t *)&op_table, i = 0;
	     i < op_tbl_size; optp++, i++) {
		if ((strncmp(op, optp->op, len) == 0) &&
		    (len == strlen(optp->op))) {
			if (w == 0)
				return stringcomp(arg1, arg2, optp->opcode);
			else
				return arithcomp(arg1, arg2, optp->opcode, w);
		}
	}

	printf_err("unknown operator '%s'\n", op);

	/* Op code not found */
	return 0;
}

/* Command line interface to the shell test */
int do_itest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int value, w;

	/* Validate arguments */
	if ((argc != 4)) {
		print_cmd_help(cmdtp);
		return 1;
	}

	/*
	 * Check for a data width specification.
	 * Defaults to long (4) if no specification.
	 * Uses -2 as 'width' for .s (string) so as not to upset existing code
	 */
	switch (w = cmd_get_data_size(argv[0], 4)) {
	case 1:
	case 2:
	case 4:
		value = binary_test(argv[2], argv[1], argv[3], w);
		break;
	case -2:
		value = binary_test(argv[2], argv[1], argv[3], 0);
		break;
	case -1:
	default:
		printf_err("invalid data width specifier\n");
		value = 0;
		break;
	}

	return !value;
}

U_BOOT_CMD(itest, 4, 0, do_itest, "return true/false on int compare\n",
	"[.b, .w, .l, .s] [*]val1 <op> [*]val2\n");
#endif /* CONFIG_CMD_ITEST */
