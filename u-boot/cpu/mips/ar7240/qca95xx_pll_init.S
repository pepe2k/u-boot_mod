/*
 * PLL and clocks configurations for
 * Qualcomm/Atheros AR934x and QCA95xx WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <soc/qca_pll_list.h>
#include <config.h>
#include <soc/qca_soc_common.h>
#include <soc/qca95xx_pll_init.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>

#define reg_oc_recovery		t0
#define reg_spi_ctrl_cfg	t1
#define reg_ref_clk_val		t2
#define reg_cpu_pll_cfg		t3
#define reg_ddr_pll_cfg		t4
#define reg_cpu_ddr_clk		t5
#define reg_cpu_pll_dit		t6
#define reg_ddr_pll_dit		t7

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

	b ahb_max_timeout
	nop

set_xtal_40mhz:
	li reg_ref_clk_val, 40

/* AHB max master timeout */
ahb_max_timeout:
	li t8, QCA_AHB_MASTER_TOUT_MAX_REG
	lw t9, 0(t8)
	or t9, t9, 0xFFFFF
	sw t9, 0(t8)

/*
 * Reset RTC:
 * 1. First reset RTC submodule using RST_RESET register
 * 2. Then use RTC_SYNC_RESET register
 * 3. And at the end, wait for ON_STATE bit set in RTC_SYNC_STATUS register
 *
 * TODO: do we need to reset RTC at all?
 */
rtc_reset:
	li  t8, QCA_RST_RESET_REG
	lw  t9, 0(t8)
	or  t9, t9, QCA_RST_RESET_RTC_RST_MASK
	sw  t9, 0(t8)
	nop
	nop

	lw  t9, 0(t8)
	and t9, t9, ~QCA_RST_RESET_RTC_RST_MASK
	sw  t9, 0(t8)
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
 *    - DDR_PLL_CONFIG (offset 12)
 *    - CPU_DDR_CLOCK_CONTROL (offset 16)
 *    - CPU_PLL_DITHER (offset 20)
 *    - DDR_PLL_DITHER (offset 24)
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
	lw reg_spi_ctrl_cfg, 4(t8)
	lw reg_cpu_pll_cfg,  8(t8)
	lw reg_ddr_pll_cfg, 12(t8)
	lw reg_cpu_ddr_clk, 16(t8)
	lw reg_cpu_pll_dit, 20(t8)
	lw reg_ddr_pll_dit, 24(t8)
	b  cpu_ddr_clock_control
	nop
#endif /* CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET */

/*
 * Check XTAL type and include dedicated PLL/clocks values,
 * predefined in header file, based on selected preset configuration
 */
xtal_type_check:
	beq reg_ref_clk_val, 40, xtal_is_40mhz
	nop

xtal_is_25mhz:
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	beq reg_oc_recovery, 1, xtal_is_25mhz_recovery
	nop
#endif

	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25
	li reg_ddr_pll_cfg,  QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25
	li reg_cpu_ddr_clk,  QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25
	li reg_ddr_pll_dit,  QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25
	b  cpu_ddr_clock_control
	nop

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
xtal_is_25mhz_recovery:
	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL_SAFE
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL25
	li reg_ddr_pll_cfg,  QCA_PLL_DDR_PLL_CFG_REG_VAL_SAFE_XTAL25
	li reg_cpu_ddr_clk,  QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_SAFE_XTAL25
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_REG_VAL_SAFE_XTAL25
	li reg_ddr_pll_dit,  QCA_PLL_DDR_PLL_DITHER_REG_VAL_SAFE_XTAL25
	b  cpu_ddr_clock_control
	nop
#endif

xtal_is_40mhz:
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	beq reg_oc_recovery, 1, xtal_is_40mhz_recovery
	nop
#endif

	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40
	li reg_ddr_pll_cfg,  QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40
	li reg_cpu_ddr_clk,  QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40
	li reg_ddr_pll_dit,  QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	b  cpu_ddr_clock_control
	nop

xtal_is_40mhz_recovery:
	li reg_spi_ctrl_cfg, QCA_SPI_CTRL_REG_VAL_SAFE
	li reg_cpu_pll_cfg,  QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL40
	li reg_ddr_pll_cfg,  QCA_PLL_DDR_PLL_CFG_REG_VAL_SAFE_XTAL40
	li reg_cpu_ddr_clk,  QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_SAFE_XTAL40
	li reg_cpu_pll_dit,  QCA_PLL_CPU_PLL_DITHER_REG_VAL_SAFE_XTAL40
	li reg_ddr_pll_dit,  QCA_PLL_DDR_PLL_DITHER_REG_VAL_SAFE_XTAL40
