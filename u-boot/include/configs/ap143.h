/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros QCA953x based devices
 *
 * Reference designs: AP143
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _AP143_H
#define _AP143_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

/*
 * ==================
 * GPIO configuration
 * ==================
 */
#if defined(CONFIG_FOR_COMFAST_CF_E314N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO4  | GPIO11 | GPIO14 |\
						GPIO15 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO0 | GPIO2 | GPIO3
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_H |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_COMFAST_CF_E320N_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0 | GPIO2 | GPIO3
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11 | GPIO12 | GPIO14 |\
						GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_COMFAST_CF_E520N) ||\
      defined(CONFIG_FOR_COMFAST_CF_E530N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_P2W_CPE505N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO4  | GPIO11 | GPIO12 |\
						GPIO14 | GPIO15
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_P2W_R602N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO4  | GPIO11 | GPIO12 |\
						GPIO14 | GPIO15 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WA850RE_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO0  | GPIO1 | GPIO2  |\
						GPIO3  | GPIO4 | GPIO12 |\
						GPIO13 | GPIO14
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO15 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO15 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR810N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO13
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO11 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO0 | GPIO1 | GPIO12
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO11 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR820N_CN) ||\
      defined(CONFIG_FOR_TPLINK_WR802N)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO13
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO12
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR841N_V10) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V9)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO3  | GPIO4  | GPIO11 |\
						GPIO13 | GPIO14 | GPIO15 |\
						GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO12 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR841N_V11)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO1  | GPIO2  | GPIO3  |\
						GPIO4  | GPIO11 | GPIO13 |\
						GPIO14 | GPIO15 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO12 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_WALLYS_DR531)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO11 | GPIO12 | GPIO13 |\
						GPIO14 | GPIO15 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_YUNCORE_AP90Q)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO4 | GPIO12 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_YUNCORE_CPE830)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO0 | GPIO1 | GPIO2  |\
						GPIO3 | GPIO4 | GPIO12 |\
						GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO4  | GPIO11 | GPIO12 |\
						GPIO13 | GPIO14 | GPIO15 |\
						GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#endif

/*
 * ================
 * Default bootargs
 * ================
 */
#if defined(CONFIG_FOR_COMFAST_CF_E314N) ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:03 "\
				"rootfstype=jffs2 init=/sbin/init "\
				"mtdparts=ath-nor0:64k(u-boot),64k(art),1536k(uImage),14656k(rootfs),64k(mib0)"

#elif defined(CONFIG_FOR_COMFAST_CF_E520N) ||\
      defined(CONFIG_FOR_COMFAST_CF_E530N)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:03 "\
				"rootfstype=jffs2 init=/sbin/init "\
				"mtdparts=ath-nor0:64k(u-boot),64k(art),1536k(uImage),6464k(rootfs),64k(mib0)"

#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=spi0.0:256k(u-boot),64k(u-boot-env),14528k(rootfs),1472k(kernel),64k(art),16000k(firmware)"

#elif defined(CONFIG_FOR_TPLINK_WR810N)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),6912k(rootfs),64k(config),64k(art)"

#elif defined(CONFIG_FOR_TPLINK_WR820N_CN)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:32k(u-boot1),32k(u-boot2),3008k(rootfs),896k(uImage),64k(mib0),64k(art)"

#elif defined(CONFIG_FOR_TPLINK_WA850RE_V2) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V10) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V11) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V9)  ||\
      defined(CONFIG_FOR_TPLINK_WR802N)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#elif defined(CONFIG_FOR_WALLYS_DR531)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=jffs2 init=/sbin/init "\
				"mtdparts=ath-nor0:256k(u-boot),64k(u-boot-env),6336k(rootfs),1408k(uImage),64k(mib0),64k(ART)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */
#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)    ||\
    defined(CONFIG_FOR_TPLINK_WA850RE_V2)   ||\
    defined(CONFIG_FOR_TPLINK_WR802N)       ||\
    defined(CONFIG_FOR_TPLINK_WR810N)       ||\
    defined(CONFIG_FOR_TPLINK_WR820N_CN)    ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V10)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V11)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V9)
	#define CFG_LOAD_ADDR	0x9F020000
#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_WALLYS_DR531)   ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define CFG_LOAD_ADDR	0x9F050000
#endif

#if defined(CONFIG_FOR_P2W_CPE505N)    ||\
    defined(CONFIG_FOR_P2W_R602N)      ||\
    defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
    defined(CONFIG_FOR_YUNCORE_CPE830) ||\
    defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define CONFIG_BOOTCOMMAND	"bootm 0x9F050000 || bootm 0x9FE80000"
#else
	#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)
#endif

/*
 * =========================
 * Environment configuration
 * =========================
 */
#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)
	#define CFG_ENV_ADDR		0x9F018000
	#define CFG_ENV_SIZE		0x7C00
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define CFG_ENV_ADDR		0x9F040000
	#define CFG_ENV_SIZE		0xFC00
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_TPLINK_WA850RE_V2) ||\
      defined(CONFIG_FOR_TPLINK_WR802N)     ||\
      defined(CONFIG_FOR_TPLINK_WR810N)     ||\
      defined(CONFIG_FOR_TPLINK_WR820N_CN)  ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V10) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V11) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V9)
	#define CFG_ENV_ADDR		0x9F01EC00
	#define CFG_ENV_SIZE		0x1000
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_WALLYS_DR531)
	#define CFG_ENV_ADDR		0x9F030000
	#define CFG_ENV_SIZE		0xF800
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
#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)
	#define OFFSET_MAC_DATA_BLOCK		0x10000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x10000
	#define OFFSET_MAC_ADDRESS		0x00000
