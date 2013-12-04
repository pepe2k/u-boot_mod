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
#define CFG_BAUDRATE_TABLE			{115200}

/*
 * Miscellaneous configurable options
 */
#define CFG_ALT_MEMTEST
#define	CFG_LONGHELP											/* undef to save memory      */
#define	CFG_PROMPT			"uboot> "							/* Monitor Command Prompt    */
#define	CFG_CBSIZE			1024								/* Console I/O Buffer Size   */
#define	CFG_PBSIZE			(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)	/* Print Buffer Size, was: def + 16 */
#define	CFG_MAXARGS			16									/* max number of command */
#define CFG_MALLOC_LEN		512*1024							// def: 128*1024
#define CFG_BOOTPARAMS_LEN	512*1024							// def: 128
#define CFG_SDRAM_BASE		0x80000000							/* Cached addr */
#define CFG_MEMTEST_START	0x80200000
#define CFG_MEMTEST_END		0x83800000
#define CFG_RX_ETH_BUFFER   16

/*
 ** PLL Config for different CPU/DDR/AHB frequencies
 */
#define CFG_PLL_200_200_100		1
#define CFG_PLL_200_200_200		2
#define CFG_PLL_225_225_112		3
#define CFG_PLL_225_225_225		4
#define CFG_PLL_250_250_125		5
#define CFG_PLL_250_250_250		6
#define CFG_PLL_300_300_150		7
#define CFG_PLL_325_325_162		8
#define CFG_PLL_350_350_175		9
#define CFG_PLL_360_360_180		10
#define CFG_PLL_380_380_190		11
#define CFG_PLL_400_400_200		12
#define CFG_PLL_412_412_206		13
#define CFG_PLL_420_420_210		14
#define CFG_PLL_425_425_212		15
#define CFG_PLL_437_437_218		16
#define CFG_PLL_440_440_220		17
#define CFG_PLL_450_450_225		18
#define CFG_PLL_460_460_230		19
#define CFG_PLL_475_475_237		20
#define CFG_PLL_480_480_240		21
#define CFG_PLL_487_487_243		22
#define CFG_PLL_500_500_250		23
#define CFG_PLL_500_250_250		24
#define CFG_PLL_520_520_260		25
#define CFG_PLL_525_262_131		26
#define CFG_PLL_560_280_140		27
#define CFG_PLL_580_290_145		28
#define CFG_PLL_600_300_200		29

// WASP
#define CFG_PLL_566_400_200			101
#define CFG_PLL_566_500_250			102
#define CFG_PLL_600_1_2G_400_200	103
#define CFG_PLL_560_480_240			104

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE				32768
#define CFG_ICACHE_SIZE				65536
#define CFG_CACHELINE_SIZE			32

#endif	/* __CONFIG_H */
