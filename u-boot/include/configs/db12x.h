/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros AR934x based devices
 *
 * Reference designs: AP123, MI124, DB120
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _DB12X_H
#define _DB12X_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

/*
 * ==================
 * GPIO configuration
 * ==================
 */
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO11 | GPIO12 | GPIO13 |\
						GPIO14 | GPIO15
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO21 | GPIO22 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO21 | GPIO22 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO11 | GPIO13 | GPIO14 |\
						GPIO15 | GPIO18 | GPIO19 |\
						GPIO20 | GPIO21 | GPIO22
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO12 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO12 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO11 | GPIO12 | GPIO13 |\
						GPIO14 | GPIO15 | GPIO18 |\
						GPIO19 | GPIO20 | GPIO21
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO4 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO4 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO12 | GPIO13 | GPIO14 |\
						GPIO15 | GPIO18 | GPIO19 |\
						GPIO20 | GPIO21
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO13 | GPIO14 | GPIO15 |\
						GPIO18
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#endif

/*
 * ================
 * Default bootargs
 * ================
 */
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1) ||\
    defined(CONFIG_FOR_TPLINK_WDR3500_V1)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:256k(u-boot),64k(u-boot-env),6336k(rootfs),1408k(uImage),64k(mib0),64k(art)"

#else

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */
#define CFG_LOAD_ADDR		0x9F020000
#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)

/*
 * =========================
 * Environment configuration
 * =========================
 */
#define CFG_ENV_ADDR		0x9F01EC00
#define CFG_ENV_SIZE		0x1000
#define CFG_ENV_SECT_SIZE	0x10000

/*
 * ===========================
 * List of available baudrates
 * ===========================
 */
#define CFG_BAUDRATE_TABLE	\
		{ 600,    1200,   2400,    4800,    9600,    14400, \
		  19200,  28800,  38400,   56000,   57600,   115200 }

/*
 * ==================================================
 * MAC address/es, model and WPS pin offsets in FLASH
 * ==================================================
 */
#define OFFSET_MAC_DATA_BLOCK		0x010000
#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
#define OFFSET_MAC_ADDRESS		0x00FC00
#define OFFSET_ROUTER_MODEL		0x00FD00
#define OFFSET_PIN_NUMBER		0x00FE00

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

/* Firmware size limit */
#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */
#define CONFIG_QCA_PLL	QCA_PLL_PRESET_550_400_200

#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1) ||\
    defined(CONFIG_FOR_TPLINK_WDR3500_V1)         ||\
    defined(CONFIG_FOR_TPLINK_MR3420_V2)          ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V8)          ||\
    defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x10000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#endif

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */
#define CONFIG_UPG_UBOOT_SIZE_BACKUP_HEX	0x20000

/*
 * ===================
 * Other configuration
 * ===================
 */

/* Cache lock for stack */
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd007000

#endif /* _DB12X_H */
