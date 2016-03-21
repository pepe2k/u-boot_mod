/*
 * Helper defines and macros related with
 * PLL and clocks configurations for
 * Qualcomm/Atheros AR933x WiSoC
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _AR933X_PLL_INIT_H_
#define _AR933X_PLL_INIT_H_

#include <soc/qca_soc_common.h>

/* CPU_PLL_CONFIG */
#define _ar933x_cpu_pll_cfg_reg_val(_nint,   \
									_refdiv, \
									_range,  \
									_outdiv) \
											 \
		((_nint   << QCA_PLL_CPU_PLL_CFG_NINT_SHIFT)   & QCA_PLL_CPU_PLL_CFG_NINT_MASK)   |\
		((_refdiv << QCA_PLL_CPU_PLL_CFG_REFDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_REFDIV_MASK) |\
		((_range  << QCA_PLL_CPU_PLL_CFG_RANGE_SHIFT)  & QCA_PLL_CPU_PLL_CFG_RANGE_MASK)  |\
		((_outdiv << QCA_PLL_CPU_PLL_CFG_OUTDIV_SHIFT) & QCA_PLL_CPU_PLL_CFG_OUTDIV_MASK)

/* CPU_CLOCK_CONTROL */
#define _ar933x_cpu_clk_ctrl_reg_val(_cpudiv, \
									 _ddrdiv, \
									 _ahbdiv) \
											  \
		(((_cpudiv - 1) << QCA_PLL_CPU_CLK_CTRL_CPU_POST_DIV_SHIFT) &\
		 QCA_PLL_CPU_CLK_CTRL_CPU_POST_DIV_MASK) |\
		(((_ddrdiv - 1) << QCA_PLL_CPU_CLK_CTRL_DDR_POST_DIV_SHIFT) &\
		 QCA_PLL_CPU_CLK_CTRL_DDR_POST_DIV_MASK) |\
		(((_ahbdiv - 1) << QCA_PLL_CPU_CLK_CTRL_AHB_POST_DIV_SHIFT) &\
		 QCA_PLL_CPU_CLK_CTRL_AHB_POST_DIV_MASK)

/* PLL_DITHER_FRAC */
#define _ar933x_cpu_pll_dither_frac_reg_val(_nfracmin)	\
		((_nfracmin << QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_SHIFT) &\
		 QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK)

/* SPI_CONTROL_ADDR */
#define _ar933x_spi_ctrl_addr_reg_val(_clk_div,   \
									  _remap_dis, \
									  _reloc_spi) \
												  \
		((((_clk_div / 2) - 1) << QCA_SPI_CTRL_CLK_DIV_SHIFT) & QCA_SPI_CTRL_CLK_DIV_MASK) |\
		((_remap_dis << QCA_SPI_CTRL_REMAP_DIS_SHIFT)    & QCA_SPI_CTRL_REMAP_DIS_MASK)    |\
		((_reloc_spi << QCA_SPI_CTRL_SPI_RELOCATE_SHIFT) & QCA_SPI_CTRL_SPI_RELOCATE_MASK)

/*
 * =============================
 * PLL configuration preset list
 * =============================
 */
#if (CONFIG_QCA_PLL == QCA_PLL_PRESET_100_100_50)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(16, 1, 1, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(10, 1, 1, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(4, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_100_100_100)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(4, 4, 4)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(4, 4, 4)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(4, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_150_150_150)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(15, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 2)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(6, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_160_160_80)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4)
	#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL25	_ar933x_cpu_pll_dither_frac_reg_val(615)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(16, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(4, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_200_200_100)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 2)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 2)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(4, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_200_200_200)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 2)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 1)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 2)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 1)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_300_300_150)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(15, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(6, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_350_350_175)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(28, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(17, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)
	#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL40	_ar933x_cpu_pll_dither_frac_reg_val(512)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(6, 1, 0)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_400_400_200)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

#elif (CONFIG_QCA_PLL == QCA_PLL_PRESET_500_500_250)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL25			_ar933x_cpu_pll_cfg_reg_val(40, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_PLL_CPU_PLL_CFG_REG_VAL_XTAL40			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1)
	#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)

	#define QCA_SPI_CTRL_REG_VAL						_ar933x_spi_ctrl_addr_reg_val(10, 1, 0)

#else
	#error "QCA PLL configuration not supported or not selected!"
#endif

/*
 * Safe configuration, used in "O/C recovery" mode:
 * CPU/DDR/AHB/SPI: 400/400/200/20
 */
#define QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL25				_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1)
#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_SAFE_XTAL25			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)
#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_SAFE_XTAL25		_ar933x_cpu_pll_dither_frac_reg_val(0)

#define QCA_PLL_CPU_PLL_CFG_REG_VAL_SAFE_XTAL40				_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1)
#define QCA_PLL_CPU_CLK_CTRL_REG_VAL_SAFE_XTAL40			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2)
#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_SAFE_XTAL40		_ar933x_cpu_pll_dither_frac_reg_val(0)

#define QCA_SPI_CTRL_REG_VAL_SAFE							_ar933x_spi_ctrl_addr_reg_val(10, 1, 0)

/*
 * Default values (if not defined above)
 */

/* Maximum clock for SPI NOR FLASH */
#ifndef CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ
	#define CONFIG_QCA_SPI_NOR_FLASH_MAX_CLK_MHZ	30
#endif

/* SPI_CONTROL_ADDR register value */
#ifndef QCA_SPI_CTRL_REG_VAL
	#define QCA_SPI_CTRL_REG_VAL					_ar933x_spi_ctrl_addr_reg_val(8, 1, 0)
#endif

/* CPU PLL dither register values */
#ifndef QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL25
	#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL25		_ar933x_cpu_pll_dither_frac_reg_val(0)
#endif

#ifndef QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL40
	#define QCA_PLL_CPU_PLL_DITHER_FRAC_REG_VAL_XTAL40		_ar933x_cpu_pll_dither_frac_reg_val(0)
#endif

/* CPU PLL settle time */
#define QCA_PLL_CPU_PLL_CFG2_SETTLE_TIME_REG_VAL_XTAL25		0x550
#define QCA_PLL_CPU_PLL_CFG2_SETTLE_TIME_REG_VAL_XTAL40		0x352

#endif /* _AR933X_PLL_INIT_H_ */
