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
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <malloc.h>
#include <devices.h>
#include <version.h>
#include <net.h>
#include <environment.h>

DECLARE_GLOBAL_DATA_PTR;

/*#define	BOARD_DEBUG*/

#if (((CFG_ENV_ADDR+CFG_ENV_SIZE) < CFG_MONITOR_BASE) || \
	 (CFG_ENV_ADDR >= (CFG_MONITOR_BASE + CFG_MONITOR_LEN))) \
	 || defined(CFG_ENV_IS_IN_NVRAM)
	#define	TOTAL_MALLOC_LEN	(CFG_MALLOC_LEN + CFG_ENV_SIZE)
#else
	#define	TOTAL_MALLOC_LEN	CFG_MALLOC_LEN
#endif

extern ulong uboot_end_data;
extern ulong uboot_end;

ulong monitor_flash_len;

const char version_string[] = U_BOOT_VERSION;

/* Begin and end of memory area for malloc(), and current "brk" */
static ulong mem_malloc_start;
static ulong mem_malloc_end;
static ulong mem_malloc_brk;

/* The Malloc area is immediately below the monitor copy in DRAM */
static void mem_malloc_init(void)
{
	ulong dest_addr = CFG_MONITOR_BASE + gd->reloc_off;

	mem_malloc_end = dest_addr;
	mem_malloc_start = dest_addr - TOTAL_MALLOC_LEN;
	mem_malloc_brk = mem_malloc_start;

	memset((void *)mem_malloc_start, 0, mem_malloc_end - mem_malloc_start);
}

void *sbrk(ptrdiff_t increment)
{
	ulong old = mem_malloc_brk;
	ulong new = old + increment;

	if ((new < mem_malloc_start) || (new > mem_malloc_end)) {
		printf("## Error: sbrk: out of memory (%d requested > %d available)\n",
			increment, mem_malloc_end - old);

		return (void*)MORECORE_FAILURE;
	}

	mem_malloc_brk = new;

	return (void *)old;
}

static int display_banner(void)
{
	puts("\n");

#ifdef CONFIG_SKIP_LOWLEVEL_INIT
	puts("\n***************************************"
		 "\n*                                     *"
		 "\n*             RAM VERSION             *"
		 "\n*                                     *");
#endif

	printf("\n***************************************"
		   "\n*     %s     *"
		   "\n*        " __DATE__ ", " __TIME__ "        *"
		   "\n***************************************\n\n",
			version_string);

	return 0;
}

static int baudrate_init(void)
{
	char *s;

	if ((s = getenv("baudrate")) != NULL) {
		gd->baudrate = simple_strtoul(s, NULL, 10);
	} else {
		gd->baudrate = CONFIG_BAUDRATE;
	}

	return 0;
}

#ifndef COMPRESSED_UBOOT
static int init_func_ram(void)
{
	if ((gd->ram_size = dram_init()) > 0)
		return 0;

	puts("## Error on RAM initialization!\n");
	return 1;
}
#endif

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

#ifndef COMPRESSED_UBOOT
init_fnc_t *init_sequence[] = { timer_init,
								env_init,
								baudrate_init,
								serial_init,
								console_init_f,
								display_banner,
								init_func_ram,
								NULL, };
#else
init_fnc_t *init_sequence[] = { timer_init,
								env_init,
								baudrate_init,
								serial_init,
								console_init_f,
								display_banner,
								NULL, };
#endif

/*
 *
 * BOARD INITIALIZATION
 *
 */
void board_init_f(ulong bootflag)
{
	gd_t gd_data, *id;
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	ulong addr, addr_sp, len = (ulong)&uboot_end - CFG_MONITOR_BASE;
	ulong *s;

	/* Pointer is writable since we allocated a register for it */
	gd = &gd_data;

	/* Compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	memset((void *)gd, 0, sizeof(gd_t));

	/* Loop trough init_sequence */
	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0)
			hang();
	}

#ifdef COMPRESSED_UBOOT
	gd->ram_size = bootflag;
#endif

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

#ifdef BOARD_DEBUG
	printf("Top of RAM usable for U-Boot at: %08lX\n", addr);
#endif

	/*
	 * Reserve memory for U-Boot code, data & bss,
	 * round down to next 16 kB limit
	 */
	addr -= len;
	addr &= ~(16 * 1024 - 1);

#ifdef BOARD_DEBUG
	printf("Reserving %ldk for U-Boot at: %08lX\n", len >> 10, addr);
#endif

	/* Reserve memory for malloc() arena */
	addr_sp = addr - TOTAL_MALLOC_LEN;

#ifdef BOARD_DEBUG
	printf("Reserving %dk for malloc() at: %08lX\n", TOTAL_MALLOC_LEN >> 10, addr_sp);
#endif

	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof(bd_t);
	bd = (bd_t *)addr_sp;
	gd->bd = bd;

#ifdef BOARD_DEBUG
	printf("Reserving %d Bytes for Board Info at: %08lX\n", sizeof(bd_t), addr_sp);
