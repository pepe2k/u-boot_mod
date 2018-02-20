/*
 * PLL and clocks configurations for
 * Qualcomm/Atheros QCA956x WiSoCs
 *
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2018 Julien Dusser <julien.dusser@free.fr>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <soc/qca956x_pll_init.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/* Sanity check for O/C recovery button number */
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
	#if (CONFIG_QCA_GPIO_OC_RECOVERY_BTN >= QCA_GPIO_COUNT)
		#error "O/C recovery button number is not correct!"
	#endif

	#define CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN	\
					(1 << CONFIG_QCA_GPIO_OC_RECOVERY_BTN)
#endif

/*
 * Helper macros.
 * These Clobber t8 and t9
 */
#define reg_write(_reg, _val)			\
	li	t9,	KSEG1ADDR(_reg);	\
	li	t8,	_val;			\
	sw	t8,	0(t9);

#define UPPER(ADDR) ((ADDR)>>16)
#define LOWER(ADDR) ((ADDR)&0xffff)
/******************************************************************************
 * first level initialization:
 *
 * 0) If clock cntrl reset switch is already set, we're recovering from
 *    "divider reset"; goto 3.
 * 1) Setup divide ratios.
 * 2) Reset.
 * 3) Setup pll's, wait for lock.
 *
 *****************************************************************************/

.globl lowlevel_init
	.type	lowlevel_init, @function
	.text
	.align 4

lowlevel_init:
	lui	t8, UPPER(QCA_PLL_SRIF_BASE_REG)
	li	t9, (2 << QCA_PLL_SRIF_DPLL2_KI_SHIFT | \
				0xa << QCA_PLL_SRIF_DPLL2_KD_SHIFT | \
				1 << QCA_PLL_SRIF_DPLL2_OUTDIV_SHIFT | \
				QCA_PLL_SRIF_DPLL2_PLLPWD_MASK | \
				0x6 << QCA_PLL_SRIF_DPLL2_PHASE_SHIFT_SHIFT)
	sw	t9, LOWER(QCA_PLL_SRIF_BB_DPLL2_REG)(t8)

	li	t9, (2 << QCA_PLL_SRIF_DPLL2_KI_SHIFT | \
                0xa << QCA_PLL_SRIF_DPLL2_KD_SHIFT | \
				QCA_PLL_SRIF_DPLL2_PLLPWD_MASK | \
				0x3 << QCA_PLL_SRIF_DPLL2_OUTDIV_SHIFT | \
				0x6 << QCA_PLL_SRIF_DPLL2_PHASE_SHIFT_SHIFT)
	sw	t9, LOWER(QCA_PLL_SRIF_PCIE_DPLL2_REG)(t8)

	li	t9, (2 << QCA_PLL_SRIF_DPLL2_KI_SHIFT | \
				0xa << QCA_PLL_SRIF_DPLL2_KD_SHIFT | \
				QCA_PLL_SRIF_DPLL2_PLLPWD_MASK | \
				0x6 << QCA_PLL_SRIF_DPLL2_PHASE_SHIFT_SHIFT)
	sw	t9, LOWER(QCA_PLL_SRIF_DDR_DPLL2_REG)(t8)

	li	t9, (2 << QCA_PLL_SRIF_DPLL2_KI_SHIFT | \
				0x7 << QCA_PLL_SRIF_DPLL2_KD_SHIFT  | \
				QCA_PLL_SRIF_DPLL2_PLLPWD_MASK | \
				0x6 << QCA_PLL_SRIF_DPLL2_PHASE_SHIFT_SHIFT);
	sw	t9, LOWER(QCA_PLL_SRIF_CPU_DPLL2_REG)(t8)

	lui	t0,	UPPER(KSEG1ADDR(QCA_PLL_BASE_REG))
#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
is_oc_recovery_btn_pressed:
	li  t8, QCA_GPIO_IN_REG
	lw  t9, 0(t8)
	and t9, t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN

	#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN_ACTIVE_LOW
	bne t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN, init_with_const
	nop
	#else
	beq t9, CONFIG_QCA_GPIO_MASK_OC_RECOVERY_BTN, init_with_const
	nop
	#endif
#endif /* CONFIG_QCA_GPIO_OC_RECOVERY_BTN */

#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
	li	t1,	CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
	lw	t8,	0(t1)
	li	t9,	QCA_PLL_IN_FLASH_MAGIC
	bne	t9,	t8,	init_with_const
	nop
#else
	b init_with_const
	nop
#endif

init_from_flash:
	/* Too much register to fit in t0-t8 */
	/*
	u32 magic;				0
	u32 SPI; TODO			4
	u32 cpu_pll_cfg1;		8
	u32 ddr_pll_cfg1;		12
	u32 cpu_pll_cfg;		16
	u32 ddr_pll_cfg;		20
	u32 cpu_ddr_clk_ctrl;	24
	u32 cpu_pll_dit;		28
	u32 ddr_pll_dit;		32
	u32 cpu_pll_dit2;		36
	u32 ddr_pll_dit2;		40
	*/

init_keep_spi_value_from_flash:
	lw	t2, 4(t1)

/*
 * Load target value into CPU_DDR_CLOCK_CONTROL register,
 * but for now keep bypass enabled for all clocks (CPU, DDR, AHB)
 * (by default, after reset, they should be bypassed, do it just in case)
 */

init_ahb_pll_ft2rom_flash:
	lw	t9, 24(t1)
	or	t9, t9,	(QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK | \
					QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK | \
					QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)
	sw	t9,	LOWER(QCA_PLL_CPU_DDR_CLK_CTRL_REG)(t0)

