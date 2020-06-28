/*
 * Copyright (C) 2018
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros QCA956x based devices
 *
 * Reference designs: AP152
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _AP152_H
#define _AP152_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

#define WLANCAL				0x9fff1000
#define BOARDCAL			0x9fff0000
#define ATHEROS_PRODUCT_ID		137
#define CAL_SECTOR			(CFG_MAX_FLASH_SECT - 1)

/* For Merlin, both PCI, PCI-E interfaces are valid */
#define ATH_ART_PCICFG_OFFSET		12

#define CONFIG_PCI_CONFIG_DATA_IN_OTP


#undef BOARDCAL


/*
 * ==================
 * GPIO configuration
 * ==================
 */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO1 | GPIO7 | GPIO9
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO5 | GPIO8 | GPIO10
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO2 | GPIO4
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H GPIO5
	#define CONFIG_QCA_GPIO_LSUART_TX 17
	#define CONFIG_QCA_GPIO_LSUART_RX 16
	#define CONFIG_QCA_GPIO_MDC 8
	#define CONFIG_QCA_GPIO_MDIO 10
	#define CONFIG_QCA_MDC_MDIO_AS_GPIO	1
	#define CONFIG_GPIO_RESET_BTN 2
#endif

/*
 * ================
 * Default bootargs
 * ================
 */

#if defined(CONFIG_FOR_TPLINK_EAP245_V1)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	#define CFG_LOAD_ADDR	0x9F040000

#endif

#define CONFIG_BOOTCOMMAND	"bootelf " MK_STR(CFG_LOAD_ADDR)


/*
 * =========================
 * Environment configuration
 * =========================
 */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1) 
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
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	#define OFFSET_MAC_DATA_BLOCK		0x030000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000008
	#define OFFSET_ROUTER_MODEL		0x001008
	#define OFFSET_PIN_NUMBER		0x001108
#endif

/*
 * =========================
 * Custom changes per device
 * =========================
 */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	#undef CONFIG_CMD_GPIO
#endif

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

//	#define WEBFAILSAFE_UPLOAD_ART_ADDRESS	(CFG_FLASH_BASE + 0x10000)


/* Firmware size limit (FLASH_SIZE - WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES) */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(0x40000 + 0x30000 + 0x10000) /* kernel_off + config_sz + art_sz */
#endif

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */
#if defined(CONFIG_FOR_TPLINK_EAP245_V1)
	//#define CONFIG_QCA_PLL	QCA_PLL_PRESET_550_400_200
#endif

#if defined(CONFIG_FOR_TPLINK_EAP245_V1) 
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x10000
	//#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000
#endif

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */
//#define CONFIG_MAX_UBOOT_SIZE_HEX 0x1ec00
#define CONFIG_UPG_UBOOT_SIZE_BACKUP_HEX	0x20000
//#define CONFIG_UPG_SCRIPTS_FW_ADDR_HEX	0x9F050000


/*
 * ===================
 * Other configuration
 * ===================
 */

/* Cache lock for stack */
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd001800

#define CFG_DDR_REFRESH_VAL		0x4186
//#define CFG_FLASH_SIZE (CONFIG_DEFAULT_FLASH_SIZE_IN_MB*1024*1024)
//#define FLASH_SIZE CONFIG_DEFAULT_FLASH_SIZE_IN_MB
#define CFG_FLASH_SECTOR_SIZE 0x10000
#define CFG_DDR2_REFRESH_VAL    0x40c3
#define WLANCAL				0x9fff1000
#define ATH_ART_PCICFG_OFFSET		12


#define CONFIG_MII_PHY_ADDR	0x4


#define CFG_INIT_SRAM_SP_OFFSET	0xbd001800
#endif /* _AP152_H */
