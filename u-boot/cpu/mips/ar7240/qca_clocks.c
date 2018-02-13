/*
 * Qualcomm/Atheros WiSoCs system clocks related functions
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * Partially based on:
 * Linux/arch/mips/ath79/clock.c
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/*
 * Calculates and returns PLL value
 * TODO: check for overflow!
 */
static u32 qca_get_pll(u32 ref_clk,
					   u32 refdiv,
					   u32 nfrac,
					   u32 nfracdiv,
					   u32 nint,
					   u32 outdiv)
{
	u64 pll_mul, pll_div;

	pll_mul = ref_clk;
	pll_div = refdiv;

	if (pll_div == 0)
		pll_div = 1;

	if (nfrac > 0) {
		pll_mul = pll_mul * ((nint * nfracdiv) + nfrac);
		pll_div = pll_div * nfracdiv;
	} else {
		pll_mul = pll_mul * nint;
	}

	pll_div = pll_div << outdiv;

	return (u32)(pll_mul / pll_div);
}


#if 0
/*
 * Display QCA956x clocks from init-956x.c
 *
 */
void qca956x_sys_clocks(void)
{
	u32 rdata, i;
	u32 cpu_pll_low_int, cpu_pll_low_frac, cpu_pll_high_int, cpu_pll_high_frac;
	u32 ddr_pll_low_int, ddr_pll_low_frac, ddr_pll_high_int, ddr_pll_high_frac;
	u32 cpu_clk_low, cpu_clk_high;
	u32 ddr_clk_low, ddr_clk_high;
	u32 ahb_clk_low, ahb_clk_high;
	/* CPU_DDR_CLOCK_CONTROL */
	u32 ahbclk_from_ddrpll, ahb_post_div, ddr_post_div, cpu_post_div;
	u32 cpu_ddr_clk_from_cpupll, cpu_ddr_clk_from_ddrpll;
	u32 ahb_pll_bypass, ddr_pll_bypass, cpu_pll_bypass;
	/* CPU_PLL_CONFIG, CPU_PLL_CONFIG1, CPU_PLL_DITHER1, CPU_PLL_DITHER2 */
	u32 cpu_pllpwd, cpu_outdiv, cpu_Refdiv, cpu_Nint;
	u32 cpu_dither_en, cpu_NFrac_Min, cpu_NFrac_Max;
	u32 cpu_NFrac_Min_17_5, cpu_NFrac_Min_4_0;
	u32 cpu_NFrac_Max_17_5, cpu_NFrac_Max_4_0;
	/* DDR_PLL_CONFIG, DDR_PLL_CONFIG1, DDR_PLL_DITHER1, DDR_PLL_DITHER2 */
	u32 ddr_pllpwd, ddr_outdiv, ddr_Refdiv, ddr_Nint;
	u32 ddr_dither_en, ddr_NFrac_Min, ddr_NFrac_Max;
	u32 ddr_NFrac_Min_17_5, ddr_NFrac_Min_4_0;
	u32 ddr_NFrac_Max_17_5, ddr_NFrac_Max_4_0;
	static u32 ath_cpu_freq, ath_ddr_freq, ath_ahb_freq;

	uint32_t ref_clk;


	if (qca_xtal_is_40mhz() == 1) {
		ref_clk = VAL_40MHz;
	} else {
		ref_clk = VAL_25MHz;
	}

	rdata = ath_reg_rd(CPU_DDR_CLOCK_CONTROL_ADDRESS);
	ahbclk_from_ddrpll	= CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_GET(rdata);
	ahb_post_div		= CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_GET(rdata);
	ddr_post_div		= CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_GET(rdata);
	cpu_post_div		= CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_GET(rdata);
	cpu_ddr_clk_from_cpupll = CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_GET(rdata);
	cpu_ddr_clk_from_ddrpll = CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_GET(rdata);
	ahb_pll_bypass		= CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_GET(rdata);
	ddr_pll_bypass		= CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_GET(rdata);
	cpu_pll_bypass		= CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_GET(rdata);

	if (ahb_pll_bypass) {
		ath_ahb_freq = ref_clk / (ahb_post_div + 1);
		//*ahb_clk_h = ref_clk / (ahb_post_div + 1);
	}

	if (ddr_pll_bypass) {
		ath_ddr_freq = ref_clk;
		//*ddr_clk_h = ref_clk;
	}

	if (cpu_pll_bypass) {
		ath_cpu_freq = ref_clk;
		//*cpu_clk_h = ref_clk;
	}

	if (ahb_pll_bypass && ddr_pll_bypass && cpu_pll_bypass) {
		return;
	}

	rdata = ath_reg_rd(CPU_PLL_CONFIG_ADDRESS);
	cpu_pllpwd	= CPU_PLL_CONFIG_PLLPWD_GET(rdata);
	cpu_outdiv	= CPU_PLL_CONFIG_OUTDIV_GET(rdata);
	cpu_Refdiv	= CPU_PLL_CONFIG_REFDIV_GET(rdata);

	rdata = ath_reg_rd(CPU_PLL_CONFIG1_ADDRESS);
	cpu_Nint	= CPU_PLL_CONFIG1_NINT_GET(rdata);

	rdata = ath_reg_rd(CPU_PLL_DITHER1_ADDRESS);
	cpu_dither_en	= CPU_PLL_DITHER1_DITHER_EN_GET(rdata);
	cpu_NFrac_Min	= CPU_PLL_DITHER1_NFRAC_MIN_GET(rdata);
	cpu_NFrac_Min_17_5 = (cpu_NFrac_Min >> 5) & 0x1fff;
	cpu_NFrac_Min_4_0  = cpu_NFrac_Min & 0x1f;

	rdata = ath_reg_rd(CPU_PLL_DITHER1_ADDRESS);
	cpu_NFrac_Max	= CPU_PLL_DITHER2_NFRAC_MAX_GET(rdata);
	cpu_NFrac_Max_17_5 = (cpu_NFrac_Max >> 5) & 0x1fff;
	cpu_NFrac_Max_4_0  = cpu_NFrac_Max & 0x1f;

	rdata = ath_reg_rd(DDR_PLL_CONFIG_ADDRESS);
	ddr_pllpwd	= DDR_PLL_CONFIG_PLLPWD_GET(rdata);
	ddr_outdiv	= DDR_PLL_CONFIG_OUTDIV_GET(rdata);
	ddr_Refdiv	= DDR_PLL_CONFIG_REFDIV_GET(rdata);

	rdata = ath_reg_rd(DDR_PLL_CONFIG1_ADDRESS);
	ddr_Nint	= DDR_PLL_CONFIG1_NINT_GET(rdata);

	rdata = ath_reg_rd(DDR_PLL_DITHER1_ADDRESS);
	ddr_dither_en	= DDR_PLL_DITHER1_DITHER_EN_GET(rdata);
	ddr_NFrac_Min	= DDR_PLL_DITHER1_NFRAC_MIN_GET(rdata);
	ddr_NFrac_Min_17_5 = (ddr_NFrac_Min >> 5) & 0x1fff;
	ddr_NFrac_Min_4_0  = ddr_NFrac_Min & 0x1f;

	rdata = ath_reg_rd(DDR_PLL_DITHER1_ADDRESS);
	ddr_NFrac_Max	= DDR_PLL_DITHER2_NFRAC_MAX_GET(rdata);
	ddr_NFrac_Max_17_5 = (ddr_NFrac_Max >> 5) & 0x1fff;
	ddr_NFrac_Max_4_0  = ddr_NFrac_Max & 0x1f;

	/* CPU PLL */
	i = (ref_clk/cpu_Refdiv);

	cpu_pll_low_int  = i*cpu_Nint;
	cpu_pll_high_int = cpu_pll_low_int;

	cpu_pll_low_frac = (i/(25*32))*((cpu_NFrac_Min_17_5*25 + cpu_NFrac_Min_4_0)/(8192/32));
	cpu_pll_high_frac = (i/(25*32))*((cpu_NFrac_Max_17_5*25 + cpu_NFrac_Max_4_0)/(8192/32));

	if (!cpu_dither_en || cpu_pll_high_frac <= cpu_pll_low_frac) {
		cpu_pll_high_frac = cpu_pll_low_frac;
	}

	 /* DDR PLL */
	i = (ref_clk/ddr_Refdiv);

	ddr_pll_low_int  = i*ddr_Nint;
	ddr_pll_high_int = ddr_pll_low_int;

	ddr_pll_low_frac = (i/(25*32))*((ddr_NFrac_Min_17_5*25 + ddr_NFrac_Min_4_0)/(8192/32));
	ddr_pll_high_frac = (i/(25*32))*((ddr_NFrac_Max_17_5*25 + ddr_NFrac_Max_4_0)/(8192/32));

	if (!ddr_dither_en || ddr_pll_high_frac <= ddr_pll_low_frac) {
		ddr_pll_high_frac = ddr_pll_low_frac;
	}

	/* CPU Clock, DDR Clock, AHB Clock (before post div) */
	if (cpu_ddr_clk_from_cpupll) {
		cpu_clk_low  = cpu_pll_low_int + cpu_pll_low_frac;
		cpu_clk_high = cpu_pll_high_int + cpu_pll_high_frac;

		if (cpu_outdiv != 0) {
			cpu_clk_low  /= (2*cpu_outdiv);
			cpu_clk_high /= (2*cpu_outdiv);
		}

		ddr_clk_low  = cpu_clk_low;
		ddr_clk_high = cpu_clk_high;
	} else if (cpu_ddr_clk_from_ddrpll) {
		ddr_clk_low  = ddr_pll_low_int + ddr_pll_low_frac;
		ddr_clk_high = ddr_pll_high_int + ddr_pll_high_frac;

		if (ddr_outdiv != 0) {
			ddr_clk_low  /= (2*ddr_outdiv);
			ddr_clk_high /= (2*ddr_outdiv);
		}

		cpu_clk_low  = ddr_clk_low;
		cpu_clk_high = ddr_clk_high;
	} else {
		cpu_clk_low  = cpu_pll_low_int + cpu_pll_low_frac;
		cpu_clk_high = cpu_pll_high_int + cpu_pll_high_frac;
		ddr_clk_low  = ddr_pll_low_int + ddr_pll_low_frac;
		ddr_clk_high = ddr_pll_high_int + ddr_pll_high_frac;

		if (cpu_outdiv != 0) {
			cpu_clk_low  /= (2*cpu_outdiv);
			cpu_clk_high /= (2*cpu_outdiv);
		}

		if (ddr_outdiv != 0) {
			ddr_clk_low  /= (2*ddr_outdiv);
			ddr_clk_high /= (2*ddr_outdiv);
		}
	}

	if (ahbclk_from_ddrpll) {
		ahb_clk_low  = ddr_clk_low;
		ahb_clk_high = ddr_clk_high;
	} else {
		ahb_clk_low  = cpu_clk_low;
		ahb_clk_high = cpu_clk_high;
	}

	/* CPU Clock, DDR Clock, AHB Clock */
	cpu_clk_low  /= (cpu_post_div + 1);
	cpu_clk_high /= (cpu_post_div + 1);
	ddr_clk_low  /= (ddr_post_div + 1);
	ddr_clk_high /= (ddr_post_div + 1);
	ahb_clk_low  /= (ahb_post_div + 1);
	ahb_clk_high /= (ahb_post_div + 1);

	printf("%s: cpu %u-%u ddr %u-%u ahb %u-%u\n", __func__,
		cpu_clk_high / 1000000,
		cpu_clk_low / 1000000,
		ddr_clk_high / 1000000,
		ddr_clk_low / 1000000,
		ahb_clk_high / 1000000,
		ahb_clk_low / 1000000);
}
#endif

