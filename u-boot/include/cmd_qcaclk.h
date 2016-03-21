/*
 * Commands related with PLL/clocks settings
 * for Qualcomm/Atheros WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _CMD_QCACLK_H_
#define _CMD_QCACLK_H_

#include <soc/qca_soc_common.h>
#if (SOC_TYPE & QCA_AR933X_SOC)
	#include <soc/ar933x_pll_init.h>
#else
	#include <soc/qca95xx_pll_init.h>
#endif

#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET

	#ifndef CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET
		#error "Missing definition for CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET"
	#endif

	#ifndef CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE
		#error "Missing definition for CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE"
	#endif

	#if (SOC_TYPE & QCA_AR933X_SOC)
typedef struct {
	u32 cpu_pll_cfg;
	u32 cpu_clk_ctrl;
	u32 cpu_pll_dit;
} pll_regs;
	#else
typedef struct {
	u32 cpu_pll_cfg;
	u32 ddr_pll_cfg;
	u32 cpu_ddr_clk_ctrl;
	u32 cpu_pll_dit;
	u32 ddr_pll_dit;
} pll_regs;
	#endif /* SOC_TYPE & QCA_AR933X_SOC */

typedef struct {
	u32 spi_ctrl;
	pll_regs regs;
} clk_cfg_flash;

/*
 * Contains:
 * 1. CPU, RAM, AHB and SPI clocks [MHz]
 * 2. Target SPI_CONTROL register value
 * 3. Target PLL related register values,
 *    for 25 and 40 MHz XTAL types
 */
typedef struct {
	u16 cpu_clk;
	u16 ddr_clk;
	u16 ahb_clk;
	u8  spi_clk;

	u32 spi_ctrl;

	pll_regs xtal_25mhz;
	pll_regs xtal_40mhz;
} clk_profile;

static const clk_profile clk_profiles[] = {
	#if (SOC_TYPE & QCA_AR933X_SOC)
	{
		/* Tested! */
		100, 100, 50, 12,
		_ar933x_spi_ctrl_addr_reg_val(4, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(16, 1, 1, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(10, 1, 1, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		100, 100, 100, 25,
		_ar933x_spi_ctrl_addr_reg_val(4, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(4, 4, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(4, 4, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		150, 150, 150, 25,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(15, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		160, 160, 80, 20,
		_ar933x_spi_ctrl_addr_reg_val(4, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(615)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(16, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(2, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		200, 200, 100, 25,
		_ar933x_spi_ctrl_addr_reg_val(4, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 2),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 2),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		200, 200, 200, 25,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 2),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 1),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 2),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 1),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		300, 300, 150, 25,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(15, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		350, 350, 175, 29,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(28, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(17, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		400, 400, 200, 25,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		410, 410, 205, 25,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(820)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		420, 420, 210, 26,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(33, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(615)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(21, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		430, 430, 215, 26,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(34, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(410)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(21, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		440, 440, 220, 27,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(35, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(205)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(22, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		450, 450, 225, 28,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(36, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(45, 2, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		460, 460, 230, 28,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(36, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(820)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(23, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		470, 470, 235, 29,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(37, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(615)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(23, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		480, 480, 240, 30,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(38, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(410)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		490, 490, 245, 30,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(39, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(205)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(24, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		500, 500, 250, 25,
		_ar933x_spi_ctrl_addr_reg_val(10, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(40, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		510, 510, 255, 25,
		_ar933x_spi_ctrl_addr_reg_val(10, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(40, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(820)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		520, 520, 260, 26,
		_ar933x_spi_ctrl_addr_reg_val(10, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(41, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(615)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(26, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		530, 265, 132, 22,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(42, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(410)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(26, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		540, 270, 135, 22,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(43, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(205)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(27, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		550, 275, 137, 22,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(44, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(27, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		560, 280, 140, 23,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(44, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(820)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(28, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	{
		/* Tested! */
		570, 285, 142, 23,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(45, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(615)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(28, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	},
	{
		/* Tested! */
		580, 290, 145, 24,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(46, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(410)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(29, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	#else
	{
		/* Tested! */
		100, 100, 100, 25,
		_qca95xx_spi_ctrl_addr_reg_val(4, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(28, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(28, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(7, 7, 7, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(35, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(35, 2, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(7, 7, 7, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		125, 100, 100, 25,
		_qca95xx_spi_ctrl_addr_reg_val(4, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(25, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(28, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 7, 7, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(35, 2, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 7, 7, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		150, 150, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		150, 150, 150, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		160, 160, 80, 10,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(26, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		170, 170, 85, 10,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(34, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(34, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(5, 5, 10, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(17, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(17, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		180, 180, 90, 11,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(29, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(29, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(9, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(9, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		200, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		200, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		200, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(3, 3, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 3, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		300, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		350, 350, 175, 21,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(14, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(14, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(35, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(35, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		360, 360, 180, 22,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(29, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(29, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(2, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(9, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(9, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		380, 380, 190, 23,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(13),
			_qca95xx_ddr_pll_dither_reg_val(205)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(19, 1, 0, 1, 0),
			_qca95xx_ddr_pll_cfg_reg_val(19, 1, 0, 1, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 300, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		400, 400, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 300, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 300, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 400, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 400, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 300, 275, 27,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 300, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 375, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(30, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(19, 1, 0, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		560, 450, 225, 28,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(26),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(14, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 300, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 300, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 400, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 400, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 400, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 450, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 450, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 450, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 450, 225, 28,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 450, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 500, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 500, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 500, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 500, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 500, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 550, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 550, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 550, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 550, 275, 27,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 550, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(55, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 600, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 6, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 600, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 600, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 0, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		600, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 200, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 200, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 3, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 200, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 300, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 300, 150, 18,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 300, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 300, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(12, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 1, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 400, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 400, 155, 19,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 400, 310, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 100, 12,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 155, 19,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 166, 20,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 206, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		620, 500, 310, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(24, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(20, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(52),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(31, 2, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(25, 2, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 420, 210, 26,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(820)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(42, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 450, 225, 28,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(18, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(45, 4, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	},
	#endif /* SOC_TYPE & QCA_AR933X_SOC */
};

/* Number of all profiles */
static u32 clk_profiles_cnt = sizeof(clk_profiles) / sizeof(clk_profile);

#endif /* CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET */

#endif /* _CMD_QCACLK_H_ */