#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define OFFSET_MAC_DATA_BLOCK		0xFF0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000000
#elif defined(CONFIG_FOR_TPLINK_WA850RE_V2)
	#define OFFSET_MAC_DATA_BLOCK		0x3c0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000008
#elif defined(CONFIG_FOR_TPLINK_WR802N)     ||\
      defined(CONFIG_FOR_TPLINK_WR810N)     ||\
      defined(CONFIG_FOR_TPLINK_WR820N_CN)  ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V10) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V11) ||\
      defined(CONFIG_FOR_TPLINK_WR841N_V9)
	#define OFFSET_MAC_DATA_BLOCK		0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00FC00
	#define OFFSET_ROUTER_MODEL		0x00FD00
	#define OFFSET_PIN_NUMBER		0x00FE00
#elif defined(CONFIG_FOR_WALLYS_DR531)
	#define OFFSET_MAC_DATA_BLOCK		0x030000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00F810
#endif

/*
 * =========================
 * Custom changes per device
 * =========================
 */

/*
 * Comfast CF-E520N and E320Nv2 are limited to 64 KB only,
 * disable some commands
 */
#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)
	#undef CONFIG_CMD_DHCP
	#undef CONFIG_CMD_LOADB
	#undef CONFIG_CMD_SNTP
	#undef CONFIG_UPG_SCRIPTS_UBOOT
#endif

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)
	#define WEBFAILSAFE_UPLOAD_ART_ADDRESS	(CFG_FLASH_BASE + 0x10000)
#endif

/* Firmware size limit */
#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)    ||\
    defined(CONFIG_FOR_TPLINK_WR802N)       ||\
    defined(CONFIG_FOR_TPLINK_WR810N)       ||\
    defined(CONFIG_FOR_TPLINK_WR820N_CN)    ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V10)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V11)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V9)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#elif defined(CONFIG_FOR_TPLINK_WA850RE_V2)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(448 * 1024)
#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_WALLYS_DR531)   ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(384 * 1024)
#endif

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */
#if defined(CONFIG_FOR_TPLINK_WA850RE_V2) ||\
    defined(CONFIG_FOR_TPLINK_WR802N)     ||\
    defined(CONFIG_FOR_TPLINK_WR820N_CN)  ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V9)
	#define CONFIG_QCA_PLL	QCA_PLL_PRESET_550_400_200
#else
	#define CONFIG_QCA_PLL	QCA_PLL_PRESET_650_400_200
#endif

#if defined(CONFIG_FOR_COMFAST_CF_E314N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E320N_V2) ||\
    defined(CONFIG_FOR_COMFAST_CF_E520N)    ||\
    defined(CONFIG_FOR_COMFAST_CF_E530N)    ||\
    defined(CONFIG_FOR_TPLINK_WA850RE_V2)   ||\
    defined(CONFIG_FOR_TPLINK_WR802N)       ||\
    defined(CONFIG_FOR_TPLINK_WR810N)       ||\
    defined(CONFIG_FOR_TPLINK_WR820N_CN)    ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V10)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V11)   ||\
    defined(CONFIG_FOR_TPLINK_WR841N_V9)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x10000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#elif defined(CONFIG_FOR_P2W_CPE505N)    ||\
      defined(CONFIG_FOR_P2W_R602N)      ||\
      defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
      defined(CONFIG_FOR_YUNCORE_CPE830) ||\
      defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x40000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#elif defined(CONFIG_FOR_WALLYS_DR531)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x30000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#endif

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */
#if !defined(CONFIG_FOR_COMFAST_CF_E314N)    &&\
    !defined(CONFIG_FOR_COMFAST_CF_E320N_V2) &&\
    !defined(CONFIG_FOR_COMFAST_CF_E520N)    &&\
    !defined(CONFIG_FOR_COMFAST_CF_E530N)    &&\
    !defined(CONFIG_FOR_P2W_CPE505N)         &&\
    !defined(CONFIG_FOR_P2W_R602N)           &&\
    !defined(CONFIG_FOR_WALLYS_DR531)        &&\
    !defined(CONFIG_FOR_YUNCORE_AP90Q)       &&\
    !defined(CONFIG_FOR_YUNCORE_CPE830)      &&\
    !defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define CONFIG_UPG_UBOOT_SIZE_BACKUP_HEX	0x20000
#endif

#if defined(CONFIG_FOR_P2W_CPE505N)    ||\
    defined(CONFIG_FOR_P2W_R602N)      ||\
    defined(CONFIG_FOR_YUNCORE_AP90Q)  ||\
    defined(CONFIG_FOR_YUNCORE_CPE830) ||\
    defined(CONFIG_FOR_ZBTLINK_ZBT_WE1526)
	#define CONFIG_UPG_SCRIPTS_FW_ADDR_HEX	0x9F050000
#endif

/*
 * ===================
 * Other configuration
 * ===================
 */

/* Cache lock for stack */
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd001800

#endif /* _AP143_H */
