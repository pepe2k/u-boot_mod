/*
 * PLL and clocks configurations for
 * Qualcomm/Atheros AR933x WiSoC
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <soc/qca_pll_list.h>
#include <config.h>
#include <soc/qca_soc_common.h>
#include <soc/ar933x_pll_init.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>

#define reg_oc_recovery		t0
#define reg_spi_ctrl_cfg	t1
#define reg_ref_clk_val		t2
#define reg_cpu_pll_cfg		t3
#define reg_cpu_clk_ctrl	t4
#define reg_cpu_pll_dit		t5
#define reg_loop_counter	t6

/* Sanity check for O/C recovery button number */
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	#if (CONFIG_QCA_GPIO_OC_RECOVERY_BTN >= QCA_GPIO_COUNT)
		#error "O/C recovery button number is not correct!"
	#endif

	#define CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN	\
					(1 << CONFIG_QCA_GPIO_OC_RECOVERY_BTN)
#endif

.globl lowlevel_init
.type  lowlevel_init, @function
.align 4
.text
.ent lowlevel_init

lowlevel_init:

/*
 * Get reference clock (XTAL) type, based on BOOTSTRAP register
 * and save its value in one register for later use
 */
	li   reg_ref_clk_val, 25
	li   t8, QCA_RST_BOOTSTRAP_REG
	lw   t9, 0(t8)
	li   t8, QCA_RST_BOOTSTRAP_REF_CLK_MASK
	and  t9, t9, t8
	bgtz t9, set_xtal_40mhz
	nop

	b wlan_rst_init
	nop

set_xtal_40mhz:
	li reg_ref_clk_val,  40

/*
 * Several WLAN module resets as in Atheros (Q)SDK
 */
wlan_rst_init:
	li  t8, QCA_RST_RESET_REG

	/* 2x WLAN resets */
	lw  t9, 0(t8)
	or  t9, t9, QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop
	lw  t9, 0(t8)
	and t9, t9, ~QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop

	lw  t9, 0(t8)
	or  t9, t9, QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop
	lw  t9, 0(t8)
	and t9, t9, ~QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop

wlan_rst:
	li  t8, QCA_RST_RESET_REG

	lw  t9, 0(t8)
	or  t9, t9, QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop
	lw  t9, 0(t8)
	and t9, t9, ~QCA_RST_RESET_WLAN_RST_MASK
	sw  t9, 0(t8)
	nop
	nop

	li reg_loop_counter, 30

eep_busy:
	beq  zero, reg_loop_counter, wlan_rst
	nop
	addi reg_loop_counter, reg_loop_counter, -1
	li   t8, QCA_RST_BOOTSTRAP_REG
	lw   t9, 0(t8)
	and  t9, t9, QCA_RST_BOOTSTRAP_EEPBUSY_MASK
	bnez t9, eep_busy
	nop

/*
 * From datasheet:
 * For normal operation mode, SW should select
 * the APB interface before register access
 *
 * Register: BOOTSTRAP, bit: 17 (JTAG=1, APB=0)
 * Should be set by default, but it's not...
 */
sel_apb_for_mac:
	li  t8, QCA_RST_BOOTSTRAP_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_RST_BOOTSTRAP_JTAG_APB_SEL_MASK
	sw  t9, 0(t8)

/* AHB max master timeout */
ahb_max_timeout:
	li t8, QCA_AHB_MASTER_TOUT_MAX_REG
	lw t9, 0(t8)
	or t9, t9, 0xFFFFF
	sw t9, 0(t8)

/*
 * Reset RTC
 * TODO: do we need to reset RTC at all?
 */
rtc_reset:
	li  t8, QCA_RTC_SYNC_FORCE_WAKE_REG
	li  t9, (QCA_RTC_SYNC_FORCE_WAKE_EN_MASK |\
			 QCA_RTC_SYNC_FORCE_WAKE_MACINTR_MASK)
	sw  t9, 0(t8)
	nop
	nop

	li  t8, QCA_RTC_SYNC_RST_REG
	li  t9, 0x0
	sw  t9, 0(t8)
	nop
	nop

	li  t9, QCA_RTC_SYNC_RST_RESET_MASK
	sw  t9, 0(t8)
	nop

	li  t8, QCA_RTC_SYNC_STATUS_REG

rtc_wait_on:
	lw   t9, 0(t8)
	and  t9, t9, QCA_RTC_SYNC_STATUS_ON_MASK
	beqz t9, rtc_wait_on
	nop

/*
 * O/C recovery mode (start with safe PLL/clocks configuration):
 * 1. Check if defined recovery button is pressed
 * 2. Indicate recovery mode in predefined register
 * 3. If in recovery mode, do not use PLL configuration from FLASH,
 *    because it is probably the reason why user is using recovery mode
 */
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
is_oc_recovery_btn_pressed:
	li  reg_oc_recovery, 0
	li  t8, QCA_GPIO_IN_REG
	lw  t9, 0(t8)
	and t9, t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN

	#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN_ACTIVE_LOW
	bne t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN, in_oc_recovery_mode
	nop
	#else
	beq t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN, in_oc_recovery_mode
	nop
	#endif

	#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
	b is_pll_cfg_in_flash
	#else
	b xtal_type_check
	#endif
	nop

in_oc_recovery_mode:
	li reg_oc_recovery, 1
	b  xtal_type_check
	nop
#endif /* CONFIG_QCA_GPIO_OC_RECOVERY_BTN */

