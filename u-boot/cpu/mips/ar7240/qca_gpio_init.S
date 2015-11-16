/*
 * This file contains code used for lowlevel initialization
 * of GPIO, on supported Qualcomm/Atheros platforms
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

.globl lowlevel_gpio_init
.ent   lowlevel_gpio_init

lowlevel_gpio_init:

/*
 * JTAG and UART init
 */
#if (SOC_TYPE & QCA_AR934X_SOC)  || \
	(SOC_TYPE & QCA_QCA955X_SOC) || \
	(SOC_TYPE & QCA_QCA953X_SOC)
	/*
	 * Disable JTAG (bit 1 set) and ALL clock observation (bit 2~9 reset)
	 * Do not do this in RAM version!
	 */
	li t8, QCA_GPIO_FUNC_REG

  #ifndef CONFIG_SKIP_LOWLEVEL_INIT
	li t9, QCA_GPIO_FUNC_JTAG_DIS_MASK
  #else
	li t9, 0x0
  #endif
	sw t9, 0(t8)

	/*
	 * Setup GPIOs for LS UART:
	 * - TX: GPIO10
	 * - RX: GPIO9
	 *
	 * TODO:
	 * - allow select LS or HS UART on platforms which support both
	 * - allow select other than default GPIOs for LS/HS UART pins
	 */

	/* GPIO10 as output, GPIO9 as input */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	and t9, t9, ~GPIO10
	or  t9, t9, GPIO9
	sw  t9, 0(t8)

	/* Set LSUART_TXD on GPIO10 */
	li  t8, QCA_GPIO_OUT_FUNC2_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_GPIO_OUT_FUNCX_GPIO10_EN_MASK
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 QCA_GPIO_OUT_FUNCX_GPIO10_EN_SHIFT)
	sw  t9, 0(t8)

	/* Set LSUART_RXD on GPIO9 */
	li  t8, QCA_GPIO_IN_EN0_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_GPIO_IN_EN0_LSUART_RXD_MASK
	or  t9, t9, (9 << QCA_GPIO_IN_EN0_LSUART_RXD_SHIFT)
	sw  t9, 0(t8)
#endif

/*
 * General configuration of GPIO (buttons, LEDs, default value, etc.)
 */
#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)
	/*
	 * LEDs and buttons GPIOs on WDR3600/WDR43x0 v1:
	 *
	 * 11 => USB1 LED
	 * 12 => USB2 LED
	 * 13 => WLAN2G
	 * 14 => SYS
	 * 15 => QSS
	 * 21 => USB2 POWER (active high)
	 * 22 => USB1 POWER (active high)
	 *
	 * 16 => Reset button
	 * 17 => Wi-Fi ON/OFF switch
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	/* GPIO Init */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	/* Set GPIOs 11~15 and 21~22 as outputs */
	and t9, t9, ~(GPIO11 | GPIO12 | GPIO13 | \
				  GPIO14 | GPIO15 | GPIO21 | GPIO22)
	/* Set GPIOs 16~17 as inputs */
	or  t9, t9, (GPIO16 | GPIO17)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIO 11 */
	li  t8, QCA_GPIO_OUT_FUNC2_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO11_EN_MASK)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 12~15 */
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	li  t9, 0x0
	sw  t9, 0(t8)

	/* Turn on all LEDS and power on both USB */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO21 | GPIO22)
	sw  t9, 0(t8)

	/* Wait for a while, for LEDs bootup blink */
	li  t8, 0
	li  t9, 0x70000

1:
	addi t8, t8, 1
	bne  t8, t9, 1b
	nop

	/* Turn off all LEDs */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO11 | GPIO12 | GPIO13 | \
			 GPIO14 | GPIO15 | GPIO21 | GPIO22)
	sw  t9, 0(t8)

#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)
	/*
	 * LEDs and buttons GPIOs on WDR3500 v1:
	 *
	 * 11 => USB LED
	 * 12 => USB POWER (active high)
	 * 13 => WLAN2G
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 * 22 => LAN4
	 *
	 * 16 => Reset button
	 * 17 => Wi-Fi ON/OFF switch
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	/* GPIO Init */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	/* Set GPIOs 11~15 and 18~22 as outputs */
	and t9, t9, ~(GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15 | \
				  GPIO18 | GPIO19 | GPIO20 | GPIO21 | GPIO22)
	/* Set GPIOs 16~17 as inputs */
	or  t9, t9, (GPIO16 | GPIO17)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIO 11 */
	li  t8, QCA_GPIO_OUT_FUNC2_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO11_EN_MASK)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 12~15 */
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	li  t9, 0x0
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 18~19 */
	li  t8, QCA_GPIO_OUT_FUNC4_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO18_EN_MASK | \
				  QCA_GPIO_OUT_FUNCX_GPIO19_EN_MASK)
	sw  t9, 0(t8)

	/* Turn off all LEDs and turn on power on USB */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15 | \
			 GPIO18 | GPIO19 | GPIO20 | GPIO21 | GPIO22)
	sw  t9, 0(t8)

