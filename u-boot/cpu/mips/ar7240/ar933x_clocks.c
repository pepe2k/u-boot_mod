/*
 * Atheros AR933x clocks helper functions
 *
 * Copyright (C) 2014 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2014 Mantas Pucka <mantas@8devices.com>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <asm/ar933x.h>

inline int ar933x_40MHz_xtal(void)
{
	return (ar933x_reg_read(BOOTSTRAP_STATUS_REG) & BOOTSTRAP_SEL_25_40M_MASK);
}

/*
 * Get CPU, RAM and AHB clocks
 * Based on: Linux/arch/mips/ath79/clock.c
 */
/* TODO: void ar933x_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq) */
void ar7240_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq)
{
	u32 ref_rate, clock_ctrl, cpu_config, pll, temp;

	if(ar933x_40MHz_xtal() == 1){
		ref_rate = 40000000;
	} else {
		ref_rate = 25000000;
	}

	/*
	 * Read CPU CLock Control Register (CLOCK_CONTROL) value
	 */
	clock_ctrl = ar933x_reg_read(CPU_CLOCK_CONTROL_REG);

	if(clock_ctrl & CPU_CLOCK_CONTROL_BYPASS_MASK){
		/* PLL is bypassed, so all clocks are == reference clock */
		*cpu_freq = ref_rate;
		*ddr_freq = ref_rate;
		*ahb_freq = ref_rate;
	} else {
		/* read CPU PLL Configuration register (CPU_PLL_CONFIG) value */
		cpu_config = ar933x_reg_read(CPU_PLL_CONFIG_REG);

		/* REFDIV */
		temp = (cpu_config & CPU_PLL_CONFIG_REFDIV_MASK)
				>> CPU_PLL_CONFIG_REFDIV_SHIFT;
		pll = ref_rate / temp;

		/* DIV_INT (multiplier) */
		temp = (cpu_config & CPU_PLL_CONFIG_DIV_INT_MASK)
				>> CPU_PLL_CONFIG_DIV_INT_SHIFT;
		pll *= temp;

		/* OUTDIV */
		temp = (cpu_config & CPU_PLL_CONFIG_OUTDIV_MASK)
				>> CPU_PLL_CONFIG_OUTDIV_SHIFT;

		/* Value 0 is not allowed */
		if(temp == 0){
			temp = 1;
		}

		pll >>= temp;

		/* CPU clock divider */
		temp = ((clock_ctrl & CPU_CLOCK_CONTROL_CPU_POST_DIV_MASK)
				>> CPU_CLOCK_CONTROL_CPU_POST_DIV_SHIFT) + 1;
		*cpu_freq = pll / temp;

		/* DDR clock divider */
		temp = ((clock_ctrl & CPU_CLOCK_CONTROL_DDR_POST_DIV_MASK)
				>> CPU_CLOCK_CONTROL_DDR_POST_DIV_SHIFT) + 1;
		*ddr_freq = pll / temp;

		/* AHB clock divider */
		temp = ((clock_ctrl & CPU_CLOCK_CONTROL_AHB_POST_DIV_MASK)
				>> CPU_CLOCK_CONTROL_AHB_POST_DIV_SHIFT) + 1;
		*ahb_freq = pll / temp;
	}
}
