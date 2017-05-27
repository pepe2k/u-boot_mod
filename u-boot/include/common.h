/*
 * (C) Copyright 2000-2004
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __COMMON_H_
#define __COMMON_H_	1

#undef	_LINUX_CONFIG_H
#define _LINUX_CONFIG_H 1	/* avoid reading Linux autoconf.h file	*/

typedef unsigned char		uchar;
typedef volatile unsigned long	vu_long;
typedef volatile unsigned short vu_short;
typedef volatile unsigned char	vu_char;

#include <config.h>
#include <linux/bitops.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/ptrace.h>
#include <stdarg.h>
#if defined(CONFIG_PCI) && defined(CONFIG_440)
#include <pci.h>
#endif
#if defined(CONFIG_8xx)
#include <asm/8xx_immap.h>
#if defined(CONFIG_MPC852)	|| defined(CONFIG_MPC852T)	|| \
    defined(CONFIG_MPC859)	|| defined(CONFIG_MPC859T)	|| \
    defined(CONFIG_MPC859DSL)	|| \
    defined(CONFIG_MPC866)	|| defined(CONFIG_MPC866T)	|| \
    defined(CONFIG_MPC866P)
# define CONFIG_MPC866_FAMILY 1
#elif defined(CONFIG_MPC870) \
   || defined(CONFIG_MPC875) \
   || defined(CONFIG_MPC880) \
   || defined(CONFIG_MPC885)
# define CONFIG_MPC885_FAMILY   1
#endif
#if   defined(CONFIG_MPC860)	   \
   || defined(CONFIG_MPC860T)	   \
   || defined(CONFIG_MPC866_FAMILY) \
   || defined(CONFIG_MPC885_FAMILY)
# define CONFIG_MPC86x 1
#endif
#elif defined(CONFIG_5xx)
#include <asm/5xx_immap.h>
#elif defined(CONFIG_MPC5xxx)
#include <mpc5xxx.h>
#elif defined(CONFIG_MPC8220)
#include <asm/immap_8220.h>
#elif defined(CONFIG_8260)
#if   defined(CONFIG_MPC8247) \
   || defined(CONFIG_MPC8248) \
   || defined(CONFIG_MPC8271) \
   || defined(CONFIG_MPC8272)
#define CONFIG_MPC8272_FAMILY	1
#endif
#if defined(CONFIG_MPC8272_FAMILY)
#define CONFIG_MPC8260	1
#endif
#include <asm/immap_8260.h>
#endif
#ifdef CONFIG_MPC85xx
#include <mpc85xx.h>
#include <asm/immap_85xx.h>
#endif
#ifdef CONFIG_MPC83XX
#include <mpc83xx.h>
#include <asm/immap_83xx.h>
#endif
#ifdef	CONFIG_4xx
#include <ppc4xx.h>
#endif
#ifdef CONFIG_HYMOD
#include <board/hymod/hymod.h>
#endif
#ifdef CONFIG_ARM
#define asmlinkage	/* nothing */
#endif

#include <flash.h>
#include <image.h>

#ifdef	DEBUG
#define debug(fmt,args...)	printf (fmt ,##args)
#define debugX(level,fmt,args...) if (DEBUG>=level) printf(fmt,##args);
#else
#define debug(fmt,args...)
#define debugX(level,fmt,args...)
#endif /* DEBUG */

typedef void (interrupt_handler_t)(void *);

#include <asm/u-boot.h> /* boot information for Linux kernel */
#include <asm/global_data.h>	/* global data used for startup functions */

/*
 * enable common handling for all TQM8xxL/M boards:
 * - CONFIG_TQM8xxM will be defined for all TQM8xxM boards
 * - CONFIG_TQM8xxL will be defined for all TQM8xxL _and_ TQM8xxM boards
 */
#if defined(CONFIG_TQM823M) || defined(CONFIG_TQM850M) || \
    defined(CONFIG_TQM855M) || defined(CONFIG_TQM860M) || \
    defined(CONFIG_TQM862M) || defined(CONFIG_TQM866M)
# ifndef CONFIG_TQM8xxM
#  define CONFIG_TQM8xxM
# endif
#endif
#if defined(CONFIG_TQM823L) || defined(CONFIG_TQM850L) || \
    defined(CONFIG_TQM855L) || defined(CONFIG_TQM860L) || \
    defined(CONFIG_TQM862L) || defined(CONFIG_TQM8xxM)