#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)
	/*
	 * LEDs and buttons GPIOs on WR841N/D v8:
	 *
	 * 12 => LAN4
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 *
	 * 16 => Wi-Fi ON/OFF switch
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	/* GPIOs init */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	/* Set GPIOs 12~15 and 18~21 as outputs */
	and t9, t9, ~(GPIO12 | GPIO13 | GPIO14 | GPIO15 | \
				  GPIO18 | GPIO19 | GPIO20 | GPIO21)
	/* Set GPIOs 16~17 as inputs */
	or  t9, t9, (GPIO16 | GPIO17)
	sw  t9, 0(t8)

	/* Set gpio function for GPIOs 12~15 */
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	li  t9, 0x0
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 18~19 */
	li  t8, QCA_GPIO_OUT_FUNC4_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO18_EN_MASK | \
				  QCA_GPIO_OUT_FUNCX_GPIO19_EN_MASK)
	sw  t9, 0(t8)

	/* Turn off all LEDs */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO12 | GPIO13 | GPIO14 | GPIO15 | \
			 GPIO18 | GPIO19 | GPIO20 | GPIO21)
	sw  t9, 0(t8)

#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)
	/*
	 * LEDs and buttons GPIOs on MR3420 v2:
	 *
	 * 4  => USB Power (active high)
	 * 11 => USB/3G LED
	 * 12 => LAN4
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 *
	 * 16 => WPS button
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	/* GPIOs init */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	/* Set GPIOs 4, 11~15 and 18~21 as outputs */
	and t9, t9, ~(GPIO4  | GPIO11 | GPIO12 | GPIO13 | GPIO14 | \
				  GPIO15 | GPIO18 | GPIO19 | GPIO20 | GPIO21)
	/* Set GPIOs 16~17 as inputs */
	or  t9, t9, (GPIO16 | GPIO17)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIO 4 */
	li  t8, QCA_GPIO_OUT_FUNC1_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO4_EN_MASK)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIO 11 */
	li  t8, QCA_GPIO_OUT_FUNC2_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO11_EN_MASK)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 12~15 */
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	li  t9, 0x0
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 18~19 */
	li  t8, QCA_GPIO_OUT_FUNC4_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO18_EN_MASK | \
				  QCA_GPIO_OUT_FUNCX_GPIO19_EN_MASK)
	sw  t9, 0(t8)

	/* Turn off all LEDs and turn on power on USB */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO4  | GPIO11 | GPIO12 | GPIO13 | GPIO14 | \
			 GPIO15 | GPIO18 | GPIO19 | GPIO20 | GPIO21)
	sw  t9, 0(t8)

#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
	/*
	 * LEDs and buttons GPIOs on WA830REv2 and WA801ND v2:
	 *
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => LAN
	 *
	 * 16 => Range Extender
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	/* GPIOs init */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
	/* Set GPIOs 13~15 and 18 as outputs */
	and t9, t9, ~(GPIO13 | GPIO14 | GPIO15 | GPIO18)
	/* Set GPIOs 16~17 as inputs */
	or  t9, t9, (GPIO16 | GPIO17)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIOs 13~15 */
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO13_EN_MASK | \
				  QCA_GPIO_OUT_FUNCX_GPIO14_EN_MASK | \
				  QCA_GPIO_OUT_FUNCX_GPIO15_EN_MASK)
	sw  t9, 0(t8)

	/* Set GPIO function for GPIO 18 */
	li  t8, QCA_GPIO_OUT_FUNC4_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO18_EN_MASK)
	sw  t9, 0(t8)

	/* Turn off all LEDs */
	li  t8, QCA_GPIO_SET_REG
	li  t9, (GPIO13 | GPIO14 | GPIO15 | GPIO18)
	sw  t9, 0(t8)
#endif

	j ra
	.end lowlevel_gpio_init
