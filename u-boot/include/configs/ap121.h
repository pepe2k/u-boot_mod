/*
 * This file contains the configuration parameters for the AP121 (AR9331) board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/ar7240.h>
#include <config.h>

/*
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS			1
#define CFG_MAX_FLASH_SECT			4096	// 4 KB sectors in 16 MB flash

/*
 * We boot from this flash
 */
#define CFG_FLASH_BASE					0x9F000000
#ifdef COMPRESSED_UBOOT
	#define BOOTSTRAP_TEXT_BASE			CFG_FLASH_BASE
	#define BOOTSTRAP_CFG_MONITOR_BASE 	BOOTSTRAP_TEXT_BASE
#endif

/*
 * The following #defines are needed to get flash environment right
 */
#define	CFG_MONITOR_BASE	TEXT_BASE
#define	CFG_MONITOR_LEN		(192 << 10)

/*
 * Default bootargs
 */
#undef CONFIG_BOOTARGS

#if defined(CONFIG_FOR_TPLINK_WR703N_V1) || \
	defined(CONFIG_FOR_TPLINK_WR720N_V3) || \
	defined(CONFIG_FOR_TPLINK_MR3020_V1) || \
	defined(CONFIG_FOR_TPLINK_MR3040_V1V2) || \
	defined(CONFIG_FOR_TPLINK_MR10U_V1) || \
	defined(CONFIG_FOR_TPLINK_WR740N_V4) || \
	defined(CONFIG_FOR_TPLINK_MR3220_V2) || \
	defined(CONFIG_FOR_TPLINK_MR13U_V1) || \
	defined(CONFIG_FOR_GL_INET)

	#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(ART)"

#elif defined(CONFIG_FOR_TPLINK_WR710N_V1)

	#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),6912k(rootfs),64k(config),64k(ART)"

#elif defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:06 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:64k(u-boot),64k(ART),64k(mac),64k(nvram),256k(language),1024k(uImage),6656k(rootfs)"

#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)

	#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(ART)"

#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)

	#define	CONFIG_BOOTARGS "console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:256k(u-boot),64k(u-boot-env),16000k(firmware),64k(ART)"

#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)

	#define	CONFIG_BOOTARGS "console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:192k(u-boot),64k(u-boot-env),16064k(firmware),64k(ART)"

#endif

/*
 * Other env default values
 */
#undef CONFIG_BOOTFILE
#define CONFIG_BOOTFILE			"firmware.bin"

#undef CONFIG_LOADADDR
#define CONFIG_LOADADDR			0x80800000

#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define	CFG_LOAD_ADDR			 0x9F080000
	#define UPDATE_SCRIPT_FW_ADDR	"0x9F080000"
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define	CFG_LOAD_ADDR			 0x9F050000
	#define UPDATE_SCRIPT_FW_ADDR	"0x9F050000"
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define	CFG_LOAD_ADDR			 0x9F040000
	#define UPDATE_SCRIPT_FW_ADDR	"0x9F040000"
#else
	#define	CFG_LOAD_ADDR			 0x9F020000
	#define UPDATE_SCRIPT_FW_ADDR	"0x9F020000"
#endif

#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define CONFIG_BOOTCOMMAND "bootm 0x9F080000"
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define CONFIG_BOOTCOMMAND "bootm 0x9F050000"
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define CONFIG_BOOTCOMMAND "bootm 0x9F040000"
#else
	#define CONFIG_BOOTCOMMAND "bootm 0x9F020000"
#endif

/*
 * Dragino 2 uses different IP addresses
 */
#if defined(CONFIG_FOR_DRAGINO_V2)
	#define CONFIG_IPADDR		192.168.255.1
	#define CONFIG_SERVERIP		192.168.255.2
#else
	#define CONFIG_IPADDR		192.168.1.1
	#define CONFIG_SERVERIP		192.168.1.2
#endif

/*
 * Dragino 2 uses different prompt
 */
#if defined(CONFIG_FOR_DRAGINO_V2) || \
    defined(CONFIG_FOR_MESH_POTATO_V2)
	#if defined(CFG_PROMPT)
		#undef CFG_PROMPT
	#endif
	#define	CFG_PROMPT "dr_boot> "
#endif

