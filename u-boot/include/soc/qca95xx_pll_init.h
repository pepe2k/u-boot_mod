/*
 * Helper defines and macros related with
 * PLL and clocks configurations for
 * Qualcomm/Atheros AR934x and QCA95xx WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _QCA95XX_PLL_INIT_H_
#define _QCA95XX_PLL_INIT_H_

#include <soc/qca_soc_common.h>

/* CPU_PLL_CONFIG */
#define _qca95xx_cpu_pll_cfg_reg_val(_nint,   \
				     _refdiv, \
				     _range,  \
				     _outdiv, \
				     _dis)    \
					      \
	((_nint   << QCA_PLL_CPU_PLL_CFG_NINT_SHIFT)   & QCA_PLL_CPU_PLL_CFG_NINT_MASK)   |\
	((_refdiv << QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK) |\
	((_range  << QCA_PLL_CPU_PLL_CFG_RANGE_SHIFT)  & QCA_PLL_CPU_PLL_CFG_RANGE_MASK)  |\
	((_outdiv << QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK) |\
	((_dis    << QCA_PLL_CPU_PLL_CFG_PLLPWD_SHIFT) & QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK)

/* DDR_PLL_CONFIG */
#define _qca95xx_ddr_pll_cfg_reg_val(_nint,   \
				     _refdiv, \
				     _range,  \
				     _outdiv, \
				     _dis)    \
					      \
	((_nint   << QCA_PLL_DDR_PLL_CFG_NINT_SHIFT)   & QCA_PLL_DDR_PLL_CFG_NINT_MASK)   |\
	((_refdiv << QCA_PLL_DDR_PLL_CFG_REFDIV_SHIFT) & QCA_PLL_DDR_PLL_CFG_REFDIV_MASK) |\
	((_range  << QCA_PLL_DDR_PLL_CFG_RANGE_SHIFT)  & QCA_PLL_DDR_PLL_CFG_RANGE_MASK)  |\
	((_outdiv << QCA_PLL_DDR_PLL_CFG_OUTDIV_SHIFT) & QCA_PLL_DDR_PLL_CFG_OUTDIV_MASK) |\
	((_dis    << QCA_PLL_DDR_PLL_CFG_PLLPWD_SHIFT) & QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK)

/* CPU_DDR_CLOCK_CONTROL */
#define _qca95xx_cpu_ddr_clk_ctrl_reg_val(_cpudiv,          \
					  _ddrdiv,          \
					  _ahbdiv,          \
					  _cpu_from_cpupll, \
					  _ddr_from_ddrpll, \
					  _ahb_from_ddrpll) \
							    \
	(((_cpudiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_MASK) |\
	(((_ddrdiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_MASK) |\
	(((_ahbdiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_MASK) |\
	((_cpu_from_cpupll << QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_CPUPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_CPUPLL_MASK) |\
	((_ddr_from_ddrpll << QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_DDRPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_DDRPLL_MASK) |\
	((_ahb_from_ddrpll << QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_MASK)

/* CPU/DDR_PLL_DITHER */
#define _qca95xx_cpu_pll_dither_reg_val(_nfracmin)	\
	((_nfracmin << QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK)

#define _qca95xx_ddr_pll_dither_reg_val(_nfracmin)	\
	((_nfracmin << QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK)

/* SPI_CONTROL_ADDR */
#define _qca95xx_spi_ctrl_addr_reg_val(_clk_div,   \
				       _remap_dis, \
				       _reloc_spi, \
				       _tshsl_cnt) \
						   \
	((((_clk_div / 2) - 1) << QCA_SPI_CTRL_CLK_DIV_SHIFT) & QCA_SPI_CTRL_CLK_DIV_MASK) |\
	((_remap_dis << QCA_SPI_CTRL_REMAP_DIS_SHIFT)    & QCA_SPI_CTRL_REMAP_DIS_MASK)    |\
	((_reloc_spi << QCA_SPI_CTRL_SPI_RELOCATE_SHIFT) & QCA_SPI_CTRL_SPI_RELOCATE_MASK) |\
	((_tshsl_cnt << QCA_SPI_CTRL_TSHSL_CNT_SHIFT)    & QCA_SPI_CTRL_TSHSL_CNT_MASK)

/*
 * =============================
 * PLL configuration preset list
 * =============================
 */
#if (CONFIG_QCA_PLL == QCA_PLL_PRESET_100_100_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(28, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(28, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(7, 7, 7, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(35, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(35, 2, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(7, 7, 7, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(4, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_125_100_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(25, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(28, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 7, 7, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(35, 2, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 7, 7, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(16)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(4, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_150_150_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_150_150_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_160_160_80)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(26, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_170_170_85)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(34, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(34, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 5, 10, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(17, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(17, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_180_180_90)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(29, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(29, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(9, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(9, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_200_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 6, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 6, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_200_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_200_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 6, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 6, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 6, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 6, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_350_350_175)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(14, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(14, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(8, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(8, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_360_360_180)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(29, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(29, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(9, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(9, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_380_380_190)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(13)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_ddr_pll_dither_reg_val(205)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(19, 1, 0, 1, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(19, 1, 0, 1, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(6,  1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 1, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 0, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_300_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_400_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_300_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_300_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_400_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_400_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_300_275)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_300_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_375_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(30, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(19, 1, 0, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_550_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(48)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_560_450_225)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(26)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(14, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 0, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 0, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_300_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 1, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(6,  1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 1, 1, 0, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_300_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_400_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_400_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_400_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_450_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_450_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_450_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_450_225)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_450_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_500_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_500_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_500_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_500_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_500_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_550_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_550_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_550_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_550_275)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_550_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(13, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(768)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_600_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_600_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_600_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_600_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(6,  1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_600_600_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_200_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_200_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_200_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_300_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_300_150)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_300_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_300_300)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_400_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_400_155)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_400_310)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_100)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_155)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_166)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_206)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_250)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_620_500_310)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_cpu_pll_dither_reg_val(52)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0)

	#define QCA_SPI_CTRL_REG_VAL				_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_650_400_200)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(16)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_650_420_210)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25		_qca95xx_ddr_pll_dither_reg_val(820)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(16)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(512)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_650_450_225)	/* Tested! */

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(11, 1, 1, 0, 0)
	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL40		_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_cpu_pll_dither_reg_val(16)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40		_qca95xx_ddr_pll_dither_reg_val(256)

#else
	#error "QCA PLL configuration not supported or not selected!"
#endif

/*
 * Safe configuration, used in "O/C recovery" mode:
 * CPU/DDR/AHB/SPI: 400/400/200/20
 */
#define QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL25		_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0)
#define QCA_PLL_DDR_PLL_CFG_REG_VAL_SAFE_XTAL25		_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0)
#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_SAFE_XTAL25	_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_SAFE_XTAL25	_qca95xx_cpu_pll_dither_reg_val(0)
#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_SAFE_XTAL25	_qca95xx_ddr_pll_dither_reg_val(0)

#define QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL40		_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0)
#define QCA_PLL_DDR_PLL_CFG_REG_VAL_SAFE_XTAL40		_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0)
#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_SAFE_XTAL40	_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1)
#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_SAFE_XTAL40	_qca95xx_cpu_pll_dither_reg_val(0)
#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_SAFE_XTAL40	_qca95xx_ddr_pll_dither_reg_val(0)

#define QCA_SPI_CTRL_REG_VAL_SAFE			_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2)

/*
 * Default values (if not defined above)
 */

/* Maximum clock for SPI NOR FLASH */
#ifndef CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ
	#define CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ	30
#endif

/* SPI_CONTROL_ADDR register value */
#ifndef QCA_SPI_CTRL_REG_VAL
	#define QCA_SPI_CTRL_REG_VAL			_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2)
#endif

/* CPU PLL dither register values */
#ifndef QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca95xx_cpu_pll_dither_reg_val(0)
#endif

#ifndef QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40
	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL40	_qca95xx_cpu_pll_dither_reg_val(0)
#endif

/* DDR PLL dither register values */
#ifndef QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca95xx_ddr_pll_dither_reg_val(0)
#endif

#ifndef QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL40	_qca95xx_ddr_pll_dither_reg_val(0)
#endif

#endif /* _QCA95XX_PLL_INIT_H_ */
