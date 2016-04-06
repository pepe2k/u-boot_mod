/*
 * This file contains the configuration parameters for the AP121 (AR9331) board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/ar7240.h>
#include <config.h>
#include <soc/soc_common.h>

/*
 * GPIO configuration
 */
#if defined(CONFIG_FOR_TPLINK_WR703N_V1) ||\
	defined(CONFIG_FOR_TPLINK_WR710N_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO27

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)

#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO27

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)

#elif defined(CONFIG_FOR_TPLINK_WR720N_V3)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO27

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO11 | GPIO18 | GPIO20)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)

#elif defined(CONFIG_FOR_TPLINK_MR13U_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO27

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO6 | GPIO7 | GPIO11)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)

#elif defined(CONFIG_FOR_DLINK_DIR505_A1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO26 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO

#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO27

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO

#elif defined(CONFIG_FOR_TPLINK_MR3020_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		GPIO0
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO17 | GPIO26 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO |\
													 CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI |\
													 GPIO8)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO11 | GPIO18 | GPIO20)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO17 | GPIO26 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO18)
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_TPLINK_WR740N_V4)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		(GPIO0  | GPIO1 | GPIO13 | GPIO14 | GPIO15 | GPIO16)
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO17 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO |\
													 CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO11 | GPIO26)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_TPLINK_MR3220_V2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		(GPIO0  | GPIO1 | GPIO13 | GPIO14 | GPIO15 | GPIO16 | GPIO26)
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO17 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO |\
													 CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI |\
													 GPIO8)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO11)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO8)
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_GS_OOLITE_V1_DEV)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO13 | GPIO15 | GPIO17 | GPIO27)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO11)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO

#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		(GPIO13 | GPIO14)
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		GPIO0

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO |\
													 CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_DRAGINO_V2) ||\
	  defined(CONFIG_FOR_MESH_POTATO_V2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		(GPIO0  | GPIO28)
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO13 | GPIO17)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO |\
													 CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#elif defined(CONFIG_FOR_GL_INET)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI		(GPIO0 | GPIO13)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI
	#define CONFIG_QCA_GPIO_MASK_INPUTS				GPIO11

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI

#endif

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

#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)

	#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ar7240-nor0:128k(u-boot),64k(u-boot-env),16128k(firmware),64k(ART)"

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
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define	CFG_LOAD_ADDR			 0x9F030000
	#define UPDATE_SCRIPT_FW_ADDR	"0x9F030000"
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
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define CONFIG_BOOTCOMMAND "bootm 0x9F030000"
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

#if defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#if defined(CFG_PROMPT)
		#undef CFG_PROMPT
	#endif
	#define	CFG_PROMPT "BSB> "
#endif

/*
 * PLL/Clocks configuration
 */
#ifdef CFG_HZ
	#undef	CFG_HZ
#endif
#define	CFG_HZ	bd->bi_cfg_hz

#define CONFIG_QCA_PLL 		QCA_PLL_PRESET_400_400_200


/*
 * For PLL/clocks recovery use reset button by default
 */
#ifdef CONFIG_GPIO_RESET_BTN
	#define CONFIG_QCA_GPIO_OC_RECOVERY_BTN		CONFIG_GPIO_RESET_BTN
#endif

#ifdef CONFIG_GPIO_RESET_BTN_ACTIVE_LOW
	#define CONFIG_QCA_GPIO_OC_RECOVERY_BTN_ACTIVE_LOW	1
#endif

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET		0x1000

/*
 * Address and size of Primary Environment Sector
 */
#if !defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define CFG_ENV_IS_IN_FLASH	1
	#undef  CFG_ENV_IS_NOWHERE
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
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define CFG_ENV_ADDR		0x9F020000
	#define CFG_ENV_SIZE		0x8000
	#define CFG_ENV_SECT_SIZE	0x10000
#else
	#define CFG_ENV_ADDR		0x9F01EC00
	#define CFG_ENV_SIZE		0x1000
	#define CFG_ENV_SECT_SIZE	0x10000
#endif

/*
 * Available commands
 */
#if defined(CONFIG_FOR_DLINK_DIR505_A1)

	#define CONFIG_COMMANDS (CFG_CMD_MEMORY | \
							 CFG_CMD_PING   | \
							 CFG_CMD_FLASH  | \
							 CFG_CMD_NET    | \
							 CFG_CMD_RUN    | \
							 CFG_CMD_DATE   | \
							 CFG_CMD_ECHO   | \
							 CFG_CMD_BOOTD  | \
							 CFG_CMD_ITEST  | \
							 CFG_CMD_IMI)