#undef	CFG_HZ
#define	CFG_HZ				bd->bi_cfg_hz
#undef	CPU_PLL_CONFIG_VAL
#undef	CPU_CLK_CONTROL_VAL

// CPU-RAM-AHB frequency setting
#ifndef CFG_PLL_FREQ
	#define CFG_PLL_FREQ    CFG_PLL_400_400_200
#endif

/*
 * CPU_PLL_DITHER_FRAC_VAL
 *
 * Value written into CPU PLL Dither FRAC Register (PLL_DITHER_FRAC)
 *
 * bits	0..9	NFRAC_MAX	=>	1000 (0x3E8)
 * bits	10..13	NFRAC_MIN	=>	0 (minimum value is used)
 * bits	20..29	NFRAC_STEP	=>	1
 *
 */
#define CPU_PLL_DITHER_FRAC_VAL		0x001003E8

/*
 * CPU_PLL_SETTLE_TIME_VAL
 *
 * Value written into CPU Phase Lock Loop Configuration Register 2 (CPU_PLL_CONFIG2)
 *
 * bits	0..11	SETTLE_TIME	=>	850 (0x352)
 *
 */
#if CONFIG_40MHZ_XTAL_SUPPORT
	#define CPU_PLL_SETTLE_TIME_VAL		0x00000550
#else
	#define CPU_PLL_SETTLE_TIME_VAL		0x00000352
#endif

/*
 * CPU_CLK_CONTROL_VAL
 *
 * In CPU_CLK_CONTROL_VAL bit 2 is set (BYPASS = 1 -> bypass PLL)
 * After PLL configuration we nedd to clear this bit
 *
 * Values written into CPU Clock Control Register CLOCK_CONTROL
 *
 * bits	2		(1bit)	BYPASS (Bypass PLL. This defaults to 1 for test purposes. Software must enable the CPU PLL for normal operation and then set this bit to 0)
 * bits	5..6	(2bit)	CPU_POST_DIV	=>	0	(DEFAULT, Ratio = 1)
 * bits	10..11	(2bit)	DDR_POST_DIV 	=>	0	(DEFAULT, Ratio = 1)
 * bits	15..16	(2bit)	AHB_POST_DIV	=>	1	(DEFAULT, Ratio = 2)
 *
 */

/*
 * CPU_PLL_CONFIG_VAL
 *
 * In CPU_PLL_CONFIG_VAL bit 30 is set (CPU_PLLPWD = 1 -> power down control for CPU PLL)
 * After PLL configuration we need to clear this bit
 *
 * Values written into CPU Phase Lock Loop Configuration (CPU_PLL_CONFIG)
 *
 * bits 10..15	(6bit)	DIV_INT	(The integer part of the DIV to CPU PLL)			=>	32	(0x20)
 * bits 16..20	(5bit)	REFDIV	(Reference clock divider)							=>	1	(0x1)	[doesn't start at values different than 1 (maybe need to change other dividers?)]
 * bits 21		(1bit)	RANGE	(Determine the VCO frequency range of the CPU PLL)	=>	0	(0x0)	[doesn't have impact on clock values]
 * bits 23..25	(3bit)	OUTDIV	(Define the ratio between VCO output and PLL output	=>	1	(0x1)	[value == 0 is illegal!]
 * 								VCOOUT * (1/2^OUTDIV) = PLLOUT)
 */

/*
 * = PLL CALCULATION =============
 * PLL = ((25 MHz / REFDIV) * DIV_INT) / (2 ^ OUTDIV)	// XTAL=25 MHz
 * OR
 * PLL = ((40 MHz / REFDIV) * DIV_INT) / (2 ^ OUTDIV)	// XTAL=40 MHz
 *
 * CPU = PLL / CPU_POST_DIV
 * DDR = PLL / DDR_POST_DIV
 * AHB = PLL / AHB_POST_DIV
 *
 */

/*
 * AR7240_SPI_CONTROL
 *
 * Value written into SPI Control (SPI_CONTROL) register
 *
 * bits	0..5	(6bit)	CLOCK_DIVIDER	(Specifies the clock divider setting. Actual clock frequency would be (AHB_CLK / ((CLOCK_DIVIDER+1)*2)) )
 * bits	6		(1bit)	REMAP_DISABLE	(Remaps 4 MB space over unless explicitly disabled by setting this bit to 1. If set to 1, 16 MB is accessible.)
 *
 */