#endif

/*
 * Load target value into CPU_DDR_CLOCK_CONTROL register,
 * but for now keep bypass enabled for all clocks (CPU, DDR, AHB)
 * (by default, after reset, they should be bypassed, do it just in case)
 */
cpu_ddr_clock_control:
	li   t8, QCA_PLL_CPU_DDR_CLK_CTRL_REG
	move t9, reg_cpu_ddr_clk
	or   t9, t9, (QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)
	sw   t9, 0(t8)

/*
 * Load target values into CPU/DDR_PLL_CONFIG registers, but for now keep PLLs down
 * (by default, after reset, it should be powered down, do it just in case)
 */
cpu_pll_config:
	li   t8, QCA_PLL_CPU_PLL_CFG_REG
	move t9, reg_cpu_pll_cfg
	or   t9, t9, QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw   t9, 0(t8)

ddr_pll_config:
	li   t8, QCA_PLL_DDR_PLL_CFG_REG
	move t9, reg_ddr_pll_cfg
	or   t9, t9, QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	sw   t9, 0(t8)

/* Load target NFRAC_MIN values into CPU/DDR_PLL_DITHER registers */
cpu_pll_dither:
	li  t8, QCA_PLL_CPU_PLL_DITHER_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK
	or  t9, t9, reg_cpu_pll_dit
	sw  t9, 0(t8)

ddr_pll_dither:
	li  t8, QCA_PLL_DDR_PLL_DITHER_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK
	or  t9, t9, reg_ddr_pll_dit
	sw  t9, 0(t8)

/* Disable PLL configuration over SRIF registers (just for sure) */
cpu_pll_srif_disable:
	li  t8, QCA_PLL_SRIF_CPU_DPLL2_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_SRIF_DPLL2_LOCAL_PLL_MASK
	sw  t9, 0(t8)

ddr_pll_srif_disable:
	li  t8, QCA_PLL_SRIF_DDR_DPLL2_REG
	lw  t9, 0(t8)
	and t9, t9, ~QCA_PLL_SRIF_DPLL2_LOCAL_PLL_MASK
	sw  t9, 0(t8)

/* Enable CPU PLL (only if we need it) and wait for update complete */
cpu_pll_enable:
	move t8, reg_cpu_pll_cfg
	and  t8, t8, QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	bgtz t8, ddr_pll_enable
	nop
	li   t8, QCA_PLL_CPU_PLL_CFG_REG
	lw   t9, 0(t8)
	and  t9, t9, ~QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw   t9, 0(t8)
	nop

/* Wait for CPU PLL update complete */
cpu_pll_wait:
	lw   t9, 0(t8)
	and  t9, t9, QCA_PLL_CPU_PLL_CFG_UPDATING_MASK
	bgtz t9, cpu_pll_wait
	nop

/* Enable DDR PLL (only if we need it) and wait for update complete */
ddr_pll_enable:
	move t8, reg_ddr_pll_cfg
	and  t8, t8, QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	bgtz t8, pll_bypass_disable
	nop
	li   t8, QCA_PLL_DDR_PLL_CFG_REG
	lw   t9, 0(t8)
	and  t9, t9, ~QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	sw   t9, 0(t8)
	nop

/* Wait for DDR PLL update complete */
ddr_pll_wait:
	lw   t9, 0(t8)
	and  t9, t9, QCA_PLL_DDR_PLL_CFG_UPDATING_MASK
	bgtz t9, ddr_pll_wait
	nop

/* Disable bypassing all clocks */
pll_bypass_disable:
	li  t8, QCA_PLL_CPU_DDR_CLK_CTRL_REG
	lw  t9, 0(t8)
	and t9, t9, ~(QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)
	sw  t9, 0(t8)

/* Setup SPI (clock and other settings) */
spi_setup:

