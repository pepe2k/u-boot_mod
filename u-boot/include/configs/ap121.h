/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros AR933x based devices
 *
 * Reference designs: AP121
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _AP121_H
#define _AP121_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

/*
 * ==================
 * GPIO configuration
 * ==================
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO13 | GPIO14
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO0
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0  | GPIO1 | GPIO13
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO17 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO26 | GPIO28 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11 | GPIO12
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO26 | GPIO28 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO26 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0 | GPIO28
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO13 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_GL_AR150)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0 | GPIO13 | GPIO15
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO6 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO1  | GPIO7  | GPIO8 | GPIO11 |\
						GPIO14 | GPIO16 | GPIO17
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO6
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_GL_INET)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0 | GPIO13
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO13 | GPIO15 | GPIO17 |\
						GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO18 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO18 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_MR13U_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO18 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO6 | GPIO7 | GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO18
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_TPLINK_MR3020_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO17 | GPIO26 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11 | GPIO18 | GPIO20
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO17 | GPIO26 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO18 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO18 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_MR3220_V2)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0  | GPIO1  | GPIO13 |\
						GPIO14 | GPIO15 | GPIO16 |\
						GPIO26
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO17 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#elif defined(CONFIG_FOR_TPLINK_WR703N_V1) ||\
      defined(CONFIG_FOR_TPLINK_WR710N_V1)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR720N_V3)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11 | GPIO18 | GPIO20
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO8 |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_L

#elif defined(CONFIG_FOR_TPLINK_WR740N_V4)

	#define CONFIG_QCA_GPIO_MASK_LED_ACT_H	GPIO0  | GPIO1  | GPIO13 |\
						GPIO14 | GPIO15 | GPIO16
	#define CONFIG_QCA_GPIO_MASK_LED_ACT_L	GPIO17 | GPIO27
	#define CONFIG_QCA_GPIO_MASK_OUT	CONFIG_QCA_GPIO_MASK_LED_ACT_L |\
						CONFIG_QCA_GPIO_MASK_LED_ACT_H
	#define CONFIG_QCA_GPIO_MASK_IN		GPIO11 | GPIO26
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	CONFIG_QCA_GPIO_MASK_LED_ACT_L
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_L	CONFIG_QCA_GPIO_MASK_LED_ACT_H

#endif

/*
 * ================
 * Default bootargs
 * ================
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:256k(u-boot),64k(u-boot-env),16000k(firmware),64k(art)"

#elif defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:256k(u-boot),64k(u-boot-env),6144k(rootfs),1600k(uImage),64k(NVRAM),64k(ART)"

#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:128k(u-boot),64k(u-boot-env),16128k(firmware),64k(art)"

#elif defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:06 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:64k(u-boot),64k(art),64k(mac),64k(nvram),256k(language),1024k(uImage),6656k(rootfs)"

#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:192k(u-boot),64k(u-boot-env),16064k(firmware),64k(art)"

#elif defined(CONFIG_FOR_GL_AR150)

	#define CONFIG_BOOTARGS	"console=ttyATH0,115200 board=domino root=31:03 "\
				"rootfstype=squashfs,jffs2 noinitrd "\
				"mtdparts=spi0.0:256k(u-boot)ro,64k(u-boot-env)ro,1280k(kernel),14656k(rootfs),64k(nvram),64k(art)ro,15936k@0x50000(firmware)"

#elif defined(CONFIG_FOR_GL_INET)            ||\
      defined(CONFIG_FOR_TPLINK_MR10U_V1)    ||\
      defined(CONFIG_FOR_TPLINK_MR13U_V1)    ||\
      defined(CONFIG_FOR_TPLINK_MR3020_V1)   ||\
      defined(CONFIG_FOR_TPLINK_MR3040_V1V2) ||\
      defined(CONFIG_FOR_TPLINK_MR3220_V2)   ||\
      defined(CONFIG_FOR_TPLINK_WR703N_V1)   ||\
      defined(CONFIG_FOR_TPLINK_WR720N_V3)   ||\
      defined(CONFIG_FOR_TPLINK_WR740N_V4)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#elif defined(CONFIG_FOR_TPLINK_WR710N_V1)

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ar7240-nor0:128k(u-boot),1024k(kernel),6912k(rootfs),64k(config),64k(art)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    ||\
    defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) ||\
    defined(CONFIG_FOR_GL_AR150)
	#define CFG_LOAD_ADDR	0x9F050000
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define CFG_LOAD_ADDR	0x9F030000
#elif defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define CFG_LOAD_ADDR	0x9F080000
#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define CFG_LOAD_ADDR	0x9F040000
#else
	#define CFG_LOAD_ADDR	0x9F020000
#endif

#if defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB)
	#define CONFIG_BOOTCOMMAND	"bootm 0x9F050000 || bootm 0x9FE50000 || bootm 0x9F650000"
#else
	#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)
#endif

/*
 * =========================
 * Environment configuration
 * =========================
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    ||\
    defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) ||\
    defined(CONFIG_FOR_GL_AR150)
	#define CFG_ENV_ADDR		0x9F040000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define CFG_ENV_ADDR		0x9F020000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define CFG_ENV_ADDR		0x9F028000
	#define CFG_ENV_SIZE		0x7C00
	#define CFG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define CFG_ENV_ADDR		0x9F030000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#else
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
		{ 600,    1200,   2400,    4800,    9600,    14400,  \
		  19200,  28800,  38400,   56000,   57600,   115200, \
		  128000, 153600, 230400,  250000,  256000,  460800, \
		  576000, 921600, 1000000, 1152000, 1500000, 2000000 }

/*
 * ==================================================
 * MAC address/es, model and WPS pin offsets in FLASH
 * ==================================================
 */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    ||\
    defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) ||\
    defined(CONFIG_FOR_DRAGINO_V2)             ||\
    defined(CONFIG_FOR_MESH_POTATO_V2)
	#define OFFSET_MAC_DATA_BLOCK		0xFF0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000000
	#define OFFSET_MAC_ADDRESS2		0x000006
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD) ||\
      defined(CONFIG_FOR_GL_AR150)
	#define OFFSET_MAC_DATA_BLOCK		0xFF0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000000
