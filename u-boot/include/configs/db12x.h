/*
 * This file contains the configuration parameters for the DB12x (AR9344) board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/ar7240.h>
#include <config.h>
#include <soc/soc_common.h>

/*
 * GPIO configuration
 */
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO21 | GPIO22)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO16 | GPIO17)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO21 | GPIO22)

#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO11 | GPIO13 | GPIO14 | GPIO15 | GPIO18 |\
													 GPIO19 | GPIO20 | GPIO21 | GPIO22)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO12)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO16 | GPIO17)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO12)

#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15 |\
													 GPIO18 | GPIO19 | GPIO20 | GPIO21)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO4)
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO16 | GPIO17)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO | GPIO4)

#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO12 | GPIO13 | GPIO14 | GPIO15 | GPIO18 |\
													 GPIO19 | GPIO20 | GPIO21)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO16 | GPIO17)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO

#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
	/* LEDs */
	#define CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO		(GPIO13 | GPIO14 | GPIO15 | GPIO18)

	/* Outputs, inputs */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS			CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#define CONFIG_QCA_GPIO_MASK_INPUTS				(GPIO16 | GPIO17)

	/* Initial states */
	#define CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI	CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO

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
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1) || defined (CONFIG_FOR_TPLINK_WDR3500_V1)
#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ath-nor0:256k(u-boot),64k(u-boot-env),6336k(rootfs),1408k(uImage),64k(mib0),64k(ART)"
#else
#define	CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 rootfstype=squashfs init=/sbin/init mtdparts=ath-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"
#endif

/*
 * Other env default values
 */
#undef CONFIG_BOOTFILE
#define CONFIG_BOOTFILE		"firmware.bin"

#undef CONFIG_LOADADDR
#define CONFIG_LOADADDR		0x80800000

#define	CFG_LOAD_ADDR			 0x9F020000
#define UPDATE_SCRIPT_FW_ADDR	"0x9F020000"
#define CONFIG_BOOTCOMMAND 		"bootm 0x9F020000"


#define CONFIG_IPADDR		192.168.1.1
#define CONFIG_SERVERIP		192.168.1.2

/*
 * PLL/Clocks configuration
 */
#ifdef CFG_HZ
	#undef	CFG_HZ
#endif
#define	CFG_HZ	bd->bi_cfg_hz

/* For now, use some safe clocks for all AR934x */
#define CONFIG_QCA_PLL 		QCA_PLL_PRESET_550_400_200


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
 * MIPS32 24K Processor Core Family Software User's Manual
 *
 * 6.2.9 Count Register (CP0 Register 9, Select 0)
 * The Count register acts as a timer, incrementing at a constant
 * rate, whether or not an instruction is executed, retired, or
 * any forward progress is made through the pipeline.  The counter
 * increments every other clock, if the DC bit in the Cause register
 * is 0.
 *
 * Since the count is incremented every other tick, divide by 2
 * XXX derive this from CFG_PLL_FREQ
 */

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET			0x1000
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd007000

/*
 * Address and size of Primary Environment Sector
 */
#define CFG_ENV_IS_IN_FLASH	1
#undef  CFG_ENV_IS_NOWHERE

#define CFG_ENV_ADDR		0x9F01EC00
#define CFG_ENV_SIZE		0x1000
#define CFG_ENV_SECT_SIZE	0x10000

/*
 * Available commands
 */
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

// Enable NetConsole and custom NetConsole port
#define CONFIG_NETCONSOLE
#define CONFIG_NETCONSOLE_PORT	6666

#define CONFIG_NET_MULTI

#ifdef CFG_ATHRS27_PHY
	/* use eth1(LAN) as the net interface */
	#define CONFIG_AG7240_SPEPHY
#endif

/*
 * Web Failsafe configuration
 */
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS				CONFIG_LOADADDR
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS			CFG_FLASH_BASE

// Firmware partition offset
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x20000

// U-Boot partition size
#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		(CONFIG_MAX_UBOOT_SIZE_KB * 1024)

// TODO: should be == CONFIG_MAX_UBOOT_SIZE_KB
#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES			"0x1EC00"
#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	"0x20000"

// ART partition size
#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES		(64 * 1024)

// max. firmware size <= (FLASH_SIZE -  WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES)
// TP-Link: 64k(U-Boot),64k(MAC/model/WPS pin block),64k(ART)
#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)

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

#define CFG_MII0_RMII				1
#define CFG_BOOTM_LEN				(16 << 20) /* 16 MB */

#undef DEBUG

/* MAC address, model and PIN number offsets in FLASH */
#define OFFSET_MAC_DATA_BLOCK			0x010000
#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
#define OFFSET_MAC_ADDRESS				0x00FC00
#define OFFSET_ROUTER_MODEL				0x00FD00
#define OFFSET_PIN_NUMBER				0x00FE00

/*
 * PLL and clocks configurations from FLASH
 */
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1) || \
	defined(CONFIG_FOR_TPLINK_WDR3500_V1)         || \
	defined(CONFIG_FOR_TPLINK_MR3420_V2)          || \
	defined(CONFIG_FOR_TPLINK_WR841N_V8)          || \
	defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
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
