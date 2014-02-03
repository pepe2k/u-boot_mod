/*
 * (C) Copyright 2000-2003
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

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

#if defined(CONFIG_I386) || defined(CONFIG_MIPS)
DECLARE_GLOBAL_DATA_PTR;
#endif

int do_go(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr, rc;
	int rcode = 0;

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

	addr = simple_strtoul(argv[1], NULL, 16);

	printf("## Starting application at 0x%08lX...\n", addr);

	/*
	 * Pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = ((ulong (*)(int, char *[]))addr)(--argc, &argv[1]);

	if(rc != 0){
		rcode = 1;
	}

	printf("## Application terminated, rc = 0x%lX\n", rc);

	return(rcode);
}

U_BOOT_CMD(go, CFG_MAXARGS, 1, do_go, "start application at address 'addr'\n",
		"addr [arg ...]\n"
		"\t- start application at address 'addr'\n"
		"\t  passing 'arg' as arguments\n");

extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

U_BOOT_CMD(reset, 1, 0, do_reset, "perform RESET of the CPU\n", NULL);
