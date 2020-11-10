/*
 * Helper defines and macros related with
 * PLL and clocks configurations for
 * Qualcomm/Atheros QCA956x WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2018 Julien Dusser <julien.dusser@free.fr>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _QCA956X_PLL_INIT_H_
#define _QCA956X_PLL_INIT_H_

#include <config.h>

/* CPU_PLL_CONFIG */
#define _qca956x_cpu_pll_cfg_reg_val(_refdiv, \
				     _range,  \
				     _outdiv, \
				     _dis)    \
					      \
	(((_refdiv << QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK) |\
	((_range  << QCA_PLL_CPU_PLL_CFG_RANGE_SHIFT)  & QCA_PLL_CPU_PLL_CFG_RANGE_MASK)  |\
	((_outdiv << QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK) |\
	((_dis    << QCA_PLL_CPU_PLL_CFG_PLLPWD_SHIFT) & QCA_PLL_CPU_PLL_CFG_PLLPWD_MASK))

#define _qca956x_cpu_pll_cfg1_reg_val(_nint,   \
				     _nfrac_h, \
				     _nfrac_l)  \
					      \
	(((_nint    << QCA_PLL_CPU_PLL_CFG1_NINT_SHIFT)    & QCA_PLL_CPU_PLL_CFG1_NINT_MASK)   |\
	((_nfrac_h << QCA_PLL_CPU_PLL_CFG1_NFRAC_H_SHIFT) & QCA_PLL_CPU_PLL_CFG1_NFRAC_H_MASK) |\
	((_nfrac_l << QCA_PLL_CPU_PLL_CFG1_NFRAC_L_SHIFT) & QCA_PLL_CPU_PLL_CFG1_NFRAC_L_MASK))

/* DDR_PLL_CONFIG */
#define _qca956x_ddr_pll_cfg_reg_val(_refdiv, \
				     _range,  \
				     _outdiv, \
				     _dis)    \
					      \
	(((_refdiv << QCA_PLL_DDR_PLL_CFG_REFDIV_SHIFT) & QCA_PLL_DDR_PLL_CFG_REFDIV_MASK) |\
	((_range  << QCA_PLL_DDR_PLL_CFG_RANGE_SHIFT)  & QCA_PLL_DDR_PLL_CFG_RANGE_MASK)  |\
	((_outdiv << QCA_PLL_DDR_PLL_CFG_OUTDIV_SHIFT) & QCA_PLL_DDR_PLL_CFG_OUTDIV_MASK) |\
	((_dis    << QCA_PLL_DDR_PLL_CFG_PLLPWD_SHIFT) & QCA_PLL_DDR_PLL_CFG_PLLPWD_MASK))

#define _qca956x_ddr_pll_cfg1_reg_val(_nint,   \
				     _nfrac_h, \
				     _nfrac_l)  \
					      \
	(((_nint   << QCA_PLL_DDR_PLL_CFG1_NINT_SHIFT)    & QCA_PLL_DDR_PLL_CFG1_NINT_MASK)   |\
	((_nfrac_h << QCA_PLL_DDR_PLL_CFG1_NFRAC_H_SHIFT) & QCA_PLL_DDR_PLL_CFG1_NFRAC_H_MASK) |\
	((_nfrac_l << QCA_PLL_DDR_PLL_CFG1_NFRAC_L_SHIFT) & QCA_PLL_DDR_PLL_CFG1_NFRAC_L_MASK))


