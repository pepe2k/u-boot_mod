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
