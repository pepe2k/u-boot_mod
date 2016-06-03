/*
 * This file contains code used for lowlevel initialization
 * of GPIO, on supported Qualcomm/Atheros platforms
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/*
 * Low level GPIO initialization:
 * 1. Setup JTAG (disable by default, but allow to keep it up)
 * 2. Disable all clock observation on platforms which support this
 * 3. Setup UART lines
 * 4. Setup all configured GPIO inputs/outputs
 * 5. Set desired init values on configured GPIOs
 *
 * The user may use several config definitions here:
 * 1. CONFIG_QCA_KEEP_JTAG_ENABLED
 *    - if defined, JTAG will not be disabled
 * 2. CONFIG_QCA_GPIO_MASK_OUTPUTS,
 *    CONFIG_QCA_GPIO_MASK_INPUTS
 *    - bitmask for GPIOs to be set as outputs and inputs
 * 3. CONFIG_QCA_GPIO_LSUART_TX,
 *    CONFIG_QCA_GPIO_LSUART_RX
 *    - GPIO number for LSUART TX (10 if empty) and RX line (9 if empty)
 * 4. CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI,
 *    CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO
 *    - bitmask for outputs initialized to high and low state at start
 * 5. CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI,
 *    CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
 *    - bitmask for GPIO driven LEDs, used only in leds_on/leds_off functions,
 *      GPIO numbers for LEDs MUST be defined also in CONFIG_QCA_GPIO_MASK_OUTPUTS!
 *
 * TODO:
 * 1. Allow to select LS, HS, both or none UART type
 *    on platforms which support both
 * 2. Allow to select clocks observation on chosen pins
 * 3. Ethernet/WLAN LEDs configuration
 * 4. Enable JTAG on request (button?)
 */

/* Sanity check for GPIO driven LEDs */
#if (defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)  || \
	 defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO)) && \
	!defined(CONFIG_QCA_GPIO_MASK_OUTPUTS)
	#error "GPIO numbers for LEDs must be included in CONFIG_QCA_GPIO_MASK_OUTPUTS!"
#endif

#if (defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI) && \
	 !(CONFIG_QCA_GPIO_MASK_OUTPUTS & CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)) || \
	(defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO) && \
	 !(CONFIG_QCA_GPIO_MASK_OUTPUTS & CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO))
	#error "GPIO numbers for LEDs must be included in CONFIG_QCA_GPIO_MASK_OUTPUTS!"
#endif

.globl lowlevel_gpio_init
.type  lowlevel_gpio_init, @function
.align 4
.text
.ent lowlevel_gpio_init

lowlevel_gpio_init:
/*
 * =========================
 * Low level GPIO setup for:
 * 1. AR934x
 * 2. QCA953x
 * 3. QCA955x
 * =========================
 */