/*
 * Get CPU, RAM, AHB and SPI clocks
 * TODO: confirm nfracdiv values
 */
void qca_sys_clocks(u32 *cpu_clk,
					u32 *ddr_clk,
					u32 *ahb_clk,
					u32 *spi_clk,
					u32 *ref_clk)
{
	u32 qca_ahb_clk, qca_cpu_clk, qca_ddr_clk, qca_ref_clk, qca_spi_clk;
	u32 nint, outdiv, refdiv;
	u32 nfrac, nfracdiv;
	u32 reg_val, temp;

#if (SOC_TYPE & QCA_AR933X_SOC)
	u32 cpu_pll;
#else
	u32 cpu_pll, ddr_pll;
#endif

	if (qca_xtal_is_40mhz() == 1) {
		qca_ref_clk = VAL_40MHz;
	} else {
		qca_ref_clk = VAL_25MHz;
	}

#if (SOC_TYPE & QCA_AR933X_SOC)
	/*
	 * Main AR933x CPU PLL clock calculation:
	 *
	 * 1. If CPU PLL DITHER is disabled:
	 *    VCO_OUT = (REF_CLK / REF_DIV) * (NINT + (NFRAC_MIN / 1024))
	 *    CPU_PLL_OUT = VCO_OUT / (2^OUT_DIV)
	 *
	 * 2. If CPU PLL DITHER is enabled:
	 *    VCO_OUT = (REF_CLK / REF_DIV) * (NINT + (NFRAC / 1024))
	 *    CPU_PLL_OUT = VCO_OUT / (2^OUT_DIV)
	 *
	 *    TODO: NFRAC does not exist in AR9331 datasheet,
	 *          but exist in many other QC/A WiSOC datasheets,
	 *          we should somehow (scope?) check and confirm it
	 */

	/* Read CPU CLock Control Register (CLOCK_CONTROL) value */
	reg_val = qca_soc_reg_read(QCA_PLL_CPU_CLK_CTRL_REG);

	if (reg_val & QCA_PLL_CPU_CLK_CTRL_BYPASS_MASK) {
		/* PLL is bypassed, so all clocks are == reference clock */
		qca_cpu_clk = qca_ref_clk;
		qca_ddr_clk = qca_ref_clk;
		qca_ahb_clk = qca_ref_clk;
	} else {
		reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_REG);

		if (reg_val & QCA_PLL_CPU_PLL_DITHER_DITHER_EN_MASK) {
			reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG_REG);
			nfrac = (reg_val & QCA_PLL_CPU_PLL_CFG_NFRAC_MASK)
					>> QCA_PLL_CPU_PLL_CFG_NFRAC_SHIFT;
		} else {
			/* NFRAC = NFRAC_MIN if DITHER_EN is 0 */
			reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_FRAC_REG);
			nfrac = (reg_val & QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK)
					>> QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_SHIFT;
		}

		nfracdiv = 1 << 10;

		reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG_REG);

		nint = (reg_val & QCA_PLL_CPU_PLL_CFG_NINT_MASK)
			   >> QCA_PLL_CPU_PLL_CFG_NINT_SHIFT;

		refdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK)
				 >> QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT;

		outdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK)
				 >> QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT;

		/* TODO: need confirmation that OUTDIV == 0 is not supported for AR933x */
		if (outdiv == 0)
			outdiv = 1;

		/* Final CPU PLL value */
		cpu_pll = qca_get_pll(qca_ref_clk, refdiv,
							  nfrac, nfracdiv, nint, outdiv);

		/* CPU, DDR and AHB clock dividers */
		reg_val = qca_soc_reg_read(QCA_PLL_CPU_CLK_CTRL_REG);

		temp = ((reg_val & QCA_PLL_CPU_CLK_CTRL_CPU_POST_DIV_MASK)
				>> QCA_PLL_CPU_CLK_CTRL_CPU_POST_DIV_SHIFT) + 1;
		qca_cpu_clk = cpu_pll / temp;

		temp = ((reg_val & QCA_PLL_CPU_CLK_CTRL_DDR_POST_DIV_MASK)
				>> QCA_PLL_CPU_CLK_CTRL_DDR_POST_DIV_SHIFT) + 1;
		qca_ddr_clk = cpu_pll / temp;

		temp = ((reg_val & QCA_PLL_CPU_CLK_CTRL_AHB_POST_DIV_MASK)
				>> QCA_PLL_CPU_CLK_CTRL_AHB_POST_DIV_SHIFT) + 1;
		qca_ahb_clk = cpu_pll / temp;
	}
