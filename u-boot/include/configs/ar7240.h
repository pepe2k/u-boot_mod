/*
 * This file contains the configuration parameters for the dbau1x00 board.
 */

#ifndef __AR7240_H
#define __AR7240_H

#ifndef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY	1									/* autoboot after x seconds */
#endif

#define CONFIG_MENUPROMPT			"Hit any key to stop autobooting: %2d "
#define CONFIG_AUTOBOOT_PROMPT		"Autobooting in:\t%d s (type 'tpl' to run U-Boot console)\n\n"
#define CONFIG_AUTOBOOT_STOP_STR	"tpl"
#undef  CONFIG_AUTOBOOT_DELAY_STR
#define DEBUG_BOOTKEYS				0
#define CONFIG_BAUDRATE				115200
#define CFG_BAUDRATE_TABLE			{ 600,    1200,   2400,    4800,    9600,    14400,  \
									  19200,  28800,  38400,   56000,   57600,   115200, \
									  128000, 153600, 230400,  250000,  256000,  460800, \
									  576000, 921600, 1000000, 1152000, 1500000, 2000000 }

/*
 * Miscellaneous configurable options
 */
#define CFG_ALT_MEMTEST
#define CFG_HUSH_PARSER
#define	CFG_LONGHELP														/* undef to save memory      */
#define	CFG_PROMPT			"uboot> "										/* Monitor Command Prompt    */
#define CFG_PROMPT_HUSH_PS2	"> "
#define	CFG_CBSIZE			1024											/* Console I/O Buffer Size   */
#define	CFG_PBSIZE			(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)				/* Print Buffer Size, was: def + 16 */
#define	CFG_MAXARGS			16												/* max number of command */
#define CFG_MALLOC_LEN		512*1024										/* def: 128*1024 */
#define CFG_BOOTPARAMS_LEN	512*1024										/* def: 128 */
#define CFG_SDRAM_BASE		0x80000000										/* Cached addr */
#define CFG_MEMTEST_START	(CFG_SDRAM_BASE + 0x200000)						/* RAM test start = CFG_SDRAM_BASE + 2 MB */
#define CFG_MEMTEST_END		(CFG_SDRAM_BASE + bd->bi_memsize - 0x200001)	/* RAM test end   = CFG_SDRAM_BASE + RAM size - 2 MB - 1 Byte */
#define CFG_RX_ETH_BUFFER   16

#if defined(CONFIG_SILENT_CONSOLE)
	#define SILENT_ENV_VARIABLE	"silent=1\0"
#else
	#define SILENT_ENV_VARIABLE	""
#endif

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE				32768
#define CFG_ICACHE_SIZE				65536
#define CFG_CACHELINE_SIZE			32

#endif	/* __CONFIG_H */