#endif

	addr_sp -= sizeof(gd_t);
	id = (gd_t *)addr_sp;

#ifdef BOARD_DEBUG
	printf("Reserving %d Bytes for Global Data at: %08lX\n", sizeof(gd_t), addr_sp);
#endif

	/* Reserve memory for boot params */
	addr_sp -= CFG_BOOTPARAMS_LEN;
	bd->bi_boot_params = addr_sp;

#ifdef BOARD_DEBUG
	printf("Reserving %dk for boot params() at: %08lX\n", CFG_BOOTPARAMS_LEN >> 10, addr_sp);
#endif

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

#ifdef BOARD_DEBUG
	printf("Stack Pointer at: %08lX\n", addr_sp);
#endif

	/*
	 * Save local variables to board info struct:
	 * - start of DRAM memory
	 * - size  of DRAM memory in bytes
	 * - console baudrate
	 */
	bd->bi_memstart = CFG_SDRAM_BASE;
	bd->bi_memsize  = gd->ram_size;
	bd->bi_baudrate = gd->baudrate;

	memcpy(id, (void *)gd, sizeof(gd_t));

	relocate_code(addr_sp, id, addr);
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
void board_init_r(gd_t *id, ulong dest_addr)
{
	cmd_tbl_t *cmdtp;
	extern void malloc_bin_reloc(void);
#ifndef CFG_ENV_IS_NOWHERE
	extern char *env_name_spec;
#endif
	bd_t *bd;
	char *s;

	gd = id;

	/* Tell others: relocation done */
	gd->flags |= GD_FLG_RELOC;

	/* bd -> board data */
	bd = gd->bd;

#ifdef BOARD_DEBUG
	printf("Now running in RAM - U-Boot at: %08lX\n", dest_addr);
#endif

	/* We need (half of the) main CPU clock for udelay */
	bd->bi_cfg_hz = (u32)(main_cpu_clk() >> 1);

	gd->reloc_off = dest_addr - CFG_MONITOR_BASE;

	monitor_flash_len = (ulong)&uboot_end_data - dest_addr;

	/* We have to relocate the command table manually */
	for (cmdtp = &__u_boot_cmd_start; cmdtp != &__u_boot_cmd_end; cmdtp++) {
		ulong addr;

		addr = (ulong)(cmdtp->cmd) + gd->reloc_off;

		cmdtp->cmd = (int (*)(struct cmd_tbl_s *, int, int, char *[]))addr;

		addr = (ulong)(cmdtp->name) + gd->reloc_off;
		cmdtp->name = (char *)addr;

		if (cmdtp->usage) {
			addr = (ulong)(cmdtp->usage) + gd->reloc_off;
			cmdtp->usage = (char *)addr;
		}

#ifdef	CFG_LONGHELP
		if (cmdtp->help) {
			addr = (ulong)(cmdtp->help) + gd->reloc_off;
			cmdtp->help = (char *)addr;
		}
#endif
	}

	/* There are some other pointer constants we must deal with */
#ifndef CFG_ENV_IS_NOWHERE
	env_name_spec += gd->reloc_off;
#endif

	/* Configure available FLASH banks */
	bd->bi_flashstart = CFG_FLASH_BASE;
	bd->bi_flashsize  = flash_init();

#if CFG_MONITOR_BASE == CFG_FLASH_BASE
	/* Reserved area for U-Boot */
	bd->bi_flashoffset = monitor_flash_len;
#else
	bd->bi_flashoffset = 0;
#endif

	/* Initialize malloc() area */
	mem_malloc_init();
	malloc_bin_reloc();

	/* Relocate environment function pointers etc. */
	env_relocate();

	/* Local device IP address */
	bd->bi_ip_addr = getenv_IPaddr("ipaddr");

#if defined(CONFIG_PCI)
	/* Do pci configuration */
	pci_init();
#endif

	/* Leave this here (after malloc(), environment and PCI are working) */
	/* Initialize devices */
	devices_init();

	jumptable_init();

	/* Initialize the console (after the relocation and devices init) */
	console_init_r();

	/* Initialize from environment */
	if ((s = getenv("loadaddr")) != NULL)
		load_addr = simple_strtoul(s, NULL, 16);

#if (CONFIG_COMMANDS & CFG_CMD_NET)
	if ((s = getenv("bootfile")) != NULL)
		copy_filename(BootFile, s, sizeof(BootFile));
#endif

	/* Init MAC address in board data info */
	macaddr_init(bd->bi_enetaddr);

	/* Print some information about board */
	print_board_info();

#if (CONFIG_COMMANDS & CFG_CMD_NET)
	all_led_on();
	eth_initialize(gd->bd);
	all_led_off();
#endif

	/* main_loop() can return to retry autoboot, if so just run it again */
	for (;;)
		main_loop();

	/* NOTREACHED - no way out of command loop except booting */
}

void hang(void)
{
	puts("## ERROR ##\n");

	for (;;)
		;
}