#else
#	if (SOC_TYPE & QCA_QCA956X_SOC)
	/* QCA956x uses CFG1 for CPU and DDR */

	u32 nfrac_l, nfrac_h;

	reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG1_REG);
	nint = (reg_val & QCA_PLL_CPU_PLL_CFG1_NINT_MASK)
				   >> QCA_PLL_CPU_PLL_CFG1_NINT_SHIFT;

	reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_REG);
	if (reg_val & QCA_PLL_CPU_PLL_DITHER_DITHER_EN_MASK) {
		reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG1_REG);
		nfrac_l = (reg_val & QCA_PLL_CPU_PLL_CFG1_NFRAC_L_MASK)
							>> QCA_PLL_CPU_PLL_CFG1_NFRAC_L_SHIFT;
		nfrac_h = (reg_val & QCA_PLL_CPU_PLL_CFG1_NFRAC_H_MASK)
					>> QCA_PLL_CPU_PLL_CFG1_NFRAC_H_SHIFT;
		nfrac = (nfrac_h * (QCA_PLL_CPU_PLL_CFG1_NFRAC_L_MASK + 1)) | nfrac_l;
	} else {
		/* NFRAC = NFRAC_MIN if DITHER_EN is 0 */
		nfrac_l = (reg_val & QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_L_MASK)
							>> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_L_SHIFT;
		nfrac_h = (reg_val & QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_H_MASK)
					>> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_H_SHIFT;
		nfrac = (nfrac_h * (QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_L_MASK + 1)) | nfrac_l;
	}
	nfracdiv = 1 << 18;

	reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG_REG);
		refdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK)
					 >> QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT;

	outdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK)
					 >> QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT;

	/* Final CPU PLL value */
	cpu_pll = qca_get_pll(qca_ref_clk, refdiv, nfrac, nfracdiv, nint, outdiv);

	reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_CFG1_REG);
	nint = (reg_val & QCA_PLL_DDR_PLL_CFG1_NINT_MASK)
				   >> QCA_PLL_DDR_PLL_CFG1_NINT_SHIFT;

	reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_DITHER_REG);
	if (reg_val & QCA_PLL_DDR_PLL_DITHER_DITHER_EN_MASK) {
		reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_CFG1_REG);
		nfrac_l = (reg_val & QCA_PLL_DDR_PLL_CFG1_NFRAC_L_MASK)
							>> QCA_PLL_DDR_PLL_CFG1_NFRAC_L_SHIFT;
		nfrac_h = (reg_val & QCA_PLL_DDR_PLL_CFG1_NFRAC_H_MASK)
					>> QCA_PLL_DDR_PLL_CFG1_NFRAC_H_SHIFT;
		nfrac = (nfrac_h * (QCA_PLL_DDR_PLL_CFG1_NFRAC_L_MASK + 1)) | nfrac_l;
	} else {
		/* NFRAC = NFRAC_MIN if DITHER_EN is 0 */
		nfrac_l = (reg_val & QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_L_MASK)
							>> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_L_SHIFT;
		nfrac_h = (reg_val & QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_H_MASK)
					>> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_H_SHIFT;
		nfrac = (nfrac_h * (QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_L_MASK + 1)) | nfrac_l;
	}
	nfracdiv = 1 << 18;

	reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_CFG_REG);
		refdiv = (reg_val & QCA_PLL_DDR_PLL_CFG_REFDIV_MASK)
					 >> QCA_PLL_DDR_PLL_CFG_REFDIV_SHIFT;

	outdiv = (reg_val & QCA_PLL_DDR_PLL_CFG_OUTDIV_MASK)
					 >> QCA_PLL_DDR_PLL_CFG_OUTDIV_SHIFT;

	/* Final CPU PLL value */
	ddr_pll = qca_get_pll(qca_ref_clk, refdiv, nfrac, nfracdiv, nint, outdiv);
