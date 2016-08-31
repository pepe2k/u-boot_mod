/*
 * Upgrade and recovery helper environment scripts
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _ENV_SCRIPTS_H_
#define _ENV_SCRIPTS_H_

/*
 * U-Boot upgrade
 */
#if defined(CONFIG_UPG_SCRIPTS_UBOOT) &&\
    defined(CONFIG_MAX_UBOOT_SIZE_HEX)

	/* Backup size: use image limit size by default */
	#if !defined(CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX)
		#define CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX	\
				CONFIG_MAX_UBOOT_SIZE_HEX
	#endif

	/* Target address: use CFG_FLASH_BASE by default */
	#if !defined(CONFIG_UPG_SCRIPTS_UBOOT_ADDR_HEX)
		#define CONFIG_UPG_SCRIPTS_UBOOT_ADDR_HEX	\
				CFG_FLASH_BASE
	#endif

	/* Limit size: use image limit size by default */
	#if !defined(CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX)
		#define CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX	\
				CONFIG_MAX_UBOOT_SIZE_HEX
	#endif

	/* Small check */
	#if (CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX < \
	     CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX)
		#error "U-Boot backup size must be >= U-Boot image size"
	#endif

	/* Include backup stage only if needed */
	#if (CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX == \
	     CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX)
		#define CONFIG_ENV_UPG_SCRIPTS_UBOOT	\
		"uboot_name=u-boot.bin\0" \
		"uboot_addr=" MK_STR(CONFIG_UPG_SCRIPTS_UBOOT_ADDR_HEX) "\0" \
		"uboot_size=" MK_STR(CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX) "\0" \
		"uboot_upg=" \
			"if ping $serverip; then " \
				"tftp $loadaddr $uboot_name && " \
				"if itest.l $filesize <= $uboot_size; then " \
					"erase $uboot_addr +$uboot_size && " \
					"cp.b $loadaddr $uboot_addr $uboot_size && " \
					"echo DONE! U-Boot upgraded!; " \
				"else " \
					"echo ERROR! File is too big!; " \
				"fi; " \
			"else " \
				"echo ERROR! $serverip is not reachable!; " \
			"fi\0"
	#else
		#define CONFIG_ENV_UPG_SCRIPTS_UBOOT	\
		"uboot_name=u-boot.bin\0" \
		"uboot_addr=" MK_STR(CONFIG_UPG_SCRIPTS_UBOOT_ADDR_HEX) "\0" \
		"uboot_size=" MK_STR(CONFIG_UPG_SCRIPTS_UBOOT_SIZE_HEX) "\0" \
		"uboot_bckp=" MK_STR(CONFIG_UPG_SCRIPTS_UBOOT_SIZE_BCKP_HEX) "\0" \
		"uboot_upg=" \
			"if ping $serverip; then " \
				"mw.b $loadaddr 0xFF $uboot_bckp && " \
				"cp.b $uboot_addr $loadaddr $uboot_bckp && " \
				"tftp $loadaddr $uboot_name && " \
				"if itest.l $filesize <= $uboot_size; then " \
					"erase $uboot_addr +$uboot_bckp && " \
					"cp.b $loadaddr $uboot_addr $uboot_bckp && " \
					"echo DONE! U-Boot upgraded!; " \
				"else " \
					"echo ERROR! File is too big!; " \
				"fi; " \
			"else " \
				"echo ERROR! $serverip is not reachable!; " \
			"fi\0"
	#endif

#endif /* CONFIG_UPG_SCRIPTS_UBOOT && CONFIG_MAX_UBOOT_SIZE_HEX */

/*
 * Firmware upgrade
 */
#if defined(CONFIG_UPG_SCRIPTS_FW)

	/* Target address: use CFG_LOAD_ADDR by default */
	#if !defined(CONFIG_UPG_SCRIPTS_FW_ADDR_HEX)
		#define CONFIG_UPG_SCRIPTS_FW_ADDR_HEX	\
				CFG_LOAD_ADDR
	#endif

	#define CONFIG_ENV_UPG_SCRIPTS_FW	\
		"fw_addr=" MK_STR(CONFIG_UPG_SCRIPTS_FW_ADDR_HEX) "\0" \
		"fw_upg=" \
			"if ping $serverip; then " \
				"tftp $loadaddr $bootfile && " \
				"erase $fw_addr +$filesize && " \
				"cp.b $loadaddr $fw_addr $filesize && " \
				"echo DONE! Firmware upgraded!; " \
			"else " \
				"echo ERROR! $serverip is not reachable!; " \
			"fi\0"

#endif /* CONFIG_UPG_SCRIPTS_FW */

/*
 * Recovery
 */
#if defined(CONFIG_BTN_RECOVERY_SCRIPT)

	#if !defined(CONFIG_CMD_BUTTON) ||\
	    !defined(CONFIG_CMD_SLEEP)  ||\
	    !defined(CONFIG_CMD_LED)    ||\
	    !defined(CONFIG_CMD_SETEXPR)
		#error "Commands setexpr, sleep, button and led{on, off} are required for recovery"
	#endif

	#if !defined(CONFIG_GPIO_RESET_BTN)
		#error "Reset button definition is required for recovery"
	#endif

	#if defined(CONFIG_CMD_HTTPD)
		#define SCRIPT_HTTP_PART_1	\
		"echo - 3s for web based recovery;"

		#define SCRIPT_HTTP_PART_2	\
		"elif test $cnt -ge 3; then " \
			"echo HTTP server is starting for firmware update...;" \
			"setenv stop_boot 1;" \
			"echo;" \
			"httpd;" \
		"elif test $cnt -lt 3; then "
	#else
		#define SCRIPT_HTTP_PART_1	""
		#define SCRIPT_HTTP_PART_2	\
		"elif test $cnt -lt 5; then "
	#endif

	#define CONFIG_ENV_BTN_RECOVERY_SCRIPT	\
		"recovery=" \
		"if button; then " \
			"sleep 600;" \
			"setenv cnt 0;" \
			"echo Keep button pressed for at least:;" \
			SCRIPT_HTTP_PART_1 \
			"echo - 5s for U-Boot console;" \
			"echo - 7s for network console;" \
			"echo;" \
			"while button; do " \
				"ledon;" \
				"sleep 300;" \
				"echo . \'\\\\c\';" \
				"sleep 300;" \
				"ledoff;" \
				"sleep 600;" \
				"setexpr cnt $cnt + 1;" \
			"done;" \
			"echo $cnt seconds;" \
			"echo;" \
			"if test $cnt -ge 7; then " \
				"echo Starting network console...;" \
				"setenv stop_boot 1;" \
				"echo;" \
				"startnc;" \
			"elif test $cnt -ge 5; then " \
				"echo Starting U-Boot console...;" \
				"setenv stop_boot 1;" \
				"echo;" \
			SCRIPT_HTTP_PART_2 \
				"echo \\#\\# Error: button was not pressed long enough!;" \
				"echo Continuing normal boot...;" \
				"echo;" \
			"fi;"\
		"fi\0"

#endif /* CONFIG_BTN_RECOVERY_SCRIPT */

#endif /* _ENV_SCRIPTS_H_ */
