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

/*
 * ================
 * Default bootargs
 * ================
 */

/*
 * =============================
 * Load address and boot command
 * =============================
 */

#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)

/*
 * =========================
 * Environment configuration
 * =========================
 */

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

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */

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
