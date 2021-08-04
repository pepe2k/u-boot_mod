/*
 * QCA 955x series processor SOC registers
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

#ifndef _QCA955X_H
#define _QCA955X_H

#ifndef __ASSEMBLY__
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/types.h>
#include <linux/types.h>
#endif /* __ASSEMBLY__ */

#undef is_qca955x
#undef is_sco

#define is_qca955x()	(1)
#define is_sco()	(1)

#define CPU_PLL_CONFIG_UPDATING_MSB                                  31
#define CPU_PLL_CONFIG_UPDATING_LSB                                  31
#define CPU_PLL_CONFIG_UPDATING_MASK                                 0x80000000
#define CPU_PLL_CONFIG_UPDATING_GET(x)                               (((x) & CPU_PLL_CONFIG_UPDATING_MASK) >> CPU_PLL_CONFIG_UPDATING_LSB)
#define CPU_PLL_CONFIG_UPDATING_SET(x)                               (((x) << CPU_PLL_CONFIG_UPDATING_LSB) & CPU_PLL_CONFIG_UPDATING_MASK)
#define CPU_PLL_CONFIG_UPDATING_RESET                                0x1 // 1
#define CPU_PLL_CONFIG_PLLPWD_MSB                                    30
#define CPU_PLL_CONFIG_PLLPWD_LSB                                    30
#define CPU_PLL_CONFIG_PLLPWD_MASK                                   0x40000000
#define CPU_PLL_CONFIG_PLLPWD_GET(x)                                 (((x) & CPU_PLL_CONFIG_PLLPWD_MASK) >> CPU_PLL_CONFIG_PLLPWD_LSB)
#define CPU_PLL_CONFIG_PLLPWD_SET(x)                                 (((x) << CPU_PLL_CONFIG_PLLPWD_LSB) & CPU_PLL_CONFIG_PLLPWD_MASK)
#define CPU_PLL_CONFIG_PLLPWD_RESET                                  0x1 // 1
#define CPU_PLL_CONFIG_SPARE_MSB                                     29
#define CPU_PLL_CONFIG_SPARE_LSB                                     22
#define CPU_PLL_CONFIG_SPARE_MASK                                    0x3fc00000
#define CPU_PLL_CONFIG_SPARE_GET(x)                                  (((x) & CPU_PLL_CONFIG_SPARE_MASK) >> CPU_PLL_CONFIG_SPARE_LSB)
#define CPU_PLL_CONFIG_SPARE_SET(x)                                  (((x) << CPU_PLL_CONFIG_SPARE_LSB) & CPU_PLL_CONFIG_SPARE_MASK)
#define CPU_PLL_CONFIG_SPARE_RESET                                   0x0 // 0
#define CPU_PLL_CONFIG_OUTDIV_MSB                                    21
#define CPU_PLL_CONFIG_OUTDIV_LSB                                    19
#define CPU_PLL_CONFIG_OUTDIV_MASK                                   0x00380000
#define CPU_PLL_CONFIG_OUTDIV_GET(x)                                 (((x) & CPU_PLL_CONFIG_OUTDIV_MASK) >> CPU_PLL_CONFIG_OUTDIV_LSB)
#define CPU_PLL_CONFIG_OUTDIV_SET(x)                                 (((x) << CPU_PLL_CONFIG_OUTDIV_LSB) & CPU_PLL_CONFIG_OUTDIV_MASK)
#define CPU_PLL_CONFIG_OUTDIV_RESET                                  0x0 // 0
#define CPU_PLL_CONFIG_RANGE_MSB                                     18
#define CPU_PLL_CONFIG_RANGE_LSB                                     17
#define CPU_PLL_CONFIG_RANGE_MASK                                    0x00060000
#define CPU_PLL_CONFIG_RANGE_GET(x)                                  (((x) & CPU_PLL_CONFIG_RANGE_MASK) >> CPU_PLL_CONFIG_RANGE_LSB)
#define CPU_PLL_CONFIG_RANGE_SET(x)                                  (((x) << CPU_PLL_CONFIG_RANGE_LSB) & CPU_PLL_CONFIG_RANGE_MASK)
#define CPU_PLL_CONFIG_RANGE_RESET                                   0x3 // 3
#define CPU_PLL_CONFIG_REFDIV_MSB                                    16
#define CPU_PLL_CONFIG_REFDIV_LSB                                    12
#define CPU_PLL_CONFIG_REFDIV_MASK                                   0x0001f000
#define CPU_PLL_CONFIG_REFDIV_GET(x)                                 (((x) & CPU_PLL_CONFIG_REFDIV_MASK) >> CPU_PLL_CONFIG_REFDIV_LSB)
#define CPU_PLL_CONFIG_REFDIV_SET(x)                                 (((x) << CPU_PLL_CONFIG_REFDIV_LSB) & CPU_PLL_CONFIG_REFDIV_MASK)
#define CPU_PLL_CONFIG_REFDIV_RESET                                  0x2 // 2
#define CPU_PLL_CONFIG_NINT_MSB                                      11
#define CPU_PLL_CONFIG_NINT_LSB                                      6
#define CPU_PLL_CONFIG_NINT_MASK                                     0x00000fc0
#define CPU_PLL_CONFIG_NINT_GET(x)                                   (((x) & CPU_PLL_CONFIG_NINT_MASK) >> CPU_PLL_CONFIG_NINT_LSB)
#define CPU_PLL_CONFIG_NINT_SET(x)                                   (((x) << CPU_PLL_CONFIG_NINT_LSB) & CPU_PLL_CONFIG_NINT_MASK)
#define CPU_PLL_CONFIG_NINT_RESET                                    0x14 // 20
#define CPU_PLL_CONFIG_NFRAC_MSB                                     5
#define CPU_PLL_CONFIG_NFRAC_LSB                                     0
#define CPU_PLL_CONFIG_NFRAC_MASK                                    0x0000003f
#define CPU_PLL_CONFIG_NFRAC_GET(x)                                  (((x) & CPU_PLL_CONFIG_NFRAC_MASK) >> CPU_PLL_CONFIG_NFRAC_LSB)
#define CPU_PLL_CONFIG_NFRAC_SET(x)                                  (((x) << CPU_PLL_CONFIG_NFRAC_LSB) & CPU_PLL_CONFIG_NFRAC_MASK)
#define CPU_PLL_CONFIG_NFRAC_RESET                                   0x10 // 16
#define CPU_PLL_CONFIG_ADDRESS                                       0x18050000

#define DDR_EMR2_ADDRESS                                             0x180000bc
#define DDR_EMR3_ADDRESS                                             0x180000c0

#define DDR_PLL_CONFIG_UPDATING_MSB                                  31
#define DDR_PLL_CONFIG_UPDATING_LSB                                  31
#define DDR_PLL_CONFIG_UPDATING_MASK                                 0x80000000
#define DDR_PLL_CONFIG_UPDATING_GET(x)                               (((x) & DDR_PLL_CONFIG_UPDATING_MASK) >> DDR_PLL_CONFIG_UPDATING_LSB)
#define DDR_PLL_CONFIG_UPDATING_SET(x)                               (((x) << DDR_PLL_CONFIG_UPDATING_LSB) & DDR_PLL_CONFIG_UPDATING_MASK)
#define DDR_PLL_CONFIG_UPDATING_RESET                                0x1 // 1
#define DDR_PLL_CONFIG_PLLPWD_MSB                                    30
#define DDR_PLL_CONFIG_PLLPWD_LSB                                    30
#define DDR_PLL_CONFIG_PLLPWD_MASK                                   0x40000000
#define DDR_PLL_CONFIG_PLLPWD_GET(x)                                 (((x) & DDR_PLL_CONFIG_PLLPWD_MASK) >> DDR_PLL_CONFIG_PLLPWD_LSB)
#define DDR_PLL_CONFIG_PLLPWD_SET(x)                                 (((x) << DDR_PLL_CONFIG_PLLPWD_LSB) & DDR_PLL_CONFIG_PLLPWD_MASK)
#define DDR_PLL_CONFIG_PLLPWD_RESET                                  0x1 // 1
#define DDR_PLL_CONFIG_SPARE_MSB                                     29
#define DDR_PLL_CONFIG_SPARE_LSB                                     26
#define DDR_PLL_CONFIG_SPARE_MASK                                    0x3c000000
#define DDR_PLL_CONFIG_SPARE_GET(x)                                  (((x) & DDR_PLL_CONFIG_SPARE_MASK) >> DDR_PLL_CONFIG_SPARE_LSB)
#define DDR_PLL_CONFIG_SPARE_SET(x)                                  (((x) << DDR_PLL_CONFIG_SPARE_LSB) & DDR_PLL_CONFIG_SPARE_MASK)
#define DDR_PLL_CONFIG_SPARE_RESET                                   0x0 // 0
#define DDR_PLL_CONFIG_OUTDIV_MSB                                    25
#define DDR_PLL_CONFIG_OUTDIV_LSB                                    23
#define DDR_PLL_CONFIG_OUTDIV_MASK                                   0x03800000
#define DDR_PLL_CONFIG_OUTDIV_GET(x)                                 (((x) & DDR_PLL_CONFIG_OUTDIV_MASK) >> DDR_PLL_CONFIG_OUTDIV_LSB)
#define DDR_PLL_CONFIG_OUTDIV_SET(x)                                 (((x) << DDR_PLL_CONFIG_OUTDIV_LSB) & DDR_PLL_CONFIG_OUTDIV_MASK)
#define DDR_PLL_CONFIG_OUTDIV_RESET                                  0x0 // 0
#define DDR_PLL_CONFIG_RANGE_MSB                                     22
#define DDR_PLL_CONFIG_RANGE_LSB                                     21
#define DDR_PLL_CONFIG_RANGE_MASK                                    0x00600000
#define DDR_PLL_CONFIG_RANGE_GET(x)                                  (((x) & DDR_PLL_CONFIG_RANGE_MASK) >> DDR_PLL_CONFIG_RANGE_LSB)
#define DDR_PLL_CONFIG_RANGE_SET(x)                                  (((x) << DDR_PLL_CONFIG_RANGE_LSB) & DDR_PLL_CONFIG_RANGE_MASK)
#define DDR_PLL_CONFIG_RANGE_RESET                                   0x3 // 3
#define DDR_PLL_CONFIG_REFDIV_MSB                                    20
#define DDR_PLL_CONFIG_REFDIV_LSB                                    16
#define DDR_PLL_CONFIG_REFDIV_MASK                                   0x001f0000
#define DDR_PLL_CONFIG_REFDIV_GET(x)                                 (((x) & DDR_PLL_CONFIG_REFDIV_MASK) >> DDR_PLL_CONFIG_REFDIV_LSB)
#define DDR_PLL_CONFIG_REFDIV_SET(x)                                 (((x) << DDR_PLL_CONFIG_REFDIV_LSB) & DDR_PLL_CONFIG_REFDIV_MASK)
#define DDR_PLL_CONFIG_REFDIV_RESET                                  0x2 // 2
#define DDR_PLL_CONFIG_NINT_MSB                                      15
#define DDR_PLL_CONFIG_NINT_LSB                                      10
#define DDR_PLL_CONFIG_NINT_MASK                                     0x0000fc00
#define DDR_PLL_CONFIG_NINT_GET(x)                                   (((x) & DDR_PLL_CONFIG_NINT_MASK) >> DDR_PLL_CONFIG_NINT_LSB)
#define DDR_PLL_CONFIG_NINT_SET(x)                                   (((x) << DDR_PLL_CONFIG_NINT_LSB) & DDR_PLL_CONFIG_NINT_MASK)
#define DDR_PLL_CONFIG_NINT_RESET                                    0x14 // 20
#define DDR_PLL_CONFIG_NFRAC_MSB                                     9
#define DDR_PLL_CONFIG_NFRAC_LSB                                     0
#define DDR_PLL_CONFIG_NFRAC_MASK                                    0x000003ff
#define DDR_PLL_CONFIG_NFRAC_GET(x)                                  (((x) & DDR_PLL_CONFIG_NFRAC_MASK) >> DDR_PLL_CONFIG_NFRAC_LSB)
#define DDR_PLL_CONFIG_NFRAC_SET(x)                                  (((x) << DDR_PLL_CONFIG_NFRAC_LSB) & DDR_PLL_CONFIG_NFRAC_MASK)
#define DDR_PLL_CONFIG_NFRAC_RESET                                   0x200 // 512
#define DDR_PLL_CONFIG_ADDRESS                                       0x18050004

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
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_MSB                             20
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_LSB                             20
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_MASK                            0x00100000
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_GET(x)                          (((x) & DDR_CTL_CONFIG_GE0_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_GE0_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_SET(x)                          (((x) << DDR_CTL_CONFIG_GE0_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_GE0_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_GE0_SRAM_SYNC_RESET                           0x1 // 1
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_MSB                             19
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_LSB                             19
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_MASK                            0x00080000
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_GET(x)                          (((x) & DDR_CTL_CONFIG_GE1_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_GE1_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_SET(x)                          (((x) << DDR_CTL_CONFIG_GE1_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_GE1_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_GE1_SRAM_SYNC_RESET                           0x1 // 1
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_MSB                             18
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_LSB                             18
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_MASK                            0x00040000
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_GET(x)                          (((x) & DDR_CTL_CONFIG_USB_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_USB_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_SET(x)                          (((x) << DDR_CTL_CONFIG_USB_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_USB_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_USB_SRAM_SYNC_RESET                           0x1 // 1
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_MSB                            17
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_LSB                            17
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_MASK                           0x00020000
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_GET(x)                         (((x) & DDR_CTL_CONFIG_PCIE_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_PCIE_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_SET(x)                         (((x) << DDR_CTL_CONFIG_PCIE_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_PCIE_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_PCIE_SRAM_SYNC_RESET                          0x1 // 1
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_MSB                            16
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_LSB                            16
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_MASK                           0x00010000
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_GET(x)                         (((x) & DDR_CTL_CONFIG_WMAC_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_WMAC_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_SET(x)                         (((x) << DDR_CTL_CONFIG_WMAC_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_WMAC_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_WMAC_SRAM_SYNC_RESET                          0x1 // 1
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_MSB                       15
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_LSB                       15
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_MASK                      0x00008000
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_GET(x)                    (((x) & DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_SET(x)                    (((x) << DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_RESET                     0x1 // 1
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_MSB                       14
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_LSB                       14
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_MASK                      0x00004000
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_GET(x)                    (((x) & DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_MASK) >> DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_LSB)
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_SET(x)                    (((x) << DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_LSB) & DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_MASK)
#define DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_RESET                     0x1 // 1
#define DDR_CTL_CONFIG_SPARE_MSB                                     13
#define DDR_CTL_CONFIG_SPARE_LSB                                     7
#define DDR_CTL_CONFIG_SPARE_MASK                                    0x00003f80
#define DDR_CTL_CONFIG_SPARE_GET(x)                                  (((x) & DDR_CTL_CONFIG_SPARE_MASK) >> DDR_CTL_CONFIG_SPARE_LSB)
#define DDR_CTL_CONFIG_SPARE_SET(x)                                  (((x) << DDR_CTL_CONFIG_SPARE_LSB) & DDR_CTL_CONFIG_SPARE_MASK)
#define DDR_CTL_CONFIG_SPARE_RESET                                   0x0 // 0
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_MSB                              6
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_LSB                              6
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_MASK                             0x00000040
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_GET(x)                           (((x) & DDR_CTL_CONFIG_PAD_DDR2_SEL_MASK) >> DDR_CTL_CONFIG_PAD_DDR2_SEL_LSB)
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_SET(x)                           (((x) << DDR_CTL_CONFIG_PAD_DDR2_SEL_LSB) & DDR_CTL_CONFIG_PAD_DDR2_SEL_MASK)
#define DDR_CTL_CONFIG_PAD_DDR2_SEL_RESET                            0x0 // 0
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_MSB                             4
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_LSB                             4
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_MASK                            0x00000010
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_GET(x)                          (((x) & DDR_CTL_CONFIG_GATE_SRAM_CLK_MASK) >> DDR_CTL_CONFIG_GATE_SRAM_CLK_LSB)
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_SET(x)                          (((x) << DDR_CTL_CONFIG_GATE_SRAM_CLK_LSB) & DDR_CTL_CONFIG_GATE_SRAM_CLK_MASK)
#define DDR_CTL_CONFIG_GATE_SRAM_CLK_RESET                           0x0 // 0
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_MSB                              3
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_LSB                              3
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_MASK                             0x00000008
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_GET(x)                           (((x) & DDR_CTL_CONFIG_SRAM_REQ_ACK_MASK) >> DDR_CTL_CONFIG_SRAM_REQ_ACK_LSB)
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_SET(x)                           (((x) << DDR_CTL_CONFIG_SRAM_REQ_ACK_LSB) & DDR_CTL_CONFIG_SRAM_REQ_ACK_MASK)
#define DDR_CTL_CONFIG_SRAM_REQ_ACK_RESET                            0x0 // 0
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_MSB                              2
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_LSB                              2
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_MASK                             0x00000004
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_GET(x)                           (((x) & DDR_CTL_CONFIG_CPU_DDR_SYNC_MASK) >> DDR_CTL_CONFIG_CPU_DDR_SYNC_LSB)
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_SET(x)                           (((x) << DDR_CTL_CONFIG_CPU_DDR_SYNC_LSB) & DDR_CTL_CONFIG_CPU_DDR_SYNC_MASK)
#define DDR_CTL_CONFIG_CPU_DDR_SYNC_RESET                            0x0 // 0
#define DDR_CTL_CONFIG_HALF_WIDTH_MSB                                1
#define DDR_CTL_CONFIG_HALF_WIDTH_LSB                                1
#define DDR_CTL_CONFIG_HALF_WIDTH_MASK                               0x00000002
#define DDR_CTL_CONFIG_HALF_WIDTH_GET(x)                             (((x) & DDR_CTL_CONFIG_HALF_WIDTH_MASK) >> DDR_CTL_CONFIG_HALF_WIDTH_LSB)
#define DDR_CTL_CONFIG_HALF_WIDTH_SET(x)                             (((x) << DDR_CTL_CONFIG_HALF_WIDTH_LSB) & DDR_CTL_CONFIG_HALF_WIDTH_MASK)
#define DDR_CTL_CONFIG_HALF_WIDTH_RESET                              0x1 // 1
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_MSB                             0
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_LSB                             0
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_MASK                            0x00000001
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_GET(x)                          (((x) & DDR_CTL_CONFIG_SDRAM_MODE_EN_MASK) >> DDR_CTL_CONFIG_SDRAM_MODE_EN_LSB)
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_SET(x)                          (((x) << DDR_CTL_CONFIG_SDRAM_MODE_EN_LSB) & DDR_CTL_CONFIG_SDRAM_MODE_EN_MASK)
#define DDR_CTL_CONFIG_SDRAM_MODE_EN_RESET                           0x0 // 0
#define DDR_CTL_CONFIG_ADDRESS                                       0x18000108

#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_MSB                            31
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_LSB                            31
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_MASK                           0x80000000
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_GET(x)                         (((x) & DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_MASK) >> DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_LSB)
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_SET(x)                         (((x) << DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_LSB) & DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_MASK)
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQ_RESET                          0x0 // 0
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_MSB                           30
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_LSB                           30
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_MASK                          0x40000000
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_GET(x)                        (((x) & DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_MASK) >> DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_LSB)
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_SET(x)                        (((x) << DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_LSB) & DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_MASK)
#define DDR_DEBUG_RD_CNTL_FORCE_WR_DQS_RESET                         0x0 // 0
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_MSB                             29
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_LSB                             29
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_MASK                            0x20000000
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_GET(x)                          (((x) & DDR_DEBUG_RD_CNTL_USE_LB_CLK_MASK) >> DDR_DEBUG_RD_CNTL_USE_LB_CLK_LSB)
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_SET(x)                          (((x) << DDR_DEBUG_RD_CNTL_USE_LB_CLK_LSB) & DDR_DEBUG_RD_CNTL_USE_LB_CLK_MASK)
#define DDR_DEBUG_RD_CNTL_USE_LB_CLK_RESET                           0x0 // 0
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_MSB                            28
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_LSB                            28
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_MASK                           0x10000000
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_GET(x)                         (((x) & DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_MASK) >> DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_LSB)
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_SET(x)                         (((x) << DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_LSB) & DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_MASK)
#define DDR_DEBUG_RD_CNTL_LB_SRC_CK_P_RESET                          0x1 // 1
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_MSB                            27
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_LSB                            27
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_MASK                           0x08000000
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_GET(x)                         (((x) & DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_MASK) >> DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_LSB)
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_SET(x)                         (((x) << DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_LSB) & DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_MASK)
#define DDR_DEBUG_RD_CNTL_EN_RD_ON_WR_RESET                          0x0 // 0
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_MSB                          14
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_LSB                          13
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_MASK                         0x00006000
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_GET(x)                       (((x) & DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_MASK) >> DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_LSB)
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_SET(x)                       (((x) << DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_LSB) & DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_MASK)
#define DDR_DEBUG_RD_CNTL_GATE_TAP_PDLY_RESET                        0x0 // 0
#define DDR_DEBUG_RD_CNTL_GATE_TAP_MSB                               12
#define DDR_DEBUG_RD_CNTL_GATE_TAP_LSB                               8
#define DDR_DEBUG_RD_CNTL_GATE_TAP_MASK                              0x00001f00
#define DDR_DEBUG_RD_CNTL_GATE_TAP_GET(x)                            (((x) & DDR_DEBUG_RD_CNTL_GATE_TAP_MASK) >> DDR_DEBUG_RD_CNTL_GATE_TAP_LSB)
#define DDR_DEBUG_RD_CNTL_GATE_TAP_SET(x)                            (((x) << DDR_DEBUG_RD_CNTL_GATE_TAP_LSB) & DDR_DEBUG_RD_CNTL_GATE_TAP_MASK)
#define DDR_DEBUG_RD_CNTL_GATE_TAP_RESET                             0x1 // 1
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_MSB                          6
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_LSB                          5
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_MASK                         0x00000060
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_GET(x)                       (((x) & DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_MASK) >> DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_LSB)
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_SET(x)                       (((x) << DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_LSB) & DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_MASK)
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_PDLY_RESET                        0x0 // 0
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_MSB                               4
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_LSB                               0
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_MASK                              0x0000001f
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_GET(x)                            (((x) & DDR_DEBUG_RD_CNTL_CK_P_TAP_MASK) >> DDR_DEBUG_RD_CNTL_CK_P_TAP_LSB)
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_SET(x)                            (((x) << DDR_DEBUG_RD_CNTL_CK_P_TAP_LSB) & DDR_DEBUG_RD_CNTL_CK_P_TAP_MASK)
#define DDR_DEBUG_RD_CNTL_CK_P_TAP_RESET                             0x1 // 1
#define DDR_DEBUG_RD_CNTL_ADDRESS                                    0x18000118

#define DDR2_CONFIG_DDR2_TWL_MSB                                     13
#define DDR2_CONFIG_DDR2_TWL_LSB                                     10
#define DDR2_CONFIG_DDR2_TWL_MASK                                    0x00003c00
#define DDR2_CONFIG_DDR2_TWL_GET(x)                                  (((x) & DDR2_CONFIG_DDR2_TWL_MASK) >> DDR2_CONFIG_DDR2_TWL_LSB)
#define DDR2_CONFIG_DDR2_TWL_SET(x)                                  (((x) << DDR2_CONFIG_DDR2_TWL_LSB) & DDR2_CONFIG_DDR2_TWL_MASK)
#define DDR2_CONFIG_DDR2_TWL_RESET                                   0x1 // 1
#define DDR2_CONFIG_DDR2_ODT_MSB                                     9
#define DDR2_CONFIG_DDR2_ODT_LSB                                     9
#define DDR2_CONFIG_DDR2_ODT_MASK                                    0x00000200
#define DDR2_CONFIG_DDR2_ODT_GET(x)                                  (((x) & DDR2_CONFIG_DDR2_ODT_MASK) >> DDR2_CONFIG_DDR2_ODT_LSB)
#define DDR2_CONFIG_DDR2_ODT_SET(x)                                  (((x) << DDR2_CONFIG_DDR2_ODT_LSB) & DDR2_CONFIG_DDR2_ODT_MASK)
#define DDR2_CONFIG_DDR2_ODT_RESET                                   0x1 // 1
#define DDR2_CONFIG_TFAW_MSB                                         7
#define DDR2_CONFIG_TFAW_LSB                                         2
#define DDR2_CONFIG_TFAW_MASK                                        0x000000fc
#define DDR2_CONFIG_TFAW_GET(x)                                      (((x) & DDR2_CONFIG_TFAW_MASK) >> DDR2_CONFIG_TFAW_LSB)
#define DDR2_CONFIG_TFAW_SET(x)                                      (((x) << DDR2_CONFIG_TFAW_LSB) & DDR2_CONFIG_TFAW_MASK)
#define DDR2_CONFIG_TFAW_RESET                                       0x16 // 22
#define DDR2_CONFIG_ENABLE_DDR2_MSB                                  0
#define DDR2_CONFIG_ENABLE_DDR2_LSB                                  0
#define DDR2_CONFIG_ENABLE_DDR2_MASK                                 0x00000001
#define DDR2_CONFIG_ENABLE_DDR2_GET(x)                               (((x) & DDR2_CONFIG_ENABLE_DDR2_MASK) >> DDR2_CONFIG_ENABLE_DDR2_LSB)
#define DDR2_CONFIG_ENABLE_DDR2_SET(x)                               (((x) << DDR2_CONFIG_ENABLE_DDR2_LSB) & DDR2_CONFIG_ENABLE_DDR2_MASK)
#define DDR2_CONFIG_ENABLE_DDR2_RESET                                0x0 // 0
#define DDR2_CONFIG_ADDRESS                                          0x180000b8

#define DDR_CONTROL_EMR3S_MSB                                        5
#define DDR_CONTROL_EMR3S_LSB                                        5
#define DDR_CONTROL_EMR3S_MASK                                       0x00000020
#define DDR_CONTROL_EMR3S_GET(x)                                     (((x) & DDR_CONTROL_EMR3S_MASK) >> DDR_CONTROL_EMR3S_LSB)
#define DDR_CONTROL_EMR3S_SET(x)                                     (((x) << DDR_CONTROL_EMR3S_LSB) & DDR_CONTROL_EMR3S_MASK)
#define DDR_CONTROL_EMR3S_RESET                                      0x0 // 0
#define DDR_CONTROL_EMR2S_MSB                                        4
#define DDR_CONTROL_EMR2S_LSB                                        4
#define DDR_CONTROL_EMR2S_MASK                                       0x00000010
#define DDR_CONTROL_EMR2S_GET(x)                                     (((x) & DDR_CONTROL_EMR2S_MASK) >> DDR_CONTROL_EMR2S_LSB)
#define DDR_CONTROL_EMR2S_SET(x)                                     (((x) << DDR_CONTROL_EMR2S_LSB) & DDR_CONTROL_EMR2S_MASK)
#define DDR_CONTROL_EMR2S_RESET                                      0x0 // 0
#define DDR_CONTROL_PREA_MSB                                         3
#define DDR_CONTROL_PREA_LSB                                         3
#define DDR_CONTROL_PREA_MASK                                        0x00000008
#define DDR_CONTROL_PREA_GET(x)                                      (((x) & DDR_CONTROL_PREA_MASK) >> DDR_CONTROL_PREA_LSB)
#define DDR_CONTROL_PREA_SET(x)                                      (((x) << DDR_CONTROL_PREA_LSB) & DDR_CONTROL_PREA_MASK)
#define DDR_CONTROL_PREA_RESET                                       0x0 // 0
#define DDR_CONTROL_REF_MSB                                          2
#define DDR_CONTROL_REF_LSB                                          2
#define DDR_CONTROL_REF_MASK                                         0x00000004
#define DDR_CONTROL_REF_GET(x)                                       (((x) & DDR_CONTROL_REF_MASK) >> DDR_CONTROL_REF_LSB)
#define DDR_CONTROL_REF_SET(x)                                       (((x) << DDR_CONTROL_REF_LSB) & DDR_CONTROL_REF_MASK)
#define DDR_CONTROL_REF_RESET                                        0x0 // 0
#define DDR_CONTROL_EMRS_MSB                                         1
#define DDR_CONTROL_EMRS_LSB                                         1
#define DDR_CONTROL_EMRS_MASK                                        0x00000002
#define DDR_CONTROL_EMRS_GET(x)                                      (((x) & DDR_CONTROL_EMRS_MASK) >> DDR_CONTROL_EMRS_LSB)
#define DDR_CONTROL_EMRS_SET(x)                                      (((x) << DDR_CONTROL_EMRS_LSB) & DDR_CONTROL_EMRS_MASK)
#define DDR_CONTROL_EMRS_RESET                                       0x0 // 0
#define DDR_CONTROL_MRS_MSB                                          0
#define DDR_CONTROL_MRS_LSB                                          0
#define DDR_CONTROL_MRS_MASK                                         0x00000001
#define DDR_CONTROL_MRS_GET(x)                                       (((x) & DDR_CONTROL_MRS_MASK) >> DDR_CONTROL_MRS_LSB)
#define DDR_CONTROL_MRS_SET(x)                                       (((x) << DDR_CONTROL_MRS_LSB) & DDR_CONTROL_MRS_MASK)
#define DDR_CONTROL_MRS_RESET                                        0x0 // 0
#define DDR_CONTROL_ADDRESS                                          0x18000010

#define DDR_CONFIG_CAS_LATENCY_MSB_MSB                               31
#define DDR_CONFIG_CAS_LATENCY_MSB_LSB                               31
#define DDR_CONFIG_CAS_LATENCY_MSB_MASK                              0x80000000
#define DDR_CONFIG_CAS_LATENCY_MSB_GET(x)                            (((x) & DDR_CONFIG_CAS_LATENCY_MSB_MASK) >> DDR_CONFIG_CAS_LATENCY_MSB_LSB)
#define DDR_CONFIG_CAS_LATENCY_MSB_SET(x)                            (((x) << DDR_CONFIG_CAS_LATENCY_MSB_LSB) & DDR_CONFIG_CAS_LATENCY_MSB_MASK)
#define DDR_CONFIG_CAS_LATENCY_MSB_RESET                             0x0 // 0
#define DDR_CONFIG_OPEN_PAGE_MSB                                     30
#define DDR_CONFIG_OPEN_PAGE_LSB                                     30
#define DDR_CONFIG_OPEN_PAGE_MASK                                    0x40000000
#define DDR_CONFIG_OPEN_PAGE_GET(x)                                  (((x) & DDR_CONFIG_OPEN_PAGE_MASK) >> DDR_CONFIG_OPEN_PAGE_LSB)
#define DDR_CONFIG_OPEN_PAGE_SET(x)                                  (((x) << DDR_CONFIG_OPEN_PAGE_LSB) & DDR_CONFIG_OPEN_PAGE_MASK)
#define DDR_CONFIG_OPEN_PAGE_RESET                                   0x1 // 1
#define DDR_CONFIG_CAS_LATENCY_MSB                                   29
#define DDR_CONFIG_CAS_LATENCY_LSB                                   27
#define DDR_CONFIG_CAS_LATENCY_MASK                                  0x38000000
#define DDR_CONFIG_CAS_LATENCY_GET(x)                                (((x) & DDR_CONFIG_CAS_LATENCY_MASK) >> DDR_CONFIG_CAS_LATENCY_LSB)
#define DDR_CONFIG_CAS_LATENCY_SET(x)                                (((x) << DDR_CONFIG_CAS_LATENCY_LSB) & DDR_CONFIG_CAS_LATENCY_MASK)
#define DDR_CONFIG_CAS_LATENCY_RESET                                 0x6 // 6
#define DDR_CONFIG_TMRD_MSB                                          26
#define DDR_CONFIG_TMRD_LSB                                          23
#define DDR_CONFIG_TMRD_MASK                                         0x07800000
#define DDR_CONFIG_TMRD_GET(x)                                       (((x) & DDR_CONFIG_TMRD_MASK) >> DDR_CONFIG_TMRD_LSB)
#define DDR_CONFIG_TMRD_SET(x)                                       (((x) << DDR_CONFIG_TMRD_LSB) & DDR_CONFIG_TMRD_MASK)
#define DDR_CONFIG_TMRD_RESET                                        0xf // 15
#define DDR_CONFIG_TRFC_MSB                                          22
#define DDR_CONFIG_TRFC_LSB                                          17
#define DDR_CONFIG_TRFC_MASK                                         0x007e0000
#define DDR_CONFIG_TRFC_GET(x)                                       (((x) & DDR_CONFIG_TRFC_MASK) >> DDR_CONFIG_TRFC_LSB)
#define DDR_CONFIG_TRFC_SET(x)                                       (((x) << DDR_CONFIG_TRFC_LSB) & DDR_CONFIG_TRFC_MASK)
#define DDR_CONFIG_TRFC_RESET                                        0x24 // 36
#define DDR_CONFIG_TRRD_MSB                                          16
#define DDR_CONFIG_TRRD_LSB                                          13
#define DDR_CONFIG_TRRD_MASK                                         0x0001e000
#define DDR_CONFIG_TRRD_GET(x)                                       (((x) & DDR_CONFIG_TRRD_MASK) >> DDR_CONFIG_TRRD_LSB)
#define DDR_CONFIG_TRRD_SET(x)                                       (((x) << DDR_CONFIG_TRRD_LSB) & DDR_CONFIG_TRRD_MASK)
#define DDR_CONFIG_TRRD_RESET                                        0x4 // 4
#define DDR_CONFIG_TRP_MSB                                           12
#define DDR_CONFIG_TRP_LSB                                           9
#define DDR_CONFIG_TRP_MASK                                          0x00001e00
#define DDR_CONFIG_TRP_GET(x)                                        (((x) & DDR_CONFIG_TRP_MASK) >> DDR_CONFIG_TRP_LSB)
#define DDR_CONFIG_TRP_SET(x)                                        (((x) << DDR_CONFIG_TRP_LSB) & DDR_CONFIG_TRP_MASK)
#define DDR_CONFIG_TRP_RESET                                         0x6 // 6
#define DDR_CONFIG_TRCD_MSB                                          8
#define DDR_CONFIG_TRCD_LSB                                          5
#define DDR_CONFIG_TRCD_MASK                                         0x000001e0
#define DDR_CONFIG_TRCD_GET(x)                                       (((x) & DDR_CONFIG_TRCD_MASK) >> DDR_CONFIG_TRCD_LSB)
#define DDR_CONFIG_TRCD_SET(x)                                       (((x) << DDR_CONFIG_TRCD_LSB) & DDR_CONFIG_TRCD_MASK)
#define DDR_CONFIG_TRCD_RESET                                        0x6 // 6
#define DDR_CONFIG_TRAS_MSB                                          4
#define DDR_CONFIG_TRAS_LSB                                          0
#define DDR_CONFIG_TRAS_MASK                                         0x0000001f
#define DDR_CONFIG_TRAS_GET(x)                                       (((x) & DDR_CONFIG_TRAS_MASK) >> DDR_CONFIG_TRAS_LSB)
#define DDR_CONFIG_TRAS_SET(x)                                       (((x) << DDR_CONFIG_TRAS_LSB) & DDR_CONFIG_TRAS_MASK)
#define DDR_CONFIG_TRAS_RESET                                        0x10 // 16
#define DDR_CONFIG_ADDRESS                                           0x18000000

#define DDR_CONFIG2_HALF_WIDTH_LOW_MSB                               31
#define DDR_CONFIG2_HALF_WIDTH_LOW_LSB                               31
#define DDR_CONFIG2_HALF_WIDTH_LOW_MASK                              0x80000000
#define DDR_CONFIG2_HALF_WIDTH_LOW_GET(x)                            (((x) & DDR_CONFIG2_HALF_WIDTH_LOW_MASK) >> DDR_CONFIG2_HALF_WIDTH_LOW_LSB)
#define DDR_CONFIG2_HALF_WIDTH_LOW_SET(x)                            (((x) << DDR_CONFIG2_HALF_WIDTH_LOW_LSB) & DDR_CONFIG2_HALF_WIDTH_LOW_MASK)
#define DDR_CONFIG2_HALF_WIDTH_LOW_RESET                             0x1 // 1
#define DDR_CONFIG2_SWAP_A26_A27_MSB                                 30
#define DDR_CONFIG2_SWAP_A26_A27_LSB                                 30
#define DDR_CONFIG2_SWAP_A26_A27_MASK                                0x40000000
#define DDR_CONFIG2_SWAP_A26_A27_GET(x)                              (((x) & DDR_CONFIG2_SWAP_A26_A27_MASK) >> DDR_CONFIG2_SWAP_A26_A27_LSB)
#define DDR_CONFIG2_SWAP_A26_A27_SET(x)                              (((x) << DDR_CONFIG2_SWAP_A26_A27_LSB) & DDR_CONFIG2_SWAP_A26_A27_MASK)
#define DDR_CONFIG2_SWAP_A26_A27_RESET                               0x0 // 0
#define DDR_CONFIG2_GATE_OPEN_LATENCY_MSB                            29
#define DDR_CONFIG2_GATE_OPEN_LATENCY_LSB                            26
#define DDR_CONFIG2_GATE_OPEN_LATENCY_MASK                           0x3c000000
#define DDR_CONFIG2_GATE_OPEN_LATENCY_GET(x)                         (((x) & DDR_CONFIG2_GATE_OPEN_LATENCY_MASK) >> DDR_CONFIG2_GATE_OPEN_LATENCY_LSB)
#define DDR_CONFIG2_GATE_OPEN_LATENCY_SET(x)                         (((x) << DDR_CONFIG2_GATE_OPEN_LATENCY_LSB) & DDR_CONFIG2_GATE_OPEN_LATENCY_MASK)
#define DDR_CONFIG2_GATE_OPEN_LATENCY_RESET                          0x6 // 6
#define DDR_CONFIG2_TWTR_MSB                                         25
#define DDR_CONFIG2_TWTR_LSB                                         21
#define DDR_CONFIG2_TWTR_MASK                                        0x03e00000
#define DDR_CONFIG2_TWTR_GET(x)                                      (((x) & DDR_CONFIG2_TWTR_MASK) >> DDR_CONFIG2_TWTR_LSB)
#define DDR_CONFIG2_TWTR_SET(x)                                      (((x) << DDR_CONFIG2_TWTR_LSB) & DDR_CONFIG2_TWTR_MASK)
#define DDR_CONFIG2_TWTR_RESET                                       0xe // 14
#define DDR_CONFIG2_TRTP_MSB                                         20
#define DDR_CONFIG2_TRTP_LSB                                         17
#define DDR_CONFIG2_TRTP_MASK                                        0x001e0000
#define DDR_CONFIG2_TRTP_GET(x)                                      (((x) & DDR_CONFIG2_TRTP_MASK) >> DDR_CONFIG2_TRTP_LSB)
#define DDR_CONFIG2_TRTP_SET(x)                                      (((x) << DDR_CONFIG2_TRTP_LSB) & DDR_CONFIG2_TRTP_MASK)
#define DDR_CONFIG2_TRTP_RESET                                       0x8 // 8
#define DDR_CONFIG2_TRTW_MSB                                         16
#define DDR_CONFIG2_TRTW_LSB                                         12
#define DDR_CONFIG2_TRTW_MASK                                        0x0001f000
#define DDR_CONFIG2_TRTW_GET(x)                                      (((x) & DDR_CONFIG2_TRTW_MASK) >> DDR_CONFIG2_TRTW_LSB)
#define DDR_CONFIG2_TRTW_SET(x)                                      (((x) << DDR_CONFIG2_TRTW_LSB) & DDR_CONFIG2_TRTW_MASK)
#define DDR_CONFIG2_TRTW_RESET                                       0x10 // 16
#define DDR_CONFIG2_TWR_MSB                                          11
#define DDR_CONFIG2_TWR_LSB                                          8
#define DDR_CONFIG2_TWR_MASK                                         0x00000f00
#define DDR_CONFIG2_TWR_GET(x)                                       (((x) & DDR_CONFIG2_TWR_MASK) >> DDR_CONFIG2_TWR_LSB)
#define DDR_CONFIG2_TWR_SET(x)                                       (((x) << DDR_CONFIG2_TWR_LSB) & DDR_CONFIG2_TWR_MASK)
#define DDR_CONFIG2_TWR_RESET                                        0x6 // 6
#define DDR_CONFIG2_CKE_MSB                                          7
#define DDR_CONFIG2_CKE_LSB                                          7
#define DDR_CONFIG2_CKE_MASK                                         0x00000080
#define DDR_CONFIG2_CKE_GET(x)                                       (((x) & DDR_CONFIG2_CKE_MASK) >> DDR_CONFIG2_CKE_LSB)
#define DDR_CONFIG2_CKE_SET(x)                                       (((x) << DDR_CONFIG2_CKE_LSB) & DDR_CONFIG2_CKE_MASK)
#define DDR_CONFIG2_CKE_RESET                                        0x0 // 0
#define DDR_CONFIG2_PHASE_SELECT_MSB                                 6
#define DDR_CONFIG2_PHASE_SELECT_LSB                                 6
#define DDR_CONFIG2_PHASE_SELECT_MASK                                0x00000040
#define DDR_CONFIG2_PHASE_SELECT_GET(x)                              (((x) & DDR_CONFIG2_PHASE_SELECT_MASK) >> DDR_CONFIG2_PHASE_SELECT_LSB)
#define DDR_CONFIG2_PHASE_SELECT_SET(x)                              (((x) << DDR_CONFIG2_PHASE_SELECT_LSB) & DDR_CONFIG2_PHASE_SELECT_MASK)
#define DDR_CONFIG2_PHASE_SELECT_RESET                               0x0 // 0
#define DDR_CONFIG2_CNTL_OE_EN_MSB                                   5
#define DDR_CONFIG2_CNTL_OE_EN_LSB                                   5
#define DDR_CONFIG2_CNTL_OE_EN_MASK                                  0x00000020
#define DDR_CONFIG2_CNTL_OE_EN_GET(x)                                (((x) & DDR_CONFIG2_CNTL_OE_EN_MASK) >> DDR_CONFIG2_CNTL_OE_EN_LSB)
#define DDR_CONFIG2_CNTL_OE_EN_SET(x)                                (((x) << DDR_CONFIG2_CNTL_OE_EN_LSB) & DDR_CONFIG2_CNTL_OE_EN_MASK)
#define DDR_CONFIG2_CNTL_OE_EN_RESET                                 0x1 // 1
#define DDR_CONFIG2_BURST_TYPE_MSB                                   4
#define DDR_CONFIG2_BURST_TYPE_LSB                                   4
#define DDR_CONFIG2_BURST_TYPE_MASK                                  0x00000010
#define DDR_CONFIG2_BURST_TYPE_GET(x)                                (((x) & DDR_CONFIG2_BURST_TYPE_MASK) >> DDR_CONFIG2_BURST_TYPE_LSB)
#define DDR_CONFIG2_BURST_TYPE_SET(x)                                (((x) << DDR_CONFIG2_BURST_TYPE_LSB) & DDR_CONFIG2_BURST_TYPE_MASK)
#define DDR_CONFIG2_BURST_TYPE_RESET                                 0x0 // 0
#define DDR_CONFIG2_BURST_LENGTH_MSB                                 3
#define DDR_CONFIG2_BURST_LENGTH_LSB                                 0
#define DDR_CONFIG2_BURST_LENGTH_MASK                                0x0000000f
#define DDR_CONFIG2_BURST_LENGTH_GET(x)                              (((x) & DDR_CONFIG2_BURST_LENGTH_MASK) >> DDR_CONFIG2_BURST_LENGTH_LSB)
#define DDR_CONFIG2_BURST_LENGTH_SET(x)                              (((x) << DDR_CONFIG2_BURST_LENGTH_LSB) & DDR_CONFIG2_BURST_LENGTH_MASK)
#define DDR_CONFIG2_BURST_LENGTH_RESET                               0x8 // 8
#define DDR_CONFIG2_ADDRESS                                          0x18000004

#define DDR_CONFIG_3_SPARE_MSB                                       31
#define DDR_CONFIG_3_SPARE_LSB                                       4
#define DDR_CONFIG_3_SPARE_MASK                                      0xfffffff0
#define DDR_CONFIG_3_SPARE_GET(x)                                    (((x) & DDR_CONFIG_3_SPARE_MASK) >> DDR_CONFIG_3_SPARE_LSB)
#define DDR_CONFIG_3_SPARE_SET(x)                                    (((x) << DDR_CONFIG_3_SPARE_LSB) & DDR_CONFIG_3_SPARE_MASK)
#define DDR_CONFIG_3_SPARE_RESET                                     0x0 // 0
#define DDR_CONFIG_3_TWR_MSB_MSB                                     3
#define DDR_CONFIG_3_TWR_MSB_LSB                                     3
#define DDR_CONFIG_3_TWR_MSB_MASK                                    0x00000008
#define DDR_CONFIG_3_TWR_MSB_GET(x)                                  (((x) & DDR_CONFIG_3_TWR_MSB_MASK) >> DDR_CONFIG_3_TWR_MSB_LSB)
#define DDR_CONFIG_3_TWR_MSB_SET(x)                                  (((x) << DDR_CONFIG_3_TWR_MSB_LSB) & DDR_CONFIG_3_TWR_MSB_MASK)
#define DDR_CONFIG_3_TWR_MSB_RESET                                   0x0 // 0
#define DDR_CONFIG_3_TRAS_MSB_MSB                                    2
#define DDR_CONFIG_3_TRAS_MSB_LSB                                    2
#define DDR_CONFIG_3_TRAS_MSB_MASK                                   0x00000004
#define DDR_CONFIG_3_TRAS_MSB_GET(x)                                 (((x) & DDR_CONFIG_3_TRAS_MSB_MASK) >> DDR_CONFIG_3_TRAS_MSB_LSB)
#define DDR_CONFIG_3_TRAS_MSB_SET(x)                                 (((x) << DDR_CONFIG_3_TRAS_MSB_LSB) & DDR_CONFIG_3_TRAS_MSB_MASK)
#define DDR_CONFIG_3_TRAS_MSB_RESET                                  0x0 // 0
#define DDR_CONFIG_3_TRFC_LSB_MSB                                    1
#define DDR_CONFIG_3_TRFC_LSB_LSB                                    0
#define DDR_CONFIG_3_TRFC_LSB_MASK                                   0x00000003
#define DDR_CONFIG_3_TRFC_LSB_GET(x)                                 (((x) & DDR_CONFIG_3_TRFC_LSB_MASK) >> DDR_CONFIG_3_TRFC_LSB_LSB)
#define DDR_CONFIG_3_TRFC_LSB_SET(x)                                 (((x) << DDR_CONFIG_3_TRFC_LSB_LSB) & DDR_CONFIG_3_TRFC_LSB_MASK)
#define DDR_CONFIG_3_TRFC_LSB_RESET                                  0x0 // 0
#define DDR_CONFIG_3_ADDRESS                                         0x1800015c

#define DDR_MODE_REGISTER_VALUE_MSB                                  13
#define DDR_MODE_REGISTER_VALUE_LSB                                  0
#define DDR_MODE_REGISTER_VALUE_MASK                                 0x00003fff
#define DDR_MODE_REGISTER_VALUE_GET(x)                               (((x) & DDR_MODE_REGISTER_VALUE_MASK) >> DDR_MODE_REGISTER_VALUE_LSB)
#define DDR_MODE_REGISTER_VALUE_SET(x)                               (((x) << DDR_MODE_REGISTER_VALUE_LSB) & DDR_MODE_REGISTER_VALUE_MASK)
#define DDR_MODE_REGISTER_VALUE_RESET                                0x133 // 307
#define DDR_MODE_REGISTER_ADDRESS                                    0x18000008

#define DDR_EXTENDED_MODE_REGISTER_VALUE_MSB                         13
#define DDR_EXTENDED_MODE_REGISTER_VALUE_LSB                         0
#define DDR_EXTENDED_MODE_REGISTER_VALUE_MASK                        0x00003fff
#define DDR_EXTENDED_MODE_REGISTER_VALUE_GET(x)                      (((x) & DDR_EXTENDED_MODE_REGISTER_VALUE_MASK) >> DDR_EXTENDED_MODE_REGISTER_VALUE_LSB)
#define DDR_EXTENDED_MODE_REGISTER_VALUE_SET(x)                      (((x) << DDR_EXTENDED_MODE_REGISTER_VALUE_LSB) & DDR_EXTENDED_MODE_REGISTER_VALUE_MASK)
#define DDR_EXTENDED_MODE_REGISTER_VALUE_RESET                       0x2 // 2
#define DDR_EXTENDED_MODE_REGISTER_ADDRESS                           0x1800000c

#define DDR_REFRESH_ENABLE_MSB                                       14
#define DDR_REFRESH_ENABLE_LSB                                       14
#define DDR_REFRESH_ENABLE_MASK                                      0x00004000
#define DDR_REFRESH_ENABLE_GET(x)                                    (((x) & DDR_REFRESH_ENABLE_MASK) >> DDR_REFRESH_ENABLE_LSB)
#define DDR_REFRESH_ENABLE_SET(x)                                    (((x) << DDR_REFRESH_ENABLE_LSB) & DDR_REFRESH_ENABLE_MASK)
#define DDR_REFRESH_ENABLE_RESET                                     0x0 // 0
#define DDR_REFRESH_PERIOD_MSB                                       13
#define DDR_REFRESH_PERIOD_LSB                                       0
#define DDR_REFRESH_PERIOD_MASK                                      0x00003fff
#define DDR_REFRESH_PERIOD_GET(x)                                    (((x) & DDR_REFRESH_PERIOD_MASK) >> DDR_REFRESH_PERIOD_LSB)
#define DDR_REFRESH_PERIOD_SET(x)                                    (((x) << DDR_REFRESH_PERIOD_LSB) & DDR_REFRESH_PERIOD_MASK)
#define DDR_REFRESH_PERIOD_RESET                                     0x12c // 300
#define DDR_REFRESH_ADDRESS                                          0x18000014

#define BB_DPLL2_RANGE_MSB                                           31
#define BB_DPLL2_RANGE_LSB                                           31
#define BB_DPLL2_RANGE_MASK                                          0x80000000
#define BB_DPLL2_RANGE_GET(x)                                        (((x) & BB_DPLL2_RANGE_MASK) >> BB_DPLL2_RANGE_LSB)
#define BB_DPLL2_RANGE_SET(x)                                        (((x) << BB_DPLL2_RANGE_LSB) & BB_DPLL2_RANGE_MASK)
#define BB_DPLL2_RANGE_RESET                                         0x0 // 0
#define BB_DPLL2_LOCAL_PLL_MSB                                       30
#define BB_DPLL2_LOCAL_PLL_LSB                                       30
#define BB_DPLL2_LOCAL_PLL_MASK                                      0x40000000
#define BB_DPLL2_LOCAL_PLL_GET(x)                                    (((x) & BB_DPLL2_LOCAL_PLL_MASK) >> BB_DPLL2_LOCAL_PLL_LSB)
#define BB_DPLL2_LOCAL_PLL_SET(x)                                    (((x) << BB_DPLL2_LOCAL_PLL_LSB) & BB_DPLL2_LOCAL_PLL_MASK)
#define BB_DPLL2_LOCAL_PLL_RESET                                     0x0 // 0
#define BB_DPLL2_KI_MSB                                              29
#define BB_DPLL2_KI_LSB                                              26
#define BB_DPLL2_KI_MASK                                             0x3c000000
#define BB_DPLL2_KI_GET(x)                                           (((x) & BB_DPLL2_KI_MASK) >> BB_DPLL2_KI_LSB)
#define BB_DPLL2_KI_SET(x)                                           (((x) << BB_DPLL2_KI_LSB) & BB_DPLL2_KI_MASK)
#define BB_DPLL2_KI_RESET                                            0x6 // 6
#define BB_DPLL2_KD_MSB                                              25
#define BB_DPLL2_KD_LSB                                              19
#define BB_DPLL2_KD_MASK                                             0x03f80000
#define BB_DPLL2_KD_GET(x)                                           (((x) & BB_DPLL2_KD_MASK) >> BB_DPLL2_KD_LSB)
#define BB_DPLL2_KD_SET(x)                                           (((x) << BB_DPLL2_KD_LSB) & BB_DPLL2_KD_MASK)
#define BB_DPLL2_KD_RESET                                            0x7f // 127
#define BB_DPLL2_EN_NEGTRIG_MSB                                      18
#define BB_DPLL2_EN_NEGTRIG_LSB                                      18
#define BB_DPLL2_EN_NEGTRIG_MASK                                     0x00040000
#define BB_DPLL2_EN_NEGTRIG_GET(x)                                   (((x) & BB_DPLL2_EN_NEGTRIG_MASK) >> BB_DPLL2_EN_NEGTRIG_LSB)
#define BB_DPLL2_EN_NEGTRIG_SET(x)                                   (((x) << BB_DPLL2_EN_NEGTRIG_LSB) & BB_DPLL2_EN_NEGTRIG_MASK)
#define BB_DPLL2_EN_NEGTRIG_RESET                                    0x0 // 0
#define BB_DPLL2_SEL_1SDM_MSB                                        17
#define BB_DPLL2_SEL_1SDM_LSB                                        17
#define BB_DPLL2_SEL_1SDM_MASK                                       0x00020000
#define BB_DPLL2_SEL_1SDM_GET(x)                                     (((x) & BB_DPLL2_SEL_1SDM_MASK) >> BB_DPLL2_SEL_1SDM_LSB)
#define BB_DPLL2_SEL_1SDM_SET(x)                                     (((x) << BB_DPLL2_SEL_1SDM_LSB) & BB_DPLL2_SEL_1SDM_MASK)
#define BB_DPLL2_SEL_1SDM_RESET                                      0x0 // 0
#define BB_DPLL2_PLL_PWD_MSB                                         16
#define BB_DPLL2_PLL_PWD_LSB                                         16
#define BB_DPLL2_PLL_PWD_MASK                                        0x00010000
#define BB_DPLL2_PLL_PWD_GET(x)                                      (((x) & BB_DPLL2_PLL_PWD_MASK) >> BB_DPLL2_PLL_PWD_LSB)
#define BB_DPLL2_PLL_PWD_SET(x)                                      (((x) << BB_DPLL2_PLL_PWD_LSB) & BB_DPLL2_PLL_PWD_MASK)
#define BB_DPLL2_PLL_PWD_RESET                                       0x1 // 1
#define BB_DPLL2_OUTDIV_MSB                                          15
#define BB_DPLL2_OUTDIV_LSB                                          13
#define BB_DPLL2_OUTDIV_MASK                                         0x0000e000
#define BB_DPLL2_OUTDIV_GET(x)                                       (((x) & BB_DPLL2_OUTDIV_MASK) >> BB_DPLL2_OUTDIV_LSB)
#define BB_DPLL2_OUTDIV_SET(x)                                       (((x) << BB_DPLL2_OUTDIV_LSB) & BB_DPLL2_OUTDIV_MASK)
#define BB_DPLL2_OUTDIV_RESET                                        0x0 // 0
#define BB_DPLL2_DELTA_MSB                                           12
#define BB_DPLL2_DELTA_LSB                                           7
#define BB_DPLL2_DELTA_MASK                                          0x00001f80
#define BB_DPLL2_DELTA_GET(x)                                        (((x) & BB_DPLL2_DELTA_MASK) >> BB_DPLL2_DELTA_LSB)
#define BB_DPLL2_DELTA_SET(x)                                        (((x) << BB_DPLL2_DELTA_LSB) & BB_DPLL2_DELTA_MASK)
#define BB_DPLL2_DELTA_RESET                                         0x1e // 30
#define BB_DPLL2_TESTINMSB_MSB                                       6
#define BB_DPLL2_TESTINMSB_LSB                                       0
#define BB_DPLL2_TESTINMSB_MASK                                      0x0000007f
#define BB_DPLL2_TESTINMSB_GET(x)                                    (((x) & BB_DPLL2_TESTINMSB_MASK) >> BB_DPLL2_TESTINMSB_LSB)
#define BB_DPLL2_TESTINMSB_SET(x)                                    (((x) << BB_DPLL2_TESTINMSB_LSB) & BB_DPLL2_TESTINMSB_MASK)
#define BB_DPLL2_TESTINMSB_RESET                                     0x0 // 0
#define BB_DPLL2_ADDRESS                                             0x18116184

#define PCIe_DPLL2_RANGE_MSB                                         31
#define PCIe_DPLL2_RANGE_LSB                                         31
#define PCIe_DPLL2_RANGE_MASK                                        0x80000000
#define PCIe_DPLL2_RANGE_GET(x)                                      (((x) & PCIe_DPLL2_RANGE_MASK) >> PCIe_DPLL2_RANGE_LSB)
#define PCIe_DPLL2_RANGE_SET(x)                                      (((x) << PCIe_DPLL2_RANGE_LSB) & PCIe_DPLL2_RANGE_MASK)
#define PCIe_DPLL2_RANGE_RESET                                       0x0 // 0
#define PCIe_DPLL2_LOCAL_PLL_MSB                                     30
#define PCIe_DPLL2_LOCAL_PLL_LSB                                     30
#define PCIe_DPLL2_LOCAL_PLL_MASK                                    0x40000000
#define PCIe_DPLL2_LOCAL_PLL_GET(x)                                  (((x) & PCIe_DPLL2_LOCAL_PLL_MASK) >> PCIe_DPLL2_LOCAL_PLL_LSB)
#define PCIe_DPLL2_LOCAL_PLL_SET(x)                                  (((x) << PCIe_DPLL2_LOCAL_PLL_LSB) & PCIe_DPLL2_LOCAL_PLL_MASK)
#define PCIe_DPLL2_LOCAL_PLL_RESET                                   0x0 // 0
#define PCIe_DPLL2_KI_MSB                                            29
#define PCIe_DPLL2_KI_LSB                                            26
#define PCIe_DPLL2_KI_MASK                                           0x3c000000
#define PCIe_DPLL2_KI_GET(x)                                         (((x) & PCIe_DPLL2_KI_MASK) >> PCIe_DPLL2_KI_LSB)
#define PCIe_DPLL2_KI_SET(x)                                         (((x) << PCIe_DPLL2_KI_LSB) & PCIe_DPLL2_KI_MASK)
#define PCIe_DPLL2_KI_RESET                                          0x6 // 6
#define PCIe_DPLL2_KD_MSB                                            25
#define PCIe_DPLL2_KD_LSB                                            19
#define PCIe_DPLL2_KD_MASK                                           0x03f80000
#define PCIe_DPLL2_KD_GET(x)                                         (((x) & PCIe_DPLL2_KD_MASK) >> PCIe_DPLL2_KD_LSB)
#define PCIe_DPLL2_KD_SET(x)                                         (((x) << PCIe_DPLL2_KD_LSB) & PCIe_DPLL2_KD_MASK)
#define PCIe_DPLL2_KD_RESET                                          0x7f // 127
#define PCIe_DPLL2_EN_NEGTRIG_MSB                                    18
#define PCIe_DPLL2_EN_NEGTRIG_LSB                                    18
#define PCIe_DPLL2_EN_NEGTRIG_MASK                                   0x00040000
#define PCIe_DPLL2_EN_NEGTRIG_GET(x)                                 (((x) & PCIe_DPLL2_EN_NEGTRIG_MASK) >> PCIe_DPLL2_EN_NEGTRIG_LSB)
#define PCIe_DPLL2_EN_NEGTRIG_SET(x)                                 (((x) << PCIe_DPLL2_EN_NEGTRIG_LSB) & PCIe_DPLL2_EN_NEGTRIG_MASK)
#define PCIe_DPLL2_EN_NEGTRIG_RESET                                  0x0 // 0
#define PCIe_DPLL2_SEL_1SDM_MSB                                      17
#define PCIe_DPLL2_SEL_1SDM_LSB                                      17
#define PCIe_DPLL2_SEL_1SDM_MASK                                     0x00020000
#define PCIe_DPLL2_SEL_1SDM_GET(x)                                   (((x) & PCIe_DPLL2_SEL_1SDM_MASK) >> PCIe_DPLL2_SEL_1SDM_LSB)
#define PCIe_DPLL2_SEL_1SDM_SET(x)                                   (((x) << PCIe_DPLL2_SEL_1SDM_LSB) & PCIe_DPLL2_SEL_1SDM_MASK)
#define PCIe_DPLL2_SEL_1SDM_RESET                                    0x0 // 0
#define PCIe_DPLL2_PLL_PWD_MSB                                       16
#define PCIe_DPLL2_PLL_PWD_LSB                                       16
#define PCIe_DPLL2_PLL_PWD_MASK                                      0x00010000
#define PCIe_DPLL2_PLL_PWD_GET(x)                                    (((x) & PCIe_DPLL2_PLL_PWD_MASK) >> PCIe_DPLL2_PLL_PWD_LSB)
#define PCIe_DPLL2_PLL_PWD_SET(x)                                    (((x) << PCIe_DPLL2_PLL_PWD_LSB) & PCIe_DPLL2_PLL_PWD_MASK)
#define PCIe_DPLL2_PLL_PWD_RESET                                     0x1 // 1
#define PCIe_DPLL2_OUTDIV_MSB                                        15
#define PCIe_DPLL2_OUTDIV_LSB                                        13
#define PCIe_DPLL2_OUTDIV_MASK                                       0x0000e000
#define PCIe_DPLL2_OUTDIV_GET(x)                                     (((x) & PCIe_DPLL2_OUTDIV_MASK) >> PCIe_DPLL2_OUTDIV_LSB)
#define PCIe_DPLL2_OUTDIV_SET(x)                                     (((x) << PCIe_DPLL2_OUTDIV_LSB) & PCIe_DPLL2_OUTDIV_MASK)
#define PCIe_DPLL2_OUTDIV_RESET                                      0x0 // 0
#define PCIe_DPLL2_DELTA_MSB                                         12
#define PCIe_DPLL2_DELTA_LSB                                         7
#define PCIe_DPLL2_DELTA_MASK                                        0x00001f80
#define PCIe_DPLL2_DELTA_GET(x)                                      (((x) & PCIe_DPLL2_DELTA_MASK) >> PCIe_DPLL2_DELTA_LSB)
#define PCIe_DPLL2_DELTA_SET(x)                                      (((x) << PCIe_DPLL2_DELTA_LSB) & PCIe_DPLL2_DELTA_MASK)
#define PCIe_DPLL2_DELTA_RESET                                       0x1e // 30
#define PCIe_DPLL2_TESTINMSB_MSB                                     6
#define PCIe_DPLL2_TESTINMSB_LSB                                     0
#define PCIe_DPLL2_TESTINMSB_MASK                                    0x0000007f
#define PCIe_DPLL2_TESTINMSB_GET(x)                                  (((x) & PCIe_DPLL2_TESTINMSB_MASK) >> PCIe_DPLL2_TESTINMSB_LSB)
#define PCIe_DPLL2_TESTINMSB_SET(x)                                  (((x) << PCIe_DPLL2_TESTINMSB_LSB) & PCIe_DPLL2_TESTINMSB_MASK)
#define PCIe_DPLL2_TESTINMSB_RESET                                   0x0 // 0
#define PCIe_DPLL2_ADDRESS                                           0x18116c84

#define DDR_DPLL2_RANGE_MSB                                          31
#define DDR_DPLL2_RANGE_LSB                                          31
#define DDR_DPLL2_RANGE_MASK                                         0x80000000
#define DDR_DPLL2_RANGE_GET(x)                                       (((x) & DDR_DPLL2_RANGE_MASK) >> DDR_DPLL2_RANGE_LSB)
#define DDR_DPLL2_RANGE_SET(x)                                       (((x) << DDR_DPLL2_RANGE_LSB) & DDR_DPLL2_RANGE_MASK)
#define DDR_DPLL2_RANGE_RESET                                        0x0 // 0
#define DDR_DPLL2_LOCAL_PLL_MSB                                      30
#define DDR_DPLL2_LOCAL_PLL_LSB                                      30
#define DDR_DPLL2_LOCAL_PLL_MASK                                     0x40000000
#define DDR_DPLL2_LOCAL_PLL_GET(x)                                   (((x) & DDR_DPLL2_LOCAL_PLL_MASK) >> DDR_DPLL2_LOCAL_PLL_LSB)
#define DDR_DPLL2_LOCAL_PLL_SET(x)                                   (((x) << DDR_DPLL2_LOCAL_PLL_LSB) & DDR_DPLL2_LOCAL_PLL_MASK)
#define DDR_DPLL2_LOCAL_PLL_RESET                                    0x0 // 0
#define DDR_DPLL2_KI_MSB                                             29
#define DDR_DPLL2_KI_LSB                                             26
#define DDR_DPLL2_KI_MASK                                            0x3c000000
#define DDR_DPLL2_KI_GET(x)                                          (((x) & DDR_DPLL2_KI_MASK) >> DDR_DPLL2_KI_LSB)
#define DDR_DPLL2_KI_SET(x)                                          (((x) << DDR_DPLL2_KI_LSB) & DDR_DPLL2_KI_MASK)
#define DDR_DPLL2_KI_RESET                                           0x6 // 6
#define DDR_DPLL2_KD_MSB                                             25
#define DDR_DPLL2_KD_LSB                                             19
#define DDR_DPLL2_KD_MASK                                            0x03f80000
#define DDR_DPLL2_KD_GET(x)                                          (((x) & DDR_DPLL2_KD_MASK) >> DDR_DPLL2_KD_LSB)
#define DDR_DPLL2_KD_SET(x)                                          (((x) << DDR_DPLL2_KD_LSB) & DDR_DPLL2_KD_MASK)
#define DDR_DPLL2_KD_RESET                                           0x7f // 127
#define DDR_DPLL2_EN_NEGTRIG_MSB                                     18
#define DDR_DPLL2_EN_NEGTRIG_LSB                                     18
#define DDR_DPLL2_EN_NEGTRIG_MASK                                    0x00040000
#define DDR_DPLL2_EN_NEGTRIG_GET(x)                                  (((x) & DDR_DPLL2_EN_NEGTRIG_MASK) >> DDR_DPLL2_EN_NEGTRIG_LSB)
#define DDR_DPLL2_EN_NEGTRIG_SET(x)                                  (((x) << DDR_DPLL2_EN_NEGTRIG_LSB) & DDR_DPLL2_EN_NEGTRIG_MASK)
#define DDR_DPLL2_EN_NEGTRIG_RESET                                   0x0 // 0
#define DDR_DPLL2_SEL_1SDM_MSB                                       17
#define DDR_DPLL2_SEL_1SDM_LSB                                       17
#define DDR_DPLL2_SEL_1SDM_MASK                                      0x00020000
#define DDR_DPLL2_SEL_1SDM_GET(x)                                    (((x) & DDR_DPLL2_SEL_1SDM_MASK) >> DDR_DPLL2_SEL_1SDM_LSB)
#define DDR_DPLL2_SEL_1SDM_SET(x)                                    (((x) << DDR_DPLL2_SEL_1SDM_LSB) & DDR_DPLL2_SEL_1SDM_MASK)
#define DDR_DPLL2_SEL_1SDM_RESET                                     0x0 // 0
#define DDR_DPLL2_PLL_PWD_MSB                                        16
#define DDR_DPLL2_PLL_PWD_LSB                                        16
#define DDR_DPLL2_PLL_PWD_MASK                                       0x00010000
#define DDR_DPLL2_PLL_PWD_GET(x)                                     (((x) & DDR_DPLL2_PLL_PWD_MASK) >> DDR_DPLL2_PLL_PWD_LSB)
#define DDR_DPLL2_PLL_PWD_SET(x)                                     (((x) << DDR_DPLL2_PLL_PWD_LSB) & DDR_DPLL2_PLL_PWD_MASK)
#define DDR_DPLL2_PLL_PWD_RESET                                      0x1 // 1
#define DDR_DPLL2_OUTDIV_MSB                                         15
#define DDR_DPLL2_OUTDIV_LSB                                         13
#define DDR_DPLL2_OUTDIV_MASK                                        0x0000e000
#define DDR_DPLL2_OUTDIV_GET(x)                                      (((x) & DDR_DPLL2_OUTDIV_MASK) >> DDR_DPLL2_OUTDIV_LSB)
#define DDR_DPLL2_OUTDIV_SET(x)                                      (((x) << DDR_DPLL2_OUTDIV_LSB) & DDR_DPLL2_OUTDIV_MASK)
#define DDR_DPLL2_OUTDIV_RESET                                       0x0 // 0
#define DDR_DPLL2_DELTA_MSB                                          12
#define DDR_DPLL2_DELTA_LSB                                          7
#define DDR_DPLL2_DELTA_MASK                                         0x00001f80
#define DDR_DPLL2_DELTA_GET(x)                                       (((x) & DDR_DPLL2_DELTA_MASK) >> DDR_DPLL2_DELTA_LSB)
#define DDR_DPLL2_DELTA_SET(x)                                       (((x) << DDR_DPLL2_DELTA_LSB) & DDR_DPLL2_DELTA_MASK)
#define DDR_DPLL2_DELTA_RESET                                        0x1e // 30
#define DDR_DPLL2_TESTINMSB_MSB                                      6
#define DDR_DPLL2_TESTINMSB_LSB                                      0
#define DDR_DPLL2_TESTINMSB_MASK                                     0x0000007f
#define DDR_DPLL2_TESTINMSB_GET(x)                                   (((x) & DDR_DPLL2_TESTINMSB_MASK) >> DDR_DPLL2_TESTINMSB_LSB)
#define DDR_DPLL2_TESTINMSB_SET(x)                                   (((x) << DDR_DPLL2_TESTINMSB_LSB) & DDR_DPLL2_TESTINMSB_MASK)
#define DDR_DPLL2_TESTINMSB_RESET                                    0x0 // 0
#define DDR_DPLL2_ADDRESS                                            0x18116ec4

#define CPU_DPLL2_RANGE_MSB                                          31
#define CPU_DPLL2_RANGE_LSB                                          31
#define CPU_DPLL2_RANGE_MASK                                         0x80000000
#define CPU_DPLL2_RANGE_GET(x)                                       (((x) & CPU_DPLL2_RANGE_MASK) >> CPU_DPLL2_RANGE_LSB)
#define CPU_DPLL2_RANGE_SET(x)                                       (((x) << CPU_DPLL2_RANGE_LSB) & CPU_DPLL2_RANGE_MASK)
#define CPU_DPLL2_RANGE_RESET                                        0x0 // 0
#define CPU_DPLL2_LOCAL_PLL_MSB                                      30
#define CPU_DPLL2_LOCAL_PLL_LSB                                      30
#define CPU_DPLL2_LOCAL_PLL_MASK                                     0x40000000
#define CPU_DPLL2_LOCAL_PLL_GET(x)                                   (((x) & CPU_DPLL2_LOCAL_PLL_MASK) >> CPU_DPLL2_LOCAL_PLL_LSB)
#define CPU_DPLL2_LOCAL_PLL_SET(x)                                   (((x) << CPU_DPLL2_LOCAL_PLL_LSB) & CPU_DPLL2_LOCAL_PLL_MASK)
#define CPU_DPLL2_LOCAL_PLL_RESET                                    0x0 // 0
#define CPU_DPLL2_KI_MSB                                             29
#define CPU_DPLL2_KI_LSB                                             26
#define CPU_DPLL2_KI_MASK                                            0x3c000000
#define CPU_DPLL2_KI_GET(x)                                          (((x) & CPU_DPLL2_KI_MASK) >> CPU_DPLL2_KI_LSB)
#define CPU_DPLL2_KI_SET(x)                                          (((x) << CPU_DPLL2_KI_LSB) & CPU_DPLL2_KI_MASK)
#define CPU_DPLL2_KI_RESET                                           0x6 // 6
#define CPU_DPLL2_KD_MSB                                             25
#define CPU_DPLL2_KD_LSB                                             19
#define CPU_DPLL2_KD_MASK                                            0x03f80000
#define CPU_DPLL2_KD_GET(x)                                          (((x) & CPU_DPLL2_KD_MASK) >> CPU_DPLL2_KD_LSB)
#define CPU_DPLL2_KD_SET(x)                                          (((x) << CPU_DPLL2_KD_LSB) & CPU_DPLL2_KD_MASK)
#define CPU_DPLL2_KD_RESET                                           0x7f // 127
#define CPU_DPLL2_EN_NEGTRIG_MSB                                     18
#define CPU_DPLL2_EN_NEGTRIG_LSB                                     18
#define CPU_DPLL2_EN_NEGTRIG_MASK                                    0x00040000
#define CPU_DPLL2_EN_NEGTRIG_GET(x)                                  (((x) & CPU_DPLL2_EN_NEGTRIG_MASK) >> CPU_DPLL2_EN_NEGTRIG_LSB)
#define CPU_DPLL2_EN_NEGTRIG_SET(x)                                  (((x) << CPU_DPLL2_EN_NEGTRIG_LSB) & CPU_DPLL2_EN_NEGTRIG_MASK)
#define CPU_DPLL2_EN_NEGTRIG_RESET                                   0x0 // 0
#define CPU_DPLL2_SEL_1SDM_MSB                                       17
#define CPU_DPLL2_SEL_1SDM_LSB                                       17
#define CPU_DPLL2_SEL_1SDM_MASK                                      0x00020000
#define CPU_DPLL2_SEL_1SDM_GET(x)                                    (((x) & CPU_DPLL2_SEL_1SDM_MASK) >> CPU_DPLL2_SEL_1SDM_LSB)
#define CPU_DPLL2_SEL_1SDM_SET(x)                                    (((x) << CPU_DPLL2_SEL_1SDM_LSB) & CPU_DPLL2_SEL_1SDM_MASK)
#define CPU_DPLL2_SEL_1SDM_RESET                                     0x0 // 0
#define CPU_DPLL2_PLL_PWD_MSB                                        16
#define CPU_DPLL2_PLL_PWD_LSB                                        16
#define CPU_DPLL2_PLL_PWD_MASK                                       0x00010000
#define CPU_DPLL2_PLL_PWD_GET(x)                                     (((x) & CPU_DPLL2_PLL_PWD_MASK) >> CPU_DPLL2_PLL_PWD_LSB)
#define CPU_DPLL2_PLL_PWD_SET(x)                                     (((x) << CPU_DPLL2_PLL_PWD_LSB) & CPU_DPLL2_PLL_PWD_MASK)
#define CPU_DPLL2_PLL_PWD_RESET                                      0x1 // 1
#define CPU_DPLL2_OUTDIV_MSB                                         15
#define CPU_DPLL2_OUTDIV_LSB                                         13
#define CPU_DPLL2_OUTDIV_MASK                                        0x0000e000
#define CPU_DPLL2_OUTDIV_GET(x)                                      (((x) & CPU_DPLL2_OUTDIV_MASK) >> CPU_DPLL2_OUTDIV_LSB)
#define CPU_DPLL2_OUTDIV_SET(x)                                      (((x) << CPU_DPLL2_OUTDIV_LSB) & CPU_DPLL2_OUTDIV_MASK)
#define CPU_DPLL2_OUTDIV_RESET                                       0x0 // 0
#define CPU_DPLL2_DELTA_MSB                                          12
#define CPU_DPLL2_DELTA_LSB                                          7
#define CPU_DPLL2_DELTA_MASK                                         0x00001f80
#define CPU_DPLL2_DELTA_GET(x)                                       (((x) & CPU_DPLL2_DELTA_MASK) >> CPU_DPLL2_DELTA_LSB)
#define CPU_DPLL2_DELTA_SET(x)                                       (((x) << CPU_DPLL2_DELTA_LSB) & CPU_DPLL2_DELTA_MASK)
#define CPU_DPLL2_DELTA_RESET                                        0x1e // 30
#define CPU_DPLL2_TESTINMSB_MSB                                      6
#define CPU_DPLL2_TESTINMSB_LSB                                      0
#define CPU_DPLL2_TESTINMSB_MASK                                     0x0000007f
#define CPU_DPLL2_TESTINMSB_GET(x)                                   (((x) & CPU_DPLL2_TESTINMSB_MASK) >> CPU_DPLL2_TESTINMSB_LSB)
#define CPU_DPLL2_TESTINMSB_SET(x)                                   (((x) << CPU_DPLL2_TESTINMSB_LSB) & CPU_DPLL2_TESTINMSB_MASK)
#define CPU_DPLL2_TESTINMSB_RESET                                    0x0 // 0
#define CPU_DPLL2_ADDRESS                                            0x18116f04

#define DPLL2_ADDRESS                           0x18116204
#define DPLL3_ADDRESS                           0x18116208
#define DPLL4_ADDRESS                           0x1811620c

#define DPLL2_RANGE_MSB                         31
#define DPLL2_RANGE_LSB                         31
#define DPLL2_RANGE_MASK                        0x80000000
#define DPLL2_RANGE_GET(x)                      (((x) & DPLL2_RANGE_MASK) >> DPLL2_RANGE_LSB)
#define DPLL2_RANGE_SET(x)                      (((x) << DPLL2_RANGE_LSB) & DPLL2_RANGE_MASK)
#define DPLL2_RANGE_RESET                       0x0 // 0
#define DPLL2_KI_MSB                            29
#define DPLL2_KI_LSB                            26
#define DPLL2_KI_MASK                           0x3c000000
#define DPLL2_KI_GET(x)                         (((x) & DPLL2_KI_MASK) >> DPLL2_KI_LSB)
#define DPLL2_KI_SET(x)                         (((x) << DPLL2_KI_LSB) & DPLL2_KI_MASK)
#define DPLL2_KI_RESET                          0x6 // 6
#define DPLL2_KD_MSB                            25
#define DPLL2_KD_LSB                            19
#define DPLL2_KD_MASK                           0x03f80000
#define DPLL2_KD_GET(x)                         (((x) & DPLL2_KD_MASK) >> DPLL2_KD_LSB)
#define DPLL2_KD_SET(x)                         (((x) << DPLL2_KD_LSB) & DPLL2_KD_MASK)
#define DPLL2_KD_RESET                          0x7f // 127

#define DPLL3_DO_MEAS_MSB                       30
#define DPLL3_DO_MEAS_LSB                       30
#define DPLL3_DO_MEAS_MASK                      0x40000000
#define DPLL3_DO_MEAS_GET(x)                    (((x) & DPLL3_DO_MEAS_MASK) >> DPLL3_DO_MEAS_LSB)
#define DPLL3_DO_MEAS_SET(x)                    (((x) << DPLL3_DO_MEAS_LSB) & DPLL3_DO_MEAS_MASK)
#define DPLL3_DO_MEAS_RESET                     0x0 // 0
#define DPLL3_PHASE_SHIFT_MSB                   29
#define DPLL3_PHASE_SHIFT_LSB                   23
#define DPLL3_PHASE_SHIFT_MASK                  0x3f800000
#define DPLL3_PHASE_SHIFT_GET(x)                (((x) & DPLL3_PHASE_SHIFT_MASK) >> DPLL3_PHASE_SHIFT_LSB)
#define DPLL3_PHASE_SHIFT_SET(x)                (((x) << DPLL3_PHASE_SHIFT_LSB) & DPLL3_PHASE_SHIFT_MASK)
#define DPLL3_PHASE_SHIFT_RESET                 0x0 // 0
#define DPLL3_SQSUM_DVC_MSB                     22
#define DPLL3_SQSUM_DVC_LSB                     3
#define DPLL3_SQSUM_DVC_MASK                    0x007ffff8
#define DPLL3_SQSUM_DVC_GET(x)                  (((x) & DPLL3_SQSUM_DVC_MASK) >> DPLL3_SQSUM_DVC_LSB)

#define DPLL4_MEAS_DONE_MSB                     3
#define DPLL4_MEAS_DONE_LSB                     3
#define DPLL4_MEAS_DONE_MASK                    0x00000008
#define DPLL4_MEAS_DONE_GET(x)                  (((x) & DPLL4_MEAS_DONE_MASK) >> DPLL4_MEAS_DONE_LSB)
#define DPLL4_MEAS_DONE_SET(x)                  (((x) << DPLL4_MEAS_DONE_LSB) & DPLL4_MEAS_DONE_MASK)
#define DPLL4_MEAS_DONE_RESET                   0x0 // 0

#define STEREO0_VOLUME_CHANNEL1_MSB             12
#define STEREO0_VOLUME_CHANNEL1_LSB             8
#define STEREO0_VOLUME_CHANNEL1_MASK            0x00001f00
#define STEREO0_VOLUME_CHANNEL1_GET(x)          (((x) & STEREO0_VOLUME_CHANNEL1_MASK) >> STEREO0_VOLUME_CHANNEL1_LSB)
#define STEREO0_VOLUME_CHANNEL1_SET(x)          (((x) << STEREO0_VOLUME_CHANNEL1_LSB) & STEREO0_VOLUME_CHANNEL1_MASK)
#define STEREO0_VOLUME_CHANNEL1_RESET           0x0 // 0
#define STEREO0_VOLUME_CHANNEL0_MSB             4
#define STEREO0_VOLUME_CHANNEL0_LSB             0
#define STEREO0_VOLUME_CHANNEL0_MASK            0x0000001f
#define STEREO0_VOLUME_CHANNEL0_GET(x)          (((x) & STEREO0_VOLUME_CHANNEL0_MASK) >> STEREO0_VOLUME_CHANNEL0_LSB)
#define STEREO0_VOLUME_CHANNEL0_SET(x)          (((x) << STEREO0_VOLUME_CHANNEL0_LSB) & STEREO0_VOLUME_CHANNEL0_MASK)
#define STEREO0_VOLUME_CHANNEL0_RESET           0x0 // 0
#define STEREO0_VOLUME_ADDRESS                  0x180b0004
#define STEREO0_VOLUME_SW_MASK                  0x00001f1f
#define STEREO0_VOLUME_RSTMASK                  0xffffffff
#define STEREO0_VOLUME_RESET                    0x00000000

#define DDR_RD_DATA_THIS_CYCLE_ADDRESS                               0x18000018

#define TAP_CONTROL_0_ADDRESS                                        0x1800001c
#define TAP_CONTROL_1_ADDRESS                                        0x18000020
#define TAP_CONTROL_2_ADDRESS                                        0x18000024
#define TAP_CONTROL_3_ADDRESS                                        0x18000028

#define DDR_BURST_ADDRESS                                            0x180000c4
#define DDR_BURST2_ADDRESS                                           0x180000c8
#define DDR_AHB_MASTER_TIMEOUT_MAX_ADDRESS                           0x180000cc

#define PMU1_SWREG_MSB                                               31
#define PMU1_SWREG_LSB                                               0
#define PMU1_SWREG_MASK                                              0xffffffff
#define PMU1_SWREG_GET(x)                                            (((x) & PMU1_SWREG_MASK) >> PMU1_SWREG_LSB)
#define PMU1_SWREG_SET(x)                                            (((x) << PMU1_SWREG_LSB) & PMU1_SWREG_MASK)
#define PMU1_SWREG_RESET                                             805951696
#define PMU1_HW_MASK                                                 0xffffffff
#define PMU1_SW_MASK                                                 0xffffffff
#define PMU1_HW_WRITE_MASK                                           0x00000000
#define PMU1_SW_WRITE_MASK                                           0xffffffff
#define PMU1_RSTMASK                                                 0xffffffff
#define PMU1_RESET                                                   0x3009d8d0
#define PMU1_ADDRESS                                                 0x18116cc0

#define PMU2_SWREGMSB_MSB                                            31
#define PMU2_SWREGMSB_LSB                                            22
#define PMU2_SWREGMSB_MASK                                           0xffc00000
#define PMU2_SWREGMSB_GET(x)                                         (((x) & PMU2_SWREGMSB_MASK) >> PMU2_SWREGMSB_LSB)
#define PMU2_SWREGMSB_SET(x)                                         (((x) << PMU2_SWREGMSB_LSB) & PMU2_SWREGMSB_MASK)
#define PMU2_SWREGMSB_RESET                                          0x0 // 0
#define PMU2_PGM_MSB                                                 21
#define PMU2_PGM_LSB                                                 21
#define PMU2_PGM_MASK                                                0x00200000
#define PMU2_PGM_GET(x)                                              (((x) & PMU2_PGM_MASK) >> PMU2_PGM_LSB)
#define PMU2_PGM_SET(x)                                              (((x) << PMU2_PGM_LSB) & PMU2_PGM_MASK)
#define PMU2_PGM_RESET                                               0x0 // 0
#define PMU2_LDO_TUNE_MSB                                            20
#define PMU2_LDO_TUNE_LSB                                            19
#define PMU2_LDO_TUNE_MASK                                           0x00180000
#define PMU2_LDO_TUNE_GET(x)                                         (((x) & PMU2_LDO_TUNE_MASK) >> PMU2_LDO_TUNE_LSB)
#define PMU2_LDO_TUNE_SET(x)                                         (((x) << PMU2_LDO_TUNE_LSB) & PMU2_LDO_TUNE_MASK)
#define PMU2_LDO_TUNE_RESET                                          0x0 // 0
#define PMU2_PWDLDO_DDR_MSB                                          18
#define PMU2_PWDLDO_DDR_LSB                                          18
#define PMU2_PWDLDO_DDR_MASK                                         0x00040000
#define PMU2_PWDLDO_DDR_GET(x)                                       (((x) & PMU2_PWDLDO_DDR_MASK) >> PMU2_PWDLDO_DDR_LSB)
#define PMU2_PWDLDO_DDR_SET(x)                                       (((x) << PMU2_PWDLDO_DDR_LSB) & PMU2_PWDLDO_DDR_MASK)
#define PMU2_PWDLDO_DDR_RESET                                        0x0 // 0
#define PMU2_LPOPWD_MSB                                              17
#define PMU2_LPOPWD_LSB                                              17
#define PMU2_LPOPWD_MASK                                             0x00020000
#define PMU2_LPOPWD_GET(x)                                           (((x) & PMU2_LPOPWD_MASK) >> PMU2_LPOPWD_LSB)
#define PMU2_LPOPWD_SET(x)                                           (((x) << PMU2_LPOPWD_LSB) & PMU2_LPOPWD_MASK)
#define PMU2_LPOPWD_RESET                                            0x0 // 0
#define PMU2_SPARE_MSB                                               16
#define PMU2_SPARE_LSB                                               0
#define PMU2_SPARE_MASK                                              0x0001ffff
#define PMU2_SPARE_GET(x)                                            (((x) & PMU2_SPARE_MASK) >> PMU2_SPARE_LSB)
#define PMU2_SPARE_SET(x)                                            (((x) << PMU2_SPARE_LSB) & PMU2_SPARE_MASK)
#define PMU2_SPARE_RESET                                             0x0 // 0
#define PMU2_ADDRESS                                                 0x18116cc4






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
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_RESET             0x0
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_MSB            21
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_LSB            21
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_MASK           0x00200000
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_GET(x)         (((x) & CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_SET(x)         (((x) << CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_CPUPLL_RESET          0x0
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_MSB            20
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_LSB            20
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_MASK           0x00100000
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_GET(x)         (((x) & CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_SET(x)         (((x) << CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_DDR_CLK_FROM_DDRPLL_RESET          0x0 // 0
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
#define CPU_DDR_CLOCK_CONTROL_ADDRESS                                0x18050008

#define PCIE_PLL_CONFIG_UPDATING_MSB                                 31
#define PCIE_PLL_CONFIG_UPDATING_LSB                                 31
#define PCIE_PLL_CONFIG_UPDATING_MASK                                0x80000000
#define PCIE_PLL_CONFIG_UPDATING_GET(x)                              (((x) & PCIE_PLL_CONFIG_UPDATING_MASK) >> PCIE_PLL_CONFIG_UPDATING_LSB)
#define PCIE_PLL_CONFIG_UPDATING_SET(x)                              (((x) << PCIE_PLL_CONFIG_UPDATING_LSB) & PCIE_PLL_CONFIG_UPDATING_MASK)
#define PCIE_PLL_CONFIG_UPDATING_RESET                               0x0 // 0
#define PCIE_PLL_CONFIG_PLLPWD_MSB                                   30
#define PCIE_PLL_CONFIG_PLLPWD_LSB                                   30
#define PCIE_PLL_CONFIG_PLLPWD_MASK                                  0x40000000
#define PCIE_PLL_CONFIG_PLLPWD_GET(x)                                (((x) & PCIE_PLL_CONFIG_PLLPWD_MASK) >> PCIE_PLL_CONFIG_PLLPWD_LSB)
#define PCIE_PLL_CONFIG_PLLPWD_SET(x)                                (((x) << PCIE_PLL_CONFIG_PLLPWD_LSB) & PCIE_PLL_CONFIG_PLLPWD_MASK)
#define PCIE_PLL_CONFIG_PLLPWD_RESET                                 0x1 // 1
#define PCIE_PLL_CONFIG_BYPASS_MSB                                   16
#define PCIE_PLL_CONFIG_BYPASS_LSB                                   16
#define PCIE_PLL_CONFIG_BYPASS_MASK                                  0x00010000
#define PCIE_PLL_CONFIG_BYPASS_GET(x)                                (((x) & PCIE_PLL_CONFIG_BYPASS_MASK) >> PCIE_PLL_CONFIG_BYPASS_LSB)
#define PCIE_PLL_CONFIG_BYPASS_SET(x)                                (((x) << PCIE_PLL_CONFIG_BYPASS_LSB) & PCIE_PLL_CONFIG_BYPASS_MASK)
#define PCIE_PLL_CONFIG_BYPASS_RESET                                 0x1 // 1
#define PCIE_PLL_CONFIG_REFDIV_MSB                                   14
#define PCIE_PLL_CONFIG_REFDIV_LSB                                   10
#define PCIE_PLL_CONFIG_REFDIV_MASK                                  0x00007c00
#define PCIE_PLL_CONFIG_REFDIV_GET(x)                                (((x) & PCIE_PLL_CONFIG_REFDIV_MASK) >> PCIE_PLL_CONFIG_REFDIV_LSB)
#define PCIE_PLL_CONFIG_REFDIV_SET(x)                                (((x) << PCIE_PLL_CONFIG_REFDIV_LSB) & PCIE_PLL_CONFIG_REFDIV_MASK)
#define PCIE_PLL_CONFIG_REFDIV_RESET                                 0x1 // 1
#define PCIE_PLL_CONFIG_ADDRESS                                      0x1805000c

#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MSB                        31
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB                        31
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK                       0x80000000
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_GET(x)                     (((x) & PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK) >> PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_SET(x)                     (((x) << PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_LSB) & PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_RESET                      0x1 // 1
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MSB                          30
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB                          30
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK                         0x40000000
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_GET(x)                       (((x) & PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK) >> PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_SET(x)                       (((x) << PCIE_PLL_DITHER_DIV_MAX_USE_MAX_LSB) & PCIE_PLL_DITHER_DIV_MAX_USE_MAX_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_USE_MAX_RESET                        0x1 // 1
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MSB                      20
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB                      15
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK                     0x001f8000
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_GET(x)                   (((x) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK) >> PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_SET(x)                   (((x) << PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_LSB) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_RESET                    0x13 // 19
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MSB                     14
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB                     1
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK                    0x00007ffe
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_GET(x)                  (((x) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK) >> PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_SET(x)                  (((x) << PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_LSB) & PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_MASK)
#define PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_RESET                   0x3fff // 16383
#define PCIE_PLL_DITHER_DIV_MAX_ADDRESS                              0x18050010

#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MSB                      20
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB                      15
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK                     0x001f8000
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_GET(x)                   (((x) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK) >> PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_SET(x)                   (((x) << PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_LSB) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_MASK)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_RESET                    0x13 // 19
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MSB                     14
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB                     1
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK                    0x00007ffe
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_GET(x)                  (((x) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK) >> PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_SET(x)                  (((x) << PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_LSB) & PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_MASK)
#define PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_FRAC_RESET                   0x399d // 14749
#define PCIE_PLL_DITHER_DIV_MIN_ADDRESS                              0x18050014

#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_MSB                          31
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB                          28
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK                         0xf0000000
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_GET(x)                       (((x) & PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK) >> PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB)
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_SET(x)                       (((x) << PCIE_PLL_DITHER_STEP_UPDATE_CNT_LSB) & PCIE_PLL_DITHER_STEP_UPDATE_CNT_MASK)
#define PCIE_PLL_DITHER_STEP_UPDATE_CNT_RESET                        0x0 // 0
#define PCIE_PLL_DITHER_STEP_STEP_INT_MSB                            24
#define PCIE_PLL_DITHER_STEP_STEP_INT_LSB                            15
#define PCIE_PLL_DITHER_STEP_STEP_INT_MASK                           0x01ff8000
#define PCIE_PLL_DITHER_STEP_STEP_INT_GET(x)                         (((x) & PCIE_PLL_DITHER_STEP_STEP_INT_MASK) >> PCIE_PLL_DITHER_STEP_STEP_INT_LSB)
#define PCIE_PLL_DITHER_STEP_STEP_INT_SET(x)                         (((x) << PCIE_PLL_DITHER_STEP_STEP_INT_LSB) & PCIE_PLL_DITHER_STEP_STEP_INT_MASK)
#define PCIE_PLL_DITHER_STEP_STEP_INT_RESET                          0x0 // 0
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_MSB                           14
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB                           1
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK                          0x00007ffe
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_GET(x)                        (((x) & PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK) >> PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB)
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_SET(x)                        (((x) << PCIE_PLL_DITHER_STEP_STEP_FRAC_LSB) & PCIE_PLL_DITHER_STEP_STEP_FRAC_MASK)
#define PCIE_PLL_DITHER_STEP_STEP_FRAC_RESET                         0xa // 10
#define PCIE_PLL_DITHER_STEP_ADDRESS                                 0x18050018

#define LDO_POWER_CONTROL_PKG_SEL_MSB                                5
#define LDO_POWER_CONTROL_PKG_SEL_LSB                                5
#define LDO_POWER_CONTROL_PKG_SEL_MASK                               0x00000020
#define LDO_POWER_CONTROL_PKG_SEL_GET(x)                             (((x) & LDO_POWER_CONTROL_PKG_SEL_MASK) >> LDO_POWER_CONTROL_PKG_SEL_LSB)
#define LDO_POWER_CONTROL_PKG_SEL_SET(x)                             (((x) << LDO_POWER_CONTROL_PKG_SEL_LSB) & LDO_POWER_CONTROL_PKG_SEL_MASK)
#define LDO_POWER_CONTROL_PKG_SEL_RESET                              0x0 // 0
#define LDO_POWER_CONTROL_PWDLDO_CPU_MSB                             4
#define LDO_POWER_CONTROL_PWDLDO_CPU_LSB                             4
#define LDO_POWER_CONTROL_PWDLDO_CPU_MASK                            0x00000010
#define LDO_POWER_CONTROL_PWDLDO_CPU_GET(x)                          (((x) & LDO_POWER_CONTROL_PWDLDO_CPU_MASK) >> LDO_POWER_CONTROL_PWDLDO_CPU_LSB)
#define LDO_POWER_CONTROL_PWDLDO_CPU_SET(x)                          (((x) << LDO_POWER_CONTROL_PWDLDO_CPU_LSB) & LDO_POWER_CONTROL_PWDLDO_CPU_MASK)
#define LDO_POWER_CONTROL_PWDLDO_CPU_RESET                           0x0 // 0
#define LDO_POWER_CONTROL_PWDLDO_DDR_MSB                             3
#define LDO_POWER_CONTROL_PWDLDO_DDR_LSB                             3
#define LDO_POWER_CONTROL_PWDLDO_DDR_MASK                            0x00000008
#define LDO_POWER_CONTROL_PWDLDO_DDR_GET(x)                          (((x) & LDO_POWER_CONTROL_PWDLDO_DDR_MASK) >> LDO_POWER_CONTROL_PWDLDO_DDR_LSB)
#define LDO_POWER_CONTROL_PWDLDO_DDR_SET(x)                          (((x) << LDO_POWER_CONTROL_PWDLDO_DDR_LSB) & LDO_POWER_CONTROL_PWDLDO_DDR_MASK)
#define LDO_POWER_CONTROL_PWDLDO_DDR_RESET                           0x0 // 0
#define LDO_POWER_CONTROL_CPU_REFSEL_MSB                             2
#define LDO_POWER_CONTROL_CPU_REFSEL_LSB                             1
#define LDO_POWER_CONTROL_CPU_REFSEL_MASK                            0x00000006
#define LDO_POWER_CONTROL_CPU_REFSEL_GET(x)                          (((x) & LDO_POWER_CONTROL_CPU_REFSEL_MASK) >> LDO_POWER_CONTROL_CPU_REFSEL_LSB)
#define LDO_POWER_CONTROL_CPU_REFSEL_SET(x)                          (((x) << LDO_POWER_CONTROL_CPU_REFSEL_LSB) & LDO_POWER_CONTROL_CPU_REFSEL_MASK)
#define LDO_POWER_CONTROL_CPU_REFSEL_RESET                           0x3 // 3
#define LDO_POWER_CONTROL_SELECT_DDR1_MSB                            0
#define LDO_POWER_CONTROL_SELECT_DDR1_LSB                            0
#define LDO_POWER_CONTROL_SELECT_DDR1_MASK                           0x00000001
#define LDO_POWER_CONTROL_SELECT_DDR1_GET(x)                         (((x) & LDO_POWER_CONTROL_SELECT_DDR1_MASK) >> LDO_POWER_CONTROL_SELECT_DDR1_LSB)
#define LDO_POWER_CONTROL_SELECT_DDR1_SET(x)                         (((x) << LDO_POWER_CONTROL_SELECT_DDR1_LSB) & LDO_POWER_CONTROL_SELECT_DDR1_MASK)
#define LDO_POWER_CONTROL_SELECT_DDR1_RESET                          0x0 // 0
#define LDO_POWER_CONTROL_ADDRESS                                    0x1805001c

#define SWITCH_CLOCK_SPARE_SPARE_MSB                                 31
#define SWITCH_CLOCK_SPARE_SPARE_LSB                                 16
#define SWITCH_CLOCK_SPARE_SPARE_MASK                                0xffff0000
#define SWITCH_CLOCK_SPARE_SPARE_GET(x)                              (((x) & SWITCH_CLOCK_SPARE_SPARE_MASK) >> SWITCH_CLOCK_SPARE_SPARE_LSB)
#define SWITCH_CLOCK_SPARE_SPARE_SET(x)                              (((x) << SWITCH_CLOCK_SPARE_SPARE_LSB) & SWITCH_CLOCK_SPARE_SPARE_MASK)
#define SWITCH_CLOCK_SPARE_SPARE_RESET                               0x0 // 0
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_MSB                       15
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_LSB                       15
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_MASK                      0x00008000
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_2_RESET                     0x0 // 0
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_MSB                       14
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_LSB                       14
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_MASK                      0x00004000
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL1_1_RESET                     0x0 // 0
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_MSB                       13
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_LSB                       13
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_MASK                      0x00002000
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_2_RESET                     0x0 // 0
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_MSB                         12
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_LSB                         12
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_MASK                        0x00001000
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_GET(x)                      (((x) & SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_SET(x)                      (((x) << SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_NANDF_CLK_SEL_RESET                       0x0 // 0
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MSB                   11
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB                   8
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK                  0x00000f00
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_GET(x)                (((x) & SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK) >> SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB)
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(x)                (((x) << SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_LSB) & SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_MASK)
#define SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_RESET                 0x5 // 5
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MSB                         7
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB                         7
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK                        0x00000080
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_GET(x)                      (((x) & SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_SET(x)                      (((x) << SWITCH_CLOCK_SPARE_UART1_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_UART1_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_UART1_CLK_SEL_RESET                       0x0 // 0
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_MSB                       6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_LSB                       6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_MASK                      0x00000040
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL0_1_RESET                     0x0 // 0
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_MSB                           5
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_LSB                           5
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_MASK                          0x00000020
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_GET(x)                        (((x) & SWITCH_CLOCK_SPARE_I2C_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_I2C_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_SET(x)                        (((x) << SWITCH_CLOCK_SPARE_I2C_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_I2C_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_I2C_CLK_SEL_RESET                         0x0 // 0
#define SWITCH_CLOCK_SPARE_SPARE_0_MSB                               4
#define SWITCH_CLOCK_SPARE_SPARE_0_LSB                               0
#define SWITCH_CLOCK_SPARE_SPARE_0_MASK                              0x0000001f
#define SWITCH_CLOCK_SPARE_SPARE_0_GET(x)                            (((x) & SWITCH_CLOCK_SPARE_SPARE_0_MASK) >> SWITCH_CLOCK_SPARE_SPARE_0_LSB)
#define SWITCH_CLOCK_SPARE_SPARE_0_SET(x)                            (((x) << SWITCH_CLOCK_SPARE_SPARE_0_LSB) & SWITCH_CLOCK_SPARE_SPARE_0_MASK)
#define SWITCH_CLOCK_SPARE_SPARE_0_RESET                             0x0 // 0
#define SWITCH_CLOCK_SPARE_ADDRESS                                   0x18050020

#define MDIO_PHY_ADDR_VALUE_MSB                                      2
#define MDIO_PHY_ADDR_VALUE_LSB                                      0
#define MDIO_PHY_ADDR_VALUE_MASK                                     0x00000007
#define MDIO_PHY_ADDR_VALUE_GET(x)                                   (((x) & MDIO_PHY_ADDR_VALUE_MASK) >> MDIO_PHY_ADDR_VALUE_LSB)
#define MDIO_PHY_ADDR_VALUE_SET(x)                                   (((x) << MDIO_PHY_ADDR_VALUE_LSB) & MDIO_PHY_ADDR_VALUE_MASK)
#define MDIO_PHY_ADDR_VALUE_RESET                                    0x7
#define MDIO_PHY_ADDR_ADDRESS                                        0x180b8024

#define CURRENT_PCIE_PLL_DITHER_INT_MSB                              20
#define CURRENT_PCIE_PLL_DITHER_INT_LSB                              15
#define CURRENT_PCIE_PLL_DITHER_INT_MASK                             0x001f8000
#define CURRENT_PCIE_PLL_DITHER_INT_GET(x)                           (((x) & CURRENT_PCIE_PLL_DITHER_INT_MASK) >> CURRENT_PCIE_PLL_DITHER_INT_LSB)
#define CURRENT_PCIE_PLL_DITHER_INT_SET(x)                           (((x) << CURRENT_PCIE_PLL_DITHER_INT_LSB) & CURRENT_PCIE_PLL_DITHER_INT_MASK)
#define CURRENT_PCIE_PLL_DITHER_INT_RESET                            0x1 // 1
#define CURRENT_PCIE_PLL_DITHER_FRAC_MSB                             13
#define CURRENT_PCIE_PLL_DITHER_FRAC_LSB                             0
#define CURRENT_PCIE_PLL_DITHER_FRAC_MASK                            0x00003fff
#define CURRENT_PCIE_PLL_DITHER_FRAC_GET(x)                          (((x) & CURRENT_PCIE_PLL_DITHER_FRAC_MASK) >> CURRENT_PCIE_PLL_DITHER_FRAC_LSB)
#define CURRENT_PCIE_PLL_DITHER_FRAC_SET(x)                          (((x) << CURRENT_PCIE_PLL_DITHER_FRAC_LSB) & CURRENT_PCIE_PLL_DITHER_FRAC_MASK)
#define CURRENT_PCIE_PLL_DITHER_FRAC_RESET                           0x0 // 0
#define CURRENT_PCIE_PLL_DITHER_ADDRESS                              0x18050024

#define ETH_XMII_TX_INVERT_MSB                                       31
#define ETH_XMII_TX_INVERT_LSB                                       31
#define ETH_XMII_TX_INVERT_MASK                                      0x80000000
#define ETH_XMII_TX_INVERT_GET(x)                                    (((x) & ETH_XMII_TX_INVERT_MASK) >> ETH_XMII_TX_INVERT_LSB)
#define ETH_XMII_TX_INVERT_SET(x)                                    (((x) << ETH_XMII_TX_INVERT_LSB) & ETH_XMII_TX_INVERT_MASK)
#define ETH_XMII_TX_INVERT_RESET                                     0x0 // 0
#define ETH_XMII_GIGE_QUAD_MSB                                       30
#define ETH_XMII_GIGE_QUAD_LSB                                       30
#define ETH_XMII_GIGE_QUAD_MASK                                      0x40000000
#define ETH_XMII_GIGE_QUAD_GET(x)                                    (((x) & ETH_XMII_GIGE_QUAD_MASK) >> ETH_XMII_GIGE_QUAD_LSB)
#define ETH_XMII_GIGE_QUAD_SET(x)                                    (((x) << ETH_XMII_GIGE_QUAD_LSB) & ETH_XMII_GIGE_QUAD_MASK)
#define ETH_XMII_GIGE_QUAD_RESET                                     0x0 // 0
#define ETH_XMII_RX_DELAY_MSB                                        29
#define ETH_XMII_RX_DELAY_LSB                                        28
#define ETH_XMII_RX_DELAY_MASK                                       0x30000000
#define ETH_XMII_RX_DELAY_GET(x)                                     (((x) & ETH_XMII_RX_DELAY_MASK) >> ETH_XMII_RX_DELAY_LSB)
#define ETH_XMII_RX_DELAY_SET(x)                                     (((x) << ETH_XMII_RX_DELAY_LSB) & ETH_XMII_RX_DELAY_MASK)
#define ETH_XMII_RX_DELAY_RESET                                      0x0 // 0
#define ETH_XMII_TX_DELAY_MSB                                        27
#define ETH_XMII_TX_DELAY_LSB                                        26
#define ETH_XMII_TX_DELAY_MASK                                       0x0c000000
#define ETH_XMII_TX_DELAY_GET(x)                                     (((x) & ETH_XMII_TX_DELAY_MASK) >> ETH_XMII_TX_DELAY_LSB)
#define ETH_XMII_TX_DELAY_SET(x)                                     (((x) << ETH_XMII_TX_DELAY_LSB) & ETH_XMII_TX_DELAY_MASK)
#define ETH_XMII_TX_DELAY_RESET                                      0x0 // 0
#define ETH_XMII_GIGE_MSB                                            25
#define ETH_XMII_GIGE_LSB                                            25
#define ETH_XMII_GIGE_MASK                                           0x02000000
#define ETH_XMII_GIGE_GET(x)                                         (((x) & ETH_XMII_GIGE_MASK) >> ETH_XMII_GIGE_LSB)
#define ETH_XMII_GIGE_SET(x)                                         (((x) << ETH_XMII_GIGE_LSB) & ETH_XMII_GIGE_MASK)
#define ETH_XMII_GIGE_RESET                                          0x0 // 0
#define ETH_XMII_OFFSET_PHASE_MSB                                    24
#define ETH_XMII_OFFSET_PHASE_LSB                                    24
#define ETH_XMII_OFFSET_PHASE_MASK                                   0x01000000
#define ETH_XMII_OFFSET_PHASE_GET(x)                                 (((x) & ETH_XMII_OFFSET_PHASE_MASK) >> ETH_XMII_OFFSET_PHASE_LSB)
#define ETH_XMII_OFFSET_PHASE_SET(x)                                 (((x) << ETH_XMII_OFFSET_PHASE_LSB) & ETH_XMII_OFFSET_PHASE_MASK)
#define ETH_XMII_OFFSET_PHASE_RESET                                  0x0 // 0
#define ETH_XMII_OFFSET_COUNT_MSB                                    23
#define ETH_XMII_OFFSET_COUNT_LSB                                    16
#define ETH_XMII_OFFSET_COUNT_MASK                                   0x00ff0000
#define ETH_XMII_OFFSET_COUNT_GET(x)                                 (((x) & ETH_XMII_OFFSET_COUNT_MASK) >> ETH_XMII_OFFSET_COUNT_LSB)
#define ETH_XMII_OFFSET_COUNT_SET(x)                                 (((x) << ETH_XMII_OFFSET_COUNT_LSB) & ETH_XMII_OFFSET_COUNT_MASK)
#define ETH_XMII_OFFSET_COUNT_RESET                                  0x0 // 0
#define ETH_XMII_PHASE1_COUNT_MSB                                    15
#define ETH_XMII_PHASE1_COUNT_LSB                                    8
#define ETH_XMII_PHASE1_COUNT_MASK                                   0x0000ff00
#define ETH_XMII_PHASE1_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE1_COUNT_MASK) >> ETH_XMII_PHASE1_COUNT_LSB)
#define ETH_XMII_PHASE1_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE1_COUNT_LSB) & ETH_XMII_PHASE1_COUNT_MASK)
#define ETH_XMII_PHASE1_COUNT_RESET                                  0x1 // 1
#define ETH_XMII_PHASE0_COUNT_MSB                                    7
#define ETH_XMII_PHASE0_COUNT_LSB                                    0
#define ETH_XMII_PHASE0_COUNT_MASK                                   0x000000ff
#define ETH_XMII_PHASE0_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE0_COUNT_MASK) >> ETH_XMII_PHASE0_COUNT_LSB)
#define ETH_XMII_PHASE0_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE0_COUNT_LSB) & ETH_XMII_PHASE0_COUNT_MASK)
#define ETH_XMII_PHASE0_COUNT_RESET                                  0x1 // 1
#define ETH_XMII_ADDRESS                                             0x18050028

#define AUDIO_PLL_CONFIG_UPDATING_MSB                                31
#define AUDIO_PLL_CONFIG_UPDATING_LSB                                31
#define AUDIO_PLL_CONFIG_UPDATING_MASK                               0x80000000
#define AUDIO_PLL_CONFIG_UPDATING_GET(x)                             (((x) & AUDIO_PLL_CONFIG_UPDATING_MASK) >> AUDIO_PLL_CONFIG_UPDATING_LSB)
#define AUDIO_PLL_CONFIG_UPDATING_SET(x)                             (((x) << AUDIO_PLL_CONFIG_UPDATING_LSB) & AUDIO_PLL_CONFIG_UPDATING_MASK)
#define AUDIO_PLL_CONFIG_UPDATING_RESET                              0x1 // 1
#define AUDIO_PLL_CONFIG_EXT_DIV_MSB                                 14
#define AUDIO_PLL_CONFIG_EXT_DIV_LSB                                 12
#define AUDIO_PLL_CONFIG_EXT_DIV_MASK                                0x00007000
#define AUDIO_PLL_CONFIG_EXT_DIV_GET(x)                              (((x) & AUDIO_PLL_CONFIG_EXT_DIV_MASK) >> AUDIO_PLL_CONFIG_EXT_DIV_LSB)
#define AUDIO_PLL_CONFIG_EXT_DIV_SET(x)                              (((x) << AUDIO_PLL_CONFIG_EXT_DIV_LSB) & AUDIO_PLL_CONFIG_EXT_DIV_MASK)
#define AUDIO_PLL_CONFIG_EXT_DIV_RESET                               0x1 // 1
#define AUDIO_PLL_CONFIG_POSTPLLDIV_MSB                              9
#define AUDIO_PLL_CONFIG_POSTPLLDIV_LSB                              7
#define AUDIO_PLL_CONFIG_POSTPLLDIV_MASK                             0x00000380
#define AUDIO_PLL_CONFIG_POSTPLLDIV_GET(x)                           (((x) & AUDIO_PLL_CONFIG_POSTPLLDIV_MASK) >> AUDIO_PLL_CONFIG_POSTPLLDIV_LSB)
#define AUDIO_PLL_CONFIG_POSTPLLDIV_SET(x)                           (((x) << AUDIO_PLL_CONFIG_POSTPLLDIV_LSB) & AUDIO_PLL_CONFIG_POSTPLLDIV_MASK)
#define AUDIO_PLL_CONFIG_POSTPLLDIV_RESET                            0x1 // 1
#define AUDIO_PLL_CONFIG_PLLPWD_MSB                                  5
#define AUDIO_PLL_CONFIG_PLLPWD_LSB                                  5
#define AUDIO_PLL_CONFIG_PLLPWD_MASK                                 0x00000020
#define AUDIO_PLL_CONFIG_PLLPWD_GET(x)                               (((x) & AUDIO_PLL_CONFIG_PLLPWD_MASK) >> AUDIO_PLL_CONFIG_PLLPWD_LSB)
#define AUDIO_PLL_CONFIG_PLLPWD_SET(x)                               (((x) << AUDIO_PLL_CONFIG_PLLPWD_LSB) & AUDIO_PLL_CONFIG_PLLPWD_MASK)
#define AUDIO_PLL_CONFIG_PLLPWD_RESET                                0x1 // 1
#define AUDIO_PLL_CONFIG_BYPASS_MSB                                  4
#define AUDIO_PLL_CONFIG_BYPASS_LSB                                  4
#define AUDIO_PLL_CONFIG_BYPASS_MASK                                 0x00000010
#define AUDIO_PLL_CONFIG_BYPASS_GET(x)                               (((x) & AUDIO_PLL_CONFIG_BYPASS_MASK) >> AUDIO_PLL_CONFIG_BYPASS_LSB)
#define AUDIO_PLL_CONFIG_BYPASS_SET(x)                               (((x) << AUDIO_PLL_CONFIG_BYPASS_LSB) & AUDIO_PLL_CONFIG_BYPASS_MASK)
#define AUDIO_PLL_CONFIG_BYPASS_RESET                                0x1 // 1
#define AUDIO_PLL_CONFIG_REFDIV_MSB                                  3
#define AUDIO_PLL_CONFIG_REFDIV_LSB                                  0
#define AUDIO_PLL_CONFIG_REFDIV_MASK                                 0x0000000f
#define AUDIO_PLL_CONFIG_REFDIV_GET(x)                               (((x) & AUDIO_PLL_CONFIG_REFDIV_MASK) >> AUDIO_PLL_CONFIG_REFDIV_LSB)
#define AUDIO_PLL_CONFIG_REFDIV_SET(x)                               (((x) << AUDIO_PLL_CONFIG_REFDIV_LSB) & AUDIO_PLL_CONFIG_REFDIV_MASK)
#define AUDIO_PLL_CONFIG_REFDIV_RESET                                0x3 // 3
#define AUDIO_PLL_CONFIG_ADDRESS                                     0x1805002c

#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MSB                        28
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB                        11
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK                       0x1ffff800
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_GET(x)                     (((x) & AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK) >> AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB)
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_SET(x)                     (((x) << AUDIO_PLL_MODULATION_TGT_DIV_FRAC_LSB) & AUDIO_PLL_MODULATION_TGT_DIV_FRAC_MASK)
#define AUDIO_PLL_MODULATION_TGT_DIV_FRAC_RESET                      0x148fe // 84222
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_MSB                         6
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB                         1
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK                        0x0000007e
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_GET(x)                      (((x) & AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK) >> AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB)
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_SET(x)                      (((x) << AUDIO_PLL_MODULATION_TGT_DIV_INT_LSB) & AUDIO_PLL_MODULATION_TGT_DIV_INT_MASK)
#define AUDIO_PLL_MODULATION_TGT_DIV_INT_RESET                       0x14 // 20
#define AUDIO_PLL_MODULATION_START_MSB                               0
#define AUDIO_PLL_MODULATION_START_LSB                               0
#define AUDIO_PLL_MODULATION_START_MASK                              0x00000001
#define AUDIO_PLL_MODULATION_START_GET(x)                            (((x) & AUDIO_PLL_MODULATION_START_MASK) >> AUDIO_PLL_MODULATION_START_LSB)
#define AUDIO_PLL_MODULATION_START_SET(x)                            (((x) << AUDIO_PLL_MODULATION_START_LSB) & AUDIO_PLL_MODULATION_START_MASK)
#define AUDIO_PLL_MODULATION_START_RESET                             0x0 // 0
#define AUDIO_PLL_MODULATION_ADDRESS                                 0x18050030

#define AUDIO_PLL_MOD_STEP_FRAC_MSB                                  31
#define AUDIO_PLL_MOD_STEP_FRAC_LSB                                  14
#define AUDIO_PLL_MOD_STEP_FRAC_MASK                                 0xffffc000
#define AUDIO_PLL_MOD_STEP_FRAC_GET(x)                               (((x) & AUDIO_PLL_MOD_STEP_FRAC_MASK) >> AUDIO_PLL_MOD_STEP_FRAC_LSB)
#define AUDIO_PLL_MOD_STEP_FRAC_SET(x)                               (((x) << AUDIO_PLL_MOD_STEP_FRAC_LSB) & AUDIO_PLL_MOD_STEP_FRAC_MASK)
#define AUDIO_PLL_MOD_STEP_FRAC_RESET                                0x1 // 1
#define AUDIO_PLL_MOD_STEP_INT_MSB                                   13
#define AUDIO_PLL_MOD_STEP_INT_LSB                                   4
#define AUDIO_PLL_MOD_STEP_INT_MASK                                  0x00003ff0
#define AUDIO_PLL_MOD_STEP_INT_GET(x)                                (((x) & AUDIO_PLL_MOD_STEP_INT_MASK) >> AUDIO_PLL_MOD_STEP_INT_LSB)
#define AUDIO_PLL_MOD_STEP_INT_SET(x)                                (((x) << AUDIO_PLL_MOD_STEP_INT_LSB) & AUDIO_PLL_MOD_STEP_INT_MASK)
#define AUDIO_PLL_MOD_STEP_INT_RESET                                 0x0 // 0
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_MSB                            3
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB                            0
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK                           0x0000000f
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_GET(x)                         (((x) & AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK) >> AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB)
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_SET(x)                         (((x) << AUDIO_PLL_MOD_STEP_UPDATE_CNT_LSB) & AUDIO_PLL_MOD_STEP_UPDATE_CNT_MASK)
#define AUDIO_PLL_MOD_STEP_UPDATE_CNT_RESET                          0x0 // 0
#define AUDIO_PLL_MOD_STEP_ADDRESS                                   0x18050034

#define CURRENT_AUDIO_PLL_MODULATION_FRAC_MSB                        27
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB                        10
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK                       0x0ffffc00
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_GET(x)                     (((x) & CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK) >> CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB)
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_SET(x)                     (((x) << CURRENT_AUDIO_PLL_MODULATION_FRAC_LSB) & CURRENT_AUDIO_PLL_MODULATION_FRAC_MASK)
#define CURRENT_AUDIO_PLL_MODULATION_FRAC_RESET                      0x1 // 1
#define CURRENT_AUDIO_PLL_MODULATION_INT_MSB                         6
#define CURRENT_AUDIO_PLL_MODULATION_INT_LSB                         1
#define CURRENT_AUDIO_PLL_MODULATION_INT_MASK                        0x0000007e
#define CURRENT_AUDIO_PLL_MODULATION_INT_GET(x)                      (((x) & CURRENT_AUDIO_PLL_MODULATION_INT_MASK) >> CURRENT_AUDIO_PLL_MODULATION_INT_LSB)
#define CURRENT_AUDIO_PLL_MODULATION_INT_SET(x)                      (((x) << CURRENT_AUDIO_PLL_MODULATION_INT_LSB) & CURRENT_AUDIO_PLL_MODULATION_INT_MASK)
#define CURRENT_AUDIO_PLL_MODULATION_INT_RESET                       0x0 // 0
#define CURRENT_AUDIO_PLL_MODULATION_ADDRESS                         0x18050038

#define BB_PLL_CONFIG_UPDATING_MSB                                   31
#define BB_PLL_CONFIG_UPDATING_LSB                                   31
#define BB_PLL_CONFIG_UPDATING_MASK                                  0x80000000
#define BB_PLL_CONFIG_UPDATING_GET(x)                                (((x) & BB_PLL_CONFIG_UPDATING_MASK) >> BB_PLL_CONFIG_UPDATING_LSB)
#define BB_PLL_CONFIG_UPDATING_SET(x)                                (((x) << BB_PLL_CONFIG_UPDATING_LSB) & BB_PLL_CONFIG_UPDATING_MASK)
#define BB_PLL_CONFIG_UPDATING_RESET                                 0x1 // 1
#define BB_PLL_CONFIG_PLLPWD_MSB                                     30
#define BB_PLL_CONFIG_PLLPWD_LSB                                     30
#define BB_PLL_CONFIG_PLLPWD_MASK                                    0x40000000
#define BB_PLL_CONFIG_PLLPWD_GET(x)                                  (((x) & BB_PLL_CONFIG_PLLPWD_MASK) >> BB_PLL_CONFIG_PLLPWD_LSB)
#define BB_PLL_CONFIG_PLLPWD_SET(x)                                  (((x) << BB_PLL_CONFIG_PLLPWD_LSB) & BB_PLL_CONFIG_PLLPWD_MASK)
#define BB_PLL_CONFIG_PLLPWD_RESET                                   0x1 // 1
#define BB_PLL_CONFIG_SPARE_MSB                                      29
#define BB_PLL_CONFIG_SPARE_LSB                                      29
#define BB_PLL_CONFIG_SPARE_MASK                                     0x20000000
#define BB_PLL_CONFIG_SPARE_GET(x)                                   (((x) & BB_PLL_CONFIG_SPARE_MASK) >> BB_PLL_CONFIG_SPARE_LSB)
#define BB_PLL_CONFIG_SPARE_SET(x)                                   (((x) << BB_PLL_CONFIG_SPARE_LSB) & BB_PLL_CONFIG_SPARE_MASK)
#define BB_PLL_CONFIG_SPARE_RESET                                    0x0 // 0
#define BB_PLL_CONFIG_REFDIV_MSB                                     28
#define BB_PLL_CONFIG_REFDIV_LSB                                     24
#define BB_PLL_CONFIG_REFDIV_MASK                                    0x1f000000
#define BB_PLL_CONFIG_REFDIV_GET(x)                                  (((x) & BB_PLL_CONFIG_REFDIV_MASK) >> BB_PLL_CONFIG_REFDIV_LSB)
#define BB_PLL_CONFIG_REFDIV_SET(x)                                  (((x) << BB_PLL_CONFIG_REFDIV_LSB) & BB_PLL_CONFIG_REFDIV_MASK)
#define BB_PLL_CONFIG_REFDIV_RESET                                   0x1 // 1
#define BB_PLL_CONFIG_NINT_MSB                                       21
#define BB_PLL_CONFIG_NINT_LSB                                       16
#define BB_PLL_CONFIG_NINT_MASK                                      0x003f0000
#define BB_PLL_CONFIG_NINT_GET(x)                                    (((x) & BB_PLL_CONFIG_NINT_MASK) >> BB_PLL_CONFIG_NINT_LSB)
#define BB_PLL_CONFIG_NINT_SET(x)                                    (((x) << BB_PLL_CONFIG_NINT_LSB) & BB_PLL_CONFIG_NINT_MASK)
#define BB_PLL_CONFIG_NINT_RESET                                     0x2 // 2
#define BB_PLL_CONFIG_NFRAC_MSB                                      13
#define BB_PLL_CONFIG_NFRAC_LSB                                      0
#define BB_PLL_CONFIG_NFRAC_MASK                                     0x00003fff
#define BB_PLL_CONFIG_NFRAC_GET(x)                                   (((x) & BB_PLL_CONFIG_NFRAC_MASK) >> BB_PLL_CONFIG_NFRAC_LSB)
#define BB_PLL_CONFIG_NFRAC_SET(x)                                   (((x) << BB_PLL_CONFIG_NFRAC_LSB) & BB_PLL_CONFIG_NFRAC_MASK)
#define BB_PLL_CONFIG_NFRAC_RESET                                    0xccc // 3276
#define BB_PLL_CONFIG_ADDRESS                                        0x1805003c

#define DDR_PLL_DITHER_DITHER_EN_MSB                                 31
#define DDR_PLL_DITHER_DITHER_EN_LSB                                 31
#define DDR_PLL_DITHER_DITHER_EN_MASK                                0x80000000
#define DDR_PLL_DITHER_DITHER_EN_GET(x)                              (((x) & DDR_PLL_DITHER_DITHER_EN_MASK) >> DDR_PLL_DITHER_DITHER_EN_LSB)
#define DDR_PLL_DITHER_DITHER_EN_SET(x)                              (((x) << DDR_PLL_DITHER_DITHER_EN_LSB) & DDR_PLL_DITHER_DITHER_EN_MASK)
#define DDR_PLL_DITHER_DITHER_EN_RESET                               0x0 // 0
#define DDR_PLL_DITHER_UPDATE_COUNT_MSB                              30
#define DDR_PLL_DITHER_UPDATE_COUNT_LSB                              27
#define DDR_PLL_DITHER_UPDATE_COUNT_MASK                             0x78000000
#define DDR_PLL_DITHER_UPDATE_COUNT_GET(x)                           (((x) & DDR_PLL_DITHER_UPDATE_COUNT_MASK) >> DDR_PLL_DITHER_UPDATE_COUNT_LSB)
#define DDR_PLL_DITHER_UPDATE_COUNT_SET(x)                           (((x) << DDR_PLL_DITHER_UPDATE_COUNT_LSB) & DDR_PLL_DITHER_UPDATE_COUNT_MASK)
#define DDR_PLL_DITHER_UPDATE_COUNT_RESET                            0xf // 15
#define DDR_PLL_DITHER_NFRAC_STEP_MSB                                26
#define DDR_PLL_DITHER_NFRAC_STEP_LSB                                20
#define DDR_PLL_DITHER_NFRAC_STEP_MASK                               0x07f00000
#define DDR_PLL_DITHER_NFRAC_STEP_GET(x)                             (((x) & DDR_PLL_DITHER_NFRAC_STEP_MASK) >> DDR_PLL_DITHER_NFRAC_STEP_LSB)
#define DDR_PLL_DITHER_NFRAC_STEP_SET(x)                             (((x) << DDR_PLL_DITHER_NFRAC_STEP_LSB) & DDR_PLL_DITHER_NFRAC_STEP_MASK)
#define DDR_PLL_DITHER_NFRAC_STEP_RESET                              0x1 // 1
#define DDR_PLL_DITHER_NFRAC_MIN_MSB                                 19
#define DDR_PLL_DITHER_NFRAC_MIN_LSB                                 10
#define DDR_PLL_DITHER_NFRAC_MIN_MASK                                0x000ffc00
#define DDR_PLL_DITHER_NFRAC_MIN_GET(x)                              (((x) & DDR_PLL_DITHER_NFRAC_MIN_MASK) >> DDR_PLL_DITHER_NFRAC_MIN_LSB)
#define DDR_PLL_DITHER_NFRAC_MIN_SET(x)                              (((x) << DDR_PLL_DITHER_NFRAC_MIN_LSB) & DDR_PLL_DITHER_NFRAC_MIN_MASK)
#define DDR_PLL_DITHER_NFRAC_MIN_RESET                               0x19 // 25
#define DDR_PLL_DITHER_NFRAC_MAX_MSB                                 9
#define DDR_PLL_DITHER_NFRAC_MAX_LSB                                 0
#define DDR_PLL_DITHER_NFRAC_MAX_MASK                                0x000003ff
#define DDR_PLL_DITHER_NFRAC_MAX_GET(x)                              (((x) & DDR_PLL_DITHER_NFRAC_MAX_MASK) >> DDR_PLL_DITHER_NFRAC_MAX_LSB)
#define DDR_PLL_DITHER_NFRAC_MAX_SET(x)                              (((x) << DDR_PLL_DITHER_NFRAC_MAX_LSB) & DDR_PLL_DITHER_NFRAC_MAX_MASK)
#define DDR_PLL_DITHER_NFRAC_MAX_RESET                               0x3e8 // 1000
#define DDR_PLL_DITHER_ADDRESS                                       0x18050040

#define CPU_PLL_DITHER_DITHER_EN_MSB                                 31
#define CPU_PLL_DITHER_DITHER_EN_LSB                                 31
#define CPU_PLL_DITHER_DITHER_EN_MASK                                0x80000000
#define CPU_PLL_DITHER_DITHER_EN_GET(x)                              (((x) & CPU_PLL_DITHER_DITHER_EN_MASK) >> CPU_PLL_DITHER_DITHER_EN_LSB)
#define CPU_PLL_DITHER_DITHER_EN_SET(x)                              (((x) << CPU_PLL_DITHER_DITHER_EN_LSB) & CPU_PLL_DITHER_DITHER_EN_MASK)
#define CPU_PLL_DITHER_DITHER_EN_RESET                               0x0 // 0
#define CPU_PLL_DITHER_UPDATE_COUNT_MSB                              23
#define CPU_PLL_DITHER_UPDATE_COUNT_LSB                              18
#define CPU_PLL_DITHER_UPDATE_COUNT_MASK                             0x00fc0000
#define CPU_PLL_DITHER_UPDATE_COUNT_GET(x)                           (((x) & CPU_PLL_DITHER_UPDATE_COUNT_MASK) >> CPU_PLL_DITHER_UPDATE_COUNT_LSB)
#define CPU_PLL_DITHER_UPDATE_COUNT_SET(x)                           (((x) << CPU_PLL_DITHER_UPDATE_COUNT_LSB) & CPU_PLL_DITHER_UPDATE_COUNT_MASK)
#define CPU_PLL_DITHER_UPDATE_COUNT_RESET                            0x14 // 20
#define CPU_PLL_DITHER_NFRAC_STEP_MSB                                17
#define CPU_PLL_DITHER_NFRAC_STEP_LSB                                12
#define CPU_PLL_DITHER_NFRAC_STEP_MASK                               0x0003f000
#define CPU_PLL_DITHER_NFRAC_STEP_GET(x)                             (((x) & CPU_PLL_DITHER_NFRAC_STEP_MASK) >> CPU_PLL_DITHER_NFRAC_STEP_LSB)
#define CPU_PLL_DITHER_NFRAC_STEP_SET(x)                             (((x) << CPU_PLL_DITHER_NFRAC_STEP_LSB) & CPU_PLL_DITHER_NFRAC_STEP_MASK)
#define CPU_PLL_DITHER_NFRAC_STEP_RESET                              0x1 // 1
#define CPU_PLL_DITHER_NFRAC_MIN_MSB                                 11
#define CPU_PLL_DITHER_NFRAC_MIN_LSB                                 6
#define CPU_PLL_DITHER_NFRAC_MIN_MASK                                0x00000fc0
#define CPU_PLL_DITHER_NFRAC_MIN_GET(x)                              (((x) & CPU_PLL_DITHER_NFRAC_MIN_MASK) >> CPU_PLL_DITHER_NFRAC_MIN_LSB)
#define CPU_PLL_DITHER_NFRAC_MIN_SET(x)                              (((x) << CPU_PLL_DITHER_NFRAC_MIN_LSB) & CPU_PLL_DITHER_NFRAC_MIN_MASK)
#define CPU_PLL_DITHER_NFRAC_MIN_RESET                               0x3 // 3
#define CPU_PLL_DITHER_NFRAC_MAX_MSB                                 5
#define CPU_PLL_DITHER_NFRAC_MAX_LSB                                 0
#define CPU_PLL_DITHER_NFRAC_MAX_MASK                                0x0000003f
#define CPU_PLL_DITHER_NFRAC_MAX_GET(x)                              (((x) & CPU_PLL_DITHER_NFRAC_MAX_MASK) >> CPU_PLL_DITHER_NFRAC_MAX_LSB)
#define CPU_PLL_DITHER_NFRAC_MAX_SET(x)                              (((x) << CPU_PLL_DITHER_NFRAC_MAX_LSB) & CPU_PLL_DITHER_NFRAC_MAX_MASK)
#define CPU_PLL_DITHER_NFRAC_MAX_RESET                               0x3c // 60
#define CPU_PLL_DITHER_ADDRESS                                       0x18050044

#define RST_RESET_HOST_RESET_MSB                                     31
#define RST_RESET_HOST_RESET_LSB                                     31
#define RST_RESET_HOST_RESET_MASK                                    0x80000000
#define RST_RESET_HOST_RESET_GET(x)                                  (((x) & RST_RESET_HOST_RESET_MASK) >> RST_RESET_HOST_RESET_LSB)
#define RST_RESET_HOST_RESET_SET(x)                                  (((x) << RST_RESET_HOST_RESET_LSB) & RST_RESET_HOST_RESET_MASK)
#define RST_RESET_HOST_RESET_RESET                                   0x0 // 0
#define RST_RESET_SLIC_RESET_MSB                                     30
#define RST_RESET_SLIC_RESET_LSB                                     30
#define RST_RESET_SLIC_RESET_MASK                                    0x40000000
#define RST_RESET_SLIC_RESET_GET(x)                                  (((x) & RST_RESET_SLIC_RESET_MASK) >> RST_RESET_SLIC_RESET_LSB)
#define RST_RESET_SLIC_RESET_SET(x)                                  (((x) << RST_RESET_SLIC_RESET_LSB) & RST_RESET_SLIC_RESET_MASK)
#define RST_RESET_SLIC_RESET_RESET                                   0x0 // 0
#define RST_RESET_HDMA_RESET_MSB                                     29
#define RST_RESET_HDMA_RESET_LSB                                     29
#define RST_RESET_HDMA_RESET_MASK                                    0x20000000
#define RST_RESET_HDMA_RESET_GET(x)                                  (((x) & RST_RESET_HDMA_RESET_MASK) >> RST_RESET_HDMA_RESET_LSB)
#define RST_RESET_HDMA_RESET_SET(x)                                  (((x) << RST_RESET_HDMA_RESET_LSB) & RST_RESET_HDMA_RESET_MASK)
#define RST_RESET_HDMA_RESET_RESET                                   0x1 // 1
#define RST_RESET_EXTERNAL_RESET_MSB                                 28
#define RST_RESET_EXTERNAL_RESET_LSB                                 28
#define RST_RESET_EXTERNAL_RESET_MASK                                0x10000000
#define RST_RESET_EXTERNAL_RESET_GET(x)                              (((x) & RST_RESET_EXTERNAL_RESET_MASK) >> RST_RESET_EXTERNAL_RESET_LSB)
#define RST_RESET_EXTERNAL_RESET_SET(x)                              (((x) << RST_RESET_EXTERNAL_RESET_LSB) & RST_RESET_EXTERNAL_RESET_MASK)
#define RST_RESET_EXTERNAL_RESET_RESET                               0x0 // 0
#define RST_RESET_RTC_RESET_MSB                                      27
#define RST_RESET_RTC_RESET_LSB                                      27
#define RST_RESET_RTC_RESET_MASK                                     0x08000000
#define RST_RESET_RTC_RESET_GET(x)                                   (((x) & RST_RESET_RTC_RESET_MASK) >> RST_RESET_RTC_RESET_LSB)
#define RST_RESET_RTC_RESET_SET(x)                                   (((x) << RST_RESET_RTC_RESET_LSB) & RST_RESET_RTC_RESET_MASK)
#define RST_RESET_RTC_RESET_RESET                                    0x1 // 1
#define RST_RESET_PCIEEP_RST_INT_MSB                                 26
#define RST_RESET_PCIEEP_RST_INT_LSB                                 26
#define RST_RESET_PCIEEP_RST_INT_MASK                                0x04000000
#define RST_RESET_PCIEEP_RST_INT_GET(x)                              (((x) & RST_RESET_PCIEEP_RST_INT_MASK) >> RST_RESET_PCIEEP_RST_INT_LSB)
#define RST_RESET_PCIEEP_RST_INT_SET(x)                              (((x) << RST_RESET_PCIEEP_RST_INT_LSB) & RST_RESET_PCIEEP_RST_INT_MASK)
#define RST_RESET_PCIEEP_RST_INT_RESET                               0x0 // 0
#define RST_RESET_CHKSUM_ACC_RESET_MSB                               25
#define RST_RESET_CHKSUM_ACC_RESET_LSB                               25
#define RST_RESET_CHKSUM_ACC_RESET_MASK                              0x02000000
#define RST_RESET_CHKSUM_ACC_RESET_GET(x)                            (((x) & RST_RESET_CHKSUM_ACC_RESET_MASK) >> RST_RESET_CHKSUM_ACC_RESET_LSB)
#define RST_RESET_CHKSUM_ACC_RESET_SET(x)                            (((x) << RST_RESET_CHKSUM_ACC_RESET_LSB) & RST_RESET_CHKSUM_ACC_RESET_MASK)
#define RST_RESET_CHKSUM_ACC_RESET_RESET                             0x0 // 0
#define RST_RESET_FULL_CHIP_RESET_MSB                                24
#define RST_RESET_FULL_CHIP_RESET_LSB                                24
#define RST_RESET_FULL_CHIP_RESET_MASK                               0x01000000
#define RST_RESET_FULL_CHIP_RESET_GET(x)                             (((x) & RST_RESET_FULL_CHIP_RESET_MASK) >> RST_RESET_FULL_CHIP_RESET_LSB)
#define RST_RESET_FULL_CHIP_RESET_SET(x)                             (((x) << RST_RESET_FULL_CHIP_RESET_LSB) & RST_RESET_FULL_CHIP_RESET_MASK)
#define RST_RESET_FULL_CHIP_RESET_RESET                              0x0 // 0
#define RST_RESET_GE1_MDIO_RESET_MSB                                 23
#define RST_RESET_GE1_MDIO_RESET_LSB                                 23
#define RST_RESET_GE1_MDIO_RESET_MASK                                0x00800000
#define RST_RESET_GE1_MDIO_RESET_GET(x)                              (((x) & RST_RESET_GE1_MDIO_RESET_MASK) >> RST_RESET_GE1_MDIO_RESET_LSB)
#define RST_RESET_GE1_MDIO_RESET_SET(x)                              (((x) << RST_RESET_GE1_MDIO_RESET_LSB) & RST_RESET_GE1_MDIO_RESET_MASK)
#define RST_RESET_GE1_MDIO_RESET_RESET                               0x1 // 1
#define RST_RESET_GE0_MDIO_RESET_MSB                                 22
#define RST_RESET_GE0_MDIO_RESET_LSB                                 22
#define RST_RESET_GE0_MDIO_RESET_MASK                                0x00400000
#define RST_RESET_GE0_MDIO_RESET_GET(x)                              (((x) & RST_RESET_GE0_MDIO_RESET_MASK) >> RST_RESET_GE0_MDIO_RESET_LSB)
#define RST_RESET_GE0_MDIO_RESET_SET(x)                              (((x) << RST_RESET_GE0_MDIO_RESET_LSB) & RST_RESET_GE0_MDIO_RESET_MASK)
#define RST_RESET_GE0_MDIO_RESET_RESET                               0x1 // 1
#define RST_RESET_CPU_NMI_MSB                                        21
#define RST_RESET_CPU_NMI_LSB                                        21
#define RST_RESET_CPU_NMI_MASK                                       0x00200000
#define RST_RESET_CPU_NMI_GET(x)                                     (((x) & RST_RESET_CPU_NMI_MASK) >> RST_RESET_CPU_NMI_LSB)
#define RST_RESET_CPU_NMI_SET(x)                                     (((x) << RST_RESET_CPU_NMI_LSB) & RST_RESET_CPU_NMI_MASK)
#define RST_RESET_CPU_NMI_RESET                                      0x0 // 0
#define RST_RESET_CPU_COLD_RESET_MSB                                 20
#define RST_RESET_CPU_COLD_RESET_LSB                                 20
#define RST_RESET_CPU_COLD_RESET_MASK                                0x00100000
#define RST_RESET_CPU_COLD_RESET_GET(x)                              (((x) & RST_RESET_CPU_COLD_RESET_MASK) >> RST_RESET_CPU_COLD_RESET_LSB)
#define RST_RESET_CPU_COLD_RESET_SET(x)                              (((x) << RST_RESET_CPU_COLD_RESET_LSB) & RST_RESET_CPU_COLD_RESET_MASK)
#define RST_RESET_CPU_COLD_RESET_RESET                               0x0 // 0
#define RST_RESET_HOST_RESET_INT_MSB                                 19
#define RST_RESET_HOST_RESET_INT_LSB                                 19
#define RST_RESET_HOST_RESET_INT_MASK                                0x00080000
#define RST_RESET_HOST_RESET_INT_GET(x)                              (((x) & RST_RESET_HOST_RESET_INT_MASK) >> RST_RESET_HOST_RESET_INT_LSB)
#define RST_RESET_HOST_RESET_INT_SET(x)                              (((x) << RST_RESET_HOST_RESET_INT_LSB) & RST_RESET_HOST_RESET_INT_MASK)
#define RST_RESET_HOST_RESET_INT_RESET                               0x0 // 0
#define RST_RESET_PCIEEP_RESET_MSB                                   18
#define RST_RESET_PCIEEP_RESET_LSB                                   18
#define RST_RESET_PCIEEP_RESET_MASK                                  0x00040000
#define RST_RESET_PCIEEP_RESET_GET(x)                                (((x) & RST_RESET_PCIEEP_RESET_MASK) >> RST_RESET_PCIEEP_RESET_LSB)
#define RST_RESET_PCIEEP_RESET_SET(x)                                (((x) << RST_RESET_PCIEEP_RESET_LSB) & RST_RESET_PCIEEP_RESET_MASK)
#define RST_RESET_PCIEEP_RESET_RESET                                 0x0 // 0
#define RST_RESET_UART1_RESET_MSB                                    17
#define RST_RESET_UART1_RESET_LSB                                    17
#define RST_RESET_UART1_RESET_MASK                                   0x00020000
#define RST_RESET_UART1_RESET_GET(x)                                 (((x) & RST_RESET_UART1_RESET_MASK) >> RST_RESET_UART1_RESET_LSB)
#define RST_RESET_UART1_RESET_SET(x)                                 (((x) << RST_RESET_UART1_RESET_LSB) & RST_RESET_UART1_RESET_MASK)
#define RST_RESET_UART1_RESET_RESET                                  0x0 // 0
#define RST_RESET_DDR_RESET_MSB                                      16
#define RST_RESET_DDR_RESET_LSB                                      16
#define RST_RESET_DDR_RESET_MASK                                     0x00010000
#define RST_RESET_DDR_RESET_GET(x)                                   (((x) & RST_RESET_DDR_RESET_MASK) >> RST_RESET_DDR_RESET_LSB)
#define RST_RESET_DDR_RESET_SET(x)                                   (((x) << RST_RESET_DDR_RESET_LSB) & RST_RESET_DDR_RESET_MASK)
#define RST_RESET_DDR_RESET_RESET                                    0x0 // 0
#define RST_RESET_USB_PHY_PLL_PWD_EXT_MSB                            15
#define RST_RESET_USB_PHY_PLL_PWD_EXT_LSB                            15
#define RST_RESET_USB_PHY_PLL_PWD_EXT_MASK                           0x00008000
#define RST_RESET_USB_PHY_PLL_PWD_EXT_GET(x)                         (((x) & RST_RESET_USB_PHY_PLL_PWD_EXT_MASK) >> RST_RESET_USB_PHY_PLL_PWD_EXT_LSB)
#define RST_RESET_USB_PHY_PLL_PWD_EXT_SET(x)                         (((x) << RST_RESET_USB_PHY_PLL_PWD_EXT_LSB) & RST_RESET_USB_PHY_PLL_PWD_EXT_MASK)
#define RST_RESET_USB_PHY_PLL_PWD_EXT_RESET                          0x0 // 0
#define RST_RESET_NANDF_RESET_MSB                                    14
#define RST_RESET_NANDF_RESET_LSB                                    14
#define RST_RESET_NANDF_RESET_MASK                                   0x00004000
#define RST_RESET_NANDF_RESET_GET(x)                                 (((x) & RST_RESET_NANDF_RESET_MASK) >> RST_RESET_NANDF_RESET_LSB)
#define RST_RESET_NANDF_RESET_SET(x)                                 (((x) << RST_RESET_NANDF_RESET_LSB) & RST_RESET_NANDF_RESET_MASK)
#define RST_RESET_NANDF_RESET_RESET                                  0x1 // 1
#define RST_RESET_GE1_MAC_RESET_MSB                                  13
#define RST_RESET_GE1_MAC_RESET_LSB                                  13
#define RST_RESET_GE1_MAC_RESET_MASK                                 0x00002000
#define RST_RESET_GE1_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE1_MAC_RESET_MASK) >> RST_RESET_GE1_MAC_RESET_LSB)
#define RST_RESET_GE1_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE1_MAC_RESET_LSB) & RST_RESET_GE1_MAC_RESET_MASK)
#define RST_RESET_GE1_MAC_RESET_RESET                                0x1 // 1
#define RST_RESET_ETH_SGMII_ARESET_MSB                               12
#define RST_RESET_ETH_SGMII_ARESET_LSB                               12
#define RST_RESET_ETH_SGMII_ARESET_MASK                              0x00001000
#define RST_RESET_ETH_SGMII_ARESET_GET(x)                            (((x) & RST_RESET_ETH_SGMII_ARESET_MASK) >> RST_RESET_ETH_SGMII_ARESET_LSB)
#define RST_RESET_ETH_SGMII_ARESET_SET(x)                            (((x) << RST_RESET_ETH_SGMII_ARESET_LSB) & RST_RESET_ETH_SGMII_ARESET_MASK)
#define RST_RESET_ETH_SGMII_ARESET_RESET                             0x1 // 1
#define RST_RESET_USB_PHY_ARESET_MSB                                 11
#define RST_RESET_USB_PHY_ARESET_LSB                                 11
#define RST_RESET_USB_PHY_ARESET_MASK                                0x00000800
#define RST_RESET_USB_PHY_ARESET_GET(x)                              (((x) & RST_RESET_USB_PHY_ARESET_MASK) >> RST_RESET_USB_PHY_ARESET_LSB)
#define RST_RESET_USB_PHY_ARESET_SET(x)                              (((x) << RST_RESET_USB_PHY_ARESET_LSB) & RST_RESET_USB_PHY_ARESET_MASK)
#define RST_RESET_USB_PHY_ARESET_RESET                               0x1 // 1
#define RST_RESET_HOST_DMA_INT_MSB                                   10
#define RST_RESET_HOST_DMA_INT_LSB                                   10
#define RST_RESET_HOST_DMA_INT_MASK                                  0x00000400
#define RST_RESET_HOST_DMA_INT_GET(x)                                (((x) & RST_RESET_HOST_DMA_INT_MASK) >> RST_RESET_HOST_DMA_INT_LSB)
#define RST_RESET_HOST_DMA_INT_SET(x)                                (((x) << RST_RESET_HOST_DMA_INT_LSB) & RST_RESET_HOST_DMA_INT_MASK)
#define RST_RESET_HOST_DMA_INT_RESET                                 0x0 // 0
#define RST_RESET_GE0_MAC_RESET_MSB                                  9
#define RST_RESET_GE0_MAC_RESET_LSB                                  9
#define RST_RESET_GE0_MAC_RESET_MASK                                 0x00000200
#define RST_RESET_GE0_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE0_MAC_RESET_MASK) >> RST_RESET_GE0_MAC_RESET_LSB)
#define RST_RESET_GE0_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE0_MAC_RESET_LSB) & RST_RESET_GE0_MAC_RESET_MASK)
#define RST_RESET_GE0_MAC_RESET_RESET                                0x1 // 1
#define RST_RESET_ETH_SGMII_RESET_MSB                                8
#define RST_RESET_ETH_SGMII_RESET_LSB                                8
#define RST_RESET_ETH_SGMII_RESET_MASK                               0x00000100
#define RST_RESET_ETH_SGMII_RESET_GET(x)                             (((x) & RST_RESET_ETH_SGMII_RESET_MASK) >> RST_RESET_ETH_SGMII_RESET_LSB)
#define RST_RESET_ETH_SGMII_RESET_SET(x)                             (((x) << RST_RESET_ETH_SGMII_RESET_LSB) & RST_RESET_ETH_SGMII_RESET_MASK)
#define RST_RESET_ETH_SGMII_RESET_RESET                              0x1 // 1
#define RST_RESET_PCIE_PHY_RESET_MSB                                 7
#define RST_RESET_PCIE_PHY_RESET_LSB                                 7
#define RST_RESET_PCIE_PHY_RESET_MASK                                0x00000080
#define RST_RESET_PCIE_PHY_RESET_GET(x)                              (((x) & RST_RESET_PCIE_PHY_RESET_MASK) >> RST_RESET_PCIE_PHY_RESET_LSB)
#define RST_RESET_PCIE_PHY_RESET_SET(x)                              (((x) << RST_RESET_PCIE_PHY_RESET_LSB) & RST_RESET_PCIE_PHY_RESET_MASK)
#define RST_RESET_PCIE_PHY_RESET_RESET                               0x1 // 1
#define RST_RESET_PCIE_RESET_MSB                                     6
#define RST_RESET_PCIE_RESET_LSB                                     6
#define RST_RESET_PCIE_RESET_MASK                                    0x00000040
#define RST_RESET_PCIE_RESET_GET(x)                                  (((x) & RST_RESET_PCIE_RESET_MASK) >> RST_RESET_PCIE_RESET_LSB)
#define RST_RESET_PCIE_RESET_SET(x)                                  (((x) << RST_RESET_PCIE_RESET_LSB) & RST_RESET_PCIE_RESET_MASK)
#define RST_RESET_PCIE_RESET_RESET                                   0x1 // 1
#define RST_RESET_USB_HOST_RESET_MSB                                 5
#define RST_RESET_USB_HOST_RESET_LSB                                 5
#define RST_RESET_USB_HOST_RESET_MASK                                0x00000020
#define RST_RESET_USB_HOST_RESET_GET(x)                              (((x) & RST_RESET_USB_HOST_RESET_MASK) >> RST_RESET_USB_HOST_RESET_LSB)
#define RST_RESET_USB_HOST_RESET_SET(x)                              (((x) << RST_RESET_USB_HOST_RESET_LSB) & RST_RESET_USB_HOST_RESET_MASK)
#define RST_RESET_USB_HOST_RESET_RESET                               0x1 // 1
#define RST_RESET_USB_PHY_RESET_MSB                                  4
#define RST_RESET_USB_PHY_RESET_LSB                                  4
#define RST_RESET_USB_PHY_RESET_MASK                                 0x00000010
#define RST_RESET_USB_PHY_RESET_GET(x)                               (((x) & RST_RESET_USB_PHY_RESET_MASK) >> RST_RESET_USB_PHY_RESET_LSB)
#define RST_RESET_USB_PHY_RESET_SET(x)                               (((x) << RST_RESET_USB_PHY_RESET_LSB) & RST_RESET_USB_PHY_RESET_MASK)
#define RST_RESET_USB_PHY_RESET_RESET                                0x1 // 1
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MSB                       3
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB                       3
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK                      0x00000008
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_GET(x)                    (((x) & RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK) >> RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB)
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_SET(x)                    (((x) << RST_RESET_USB_PHY_SUSPEND_OVERRIDE_LSB) & RST_RESET_USB_PHY_SUSPEND_OVERRIDE_MASK)
#define RST_RESET_USB_PHY_SUSPEND_OVERRIDE_RESET                     0x0 // 0
#define RST_RESET_LUT_RESET_MSB                                      2
#define RST_RESET_LUT_RESET_LSB                                      2
#define RST_RESET_LUT_RESET_MASK                                     0x00000004
#define RST_RESET_LUT_RESET_GET(x)                                   (((x) & RST_RESET_LUT_RESET_MASK) >> RST_RESET_LUT_RESET_LSB)
#define RST_RESET_LUT_RESET_SET(x)                                   (((x) << RST_RESET_LUT_RESET_LSB) & RST_RESET_LUT_RESET_MASK)
#define RST_RESET_LUT_RESET_RESET                                    0x0 // 0
#define RST_RESET_MBOX_RESET_MSB                                     1
#define RST_RESET_MBOX_RESET_LSB                                     1
#define RST_RESET_MBOX_RESET_MASK                                    0x00000002
#define RST_RESET_MBOX_RESET_GET(x)                                  (((x) & RST_RESET_MBOX_RESET_MASK) >> RST_RESET_MBOX_RESET_LSB)
#define RST_RESET_MBOX_RESET_SET(x)                                  (((x) << RST_RESET_MBOX_RESET_LSB) & RST_RESET_MBOX_RESET_MASK)
#define RST_RESET_MBOX_RESET_RESET                                   0x0 // 0
#define RST_RESET_I2S_RESET_MSB                                      0
#define RST_RESET_I2S_RESET_LSB                                      0
#define RST_RESET_I2S_RESET_MASK                                     0x00000001
#define RST_RESET_I2S_RESET_GET(x)                                   (((x) & RST_RESET_I2S_RESET_MASK) >> RST_RESET_I2S_RESET_LSB)
#define RST_RESET_I2S_RESET_SET(x)                                   (((x) << RST_RESET_I2S_RESET_LSB) & RST_RESET_I2S_RESET_MASK)
#define RST_RESET_I2S_RESET_RESET                                    0x0 // 0
#define RST_RESET_ADDRESS                                            0x1806001c

#define RST_WATCHDOG_TIMER_CONTROL_LAST_MSB                          31
#define RST_WATCHDOG_TIMER_CONTROL_LAST_LSB                          31
#define RST_WATCHDOG_TIMER_CONTROL_LAST_MASK                         0x80000000
#define RST_WATCHDOG_TIMER_CONTROL_LAST_GET(x)                       (((x) & RST_WATCHDOG_TIMER_CONTROL_LAST_MASK) >> RST_WATCHDOG_TIMER_CONTROL_LAST_LSB)
#define RST_WATCHDOG_TIMER_CONTROL_LAST_SET(x)                       (((x) << RST_WATCHDOG_TIMER_CONTROL_LAST_LSB) & RST_WATCHDOG_TIMER_CONTROL_LAST_MASK)
#define RST_WATCHDOG_TIMER_CONTROL_LAST_RESET                        0x0 // 0
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_MSB                        1
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_LSB                        0
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_MASK                       0x00000003
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_GET(x)                     (((x) & RST_WATCHDOG_TIMER_CONTROL_ACTION_MASK) >> RST_WATCHDOG_TIMER_CONTROL_ACTION_LSB)
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_SET(x)                     (((x) << RST_WATCHDOG_TIMER_CONTROL_ACTION_LSB) & RST_WATCHDOG_TIMER_CONTROL_ACTION_MASK)
#define RST_WATCHDOG_TIMER_CONTROL_ACTION_RESET                      0x0 // 0
#define RST_WATCHDOG_TIMER_CONTROL_ADDRESS                           0x18060008

#define RST_WATCHDOG_TIMER_TIMER_MSB                                 31
#define RST_WATCHDOG_TIMER_TIMER_LSB                                 0
#define RST_WATCHDOG_TIMER_TIMER_MASK                                0xffffffff
#define RST_WATCHDOG_TIMER_TIMER_GET(x)                              (((x) & RST_WATCHDOG_TIMER_TIMER_MASK) >> RST_WATCHDOG_TIMER_TIMER_LSB)
#define RST_WATCHDOG_TIMER_TIMER_SET(x)                              (((x) << RST_WATCHDOG_TIMER_TIMER_LSB) & RST_WATCHDOG_TIMER_TIMER_MASK)
#define RST_WATCHDOG_TIMER_TIMER_RESET                               0x0 // 0
#define RST_WATCHDOG_TIMER_ADDRESS                                   0x1806000c

#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_MSB                  26
#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_LSB                  26
#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_MASK                 0x04000000
#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_GET(x)               (((x) & RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_MASK) >> RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_LSB)
#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_SET(x)               (((x) << RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_LSB) & RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_MASK)
#define RST_MISC_INTERRUPT_STATUS_USB2_PLL_LOCK_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_MSB                  25
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_LSB                  25
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_MASK                 0x02000000
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_GET(x)               (((x) & RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_MASK) >> RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_LSB)
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_SET(x)               (((x) << RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_LSB) & RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_MASK)
#define RST_MISC_INTERRUPT_STATUS_USB1_PLL_LOCK_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_MSB                        24
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_LSB                        24
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_MASK                       0x01000000
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_GET(x)                     (((x) & RST_MISC_INTERRUPT_STATUS_I2C_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_I2C_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_SET(x)                     (((x) << RST_MISC_INTERRUPT_STATUS_I2C_INT_LSB) & RST_MISC_INTERRUPT_STATUS_I2C_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_I2C_INT_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_MSB                        23
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_LSB                        23
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_MASK                       0x00800000
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_GET(x)                     (((x) & RST_MISC_INTERRUPT_STATUS_FDC_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_FDC_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_SET(x)                     (((x) << RST_MISC_INTERRUPT_STATUS_FDC_INT_LSB) & RST_MISC_INTERRUPT_STATUS_FDC_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_FDC_INT_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_MSB                      22
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_LSB                      22
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_MASK                     0x00400000
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_GET(x)                   (((x) & RST_MISC_INTERRUPT_STATUS_PGPIO_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_PGPIO_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_SET(x)                   (((x) << RST_MISC_INTERRUPT_STATUS_PGPIO_INT_LSB) & RST_MISC_INTERRUPT_STATUS_PGPIO_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_PGPIO_INT_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_MSB                     21
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_LSB                     21
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_MASK                    0x00200000
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_GET(x)                  (((x) & RST_MISC_INTERRUPT_STATUS_NANDF_INTR_MASK) >> RST_MISC_INTERRUPT_STATUS_NANDF_INTR_LSB)
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_SET(x)                  (((x) << RST_MISC_INTERRUPT_STATUS_NANDF_INTR_LSB) & RST_MISC_INTERRUPT_STATUS_NANDF_INTR_MASK)
#define RST_MISC_INTERRUPT_STATUS_NANDF_INTR_RESET                   0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_MSB                       20
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_LSB                       20
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_MASK                      0x00100000
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_GET(x)                    (((x) & RST_MISC_INTERRUPT_STATUS_WOW_INTR_MASK) >> RST_MISC_INTERRUPT_STATUS_WOW_INTR_LSB)
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_SET(x)                    (((x) << RST_MISC_INTERRUPT_STATUS_WOW_INTR_LSB) & RST_MISC_INTERRUPT_STATUS_WOW_INTR_MASK)
#define RST_MISC_INTERRUPT_STATUS_WOW_INTR_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_MSB                      19
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_LSB                      19
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_MASK                     0x00080000
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_GET(x)                   (((x) & RST_MISC_INTERRUPT_STATUS_SLIC_INTR_MASK) >> RST_MISC_INTERRUPT_STATUS_SLIC_INTR_LSB)
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_SET(x)                   (((x) << RST_MISC_INTERRUPT_STATUS_SLIC_INTR_LSB) & RST_MISC_INTERRUPT_STATUS_SLIC_INTR_MASK)
#define RST_MISC_INTERRUPT_STATUS_SLIC_INTR_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_MSB             18
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_LSB             18
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_MASK            0x00040000
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_GET(x)          (((x) & RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_MASK) >> RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_LSB)
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_SET(x)          (((x) << RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_LSB) & RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_MASK)
#define RST_MISC_INTERRUPT_STATUS_DDR_ACTIVITY_IN_SF_RESET           0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_MSB                    17
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_LSB                    17
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_MASK                   0x00020000
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_GET(x)                 (((x) & RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_MASK) >> RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_LSB)
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_SET(x)                 (((x) << RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_LSB) & RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_MASK)
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_EXIT_RESET                  0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_MSB                   16
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_LSB                   16
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_MASK                  0x00010000
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_GET(x)                (((x) & RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_MASK) >> RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_LSB)
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_SET(x)                (((x) << RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_LSB) & RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_MASK)
#define RST_MISC_INTERRUPT_STATUS_DDR_SF_ENTRY_RESET                 0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_MSB                 15
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_LSB                 15
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_MASK                0x00008000
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_GET(x)              (((x) & RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_SET(x)              (((x) << RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_LSB) & RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_CHKSUM_ACC_INT_RESET               0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_MSB                        14
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_LSB                        14
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_MASK                       0x00004000
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_GET(x)                     (((x) & RST_MISC_INTERRUPT_STATUS_OTP_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_OTP_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_SET(x)                     (((x) << RST_MISC_INTERRUPT_STATUS_OTP_INT_LSB) & RST_MISC_INTERRUPT_STATUS_OTP_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_OTP_INT_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_MSB                  13
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_LSB                  13
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_MASK                 0x00002000
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_GET(x)               (((x) & RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_SET(x)               (((x) << RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_LSB) & RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_LUTS_AGER_INT_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_MSB                  12
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_LSB                  12
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_MASK                 0x00001000
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_GET(x)               (((x) & RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_SET(x)               (((x) << RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_LSB) & RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_SGMII_MAC_INT_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_MSB                   11
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_LSB                   11
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_MASK                  0x00000800
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_GET(x)                (((x) & RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_SET(x)                (((x) << RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_LSB) & RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_DDR_PERF_INT_RESET                 0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_MSB                     10
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_LSB                     10
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_MASK                    0x00000400
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_GET(x)                  (((x) & RST_MISC_INTERRUPT_STATUS_TIMER4_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_TIMER4_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_SET(x)                  (((x) << RST_MISC_INTERRUPT_STATUS_TIMER4_INT_LSB) & RST_MISC_INTERRUPT_STATUS_TIMER4_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_TIMER4_INT_RESET                   0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_MSB                     9
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_LSB                     9
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_MASK                    0x00000200
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_GET(x)                  (((x) & RST_MISC_INTERRUPT_STATUS_TIMER3_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_TIMER3_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_SET(x)                  (((x) << RST_MISC_INTERRUPT_STATUS_TIMER3_INT_LSB) & RST_MISC_INTERRUPT_STATUS_TIMER3_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_TIMER3_INT_RESET                   0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_MSB                     8
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_LSB                     8
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_MASK                    0x00000100
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_GET(x)                  (((x) & RST_MISC_INTERRUPT_STATUS_TIMER2_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_TIMER2_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_SET(x)                  (((x) << RST_MISC_INTERRUPT_STATUS_TIMER2_INT_LSB) & RST_MISC_INTERRUPT_STATUS_TIMER2_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_TIMER2_INT_RESET                   0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_MSB                       7
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_LSB                       7
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_MASK                      0x00000080
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_GET(x)                    (((x) & RST_MISC_INTERRUPT_STATUS_MBOX_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_MBOX_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_SET(x)                    (((x) << RST_MISC_INTERRUPT_STATUS_MBOX_INT_LSB) & RST_MISC_INTERRUPT_STATUS_MBOX_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_MBOX_INT_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_MSB                      6
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_LSB                      6
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_MASK                     0x00000040
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_GET(x)                   (((x) & RST_MISC_INTERRUPT_STATUS_UART1_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_UART1_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_SET(x)                   (((x) << RST_MISC_INTERRUPT_STATUS_UART1_INT_LSB) & RST_MISC_INTERRUPT_STATUS_UART1_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_UART1_INT_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_PC_INT_MSB                         5
#define RST_MISC_INTERRUPT_STATUS_PC_INT_LSB                         5
#define RST_MISC_INTERRUPT_STATUS_PC_INT_MASK                        0x00000020
#define RST_MISC_INTERRUPT_STATUS_PC_INT_GET(x)                      (((x) & RST_MISC_INTERRUPT_STATUS_PC_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_PC_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_PC_INT_SET(x)                      (((x) << RST_MISC_INTERRUPT_STATUS_PC_INT_LSB) & RST_MISC_INTERRUPT_STATUS_PC_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_PC_INT_RESET                       0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_MSB                   4
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_LSB                   4
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_MASK                  0x00000010
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_GET(x)                (((x) & RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_SET(x)                (((x) << RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_LSB) & RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_WATCHDOG_INT_RESET                 0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_UART_INT_MSB                       3
#define RST_MISC_INTERRUPT_STATUS_UART_INT_LSB                       3
#define RST_MISC_INTERRUPT_STATUS_UART_INT_MASK                      0x00000008
#define RST_MISC_INTERRUPT_STATUS_UART_INT_GET(x)                    (((x) & RST_MISC_INTERRUPT_STATUS_UART_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_UART_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_UART_INT_SET(x)                    (((x) << RST_MISC_INTERRUPT_STATUS_UART_INT_LSB) & RST_MISC_INTERRUPT_STATUS_UART_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_UART_INT_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_MSB                       2
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_LSB                       2
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_MASK                      0x00000004
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_GET(x)                    (((x) & RST_MISC_INTERRUPT_STATUS_GPIO_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_GPIO_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_SET(x)                    (((x) << RST_MISC_INTERRUPT_STATUS_GPIO_INT_LSB) & RST_MISC_INTERRUPT_STATUS_GPIO_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_GPIO_INT_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_MSB                      1
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_LSB                      1
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_MASK                     0x00000002
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_GET(x)                   (((x) & RST_MISC_INTERRUPT_STATUS_ERROR_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_ERROR_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_SET(x)                   (((x) << RST_MISC_INTERRUPT_STATUS_ERROR_INT_LSB) & RST_MISC_INTERRUPT_STATUS_ERROR_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_ERROR_INT_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_MSB                      0
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_LSB                      0
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_MASK                     0x00000001
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_GET(x)                   (((x) & RST_MISC_INTERRUPT_STATUS_TIMER_INT_MASK) >> RST_MISC_INTERRUPT_STATUS_TIMER_INT_LSB)
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_SET(x)                   (((x) << RST_MISC_INTERRUPT_STATUS_TIMER_INT_LSB) & RST_MISC_INTERRUPT_STATUS_TIMER_INT_MASK)
#define RST_MISC_INTERRUPT_STATUS_TIMER_INT_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_STATUS_ADDRESS                            0x18060010

#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_MSB               26
#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_LSB               26
#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_MASK              0x04000000
#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_GET(x)            (((x) & RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_SET(x)            (((x) << RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_LSB) & RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_USB2_PLL_LOCK_MASK_RESET             0x0 // 0
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_MSB               25
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_LSB               25
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_MASK              0x02000000
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_GET(x)            (((x) & RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_SET(x)            (((x) << RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_LSB) & RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_USB1_PLL_LOCK_MASK_RESET             0x0 // 0
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_MSB                         24
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_LSB                         24
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_MASK                        0x01000000
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_GET(x)                      (((x) & RST_MISC_INTERRUPT_MASK_I2C_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_I2C_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_SET(x)                      (((x) << RST_MISC_INTERRUPT_MASK_I2C_MASK_LSB) & RST_MISC_INTERRUPT_MASK_I2C_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_I2C_MASK_RESET                       0x0 // 0
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_MSB                         23
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_LSB                         23
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_MASK                        0x00800000
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_GET(x)                      (((x) & RST_MISC_INTERRUPT_MASK_FDC_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_FDC_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_SET(x)                      (((x) << RST_MISC_INTERRUPT_MASK_FDC_MASK_LSB) & RST_MISC_INTERRUPT_MASK_FDC_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_FDC_MASK_RESET                       0x0 // 0
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_MSB                   22
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_LSB                   22
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_MASK                  0x00400000
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_GET(x)                (((x) & RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_SET(x)                (((x) << RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_LSB) & RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_PGPIO_INT_MASK_RESET                 0x0 // 0
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_MSB                  21
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_LSB                  21
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_MASK                 0x00200000
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_GET(x)               (((x) & RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_SET(x)               (((x) << RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_LSB) & RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_NANDF_INTR_MASK_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_MSB                    20
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_LSB                    20
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_MASK                   0x00100000
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_GET(x)                 (((x) & RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_SET(x)                 (((x) << RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_LSB) & RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_WOW_INTR_MASK_RESET                  0x0 // 0
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_MSB                   19
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_LSB                   19
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_MASK                  0x00080000
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_GET(x)                (((x) & RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_SET(x)                (((x) << RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_LSB) & RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_SLIC_INTR_MASK_RESET                 0x0 // 0
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_MSB          18
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_LSB          18
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_MASK         0x00040000
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_GET(x)       (((x) & RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_SET(x)       (((x) << RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_LSB) & RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_DDR_ACTIVITY_IN_SF_MASK_RESET        0x0 // 0
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_MSB                 17
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_LSB                 17
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_MASK                0x00020000
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_GET(x)              (((x) & RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_SET(x)              (((x) << RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_LSB) & RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_DDR_SF_EXIT_MASK_RESET               0x0 // 0
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_MSB                16
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_LSB                16
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_MASK               0x00010000
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_GET(x)             (((x) & RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_SET(x)             (((x) << RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_LSB) & RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_DDR_SF_ENTRY_MASK_RESET              0x0 // 0
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_MSB                  15
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_LSB                  15
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_MASK                 0x00008000
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_GET(x)               (((x) & RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_SET(x)               (((x) << RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_LSB) & RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_CHKSUM_ACC_MASK_RESET                0x0 // 0
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_MSB                     14
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_LSB                     14
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_MASK                    0x00004000
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_GET(x)                  (((x) & RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_SET(x)                  (((x) << RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_LSB) & RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_OTP_INT_MASK_RESET                   0x0 // 0
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_MSB               13
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_LSB               13
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_MASK              0x00002000
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_GET(x)            (((x) & RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_SET(x)            (((x) << RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_LSB) & RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_LUTS_AGER_INT_MASK_RESET             0x0 // 0
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_MSB               12
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_LSB               12
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_MASK              0x00001000
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_GET(x)            (((x) & RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_SET(x)            (((x) << RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_LSB) & RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_SGMII_MAC_INT_MASK_RESET             0x0 // 0
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_MSB                    11
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_LSB                    11
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_MASK                   0x00000800
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_GET(x)                 (((x) & RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_SET(x)                 (((x) << RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_LSB) & RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_DDR_PERF_MASK_RESET                  0x0 // 0
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_MSB                      10
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_LSB                      10
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_MASK                     0x00000400
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_GET(x)                   (((x) & RST_MISC_INTERRUPT_MASK_TIMER4_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_TIMER4_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_SET(x)                   (((x) << RST_MISC_INTERRUPT_MASK_TIMER4_MASK_LSB) & RST_MISC_INTERRUPT_MASK_TIMER4_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_TIMER4_MASK_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_MSB                      9
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_LSB                      9
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_MASK                     0x00000200
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_GET(x)                   (((x) & RST_MISC_INTERRUPT_MASK_TIMER3_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_TIMER3_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_SET(x)                   (((x) << RST_MISC_INTERRUPT_MASK_TIMER3_MASK_LSB) & RST_MISC_INTERRUPT_MASK_TIMER3_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_TIMER3_MASK_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_MSB                      8
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_LSB                      8
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_MASK                     0x00000100
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_GET(x)                   (((x) & RST_MISC_INTERRUPT_MASK_TIMER2_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_TIMER2_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_SET(x)                   (((x) << RST_MISC_INTERRUPT_MASK_TIMER2_MASK_LSB) & RST_MISC_INTERRUPT_MASK_TIMER2_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_TIMER2_MASK_RESET                    0x0 // 0
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_MSB                        7
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_LSB                        7
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_MASK                       0x00000080
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_GET(x)                     (((x) & RST_MISC_INTERRUPT_MASK_MBOX_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_MBOX_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_SET(x)                     (((x) << RST_MISC_INTERRUPT_MASK_MBOX_MASK_LSB) & RST_MISC_INTERRUPT_MASK_MBOX_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_MBOX_MASK_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_MSB                       6
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_LSB                       6
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_MASK                      0x00000040
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_GET(x)                    (((x) & RST_MISC_INTERRUPT_MASK_UART1_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_UART1_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_SET(x)                    (((x) << RST_MISC_INTERRUPT_MASK_UART1_MASK_LSB) & RST_MISC_INTERRUPT_MASK_UART1_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_UART1_MASK_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_MASK_PC_MASK_MSB                          5
#define RST_MISC_INTERRUPT_MASK_PC_MASK_LSB                          5
#define RST_MISC_INTERRUPT_MASK_PC_MASK_MASK                         0x00000020
#define RST_MISC_INTERRUPT_MASK_PC_MASK_GET(x)                       (((x) & RST_MISC_INTERRUPT_MASK_PC_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_PC_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_PC_MASK_SET(x)                       (((x) << RST_MISC_INTERRUPT_MASK_PC_MASK_LSB) & RST_MISC_INTERRUPT_MASK_PC_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_PC_MASK_RESET                        0x0 // 0
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_MSB                    4
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_LSB                    4
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_MASK                   0x00000010
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_GET(x)                 (((x) & RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_SET(x)                 (((x) << RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_LSB) & RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_WATCHDOG_MASK_RESET                  0x0 // 0
#define RST_MISC_INTERRUPT_MASK_UART_MASK_MSB                        3
#define RST_MISC_INTERRUPT_MASK_UART_MASK_LSB                        3
#define RST_MISC_INTERRUPT_MASK_UART_MASK_MASK                       0x00000008
#define RST_MISC_INTERRUPT_MASK_UART_MASK_GET(x)                     (((x) & RST_MISC_INTERRUPT_MASK_UART_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_UART_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_UART_MASK_SET(x)                     (((x) << RST_MISC_INTERRUPT_MASK_UART_MASK_LSB) & RST_MISC_INTERRUPT_MASK_UART_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_UART_MASK_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_MSB                        2
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_LSB                        2
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_MASK                       0x00000004
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_GET(x)                     (((x) & RST_MISC_INTERRUPT_MASK_GPIO_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_GPIO_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_SET(x)                     (((x) << RST_MISC_INTERRUPT_MASK_GPIO_MASK_LSB) & RST_MISC_INTERRUPT_MASK_GPIO_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_GPIO_MASK_RESET                      0x0 // 0
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_MSB                       1
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_LSB                       1
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_MASK                      0x00000002
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_GET(x)                    (((x) & RST_MISC_INTERRUPT_MASK_ERROR_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_ERROR_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_SET(x)                    (((x) << RST_MISC_INTERRUPT_MASK_ERROR_MASK_LSB) & RST_MISC_INTERRUPT_MASK_ERROR_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_ERROR_MASK_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_MSB                       0
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_LSB                       0
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_MASK                      0x00000001
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_GET(x)                    (((x) & RST_MISC_INTERRUPT_MASK_TIMER_MASK_MASK) >> RST_MISC_INTERRUPT_MASK_TIMER_MASK_LSB)
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_SET(x)                    (((x) << RST_MISC_INTERRUPT_MASK_TIMER_MASK_LSB) & RST_MISC_INTERRUPT_MASK_TIMER_MASK_MASK)
#define RST_MISC_INTERRUPT_MASK_TIMER_MASK_RESET                     0x0 // 0
#define RST_MISC_INTERRUPT_MASK_ADDRESS                              0x18060014

#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_MSB                     9
#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_LSB                     9
#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_MASK                    0x00000200
#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_GET(x)                  (((x) & RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_SET(x)                  (((x) << RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_WMAC_INT_RESET                   0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_MSB                 8
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_LSB                 8
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_MASK                0x00000100
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_GET(x)              (((x) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_SET(x)              (((x) << RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_RC2_INT_RESET               0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_MSB                     7
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_LSB                     7
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_MASK                    0x00000080
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_GET(x)                  (((x) & RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_SET(x)                  (((x) << RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_USB2_INT_RESET                   0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_MSB                  6
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_LSB                  6
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_MASK                 0x00000040
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_GET(x)               (((x) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_SET(x)               (((x) << RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_EP_INT_RESET                0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_MSB                    5
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_LSB                    5
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_MASK                   0x00000020
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_GET(x)                 (((x) & RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_SET(x)                 (((x) << RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_TIMER_INT_RESET                  0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_MSB                     4
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_LSB                     4
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_MASK                    0x00000010
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_GET(x)                  (((x) & RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_SET(x)                  (((x) << RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_MISC_INT_RESET                   0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_MSB                      3
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_LSB                      3
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_MASK                     0x00000008
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_GET(x)                   (((x) & RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_SET(x)                   (((x) << RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_GE1_INT_RESET                    0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_MSB                      2
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_LSB                      2
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_MASK                     0x00000004
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_GET(x)                   (((x) & RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_SET(x)                   (((x) << RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_GE0_INT_RESET                    0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_MSB                     1
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_LSB                     1
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_MASK                    0x00000002
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_GET(x)                  (((x) & RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_SET(x)                  (((x) << RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_USB1_INT_RESET                   0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_MSB                     0
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_LSB                     0
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_MASK                    0x00000001
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_GET(x)                  (((x) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_MASK) >> RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_LSB)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_SET(x)                  (((x) << RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_LSB) & RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_MASK)
#define RST_GLOBAL_INTERRUPT_STATUS_PCIE_INT_RESET                   0x0 // 0
#define RST_GLOBAL_INTERRUPT_STATUS_ADDRESS                          0x18060018

#define RST_EXT_INTERRUPT_STATUS_USB2_INT_MSB		28
#define RST_EXT_INTERRUPT_STATUS_USB2_INT_LSB		28
#define RST_EXT_INTERRUPT_STATUS_USB2_INT_MASK		0x10000000
#define RST_EXT_INTERRUPT_STATUS_USB2_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_USB2_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_USB2_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_USB2_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_USB2_INT_LSB) & RST_EXT_INTERRUPT_STATUS_USB2_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_USB2_INT_RESET		0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_MSB		24
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_LSB		24
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_MASK		0x01000000
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_USB1_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_USB1_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_USB1_INT_LSB) & RST_EXT_INTERRUPT_STATUS_USB1_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_USB1_INT_RESET		0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_MSB	21
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_LSB	21
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_MASK	0x00200000
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_HOSTIF_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_MSB	20
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_LSB	20
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_MASK	0x00100000
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_HSTDMA_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_MSB	16
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_LSB	16
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_MASK	0x00010000
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT3_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_MSB	15
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_LSB	15
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_MASK	0x00008000
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT2_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_MSB	14
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_LSB	14
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_MASK	0x00004000
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT1_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_MSB	13
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_LSB	13
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_MASK	0x00002000
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT0_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_MSB	12
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_LSB	12
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_MASK	0x00001000
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC2_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_MSB	8
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_LSB	8
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_MASK	0x00000100
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT3_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_MSB	7
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_LSB	7
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_MASK	0x00000080
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT2_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_MSB	6
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_LSB	6
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_MASK	0x00000040
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT1_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_MSB	5
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_LSB	5
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_MASK	0x00000020
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT0_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_MSB	4
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_LSB	4
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_MASK	0x00000010
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_LSB) & RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_PCIE_RC_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_MSB	3
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_LSB	3
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_MASK	0x00000008
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_LSB) & RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXHP_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_MSB	2
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_LSB	2
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_MASK	0x00000004
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_LSB) & RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_WMAC_RXLP_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_MSB	1
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_LSB	1
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_MASK	0x00000002
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_LSB) & RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_WMAC_TX_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_MSB	0
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_LSB	0
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_MASK	0x00000001
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_GET(x)	(((x) & RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_MASK) >> RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_LSB)
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_SET(x)	(((x) << RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_LSB) & RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_MASK)
#define RST_EXT_INTERRUPT_STATUS_WMAC_MISC_INT_RESET	0x0 // 0
#define RST_EXT_INTERRUPT_STATUS_ADDRESS		0x180600ac

#define RST_MISC2_PCIEEP_LINK_UP_MSB                                 30
#define RST_MISC2_PCIEEP_LINK_UP_LSB                                 30
#define RST_MISC2_PCIEEP_LINK_UP_MASK                                0x40000000
#define RST_MISC2_PCIEEP_LINK_UP_GET(x)                              (((x) & RST_MISC2_PCIEEP_LINK_UP_MASK) >> RST_MISC2_PCIEEP_LINK_UP_LSB)
#define RST_MISC2_PCIEEP_LINK_UP_SET(x)                              (((x) << RST_MISC2_PCIEEP_LINK_UP_LSB) & RST_MISC2_PCIEEP_LINK_UP_MASK)
#define RST_MISC2_PCIEEP_LINK_UP_RESET                               0x0 // 0
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_MSB                             29
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_LSB                             29
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_MASK                            0x20000000
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_GET(x)                          (((x) & RST_MISC2_PCIEEP_CLKOBS2_SEL_MASK) >> RST_MISC2_PCIEEP_CLKOBS2_SEL_LSB)
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_SET(x)                          (((x) << RST_MISC2_PCIEEP_CLKOBS2_SEL_LSB) & RST_MISC2_PCIEEP_CLKOBS2_SEL_MASK)
#define RST_MISC2_PCIEEP_CLKOBS2_SEL_RESET                           0x0 // 0
#define RST_MISC2_PCIE_CLKOBS1_SEL_MSB                               28
#define RST_MISC2_PCIE_CLKOBS1_SEL_LSB                               28
#define RST_MISC2_PCIE_CLKOBS1_SEL_MASK                              0x10000000
#define RST_MISC2_PCIE_CLKOBS1_SEL_GET(x)                            (((x) & RST_MISC2_PCIE_CLKOBS1_SEL_MASK) >> RST_MISC2_PCIE_CLKOBS1_SEL_LSB)
#define RST_MISC2_PCIE_CLKOBS1_SEL_SET(x)                            (((x) << RST_MISC2_PCIE_CLKOBS1_SEL_LSB) & RST_MISC2_PCIE_CLKOBS1_SEL_MASK)
#define RST_MISC2_PCIE_CLKOBS1_SEL_RESET                             0x0 // 0
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_MSB                     27
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_LSB                     27
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_MASK                    0x08000000
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_GET(x)                  (((x) & RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_MASK) >> RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_LSB)
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_SET(x)                  (((x) << RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_LSB) & RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_MASK)
#define RST_MISC2_JTAG_EJTAG_SWITCH_CPU_CTRL_RESET                   0x0 // 0
#define RST_MISC2_WOW_STATUS_MSB                                     26
#define RST_MISC2_WOW_STATUS_LSB                                     26
#define RST_MISC2_WOW_STATUS_MASK                                    0x04000000
#define RST_MISC2_WOW_STATUS_GET(x)                                  (((x) & RST_MISC2_WOW_STATUS_MASK) >> RST_MISC2_WOW_STATUS_LSB)
#define RST_MISC2_WOW_STATUS_SET(x)                                  (((x) << RST_MISC2_WOW_STATUS_LSB) & RST_MISC2_WOW_STATUS_MASK)
#define RST_MISC2_WOW_STATUS_RESET                                   0x0 // 0
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
#define RST_MISC2_PCIEEP_RST_INT_MSB                                 17
#define RST_MISC2_PCIEEP_RST_INT_LSB                                 17
#define RST_MISC2_PCIEEP_RST_INT_MASK                                0x00020000
#define RST_MISC2_PCIEEP_RST_INT_GET(x)                              (((x) & RST_MISC2_PCIEEP_RST_INT_MASK) >> RST_MISC2_PCIEEP_RST_INT_LSB)
#define RST_MISC2_PCIEEP_RST_INT_SET(x)                              (((x) << RST_MISC2_PCIEEP_RST_INT_LSB) & RST_MISC2_PCIEEP_RST_INT_MASK)
#define RST_MISC2_PCIEEP_RST_INT_RESET                               0x0 // 0
#define RST_MISC2_HOST_RESET_INT_MSB                                 16
#define RST_MISC2_HOST_RESET_INT_LSB                                 16
#define RST_MISC2_HOST_RESET_INT_MASK                                0x00010000
#define RST_MISC2_HOST_RESET_INT_GET(x)                              (((x) & RST_MISC2_HOST_RESET_INT_MASK) >> RST_MISC2_HOST_RESET_INT_LSB)
#define RST_MISC2_HOST_RESET_INT_SET(x)                              (((x) << RST_MISC2_HOST_RESET_INT_LSB) & RST_MISC2_HOST_RESET_INT_MASK)
#define RST_MISC2_HOST_RESET_INT_RESET                               0x0 // 0
#define RST_MISC2_CPU_HOST_WA_MSB                                    15
#define RST_MISC2_CPU_HOST_WA_LSB                                    15
#define RST_MISC2_CPU_HOST_WA_MASK                                   0x00008000
#define RST_MISC2_CPU_HOST_WA_GET(x)                                 (((x) & RST_MISC2_CPU_HOST_WA_MASK) >> RST_MISC2_CPU_HOST_WA_LSB)
#define RST_MISC2_CPU_HOST_WA_SET(x)                                 (((x) << RST_MISC2_CPU_HOST_WA_LSB) & RST_MISC2_CPU_HOST_WA_MASK)
#define RST_MISC2_CPU_HOST_WA_RESET                                  0x0 // 0
#define RST_MISC2_PERSTN_RCPHY2_MSB                                  14
#define RST_MISC2_PERSTN_RCPHY2_LSB                                  14
#define RST_MISC2_PERSTN_RCPHY2_MASK                                 0x00004000
#define RST_MISC2_PERSTN_RCPHY2_GET(x)                               (((x) & RST_MISC2_PERSTN_RCPHY2_MASK) >> RST_MISC2_PERSTN_RCPHY2_LSB)
#define RST_MISC2_PERSTN_RCPHY2_SET(x)                               (((x) << RST_MISC2_PERSTN_RCPHY2_LSB) & RST_MISC2_PERSTN_RCPHY2_MASK)
#define RST_MISC2_PERSTN_RCPHY2_RESET                                0x1 // 1
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
#define RST_MISC2_PCIEEP_LINK_STATUS_MSB                             4
#define RST_MISC2_PCIEEP_LINK_STATUS_LSB                             4
#define RST_MISC2_PCIEEP_LINK_STATUS_MASK                            0x00000010
#define RST_MISC2_PCIEEP_LINK_STATUS_GET(x)                          (((x) & RST_MISC2_PCIEEP_LINK_STATUS_MASK) >> RST_MISC2_PCIEEP_LINK_STATUS_LSB)
#define RST_MISC2_PCIEEP_LINK_STATUS_SET(x)                          (((x) << RST_MISC2_PCIEEP_LINK_STATUS_LSB) & RST_MISC2_PCIEEP_LINK_STATUS_MASK)
#define RST_MISC2_PCIEEP_LINK_STATUS_RESET                           0x0 // 0
#define RST_MISC2_WOW_DETECT_MSB                                     3
#define RST_MISC2_WOW_DETECT_LSB                                     3
#define RST_MISC2_WOW_DETECT_MASK                                    0x00000008
#define RST_MISC2_WOW_DETECT_GET(x)                                  (((x) & RST_MISC2_WOW_DETECT_MASK) >> RST_MISC2_WOW_DETECT_LSB)
#define RST_MISC2_WOW_DETECT_SET(x)                                  (((x) << RST_MISC2_WOW_DETECT_LSB) & RST_MISC2_WOW_DETECT_MASK)
#define RST_MISC2_WOW_DETECT_RESET                                   0x0 // 0
#define RST_MISC2_PCIEEP_RXDETECT_DONE_MSB                           2
#define RST_MISC2_PCIEEP_RXDETECT_DONE_LSB                           2
#define RST_MISC2_PCIEEP_RXDETECT_DONE_MASK                          0x00000004
#define RST_MISC2_PCIEEP_RXDETECT_DONE_GET(x)                        (((x) & RST_MISC2_PCIEEP_RXDETECT_DONE_MASK) >> RST_MISC2_PCIEEP_RXDETECT_DONE_LSB)
#define RST_MISC2_PCIEEP_RXDETECT_DONE_SET(x)                        (((x) << RST_MISC2_PCIEEP_RXDETECT_DONE_LSB) & RST_MISC2_PCIEEP_RXDETECT_DONE_MASK)
#define RST_MISC2_PCIEEP_RXDETECT_DONE_RESET                         0x0 // 0
#define RST_MISC2_PCIEEP_WOW_INT_MSB                                 1
#define RST_MISC2_PCIEEP_WOW_INT_LSB                                 1
#define RST_MISC2_PCIEEP_WOW_INT_MASK                                0x00000002
#define RST_MISC2_PCIEEP_WOW_INT_GET(x)                              (((x) & RST_MISC2_PCIEEP_WOW_INT_MASK) >> RST_MISC2_PCIEEP_WOW_INT_LSB)
#define RST_MISC2_PCIEEP_WOW_INT_SET(x)                              (((x) << RST_MISC2_PCIEEP_WOW_INT_LSB) & RST_MISC2_PCIEEP_WOW_INT_MASK)
#define RST_MISC2_PCIEEP_WOW_INT_RESET                               0x0 // 0
#define RST_MISC2_PCIEEP_CFG_DONE_MSB                                0
#define RST_MISC2_PCIEEP_CFG_DONE_LSB                                0
#define RST_MISC2_PCIEEP_CFG_DONE_MASK                               0x00000001
#define RST_MISC2_PCIEEP_CFG_DONE_GET(x)                             (((x) & RST_MISC2_PCIEEP_CFG_DONE_MASK) >> RST_MISC2_PCIEEP_CFG_DONE_LSB)
#define RST_MISC2_PCIEEP_CFG_DONE_SET(x)                             (((x) << RST_MISC2_PCIEEP_CFG_DONE_LSB) & RST_MISC2_PCIEEP_CFG_DONE_MASK)
#define RST_MISC2_PCIEEP_CFG_DONE_RESET                              0x0 // 0
#define RST_MISC2_ADDRESS                                            0x180600bc

#define DMA_RESET_DMA_TX_RESET_MSB                                   31
#define DMA_RESET_DMA_TX_RESET_LSB                                   31
#define DMA_RESET_DMA_TX_RESET_MASK                                  0x80000000
#define DMA_RESET_DMA_TX_RESET_GET(x)                                (((x) & DMA_RESET_DMA_TX_RESET_MASK) >> DMA_RESET_DMA_TX_RESET_LSB)
#define DMA_RESET_DMA_TX_RESET_SET(x)                                (((x) << DMA_RESET_DMA_TX_RESET_LSB) & DMA_RESET_DMA_TX_RESET_MASK)
#define DMA_RESET_DMA_TX_RESET_RESET                                 0x0 // 0
#define DMA_RESET_DMA_RX_RESET_MSB                                   30
#define DMA_RESET_DMA_RX_RESET_LSB                                   30
#define DMA_RESET_DMA_RX_RESET_MASK                                  0x40000000
#define DMA_RESET_DMA_RX_RESET_GET(x)                                (((x) & DMA_RESET_DMA_RX_RESET_MASK) >> DMA_RESET_DMA_RX_RESET_LSB)
#define DMA_RESET_DMA_RX_RESET_SET(x)                                (((x) << DMA_RESET_DMA_RX_RESET_LSB) & DMA_RESET_DMA_RX_RESET_MASK)
#define DMA_RESET_DMA_RX_RESET_RESET                                 0x0 // 0
#define DMA_RESET_SCRATCHREG_2_MSB                                   29
#define DMA_RESET_SCRATCHREG_2_LSB                                   0
#define DMA_RESET_SCRATCHREG_2_MASK                                  0x3fffffff
#define DMA_RESET_SCRATCHREG_2_GET(x)                                (((x) & DMA_RESET_SCRATCHREG_2_MASK) >> DMA_RESET_SCRATCHREG_2_LSB)
#define DMA_RESET_SCRATCHREG_2_SET(x)                                (((x) << DMA_RESET_SCRATCHREG_2_LSB) & DMA_RESET_SCRATCHREG_2_MASK)
#define DMA_RESET_SCRATCHREG_2_RESET                                 0x0 // 0
#define DMA_RESET_ADDRESS                                            0x01bc
#define DMA_RESET_MASK                                               0xffffffff
#define DMA_RESET_RESET                                              0x00000000

#define XTAL_TCXODET_MSB                                             31
#define XTAL_TCXODET_LSB                                             31
#define XTAL_TCXODET_MASK                                            0x80000000
#define XTAL_TCXODET_GET(x)                                          (((x) & XTAL_TCXODET_MASK) >> XTAL_TCXODET_LSB)
#define XTAL_TCXODET_SET(x)                                          (((x) << XTAL_TCXODET_LSB) & XTAL_TCXODET_MASK)
#define XTAL_TCXODET_RESET                                           0x0 // 0
#define XTAL_XTAL_CAPINDAC_MSB                                       30
#define XTAL_XTAL_CAPINDAC_LSB                                       24
#define XTAL_XTAL_CAPINDAC_MASK                                      0x7f000000
#define XTAL_XTAL_CAPINDAC_GET(x)                                    (((x) & XTAL_XTAL_CAPINDAC_MASK) >> XTAL_XTAL_CAPINDAC_LSB)
#define XTAL_XTAL_CAPINDAC_SET(x)                                    (((x) << XTAL_XTAL_CAPINDAC_LSB) & XTAL_XTAL_CAPINDAC_MASK)
#define XTAL_XTAL_CAPINDAC_RESET                                     0x4b // 75
#define XTAL_XTAL_CAPOUTDAC_MSB                                      23
#define XTAL_XTAL_CAPOUTDAC_LSB                                      17
#define XTAL_XTAL_CAPOUTDAC_MASK                                     0x00fe0000
#define XTAL_XTAL_CAPOUTDAC_GET(x)                                   (((x) & XTAL_XTAL_CAPOUTDAC_MASK) >> XTAL_XTAL_CAPOUTDAC_LSB)
#define XTAL_XTAL_CAPOUTDAC_SET(x)                                   (((x) << XTAL_XTAL_CAPOUTDAC_LSB) & XTAL_XTAL_CAPOUTDAC_MASK)
#define XTAL_XTAL_CAPOUTDAC_RESET                                    0x4b // 75
#define XTAL_XTAL_DRVSTR_MSB                                         16
#define XTAL_XTAL_DRVSTR_LSB                                         15
#define XTAL_XTAL_DRVSTR_MASK                                        0x00018000
#define XTAL_XTAL_DRVSTR_GET(x)                                      (((x) & XTAL_XTAL_DRVSTR_MASK) >> XTAL_XTAL_DRVSTR_LSB)
#define XTAL_XTAL_DRVSTR_SET(x)                                      (((x) << XTAL_XTAL_DRVSTR_LSB) & XTAL_XTAL_DRVSTR_MASK)
#define XTAL_XTAL_DRVSTR_RESET                                       0x0 // 0
#define XTAL_XTAL_SHORTXIN_MSB                                       14
#define XTAL_XTAL_SHORTXIN_LSB                                       14
#define XTAL_XTAL_SHORTXIN_MASK                                      0x00004000
#define XTAL_XTAL_SHORTXIN_GET(x)                                    (((x) & XTAL_XTAL_SHORTXIN_MASK) >> XTAL_XTAL_SHORTXIN_LSB)
#define XTAL_XTAL_SHORTXIN_SET(x)                                    (((x) << XTAL_XTAL_SHORTXIN_LSB) & XTAL_XTAL_SHORTXIN_MASK)
#define XTAL_XTAL_SHORTXIN_RESET                                     0x0 // 0
#define XTAL_XTAL_LOCALBIAS_MSB                                      13
#define XTAL_XTAL_LOCALBIAS_LSB                                      13
#define XTAL_XTAL_LOCALBIAS_MASK                                     0x00002000
#define XTAL_XTAL_LOCALBIAS_GET(x)                                   (((x) & XTAL_XTAL_LOCALBIAS_MASK) >> XTAL_XTAL_LOCALBIAS_LSB)
#define XTAL_XTAL_LOCALBIAS_SET(x)                                   (((x) << XTAL_XTAL_LOCALBIAS_LSB) & XTAL_XTAL_LOCALBIAS_MASK)
#define XTAL_XTAL_LOCALBIAS_RESET                                    0x1 // 1
#define XTAL_XTAL_PWDCLKD_MSB                                        12
#define XTAL_XTAL_PWDCLKD_LSB                                        12
#define XTAL_XTAL_PWDCLKD_MASK                                       0x00001000
#define XTAL_XTAL_PWDCLKD_GET(x)                                     (((x) & XTAL_XTAL_PWDCLKD_MASK) >> XTAL_XTAL_PWDCLKD_LSB)
#define XTAL_XTAL_PWDCLKD_SET(x)                                     (((x) << XTAL_XTAL_PWDCLKD_LSB) & XTAL_XTAL_PWDCLKD_MASK)
#define XTAL_XTAL_PWDCLKD_RESET                                      0x0 // 0
#define XTAL_XTAL_BIAS2X_MSB                                         11
#define XTAL_XTAL_BIAS2X_LSB                                         11
#define XTAL_XTAL_BIAS2X_MASK                                        0x00000800
#define XTAL_XTAL_BIAS2X_GET(x)                                      (((x) & XTAL_XTAL_BIAS2X_MASK) >> XTAL_XTAL_BIAS2X_LSB)
#define XTAL_XTAL_BIAS2X_SET(x)                                      (((x) << XTAL_XTAL_BIAS2X_LSB) & XTAL_XTAL_BIAS2X_MASK)
#define XTAL_XTAL_BIAS2X_RESET                                       0x1 // 1
#define XTAL_XTAL_LBIAS2X_MSB                                        10
#define XTAL_XTAL_LBIAS2X_LSB                                        10
#define XTAL_XTAL_LBIAS2X_MASK                                       0x00000400
#define XTAL_XTAL_LBIAS2X_GET(x)                                     (((x) & XTAL_XTAL_LBIAS2X_MASK) >> XTAL_XTAL_LBIAS2X_LSB)
#define XTAL_XTAL_LBIAS2X_SET(x)                                     (((x) << XTAL_XTAL_LBIAS2X_LSB) & XTAL_XTAL_LBIAS2X_MASK)
#define XTAL_XTAL_LBIAS2X_RESET                                      0x1 // 1
#define XTAL_XTAL_ATBVREG_MSB                                        9
#define XTAL_XTAL_ATBVREG_LSB                                        9
#define XTAL_XTAL_ATBVREG_MASK                                       0x00000200
#define XTAL_XTAL_ATBVREG_GET(x)                                     (((x) & XTAL_XTAL_ATBVREG_MASK) >> XTAL_XTAL_ATBVREG_LSB)
#define XTAL_XTAL_ATBVREG_SET(x)                                     (((x) << XTAL_XTAL_ATBVREG_LSB) & XTAL_XTAL_ATBVREG_MASK)
#define XTAL_XTAL_ATBVREG_RESET                                      0x0 // 0
#define XTAL_XTAL_OSCON_MSB                                          8
#define XTAL_XTAL_OSCON_LSB                                          8
#define XTAL_XTAL_OSCON_MASK                                         0x00000100
#define XTAL_XTAL_OSCON_GET(x)                                       (((x) & XTAL_XTAL_OSCON_MASK) >> XTAL_XTAL_OSCON_LSB)
#define XTAL_XTAL_OSCON_SET(x)                                       (((x) << XTAL_XTAL_OSCON_LSB) & XTAL_XTAL_OSCON_MASK)
#define XTAL_XTAL_OSCON_RESET                                        0x1 // 1
#define XTAL_XTAL_PWDCLKIN_MSB                                       7
#define XTAL_XTAL_PWDCLKIN_LSB                                       7
#define XTAL_XTAL_PWDCLKIN_MASK                                      0x00000080
#define XTAL_XTAL_PWDCLKIN_GET(x)                                    (((x) & XTAL_XTAL_PWDCLKIN_MASK) >> XTAL_XTAL_PWDCLKIN_LSB)
#define XTAL_XTAL_PWDCLKIN_SET(x)                                    (((x) << XTAL_XTAL_PWDCLKIN_LSB) & XTAL_XTAL_PWDCLKIN_MASK)
#define XTAL_XTAL_PWDCLKIN_RESET                                     0x0 // 0
#define XTAL_LOCAL_XTAL_MSB                                          6
#define XTAL_LOCAL_XTAL_LSB                                          6
#define XTAL_LOCAL_XTAL_MASK                                         0x00000040
#define XTAL_LOCAL_XTAL_GET(x)                                       (((x) & XTAL_LOCAL_XTAL_MASK) >> XTAL_LOCAL_XTAL_LSB)
#define XTAL_LOCAL_XTAL_SET(x)                                       (((x) << XTAL_LOCAL_XTAL_LSB) & XTAL_LOCAL_XTAL_MASK)
#define XTAL_LOCAL_XTAL_RESET                                        0x0 // 0
#define XTAL_PWD_SWREGCLK_MSB                                        5
#define XTAL_PWD_SWREGCLK_LSB                                        5
#define XTAL_PWD_SWREGCLK_MASK                                       0x00000020
#define XTAL_PWD_SWREGCLK_GET(x)                                     (((x) & XTAL_PWD_SWREGCLK_MASK) >> XTAL_PWD_SWREGCLK_LSB)
#define XTAL_PWD_SWREGCLK_SET(x)                                     (((x) << XTAL_PWD_SWREGCLK_LSB) & XTAL_PWD_SWREGCLK_MASK)
#define XTAL_PWD_SWREGCLK_RESET                                      0x0 // 0
#define XTAL_SWREGCLK_EDGE_SEL_MSB                                   4
#define XTAL_SWREGCLK_EDGE_SEL_LSB                                   4
#define XTAL_SWREGCLK_EDGE_SEL_MASK                                  0x00000010
#define XTAL_SWREGCLK_EDGE_SEL_GET(x)                                (((x) & XTAL_SWREGCLK_EDGE_SEL_MASK) >> XTAL_SWREGCLK_EDGE_SEL_LSB)
#define XTAL_SWREGCLK_EDGE_SEL_SET(x)                                (((x) << XTAL_SWREGCLK_EDGE_SEL_LSB) & XTAL_SWREGCLK_EDGE_SEL_MASK)
#define XTAL_SWREGCLK_EDGE_SEL_RESET                                 0x0 // 0
#define XTAL_SPARE_MSB                                               3
#define XTAL_SPARE_LSB                                               0
#define XTAL_SPARE_MASK                                              0x0000000f
#define XTAL_SPARE_GET(x)                                            (((x) & XTAL_SPARE_MASK) >> XTAL_SPARE_LSB)
#define XTAL_SPARE_SET(x)                                            (((x) << XTAL_SPARE_LSB) & XTAL_SPARE_MASK)
#define XTAL_SPARE_RESET                                             0xf // 15
#define XTAL_ADDRESS                                                 0x18116290

#define UART1_REG_ADDRESS                                            0x18500000
#define RST_REVISION_ID_ADDRESS                                      0x18060090
#define RST_GENERAL_TIMER2_ADDRESS                                   0x18060094
#define RST_GENERAL_TIMER2_RELOAD_ADDRESS                            0x18060098
#define RST_GENERAL_TIMER3_ADDRESS                                   0x1806009c
#define RST_GENERAL_TIMER3_RELOAD_ADDRESS                            0x180600a0
#define is_drqfn()	(!(ath_reg_rd(RST_REVISION_ID_ADDRESS) & 0x1000))

#define RST_BOOTSTRAP_BOOT_INTF_SEL_MSB                              17
#define RST_BOOTSTRAP_BOOT_INTF_SEL_LSB                              16
#define RST_BOOTSTRAP_BOOT_INTF_SEL_MASK                             0x00030000
#define RST_BOOTSTRAP_BOOT_INTF_SEL_GET(x)                           (((x) & RST_BOOTSTRAP_BOOT_INTF_SEL_MASK) >> RST_BOOTSTRAP_BOOT_INTF_SEL_LSB)
#define RST_BOOTSTRAP_BOOT_INTF_SEL_SET(x)                           (((x) << RST_BOOTSTRAP_BOOT_INTF_SEL_LSB) & RST_BOOTSTRAP_BOOT_INTF_SEL_MASK)
#define RST_BOOTSTRAP_BOOT_INTF_SEL_RESET                            0x0 // 0
#define RST_BOOTSTRAP_RES0_MSB                                       15
#define RST_BOOTSTRAP_RES0_LSB                                       13
#define RST_BOOTSTRAP_RES0_MASK                                      0x0000e000
#define RST_BOOTSTRAP_RES0_GET(x)                                    (((x) & RST_BOOTSTRAP_RES0_MASK) >> RST_BOOTSTRAP_RES0_LSB)
#define RST_BOOTSTRAP_RES0_SET(x)                                    (((x) << RST_BOOTSTRAP_RES0_LSB) & RST_BOOTSTRAP_RES0_MASK)
#define RST_BOOTSTRAP_RES0_RESET                                     0x0 // 0
#define RST_BOOTSTRAP_SW_OPTION2_MSB                                 12
#define RST_BOOTSTRAP_SW_OPTION2_LSB                                 12
#define RST_BOOTSTRAP_SW_OPTION2_MASK                                0x00001000
#define RST_BOOTSTRAP_SW_OPTION2_GET(x)                              (((x) & RST_BOOTSTRAP_SW_OPTION2_MASK) >> RST_BOOTSTRAP_SW_OPTION2_LSB)
#define RST_BOOTSTRAP_SW_OPTION2_SET(x)                              (((x) << RST_BOOTSTRAP_SW_OPTION2_LSB) & RST_BOOTSTRAP_SW_OPTION2_MASK)
#define RST_BOOTSTRAP_SW_OPTION2_RESET                               0x0 // 0
#define RST_BOOTSTRAP_SW_OPTION1_MSB                                 11
#define RST_BOOTSTRAP_SW_OPTION1_LSB                                 11
#define RST_BOOTSTRAP_SW_OPTION1_MASK                                0x00000800
#define RST_BOOTSTRAP_SW_OPTION1_GET(x)                              (((x) & RST_BOOTSTRAP_SW_OPTION1_MASK) >> RST_BOOTSTRAP_SW_OPTION1_LSB)
#define RST_BOOTSTRAP_SW_OPTION1_SET(x)                              (((x) << RST_BOOTSTRAP_SW_OPTION1_LSB) & RST_BOOTSTRAP_SW_OPTION1_MASK)
#define RST_BOOTSTRAP_SW_OPTION1_RESET                               0x0 // 0
#define RST_BOOTSTRAP_TESTROM_DISABLE_MSB                            10
#define RST_BOOTSTRAP_TESTROM_DISABLE_LSB                            10
#define RST_BOOTSTRAP_TESTROM_DISABLE_MASK                           0x00000400
#define RST_BOOTSTRAP_TESTROM_DISABLE_GET(x)                         (((x) & RST_BOOTSTRAP_TESTROM_DISABLE_MASK) >> RST_BOOTSTRAP_TESTROM_DISABLE_LSB)
#define RST_BOOTSTRAP_TESTROM_DISABLE_SET(x)                         (((x) << RST_BOOTSTRAP_TESTROM_DISABLE_LSB) & RST_BOOTSTRAP_TESTROM_DISABLE_MASK)
#define RST_BOOTSTRAP_TESTROM_DISABLE_RESET                          0x1 // 1
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_MSB                      9
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_LSB                      9
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_MASK                     0x00000200
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_GET(x)                   (((x) & RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_MASK) >> RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_LSB)
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_SET(x)                   (((x) << RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_LSB) & RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_MASK)
#define RST_BOOTSTRAP_DISABLE_OTPMEM_ACCESS_RESET                    0x0 // 0
#define RST_BOOTSTRAP_SRIF_ENABLE_MSB                                8
#define RST_BOOTSTRAP_SRIF_ENABLE_LSB                                8
#define RST_BOOTSTRAP_SRIF_ENABLE_MASK                               0x00000100
#define RST_BOOTSTRAP_SRIF_ENABLE_GET(x)                             (((x) & RST_BOOTSTRAP_SRIF_ENABLE_MASK) >> RST_BOOTSTRAP_SRIF_ENABLE_LSB)
#define RST_BOOTSTRAP_SRIF_ENABLE_SET(x)                             (((x) << RST_BOOTSTRAP_SRIF_ENABLE_LSB) & RST_BOOTSTRAP_SRIF_ENABLE_MASK)
#define RST_BOOTSTRAP_SRIF_ENABLE_RESET                              0x0 // 0
#define RST_BOOTSTRAP_USB_MODE_MSB                                   7
#define RST_BOOTSTRAP_USB_MODE_LSB                                   7
#define RST_BOOTSTRAP_USB_MODE_MASK                                  0x00000080
#define RST_BOOTSTRAP_USB_MODE_GET(x)                                (((x) & RST_BOOTSTRAP_USB_MODE_MASK) >> RST_BOOTSTRAP_USB_MODE_LSB)
#define RST_BOOTSTRAP_USB_MODE_SET(x)                                (((x) << RST_BOOTSTRAP_USB_MODE_LSB) & RST_BOOTSTRAP_USB_MODE_MASK)
#define RST_BOOTSTRAP_USB_MODE_RESET                                 0x0 // 0
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_MSB                          6
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_LSB                          6
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_MASK                         0x00000040
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_GET(x)                       (((x) & RST_BOOTSTRAP_PCIE_RC_EP_SELECT_MASK) >> RST_BOOTSTRAP_PCIE_RC_EP_SELECT_LSB)
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_SET(x)                       (((x) << RST_BOOTSTRAP_PCIE_RC_EP_SELECT_LSB) & RST_BOOTSTRAP_PCIE_RC_EP_SELECT_MASK)
#define RST_BOOTSTRAP_PCIE_RC_EP_SELECT_RESET                        0x0 // 0
#define RST_BOOTSTRAP_JTAG_MODE_MSB                                  5
#define RST_BOOTSTRAP_JTAG_MODE_LSB                                  5
#define RST_BOOTSTRAP_JTAG_MODE_MASK                                 0x00000020
#define RST_BOOTSTRAP_JTAG_MODE_GET(x)                               (((x) & RST_BOOTSTRAP_JTAG_MODE_MASK) >> RST_BOOTSTRAP_JTAG_MODE_LSB)
#define RST_BOOTSTRAP_JTAG_MODE_SET(x)                               (((x) << RST_BOOTSTRAP_JTAG_MODE_LSB) & RST_BOOTSTRAP_JTAG_MODE_MASK)
#define RST_BOOTSTRAP_JTAG_MODE_RESET                                0x1 // 1
#define RST_BOOTSTRAP_REF_CLK_MSB                                    4
#define RST_BOOTSTRAP_REF_CLK_LSB                                    4
#define RST_BOOTSTRAP_REF_CLK_MASK                                   0x00000010
#define RST_BOOTSTRAP_REF_CLK_GET(x)                                 (((x) & RST_BOOTSTRAP_REF_CLK_MASK) >> RST_BOOTSTRAP_REF_CLK_LSB)
#define RST_BOOTSTRAP_REF_CLK_SET(x)                                 (((x) << RST_BOOTSTRAP_REF_CLK_LSB) & RST_BOOTSTRAP_REF_CLK_MASK)
#define RST_BOOTSTRAP_REF_CLK_RESET                                  0x0 // 0
#define RST_BOOTSTRAP_DDR_WIDTH_MSB                                  3
#define RST_BOOTSTRAP_DDR_WIDTH_LSB                                  3
#define RST_BOOTSTRAP_DDR_WIDTH_MASK                                 0x00000008
#define RST_BOOTSTRAP_DDR_WIDTH_GET(x)                               (((x) & RST_BOOTSTRAP_DDR_WIDTH_MASK) >> RST_BOOTSTRAP_DDR_WIDTH_LSB)
#define RST_BOOTSTRAP_DDR_WIDTH_SET(x)                               (((x) << RST_BOOTSTRAP_DDR_WIDTH_LSB) & RST_BOOTSTRAP_DDR_WIDTH_MASK)
#define RST_BOOTSTRAP_DDR_WIDTH_RESET                                0x0 // 0
#define RST_BOOTSTRAP_BOOT_SELECT_MSB                                2
#define RST_BOOTSTRAP_BOOT_SELECT_LSB                                2
#define RST_BOOTSTRAP_BOOT_SELECT_MASK                               0x00000004
#define RST_BOOTSTRAP_BOOT_SELECT_GET(x)                             (((x) & RST_BOOTSTRAP_BOOT_SELECT_MASK) >> RST_BOOTSTRAP_BOOT_SELECT_LSB)
#define RST_BOOTSTRAP_BOOT_SELECT_SET(x)                             (((x) << RST_BOOTSTRAP_BOOT_SELECT_LSB) & RST_BOOTSTRAP_BOOT_SELECT_MASK)
#define RST_BOOTSTRAP_BOOT_SELECT_RESET                              0x0 // 0
#define RST_BOOTSTRAP_SDRAM_DISABLE_MSB                              1
#define RST_BOOTSTRAP_SDRAM_DISABLE_LSB                              1
#define RST_BOOTSTRAP_SDRAM_DISABLE_MASK                             0x00000002
#define RST_BOOTSTRAP_SDRAM_DISABLE_GET(x)                           (((x) & RST_BOOTSTRAP_SDRAM_DISABLE_MASK) >> RST_BOOTSTRAP_SDRAM_DISABLE_LSB)
#define RST_BOOTSTRAP_SDRAM_DISABLE_SET(x)                           (((x) << RST_BOOTSTRAP_SDRAM_DISABLE_LSB) & RST_BOOTSTRAP_SDRAM_DISABLE_MASK)
#define RST_BOOTSTRAP_SDRAM_DISABLE_RESET                            0x0 // 0
#define RST_BOOTSTRAP_DDR_SELECT_MSB                                 0
#define RST_BOOTSTRAP_DDR_SELECT_LSB                                 0
#define RST_BOOTSTRAP_DDR_SELECT_MASK                                0x00000001
#define RST_BOOTSTRAP_DDR_SELECT_GET(x)                              (((x) & RST_BOOTSTRAP_DDR_SELECT_MASK) >> RST_BOOTSTRAP_DDR_SELECT_LSB)
#define RST_BOOTSTRAP_DDR_SELECT_SET(x)                              (((x) << RST_BOOTSTRAP_DDR_SELECT_LSB) & RST_BOOTSTRAP_DDR_SELECT_MASK)
#define RST_BOOTSTRAP_DDR_SELECT_RESET                               0x0 // 0
#define RST_BOOTSTRAP_ADDRESS                                        0x180600b0

#define GPIO_OE_ADDRESS                                              0x18040000
#define GPIO_OUT_ADDRESS                                             0x18040008
#define GPIO_SPARE_ADDRESS                                           0x18040028 //GPIO_IN_ETH_SWITCH_LED

#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_MSB                         31
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_LSB                         24
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_MASK                        0xff000000
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_GET(x)                      (((x) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_MASK) >> GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_LSB)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_SET(x)                      (((x) << GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_LSB) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_MASK)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_3_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_MSB                         23
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_LSB                         16
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_MASK                        0x00ff0000
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_GET(x)                      (((x) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_MASK) >> GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_LSB)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_SET(x)                      (((x) << GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_LSB) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_MASK)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_2_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_MSB                         15
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_LSB                         8
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_MASK                        0x0000ff00
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_GET(x)                      (((x) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_MASK) >> GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_LSB)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_SET(x)                      (((x) << GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_LSB) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_MASK)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_1_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_MSB                         7
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_LSB                         0
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_MASK                        0x000000ff
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_GET(x)                      (((x) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_MASK) >> GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_LSB)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_SET(x)                      (((x) << GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_LSB) & GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_MASK)
#define GPIO_OUT_FUNCTION0_ENABLE_GPIO_0_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION0_ADDRESS                                   0x1804002c

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

#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_MSB                        31
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_LSB                        24
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_MASK                       0xff000000
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_GET(x)                     (((x) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_MASK) >> GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_LSB)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_SET(x)                     (((x) << GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_LSB) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_MASK)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_11_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_MSB                        23
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_LSB                        16
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_MASK                       0x00ff0000
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_GET(x)                     (((x) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_MASK) >> GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_LSB)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_SET(x)                     (((x) << GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_LSB) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_MASK)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_MSB                         15
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_LSB                         8
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_MASK                        0x0000ff00
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_GET(x)                      (((x) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_MASK) >> GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_LSB)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_SET(x)                      (((x) << GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_LSB) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_MASK)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_9_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_MSB                         7
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_LSB                         0
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_MASK                        0x000000ff
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_GET(x)                      (((x) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_MASK) >> GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_LSB)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_SET(x)                      (((x) << GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_LSB) & GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_MASK)
#define GPIO_OUT_FUNCTION2_ENABLE_GPIO_8_RESET                       0x0 // 0
#define GPIO_OUT_FUNCTION2_ADDRESS                                   0x18040034

#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_MSB                        31
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_LSB                        24
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_MASK                       0xff000000
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_GET(x)                     (((x) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_MASK) >> GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_LSB)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_SET(x)                     (((x) << GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_LSB) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_MASK)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_15_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_MSB                        23
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_LSB                        16
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_MASK                       0x00ff0000
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_GET(x)                     (((x) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_MASK) >> GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_LSB)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_SET(x)                     (((x) << GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_LSB) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_MASK)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_14_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MSB                        15
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_LSB                        8
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MASK                       0x0000ff00
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_GET(x)                     (((x) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MASK) >> GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_LSB)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_SET(x)                     (((x) << GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_LSB) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MASK)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_MSB                        7
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_LSB                        0
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_MASK                       0x000000ff
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_GET(x)                     (((x) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_MASK) >> GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_LSB)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_SET(x)                     (((x) << GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_LSB) & GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_MASK)
#define GPIO_OUT_FUNCTION3_ENABLE_GPIO_12_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION3_ADDRESS				     0x18040038

#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MSB                        31
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_LSB                        24
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MASK                       0xff000000
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_MSB                        23
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_LSB                        16
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_MASK                       0x00ff0000
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_18_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MSB                        15
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB                        8
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK                       0x0000ff00
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MSB                        7
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB                        0
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK                       0x000000ff
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION4_ADDRESS                                   0x1804003c

#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_MSB                        31
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_LSB                        24
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_MASK                       0xff000000
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_GET(x)                     (((x) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_MASK) >> GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_LSB)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_SET(x)                     (((x) << GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_LSB) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_MASK)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_23_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MSB                        23
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_LSB                        16
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MASK                       0x00ff0000
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_GET(x)                     (((x) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MASK) >> GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_LSB)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_SET(x)                     (((x) << GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_LSB) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MASK)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_MSB                        15
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_LSB                        8
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_MASK                       0x0000ff00
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_GET(x)                     (((x) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_MASK) >> GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_LSB)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_SET(x)                     (((x) << GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_LSB) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_MASK)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_21_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_MSB                        7
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_LSB                        0
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_MASK                       0x000000ff
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_GET(x)                     (((x) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_MASK) >> GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_LSB)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_SET(x)                     (((x) << GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_LSB) & GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_MASK)
#define GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION5_ADDRESS                                   0x18040040

#define GPIO_IN_ENABLE0_UART_SIN_MSB                                 15
#define GPIO_IN_ENABLE0_UART_SIN_LSB                                 8
#define GPIO_IN_ENABLE0_UART_SIN_MASK                                0x0000ff00
#define GPIO_IN_ENABLE0_UART_SIN_GET(x)                              (((x) & GPIO_IN_ENABLE0_UART_SIN_MASK) >> GPIO_IN_ENABLE0_UART_SIN_LSB)
#define GPIO_IN_ENABLE0_UART_SIN_SET(x)                              (((x) << GPIO_IN_ENABLE0_UART_SIN_LSB) & GPIO_IN_ENABLE0_UART_SIN_MASK)
#define GPIO_IN_ENABLE0_UART_SIN_RESET                               0x0 // 0
#define GPIO_IN_ENABLE0_SPI_DATA_IN_MSB                              7
#define GPIO_IN_ENABLE0_SPI_DATA_IN_LSB                              0
#define GPIO_IN_ENABLE0_SPI_DATA_IN_MASK                             0x000000ff
#define GPIO_IN_ENABLE0_SPI_DATA_IN_GET(x)                           (((x) & GPIO_IN_ENABLE0_SPI_DATA_IN_MASK) >> GPIO_IN_ENABLE0_SPI_DATA_IN_LSB)
#define GPIO_IN_ENABLE0_SPI_DATA_IN_SET(x)                           (((x) << GPIO_IN_ENABLE0_SPI_DATA_IN_LSB) & GPIO_IN_ENABLE0_SPI_DATA_IN_MASK)
#define GPIO_IN_ENABLE0_SPI_DATA_IN_RESET                            0x8 // 8
#define GPIO_IN_ENABLE0_ADDRESS                                      0x18040044

#define GPIO_IN_ENABLE1_I2SEXT_MCLK_MSB                              31
#define GPIO_IN_ENABLE1_I2SEXT_MCLK_LSB                              24
#define GPIO_IN_ENABLE1_I2SEXT_MCLK_MASK                             0xff000000
#define GPIO_IN_ENABLE1_I2SEXT_MCLK_GET(x)                           (((x) & GPIO_IN_ENABLE1_I2SEXT_MCLK_MASK) >> GPIO_IN_ENABLE1_I2SEXT_MCLK_LSB)
#define GPIO_IN_ENABLE1_I2SEXT_MCLK_SET(x)                           (((x) << GPIO_IN_ENABLE1_I2SEXT_MCLK_LSB) & GPIO_IN_ENABLE1_I2SEXT_MCLK_MASK)
#define GPIO_IN_ENABLE1_I2SEXT_MCLK_RESET                            0x0 // 0
#define GPIO_IN_ENABLE1_I2SEXTCLK_MSB                                23
#define GPIO_IN_ENABLE1_I2SEXTCLK_LSB                                16
#define GPIO_IN_ENABLE1_I2SEXTCLK_MASK                               0x00ff0000
#define GPIO_IN_ENABLE1_I2SEXTCLK_GET(x)                             (((x) & GPIO_IN_ENABLE1_I2SEXTCLK_MASK) >> GPIO_IN_ENABLE1_I2SEXTCLK_LSB)
#define GPIO_IN_ENABLE1_I2SEXTCLK_SET(x)                             (((x) << GPIO_IN_ENABLE1_I2SEXTCLK_LSB) & GPIO_IN_ENABLE1_I2SEXTCLK_MASK)
#define GPIO_IN_ENABLE1_I2SEXTCLK_RESET                              0x0 // 0
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_MSB                             15
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_LSB                             8
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_MASK                            0x0000ff00
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_GET(x)                          (((x) & GPIO_IN_ENABLE1_I2S0__MIC_SD_MASK) >> GPIO_IN_ENABLE1_I2S0__MIC_SD_LSB)
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_SET(x)                          (((x) << GPIO_IN_ENABLE1_I2S0__MIC_SD_LSB) & GPIO_IN_ENABLE1_I2S0__MIC_SD_MASK)
#define GPIO_IN_ENABLE1_I2S0__MIC_SD_RESET                           0x0 // 0
#define GPIO_IN_ENABLE1_I2S0__WS_MSB                                 7
#define GPIO_IN_ENABLE1_I2S0__WS_LSB                                 0
#define GPIO_IN_ENABLE1_I2S0__WS_MASK                                0x000000ff
#define GPIO_IN_ENABLE1_I2S0__WS_GET(x)                              (((x) & GPIO_IN_ENABLE1_I2S0__WS_MASK) >> GPIO_IN_ENABLE1_I2S0__WS_LSB)
#define GPIO_IN_ENABLE1_I2S0__WS_SET(x)                              (((x) << GPIO_IN_ENABLE1_I2S0__WS_LSB) & GPIO_IN_ENABLE1_I2S0__WS_MASK)
#define GPIO_IN_ENABLE1_I2S0__WS_RESET                               0x0 // 0
#define GPIO_IN_ENABLE1_ADDRESS                                      0x18040048

#define GPIO_IN_ENABLE2_SLICEXT_MCLK_MSB                             31
#define GPIO_IN_ENABLE2_SLICEXT_MCLK_LSB                             24
#define GPIO_IN_ENABLE2_SLICEXT_MCLK_MASK                            0xff000000
#define GPIO_IN_ENABLE2_SLICEXT_MCLK_GET(x)                          (((x) & GPIO_IN_ENABLE2_SLICEXT_MCLK_MASK) >> GPIO_IN_ENABLE2_SLICEXT_MCLK_LSB)
#define GPIO_IN_ENABLE2_SLICEXT_MCLK_SET(x)                          (((x) << GPIO_IN_ENABLE2_SLICEXT_MCLK_LSB) & GPIO_IN_ENABLE2_SLICEXT_MCLK_MASK)
#define GPIO_IN_ENABLE2_SLICEXT_MCLK_RESET                           0x80 // 128
#define GPIO_IN_ENABLE2_ETH__RX_CRS_MSB                              23
#define GPIO_IN_ENABLE2_ETH__RX_CRS_LSB                              16
#define GPIO_IN_ENABLE2_ETH__RX_CRS_MASK                             0x00ff0000
#define GPIO_IN_ENABLE2_ETH__RX_CRS_GET(x)                           (((x) & GPIO_IN_ENABLE2_ETH__RX_CRS_MASK) >> GPIO_IN_ENABLE2_ETH__RX_CRS_LSB)
#define GPIO_IN_ENABLE2_ETH__RX_CRS_SET(x)                           (((x) << GPIO_IN_ENABLE2_ETH__RX_CRS_LSB) & GPIO_IN_ENABLE2_ETH__RX_CRS_MASK)
#define GPIO_IN_ENABLE2_ETH__RX_CRS_RESET                            0x80 // 128
#define GPIO_IN_ENABLE2_ETH__RX_COL_MSB                              15
#define GPIO_IN_ENABLE2_ETH__RX_COL_LSB                              8
#define GPIO_IN_ENABLE2_ETH__RX_COL_MASK                             0x0000ff00
#define GPIO_IN_ENABLE2_ETH__RX_COL_GET(x)                           (((x) & GPIO_IN_ENABLE2_ETH__RX_COL_MASK) >> GPIO_IN_ENABLE2_ETH__RX_COL_LSB)
#define GPIO_IN_ENABLE2_ETH__RX_COL_SET(x)                           (((x) << GPIO_IN_ENABLE2_ETH__RX_COL_LSB) & GPIO_IN_ENABLE2_ETH__RX_COL_MASK)
#define GPIO_IN_ENABLE2_ETH__RX_COL_RESET                            0x80 // 128
#define GPIO_IN_ENABLE2_ETH__RX_ERR_MSB                              7
#define GPIO_IN_ENABLE2_ETH__RX_ERR_LSB                              0
#define GPIO_IN_ENABLE2_ETH__RX_ERR_MASK                             0x000000ff
#define GPIO_IN_ENABLE2_ETH__RX_ERR_GET(x)                           (((x) & GPIO_IN_ENABLE2_ETH__RX_ERR_MASK) >> GPIO_IN_ENABLE2_ETH__RX_ERR_LSB)
#define GPIO_IN_ENABLE2_ETH__RX_ERR_SET(x)                           (((x) << GPIO_IN_ENABLE2_ETH__RX_ERR_LSB) & GPIO_IN_ENABLE2_ETH__RX_ERR_MASK)
#define GPIO_IN_ENABLE2_ETH__RX_ERR_RESET                            0x80 // 128
#define GPIO_IN_ENABLE2_ADDRESS                                      0x1804004c

#define GPIO_IN_ENABLE3_MII_GE1_MDI_MSB                              23
#define GPIO_IN_ENABLE3_MII_GE1_MDI_LSB                              16
#define GPIO_IN_ENABLE3_MII_GE1_MDI_MASK                             0x00ff0000
#define GPIO_IN_ENABLE3_MII_GE1_MDI_GET(x)                           (((x) & GPIO_IN_ENABLE3_MII_GE1_MDI_MASK) >> GPIO_IN_ENABLE3_MII_GE1_MDI_LSB)
#define GPIO_IN_ENABLE3_MII_GE1_MDI_SET(x)                           (((x) << GPIO_IN_ENABLE3_MII_GE1_MDI_LSB) & GPIO_IN_ENABLE3_MII_GE1_MDI_MASK)
#define GPIO_IN_ENABLE3_MII_GE1_MDI_RESET                            0x80 // 128
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_MSB                             15
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_LSB                             8
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_MASK                            0x0000ff00
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_GET(x)                          (((x) & GPIO_IN_ENABLE3_BOOT_EXT_MDC_MASK) >> GPIO_IN_ENABLE3_BOOT_EXT_MDC_LSB)
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_SET(x)                          (((x) << GPIO_IN_ENABLE3_BOOT_EXT_MDC_LSB) & GPIO_IN_ENABLE3_BOOT_EXT_MDC_MASK)
#define GPIO_IN_ENABLE3_BOOT_EXT_MDC_RESET                           0x80 // 128
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_MSB                             7
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_LSB                             0
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_MASK                            0x000000ff
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_GET(x)                          (((x) & GPIO_IN_ENABLE3_BOOT_EXT_MDO_MASK) >> GPIO_IN_ENABLE3_BOOT_EXT_MDO_LSB)
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_SET(x)                          (((x) << GPIO_IN_ENABLE3_BOOT_EXT_MDO_LSB) & GPIO_IN_ENABLE3_BOOT_EXT_MDO_MASK)
#define GPIO_IN_ENABLE3_BOOT_EXT_MDO_RESET                           0x80 // 128
#define GPIO_IN_ENABLE3_ADDRESS                                      0x18040050

#define GPIO_IN_ENABLE4_I2C_DATA_MSB                                 31
#define GPIO_IN_ENABLE4_I2C_DATA_LSB                                 24
#define GPIO_IN_ENABLE4_I2C_DATA_MASK                                0xff000000
#define GPIO_IN_ENABLE4_I2C_DATA_GET(x)                              (((x) & GPIO_IN_ENABLE4_I2C_DATA_MASK) >> GPIO_IN_ENABLE4_I2C_DATA_LSB)
#define GPIO_IN_ENABLE4_I2C_DATA_SET(x)                              (((x) << GPIO_IN_ENABLE4_I2C_DATA_LSB) & GPIO_IN_ENABLE4_I2C_DATA_MASK)
#define GPIO_IN_ENABLE4_I2C_DATA_RESET                               0x80 // 128
#define GPIO_IN_ENABLE4_I2C_CLK_MSB                                  23
#define GPIO_IN_ENABLE4_I2C_CLK_LSB                                  16
#define GPIO_IN_ENABLE4_I2C_CLK_MASK                                 0x00ff0000
#define GPIO_IN_ENABLE4_I2C_CLK_GET(x)                               (((x) & GPIO_IN_ENABLE4_I2C_CLK_MASK) >> GPIO_IN_ENABLE4_I2C_CLK_LSB)
#define GPIO_IN_ENABLE4_I2C_CLK_SET(x)                               (((x) << GPIO_IN_ENABLE4_I2C_CLK_LSB) & GPIO_IN_ENABLE4_I2C_CLK_MASK)
#define GPIO_IN_ENABLE4_I2C_CLK_RESET                                0x80 // 128
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_MSB                           15
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_LSB                           8
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_MASK                          0x0000ff00
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_GET(x)                        (((x) & GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_MASK) >> GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_LSB)
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_SET(x)                        (((x) << GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_LSB) & GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_MASK)
#define GPIO_IN_ENABLE4_SLIC_PCM_FS_IN_RESET                         0x80 // 128
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_MSB                             7
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_LSB                             0
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_MASK                            0x000000ff
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_GET(x)                          (((x) & GPIO_IN_ENABLE4_SLIC_DATA_IN_MASK) >> GPIO_IN_ENABLE4_SLIC_DATA_IN_LSB)
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_SET(x)                          (((x) << GPIO_IN_ENABLE4_SLIC_DATA_IN_LSB) & GPIO_IN_ENABLE4_SLIC_DATA_IN_MASK)
#define GPIO_IN_ENABLE4_SLIC_DATA_IN_RESET                           0x80 // 128
#define GPIO_IN_ENABLE4_ADDRESS                                      0x18040054

#define GPIO_IN_ENABLE5_ADDRESS                                      0x18040058

#define GPIO_IN_ENABLE6_ADDRESS                                      0x1804005c

#define GPIO_IN_ENABLE7_ADDRESS                                      0x18040060

#define GPIO_IN_ENABLE8_ADDRESS                                      0x18040064

#define GPIO_IN_ENABLE9_UART1_CTS_MSB                                31
#define GPIO_IN_ENABLE9_UART1_CTS_LSB                                24
#define GPIO_IN_ENABLE9_UART1_CTS_MASK                               0xff000000
#define GPIO_IN_ENABLE9_UART1_CTS_GET(x)                             (((x) & GPIO_IN_ENABLE9_UART1_CTS_MASK) >> GPIO_IN_ENABLE9_UART1_CTS_LSB)
#define GPIO_IN_ENABLE9_UART1_CTS_SET(x)                             (((x) << GPIO_IN_ENABLE9_UART1_CTS_LSB) & GPIO_IN_ENABLE9_UART1_CTS_MASK)
#define GPIO_IN_ENABLE9_UART1_CTS_RESET                              0x80 // 128
#define GPIO_IN_ENABLE9_UART1_RD_MSB                                 23
#define GPIO_IN_ENABLE9_UART1_RD_LSB                                 16
#define GPIO_IN_ENABLE9_UART1_RD_MASK                                0x00ff0000
#define GPIO_IN_ENABLE9_UART1_RD_GET(x)                              (((x) & GPIO_IN_ENABLE9_UART1_RD_MASK) >> GPIO_IN_ENABLE9_UART1_RD_LSB)
#define GPIO_IN_ENABLE9_UART1_RD_SET(x)                              (((x) << GPIO_IN_ENABLE9_UART1_RD_LSB) & GPIO_IN_ENABLE9_UART1_RD_MASK)
#define GPIO_IN_ENABLE9_UART1_RD_RESET                               0x80 // 128
#define GPIO_IN_ENABLE9_UART1_RTS_MSB                                15
#define GPIO_IN_ENABLE9_UART1_RTS_LSB                                8
#define GPIO_IN_ENABLE9_UART1_RTS_MASK                               0x0000ff00
#define GPIO_IN_ENABLE9_UART1_RTS_GET(x)                             (((x) & GPIO_IN_ENABLE9_UART1_RTS_MASK) >> GPIO_IN_ENABLE9_UART1_RTS_LSB)
#define GPIO_IN_ENABLE9_UART1_RTS_SET(x)                             (((x) << GPIO_IN_ENABLE9_UART1_RTS_LSB) & GPIO_IN_ENABLE9_UART1_RTS_MASK)
#define GPIO_IN_ENABLE9_UART1_RTS_RESET                              0x80 // 128
#define GPIO_IN_ENABLE9_UART1_TD_MSB                                 7
#define GPIO_IN_ENABLE9_UART1_TD_LSB                                 0
#define GPIO_IN_ENABLE9_UART1_TD_MASK                                0x000000ff
#define GPIO_IN_ENABLE9_UART1_TD_GET(x)                              (((x) & GPIO_IN_ENABLE9_UART1_TD_MASK) >> GPIO_IN_ENABLE9_UART1_TD_LSB)
#define GPIO_IN_ENABLE9_UART1_TD_SET(x)                              (((x) << GPIO_IN_ENABLE9_UART1_TD_LSB) & GPIO_IN_ENABLE9_UART1_TD_MASK)
#define GPIO_IN_ENABLE9_UART1_TD_RESET                               0x80 // 128
#define GPIO_IN_ENABLE9_ADDRESS                                      0x18040068

#define GPIO_FUNCTION_CLK_OBS9_ENABLE_MSB                            11
#define GPIO_FUNCTION_CLK_OBS9_ENABLE_LSB                            11
#define GPIO_FUNCTION_CLK_OBS9_ENABLE_MASK                           0x00000800
#define GPIO_FUNCTION_CLK_OBS9_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS9_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS9_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS9_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS9_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS9_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS9_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_MSB                            10
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_LSB                            10
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_MASK                           0x00000400
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS8_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS8_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS8_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS8_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS8_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_MSB                            9
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_LSB                            9
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_MASK                           0x00000200
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS7_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS7_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS7_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS7_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS7_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_MSB                            8
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_LSB                            8
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_MASK                           0x00000100
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS6_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS6_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS6_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS6_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS6_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_MSB                            7
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_LSB                            7
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_MASK                           0x00000080
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS5_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS5_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS5_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS5_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_RESET                          0x1 // 1
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_MSB                            6
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_LSB                            6
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_MASK                           0x00000040
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS4_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS4_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS4_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS4_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS4_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_MSB                            5
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_LSB                            5
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_MASK                           0x00000020
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS3_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS3_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS3_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS3_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_MSB                            4
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_LSB                            4
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_MASK                           0x00000010
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS2_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS2_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS2_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS2_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS2_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_MSB                            3
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_LSB                            3
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_MASK                           0x00000008
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS1_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS1_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS1_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS1_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS1_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_MSB                            2
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_LSB                            2
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_MASK                           0x00000004
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_GET(x)                         (((x) & GPIO_FUNCTION_CLK_OBS0_ENABLE_MASK) >> GPIO_FUNCTION_CLK_OBS0_ENABLE_LSB)
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_SET(x)                         (((x) << GPIO_FUNCTION_CLK_OBS0_ENABLE_LSB) & GPIO_FUNCTION_CLK_OBS0_ENABLE_MASK)
#define GPIO_FUNCTION_CLK_OBS0_ENABLE_RESET                          0x0 // 0
#define GPIO_FUNCTION_DISABLE_JTAG_MSB                               1
#define GPIO_FUNCTION_DISABLE_JTAG_LSB                               1
#define GPIO_FUNCTION_DISABLE_JTAG_MASK                              0x00000002
#define GPIO_FUNCTION_DISABLE_JTAG_GET(x)                            (((x) & GPIO_FUNCTION_DISABLE_JTAG_MASK) >> GPIO_FUNCTION_DISABLE_JTAG_LSB)
#define GPIO_FUNCTION_DISABLE_JTAG_SET(x)                            (((x) << GPIO_FUNCTION_DISABLE_JTAG_LSB) & GPIO_FUNCTION_DISABLE_JTAG_MASK)
#define GPIO_FUNCTION_DISABLE_JTAG_RESET                             0x0 // 0
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_MSB                           0
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_LSB                           0
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_MASK                          0x00000001
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_GET(x)                        (((x) & GPIO_FUNCTION_ENABLE_GPIO_SRIF_MASK) >> GPIO_FUNCTION_ENABLE_GPIO_SRIF_LSB)
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_SET(x)                        (((x) << GPIO_FUNCTION_ENABLE_GPIO_SRIF_LSB) & GPIO_FUNCTION_ENABLE_GPIO_SRIF_MASK)
#define GPIO_FUNCTION_ENABLE_GPIO_SRIF_RESET                         0x0 // 0
#define GPIO_FUNCTION_ADDRESS                                        0x1804006c



#define PCIE_RESET_EP_RESET_L_MSB                                    2
#define PCIE_RESET_EP_RESET_L_LSB                                    2
#define PCIE_RESET_EP_RESET_L_MASK                                   0x00000004
#define PCIE_RESET_EP_RESET_L_GET(x)                                 (((x) & PCIE_RESET_EP_RESET_L_MASK) >> PCIE_RESET_EP_RESET_L_LSB)
#define PCIE_RESET_EP_RESET_L_SET(x)                                 (((x) << PCIE_RESET_EP_RESET_L_LSB) & PCIE_RESET_EP_RESET_L_MASK)
#define PCIE_RESET_EP_RESET_L_RESET                                  0x0 // 0
#define PCIE_RESET_LINK_REQ_RESET_MSB                                1
#define PCIE_RESET_LINK_REQ_RESET_LSB                                1
#define PCIE_RESET_LINK_REQ_RESET_MASK                               0x00000002
#define PCIE_RESET_LINK_REQ_RESET_GET(x)                             (((x) & PCIE_RESET_LINK_REQ_RESET_MASK) >> PCIE_RESET_LINK_REQ_RESET_LSB)
#define PCIE_RESET_LINK_REQ_RESET_SET(x)                             (((x) << PCIE_RESET_LINK_REQ_RESET_LSB) & PCIE_RESET_LINK_REQ_RESET_MASK)
#define PCIE_RESET_LINK_REQ_RESET_RESET                              0x0 // 0
#define PCIE_RESET_LINK_UP_MSB                                       0
#define PCIE_RESET_LINK_UP_LSB                                       0
#define PCIE_RESET_LINK_UP_MASK                                      0x00000001
#define PCIE_RESET_LINK_UP_GET(x)                                    (((x) & PCIE_RESET_LINK_UP_MASK) >> PCIE_RESET_LINK_UP_LSB)
#define PCIE_RESET_LINK_UP_SET(x)                                    (((x) << PCIE_RESET_LINK_UP_LSB) & PCIE_RESET_LINK_UP_MASK)
#define PCIE_RESET_LINK_UP_RESET                                     0x0 // 0
#define PCIE_RESET_ADDRESS                                           0x180f0018

#define PCIE_RESET_ADDRESS_2                                         0x18280018

#define PCIE_APP_CFG_TYPE_MSB                                        21
#define PCIE_APP_CFG_TYPE_LSB                                        20
#define PCIE_APP_CFG_TYPE_MASK                                       0x00300000
#define PCIE_APP_CFG_TYPE_GET(x)                                     (((x) & PCIE_APP_CFG_TYPE_MASK) >> PCIE_APP_CFG_TYPE_LSB)
#define PCIE_APP_CFG_TYPE_SET(x)                                     (((x) << PCIE_APP_CFG_TYPE_LSB) & PCIE_APP_CFG_TYPE_MASK)
#define PCIE_APP_CFG_TYPE_RESET                                      0x0 // 0
#define PCIE_APP_PCIE_BAR_MSN_MSB                                    19
#define PCIE_APP_PCIE_BAR_MSN_LSB                                    16
#define PCIE_APP_PCIE_BAR_MSN_MASK                                   0x000f0000
#define PCIE_APP_PCIE_BAR_MSN_GET(x)                                 (((x) & PCIE_APP_PCIE_BAR_MSN_MASK) >> PCIE_APP_PCIE_BAR_MSN_LSB)
#define PCIE_APP_PCIE_BAR_MSN_SET(x)                                 (((x) << PCIE_APP_PCIE_BAR_MSN_LSB) & PCIE_APP_PCIE_BAR_MSN_MASK)
#define PCIE_APP_PCIE_BAR_MSN_RESET                                  0x1 // 1
#define PCIE_APP_CFG_BE_MSB                                          15
#define PCIE_APP_CFG_BE_LSB                                          12
#define PCIE_APP_CFG_BE_MASK                                         0x0000f000
#define PCIE_APP_CFG_BE_GET(x)                                       (((x) & PCIE_APP_CFG_BE_MASK) >> PCIE_APP_CFG_BE_LSB)
#define PCIE_APP_CFG_BE_SET(x)                                       (((x) << PCIE_APP_CFG_BE_LSB) & PCIE_APP_CFG_BE_MASK)
#define PCIE_APP_CFG_BE_RESET                                        0xf // 15
#define PCIE_APP_SLV_RESP_ERR_MAP_MSB                                11
#define PCIE_APP_SLV_RESP_ERR_MAP_LSB                                6
#define PCIE_APP_SLV_RESP_ERR_MAP_MASK                               0x00000fc0
#define PCIE_APP_SLV_RESP_ERR_MAP_GET(x)                             (((x) & PCIE_APP_SLV_RESP_ERR_MAP_MASK) >> PCIE_APP_SLV_RESP_ERR_MAP_LSB)
#define PCIE_APP_SLV_RESP_ERR_MAP_SET(x)                             (((x) << PCIE_APP_SLV_RESP_ERR_MAP_LSB) & PCIE_APP_SLV_RESP_ERR_MAP_MASK)
#define PCIE_APP_SLV_RESP_ERR_MAP_RESET                              0x3f // 63
#define PCIE_APP_MSTR_RESP_ERR_MAP_MSB                               5
#define PCIE_APP_MSTR_RESP_ERR_MAP_LSB                               4
#define PCIE_APP_MSTR_RESP_ERR_MAP_MASK                              0x00000030
#define PCIE_APP_MSTR_RESP_ERR_MAP_GET(x)                            (((x) & PCIE_APP_MSTR_RESP_ERR_MAP_MASK) >> PCIE_APP_MSTR_RESP_ERR_MAP_LSB)
#define PCIE_APP_MSTR_RESP_ERR_MAP_SET(x)                            (((x) << PCIE_APP_MSTR_RESP_ERR_MAP_LSB) & PCIE_APP_MSTR_RESP_ERR_MAP_MASK)
#define PCIE_APP_MSTR_RESP_ERR_MAP_RESET                             0x0 // 0
#define PCIE_APP_INIT_RST_MSB                                        3
#define PCIE_APP_INIT_RST_LSB                                        3
#define PCIE_APP_INIT_RST_MASK                                       0x00000008
#define PCIE_APP_INIT_RST_GET(x)                                     (((x) & PCIE_APP_INIT_RST_MASK) >> PCIE_APP_INIT_RST_LSB)
#define PCIE_APP_INIT_RST_SET(x)                                     (((x) << PCIE_APP_INIT_RST_LSB) & PCIE_APP_INIT_RST_MASK)
#define PCIE_APP_INIT_RST_RESET                                      0x0 // 0
#define PCIE_APP_PM_XMT_TURNOFF_MSB                                  2
#define PCIE_APP_PM_XMT_TURNOFF_LSB                                  2
#define PCIE_APP_PM_XMT_TURNOFF_MASK                                 0x00000004
#define PCIE_APP_PM_XMT_TURNOFF_GET(x)                               (((x) & PCIE_APP_PM_XMT_TURNOFF_MASK) >> PCIE_APP_PM_XMT_TURNOFF_LSB)
#define PCIE_APP_PM_XMT_TURNOFF_SET(x)                               (((x) << PCIE_APP_PM_XMT_TURNOFF_LSB) & PCIE_APP_PM_XMT_TURNOFF_MASK)
#define PCIE_APP_PM_XMT_TURNOFF_RESET                                0x0 // 0
#define PCIE_APP_UNLOCK_MSG_MSB                                      1
#define PCIE_APP_UNLOCK_MSG_LSB                                      1
#define PCIE_APP_UNLOCK_MSG_MASK                                     0x00000002
#define PCIE_APP_UNLOCK_MSG_GET(x)                                   (((x) & PCIE_APP_UNLOCK_MSG_MASK) >> PCIE_APP_UNLOCK_MSG_LSB)
#define PCIE_APP_UNLOCK_MSG_SET(x)                                   (((x) << PCIE_APP_UNLOCK_MSG_LSB) & PCIE_APP_UNLOCK_MSG_MASK)
#define PCIE_APP_UNLOCK_MSG_RESET                                    0x0 // 0
#define PCIE_APP_LTSSM_ENABLE_MSB                                    0
#define PCIE_APP_LTSSM_ENABLE_LSB                                    0
#define PCIE_APP_LTSSM_ENABLE_MASK                                   0x00000001
#define PCIE_APP_LTSSM_ENABLE_GET(x)                                 (((x) & PCIE_APP_LTSSM_ENABLE_MASK) >> PCIE_APP_LTSSM_ENABLE_LSB)
#define PCIE_APP_LTSSM_ENABLE_SET(x)                                 (((x) << PCIE_APP_LTSSM_ENABLE_LSB) & PCIE_APP_LTSSM_ENABLE_MASK)
#define PCIE_APP_LTSSM_ENABLE_RESET                                  0x0 // 0
#define PCIE_APP_ADDRESS                                             0x180f0000

#define PCIE_APP_ADDRESS_2                                           0x18280000

#define PCIE_INT_STATUS_LINK_DOWN_MSB                                27
#define PCIE_INT_STATUS_LINK_DOWN_LSB                                27
#define PCIE_INT_STATUS_LINK_DOWN_MASK                               0x08000000
#define PCIE_INT_STATUS_LINK_DOWN_GET(x)                             (((x) & PCIE_INT_STATUS_LINK_DOWN_MASK) >> PCIE_INT_STATUS_LINK_DOWN_LSB)
#define PCIE_INT_STATUS_LINK_DOWN_SET(x)                             (((x) << PCIE_INT_STATUS_LINK_DOWN_LSB) & PCIE_INT_STATUS_LINK_DOWN_MASK)
#define PCIE_INT_STATUS_LINK_DOWN_RESET                              0x0 // 0
#define PCIE_INT_STATUS_LINK_REQ_RST_MSB                             26
#define PCIE_INT_STATUS_LINK_REQ_RST_LSB                             26
#define PCIE_INT_STATUS_LINK_REQ_RST_MASK                            0x04000000
#define PCIE_INT_STATUS_LINK_REQ_RST_GET(x)                          (((x) & PCIE_INT_STATUS_LINK_REQ_RST_MASK) >> PCIE_INT_STATUS_LINK_REQ_RST_LSB)
#define PCIE_INT_STATUS_LINK_REQ_RST_SET(x)                          (((x) << PCIE_INT_STATUS_LINK_REQ_RST_LSB) & PCIE_INT_STATUS_LINK_REQ_RST_MASK)
#define PCIE_INT_STATUS_LINK_REQ_RST_RESET                           0x0 // 0
#define PCIE_INT_STATUS_MSI_VEC_MSB                                  25
#define PCIE_INT_STATUS_MSI_VEC_LSB                                  22
#define PCIE_INT_STATUS_MSI_VEC_MASK                                 0x03c00000
#define PCIE_INT_STATUS_MSI_VEC_GET(x)                               (((x) & PCIE_INT_STATUS_MSI_VEC_MASK) >> PCIE_INT_STATUS_MSI_VEC_LSB)
#define PCIE_INT_STATUS_MSI_VEC_SET(x)                               (((x) << PCIE_INT_STATUS_MSI_VEC_LSB) & PCIE_INT_STATUS_MSI_VEC_MASK)
#define PCIE_INT_STATUS_MSI_VEC_RESET                                0x0 // 0
#define PCIE_INT_STATUS_CPU_INTD_MSB                                 21
#define PCIE_INT_STATUS_CPU_INTD_LSB                                 21
#define PCIE_INT_STATUS_CPU_INTD_MASK                                0x00200000
#define PCIE_INT_STATUS_CPU_INTD_GET(x)                              (((x) & PCIE_INT_STATUS_CPU_INTD_MASK) >> PCIE_INT_STATUS_CPU_INTD_LSB)
#define PCIE_INT_STATUS_CPU_INTD_SET(x)                              (((x) << PCIE_INT_STATUS_CPU_INTD_LSB) & PCIE_INT_STATUS_CPU_INTD_MASK)
#define PCIE_INT_STATUS_CPU_INTD_RESET                               0x0 // 0
#define PCIE_INT_STATUS_CPU_INTC_MSB                                 20
#define PCIE_INT_STATUS_CPU_INTC_LSB                                 20
#define PCIE_INT_STATUS_CPU_INTC_MASK                                0x00100000
#define PCIE_INT_STATUS_CPU_INTC_GET(x)                              (((x) & PCIE_INT_STATUS_CPU_INTC_MASK) >> PCIE_INT_STATUS_CPU_INTC_LSB)
#define PCIE_INT_STATUS_CPU_INTC_SET(x)                              (((x) << PCIE_INT_STATUS_CPU_INTC_LSB) & PCIE_INT_STATUS_CPU_INTC_MASK)
#define PCIE_INT_STATUS_CPU_INTC_RESET                               0x0 // 0
#define PCIE_INT_STATUS_CPU_INTB_MSB                                 19
#define PCIE_INT_STATUS_CPU_INTB_LSB                                 19
#define PCIE_INT_STATUS_CPU_INTB_MASK                                0x00080000
#define PCIE_INT_STATUS_CPU_INTB_GET(x)                              (((x) & PCIE_INT_STATUS_CPU_INTB_MASK) >> PCIE_INT_STATUS_CPU_INTB_LSB)
#define PCIE_INT_STATUS_CPU_INTB_SET(x)                              (((x) << PCIE_INT_STATUS_CPU_INTB_LSB) & PCIE_INT_STATUS_CPU_INTB_MASK)
#define PCIE_INT_STATUS_CPU_INTB_RESET                               0x0 // 0
#define PCIE_INT_STATUS_CPU_INTA_MSB                                 18
#define PCIE_INT_STATUS_CPU_INTA_LSB                                 18
#define PCIE_INT_STATUS_CPU_INTA_MASK                                0x00040000
#define PCIE_INT_STATUS_CPU_INTA_GET(x)                              (((x) & PCIE_INT_STATUS_CPU_INTA_MASK) >> PCIE_INT_STATUS_CPU_INTA_LSB)
#define PCIE_INT_STATUS_CPU_INTA_SET(x)                              (((x) << PCIE_INT_STATUS_CPU_INTA_LSB) & PCIE_INT_STATUS_CPU_INTA_MASK)
#define PCIE_INT_STATUS_CPU_INTA_RESET                               0x0 // 0
#define PCIE_INT_STATUS_INTDL_MSB                                    17
#define PCIE_INT_STATUS_INTDL_LSB                                    17
#define PCIE_INT_STATUS_INTDL_MASK                                   0x00020000
#define PCIE_INT_STATUS_INTDL_GET(x)                                 (((x) & PCIE_INT_STATUS_INTDL_MASK) >> PCIE_INT_STATUS_INTDL_LSB)
#define PCIE_INT_STATUS_INTDL_SET(x)                                 (((x) << PCIE_INT_STATUS_INTDL_LSB) & PCIE_INT_STATUS_INTDL_MASK)
#define PCIE_INT_STATUS_INTDL_RESET                                  0x0 // 0
#define PCIE_INT_STATUS_INTCL_MSB                                    16
#define PCIE_INT_STATUS_INTCL_LSB                                    16
#define PCIE_INT_STATUS_INTCL_MASK                                   0x00010000
#define PCIE_INT_STATUS_INTCL_GET(x)                                 (((x) & PCIE_INT_STATUS_INTCL_MASK) >> PCIE_INT_STATUS_INTCL_LSB)
#define PCIE_INT_STATUS_INTCL_SET(x)                                 (((x) << PCIE_INT_STATUS_INTCL_LSB) & PCIE_INT_STATUS_INTCL_MASK)
#define PCIE_INT_STATUS_INTCL_RESET                                  0x0 // 0
#define PCIE_INT_STATUS_INTBL_MSB                                    15
#define PCIE_INT_STATUS_INTBL_LSB                                    15
#define PCIE_INT_STATUS_INTBL_MASK                                   0x00008000
#define PCIE_INT_STATUS_INTBL_GET(x)                                 (((x) & PCIE_INT_STATUS_INTBL_MASK) >> PCIE_INT_STATUS_INTBL_LSB)
#define PCIE_INT_STATUS_INTBL_SET(x)                                 (((x) << PCIE_INT_STATUS_INTBL_LSB) & PCIE_INT_STATUS_INTBL_MASK)
#define PCIE_INT_STATUS_INTBL_RESET                                  0x0 // 0
#define PCIE_INT_STATUS_INTAL_MSB                                    14
#define PCIE_INT_STATUS_INTAL_LSB                                    14
#define PCIE_INT_STATUS_INTAL_MASK                                   0x00004000
#define PCIE_INT_STATUS_INTAL_GET(x)                                 (((x) & PCIE_INT_STATUS_INTAL_MASK) >> PCIE_INT_STATUS_INTAL_LSB)
#define PCIE_INT_STATUS_INTAL_SET(x)                                 (((x) << PCIE_INT_STATUS_INTAL_LSB) & PCIE_INT_STATUS_INTAL_MASK)
#define PCIE_INT_STATUS_INTAL_RESET                                  0x0 // 0
#define PCIE_INT_STATUS_SYS_ERR_MSB                                  13
#define PCIE_INT_STATUS_SYS_ERR_LSB                                  13
#define PCIE_INT_STATUS_SYS_ERR_MASK                                 0x00002000
#define PCIE_INT_STATUS_SYS_ERR_GET(x)                               (((x) & PCIE_INT_STATUS_SYS_ERR_MASK) >> PCIE_INT_STATUS_SYS_ERR_LSB)
#define PCIE_INT_STATUS_SYS_ERR_SET(x)                               (((x) << PCIE_INT_STATUS_SYS_ERR_LSB) & PCIE_INT_STATUS_SYS_ERR_MASK)
#define PCIE_INT_STATUS_SYS_ERR_RESET                                0x0 // 0
#define PCIE_INT_STATUS_AER_MSI_MSB                                  12
#define PCIE_INT_STATUS_AER_MSI_LSB                                  12
#define PCIE_INT_STATUS_AER_MSI_MASK                                 0x00001000
#define PCIE_INT_STATUS_AER_MSI_GET(x)                               (((x) & PCIE_INT_STATUS_AER_MSI_MASK) >> PCIE_INT_STATUS_AER_MSI_LSB)
#define PCIE_INT_STATUS_AER_MSI_SET(x)                               (((x) << PCIE_INT_STATUS_AER_MSI_LSB) & PCIE_INT_STATUS_AER_MSI_MASK)
#define PCIE_INT_STATUS_AER_MSI_RESET                                0x0 // 0
#define PCIE_INT_STATUS_AER_INT_MSB                                  11
#define PCIE_INT_STATUS_AER_INT_LSB                                  11
#define PCIE_INT_STATUS_AER_INT_MASK                                 0x00000800
#define PCIE_INT_STATUS_AER_INT_GET(x)                               (((x) & PCIE_INT_STATUS_AER_INT_MASK) >> PCIE_INT_STATUS_AER_INT_LSB)
#define PCIE_INT_STATUS_AER_INT_SET(x)                               (((x) << PCIE_INT_STATUS_AER_INT_LSB) & PCIE_INT_STATUS_AER_INT_MASK)
#define PCIE_INT_STATUS_AER_INT_RESET                                0x0 // 0
#define PCIE_INT_STATUS_MSI_ERR_MSB                                  10
#define PCIE_INT_STATUS_MSI_ERR_LSB                                  10
#define PCIE_INT_STATUS_MSI_ERR_MASK                                 0x00000400
#define PCIE_INT_STATUS_MSI_ERR_GET(x)                               (((x) & PCIE_INT_STATUS_MSI_ERR_MASK) >> PCIE_INT_STATUS_MSI_ERR_LSB)
#define PCIE_INT_STATUS_MSI_ERR_SET(x)                               (((x) << PCIE_INT_STATUS_MSI_ERR_LSB) & PCIE_INT_STATUS_MSI_ERR_MASK)
#define PCIE_INT_STATUS_MSI_ERR_RESET                                0x0 // 0
#define PCIE_INT_STATUS_MSI_MSB                                      9
#define PCIE_INT_STATUS_MSI_LSB                                      9
#define PCIE_INT_STATUS_MSI_MASK                                     0x00000200
#define PCIE_INT_STATUS_MSI_GET(x)                                   (((x) & PCIE_INT_STATUS_MSI_MASK) >> PCIE_INT_STATUS_MSI_LSB)
#define PCIE_INT_STATUS_MSI_SET(x)                                   (((x) << PCIE_INT_STATUS_MSI_LSB) & PCIE_INT_STATUS_MSI_MASK)
#define PCIE_INT_STATUS_MSI_RESET                                    0x0 // 0
#define PCIE_INT_STATUS_INTD_MSB                                     8
#define PCIE_INT_STATUS_INTD_LSB                                     8
#define PCIE_INT_STATUS_INTD_MASK                                    0x00000100
#define PCIE_INT_STATUS_INTD_GET(x)                                  (((x) & PCIE_INT_STATUS_INTD_MASK) >> PCIE_INT_STATUS_INTD_LSB)
#define PCIE_INT_STATUS_INTD_SET(x)                                  (((x) << PCIE_INT_STATUS_INTD_LSB) & PCIE_INT_STATUS_INTD_MASK)
#define PCIE_INT_STATUS_INTD_RESET                                   0x0 // 0
#define PCIE_INT_STATUS_INTC_MSB                                     7
#define PCIE_INT_STATUS_INTC_LSB                                     7
#define PCIE_INT_STATUS_INTC_MASK                                    0x00000080
#define PCIE_INT_STATUS_INTC_GET(x)                                  (((x) & PCIE_INT_STATUS_INTC_MASK) >> PCIE_INT_STATUS_INTC_LSB)
#define PCIE_INT_STATUS_INTC_SET(x)                                  (((x) << PCIE_INT_STATUS_INTC_LSB) & PCIE_INT_STATUS_INTC_MASK)
#define PCIE_INT_STATUS_INTC_RESET                                   0x0 // 0
#define PCIE_INT_STATUS_INTB_MSB                                     6
#define PCIE_INT_STATUS_INTB_LSB                                     6
#define PCIE_INT_STATUS_INTB_MASK                                    0x00000040
#define PCIE_INT_STATUS_INTB_GET(x)                                  (((x) & PCIE_INT_STATUS_INTB_MASK) >> PCIE_INT_STATUS_INTB_LSB)
#define PCIE_INT_STATUS_INTB_SET(x)                                  (((x) << PCIE_INT_STATUS_INTB_LSB) & PCIE_INT_STATUS_INTB_MASK)
#define PCIE_INT_STATUS_INTB_RESET                                   0x0 // 0
#define PCIE_INT_STATUS_INTA_MSB                                     5
#define PCIE_INT_STATUS_INTA_LSB                                     5
#define PCIE_INT_STATUS_INTA_MASK                                    0x00000020
#define PCIE_INT_STATUS_INTA_GET(x)                                  (((x) & PCIE_INT_STATUS_INTA_MASK) >> PCIE_INT_STATUS_INTA_LSB)
#define PCIE_INT_STATUS_INTA_SET(x)                                  (((x) << PCIE_INT_STATUS_INTA_LSB) & PCIE_INT_STATUS_INTA_MASK)
#define PCIE_INT_STATUS_INTA_RESET                                   0x0 // 0
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_MSB                    4
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_LSB                    4
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_MASK                   0x00000010
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_GET(x)                 (((x) & PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_MASK) >> PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_LSB)
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_SET(x)                 (((x) << PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_LSB) & PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_MASK)
#define PCIE_INT_STATUS_RADMX_COMP_LOOKUP_ERR_RESET                  0x0 // 0
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_MSB                       3
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_LSB                       3
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_MASK                      0x00000008
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_GET(x)                    (((x) & PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_MASK) >> PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_LSB)
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_SET(x)                    (((x) << PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_LSB) & PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_MASK)
#define PCIE_INT_STATUS_GM_COMP_LOOKUP_ERR_RESET                     0x0 // 0
#define PCIE_INT_STATUS_FATAL_ERR_MSB                                2
#define PCIE_INT_STATUS_FATAL_ERR_LSB                                2
#define PCIE_INT_STATUS_FATAL_ERR_MASK                               0x00000004
#define PCIE_INT_STATUS_FATAL_ERR_GET(x)                             (((x) & PCIE_INT_STATUS_FATAL_ERR_MASK) >> PCIE_INT_STATUS_FATAL_ERR_LSB)
#define PCIE_INT_STATUS_FATAL_ERR_SET(x)                             (((x) << PCIE_INT_STATUS_FATAL_ERR_LSB) & PCIE_INT_STATUS_FATAL_ERR_MASK)
#define PCIE_INT_STATUS_FATAL_ERR_RESET                              0x0 // 0
#define PCIE_INT_STATUS_NONFATAL_ERR_MSB                             1
#define PCIE_INT_STATUS_NONFATAL_ERR_LSB                             1
#define PCIE_INT_STATUS_NONFATAL_ERR_MASK                            0x00000002
#define PCIE_INT_STATUS_NONFATAL_ERR_GET(x)                          (((x) & PCIE_INT_STATUS_NONFATAL_ERR_MASK) >> PCIE_INT_STATUS_NONFATAL_ERR_LSB)
#define PCIE_INT_STATUS_NONFATAL_ERR_SET(x)                          (((x) << PCIE_INT_STATUS_NONFATAL_ERR_LSB) & PCIE_INT_STATUS_NONFATAL_ERR_MASK)
#define PCIE_INT_STATUS_NONFATAL_ERR_RESET                           0x0 // 0
#define PCIE_INT_STATUS_CORR_ERR_MSB                                 0
#define PCIE_INT_STATUS_CORR_ERR_LSB                                 0
#define PCIE_INT_STATUS_CORR_ERR_MASK                                0x00000001
#define PCIE_INT_STATUS_CORR_ERR_GET(x)                              (((x) & PCIE_INT_STATUS_CORR_ERR_MASK) >> PCIE_INT_STATUS_CORR_ERR_LSB)
#define PCIE_INT_STATUS_CORR_ERR_SET(x)                              (((x) << PCIE_INT_STATUS_CORR_ERR_LSB) & PCIE_INT_STATUS_CORR_ERR_MASK)
#define PCIE_INT_STATUS_CORR_ERR_RESET                               0x0 // 0

#define PCIE_INT_MASK_LINK_DOWN_MSB                                  27
#define PCIE_INT_MASK_LINK_DOWN_LSB                                  27
#define PCIE_INT_MASK_LINK_DOWN_MASK                                 0x08000000
#define PCIE_INT_MASK_LINK_DOWN_GET(x)                               (((x) & PCIE_INT_MASK_LINK_DOWN_MASK) >> PCIE_INT_MASK_LINK_DOWN_LSB)
#define PCIE_INT_MASK_LINK_DOWN_SET(x)                               (((x) << PCIE_INT_MASK_LINK_DOWN_LSB) & PCIE_INT_MASK_LINK_DOWN_MASK)
#define PCIE_INT_MASK_LINK_DOWN_RESET                                0x0 // 0
#define PCIE_INT_MASK_LINK_REQ_RST_MSB                               26
#define PCIE_INT_MASK_LINK_REQ_RST_LSB                               26
#define PCIE_INT_MASK_LINK_REQ_RST_MASK                              0x04000000
#define PCIE_INT_MASK_LINK_REQ_RST_GET(x)                            (((x) & PCIE_INT_MASK_LINK_REQ_RST_MASK) >> PCIE_INT_MASK_LINK_REQ_RST_LSB)
#define PCIE_INT_MASK_LINK_REQ_RST_SET(x)                            (((x) << PCIE_INT_MASK_LINK_REQ_RST_LSB) & PCIE_INT_MASK_LINK_REQ_RST_MASK)
#define PCIE_INT_MASK_LINK_REQ_RST_RESET                             0x0 // 0
#define PCIE_INT_MASK_INTDL_MSB                                      17
#define PCIE_INT_MASK_INTDL_LSB                                      17
#define PCIE_INT_MASK_INTDL_MASK                                     0x00020000
#define PCIE_INT_MASK_INTDL_GET(x)                                   (((x) & PCIE_INT_MASK_INTDL_MASK) >> PCIE_INT_MASK_INTDL_LSB)
#define PCIE_INT_MASK_INTDL_SET(x)                                   (((x) << PCIE_INT_MASK_INTDL_LSB) & PCIE_INT_MASK_INTDL_MASK)
#define PCIE_INT_MASK_INTDL_RESET                                    0x0 // 0
#define PCIE_INT_MASK_INTCL_MSB                                      16
#define PCIE_INT_MASK_INTCL_LSB                                      16
#define PCIE_INT_MASK_INTCL_MASK                                     0x00010000
#define PCIE_INT_MASK_INTCL_GET(x)                                   (((x) & PCIE_INT_MASK_INTCL_MASK) >> PCIE_INT_MASK_INTCL_LSB)
#define PCIE_INT_MASK_INTCL_SET(x)                                   (((x) << PCIE_INT_MASK_INTCL_LSB) & PCIE_INT_MASK_INTCL_MASK)
#define PCIE_INT_MASK_INTCL_RESET                                    0x0 // 0
#define PCIE_INT_MASK_INTBL_MSB                                      15
#define PCIE_INT_MASK_INTBL_LSB                                      15
#define PCIE_INT_MASK_INTBL_MASK                                     0x00008000
#define PCIE_INT_MASK_INTBL_GET(x)                                   (((x) & PCIE_INT_MASK_INTBL_MASK) >> PCIE_INT_MASK_INTBL_LSB)
#define PCIE_INT_MASK_INTBL_SET(x)                                   (((x) << PCIE_INT_MASK_INTBL_LSB) & PCIE_INT_MASK_INTBL_MASK)
#define PCIE_INT_MASK_INTBL_RESET                                    0x0 // 0
#define PCIE_INT_MASK_INTAL_MSB                                      14
#define PCIE_INT_MASK_INTAL_LSB                                      14
#define PCIE_INT_MASK_INTAL_MASK                                     0x00004000
#define PCIE_INT_MASK_INTAL_GET(x)                                   (((x) & PCIE_INT_MASK_INTAL_MASK) >> PCIE_INT_MASK_INTAL_LSB)
#define PCIE_INT_MASK_INTAL_SET(x)                                   (((x) << PCIE_INT_MASK_INTAL_LSB) & PCIE_INT_MASK_INTAL_MASK)
#define PCIE_INT_MASK_INTAL_RESET                                    0x0 // 0
#define PCIE_INT_MASK_SYS_ERR_MSB                                    13
#define PCIE_INT_MASK_SYS_ERR_LSB                                    13
#define PCIE_INT_MASK_SYS_ERR_MASK                                   0x00002000
#define PCIE_INT_MASK_SYS_ERR_GET(x)                                 (((x) & PCIE_INT_MASK_SYS_ERR_MASK) >> PCIE_INT_MASK_SYS_ERR_LSB)
#define PCIE_INT_MASK_SYS_ERR_SET(x)                                 (((x) << PCIE_INT_MASK_SYS_ERR_LSB) & PCIE_INT_MASK_SYS_ERR_MASK)
#define PCIE_INT_MASK_SYS_ERR_RESET                                  0x0 // 0
#define PCIE_INT_MASK_AER_MSI_MSB                                    12
#define PCIE_INT_MASK_AER_MSI_LSB                                    12
#define PCIE_INT_MASK_AER_MSI_MASK                                   0x00001000
#define PCIE_INT_MASK_AER_MSI_GET(x)                                 (((x) & PCIE_INT_MASK_AER_MSI_MASK) >> PCIE_INT_MASK_AER_MSI_LSB)
#define PCIE_INT_MASK_AER_MSI_SET(x)                                 (((x) << PCIE_INT_MASK_AER_MSI_LSB) & PCIE_INT_MASK_AER_MSI_MASK)
#define PCIE_INT_MASK_AER_MSI_RESET                                  0x0 // 0
#define PCIE_INT_MASK_AER_INT_MSB                                    11
#define PCIE_INT_MASK_AER_INT_LSB                                    11
#define PCIE_INT_MASK_AER_INT_MASK                                   0x00000800
#define PCIE_INT_MASK_AER_INT_GET(x)                                 (((x) & PCIE_INT_MASK_AER_INT_MASK) >> PCIE_INT_MASK_AER_INT_LSB)
#define PCIE_INT_MASK_AER_INT_SET(x)                                 (((x) << PCIE_INT_MASK_AER_INT_LSB) & PCIE_INT_MASK_AER_INT_MASK)
#define PCIE_INT_MASK_AER_INT_RESET                                  0x0 // 0
#define PCIE_INT_MASK_MSI_ERR_MSB                                    10
#define PCIE_INT_MASK_MSI_ERR_LSB                                    10
#define PCIE_INT_MASK_MSI_ERR_MASK                                   0x00000400
#define PCIE_INT_MASK_MSI_ERR_GET(x)                                 (((x) & PCIE_INT_MASK_MSI_ERR_MASK) >> PCIE_INT_MASK_MSI_ERR_LSB)
#define PCIE_INT_MASK_MSI_ERR_SET(x)                                 (((x) << PCIE_INT_MASK_MSI_ERR_LSB) & PCIE_INT_MASK_MSI_ERR_MASK)
#define PCIE_INT_MASK_MSI_ERR_RESET                                  0x0 // 0
#define PCIE_INT_MASK_MSI_MSB                                        9
#define PCIE_INT_MASK_MSI_LSB                                        9
#define PCIE_INT_MASK_MSI_MASK                                       0x00000200
#define PCIE_INT_MASK_MSI_GET(x)                                     (((x) & PCIE_INT_MASK_MSI_MASK) >> PCIE_INT_MASK_MSI_LSB)
#define PCIE_INT_MASK_MSI_SET(x)                                     (((x) << PCIE_INT_MASK_MSI_LSB) & PCIE_INT_MASK_MSI_MASK)
#define PCIE_INT_MASK_MSI_RESET                                      0x0 // 0
#define PCIE_INT_MASK_INTD_MSB                                       8
#define PCIE_INT_MASK_INTD_LSB                                       8
#define PCIE_INT_MASK_INTD_MASK                                      0x00000100
#define PCIE_INT_MASK_INTD_GET(x)                                    (((x) & PCIE_INT_MASK_INTD_MASK) >> PCIE_INT_MASK_INTD_LSB)
#define PCIE_INT_MASK_INTD_SET(x)                                    (((x) << PCIE_INT_MASK_INTD_LSB) & PCIE_INT_MASK_INTD_MASK)
#define PCIE_INT_MASK_INTD_RESET                                     0x0 // 0
#define PCIE_INT_MASK_INTC_MSB                                       7
#define PCIE_INT_MASK_INTC_LSB                                       7
#define PCIE_INT_MASK_INTC_MASK                                      0x00000080
#define PCIE_INT_MASK_INTC_GET(x)                                    (((x) & PCIE_INT_MASK_INTC_MASK) >> PCIE_INT_MASK_INTC_LSB)
#define PCIE_INT_MASK_INTC_SET(x)                                    (((x) << PCIE_INT_MASK_INTC_LSB) & PCIE_INT_MASK_INTC_MASK)
#define PCIE_INT_MASK_INTC_RESET                                     0x0 // 0
#define PCIE_INT_MASK_INTB_MSB                                       6
#define PCIE_INT_MASK_INTB_LSB                                       6
#define PCIE_INT_MASK_INTB_MASK                                      0x00000040
#define PCIE_INT_MASK_INTB_GET(x)                                    (((x) & PCIE_INT_MASK_INTB_MASK) >> PCIE_INT_MASK_INTB_LSB)
#define PCIE_INT_MASK_INTB_SET(x)                                    (((x) << PCIE_INT_MASK_INTB_LSB) & PCIE_INT_MASK_INTB_MASK)
#define PCIE_INT_MASK_INTB_RESET                                     0x0 // 0
#define PCIE_INT_MASK_INTA_MSB                                       5
#define PCIE_INT_MASK_INTA_LSB                                       5
#define PCIE_INT_MASK_INTA_MASK                                      0x00000020
#define PCIE_INT_MASK_INTA_GET(x)                                    (((x) & PCIE_INT_MASK_INTA_MASK) >> PCIE_INT_MASK_INTA_LSB)
#define PCIE_INT_MASK_INTA_SET(x)                                    (((x) << PCIE_INT_MASK_INTA_LSB) & PCIE_INT_MASK_INTA_MASK)
#define PCIE_INT_MASK_INTA_RESET                                     0x0 // 0
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_MSB                      4
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_LSB                      4
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_MASK                     0x00000010
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_GET(x)                   (((x) & PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_MASK) >> PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_LSB)
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_SET(x)                   (((x) << PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_LSB) & PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_MASK)
#define PCIE_INT_MASK_RADMX_COMP_LOOKUP_ERR_RESET                    0x0 // 0
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_MSB                         3
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_LSB                         3
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_MASK                        0x00000008
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_GET(x)                      (((x) & PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_MASK) >> PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_LSB)
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_SET(x)                      (((x) << PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_LSB) & PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_MASK)
#define PCIE_INT_MASK_GM_COMP_LOOKUP_ERR_RESET                       0x0 // 0
#define PCIE_INT_MASK_FATAL_ERR_MSB                                  2
#define PCIE_INT_MASK_FATAL_ERR_LSB                                  2
#define PCIE_INT_MASK_FATAL_ERR_MASK                                 0x00000004
#define PCIE_INT_MASK_FATAL_ERR_GET(x)                               (((x) & PCIE_INT_MASK_FATAL_ERR_MASK) >> PCIE_INT_MASK_FATAL_ERR_LSB)
#define PCIE_INT_MASK_FATAL_ERR_SET(x)                               (((x) << PCIE_INT_MASK_FATAL_ERR_LSB) & PCIE_INT_MASK_FATAL_ERR_MASK)
#define PCIE_INT_MASK_FATAL_ERR_RESET                                0x0 // 0
#define PCIE_INT_MASK_NONFATAL_ERR_MSB                               1
#define PCIE_INT_MASK_NONFATAL_ERR_LSB                               1
#define PCIE_INT_MASK_NONFATAL_ERR_MASK                              0x00000002
#define PCIE_INT_MASK_NONFATAL_ERR_GET(x)                            (((x) & PCIE_INT_MASK_NONFATAL_ERR_MASK) >> PCIE_INT_MASK_NONFATAL_ERR_LSB)
#define PCIE_INT_MASK_NONFATAL_ERR_SET(x)                            (((x) << PCIE_INT_MASK_NONFATAL_ERR_LSB) & PCIE_INT_MASK_NONFATAL_ERR_MASK)
#define PCIE_INT_MASK_NONFATAL_ERR_RESET                             0x0 // 0
#define PCIE_INT_MASK_CORR_ERR_MSB                                   0
#define PCIE_INT_MASK_CORR_ERR_LSB                                   0
#define PCIE_INT_MASK_CORR_ERR_MASK                                  0x00000001
#define PCIE_INT_MASK_CORR_ERR_GET(x)                                (((x) & PCIE_INT_MASK_CORR_ERR_MASK) >> PCIE_INT_MASK_CORR_ERR_LSB)
#define PCIE_INT_MASK_CORR_ERR_SET(x)                                (((x) << PCIE_INT_MASK_CORR_ERR_LSB) & PCIE_INT_MASK_CORR_ERR_MASK)
#define PCIE_INT_MASK_CORR_ERR_RESET                                 0x0 // 0

#define PCIE_INT_STATUS_ADDRESS                                      0x180f004c
#define PCIE_INT_MASK_ADDRESS                                        0x180f0050

#define PCIE_INT_STATUS_ADDRESS_2                                    0x1828004c
#define PCIE_INT_MASK_ADDRESS_2                                      0x18280050

#define ETH_SGMII_SERDES_EN_LOCK_DETECT_MSB                          2
#define ETH_SGMII_SERDES_EN_LOCK_DETECT_LSB                          2
#define ETH_SGMII_SERDES_EN_LOCK_DETECT_MASK                         0x00000004
#define ETH_SGMII_SERDES_EN_LOCK_DETECT_GET(x)                       (((x) & ETH_SGMII_SERDES_EN_LOCK_DETECT_MASK) >> ETH_SGMII_SERDES_EN_LOCK_DETECT_LSB)
#define ETH_SGMII_SERDES_EN_LOCK_DETECT_SET(x)                       (((x) << ETH_SGMII_SERDES_EN_LOCK_DETECT_LSB) & ETH_SGMII_SERDES_EN_LOCK_DETECT_MASK)
#define ETH_SGMII_SERDES_EN_LOCK_DETECT_RESET                        0x0 // 0
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_MSB                          1
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_LSB                          1
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_MASK                         0x00000002
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_GET(x)                       (((x) & ETH_SGMII_SERDES_PLL_REFCLK_SEL_MASK) >> ETH_SGMII_SERDES_PLL_REFCLK_SEL_LSB)
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_SET(x)                       (((x) << ETH_SGMII_SERDES_PLL_REFCLK_SEL_LSB) & ETH_SGMII_SERDES_PLL_REFCLK_SEL_MASK)
#define ETH_SGMII_SERDES_PLL_REFCLK_SEL_RESET                        0x0 // 0
#define ETH_SGMII_SERDES_EN_PLL_MSB                                  0
#define ETH_SGMII_SERDES_EN_PLL_LSB                                  0
#define ETH_SGMII_SERDES_EN_PLL_MASK                                 0x00000001
#define ETH_SGMII_SERDES_EN_PLL_GET(x)                               (((x) & ETH_SGMII_SERDES_EN_PLL_MASK) >> ETH_SGMII_SERDES_EN_PLL_LSB)
#define ETH_SGMII_SERDES_EN_PLL_SET(x)                               (((x) << ETH_SGMII_SERDES_EN_PLL_LSB) & ETH_SGMII_SERDES_EN_PLL_MASK)
#define ETH_SGMII_SERDES_EN_PLL_RESET                                0x1 // 1
#define ETH_SGMII_SERDES_ADDRESS                                     0x1805004c

#define SLIC_PCM_DIV_ADDRESS                                         0x18050054

#define ETH_CFG_ETH_SPARE_MSB                                        31
#define ETH_CFG_ETH_SPARE_LSB                                        22
#define ETH_CFG_ETH_SPARE_MASK                                       0xffc00000
#define ETH_CFG_ETH_SPARE_GET(x)                                     (((x) & ETH_CFG_ETH_SPARE_MASK) >> ETH_CFG_ETH_SPARE_LSB)
#define ETH_CFG_ETH_SPARE_SET(x)                                     (((x) << ETH_CFG_ETH_SPARE_LSB) & ETH_CFG_ETH_SPARE_MASK)
#define ETH_CFG_ETH_SPARE_RESET                                      0x0 // 0
#define ETH_CFG_ETH_TXEN_DELAY_MSB                                   21
#define ETH_CFG_ETH_TXEN_DELAY_LSB                                   20
#define ETH_CFG_ETH_TXEN_DELAY_MASK                                  0x00300000
#define ETH_CFG_ETH_TXEN_DELAY_GET(x)                                (((x) & ETH_CFG_ETH_TXEN_DELAY_MASK) >> ETH_CFG_ETH_TXEN_DELAY_LSB)
#define ETH_CFG_ETH_TXEN_DELAY_SET(x)                                (((x) << ETH_CFG_ETH_TXEN_DELAY_LSB) & ETH_CFG_ETH_TXEN_DELAY_MASK)
#define ETH_CFG_ETH_TXEN_DELAY_RESET                                 0x0 // 0
#define ETH_CFG_ETH_TXD_DELAY_MSB                                    19
#define ETH_CFG_ETH_TXD_DELAY_LSB                                    18
#define ETH_CFG_ETH_TXD_DELAY_MASK                                   0x000c0000
#define ETH_CFG_ETH_TXD_DELAY_GET(x)                                 (((x) & ETH_CFG_ETH_TXD_DELAY_MASK) >> ETH_CFG_ETH_TXD_DELAY_LSB)
#define ETH_CFG_ETH_TXD_DELAY_SET(x)                                 (((x) << ETH_CFG_ETH_TXD_DELAY_LSB) & ETH_CFG_ETH_TXD_DELAY_MASK)
#define ETH_CFG_ETH_TXD_DELAY_RESET                                  0x0 // 0
#define ETH_CFG_ETH_RXDV_DELAY_MSB                                   17
#define ETH_CFG_ETH_RXDV_DELAY_LSB                                   16
#define ETH_CFG_ETH_RXDV_DELAY_MASK                                  0x00030000
#define ETH_CFG_ETH_RXDV_DELAY_GET(x)                                (((x) & ETH_CFG_ETH_RXDV_DELAY_MASK) >> ETH_CFG_ETH_RXDV_DELAY_LSB)
#define ETH_CFG_ETH_RXDV_DELAY_SET(x)                                (((x) << ETH_CFG_ETH_RXDV_DELAY_LSB) & ETH_CFG_ETH_RXDV_DELAY_MASK)
#define ETH_CFG_ETH_RXDV_DELAY_RESET                                 0x0 // 0
#define ETH_CFG_ETH_RXD_DELAY_MSB                                    15
#define ETH_CFG_ETH_RXD_DELAY_LSB                                    14
#define ETH_CFG_ETH_RXD_DELAY_MASK                                   0x0000c000
#define ETH_CFG_ETH_RXD_DELAY_GET(x)                                 (((x) & ETH_CFG_ETH_RXD_DELAY_MASK) >> ETH_CFG_ETH_RXD_DELAY_LSB)
#define ETH_CFG_ETH_RXD_DELAY_SET(x)                                 (((x) << ETH_CFG_ETH_RXD_DELAY_LSB) & ETH_CFG_ETH_RXD_DELAY_MASK)
#define ETH_CFG_ETH_RXD_DELAY_RESET                                  0x0 // 0
#define ETH_CFG_RMII_GE0_MASTER_MSB                                  12
#define ETH_CFG_RMII_GE0_MASTER_LSB                                  12
#define ETH_CFG_RMII_GE0_MASTER_MASK                                 0x00001000
#define ETH_CFG_RMII_GE0_MASTER_GET(x)                               (((x) & ETH_CFG_RMII_GE0_MASTER_MASK) >> ETH_CFG_RMII_GE0_MASTER_LSB)
#define ETH_CFG_RMII_GE0_MASTER_SET(x)                               (((x) << ETH_CFG_RMII_GE0_MASTER_LSB) & ETH_CFG_RMII_GE0_MASTER_MASK)
#define ETH_CFG_RMII_GE0_MASTER_RESET                                0x1 // 1
#define ETH_CFG_MII_CNTL_SPEED_MSB                                   11
#define ETH_CFG_MII_CNTL_SPEED_LSB                                   11
#define ETH_CFG_MII_CNTL_SPEED_MASK                                  0x00000800
#define ETH_CFG_MII_CNTL_SPEED_GET(x)                                (((x) & ETH_CFG_MII_CNTL_SPEED_MASK) >> ETH_CFG_MII_CNTL_SPEED_LSB)
#define ETH_CFG_MII_CNTL_SPEED_SET(x)                                (((x) << ETH_CFG_MII_CNTL_SPEED_LSB) & ETH_CFG_MII_CNTL_SPEED_MASK)
#define ETH_CFG_MII_CNTL_SPEED_RESET                                 0x0 // 0
#define ETH_CFG_RMII_GE0_MSB                                         10
#define ETH_CFG_RMII_GE0_LSB                                         10
#define ETH_CFG_RMII_GE0_MASK                                        0x00000400
#define ETH_CFG_RMII_GE0_GET(x)                                      (((x) & ETH_CFG_RMII_GE0_MASK) >> ETH_CFG_RMII_GE0_LSB)
#define ETH_CFG_RMII_GE0_SET(x)                                      (((x) << ETH_CFG_RMII_GE0_LSB) & ETH_CFG_RMII_GE0_MASK)
#define ETH_CFG_RMII_GE0_RESET                                       0x0 // 0
#define ETH_CFG_GE0_SGMII_MSB                                        6
#define ETH_CFG_GE0_SGMII_LSB                                        6
#define ETH_CFG_GE0_SGMII_MASK                                       0x00000040
#define ETH_CFG_GE0_SGMII_GET(x)                                     (((x) & ETH_CFG_GE0_SGMII_MASK) >> ETH_CFG_GE0_SGMII_LSB)
#define ETH_CFG_GE0_SGMII_SET(x)                                     (((x) << ETH_CFG_GE0_SGMII_LSB) & ETH_CFG_GE0_SGMII_MASK)
#define ETH_CFG_GE0_SGMII_RESET                                      0x0 // 0
#define ETH_CFG_GE0_ERR_EN_MSB                                       5
#define ETH_CFG_GE0_ERR_EN_LSB                                       5
#define ETH_CFG_GE0_ERR_EN_MASK                                      0x00000020
#define ETH_CFG_GE0_ERR_EN_GET(x)                                    (((x) & ETH_CFG_GE0_ERR_EN_MASK) >> ETH_CFG_GE0_ERR_EN_LSB)
#define ETH_CFG_GE0_ERR_EN_SET(x)                                    (((x) << ETH_CFG_GE0_ERR_EN_LSB) & ETH_CFG_GE0_ERR_EN_MASK)
#define ETH_CFG_GE0_ERR_EN_RESET                                     0x0 // 0
#define ETH_CFG_MII_GE0_SLAVE_MSB                                    4
#define ETH_CFG_MII_GE0_SLAVE_LSB                                    4
#define ETH_CFG_MII_GE0_SLAVE_MASK                                   0x00000010
#define ETH_CFG_MII_GE0_SLAVE_GET(x)                                 (((x) & ETH_CFG_MII_GE0_SLAVE_MASK) >> ETH_CFG_MII_GE0_SLAVE_LSB)
#define ETH_CFG_MII_GE0_SLAVE_SET(x)                                 (((x) << ETH_CFG_MII_GE0_SLAVE_LSB) & ETH_CFG_MII_GE0_SLAVE_MASK)
#define ETH_CFG_MII_GE0_SLAVE_RESET                                  0x0 // 0
#define ETH_CFG_MII_GE0_MASTER_MSB                                   3
#define ETH_CFG_MII_GE0_MASTER_LSB                                   3
#define ETH_CFG_MII_GE0_MASTER_MASK                                  0x00000008
#define ETH_CFG_MII_GE0_MASTER_GET(x)                                (((x) & ETH_CFG_MII_GE0_MASTER_MASK) >> ETH_CFG_MII_GE0_MASTER_LSB)
#define ETH_CFG_MII_GE0_MASTER_SET(x)                                (((x) << ETH_CFG_MII_GE0_MASTER_LSB) & ETH_CFG_MII_GE0_MASTER_MASK)
#define ETH_CFG_MII_GE0_MASTER_RESET                                 0x0 // 0
#define ETH_CFG_GMII_GE0_MSB                                         2
#define ETH_CFG_GMII_GE0_LSB                                         2
#define ETH_CFG_GMII_GE0_MASK                                        0x00000004
#define ETH_CFG_GMII_GE0_GET(x)                                      (((x) & ETH_CFG_GMII_GE0_MASK) >> ETH_CFG_GMII_GE0_LSB)
#define ETH_CFG_GMII_GE0_SET(x)                                      (((x) << ETH_CFG_GMII_GE0_LSB) & ETH_CFG_GMII_GE0_MASK)
#define ETH_CFG_GMII_GE0_RESET                                       0x0 // 0
#define ETH_CFG_MII_GE0_MSB                                          1
#define ETH_CFG_MII_GE0_LSB                                          1
#define ETH_CFG_MII_GE0_MASK                                         0x00000002
#define ETH_CFG_MII_GE0_GET(x)                                       (((x) & ETH_CFG_MII_GE0_MASK) >> ETH_CFG_MII_GE0_LSB)
#define ETH_CFG_MII_GE0_SET(x)                                       (((x) << ETH_CFG_MII_GE0_LSB) & ETH_CFG_MII_GE0_MASK)
#define ETH_CFG_MII_GE0_RESET                                        0x0 // 0
#define ETH_CFG_RGMII_GE0_MSB                                        0
#define ETH_CFG_RGMII_GE0_LSB                                        0
#define ETH_CFG_RGMII_GE0_MASK                                       0x00000001
#define ETH_CFG_RGMII_GE0_GET(x)                                     (((x) & ETH_CFG_RGMII_GE0_MASK) >> ETH_CFG_RGMII_GE0_LSB)
#define ETH_CFG_RGMII_GE0_SET(x)                                     (((x) << ETH_CFG_RGMII_GE0_LSB) & ETH_CFG_RGMII_GE0_MASK)
#define ETH_CFG_RGMII_GE0_RESET                                      0x0 // 0
#define ETH_CFG_ADDRESS                                              0x18070000



#define SGMII_SERDES_VCO_REG_MSB                                     30
#define SGMII_SERDES_VCO_REG_LSB                                     27
#define SGMII_SERDES_VCO_REG_MASK                                    0x78000000
#define SGMII_SERDES_VCO_REG_GET(x)                                  (((x) & SGMII_SERDES_VCO_REG_MASK) >> SGMII_SERDES_VCO_REG_LSB)
#define SGMII_SERDES_VCO_REG_SET(x)                                  (((x) << SGMII_SERDES_VCO_REG_LSB) & SGMII_SERDES_VCO_REG_MASK)
#define SGMII_SERDES_VCO_REG_RESET                                   0x3 // 3
#define SGMII_SERDES_RES_CALIBRATION_MSB                             26
#define SGMII_SERDES_RES_CALIBRATION_LSB                             23
#define SGMII_SERDES_RES_CALIBRATION_MASK                            0x07800000
#define SGMII_SERDES_RES_CALIBRATION_GET(x)                          (((x) & SGMII_SERDES_RES_CALIBRATION_MASK) >> SGMII_SERDES_RES_CALIBRATION_LSB)
#define SGMII_SERDES_RES_CALIBRATION_SET(x)                          (((x) << SGMII_SERDES_RES_CALIBRATION_LSB) & SGMII_SERDES_RES_CALIBRATION_MASK)
#define SGMII_SERDES_RES_CALIBRATION_RESET                           0x0 // 0
#define SGMII_SERDES_FIBER_MODE_MSB                                  21
#define SGMII_SERDES_FIBER_MODE_LSB                                  20
#define SGMII_SERDES_FIBER_MODE_MASK                                 0x00300000
#define SGMII_SERDES_FIBER_MODE_GET(x)                               (((x) & SGMII_SERDES_FIBER_MODE_MASK) >> SGMII_SERDES_FIBER_MODE_LSB)
#define SGMII_SERDES_FIBER_MODE_SET(x)                               (((x) << SGMII_SERDES_FIBER_MODE_LSB) & SGMII_SERDES_FIBER_MODE_MASK)
#define SGMII_SERDES_FIBER_MODE_RESET                                0x0 // 0
#define SGMII_SERDES_THRESHOLD_CTRL_MSB                              19
#define SGMII_SERDES_THRESHOLD_CTRL_LSB                              18
#define SGMII_SERDES_THRESHOLD_CTRL_MASK                             0x000c0000
#define SGMII_SERDES_THRESHOLD_CTRL_GET(x)                           (((x) & SGMII_SERDES_THRESHOLD_CTRL_MASK) >> SGMII_SERDES_THRESHOLD_CTRL_LSB)
#define SGMII_SERDES_THRESHOLD_CTRL_SET(x)                           (((x) << SGMII_SERDES_THRESHOLD_CTRL_LSB) & SGMII_SERDES_THRESHOLD_CTRL_MASK)
#define SGMII_SERDES_THRESHOLD_CTRL_RESET                            0x0 // 0
#define SGMII_SERDES_FIBER_SDO_MSB                                   17
#define SGMII_SERDES_FIBER_SDO_LSB                                   17
#define SGMII_SERDES_FIBER_SDO_MASK                                  0x00020000
#define SGMII_SERDES_FIBER_SDO_GET(x)                                (((x) & SGMII_SERDES_FIBER_SDO_MASK) >> SGMII_SERDES_FIBER_SDO_LSB)
#define SGMII_SERDES_FIBER_SDO_SET(x)                                (((x) << SGMII_SERDES_FIBER_SDO_LSB) & SGMII_SERDES_FIBER_SDO_MASK)
#define SGMII_SERDES_FIBER_SDO_RESET                                 0x0 // 0
#define SGMII_SERDES_EN_SIGNAL_DETECT_MSB                            16
#define SGMII_SERDES_EN_SIGNAL_DETECT_LSB                            16
#define SGMII_SERDES_EN_SIGNAL_DETECT_MASK                           0x00010000
#define SGMII_SERDES_EN_SIGNAL_DETECT_GET(x)                         (((x) & SGMII_SERDES_EN_SIGNAL_DETECT_MASK) >> SGMII_SERDES_EN_SIGNAL_DETECT_LSB)
#define SGMII_SERDES_EN_SIGNAL_DETECT_SET(x)                         (((x) << SGMII_SERDES_EN_SIGNAL_DETECT_LSB) & SGMII_SERDES_EN_SIGNAL_DETECT_MASK)
#define SGMII_SERDES_EN_SIGNAL_DETECT_RESET                          0x1 // 1
#define SGMII_SERDES_LOCK_DETECT_STATUS_MSB                          15
#define SGMII_SERDES_LOCK_DETECT_STATUS_LSB                          15
#define SGMII_SERDES_LOCK_DETECT_STATUS_MASK                         0x00008000
#define SGMII_SERDES_LOCK_DETECT_STATUS_GET(x)                       (((x) & SGMII_SERDES_LOCK_DETECT_STATUS_MASK) >> SGMII_SERDES_LOCK_DETECT_STATUS_LSB)
#define SGMII_SERDES_LOCK_DETECT_STATUS_SET(x)                       (((x) << SGMII_SERDES_LOCK_DETECT_STATUS_LSB) & SGMII_SERDES_LOCK_DETECT_STATUS_MASK)
#define SGMII_SERDES_LOCK_DETECT_STATUS_RESET                        0x0 // 0
#define SGMII_SERDES_SPARE0_MSB                                      14
#define SGMII_SERDES_SPARE0_LSB                                      11
#define SGMII_SERDES_SPARE0_MASK                                     0x00007800
#define SGMII_SERDES_SPARE0_GET(x)                                   (((x) & SGMII_SERDES_SPARE0_MASK) >> SGMII_SERDES_SPARE0_LSB)
#define SGMII_SERDES_SPARE0_SET(x)                                   (((x) << SGMII_SERDES_SPARE0_LSB) & SGMII_SERDES_SPARE0_MASK)
#define SGMII_SERDES_SPARE0_RESET                                    0x0 // 0
#define SGMII_SERDES_VCO_SLOW_MSB                                    10
#define SGMII_SERDES_VCO_SLOW_LSB                                    10
#define SGMII_SERDES_VCO_SLOW_MASK                                   0x00000400
#define SGMII_SERDES_VCO_SLOW_GET(x)                                 (((x) & SGMII_SERDES_VCO_SLOW_MASK) >> SGMII_SERDES_VCO_SLOW_LSB)
#define SGMII_SERDES_VCO_SLOW_SET(x)                                 (((x) << SGMII_SERDES_VCO_SLOW_LSB) & SGMII_SERDES_VCO_SLOW_MASK)
#define SGMII_SERDES_VCO_SLOW_RESET                                  0x0 // 0
#define SGMII_SERDES_VCO_FAST_MSB                                    9
#define SGMII_SERDES_VCO_FAST_LSB                                    9
#define SGMII_SERDES_VCO_FAST_MASK                                   0x00000200
#define SGMII_SERDES_VCO_FAST_GET(x)                                 (((x) & SGMII_SERDES_VCO_FAST_MASK) >> SGMII_SERDES_VCO_FAST_LSB)
#define SGMII_SERDES_VCO_FAST_SET(x)                                 (((x) << SGMII_SERDES_VCO_FAST_LSB) & SGMII_SERDES_VCO_FAST_MASK)
#define SGMII_SERDES_VCO_FAST_RESET                                  0x0 // 0
#define SGMII_SERDES_PLL_BW_MSB                                      8
#define SGMII_SERDES_PLL_BW_LSB                                      8
#define SGMII_SERDES_PLL_BW_MASK                                     0x00000100
#define SGMII_SERDES_PLL_BW_GET(x)                                   (((x) & SGMII_SERDES_PLL_BW_MASK) >> SGMII_SERDES_PLL_BW_LSB)
#define SGMII_SERDES_PLL_BW_SET(x)                                   (((x) << SGMII_SERDES_PLL_BW_LSB) & SGMII_SERDES_PLL_BW_MASK)
#define SGMII_SERDES_PLL_BW_RESET                                    0x1 // 1
#define SGMII_SERDES_TX_IMPEDANCE_MSB                                7
#define SGMII_SERDES_TX_IMPEDANCE_LSB                                7
#define SGMII_SERDES_TX_IMPEDANCE_MASK                               0x00000080
#define SGMII_SERDES_TX_IMPEDANCE_GET(x)                             (((x) & SGMII_SERDES_TX_IMPEDANCE_MASK) >> SGMII_SERDES_TX_IMPEDANCE_LSB)
#define SGMII_SERDES_TX_IMPEDANCE_SET(x)                             (((x) << SGMII_SERDES_TX_IMPEDANCE_LSB) & SGMII_SERDES_TX_IMPEDANCE_MASK)
#define SGMII_SERDES_TX_IMPEDANCE_RESET                              0x0 // 0
#define SGMII_SERDES_TX_DR_CTRL_MSB                                  6
#define SGMII_SERDES_TX_DR_CTRL_LSB                                  4
#define SGMII_SERDES_TX_DR_CTRL_MASK                                 0x00000070
#define SGMII_SERDES_TX_DR_CTRL_GET(x)                               (((x) & SGMII_SERDES_TX_DR_CTRL_MASK) >> SGMII_SERDES_TX_DR_CTRL_LSB)
#define SGMII_SERDES_TX_DR_CTRL_SET(x)                               (((x) << SGMII_SERDES_TX_DR_CTRL_LSB) & SGMII_SERDES_TX_DR_CTRL_MASK)
#define SGMII_SERDES_TX_DR_CTRL_RESET                                0x1 // 1
#define SGMII_SERDES_HALF_TX_MSB                                     3
#define SGMII_SERDES_HALF_TX_LSB                                     3
#define SGMII_SERDES_HALF_TX_MASK                                    0x00000008
#define SGMII_SERDES_HALF_TX_GET(x)                                  (((x) & SGMII_SERDES_HALF_TX_MASK) >> SGMII_SERDES_HALF_TX_LSB)
#define SGMII_SERDES_HALF_TX_SET(x)                                  (((x) << SGMII_SERDES_HALF_TX_LSB) & SGMII_SERDES_HALF_TX_MASK)
#define SGMII_SERDES_HALF_TX_RESET                                   0x0 // 0
#define SGMII_SERDES_CDR_BW_MSB                                      2
#define SGMII_SERDES_CDR_BW_LSB                                      1
#define SGMII_SERDES_CDR_BW_MASK                                     0x00000006
#define SGMII_SERDES_CDR_BW_GET(x)                                   (((x) & SGMII_SERDES_CDR_BW_MASK) >> SGMII_SERDES_CDR_BW_LSB)
#define SGMII_SERDES_CDR_BW_SET(x)                                   (((x) << SGMII_SERDES_CDR_BW_LSB) & SGMII_SERDES_CDR_BW_MASK)
#define SGMII_SERDES_CDR_BW_RESET                                    0x3 // 3
#define SGMII_SERDES_RX_IMPEDANCE_MSB                                0
#define SGMII_SERDES_RX_IMPEDANCE_LSB                                0
#define SGMII_SERDES_RX_IMPEDANCE_MASK                               0x00000001
#define SGMII_SERDES_RX_IMPEDANCE_GET(x)                             (((x) & SGMII_SERDES_RX_IMPEDANCE_MASK) >> SGMII_SERDES_RX_IMPEDANCE_LSB)
#define SGMII_SERDES_RX_IMPEDANCE_SET(x)                             (((x) << SGMII_SERDES_RX_IMPEDANCE_LSB) & SGMII_SERDES_RX_IMPEDANCE_MASK)
#define SGMII_SERDES_RX_IMPEDANCE_RESET                              0x0 // 0
#define SGMII_SERDES_ADDRESS                                         0x18070018

#define RST_RESET2_SPARE_MSB                                         31
#define RST_RESET2_SPARE_LSB                                         19
#define RST_RESET2_SPARE_MASK                                        0xfff80000
#define RST_RESET2_SPARE_GET(x)                                      (((x) & RST_RESET2_SPARE_MASK) >> RST_RESET2_SPARE_LSB)
#define RST_RESET2_SPARE_SET(x)                                      (((x) << RST_RESET2_SPARE_LSB) & RST_RESET2_SPARE_MASK)
#define RST_RESET2_SPARE_RESET                                       0x0 // 0
#define RST_RESET2_EP_MODE_MSB                                       18
#define RST_RESET2_EP_MODE_LSB                                       18
#define RST_RESET2_EP_MODE_MASK                                      0x00040000
#define RST_RESET2_EP_MODE_GET(x)                                    (((x) & RST_RESET2_EP_MODE_MASK) >> RST_RESET2_EP_MODE_LSB)
#define RST_RESET2_EP_MODE_SET(x)                                    (((x) << RST_RESET2_EP_MODE_LSB) & RST_RESET2_EP_MODE_MASK)
#define RST_RESET2_EP_MODE_RESET                                     0x0 // 0
#define RST_RESET2_USB2_EXT_PWR_SEQ_MSB                              17
#define RST_RESET2_USB2_EXT_PWR_SEQ_LSB                              17
#define RST_RESET2_USB2_EXT_PWR_SEQ_MASK                             0x00020000
#define RST_RESET2_USB2_EXT_PWR_SEQ_GET(x)                           (((x) & RST_RESET2_USB2_EXT_PWR_SEQ_MASK) >> RST_RESET2_USB2_EXT_PWR_SEQ_LSB)
#define RST_RESET2_USB2_EXT_PWR_SEQ_SET(x)                           (((x) << RST_RESET2_USB2_EXT_PWR_SEQ_LSB) & RST_RESET2_USB2_EXT_PWR_SEQ_MASK)
#define RST_RESET2_USB2_EXT_PWR_SEQ_RESET                            0x1 // 1
#define RST_RESET2_USB1_EXT_PWR_SEQ_MSB                              16
#define RST_RESET2_USB1_EXT_PWR_SEQ_LSB                              16
#define RST_RESET2_USB1_EXT_PWR_SEQ_MASK                             0x00010000
#define RST_RESET2_USB1_EXT_PWR_SEQ_GET(x)                           (((x) & RST_RESET2_USB1_EXT_PWR_SEQ_MASK) >> RST_RESET2_USB1_EXT_PWR_SEQ_LSB)
#define RST_RESET2_USB1_EXT_PWR_SEQ_SET(x)                           (((x) << RST_RESET2_USB1_EXT_PWR_SEQ_LSB) & RST_RESET2_USB1_EXT_PWR_SEQ_MASK)
#define RST_RESET2_USB1_EXT_PWR_SEQ_RESET                            0x1 // 1
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_MSB                          15
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_LSB                          15
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_MASK                         0x00008000
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_GET(x)                       (((x) & RST_RESET2_USB_PHY2_PLL_PWD_EXT_MASK) >> RST_RESET2_USB_PHY2_PLL_PWD_EXT_LSB)
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_SET(x)                       (((x) << RST_RESET2_USB_PHY2_PLL_PWD_EXT_LSB) & RST_RESET2_USB_PHY2_PLL_PWD_EXT_MASK)
#define RST_RESET2_USB_PHY2_PLL_PWD_EXT_RESET                        0x0 // 0
#define RST_RESET2_USB_PHY2_ARESET_MSB                               11
#define RST_RESET2_USB_PHY2_ARESET_LSB                               11
#define RST_RESET2_USB_PHY2_ARESET_MASK                              0x00000800
#define RST_RESET2_USB_PHY2_ARESET_GET(x)                            (((x) & RST_RESET2_USB_PHY2_ARESET_MASK) >> RST_RESET2_USB_PHY2_ARESET_LSB)
#define RST_RESET2_USB_PHY2_ARESET_SET(x)                            (((x) << RST_RESET2_USB_PHY2_ARESET_LSB) & RST_RESET2_USB_PHY2_ARESET_MASK)
#define RST_RESET2_USB_PHY2_ARESET_RESET                             0x1 // 1
#define RST_RESET2_PCIE2_PHY_RESET_MSB                               7
#define RST_RESET2_PCIE2_PHY_RESET_LSB                               7
#define RST_RESET2_PCIE2_PHY_RESET_MASK                              0x00000080
#define RST_RESET2_PCIE2_PHY_RESET_GET(x)                            (((x) & RST_RESET2_PCIE2_PHY_RESET_MASK) >> RST_RESET2_PCIE2_PHY_RESET_LSB)
#define RST_RESET2_PCIE2_PHY_RESET_SET(x)                            (((x) << RST_RESET2_PCIE2_PHY_RESET_LSB) & RST_RESET2_PCIE2_PHY_RESET_MASK)
#define RST_RESET2_PCIE2_PHY_RESET_RESET                             0x1 // 1
#define RST_RESET2_PCIE2_RESET_MSB                                   6
#define RST_RESET2_PCIE2_RESET_LSB                                   6
#define RST_RESET2_PCIE2_RESET_MASK                                  0x00000040
#define RST_RESET2_PCIE2_RESET_GET(x)                                (((x) & RST_RESET2_PCIE2_RESET_MASK) >> RST_RESET2_PCIE2_RESET_LSB)
#define RST_RESET2_PCIE2_RESET_SET(x)                                (((x) << RST_RESET2_PCIE2_RESET_LSB) & RST_RESET2_PCIE2_RESET_MASK)
#define RST_RESET2_PCIE2_RESET_RESET                                 0x1 // 1
#define RST_RESET2_USB_HOST2_RESET_MSB                               5
#define RST_RESET2_USB_HOST2_RESET_LSB                               5
#define RST_RESET2_USB_HOST2_RESET_MASK                              0x00000020
#define RST_RESET2_USB_HOST2_RESET_GET(x)                            (((x) & RST_RESET2_USB_HOST2_RESET_MASK) >> RST_RESET2_USB_HOST2_RESET_LSB)
#define RST_RESET2_USB_HOST2_RESET_SET(x)                            (((x) << RST_RESET2_USB_HOST2_RESET_LSB) & RST_RESET2_USB_HOST2_RESET_MASK)
#define RST_RESET2_USB_HOST2_RESET_RESET                             0x1 // 1
#define RST_RESET2_USB_PHY2_RESET_MSB                                4
#define RST_RESET2_USB_PHY2_RESET_LSB                                4
#define RST_RESET2_USB_PHY2_RESET_MASK                               0x00000010
#define RST_RESET2_USB_PHY2_RESET_GET(x)                             (((x) & RST_RESET2_USB_PHY2_RESET_MASK) >> RST_RESET2_USB_PHY2_RESET_LSB)
#define RST_RESET2_USB_PHY2_RESET_SET(x)                             (((x) << RST_RESET2_USB_PHY2_RESET_LSB) & RST_RESET2_USB_PHY2_RESET_MASK)
#define RST_RESET2_USB_PHY2_RESET_RESET                              0x1 // 1
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_MSB                     3
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_LSB                     3
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_MASK                    0x00000008
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_GET(x)                  (((x) & RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_MASK) >> RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_LSB)
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_SET(x)                  (((x) << RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_LSB) & RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_MASK)
#define RST_RESET2_USB_PHY2_SUSPEND_OVERRIDE_RESET                   0x0 // 0
#define RST_RESET2_USB2_MODE_MSB                                     0
#define RST_RESET2_USB2_MODE_LSB                                     0
#define RST_RESET2_USB2_MODE_MASK                                    0x00000001
#define RST_RESET2_USB2_MODE_GET(x)                                  (((x) & RST_RESET2_USB2_MODE_MASK) >> RST_RESET2_USB2_MODE_LSB)
#define RST_RESET2_USB2_MODE_SET(x)                                  (((x) << RST_RESET2_USB2_MODE_LSB) & RST_RESET2_USB2_MODE_MASK)
#define RST_RESET2_USB2_MODE_RESET                                   0x1 // 1
#define RST_RESET2_ADDRESS                                           0x180600c4

#define PCIE2_RESET_EP_RESET_L_MSB                                   2
#define PCIE2_RESET_EP_RESET_L_LSB                                   2
#define PCIE2_RESET_EP_RESET_L_MASK                                  0x00000004
#define PCIE2_RESET_EP_RESET_L_GET(x)                                (((x) & PCIE2_RESET_EP_RESET_L_MASK) >> PCIE2_RESET_EP_RESET_L_LSB)
#define PCIE2_RESET_EP_RESET_L_SET(x)                                (((x) << PCIE2_RESET_EP_RESET_L_LSB) & PCIE2_RESET_EP_RESET_L_MASK)
#define PCIE2_RESET_EP_RESET_L_RESET                                 0x0 // 0
#define PCIE2_RESET_LINK_REQ_RESET_MSB                               1
#define PCIE2_RESET_LINK_REQ_RESET_LSB                               1
#define PCIE2_RESET_LINK_REQ_RESET_MASK                              0x00000002
#define PCIE2_RESET_LINK_REQ_RESET_GET(x)                            (((x) & PCIE2_RESET_LINK_REQ_RESET_MASK) >> PCIE2_RESET_LINK_REQ_RESET_LSB)
#define PCIE2_RESET_LINK_REQ_RESET_SET(x)                            (((x) << PCIE2_RESET_LINK_REQ_RESET_LSB) & PCIE2_RESET_LINK_REQ_RESET_MASK)
#define PCIE2_RESET_LINK_REQ_RESET_RESET                             0x0 // 0
#define PCIE2_RESET_LINK_UP_MSB                                      0
#define PCIE2_RESET_LINK_UP_LSB                                      0
#define PCIE2_RESET_LINK_UP_MASK                                     0x00000001
#define PCIE2_RESET_LINK_UP_GET(x)                                   (((x) & PCIE2_RESET_LINK_UP_MASK) >> PCIE2_RESET_LINK_UP_LSB)
#define PCIE2_RESET_LINK_UP_SET(x)                                   (((x) << PCIE2_RESET_LINK_UP_LSB) & PCIE2_RESET_LINK_UP_MASK)
#define PCIE2_RESET_LINK_UP_RESET                                    0x0 // 0
#define PCIE2_RESET_ADDRESS                                          0x18280018

#define PCIE2_APP_CFG_TYPE_MSB                                       21
#define PCIE2_APP_CFG_TYPE_LSB                                       20
#define PCIE2_APP_CFG_TYPE_MASK                                      0x00300000
#define PCIE2_APP_CFG_TYPE_GET(x)                                    (((x) & PCIE2_APP_CFG_TYPE_MASK) >> PCIE2_APP_CFG_TYPE_LSB)
#define PCIE2_APP_CFG_TYPE_SET(x)                                    (((x) << PCIE2_APP_CFG_TYPE_LSB) & PCIE2_APP_CFG_TYPE_MASK)
#define PCIE2_APP_CFG_TYPE_RESET                                     0x0 // 0
#define PCIE2_APP_PCIE2_BAR_MSN_MSB                                   19
#define PCIE2_APP_PCIE2_BAR_MSN_LSB                                   16
#define PCIE2_APP_PCIE2_BAR_MSN_MASK                                  0x000f0000
#define PCIE2_APP_PCIE2_BAR_MSN_GET(x)                                (((x) & PCIE2_APP_PCIE2_BAR_MSN_MASK) >> PCIE2_APP_PCIE2_BAR_MSN_LSB)
#define PCIE2_APP_PCIE2_BAR_MSN_SET(x)                                (((x) << PCIE2_APP_PCIE2_BAR_MSN_LSB) & PCIE2_APP_PCIE2_BAR_MSN_MASK)
#define PCIE2_APP_PCIE2_BAR_MSN_RESET                                 0x1 // 1
#define PCIE2_APP_CFG_BE_MSB                                         15
#define PCIE2_APP_CFG_BE_LSB                                         12
#define PCIE2_APP_CFG_BE_MASK                                        0x0000f000
#define PCIE2_APP_CFG_BE_GET(x)                                      (((x) & PCIE2_APP_CFG_BE_MASK) >> PCIE2_APP_CFG_BE_LSB)
#define PCIE2_APP_CFG_BE_SET(x)                                      (((x) << PCIE2_APP_CFG_BE_LSB) & PCIE2_APP_CFG_BE_MASK)
#define PCIE2_APP_CFG_BE_RESET                                       0xf // 15
#define PCIE2_APP_SLV_RESP_ERR_MAP_MSB                               11
#define PCIE2_APP_SLV_RESP_ERR_MAP_LSB                               6
#define PCIE2_APP_SLV_RESP_ERR_MAP_MASK                              0x00000fc0
#define PCIE2_APP_SLV_RESP_ERR_MAP_GET(x)                            (((x) & PCIE2_APP_SLV_RESP_ERR_MAP_MASK) >> PCIE2_APP_SLV_RESP_ERR_MAP_LSB)
#define PCIE2_APP_SLV_RESP_ERR_MAP_SET(x)                            (((x) << PCIE2_APP_SLV_RESP_ERR_MAP_LSB) & PCIE2_APP_SLV_RESP_ERR_MAP_MASK)
#define PCIE2_APP_SLV_RESP_ERR_MAP_RESET                             0x3f // 63
#define PCIE2_APP_MSTR_RESP_ERR_MAP_MSB                              5
#define PCIE2_APP_MSTR_RESP_ERR_MAP_LSB                              4
#define PCIE2_APP_MSTR_RESP_ERR_MAP_MASK                             0x00000030
#define PCIE2_APP_MSTR_RESP_ERR_MAP_GET(x)                           (((x) & PCIE2_APP_MSTR_RESP_ERR_MAP_MASK) >> PCIE2_APP_MSTR_RESP_ERR_MAP_LSB)
#define PCIE2_APP_MSTR_RESP_ERR_MAP_SET(x)                           (((x) << PCIE2_APP_MSTR_RESP_ERR_MAP_LSB) & PCIE2_APP_MSTR_RESP_ERR_MAP_MASK)
#define PCIE2_APP_MSTR_RESP_ERR_MAP_RESET                            0x0 // 0
#define PCIE2_APP_INIT_RST_MSB                                       3
#define PCIE2_APP_INIT_RST_LSB                                       3
#define PCIE2_APP_INIT_RST_MASK                                      0x00000008
#define PCIE2_APP_INIT_RST_GET(x)                                    (((x) & PCIE2_APP_INIT_RST_MASK) >> PCIE2_APP_INIT_RST_LSB)
#define PCIE2_APP_INIT_RST_SET(x)                                    (((x) << PCIE2_APP_INIT_RST_LSB) & PCIE2_APP_INIT_RST_MASK)
#define PCIE2_APP_INIT_RST_RESET                                     0x0 // 0
#define PCIE2_APP_PM_XMT_TURNOFF_MSB                                 2
#define PCIE2_APP_PM_XMT_TURNOFF_LSB                                 2
#define PCIE2_APP_PM_XMT_TURNOFF_MASK                                0x00000004
#define PCIE2_APP_PM_XMT_TURNOFF_GET(x)                              (((x) & PCIE2_APP_PM_XMT_TURNOFF_MASK) >> PCIE2_APP_PM_XMT_TURNOFF_LSB)
#define PCIE2_APP_PM_XMT_TURNOFF_SET(x)                              (((x) << PCIE2_APP_PM_XMT_TURNOFF_LSB) & PCIE2_APP_PM_XMT_TURNOFF_MASK)
#define PCIE2_APP_PM_XMT_TURNOFF_RESET                               0x0 // 0
#define PCIE2_APP_UNLOCK_MSG_MSB                                     1
#define PCIE2_APP_UNLOCK_MSG_LSB                                     1
#define PCIE2_APP_UNLOCK_MSG_MASK                                    0x00000002
#define PCIE2_APP_UNLOCK_MSG_GET(x)                                  (((x) & PCIE2_APP_UNLOCK_MSG_MASK) >> PCIE2_APP_UNLOCK_MSG_LSB)
#define PCIE2_APP_UNLOCK_MSG_SET(x)                                  (((x) << PCIE2_APP_UNLOCK_MSG_LSB) & PCIE2_APP_UNLOCK_MSG_MASK)
#define PCIE2_APP_UNLOCK_MSG_RESET                                   0x0 // 0
#define PCIE2_APP_LTSSM_ENABLE_MSB                                   0
#define PCIE2_APP_LTSSM_ENABLE_LSB                                   0
#define PCIE2_APP_LTSSM_ENABLE_MASK                                  0x00000001
#define PCIE2_APP_LTSSM_ENABLE_GET(x)                                (((x) & PCIE2_APP_LTSSM_ENABLE_MASK) >> PCIE2_APP_LTSSM_ENABLE_LSB)
#define PCIE2_APP_LTSSM_ENABLE_SET(x)                                (((x) << PCIE2_APP_LTSSM_ENABLE_LSB) & PCIE2_APP_LTSSM_ENABLE_MASK)
#define PCIE2_APP_LTSSM_ENABLE_RESET                                 0x0 // 0
#define PCIE2_APP_ADDRESS                                            0x18280000

#define MBOX_FIFO				0x180a0000
#define MBOX_FIFO_STATUS			0x180a0008
#define MBOX_SLIC_FIFO_STATUS			0x180a000c
#define MBOX_DMA_POLICY				0x180a0010
#define MBOX_SLIC_DMA_POLICY			0x180a0014
#define MBOX_DMA_RX_DESCRIPTOR_BASE0		0x180a0018
#define MBOX_DMA_RX_CONTROL0			0x180a001c
#define MBOX_DMA_TX_DESCRIPTOR_BASE0		0x180a0020
#define MBOX_DMA_TX_CONTROL0			0x180a0024
#define MBOX_DMA_RX_DESCRIPTOR_BASE1		0x180a0028
#define MBOX_DMA_RX_CONTROL1			0x180a002c
#define MBOX_DMA_TX_DESCRIPTOR_BASE1		0x180a0030
#define MBOX_DMA_TX_CONTROL1			0x180a0034
#define MBOX_FRAME				0x180a0034
#define MBOX_SLIC_FRAME				0x180a003c
#define MBOX_FIFO_TIMEOUT			0x180a0040
#define MBOX_INT_STATUS				0x180a0044
#define MBOX_SLIC_INT_STATUS			0x180a0048
#define MBOX_INT_ENABLE				0x180a004c
#define MBOX_SLIC_INT_ENABLE			0x180a0050
#define MBOX_FIFO_RESET				0x180a0058
#define MBOX_SLIC_FIFO_RESET			0x180a005c

#define MBOX_DMA_POLICY_RX_QUANTUM		(1<< 1)
#define MBOX_DMA_POLICY_TX_QUANTUM		(1<< 3)
#define MBOX_DMA_POLICY_TX_FIFO_THRESH(x)	((0xff&x)<< 4)

#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_MSB      11
#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_LSB      11
#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_MASK     0x00000800
#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_GET(x)   (((x) & MBOX_DMA_POLICY_TXD_16BIT_SWAP_MASK) >> MBOX_DMA_POLICY_TXD_16BIT_SWAP_LSB)
#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_SET(x)   (((x) << MBOX_DMA_POLICY_TXD_16BIT_SWAP_LSB) & MBOX_DMA_POLICY_TXD_16BIT_SWAP_MASK)
#define MBOX_DMA_POLICY_TXD_16BIT_SWAP_RESET    0x0 // 0
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_MSB      10
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_LSB      10
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_MASK     0x00000400
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_GET(x)   (((x) & MBOX_DMA_POLICY_RXD_16BIT_SWAP_MASK) >> MBOX_DMA_POLICY_RXD_16BIT_SWAP_LSB)
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_SET(x)   (((x) << MBOX_DMA_POLICY_RXD_16BIT_SWAP_LSB) & MBOX_DMA_POLICY_RXD_16BIT_SWAP_MASK)
#define MBOX_DMA_POLICY_RXD_16BIT_SWAP_RESET    0x0 // 0
#define MBOX_DMA_POLICY_TXD_END_SWAP_MSB        9
#define MBOX_DMA_POLICY_TXD_END_SWAP_LSB        9
#define MBOX_DMA_POLICY_TXD_END_SWAP_MASK       0x00000200
#define MBOX_DMA_POLICY_TXD_END_SWAP_GET(x)     (((x) & MBOX_DMA_POLICY_TXD_END_SWAP_MASK) >> MBOX_DMA_POLICY_TXD_END_SWAP_LSB)
#define MBOX_DMA_POLICY_TXD_END_SWAP_SET(x)     (((x) << MBOX_DMA_POLICY_TXD_END_SWAP_LSB) & MBOX_DMA_POLICY_TXD_END_SWAP_MASK)
#define MBOX_DMA_POLICY_TXD_END_SWAP_RESET      0x0 // 0
#define MBOX_DMA_POLICY_RXD_END_SWAP_MSB        8
#define MBOX_DMA_POLICY_RXD_END_SWAP_LSB        8
#define MBOX_DMA_POLICY_RXD_END_SWAP_MASK       0x00000100
#define MBOX_DMA_POLICY_RXD_END_SWAP_GET(x)     (((x) & MBOX_DMA_POLICY_RXD_END_SWAP_MASK) >> MBOX_DMA_POLICY_RXD_END_SWAP_LSB)
#define MBOX_DMA_POLICY_RXD_END_SWAP_SET(x)     (((x) << MBOX_DMA_POLICY_RXD_END_SWAP_LSB) & MBOX_DMA_POLICY_RXD_END_SWAP_MASK)
#define MBOX_DMA_POLICY_RXD_END_SWAP_RESET      0x0 // 0

#define MBOX_DMA_PAUSE				0x1
#define MBOX_DMA_START				0x2
#define MBOX_DMA_RESUME				0x4

#define MBOX_DMA_POLICY_RX_QUANTUM		(1<< 1)
#define MBOX_DMA_POLICY_TX_QUANTUM		(1<< 3)
#define MBOX_DMA_POLICY_TX_FIFO_THRESH(x)	((0xff&x)<< 4)
#define MBOX_DMA_POLICY_SRAM_AC			(1<<12)

#define MBOX_SLIC_RX_DMA_COMPLETE		(1 << 6)
#define MBOX_SLIC_TX_DMA_COMPLETE		(1 << 4)
#define MBOX_SLIC_TX_NOT_EMPTY			(1 << 1)
#define MBOX_SLIC_RX_UNDERFLOW			(1 << 2)
#define MBOX_SLIC_RX_NOT_FULL			(1 << 0)
#define MBOX_SLIC_TX_OVERFLOW			(1 << 3)

#define MBOX_RX_DMA_COMPLETE			(1 << 10)
#define MBOX_TX_DMA_EOM_COMPLETE		(1 << 8)
#define MBOX_TX_DMA_COMPLETE			(1 << 6)
#define MBOX_TX_OVERFLOW			(1 << 5)
#define MBOX_RX_UNDERFLOW			(1 << 4)
#define MBOX_TX_NOT_EMPTY			(1 << 2)
#define MBOX_SLIC_FIFO_RESET_RX_INIT		(1 << 1)
#define MBOX_SLIC_FIFO_STATUS_EMPTY		(1 << 1)
#define MBOX_SLIC_FRAME_RX_SOM			(1 << 0)
#define MBOX_RX_NOT_FULL			(1 << 0)
#define MBOX_SLIC_FIFO_RESET_TX_INIT		(1 << 0)
#define MBOX_SLIC_FIFO_STATUS_FULL		(1 << 0)

#define SLIC_SLOT				0x180a9000
#define SLIC_CLOCK_CTRL				0x180a9004
#define SLIC_CTRL				0x180a9008
#define SLIC_TX_SLOTS1				0x180a900c
#define SLIC_TX_SLOTS2				0x180a9010
#define SLIC_RX_SLOTS1				0x180a9014
#define SLIC_RX_SLOTS2				0x180a9018
#define SLIC_TIMING_CTRL			0x180a901c
#define SLIC_INTR				0x180a9020
#define SLIC_SWAP				0x180a9024
#define SLIC_PWM_CTL				0x180a9028
#define SLIC_PWM_DATA				0x180a9030

#define SLIC_CNTRL_ENABLE			(1<<0)
#define SLIC_CNTRL_SLOT0_ENABLE			(1<<1)
#define SLIC_CNTRL_SLOT1_ENABLE			(1<<2)
#define SLIC_CNTRL_IRQ_ENABLE			(1<<3)

#define SLIC_SLOT_SEL(x)                            (0x7f&x)
#define SLIC_CLOCK_CTRL_DIV(x)                      (0x3f&x)
#define SLIC_CTRL_CLK_EN                            (1<<3)
#define SLIC_CTRL_MASTER                            (1<<2)
#define SLIC_CTRL_SLAVE                             (0<<2)
#define SLIC_CTRL_EN                                (1<<1)

#define SLIC_CTRL_PLL_SOURCE_SEL_MSB                                 5
#define SLIC_CTRL_PLL_SOURCE_SEL_LSB                                 4
#define SLIC_CTRL_PLL_SOURCE_SEL_MASK                                0x00000030
#define SLIC_CTRL_PLL_SOURCE_SEL_GET(x)                              (((x) & SLIC_CTRL_PLL_SOURCE_SEL_MASK) >> SLIC_CTRL_PLL_SOURCE_SEL_LSB)
#define SLIC_CTRL_PLL_SOURCE_SEL_SET(x)                              (((x) << SLIC_CTRL_PLL_SOURCE_SEL_LSB) & SLIC_CTRL_PLL_SOURCE_SEL_MASK)
#define SLIC_CTRL_PLL_SOURCE_SEL_RESET                               0x0 // 0

#define SLIC_TX_SLOTS1_EN(x)                        (x)
#define SLIC_TX_SLOTS2_EN(x)                        (x)
#define SLIC_RX_SLOTS1_EN(x)                        (x)
#define SLIC_RX_SLOTS2_EN(x)                        (x)
#define SLIC_TIMING_CTRL_RXDATA_SAMPLE_POS_EXTEND(x)((0x3&x)<<11)
#define SLIC_TIMING_CTRL_TXDATA_FS_SYNC_EXTEND      (1<<10)
#define SLIC_TIMING_CTRL_DATAOEN_ALWAYS             (1<<9)
#define SLIC_TIMING_CTRL_RXDATA_SAMPLE_POS(x)       ((0x3&x)<<7)
#define SLIC_TIMING_CTRL_TXDATA_FS_SYNC(x)          ((0x3&x)<<5)
#define SLIC_TIMING_CTRL_LONG_FSCLKS(x)             ((0x7&x)<<2)
#define SLIC_TIMING_CTRL_FS_POS                     (1<<1)
#define SLIC_TIMING_CTRL_LONG_FS                    (1<<0)
#define SLIC_INTR_MASK(x)                           (0x1f&x)
#define SLIC_SWAP_RX_DATA                           (1<<1)
#define SLIC_SWAP_TX_DATA                           (1<<0)

#define MAC_CONFIGURATION_1_SOFT_RESET_MSB                           31
#define MAC_CONFIGURATION_1_SOFT_RESET_LSB                           31
#define MAC_CONFIGURATION_1_SOFT_RESET_MASK                          0x80000000
#define MAC_CONFIGURATION_1_SOFT_RESET_GET(x)                        (((x) & MAC_CONFIGURATION_1_SOFT_RESET_MASK) >> MAC_CONFIGURATION_1_SOFT_RESET_LSB)
#define MAC_CONFIGURATION_1_SOFT_RESET_SET(x)                        (((x) << MAC_CONFIGURATION_1_SOFT_RESET_LSB) & MAC_CONFIGURATION_1_SOFT_RESET_MASK)
#define MAC_CONFIGURATION_1_SOFT_RESET_RESET                         0x1 // 1
#define MAC_CONFIGURATION_1_SIM_RESET_MSB                            30
#define MAC_CONFIGURATION_1_SIM_RESET_LSB                            30
#define MAC_CONFIGURATION_1_SIM_RESET_MASK                           0x40000000
#define MAC_CONFIGURATION_1_SIM_RESET_GET(x)                         (((x) & MAC_CONFIGURATION_1_SIM_RESET_MASK) >> MAC_CONFIGURATION_1_SIM_RESET_LSB)
#define MAC_CONFIGURATION_1_SIM_RESET_SET(x)                         (((x) << MAC_CONFIGURATION_1_SIM_RESET_LSB) & MAC_CONFIGURATION_1_SIM_RESET_MASK)
#define MAC_CONFIGURATION_1_SIM_RESET_RESET                          0x0 // 0
#define MAC_CONFIGURATION_1_RESET_RX_MAC_MSB                         19
#define MAC_CONFIGURATION_1_RESET_RX_MAC_LSB                         19
#define MAC_CONFIGURATION_1_RESET_RX_MAC_MASK                        0x00080000
#define MAC_CONFIGURATION_1_RESET_RX_MAC_GET(x)                      (((x) & MAC_CONFIGURATION_1_RESET_RX_MAC_MASK) >> MAC_CONFIGURATION_1_RESET_RX_MAC_LSB)
#define MAC_CONFIGURATION_1_RESET_RX_MAC_SET(x)                      (((x) << MAC_CONFIGURATION_1_RESET_RX_MAC_LSB) & MAC_CONFIGURATION_1_RESET_RX_MAC_MASK)
#define MAC_CONFIGURATION_1_RESET_RX_MAC_RESET                       0x0 // 0
#define MAC_CONFIGURATION_1_RESET_TX_MAC_MSB                         18
#define MAC_CONFIGURATION_1_RESET_TX_MAC_LSB                         18
#define MAC_CONFIGURATION_1_RESET_TX_MAC_MASK                        0x00040000
#define MAC_CONFIGURATION_1_RESET_TX_MAC_GET(x)                      (((x) & MAC_CONFIGURATION_1_RESET_TX_MAC_MASK) >> MAC_CONFIGURATION_1_RESET_TX_MAC_LSB)
#define MAC_CONFIGURATION_1_RESET_TX_MAC_SET(x)                      (((x) << MAC_CONFIGURATION_1_RESET_TX_MAC_LSB) & MAC_CONFIGURATION_1_RESET_TX_MAC_MASK)
#define MAC_CONFIGURATION_1_RESET_TX_MAC_RESET                       0x0 // 0
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_MSB                        17
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_LSB                        17
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_MASK                       0x00020000
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_GET(x)                     (((x) & MAC_CONFIGURATION_1_RESET_RX_FUNC_MASK) >> MAC_CONFIGURATION_1_RESET_RX_FUNC_LSB)
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_SET(x)                     (((x) << MAC_CONFIGURATION_1_RESET_RX_FUNC_LSB) & MAC_CONFIGURATION_1_RESET_RX_FUNC_MASK)
#define MAC_CONFIGURATION_1_RESET_RX_FUNC_RESET                      0x0 // 0
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_MSB                        16
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_LSB                        16
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_MASK                       0x00010000
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_GET(x)                     (((x) & MAC_CONFIGURATION_1_RESET_TX_FUNC_MASK) >> MAC_CONFIGURATION_1_RESET_TX_FUNC_LSB)
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_SET(x)                     (((x) << MAC_CONFIGURATION_1_RESET_TX_FUNC_LSB) & MAC_CONFIGURATION_1_RESET_TX_FUNC_MASK)
#define MAC_CONFIGURATION_1_RESET_TX_FUNC_RESET                      0x0 // 0
#define MAC_CONFIGURATION_1_LOOP_BACK_MSB                            8
#define MAC_CONFIGURATION_1_LOOP_BACK_LSB                            8
#define MAC_CONFIGURATION_1_LOOP_BACK_MASK                           0x00000100
#define MAC_CONFIGURATION_1_LOOP_BACK_GET(x)                         (((x) & MAC_CONFIGURATION_1_LOOP_BACK_MASK) >> MAC_CONFIGURATION_1_LOOP_BACK_LSB)
#define MAC_CONFIGURATION_1_LOOP_BACK_SET(x)                         (((x) << MAC_CONFIGURATION_1_LOOP_BACK_LSB) & MAC_CONFIGURATION_1_LOOP_BACK_MASK)
#define MAC_CONFIGURATION_1_LOOP_BACK_RESET                          0x0 // 0
#define MAC_CONFIGURATION_1_RX_FLOW_MSB                              5
#define MAC_CONFIGURATION_1_RX_FLOW_LSB                              5
#define MAC_CONFIGURATION_1_RX_FLOW_MASK                             0x00000020
#define MAC_CONFIGURATION_1_RX_FLOW_GET(x)                           (((x) & MAC_CONFIGURATION_1_RX_FLOW_MASK) >> MAC_CONFIGURATION_1_RX_FLOW_LSB)
#define MAC_CONFIGURATION_1_RX_FLOW_SET(x)                           (((x) << MAC_CONFIGURATION_1_RX_FLOW_LSB) & MAC_CONFIGURATION_1_RX_FLOW_MASK)
#define MAC_CONFIGURATION_1_RX_FLOW_RESET                            0x0 // 0
#define MAC_CONFIGURATION_1_TX_FLOW_MSB                              4
#define MAC_CONFIGURATION_1_TX_FLOW_LSB                              4
#define MAC_CONFIGURATION_1_TX_FLOW_MASK                             0x00000010
#define MAC_CONFIGURATION_1_TX_FLOW_GET(x)                           (((x) & MAC_CONFIGURATION_1_TX_FLOW_MASK) >> MAC_CONFIGURATION_1_TX_FLOW_LSB)
#define MAC_CONFIGURATION_1_TX_FLOW_SET(x)                           (((x) << MAC_CONFIGURATION_1_TX_FLOW_LSB) & MAC_CONFIGURATION_1_TX_FLOW_MASK)
#define MAC_CONFIGURATION_1_TX_FLOW_RESET                            0x0 // 0
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_MSB                         3
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_LSB                         3
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_MASK                        0x00000008
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_GET(x)                      (((x) & MAC_CONFIGURATION_1_SYNCED_RX_EN_MASK) >> MAC_CONFIGURATION_1_SYNCED_RX_EN_LSB)
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_SET(x)                      (((x) << MAC_CONFIGURATION_1_SYNCED_RX_EN_LSB) & MAC_CONFIGURATION_1_SYNCED_RX_EN_MASK)
#define MAC_CONFIGURATION_1_SYNCED_RX_EN_RESET                       0x0 // 0
#define MAC_CONFIGURATION_1_RX_ENABLE_MSB                            2
#define MAC_CONFIGURATION_1_RX_ENABLE_LSB                            2
#define MAC_CONFIGURATION_1_RX_ENABLE_MASK                           0x00000004
#define MAC_CONFIGURATION_1_RX_ENABLE_GET(x)                         (((x) & MAC_CONFIGURATION_1_RX_ENABLE_MASK) >> MAC_CONFIGURATION_1_RX_ENABLE_LSB)
#define MAC_CONFIGURATION_1_RX_ENABLE_SET(x)                         (((x) << MAC_CONFIGURATION_1_RX_ENABLE_LSB) & MAC_CONFIGURATION_1_RX_ENABLE_MASK)
#define MAC_CONFIGURATION_1_RX_ENABLE_RESET                          0x0 // 0
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_MSB                         1
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_LSB                         1
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_MASK                        0x00000002
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_GET(x)                      (((x) & MAC_CONFIGURATION_1_SYNCED_TX_EN_MASK) >> MAC_CONFIGURATION_1_SYNCED_TX_EN_LSB)
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_SET(x)                      (((x) << MAC_CONFIGURATION_1_SYNCED_TX_EN_LSB) & MAC_CONFIGURATION_1_SYNCED_TX_EN_MASK)
#define MAC_CONFIGURATION_1_SYNCED_TX_EN_RESET                       0x0 // 0
#define MAC_CONFIGURATION_1_TX_ENABLE_MSB                            0
#define MAC_CONFIGURATION_1_TX_ENABLE_LSB                            0
#define MAC_CONFIGURATION_1_TX_ENABLE_MASK                           0x00000001
#define MAC_CONFIGURATION_1_TX_ENABLE_GET(x)                         (((x) & MAC_CONFIGURATION_1_TX_ENABLE_MASK) >> MAC_CONFIGURATION_1_TX_ENABLE_LSB)
#define MAC_CONFIGURATION_1_TX_ENABLE_SET(x)                         (((x) << MAC_CONFIGURATION_1_TX_ENABLE_LSB) & MAC_CONFIGURATION_1_TX_ENABLE_MASK)
#define MAC_CONFIGURATION_1_TX_ENABLE_RESET                          0x0 // 0
#define MAC_CONFIGURATION_1_ADDRESS                                  0x0000
#define MAC_CONFIGURATION_1_SW_MASK                                  0xc00f013f
#define MAC_CONFIGURATION_1_RSTMASK                                  0xffffffff
#define MAC_CONFIGURATION_1_RESET                                    0x80000000

#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_MSB                      15
#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_LSB                      12
#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_MASK                     0x0000f000
#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_GET(x)                   (((x) & MAC_CONFIGURATION_2_PREAMBLE_LENGTH_MASK) >> MAC_CONFIGURATION_2_PREAMBLE_LENGTH_LSB)
#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_SET(x)                   (((x) << MAC_CONFIGURATION_2_PREAMBLE_LENGTH_LSB) & MAC_CONFIGURATION_2_PREAMBLE_LENGTH_MASK)
#define MAC_CONFIGURATION_2_PREAMBLE_LENGTH_RESET                    0x7 // 7
#define MAC_CONFIGURATION_2_IF_MODE_MSB                              9
#define MAC_CONFIGURATION_2_IF_MODE_LSB                              8
#define MAC_CONFIGURATION_2_IF_MODE_MASK                             0x00000300
#define MAC_CONFIGURATION_2_IF_MODE_GET(x)                           (((x) & MAC_CONFIGURATION_2_IF_MODE_MASK) >> MAC_CONFIGURATION_2_IF_MODE_LSB)
#define MAC_CONFIGURATION_2_IF_MODE_SET(x)                           (((x) << MAC_CONFIGURATION_2_IF_MODE_LSB) & MAC_CONFIGURATION_2_IF_MODE_MASK)
#define MAC_CONFIGURATION_2_IF_MODE_RESET                            0x0 // 0
#define MAC_CONFIGURATION_2_HUGE_FRAME_MSB                           5
#define MAC_CONFIGURATION_2_HUGE_FRAME_LSB                           5
#define MAC_CONFIGURATION_2_HUGE_FRAME_MASK                          0x00000020
#define MAC_CONFIGURATION_2_HUGE_FRAME_GET(x)                        (((x) & MAC_CONFIGURATION_2_HUGE_FRAME_MASK) >> MAC_CONFIGURATION_2_HUGE_FRAME_LSB)
#define MAC_CONFIGURATION_2_HUGE_FRAME_SET(x)                        (((x) << MAC_CONFIGURATION_2_HUGE_FRAME_LSB) & MAC_CONFIGURATION_2_HUGE_FRAME_MASK)
#define MAC_CONFIGURATION_2_HUGE_FRAME_RESET                         0x0 // 0
#define MAC_CONFIGURATION_2_LENGTH_CHECK_MSB                         4
#define MAC_CONFIGURATION_2_LENGTH_CHECK_LSB                         4
#define MAC_CONFIGURATION_2_LENGTH_CHECK_MASK                        0x00000010
#define MAC_CONFIGURATION_2_LENGTH_CHECK_GET(x)                      (((x) & MAC_CONFIGURATION_2_LENGTH_CHECK_MASK) >> MAC_CONFIGURATION_2_LENGTH_CHECK_LSB)
#define MAC_CONFIGURATION_2_LENGTH_CHECK_SET(x)                      (((x) << MAC_CONFIGURATION_2_LENGTH_CHECK_LSB) & MAC_CONFIGURATION_2_LENGTH_CHECK_MASK)
#define MAC_CONFIGURATION_2_LENGTH_CHECK_RESET                       0x0 // 0
#define MAC_CONFIGURATION_2_PAD_CRC_MSB                              2
#define MAC_CONFIGURATION_2_PAD_CRC_LSB                              2
#define MAC_CONFIGURATION_2_PAD_CRC_MASK                             0x00000004
#define MAC_CONFIGURATION_2_PAD_CRC_GET(x)                           (((x) & MAC_CONFIGURATION_2_PAD_CRC_MASK) >> MAC_CONFIGURATION_2_PAD_CRC_LSB)
#define MAC_CONFIGURATION_2_PAD_CRC_SET(x)                           (((x) << MAC_CONFIGURATION_2_PAD_CRC_LSB) & MAC_CONFIGURATION_2_PAD_CRC_MASK)
#define MAC_CONFIGURATION_2_PAD_CRC_RESET                            0x0 // 0
#define MAC_CONFIGURATION_2_CRC_ENABLE_MSB                           1
#define MAC_CONFIGURATION_2_CRC_ENABLE_LSB                           1
#define MAC_CONFIGURATION_2_CRC_ENABLE_MASK                          0x00000002
#define MAC_CONFIGURATION_2_CRC_ENABLE_GET(x)                        (((x) & MAC_CONFIGURATION_2_CRC_ENABLE_MASK) >> MAC_CONFIGURATION_2_CRC_ENABLE_LSB)
#define MAC_CONFIGURATION_2_CRC_ENABLE_SET(x)                        (((x) << MAC_CONFIGURATION_2_CRC_ENABLE_LSB) & MAC_CONFIGURATION_2_CRC_ENABLE_MASK)
#define MAC_CONFIGURATION_2_CRC_ENABLE_RESET                         0x0 // 0
#define MAC_CONFIGURATION_2_FULL_DUPLEX_MSB                          0
#define MAC_CONFIGURATION_2_FULL_DUPLEX_LSB                          0
#define MAC_CONFIGURATION_2_FULL_DUPLEX_MASK                         0x00000001
#define MAC_CONFIGURATION_2_FULL_DUPLEX_GET(x)                       (((x) & MAC_CONFIGURATION_2_FULL_DUPLEX_MASK) >> MAC_CONFIGURATION_2_FULL_DUPLEX_LSB)
#define MAC_CONFIGURATION_2_FULL_DUPLEX_SET(x)                       (((x) << MAC_CONFIGURATION_2_FULL_DUPLEX_LSB) & MAC_CONFIGURATION_2_FULL_DUPLEX_MASK)
#define MAC_CONFIGURATION_2_FULL_DUPLEX_RESET                        0x0 // 0
#define MAC_CONFIGURATION_2_ADDRESS                                  0x0004
#define MAC_CONFIGURATION_2_SW_MASK                                  0x0000f337
#define MAC_CONFIGURATION_2_RSTMASK                                  0xffffffff
#define MAC_CONFIGURATION_2_RESET                                    0x00007000

#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_MSB                       15
#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_LSB                       0
#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_MASK                      0x0000ffff
#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_GET(x)                    (((x) & MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_MASK) >> MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_LSB)
#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_SET(x)                    (((x) << MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_LSB) & MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_MASK)
#define MAXIMUM_FRAME_LENGTH_MAXIMUM_FRAME_RESET                     0x600 // 1536
#define MAXIMUM_FRAME_LENGTH_ADDRESS                                 0x0010

#define MII_MGMT_CONFIGURATION_RESET_MGMT_MSB                        31
#define MII_MGMT_CONFIGURATION_RESET_MGMT_LSB                        31
#define MII_MGMT_CONFIGURATION_RESET_MGMT_MASK                       0x80000000
#define MII_MGMT_CONFIGURATION_RESET_MGMT_GET(x)                     (((x) & MII_MGMT_CONFIGURATION_RESET_MGMT_MASK) >> MII_MGMT_CONFIGURATION_RESET_MGMT_LSB)
#define MII_MGMT_CONFIGURATION_RESET_MGMT_SET(x)                     (((x) << MII_MGMT_CONFIGURATION_RESET_MGMT_LSB) & MII_MGMT_CONFIGURATION_RESET_MGMT_MASK)
#define MII_MGMT_CONFIGURATION_RESET_MGMT_RESET                      0x0 // 0
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_MSB                         5
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_LSB                         5
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_MASK                        0x00000020
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_GET(x)                      (((x) & MII_MGMT_CONFIGURATION_SCAN_AUTO_MASK) >> MII_MGMT_CONFIGURATION_SCAN_AUTO_LSB)
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_SET(x)                      (((x) << MII_MGMT_CONFIGURATION_SCAN_AUTO_LSB) & MII_MGMT_CONFIGURATION_SCAN_AUTO_MASK)
#define MII_MGMT_CONFIGURATION_SCAN_AUTO_RESET                       0x0 // 0
#define MII_MGMT_CONFIGURATION_NO_PRE_MSB                            4
#define MII_MGMT_CONFIGURATION_NO_PRE_LSB                            4
#define MII_MGMT_CONFIGURATION_NO_PRE_MASK                           0x00000010
#define MII_MGMT_CONFIGURATION_NO_PRE_GET(x)                         (((x) & MII_MGMT_CONFIGURATION_NO_PRE_MASK) >> MII_MGMT_CONFIGURATION_NO_PRE_LSB)
#define MII_MGMT_CONFIGURATION_NO_PRE_SET(x)                         (((x) << MII_MGMT_CONFIGURATION_NO_PRE_LSB) & MII_MGMT_CONFIGURATION_NO_PRE_MASK)
#define MII_MGMT_CONFIGURATION_NO_PRE_RESET                          0x0 // 0
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_MSB                 3
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_LSB                 0
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_MASK                0x0000000f
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_GET(x)              (((x) & MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_MASK) >> MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_LSB)
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_SET(x)              (((x) << MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_LSB) & MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_MASK)
#define MII_MGMT_CONFIGURATION_MGMT_CLOCK_SELECT_RESET               0x0 // 0
#define MII_MGMT_CONFIGURATION_ADDRESS                               0x0020

#define INTERFACE_CONTROL_UMWOLEN_MSB                                13
#define INTERFACE_CONTROL_UMWOLEN_LSB                                13
#define INTERFACE_CONTROL_UMWOLEN_MASK                               0x00002000
#define INTERFACE_CONTROL_UMWOLEN_GET(x)                             (((x) & INTERFACE_CONTROL_UMWOLEN_MASK) >> INTERFACE_CONTROL_UMWOLEN_LSB)
#define INTERFACE_CONTROL_UMWOLEN_SET(x)                             (((x) << INTERFACE_CONTROL_UMWOLEN_LSB) & INTERFACE_CONTROL_UMWOLEN_MASK)
#define INTERFACE_CONTROL_UMWOLEN_RESET                              0x0 // 0
#define INTERFACE_CONTROL_MPWOLEN_MSB                                12
#define INTERFACE_CONTROL_MPWOLEN_LSB                                12
#define INTERFACE_CONTROL_MPWOLEN_MASK                               0x00001000
#define INTERFACE_CONTROL_MPWOLEN_GET(x)                             (((x) & INTERFACE_CONTROL_MPWOLEN_MASK) >> INTERFACE_CONTROL_MPWOLEN_LSB)
#define INTERFACE_CONTROL_MPWOLEN_SET(x)                             (((x) << INTERFACE_CONTROL_MPWOLEN_LSB) & INTERFACE_CONTROL_MPWOLEN_MASK)
#define INTERFACE_CONTROL_MPWOLEN_RESET                              0x0 // 0
#define INTERFACE_CONTROL_WOLDTCTDCLR_MSB                            11
#define INTERFACE_CONTROL_WOLDTCTDCLR_LSB                            11
#define INTERFACE_CONTROL_WOLDTCTDCLR_MASK                           0x00000800
#define INTERFACE_CONTROL_WOLDTCTDCLR_GET(x)                         (((x) & INTERFACE_CONTROL_WOLDTCTDCLR_MASK) >> INTERFACE_CONTROL_WOLDTCTDCLR_LSB)
#define INTERFACE_CONTROL_WOLDTCTDCLR_SET(x)                         (((x) << INTERFACE_CONTROL_WOLDTCTDCLR_LSB) & INTERFACE_CONTROL_WOLDTCTDCLR_MASK)
#define INTERFACE_CONTROL_WOLDTCTDCLR_RESET                          0x0 // 0
#define INTERFACE_CONTROL_ADDRESS                                    0x0038

#define ETH_CFG_0_FTFENRPLY_MSB                                  20
#define ETH_CFG_0_FTFENRPLY_LSB                                  20
#define ETH_CFG_0_FTFENRPLY_MASK                                 0x00100000
#define ETH_CFG_0_FTFENRPLY_GET(x)                               (((x) & ETH_CFG_0_FTFENRPLY_MASK) >> ETH_CFG_0_FTFENRPLY_LSB)
#define ETH_CFG_0_FTFENRPLY_SET(x)                               (((x) << ETH_CFG_0_FTFENRPLY_LSB) & ETH_CFG_0_FTFENRPLY_MASK)
#define ETH_CFG_0_FTFENRPLY_RESET                                0x0 // 0
#define ETH_CFG_0_STFENRPLY_MSB                                  19
#define ETH_CFG_0_STFENRPLY_LSB                                  19
#define ETH_CFG_0_STFENRPLY_MASK                                 0x00080000
#define ETH_CFG_0_STFENRPLY_GET(x)                               (((x) & ETH_CFG_0_STFENRPLY_MASK) >> ETH_CFG_0_STFENRPLY_LSB)
#define ETH_CFG_0_STFENRPLY_SET(x)                               (((x) << ETH_CFG_0_STFENRPLY_LSB) & ETH_CFG_0_STFENRPLY_MASK)
#define ETH_CFG_0_STFENRPLY_RESET                                0x0 // 0
#define ETH_CFG_0_FRFENRPLY_MSB                                  18
#define ETH_CFG_0_FRFENRPLY_LSB                                  18
#define ETH_CFG_0_FRFENRPLY_MASK                                 0x00040000
#define ETH_CFG_0_FRFENRPLY_GET(x)                               (((x) & ETH_CFG_0_FRFENRPLY_MASK) >> ETH_CFG_0_FRFENRPLY_LSB)
#define ETH_CFG_0_FRFENRPLY_SET(x)                               (((x) << ETH_CFG_0_FRFENRPLY_LSB) & ETH_CFG_0_FRFENRPLY_MASK)
#define ETH_CFG_0_FRFENRPLY_RESET                                0x0 // 0
#define ETH_CFG_0_SRFENRPLY_MSB                                  17
#define ETH_CFG_0_SRFENRPLY_LSB                                  17
#define ETH_CFG_0_SRFENRPLY_MASK                                 0x00020000
#define ETH_CFG_0_SRFENRPLY_GET(x)                               (((x) & ETH_CFG_0_SRFENRPLY_MASK) >> ETH_CFG_0_SRFENRPLY_LSB)
#define ETH_CFG_0_SRFENRPLY_SET(x)                               (((x) << ETH_CFG_0_SRFENRPLY_LSB) & ETH_CFG_0_SRFENRPLY_MASK)
#define ETH_CFG_0_SRFENRPLY_RESET                                0x0 // 0
#define ETH_CFG_0_WTMENRPLY_MSB                                  16
#define ETH_CFG_0_WTMENRPLY_LSB                                  16
#define ETH_CFG_0_WTMENRPLY_MASK                                 0x00010000
#define ETH_CFG_0_WTMENRPLY_GET(x)                               (((x) & ETH_CFG_0_WTMENRPLY_MASK) >> ETH_CFG_0_WTMENRPLY_LSB)
#define ETH_CFG_0_WTMENRPLY_SET(x)                               (((x) << ETH_CFG_0_WTMENRPLY_LSB) & ETH_CFG_0_WTMENRPLY_MASK)
#define ETH_CFG_0_WTMENRPLY_RESET                                0x0 // 0
#define ETH_CFG_0_FTFENREQ_MSB                                   12
#define ETH_CFG_0_FTFENREQ_LSB                                   12
#define ETH_CFG_0_FTFENREQ_MASK                                  0x00001000
#define ETH_CFG_0_FTFENREQ_GET(x)                                (((x) & ETH_CFG_0_FTFENREQ_MASK) >> ETH_CFG_0_FTFENREQ_LSB)
#define ETH_CFG_0_FTFENREQ_SET(x)                                (((x) << ETH_CFG_0_FTFENREQ_LSB) & ETH_CFG_0_FTFENREQ_MASK)
#define ETH_CFG_0_FTFENREQ_RESET                                 0x0 // 0
#define ETH_CFG_0_STFENREQ_MSB                                   11
#define ETH_CFG_0_STFENREQ_LSB                                   11
#define ETH_CFG_0_STFENREQ_MASK                                  0x00000800
#define ETH_CFG_0_STFENREQ_GET(x)                                (((x) & ETH_CFG_0_STFENREQ_MASK) >> ETH_CFG_0_STFENREQ_LSB)
#define ETH_CFG_0_STFENREQ_SET(x)                                (((x) << ETH_CFG_0_STFENREQ_LSB) & ETH_CFG_0_STFENREQ_MASK)
#define ETH_CFG_0_STFENREQ_RESET                                 0x0 // 0
#define ETH_CFG_0_FRFENREQ_MSB                                   10
#define ETH_CFG_0_FRFENREQ_LSB                                   10
#define ETH_CFG_0_FRFENREQ_MASK                                  0x00000400
#define ETH_CFG_0_FRFENREQ_GET(x)                                (((x) & ETH_CFG_0_FRFENREQ_MASK) >> ETH_CFG_0_FRFENREQ_LSB)
#define ETH_CFG_0_FRFENREQ_SET(x)                                (((x) << ETH_CFG_0_FRFENREQ_LSB) & ETH_CFG_0_FRFENREQ_MASK)
#define ETH_CFG_0_FRFENREQ_RESET                                 0x0 // 0
#define ETH_CFG_0_SRFENREQ_MSB                                   9
#define ETH_CFG_0_SRFENREQ_LSB                                   9
#define ETH_CFG_0_SRFENREQ_MASK                                  0x00000200
#define ETH_CFG_0_SRFENREQ_GET(x)                                (((x) & ETH_CFG_0_SRFENREQ_MASK) >> ETH_CFG_0_SRFENREQ_LSB)
#define ETH_CFG_0_SRFENREQ_SET(x)                                (((x) << ETH_CFG_0_SRFENREQ_LSB) & ETH_CFG_0_SRFENREQ_MASK)
#define ETH_CFG_0_SRFENREQ_RESET                                 0x0 // 0
#define ETH_CFG_0_WTMENREQ_MSB                                   8
#define ETH_CFG_0_WTMENREQ_LSB                                   8
#define ETH_CFG_0_WTMENREQ_MASK                                  0x00000100
#define ETH_CFG_0_WTMENREQ_GET(x)                                (((x) & ETH_CFG_0_WTMENREQ_MASK) >> ETH_CFG_0_WTMENREQ_LSB)
#define ETH_CFG_0_WTMENREQ_SET(x)                                (((x) << ETH_CFG_0_WTMENREQ_LSB) & ETH_CFG_0_WTMENREQ_MASK)
#define ETH_CFG_0_WTMENREQ_RESET                                 0x0 // 0
#define ETH_CFG_0_HSTRSTFT_MSB                                   4
#define ETH_CFG_0_HSTRSTFT_LSB                                   4
#define ETH_CFG_0_HSTRSTFT_MASK                                  0x00000010
#define ETH_CFG_0_HSTRSTFT_GET(x)                                (((x) & ETH_CFG_0_HSTRSTFT_MASK) >> ETH_CFG_0_HSTRSTFT_LSB)
#define ETH_CFG_0_HSTRSTFT_SET(x)                                (((x) << ETH_CFG_0_HSTRSTFT_LSB) & ETH_CFG_0_HSTRSTFT_MASK)
#define ETH_CFG_0_HSTRSTFT_RESET                                 0x0 // 0
#define ETH_CFG_0_HSTRSTST_MSB                                   3
#define ETH_CFG_0_HSTRSTST_LSB                                   3
#define ETH_CFG_0_HSTRSTST_MASK                                  0x00000008
#define ETH_CFG_0_HSTRSTST_GET(x)                                (((x) & ETH_CFG_0_HSTRSTST_MASK) >> ETH_CFG_0_HSTRSTST_LSB)
#define ETH_CFG_0_HSTRSTST_SET(x)                                (((x) << ETH_CFG_0_HSTRSTST_LSB) & ETH_CFG_0_HSTRSTST_MASK)
#define ETH_CFG_0_HSTRSTST_RESET                                 0x0 // 0
#define ETH_CFG_0_HSTRSTFR_MSB                                   2
#define ETH_CFG_0_HSTRSTFR_LSB                                   2
#define ETH_CFG_0_HSTRSTFR_MASK                                  0x00000004
#define ETH_CFG_0_HSTRSTFR_GET(x)                                (((x) & ETH_CFG_0_HSTRSTFR_MASK) >> ETH_CFG_0_HSTRSTFR_LSB)
#define ETH_CFG_0_HSTRSTFR_SET(x)                                (((x) << ETH_CFG_0_HSTRSTFR_LSB) & ETH_CFG_0_HSTRSTFR_MASK)
#define ETH_CFG_0_HSTRSTFR_RESET                                 0x0 // 0
#define ETH_CFG_0_HSTRSTSR_MSB                                   1
#define ETH_CFG_0_HSTRSTSR_LSB                                   1
#define ETH_CFG_0_HSTRSTSR_MASK                                  0x00000002
#define ETH_CFG_0_HSTRSTSR_GET(x)                                (((x) & ETH_CFG_0_HSTRSTSR_MASK) >> ETH_CFG_0_HSTRSTSR_LSB)
#define ETH_CFG_0_HSTRSTSR_SET(x)                                (((x) << ETH_CFG_0_HSTRSTSR_LSB) & ETH_CFG_0_HSTRSTSR_MASK)
#define ETH_CFG_0_HSTRSTSR_RESET                                 0x0 // 0
#define ETH_CFG_0_HSTRSTWT_MSB                                   0
#define ETH_CFG_0_HSTRSTWT_LSB                                   0
#define ETH_CFG_0_HSTRSTWT_MASK                                  0x00000001
#define ETH_CFG_0_HSTRSTWT_GET(x)                                (((x) & ETH_CFG_0_HSTRSTWT_MASK) >> ETH_CFG_0_HSTRSTWT_LSB)
#define ETH_CFG_0_HSTRSTWT_SET(x)                                (((x) << ETH_CFG_0_HSTRSTWT_LSB) & ETH_CFG_0_HSTRSTWT_MASK)
#define ETH_CFG_0_HSTRSTWT_RESET                                 0x0 // 0
#define ETH_CFG_0_ADDRESS                                        0x0048

#define ETH_CFG_1_CFGFRTH_MSB                                    25
#define ETH_CFG_1_CFGFRTH_LSB                                    16
#define ETH_CFG_1_CFGFRTH_MASK                                   0x03ff0000
#define ETH_CFG_1_CFGFRTH_GET(x)                                 (((x) & ETH_CFG_1_CFGFRTH_MASK) >> ETH_CFG_1_CFGFRTH_LSB)
#define ETH_CFG_1_CFGFRTH_SET(x)                                 (((x) << ETH_CFG_1_CFGFRTH_LSB) & ETH_CFG_1_CFGFRTH_MASK)
#define ETH_CFG_1_CFGFRTH_RESET                                  0x3ff // 1023
#define ETH_CFG_1_CFGXOFFRTX_MSB                                 15
#define ETH_CFG_1_CFGXOFFRTX_LSB                                 0
#define ETH_CFG_1_CFGXOFFRTX_MASK                                0x0000ffff
#define ETH_CFG_1_CFGXOFFRTX_GET(x)                              (((x) & ETH_CFG_1_CFGXOFFRTX_MASK) >> ETH_CFG_1_CFGXOFFRTX_LSB)
#define ETH_CFG_1_CFGXOFFRTX_SET(x)                              (((x) << ETH_CFG_1_CFGXOFFRTX_LSB) & ETH_CFG_1_CFGXOFFRTX_MASK)
#define ETH_CFG_1_CFGXOFFRTX_RESET                               0xffff // 65535
#define ETH_CFG_1_ADDRESS                                        0x004c

#define ETH_CFG_2_CFGHWM_MSB                                     26
#define ETH_CFG_2_CFGHWM_LSB                                     16
#define ETH_CFG_2_CFGHWM_MASK                                    0x07ff0000
#define ETH_CFG_2_CFGHWM_GET(x)                                  (((x) & ETH_CFG_2_CFGHWM_MASK) >> ETH_CFG_2_CFGHWM_LSB)
#define ETH_CFG_2_CFGHWM_SET(x)                                  (((x) << ETH_CFG_2_CFGHWM_LSB) & ETH_CFG_2_CFGHWM_MASK)
#define ETH_CFG_2_CFGHWM_RESET                                   0x2aa // 682
#define ETH_CFG_2_CFGLWM_MSB                                     10
#define ETH_CFG_2_CFGLWM_LSB                                     0
#define ETH_CFG_2_CFGLWM_MASK                                    0x000007ff
#define ETH_CFG_2_CFGLWM_GET(x)                                  (((x) & ETH_CFG_2_CFGLWM_MASK) >> ETH_CFG_2_CFGLWM_LSB)
#define ETH_CFG_2_CFGLWM_SET(x)                                  (((x) << ETH_CFG_2_CFGLWM_LSB) & ETH_CFG_2_CFGLWM_MASK)
#define ETH_CFG_2_CFGLWM_RESET                                   0x155 // 341
#define ETH_CFG_2_ADDRESS                                        0x0050

#define ETH_CFG_3_CFGHWMFT_MSB                                   25
#define ETH_CFG_3_CFGHWMFT_LSB                                   16
#define ETH_CFG_3_CFGHWMFT_MASK                                  0x03ff0000
#define ETH_CFG_3_CFGHWMFT_GET(x)                                (((x) & ETH_CFG_3_CFGHWMFT_MASK) >> ETH_CFG_3_CFGHWMFT_LSB)
#define ETH_CFG_3_CFGHWMFT_SET(x)                                (((x) << ETH_CFG_3_CFGHWMFT_LSB) & ETH_CFG_3_CFGHWMFT_MASK)
#define ETH_CFG_3_CFGHWMFT_RESET                                 0x155 // 341
#define ETH_CFG_3_CFGFTTH_MSB                                    9
#define ETH_CFG_3_CFGFTTH_LSB                                    0
#define ETH_CFG_3_CFGFTTH_MASK                                   0x000003ff
#define ETH_CFG_3_CFGFTTH_GET(x)                                 (((x) & ETH_CFG_3_CFGFTTH_MASK) >> ETH_CFG_3_CFGFTTH_LSB)
#define ETH_CFG_3_CFGFTTH_SET(x)                                 (((x) << ETH_CFG_3_CFGFTTH_LSB) & ETH_CFG_3_CFGFTTH_MASK)
#define ETH_CFG_3_CFGFTTH_RESET                                  0x3ff // 1023
#define ETH_CFG_3_ADDRESS                                        0x0054

#define ETH_CFG_4_HSTFLTRFRM_MSB                                 17
#define ETH_CFG_4_HSTFLTRFRM_LSB                                 0
#define ETH_CFG_4_HSTFLTRFRM_MASK                                0x0003ffff
#define ETH_CFG_4_HSTFLTRFRM_GET(x)                              (((x) & ETH_CFG_4_HSTFLTRFRM_MASK) >> ETH_CFG_4_HSTFLTRFRM_LSB)
#define ETH_CFG_4_HSTFLTRFRM_SET(x)                              (((x) << ETH_CFG_4_HSTFLTRFRM_LSB) & ETH_CFG_4_HSTFLTRFRM_MASK)
#define ETH_CFG_4_HSTFLTRFRM_RESET                               0x0 // 0
#define ETH_CFG_4_ADDRESS                                        0x0058

#define ETH_CFG_5_SRFULL_MSB                                     21
#define ETH_CFG_5_SRFULL_LSB                                     21
#define ETH_CFG_5_SRFULL_MASK                                    0x00200000
#define ETH_CFG_5_SRFULL_GET(x)                                  (((x) & ETH_CFG_5_SRFULL_MASK) >> ETH_CFG_5_SRFULL_LSB)
#define ETH_CFG_5_SRFULL_SET(x)                                  (((x) << ETH_CFG_5_SRFULL_LSB) & ETH_CFG_5_SRFULL_MASK)
#define ETH_CFG_5_SRFULL_RESET                                   0x0 // 0
#define ETH_CFG_5_HSTSRFULLCLR_MSB                               20
#define ETH_CFG_5_HSTSRFULLCLR_LSB                               20
#define ETH_CFG_5_HSTSRFULLCLR_MASK                              0x00100000
#define ETH_CFG_5_HSTSRFULLCLR_GET(x)                            (((x) & ETH_CFG_5_HSTSRFULLCLR_MASK) >> ETH_CFG_5_HSTSRFULLCLR_LSB)
#define ETH_CFG_5_HSTSRFULLCLR_SET(x)                            (((x) << ETH_CFG_5_HSTSRFULLCLR_LSB) & ETH_CFG_5_HSTSRFULLCLR_MASK)
#define ETH_CFG_5_HSTSRFULLCLR_RESET                             0x0 // 0
#define ETH_CFG_5_CFGBYTMODE_MSB                                 19
#define ETH_CFG_5_CFGBYTMODE_LSB                                 19
#define ETH_CFG_5_CFGBYTMODE_MASK                                0x00080000
#define ETH_CFG_5_CFGBYTMODE_GET(x)                              (((x) & ETH_CFG_5_CFGBYTMODE_MASK) >> ETH_CFG_5_CFGBYTMODE_LSB)
#define ETH_CFG_5_CFGBYTMODE_SET(x)                              (((x) << ETH_CFG_5_CFGBYTMODE_LSB) & ETH_CFG_5_CFGBYTMODE_MASK)
#define ETH_CFG_5_CFGBYTMODE_RESET                               0x0 // 0
#define ETH_CFG_5_HSTDRPLT64_MSB                                 18
#define ETH_CFG_5_HSTDRPLT64_LSB                                 18
#define ETH_CFG_5_HSTDRPLT64_MASK                                0x00040000
#define ETH_CFG_5_HSTDRPLT64_GET(x)                              (((x) & ETH_CFG_5_HSTDRPLT64_MASK) >> ETH_CFG_5_HSTDRPLT64_LSB)
#define ETH_CFG_5_HSTDRPLT64_SET(x)                              (((x) << ETH_CFG_5_HSTDRPLT64_LSB) & ETH_CFG_5_HSTDRPLT64_MASK)
#define ETH_CFG_5_HSTDRPLT64_RESET                               0x0 // 0
#define ETH_CFG_5_HSTFLTRFRMDC_MSB                               17
#define ETH_CFG_5_HSTFLTRFRMDC_LSB                               0
#define ETH_CFG_5_HSTFLTRFRMDC_MASK                              0x0003ffff
#define ETH_CFG_5_HSTFLTRFRMDC_GET(x)                            (((x) & ETH_CFG_5_HSTFLTRFRMDC_MASK) >> ETH_CFG_5_HSTFLTRFRMDC_LSB)
#define ETH_CFG_5_HSTFLTRFRMDC_SET(x)                            (((x) << ETH_CFG_5_HSTFLTRFRMDC_LSB) & ETH_CFG_5_HSTFLTRFRMDC_MASK)
#define ETH_CFG_5_HSTFLTRFRMDC_RESET                             0x3ffff // 262143
#define ETH_CFG_5_ADDRESS                                        0x005c

#define TXFIFO_TH_TXFIFO_MAXTH_MSB                                   25
#define TXFIFO_TH_TXFIFO_MAXTH_LSB                                   16
#define TXFIFO_TH_TXFIFO_MAXTH_MASK                                  0x03ff0000
#define TXFIFO_TH_TXFIFO_MAXTH_GET(x)                                (((x) & TXFIFO_TH_TXFIFO_MAXTH_MASK) >> TXFIFO_TH_TXFIFO_MAXTH_LSB)
#define TXFIFO_TH_TXFIFO_MAXTH_SET(x)                                (((x) << TXFIFO_TH_TXFIFO_MAXTH_LSB) & TXFIFO_TH_TXFIFO_MAXTH_MASK)
#define TXFIFO_TH_TXFIFO_MAXTH_RESET                                 0x1d8 // 472
#define TXFIFO_TH_TXFIFO_MINTH_MSB                                   9
#define TXFIFO_TH_TXFIFO_MINTH_LSB                                   0
#define TXFIFO_TH_TXFIFO_MINTH_MASK                                  0x000003ff
#define TXFIFO_TH_TXFIFO_MINTH_GET(x)                                (((x) & TXFIFO_TH_TXFIFO_MINTH_MASK) >> TXFIFO_TH_TXFIFO_MINTH_LSB)
#define TXFIFO_TH_TXFIFO_MINTH_SET(x)                                (((x) << TXFIFO_TH_TXFIFO_MINTH_LSB) & TXFIFO_TH_TXFIFO_MINTH_MASK)
#define TXFIFO_TH_TXFIFO_MINTH_RESET                                 0x160 // 352
#define TXFIFO_TH_ADDRESS                                            0x01a4


#define CONFIG_MIPS32		1	/* MIPS32 CPU core	*/

#define CONFIG_BOOTDELAY	1	/* autoboot after 4 seconds	*/

/* lsz add CONFIG_AUTOBOOT_STOP_STR 090223 */
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT   "Autobooting in %d seconds\n"
#define CONFIG_AUTOBOOT_STOP_STR "tpl"
#undef  CONFIG_AUTOBOOT_DELAY_STR
#define DEBUG_BOOTKEYS       0

#define CONFIG_BAUDRATE		115200

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */

#define CONFIG_ROOTFS_RD

#define	CONFIG_BOOTARGS_RD     "console=ttyS0,115200 root=01:00 rd_start=0x802d0000 rd_size=5242880 init=/sbin/init mtdparts=ath-nor0:256k(u-boot),64k(u-boot-env),4096k(rootfs),2048k(uImage)"

/* XXX - putting rootfs in last partition results in jffs errors */
#define	CONFIG_BOOTARGS_FL     "console=ttyS0,115200 root=31:02 rootfstype=jffs2 init=/sbin/init mtdparts=ath-nor0:256k(u-boot),64k(u-boot-env),5120k(rootfs),2048k(uImage)"


/*
 * Miscellaneous configurable options
 */



#define	CFG_MAXARGS		16		/* max number of command args*/


#define CFG_SDRAM_BASE		0x80000000     /* Cached addr */
//#define CFG_SDRAM_BASE	0xa0000000     /* Cached addr */


/*------------------------------------------------------------------------
 * *  * JFFS2
 */
#define CFG_JFFS_CUSTOM_PART            /* board defined part   */
#define CONFIG_JFFS2_CMDLINE
#define MTDIDS_DEFAULT		"nor0=ath-nor0"

#define CONFIG_MEMSIZE_IN_BYTES

#define CFG_RX_ETH_BUFFER	16


/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_CACHELINE_SIZE	32

/*
 * Address map
 */
#define ATH_PCI_MEM_BASE		0x10000000	/* 128M */
#define ATH_APB_BASE			0x18000000	/* 384M */
#define ATH_GE0_BASE			0x19000000	/* 16M */
#define ATH_GE1_BASE			0x1a000000	/* 16M */
#define ATH_USB_OHCI_BASE		0x1b000000
#define ATH_USB_EHCI_BASE		0x1b000000
#define ATH_USB_EHCI_BASE_1		0x1b000000
#define ATH_USB_EHCI_BASE_2		0x1b400000
#define ATH_SPI_BASE			0x1f000000

/*
 * Added the PCI LCL RESET register from u-boot
 * ath_soc.h so that we can query the PCI LCL RESET
 * register for the presence of WLAN H/W.
 */
#define ATH_PCI_LCL_BASE		(ATH_APB_BASE+0x000f0000)
#define ATH_PCI_LCL_APP			(ATH_PCI_LCL_BASE+0x00)
#define ATH_PCI_LCL_RESET		(ATH_PCI_LCL_BASE+0x18)

/*
 * APB block
 */
#define ATH_DDR_CTL_BASE		ATH_APB_BASE+0x00000000
#define ATH_CPU_BASE			ATH_APB_BASE+0x00010000
#define ATH_UART_BASE			ATH_APB_BASE+0x00020000
#define ATH_USB_CONFIG_BASE		ATH_APB_BASE+0x00030000
#define ATH_GPIO_BASE			ATH_APB_BASE+0x00040000
#define ATH_PLL_BASE			ATH_APB_BASE+0x00050000
#define ATH_RESET_BASE			ATH_APB_BASE+0x00060000
#define ATH_DMA_BASE			ATH_APB_BASE+0x000A0000
#define ATH_SLIC_BASE			ATH_APB_BASE+0x000A9000
#define ATH_STEREO_BASE			ATH_APB_BASE+0x000B0000
#define ATH_PCI_CTLR_BASE		ATH_APB_BASE+0x000F0000
#define ATH_OTP_BASE			ATH_APB_BASE+0x00130000
#define ATH_NAND_FLASH_BASE		0x1b800000u


/*
 * DDR Config values
 */
#define ATH_DDR_CONFIG_16BIT		(1 << 31)
#define ATH_DDR_CONFIG_PAGE_OPEN	(1 << 30)
#define ATH_DDR_CONFIG_CAS_LAT_SHIFT	27
#define ATH_DDR_CONFIG_TMRD_SHIFT	23
#define ATH_DDR_CONFIG_TRFC_SHIFT	17
#define ATH_DDR_CONFIG_TRRD_SHIFT	13
#define ATH_DDR_CONFIG_TRP_SHIFT	9
#define ATH_DDR_CONFIG_TRCD_SHIFT	5
#define ATH_DDR_CONFIG_TRAS_SHIFT	0

#define ATH_DDR_CONFIG2_BL2		(2 << 0)
#define ATH_DDR_CONFIG2_BL4		(4 << 0)
#define ATH_DDR_CONFIG2_BL8		(8 << 0)

#define ATH_DDR_CONFIG2_BT_IL		(1 << 4)
#define ATH_DDR_CONFIG2_CNTL_OE_EN	(1 << 5)
#define ATH_DDR_CONFIG2_PHASE_SEL	(1 << 6)
#define ATH_DDR_CONFIG2_DRAM_CKE	(1 << 7)
#define ATH_DDR_CONFIG2_TWR_SHIFT	8
#define ATH_DDR_CONFIG2_TRTW_SHIFT	12
#define ATH_DDR_CONFIG2_TRTP_SHIFT	17
#define ATH_DDR_CONFIG2_TWTR_SHIFT	21
#define ATH_DDR_CONFIG2_HALF_WIDTH_L	(1 << 31)

#define ATH_DDR_TAP_DEFAULT		0x18

/*
 * DDR block, gmac flushing
 */
#define ATH_DDR_GE0_FLUSH		ATH_DDR_CTL_BASE+0x9c
#define ATH_DDR_GE1_FLUSH		ATH_DDR_CTL_BASE+0xa0
#define ATH_DDR_USB_FLUSH		ATH_DDR_CTL_BASE+0xa4
#define ATH_DDR_PCIE_FLUSH		ATH_DDR_CTL_BASE+0x88

#define ATH_EEPROM_GE0_MAC_ADDR		0xbfff1000
#define ATH_EEPROM_GE1_MAC_ADDR		0xbfff1006

/*
 * PLL block/CPU
 */

#define ATH_PLL_CONFIG			ATH_PLL_BASE+0x0
#define ATH_DDR_CLK_CTRL		ATH_PLL_BASE+0x8


#define PLL_DIV_SHIFT			0
#define PLL_DIV_MASK			0x3ff
#define REF_DIV_SHIFT			10
#define REF_DIV_MASK			0xf
#define AHB_DIV_SHIFT			19
#define AHB_DIV_MASK			0x1
#define DDR_DIV_SHIFT			22
#define DDR_DIV_MASK			0x1
#define ATH_DDR_PLL_CONFIG		ATH_PLL_BASE+0x4
#define ATH_ETH_XMII_CONFIG		ATH_PLL_BASE+0x2c
#define ATH_AUDIO_PLL_CONFIG		ATH_PLL_BASE+0x30

#define ATH_ETH_INT0_CLK		ATH_PLL_BASE+0x14
#define ATH_ETH_INT1_CLK		ATH_PLL_BASE+0x18


/*
 * USB block
 */
#define USB_FLADJ_VAL		0x18030000
#define USB_CONFIG			0x18030004
#define USB_WINDOW			0x10000
#define USB_MODE			0x1b0001a8
#define USB2_MODE                   0x1b4001a8
#define USB_PORTSCX                 0x1b000184
#define USB2_PORTSCX                0x1b400184
#define USB_STS                  	0x1b000144
#define USB2_STS                 	0x1b400144
#define USB_SET_SERIAL_MODE         (1<<29) /* This bit will enable the serial mode */
#define USB_STS_SOF                 (1<<7)
#define USB2_STS_SOF                (1<<7)

/*
 * PCI block
 */
#define ATH_PCI_WINDOW			0x8000000 /* 128MB */
#define ATH_PCI_WINDOW0_OFFSET		ATH_DDR_CTL_BASE+0x7c
#define ATH_PCI_WINDOW1_OFFSET		ATH_DDR_CTL_BASE+0x80
#define ATH_PCI_WINDOW2_OFFSET		ATH_DDR_CTL_BASE+0x84
#define ATH_PCI_WINDOW3_OFFSET		ATH_DDR_CTL_BASE+0x88
#define ATH_PCI_WINDOW4_OFFSET		ATH_DDR_CTL_BASE+0x8c
#define ATH_PCI_WINDOW5_OFFSET		ATH_DDR_CTL_BASE+0x90
#define ATH_PCI_WINDOW6_OFFSET		ATH_DDR_CTL_BASE+0x94
#define ATH_PCI_WINDOW7_OFFSET		ATH_DDR_CTL_BASE+0x98

#define ATH_PCI_WINDOW0_VAL		0x10000000
#define ATH_PCI_WINDOW1_VAL		0x11000000
#define ATH_PCI_WINDOW2_VAL		0x12000000
#define ATH_PCI_WINDOW3_VAL		0x13000000
#define ATH_PCI_WINDOW4_VAL		0x14000000
#define ATH_PCI_WINDOW5_VAL		0x15000000
#define ATH_PCI_WINDOW6_VAL		0x16000000
#define ATH_PCI_WINDOW7_VAL		0x07000000

#define ath_write_pci_window(_no)	\
	ath_reg_wr(ATH_PCI_WINDOW##_no##_OFFSET, ATH_PCI_WINDOW##_no##_VAL);

/*
 * CRP. To access the host controller config and status registers
 */
#define ATH_PCI_CRP			0x180c0000 //PCIE_RC_REG_ADDRESS
#define ATH_PCI_DEV_CFGBASE		0x14000000
#define ATH_PCI_CRP_AD_CBE		ATH_PCI_CRP
#define ATH_PCI_CRP_WRDATA		ATH_PCI_CRP+0x4
#define ATH_PCI_CRP_RDDATA		ATH_PCI_CRP+0x8
#define ATH_PCI_ERROR			ATH_PCI_CRP+0x1c
#define ATH_PCI_ERROR_ADDRESS		ATH_PCI_CRP+0x20
#define ATH_PCI_AHB_ERROR		ATH_PCI_CRP+0x24
#define ATH_PCI_AHB_ERROR_ADDRESS	ATH_PCI_CRP+0x28

#define ATH_CRP_CMD_WRITE		0x00010000
#define ATH_CRP_CMD_READ		0x00000000

#define PCIERC_RC_REG_ADDRESS		0x18250000

/*
 * PCI CFG. To generate config cycles
 */
#define ATH_PCI_CFG_AD			ATH_PCI_CRP+0xc
#define ATH_PCI_CFG_CBE			ATH_PCI_CRP+0x10
#define ATH_PCI_CFG_WRDATA		ATH_PCI_CRP+0x14
#define ATH_PCI_CFG_RDDATA		ATH_PCI_CRP+0x18
#define ATH_CFG_CMD_READ		0x0000000a
#define ATH_CFG_CMD_WRITE		0x0000000b

#define ATH_PCI_IDSEL_ADLINE_START	17

#define ATH_SPI_FS		(ATH_SPI_BASE+0x00)
#define ATH_SPI_READ		(ATH_SPI_BASE+0x00)
#define ATH_SPI_CLOCK		(ATH_SPI_BASE+0x04)
#define ATH_SPI_WRITE		(ATH_SPI_BASE+0x08)
#define ATH_SPI_RD_STATUS	(ATH_SPI_BASE+0x0c)
#define ATH_SPI_SHIFT_DO	(ATH_SPI_BASE+0x10)
#define ATH_SPI_SHIFT_CNT	(ATH_SPI_BASE+0x14)
#define ATH_SPI_SHIFT_DI	(ATH_SPI_BASE+0x18)
#define ATH_SPI_D0_HIGH		(1<<0)	/* Pin spi_do */
#define ATH_SPI_CLK_HIGH	(1<<8)	/* Pin spi_clk */

#define ATH_SPI_CS_ENABLE_0	(6<<16)	/* Pin gpio/cs0 (active low) */
#define ATH_SPI_CS_ENABLE_1	(5<<16)	/* Pin gpio/cs1 (active low) */
#define ATH_SPI_CS_ENABLE_2	(3<<16)	/* Pin gpio/cs2 (active low) */
#define ATH_SPI_CS_DIS		0x70000
#define ATH_SPI_CE_LOW		0x60000
#define ATH_SPI_CE_HIGH		0x60100

#define ATH_SPI_SECTOR_SIZE	(1024*64)
#define ATH_SPI_PAGE_SIZE	256

#define ATH_RESET_GE0_MAC	RST_RESET_GE0_MAC_RESET_SET(1)
#define ATH_RESET_GE0_PHY	(0)	// Nothing similar to wasp??
#define ATH_RESET_GE1_MAC	RST_RESET_GE1_MAC_RESET_SET(1)
#define ATH_RESET_GE1_PHY	(0)	// Nothing similar to wasp??
#define ATH_RESET_GE0_MDIO	RST_RESET_GE0_MDIO_RESET_SET(1)
#define ATH_RESET_GE1_MDIO	RST_RESET_GE1_MDIO_RESET_SET(1)

/*
 * SOC
 */
#define ATH_SPI_CMD_WRITE_SR		0x01
#define ATH_SPI_CMD_WREN		0x06
#define ATH_SPI_CMD_RD_STATUS		0x05
#define ATH_SPI_CMD_FAST_READ		0x0b
#define ATH_SPI_CMD_PAGE_PROG		0x02
#define ATH_SPI_CMD_SECTOR_ERASE	0xd8
#define ATH_SPI_CMD_CHIP_ERASE		0xc7
#define ATH_SPI_CMD_RDID		0x9f




#define __nint_to_mhz(n, ref)	((n) * (ref) * 1000000)
#define __cpu_hz_40(pll)	(__nint_to_mhz(CPU_PLL_CONFIG_NINT_GET(pll), 40))
#define __cpu_hz_25(pll)	(__nint_to_mhz(CPU_PLL_CONFIG_NINT_GET(pll), 25))

/* Since the count is incremented every other tick, divide by 2 */


/* SGMII DEFINES */

// 32'h18070034 (SGMII_CONFIG)
#define SGMII_CONFIG_BERT_ENABLE_MSB                                 14
#define SGMII_CONFIG_BERT_ENABLE_LSB                                 14
#define SGMII_CONFIG_BERT_ENABLE_MASK                                0x00004000
#define SGMII_CONFIG_BERT_ENABLE_GET(x)                              (((x) & SGMII_CONFIG_BERT_ENABLE_MASK) >> SGMII_CONFIG_BERT_ENABLE_LSB)
#define SGMII_CONFIG_BERT_ENABLE_SET(x)                              (((x) << SGMII_CONFIG_BERT_ENABLE_LSB) & SGMII_CONFIG_BERT_ENABLE_MASK)
#define SGMII_CONFIG_BERT_ENABLE_RESET                               0x0 // 0
#define SGMII_CONFIG_PRBS_ENABLE_MSB                                 13
#define SGMII_CONFIG_PRBS_ENABLE_LSB                                 13
#define SGMII_CONFIG_PRBS_ENABLE_MASK                                0x00002000
#define SGMII_CONFIG_PRBS_ENABLE_GET(x)                              (((x) & SGMII_CONFIG_PRBS_ENABLE_MASK) >> SGMII_CONFIG_PRBS_ENABLE_LSB)
#define SGMII_CONFIG_PRBS_ENABLE_SET(x)                              (((x) << SGMII_CONFIG_PRBS_ENABLE_LSB) & SGMII_CONFIG_PRBS_ENABLE_MASK)
#define SGMII_CONFIG_PRBS_ENABLE_RESET                               0x0 // 0
#define SGMII_CONFIG_MDIO_COMPLETE_MSB                               12
#define SGMII_CONFIG_MDIO_COMPLETE_LSB                               12
#define SGMII_CONFIG_MDIO_COMPLETE_MASK                              0x00001000
#define SGMII_CONFIG_MDIO_COMPLETE_GET(x)                            (((x) & SGMII_CONFIG_MDIO_COMPLETE_MASK) >> SGMII_CONFIG_MDIO_COMPLETE_LSB)
#define SGMII_CONFIG_MDIO_COMPLETE_SET(x)                            (((x) << SGMII_CONFIG_MDIO_COMPLETE_LSB) & SGMII_CONFIG_MDIO_COMPLETE_MASK)
#define SGMII_CONFIG_MDIO_COMPLETE_RESET                             0x0 // 0
#define SGMII_CONFIG_MDIO_PULSE_MSB                                  11
#define SGMII_CONFIG_MDIO_PULSE_LSB                                  11
#define SGMII_CONFIG_MDIO_PULSE_MASK                                 0x00000800
#define SGMII_CONFIG_MDIO_PULSE_GET(x)                               (((x) & SGMII_CONFIG_MDIO_PULSE_MASK) >> SGMII_CONFIG_MDIO_PULSE_LSB)
#define SGMII_CONFIG_MDIO_PULSE_SET(x)                               (((x) << SGMII_CONFIG_MDIO_PULSE_LSB) & SGMII_CONFIG_MDIO_PULSE_MASK)
#define SGMII_CONFIG_MDIO_PULSE_RESET                                0x0 // 0
#define SGMII_CONFIG_MDIO_ENABLE_MSB                                 10
#define SGMII_CONFIG_MDIO_ENABLE_LSB                                 10
#define SGMII_CONFIG_MDIO_ENABLE_MASK                                0x00000400
#define SGMII_CONFIG_MDIO_ENABLE_GET(x)                              (((x) & SGMII_CONFIG_MDIO_ENABLE_MASK) >> SGMII_CONFIG_MDIO_ENABLE_LSB)
#define SGMII_CONFIG_MDIO_ENABLE_SET(x)                              (((x) << SGMII_CONFIG_MDIO_ENABLE_LSB) & SGMII_CONFIG_MDIO_ENABLE_MASK)
#define SGMII_CONFIG_MDIO_ENABLE_RESET                               0x0 // 0
#define SGMII_CONFIG_NEXT_PAGE_LOADED_MSB                            9
#define SGMII_CONFIG_NEXT_PAGE_LOADED_LSB                            9
#define SGMII_CONFIG_NEXT_PAGE_LOADED_MASK                           0x00000200
#define SGMII_CONFIG_NEXT_PAGE_LOADED_GET(x)                         (((x) & SGMII_CONFIG_NEXT_PAGE_LOADED_MASK) >> SGMII_CONFIG_NEXT_PAGE_LOADED_LSB)
#define SGMII_CONFIG_NEXT_PAGE_LOADED_SET(x)                         (((x) << SGMII_CONFIG_NEXT_PAGE_LOADED_LSB) & SGMII_CONFIG_NEXT_PAGE_LOADED_MASK)
#define SGMII_CONFIG_NEXT_PAGE_LOADED_RESET                          0x0 // 0
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_MSB                         8
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_LSB                         8
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_MASK                        0x00000100
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_GET(x)                      (((x) & SGMII_CONFIG_REMOTE_PHY_LOOPBACK_MASK) >> SGMII_CONFIG_REMOTE_PHY_LOOPBACK_LSB)
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_SET(x)                      (((x) << SGMII_CONFIG_REMOTE_PHY_LOOPBACK_LSB) & SGMII_CONFIG_REMOTE_PHY_LOOPBACK_MASK)
#define SGMII_CONFIG_REMOTE_PHY_LOOPBACK_RESET                       0x0 // 0
#define SGMII_CONFIG_SPEED_MSB                                       7
#define SGMII_CONFIG_SPEED_LSB                                       6
#define SGMII_CONFIG_SPEED_MASK                                      0x000000c0
#define SGMII_CONFIG_SPEED_GET(x)                                    (((x) & SGMII_CONFIG_SPEED_MASK) >> SGMII_CONFIG_SPEED_LSB)
#define SGMII_CONFIG_SPEED_SET(x)                                    (((x) << SGMII_CONFIG_SPEED_LSB) & SGMII_CONFIG_SPEED_MASK)
#define SGMII_CONFIG_SPEED_RESET                                     0x0 // 0
#define SGMII_CONFIG_FORCE_SPEED_MSB                                 5
#define SGMII_CONFIG_FORCE_SPEED_LSB                                 5
#define SGMII_CONFIG_FORCE_SPEED_MASK                                0x00000020
#define SGMII_CONFIG_FORCE_SPEED_GET(x)                              (((x) & SGMII_CONFIG_FORCE_SPEED_MASK) >> SGMII_CONFIG_FORCE_SPEED_LSB)
#define SGMII_CONFIG_FORCE_SPEED_SET(x)                              (((x) << SGMII_CONFIG_FORCE_SPEED_LSB) & SGMII_CONFIG_FORCE_SPEED_MASK)
#define SGMII_CONFIG_FORCE_SPEED_RESET                               0x0 // 0
#define SGMII_CONFIG_MR_REG4_CHANGED_MSB                             4
#define SGMII_CONFIG_MR_REG4_CHANGED_LSB                             4
#define SGMII_CONFIG_MR_REG4_CHANGED_MASK                            0x00000010
#define SGMII_CONFIG_MR_REG4_CHANGED_GET(x)                          (((x) & SGMII_CONFIG_MR_REG4_CHANGED_MASK) >> SGMII_CONFIG_MR_REG4_CHANGED_LSB)
#define SGMII_CONFIG_MR_REG4_CHANGED_SET(x)                          (((x) << SGMII_CONFIG_MR_REG4_CHANGED_LSB) & SGMII_CONFIG_MR_REG4_CHANGED_MASK)
#define SGMII_CONFIG_MR_REG4_CHANGED_RESET                           0x0 // 0
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_MSB                       3
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_LSB                       3
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_MASK                      0x00000008
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_GET(x)                    (((x) & SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_MASK) >> SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_LSB)
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_SET(x)                    (((x) << SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_LSB) & SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_MASK)
#define SGMII_CONFIG_ENABLE_SGMII_TX_PAUSE_RESET                     0x0 // 0
#define SGMII_CONFIG_MODE_CTRL_MSB                                   2
#define SGMII_CONFIG_MODE_CTRL_LSB                                   0
#define SGMII_CONFIG_MODE_CTRL_MASK                                  0x00000007
#define SGMII_CONFIG_MODE_CTRL_GET(x)                                (((x) & SGMII_CONFIG_MODE_CTRL_MASK) >> SGMII_CONFIG_MODE_CTRL_LSB)
#define SGMII_CONFIG_MODE_CTRL_SET(x)                                (((x) << SGMII_CONFIG_MODE_CTRL_LSB) & SGMII_CONFIG_MODE_CTRL_MASK)
#define SGMII_CONFIG_MODE_CTRL_RESET                                 0x0 // 0
#define SGMII_CONFIG_ADDRESS                                         0x18070034



// 32'h1807001c (MR_AN_CONTROL)
#define MR_AN_CONTROL_PHY_RESET_MSB                                  15
#define MR_AN_CONTROL_PHY_RESET_LSB                                  15
#define MR_AN_CONTROL_PHY_RESET_MASK                                 0x00008000
#define MR_AN_CONTROL_PHY_RESET_GET(x)                               (((x) & MR_AN_CONTROL_PHY_RESET_MASK) >> MR_AN_CONTROL_PHY_RESET_LSB)
#define MR_AN_CONTROL_PHY_RESET_SET(x)                               (((x) << MR_AN_CONTROL_PHY_RESET_LSB) & MR_AN_CONTROL_PHY_RESET_MASK)
#define MR_AN_CONTROL_PHY_RESET_RESET                                0x0 // 0
#define MR_AN_CONTROL_LOOPBACK_MSB                                   14
#define MR_AN_CONTROL_LOOPBACK_LSB                                   14
#define MR_AN_CONTROL_LOOPBACK_MASK                                  0x00004000
#define MR_AN_CONTROL_LOOPBACK_GET(x)                                (((x) & MR_AN_CONTROL_LOOPBACK_MASK) >> MR_AN_CONTROL_LOOPBACK_LSB)
#define MR_AN_CONTROL_LOOPBACK_SET(x)                                (((x) << MR_AN_CONTROL_LOOPBACK_LSB) & MR_AN_CONTROL_LOOPBACK_MASK)
#define MR_AN_CONTROL_LOOPBACK_RESET                                 0x0 // 0
#define MR_AN_CONTROL_SPEED_SEL0_MSB                                 13
#define MR_AN_CONTROL_SPEED_SEL0_LSB                                 13
#define MR_AN_CONTROL_SPEED_SEL0_MASK                                0x00002000
#define MR_AN_CONTROL_SPEED_SEL0_GET(x)                              (((x) & MR_AN_CONTROL_SPEED_SEL0_MASK) >> MR_AN_CONTROL_SPEED_SEL0_LSB)
#define MR_AN_CONTROL_SPEED_SEL0_SET(x)                              (((x) << MR_AN_CONTROL_SPEED_SEL0_LSB) & MR_AN_CONTROL_SPEED_SEL0_MASK)
#define MR_AN_CONTROL_SPEED_SEL0_RESET                               0x0 // 0
#define MR_AN_CONTROL_AN_ENABLE_MSB                                  12
#define MR_AN_CONTROL_AN_ENABLE_LSB                                  12
#define MR_AN_CONTROL_AN_ENABLE_MASK                                 0x00001000
#define MR_AN_CONTROL_AN_ENABLE_GET(x)                               (((x) & MR_AN_CONTROL_AN_ENABLE_MASK) >> MR_AN_CONTROL_AN_ENABLE_LSB)
#define MR_AN_CONTROL_AN_ENABLE_SET(x)                               (((x) << MR_AN_CONTROL_AN_ENABLE_LSB) & MR_AN_CONTROL_AN_ENABLE_MASK)
#define MR_AN_CONTROL_AN_ENABLE_RESET                                0x1 // 1
#define MR_AN_CONTROL_POWER_DOWN_MSB                                 11
#define MR_AN_CONTROL_POWER_DOWN_LSB                                 11
#define MR_AN_CONTROL_POWER_DOWN_MASK                                0x00000800
#define MR_AN_CONTROL_POWER_DOWN_GET(x)                              (((x) & MR_AN_CONTROL_POWER_DOWN_MASK) >> MR_AN_CONTROL_POWER_DOWN_LSB)
#define MR_AN_CONTROL_POWER_DOWN_SET(x)                              (((x) << MR_AN_CONTROL_POWER_DOWN_LSB) & MR_AN_CONTROL_POWER_DOWN_MASK)
#define MR_AN_CONTROL_POWER_DOWN_RESET                               0x0 // 0
#define MR_AN_CONTROL_RESTART_AN_MSB                                 9
#define MR_AN_CONTROL_RESTART_AN_LSB                                 9
#define MR_AN_CONTROL_RESTART_AN_MASK                                0x00000200
#define MR_AN_CONTROL_RESTART_AN_GET(x)                              (((x) & MR_AN_CONTROL_RESTART_AN_MASK) >> MR_AN_CONTROL_RESTART_AN_LSB)
#define MR_AN_CONTROL_RESTART_AN_SET(x)                              (((x) << MR_AN_CONTROL_RESTART_AN_LSB) & MR_AN_CONTROL_RESTART_AN_MASK)
#define MR_AN_CONTROL_RESTART_AN_RESET                               0x0 // 0
#define MR_AN_CONTROL_DUPLEX_MODE_MSB                                8
#define MR_AN_CONTROL_DUPLEX_MODE_LSB                                8
#define MR_AN_CONTROL_DUPLEX_MODE_MASK                               0x00000100
#define MR_AN_CONTROL_DUPLEX_MODE_GET(x)                             (((x) & MR_AN_CONTROL_DUPLEX_MODE_MASK) >> MR_AN_CONTROL_DUPLEX_MODE_LSB)
#define MR_AN_CONTROL_DUPLEX_MODE_SET(x)                             (((x) << MR_AN_CONTROL_DUPLEX_MODE_LSB) & MR_AN_CONTROL_DUPLEX_MODE_MASK)
#define MR_AN_CONTROL_DUPLEX_MODE_RESET                              0x1 // 1
#define MR_AN_CONTROL_SPEED_SEL1_MSB                                 6
#define MR_AN_CONTROL_SPEED_SEL1_LSB                                 6
#define MR_AN_CONTROL_SPEED_SEL1_MASK                                0x00000040
#define MR_AN_CONTROL_SPEED_SEL1_GET(x)                              (((x) & MR_AN_CONTROL_SPEED_SEL1_MASK) >> MR_AN_CONTROL_SPEED_SEL1_LSB)
#define MR_AN_CONTROL_SPEED_SEL1_SET(x)                              (((x) << MR_AN_CONTROL_SPEED_SEL1_LSB) & MR_AN_CONTROL_SPEED_SEL1_MASK)
#define MR_AN_CONTROL_SPEED_SEL1_RESET                               0x1 // 1
#define MR_AN_CONTROL_ADDRESS                                        0x1807001c





// 32'h18070014 (SGMII_RESET)
#define SGMII_RESET_HW_RX_125M_N_MSB                                 4
#define SGMII_RESET_HW_RX_125M_N_LSB                                 4
#define SGMII_RESET_HW_RX_125M_N_MASK                                0x00000010
#define SGMII_RESET_HW_RX_125M_N_GET(x)                              (((x) & SGMII_RESET_HW_RX_125M_N_MASK) >> SGMII_RESET_HW_RX_125M_N_LSB)
#define SGMII_RESET_HW_RX_125M_N_SET(x)                              (((x) << SGMII_RESET_HW_RX_125M_N_LSB) & SGMII_RESET_HW_RX_125M_N_MASK)
#define SGMII_RESET_HW_RX_125M_N_RESET                               0x0 // 0
#define SGMII_RESET_TX_125M_N_MSB                                    3
#define SGMII_RESET_TX_125M_N_LSB                                    3
#define SGMII_RESET_TX_125M_N_MASK                                   0x00000008
#define SGMII_RESET_TX_125M_N_GET(x)                                 (((x) & SGMII_RESET_TX_125M_N_MASK) >> SGMII_RESET_TX_125M_N_LSB)
#define SGMII_RESET_TX_125M_N_SET(x)                                 (((x) << SGMII_RESET_TX_125M_N_LSB) & SGMII_RESET_TX_125M_N_MASK)
#define SGMII_RESET_TX_125M_N_RESET                                  0x0 // 0
#define SGMII_RESET_RX_125M_N_MSB                                    2
#define SGMII_RESET_RX_125M_N_LSB                                    2
#define SGMII_RESET_RX_125M_N_MASK                                   0x00000004
#define SGMII_RESET_RX_125M_N_GET(x)                                 (((x) & SGMII_RESET_RX_125M_N_MASK) >> SGMII_RESET_RX_125M_N_LSB)
#define SGMII_RESET_RX_125M_N_SET(x)                                 (((x) << SGMII_RESET_RX_125M_N_LSB) & SGMII_RESET_RX_125M_N_MASK)
#define SGMII_RESET_RX_125M_N_RESET                                  0x0 // 0
#define SGMII_RESET_TX_CLK_N_MSB                                     1
#define SGMII_RESET_TX_CLK_N_LSB                                     1
#define SGMII_RESET_TX_CLK_N_MASK                                    0x00000002
#define SGMII_RESET_TX_CLK_N_GET(x)                                  (((x) & SGMII_RESET_TX_CLK_N_MASK) >> SGMII_RESET_TX_CLK_N_LSB)
#define SGMII_RESET_TX_CLK_N_SET(x)                                  (((x) << SGMII_RESET_TX_CLK_N_LSB) & SGMII_RESET_TX_CLK_N_MASK)
#define SGMII_RESET_TX_CLK_N_RESET                                   0x0 // 0
#define SGMII_RESET_RX_CLK_N_MSB                                     0
#define SGMII_RESET_RX_CLK_N_LSB                                     0
#define SGMII_RESET_RX_CLK_N_MASK                                    0x00000001
#define SGMII_RESET_RX_CLK_N_GET(x)                                  (((x) & SGMII_RESET_RX_CLK_N_MASK) >> SGMII_RESET_RX_CLK_N_LSB)
#define SGMII_RESET_RX_CLK_N_SET(x)                                  (((x) << SGMII_RESET_RX_CLK_N_LSB) & SGMII_RESET_RX_CLK_N_MASK)
#define SGMII_RESET_RX_CLK_N_RESET                                   0x0 // 0
#define SGMII_RESET_ADDRESS                                          0x18070014



// 32'h18070038 (SGMII_MAC_RX_CONFIG)
#define SGMII_MAC_RX_CONFIG_LINK_MSB                                 15
#define SGMII_MAC_RX_CONFIG_LINK_LSB                                 15
#define SGMII_MAC_RX_CONFIG_LINK_MASK                                0x00008000
#define SGMII_MAC_RX_CONFIG_LINK_GET(x)                              (((x) & SGMII_MAC_RX_CONFIG_LINK_MASK) >> SGMII_MAC_RX_CONFIG_LINK_LSB)
#define SGMII_MAC_RX_CONFIG_LINK_SET(x)                              (((x) << SGMII_MAC_RX_CONFIG_LINK_LSB) & SGMII_MAC_RX_CONFIG_LINK_MASK)
#define SGMII_MAC_RX_CONFIG_LINK_RESET                               0x0 // 0
#define SGMII_MAC_RX_CONFIG_ACK_MSB                                  14
#define SGMII_MAC_RX_CONFIG_ACK_LSB                                  14
#define SGMII_MAC_RX_CONFIG_ACK_MASK                                 0x00004000
#define SGMII_MAC_RX_CONFIG_ACK_GET(x)                               (((x) & SGMII_MAC_RX_CONFIG_ACK_MASK) >> SGMII_MAC_RX_CONFIG_ACK_LSB)
#define SGMII_MAC_RX_CONFIG_ACK_SET(x)                               (((x) << SGMII_MAC_RX_CONFIG_ACK_LSB) & SGMII_MAC_RX_CONFIG_ACK_MASK)
#define SGMII_MAC_RX_CONFIG_ACK_RESET                                0x0 // 0
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_MSB                          12
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_LSB                          12
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_MASK                         0x00001000
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_GET(x)                       (((x) & SGMII_MAC_RX_CONFIG_DUPLEX_MODE_MASK) >> SGMII_MAC_RX_CONFIG_DUPLEX_MODE_LSB)
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_SET(x)                       (((x) << SGMII_MAC_RX_CONFIG_DUPLEX_MODE_LSB) & SGMII_MAC_RX_CONFIG_DUPLEX_MODE_MASK)
#define SGMII_MAC_RX_CONFIG_DUPLEX_MODE_RESET                        0x0 // 0
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_MSB                           11
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_LSB                           10
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_MASK                          0x00000c00
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_GET(x)                        (((x) & SGMII_MAC_RX_CONFIG_SPEED_MODE_MASK) >> SGMII_MAC_RX_CONFIG_SPEED_MODE_LSB)
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_SET(x)                        (((x) << SGMII_MAC_RX_CONFIG_SPEED_MODE_LSB) & SGMII_MAC_RX_CONFIG_SPEED_MODE_MASK)
#define SGMII_MAC_RX_CONFIG_SPEED_MODE_RESET                         0x0 // 0
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_MSB                            8
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_LSB                            8
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_MASK                           0x00000100
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_GET(x)                         (((x) & SGMII_MAC_RX_CONFIG_ASM_PAUSE_MASK) >> SGMII_MAC_RX_CONFIG_ASM_PAUSE_LSB)
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_SET(x)                         (((x) << SGMII_MAC_RX_CONFIG_ASM_PAUSE_LSB) & SGMII_MAC_RX_CONFIG_ASM_PAUSE_MASK)
#define SGMII_MAC_RX_CONFIG_ASM_PAUSE_RESET                          0x0 // 0
#define SGMII_MAC_RX_CONFIG_PAUSE_MSB                                7
#define SGMII_MAC_RX_CONFIG_PAUSE_LSB                                7
#define SGMII_MAC_RX_CONFIG_PAUSE_MASK                               0x00000080
#define SGMII_MAC_RX_CONFIG_PAUSE_GET(x)                             (((x) & SGMII_MAC_RX_CONFIG_PAUSE_MASK) >> SGMII_MAC_RX_CONFIG_PAUSE_LSB)
#define SGMII_MAC_RX_CONFIG_PAUSE_SET(x)                             (((x) << SGMII_MAC_RX_CONFIG_PAUSE_LSB) & SGMII_MAC_RX_CONFIG_PAUSE_MASK)
#define SGMII_MAC_RX_CONFIG_PAUSE_RESET                              0x0 // 0
#define SGMII_MAC_RX_CONFIG_RES0_MSB                                 0
#define SGMII_MAC_RX_CONFIG_RES0_LSB                                 0
#define SGMII_MAC_RX_CONFIG_RES0_MASK                                0x00000001
#define SGMII_MAC_RX_CONFIG_RES0_GET(x)                              (((x) & SGMII_MAC_RX_CONFIG_RES0_MASK) >> SGMII_MAC_RX_CONFIG_RES0_LSB)
#define SGMII_MAC_RX_CONFIG_RES0_SET(x)                              (((x) << SGMII_MAC_RX_CONFIG_RES0_LSB) & SGMII_MAC_RX_CONFIG_RES0_MASK)
#define SGMII_MAC_RX_CONFIG_RES0_RESET                               0x1 // 1
#define SGMII_MAC_RX_CONFIG_ADDRESS                                  0x18070038

// 32'h18070058 (SGMII_DEBUG)
#define SGMII_DEBUG_ARB_STATE_MSB                                    27
#define SGMII_DEBUG_ARB_STATE_LSB                                    24
#define SGMII_DEBUG_ARB_STATE_MASK                                   0x0f000000
#define SGMII_DEBUG_ARB_STATE_GET(x)                                 (((x) & SGMII_DEBUG_ARB_STATE_MASK) >> SGMII_DEBUG_ARB_STATE_LSB)
#define SGMII_DEBUG_ARB_STATE_SET(x)                                 (((x) << SGMII_DEBUG_ARB_STATE_LSB) & SGMII_DEBUG_ARB_STATE_MASK)
#define SGMII_DEBUG_ARB_STATE_RESET                                  0x0 // 0
#define SGMII_DEBUG_RX_SYNC_STATE_MSB                                23
#define SGMII_DEBUG_RX_SYNC_STATE_LSB                                16
#define SGMII_DEBUG_RX_SYNC_STATE_MASK                               0x00ff0000
#define SGMII_DEBUG_RX_SYNC_STATE_GET(x)                             (((x) & SGMII_DEBUG_RX_SYNC_STATE_MASK) >> SGMII_DEBUG_RX_SYNC_STATE_LSB)
#define SGMII_DEBUG_RX_SYNC_STATE_SET(x)                             (((x) << SGMII_DEBUG_RX_SYNC_STATE_LSB) & SGMII_DEBUG_RX_SYNC_STATE_MASK)
#define SGMII_DEBUG_RX_SYNC_STATE_RESET                              0x0 // 0
#define SGMII_DEBUG_RX_STATE_MSB                                     15
#define SGMII_DEBUG_RX_STATE_LSB                                     8
#define SGMII_DEBUG_RX_STATE_MASK                                    0x0000ff00
#define SGMII_DEBUG_RX_STATE_GET(x)                                  (((x) & SGMII_DEBUG_RX_STATE_MASK) >> SGMII_DEBUG_RX_STATE_LSB)
#define SGMII_DEBUG_RX_STATE_SET(x)                                  (((x) << SGMII_DEBUG_RX_STATE_LSB) & SGMII_DEBUG_RX_STATE_MASK)
#define SGMII_DEBUG_RX_STATE_RESET                                   0x0 // 0
#define SGMII_DEBUG_TX_STATE_MSB                                     7
#define SGMII_DEBUG_TX_STATE_LSB                                     0
#define SGMII_DEBUG_TX_STATE_MASK                                    0x000000ff
#define SGMII_DEBUG_TX_STATE_GET(x)                                  (((x) & SGMII_DEBUG_TX_STATE_MASK) >> SGMII_DEBUG_TX_STATE_LSB)
#define SGMII_DEBUG_TX_STATE_SET(x)                                  (((x) << SGMII_DEBUG_TX_STATE_LSB) & SGMII_DEBUG_TX_STATE_MASK)
#define SGMII_DEBUG_TX_STATE_RESET                                   0x0 // 0
#define SGMII_DEBUG_ADDRESS                                          0x18070058
#define SGMII_DEBUG_OFFSET                                           0x0058



// 32'h18070060 (SGMII_INTERRUPT_MASK)
#define SGMII_INTERRUPT_MASK_MASK_MSB                                7
#define SGMII_INTERRUPT_MASK_MASK_LSB                                0
#define SGMII_INTERRUPT_MASK_MASK_MASK                               0x000000ff
#define SGMII_INTERRUPT_MASK_MASK_GET(x)                             (((x) & SGMII_INTERRUPT_MASK_MASK_MASK) >> SGMII_INTERRUPT_MASK_MASK_LSB)
#define SGMII_INTERRUPT_MASK_MASK_SET(x)                             (((x) << SGMII_INTERRUPT_MASK_MASK_LSB) & SGMII_INTERRUPT_MASK_MASK_MASK)
#define SGMII_INTERRUPT_MASK_MASK_RESET                              0x0 // 0
#define SGMII_INTERRUPT_MASK_ADDRESS                                 0x18070060




// 32'h1807005c (SGMII_INTERRUPT)
#define SGMII_INTERRUPT_INTR_MSB                                     7
#define SGMII_INTERRUPT_INTR_LSB                                     0
#define SGMII_INTERRUPT_INTR_MASK                                    0x000000ff
#define SGMII_INTERRUPT_INTR_GET(x)                                  (((x) & SGMII_INTERRUPT_INTR_MASK) >> SGMII_INTERRUPT_INTR_LSB)
#define SGMII_INTERRUPT_INTR_SET(x)                                  (((x) << SGMII_INTERRUPT_INTR_LSB) & SGMII_INTERRUPT_INTR_MASK)
#define SGMII_INTERRUPT_INTR_RESET                                   0x0 // 0
#define SGMII_INTERRUPT_ADDRESS                                      0x1807005c
#define SGMII_INTERRUPT_OFFSET                                       0x005c
// SW modifiable bits
#define SGMII_INTERRUPT_SW_MASK                                      0x000000ff
// bits defined at reset
#define SGMII_INTERRUPT_RSTMASK                                      0xffffffff
// reset value (ignore bits undefined at reset)
#define SGMII_INTERRUPT_RESET                                        0x00000000

// 32'h18070060 (SGMII_INTERRUPT_MASK)
#define SGMII_INTERRUPT_MASK_MASK_MSB                                7
#define SGMII_INTERRUPT_MASK_MASK_LSB                                0
#define SGMII_INTERRUPT_MASK_MASK_MASK                               0x000000ff
#define SGMII_INTERRUPT_MASK_MASK_GET(x)                             (((x) & SGMII_INTERRUPT_MASK_MASK_MASK) >> SGMII_INTERRUPT_MASK_MASK_LSB)
#define SGMII_INTERRUPT_MASK_MASK_SET(x)                             (((x) << SGMII_INTERRUPT_MASK_MASK_LSB) & SGMII_INTERRUPT_MASK_MASK_MASK)
#define SGMII_INTERRUPT_MASK_MASK_RESET                              0x0 // 0
#define SGMII_INTERRUPT_MASK_ADDRESS                                 0x18070060


#define SGMII_LINK_FAIL				(1 << 0)
#define SGMII_DUPLEX_ERR			(1 << 1)
#define SGMII_MR_AN_COMPLETE			(1 << 2)
#define SGMII_LINK_MAC_CHANGE			(1 << 3)
#define SGMII_DUPLEX_MODE_CHANGE		(1 << 4)
#define SGMII_SPEED_MODE_MAC_CHANGE		(1 << 5)
#define SGMII_RX_QUIET_CHANGE			(1 << 6)
#define SGMII_RX_MDIO_COMP_CHANGE		(1 << 7)

#define SGMII_INTR				SGMII_LINK_FAIL | \
						SGMII_LINK_MAC_CHANGE | \
						SGMII_DUPLEX_MODE_CHANGE | \
						SGMII_SPEED_MODE_MAC_CHANGE


// 32'h18050048 (ETH_SGMII)
#define ETH_SGMII_TX_INVERT_MSB                                      31
#define ETH_SGMII_TX_INVERT_LSB                                      31
#define ETH_SGMII_TX_INVERT_MASK                                     0x80000000
#define ETH_SGMII_TX_INVERT_GET(x)                                   (((x) & ETH_SGMII_TX_INVERT_MASK) >> ETH_SGMII_TX_INVERT_LSB)
#define ETH_SGMII_TX_INVERT_SET(x)                                   (((x) << ETH_SGMII_TX_INVERT_LSB) & ETH_SGMII_TX_INVERT_MASK)
#define ETH_SGMII_TX_INVERT_RESET                                    0x0 // 0
#define ETH_SGMII_GIGE_QUAD_MSB                                      30
#define ETH_SGMII_GIGE_QUAD_LSB                                      30
#define ETH_SGMII_GIGE_QUAD_MASK                                     0x40000000
#define ETH_SGMII_GIGE_QUAD_GET(x)                                   (((x) & ETH_SGMII_GIGE_QUAD_MASK) >> ETH_SGMII_GIGE_QUAD_LSB)
#define ETH_SGMII_GIGE_QUAD_SET(x)                                   (((x) << ETH_SGMII_GIGE_QUAD_LSB) & ETH_SGMII_GIGE_QUAD_MASK)
#define ETH_SGMII_GIGE_QUAD_RESET                                    0x0 // 0
#define ETH_SGMII_RX_DELAY_MSB                                       29
#define ETH_SGMII_RX_DELAY_LSB                                       28
#define ETH_SGMII_RX_DELAY_MASK                                      0x30000000
#define ETH_SGMII_RX_DELAY_GET(x)                                    (((x) & ETH_SGMII_RX_DELAY_MASK) >> ETH_SGMII_RX_DELAY_LSB)
#define ETH_SGMII_RX_DELAY_SET(x)                                    (((x) << ETH_SGMII_RX_DELAY_LSB) & ETH_SGMII_RX_DELAY_MASK)
#define ETH_SGMII_RX_DELAY_RESET                                     0x0 // 0
#define ETH_SGMII_TX_DELAY_MSB                                       27
#define ETH_SGMII_TX_DELAY_LSB                                       26
#define ETH_SGMII_TX_DELAY_MASK                                      0x0c000000
#define ETH_SGMII_TX_DELAY_GET(x)                                    (((x) & ETH_SGMII_TX_DELAY_MASK) >> ETH_SGMII_TX_DELAY_LSB)
#define ETH_SGMII_TX_DELAY_SET(x)                                    (((x) << ETH_SGMII_TX_DELAY_LSB) & ETH_SGMII_TX_DELAY_MASK)
#define ETH_SGMII_TX_DELAY_RESET                                     0x0 // 0
#define ETH_SGMII_CLK_SEL_MSB                                        25
#define ETH_SGMII_CLK_SEL_LSB                                        25
#define ETH_SGMII_CLK_SEL_MASK                                       0x02000000
#define ETH_SGMII_CLK_SEL_GET(x)                                     (((x) & ETH_SGMII_CLK_SEL_MASK) >> ETH_SGMII_CLK_SEL_LSB)
#define ETH_SGMII_CLK_SEL_SET(x)                                     (((x) << ETH_SGMII_CLK_SEL_LSB) & ETH_SGMII_CLK_SEL_MASK)
#define ETH_SGMII_CLK_SEL_RESET                                      0x1 // 1
#define ETH_SGMII_GIGE_MSB                                           24
#define ETH_SGMII_GIGE_LSB                                           24
#define ETH_SGMII_GIGE_MASK                                          0x01000000
#define ETH_SGMII_GIGE_GET(x)                                        (((x) & ETH_SGMII_GIGE_MASK) >> ETH_SGMII_GIGE_LSB)
#define ETH_SGMII_GIGE_SET(x)                                        (((x) << ETH_SGMII_GIGE_LSB) & ETH_SGMII_GIGE_MASK)
#define ETH_SGMII_GIGE_RESET                                         0x1 // 1
#define ETH_SGMII_PHASE1_COUNT_MSB                                   15
#define ETH_SGMII_PHASE1_COUNT_LSB                                   8
#define ETH_SGMII_PHASE1_COUNT_MASK                                  0x0000ff00
#define ETH_SGMII_PHASE1_COUNT_GET(x)                                (((x) & ETH_SGMII_PHASE1_COUNT_MASK) >> ETH_SGMII_PHASE1_COUNT_LSB)
#define ETH_SGMII_PHASE1_COUNT_SET(x)                                (((x) << ETH_SGMII_PHASE1_COUNT_LSB) & ETH_SGMII_PHASE1_COUNT_MASK)
#define ETH_SGMII_PHASE1_COUNT_RESET                                 0x1 // 1
#define ETH_SGMII_PHASE0_COUNT_MSB                                   7
#define ETH_SGMII_PHASE0_COUNT_LSB                                   0
#define ETH_SGMII_PHASE0_COUNT_MASK                                  0x000000ff
#define ETH_SGMII_PHASE0_COUNT_GET(x)                                (((x) & ETH_SGMII_PHASE0_COUNT_MASK) >> ETH_SGMII_PHASE0_COUNT_LSB)
#define ETH_SGMII_PHASE0_COUNT_SET(x)                                (((x) << ETH_SGMII_PHASE0_COUNT_LSB) & ETH_SGMII_PHASE0_COUNT_MASK)
#define ETH_SGMII_PHASE0_COUNT_RESET                                 0x1 // 1
#define ETH_SGMII_ADDRESS                                            0x18050048

#define OTP_MEM_0_OTP_MEM_MSB				31
#define OTP_MEM_0_OTP_MEM_LSB				0
#define OTP_MEM_0_OTP_MEM_MASK				0xffffffff
#define OTP_MEM_0_OTP_MEM_GET(x)			(((x) & OTP_MEM_0_OTP_MEM_MASK) >> OTP_MEM_0_OTP_MEM_LSB)
#define OTP_MEM_0_OTP_MEM_SET(x)			(((x) << OTP_MEM_0_OTP_MEM_LSB) & OTP_MEM_0_OTP_MEM_MASK)
#define OTP_MEM_0_ADDRESS				0x18130000

#define OTP_INTF0_EFUSE_WR_ENABLE_REG_V_MSB		31
#define OTP_INTF0_EFUSE_WR_ENABLE_REG_V_LSB		0
#define OTP_INTF0_EFUSE_WR_ENABLE_REG_V_MASK		0xffffffff
#define OTP_INTF0_EFUSE_WR_ENABLE_REG_V_GET(x)		(((x) & OTP_INTF0_EFUSE_WR_ENABLE_REG_V_MASK) >> OTP_INTF0_EFUSE_WR_ENABLE_REG_V_LSB)
#define OTP_INTF0_EFUSE_WR_ENABLE_REG_V_SET(x)		(((x) << OTP_INTF0_EFUSE_WR_ENABLE_REG_V_LSB) & OTP_INTF0_EFUSE_WR_ENABLE_REG_V_MASK)
#define OTP_INTF0_ADDRESS				0x18131000

#define OTP_INTF1_BITMASK_WR_REG_V_MSB			31
#define OTP_INTF1_BITMASK_WR_REG_V_LSB			0
#define OTP_INTF1_BITMASK_WR_REG_V_MASK			0xffffffff
#define OTP_INTF1_BITMASK_WR_REG_V_GET(x)		(((x) & OTP_INTF1_BITMASK_WR_REG_V_MASK) >> OTP_INTF1_BITMASK_WR_REG_V_LSB)
#define OTP_INTF1_BITMASK_WR_REG_V_SET(x)		(((x) << OTP_INTF1_BITMASK_WR_REG_V_LSB) & OTP_INTF1_BITMASK_WR_REG_V_MASK)
#define OTP_INTF1_ADDRESS				0x18131004

#define OTP_INTF2_PG_STROBE_PW_REG_V_MSB		31
#define OTP_INTF2_PG_STROBE_PW_REG_V_LSB		0
#define OTP_INTF2_PG_STROBE_PW_REG_V_MASK		0xffffffff
#define OTP_INTF2_PG_STROBE_PW_REG_V_GET(x)		(((x) & OTP_INTF2_PG_STROBE_PW_REG_V_MASK) >> OTP_INTF2_PG_STROBE_PW_REG_V_LSB)
#define OTP_INTF2_PG_STROBE_PW_REG_V_SET(x)		(((x) << OTP_INTF2_PG_STROBE_PW_REG_V_LSB) & OTP_INTF2_PG_STROBE_PW_REG_V_MASK)
#define OTP_INTF2_ADDRESS				0x18131008

#define OTP_INTF3_RD_STROBE_PW_REG_V_MSB		31
#define OTP_INTF3_RD_STROBE_PW_REG_V_LSB		0
#define OTP_INTF3_RD_STROBE_PW_REG_V_MASK		0xffffffff
#define OTP_INTF3_RD_STROBE_PW_REG_V_GET(x)		(((x) & OTP_INTF3_RD_STROBE_PW_REG_V_MASK) >> OTP_INTF3_RD_STROBE_PW_REG_V_LSB)
#define OTP_INTF3_RD_STROBE_PW_REG_V_SET(x)		(((x) << OTP_INTF3_RD_STROBE_PW_REG_V_LSB) & OTP_INTF3_RD_STROBE_PW_REG_V_MASK)
#define OTP_INTF3_ADDRESS				0x1813100c

#define OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_MSB		31
#define OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_LSB		0
#define OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_MASK		0xffffffff
#define OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_GET(x)		(((x) & OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_MASK) >> OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_LSB)
#define OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_SET(x)		(((x) << OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_LSB) & OTP_INTF4_VDDQ_SETTLE_TIME_REG_V_MASK)
#define OTP_INTF4_ADDRESS				0x18131010

#define OTP_INTF5_EFUSE_INT_ENABLE_REG_V_MSB		0
#define OTP_INTF5_EFUSE_INT_ENABLE_REG_V_LSB		0
#define OTP_INTF5_EFUSE_INT_ENABLE_REG_V_MASK		0x00000001
#define OTP_INTF5_EFUSE_INT_ENABLE_REG_V_GET(x)		(((x) & OTP_INTF5_EFUSE_INT_ENABLE_REG_V_MASK) >> OTP_INTF5_EFUSE_INT_ENABLE_REG_V_LSB)
#define OTP_INTF5_EFUSE_INT_ENABLE_REG_V_SET(x)		(((x) << OTP_INTF5_EFUSE_INT_ENABLE_REG_V_LSB) & OTP_INTF5_EFUSE_INT_ENABLE_REG_V_MASK)
#define OTP_INTF5_ADDRESS				0x18131014

#define OTP_STATUS0_EFUSE_READ_DATA_VALID_MSB                        2
#define OTP_STATUS0_EFUSE_READ_DATA_VALID_LSB                        2
#define OTP_STATUS0_EFUSE_READ_DATA_VALID_MASK                       0x00000004
#define OTP_STATUS0_EFUSE_READ_DATA_VALID_GET(x)                     (((x) & OTP_STATUS0_EFUSE_READ_DATA_VALID_MASK) >> OTP_STATUS0_EFUSE_READ_DATA_VALID_LSB)
#define OTP_STATUS0_EFUSE_READ_DATA_VALID_SET(x)                     (((x) << OTP_STATUS0_EFUSE_READ_DATA_VALID_LSB) & OTP_STATUS0_EFUSE_READ_DATA_VALID_MASK)
#define OTP_STATUS0_EFUSE_READ_DATA_VALID_RESET                      0x0 // 0
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_MSB                            1
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_LSB                            1
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_MASK                           0x00000002
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_GET(x)                         (((x) & OTP_STATUS0_EFUSE_ACCESS_BUSY_MASK) >> OTP_STATUS0_EFUSE_ACCESS_BUSY_LSB)
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_SET(x)                         (((x) << OTP_STATUS0_EFUSE_ACCESS_BUSY_LSB) & OTP_STATUS0_EFUSE_ACCESS_BUSY_MASK)
#define OTP_STATUS0_EFUSE_ACCESS_BUSY_RESET                          0x0 // 0
#define OTP_STATUS0_OTP_SM_BUSY_MSB                                  0
#define OTP_STATUS0_OTP_SM_BUSY_LSB                                  0
#define OTP_STATUS0_OTP_SM_BUSY_MASK                                 0x00000001
#define OTP_STATUS0_OTP_SM_BUSY_GET(x)                               (((x) & OTP_STATUS0_OTP_SM_BUSY_MASK) >> OTP_STATUS0_OTP_SM_BUSY_LSB)
#define OTP_STATUS0_OTP_SM_BUSY_SET(x)                               (((x) << OTP_STATUS0_OTP_SM_BUSY_LSB) & OTP_STATUS0_OTP_SM_BUSY_MASK)
#define OTP_STATUS0_OTP_SM_BUSY_RESET                                0x0 // 0
#define OTP_STATUS0_ADDRESS                                          0x18131018

#define OTP_STATUS1_EFUSE_READ_DATA_MSB			31
#define OTP_STATUS1_EFUSE_READ_DATA_LSB			0
#define OTP_STATUS1_EFUSE_READ_DATA_MASK		0xffffffff
#define OTP_STATUS1_EFUSE_READ_DATA_GET(x)		(((x) & OTP_STATUS1_EFUSE_READ_DATA_MASK) >> OTP_STATUS1_EFUSE_READ_DATA_LSB)
#define OTP_STATUS1_EFUSE_READ_DATA_SET(x)		(((x) << OTP_STATUS1_EFUSE_READ_DATA_LSB) & OTP_STATUS1_EFUSE_READ_DATA_MASK)
#define OTP_STATUS1_ADDRESS				0x1813101c

#define OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_MSB		31
#define OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_LSB		0
#define OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_MASK	0xffffffff
#define OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_GET(x)	(((x) & OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_MASK) >> OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_LSB)
#define OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_SET(x)	(((x) << OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_LSB) & OTP_INTF6_BACK_TO_BACK_ACCESS_DELAY_MASK)
#define OTP_INTF6_ADDRESS				0x18131020

#define OTP_LDO_CONTROL_ENABLE_MSB			0
#define OTP_LDO_CONTROL_ENABLE_LSB			0
#define OTP_LDO_CONTROL_ENABLE_MASK			0x00000001
#define OTP_LDO_CONTROL_ENABLE_GET(x)			(((x) & OTP_LDO_CONTROL_ENABLE_MASK) >> OTP_LDO_CONTROL_ENABLE_LSB)
#define OTP_LDO_CONTROL_ENABLE_SET(x)			(((x) << OTP_LDO_CONTROL_ENABLE_LSB) & OTP_LDO_CONTROL_ENABLE_MASK)
#define OTP_LDO_CONTROL_ADDRESS				0x18131024

#define OTP_LDO_POWER_GOOD_DELAY_MSB			11
#define OTP_LDO_POWER_GOOD_DELAY_LSB			0
#define OTP_LDO_POWER_GOOD_DELAY_MASK			0x00000fff
#define OTP_LDO_POWER_GOOD_DELAY_GET(x)			(((x) & OTP_LDO_POWER_GOOD_DELAY_MASK) >> OTP_LDO_POWER_GOOD_DELAY_LSB)
#define OTP_LDO_POWER_GOOD_DELAY_SET(x)			(((x) << OTP_LDO_POWER_GOOD_DELAY_LSB) & OTP_LDO_POWER_GOOD_DELAY_MASK)
#define OTP_LDO_POWER_GOOD_ADDRESS			0x18131028

#define OTP_LDO_STATUS_POWER_ON_MSB                                  0
#define OTP_LDO_STATUS_POWER_ON_LSB                                  0
#define OTP_LDO_STATUS_POWER_ON_MASK                                 0x00000001
#define OTP_LDO_STATUS_POWER_ON_GET(x)                               (((x) & OTP_LDO_STATUS_POWER_ON_MASK) >> OTP_LDO_STATUS_POWER_ON_LSB)
#define OTP_LDO_STATUS_POWER_ON_SET(x)                               (((x) << OTP_LDO_STATUS_POWER_ON_LSB) & OTP_LDO_STATUS_POWER_ON_MASK)
#define OTP_LDO_STATUS_POWER_ON_RESET                                0x0 // 0
#define OTP_LDO_STATUS_ADDRESS                                       0x1813102c

#define OTP_VDDQ_HOLD_TIME_DELAY_MSB			31
#define OTP_VDDQ_HOLD_TIME_DELAY_LSB			0
#define OTP_VDDQ_HOLD_TIME_DELAY_MASK			0xffffffff
#define OTP_VDDQ_HOLD_TIME_DELAY_GET(x)			(((x) & OTP_VDDQ_HOLD_TIME_DELAY_MASK) >> OTP_VDDQ_HOLD_TIME_DELAY_LSB)
#define OTP_VDDQ_HOLD_TIME_DELAY_SET(x)			(((x) << OTP_VDDQ_HOLD_TIME_DELAY_LSB) & OTP_VDDQ_HOLD_TIME_DELAY_MASK)
#define OTP_VDDQ_HOLD_TIME_ADDRESS			0x18131030

#define OTP_PGENB_SETUP_HOLD_TIME_DELAY_MSB		31
#define OTP_PGENB_SETUP_HOLD_TIME_DELAY_LSB		0
#define OTP_PGENB_SETUP_HOLD_TIME_DELAY_MASK		0xffffffff
#define OTP_PGENB_SETUP_HOLD_TIME_DELAY_GET(x)		(((x) & OTP_PGENB_SETUP_HOLD_TIME_DELAY_MASK) >> OTP_PGENB_SETUP_HOLD_TIME_DELAY_LSB)
#define OTP_PGENB_SETUP_HOLD_TIME_DELAY_SET(x)		(((x) << OTP_PGENB_SETUP_HOLD_TIME_DELAY_LSB) & OTP_PGENB_SETUP_HOLD_TIME_DELAY_MASK)
#define OTP_PGENB_SETUP_HOLD_TIME_ADDRESS		0x18131034

#define OTP_STROBE_PULSE_INTERVAL_DELAY_MSB		31
#define OTP_STROBE_PULSE_INTERVAL_DELAY_LSB		0
#define OTP_STROBE_PULSE_INTERVAL_DELAY_MASK		0xffffffff
#define OTP_STROBE_PULSE_INTERVAL_DELAY_GET(x)		(((x) & OTP_STROBE_PULSE_INTERVAL_DELAY_MASK) >> OTP_STROBE_PULSE_INTERVAL_DELAY_LSB)
#define OTP_STROBE_PULSE_INTERVAL_DELAY_SET(x)		(((x) << OTP_STROBE_PULSE_INTERVAL_DELAY_LSB) & OTP_STROBE_PULSE_INTERVAL_DELAY_MASK)
#define OTP_STROBE_PULSE_INTERVAL_ADDRESS		0x18131038

#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_MSB		31
#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_LSB		0
#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_MASK		0xffffffff
#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_GET(x)	(((x) & OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_MASK) >> OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_LSB)
#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_SET(x)	(((x) << OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_LSB) & OTP_CSB_ADDR_LOAD_SETUP_HOLD_DELAY_MASK)
#define OTP_CSB_ADDR_LOAD_SETUP_HOLD_ADDRESS		0x1813103c

#define USB_PHY_CTRL1_USE_PLL_LOCKDETECT_MASK				0x00100000
#define USB_PHY_CTRL1_RX_LOWR_PDET_MASK					0x00000010
#define USB_PHY_CTRL1_ADDRESS						0x18116d84

#define USB2_PHY_CTRL1_USE_PLL_LOCKDETECT_MASK				0x00100000
#define USB2_PHY_CTRL1_RX_LOWR_PDET_MASK				0x00000010
#define USB2_PHY_CTRL1_ADDRESS						0x18116e44

#define USB_PHY_CTRL5					0x18116d94
#define USB2_PHY_CTRL5					0x18116e54

#define GPIO_FUNCTION_STEREO_EN			(1<<17)
#define GPIO_FUNCTION_SLIC_EN			(1<<16)
#define GPIO_FUNCTION_OVERCURRENT_EN		(1<< 4)
#define GPIO_FUNCTION_USB_CLK_CORE_EN		(1<< 0)
#define GPIO_FUNCTION_WMAC_LED			(1<<22)
#define GPIO_FUNCTION_STEREO_EN			(1<<17)
#define GPIO_FUNCTION_SLIC_EN			(1<<16)
#define GPIO_FUNCTION_SPDIF2TCK_EN			(1<<31)
#define GPIO_FUNCTION_SPDIF_EN			(1<<30)
#define GPIO_FUNCTION_I2S_GPIO_18_22_EN		(1<<29)
#define GPIO_FUNCTION_I2S_REFCLKEN			(1<<28)
#define GPIO_FUNCTION_I2S_MCKEN			(1<<27)
#define GPIO_FUNCTION_I2S0_EN			(1<<26)
#define GPIO_FUNCTION_ETH_SWITCH_LED_DUPL_EN	(1<<25)
#define GPIO_FUNCTION_ETH_SWITCH_LED_COLL		(1<<24)
#define GPIO_FUNCTION_ETH_SWITCH_LED_ACTV		(1<<23)
#define GPIO_FUNCTION_PLL_SHIFT_EN			(1<<22)
#define GPIO_FUNCTION_EXT_MDIO_SEL			(1<<21)
#define GPIO_FUNCTION_CLK_OBS6_ENABLE		(1<<20)
#define GPIO_FUNCTION_CLK_OBS0_ENABLE		(1<<19)
#define GPIO_FUNCTION_SPI_EN			(1<<18)
#define GPIO_FUNCTION_DDR_DQOE_EN			(1<<17)
#define GPIO_FUNCTION_PCIEPHY_TST_EN		(1<<16)
#define GPIO_FUNCTION_S26_UART_DISABLE		(1<<15)
#define GPIO_FUNCTION_SPI_CS_1_EN			(1<<14)
#define GPIO_FUNCTION_SPI_CS_0_EN			(1<<13)
#define GPIO_FUNCTION_CLK_OBS5_ENABLE		(1<<12)
#define GPIO_FUNCTION_CLK_OBS4_ENABLE		(1<<11)
#define GPIO_FUNCTION_CLK_OBS3_ENABLE		(1<<10)
#define GPIO_FUNCTION_CLK_OBS2_ENABLE		(1<< 9)
#define GPIO_FUNCTION_CLK_OBS1_ENABLE		(1<< 8)
#define GPIO_FUNCTION_ETH_SWITCH_LED4_EN		(1<< 7)
#define GPIO_FUNCTION_ETH_SWITCH_LED3_EN		(1<< 6)
#define GPIO_FUNCTION_ETH_SWITCH_LED2_EN		(1<< 5)
#define GPIO_FUNCTION_ETH_SWITCH_LED1_EN		(1<< 4)
#define GPIO_FUNCTION_ETH_SWITCH_LED0_EN		(1<< 3)
#define GPIO_FUNCTION_UART_RTS_CTS_EN		(1<< 2)
#define GPIO_FUNCTION_UART_EN			(1<< 1)
#define GPIO_FUNCTION_2_EN_I2WS_ON_0		(1<< 4)
#define GPIO_FUNCTION_2_EN_I2SCK_ON_1		(1<< 3)
#define GPIO_FUNCTION_2_I2S_ON_LED			(1<< 1)
#define GPIO_FUNCTION_SRIF_ENABLE			(1<< 0)
#define GPIO_FUNCTION_JTAG_DISABLE			(1<< 1)
#define GPIO_FUNCTION_USB_LED			(1<< 4)
#define GPIO_FUNCTION_JTAG_DISABLE			(1<< 1)

#define RESET_SLIC			(1 << 30)
#define RESET_EXTERNAL		(1 << 28)
#define RESET_FULL_CHIP		(1 << 24)
#define RESET_GE0_MDIO		(1 << 22)
#define RESET_CPU_NMI		(1 << 21)
#define RESET_CPU_COLD_RESET_MASK	(1 << 20)
#define RESET_DMA			(1 << 19)
#define RESET_STEREO		(1 << 17)
#define RESET_DDR			(1 << 16)
#define RESET_GE1_MAC		(1 << 13)
#define RESET_GE1_PHY		(1 << 12)
#define RESET_USB_PHY_ANALOG	(1 << 11)
#define RESET_PCIE_PHY_SHIFT	(1 << 10)
#define RESET_GE0_MAC		(1 << 9)
#define RESET_GE0_PHY		(1 << 8)
#define RESET_USBSUS_OVRIDE		(1 << 3)
#define RESET_USB_OHCI_DLL		(1 << 3)
#define RESET_USB_HOST		(1 << 5)
#define RESET_USB_PHY		(1 << 4)
#define RESET_PCI_BUS		(1 << 1)
#define RESET_PCI_CORE		(1 << 0)
#define RESET_I2S			(1 << 0)

#endif /* _QCA955X_H */