# ifndef CONFIG_TQM8xxL
#  define CONFIG_TQM8xxL
# endif
#endif

#ifndef CONFIG_SERIAL_MULTI

#if defined(CONFIG_8xx_CONS_SMC1) || defined(CONFIG_8xx_CONS_SMC2) \
 || defined(CONFIG_8xx_CONS_SCC1) || defined(CONFIG_8xx_CONS_SCC2) \
 || defined(CONFIG_8xx_CONS_SCC3) || defined(CONFIG_8xx_CONS_SCC4)

#define CONFIG_SERIAL_MULTI	1

#endif

#endif /* CONFIG_SERIAL_MULTI */

/*
 * General Purpose Utilities
 */
#define min(X, Y)				\
	({ typeof (X) __x = (X), __y = (Y);	\
		(__x < __y) ? __x : __y; })

#define max(X, Y)				\
	({ typeof (X) __x = (X), __y = (Y);	\
		(__x > __y) ? __x : __y; })


/*
 * Function Prototypes
 */

void hang(void) __attribute__ ((noreturn));

/* */
long int dram_init(void);
int      timer_init(void);
void     full_reset(void);
void     all_led_on(void);
void     all_led_off(void);
void     print_size(ulong, const char *);
void     print_board_info(void);
void     macaddr_init(unsigned char *);
void     flash_print_name(void);
void     cpu_name(char *name);
unsigned int main_cpu_clk(void);

/* common/main.c */
void	main_loop		(void);
int		run_command		(const char *cmd, int flag);
int		readline 		(const char *const prompt);
void	init_cmd_timeout(void);
void	reset_cmd_timeout(void);

/* lib_$(ARCH)/board.c */
void board_init_f(ulong);
void board_init_r(gd_t *, ulong);
char *strmhz(char *buf, long hz);
int  checkboard(void);
int  checkflash(void);
int  checkdram(void);
int  last_stage_init(void);
int  reset_button_status(void);
extern ulong monitor_flash_len;

/* common/flash.c */
void flash_perror (int);

/* common/cmd_autoscript.c */
int	autoscript (ulong addr);

extern u32 load_addr;	/* Default Load Address */
extern u32 save_addr;	/* Default Save Address */
extern u32 save_size;	/* Default Save Size */

/* common/cmd_nvedit.c */
int		env_init     (void);
void	env_relocate (void);
char	*getenv	     (char *);
int		getenv_r     (char *name, char *buf, unsigned len);
int		saveenv	     (void);
void	setenv	     (char *, char *);


#ifdef CONFIG_ARM
# include <asm/mach-types.h>
# include <asm/setup.h>
# include <asm/u-boot-arm.h>	/* ARM version to be fixed! */
#endif /* CONFIG_ARM */
#ifdef CONFIG_I386		/* x86 version to be fixed! */
# include <asm/u-boot-i386.h>
#endif /* CONFIG_I386 */

void	pci_init      (void);
int		pci_init_board(void);
void	pciinfo	      (int, int);

#if defined(CONFIG_PCI) && defined(CONFIG_440)
#   if defined(CFG_PCI_PRE_INIT)
    int	   pci_pre_init	       (struct pci_controller * );
#   endif
#   if defined(CFG_PCI_TARGET_INIT)
	void	pci_target_init	     (struct pci_controller *);
#   endif
#   if defined(CFG_PCI_MASTER_INIT)
	void	pci_master_init	     (struct pci_controller *);
#   endif
    int	    is_pci_host		(struct pci_controller *);
#endif

int	misc_init_f   (void);
int	misc_init_r   (void);

/* common/exports.c */
void	jumptable_init(void);

/* common/memsize.c */
int	get_ram_size  (volatile long *, long);

/* $(BOARD)/$(BOARD).c */
void	reset_phy     (void);
void	fdc_hw_init   (void);