/* CPU/DDR_PLL_DITHER */
#define _qca956x_cpu_pll_dither_reg_val(_dither_en,	\
					_nfrac_min_l,	\
					_nfrac_min_h,	\
					_nfrac_step,	\
					_update_count)	\
	(((_dither_en << QCA_PLL_CPU_PLL_DITHER_DITHER_EN_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_DITHER_EN_MASK) |\
	((_nfrac_min_l << QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_L_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_L_MASK) |\
	((_nfrac_min_h << QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_H_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_H_MASK) |\
	((_nfrac_step << QCA_PLL_CPU_PLL_DITHER_NFRAC_STEP_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_NFRAC_STEP_MASK) |\
	((_update_count << QCA_PLL_CPU_PLL_DITHER_UPDATE_CNT_SHIFT) &\
	 QCA_PLL_CPU_PLL_DITHER_UPDATE_CNT_MASK))

#define _qca956x_ddr_pll_dither_reg_val(_dither_en,	\
					_nfrac_min_l,	\
					_nfrac_min_h,	\
					_nfrac_step,	\
					_update_count)	\
	(((_dither_en << QCA_PLL_DDR_PLL_DITHER_DITHER_EN_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_DITHER_EN_MASK) |\
	((_nfrac_min_l << QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_L_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_L_MASK) |\
	((_nfrac_min_h << QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_H_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_H_MASK) |\
	((_nfrac_step << QCA_PLL_DDR_PLL_DITHER_NFRAC_STEP_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_NFRAC_STEP_MASK) |\
	((_update_count << QCA_PLL_DDR_PLL_DITHER_UPDATE_CNT_SHIFT) &\
	 QCA_PLL_DDR_PLL_DITHER_UPDATE_CNT_MASK))

/* CPU_DDR_CLOCK_CONTROL */
#define _qca956x_cpu_ddr_clk_ctrl_reg_val(_cpudiv,          \
					  _ddrdiv,          \
					  _ahbdiv,          \
					  _ddr_from_cpupll, \
					  _ddr_from_ddrpll, \
					  _ahb_from_ddrpll) \
							    \
	((((_cpudiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_CPU_POST_DIV_MASK) |\
	(((_ddrdiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_DDR_POST_DIV_MASK) |\
	(((_ahbdiv - 1) << QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_AHB_POST_DIV_MASK) |\
	((_ddr_from_cpupll << QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_CPUPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_DDRCLK_FROM_CPUPLL_MASK) |\
	((_ddr_from_ddrpll << QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_DDRPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_CPUCLK_FROM_DDRPLL_MASK) |\
	((_ahb_from_ddrpll << QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_SHIFT) &\
	 QCA_PLL_CPU_DDR_CLK_CTRL_AHBCLK_FROM_DDRPLL_MASK))

/* SPI_CONTROL_ADDR same than _qca95xx_spi_ctrl_addr_reg_val */
#define _qca956x_spi_ctrl_addr_reg_val(_clk_div,   \
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
#if (CONFIG_QCA_PLL == QCA_PLL_PRESET_750_393_196) //DDR1 CAL = 3
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(30, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(31, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 0, 0, 1)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 12, 3604, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa24

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_750_400_250) //DDR1 CAL = 3
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(30, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(32, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa24

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_750_667_250) //DDR2 CAL = 6
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(30, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 14, 5570, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_775_650_258) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(31, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_333_266) //DDR1 CAL = 3
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)


	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 22, 5242, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa24

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_400_266) //DDR1 CAL = 3
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(32, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa24

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_450_266) //DDR2 CAL = 4
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(36, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_533_266) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(42, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 22, 5242, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_600_266) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(24, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_600_300) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(24, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 0, 0, 1)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_666_266) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 22, 5242, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_667_266) //DDR2 CAL = 6
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 14, 5570, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_800_700_266) //DDR2 CAL = 6
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(28, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 0, 0, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_810_400_270) //DDR1 CAL = 3
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(32, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 1, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 20, 3276, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa24

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_810_666_270) //DDR2 CAL = 5
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(26, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 20, 3276, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 22, 5242, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL				0xa12

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_810_700_270) //DDR2 CAL = 6
	#define QCA_PLL_CPU_PLL_CFG1_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg1_reg_val(32, 0, 0)
	#define QCA_PLL_DDR_PLL_CFG1_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg1_reg_val(28, 0, 0)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25	_qca956x_cpu_pll_cfg_reg_val(1, 0, 0, 1)
	#define QCA_PLL_DDR_PLL_CFG_REG_VAL_XTAL25	_qca956x_ddr_pll_cfg_reg_val(1, 0, 0, 1)

	#define QCA_PLL_CPU_DDR_CLK_CTRL_REG_VAL_XTAL25	_qca956x_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER_REG_VAL_XTAL25	_qca956x_cpu_pll_dither_reg_val(0, 20, 3276, 0, 0)
	#define QCA_PLL_DDR_PLL_DITHER_REG_VAL_XTAL25	_qca956x_ddr_pll_dither_reg_val(0, 0, 0, 0, 0)

	#define QCA_PLL_CPU_PLL_DITHER2_REG_VAL_XTAL25  0
	#define QCA_PLL_DDR_PLL_DITHER2_REG_VAL_XTAL25  0

	#define QCA_DDR_FSM_WAIT_CTRL_VAL		0xa12

#else
#   error "CONFIG_QCA_PLL not set"
#endif  /* CONFIG_QCA_PLL */

/* Maximum clock for SPI NOR FLASH */
#ifndef CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ
	#define CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ	30
#endif

/* SPI_CONTROL_ADDR register value */
#ifndef QCA_SPI_CTRL_REG_VAL
	#define QCA_SPI_CTRL_REG_VAL			_qca956x_spi_ctrl_addr_reg_val(14, 1, 0, 2)
#endif





	/* Common */
#define QCA_DDR_CTRL_CFG_SYNC_MODE			0

#endif /* _QCA956X_PLL_INIT_H_ */