#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || \
      defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2) || \
      defined(CONFIG_FOR_BLACK_SWIFT_BOARD)

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
							 CFG_CMD_ENV    | \
							 CFG_CMD_LOADB)

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
							 CFG_CMD_ITEST  | \
							 CFG_CMD_ENV    | \
							 CFG_CMD_LOADB)

#endif

// Enable NetConsole and custom NetConsole port
#define CONFIG_NETCONSOLE
#define CONFIG_NETCONSOLE_PORT	6666

#define CONFIG_NET_MULTI

/* choose eth1 first for tftpboot interface added by ZJin, 110328 */
#define CONFIG_AG7240_SPEPHY

/*
 * Web Failsafe configuration
 */
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS					CONFIG_LOADADDR

// U-Boot partition size and offset
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS				CFG_FLASH_BASE
#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES			(CONFIG_MAX_UBOOT_SIZE_KB * 1024)

#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x10000"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x40000"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x30000"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x20000"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES
#else
	// TODO: should be == CONFIG_MAX_UBOOT_SIZE_KB
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x1EC00"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	"0x20000"
#endif

// Firmware partition offset
#if defined(CONFIG_FOR_DLINK_DIR505_A1)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x80000
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x50000
#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x40000
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x30000
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
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	// Black Swift board: 128k(U-Boot),64k(U-Boot env),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(256 * 1024)
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
									"uboot_backup_size=" UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES "\0" \
									"uboot_upg=" \
										"if ping $serverip; then " \
											"mw.b $loadaddr 0xFF $uboot_backup_size && " \
											"cp.b $uboot_addr $loadaddr $uboot_backup_size && " \
											"tftp $loadaddr $uboot_name && " \
											"if itest.l $filesize <= $uboot_size; then " \
												"erase $uboot_addr +$uboot_backup_size && " \
												"cp.b $loadaddr $uboot_addr $uboot_backup_size && " \
												"echo OK!; " \
											"else " \
												"echo ERROR! Wrong file size!; " \
											"fi; " \
										"else " \
											"echo ERROR! Server not reachable!; " \
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
											"echo ERROR! Server not reachable!; " \
										"fi\0" \
									SILENT_ENV_VARIABLE

#define CFG_ATHRS26_PHY				1
#define CFG_AG7240_NMACS			2
#define CFG_MII0_RMII				1
#define CFG_BOOTM_LEN				(16 << 20) /* 16 MB */

#undef DEBUG

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
#elif defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	// Black Swift board has only one MAC address at the beginning of ART partition
	#define OFFSET_MAC_DATA_BLOCK		0xFF0000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000000
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
	!defined(CONFIG_FOR_GL_INET)             && \
	!defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
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
 */
#if defined(CONFIG_FOR_DLINK_DIR505_A1) || \
    defined(CONFIG_FOR_BLACK_SWIFT_BOARD)
	/*
	 * For DIR505 A1:
	 * We will store PLL and CLOCK registers
	 * configuration at the end of MAC data
	 * partition (3rd 64 KiB block)
	 * ----
	 * For Black Swift board:
	 * We will store PLL and CLOCK registers
	 * configuration at the end of environment
	 * sector (64 KB, environment uses only part!)
	 */
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x00020000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE		0x00010000

#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	/*
	 * We will store PLL and CLOCK registers
	 * configuration at the end of environment
	 * sector (64 KB, environment uses only half!)
	 */
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x00040000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE		0x00010000

#elif defined(CONFIG_FOR_DRAGINO_V2) || \
      defined(CONFIG_FOR_MESH_POTATO_V2)
	/*
	 * We will store PLL and CLOCK registers
	 * configuration at the end of environment
	 * sector (64 KB, environment uses only half!)
	 */
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x00030000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE		0x00010000

#else
	/*
	 * All TP-Link routers have a lot of unused space
	 * in FLASH, in second 64 KiB block.
	 * We will store there PLL and CLOCK
	 * registers configuration.
	 */
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET	0x00010000
	#define CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE		0x00010000

#endif

#if defined(CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET)
	/* Use last 32 bytes */
	#define CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET	(CFG_FLASH_BASE + \
													 CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET + \
													 0x0000FFE0)
#endif

#include <cmd_confdefs.h>

#endif	/* __CONFIG_H */