#if (SOC_TYPE & QCA_AR934X_SOC)  || \
	(SOC_TYPE & QCA_QCA953X_SOC) || \
	(SOC_TYPE & QCA_QCA955X_SOC)

	/* Sanity check for JTAG pins (GPIO 0~3) */
	#if defined(CONFIG_SKIP_LOWLEVEL_INIT) || \
		defined(CONFIG_QCA_KEEP_JTAG_ENABLED)
		#if (defined(CONFIG_QCA_GPIO_MASK_INPUTS)  && (CONFIG_QCA_GPIO_MASK_INPUTS  & 0xF)) || \
			(defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) && (CONFIG_QCA_GPIO_MASK_OUTPUTS & 0xF))
				#error "Cannot use JTAG and GPIO0~3 at the same time!"
		#endif
	#endif

	/*
	 * Disable:
	 * 1. By default JTAG (bit 1 set)
	 * 2. All clock observation (bits 2~9 reset)
	 */
	li t8, QCA_GPIO_FUNC_REG
	#if defined(CONFIG_SKIP_LOWLEVEL_INIT) || \
		defined(CONFIG_QCA_KEEP_JTAG_ENABLED)
	li t9, 0x0
	#else
	li t9, QCA_GPIO_FUNC_JTAG_DIS_MASK
	#endif
	sw t9, 0(t8)

	/* By default use GPIO10 for TX and GPIO9 for RX */
	#ifndef CONFIG_QCA_GPIO_LSUART_TX
		#define CONFIG_QCA_GPIO_LSUART_TX	10
	#endif

	#ifndef CONFIG_QCA_GPIO_LSUART_RX
		#define CONFIG_QCA_GPIO_LSUART_RX	9
	#endif

	#define CONFIG_QCA_GPIO_MASK_LSUART_TX	(1 << CONFIG_QCA_GPIO_LSUART_TX)
	#define CONFIG_QCA_GPIO_MASK_LSUART_RX	(1 << CONFIG_QCA_GPIO_LSUART_RX)

	#define CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT	\
									(8 * (CONFIG_QCA_GPIO_LSUART_TX - \
									((CONFIG_QCA_GPIO_LSUART_TX / 4) * 4)))

	/* Some sanity checks for LS UART GPIO lines */
	#if (CONFIG_QCA_GPIO_LSUART_TX >= QCA_GPIO_COUNT) || \
		(CONFIG_QCA_GPIO_LSUART_RX >= QCA_GPIO_COUNT)
		#error "LSUART GPIO numbers for TX and/or RX lines are not correct!"
	#endif

	#if (CONFIG_QCA_GPIO_LSUART_TX == CONFIG_QCA_GPIO_LSUART_RX)
		#error "LSUART TX and RX GPIO numbers cannot be the same!"
	#endif

	/*
	 * Do not allow to use LSUART TX/RX lines
	 * as regular GPIO inputs/outputs at the same time
	 */
	#if defined(CONFIG_QCA_GPIO_MASK_INPUTS) || defined(CONFIG_QCA_GPIO_MASK_OUTPUTS)
		#if (CONFIG_QCA_GPIO_MASK_INPUTS  & CONFIG_QCA_GPIO_MASK_LSUART_TX) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS  & CONFIG_QCA_GPIO_MASK_LSUART_RX) || \
			(CONFIG_QCA_GPIO_MASK_OUTPUTS & CONFIG_QCA_GPIO_MASK_LSUART_TX) || \
			(CONFIG_QCA_GPIO_MASK_OUTPUTS & CONFIG_QCA_GPIO_MASK_LSUART_RX)
			#error "Cannot use LSUART lines as regular GPIOs at the same time!"
		#endif
	#endif

	/*
	 * Target regular GPIO and LSUART TX line configuration
	 *
	 * After selecting GPIO as output in GPIO_OE register,
	 * the line will be set to low, which causes signal
	 * toggle on pulled-up lines
	 *
	 * To prevent this, we need to first setup desired
	 * init state for all GPIOs configured as outputs
	 * and then setup them as outputs
	 */
	li  t8, QCA_GPIO_OUT_REG
	lw  t9, 0(t8)
	#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI
	or  t9, t9, (CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI | \
				 CONFIG_QCA_GPIO_MASK_LSUART_TX)
	#else
	or  t9, t9, CONFIG_QCA_GPIO_MASK_LSUART_TX
	#endif
	#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO)
	#endif
	sw  t9, 0(t8)

	/*
	 * Setup GPIO type (out/in) in GPIO_OE
	 * register for all configured regular
	 * GPIOs and LSUART TX/RX lines
	 */
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
		#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_OUTPUTS | \
				  CONFIG_QCA_GPIO_MASK_LSUART_TX)
		#else
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_LSUART_TX)
		#endif
		#ifdef CONFIG_QCA_GPIO_MASK_INPUTS
	or  t9, t9, (CONFIG_QCA_GPIO_MASK_INPUTS | CONFIG_QCA_GPIO_MASK_LSUART_RX)
		#else
	or  t9, t9, CONFIG_QCA_GPIO_MASK_LSUART_RX
		#endif
	sw  t9, 0(t8)

	/* Setup GPIO number for LSUART RX in GPIO IN MUX */
	li  t8, QCA_GPIO_IN_EN0_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_GPIO_IN_EN0_LSUART_RXD_MASK)
	or  t9, t9, (CONFIG_QCA_GPIO_LSUART_RX << QCA_GPIO_IN_EN0_LSUART_RXD_SHIFT)
	sw  t9, 0(t8)

	/*
	 * TODO: what with default LSUART TX line?
	 *
	 * Some of QCA WiSoCs have GPIOs for LSUART TX/RX lines
	 * set by default (10 and 9 respectively) on reset and
	 * others do not (ex. QCA953x?).
	 *
	 * Because of that we can use more than one line
	 * for TX signal if we setup other than default
	 * GPIO for it, without change default GPIO
	 * function.
	 *
	 * Confirmed on AR9344 with LSUART TX set on
	 * GPIO1 and GPIO10 at the same time
	 */

	/*
	 * Set GPIO mode on desired lines and GPIO number
	 * for LSUART TX using GPIO_OUT_FUNCTIONX registers:
	 * -  0 ~  3 -> GPIO_OUT_FUNCTION0 (mask: 0x00000F)
	 * -  4 ~  7 -> GPIO_OUT_FUNCTION1 (mask: 0x0000F0)
	 * -  8 ~ 11 -> GPIO_OUT_FUNCTION2 (mask: 0x000F00)
	 * - 12 ~ 15 -> GPIO_OUT_FUNCTION3 (mask: 0x00F000)
	 * - 16 ~ 19 -> GPIO_OUT_FUNCTION4 (mask: 0x0F0000)
	 * - 20 ~ 23 -> GPIO_OUT_FUNCTION5 (mask: 0xF00000)
	 */
	#if defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) || \
		defined(CONFIG_QCA_GPIO_MASK_INPUTS)  || \
		defined(CONFIG_QCA_GPIO_MASK_LSUART_TX)

		/* GPIO_OUT_FUNCTION0 (GPIO 0~3) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0x00000F) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0x00000F) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x00000F)
	li  t8, QCA_GPIO_OUT_FUNC0_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO0) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO0)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO0_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO1) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO1)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO1_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO2) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO2)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO2_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO3) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO3)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO3_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x00000F)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

		/* GPIO_OUT_FUNCTION1 (GPIO 4~7) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0x0000F0) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0x0000F0) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x0000F0)
	li  t8, QCA_GPIO_OUT_FUNC1_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO4) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO4)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO4_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO5) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO5)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO5_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO6) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO6)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO6_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO7) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO7)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO7_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x0000F0)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

		/* GPIO_OUT_FUNCTION2 (GPIO 8~11) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0x000F00) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0x000F00) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x000F00)
	li  t8, QCA_GPIO_OUT_FUNC2_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO8) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO8)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO8_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO9) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO9)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO9_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO10) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO10)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO10_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO11) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO11)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO11_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x000F00)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

		/* GPIO_OUT_FUNCTION3 (GPIO 12~15) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0x00F000) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0x00F000) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x00F000)
	li  t8, QCA_GPIO_OUT_FUNC3_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO12) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO12)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO12_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO13) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO13)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO13_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO14) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO14)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO14_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO15) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO15)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO15_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x00F000)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

		/* GPIO_OUT_FUNCTION4 (GPIO 16~19) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0x0F0000) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0x0F0000) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x0F0000)
	li  t8, QCA_GPIO_OUT_FUNC4_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO16) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO16)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO16_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO17) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO17)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO17_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO18) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO18)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO18_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO19) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO19)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO19_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0x0F0000)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

		/* GPIO_OUT_FUNCTION5 (GPIO 20~23) */
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS   & 0xF00000) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS    & 0xF00000) || \
			(CONFIG_QCA_GPIO_MASK_LSUART_TX & 0xF00000)
	li  t8, QCA_GPIO_OUT_FUNC5_REG
	lw  t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO20) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO20)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO20_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO21) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO21)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO21_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO22) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO22)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO22_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO23) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO23)
	and t9, t9, ~(QCA_GPIO_OUT_FUNCX_GPIO23_EN_MASK)
			#endif
			#if (CONFIG_QCA_GPIO_MASK_LSUART_TX & 0xF00000)
	and t9, t9, ~(0xFF << CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
	or  t9, t9, (QCA_GPIO_OUT_MUX_LSUART_TXD_VAL << \
				 CONFIG_QCA_GPIO_LSUART_TX_FUNCX_SHIFT)
			#endif
	sw  t9, 0(t8)
		#endif

	#endif /* CONFIG_QCA_GPIO_MASK_OUTPUTS || CONFIG_QCA_GPIO_MASK_INPUTS || CONFIG_QCA_GPIO_MASK_LSUART_TX */

#endif /* (SOC_TYPE & QCA_AR934X_SOC) || (SOC_TYPE & QCA_QCA953X_SOC) || (SOC_TYPE & QCA_QCA955X_SOC) */

/*
 * ===============================
 * Low level GPIO setup for AR933x
 * ===============================
 */
#if (SOC_TYPE & QCA_AR933X_SOC)

	/* Sanity check for JTAG pins (GPIO 6~8) */
	#if defined(CONFIG_SKIP_LOWLEVEL_INIT) || \
		defined(CONFIG_QCA_KEEP_JTAG_ENABLED)
		#if (defined(CONFIG_QCA_GPIO_MASK_INPUTS)  && (CONFIG_QCA_GPIO_MASK_INPUTS  & 0x1C0)) || \
			(defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) && (CONFIG_QCA_GPIO_MASK_OUTPUTS & 0x1C0))
				#error "Cannot use JTAG and GPIO6~8 at the same time!"
		#endif
	#endif

	/*
	 * On AR933x HSUART TX/RX lines are connected to
	 * GPIO10 and GPIO9 respectively, so do not allow
	 * to use those GPIOs as regular at the same time
	 */
	#if defined(CONFIG_QCA_GPIO_MASK_INPUTS) || defined(CONFIG_QCA_GPIO_MASK_OUTPUTS)
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & (GPIO9 | GPIO10)) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS  & (GPIO9 | GPIO10))
			#error "Cannot use HSUART lines as regular GPIOs at the same time!"
		#endif
	#endif

	/*
	 * Workaround for hang issue,
	 * from original Atheros (Q)SDK:
	 *
	 *    "Hornet 1.1 currently need a reset
	 *     once we boot to let the resetb has
	 *     enough time to stable, so that
	 *     trigger reset at 1st boot".
	 *
	 * Read one 4 byte value from SRAM base address and compare it with
	 * known magic number (0x12345678 here), if it's the same, it means
	 * that this is not first boot and we can continue. Otherwise, make
	 * full chip reset (it's not power reset, SRAM data will survive).
	 *
	 * We need it here as it's first custom asm code executed in start{_bootstrap).S
	 *
	 * TODO: FIXME!
	 */