/*
 * Check if PLL configuration is stored in FLASH:
 * 1. Get 32-bit value from defined offset in FLASH
 * 2. Compare it with predefined magic value
 * 3. If values are not equal, continue default PLL/clocks configuration
 * 4. If values are equal it means we should have target PLL/clocks register
 *    values stored in FLASH, just after magic value, in the following order:
 *    - SPI_CONTROL (offset 4)
 *    - CPU_PLL_CONFIG (offset 8)
 *    - CPU_CLOCK_CONTROL (offset 12)
 *    - CPU_PLL_DITHER_FRAC (offset 16)
 * 5. After loading target values from FLASH,
 *    jump directly to PLL/clocks configuration
 */
#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
is_pll_cfg_in_flash:
	li  t8, CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
	lw  t9, 0(t8)
	bne t9, QCA_PLL_IN_FLASH_MAGIC, xtal_type_check
	nop

pll_cfg_in_flash:
	lw reg_spi_ctrl_cfg,  4(t8)
	lw reg_cpu_pll_cfg,   8(t8)
	lw reg_cpu_clk_ctrl, 12(t8)
	lw reg_cpu_pll_dit,  16(t8)
	b  cpu_clock_control
	nop
#endif /* CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET */

/*
 * Check XTAL type, configure PLL settle time and include dedicated
 * PLL/clocks values, predefined in header file, based on selected
 * preset configuration
 */
xtal_type_check:
	beq reg_ref_clk_val, 40, xtal_is_40mhz
	nop

xtal_is_25mhz:
	li t8, QCA_PLL_CPU_PLL_CFG2_REG
	li t9, QCA_PLL_CPU_PLL_CFG2_SETTLE_TIME_REG_VAL_XTAL25
	sw t9, 0(t8)

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	beq reg_oc_recovery, 1, xtal_is_25mhz_recovery
	nop
#endif

	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25
	li reg_cpu_clk_ctrl, QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL25
	b  cpu_clock_control
	nop

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
xtal_is_25mhz_recovery:
	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL_SAFE
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL25
	li reg_cpu_clk_ctrl, QCA_PLL_CPU_CLK_CTRL_REG_VAL_SAFE_XTAL25
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_SAFE_XTAL25
	b  cpu_clock_control
	nop
#endif

xtal_is_40mhz:
	li t8, QCA_PLL_CPU_PLL_CFG2_REG
	li t9, QCA_PLL_CPU_PLL_CFG2_SETTLE_TIME_REG_VAL_XTAL40
	sw t9, 0(t8)

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	beq reg_oc_recovery, 1, xtal_is_40mhz_recovery
	nop
#endif

	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40
	li reg_cpu_clk_ctrl, QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL40

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	b  cpu_clock_control
	nop

xtal_is_40mhz_recovery:
	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL_SAFE
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL40
	li reg_cpu_clk_ctrl, QCA_PLL_CPU_CLK_CTRL_REG_VAL_SAFE_XTAL40
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_SAFE_XTAL40
#endif

/*
 * Load target value into CPU_CLOCK_CONTROL register, but for now keep bypass
 * enabled (by default, after reset, it should be bypassed, do it just in case)
 */
cpu_clock_control:
	li   t8, QCA_PLL_CPU_CLK_CTRL_REG
	move t9, reg_cpu_clk_ctrl
	or   t9, t9, QCA_PLL_CPU_CLK_CTRL_BYPASS_MASK
	sw   t9, 0(t8)

/*
 * Load target value into CPU_PLL_CONFIG register, but for now keep PLL down
 * (by default, after reset, it should be powered down, do it just in case)
 */
cpu_pll_config:
	li   t8, QCA_PLL_CPU_PLL_CFG_REG
	move t9, reg_cpu_pll_cfg
	or   t9, t9, QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw   t9, 0(t8)

/* Load target NFRAC_MIN value into PLL_DITHER_FRAC register */
cpu_pll_dither:
	li  t8, QCA_PLL_CPU_PLL_DITHER_FRAC_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK
	or  t9, t9, reg_cpu_pll_dit
	sw  t9, 0(t8)

/* Enable CPU PLL and wait for update complete */
cpu_pll_enable:
	li  t8, QCA_PLL_CPU_PLL_CFG_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw  t9, 0(t8)
	nop

/* Wait for CPU PLL update complete */
cpu_pll_wait:
	lw   t9, 0(t8)
	and  t9, t9, QCA_PLL_CPU_PLL_CFG_UPDATING_MASK
	bgtz t9, cpu_pll_wait
	nop

/* Disable bypassing all clocks, use target AHB_POST_DIV value */
pll_bypass_disable:
	li  t8, QCA_PLL_CPU_CLK_CTRL_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_CPU_CLK_CTRL_BYPASS_MASK
	sw  t9, 0(t8)

/* Setup SPI (clock and other settings) */
spi_setup:
	li   t8, QCA_SPI_CTRL_REG
	sw   reg_spi_ctrl_cfg, 0(t8)
	and  reg_spi_ctrl_cfg, reg_spi_ctrl_cfg, QCA_SPI_CTRL_REMAP_DIS_MASK
	beqz reg_spi_ctrl_cfg, end
	nop

/*
 * This is a small hack, needed after setting REMAP_DISABLE bit
 * in SPI_CONTROL_ADDR register.
 *
 * Before that, SPI FLASH is mapped to 0x1FC00000, but just after
 * setting REMAP_DISABLE bit, aliasing is disabled and SPI FLASH
 * is mapped to 0x1F00000, so that the whole 16 MB address space
 * could be used.
 *
 * That means, we need to "fix" return address, stored previously
 * in $ra register, subtracting a value 0x00C00000 from it.
 *
 * Without that, jump would end up somewhere far away on FLASH...
 */
	li   t8, 0x00C00000
	subu ra, ra, t8

end:
	jr ra
	nop

.end lowlevel_init