/*
 * CPU_PLL_CONFIG and CPU_CLK_CONTROL registers values generator
 */
#define MAKE_AR9331_CPU_PLL_CONFIG_VAL(divint, refdiv, range, outdiv)  ( ((0x3F & divint) << 10) | \
                                                                         ((0x1F & refdiv) << 16) | \
                                                                         ((0x1 & range)   << 21) | \
                                                                         ((0x7 & outdiv)  << 23) )

#define MAKE_AR9331_CPU_CLK_CONTROL_VAL(cpudiv, ddrdiv, ahbdiv)        ( ((0x3 & (cpudiv - 1)) << 5)  | \
                                                                         ((0x3 & (ddrdiv - 1)) << 10) | \
                                                                         ((0x3 & (ahbdiv - 1)) << 15) )

#define MAKE_AR9331_SPI_CONTROL_VAL(spidiv)                            ( ((spidiv >> 1) - 1) | 0x40 )

/*
 * Default values (400/400/200 MHz) for O/C recovery mode
 */

// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
#define CPU_CLK_CONTROL_VAL_DEFAULT		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

#if CONFIG_40MHZ_XTAL_SUPPORT
	// DIV_INT = 20 (40 MHz * 20/2 = 400 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
	#define CPU_PLL_CONFIG_VAL_DEFAULT	MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 1)
#else
	// DIV_INT = 32 (25 MHz * 32/2 = 400 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
	#define CPU_PLL_CONFIG_VAL_DEFAULT	MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 1)
#endif

// CLOCK_DIVIDER = 2 (SPI clock = 200 / 6 ~ 33 MHz)
#define AR7240_SPI_CONTROL_DEFAULT	MAKE_AR9331_SPI_CONTROL_VAL(6)