first_boot:
	li  t8, 0xBD000000
	lw  t9, 0(t8)
	li  t7, 0x12345678
	sw  t7, 0(t8)
	bne t9, t7, full_reset
	nop

	b gpio_setup
	nop

full_reset:
	li t8, QCA_RST_RESET_REG
	lw t9, 0(t8)
	or t9, t9, (QCA_RST_RESET_FULL_CHIP_RST_MASK | \
				QCA_RST_RESET_DDR_RST_MASK)
	sw t9, 0(t8)
	nop
	nop
	nop
	nop

	/*
	 * GPIO configuration, using GPIO_FUNCTION_1 register:
	 * 1. Disable JTAG by default
	 * 2. Enable HSUART on GPIO9 and GPIO10 by default
	 * 3. Disable HSUART RTS/CTS on GPIO11/12 if needed
	 * 4. Disable selected Ethernet switch LEDs if needed
	 */
gpio_setup:
	li  t8, QCA_GPIO_FUNC_1_REG
	lw  t9, 0(t8)
	#if defined(CONFIG_SKIP_LOWLEVEL_INIT) || \
		defined(CONFIG_QCA_KEEP_JTAG_ENABLED)
	and t9, t9, ~(QCA_GPIO_FUNC_1_JTAG_DIS_MASK)
	or  t9, t9, QCA_GPIO_FUNC_1_UART_EN_MASK
	#else
	or  t9, t9, (QCA_GPIO_FUNC_1_JTAG_DIS_MASK | \
				 QCA_GPIO_FUNC_1_UART_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & (GPIO11 | GPIO12)) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & (GPIO11 | GPIO12))
	and t9, t9, ~(QCA_GPIO_FUNC_1_UART_RTS_CTS_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO13) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO13)
	and t9, t9, ~(QCA_GPIO_FUNC_1_ETH_SW_LED0_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO14) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO14)
	and t9, t9, ~(QCA_GPIO_FUNC_1_ETH_SW_LED1_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO15) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO15)
	and t9, t9, ~(QCA_GPIO_FUNC_1_ETH_SW_LED2_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO16) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO16)
	and t9, t9, ~(QCA_GPIO_FUNC_1_ETH_SW_LED3_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO17) || \
		(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO17)
	and t9, t9, ~(QCA_GPIO_FUNC_1_ETH_SW_LED4_EN_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO9)
	and t9, t9, ~(QCA_GPIO_FUNC_1_SPI_CS_EN1_MASK)
	#endif
	#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO10)
	and t9, t9, ~(QCA_GPIO_FUNC_1_SPI_CS_EN2_MASK)
	#endif
	/* From datasheet: bit 15 should be written with 1 */
	or  t9, t9, ((1 << 15) | \
				 QCA_GPIO_FUNC_1_SPI_EN_MASK)
	sw  t9, 0(t8)

	/* Enable regular GPIO function on GPIO26 and/or GPIO27 if needed */
	#if defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) || \
		defined(CONFIG_QCA_GPIO_MASK_INPUTS)
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & (GPIO26 | GPIO27)) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS  & (GPIO26 | GPIO27))
	li t8, QCA_RST_BOOTSTRAP_REG
	lw t9, 0(t8)
	or t9, t9, QCA_RST_BOOTSTRAP_MDIO_GPIO_EN_MASK
	sw t9, 0(t8)
		#endif
	#endif

	/* Enable regular GPIO function on GPIO11 and/or GPIO12 if needed */
	#if defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) || \
		defined(CONFIG_QCA_GPIO_MASK_INPUTS)
		#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & (GPIO11 | GPIO12)) || \
			(CONFIG_QCA_GPIO_MASK_INPUTS  & (GPIO11 | GPIO12))
	li t8, QCA_GPIO_FUNC_2_REG
	lw t9, 0(t8)
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO11) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO11)
	or t9, t9, QCA_GPIO_FUNC_2_JUMPSTART_DIS_MASK
			#endif
			#if (CONFIG_QCA_GPIO_MASK_OUTPUTS & GPIO12) || \
				(CONFIG_QCA_GPIO_MASK_INPUTS  & GPIO12)
	or t9, t9, QCA_GPIO_FUNC_2_WPS_DIS_MASK
			#endif
	sw t9, 0(t8)
		#endif
	#endif

	/* Setup init states on requested GPIO lines */
	li  t8, QCA_GPIO_OUT_REG
	lw  t9, 0(t8)
	#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI
	or  t9, t9, CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_HI
	#endif
	#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_OUTPUTS_INIT_LO)
	#endif
	sw  t9, 0(t8)

	/* Setup GPIOs in OE register */
	#if defined(CONFIG_QCA_GPIO_MASK_OUTPUTS) || \
		defined(CONFIG_QCA_GPIO_MASK_INPUTS)
	li  t8, QCA_GPIO_OE_REG
	lw  t9, 0(t8)
		#ifdef CONFIG_QCA_GPIO_MASK_OUTPUTS
	or  t9, t9, CONFIG_QCA_GPIO_MASK_OUTPUTS
		#endif
		#ifdef CONFIG_QCA_GPIO_MASK_INPUTS
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_INPUTS)
		#endif
	sw  t9, 0(t8)
	#endif

