/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <asm/byteorder.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

/* #define DEBUG */

DECLARE_GLOBAL_DATA_PTR;

#define LINUX_MAX_ENVS	512
#define LINUX_MAX_ARGS	512

/* From cmd_bootm.c */
extern image_header_t header;

static int linux_argc;
static int linux_env_idx;

static char **linux_argv;
static char **linux_env;
static char  *linux_env_p;

#if defined(CONFIG_WASP_SUPPORT)
void wasp_set_cca(void)
{
	/* Set cache coherency attribute */
	asm("mfc0 $t0, $16\n"	/* CP0_CONFIG == 16 */
	    "li   $t1, ~7\n"
	    "and  $t0, $t0, $t1\n"
	    "ori  $t0, 3\n"	/* CONF_CM_CACHABLE_NONCOHERENT */
	    "mtc0 $t0, $16\n"	/* CP0_CONFIG == 16 */
	    "nop\n": : );
}
#endif

static void linux_params_init(ulong start, char *cmdline)
{
	char memstr[16];
	char *next, *quote, *argp;

	linux_argc = 1;
	linux_argv = (char **)start;
	linux_argv[0] = 0;
	argp = (char *)(linux_argv + LINUX_MAX_ARGS);

	next = cmdline;

	if (strstr(cmdline, "mem="))
		memstr[0] = 0;
	else
		memstr[0] = 1;

	while (cmdline && *cmdline && linux_argc < LINUX_MAX_ARGS) {
		quote = strchr(cmdline, '"');
		next  = strchr(cmdline, ' ');

		while (next != NULL && quote != NULL && quote < next) {
			/*
			 * We found a left quote before the next blank
			 * now we have to find the matching right quote
			 */
			next = strchr(quote + 1, '"');
			if (next != NULL) {
				quote = strchr(next + 1, '"');
				next  = strchr(next + 1, ' ');
			}
		}

		if (next == NULL)
			next = cmdline + strlen(cmdline);

		linux_argv[linux_argc] = argp;
		memcpy(argp, cmdline, next - cmdline);
		argp[next - cmdline] = 0;

		argp += next - cmdline + 1;
		linux_argc++;

		if (*next)
			next++;

		cmdline = next;
	}

	/* Add mem size to command line if it's missing' */
	if (memstr[0]) {
		sprintf(memstr, "mem=%luM", gd->ram_size >> 20);
		memcpy(argp, memstr, strlen(memstr) + 1);

		linux_argv[linux_argc] = argp;
		linux_argc++;

		argp += strlen(memstr) + 1;
	}

	linux_env = (char **)(((ulong)argp + 15) & ~15);
	linux_env[0] = 0;

	linux_env_p = (char *)(linux_env + LINUX_MAX_ENVS);
	linux_env_idx = 0;
}

static void linux_env_set(char *env_name, char *env_val)
{
	if (linux_env_idx < LINUX_MAX_ENVS - 1) {
		linux_env[linux_env_idx] = linux_env_p;

		strcpy(linux_env_p, env_name);
		linux_env_p += strlen(env_name);

		strcpy(linux_env_p, "=");
		linux_env_p += 1;

		strcpy(linux_env_p, env_val);
		linux_env_p += strlen(env_val);

		linux_env_p++;
		linux_env[++linux_env_idx] = 0;
	}
}

void do_bootm_linux(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int lsdk_kernel;
	char *cmdline, *s, buf[16];
	image_header_t *hdr = &header;
	void(*Kernel)(int, char **, char **);
	void(*LSDKKernel)(int, char **, ulong, ulong);

	cmdline = getenv("bootargs");

#if defined(DEBUG)
	printf("## Bootargs: '%s'\n", cmdline);
	printf("## Transferring control to Linux (at address 0x%08lx) ...\n",
	       (ulong)(ntohl(hdr->ih_ep)));
#endif

	linux_params_init(UNCACHED_SDRAM(gd->bd->bi_boot_params), cmdline);

#if defined(DEBUG)
	printf("## Giving linux memsize in MB, %lu\n", gd->ram_size >> 20);
#endif

	sprintf(buf, "%lu", gd->ram_size >> 20);
	linux_env_set("memsize", buf);

	sprintf(buf, "0x%X", (unsigned int)(gd->bd->bi_flashstart));
	linux_env_set("flash_start", buf);

	sprintf(buf, "0x%X", (unsigned int)(gd->bd->bi_flashsize));
	linux_env_set("flash_size", buf);

	/* We assume that the kernel is in place */
	printf("Starting kernel...\n\n");

#if defined(CONFIG_WASP_SUPPORT)
	wasp_set_cca();
#endif

#if defined(CONFIG_FOR_DRAGINO_V2) || defined(CONFIG_FOR_MESH_POTATO_V2)
	/* Restore WAN/LAN LEDs (BIT 3 and 7 in GPIO_FUNCTION_1) */
	ar7240_reg_wr(AR7240_GPIO_FUNC,
		      (ar7240_reg_rd(AR7240_GPIO_FUNC) | 0x88));
#endif

	/*
	 * In some of old Atheros LSDK based firmware versions (kernel 2.6.x),
	 * kernel expects RAM size (in bytes) in 3rd parameter and FLASH
	 * size (in MB) in 4th. Also, most of old TP-Link firmwares follow
	 * this 'broken' approach.
	 *
	 * To make it somehow universal, we will use here a dedicated env
	 * flag 'lsdk_kernel' - if it's set to > 0, RAM and FLASH sizes
	 * will be passed as 3rd and 4th parameters.
	 */
	s = getenv("lsdk_kernel");
	lsdk_kernel = s ? simple_strtol(s, NULL, 10) : 0;

	if (lsdk_kernel > 0) {
		LSDKKernel = (void (*)(int, char **,
				       ulong, ulong))ntohl(hdr->ih_ep);

		LSDKKernel(linux_argc, linux_argv, gd->ram_size,
			   gd->bd->bi_flashsize >> 20);
	} else {
		Kernel = (void (*)(int, char **, char **))ntohl(hdr->ih_ep);

		Kernel(linux_argc, linux_argv, linux_env);
	}
}
