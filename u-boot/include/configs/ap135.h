/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros QCA955x based devices
 *
 * Reference designs: AP135
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _AP135_H
#define _AP135_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

/*
 * ==================
 * GPIO configuration
 * ==================
 */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO12 | GPIO14 | GPIO15 |\
						GPIO17 | GPIO18 | GPIO19
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO13
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	GPIO21 | GPIO22

#endif

/*
 * ================
 * Default bootargs
 * ================
 */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=jffs2,squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),6912k(rootfs),64k(config),64k(art)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CFG_LOAD_ADDR	0x9F020000

#endif

	#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)

/*
 * =========================
 * Environment configuration
 * =========================
 */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CFG_ENV_ADDR		0x9F01EC00
	#define CFG_ENV_SIZE		0x1000
	#define CFG_ENV_SECT_SIZE	0x10000

#endif

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

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define OFFSET_MAC_DATA_BLOCK		0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00FC00
	#define OFFSET_ROUTER_MODEL		0x00FD00
	#define OFFSET_PIN_NUMBER		0x00FE00

#endif

/*
 * =========================
 * Custom changes per device
 * =========================
 */

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */

#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

/* Firmware size limit */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(320 * 1024)

#endif

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CONFIG_QCA_PLL	QCA_PLL_PRESET_720_600_200

#endif

#if defined(CONFIG_FOR_TPLINK_ARCHER_C7_V1)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x10000

#endif

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */

/*
 * ===================
 * Other configuration
 * ===================
 */

/* Cache lock for stack */
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd007000

#endif /* _AP135_H */
