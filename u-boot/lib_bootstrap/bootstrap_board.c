/*
 * (C) Copyright 2003
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
#include <malloc.h>
#include <devices.h>
#include <version.h>
#include <net.h>
#include <environment.h>
#include <tinf.h>
#include "LzmaWrapper.h"

/*#define DEBUG_ENABLE_BOOTSTRAP_PRINTF*/

DECLARE_GLOBAL_DATA_PTR;

#if (((CFG_ENV_ADDR+CFG_ENV_SIZE) < BOOTSTRAP_CFG_MONITOR_BASE) || \
	 (CFG_ENV_ADDR >= (BOOTSTRAP_CFG_MONITOR_BASE + CFG_MONITOR_LEN))) \
	 || defined(CFG_ENV_IS_IN_NVRAM)
	#define	TOTAL_MALLOC_LEN	(CFG_MALLOC_LEN + CFG_ENV_SIZE)
#else
	#define	TOTAL_MALLOC_LEN	CFG_MALLOC_LEN
#endif

#undef DEBUG

extern void bootstrap_relocate_code(ulong addr_sp, gd_t *gd, ulong addr_moni);

extern int timer_init(void);

extern ulong uboot_end_data_bootstrap;
extern ulong uboot_end_bootstrap;

/*
 * Begin and End of memory area for malloc(), and current "brk"
 */
static ulong mem_malloc_start;
static ulong mem_malloc_end;
static ulong mem_malloc_brk;

/*
 * The Malloc area is immediately below the monitor copy in DRAM
 */
static void mem_malloc_init(ulong dest_addr)
{
	/* ulong dest_addr = BOOTSTRAP_CFG_MONITOR_BASE + gd->reloc_off; */
	mem_malloc_end = dest_addr;
	mem_malloc_start = dest_addr - TOTAL_MALLOC_LEN;
	mem_malloc_brk = mem_malloc_start;

	memset((void *)mem_malloc_start, 0, mem_malloc_end - mem_malloc_start);
}

void *malloc(unsigned int size)
{
	if (size < (mem_malloc_end - mem_malloc_start)) {
		mem_malloc_start += size;
		return (void *)(mem_malloc_start - size);
	}

	return NULL;
}

void *realloc(void *src, unsigned int size)
{
	return NULL;
}

void free(void *src)
{
	return;
}

static int init_func_ram(void)
{
	if ((gd->ram_size = dram_init()) > 0)
		return 0;

	return 1;
}

/*
 * Breath some life into the board...
 *
 * The first part of initialization is running from Flash memory;
 * its main purpose is to initialize the RAM so that we
 * can relocate the monitor code to RAM.
 */

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependend #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int(init_fnc_t)(void);

init_fnc_t *init_sequence[] = { init_func_ram,
								NULL, };

void bootstrap_board_init_f(ulong bootflag)
{
	gd_t gd_data, *id;
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	ulong addr, addr_sp, len = (ulong)&uboot_end_bootstrap - BOOTSTRAP_CFG_MONITOR_BASE;
	ulong *s;

	/* Pointer is writable since we allocated a register for it */
	gd = &gd_data;

	/* Compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	memset((void *)gd, 0, sizeof(gd_t));

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0)
			hang();
	}

	/*
	 * Now that we have DRAM mapped and working, we can
	 * relocate the code and continue running from DRAM
	 */
	addr = CFG_SDRAM_BASE + gd->ram_size;

	/*
	 * We can reserve some RAM "on top" here,
	 * round down to next 4 kB limit
	 */
	addr &= ~(4096 - 1);

	/*
	 * Reserve memory for U-Boot code, data & bss,
	 * round down to next 16 kB limit
	 */
	addr -= len;
	addr &= ~(16 * 1024 - 1);

	/* Reserve memory for malloc() arena */
	addr_sp = addr - TOTAL_MALLOC_LEN;

	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof(bd_t);
	bd = (bd_t *)addr_sp;
	gd->bd = bd;

	addr_sp -= sizeof(gd_t);
	id = (gd_t *)addr_sp;

	/* Reserve memory for boot params */
	addr_sp -= CFG_BOOTPARAMS_LEN;
	bd->bi_boot_params = addr_sp;

	/*
	 * Finally, we set up a new (bigger) stack
	 *
	 * Leave some safety gap for SP, force alignment on 16 byte boundary,
	 * clear initial stack frame
	 */
	addr_sp -= 16;
	addr_sp &= ~0xF;
	s = (ulong *)addr_sp;
	*s-- = 0;
	*s-- = 0;
	addr_sp = (ulong)s;

	/*
	 * Save local variables to board info struct:
	 * - start of DRAM memory
	 * - size  of DRAM memory in bytes
	 */
	bd->bi_memstart = CFG_SDRAM_BASE;
	bd->bi_memsize  = gd->ram_size;

	memcpy(id, (void *)gd, sizeof(gd_t));

	bootstrap_relocate_code(addr_sp, id, addr);
	/* NOTREACHED - relocate_code() does not return */
}

/************************************************************************
 *
 * This is the next part if the initialization sequence: we are now
 * running from RAM and have a "normal" C environment, i. e. global
 * data can be written, BSS has been cleared, the stack size in not
 * that critical any more, etc.
 *
 ************************************************************************
 */
void bootstrap_board_init_r(gd_t *id, ulong dest_addr)
{
	int i;
	ulong addr;
	ulong data, len, checksum;
	image_header_t header;
	image_header_t *hdr = &header;
	unsigned int destLen;
	int (*fn)(int);

	/* Initialize malloc() area */
	mem_malloc_init(dest_addr);

	addr = (ulong)((char *)(BOOTSTRAP_CFG_MONITOR_BASE + ((ulong)&uboot_end_data_bootstrap - dest_addr)));
	memmove(&header, (char *)addr, sizeof(image_header_t));

	if (ntohl(hdr->ih_magic) != IH_MAGIC)
		return;

	data = (ulong)&header;
	len = sizeof(image_header_t);

	checksum = ntohl(hdr->ih_hcrc);
	hdr->ih_hcrc = 0;

	if (tinf_crc32((unsigned char *)data, len) != checksum)
		return;

	data = addr + sizeof(image_header_t);
	len = ntohl(hdr->ih_size);

	/*
	 * If we've got less than 4 MB of malloc() space,
	 * use slower decompression algorithm which requires
	 * at most 2300 KB of memory.
	 */
	destLen = 0x0;

#ifdef CONFIG_LZMA
	i = lzma_inflate((unsigned char *)data, len, (unsigned char*)ntohl(hdr->ih_load), (int *)&destLen);

	if (i != LZMA_RESULT_OK)
		return;
#endif

	fn = (void *)ntohl(hdr->ih_load);

	(*fn)(gd->ram_size);

	hang();
}

void hang(void)
{
	for (;;)
		;
}