#elif defined(CONFIG_FOR_DLINK_DIR505_A1)
	/*
	 * DIR-505 has two MAC addresses inside dedicated MAC partition
	 * They are stored in plain text...
	 * TODO: read/write MAC stored as plain text
	 * #define OFFSET_MAC_DATA_BLOCK	0x02000
	 * #define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	 * #define OFFSET_MAC_ADDRESS		0x000004
	 * #define OFFSET_MAC_ADDRESS2		0x000016
	 */
#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)
	#define OFFSET_MAC_DATA_BLOCK		0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00FC00
#else
	#define OFFSET_MAC_DATA_BLOCK		0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00FC00
#endif

#if !defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    &&\
    !defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) &&\
    !defined(CONFIG_FOR_BLACK_SWIFT_BOARD)      &&\
    !defined(CONFIG_FOR_DLINK_DIR505_A1)        &&\
    !defined(CONFIG_FOR_DRAGINO_V2)             &&\
    !defined(CONFIG_FOR_GL_AR150)               &&\
    !defined(CONFIG_FOR_GL_INET)                &&\
    !defined(CONFIG_FOR_GS_OOLITE_V1_DEV)       &&\
    !defined(CONFIG_FOR_MESH_POTATO_V2)
	#define OFFSET_ROUTER_MODEL	0xFD00
#endif

#if defined(CONFIG_FOR_TPLINK_MR3020_V1) ||\
    defined(CONFIG_FOR_TPLINK_MR3220_V2) ||\
    defined(CONFIG_FOR_TPLINK_WR710N_V1) ||\
    defined(CONFIG_FOR_TPLINK_WR740N_V4)
	#define OFFSET_PIN_NUMBER	0xFE00
#endif

/*
 * =========================
 * Custom changes per device
 * =========================
 */

/* Dragino 2 uses different IP addresses */
#if defined(CONFIG_FOR_DRAGINO_V2)
	#undef  CONFIG_IPADDR
	#define CONFIG_IPADDR	192.168.255.1

	#undef  CONFIG_SERVERIP
	#define CONFIG_SERVERIP	192.168.255.2
#endif

/* Dragino 2 and Black Swift boards use different prompts */
#if defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#undef  CFG_PROMPT
	#define CFG_PROMPT	"BSB> "
#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#undef  CFG_PROMPT
	#define CFG_PROMPT	"dr_boot> "
#endif

/* D-Link DIR-505 is limited to 64 KB only and doesn't use env */
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#undef CONFIG_CMD_DHCP
	#undef CONFIG_CMD_LOADB
#endif

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_ART_ADDRESS	(CFG_FLASH_BASE + 0x10000)
#endif

/* Firmware size limit */
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) ||\
    defined(CONFIG_FOR_GL_AR150)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(384 * 1024)
#elif defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(448 * 1024)
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(256 * 1024)
#elif defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(512 * 1024)
#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(320 * 1024)
#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#else
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#endif

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */
#define CONFIG_QCA_PLL	QCA_PLL_PRESET_400_400_200

#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    ||\
    defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) ||\
    defined(CONFIG_FOR_GL_AR150)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x40000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD) ||\
      defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x20000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
      defined(CONFIG_FOR_MESH_POTATO_V2)

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x30000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#else

	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x10000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE	0x10000

#endif

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */
#if !defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)    &&\
    !defined(CONFIG_FOR_ALFA_NETWORK_HORNET_UB) &&\
    !defined(CONFIG_FOR_BLACK_SWIFT_BOARD)      &&\
    !defined(CONFIG_FOR_DLINK_DIR505_A1)        &&\
    !defined(CONFIG_FOR_DRAGINO_V2)             &&\
    !defined(CONFIG_FOR_GL_AR150)               &&\
    !defined(CONFIG_FOR_MESH_POTATO_V2)
	#define CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX	0x20000
#endif

#endif /* _AP121_H */