/* $(BOARD)/eeprom.c */
void eeprom_init  (void);
#ifndef CONFIG_SPI
int  eeprom_probe (unsigned dev_addr, unsigned offset);
#endif
int  eeprom_read  (unsigned dev_addr, unsigned offset, uchar *buffer, unsigned cnt);
int  eeprom_write (unsigned dev_addr, unsigned offset, uchar *buffer, unsigned cnt);
#ifdef CONFIG_LWMON
extern uchar pic_read  (uchar reg);
extern void  pic_write (uchar reg, uchar val);
#endif

/*
 * Set this up regardless of board
 * type, to prevent errors.
 */
#if defined(CONFIG_SPI) || !defined(CFG_I2C_EEPROM_ADDR)
# define CFG_DEF_EEPROM_ADDR 0
#else
# define CFG_DEF_EEPROM_ADDR CFG_I2C_EEPROM_ADDR
#endif /* CONFIG_SPI || !defined(CFG_I2C_EEPROM_ADDR) */

#if defined(CONFIG_SPI)
extern void spi_init_f (void);
extern void spi_init_r (void);
extern ssize_t spi_read	 (uchar *, int, uchar *, int);
extern ssize_t spi_write (uchar *, int, uchar *, int);
#endif

#ifdef CONFIG_RPXCLASSIC
void rpxclassic_init (void);
#endif

void rpxlite_init (void);

#ifdef CONFIG_MBX
/* $(BOARD)/mbx8xx.c */
void	mbx_init (void);
void	board_serial_init (void);
void	board_ether_init (void);
#endif

#if defined(CONFIG_RPXCLASSIC)	|| defined(CONFIG_MBX) || \
    defined(CONFIG_IAD210)	|| defined(CONFIG_XPEDITE1K) || \
    defined(CONFIG_METROBOX)    || defined(CONFIG_KAREF)
void	board_get_enetaddr (uchar *addr);
#endif

#ifdef CONFIG_HERMES
/* $(BOARD)/hermes.c */
void hermes_start_lxt980 (int speed);
#endif

#ifdef CONFIG_EVB64260
void  evb64260_init(void);
void  debug_led(int, int);
void  display_mem_map(void);
void  perform_soft_reset(void);
#endif

void	load_sernum_ethaddr (void);

/* $(BOARD)/$(BOARD).c */
int board_early_init_f (void);
int board_late_init (void);
int board_postclk_init (void); /* after clocks/timebase, before env/serial */
int board_early_init_r (void);
void board_poweroff (void);

#if defined(CFG_DRAM_TEST)
int testdram(void);
#endif /* CFG_DRAM_TEST */

/* $(CPU)/start.S */
#if defined(CONFIG_5xx) || \
    defined(CONFIG_8xx)
uint	get_immr      (uint);
#endif
uint	get_pir	      (void);
#if defined(CONFIG_MPC5xxx)
uint	get_svr       (void);
#endif
uint	get_pvr	      (void);
uint	get_svr	      (void);
uint	rd_ic_cst     (void);
void	wr_ic_cst     (uint);
void	wr_ic_adr     (uint);
uint	rd_dc_cst     (void);
void	wr_dc_cst     (uint);
void	wr_dc_adr     (uint);
int	icache_status (void);
void	icache_enable (void);
void	icache_disable(void);
int	dcache_status (void);
void	dcache_enable (void);
void	dcache_disable(void);
void	relocate_code (ulong, gd_t *, ulong);
ulong	get_endaddr   (void);
void	trap_init     (ulong);
#if defined (CONFIG_4xx)	|| \
    defined (CONFIG_MPC5xxx)	|| \
    defined (CONFIG_74xx_7xx)	|| \
    defined (CONFIG_74x)	|| \
    defined (CONFIG_75x)	|| \
    defined (CONFIG_74xx)	|| \
    defined (CONFIG_MPC8220)	|| \
    defined (CONFIG_MPC85xx)	|| \
    defined (CONFIG_MPC83XX)
unsigned char	in8(unsigned int);
void		out8(unsigned int, unsigned char);
unsigned short	in16(unsigned int);
unsigned short	in16r(unsigned int);
void		out16(unsigned int, unsigned short value);
void		out16r(unsigned int, unsigned short value);
unsigned long	in32(unsigned int);
unsigned long	in32r(unsigned int);
void		out32(unsigned int, unsigned long value);
void		out32r(unsigned int, unsigned long value);
void		ppcDcbf(unsigned long value);
void		ppcDcbi(unsigned long value);
void		ppcSync(void);
void		ppcDcbz(unsigned long value);
#endif