#	endif
#	if (SOC_TYPE & QCA_QCA955X_SOC) | \
	   (SOC_TYPE & QCA_QCA956X_SOC)

	/* QCA955x and QCA956x inverts QCA_PLL_CPU_DDR_CLK_CTRL_xxx logic */
	/* CPU clock divider */
	reg_val = qca_soc_reg_read(QCA_PLL_CPU_DDR_CLK_CTRL_REG);

	temp = ((reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_MASK)
			>> QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_SHIFT) + 1;

	if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK) {
		qca_cpu_clk = qca_ref_clk;
	} else if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_DDRPLL_MASK) {
		qca_cpu_clk = ddr_pll / temp;
	} else {
		qca_cpu_clk = cpu_pll / temp;
	}

	/* DDR clock divider */
	temp = ((reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_MASK)
			>> QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_SHIFT) + 1;

	if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK) {
		qca_ddr_clk = qca_ref_clk;
	} else if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_CPUPLL_MASK) {
		qca_ddr_clk = cpu_pll / temp;
	} else {
		qca_ddr_clk = ddr_pll / temp;
	}
#	else
	/*
	 * Main AR934x/QCA95xx CPU/DDR PLL clock calculation
	 */

	/* CPU PLL */
	reg_val = qca_soc_reg_read(QCA_PLL_SRIF_CPU_DPLL2_REG);

	/* CPU PLL settings from SRIF CPU DPLL2? */
	if (reg_val & QCA_PLL_SRIF_DPLL2_LOCAL_PLL_MASK) {
		outdiv = (reg_val & QCA_PLL_SRIF_DPLL2_OUTDIV_MASK)
				 >> QCA_PLL_SRIF_DPLL2_OUTDIV_SHIFT;

		reg_val = qca_soc_reg_read(QCA_PLL_SRIF_CPU_DPLL1_REG);

		nfrac = (reg_val & QCA_PLL_SRIF_DPLL1_NFRAC_MASK)
				>> QCA_PLL_SRIF_DPLL1_NFRAC_SHIFT;

		nfracdiv = 1 << 18;

		nint = (reg_val & QCA_PLL_SRIF_DPLL1_NINT_MASK)
			   >> QCA_PLL_SRIF_DPLL1_NINT_SHIFT;

		refdiv = (reg_val & QCA_PLL_SRIF_DPLL1_REFDIV_MASK)
				 >> QCA_PLL_SRIF_DPLL1_REFDIV_SHIFT;
	} else {
		reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_REG);

		if (reg_val & QCA_PLL_CPU_PLL_DITHER_DITHER_EN_MASK) {
			reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG_REG);
			nfrac = (reg_val & QCA_PLL_CPU_PLL_CFG_NFRAC_MASK)
					>> QCA_PLL_CPU_PLL_CFG_NFRAC_SHIFT;
		} else {
			/* NFRAC = NFRAC_MIN if DITHER_EN is 0 */
			nfrac = (reg_val & QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK)
					>> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_SHIFT;
		}

		nfracdiv = 1 << 6;

		reg_val = qca_soc_reg_read(QCA_PLL_CPU_PLL_CFG_REG);

		nint = (reg_val & QCA_PLL_CPU_PLL_CFG_NINT_MASK)
			   >> QCA_PLL_CPU_PLL_CFG_NINT_SHIFT;

		refdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK)
				 >> QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT;

		outdiv = (reg_val & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK)
				 >> QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT;
	}

	/* Final CPU PLL value */
	cpu_pll = qca_get_pll(qca_ref_clk, refdiv,
						  nfrac, nfracdiv, nint, outdiv);

	/* DDR PLL */
	reg_val = qca_soc_reg_read(QCA_PLL_SRIF_DDR_DPLL2_REG);

	/* DDR PLL settings from SRIF DDR DPLL2? */
	if (reg_val & QCA_PLL_SRIF_DPLL2_LOCAL_PLL_MASK) {
		outdiv = (reg_val & QCA_PLL_SRIF_DPLL2_OUTDIV_MASK)
				 >> QCA_PLL_SRIF_DPLL2_OUTDIV_SHIFT;

		reg_val = qca_soc_reg_read(QCA_PLL_SRIF_DDR_DPLL1_REG);

		nfrac = (reg_val & QCA_PLL_SRIF_DPLL1_NFRAC_MASK)
				>> QCA_PLL_SRIF_DPLL1_NFRAC_SHIFT;

		nfracdiv = 1 << 18;

		nint = (reg_val & QCA_PLL_SRIF_DPLL1_NINT_MASK)
			   >> QCA_PLL_SRIF_DPLL1_NINT_SHIFT;

		refdiv = (reg_val & QCA_PLL_SRIF_DPLL1_REFDIV_MASK)
				 >> QCA_PLL_SRIF_DPLL1_REFDIV_SHIFT;
	} else {
		reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_DITHER_REG);

		if (reg_val & QCA_PLL_DDR_PLL_DITHER_DITHER_EN_MASK) {
			reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_CFG_REG);
			nfrac = (reg_val & QCA_PLL_DDR_PLL_CFG_NFRAC_MASK)
					>> QCA_PLL_DDR_PLL_CFG_NFRAC_SHIFT;
		} else {
			/* NFRAC = NFRAC_MIN if DITHER_EN is 0 */
			nfrac = (reg_val & QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK)
					>> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_SHIFT;
		}

		nfracdiv = 1 << 10;

		reg_val = qca_soc_reg_read(QCA_PLL_DDR_PLL_CFG_REG);

		nint = (reg_val & QCA_PLL_DDR_PLL_CFG_NINT_MASK)
			   >> QCA_PLL_DDR_PLL_CFG_NINT_SHIFT;

		refdiv = (reg_val & QCA_PLL_DDR_PLL_CFG_REFDIV_MASK)
				 >> QCA_PLL_DDR_PLL_CFG_REFDIV_SHIFT;

		outdiv = (reg_val & QCA_PLL_DDR_PLL_CFG_OUTDIV_MASK)
				 >> QCA_PLL_DDR_PLL_CFG_OUTDIV_SHIFT;
	}

	/* Final DDR PLL value */
	ddr_pll = qca_get_pll(qca_ref_clk, refdiv,
						  nfrac, nfracdiv, nint, outdiv);

	/* CPU clock divider */
	reg_val = qca_soc_reg_read(QCA_PLL_CPU_DDR_CLK_CTRL_REG);

	temp = ((reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_MASK)
			>> QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_SHIFT) + 1;

	if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPU_PLL_BYPASS_MASK) {
		qca_cpu_clk = qca_ref_clk;
	} else if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_CPUPLL_MASK) {
		qca_cpu_clk = cpu_pll / temp;
	} else {
		qca_cpu_clk = ddr_pll / temp;
	}

	/* DDR clock divider */
	temp = ((reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_MASK)
			>> QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_SHIFT) + 1;

	if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDR_PLL_BYPASS_MASK) {
		qca_ddr_clk = qca_ref_clk;
	} else if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_DDRPLL_MASK) {
		qca_ddr_clk = ddr_pll / temp;
	} else {
		qca_ddr_clk = cpu_pll / temp;
	}