#endif /* (SOC_TYPE & QCA_AR933X_SOC) */

/*
 * Custom, GPIO related code for boards should go here,
 * after initial/basic GPIO configuration
 */

	jr ra
	nop

.end lowlevel_gpio_init

/*
 * Set all predefined GPIO driven LEDs ON
 */

.globl all_led_on
.type  all_led_on, @function
.align 4
.text
.ent all_led_on

all_led_on:
#if defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI) || \
	defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO)
	li  t8, QCA_GPIO_OUT_REG
	lw  t9, 0(t8)
	#ifdef CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI
	or  t9, t9, CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI
	#endif
	#ifdef CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO)
	#endif
	sw  t9, 0(t8)
#else
	nop
#endif

	jr	ra
	nop

.end all_led_on

/*
 * Set all predefined GPIO driven LEDs OFF
 */

.globl all_led_off
.type  all_led_off, @function
.align 4
.text
.ent all_led_off

all_led_off:
#if defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI) || \
	defined(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO)
	li  t8, QCA_GPIO_OUT_REG
	lw  t9, 0(t8)
	#ifdef CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI
	and t9, t9, ~(CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_HI)
	#endif
	#ifdef CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	or t9, t9, CONFIG_QCA_GPIO_MASK_LEDS_ACTIVE_LO
	#endif
	sw  t9, 0(t8)
#else
	nop
#endif

	jr	ra
	nop

.end all_led_off