/* $(CPU)/cpu.c */
int	checkcpu      (void);
int	checkicache   (void);
int	checkdcache   (void);
void	upmconfig     (unsigned int, unsigned int *, unsigned int);
ulong	get_tbclk     (void);
void	reset_cpu     (ulong addr);

/* $(CPU)/serial.c */
int	serial_init   (void);
void	serial_addr   (unsigned int);
void	serial_putc   (const char);
void	serial_putc_raw(const char);
void	serial_puts   (const char *);
int	serial_getc   (void);
int	serial_tstc   (void);
void	serial_setbrg (void);

void	_serial_putc   (const char, const int);
void	_serial_putc_raw(const char, const int);
void	_serial_puts   (const char *, const int);
int	_serial_getc   (const int);
int	_serial_tstc   (const int);

/* $(CPU)/speed.c */
int	get_clocks (void);
int	get_clocks_866 (void);
int	sdram_adjust_866 (void);
int	adjust_sdram_tbs_8xx (void);
#if defined(CONFIG_8260)
int	prt_8260_clks (void);
#elif defined(CONFIG_MPC83XX)
int print_clock_conf(void);
#elif defined(CONFIG_MPC5xxx)
int	prt_mpc5xxx_clks (void);
#endif
#if defined(CONFIG_MPC8220)
int	prt_mpc8220_clks (void);
#endif
#ifdef CONFIG_4xx
ulong	get_OPB_freq (void);
ulong	get_PCI_freq (void);
#endif
#if defined(CONFIG_S3C2400) || defined(CONFIG_S3C2410) || defined(CONFIG_LH7A40X)
ulong	get_FCLK (void);
ulong	get_HCLK (void);
ulong	get_PCLK (void);
ulong	get_UCLK (void);
#endif
#if defined(CONFIG_LH7A40X)
ulong	get_PLLCLK (void);
#endif
#if defined CONFIG_INCA_IP
uint	incaip_get_cpuclk (void);
#endif
#if defined(CONFIG_IMX)
ulong get_systemPLLCLK(void);
ulong get_FCLK(void);
ulong get_HCLK(void);
ulong get_BCLK(void);
ulong get_PERCLK1(void);
ulong get_PERCLK2(void);
ulong get_PERCLK3(void);
#endif
ulong	get_bus_freq  (ulong);

#if defined(CONFIG_MPC85xx)
typedef MPC85xx_SYS_INFO sys_info_t;
void	get_sys_info  ( sys_info_t * );
#endif

#if defined(CONFIG_4xx) || defined(CONFIG_IOP480)
#  if defined(CONFIG_440)
    typedef PPC440_SYS_INFO sys_info_t;
#  else
    typedef PPC405_SYS_INFO sys_info_t;
#  endif
void	get_sys_info  ( sys_info_t * );
#endif

/* $(CPU)/cpu_init.c */
#if defined(CONFIG_8xx) || defined(CONFIG_8260)
void	cpu_init_f    (volatile immap_t *immr);
#endif
#if defined(CONFIG_4xx) || defined(CONFIG_MPC85xx) || defined(CONFIG_MCF52x2)
void	cpu_init_f    (void);
#endif

int	cpu_init_r    (void);
#if defined(CONFIG_8260)
int	prt_8260_rsr  (void);
#endif

/* $(CPU)/interrupts.c */
int	interrupt_init	   (void);
void	timer_interrupt	   (struct pt_regs *);
void	external_interrupt (struct pt_regs *);
void	irq_install_handler(int, interrupt_handler_t *, void *);
void	irq_free_handler   (int);
ulong	get_timer	   (ulong base);

/* $(CPU)/.../commproc.c */
int	dpram_init (void);
uint	dpram_base(void);
uint	dpram_base_align(uint align);
uint	dpram_alloc(uint size);
uint	dpram_alloc_align(uint size,uint align);
void	post_word_store (ulong);
ulong	post_word_load (void);
void	bootcount_store (ulong);
ulong	bootcount_load (void);
#define BOOTCOUNT_MAGIC		0xB001C041

/* $(CPU)/.../<eth> */
void mii_init (void);

/* $(CPU)/.../lcd.c */
ulong	lcd_setmem (ulong);

