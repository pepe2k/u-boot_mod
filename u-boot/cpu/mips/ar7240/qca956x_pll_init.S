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
#include <atheros.h>

/*
 * Helper macros.
 * These Clobber t7, t8 and t9
 */
#define reg_write(_reg, _val)			\
	li	t7,	KSEG1ADDR(_reg);	\
	li	t8,	_val;			\
	sw	t8,	0(t7);

#define reg_rmw_set(_reg, _mask, _val)		\
	li	t7,	KSEG1ADDR(_reg);	\
	lw	t8,	0(t7);			\
	li	t9,	~(_mask);		\
	and	t8,	t8,	t9;		\
	li	t9,	_val;			\
	or	t8,	t8,	t9;		\
	sw	t8,	0(t7)

#define cpu_pll_set(_mask, _val)	\
	reg_rmw_set(QCA_PLL_CPU_PLL_CFG_REG, _mask, _val)

#define ddr_pll_set(_mask, _val)	\
	reg_rmw_set(QCA_PLL_DDR_PLL_CFG_REG, _mask, _val)

#define cpu_ddr_control_set(_mask, _val)	\
	reg_rmw_set(QCA_PLL_CPU_DDR_CLK_CTRL_REG, _mask, _val)


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

	reg_write(BB_DPLL2_ADDRESS, BB_DPLL2_KI_SET(2) | \
				BB_DPLL2_KD_SET(0xa) | \
				BB_DPLL2_OUTDIV_SET(1) | \
				BB_DPLL2_PLL_PWD_SET(1) | \
				BB_DPLL2_PHASE_SHIFT_SET(0x6));
	reg_write(PCIe_DPLL2_ADDRESS, PCIe_DPLL2_KI_SET(2) | \
                PCIe_DPLL2_KD_SET(0xa) | \
				PCIe_DPLL2_PLL_PWD_SET(1) | \
				PCIe_DPLL2_OUTDIV_SET(0x3) | \
				PCIe_DPLL2_PHASE_SHIFT_SET(0x6));
	reg_write(DDR_DPLL2_ADDRESS, DDR_DPLL2_KI_SET(2) | \
				DDR_DPLL2_KD_SET(0xa) | \
				DDR_DPLL2_PLL_PWD_SET(1) | \
				DDR_DPLL2_PHASE_SHIFT_SET(0x6));
	reg_write(CPU_DPLL2_ADDRESS, CPU_DPLL2_KI_SET(1) | \
				CPU_DPLL2_KD_SET(0x7)  | \
				CPU_DPLL2_PLL_PWD_SET(1) | \
				CPU_DPLL2_PHASE_SHIFT_SET(0x6));

	li	t5,	QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25
	li	t6,	QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25
	li	t4,	QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25
	li	t3,	QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25

	li	t7,	PLL_CONFIG_VAL_F
	lw	t8,	0(t7)
	li	t7,	PLL_MAGIC
	beq	t7,	t8,	read_from_flash
	nop
	j	pll_bypass_set
	nop
read_from_flash:
	li	t7,	PLL_CONFIG_VAL_F + 4
	lw	t5,	0(t7)
	lw	t4,	4(t7)
	lw	t6,	8(t7)
	lw	t3,	12(t7)


pll_bypass_set:
	cpu_ddr_control_set (CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_SET(1));
	cpu_ddr_control_set (CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_SET(1));
	cpu_ddr_control_set (CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_SET(1));

init_cpu_pll:
	li	t7,	KSEG1ADDR(QCA_PLL_CPU_PLL_CFG_REG);
	li	t8,	QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25;
	sw	t8,	0(t7);
	li	t7,	KSEG1ADDR(QCA_PLL_CPU_PLL_CFG1_REG);
	sw  t5, 0(t7);

init_ddr_pll:
	li	t7,	KSEG1ADDR(QCA_PLL_DDR_PLL_CFG_REG)
	li	t8,	QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25;
	sw	t8,	0(t7);
	li	t7,	KSEG1ADDR(QCA_PLL_DDR_PLL_CFG1_REG)
	sw  t6, 0(t7);

init_ahb_pll:
	reg_write(QCA_PLL_CPU_DDR_CLK_CTRL_REG,
			QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25 |
			QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK |
                        QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK |
                        QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK)

ddr_pll_dither_unset:
	li	t7,	KSEG1ADDR(QCA_PLL_DDR_PLL_DITHER_REG);
	sw	t3,	0(t7);
	li	t7,	KSEG1ADDR(QCA_PLL_DDR_PLL_DITHER2_REG);
	li	t8,	QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25
	sw	t8,	0(t7);

cpu_pll_dither_unset:
	li	t7,	KSEG1ADDR(QCA_PLL_CPU_PLL_DITHER_REG);
	sw	t4,	0(t7);
	li	t7,	KSEG1ADDR(QCA_PLL_CPU_PLL_DITHER2_REG);
	li	t8,	QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25
	sw	t8,	0(t7);

pll_pwd_unset:
	cpu_pll_set(CPU_PLL_CONFIG_PLLPWD_MASK, CPU_PLL_CONFIG_PLLPWD_SET(0));
	ddr_pll_set(DDR_PLL_CONFIG_PLLPWD_MASK, DDR_PLL_CONFIG_PLLPWD_SET(0));

outdiv_unset:
	cpu_pll_set(CPU_PLL_CONFIG_OUTDIV_MASK, QCA_PLL_CPU_CFG_OUT_DIV_VAL2_XTAL25);
	ddr_pll_set(DDR_PLL_CONFIG_OUTDIV_MASK, QCA_PLL_DDR_CFG_OUT_DIV_VAL2_XTAL25);

pll_bypass_unset:
	cpu_ddr_control_set(CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_SET(0));
	cpu_ddr_control_set(CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_SET(0));
	cpu_ddr_control_set(CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK, CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_SET(0));

cpu_pll_wait:
    li   t8, KSEG1ADDR(QCA_PLL_CPU_PLL_CFG_REG)
    lw   t9, 0(t8)
    and  t9, t9, QCA_PLL_CPU_PLL_CFG_UPDATING_MASK
    bgtz t9, cpu_pll_wait
    nop


ddr_pll_wait:
    li  t8, KSEG1ADDR(QCA_PLL_DDR_PLL_CFG_REG);
    lw  t9, 0(t8);
    and  t9, t9, QCA_PLL_DDR_PLL_CFG_UPDATING_MASK
    bgtz t9, ddr_pll_wait
    nop

spi_setup:
    li   t1, QCA_SPI_CTRL_REG_VAL
    li   t8, KSEG1ADDR(QCA_SPI_CTRL_REG)

    lw   t9, 0(t8)
    nor  t9, t9, t9
    and  t9, t9, QCA_SPI_CTRL_REMAP_DIS_MASK /* REMAP was not set */
    and  t9, t1, t9
    li   t7, 0x00C00000
    beqz t9, end
    sw   t1, 0(t8) /* store in delay slot */


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