#endif
	/* AHB clock divider */
	temp = ((reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_MASK)
			>> QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_SHIFT) + 1;

	if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_AHB_PLL_BYPASS_MASK) {
		qca_ahb_clk = qca_ref_clk;
	} else if (reg_val & QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_MASK) {
		qca_ahb_clk = ddr_pll / temp;
	} else {
		qca_ahb_clk = cpu_pll / temp;
	}
#endif
	/* Calculate SPI FLASH clock if needed */
	if (spi_clk != NULL) {
		/* First disable SPI */
		qca_soc_reg_read_set(QCA_SPI_FUNC_SEL_REG,
							 QCA_SPI_FUNC_SEL_FUNC_SEL_MASK);

		/* SPI clock = AHB clock / ((SPI clock divider + 1) * 2) */
		reg_val = (qca_soc_reg_read(QCA_SPI_CTRL_REG) & QCA_SPI_CTRL_CLK_DIV_MASK)
				  >> QCA_SPI_CTRL_CLK_DIV_SHIFT;

		qca_spi_clk = qca_ahb_clk / ((reg_val + 1) * 2);

		/* Re-enable SPI */
		qca_soc_reg_read_clear(QCA_SPI_FUNC_SEL_REG,
							   QCA_SPI_FUNC_SEL_FUNC_SEL_MASK);
	}

	/* Return values */
	if (cpu_clk != NULL)
		*cpu_clk = qca_cpu_clk;

	if (ddr_clk != NULL)
		*ddr_clk = qca_ddr_clk;

	if (ahb_clk != NULL)
		*ahb_clk = qca_ahb_clk;

	if (spi_clk != NULL)
		*spi_clk = qca_spi_clk;

	if (ref_clk != NULL)
		*ref_clk = qca_ref_clk;
}