init_cpu_pll_from_flash:
	lw	t9, 16(t1)
	or	t9, t9, QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw	t9,	LOWER(QCA_PLL_CPU_PLL_CFG_REG)(t0)
	lw	t9, 8(t1)
	sw  t9, LOWER(QCA_PLL_CPU_PLL_CFG1_REG)(t0)

init_ddr_pll_from_flash:
	lw	t9, 20(t1)
	or	t9, t9, QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	sw	t9,	LOWER(QCA_PLL_DDR_PLL_CFG_REG)(t0)
	lw	t9, 12(t1)
	sw  t9, LOWER(QCA_PLL_DDR_PLL_CFG1_REG)(t0)

init_ddr_pll_dither_from_flash:
	lw	t9, 32(t1)
	sw	t9,	LOWER(QCA_PLL_DDR_PLL_DITHER_REG)(t0)
	lw	t9, 40(t1)
	sw	t9,	LOWER(QCA_PLL_DDR_PLL_DITHER2_REG)(t0)

init_cpu_pll_dither_from_flash:
	lw	t9, 28(t1)
	sw	t9,	LOWER(QCA_PLL_CPU_PLL_DITHER_REG)(t0)
	lw	t9, 36(t1)
	sw	t9,	LOWER(QCA_PLL_CPU_PLL_DITHER2_REG)(t0)

	j	cpu_pll_enable

init_with_const:

init_keep_spi_value_from_const:
	li	t2, QCA_SPI_CTRL_REG_VAL

/*
 * Load target value into CPU_DDR_CLOCK_CONTROL register,
 * but for now keep bypass enabled for all clocks (CPU, DDR, AHB)
 * (by default, after reset, they should be bypassed, do it just in case)
 */
init_ahb_pll_with_const:
	li t9,	(QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25 | \
					QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK | \
					QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK | \
					QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)
	sw	t9,	LOWER(QCA_PLL_CPU_DDR_CLK_CTRL_REG)(t0)

init_cpu_pll_with_const:
	li	t9, QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25
	or	t9, t9, QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw	t9,	LOWER(QCA_PLL_CPU_PLL_CFG_REG)(t0)
	li	t9, QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25
	sw  t9, LOWER(QCA_PLL_CPU_PLL_CFG1_REG)(t0)

init_ddr_pll_with_const:
	li	t9, QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25
	or	t9, t9, QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	sw	t9,	LOWER(QCA_PLL_DDR_PLL_CFG_REG)(t0)
	li	t9, QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25
	sw  t9, LOWER(QCA_PLL_DDR_PLL_CFG1_REG)(t0)

ddr_pll_dither_with_const:
	li	t9, QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25
	sw	t9,	LOWER(QCA_PLL_DDR_PLL_DITHER_REG)(t0)
	li	t9, QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25
	sw  t9, LOWER(QCA_PLL_DDR_PLL_DITHER2_REG)(t0)

cpu_pll_dither_with_const:
	li	t9, QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25
	sw	t9,	LOWER(QCA_PLL_CPU_PLL_DITHER_REG)(t0)
	li	t9, QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25
	sw  t9, LOWER(QCA_PLL_CPU_PLL_DITHER2_REG)(t0)

/* Enable CPU PLL (only if we need it) and wait for update complete */
cpu_pll_enable:
	lw   t9, LOWER(QCA_PLL_CPU_PLL_CFG_REG)(t0)
	and  t9, t9, ~QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK
	sw   t9, LOWER(QCA_PLL_CPU_PLL_CFG_REG)(t0)
	nop

/* Wait for CPU PLL update complete */
cpu_pll_wait:
	lw   t9, LOWER(QCA_PLL_CPU_PLL_CFG_REG)(t0)
	and  t9, t9, QCA_PLL_CPU_PLL_CFG_UPDATING_MASK
	bgtz t9, cpu_pll_wait
	nop

/* Enable DDR PLL (only if we need it) and wait for update complete */
ddr_pll_enable:
	lw   t9, LOWER(QCA_PLL_DDR_PLL_CFG_REG)(t0)
	and  t9, t9, ~QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK
	sw   t9, LOWER(QCA_PLL_DDR_PLL_CFG_REG)(t0)
	nop

/* Wait for DDR PLL update complete */
ddr_pll_wait:
	lw   t9, LOWER(QCA_PLL_DDR_PLL_CFG_REG)(t0)
	and  t9, t9, QCA_PLL_DDR_PLL_CFG_UPDATING_MASK
	bgtz t9, ddr_pll_wait
	nop

/* Disable bypassing all clocks */
pll_bypass_disable:
	lw  t9, LOWER(QCA_PLL_CPU_DDR_CLK_CTRL_REG)(t0)
	and t9, t9, ~(QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK |\
				  QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)
	sw  t9, LOWER(QCA_PLL_CPU_DDR_CLK_CTRL_REG)(t0)

spi_setup:
    li   t8, KSEG1ADDR(QCA_SPI_CTRL_REG)
    lw   t9, 0(t8)
    not  t9, t9
    and  t9, t9, QCA_SPI_CTRL_REMAP_DIS_MASK /* REMAP_DISABLE was not set */
    and  t9, t2, t9 /* REMAP_DISABLE is asked and was not set */
    li   t7, 0x00C00000 /* offset */
    beqz t9, end
    sw   t2, 0(t8) /* store in delay slot */

/*
 * This is a small hack, needed after setting REMAP_DISABLE bit
 * in SPI_CONTROL_ADDR register if was not already set.
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

    subu ra, ra, t7

end:
    jr ra
    nop