/* $(CPU)/.../vfd.c */
ulong	vfd_setmem (ulong);

/* $(CPU)/.../video.c */
ulong	video_setmem (ulong);

/* lib_$(ARCH)/cache.c */
void	flush_cache   (unsigned long, unsigned long);


/* lib_$(ARCH)/ticks.S */
unsigned long long get_ticks(void);
void	wait_ticks    (unsigned long);

/* lib_$(ARCH)/time.c */
void	udelay	      (unsigned long);
#define milisecdelay(_x)                        udelay((_x) * 1000)
ulong	usec2ticks    (unsigned long usec);
ulong	ticks2usec    (unsigned long ticks);
int	init_timebase (void);

/* lib_generic/vsprintf.c */
ulong	simple_strtoul(const char *cp,char **endp,unsigned int base);
#ifdef CFG_64BIT_VSPRINTF
unsigned long long	simple_strtoull(const char *cp,char **endp,unsigned int base);
#endif
long	simple_strtol(const char *cp,char **endp,unsigned int base);
int	sprintf(char * buf, const char *fmt, ...);
int	vsprintf(char *buf, const char *fmt, va_list args);

/* common/console.c */
int	console_init_f(void);	/* Before relocation; uses the serial  stuff	*/
int	console_init_r(void);	/* After  relocation; uses the console stuff	*/
int	console_assign (int file, char *devname);	/* Assign the console	*/
int	ctrlc (void);
int	had_ctrlc (void);	/* have we had a Control-C since last clear? */
void	clear_ctrlc (void);	/* clear the Control-C condition */
int	disable_ctrlc (int);	/* 1 to disable, 0 to enable Control-C detect */

/*
 * STDIO based functions (can always be used)
 */

/* serial stuff */
void	serial_printf (const char *fmt, ...);

/* stdin */
int	getc(void);
int	tstc(void);

/* stdout */
void	putc(const char c);
void	puts(const char *s);
void	printf(const char *fmt, ...);
void	printf_err(const char *fmt, ...);
void	printf_wrn(const char *fmt, ...);
//void	vprintf(const char *fmt, va_list args);

/* stderr */
#define eputc(c)		fputc(stderr, c)
#define eputs(s)		fputs(stderr, s)
#define eprintf(fmt,args...)	fprintf(stderr,fmt ,##args)

/*
 * FILE based functions (can only be used AFTER relocation!)
 */

#define stdin		0
#define stdout		1
#define stderr		2
#define MAX_FILES	3

void	fprintf(int file, const char *fmt, ...);
void	fputs(int file, const char *s);
void	fputc(int file, const char c);
int	ftstc(int file);
int	fgetc(int file);

int	pcmcia_init (void);

/*
 * Optional BOOTP fields
 */
#define CONFIG_BOOTP_SUBNETMASK		0x00000001
#define CONFIG_BOOTP_GATEWAY		0x00000002
#define CONFIG_BOOTP_HOSTNAME		0x00000004
#define CONFIG_BOOTP_NISDOMAIN		0x00000008
#define CONFIG_BOOTP_BOOTPATH		0x00000010
#define CONFIG_BOOTP_BOOTFILESIZE	0x00000020
#define CONFIG_BOOTP_DNS		0x00000040
#define CONFIG_BOOTP_DNS2		0x00000080
#define CONFIG_BOOTP_SEND_HOSTNAME	0x00000100
#define CONFIG_BOOTP_NTPSERVER		0x00000200
#define CONFIG_BOOTP_TIMEOFFSET		0x00000400
#define CONFIG_BOOTP_VENDOREX		0x80000000

#define CONFIG_BOOTP_ALL	(~CONFIG_BOOTP_VENDOREX)

#define CONFIG_BOOTP_DEFAULT	(CONFIG_BOOTP_SUBNETMASK |\
				 CONFIG_BOOTP_BOOTPATH   |\
				 CONFIG_BOOTP_HOSTNAME   |\
				 CONFIG_BOOTP_GATEWAY    |\
				 CONFIG_BOOTP_SEND_HOSTNAME)

#ifndef CONFIG_BOOTP_MASK
#define CONFIG_BOOTP_MASK	CONFIG_BOOTP_DEFAULT
#endif

#endif /* __COMMON_H_ */