#ifdef CONFIG_QCA_PLL_SPI_FLASH_CLK_AUTO
	/*
	 * Configure SPI FLASH and clock:
	 * 1. Check which PLL is used to drive AHB clock
	 * 2. Calculate selected PLL output value
	 * 3. Calculate target AHB clock value
	 * 4. Find minimum divider for SPI clock
	 * 5. Setup SPI FLASH clock and other related options (REMAP, etc.)
	 */
	li t8, QCA_PLL_CPU_DDR_CLK_CTRL_REG
	lw t9, 0(t8)

	and  t3, t9, QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_MASK
	srl  t3, t3, QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_SHIFT
	/* t3 = AHB_POST_DIV + 1 */
	addi t3, t3, 1

	/* Find out where AHB clock come from (CPU or DDR PLL) */
	and  t9, t9, QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_MASK
	bgtz t9, ahb_clk_from_ddr_pll
	nop

ahb_clk_from_cpu_pll:
	li t8, QCA_PLL_CPU_PLL_CFG_REG
	lw t9, 0(t8)

	/* Calculate NINT */
	and t8, t9, QCA_PLL_CPU_PLL_CFG_NINT_MASK
	srl t8, t8, QCA_PLL_CPU_PLL_CFG_NINT_SHIFT
	mul t4, t8, reg_ref_clk_val						/* t4 = REFCLK * NINT */

	/* Calculate OUTDIV */
	and  t8, t9, QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK
	srl  t8, t8, QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT
	li   t5, 1
	sllv t5, t5, t8									/* t5 = 2 ^ OUTDIV */

	/* Calculate REFDIV */
	and t8, t9, QCA_PLL_CPU_PLL_CFG_REFDIV_MASK
	srl t8, t8, QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT
	mul t5, t8, t5									/* t5 = REDIV * (2 ^ OUTDIV) */
	nop

	b ahb_clk_calculation
	nop

ahb_clk_from_ddr_pll:
	li t8, QCA_PLL_DDR_PLL_CFG_REG
	lw t9, 0(t8)

	/* Calculate NINT */
	and t8, t9, QCA_PLL_DDR_PLL_CFG_NINT_MASK
	srl t8, t8, QCA_PLL_DDR_PLL_CFG_NINT_SHIFT
	mul t4, t8, reg_ref_clk_val						/* t4 = REFCLK * NINT */

	/* Calculate OUTDIV */
	and  t8, t9, QCA_PLL_DDR_PLL_CFG_OUTDIV_MASK
	srl  t8, t8, QCA_PLL_DDR_PLL_CFG_OUTDIV_SHIFT
	li   t5, 1
	sllv t5, t5, t8									/* t5 = 2 ^ OUTDIV */

	/* Calculate REFDIV */
	and t8, t9, QCA_PLL_DDR_PLL_CFG_REFDIV_MASK
	srl t8, t8, QCA_PLL_DDR_PLL_CFG_REFDIV_SHIFT
	mul t5, t8, t5									/* t5 = REDIV * (2 ^ OUTDIV) */
	nop
	nop

ahb_clk_calculation:
	mul t5, t5, t3									/* t5 = REDIV * (2 ^ OUTDIV) * (AHB_POST_DIV + 1) */
	nop
	nop

	/* Store AHB CLK in t3 */
	div t3, t4, t5

	li t9, CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ
	li t6, 0										/* t6 = CLOCK_DIVIDER for SPI FLASH clock */

/* Maximum SPI clock divider loop */
spi_clk_calculation:
	move t7, t6
	addi t7, t7, 1
	sll  t7, t7, 1									/* t7 = 2 * (CLOCK_DIVIDER + 1) */
	div  t4, t3, t7									/* t4 = SPI FLASH clock */
	sltu t5, t4, t9									/* t4 < t9 ? t5 = 1 : t5 = 0 */

	/* SPI clock == target maximum clock? */
	beq t4, t9, spi_clk_setup
	nop

	/* SPI clock < target maximum clock? */
	bgtz t5, spi_clk_setup
	nop

	addi t6, t6, 1
	b spi_clk_calculation
	nop

spi_clk_setup:
	sll t6, t6, QCA_SPI_CTRL_CLK_DIV_SHIFT
	and reg_spi_ctrl_cfg, reg_spi_ctrl_cfg, ~QCA_SPI_CTRL_CLK_DIV_MASK
	or  reg_spi_ctrl_cfg, reg_spi_ctrl_cfg, t6
#endif /* CONFIG_QCA_PLL_SPI_FLASH_CLK_AUTO */

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