#if (CFG_PLL_FREQ == CFG_PLL_200_200_100)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 20 (40 MHz * 20/4 = 200 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 2)
	#else
		// DIV_INT = 32 (25 MHz * 32/4 = 200 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 2)
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 100 / 4 ~ 25 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(200000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_200_200_200)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 1
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 20 (40 MHz * 20/4 = 200 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 2)
	#else
		// DIV_INT = 32 (25 MHz * 32/4 = 200 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 2)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 200 / 6 ~ 33 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(200000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_225_225_112)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 36 (25 MHz * 36/4 = 225 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 2)
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 112 / 4 ~ 28 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(225000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_225_225_225)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 1
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 36 (25 MHz * 36/4 = 225 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 2)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 225 / 8 ~ 28 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(225000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_250_250_125)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 25 (40 MHz * 25/4 = 250 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 2)
	#else
		// DIV_INT = 20 (25 MHz * 20/2 = 250 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 125 / 4 ~ 31 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(250000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_250_250_250)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 1
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 25 (40 MHz * 25/4 = 250 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 2
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 2)
	#else
		// DIV_INT = 20 (25 MHz * 20/2 = 250 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 250 / 8 ~ 31 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(250000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_300_300_150)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 15 (40 MHz * 15/2 = 300 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(15, 1, 0, 1)
	#else
		// DIV_INT = 24 (25 MHz * 24/2 = 300 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(24, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 150 / 6 ~ 25 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(300000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_325_325_162)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 26 (25 MHz * 26/2 = 325 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(26, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 162 / 6 ~ 27 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(325000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_350_350_175)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 28 (25 MHz * 28/2 = 350 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(28, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 175 / 6 ~ 29 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(350000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_360_360_180)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 18 (40 MHz * 18/2 = 360 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(18, 1, 0, 1)
	#else
		// DIV_INT = 29 (25 MHz * 28/2 = 362 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(29, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 180 / 6 ~ 30 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(360000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_380_380_190)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 19 (40 MHz * 19/2 = 380 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(19, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 190 / 6 ~ 32 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(380000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_400_400_200)

	// default configuration
	#define CPU_CLK_CONTROL_VAL	CPU_CLK_CONTROL_VAL_DEFAULT
	#define CPU_PLL_CONFIG_VAL	CPU_PLL_CONFIG_VAL_DEFAULT
	#define AR7240_SPI_CONTROL	AR7240_SPI_CONTROL_DEFAULT

	#define CFG_HZ_FALLBACK	(400000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_412_412_206)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 33 (25 MHz * 33/2 = 412 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(33, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 206 / 6 ~ 34 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(412000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_420_420_210)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 21 (40 MHz * 21/2 = 420 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(21, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 210 / 6 ~ 35 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(420000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_425_425_212)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 34 (25 MHz * 34/2 = 425 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(34, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 212 / 6 ~ 35 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(425000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_437_437_218)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 35 (25 MHz * 35/2 = 437 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(35, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 218 / 8 ~ 27 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(437000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_440_440_220)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 22 (40 MHz * 22/2 = 440 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(22, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 220 / 8 ~ 27 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(440000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_450_450_225)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 36 (25 MHz * 36/2 = 450 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 225 / 8 ~ 28 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(450000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_460_460_230)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 23 (40 MHz * 23/2 = 460 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(23, 1, 0, 1)
	#else
		// DIV_INT = 37 (25 MHz * 36/2 = 462 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(37, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 230 / 8 ~ 29 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(460000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_475_475_237)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 38 (25 MHz * 38/2 = 475 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(38, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 237 / 8 ~ 30 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(475000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_480_480_240)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 24 (40 MHz * 24/2 = 480 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(24, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 240 / 8 ~ 30 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(480000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_487_487_243)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 39 (25 MHz * 39/2 = 487 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(39, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 243 / 8 ~ 30 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(487000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_500_500_250)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 25 (40 MHz * 25/2 = 500 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 1)
	#else
		// DIV_INT = 40 (25 MHz * 40/2 = 500 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(40, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 250 / 8 ~ 31 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(500000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_500_250_250)

	// CPU_DIV = 1, RAM_DIV = 2, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 25 (40 MHz * 25/2 = 500 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 1)
	#else
		// DIV_INT = 40 (25 MHz * 40/2 = 500 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(40, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 250 / 8 ~ 31 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(500000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_520_520_260)

	// CPU_DIV = 1, RAM_DIV = 1, AHB_DIV = 2
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 26 (40 MHz * 26/2 = 520 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(26, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 3 (SPI clock = 260 / 8 ~ 32 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(8)

	#define CFG_HZ_FALLBACK	(520000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_525_262_131)

	// CPU_DIV = 1, RAM_DIV = 2, AHB_DIV = 4
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		#define FREQUENCY_NOT_SUPPORTED
	#else
		// DIV_INT = 42 (25 MHz * 42/2 = 525 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(42, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 131 / 4 ~ 33 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(525000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_560_280_140)

	// CPU_DIV = 1, RAM_DIV = 2, AHB_DIV = 4
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 28 (40 MHz * 28/2 = 560 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(28, 1, 0, 1)
	#else
		// DIV_INT = 45 (25 MHz * 45/2 = 562 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(45, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 140 / 4 ~ 35 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(560000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_580_290_145)

	// CPU_DIV = 1, RAM_DIV = 2, AHB_DIV = 4
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 29 (40 MHz * 29/2 = 580 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(29, 1, 0, 1)
	#else
		#define FREQUENCY_NOT_SUPPORTED
	#endif

	// CLOCK_DIVIDER = 1 (SPI clock = 145 / 4 ~ 36 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(4)

	#define CFG_HZ_FALLBACK	(580000000LU/2)

#elif (CFG_PLL_FREQ == CFG_PLL_600_300_200)

	// CPU_DIV = 1, RAM_DIV = 2, AHB_DIV = 3
	#define CPU_CLK_CONTROL_VAL		MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 3)

	#if CONFIG_40MHZ_XTAL_SUPPORT
		// DIV_INT = 30 (40 MHz * 30/2 = 600 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(30, 1, 0, 1)
	#else
		// DIV_INT = 48 (25 MHz * 48/2 = 600 MHz), REFDIV = 1, RANGE = 0, OUTDIV = 1
		#define CPU_PLL_CONFIG_VAL	MAKE_AR9331_CPU_PLL_CONFIG_VAL(48, 1, 0, 1)
	#endif

	// CLOCK_DIVIDER = 2 (SPI clock = 200 / 6 ~ 33 MHz)
	#define AR7240_SPI_CONTROL	MAKE_AR9331_SPI_CONTROL_VAL(6)

	#define CFG_HZ_FALLBACK	(600000000LU/2)

#elif defined(CFG_PLL_FREQ)
	#error Unknown frequency setting!
#endif

/*
 * Check if clocks configuration is valid
 */
#ifdef FREQUENCY_NOT_SUPPORTED
	#error Selected frequency setting is not supported with your reference clock!
#endif

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET		0x1000

/*
 * Address and size of Primary Environment Sector
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || \
	defined(CONFIG_FOR_DRAGINO_V2) || \
	defined(CONFIG_FOR_MESH_POTATO_V2)
	#define	CFG_ENV_IS_IN_FLASH	1
	#undef CFG_ENV_IS_NOWHERE
#else
	#undef  CFG_ENV_IS_IN_FLASH
	#define CFG_ENV_IS_NOWHERE	1
#endif

#if defined(CONFIG_FOR_DRAGINO_V2) || \
	defined(CONFIG_FOR_MESH_POTATO_V2)
	#define CFG_ENV_ADDR		0x9F030000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define CFG_ENV_ADDR		0x9F040000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#else
	#define CFG_ENV_ADDR		0x9F040000
	#define CFG_ENV_SIZE		0x10000
#endif

/*
 * Available commands
 */
#if defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define CONFIG_COMMANDS (CFG_CMD_MEMORY | \
							 CFG_CMD_DHCP   | \
							 CFG_CMD_PING   | \
							 CFG_CMD_FLASH  | \
							 CFG_CMD_NET    | \
							 CFG_CMD_RUN    | \
							 CFG_CMD_DATE   | \
							 CFG_CMD_SNTP   | \
							 CFG_CMD_ECHO   | \
							 CFG_CMD_BOOTD  | \
							 CFG_CMD_ITEST  | \
							 CFG_CMD_IMI)

#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || \
      defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)

	#define CONFIG_COMMANDS (CFG_CMD_MEMORY | \
							 CFG_CMD_DHCP   | \
							 CFG_CMD_PING   | \
							 CFG_CMD_FLASH  | \
							 CFG_CMD_NET    | \
							 CFG_CMD_RUN    | \
							 CFG_CMD_DATE   | \
							 CFG_CMD_SNTP   | \
							 CFG_CMD_ECHO   | \
							 CFG_CMD_BOOTD  | \
							 CFG_CMD_ITEST  | \
							 CFG_CMD_IMI    | \
							 CFG_CMD_ENV)

#else

	#define CONFIG_COMMANDS (CFG_CMD_MEMORY | \
							 CFG_CMD_DHCP   | \
							 CFG_CMD_PING   | \
							 CFG_CMD_FLASH  | \
							 CFG_CMD_NET    | \
							 CFG_CMD_RUN    | \
							 CFG_CMD_DATE   | \
							 CFG_CMD_SNTP   | \
							 CFG_CMD_ECHO   | \
							 CFG_CMD_BOOTD  | \
							 CFG_CMD_ITEST)

#endif

// Enable NetConsole and custom NetConsole port
#define CONFIG_NETCONSOLE
#define CONFIG_NETCONSOLE_PORT	6666

/* DDR init values */
#if CONFIG_40MHZ_XTAL_SUPPORT
	#define CFG_DDR_REFRESH_VAL	0x4270
#else
	#define CFG_DDR_REFRESH_VAL	0x4186
#endif

#define CFG_DDR_CONFIG_VAL		0x7fbc8cd0
#define CFG_DDR_MODE_VAL_INIT	0x133

#ifdef LOW_DRIVE_STRENGTH
	#define CFG_DDR_EXT_MODE_VAL	0x2
#else
	#define CFG_DDR_EXT_MODE_VAL	0x0
#endif

#define CFG_DDR_MODE_VAL	0x33
#define CFG_DDR_TRTW_VAL	0x1f
#define CFG_DDR_TWTR_VAL	0x1e

//#define CFG_DDR_CONFIG2_VAL			0x99d0e6a8	// HORNET 1.0
#define CFG_DDR_CONFIG2_VAL				0x9dd0e6a8	// HORNET 1.1
#define CFG_DDR_RD_DATA_THIS_CYCLE_VAL	0x00ff
#define CFG_DDR_TAP0_VAL				0x8
#define CFG_DDR_TAP1_VAL				0x9

/* DDR2 Init values */
#define CFG_DDR2_EXT_MODE_VAL			0x402

#define CONFIG_NET_MULTI

/* choose eth1 first for tftpboot interface added by ZJin, 110328 */
#define CONFIG_AG7240_SPEPHY

/*
 * Web Failsafe configuration
 */
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS					CONFIG_LOADADDR

// U-Boot partition size and offset
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS				CFG_FLASH_BASE

#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		(64 * 1024)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x10000"
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		(256 * 1024)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x40000"
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		(192 * 1024)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x30000"
#else
	#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		(64 * 1024)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x10000"
#endif

// Firmware partition offset
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x80000
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x50000
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x40000
#else
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x20000
#endif

// ART partition size and offset
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_ART_ADDRESS				WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x10000
#endif

#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES			(64 * 1024)

// max. firmware size <= (FLASH_SIZE -  WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES)
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	// D-Link DIR-505: 64k(U-Boot),64k(ART),64k(MAC),64k(NVRAM),256k(Language)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(512 * 1024)
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	// Carambola 2: 256k(U-Boot),64k(U-Boot env),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(384 * 1024)
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	// Dragino 2: 192k(U-Boot),64k(U-Boot env),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(320 * 1024)
#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)
	// GS-Oolite v1: 128k(U-Boot + MAC),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#else
	// TP-Link: 64k(U-Boot),64k(MAC/model/WPS pin block),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#endif

// progress state info
#define WEBFAILSAFE_PROGRESS_START				0
#define WEBFAILSAFE_PROGRESS_TIMEOUT			1
#define WEBFAILSAFE_PROGRESS_UPLOAD_READY		2
#define WEBFAILSAFE_PROGRESS_UPGRADE_READY		3
#define WEBFAILSAFE_PROGRESS_UPGRADE_FAILED		4

// update type
#define WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE		0
#define WEBFAILSAFE_UPGRADE_TYPE_UBOOT			1
#define WEBFAILSAFE_UPGRADE_TYPE_ART			2

/*-----------------------------------------------------------------------*/

/*
 * Additional environment variables for simple upgrades
 */
#define CONFIG_EXTRA_ENV_SETTINGS	"uboot_addr=0x9F000000\0" \
									"uboot_name=uboot.bin\0" \
									"uboot_size=" UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES "\0" \
									"uboot_upg=" \
										"if ping $serverip; then " \
											"tftp $loadaddr $uboot_name && " \
											"if itest.l $filesize == $uboot_size; then " \
												"erase $uboot_addr +$filesize && " \
												"cp.b $loadaddr $uboot_addr $filesize && " \
												"echo OK!; " \
											"else " \
												"echo ERROR! Wrong file size!; " \
											"fi; " \
										"else " \
											"ERROR! Server not reachable!; " \
										"fi\0" \
									"firmware_addr=" UPDATE_SCRIPT_FW_ADDR "\0" \
									"firmware_name=firmware.bin\0" \
									"firmware_upg=" \
										"if ping $serverip; then " \
											"tftp $loadaddr $firmware_name && " \
											"erase $firmware_addr +$filesize && " \
											"cp.b $loadaddr $firmware_addr $filesize && " \
											"echo OK!; " \
										"else " \
											"ERROR! Server not reachable!; " \
										"fi\0" \
									SILENT_ENV_VARIABLE

#define CFG_ATHRS26_PHY				1
#define CFG_AG7240_NMACS			2
#define CFG_MII0_RMII				1
#define CFG_BOOTM_LEN				(16 << 20) /* 16 MB */

#undef DEBUG
#define milisecdelay(_x)			udelay((_x) * 1000)

/* MAC address, model and PIN number offsets in FLASH */
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	// DIR-505 has two MAC addresses inside dedicated MAC partition
	// They are stored in plain text... TODO: read/write MAC stored as plain text
	//#define OFFSET_MAC_DATA_BLOCK			0x020000
	//#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	//#define OFFSET_MAC_ADDRESS				0x000004
	//#define OFFSET_MAC_ADDRESS2				0x000016
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || \
      defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	// Carambola 2 and Dragino 2 have two MAC addresses at the beginning of ART partition
	#define OFFSET_MAC_DATA_BLOCK			0xFF0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS				0x000000
	#define OFFSET_MAC_ADDRESS2				0x000006
#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)
	// GS-OOlite has only one MAC, inside second block
	// It's some kind of TP-Link clone
	#define OFFSET_MAC_DATA_BLOCK			0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS				0x00FC00
#else
	#define OFFSET_MAC_DATA_BLOCK			0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS				0x00FC00
#endif

#if !defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) && \
	!defined(CONFIG_FOR_DLINK_DIR505_A1)     && \
	!defined(CONFIG_FOR_GS_OOLITE_V1_DEV)    && \
	!defined(CONFIG_FOR_DRAGINO_V2)          && \
	!defined(CONFIG_FOR_MESH_POTATO_V2)      && \
	!defined(CONFIG_FOR_GL_INET)
#define OFFSET_ROUTER_MODEL					0x00FD00
#endif

#if defined(CONFIG_FOR_TPLINK_MR3020_V1) || \
	defined(CONFIG_FOR_TPLINK_WR740N_V4) || \
	defined(CONFIG_FOR_TPLINK_MR3220_V2) || \
	defined(CONFIG_FOR_TPLINK_WR710N_V1)
	#define OFFSET_PIN_NUMBER				0x00FE00
#endif

/*
 * PLL and clocks configurations from FLASH
 *
 * We need space for 4x 32-bit variables:
 * - PLL_MAGIC_VARIABLE
 * - values of registers:
 *   - CPU_PLL_CONFIG (page 70 in datasheet)
 *   - CLOCK_CONTROL  (page 71)
 *   - SPI_CONTROL    (page 261)
 */
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	/*
	 * We will store PLL and CLOCK registers
	 * configuration at the end of MAC data
	 * partition (3rd 64 KiB block)
	 */
	#define PLL_IN_FLASH_MAGIC				0x504C4C73
	#define PLL_IN_FLASH_DATA_BLOCK_OFFSET	0x00020000
	#define PLL_IN_FLASH_DATA_BLOCK_LENGTH	0x00010000
	#define PLL_IN_FLASH_MAGIC_OFFSET		0x0000FFF0	// last 16 bytes
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	/*
	 * We will store PLL and CLOCK registers
	 * configuration at the end of environment
	 * sector (64 KB, environment uses only half!)
	 */
	#define PLL_IN_FLASH_MAGIC				0x504C4C73
	#define PLL_IN_FLASH_DATA_BLOCK_OFFSET	0x00040000
	#define PLL_IN_FLASH_DATA_BLOCK_LENGTH	0x00010000
	#define PLL_IN_FLASH_MAGIC_OFFSET		0x0000FFF0	// last 16 bytes
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	/*
	 * We will store PLL and CLOCK registers
	 * configuration at the end of environment
	 * sector (64 KB, environment uses only half!)
	 */
	#define PLL_IN_FLASH_MAGIC				0x504C4C73
	#define PLL_IN_FLASH_DATA_BLOCK_OFFSET	0x00030000
	#define PLL_IN_FLASH_DATA_BLOCK_LENGTH	0x00010000
	#define PLL_IN_FLASH_MAGIC_OFFSET		0x0000FFF0	// last 16 bytes
#else
	/*
	 * All TP-Link routers have a lot of unused space
	 * in FLASH, in second 64 KiB block.
	 * We will store there PLL and CLOCK
	 * registers configuration.
	 */
	#define PLL_IN_FLASH_MAGIC				0x504C4C73
	#define PLL_IN_FLASH_DATA_BLOCK_OFFSET	0x00010000
	#define PLL_IN_FLASH_DATA_BLOCK_LENGTH	0x00010000
	#define PLL_IN_FLASH_MAGIC_OFFSET		0x0000FFF0	// last 16 bytes
#endif

#include <cmd_confdefs.h>

#endif	/* __CONFIG_H */
