/*
 * Atheros AR924X series processor SOC registers
 *
 * (C) Copyright 2008 Atheros Communications, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _AR934X_SOC_H
#define _AR934X_SOC_H

// 32'h0000 (CPU_PLL_CONFIG)
#define CPU_PLL_CONFIG_UPDATING_MSB                                  31
#define CPU_PLL_CONFIG_UPDATING_LSB                                  31
#define CPU_PLL_CONFIG_UPDATING_MASK                                 0x80000000
#define CPU_PLL_CONFIG_UPDATING_GET(x)                               (((x) & CPU_PLL_CONFIG_UPDATING_MASK) >> CPU_PLL_CONFIG_UPDATING_LSB)
#define CPU_PLL_CONFIG_UPDATING_SET(x)                               (((x) << CPU_PLL_CONFIG_UPDATING_LSB) & CPU_PLL_CONFIG_UPDATING_MASK)
#define CPU_PLL_CONFIG_UPDATING_RESET                                1
#define CPU_PLL_CONFIG_PLLPWD_MSB                                    30
#define CPU_PLL_CONFIG_PLLPWD_LSB                                    30
#define CPU_PLL_CONFIG_PLLPWD_MASK                                   0x40000000
#define CPU_PLL_CONFIG_PLLPWD_GET(x)                                 (((x) & CPU_PLL_CONFIG_PLLPWD_MASK) >> CPU_PLL_CONFIG_PLLPWD_LSB)
#define CPU_PLL_CONFIG_PLLPWD_SET(x)                                 (((x) << CPU_PLL_CONFIG_PLLPWD_LSB) & CPU_PLL_CONFIG_PLLPWD_MASK)
#define CPU_PLL_CONFIG_PLLPWD_RESET                                  1
#define CPU_PLL_CONFIG_SPARE_MSB                                     29
#define CPU_PLL_CONFIG_SPARE_LSB                                     22
#define CPU_PLL_CONFIG_SPARE_MASK                                    0x3fc00000
#define CPU_PLL_CONFIG_SPARE_GET(x)                                  (((x) & CPU_PLL_CONFIG_SPARE_MASK) >> CPU_PLL_CONFIG_SPARE_LSB)
#define CPU_PLL_CONFIG_SPARE_SET(x)                                  (((x) << CPU_PLL_CONFIG_SPARE_LSB) & CPU_PLL_CONFIG_SPARE_MASK)
#define CPU_PLL_CONFIG_SPARE_RESET                                   0
#define CPU_PLL_CONFIG_OUTDIV_MSB                                    21
#define CPU_PLL_CONFIG_OUTDIV_LSB                                    19
#define CPU_PLL_CONFIG_OUTDIV_MASK                                   0x00380000
#define CPU_PLL_CONFIG_OUTDIV_GET(x)                                 (((x) & CPU_PLL_CONFIG_OUTDIV_MASK) >> CPU_PLL_CONFIG_OUTDIV_LSB)
#define CPU_PLL_CONFIG_OUTDIV_SET(x)                                 (((x) << CPU_PLL_CONFIG_OUTDIV_LSB) & CPU_PLL_CONFIG_OUTDIV_MASK)
#define CPU_PLL_CONFIG_OUTDIV_RESET                                  0
#define CPU_PLL_CONFIG_RANGE_MSB                                     18
#define CPU_PLL_CONFIG_RANGE_LSB                                     17
#define CPU_PLL_CONFIG_RANGE_MASK                                    0x00060000
#define CPU_PLL_CONFIG_RANGE_GET(x)                                  (((x) & CPU_PLL_CONFIG_RANGE_MASK) >> CPU_PLL_CONFIG_RANGE_LSB)
#define CPU_PLL_CONFIG_RANGE_SET(x)                                  (((x) << CPU_PLL_CONFIG_RANGE_LSB) & CPU_PLL_CONFIG_RANGE_MASK)
#define CPU_PLL_CONFIG_RANGE_RESET                                   3
#define CPU_PLL_CONFIG_REFDIV_MSB                                    16
#define CPU_PLL_CONFIG_REFDIV_LSB                                    12
#define CPU_PLL_CONFIG_REFDIV_MASK                                   0x0001f000
#define CPU_PLL_CONFIG_REFDIV_GET(x)                                 (((x) & CPU_PLL_CONFIG_REFDIV_MASK) >> CPU_PLL_CONFIG_REFDIV_LSB)
#define CPU_PLL_CONFIG_REFDIV_SET(x)                                 (((x) << CPU_PLL_CONFIG_REFDIV_LSB) & CPU_PLL_CONFIG_REFDIV_MASK)
#define CPU_PLL_CONFIG_REFDIV_RESET                                  2
#define CPU_PLL_CONFIG_NINT_MSB                                      11
#define CPU_PLL_CONFIG_NINT_LSB                                      6
#define CPU_PLL_CONFIG_NINT_MASK                                     0x00000fc0
#define CPU_PLL_CONFIG_NINT_GET(x)                                   (((x) & CPU_PLL_CONFIG_NINT_MASK) >> CPU_PLL_CONFIG_NINT_LSB)
#define CPU_PLL_CONFIG_NINT_SET(x)                                   (((x) << CPU_PLL_CONFIG_NINT_LSB) & CPU_PLL_CONFIG_NINT_MASK)
#define CPU_PLL_CONFIG_NINT_RESET                                    20
#define CPU_PLL_CONFIG_NFRAC_MSB                                     5
#define CPU_PLL_CONFIG_NFRAC_LSB                                     0
#define CPU_PLL_CONFIG_NFRAC_MASK                                    0x0000003f
#define CPU_PLL_CONFIG_NFRAC_GET(x)                                  (((x) & CPU_PLL_CONFIG_NFRAC_MASK) >> CPU_PLL_CONFIG_NFRAC_LSB)
#define CPU_PLL_CONFIG_NFRAC_SET(x)                                  (((x) << CPU_PLL_CONFIG_NFRAC_LSB) & CPU_PLL_CONFIG_NFRAC_MASK)
#define CPU_PLL_CONFIG_NFRAC_RESET                                   16
#define CPU_PLL_CONFIG_ADDRESS                                       0x0000
#define CPU_PLL_CONFIG_OFFSET                                        0x0000
// SW modifiable bits
#define CPU_PLL_CONFIG_SW_MASK                                       0xffffffff
// bits defined at reset
#define CPU_PLL_CONFIG_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define CPU_PLL_CONFIG_RESET                                         0xc0062510

// 32'h0004 (DDR_PLL_CONFIG)
#define DDR_PLL_CONFIG_UPDATING_MSB                                  31
#define DDR_PLL_CONFIG_UPDATING_LSB                                  31
#define DDR_PLL_CONFIG_UPDATING_MASK                                 0x80000000
#define DDR_PLL_CONFIG_UPDATING_GET(x)                               (((x) & DDR_PLL_CONFIG_UPDATING_MASK) >> DDR_PLL_CONFIG_UPDATING_LSB)
#define DDR_PLL_CONFIG_UPDATING_SET(x)                               (((x) << DDR_PLL_CONFIG_UPDATING_LSB) & DDR_PLL_CONFIG_UPDATING_MASK)
#define DDR_PLL_CONFIG_UPDATING_RESET                                1
#define DDR_PLL_CONFIG_PLLPWD_MSB                                    30
#define DDR_PLL_CONFIG_PLLPWD_LSB                                    30
#define DDR_PLL_CONFIG_PLLPWD_MASK                                   0x40000000
#define DDR_PLL_CONFIG_PLLPWD_GET(x)                                 (((x) & DDR_PLL_CONFIG_PLLPWD_MASK) >> DDR_PLL_CONFIG_PLLPWD_LSB)
#define DDR_PLL_CONFIG_PLLPWD_SET(x)                                 (((x) << DDR_PLL_CONFIG_PLLPWD_LSB) & DDR_PLL_CONFIG_PLLPWD_MASK)
#define DDR_PLL_CONFIG_PLLPWD_RESET                                  1
#define DDR_PLL_CONFIG_SPARE_MSB                                     29
#define DDR_PLL_CONFIG_SPARE_LSB                                     26
#define DDR_PLL_CONFIG_SPARE_MASK                                    0x3c000000
#define DDR_PLL_CONFIG_SPARE_GET(x)                                  (((x) & DDR_PLL_CONFIG_SPARE_MASK) >> DDR_PLL_CONFIG_SPARE_LSB)
#define DDR_PLL_CONFIG_SPARE_SET(x)                                  (((x) << DDR_PLL_CONFIG_SPARE_LSB) & DDR_PLL_CONFIG_SPARE_MASK)
#define DDR_PLL_CONFIG_SPARE_RESET                                   0
#define DDR_PLL_CONFIG_OUTDIV_MSB                                    25
#define DDR_PLL_CONFIG_OUTDIV_LSB                                    23
#define DDR_PLL_CONFIG_OUTDIV_MASK                                   0x03800000
#define DDR_PLL_CONFIG_OUTDIV_GET(x)                                 (((x) & DDR_PLL_CONFIG_OUTDIV_MASK) >> DDR_PLL_CONFIG_OUTDIV_LSB)
#define DDR_PLL_CONFIG_OUTDIV_SET(x)                                 (((x) << DDR_PLL_CONFIG_OUTDIV_LSB) & DDR_PLL_CONFIG_OUTDIV_MASK)
#define DDR_PLL_CONFIG_OUTDIV_RESET                                  0
#define DDR_PLL_CONFIG_RANGE_MSB                                     22
#define DDR_PLL_CONFIG_RANGE_LSB                                     21
#define DDR_PLL_CONFIG_RANGE_MASK                                    0x00600000
#define DDR_PLL_CONFIG_RANGE_GET(x)                                  (((x) & DDR_PLL_CONFIG_RANGE_MASK) >> DDR_PLL_CONFIG_RANGE_LSB)
#define DDR_PLL_CONFIG_RANGE_SET(x)                                  (((x) << DDR_PLL_CONFIG_RANGE_LSB) & DDR_PLL_CONFIG_RANGE_MASK)
#define DDR_PLL_CONFIG_RANGE_RESET                                   3
#define DDR_PLL_CONFIG_REFDIV_MSB                                    20
#define DDR_PLL_CONFIG_REFDIV_LSB                                    16
#define DDR_PLL_CONFIG_REFDIV_MASK                                   0x001f0000
#define DDR_PLL_CONFIG_REFDIV_GET(x)                                 (((x) & DDR_PLL_CONFIG_REFDIV_MASK) >> DDR_PLL_CONFIG_REFDIV_LSB)
#define DDR_PLL_CONFIG_REFDIV_SET(x)                                 (((x) << DDR_PLL_CONFIG_REFDIV_LSB) & DDR_PLL_CONFIG_REFDIV_MASK)
#define DDR_PLL_CONFIG_REFDIV_RESET                                  2
#define DDR_PLL_CONFIG_NINT_MSB                                      15
#define DDR_PLL_CONFIG_NINT_LSB                                      10
#define DDR_PLL_CONFIG_NINT_MASK                                     0x0000fc00
#define DDR_PLL_CONFIG_NINT_GET(x)                                   (((x) & DDR_PLL_CONFIG_NINT_MASK) >> DDR_PLL_CONFIG_NINT_LSB)
#define DDR_PLL_CONFIG_NINT_SET(x)                                   (((x) << DDR_PLL_CONFIG_NINT_LSB) & DDR_PLL_CONFIG_NINT_MASK)
#define DDR_PLL_CONFIG_NINT_RESET                                    20
#define DDR_PLL_CONFIG_NFRAC_MSB                                     9
#define DDR_PLL_CONFIG_NFRAC_LSB                                     0
#define DDR_PLL_CONFIG_NFRAC_MASK                                    0x000003ff
#define DDR_PLL_CONFIG_NFRAC_GET(x)                                  (((x) & DDR_PLL_CONFIG_NFRAC_MASK) >> DDR_PLL_CONFIG_NFRAC_LSB)
#define DDR_PLL_CONFIG_NFRAC_SET(x)                                  (((x) << DDR_PLL_CONFIG_NFRAC_LSB) & DDR_PLL_CONFIG_NFRAC_MASK)
#define DDR_PLL_CONFIG_NFRAC_RESET                                   512
#define DDR_PLL_CONFIG_ADDRESS                                       0x0004
#define DDR_PLL_CONFIG_OFFSET                                        0x0004
// SW modifiable bits
#define DDR_PLL_CONFIG_SW_MASK                                       0xffffffff
// bits defined at reset
#define DDR_PLL_CONFIG_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define DDR_PLL_CONFIG_RESET                                         0xc0625200

// 32'h0008 (CPU_DDR_CLOCK_CONTROL)
#define CPU_DDR_CLOCK_CONTROL_SPARE_MSB                              31
#define CPU_DDR_CLOCK_CONTROL_SPARE_LSB                              25
#define CPU_DDR_CLOCK_CONTROL_SPARE_MASK                             0xfe000000
#define CPU_DDR_CLOCK_CONTROL_SPARE_GET(x)                           (((x) & CPU_DDR_CLOCK_CONTROL_SPARE_MASK) >> CPU_DDR_CLOCK_CONTROL_SPARE_LSB)
#define CPU_DDR_CLOCK_CONTROL_SPARE_SET(x)                           (((x) << CPU_DDR_CLOCK_CONTROL_SPARE_LSB) & CPU_DDR_CLOCK_CONTROL_SPARE_MASK)
#define CPU_DDR_CLOCK_CONTROL_SPARE_RESET                            0
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MSB                 24
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB                 24
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK                0x01000000
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB) & CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_RESET               1
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MSB            23
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB            23
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK           0x00800000
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_GET(x)         (((x) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_SET(x)         (((x) << CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_RESET          0
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MSB               22
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB               22
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK              0x00400000
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_GET(x)            (((x) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_SET(x)            (((x) << CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_RESET             0
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MSB                 21
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB                 21
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK                0x00200000
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB) & CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_RESET               1
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MSB                 20
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB                 20
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK                0x00100000
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB) & CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_RESET               1
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MSB                       19
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB                       15
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK                      0x000f8000
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_RESET                     0
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MSB                       14
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB                       10
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK                      0x00007c00
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_RESET                     0
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MSB                       9
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB                       5
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK                      0x000003e0
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_RESET                     0
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MSB                     4
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB                     4
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK                    0x00000010
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_RESET                   1
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MSB                     3
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB                     3
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK                    0x00000008
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_RESET                   1
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MSB                     2
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB                     2
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK                    0x00000004
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_RESET                   1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MSB                       1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB                       1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK                      0x00000002
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK) >> CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB)
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB) & CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK)
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_RESET                     0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MSB                       0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB                       0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK                      0x00000001
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK) >> CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB)
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB) & CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK)
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_RESET                     0
#define CPU_DDR_CLOCK_CONTROL_ADDRESS                                0x0008
#define CPU_DDR_CLOCK_CONTROL_OFFSET                                 0x0008
// SW modifiable bits
#define CPU_DDR_CLOCK_CONTROL_SW_MASK                                0xffffffff
// bits defined at reset
#define CPU_DDR_CLOCK_CONTROL_RSTMASK                                0xffffffff
// reset value (ignore bits undefined at reset)
#define CPU_DDR_CLOCK_CONTROL_RESET                                  0x0130001c

// 32'h000c (CPU_SYNC)
#define CPU_SYNC_LENGTH_MSB                                          19
#define CPU_SYNC_LENGTH_LSB                                          16
#define CPU_SYNC_LENGTH_MASK                                         0x000f0000
#define CPU_SYNC_LENGTH_GET(x)                                       (((x) & CPU_SYNC_LENGTH_MASK) >> CPU_SYNC_LENGTH_LSB)
#define CPU_SYNC_LENGTH_SET(x)                                       (((x) << CPU_SYNC_LENGTH_LSB) & CPU_SYNC_LENGTH_MASK)
#define CPU_SYNC_LENGTH_RESET                                        0
#define CPU_SYNC_PATTERN_MSB                                         15
#define CPU_SYNC_PATTERN_LSB                                         0
#define CPU_SYNC_PATTERN_MASK                                        0x0000ffff
#define CPU_SYNC_PATTERN_GET(x)                                      (((x) & CPU_SYNC_PATTERN_MASK) >> CPU_SYNC_PATTERN_LSB)
#define CPU_SYNC_PATTERN_SET(x)                                      (((x) << CPU_SYNC_PATTERN_LSB) & CPU_SYNC_PATTERN_MASK)
#define CPU_SYNC_PATTERN_RESET                                       65535
#define CPU_SYNC_ADDRESS                                             0x000c
#define CPU_SYNC_OFFSET                                              0x000c
// SW modifiable bits
#define CPU_SYNC_SW_MASK                                             0x000fffff
// bits defined at reset
#define CPU_SYNC_RSTMASK                                             0xffffffff
// reset value (ignore bits undefined at reset)
#define CPU_SYNC_RESET                                               0x0000ffff

// 32'h0010 (PCIE_PLL_CONFIG)
#define PCIE_PLL_CONFIG_UPDATING_MSB                                 31
#define PCIE_PLL_CONFIG_UPDATING_LSB                                 31
#define PCIE_PLL_CONFIG_UPDATING_MASK                                0x80000000
#define PCIE_PLL_CONFIG_UPDATING_GET(x)                              (((x) & PCIE_PLL_CONFIG_UPDATING_MASK) >> PCIE_PLL_CONFIG_UPDATING_LSB)
#define PCIE_PLL_CONFIG_UPDATING_SET(x)                              (((x) << PCIE_PLL_CONFIG_UPDATING_LSB) & PCIE_PLL_CONFIG_UPDATING_MASK)
#define PCIE_PLL_CONFIG_UPDATING_RESET                               0
#define PCIE_PLL_CONFIG_PLLPWD_MSB                                   30
#define PCIE_PLL_CONFIG_PLLPWD_LSB                                   30
#define PCIE_PLL_CONFIG_PLLPWD_MASK                                  0x40000000
#define PCIE_PLL_CONFIG_PLLPWD_GET(x)                                (((x) & PCIE_PLL_CONFIG_PLLPWD_MASK) >> PCIE_PLL_CONFIG_PLLPWD_LSB)
#define PCIE_PLL_CONFIG_PLLPWD_SET(x)                                (((x) << PCIE_PLL_CONFIG_PLLPWD_LSB) & PCIE_PLL_CONFIG_PLLPWD_MASK)
#define PCIE_PLL_CONFIG_PLLPWD_RESET                                 1
#define PCIE_PLL_CONFIG_BYPASS_MSB                                   16
#define PCIE_PLL_CONFIG_BYPASS_LSB                                   16
#define PCIE_PLL_CONFIG_BYPASS_MASK                                  0x00010000
#define PCIE_PLL_CONFIG_BYPASS_GET(x)                                (((x) & PCIE_PLL_CONFIG_BYPASS_MASK) >> PCIE_PLL_CONFIG_BYPASS_LSB)
#define PCIE_PLL_CONFIG_BYPASS_SET(x)                                (((x) << PCIE_PLL_CONFIG_BYPASS_LSB) & PCIE_PLL_CONFIG_BYPASS_MASK)
#define PCIE_PLL_CONFIG_BYPASS_RESET                                 1
#define PCIE_PLL_CONFIG_REFDIV_MSB                                   14
#define PCIE_PLL_CONFIG_REFDIV_LSB                                   10
#define PCIE_PLL_CONFIG_REFDIV_MASK                                  0x00007c00
#define PCIE_PLL_CONFIG_REFDIV_GET(x)                                (((x) & PCIE_PLL_CONFIG_REFDIV_MASK) >> PCIE_PLL_CONFIG_REFDIV_LSB)
#define PCIE_PLL_CONFIG_REFDIV_SET(x)                                (((x) << PCIE_PLL_CONFIG_REFDIV_LSB) & PCIE_PLL_CONFIG_REFDIV_MASK)
#define PCIE_PLL_CONFIG_REFDIV_RESET                                 1
#define PCIE_PLL_CONFIG_ADDRESS                                      0x0010
#define PCIE_PLL_CONFIG_OFFSET                                       0x0010
// SW modifiable bits
#define PCIE_PLL_CONFIG_SW_MASK                                      0xc0017c00
// bits defined at reset
#define PCIE_PLL_CONFIG_RSTMASK                                      0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PLL_CONFIG_RESET                                        0x40010400

// 32'h0014 (PCIE_PLL_DITHER_DIV_MAX)
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MSB                        31
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB                        31
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK                       0x80000000
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_GET(x)                     (((x) & PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK) >> PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_SET(x)                     (((x) << PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB) & PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_RESET                      1
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MSB                          30
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB                          30
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK                         0x40000000
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_GET(x)                       (((x) & PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK) >> PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_SET(x)                       (((x) << PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB) & PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_RESET                        1
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MSB                      20
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB                      15
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK                     0x001f8000
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_GET(x)                   (((x) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK) >> PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_SET(x)                   (((x) << PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_RESET                    19
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MSB                     14
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB                     1
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK                    0x00007ffe
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_GET(x)                  (((x) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK) >> PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_SET(x)                  (((x) << PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_RESET                   16383
#define PCIE_PLL_DITHER_DIV_MAX_ADDRESS                              0x0014
#define PCIE_PLL_DITHER_DIV_MAX_OFFSET                               0x0014
// SW modifiable bits
#define PCIE_PLL_DITHER_DIV_MAX_SW_MASK                              0xc01ffffe
// bits defined at reset
#define PCIE_PLL_DITHER_DIV_MAX_RSTMASK                              0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PLL_DITHER_DIV_MAX_RESET                                0xc009fffe

// 32'h0018 (PCIE_PLL_DITHER_DIV_MIN)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MSB                      20
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB                      15
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK                     0x001f8000
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_GET(x)                   (((x) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK) >> PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_SET(x)                   (((x) << PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_RESET                    19
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MSB                     14
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB                     1
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK                    0x00007ffe
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_GET(x)                  (((x) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK) >> PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_SET(x)                  (((x) << PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_RESET                   14749
#define PCIE_PLL_DITHER_DIV_MIN_ADDRESS                              0x0018
#define PCIE_PLL_DITHER_DIV_MIN_OFFSET                               0x0018
// SW modifiable bits
#define PCIE_PLL_DITHER_DIV_MIN_SW_MASK                              0x001ffffe
// bits defined at reset
#define PCIE_PLL_DITHER_DIV_MIN_RSTMASK                              0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PLL_DITHER_DIV_MIN_RESET                                0x0009f33a

// 32'h001c (PCIE_PLL_DITHER_STEP)
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_MSB                          31
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB                          28
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK                         0xf0000000
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_GET(x)                       (((x) & PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK) >> PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB)
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_SET(x)                       (((x) << PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB) & PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK)
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_RESET                        0
#define PCIE_PLL_DITHER_STEP_STEP_INT_MSB                            24
#define PCIE_PLL_DITHER_STEP_STEP_INT_LSB                            15
#define PCIE_PLL_DITHER_STEP_STEP_INT_MASK                           0x01ff8000
#define PCIE_PLL_DITHER_STEP_STEP_INT_GET(x)                         (((x) & PCIE_PLL_DITHER_STEP_STEP_INT_MASK) >> PCIE_PLL_DITHER_STEP_STEP_INT_LSB)
#define PCIE_PLL_DITHER_STEP_STEP_INT_SET(x)                         (((x) << PCIE_PLL_DITHER_STEP_STEP_INT_LSB) & PCIE_PLL_DITHER_STEP_STEP_INT_MASK)
#define PCIE_PLL_DITHER_STEP_STEP_INT_RESET                          0
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_MSB                           14
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB                           1
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK                          0x00007ffe
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_GET(x)                        (((x) & PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK) >> PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB)
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_SET(x)                        (((x) << PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB) & PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK)
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_RESET                         10
#define PCIE_PLL_DITHER_STEP_ADDRESS                                 0x001c
#define PCIE_PLL_DITHER_STEP_OFFSET                                  0x001c
// SW modifiable bits
#define PCIE_PLL_DITHER_STEP_SW_MASK                                 0xf1fffffe
// bits defined at reset
#define PCIE_PLL_DITHER_STEP_RSTMASK                                 0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PLL_DITHER_STEP_RESET                                   0x00000014

// 32'h0020 (LDO_POWER_CONTROL)
#define LDO_POWER_CONTROL_PKG_SEL_MSB                                5
#define LDO_POWER_CONTROL_PKG_SEL_LSB                                5
#define LDO_POWER_CONTROL_PKG_SEL_MASK                               0x00000020
#define LDO_POWER_CONTROL_PKG_SEL_GET(x)                             (((x) & LDO_POWER_CONTROL_PKG_SEL_MASK) >> LDO_POWER_CONTROL_PKG_SEL_LSB)
#define LDO_POWER_CONTROL_PKG_SEL_SET(x)                             (((x) << LDO_POWER_CONTROL_PKG_SEL_LSB) & LDO_POWER_CONTROL_PKG_SEL_MASK)
#define LDO_POWER_CONTROL_PKG_SEL_RESET                              0
#define LDO_POWER_CONTROL_PWDLDO_CPU_MSB                             4
#define LDO_POWER_CONTROL_PWDLDO_CPU_LSB                             4
#define LDO_POWER_CONTROL_PWDLDO_CPU_MASK                            0x00000010
#define LDO_POWER_CONTROL_PWDLDO_CPU_GET(x)                          (((x) & LDO_POWER_CONTROL_PWDLDO_CPU_MASK) >> LDO_POWER_CONTROL_PWDLDO_CPU_LSB)
#define LDO_POWER_CONTROL_PWDLDO_CPU_SET(x)                          (((x) << LDO_POWER_CONTROL_PWDLDO_CPU_LSB) & LDO_POWER_CONTROL_PWDLDO_CPU_MASK)
#define LDO_POWER_CONTROL_PWDLDO_CPU_RESET                           0
#define LDO_POWER_CONTROL_PWDLDO_DDR_MSB                             3
#define LDO_POWER_CONTROL_PWDLDO_DDR_LSB                             3
#define LDO_POWER_CONTROL_PWDLDO_DDR_MASK                            0x00000008
#define LDO_POWER_CONTROL_PWDLDO_DDR_GET(x)                          (((x) & LDO_POWER_CONTROL_PWDLDO_DDR_MASK) >> LDO_POWER_CONTROL_PWDLDO_DDR_LSB)
#define LDO_POWER_CONTROL_PWDLDO_DDR_SET(x)                          (((x) << LDO_POWER_CONTROL_PWDLDO_DDR_LSB) & LDO_POWER_CONTROL_PWDLDO_DDR_MASK)
#define LDO_POWER_CONTROL_PWDLDO_DDR_RESET                           0
#define LDO_POWER_CONTROL_CPU_REFSEL_MSB                             2
#define LDO_POWER_CONTROL_CPU_REFSEL_LSB                             1
#define LDO_POWER_CONTROL_CPU_REFSEL_MASK                            0x00000006
#define LDO_POWER_CONTROL_CPU_REFSEL_GET(x)                          (((x) & LDO_POWER_CONTROL_CPU_REFSEL_MASK) >> LDO_POWER_CONTROL_CPU_REFSEL_LSB)
#define LDO_POWER_CONTROL_CPU_REFSEL_SET(x)                          (((x) << LDO_POWER_CONTROL_CPU_REFSEL_LSB) & LDO_POWER_CONTROL_CPU_REFSEL_MASK)
#define LDO_POWER_CONTROL_CPU_REFSEL_RESET                           3
#define LDO_POWER_CONTROL_SELECT_DDR1_MSB                            0
#define LDO_POWER_CONTROL_SELECT_DDR1_LSB                            0
#define LDO_POWER_CONTROL_SELECT_DDR1_MASK                           0x00000001
#define LDO_POWER_CONTROL_SELECT_DDR1_GET(x)                         (((x) & LDO_POWER_CONTROL_SELECT_DDR1_MASK) >> LDO_POWER_CONTROL_SELECT_DDR1_LSB)
#define LDO_POWER_CONTROL_SELECT_DDR1_SET(x)                         (((x) << LDO_POWER_CONTROL_SELECT_DDR1_LSB) & LDO_POWER_CONTROL_SELECT_DDR1_MASK)
#define LDO_POWER_CONTROL_SELECT_DDR1_RESET                          0
#define LDO_POWER_CONTROL_ADDRESS                                    0x0020
#define LDO_POWER_CONTROL_OFFSET                                     0x0020
// SW modifiable bits
#define LDO_POWER_CONTROL_SW_MASK                                    0x0000003f
// bits defined at reset
#define LDO_POWER_CONTROL_RSTMASK                                    0xffffffff
// reset value (ignore bits undefined at reset)
#define LDO_POWER_CONTROL_RESET                                      0x00000006

// 32'h0024 (SWITCH_CLOCK_SPARE)
#define SWITCH_CLOCK_SPARE_SPARE_MSB                                 31
#define SWITCH_CLOCK_SPARE_SPARE_LSB                                 12
#define SWITCH_CLOCK_SPARE_SPARE_MASK                                0xfffff000
#define SWITCH_CLOCK_SPARE_SPARE_GET(x)                              (((x) & SWITCH_CLOCK_SPARE_SPARE_MASK) >> SWITCH_CLOCK_SPARE_SPARE_LSB)
#define SWITCH_CLOCK_SPARE_SPARE_SET(x)                              (((x) << SWITCH_CLOCK_SPARE_SPARE_LSB) & SWITCH_CLOCK_SPARE_SPARE_MASK)
#define SWITCH_CLOCK_SPARE_SPARE_RESET                               0
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MSB                   11
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB                   8
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK                  0x00000f00
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_GET(x)                (((x) & SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK) >> SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB)
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(x)                (((x) << SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB) & SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK)
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_RESET                 5
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MSB                         7
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB                         7
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK                        0x00000080
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_GET(x)                      (((x) & SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_SET(x)                      (((x) << SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_RESET                       0
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MSB                          6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB                          6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK                         0x00000040
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_GET(x)                       (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_SET(x)                       (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_RESET                        0
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MSB                       5
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB                       5
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK                      0x00000020
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK) >> SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB)
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB) & SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK)
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_RESET                     1
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_MSB                            4
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB                            4
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK                           0x00000010
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_GET(x)                         (((x) & SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK) >> SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB)
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_SET(x)                         (((x) << SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB) & SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK)
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_RESET                          1
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_MSB                            3
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB                            3
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK                           0x00000008
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_GET(x)                         (((x) & SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK) >> SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB)
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_SET(x)                         (((x) << SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB) & SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK)
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_RESET                          0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MSB             2
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB             2
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK            0x00000004
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_GET(x)          (((x) & SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK) >> SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_SET(x)          (((x) << SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB) & SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_RESET           0
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MSB                  1
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB                  1
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK                 0x00000002
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_GET(x)               (((x) & SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK) >> SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB)
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_SET(x)               (((x) << SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB) & SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK)
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_RESET                0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MSB                         0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB                         0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK                        0x00000001
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_GET(x)                      (((x) & SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_SET(x)                      (((x) << SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB) & SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_RESET                       1
#define SWITCH_CLOCK_SPARE_ADDRESS                                   0x0024
#define SWITCH_CLOCK_SPARE_OFFSET                                    0x0024
// SW modifiable bits
#define SWITCH_CLOCK_SPARE_SW_MASK                                   0xffffffff
// bits defined at reset
#define SWITCH_CLOCK_SPARE_RSTMASK                                   0xffffffff
// reset value (ignore bits undefined at reset)
#define SWITCH_CLOCK_SPARE_RESET                                     0x00000531

// 32'h0028 (CURRENT_PCIE_PLL_DITHER)
#define CURRENT_PCIE_PLL_DITHER_INT_MSB                              20
#define CURRENT_PCIE_PLL_DITHER_INT_LSB                              15
#define CURRENT_PCIE_PLL_DITHER_INT_MASK                             0x001f8000
#define CURRENT_PCIE_PLL_DITHER_INT_GET(x)                           (((x) & CURRENT_PCIE_PLL_DITHER_INT_MASK) >> CURRENT_PCIE_PLL_DITHER_INT_LSB)
#define CURRENT_PCIE_PLL_DITHER_INT_SET(x)                           (((x) << CURRENT_PCIE_PLL_DITHER_INT_LSB) & CURRENT_PCIE_PLL_DITHER_INT_MASK)
#define CURRENT_PCIE_PLL_DITHER_INT_RESET                            1
#define CURRENT_PCIE_PLL_DITHER_FRAC_MSB                             13
#define CURRENT_PCIE_PLL_DITHER_FRAC_LSB                             0
#define CURRENT_PCIE_PLL_DITHER_FRAC_MASK                            0x00003fff
#define CURRENT_PCIE_PLL_DITHER_FRAC_GET(x)                          (((x) & CURRENT_PCIE_PLL_DITHER_FRAC_MASK) >> CURRENT_PCIE_PLL_DITHER_FRAC_LSB)
#define CURRENT_PCIE_PLL_DITHER_FRAC_SET(x)                          (((x) << CURRENT_PCIE_PLL_DITHER_FRAC_LSB) & CURRENT_PCIE_PLL_DITHER_FRAC_MASK)
#define CURRENT_PCIE_PLL_DITHER_FRAC_RESET                           0
#define CURRENT_PCIE_PLL_DITHER_ADDRESS                              0x0028
#define CURRENT_PCIE_PLL_DITHER_OFFSET                               0x0028
// SW modifiable bits
#define CURRENT_PCIE_PLL_DITHER_SW_MASK                              0x001fbfff
// bits defined at reset
#define CURRENT_PCIE_PLL_DITHER_RSTMASK                              0xffffffff
// reset value (ignore bits undefined at reset)
#define CURRENT_PCIE_PLL_DITHER_RESET                                0x00008000

// 32'h002c (ETH_XMII)
#define ETH_XMII_TX_INVERT_MSB                                       31
#define ETH_XMII_TX_INVERT_LSB                                       31
#define ETH_XMII_TX_INVERT_MASK                                      0x80000000
#define ETH_XMII_TX_INVERT_GET(x)                                    (((x) & ETH_XMII_TX_INVERT_MASK) >> ETH_XMII_TX_INVERT_LSB)
#define ETH_XMII_TX_INVERT_SET(x)                                    (((x) << ETH_XMII_TX_INVERT_LSB) & ETH_XMII_TX_INVERT_MASK)
#define ETH_XMII_TX_INVERT_RESET                                     0
#define ETH_XMII_GIGE_QUAD_MSB                                       30
#define ETH_XMII_GIGE_QUAD_LSB                                       30
#define ETH_XMII_GIGE_QUAD_MASK                                      0x40000000
#define ETH_XMII_GIGE_QUAD_GET(x)                                    (((x) & ETH_XMII_GIGE_QUAD_MASK) >> ETH_XMII_GIGE_QUAD_LSB)
#define ETH_XMII_GIGE_QUAD_SET(x)                                    (((x) << ETH_XMII_GIGE_QUAD_LSB) & ETH_XMII_GIGE_QUAD_MASK)
#define ETH_XMII_GIGE_QUAD_RESET                                     0
#define ETH_XMII_RX_DELAY_MSB                                        29
#define ETH_XMII_RX_DELAY_LSB                                        28
#define ETH_XMII_RX_DELAY_MASK                                       0x30000000
#define ETH_XMII_RX_DELAY_GET(x)                                     (((x) & ETH_XMII_RX_DELAY_MASK) >> ETH_XMII_RX_DELAY_LSB)
#define ETH_XMII_RX_DELAY_SET(x)                                     (((x) << ETH_XMII_RX_DELAY_LSB) & ETH_XMII_RX_DELAY_MASK)
#define ETH_XMII_RX_DELAY_RESET                                      0
#define ETH_XMII_TX_DELAY_MSB                                        27
#define ETH_XMII_TX_DELAY_LSB                                        26
#define ETH_XMII_TX_DELAY_MASK                                       0x0c000000
#define ETH_XMII_TX_DELAY_GET(x)                                     (((x) & ETH_XMII_TX_DELAY_MASK) >> ETH_XMII_TX_DELAY_LSB)
#define ETH_XMII_TX_DELAY_SET(x)                                     (((x) << ETH_XMII_TX_DELAY_LSB) & ETH_XMII_TX_DELAY_MASK)
#define ETH_XMII_TX_DELAY_RESET                                      0
#define ETH_XMII_GIGE_MSB                                            25
#define ETH_XMII_GIGE_LSB                                            25
#define ETH_XMII_GIGE_MASK                                           0x02000000
#define ETH_XMII_GIGE_GET(x)                                         (((x) & ETH_XMII_GIGE_MASK) >> ETH_XMII_GIGE_LSB)
#define ETH_XMII_GIGE_SET(x)                                         (((x) << ETH_XMII_GIGE_LSB) & ETH_XMII_GIGE_MASK)
#define ETH_XMII_GIGE_RESET                                          0
#define ETH_XMII_OFFSET_PHASE_MSB                                    24
#define ETH_XMII_OFFSET_PHASE_LSB                                    24
#define ETH_XMII_OFFSET_PHASE_MASK                                   0x01000000
#define ETH_XMII_OFFSET_PHASE_GET(x)                                 (((x) & ETH_XMII_OFFSET_PHASE_MASK) >> ETH_XMII_OFFSET_PHASE_LSB)
#define ETH_XMII_OFFSET_PHASE_SET(x)                                 (((x) << ETH_XMII_OFFSET_PHASE_LSB) & ETH_XMII_OFFSET_PHASE_MASK)
#define ETH_XMII_OFFSET_PHASE_RESET                                  0
#define ETH_XMII_OFFSET_COUNT_MSB                                    23
#define ETH_XMII_OFFSET_COUNT_LSB                                    16
#define ETH_XMII_OFFSET_COUNT_MASK                                   0x00ff0000
#define ETH_XMII_OFFSET_COUNT_GET(x)                                 (((x) & ETH_XMII_OFFSET_COUNT_MASK) >> ETH_XMII_OFFSET_COUNT_LSB)
#define ETH_XMII_OFFSET_COUNT_SET(x)                                 (((x) << ETH_XMII_OFFSET_COUNT_LSB) & ETH_XMII_OFFSET_COUNT_MASK)
#define ETH_XMII_OFFSET_COUNT_RESET                                  0
#define ETH_XMII_PHASE1_COUNT_MSB                                    15
#define ETH_XMII_PHASE1_COUNT_LSB                                    8
#define ETH_XMII_PHASE1_COUNT_MASK                                   0x0000ff00
#define ETH_XMII_PHASE1_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE1_COUNT_MASK) >> ETH_XMII_PHASE1_COUNT_LSB)
#define ETH_XMII_PHASE1_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE1_COUNT_LSB) & ETH_XMII_PHASE1_COUNT_MASK)
#define ETH_XMII_PHASE1_COUNT_RESET                                  1
#define ETH_XMII_PHASE0_COUNT_MSB                                    7
#define ETH_XMII_PHASE0_COUNT_LSB                                    0
#define ETH_XMII_PHASE0_COUNT_MASK                                   0x000000ff
#define ETH_XMII_PHASE0_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE0_COUNT_MASK) >> ETH_XMII_PHASE0_COUNT_LSB)
#define ETH_XMII_PHASE0_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE0_COUNT_LSB) & ETH_XMII_PHASE0_COUNT_MASK)
#define ETH_XMII_PHASE0_COUNT_RESET                                  1
#define ETH_XMII_ADDRESS                                             0x002c
#define ETH_XMII_OFFSET                                              0x002c
// SW modifiable bits
#define ETH_XMII_SW_MASK                                             0xffffffff
// bits defined at reset
#define ETH_XMII_RSTMASK                                             0xffffffff
// reset value (ignore bits undefined at reset)
#define ETH_XMII_RESET                                               0x00000101

// 32'h0030 (AUDIO_PLL_CONFIG)
#define AUDIO_PLL_CONFIG_UPDATING_MSB                                31
#define AUDIO_PLL_CONFIG_UPDATING_LSB                                31
#define AUDIO_PLL_CONFIG_UPDATING_MASK                               0x80000000
#define AUDIO_PLL_CONFIG_UPDATING_GET(x)                             (((x) & AUDIO_PLL_CONFIG_UPDATING_MASK) >> AUDIO_PLL_CONFIG_UPDATING_LSB)
#define AUDIO_PLL_CONFIG_UPDATING_SET(x)                             (((x) << AUDIO_PLL_CONFIG_UPDATING_LSB) & AUDIO_PLL_CONFIG_UPDATING_MASK)
#define AUDIO_PLL_CONFIG_UPDATING_RESET                              1
#define AUDIO_PLL_CONFIG_EXT_DIV_MSB                                 14
#define AUDIO_PLL_CONFIG_EXT_DIV_LSB                                 12
#define AUDIO_PLL_CONFIG_EXT_DIV_MASK                                0x00007000
#define AUDIO_PLL_CONFIG_EXT_DIV_GET(x)                              (((x) & AUDIO_PLL_CONFIG_EXT_DIV_MASK) >> AUDIO_PLL_CONFIG_EXT_DIV_LSB)
#define AUDIO_PLL_CONFIG_EXT_DIV_SET(x)                              (((x) << AUDIO_PLL_CONFIG_EXT_DIV_LSB) & AUDIO_PLL_CONFIG_EXT_DIV_MASK)
#define AUDIO_PLL_CONFIG_EXT_DIV_RESET                               1
#define AUDIO_PLL_CONFIG_POSTPLLDIV_MSB                              9
#define AUDIO_PLL_CONFIG_POSTPLLDIV_LSB                              7
#define AUDIO_PLL_CONFIG_POSTPLLDIV_MASK                             0x00000380
#define AUDIO_PLL_CONFIG_POSTPLLDIV_GET(x)                           (((x) & AUDIO_PLL_CONFIG_POSTPLLDIV_MASK) >> AUDIO_PLL_CONFIG_POSTPLLDIV_LSB)
#define AUDIO_PLL_CONFIG_POSTPLLDIV_SET(x)                           (((x) << AUDIO_PLL_CONFIG_POSTPLLDIV_LSB) & AUDIO_PLL_CONFIG_POSTPLLDIV_MASK)
#define AUDIO_PLL_CONFIG_POSTPLLDIV_RESET                            1
#define AUDIO_PLL_CONFIG_PLLPWD_MSB                                  5
#define AUDIO_PLL_CONFIG_PLLPWD_LSB                                  5
#define AUDIO_PLL_CONFIG_PLLPWD_MASK                                 0x00000020
#define AUDIO_PLL_CONFIG_PLLPWD_GET(x)                               (((x) & AUDIO_PLL_CONFIG_PLLPWD_MASK) >> AUDIO_PLL_CONFIG_PLLPWD_LSB)
#define AUDIO_PLL_CONFIG_PLLPWD_SET(x)                               (((x) << AUDIO_PLL_CONFIG_PLLPWD_LSB) & AUDIO_PLL_CONFIG_PLLPWD_MASK)
#define AUDIO_PLL_CONFIG_PLLPWD_RESET                                1
#define AUDIO_PLL_CONFIG_BYPASS_MSB                                  4
#define AUDIO_PLL_CONFIG_BYPASS_LSB                                  4
#define AUDIO_PLL_CONFIG_BYPASS_MASK                                 0x00000010
#define AUDIO_PLL_CONFIG_BYPASS_GET(x)                               (((x) & AUDIO_PLL_CONFIG_BYPASS_MASK) >> AUDIO_PLL_CONFIG_BYPASS_LSB)
#define AUDIO_PLL_CONFIG_BYPASS_SET(x)                               (((x) << AUDIO_PLL_CONFIG_BYPASS_LSB) & AUDIO_PLL_CONFIG_BYPASS_MASK)
#define AUDIO_PLL_CONFIG_BYPASS_RESET                                1
#define AUDIO_PLL_CONFIG_REFDIV_MSB                                  3
#define AUDIO_PLL_CONFIG_REFDIV_LSB                                  0
#define AUDIO_PLL_CONFIG_REFDIV_MASK                                 0x0000000f
#define AUDIO_PLL_CONFIG_REFDIV_GET(x)                               (((x) & AUDIO_PLL_CONFIG_REFDIV_MASK) >> AUDIO_PLL_CONFIG_REFDIV_LSB)
#define AUDIO_PLL_CONFIG_REFDIV_SET(x)                               (((x) << AUDIO_PLL_CONFIG_REFDIV_LSB) & AUDIO_PLL_CONFIG_REFDIV_MASK)
#define AUDIO_PLL_CONFIG_REFDIV_RESET                                3
#define AUDIO_PLL_CONFIG_ADDRESS                                     0x0030
#define AUDIO_PLL_CONFIG_OFFSET                                      0x0030
// SW modifiable bits
#define AUDIO_PLL_CONFIG_SW_MASK                                     0x800073bf
// bits defined at reset
#define AUDIO_PLL_CONFIG_RSTMASK                                     0xffffffff
// reset value (ignore bits undefined at reset)
#define AUDIO_PLL_CONFIG_RESET                                       0x800010b3

// 32'h0034 (AUDIO_PLL_MODULATION)
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MSB                        28
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB                        11
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK                       0x1ffff800
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_GET(x)                     (((x) & AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK) >> AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB)
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_SET(x)                     (((x) << AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB) & AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK)
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_RESET                      84222
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_MSB                         6
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB                         1
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK                        0x0000007e
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_GET(x)                      (((x) & AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK) >> AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB)
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_SET(x)                      (((x) << AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB) & AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK)
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_RESET                       20
#define AUDIO_PLL_MODULATION_START_MSB                               0
#define AUDIO_PLL_MODULATION_START_LSB                               0
#define AUDIO_PLL_MODULATION_START_MASK                              0x00000001
#define AUDIO_PLL_MODULATION_START_GET(x)                            (((x) & AUDIO_PLL_MODULATION_START_MASK) >> AUDIO_PLL_MODULATION_START_LSB)
#define AUDIO_PLL_MODULATION_START_SET(x)                            (((x) << AUDIO_PLL_MODULATION_START_LSB) & AUDIO_PLL_MODULATION_START_MASK)
#define AUDIO_PLL_MODULATION_START_RESET                             0
#define AUDIO_PLL_MODULATION_ADDRESS                                 0x0034
#define AUDIO_PLL_MODULATION_OFFSET                                  0x0034
// SW modifiable bits
#define AUDIO_PLL_MODULATION_SW_MASK                                 0x1ffff87f
// bits defined at reset
#define AUDIO_PLL_MODULATION_RSTMASK                                 0xffffffff
// reset value (ignore bits undefined at reset)
#define AUDIO_PLL_MODULATION_RESET                                   0x0a47f028

// 32'h0038 (AUDIO_PLL_MOD_STEP)
#define AUDIO_PLL_MOD_STEP_FRAC_MSB                                  31
#define AUDIO_PLL_MOD_STEP_FRAC_LSB                                  14
#define AUDIO_PLL_MOD_STEP_FRAC_MASK                                 0xffffc000
#define AUDIO_PLL_MOD_STEP_FRAC_GET(x)                               (((x) & AUDIO_PLL_MOD_STEP_FRAC_MASK) >> AUDIO_PLL_MOD_STEP_FRAC_LSB)
#define AUDIO_PLL_MOD_STEP_FRAC_SET(x)                               (((x) << AUDIO_PLL_MOD_STEP_FRAC_LSB) & AUDIO_PLL_MOD_STEP_FRAC_MASK)
#define AUDIO_PLL_MOD_STEP_FRAC_RESET                                1
#define AUDIO_PLL_MOD_STEP_INT_MSB                                   13
#define AUDIO_PLL_MOD_STEP_INT_LSB                                   4
#define AUDIO_PLL_MOD_STEP_INT_MASK                                  0x00003ff0
#define AUDIO_PLL_MOD_STEP_INT_GET(x)                                (((x) & AUDIO_PLL_MOD_STEP_INT_MASK) >> AUDIO_PLL_MOD_STEP_INT_LSB)
#define AUDIO_PLL_MOD_STEP_INT_SET(x)                                (((x) << AUDIO_PLL_MOD_STEP_INT_LSB) & AUDIO_PLL_MOD_STEP_INT_MASK)
#define AUDIO_PLL_MOD_STEP_INT_RESET                                 0
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_MSB                            3
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB                            0
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK                           0x0000000f
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_GET(x)                         (((x) & AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK) >> AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB)
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_SET(x)                         (((x) << AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB) & AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK)
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_RESET                          0
#define AUDIO_PLL_MOD_STEP_ADDRESS                                   0x0038
#define AUDIO_PLL_MOD_STEP_OFFSET                                    0x0038
// SW modifiable bits
#define AUDIO_PLL_MOD_STEP_SW_MASK                                   0xffffffff
// bits defined at reset
#define AUDIO_PLL_MOD_STEP_RSTMASK                                   0xffffffff
// reset value (ignore bits undefined at reset)
#define AUDIO_PLL_MOD_STEP_RESET                                     0x00004000

// 32'h003c (CURRENT_AUDIO_PLL_MODULATION)
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_MSB                        27
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB                        10
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK                       0x0ffffc00
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_GET(x)                     (((x) & CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK) >> CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB)
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_SET(x)                     (((x) << CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB) & CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK)
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_RESET                      1
#define CURRENT_AUDIO_PLL_MODULATION_INT_MSB                         6
#define CURRENT_AUDIO_PLL_MODULATION_INT_LSB                         1
#define CURRENT_AUDIO_PLL_MODULATION_INT_MASK                        0x0000007e
#define CURRENT_AUDIO_PLL_MODULATION_INT_GET(x)                      (((x) & CURRENT_AUDIO_PLL_MODULATION_INT_MASK) >> CURRENT_AUDIO_PLL_MODULATION_INT_LSB)
#define CURRENT_AUDIO_PLL_MODULATION_INT_SET(x)                      (((x) << CURRENT_AUDIO_PLL_MODULATION_INT_LSB) & CURRENT_AUDIO_PLL_MODULATION_INT_MASK)
#define CURRENT_AUDIO_PLL_MODULATION_INT_RESET                       0
#define CURRENT_AUDIO_PLL_MODULATION_ADDRESS                         0x003c
#define CURRENT_AUDIO_PLL_MODULATION_OFFSET                          0x003c
// SW modifiable bits
#define CURRENT_AUDIO_PLL_MODULATION_SW_MASK                         0x0ffffc7e
// bits defined at reset
#define CURRENT_AUDIO_PLL_MODULATION_RSTMASK                         0xffffffff
// reset value (ignore bits undefined at reset)
#define CURRENT_AUDIO_PLL_MODULATION_RESET                           0x00000400

#define RST_BOOTSTRAP_ADDRESS                                        0x180600b0

// 32'h0040 (BB_PLL_CONFIG)
#define BB_PLL_CONFIG_UPDATING_MSB                                   31
#define BB_PLL_CONFIG_UPDATING_LSB                                   31
#define BB_PLL_CONFIG_UPDATING_MASK                                  0x80000000
#define BB_PLL_CONFIG_UPDATING_GET(x)                                (((x) & BB_PLL_CONFIG_UPDATING_MASK) >> BB_PLL_CONFIG_UPDATING_LSB)
#define BB_PLL_CONFIG_UPDATING_SET(x)                                (((x) << BB_PLL_CONFIG_UPDATING_LSB) & BB_PLL_CONFIG_UPDATING_MASK)
#define BB_PLL_CONFIG_UPDATING_RESET                                 1
#define BB_PLL_CONFIG_PLLPWD_MSB                                     30
#define BB_PLL_CONFIG_PLLPWD_LSB                                     30
#define BB_PLL_CONFIG_PLLPWD_MASK                                    0x40000000
#define BB_PLL_CONFIG_PLLPWD_GET(x)                                  (((x) & BB_PLL_CONFIG_PLLPWD_MASK) >> BB_PLL_CONFIG_PLLPWD_LSB)
#define BB_PLL_CONFIG_PLLPWD_SET(x)                                  (((x) << BB_PLL_CONFIG_PLLPWD_LSB) & BB_PLL_CONFIG_PLLPWD_MASK)
#define BB_PLL_CONFIG_PLLPWD_RESET                                   1
#define BB_PLL_CONFIG_SPARE_MSB                                      29
#define BB_PLL_CONFIG_SPARE_LSB                                      29
#define BB_PLL_CONFIG_SPARE_MASK                                     0x20000000
#define BB_PLL_CONFIG_SPARE_GET(x)                                   (((x) & BB_PLL_CONFIG_SPARE_MASK) >> BB_PLL_CONFIG_SPARE_LSB)
#define BB_PLL_CONFIG_SPARE_SET(x)                                   (((x) << BB_PLL_CONFIG_SPARE_LSB) & BB_PLL_CONFIG_SPARE_MASK)
#define BB_PLL_CONFIG_SPARE_RESET                                    0
#define BB_PLL_CONFIG_REFDIV_MSB                                     28
#define BB_PLL_CONFIG_REFDIV_LSB                                     24
#define BB_PLL_CONFIG_REFDIV_MASK                                    0x1f000000
#define BB_PLL_CONFIG_REFDIV_GET(x)                                  (((x) & BB_PLL_CONFIG_REFDIV_MASK) >> BB_PLL_CONFIG_REFDIV_LSB)
#define BB_PLL_CONFIG_REFDIV_SET(x)                                  (((x) << BB_PLL_CONFIG_REFDIV_LSB) & BB_PLL_CONFIG_REFDIV_MASK)
#define BB_PLL_CONFIG_REFDIV_RESET                                   1
#define BB_PLL_CONFIG_NINT_MSB                                       21
#define BB_PLL_CONFIG_NINT_LSB                                       16
#define BB_PLL_CONFIG_NINT_MASK                                      0x003f0000
#define BB_PLL_CONFIG_NINT_GET(x)                                    (((x) & BB_PLL_CONFIG_NINT_MASK) >> BB_PLL_CONFIG_NINT_LSB)
#define BB_PLL_CONFIG_NINT_SET(x)                                    (((x) << BB_PLL_CONFIG_NINT_LSB) & BB_PLL_CONFIG_NINT_MASK)
#define BB_PLL_CONFIG_NINT_RESET                                     2
#define BB_PLL_CONFIG_NFRAC_MSB                                      13
#define BB_PLL_CONFIG_NFRAC_LSB                                      0
#define BB_PLL_CONFIG_NFRAC_MASK                                     0x00003fff
#define BB_PLL_CONFIG_NFRAC_GET(x)                                   (((x) & BB_PLL_CONFIG_NFRAC_MASK) >> BB_PLL_CONFIG_NFRAC_LSB)
#define BB_PLL_CONFIG_NFRAC_SET(x)                                   (((x) << BB_PLL_CONFIG_NFRAC_LSB) & BB_PLL_CONFIG_NFRAC_MASK)
#define BB_PLL_CONFIG_NFRAC_RESET                                    3276
#define BB_PLL_CONFIG_ADDRESS                                        0x0040
#define BB_PLL_CONFIG_OFFSET                                         0x0040
// SW modifiable bits
#define BB_PLL_CONFIG_SW_MASK                                        0xff3f3fff
// bits defined at reset
#define BB_PLL_CONFIG_RSTMASK                                        0xffffffff
// reset value (ignore bits undefined at reset)
#define BB_PLL_CONFIG_RESET                                          0xc1020ccc

// 32'h0044 (DDR_PLL_DITHER)
#define DDR_PLL_DITHER_DITHER_EN_MSB                                 31
#define DDR_PLL_DITHER_DITHER_EN_LSB                                 31
#define DDR_PLL_DITHER_DITHER_EN_MASK                                0x80000000
#define DDR_PLL_DITHER_DITHER_EN_GET(x)                              (((x) & DDR_PLL_DITHER_DITHER_EN_MASK) >> DDR_PLL_DITHER_DITHER_EN_LSB)
#define DDR_PLL_DITHER_DITHER_EN_SET(x)                              (((x) << DDR_PLL_DITHER_DITHER_EN_LSB) & DDR_PLL_DITHER_DITHER_EN_MASK)
#define DDR_PLL_DITHER_DITHER_EN_RESET                               0
#define DDR_PLL_DITHER_UPDATE_COUNT_MSB                              30
#define DDR_PLL_DITHER_UPDATE_COUNT_LSB                              27
#define DDR_PLL_DITHER_UPDATE_COUNT_MASK                             0x78000000
#define DDR_PLL_DITHER_UPDATE_COUNT_GET(x)                           (((x) & DDR_PLL_DITHER_UPDATE_COUNT_MASK) >> DDR_PLL_DITHER_UPDATE_COUNT_LSB)
#define DDR_PLL_DITHER_UPDATE_COUNT_SET(x)                           (((x) << DDR_PLL_DITHER_UPDATE_COUNT_LSB) & DDR_PLL_DITHER_UPDATE_COUNT_MASK)
#define DDR_PLL_DITHER_UPDATE_COUNT_RESET                            15
#define DDR_PLL_DITHER_NFRAC_STEP_MSB                                26
#define DDR_PLL_DITHER_NFRAC_STEP_LSB                                20
#define DDR_PLL_DITHER_NFRAC_STEP_MASK                               0x07f00000
#define DDR_PLL_DITHER_NFRAC_STEP_GET(x)                             (((x) & DDR_PLL_DITHER_NFRAC_STEP_MASK) >> DDR_PLL_DITHER_NFRAC_STEP_LSB)
#define DDR_PLL_DITHER_NFRAC_STEP_SET(x)                             (((x) << DDR_PLL_DITHER_NFRAC_STEP_LSB) & DDR_PLL_DITHER_NFRAC_STEP_MASK)
#define DDR_PLL_DITHER_NFRAC_STEP_RESET                              1
#define DDR_PLL_DITHER_NFRAC_MIN_MSB                                 19
#define DDR_PLL_DITHER_NFRAC_MIN_LSB                                 10
#define DDR_PLL_DITHER_NFRAC_MIN_MASK                                0x000ffc00
#define DDR_PLL_DITHER_NFRAC_MIN_GET(x)                              (((x) & DDR_PLL_DITHER_NFRAC_MIN_MASK) >> DDR_PLL_DITHER_NFRAC_MIN_LSB)
#define DDR_PLL_DITHER_NFRAC_MIN_SET(x)                              (((x) << DDR_PLL_DITHER_NFRAC_MIN_LSB) & DDR_PLL_DITHER_NFRAC_MIN_MASK)
#define DDR_PLL_DITHER_NFRAC_MIN_RESET                               25
#define DDR_PLL_DITHER_NFRAC_MAX_MSB                                 9
#define DDR_PLL_DITHER_NFRAC_MAX_LSB                                 0
#define DDR_PLL_DITHER_NFRAC_MAX_MASK                                0x000003ff
#define DDR_PLL_DITHER_NFRAC_MAX_GET(x)                              (((x) & DDR_PLL_DITHER_NFRAC_MAX_MASK) >> DDR_PLL_DITHER_NFRAC_MAX_LSB)
#define DDR_PLL_DITHER_NFRAC_MAX_SET(x)                              (((x) << DDR_PLL_DITHER_NFRAC_MAX_LSB) & DDR_PLL_DITHER_NFRAC_MAX_MASK)
#define DDR_PLL_DITHER_NFRAC_MAX_RESET                               1000
#define DDR_PLL_DITHER_ADDRESS                                       0x0044
#define DDR_PLL_DITHER_OFFSET                                        0x0044
// SW modifiable bits
#define DDR_PLL_DITHER_SW_MASK                                       0xffffffff
// bits defined at reset
#define DDR_PLL_DITHER_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define DDR_PLL_DITHER_RESET                                         0x781067e8

// 32'h0048 (CPU_PLL_DITHER)
#define CPU_PLL_DITHER_DITHER_EN_MSB                                 31
#define CPU_PLL_DITHER_DITHER_EN_LSB                                 31
#define CPU_PLL_DITHER_DITHER_EN_MASK                                0x80000000
#define CPU_PLL_DITHER_DITHER_EN_GET(x)                              (((x) & CPU_PLL_DITHER_DITHER_EN_MASK) >> CPU_PLL_DITHER_DITHER_EN_LSB)
#define CPU_PLL_DITHER_DITHER_EN_SET(x)                              (((x) << CPU_PLL_DITHER_DITHER_EN_LSB) & CPU_PLL_DITHER_DITHER_EN_MASK)
#define CPU_PLL_DITHER_DITHER_EN_RESET                               0
#define CPU_PLL_DITHER_UPDATE_COUNT_MSB                              23
#define CPU_PLL_DITHER_UPDATE_COUNT_LSB                              18
#define CPU_PLL_DITHER_UPDATE_COUNT_MASK                             0x00fc0000
#define CPU_PLL_DITHER_UPDATE_COUNT_GET(x)                           (((x) & CPU_PLL_DITHER_UPDATE_COUNT_MASK) >> CPU_PLL_DITHER_UPDATE_COUNT_LSB)
#define CPU_PLL_DITHER_UPDATE_COUNT_SET(x)                           (((x) << CPU_PLL_DITHER_UPDATE_COUNT_LSB) & CPU_PLL_DITHER_UPDATE_COUNT_MASK)
#define CPU_PLL_DITHER_UPDATE_COUNT_RESET                            20
#define CPU_PLL_DITHER_NFRAC_STEP_MSB                                17
#define CPU_PLL_DITHER_NFRAC_STEP_LSB                                12
#define CPU_PLL_DITHER_NFRAC_STEP_MASK                               0x0003f000
#define CPU_PLL_DITHER_NFRAC_STEP_GET(x)                             (((x) & CPU_PLL_DITHER_NFRAC_STEP_MASK) >> CPU_PLL_DITHER_NFRAC_STEP_LSB)
#define CPU_PLL_DITHER_NFRAC_STEP_SET(x)                             (((x) << CPU_PLL_DITHER_NFRAC_STEP_LSB) & CPU_PLL_DITHER_NFRAC_STEP_MASK)
#define CPU_PLL_DITHER_NFRAC_STEP_RESET                              1
#define CPU_PLL_DITHER_NFRAC_MIN_MSB                                 11
#define CPU_PLL_DITHER_NFRAC_MIN_LSB                                 6
#define CPU_PLL_DITHER_NFRAC_MIN_MASK                                0x00000fc0
#define CPU_PLL_DITHER_NFRAC_MIN_GET(x)                              (((x) & CPU_PLL_DITHER_NFRAC_MIN_MASK) >> CPU_PLL_DITHER_NFRAC_MIN_LSB)
#define CPU_PLL_DITHER_NFRAC_MIN_SET(x)                              (((x) << CPU_PLL_DITHER_NFRAC_MIN_LSB) & CPU_PLL_DITHER_NFRAC_MIN_MASK)
#define CPU_PLL_DITHER_NFRAC_MIN_RESET                               3
#define CPU_PLL_DITHER_NFRAC_MAX_MSB                                 5
#define CPU_PLL_DITHER_NFRAC_MAX_LSB                                 0
#define CPU_PLL_DITHER_NFRAC_MAX_MASK                                0x0000003f
#define CPU_PLL_DITHER_NFRAC_MAX_GET(x)                              (((x) & CPU_PLL_DITHER_NFRAC_MAX_MASK) >> CPU_PLL_DITHER_NFRAC_MAX_LSB)
#define CPU_PLL_DITHER_NFRAC_MAX_SET(x)                              (((x) << CPU_PLL_DITHER_NFRAC_MAX_LSB) & CPU_PLL_DITHER_NFRAC_MAX_MASK)
#define CPU_PLL_DITHER_NFRAC_MAX_RESET                               60
#define CPU_PLL_DITHER_ADDRESS                                       0x0048
#define CPU_PLL_DITHER_OFFSET                                        0x0048
// SW modifiable bits
#define CPU_PLL_DITHER_SW_MASK                                       0x80ffffff
// bits defined at reset
#define CPU_PLL_DITHER_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define CPU_PLL_DITHER_RESET                                         0x005010fc

// 32'h1806001c (RST_RESET)
#define RST_RESET_HOST_RESET_MSB                                     31
#define RST_RESET_HOST_RESET_LSB                                     31
#define RST_RESET_HOST_RESET_MASK                                    0x80000000
#define RST_RESET_HOST_RESET_GET(x)                                  (((x) & RST_RESET_HOST_RESET_MASK) >> RST_RESET_HOST_RESET_LSB)
#define RST_RESET_HOST_RESET_SET(x)                                  (((x) << RST_RESET_HOST_RESET_LSB) & RST_RESET_HOST_RESET_MASK)
#define RST_RESET_HOST_RESET_RESET                                   0
#define RST_RESET_SLIC_RESET_MSB                                     30
#define RST_RESET_SLIC_RESET_LSB                                     30
#define RST_RESET_SLIC_RESET_MASK                                    0x40000000
#define RST_RESET_SLIC_RESET_GET(x)                                  (((x) & RST_RESET_SLIC_RESET_MASK) >> RST_RESET_SLIC_RESET_LSB)
#define RST_RESET_SLIC_RESET_SET(x)                                  (((x) << RST_RESET_SLIC_RESET_LSB) & RST_RESET_SLIC_RESET_MASK)
#define RST_RESET_SLIC_RESET_RESET                                   0
#define RST_RESET_HDMA_RESET_MSB                                     29
#define RST_RESET_HDMA_RESET_LSB                                     29
#define RST_RESET_HDMA_RESET_MASK                                    0x20000000
#define RST_RESET_HDMA_RESET_GET(x)                                  (((x) & RST_RESET_HDMA_RESET_MASK) >> RST_RESET_HDMA_RESET_LSB)
#define RST_RESET_HDMA_RESET_SET(x)                                  (((x) << RST_RESET_HDMA_RESET_LSB) & RST_RESET_HDMA_RESET_MASK)
#define RST_RESET_HDMA_RESET_RESET                                   1
#define RST_RESET_EXTERNAL_RESET_MSB                                 28
#define RST_RESET_EXTERNAL_RESET_LSB                                 28
#define RST_RESET_EXTERNAL_RESET_MASK                                0x10000000
#define RST_RESET_EXTERNAL_RESET_GET(x)                              (((x) & RST_RESET_EXTERNAL_RESET_MASK) >> RST_RESET_EXTERNAL_RESET_LSB)
#define RST_RESET_EXTERNAL_RESET_SET(x)                              (((x) << RST_RESET_EXTERNAL_RESET_LSB) & RST_RESET_EXTERNAL_RESET_MASK)
#define RST_RESET_EXTERNAL_RESET_RESET                               0
#define RST_RESET_RTC_RESET_MSB                                      27
#define RST_RESET_RTC_RESET_LSB                                      27
#define RST_RESET_RTC_RESET_MASK                                     0x08000000
#define RST_RESET_RTC_RESET_GET(x)                                   (((x) & RST_RESET_RTC_RESET_MASK) >> RST_RESET_RTC_RESET_LSB)
#define RST_RESET_RTC_RESET_SET(x)                                   (((x) << RST_RESET_RTC_RESET_LSB) & RST_RESET_RTC_RESET_MASK)
#define RST_RESET_RTC_RESET_RESET                                    1
#define RST_RESET_PCIEEP_RST_INT_MSB                                 26
#define RST_RESET_PCIEEP_RST_INT_LSB                                 26
#define RST_RESET_PCIEEP_RST_INT_MASK                                0x04000000
#define RST_RESET_PCIEEP_RST_INT_GET(x)                              (((x) & RST_RESET_PCIEEP_RST_INT_MASK) >> RST_RESET_PCIEEP_RST_INT_LSB)
#define RST_RESET_PCIEEP_RST_INT_SET(x)                              (((x) << RST_RESET_PCIEEP_RST_INT_LSB) & RST_RESET_PCIEEP_RST_INT_MASK)
#define RST_RESET_PCIEEP_RST_INT_RESET                               0
#define RST_RESET_CHKSUM_ACC_RESET_MSB                               25
#define RST_RESET_CHKSUM_ACC_RESET_LSB                               25
#define RST_RESET_CHKSUM_ACC_RESET_MASK                              0x02000000
#define RST_RESET_CHKSUM_ACC_RESET_GET(x)                            (((x) & RST_RESET_CHKSUM_ACC_RESET_MASK) >> RST_RESET_CHKSUM_ACC_RESET_LSB)
#define RST_RESET_CHKSUM_ACC_RESET_SET(x)                            (((x) << RST_RESET_CHKSUM_ACC_RESET_LSB) & RST_RESET_CHKSUM_ACC_RESET_MASK)
#define RST_RESET_CHKSUM_ACC_RESET_RESET                             0
#define RST_RESET_FULL_CHIP_RESET_MSB                                24
#define RST_RESET_FULL_CHIP_RESET_LSB                                24
#define RST_RESET_FULL_CHIP_RESET_MASK                               0x01000000
#define RST_RESET_FULL_CHIP_RESET_GET(x)                             (((x) & RST_RESET_FULL_CHIP_RESET_MASK) >> RST_RESET_FULL_CHIP_RESET_LSB)
#define RST_RESET_FULL_CHIP_RESET_SET(x)                             (((x) << RST_RESET_FULL_CHIP_RESET_LSB) & RST_RESET_FULL_CHIP_RESET_MASK)
#define RST_RESET_FULL_CHIP_RESET_RESET                              0
#define RST_RESET_GE1_MDIO_RESET_MSB                                 23
#define RST_RESET_GE1_MDIO_RESET_LSB                                 23
#define RST_RESET_GE1_MDIO_RESET_MASK                                0x00800000
#define RST_RESET_GE1_MDIO_RESET_GET(x)                              (((x) & RST_RESET_GE1_MDIO_RESET_MASK) >> RST_RESET_GE1_MDIO_RESET_LSB)
#define RST_RESET_GE1_MDIO_RESET_SET(x)                              (((x) << RST_RESET_GE1_MDIO_RESET_LSB) & RST_RESET_GE1_MDIO_RESET_MASK)
#define RST_RESET_GE1_MDIO_RESET_RESET                               1
#define RST_RESET_GE0_MDIO_RESET_MSB                                 22
#define RST_RESET_GE0_MDIO_RESET_LSB                                 22
#define RST_RESET_GE0_MDIO_RESET_MASK                                0x00400000
#define RST_RESET_GE0_MDIO_RESET_GET(x)                              (((x) & RST_RESET_GE0_MDIO_RESET_MASK) >> RST_RESET_GE0_MDIO_RESET_LSB)
#define RST_RESET_GE0_MDIO_RESET_SET(x)                              (((x) << RST_RESET_GE0_MDIO_RESET_LSB) & RST_RESET_GE0_MDIO_RESET_MASK)
#define RST_RESET_GE0_MDIO_RESET_RESET                               1
#define RST_RESET_CPU_NMI_MSB                                        21
#define RST_RESET_CPU_NMI_LSB                                        21
#define RST_RESET_CPU_NMI_MASK                                       0x00200000
#define RST_RESET_CPU_NMI_GET(x)                                     (((x) & RST_RESET_CPU_NMI_MASK) >> RST_RESET_CPU_NMI_LSB)
#define RST_RESET_CPU_NMI_SET(x)                                     (((x) << RST_RESET_CPU_NMI_LSB) & RST_RESET_CPU_NMI_MASK)
#define RST_RESET_CPU_NMI_RESET                                      0
#define RST_RESET_CPU_COLD_RESET_MSB                                 20
#define RST_RESET_CPU_COLD_RESET_LSB                                 20
#define RST_RESET_CPU_COLD_RESET_MASK                                0x00100000
#define RST_RESET_CPU_COLD_RESET_GET(x)                              (((x) & RST_RESET_CPU_COLD_RESET_MASK) >> RST_RESET_CPU_COLD_RESET_LSB)
#define RST_RESET_CPU_COLD_RESET_SET(x)                              (((x) << RST_RESET_CPU_COLD_RESET_LSB) & RST_RESET_CPU_COLD_RESET_MASK)
#define RST_RESET_CPU_COLD_RESET_RESET                               0
#define RST_RESET_HOST_RESET_INT_MSB                                 19
#define RST_RESET_HOST_RESET_INT_LSB                                 19
#define RST_RESET_HOST_RESET_INT_MASK                                0x00080000
#define RST_RESET_HOST_RESET_INT_GET(x)                              (((x) & RST_RESET_HOST_RESET_INT_MASK) >> RST_RESET_HOST_RESET_INT_LSB)
#define RST_RESET_HOST_RESET_INT_SET(x)                              (((x) << RST_RESET_HOST_RESET_INT_LSB) & RST_RESET_HOST_RESET_INT_MASK)
#define RST_RESET_HOST_RESET_INT_RESET                               0
#define RST_RESET_PCIEEP_RESET_MSB                                   18
#define RST_RESET_PCIEEP_RESET_LSB                                   18
#define RST_RESET_PCIEEP_RESET_MASK                                  0x00040000
#define RST_RESET_PCIEEP_RESET_GET(x)                                (((x) & RST_RESET_PCIEEP_RESET_MASK) >> RST_RESET_PCIEEP_RESET_LSB)
#define RST_RESET_PCIEEP_RESET_SET(x)                                (((x) << RST_RESET_PCIEEP_RESET_LSB) & RST_RESET_PCIEEP_RESET_MASK)
#define RST_RESET_PCIEEP_RESET_RESET                                 0
#define RST_RESET_UART1_RESET_MSB                                    17
#define RST_RESET_UART1_RESET_LSB                                    17
#define RST_RESET_UART1_RESET_MASK                                   0x00020000
#define RST_RESET_UART1_RESET_GET(x)                                 (((x) & RST_RESET_UART1_RESET_MASK) >> RST_RESET_UART1_RESET_LSB)
#define RST_RESET_UART1_RESET_SET(x)                                 (((x) << RST_RESET_UART1_RESET_LSB) & RST_RESET_UART1_RESET_MASK)
#define RST_RESET_UART1_RESET_RESET                                  0
#define RST_RESET_DDR_RESET_MSB                                      16
#define RST_RESET_DDR_RESET_LSB                                      16
#define RST_RESET_DDR_RESET_MASK                                     0x00010000
#define RST_RESET_DDR_RESET_GET(x)                                   (((x) & RST_RESET_DDR_RESET_MASK) >> RST_RESET_DDR_RESET_LSB)
#define RST_RESET_DDR_RESET_SET(x)                                   (((x) << RST_RESET_DDR_RESET_LSB) & RST_RESET_DDR_RESET_MASK)
#define RST_RESET_DDR_RESET_RESET                                    0
#define RST_RESET_USB_PHY_PLL_PWD_EXT_MSB                            15
#define RST_RESET_USB_PHY_PLL_PWD_EXT_LSB                            15
#define RST_RESET_USB_PHY_PLL_PWD_EXT_MASK                           0x00008000
#define RST_RESET_USB_PHY_PLL_PWD_EXT_GET(x)                         (((x) & RST_RESET_USB_PHY_PLL_PWD_EXT_MASK) >> RST_RESET_USB_PHY_PLL_PWD_EXT_LSB)
#define RST_RESET_USB_PHY_PLL_PWD_EXT_SET(x)                         (((x) << RST_RESET_USB_PHY_PLL_PWD_EXT_LSB) & RST_RESET_USB_PHY_PLL_PWD_EXT_MASK)
#define RST_RESET_USB_PHY_PLL_PWD_EXT_RESET                          0
#define RST_RESET_NANDF_RESET_MSB                                    14
#define RST_RESET_NANDF_RESET_LSB                                    14
#define RST_RESET_NANDF_RESET_MASK                                   0x00004000
#define RST_RESET_NANDF_RESET_GET(x)                                 (((x) & RST_RESET_NANDF_RESET_MASK) >> RST_RESET_NANDF_RESET_LSB)
#define RST_RESET_NANDF_RESET_SET(x)                                 (((x) << RST_RESET_NANDF_RESET_LSB) & RST_RESET_NANDF_RESET_MASK)
#define RST_RESET_NANDF_RESET_RESET                                  1
#define RST_RESET_GE1_MAC_RESET_MSB                                  13
#define RST_RESET_GE1_MAC_RESET_LSB                                  13
#define RST_RESET_GE1_MAC_RESET_MASK                                 0x00002000
#define RST_RESET_GE1_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE1_MAC_RESET_MASK) >> RST_RESET_GE1_MAC_RESET_LSB)
#define RST_RESET_GE1_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE1_MAC_RESET_LSB) & RST_RESET_GE1_MAC_RESET_MASK)
#define RST_RESET_GE1_MAC_RESET_RESET                                1
#define RST_RESET_ETH_SWITCH_ARESET_MSB                              12
#define RST_RESET_ETH_SWITCH_ARESET_LSB                              12
#define RST_RESET_ETH_SWITCH_ARESET_MASK                             0x00001000
#define RST_RESET_ETH_SWITCH_ARESET_GET(x)                           (((x) & RST_RESET_ETH_SWITCH_ARESET_MASK) >> RST_RESET_ETH_SWITCH_ARESET_LSB)
#define RST_RESET_ETH_SWITCH_ARESET_SET(x)                           (((x) << RST_RESET_ETH_SWITCH_ARESET_LSB) & RST_RESET_ETH_SWITCH_ARESET_MASK)
#define RST_RESET_ETH_SWITCH_ARESET_RESET                            1
#define RST_RESET_USB_PHY_ARESET_MSB                                 11
#define RST_RESET_USB_PHY_ARESET_LSB                                 11
#define RST_RESET_USB_PHY_ARESET_MASK                                0x00000800
#define RST_RESET_USB_PHY_ARESET_GET(x)                              (((x) & RST_RESET_USB_PHY_ARESET_MASK) >> RST_RESET_USB_PHY_ARESET_LSB)
#define RST_RESET_USB_PHY_ARESET_SET(x)                              (((x) << RST_RESET_USB_PHY_ARESET_LSB) & RST_RESET_USB_PHY_ARESET_MASK)
#define RST_RESET_USB_PHY_ARESET_RESET                               1
#define RST_RESET_RESERVED_MSB                                       10
#define RST_RESET_RESERVED_LSB                                       10
#define RST_RESET_RESERVED_MASK                                      0x00000400
#define RST_RESET_RESERVED_GET(x)                                    (((x) & RST_RESET_RESERVED_MASK) >> RST_RESET_RESERVED_LSB)
#define RST_RESET_RESERVED_SET(x)                                    (((x) << RST_RESET_RESERVED_LSB) & RST_RESET_RESERVED_MASK)
#define RST_RESET_RESERVED_RESET                                     1
#define RST_RESET_GE0_MAC_RESET_MSB                                  9
#define RST_RESET_GE0_MAC_RESET_LSB                                  9
#define RST_RESET_GE0_MAC_RESET_MASK                                 0x00000200
#define RST_RESET_GE0_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE0_MAC_RESET_MASK) >> RST_RESET_GE0_MAC_RESET_LSB)
#define RST_RESET_GE0_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE0_MAC_RESET_LSB) & RST_RESET_GE0_MAC_RESET_MASK)
#define RST_RESET_GE0_MAC_RESET_RESET                                1
#define RST_RESET_ETH_SWITCH_RESET_MSB                               8
#define RST_RESET_ETH_SWITCH_RESET_LSB                               8
#define RST_RESET_ETH_SWITCH_RESET_MASK                              0x00000100
#define RST_RESET_ETH_SWITCH_RESET_GET(x)                            (((x) & RST_RESET_ETH_SWITCH_RESET_MASK) >> RST_RESET_ETH_SWITCH_RESET_LSB)
#define RST_RESET_ETH_SWITCH_RESET_SET(x)                            (((x) << RST_RESET_ETH_SWITCH_RESET_LSB) & RST_RESET_ETH_SWITCH_RESET_MASK)
#define RST_RESET_ETH_SWITCH_RESET_RESET                             1
#define RST_RESET_PCIE_PHY_RESET_MSB                                 7
#define RST_RESET_PCIE_PHY_RESET_LSB                                 7
#define RST_RESET_PCIE_PHY_RESET_MASK                                0x00000080
#define RST_RESET_PCIE_PHY_RESET_GET(x)                              (((x) & RST_RESET_PCIE_PHY_RESET_MASK) >> RST_RESET_PCIE_PHY_RESET_LSB)
#define RST_RESET_PCIE_PHY_RESET_SET(x)                              (((x) << RST_RESET_PCIE_PHY_RESET_LSB) & RST_RESET_PCIE_PHY_RESET_MASK)
#define RST_RESET_PCIE_PHY_RESET_RESET                               1
#define RST_RESET_PCIE_RESET_MSB                                     6
#define RST_RESET_PCIE_RESET_LSB                                     6
#define RST_RESET_PCIE_RESET_MASK                                    0x00000040
#define RST_RESET_PCIE_RESET_GET(x)                                  (((x) & RST_RESET_PCIE_RESET_MASK) >> RST_RESET_PCIE_RESET_LSB)
#define RST_RESET_PCIE_RESET_SET(x)                                  (((x) << RST_RESET_PCIE_RESET_LSB) & RST_RESET_PCIE_RESET_MASK)
#define RST_RESET_PCIE_RESET_RESET                                   1
#define RST_RESET_USB_HOST_RESET_MSB                                 5
#define RST_RESET_USB_HOST_RESET_LSB                                 5
#define RST_RESET_USB_HOST_RESET_MASK                                0x00000020
#define RST_RESET_USB_HOST_RESET_GET(x)                              (((x) & RST_RESET_USB_HOST_RESET_MASK) >> RST_RESET_USB_HOST_RESET_LSB)
#define RST_RESET_USB_HOST_RESET_SET(x)                              (((x) << RST_RESET_USB_HOST_RESET_LSB) & RST_RESET_USB_HOST_RESET_MASK)
#define RST_RESET_USB_HOST_RESET_RESET                               1
#define RST_RESET_USB_PHY_RESET_MSB                                  4
#define RST_RESET_USB_PHY_RESET_LSB                                  4
#define RST_RESET_USB_PHY_RESET_MASK                                 0x00000010
#define RST_RESET_USB_PHY_RESET_GET(x)                               (((x) & RST_RESET_USB_PHY_RESET_MASK) >> RST_RESET_USB_PHY_RESET_LSB)
#define RST_RESET_USB_PHY_RESET_SET(x)                               (((x) << RST_RESET_USB_PHY_RESET_LSB) & RST_RESET_USB_PHY_RESET_MASK)
#define RST_RESET_USB_PHY_RESET_RESET                                1
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MSB                       3
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB                       3
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK                      0x00000008
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_GET(x)                    (((x) & RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK) >> RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB)
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_SET(x)                    (((x) << RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB) & RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK)
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_RESET                     0
#define RST_RESET_LUT_RESET_MSB                                      2
#define RST_RESET_LUT_RESET_LSB                                      2
#define RST_RESET_LUT_RESET_MASK                                     0x00000004
#define RST_RESET_LUT_RESET_GET(x)                                   (((x) & RST_RESET_LUT_RESET_MASK) >> RST_RESET_LUT_RESET_LSB)
#define RST_RESET_LUT_RESET_SET(x)                                   (((x) << RST_RESET_LUT_RESET_LSB) & RST_RESET_LUT_RESET_MASK)
#define RST_RESET_LUT_RESET_RESET                                    0
#define RST_RESET_MBOX_RESET_MSB                                     1
#define RST_RESET_MBOX_RESET_LSB                                     1
#define RST_RESET_MBOX_RESET_MASK                                    0x00000002
#define RST_RESET_MBOX_RESET_GET(x)                                  (((x) & RST_RESET_MBOX_RESET_MASK) >> RST_RESET_MBOX_RESET_LSB)
#define RST_RESET_MBOX_RESET_SET(x)                                  (((x) << RST_RESET_MBOX_RESET_LSB) & RST_RESET_MBOX_RESET_MASK)
#define RST_RESET_MBOX_RESET_RESET                                   0
#define RST_RESET_I2S_RESET_MSB                                      0
#define RST_RESET_I2S_RESET_LSB                                      0
#define RST_RESET_I2S_RESET_MASK                                     0x00000001
#define RST_RESET_I2S_RESET_GET(x)                                   (((x) & RST_RESET_I2S_RESET_MASK) >> RST_RESET_I2S_RESET_LSB)
#define RST_RESET_I2S_RESET_SET(x)                                   (((x) << RST_RESET_I2S_RESET_LSB) & RST_RESET_I2S_RESET_MASK)
#define RST_RESET_I2S_RESET_RESET                                    0
#define RST_RESET_ADDRESS                                            0x1806001c
#define RST_RESET_OFFSET                                             0x001c
// SW modifiable bits
#define RST_RESET_SW_MASK                                            0xffffffff
// bits defined at reset
#define RST_RESET_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define RST_RESET_RESET                                              0x28c07ff0

#define RST_MISC2_SPARE_MSB                                          31
#define RST_MISC2_SPARE_LSB                                          26
#define RST_MISC2_SPARE_MASK                                         0xfc000000
#define RST_MISC2_SPARE_GET(x)                                       (((x) & RST_MISC2_SPARE_MASK) >> RST_MISC2_SPARE_LSB)
#define RST_MISC2_SPARE_SET(x)                                       (((x) << RST_MISC2_SPARE_LSB) & RST_MISC2_SPARE_MASK)
#define RST_MISC2_SPARE_RESET                                        0x0 // 0
#define RST_MISC2_PCIEEP_L2_EXIT_INT_MSB                             25
#define RST_MISC2_PCIEEP_L2_EXIT_INT_LSB                             25
#define RST_MISC2_PCIEEP_L2_EXIT_INT_MASK                            0x02000000
#define RST_MISC2_PCIEEP_L2_EXIT_INT_GET(x)                          (((x) & RST_MISC2_PCIEEP_L2_EXIT_INT_MASK) >> RST_MISC2_PCIEEP_L2_EXIT_INT_LSB)
#define RST_MISC2_PCIEEP_L2_EXIT_INT_SET(x)                          (((x) << RST_MISC2_PCIEEP_L2_EXIT_INT_LSB) & RST_MISC2_PCIEEP_L2_EXIT_INT_MASK)
#define RST_MISC2_PCIEEP_L2_EXIT_INT_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L2_ENTR_INT_MSB                             24
#define RST_MISC2_PCIEEP_L2_ENTR_INT_LSB                             24
#define RST_MISC2_PCIEEP_L2_ENTR_INT_MASK                            0x01000000
#define RST_MISC2_PCIEEP_L2_ENTR_INT_GET(x)                          (((x) & RST_MISC2_PCIEEP_L2_ENTR_INT_MASK) >> RST_MISC2_PCIEEP_L2_ENTR_INT_LSB)
#define RST_MISC2_PCIEEP_L2_ENTR_INT_SET(x)                          (((x) << RST_MISC2_PCIEEP_L2_ENTR_INT_LSB) & RST_MISC2_PCIEEP_L2_ENTR_INT_MASK)
#define RST_MISC2_PCIEEP_L2_ENTR_INT_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L1_EXIT_INT_MSB                             23
#define RST_MISC2_PCIEEP_L1_EXIT_INT_LSB                             23
#define RST_MISC2_PCIEEP_L1_EXIT_INT_MASK                            0x00800000
#define RST_MISC2_PCIEEP_L1_EXIT_INT_GET(x)                          (((x) & RST_MISC2_PCIEEP_L1_EXIT_INT_MASK) >> RST_MISC2_PCIEEP_L1_EXIT_INT_LSB)
#define RST_MISC2_PCIEEP_L1_EXIT_INT_SET(x)                          (((x) << RST_MISC2_PCIEEP_L1_EXIT_INT_LSB) & RST_MISC2_PCIEEP_L1_EXIT_INT_MASK)
#define RST_MISC2_PCIEEP_L1_EXIT_INT_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L1_ENTR_INT_MSB                             22
#define RST_MISC2_PCIEEP_L1_ENTR_INT_LSB                             22
#define RST_MISC2_PCIEEP_L1_ENTR_INT_MASK                            0x00400000
#define RST_MISC2_PCIEEP_L1_ENTR_INT_GET(x)                          (((x) & RST_MISC2_PCIEEP_L1_ENTR_INT_MASK) >> RST_MISC2_PCIEEP_L1_ENTR_INT_LSB)
#define RST_MISC2_PCIEEP_L1_ENTR_INT_SET(x)                          (((x) << RST_MISC2_PCIEEP_L1_ENTR_INT_LSB) & RST_MISC2_PCIEEP_L1_ENTR_INT_MASK)
#define RST_MISC2_PCIEEP_L1_ENTR_INT_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_MSB                            21
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_LSB                            21
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_MASK                           0x00200000
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_GET(x)                         (((x) & RST_MISC2_PCIEEP_L0S_EXIT_INT_MASK) >> RST_MISC2_PCIEEP_L0S_EXIT_INT_LSB)
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_SET(x)                         (((x) << RST_MISC2_PCIEEP_L0S_EXIT_INT_LSB) & RST_MISC2_PCIEEP_L0S_EXIT_INT_MASK)
#define RST_MISC2_PCIEEP_L0S_EXIT_INT_RESET                          0x0 // 0
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_MSB                            20
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_LSB                            20
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_MASK                           0x00100000
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_GET(x)                         (((x) & RST_MISC2_PCIEEP_L0S_ENTR_INT_MASK) >> RST_MISC2_PCIEEP_L0S_ENTR_INT_LSB)
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_SET(x)                         (((x) << RST_MISC2_PCIEEP_L0S_ENTR_INT_LSB) & RST_MISC2_PCIEEP_L0S_ENTR_INT_MASK)
#define RST_MISC2_PCIEEP_L0S_ENTR_INT_RESET                          0x0 // 0
#define RST_MISC2_PCIEEP_REGWR_EN_MSB                                19
#define RST_MISC2_PCIEEP_REGWR_EN_LSB                                19
#define RST_MISC2_PCIEEP_REGWR_EN_MASK                               0x00080000
#define RST_MISC2_PCIEEP_REGWR_EN_GET(x)                             (((x) & RST_MISC2_PCIEEP_REGWR_EN_MASK) >> RST_MISC2_PCIEEP_REGWR_EN_LSB)
#define RST_MISC2_PCIEEP_REGWR_EN_SET(x)                             (((x) << RST_MISC2_PCIEEP_REGWR_EN_LSB) & RST_MISC2_PCIEEP_REGWR_EN_MASK)
#define RST_MISC2_PCIEEP_REGWR_EN_RESET                              0x1 // 1
#define RST_MISC2_EXT_HOST_WASP_RST_EN_MSB                           18
#define RST_MISC2_EXT_HOST_WASP_RST_EN_LSB                           18
#define RST_MISC2_EXT_HOST_WASP_RST_EN_MASK                          0x00040000
#define RST_MISC2_EXT_HOST_WASP_RST_EN_GET(x)                        (((x) & RST_MISC2_EXT_HOST_WASP_RST_EN_MASK) >> RST_MISC2_EXT_HOST_WASP_RST_EN_LSB)
#define RST_MISC2_EXT_HOST_WASP_RST_EN_SET(x)                        (((x) << RST_MISC2_EXT_HOST_WASP_RST_EN_LSB) & RST_MISC2_EXT_HOST_WASP_RST_EN_MASK)
#define RST_MISC2_EXT_HOST_WASP_RST_EN_RESET                         0x0 // 0
#define RST_MISC2_PCIEEP_RST_INT_MASK_MSB                            17
#define RST_MISC2_PCIEEP_RST_INT_MASK_LSB                            17
#define RST_MISC2_PCIEEP_RST_INT_MASK_MASK                           0x00020000
#define RST_MISC2_PCIEEP_RST_INT_MASK_GET(x)                         (((x) & RST_MISC2_PCIEEP_RST_INT_MASK_MASK) >> RST_MISC2_PCIEEP_RST_INT_MASK_LSB)
#define RST_MISC2_PCIEEP_RST_INT_MASK_SET(x)                         (((x) << RST_MISC2_PCIEEP_RST_INT_MASK_LSB) & RST_MISC2_PCIEEP_RST_INT_MASK_MASK)
#define RST_MISC2_PCIEEP_RST_INT_MASK_RESET                          0x0 // 0
#define RST_MISC2_HOST_RESET_INT_MASK_MSB                            16
#define RST_MISC2_HOST_RESET_INT_MASK_LSB                            16
#define RST_MISC2_HOST_RESET_INT_MASK_MASK                           0x00010000
#define RST_MISC2_HOST_RESET_INT_MASK_GET(x)                         (((x) & RST_MISC2_HOST_RESET_INT_MASK_MASK) >> RST_MISC2_HOST_RESET_INT_MASK_LSB)
#define RST_MISC2_HOST_RESET_INT_MASK_SET(x)                         (((x) << RST_MISC2_HOST_RESET_INT_MASK_LSB) & RST_MISC2_HOST_RESET_INT_MASK_MASK)
#define RST_MISC2_HOST_RESET_INT_MASK_RESET                          0x0 // 0
#define RST_MISC2_CPU_HOST_WA_MSB                                    15
#define RST_MISC2_CPU_HOST_WA_LSB                                    15
#define RST_MISC2_CPU_HOST_WA_MASK                                   0x00008000
#define RST_MISC2_CPU_HOST_WA_GET(x)                                 (((x) & RST_MISC2_CPU_HOST_WA_MASK) >> RST_MISC2_CPU_HOST_WA_LSB)
#define RST_MISC2_CPU_HOST_WA_SET(x)                                 (((x) << RST_MISC2_CPU_HOST_WA_LSB) & RST_MISC2_CPU_HOST_WA_MASK)
#define RST_MISC2_CPU_HOST_WA_RESET                                  0x0 // 0
#define RST_MISC2_PERSTN_EPPHY_MSB                                   14
#define RST_MISC2_PERSTN_EPPHY_LSB                                   14
#define RST_MISC2_PERSTN_EPPHY_MASK                                  0x00004000
#define RST_MISC2_PERSTN_EPPHY_GET(x)                                (((x) & RST_MISC2_PERSTN_EPPHY_MASK) >> RST_MISC2_PERSTN_EPPHY_LSB)
#define RST_MISC2_PERSTN_EPPHY_SET(x)                                (((x) << RST_MISC2_PERSTN_EPPHY_LSB) & RST_MISC2_PERSTN_EPPHY_MASK)
#define RST_MISC2_PERSTN_EPPHY_RESET                                 0x1 // 1
#define RST_MISC2_PERSTN_RCPHY_MSB                                   13
#define RST_MISC2_PERSTN_RCPHY_LSB                                   13
#define RST_MISC2_PERSTN_RCPHY_MASK                                  0x00002000
#define RST_MISC2_PERSTN_RCPHY_GET(x)                                (((x) & RST_MISC2_PERSTN_RCPHY_MASK) >> RST_MISC2_PERSTN_RCPHY_LSB)
#define RST_MISC2_PERSTN_RCPHY_SET(x)                                (((x) << RST_MISC2_PERSTN_RCPHY_LSB) & RST_MISC2_PERSTN_RCPHY_MASK)
#define RST_MISC2_PERSTN_RCPHY_RESET                                 0x1 // 1
#define RST_MISC2_PCIEEP_LTSSM_STATE_MSB                             12
#define RST_MISC2_PCIEEP_LTSSM_STATE_LSB                             8
#define RST_MISC2_PCIEEP_LTSSM_STATE_MASK                            0x00001f00
#define RST_MISC2_PCIEEP_LTSSM_STATE_GET(x)                          (((x) & RST_MISC2_PCIEEP_LTSSM_STATE_MASK) >> RST_MISC2_PCIEEP_LTSSM_STATE_LSB)
#define RST_MISC2_PCIEEP_LTSSM_STATE_SET(x)                          (((x) << RST_MISC2_PCIEEP_LTSSM_STATE_LSB) & RST_MISC2_PCIEEP_LTSSM_STATE_MASK)
#define RST_MISC2_PCIEEP_LTSSM_STATE_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L2_INT_MASK_MSB                             7
#define RST_MISC2_PCIEEP_L2_INT_MASK_LSB                             7
#define RST_MISC2_PCIEEP_L2_INT_MASK_MASK                            0x00000080
#define RST_MISC2_PCIEEP_L2_INT_MASK_GET(x)                          (((x) & RST_MISC2_PCIEEP_L2_INT_MASK_MASK) >> RST_MISC2_PCIEEP_L2_INT_MASK_LSB)
#define RST_MISC2_PCIEEP_L2_INT_MASK_SET(x)                          (((x) << RST_MISC2_PCIEEP_L2_INT_MASK_LSB) & RST_MISC2_PCIEEP_L2_INT_MASK_MASK)
#define RST_MISC2_PCIEEP_L2_INT_MASK_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L1_INT_MASK_MSB                             6
#define RST_MISC2_PCIEEP_L1_INT_MASK_LSB                             6
#define RST_MISC2_PCIEEP_L1_INT_MASK_MASK                            0x00000040
#define RST_MISC2_PCIEEP_L1_INT_MASK_GET(x)                          (((x) & RST_MISC2_PCIEEP_L1_INT_MASK_MASK) >> RST_MISC2_PCIEEP_L1_INT_MASK_LSB)
#define RST_MISC2_PCIEEP_L1_INT_MASK_SET(x)                          (((x) << RST_MISC2_PCIEEP_L1_INT_MASK_LSB) & RST_MISC2_PCIEEP_L1_INT_MASK_MASK)
#define RST_MISC2_PCIEEP_L1_INT_MASK_RESET                           0x0 // 0
#define RST_MISC2_PCIEEP_L0S_INT_MASK_MSB                            5
#define RST_MISC2_PCIEEP_L0S_INT_MASK_LSB                            5
#define RST_MISC2_PCIEEP_L0S_INT_MASK_MASK                           0x00000020
#define RST_MISC2_PCIEEP_L0S_INT_MASK_GET(x)                         (((x) & RST_MISC2_PCIEEP_L0S_INT_MASK_MASK) >> RST_MISC2_PCIEEP_L0S_INT_MASK_LSB)
#define RST_MISC2_PCIEEP_L0S_INT_MASK_SET(x)                         (((x) << RST_MISC2_PCIEEP_L0S_INT_MASK_LSB) & RST_MISC2_PCIEEP_L0S_INT_MASK_MASK)
#define RST_MISC2_PCIEEP_L0S_INT_MASK_RESET                          0x0 // 0
#define RST_MISC2_PCIEEP_LINK_STATUS_MSB                             4
#define RST_MISC2_PCIEEP_LINK_STATUS_LSB                             4
#define RST_MISC2_PCIEEP_LINK_STATUS_MASK                            0x00000010
#define RST_MISC2_PCIEEP_LINK_STATUS_GET(x)                          (((x) & RST_MISC2_PCIEEP_LINK_STATUS_MASK) >> RST_MISC2_PCIEEP_LINK_STATUS_LSB)
#define RST_MISC2_PCIEEP_LINK_STATUS_SET(x)                          (((x) << RST_MISC2_PCIEEP_LINK_STATUS_LSB) & RST_MISC2_PCIEEP_LINK_STATUS_MASK)
#define RST_MISC2_PCIEEP_LINK_STATUS_RESET                           0x0 // 0
#define RST_MISC2_RESERVED_MSB                                       3
#define RST_MISC2_RESERVED_LSB                                       1
#define RST_MISC2_RESERVED_MASK                                      0x0000000e
#define RST_MISC2_RESERVED_GET(x)                                    (((x) & RST_MISC2_RESERVED_MASK) >> RST_MISC2_RESERVED_LSB)
#define RST_MISC2_RESERVED_SET(x)                                    (((x) << RST_MISC2_RESERVED_LSB) & RST_MISC2_RESERVED_MASK)
#define RST_MISC2_RESERVED_RESET                                     0x0 // 0
#define RST_MISC2_PCIEEP_CFG_DONE_MSB                                0
#define RST_MISC2_PCIEEP_CFG_DONE_LSB                                0
#define RST_MISC2_PCIEEP_CFG_DONE_MASK                               0x00000001
#define RST_MISC2_PCIEEP_CFG_DONE_GET(x)                             (((x) & RST_MISC2_PCIEEP_CFG_DONE_MASK) >> RST_MISC2_PCIEEP_CFG_DONE_LSB)
#define RST_MISC2_PCIEEP_CFG_DONE_SET(x)                             (((x) << RST_MISC2_PCIEEP_CFG_DONE_LSB) & RST_MISC2_PCIEEP_CFG_DONE_MASK)
#define RST_MISC2_PCIEEP_CFG_DONE_RESET                              0x0 // 0
#define RST_MISC2_ADDRESS                                            0x180600bc

#define DDR_CONFIG_CAS_LATENCY_MSB_MSB                               31
#define DDR_CONFIG_CAS_LATENCY_MSB_LSB                               31
#define DDR_CONFIG_CAS_LATENCY_MSB_MASK                              0x80000000
#define DDR_CONFIG_CAS_LATENCY_MSB_GET(x)                            (((x) & DDR_CONFIG_CAS_LATENCY_MSB_MASK) >> DDR_CONFIG_CAS_LATENCY_MSB_LSB)
#define DDR_CONFIG_CAS_LATENCY_MSB_SET(x)                            (((x) << DDR_CONFIG_CAS_LATENCY_MSB_LSB) & DDR_CONFIG_CAS_LATENCY_MSB_MASK)
//#define DDR_CONFIG_CAS_LATENCY_MSB_RESET                             1'd0
#define DDR_CONFIG_OPEN_PAGE_MSB                                     30
#define DDR_CONFIG_OPEN_PAGE_LSB                                     30
#define DDR_CONFIG_OPEN_PAGE_MASK                                    0x40000000
#define DDR_CONFIG_OPEN_PAGE_GET(x)                                  (((x) & DDR_CONFIG_OPEN_PAGE_MASK) >> DDR_CONFIG_OPEN_PAGE_LSB)
#define DDR_CONFIG_OPEN_PAGE_SET(x)                                  (((x) << DDR_CONFIG_OPEN_PAGE_LSB) & DDR_CONFIG_OPEN_PAGE_MASK)
//#define DDR_CONFIG_OPEN_PAGE_RESET                                   1'd1
#define DDR_CONFIG_CAS_LATENCY_MSB                                   29
#define DDR_CONFIG_CAS_LATENCY_LSB                                   27
#define DDR_CONFIG_CAS_LATENCY_MASK                                  0x38000000
#define DDR_CONFIG_CAS_LATENCY_GET(x)                                (((x) & DDR_CONFIG_CAS_LATENCY_MASK) >> DDR_CONFIG_CAS_LATENCY_LSB)
#define DDR_CONFIG_CAS_LATENCY_SET(x)                                (((x) << DDR_CONFIG_CAS_LATENCY_LSB) & DDR_CONFIG_CAS_LATENCY_MASK)
//#define DDR_CONFIG_CAS_LATENCY_RESET                                 3'd6
#define DDR_CONFIG_TMRD_MSB                                          26
#define DDR_CONFIG_TMRD_LSB                                          23
#define DDR_CONFIG_TMRD_MASK                                         0x07800000
#define DDR_CONFIG_TMRD_GET(x)                                       (((x) & DDR_CONFIG_TMRD_MASK) >> DDR_CONFIG_TMRD_LSB)
#define DDR_CONFIG_TMRD_SET(x)                                       (((x) << DDR_CONFIG_TMRD_LSB) & DDR_CONFIG_TMRD_MASK)
//#define DDR_CONFIG_TMRD_RESET                                        4'd15
#define DDR_CONFIG_TRFC_MSB                                          22
#define DDR_CONFIG_TRFC_LSB                                          17
#define DDR_CONFIG_TRFC_MASK                                         0x007e0000
#define DDR_CONFIG_TRFC_GET(x)                                       (((x) & DDR_CONFIG_TRFC_MASK) >> DDR_CONFIG_TRFC_LSB)
#define DDR_CONFIG_TRFC_SET(x)                                       (((x) << DDR_CONFIG_TRFC_LSB) & DDR_CONFIG_TRFC_MASK)
//#define DDR_CONFIG_TRFC_RESET                                        6'd31
#define DDR_CONFIG_TRRD_MSB                                          16
#define DDR_CONFIG_TRRD_LSB                                          13
#define DDR_CONFIG_TRRD_MASK                                         0x0001e000
#define DDR_CONFIG_TRRD_GET(x)                                       (((x) & DDR_CONFIG_TRRD_MASK) >> DDR_CONFIG_TRRD_LSB)
#define DDR_CONFIG_TRRD_SET(x)                                       (((x) << DDR_CONFIG_TRRD_LSB) & DDR_CONFIG_TRRD_MASK)
//#define DDR_CONFIG_TRRD_RESET                                        4'd4
#define DDR_CONFIG_TRP_MSB                                           12
#define DDR_CONFIG_TRP_LSB                                           9
#define DDR_CONFIG_TRP_MASK                                          0x00001e00
#define DDR_CONFIG_TRP_GET(x)                                        (((x) & DDR_CONFIG_TRP_MASK) >> DDR_CONFIG_TRP_LSB)
#define DDR_CONFIG_TRP_SET(x)                                        (((x) << DDR_CONFIG_TRP_LSB) & DDR_CONFIG_TRP_MASK)
//#define DDR_CONFIG_TRP_RESET                                         4'd6
#define DDR_CONFIG_TRCD_MSB                                          8
#define DDR_CONFIG_TRCD_LSB                                          5
#define DDR_CONFIG_TRCD_MASK                                         0x000001e0
#define DDR_CONFIG_TRCD_GET(x)                                       (((x) & DDR_CONFIG_TRCD_MASK) >> DDR_CONFIG_TRCD_LSB)
#define DDR_CONFIG_TRCD_SET(x)                                       (((x) << DDR_CONFIG_TRCD_LSB) & DDR_CONFIG_TRCD_MASK)
//#define DDR_CONFIG_TRCD_RESET                                        4'd6
#define DDR_CONFIG_TRAS_MSB                                          4
#define DDR_CONFIG_TRAS_LSB                                          0
#define DDR_CONFIG_TRAS_MASK                                         0x0000001f
#define DDR_CONFIG_TRAS_GET(x)                                       (((x) & DDR_CONFIG_TRAS_MASK) >> DDR_CONFIG_TRAS_LSB)
#define DDR_CONFIG_TRAS_SET(x)                                       (((x) << DDR_CONFIG_TRAS_LSB) & DDR_CONFIG_TRAS_MASK)
//#define DDR_CONFIG_TRAS_RESET                                        5'd16
#define DDR_CONFIG_ADDRESS                                           0x18000000

// 32'h18000004 (DDR_CONFIG2)
#define DDR_CONFIG2_HALF_WIDTH_LOW_MSB                               31
#define DDR_CONFIG2_HALF_WIDTH_LOW_LSB                               31
#define DDR_CONFIG2_HALF_WIDTH_LOW_MASK                              0x80000000
#define DDR_CONFIG2_HALF_WIDTH_LOW_GET(x)                            (((x) & DDR_CONFIG2_HALF_WIDTH_LOW_MASK) >> DDR_CONFIG2_HALF_WIDTH_LOW_LSB)
#define DDR_CONFIG2_HALF_WIDTH_LOW_SET(x)                            (((x) << DDR_CONFIG2_HALF_WIDTH_LOW_LSB) & DDR_CONFIG2_HALF_WIDTH_LOW_MASK)
//#define DDR_CONFIG2_HALF_WIDTH_LOW_RESET                             1'd1
#define DDR_CONFIG2_GATE_OPEN_LATENCY_MSB                            29
#define DDR_CONFIG2_GATE_OPEN_LATENCY_LSB                            26
#define DDR_CONFIG2_GATE_OPEN_LATENCY_MASK                           0x3c000000
#define DDR_CONFIG2_GATE_OPEN_LATENCY_GET(x)                         (((x) & DDR_CONFIG2_GATE_OPEN_LATENCY_MASK) >> DDR_CONFIG2_GATE_OPEN_LATENCY_LSB)
#define DDR_CONFIG2_GATE_OPEN_LATENCY_SET(x)                         (((x) << DDR_CONFIG2_GATE_OPEN_LATENCY_LSB) & DDR_CONFIG2_GATE_OPEN_LATENCY_MASK)
//#define DDR_CONFIG2_GATE_OPEN_LATENCY_RESET                          4'd6
#define DDR_CONFIG2_TWTR_MSB                                         25
#define DDR_CONFIG2_TWTR_LSB                                         21
#define DDR_CONFIG2_TWTR_MASK                                        0x03e00000
#define DDR_CONFIG2_TWTR_GET(x)                                      (((x) & DDR_CONFIG2_TWTR_MASK) >> DDR_CONFIG2_TWTR_LSB)
#define DDR_CONFIG2_TWTR_SET(x)                                      (((x) << DDR_CONFIG2_TWTR_LSB) & DDR_CONFIG2_TWTR_MASK)
//#define DDR_CONFIG2_TWTR_RESET                                       5'd14
#define DDR_CONFIG2_TRTP_MSB                                         20
#define DDR_CONFIG2_TRTP_LSB                                         17
#define DDR_CONFIG2_TRTP_MASK                                        0x001e0000
#define DDR_CONFIG2_TRTP_GET(x)                                      (((x) & DDR_CONFIG2_TRTP_MASK) >> DDR_CONFIG2_TRTP_LSB)
#define DDR_CONFIG2_TRTP_SET(x)                                      (((x) << DDR_CONFIG2_TRTP_LSB) & DDR_CONFIG2_TRTP_MASK)
//#define DDR_CONFIG2_TRTP_RESET                                       4'd8
#define DDR_CONFIG2_TRTW_MSB                                         16
#define DDR_CONFIG2_TRTW_LSB                                         12
#define DDR_CONFIG2_TRTW_MASK                                        0x0001f000
#define DDR_CONFIG2_TRTW_GET(x)                                      (((x) & DDR_CONFIG2_TRTW_MASK) >> DDR_CONFIG2_TRTW_LSB)
#define DDR_CONFIG2_TRTW_SET(x)                                      (((x) << DDR_CONFIG2_TRTW_LSB) & DDR_CONFIG2_TRTW_MASK)
//#define DDR_CONFIG2_TRTW_RESET                                       5'd16
#define DDR_CONFIG2_TWR_MSB                                          11
#define DDR_CONFIG2_TWR_LSB                                          8
#define DDR_CONFIG2_TWR_MASK                                         0x00000f00
#define DDR_CONFIG2_TWR_GET(x)                                       (((x) & DDR_CONFIG2_TWR_MASK) >> DDR_CONFIG2_TWR_LSB)
#define DDR_CONFIG2_TWR_SET(x)                                       (((x) << DDR_CONFIG2_TWR_LSB) & DDR_CONFIG2_TWR_MASK)
//#define DDR_CONFIG2_TWR_RESET                                        4'd6
#define DDR_CONFIG2_CKE_MSB                                          7
#define DDR_CONFIG2_CKE_LSB                                          7
#define DDR_CONFIG2_CKE_MASK                                         0x00000080
#define DDR_CONFIG2_CKE_GET(x)                                       (((x) & DDR_CONFIG2_CKE_MASK) >> DDR_CONFIG2_CKE_LSB)
#define DDR_CONFIG2_CKE_SET(x)                                       (((x) << DDR_CONFIG2_CKE_LSB) & DDR_CONFIG2_CKE_MASK)
//#define DDR_CONFIG2_CKE_RESET                                        1'd0
#define DDR_CONFIG2_PHASE_SELECT_MSB                                 6
#define DDR_CONFIG2_PHASE_SELECT_LSB                                 6
#define DDR_CONFIG2_PHASE_SELECT_MASK                                0x00000040
#define DDR_CONFIG2_PHASE_SELECT_GET(x)                              (((x) & DDR_CONFIG2_PHASE_SELECT_MASK) >> DDR_CONFIG2_PHASE_SELECT_LSB)
#define DDR_CONFIG2_PHASE_SELECT_SET(x)                              (((x) << DDR_CONFIG2_PHASE_SELECT_LSB) & DDR_CONFIG2_PHASE_SELECT_MASK)
//#define DDR_CONFIG2_PHASE_SELECT_RESET                               1'd0
#define DDR_CONFIG2_CNTL_OE_EN_MSB                                   5
#define DDR_CONFIG2_CNTL_OE_EN_LSB                                   5
#define DDR_CONFIG2_CNTL_OE_EN_MASK                                  0x00000020
#define DDR_CONFIG2_CNTL_OE_EN_GET(x)                                (((x) & DDR_CONFIG2_CNTL_OE_EN_MASK) >> DDR_CONFIG2_CNTL_OE_EN_LSB)
#define DDR_CONFIG2_CNTL_OE_EN_SET(x)                                (((x) << DDR_CONFIG2_CNTL_OE_EN_LSB) & DDR_CONFIG2_CNTL_OE_EN_MASK)
//#define DDR_CONFIG2_CNTL_OE_EN_RESET                                 1'd1
#define DDR_CONFIG2_BURST_TYPE_MSB                                   4
#define DDR_CONFIG2_BURST_TYPE_LSB                                   4
#define DDR_CONFIG2_BURST_TYPE_MASK                                  0x00000010
#define DDR_CONFIG2_BURST_TYPE_GET(x)                                (((x) & DDR_CONFIG2_BURST_TYPE_MASK) >> DDR_CONFIG2_BURST_TYPE_LSB)
#define DDR_CONFIG2_BURST_TYPE_SET(x)                                (((x) << DDR_CONFIG2_BURST_TYPE_LSB) & DDR_CONFIG2_BURST_TYPE_MASK)
//#define DDR_CONFIG2_BURST_TYPE_RESET                                 1'd0
#define DDR_CONFIG2_BURST_LENGTH_MSB                                 3
#define DDR_CONFIG2_BURST_LENGTH_LSB                                 0
#define DDR_CONFIG2_BURST_LENGTH_MASK                                0x0000000f
#define DDR_CONFIG2_BURST_LENGTH_GET(x)                              (((x) & DDR_CONFIG2_BURST_LENGTH_MASK) >> DDR_CONFIG2_BURST_LENGTH_LSB)
#define DDR_CONFIG2_BURST_LENGTH_SET(x)                              (((x) << DDR_CONFIG2_BURST_LENGTH_LSB) & DDR_CONFIG2_BURST_LENGTH_MASK)
//#define DDR_CONFIG2_BURST_LENGTH_RESET                               4'd8
#define DDR_CONFIG2_ADDRESS                                          0x18000004


#define DDR2_CONFIG_DDR2_TWL_MSB                                     13
#define DDR2_CONFIG_DDR2_TWL_LSB                                     10
#define DDR2_CONFIG_DDR2_TWL_MASK                                    0x00003c00
#define DDR2_CONFIG_DDR2_TWL_GET(x)                                  (((x) & DDR2_CONFIG_DDR2_TWL_MASK) >> DDR2_CONFIG_DDR2_TWL_LSB)
#define DDR2_CONFIG_DDR2_TWL_SET(x)                                  (((x) << DDR2_CONFIG_DDR2_TWL_LSB) & DDR2_CONFIG_DDR2_TWL_MASK)
//#define DDR2_CONFIG_DDR2_TWL_RESET                                   4'd1
#define DDR2_CONFIG_DDR2_ODT_MSB                                     9
#define DDR2_CONFIG_DDR2_ODT_LSB                                     9
#define DDR2_CONFIG_DDR2_ODT_MASK                                    0x00000200
#define DDR2_CONFIG_DDR2_ODT_GET(x)                                  (((x) & DDR2_CONFIG_DDR2_ODT_MASK) >> DDR2_CONFIG_DDR2_ODT_LSB)
#define DDR2_CONFIG_DDR2_ODT_SET(x)                                  (((x) << DDR2_CONFIG_DDR2_ODT_LSB) & DDR2_CONFIG_DDR2_ODT_MASK)
//#define DDR2_CONFIG_DDR2_ODT_RESET                                   1'd1
#define DDR2_CONFIG_TFAW_MSB                                         7
#define DDR2_CONFIG_TFAW_LSB                                         2
#define DDR2_CONFIG_TFAW_MASK                                        0x000000fc
#define DDR2_CONFIG_TFAW_GET(x)                                      (((x) & DDR2_CONFIG_TFAW_MASK) >> DDR2_CONFIG_TFAW_LSB)
#define DDR2_CONFIG_TFAW_SET(x)                                      (((x) << DDR2_CONFIG_TFAW_LSB) & DDR2_CONFIG_TFAW_MASK)
//#define DDR2_CONFIG_TFAW_RESET                                       6'd22
#define DDR2_CONFIG_ENABLE_DDR2_MSB                                  0
#define DDR2_CONFIG_ENABLE_DDR2_LSB                                  0
#define DDR2_CONFIG_ENABLE_DDR2_MASK                                 0x00000001
#define DDR2_CONFIG_ENABLE_DDR2_GET(x)                               (((x) & DDR2_CONFIG_ENABLE_DDR2_MASK) >> DDR2_CONFIG_ENABLE_DDR2_LSB)
#define DDR2_CONFIG_ENABLE_DDR2_SET(x)                               (((x) << DDR2_CONFIG_ENABLE_DDR2_LSB) & DDR2_CONFIG_ENABLE_DDR2_MASK)
//#define DDR2_CONFIG_ENABLE_DDR2_RESET                                1'd0
#define DDR2_CONFIG_ADDRESS                                          0x180000b8

#define DDR_CTL_CONFIG_SRAM_TSEL_MSB                                 31
#define DDR_CTL_CONFIG_SRAM_TSEL_LSB                                 30
#define DDR_CTL_CONFIG_SRAM_TSEL_MASK                                0xc0000000
#define DDR_CTL_CONFIG_SRAM_TSEL_GET(x)                              (((x) & DDR_CTL_CONFIG_SRAM_TSEL_MASK) >> DDR_CTL_CONFIG_SRAM_TSEL_LSB)
#define DDR_CTL_CONFIG_SRAM_TSEL_SET(x)                              (((x) << DDR_CTL_CONFIG_SRAM_TSEL_LSB) & DDR_CTL_CONFIG_SRAM_TSEL_MASK)
#define DDR_CTL_CONFIG_SRAM_TSEL_RESET                               0x1 // 1
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_MSB                           29
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_LSB                           21
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_MASK                          0x3fe00000
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_GET(x)                        (((x) & DDR_CTL_CONFIG_CLIENT_ACTIVITY_MASK) >> DDR_CTL_CONFIG_CLIENT_ACTIVITY_LSB)
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_SET(x)                        (((x) << DDR_CTL_CONFIG_CLIENT_ACTIVITY_LSB) & DDR_CTL_CONFIG_CLIENT_ACTIVITY_MASK)
#define DDR_CTL_CONFIG_CLIENT_ACTIVITY_RESET                         0x0 // 0
#define DDR_CTL_CONFIG_SPARE_MSB                                     20
#define DDR_CTL_CONFIG_SPARE_LSB                                     6
#define DDR_CTL_CONFIG_SPARE_MASK                                    0x001fffc0
#define DDR_CTL_CONFIG_SPARE_GET(x)                                  (((x) & DDR_CTL_CONFIG_SPARE_MASK) >> DDR_CTL_CONFIG_SPARE_LSB)
#define DDR_CTL_CONFIG_SPARE_SET(x)                                  (((x) << DDR_CTL_CONFIG_SPARE_LSB) & DDR_CTL_CONFIG_SPARE_MASK)
#define DDR_CTL_CONFIG_SPARE_RESET                                   0x4 // 4
#define DDR_CTL_CONFIG_PREFETCH_CNT_MSB                              5
#define DDR_CTL_CONFIG_PREFETCH_CNT_LSB                              2
#define DDR_CTL_CONFIG_PREFETCH_CNT_MASK                             0x0000003c
#define DDR_CTL_CONFIG_PREFETCH_CNT_GET(x)                           (((x) & DDR_CTL_CONFIG_PREFETCH_CNT_MASK) >> DDR_CTL_CONFIG_PREFETCH_CNT_LSB)
#define DDR_CTL_CONFIG_PREFETCH_CNT_SET(x)                           (((x) << DDR_CTL_CONFIG_PREFETCH_CNT_LSB) & DDR_CTL_CONFIG_PREFETCH_CNT_MASK)
#define DDR_CTL_CONFIG_PREFETCH_CNT_RESET                            0x3 // 3
#define DDR_CTL_CONFIG_HALF_WIDTH_MSB                                1
#define DDR_CTL_CONFIG_HALF_WIDTH_LSB                                1
#define DDR_CTL_CONFIG_HALF_WIDTH_MASK                               0x00000002
#define DDR_CTL_CONFIG_HALF_WIDTH_GET(x)                             (((x) & DDR_CTL_CONFIG_HALF_WIDTH_MASK) >> DDR_CTL_CONFIG_HALF_WIDTH_LSB)
#define DDR_CTL_CONFIG_HALF_WIDTH_SET(x)                             (((x) << DDR_CTL_CONFIG_HALF_WIDTH_LSB) & DDR_CTL_CONFIG_HALF_WIDTH_MASK)
#define DDR_CTL_CONFIG_HALF_WIDTH_RESET                              0x1 // 1
#define DDR_CTL_CONFIG_SRAM_MODE_EN_MSB                              0
#define DDR_CTL_CONFIG_SRAM_MODE_EN_LSB                              0
#define DDR_CTL_CONFIG_SRAM_MODE_EN_MASK                             0x00000001
#define DDR_CTL_CONFIG_SRAM_MODE_EN_GET(x)                           (((x) & DDR_CTL_CONFIG_SRAM_MODE_EN_MASK) >> DDR_CTL_CONFIG_SRAM_MODE_EN_LSB)
#define DDR_CTL_CONFIG_SRAM_MODE_EN_SET(x)                           (((x) << DDR_CTL_CONFIG_SRAM_MODE_EN_LSB) & DDR_CTL_CONFIG_SRAM_MODE_EN_MASK)
#define DDR_CTL_CONFIG_SRAM_MODE_EN_RESET                            0x0 // 0
#define DDR_CTL_CONFIG_ADDRESS                                       0x18000108


#define CPU_DPLL3_MEAS_AT_TXON_MSB		31
#define CPU_DPLL3_MEAS_AT_TXON_LSB		31
#define CPU_DPLL3_MEAS_AT_TXON_MASK		0x80000000
#define CPU_DPLL3_MEAS_AT_TXON_GET(x)		(((x) & CPU_DPLL3_MEAS_AT_TXON_MASK) >> CPU_DPLL3_MEAS_AT_TXON_LSB)
#define CPU_DPLL3_MEAS_AT_TXON_SET(x)		(((x) << CPU_DPLL3_MEAS_AT_TXON_LSB) & CPU_DPLL3_MEAS_AT_TXON_MASK)
#define CPU_DPLL3_MEAS_AT_TXON_RESET		0x0 // 0
#define CPU_DPLL3_DO_MEAS_MSB			30
#define CPU_DPLL3_DO_MEAS_LSB			30
#define CPU_DPLL3_DO_MEAS_MASK			0x40000000
#define CPU_DPLL3_DO_MEAS_GET(x)		(((x) & CPU_DPLL3_DO_MEAS_MASK) >> CPU_DPLL3_DO_MEAS_LSB)
#define CPU_DPLL3_DO_MEAS_SET(x)		(((x) << CPU_DPLL3_DO_MEAS_LSB) & CPU_DPLL3_DO_MEAS_MASK)
#define CPU_DPLL3_DO_MEAS_RESET			0x0 // 0
#define CPU_DPLL3_PHASE_SHIFT_MSB		29
#define CPU_DPLL3_PHASE_SHIFT_LSB		23
#define CPU_DPLL3_PHASE_SHIFT_MASK		0x3f800000
#define CPU_DPLL3_PHASE_SHIFT_GET(x)		(((x) & CPU_DPLL3_PHASE_SHIFT_MASK) >> CPU_DPLL3_PHASE_SHIFT_LSB)
#define CPU_DPLL3_PHASE_SHIFT_SET(x)		(((x) << CPU_DPLL3_PHASE_SHIFT_LSB) & CPU_DPLL3_PHASE_SHIFT_MASK)
#define CPU_DPLL3_PHASE_SHIFT_RESET		0x0 // 0
#define CPU_DPLL3_SQSUM_DVC_MSB			22
#define CPU_DPLL3_SQSUM_DVC_LSB			3
#define CPU_DPLL3_SQSUM_DVC_MASK		0x007ffff8
#define CPU_DPLL3_SQSUM_DVC_GET(x)		(((x) & CPU_DPLL3_SQSUM_DVC_MASK) >> CPU_DPLL3_SQSUM_DVC_LSB)
#define CPU_DPLL3_SQSUM_DVC_SET(x)		(((x) << CPU_DPLL3_SQSUM_DVC_LSB) & CPU_DPLL3_SQSUM_DVC_MASK)
#define CPU_DPLL3_SQSUM_DVC_RESET		0x0 // 0
#define CPU_DPLL3_SPARE_MSB			2
#define CPU_DPLL3_SPARE_LSB			0
#define CPU_DPLL3_SPARE_MASK			0x00000007
#define CPU_DPLL3_SPARE_GET(x)			(((x) & CPU_DPLL3_SPARE_MASK) >> CPU_DPLL3_SPARE_LSB)
#define CPU_DPLL3_SPARE_SET(x)			(((x) << CPU_DPLL3_SPARE_LSB) & CPU_DPLL3_SPARE_MASK)
#define CPU_DPLL3_SPARE_RESET			0x0 // 0
#define CPU_DPLL3_ADDRESS			0x181161c8
#define CPU_DPLL4_MEAN_DVC_MSB			31
#define CPU_DPLL4_MEAN_DVC_LSB			21
#define CPU_DPLL4_MEAN_DVC_MASK			0xffe00000
#define CPU_DPLL4_MEAN_DVC_GET(x)		(((x) & CPU_DPLL4_MEAN_DVC_MASK) >> CPU_DPLL4_MEAN_DVC_LSB)
#define CPU_DPLL4_MEAN_DVC_SET(x)		(((x) << CPU_DPLL4_MEAN_DVC_LSB) & CPU_DPLL4_MEAN_DVC_MASK)
#define CPU_DPLL4_MEAN_DVC_RESET		0x0 // 0
#define CPU_DPLL4_VC_MEAS0_MSB			20
#define CPU_DPLL4_VC_MEAS0_LSB			4
#define CPU_DPLL4_VC_MEAS0_MASK			0x001ffff0
#define CPU_DPLL4_VC_MEAS0_GET(x)		(((x) & CPU_DPLL4_VC_MEAS0_MASK) >> CPU_DPLL4_VC_MEAS0_LSB)
#define CPU_DPLL4_VC_MEAS0_SET(x)		(((x) << CPU_DPLL4_VC_MEAS0_LSB) & CPU_DPLL4_VC_MEAS0_MASK)
#define CPU_DPLL4_VC_MEAS0_RESET		0x0 // 0
#define CPU_DPLL4_MEAS_DONE_MSB			3
#define CPU_DPLL4_MEAS_DONE_LSB			3
#define CPU_DPLL4_MEAS_DONE_MASK		0x00000008
#define CPU_DPLL4_MEAS_DONE_GET(x)		(((x) & CPU_DPLL4_MEAS_DONE_MASK) >> CPU_DPLL4_MEAS_DONE_LSB)
#define CPU_DPLL4_MEAS_DONE_SET(x)		(((x) << CPU_DPLL4_MEAS_DONE_LSB) & CPU_DPLL4_MEAS_DONE_MASK)
#define CPU_DPLL4_MEAS_DONE_RESET		0x0 // 0
#define CPU_DPLL4_SPARE_MSB			2
#define CPU_DPLL4_SPARE_LSB			0
#define CPU_DPLL4_SPARE_MASK			0x00000007
#define CPU_DPLL4_SPARE_GET(x)			(((x) & CPU_DPLL4_SPARE_MASK) >> CPU_DPLL4_SPARE_LSB)
#define CPU_DPLL4_SPARE_SET(x)			(((x) << CPU_DPLL4_SPARE_LSB) & CPU_DPLL4_SPARE_MASK)
#define CPU_DPLL4_SPARE_RESET			0x0 // 0
#define CPU_DPLL4_ADDRESS			0x181161cc

#define DDR_DPLL3_MEAS_AT_TXON_MSB		31
#define DDR_DPLL3_MEAS_AT_TXON_LSB		31
#define DDR_DPLL3_MEAS_AT_TXON_MASK		0x80000000
#define DDR_DPLL3_MEAS_AT_TXON_GET(x)		(((x) & DDR_DPLL3_MEAS_AT_TXON_MASK) >> DDR_DPLL3_MEAS_AT_TXON_LSB)
#define DDR_DPLL3_MEAS_AT_TXON_SET(x)		(((x) << DDR_DPLL3_MEAS_AT_TXON_LSB) & DDR_DPLL3_MEAS_AT_TXON_MASK)
#define DDR_DPLL3_MEAS_AT_TXON_RESET		0x0 // 0
#define DDR_DPLL3_DO_MEAS_MSB			30
#define DDR_DPLL3_DO_MEAS_LSB			30
#define DDR_DPLL3_DO_MEAS_MASK			0x40000000
#define DDR_DPLL3_DO_MEAS_GET(x)		(((x) & DDR_DPLL3_DO_MEAS_MASK) >> DDR_DPLL3_DO_MEAS_LSB)
#define DDR_DPLL3_DO_MEAS_SET(x)		(((x) << DDR_DPLL3_DO_MEAS_LSB) & DDR_DPLL3_DO_MEAS_MASK)
#define DDR_DPLL3_DO_MEAS_RESET			0x0 // 0
#define DDR_DPLL3_PHASE_SHIFT_MSB		29
#define DDR_DPLL3_PHASE_SHIFT_LSB		23
#define DDR_DPLL3_PHASE_SHIFT_MASK		0x3f800000
#define DDR_DPLL3_PHASE_SHIFT_GET(x)		(((x) & DDR_DPLL3_PHASE_SHIFT_MASK) >> DDR_DPLL3_PHASE_SHIFT_LSB)
#define DDR_DPLL3_PHASE_SHIFT_SET(x)		(((x) << DDR_DPLL3_PHASE_SHIFT_LSB) & DDR_DPLL3_PHASE_SHIFT_MASK)
#define DDR_DPLL3_PHASE_SHIFT_RESET		0x0 // 0
#define DDR_DPLL3_SQSUM_DVC_MSB			22
#define DDR_DPLL3_SQSUM_DVC_LSB			3
#define DDR_DPLL3_SQSUM_DVC_MASK		0x007ffff8
#define DDR_DPLL3_SQSUM_DVC_GET(x)		(((x) & DDR_DPLL3_SQSUM_DVC_MASK) >> DDR_DPLL3_SQSUM_DVC_LSB)
#define DDR_DPLL3_SQSUM_DVC_SET(x)		(((x) << DDR_DPLL3_SQSUM_DVC_LSB) & DDR_DPLL3_SQSUM_DVC_MASK)
#define DDR_DPLL3_SQSUM_DVC_RESET		0x0 // 0
#define DDR_DPLL3_SPARE_MSB			2
#define DDR_DPLL3_SPARE_LSB			0
#define DDR_DPLL3_SPARE_MASK			0x00000007
#define DDR_DPLL3_SPARE_GET(x)			(((x) & DDR_DPLL3_SPARE_MASK) >> DDR_DPLL3_SPARE_LSB)
#define DDR_DPLL3_SPARE_SET(x)			(((x) << DDR_DPLL3_SPARE_LSB) & DDR_DPLL3_SPARE_MASK)
#define DDR_DPLL3_SPARE_RESET			0x0 // 0
#define DDR_DPLL3_ADDRESS			0x18116248

// 32'h1811624c (DDR_DPLL4)
#define DDR_DPLL4_MEAN_DVC_MSB			31
#define DDR_DPLL4_MEAN_DVC_LSB			21
#define DDR_DPLL4_MEAN_DVC_MASK			0xffe00000
#define DDR_DPLL4_MEAN_DVC_GET(x)		(((x) & DDR_DPLL4_MEAN_DVC_MASK) >> DDR_DPLL4_MEAN_DVC_LSB)
#define DDR_DPLL4_MEAN_DVC_SET(x)		(((x) << DDR_DPLL4_MEAN_DVC_LSB) & DDR_DPLL4_MEAN_DVC_MASK)
#define DDR_DPLL4_MEAN_DVC_RESET		0x0 // 0
#define DDR_DPLL4_VC_MEAS0_MSB			20
#define DDR_DPLL4_VC_MEAS0_LSB			4
#define DDR_DPLL4_VC_MEAS0_MASK			0x001ffff0
#define DDR_DPLL4_VC_MEAS0_GET(x)		(((x) & DDR_DPLL4_VC_MEAS0_MASK) >> DDR_DPLL4_VC_MEAS0_LSB)
#define DDR_DPLL4_VC_MEAS0_SET(x)		(((x) << DDR_DPLL4_VC_MEAS0_LSB) & DDR_DPLL4_VC_MEAS0_MASK)
#define DDR_DPLL4_VC_MEAS0_RESET		0x0 // 0
#define DDR_DPLL4_MEAS_DONE_MSB			3
#define DDR_DPLL4_MEAS_DONE_LSB			3
#define DDR_DPLL4_MEAS_DONE_MASK		0x00000008
#define DDR_DPLL4_MEAS_DONE_GET(x)		(((x) & DDR_DPLL4_MEAS_DONE_MASK) >> DDR_DPLL4_MEAS_DONE_LSB)
#define DDR_DPLL4_MEAS_DONE_SET(x)		(((x) << DDR_DPLL4_MEAS_DONE_LSB) & DDR_DPLL4_MEAS_DONE_MASK)
#define DDR_DPLL4_MEAS_DONE_RESET		0x0 // 0
#define DDR_DPLL4_SPARE_MSB			2
#define DDR_DPLL4_SPARE_LSB			0
#define DDR_DPLL4_SPARE_MASK			0x00000007
#define DDR_DPLL4_SPARE_GET(x)			(((x) & DDR_DPLL4_SPARE_MASK) >> DDR_DPLL4_SPARE_LSB)
#define DDR_DPLL4_SPARE_SET(x)			(((x) << DDR_DPLL4_SPARE_LSB) & DDR_DPLL4_SPARE_MASK)
#define DDR_DPLL4_SPARE_RESET			0x0 // 0
#define DDR_DPLL4_ADDRESS			0x1811624c

#define DPLL2_ADDRESS_c4			0x181161c4
#define DPLL3_ADDRESS_c8			CPU_DPLL3_ADDRESS
#define DPLL2_ADDRESS_44			0x18116244
#define DPLL3_ADDRESS_48			DDR_DPLL3_ADDRESS
#define DPLL3_ADDRESS_88			0x18116188

#define PCIe_DPLL_REFDIV_MSB			31
#define PCIe_DPLL_REFDIV_LSB			27
#define PCIe_DPLL_REFDIV_MASK			0xf8000000
#define PCIe_DPLL_REFDIV_GET(x)			(((x) & PCIe_DPLL_REFDIV_MASK) >> PCIe_DPLL_REFDIV_LSB)
#define PCIe_DPLL_REFDIV_SET(x)			(((x) << PCIe_DPLL_REFDIV_LSB) & PCIe_DPLL_REFDIV_MASK)
#define PCIe_DPLL_REFDIV_RESET			0x1 // 1
#define PCIe_DPLL_NINT_MSB			26
#define PCIe_DPLL_NINT_LSB			18
#define PCIe_DPLL_NINT_MASK			0x07fc0000
#define PCIe_DPLL_NINT_GET(x)			(((x) & PCIe_DPLL_NINT_MASK) >> PCIe_DPLL_NINT_LSB)
#define PCIe_DPLL_NINT_SET(x)			(((x) << PCIe_DPLL_NINT_LSB) & PCIe_DPLL_NINT_MASK)
#define PCIe_DPLL_NINT_RESET			0x10 // 16
#define PCIe_DPLL_NFRAC_MSB			17
#define PCIe_DPLL_NFRAC_LSB			0
#define PCIe_DPLL_NFRAC_MASK			0x0003ffff
#define PCIe_DPLL_NFRAC_GET(x)			(((x) & PCIe_DPLL_NFRAC_MASK) >> PCIe_DPLL_NFRAC_LSB)
#define PCIe_DPLL_NFRAC_SET(x)			(((x) << PCIe_DPLL_NFRAC_LSB) & PCIe_DPLL_NFRAC_MASK)
#define PCIe_DPLL_NFRAC_RESET			0x0 // 0
#define PCIe_DPLL_ADDRESS			0x18116c00

// 32'h18116c04 (PCIe_DPLL2)
#define PCIe_DPLL2_RANGE_MSB			31
#define PCIe_DPLL2_RANGE_LSB			31
#define PCIe_DPLL2_RANGE_MASK			0x80000000
#define PCIe_DPLL2_RANGE_GET(x)			(((x) & PCIe_DPLL2_RANGE_MASK) >> PCIe_DPLL2_RANGE_LSB)
#define PCIe_DPLL2_RANGE_SET(x)			(((x) << PCIe_DPLL2_RANGE_LSB) & PCIe_DPLL2_RANGE_MASK)
#define PCIe_DPLL2_RANGE_RESET			0x0 // 0
#define PCIe_DPLL2_LOCAL_PLL_MSB		30
#define PCIe_DPLL2_LOCAL_PLL_LSB		30
#define PCIe_DPLL2_LOCAL_PLL_MASK		0x40000000
#define PCIe_DPLL2_LOCAL_PLL_GET(x)		(((x) & PCIe_DPLL2_LOCAL_PLL_MASK) >> PCIe_DPLL2_LOCAL_PLL_LSB)
#define PCIe_DPLL2_LOCAL_PLL_SET(x)		(((x) << PCIe_DPLL2_LOCAL_PLL_LSB) & PCIe_DPLL2_LOCAL_PLL_MASK)
#define PCIe_DPLL2_LOCAL_PLL_RESET		0x0 // 0
#define PCIe_DPLL2_KI_MSB			29
#define PCIe_DPLL2_KI_LSB			26
#define PCIe_DPLL2_KI_MASK			0x3c000000
#define PCIe_DPLL2_KI_GET(x)			(((x) & PCIe_DPLL2_KI_MASK) >> PCIe_DPLL2_KI_LSB)
#define PCIe_DPLL2_KI_SET(x)			(((x) << PCIe_DPLL2_KI_LSB) & PCIe_DPLL2_KI_MASK)
#define PCIe_DPLL2_KI_RESET			0x6 // 6
#define PCIe_DPLL2_KD_MSB			25
#define PCIe_DPLL2_KD_LSB			19
#define PCIe_DPLL2_KD_MASK			0x03f80000
#define PCIe_DPLL2_KD_GET(x)			(((x) & PCIe_DPLL2_KD_MASK) >> PCIe_DPLL2_KD_LSB)
#define PCIe_DPLL2_KD_SET(x)			(((x) << PCIe_DPLL2_KD_LSB) & PCIe_DPLL2_KD_MASK)
#define PCIe_DPLL2_KD_RESET			0x7f // 127
#define PCIe_DPLL2_EN_NEGTRIG_MSB		18
#define PCIe_DPLL2_EN_NEGTRIG_LSB		18
#define PCIe_DPLL2_EN_NEGTRIG_MASK		0x00040000
#define PCIe_DPLL2_EN_NEGTRIG_GET(x)		(((x) & PCIe_DPLL2_EN_NEGTRIG_MASK) >> PCIe_DPLL2_EN_NEGTRIG_LSB)
#define PCIe_DPLL2_EN_NEGTRIG_SET(x)		(((x) << PCIe_DPLL2_EN_NEGTRIG_LSB) & PCIe_DPLL2_EN_NEGTRIG_MASK)
#define PCIe_DPLL2_EN_NEGTRIG_RESET		0x0 // 0
#define PCIe_DPLL2_SEL_1SDM_MSB			17
#define PCIe_DPLL2_SEL_1SDM_LSB			17
#define PCIe_DPLL2_SEL_1SDM_MASK		0x00020000
#define PCIe_DPLL2_SEL_1SDM_GET(x)		(((x) & PCIe_DPLL2_SEL_1SDM_MASK) >> PCIe_DPLL2_SEL_1SDM_LSB)
#define PCIe_DPLL2_SEL_1SDM_SET(x)		(((x) << PCIe_DPLL2_SEL_1SDM_LSB) & PCIe_DPLL2_SEL_1SDM_MASK)
#define PCIe_DPLL2_SEL_1SDM_RESET		0x0 // 0
#define PCIe_DPLL2_PLL_PWD_MSB			16
#define PCIe_DPLL2_PLL_PWD_LSB			16
#define PCIe_DPLL2_PLL_PWD_MASK			0x00010000
#define PCIe_DPLL2_PLL_PWD_GET(x)		(((x) & PCIe_DPLL2_PLL_PWD_MASK) >> PCIe_DPLL2_PLL_PWD_LSB)
#define PCIe_DPLL2_PLL_PWD_SET(x)		(((x) << PCIe_DPLL2_PLL_PWD_LSB) & PCIe_DPLL2_PLL_PWD_MASK)
#define PCIe_DPLL2_PLL_PWD_RESET		0x1 // 1
#define PCIe_DPLL2_OUTDIV_MSB			15
#define PCIe_DPLL2_OUTDIV_LSB			13
#define PCIe_DPLL2_OUTDIV_MASK			0x0000e000
#define PCIe_DPLL2_OUTDIV_GET(x)		(((x) & PCIe_DPLL2_OUTDIV_MASK) >> PCIe_DPLL2_OUTDIV_LSB)
#define PCIe_DPLL2_OUTDIV_SET(x)		(((x) << PCIe_DPLL2_OUTDIV_LSB) & PCIe_DPLL2_OUTDIV_MASK)
#define PCIe_DPLL2_OUTDIV_RESET			0x0 // 0
#define PCIe_DPLL2_DELTA_MSB			12
#define PCIe_DPLL2_DELTA_LSB			7
#define PCIe_DPLL2_DELTA_MASK			0x00001f80
#define PCIe_DPLL2_DELTA_GET(x)			(((x) & PCIe_DPLL2_DELTA_MASK) >> PCIe_DPLL2_DELTA_LSB)
#define PCIe_DPLL2_DELTA_SET(x)			(((x) << PCIe_DPLL2_DELTA_LSB) & PCIe_DPLL2_DELTA_MASK)
#define PCIe_DPLL2_DELTA_RESET			0x1e // 30
#define PCIe_DPLL2_SPARE_MSB			6
#define PCIe_DPLL2_SPARE_LSB			0
#define PCIe_DPLL2_SPARE_MASK			0x0000007f
#define PCIe_DPLL2_SPARE_GET(x)			(((x) & PCIe_DPLL2_SPARE_MASK) >> PCIe_DPLL2_SPARE_LSB)
#define PCIe_DPLL2_SPARE_SET(x)			(((x) << PCIe_DPLL2_SPARE_LSB) & PCIe_DPLL2_SPARE_MASK)
#define PCIe_DPLL2_SPARE_RESET			0x0 // 0
#define PCIe_DPLL2_ADDRESS			0x18116c04

#define PCIe_DPLL3_MEAS_AT_TXON_MSB		31
#define PCIe_DPLL3_MEAS_AT_TXON_LSB		31
#define PCIe_DPLL3_MEAS_AT_TXON_MASK		0x80000000
#define PCIe_DPLL3_MEAS_AT_TXON_GET(x)		(((x) & PCIe_DPLL3_MEAS_AT_TXON_MASK) >> PCIe_DPLL3_MEAS_AT_TXON_LSB)
#define PCIe_DPLL3_MEAS_AT_TXON_SET(x)		(((x) << PCIe_DPLL3_MEAS_AT_TXON_LSB) & PCIe_DPLL3_MEAS_AT_TXON_MASK)
#define PCIe_DPLL3_MEAS_AT_TXON_RESET		0x0 // 0
#define PCIe_DPLL3_DO_MEAS_MSB			30
#define PCIe_DPLL3_DO_MEAS_LSB			30
#define PCIe_DPLL3_DO_MEAS_MASK			0x40000000
#define PCIe_DPLL3_DO_MEAS_GET(x)		(((x) & PCIe_DPLL3_DO_MEAS_MASK) >> PCIe_DPLL3_DO_MEAS_LSB)
#define PCIe_DPLL3_DO_MEAS_SET(x)		(((x) << PCIe_DPLL3_DO_MEAS_LSB) & PCIe_DPLL3_DO_MEAS_MASK)
#define PCIe_DPLL3_DO_MEAS_RESET		0x0 // 0
#define PCIe_DPLL3_PHASE_SHIFT_MSB		29
#define PCIe_DPLL3_PHASE_SHIFT_LSB		23
#define PCIe_DPLL3_PHASE_SHIFT_MASK		0x3f800000
#define PCIe_DPLL3_PHASE_SHIFT_GET(x)		(((x) & PCIe_DPLL3_PHASE_SHIFT_MASK) >> PCIe_DPLL3_PHASE_SHIFT_LSB)
#define PCIe_DPLL3_PHASE_SHIFT_SET(x)		(((x) << PCIe_DPLL3_PHASE_SHIFT_LSB) & PCIe_DPLL3_PHASE_SHIFT_MASK)
#define PCIe_DPLL3_PHASE_SHIFT_RESET		0x0 // 0
#define PCIe_DPLL3_SQSUM_DVC_MSB		22
#define PCIe_DPLL3_SQSUM_DVC_LSB		3
#define PCIe_DPLL3_SQSUM_DVC_MASK		0x007ffff8
#define PCIe_DPLL3_SQSUM_DVC_GET(x)		(((x) & PCIe_DPLL3_SQSUM_DVC_MASK) >> PCIe_DPLL3_SQSUM_DVC_LSB)
#define PCIe_DPLL3_SQSUM_DVC_SET(x)		(((x) << PCIe_DPLL3_SQSUM_DVC_LSB) & PCIe_DPLL3_SQSUM_DVC_MASK)
#define PCIe_DPLL3_SQSUM_DVC_RESET		0x0 // 0
#define PCIe_DPLL3_SPARE_MSB			2
#define PCIe_DPLL3_SPARE_LSB			0
#define PCIe_DPLL3_SPARE_MASK			0x00000007
#define PCIe_DPLL3_SPARE_GET(x)			(((x) & PCIe_DPLL3_SPARE_MASK) >> PCIe_DPLL3_SPARE_LSB)
#define PCIe_DPLL3_SPARE_SET(x)			(((x) << PCIe_DPLL3_SPARE_LSB) & PCIe_DPLL3_SPARE_MASK)
#define PCIe_DPLL3_SPARE_RESET			0x0 // 0
#define PCIe_DPLL3_ADDRESS			0x18116c08

#define PCIe_DPLL4_MEAN_DVC_MSB			31
#define PCIe_DPLL4_MEAN_DVC_LSB			21
#define PCIe_DPLL4_MEAN_DVC_MASK		0xffe00000
#define PCIe_DPLL4_MEAN_DVC_GET(x)		(((x) & PCIe_DPLL4_MEAN_DVC_MASK) >> PCIe_DPLL4_MEAN_DVC_LSB)
#define PCIe_DPLL4_MEAN_DVC_SET(x)		(((x) << PCIe_DPLL4_MEAN_DVC_LSB) & PCIe_DPLL4_MEAN_DVC_MASK)
#define PCIe_DPLL4_MEAN_DVC_RESET		0x0 // 0
#define PCIe_DPLL4_VC_MEAS0_MSB			20
#define PCIe_DPLL4_VC_MEAS0_LSB			4
#define PCIe_DPLL4_VC_MEAS0_MASK		0x001ffff0
#define PCIe_DPLL4_VC_MEAS0_GET(x)		(((x) & PCIe_DPLL4_VC_MEAS0_MASK) >> PCIe_DPLL4_VC_MEAS0_LSB)
#define PCIe_DPLL4_VC_MEAS0_SET(x)		(((x) << PCIe_DPLL4_VC_MEAS0_LSB) & PCIe_DPLL4_VC_MEAS0_MASK)
#define PCIe_DPLL4_VC_MEAS0_RESET		0x0 // 0
#define PCIe_DPLL4_MEAS_DONE_MSB		3
#define PCIe_DPLL4_MEAS_DONE_LSB		3
#define PCIe_DPLL4_MEAS_DONE_MASK		0x00000008
#define PCIe_DPLL4_MEAS_DONE_GET(x)		(((x) & PCIe_DPLL4_MEAS_DONE_MASK) >> PCIe_DPLL4_MEAS_DONE_LSB)
#define PCIe_DPLL4_MEAS_DONE_SET(x)		(((x) << PCIe_DPLL4_MEAS_DONE_LSB) & PCIe_DPLL4_MEAS_DONE_MASK)
#define PCIe_DPLL4_MEAS_DONE_RESET		0x0 // 0
#define PCIe_DPLL4_SPARE_MSB			2
#define PCIe_DPLL4_SPARE_LSB			0
#define PCIe_DPLL4_SPARE_MASK			0x00000007
#define PCIe_DPLL4_SPARE_GET(x)			(((x) & PCIe_DPLL4_SPARE_MASK) >> PCIe_DPLL4_SPARE_LSB)
#define PCIe_DPLL4_SPARE_SET(x)			(((x) << PCIe_DPLL4_SPARE_LSB) & PCIe_DPLL4_SPARE_MASK)
#define PCIe_DPLL4_SPARE_RESET			0x0 // 0
#define PCIe_DPLL4_ADDRESS			0x18116c0c

#define	ATH_DDR_COUNT_LOC	0xbd000000
#define	ATH_CPU_COUNT_LOC	0xbd000004

#define XTAL_ADDRESS                                                 0x18116290

#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_MSB                          31
#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_LSB                          31
#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_MASK                         0x80000000
#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_GET(x)                       (((x) & PCIE_PHY_REG_1_SERDES_DIS_RXIMP_MASK) >> PCIE_PHY_REG_1_SERDES_DIS_RXIMP_LSB)
#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_SET(x)                       (((x) << PCIE_PHY_REG_1_SERDES_DIS_RXIMP_LSB) & PCIE_PHY_REG_1_SERDES_DIS_RXIMP_MASK)
#define PCIE_PHY_REG_1_SERDES_DIS_RXIMP_RESET                        0x0 // 0
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_MSB                          30
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_LSB                          29
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_MASK                         0x60000000
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_GET(x)                       (((x) & PCIE_PHY_REG_1_SERDES_TXDR_CTRL_MASK) >> PCIE_PHY_REG_1_SERDES_TXDR_CTRL_LSB)
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_SET(x)                       (((x) << PCIE_PHY_REG_1_SERDES_TXDR_CTRL_LSB) & PCIE_PHY_REG_1_SERDES_TXDR_CTRL_MASK)
#define PCIE_PHY_REG_1_SERDES_TXDR_CTRL_RESET                        0x0 // 0
#define PCIE_PHY_REG_1_PERSTDELAY_MSB                                28
#define PCIE_PHY_REG_1_PERSTDELAY_LSB                                27
#define PCIE_PHY_REG_1_PERSTDELAY_MASK                               0x18000000
#define PCIE_PHY_REG_1_PERSTDELAY_GET(x)                             (((x) & PCIE_PHY_REG_1_PERSTDELAY_MASK) >> PCIE_PHY_REG_1_PERSTDELAY_LSB)
#define PCIE_PHY_REG_1_PERSTDELAY_SET(x)                             (((x) << PCIE_PHY_REG_1_PERSTDELAY_LSB) & PCIE_PHY_REG_1_PERSTDELAY_MASK)
#define PCIE_PHY_REG_1_PERSTDELAY_RESET                              0x2 // 2
#define PCIE_PHY_REG_1_CLKOBSSEL_MSB                                 26
#define PCIE_PHY_REG_1_CLKOBSSEL_LSB                                 25
#define PCIE_PHY_REG_1_CLKOBSSEL_MASK                                0x06000000
#define PCIE_PHY_REG_1_CLKOBSSEL_GET(x)                              (((x) & PCIE_PHY_REG_1_CLKOBSSEL_MASK) >> PCIE_PHY_REG_1_CLKOBSSEL_LSB)
#define PCIE_PHY_REG_1_CLKOBSSEL_SET(x)                              (((x) << PCIE_PHY_REG_1_CLKOBSSEL_LSB) & PCIE_PHY_REG_1_CLKOBSSEL_MASK)
#define PCIE_PHY_REG_1_CLKOBSSEL_RESET                               0x0 // 0
#define PCIE_PHY_REG_1_DATAOBSEN_MSB                                 24
#define PCIE_PHY_REG_1_DATAOBSEN_LSB                                 24
#define PCIE_PHY_REG_1_DATAOBSEN_MASK                                0x01000000
#define PCIE_PHY_REG_1_DATAOBSEN_GET(x)                              (((x) & PCIE_PHY_REG_1_DATAOBSEN_MASK) >> PCIE_PHY_REG_1_DATAOBSEN_LSB)
#define PCIE_PHY_REG_1_DATAOBSEN_SET(x)                              (((x) << PCIE_PHY_REG_1_DATAOBSEN_LSB) & PCIE_PHY_REG_1_DATAOBSEN_MASK)
#define PCIE_PHY_REG_1_DATAOBSEN_RESET                               0x0 // 0
#define PCIE_PHY_REG_1_FUNCTESTEN_MSB                                23
#define PCIE_PHY_REG_1_FUNCTESTEN_LSB                                23
#define PCIE_PHY_REG_1_FUNCTESTEN_MASK                               0x00800000
#define PCIE_PHY_REG_1_FUNCTESTEN_GET(x)                             (((x) & PCIE_PHY_REG_1_FUNCTESTEN_MASK) >> PCIE_PHY_REG_1_FUNCTESTEN_LSB)
#define PCIE_PHY_REG_1_FUNCTESTEN_SET(x)                             (((x) << PCIE_PHY_REG_1_FUNCTESTEN_LSB) & PCIE_PHY_REG_1_FUNCTESTEN_MASK)
#define PCIE_PHY_REG_1_FUNCTESTEN_RESET                              0x0 // 0
#define PCIE_PHY_REG_1_SERDES_DISABLE_MSB                            22
#define PCIE_PHY_REG_1_SERDES_DISABLE_LSB                            22
#define PCIE_PHY_REG_1_SERDES_DISABLE_MASK                           0x00400000
#define PCIE_PHY_REG_1_SERDES_DISABLE_GET(x)                         (((x) & PCIE_PHY_REG_1_SERDES_DISABLE_MASK) >> PCIE_PHY_REG_1_SERDES_DISABLE_LSB)
#define PCIE_PHY_REG_1_SERDES_DISABLE_SET(x)                         (((x) << PCIE_PHY_REG_1_SERDES_DISABLE_LSB) & PCIE_PHY_REG_1_SERDES_DISABLE_MASK)
#define PCIE_PHY_REG_1_SERDES_DISABLE_RESET                          0x0 // 0
#define PCIE_PHY_REG_1_RXCLKINV_MSB                                  21
#define PCIE_PHY_REG_1_RXCLKINV_LSB                                  21
#define PCIE_PHY_REG_1_RXCLKINV_MASK                                 0x00200000
#define PCIE_PHY_REG_1_RXCLKINV_GET(x)                               (((x) & PCIE_PHY_REG_1_RXCLKINV_MASK) >> PCIE_PHY_REG_1_RXCLKINV_LSB)
#define PCIE_PHY_REG_1_RXCLKINV_SET(x)                               (((x) << PCIE_PHY_REG_1_RXCLKINV_LSB) & PCIE_PHY_REG_1_RXCLKINV_MASK)
#define PCIE_PHY_REG_1_RXCLKINV_RESET                                0x1 // 1
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_MSB                          20
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_LSB                          20
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_MASK                         0x00100000
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_GET(x)                       (((x) & PCIE_PHY_REG_1_FUNCTESTRXCLKINV_MASK) >> PCIE_PHY_REG_1_FUNCTESTRXCLKINV_LSB)
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_SET(x)                       (((x) << PCIE_PHY_REG_1_FUNCTESTRXCLKINV_LSB) & PCIE_PHY_REG_1_FUNCTESTRXCLKINV_MASK)
#define PCIE_PHY_REG_1_FUNCTESTRXCLKINV_RESET                        0x0 // 0
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_MSB                          19
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_LSB                          19
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_MASK                         0x00080000
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_GET(x)                       (((x) & PCIE_PHY_REG_1_FUNCTESTTXCLKINV_MASK) >> PCIE_PHY_REG_1_FUNCTESTTXCLKINV_LSB)
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_SET(x)                       (((x) << PCIE_PHY_REG_1_FUNCTESTTXCLKINV_LSB) & PCIE_PHY_REG_1_FUNCTESTTXCLKINV_MASK)
#define PCIE_PHY_REG_1_FUNCTESTTXCLKINV_RESET                        0x0 // 0
#define PCIE_PHY_REG_1_ENABLECLKREQ_MSB                              18
#define PCIE_PHY_REG_1_ENABLECLKREQ_LSB                              18
#define PCIE_PHY_REG_1_ENABLECLKREQ_MASK                             0x00040000
#define PCIE_PHY_REG_1_ENABLECLKREQ_GET(x)                           (((x) & PCIE_PHY_REG_1_ENABLECLKREQ_MASK) >> PCIE_PHY_REG_1_ENABLECLKREQ_LSB)
#define PCIE_PHY_REG_1_ENABLECLKREQ_SET(x)                           (((x) << PCIE_PHY_REG_1_ENABLECLKREQ_LSB) & PCIE_PHY_REG_1_ENABLECLKREQ_MASK)
#define PCIE_PHY_REG_1_ENABLECLKREQ_RESET                            0x0 // 0
#define PCIE_PHY_REG_1_FORCELOOPBACK_MSB                             17
#define PCIE_PHY_REG_1_FORCELOOPBACK_LSB                             17
#define PCIE_PHY_REG_1_FORCELOOPBACK_MASK                            0x00020000
#define PCIE_PHY_REG_1_FORCELOOPBACK_GET(x)                          (((x) & PCIE_PHY_REG_1_FORCELOOPBACK_MASK) >> PCIE_PHY_REG_1_FORCELOOPBACK_LSB)
#define PCIE_PHY_REG_1_FORCELOOPBACK_SET(x)                          (((x) << PCIE_PHY_REG_1_FORCELOOPBACK_LSB) & PCIE_PHY_REG_1_FORCELOOPBACK_MASK)
#define PCIE_PHY_REG_1_FORCELOOPBACK_RESET                           0x0 // 0
#define PCIE_PHY_REG_1_SEL_CLK_MSB                                   16
#define PCIE_PHY_REG_1_SEL_CLK_LSB                                   15
#define PCIE_PHY_REG_1_SEL_CLK_MASK                                  0x00018000
#define PCIE_PHY_REG_1_SEL_CLK_GET(x)                                (((x) & PCIE_PHY_REG_1_SEL_CLK_MASK) >> PCIE_PHY_REG_1_SEL_CLK_LSB)
#define PCIE_PHY_REG_1_SEL_CLK_SET(x)                                (((x) << PCIE_PHY_REG_1_SEL_CLK_LSB) & PCIE_PHY_REG_1_SEL_CLK_MASK)
#define PCIE_PHY_REG_1_SEL_CLK_RESET                                 0x2 // 2
#define PCIE_PHY_REG_1_SERDES_RX_EQ_MSB                              14
#define PCIE_PHY_REG_1_SERDES_RX_EQ_LSB                              14
#define PCIE_PHY_REG_1_SERDES_RX_EQ_MASK                             0x00004000
#define PCIE_PHY_REG_1_SERDES_RX_EQ_GET(x)                           (((x) & PCIE_PHY_REG_1_SERDES_RX_EQ_MASK) >> PCIE_PHY_REG_1_SERDES_RX_EQ_LSB)
#define PCIE_PHY_REG_1_SERDES_RX_EQ_SET(x)                           (((x) << PCIE_PHY_REG_1_SERDES_RX_EQ_LSB) & PCIE_PHY_REG_1_SERDES_RX_EQ_MASK)
#define PCIE_PHY_REG_1_SERDES_RX_EQ_RESET                            0x0 // 0
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_MSB                           13
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_LSB                           13
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_MASK                          0x00002000
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_GET(x)                        (((x) & PCIE_PHY_REG_1_SERDES_EN_LCKDT_MASK) >> PCIE_PHY_REG_1_SERDES_EN_LCKDT_LSB)
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_SET(x)                        (((x) << PCIE_PHY_REG_1_SERDES_EN_LCKDT_LSB) & PCIE_PHY_REG_1_SERDES_EN_LCKDT_MASK)
#define PCIE_PHY_REG_1_SERDES_EN_LCKDT_RESET                         0x1 // 1
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_MSB                     12
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_LSB                     12
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_MASK                    0x00001000
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_GET(x)                  (((x) & PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_MASK) >> PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_LSB)
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_SET(x)                  (((x) << PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_LSB) & PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_MASK)
#define PCIE_PHY_REG_1_SERDES_PLL_DISABLE_L1_RESET                   0x0 // 0
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_MSB                         11
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_LSB                         11
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_MASK                        0x00000800
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_GET(x)                      (((x) & PCIE_PHY_REG_1_SERDES_POWER_SAVE_MASK) >> PCIE_PHY_REG_1_SERDES_POWER_SAVE_LSB)
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_SET(x)                      (((x) << PCIE_PHY_REG_1_SERDES_POWER_SAVE_LSB) & PCIE_PHY_REG_1_SERDES_POWER_SAVE_MASK)
#define PCIE_PHY_REG_1_SERDES_POWER_SAVE_RESET                       0x0 // 0
#define PCIE_PHY_REG_1_SERDES_CDR_BW_MSB                             10
#define PCIE_PHY_REG_1_SERDES_CDR_BW_LSB                             9
#define PCIE_PHY_REG_1_SERDES_CDR_BW_MASK                            0x00000600
#define PCIE_PHY_REG_1_SERDES_CDR_BW_GET(x)                          (((x) & PCIE_PHY_REG_1_SERDES_CDR_BW_MASK) >> PCIE_PHY_REG_1_SERDES_CDR_BW_LSB)
#define PCIE_PHY_REG_1_SERDES_CDR_BW_SET(x)                          (((x) << PCIE_PHY_REG_1_SERDES_CDR_BW_LSB) & PCIE_PHY_REG_1_SERDES_CDR_BW_MASK)
#define PCIE_PHY_REG_1_SERDES_CDR_BW_RESET                           0x3 // 3
#define PCIE_PHY_REG_1_SERDES_TH_LOS_MSB                             8
#define PCIE_PHY_REG_1_SERDES_TH_LOS_LSB                             7
#define PCIE_PHY_REG_1_SERDES_TH_LOS_MASK                            0x00000180
#define PCIE_PHY_REG_1_SERDES_TH_LOS_GET(x)                          (((x) & PCIE_PHY_REG_1_SERDES_TH_LOS_MASK) >> PCIE_PHY_REG_1_SERDES_TH_LOS_LSB)
#define PCIE_PHY_REG_1_SERDES_TH_LOS_SET(x)                          (((x) << PCIE_PHY_REG_1_SERDES_TH_LOS_LSB) & PCIE_PHY_REG_1_SERDES_TH_LOS_MASK)
#define PCIE_PHY_REG_1_SERDES_TH_LOS_RESET                           0x0 // 0
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_MSB                           6
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_LSB                           6
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_MASK                          0x00000040
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_GET(x)                        (((x) & PCIE_PHY_REG_1_SERDES_EN_DEEMP_MASK) >> PCIE_PHY_REG_1_SERDES_EN_DEEMP_LSB)
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_SET(x)                        (((x) << PCIE_PHY_REG_1_SERDES_EN_DEEMP_LSB) & PCIE_PHY_REG_1_SERDES_EN_DEEMP_MASK)
#define PCIE_PHY_REG_1_SERDES_EN_DEEMP_RESET                         0x1 // 1
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_MSB                           5
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_LSB                           5
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_MASK                          0x00000020
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_GET(x)                        (((x) & PCIE_PHY_REG_1_SERDES_HALFTXDR_MASK) >> PCIE_PHY_REG_1_SERDES_HALFTXDR_LSB)
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_SET(x)                        (((x) << PCIE_PHY_REG_1_SERDES_HALFTXDR_LSB) & PCIE_PHY_REG_1_SERDES_HALFTXDR_MASK)
#define PCIE_PHY_REG_1_SERDES_HALFTXDR_RESET                         0x0 // 0
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_MSB                            4
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_LSB                            4
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_MASK                           0x00000010
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_GET(x)                         (((x) & PCIE_PHY_REG_1_SERDES_SEL_HSP_MASK) >> PCIE_PHY_REG_1_SERDES_SEL_HSP_LSB)
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_SET(x)                         (((x) << PCIE_PHY_REG_1_SERDES_SEL_HSP_LSB) & PCIE_PHY_REG_1_SERDES_SEL_HSP_MASK)
#define PCIE_PHY_REG_1_SERDES_SEL_HSP_RESET                          0x1 // 1
#define PCIE_PHY_REG_1_S_MSB                                         3
#define PCIE_PHY_REG_1_S_LSB                                         0
#define PCIE_PHY_REG_1_S_MASK                                        0x0000000f
#define PCIE_PHY_REG_1_S_GET(x)                                      (((x) & PCIE_PHY_REG_1_S_MASK) >> PCIE_PHY_REG_1_S_LSB)
#define PCIE_PHY_REG_1_S_SET(x)                                      (((x) << PCIE_PHY_REG_1_S_LSB) & PCIE_PHY_REG_1_S_MASK)
#define PCIE_PHY_REG_1_S_RESET                                       0xe // 14
#define PCIE_PHY_REG_1_ADDRESS                                       0x18116cc0

#define AR934X_GPIO_BASE               0x18040000
#define AR934X_GPIO_OE                 AR934X_GPIO_BASE + 0x0
#define AR934X_GPIO_IN                 AR934X_GPIO_BASE + 0x4
#define AR934X_GPIO_OUT                AR934X_GPIO_BASE + 0x8
#define AR934X_GPIO_SET                AR934X_GPIO_BASE + 0xC
#define AR934X_GPIO_CLEAR              AR934X_GPIO_BASE + 0x10
#define AR934X_GPIO_INT                AR934X_GPIO_BASE + 0x14
#define AR934X_GPIO_INT_TYPE           AR934X_GPIO_BASE + 0x18
#define AR934X_GPIO_INT_POLARITY       AR934X_GPIO_BASE + 0x1C
#define AR934X_GPIO_INT_PENDING        AR934X_GPIO_BASE + 0x20
#define AR934X_GPIO_INT_MASK           AR934X_GPIO_BASE + 0x24
#define AR934X_GPIO_IN_ETH_SWITCH_LED  AR934X_GPIO_BASE + 0x28
#define AR934X_GPIO_OUT_FUNCTION0      AR934X_GPIO_BASE + 0x2C
#define AR934X_GPIO_OUT_FUNCTION1      AR934X_GPIO_BASE + 0x30
#define AR934X_GPIO_OUT_FUNCTION2      AR934X_GPIO_BASE + 0x34
#define AR934X_GPIO_OUT_FUNCTION3      AR934X_GPIO_BASE + 0x38
#define AR934X_GPIO_OUT_FUNCTION4      AR934X_GPIO_BASE + 0x3C
#define AR934X_GPIO_IN_ENABLE0         AR934X_GPIO_BASE + 0x44
#define AR934X_GPIO_IN_ENABLE1         AR934X_GPIO_BASE + 0x48
#define AR934X_GPIO_IN_ENABLE2         AR934X_GPIO_BASE + 0x4C
#define AR934X_GPIO_IN_ENABLE3         AR934X_GPIO_BASE + 0x50
#define AR934X_GPIO_IN_ENABLE4         AR934X_GPIO_BASE + 0x54
#define AR934X_GPIO_IN_ENABLE9         AR934X_GPIO_BASE + 0x68
#define AR934X_GPIO_FUNCTION           AR934X_GPIO_BASE + 0x6C

#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_MSB                         31
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_LSB                         24
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_MASK                        0xff000000
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_GET(x)                      (((x) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_MASK) >> GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_LSB)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_SET(x)                      (((x) << GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_LSB) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_MASK)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_RESET                       0xb // 11
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MSB                         23
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB                         16
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK                        0x00ff0000
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_GET(x)                      (((x) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK) >> GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_SET(x)                      (((x) << GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_RESET                       0xa // 10
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_MSB                         15
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_LSB                         8
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_MASK                        0x0000ff00
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_GET(x)                      (((x) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_MASK) >> GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_LSB)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_SET(x)                      (((x) << GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_LSB) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_MASK)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_5_RESET                       0x9 // 9
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MSB                         7
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_LSB                         0
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK                        0x000000ff
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_GET(x)                      (((x) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK) >> GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_LSB)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_SET(x)                      (((x) << GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_LSB) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_RESET                       0x14 // 20
#define GPIO_OUT_FUNCTION1_ADDRESS                                   0x18040030

#endif /* _AR934X_SOC_H */
