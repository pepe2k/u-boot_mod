/*
 * Upgrade helper environment scripts
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _UPG_SCRIPTS_H_
#define _UPG_SCRIPTS_H_

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

#endif /* _UPG_SCRIPTS_H_ */
