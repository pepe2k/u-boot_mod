/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _QCA953X_H
#define _QCA953X_H

#ifndef __ASSEMBLY__
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/types.h>
#include <linux/types.h>
#endif /* __ASSEMBLY__ */

#undef is_qca953x
#undef is_hb

#define is_qca953x()	(1)
#define is_hb()		(1)


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
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_MSB                          16
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_LSB                          16
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_MASK                         0x00010000
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_GET(x)                       (((x) & DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_MASK) >> DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_LSB)
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_SET(x)                       (((x) << DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_LSB) & DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_MASK)
#define DDR_DEBUG_RD_CNTL_CK_P_PDLY_BYP_RESET                        0x0 // 0
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_MSB                     15
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_LSB                     15
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_MASK                    0x00008000
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_GET(x)                  (((x) & DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_MASK) >> DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_LSB)
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_SET(x)                  (((x) << DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_LSB) & DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_MASK)
#define DDR_DEBUG_RD_CNTL_GATE_OPEN_PDLY_BYP_RESET                   0x0 // 0
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

#define BB_DPLL2_LOCAL_PLL_MSB                                       31
#define BB_DPLL2_LOCAL_PLL_LSB                                       31
#define BB_DPLL2_LOCAL_PLL_MASK                                      0x80000000
#define BB_DPLL2_LOCAL_PLL_GET(x)                                    (((x) & BB_DPLL2_LOCAL_PLL_MASK) >> BB_DPLL2_LOCAL_PLL_LSB)
#define BB_DPLL2_LOCAL_PLL_SET(x)                                    (((x) << BB_DPLL2_LOCAL_PLL_LSB) & BB_DPLL2_LOCAL_PLL_MASK)
#define BB_DPLL2_LOCAL_PLL_RESET                                     0x0 // 0
#define BB_DPLL2_KI_MSB                                              30
#define BB_DPLL2_KI_LSB                                              29
#define BB_DPLL2_KI_MASK                                             0x60000000
#define BB_DPLL2_KI_GET(x)                                           (((x) & BB_DPLL2_KI_MASK) >> BB_DPLL2_KI_LSB)
#define BB_DPLL2_KI_SET(x)                                           (((x) << BB_DPLL2_KI_LSB) & BB_DPLL2_KI_MASK)
#define BB_DPLL2_KI_RESET                                            0x2 // 2
#define BB_DPLL2_KD_MSB                                              28
#define BB_DPLL2_KD_LSB                                              25
#define BB_DPLL2_KD_MASK                                             0x1e000000
#define BB_DPLL2_KD_GET(x)                                           (((x) & BB_DPLL2_KD_MASK) >> BB_DPLL2_KD_LSB)
#define BB_DPLL2_KD_SET(x)                                           (((x) << BB_DPLL2_KD_LSB) & BB_DPLL2_KD_MASK)
#define BB_DPLL2_KD_RESET                                            0xa // 10
#define BB_DPLL2_EN_NEGTRIG_MSB                                      24
#define BB_DPLL2_EN_NEGTRIG_LSB                                      24
#define BB_DPLL2_EN_NEGTRIG_MASK                                     0x01000000
#define BB_DPLL2_EN_NEGTRIG_GET(x)                                   (((x) & BB_DPLL2_EN_NEGTRIG_MASK) >> BB_DPLL2_EN_NEGTRIG_LSB)
#define BB_DPLL2_EN_NEGTRIG_SET(x)                                   (((x) << BB_DPLL2_EN_NEGTRIG_LSB) & BB_DPLL2_EN_NEGTRIG_MASK)
#define BB_DPLL2_EN_NEGTRIG_RESET                                    0x0 // 0
#define BB_DPLL2_SEL_1SDM_MSB                                        23
#define BB_DPLL2_SEL_1SDM_LSB                                        23
#define BB_DPLL2_SEL_1SDM_MASK                                       0x00800000
#define BB_DPLL2_SEL_1SDM_GET(x)                                     (((x) & BB_DPLL2_SEL_1SDM_MASK) >> BB_DPLL2_SEL_1SDM_LSB)
#define BB_DPLL2_SEL_1SDM_SET(x)                                     (((x) << BB_DPLL2_SEL_1SDM_LSB) & BB_DPLL2_SEL_1SDM_MASK)
#define BB_DPLL2_SEL_1SDM_RESET                                      0x0 // 0
#define BB_DPLL2_PLL_PWD_MSB                                         22
#define BB_DPLL2_PLL_PWD_LSB                                         22
#define BB_DPLL2_PLL_PWD_MASK                                        0x00400000
#define BB_DPLL2_PLL_PWD_GET(x)                                      (((x) & BB_DPLL2_PLL_PWD_MASK) >> BB_DPLL2_PLL_PWD_LSB)
#define BB_DPLL2_PLL_PWD_SET(x)                                      (((x) << BB_DPLL2_PLL_PWD_LSB) & BB_DPLL2_PLL_PWD_MASK)
#define BB_DPLL2_PLL_PWD_RESET                                       0x1 // 1
#define BB_DPLL2_OUTDIV_MSB                                          21
#define BB_DPLL2_OUTDIV_LSB                                          19
#define BB_DPLL2_OUTDIV_MASK                                         0x00380000
#define BB_DPLL2_OUTDIV_GET(x)                                       (((x) & BB_DPLL2_OUTDIV_MASK) >> BB_DPLL2_OUTDIV_LSB)
#define BB_DPLL2_OUTDIV_SET(x)                                       (((x) << BB_DPLL2_OUTDIV_LSB) & BB_DPLL2_OUTDIV_MASK)
#define BB_DPLL2_OUTDIV_RESET                                        0x1 // 1
#define BB_DPLL2_PHASE_SHIFT_MSB                                     18
#define BB_DPLL2_PHASE_SHIFT_LSB                                     12
#define BB_DPLL2_PHASE_SHIFT_MASK                                    0x0007f000
#define BB_DPLL2_PHASE_SHIFT_GET(x)                                  (((x) & BB_DPLL2_PHASE_SHIFT_MASK) >> BB_DPLL2_PHASE_SHIFT_LSB)
#define BB_DPLL2_PHASE_SHIFT_SET(x)                                  (((x) << BB_DPLL2_PHASE_SHIFT_LSB) & BB_DPLL2_PHASE_SHIFT_MASK)
#define BB_DPLL2_PHASE_SHIFT_RESET                                   0x0 // 0
#define BB_DPLL2_TESTIN_MSB                                          11
#define BB_DPLL2_TESTIN_LSB                                          2
#define BB_DPLL2_TESTIN_MASK                                         0x00000ffc
#define BB_DPLL2_TESTIN_GET(x)                                       (((x) & BB_DPLL2_TESTIN_MASK) >> BB_DPLL2_TESTIN_LSB)
#define BB_DPLL2_TESTIN_SET(x)                                       (((x) << BB_DPLL2_TESTIN_LSB) & BB_DPLL2_TESTIN_MASK)
#define BB_DPLL2_TESTIN_RESET                                        0x0 // 0
#define BB_DPLL2_SEL_COUNT_MSB                                       1
#define BB_DPLL2_SEL_COUNT_LSB                                       1
#define BB_DPLL2_SEL_COUNT_MASK                                      0x00000002
#define BB_DPLL2_SEL_COUNT_GET(x)                                    (((x) & BB_DPLL2_SEL_COUNT_MASK) >> BB_DPLL2_SEL_COUNT_LSB)
#define BB_DPLL2_SEL_COUNT_SET(x)                                    (((x) << BB_DPLL2_SEL_COUNT_LSB) & BB_DPLL2_SEL_COUNT_MASK)
#define BB_DPLL2_SEL_COUNT_RESET                                     0x0 // 0
#define BB_DPLL2_RESET_TEST_MSB                                      0
#define BB_DPLL2_RESET_TEST_LSB                                      0
#define BB_DPLL2_RESET_TEST_MASK                                     0x00000001
#define BB_DPLL2_RESET_TEST_GET(x)                                   (((x) & BB_DPLL2_RESET_TEST_MASK) >> BB_DPLL2_RESET_TEST_LSB)
#define BB_DPLL2_RESET_TEST_SET(x)                                   (((x) << BB_DPLL2_RESET_TEST_LSB) & BB_DPLL2_RESET_TEST_MASK)
#define BB_DPLL2_RESET_TEST_RESET                                    0x0 // 0
#define BB_DPLL2_ADDRESS                                             0x18116184

#define PCIe_DPLL2_LOCAL_PLL_MSB                                     31
#define PCIe_DPLL2_LOCAL_PLL_LSB                                     31
#define PCIe_DPLL2_LOCAL_PLL_MASK                                    0x80000000
#define PCIe_DPLL2_LOCAL_PLL_GET(x)                                  (((x) & PCIe_DPLL2_LOCAL_PLL_MASK) >> PCIe_DPLL2_LOCAL_PLL_LSB)
#define PCIe_DPLL2_LOCAL_PLL_SET(x)                                  (((x) << PCIe_DPLL2_LOCAL_PLL_LSB) & PCIe_DPLL2_LOCAL_PLL_MASK)
#define PCIe_DPLL2_LOCAL_PLL_RESET                                   0x0 // 0
#define PCIe_DPLL2_KI_MSB                                            30
#define PCIe_DPLL2_KI_LSB                                            29
#define PCIe_DPLL2_KI_MASK                                           0x60000000
#define PCIe_DPLL2_KI_GET(x)                                         (((x) & PCIe_DPLL2_KI_MASK) >> PCIe_DPLL2_KI_LSB)
#define PCIe_DPLL2_KI_SET(x)                                         (((x) << PCIe_DPLL2_KI_LSB) & PCIe_DPLL2_KI_MASK)
#define PCIe_DPLL2_KI_RESET                                          0x2 // 2
#define PCIe_DPLL2_KD_MSB                                            28
#define PCIe_DPLL2_KD_LSB                                            25
#define PCIe_DPLL2_KD_MASK                                           0x1e000000
#define PCIe_DPLL2_KD_GET(x)                                         (((x) & PCIe_DPLL2_KD_MASK) >> PCIe_DPLL2_KD_LSB)
#define PCIe_DPLL2_KD_SET(x)                                         (((x) << PCIe_DPLL2_KD_LSB) & PCIe_DPLL2_KD_MASK)
#define PCIe_DPLL2_KD_RESET                                          0xa // 10
#define PCIe_DPLL2_EN_NEGTRIG_MSB                                    24
#define PCIe_DPLL2_EN_NEGTRIG_LSB                                    24
#define PCIe_DPLL2_EN_NEGTRIG_MASK                                   0x01000000
#define PCIe_DPLL2_EN_NEGTRIG_GET(x)                                 (((x) & PCIe_DPLL2_EN_NEGTRIG_MASK) >> PCIe_DPLL2_EN_NEGTRIG_LSB)
#define PCIe_DPLL2_EN_NEGTRIG_SET(x)                                 (((x) << PCIe_DPLL2_EN_NEGTRIG_LSB) & PCIe_DPLL2_EN_NEGTRIG_MASK)
#define PCIe_DPLL2_EN_NEGTRIG_RESET                                  0x0 // 0
#define PCIe_DPLL2_SEL_1SDM_MSB                                      23
#define PCIe_DPLL2_SEL_1SDM_LSB                                      23
#define PCIe_DPLL2_SEL_1SDM_MASK                                     0x00800000
#define PCIe_DPLL2_SEL_1SDM_GET(x)                                   (((x) & PCIe_DPLL2_SEL_1SDM_MASK) >> PCIe_DPLL2_SEL_1SDM_LSB)
#define PCIe_DPLL2_SEL_1SDM_SET(x)                                   (((x) << PCIe_DPLL2_SEL_1SDM_LSB) & PCIe_DPLL2_SEL_1SDM_MASK)
#define PCIe_DPLL2_SEL_1SDM_RESET                                    0x0 // 0
#define PCIe_DPLL2_PLL_PWD_MSB                                       22
#define PCIe_DPLL2_PLL_PWD_LSB                                       22
#define PCIe_DPLL2_PLL_PWD_MASK                                      0x00400000
#define PCIe_DPLL2_PLL_PWD_GET(x)                                    (((x) & PCIe_DPLL2_PLL_PWD_MASK) >> PCIe_DPLL2_PLL_PWD_LSB)
#define PCIe_DPLL2_PLL_PWD_SET(x)                                    (((x) << PCIe_DPLL2_PLL_PWD_LSB) & PCIe_DPLL2_PLL_PWD_MASK)
#define PCIe_DPLL2_PLL_PWD_RESET                                     0x1 // 1
#define PCIe_DPLL2_OUTDIV_MSB                                        21
#define PCIe_DPLL2_OUTDIV_LSB                                        19
#define PCIe_DPLL2_OUTDIV_MASK                                       0x00380000
#define PCIe_DPLL2_OUTDIV_GET(x)                                     (((x) & PCIe_DPLL2_OUTDIV_MASK) >> PCIe_DPLL2_OUTDIV_LSB)
#define PCIe_DPLL2_OUTDIV_SET(x)                                     (((x) << PCIe_DPLL2_OUTDIV_LSB) & PCIe_DPLL2_OUTDIV_MASK)
#define PCIe_DPLL2_OUTDIV_RESET                                      0x1 // 1
#define PCIe_DPLL2_PHASE_SHIFT_MSB                                   18
#define PCIe_DPLL2_PHASE_SHIFT_LSB                                   12
#define PCIe_DPLL2_PHASE_SHIFT_MASK                                  0x0007f000
#define PCIe_DPLL2_PHASE_SHIFT_GET(x)                                (((x) & PCIe_DPLL2_PHASE_SHIFT_MASK) >> PCIe_DPLL2_PHASE_SHIFT_LSB)
#define PCIe_DPLL2_PHASE_SHIFT_SET(x)                                (((x) << PCIe_DPLL2_PHASE_SHIFT_LSB) & PCIe_DPLL2_PHASE_SHIFT_MASK)
#define PCIe_DPLL2_PHASE_SHIFT_RESET                                 0x0 // 0
#define PCIe_DPLL2_TESTIN_MSB                                        11
#define PCIe_DPLL2_TESTIN_LSB                                        2
#define PCIe_DPLL2_TESTIN_MASK                                       0x00000ffc
#define PCIe_DPLL2_TESTIN_GET(x)                                     (((x) & PCIe_DPLL2_TESTIN_MASK) >> PCIe_DPLL2_TESTIN_LSB)
#define PCIe_DPLL2_TESTIN_SET(x)                                     (((x) << PCIe_DPLL2_TESTIN_LSB) & PCIe_DPLL2_TESTIN_MASK)
#define PCIe_DPLL2_TESTIN_RESET                                      0x0 // 0
#define PCIe_DPLL2_SEL_COUNT_MSB                                     1
#define PCIe_DPLL2_SEL_COUNT_LSB                                     1
#define PCIe_DPLL2_SEL_COUNT_MASK                                    0x00000002
#define PCIe_DPLL2_SEL_COUNT_GET(x)                                  (((x) & PCIe_DPLL2_SEL_COUNT_MASK) >> PCIe_DPLL2_SEL_COUNT_LSB)
#define PCIe_DPLL2_SEL_COUNT_SET(x)                                  (((x) << PCIe_DPLL2_SEL_COUNT_LSB) & PCIe_DPLL2_SEL_COUNT_MASK)
#define PCIe_DPLL2_SEL_COUNT_RESET                                   0x0 // 0
#define PCIe_DPLL2_RESET_TEST_MSB                                    0
#define PCIe_DPLL2_RESET_TEST_LSB                                    0
#define PCIe_DPLL2_RESET_TEST_MASK                                   0x00000001
#define PCIe_DPLL2_RESET_TEST_GET(x)                                 (((x) & PCIe_DPLL2_RESET_TEST_MASK) >> PCIe_DPLL2_RESET_TEST_LSB)
#define PCIe_DPLL2_RESET_TEST_SET(x)                                 (((x) << PCIe_DPLL2_RESET_TEST_LSB) & PCIe_DPLL2_RESET_TEST_MASK)
#define PCIe_DPLL2_RESET_TEST_RESET                                  0x0 // 0
#define PCIe_DPLL2_ADDRESS                                           0x18116c04

#define DDR_DPLL2_LOCAL_PLL_MSB                                      31
#define DDR_DPLL2_LOCAL_PLL_LSB                                      31
#define DDR_DPLL2_LOCAL_PLL_MASK                                     0x80000000
#define DDR_DPLL2_LOCAL_PLL_GET(x)                                   (((x) & DDR_DPLL2_LOCAL_PLL_MASK) >> DDR_DPLL2_LOCAL_PLL_LSB)
#define DDR_DPLL2_LOCAL_PLL_SET(x)                                   (((x) << DDR_DPLL2_LOCAL_PLL_LSB) & DDR_DPLL2_LOCAL_PLL_MASK)
#define DDR_DPLL2_LOCAL_PLL_RESET                                    0x0 // 0
#define DDR_DPLL2_KI_MSB                                             30
#define DDR_DPLL2_KI_LSB                                             29
#define DDR_DPLL2_KI_MASK                                            0x60000000
#define DDR_DPLL2_KI_GET(x)                                          (((x) & DDR_DPLL2_KI_MASK) >> DDR_DPLL2_KI_LSB)
#define DDR_DPLL2_KI_SET(x)                                          (((x) << DDR_DPLL2_KI_LSB) & DDR_DPLL2_KI_MASK)
#define DDR_DPLL2_KI_RESET                                           0x2 // 2
#define DDR_DPLL2_KD_MSB                                             28
#define DDR_DPLL2_KD_LSB                                             25
#define DDR_DPLL2_KD_MASK                                            0x1e000000
#define DDR_DPLL2_KD_GET(x)                                          (((x) & DDR_DPLL2_KD_MASK) >> DDR_DPLL2_KD_LSB)
#define DDR_DPLL2_KD_SET(x)                                          (((x) << DDR_DPLL2_KD_LSB) & DDR_DPLL2_KD_MASK)
#define DDR_DPLL2_KD_RESET                                           0xa // 10
#define DDR_DPLL2_EN_NEGTRIG_MSB                                     24
#define DDR_DPLL2_EN_NEGTRIG_LSB                                     24
#define DDR_DPLL2_EN_NEGTRIG_MASK                                    0x01000000
#define DDR_DPLL2_EN_NEGTRIG_GET(x)                                  (((x) & DDR_DPLL2_EN_NEGTRIG_MASK) >> DDR_DPLL2_EN_NEGTRIG_LSB)
#define DDR_DPLL2_EN_NEGTRIG_SET(x)                                  (((x) << DDR_DPLL2_EN_NEGTRIG_LSB) & DDR_DPLL2_EN_NEGTRIG_MASK)
#define DDR_DPLL2_EN_NEGTRIG_RESET                                   0x0 // 0
#define DDR_DPLL2_SEL_1SDM_MSB                                       23
#define DDR_DPLL2_SEL_1SDM_LSB                                       23
#define DDR_DPLL2_SEL_1SDM_MASK                                      0x00800000
#define DDR_DPLL2_SEL_1SDM_GET(x)                                    (((x) & DDR_DPLL2_SEL_1SDM_MASK) >> DDR_DPLL2_SEL_1SDM_LSB)
#define DDR_DPLL2_SEL_1SDM_SET(x)                                    (((x) << DDR_DPLL2_SEL_1SDM_LSB) & DDR_DPLL2_SEL_1SDM_MASK)
#define DDR_DPLL2_SEL_1SDM_RESET                                     0x0 // 0
#define DDR_DPLL2_PLL_PWD_MSB                                        22
#define DDR_DPLL2_PLL_PWD_LSB                                        22
#define DDR_DPLL2_PLL_PWD_MASK                                       0x00400000
#define DDR_DPLL2_PLL_PWD_GET(x)                                     (((x) & DDR_DPLL2_PLL_PWD_MASK) >> DDR_DPLL2_PLL_PWD_LSB)
#define DDR_DPLL2_PLL_PWD_SET(x)                                     (((x) << DDR_DPLL2_PLL_PWD_LSB) & DDR_DPLL2_PLL_PWD_MASK)
#define DDR_DPLL2_PLL_PWD_RESET                                      0x1 // 1
#define DDR_DPLL2_OUTDIV_MSB                                         21
#define DDR_DPLL2_OUTDIV_LSB                                         19
#define DDR_DPLL2_OUTDIV_MASK                                        0x00380000
#define DDR_DPLL2_OUTDIV_GET(x)                                      (((x) & DDR_DPLL2_OUTDIV_MASK) >> DDR_DPLL2_OUTDIV_LSB)
#define DDR_DPLL2_OUTDIV_SET(x)                                      (((x) << DDR_DPLL2_OUTDIV_LSB) & DDR_DPLL2_OUTDIV_MASK)
#define DDR_DPLL2_OUTDIV_RESET                                       0x1 // 1
#define DDR_DPLL2_PHASE_SHIFT_MSB                                    18
#define DDR_DPLL2_PHASE_SHIFT_LSB                                    12
#define DDR_DPLL2_PHASE_SHIFT_MASK                                   0x0007f000
#define DDR_DPLL2_PHASE_SHIFT_GET(x)                                 (((x) & DDR_DPLL2_PHASE_SHIFT_MASK) >> DDR_DPLL2_PHASE_SHIFT_LSB)
#define DDR_DPLL2_PHASE_SHIFT_SET(x)                                 (((x) << DDR_DPLL2_PHASE_SHIFT_LSB) & DDR_DPLL2_PHASE_SHIFT_MASK)
#define DDR_DPLL2_PHASE_SHIFT_RESET                                  0x0 // 0
#define DDR_DPLL2_TESTIN_MSB                                         11
#define DDR_DPLL2_TESTIN_LSB                                         2
#define DDR_DPLL2_TESTIN_MASK                                        0x00000ffc
#define DDR_DPLL2_TESTIN_GET(x)                                      (((x) & DDR_DPLL2_TESTIN_MASK) >> DDR_DPLL2_TESTIN_LSB)
#define DDR_DPLL2_TESTIN_SET(x)                                      (((x) << DDR_DPLL2_TESTIN_LSB) & DDR_DPLL2_TESTIN_MASK)
#define DDR_DPLL2_TESTIN_RESET                                       0x0 // 0
#define DDR_DPLL2_SEL_COUNT_MSB                                      1
#define DDR_DPLL2_SEL_COUNT_LSB                                      1
#define DDR_DPLL2_SEL_COUNT_MASK                                     0x00000002
#define DDR_DPLL2_SEL_COUNT_GET(x)                                   (((x) & DDR_DPLL2_SEL_COUNT_MASK) >> DDR_DPLL2_SEL_COUNT_LSB)
#define DDR_DPLL2_SEL_COUNT_SET(x)                                   (((x) << DDR_DPLL2_SEL_COUNT_LSB) & DDR_DPLL2_SEL_COUNT_MASK)
#define DDR_DPLL2_SEL_COUNT_RESET                                    0x0 // 0
#define DDR_DPLL2_RESET_TEST_MSB                                     0
#define DDR_DPLL2_RESET_TEST_LSB                                     0
#define DDR_DPLL2_RESET_TEST_MASK                                    0x00000001
#define DDR_DPLL2_RESET_TEST_GET(x)                                  (((x) & DDR_DPLL2_RESET_TEST_MASK) >> DDR_DPLL2_RESET_TEST_LSB)
#define DDR_DPLL2_RESET_TEST_SET(x)                                  (((x) << DDR_DPLL2_RESET_TEST_LSB) & DDR_DPLL2_RESET_TEST_MASK)
#define DDR_DPLL2_RESET_TEST_RESET                                   0x0 // 0
#define DDR_DPLL2_ADDRESS                                            0x18116244

#define CPU_DPLL2_LOCAL_PLL_MSB                                      31
#define CPU_DPLL2_LOCAL_PLL_LSB                                      31
#define CPU_DPLL2_LOCAL_PLL_MASK                                     0x80000000
#define CPU_DPLL2_LOCAL_PLL_GET(x)                                   (((x) & CPU_DPLL2_LOCAL_PLL_MASK) >> CPU_DPLL2_LOCAL_PLL_LSB)
#define CPU_DPLL2_LOCAL_PLL_SET(x)                                   (((x) << CPU_DPLL2_LOCAL_PLL_LSB) & CPU_DPLL2_LOCAL_PLL_MASK)
#define CPU_DPLL2_LOCAL_PLL_RESET                                    0x0 // 0
#define CPU_DPLL2_KI_MSB                                             30
#define CPU_DPLL2_KI_LSB                                             29
#define CPU_DPLL2_KI_MASK                                            0x60000000
#define CPU_DPLL2_KI_GET(x)                                          (((x) & CPU_DPLL2_KI_MASK) >> CPU_DPLL2_KI_LSB)
#define CPU_DPLL2_KI_SET(x)                                          (((x) << CPU_DPLL2_KI_LSB) & CPU_DPLL2_KI_MASK)
#define CPU_DPLL2_KI_RESET                                           0x2 // 2
#define CPU_DPLL2_KD_MSB                                             28
#define CPU_DPLL2_KD_LSB                                             25
#define CPU_DPLL2_KD_MASK                                            0x1e000000
#define CPU_DPLL2_KD_GET(x)                                          (((x) & CPU_DPLL2_KD_MASK) >> CPU_DPLL2_KD_LSB)
#define CPU_DPLL2_KD_SET(x)                                          (((x) << CPU_DPLL2_KD_LSB) & CPU_DPLL2_KD_MASK)
#define CPU_DPLL2_KD_RESET                                           0xa // 10
#define CPU_DPLL2_EN_NEGTRIG_MSB                                     24
#define CPU_DPLL2_EN_NEGTRIG_LSB                                     24
#define CPU_DPLL2_EN_NEGTRIG_MASK                                    0x01000000
#define CPU_DPLL2_EN_NEGTRIG_GET(x)                                  (((x) & CPU_DPLL2_EN_NEGTRIG_MASK) >> CPU_DPLL2_EN_NEGTRIG_LSB)
#define CPU_DPLL2_EN_NEGTRIG_SET(x)                                  (((x) << CPU_DPLL2_EN_NEGTRIG_LSB) & CPU_DPLL2_EN_NEGTRIG_MASK)
#define CPU_DPLL2_EN_NEGTRIG_RESET                                   0x0 // 0
#define CPU_DPLL2_SEL_1SDM_MSB                                       23
#define CPU_DPLL2_SEL_1SDM_LSB                                       23
#define CPU_DPLL2_SEL_1SDM_MASK                                      0x00800000
#define CPU_DPLL2_SEL_1SDM_GET(x)                                    (((x) & CPU_DPLL2_SEL_1SDM_MASK) >> CPU_DPLL2_SEL_1SDM_LSB)
#define CPU_DPLL2_SEL_1SDM_SET(x)                                    (((x) << CPU_DPLL2_SEL_1SDM_LSB) & CPU_DPLL2_SEL_1SDM_MASK)
#define CPU_DPLL2_SEL_1SDM_RESET                                     0x0 // 0
#define CPU_DPLL2_PLL_PWD_MSB                                        22
#define CPU_DPLL2_PLL_PWD_LSB                                        22
#define CPU_DPLL2_PLL_PWD_MASK                                       0x00400000
#define CPU_DPLL2_PLL_PWD_GET(x)                                     (((x) & CPU_DPLL2_PLL_PWD_MASK) >> CPU_DPLL2_PLL_PWD_LSB)
#define CPU_DPLL2_PLL_PWD_SET(x)                                     (((x) << CPU_DPLL2_PLL_PWD_LSB) & CPU_DPLL2_PLL_PWD_MASK)
#define CPU_DPLL2_PLL_PWD_RESET                                      0x1 // 1
#define CPU_DPLL2_OUTDIV_MSB                                         21
#define CPU_DPLL2_OUTDIV_LSB                                         19
#define CPU_DPLL2_OUTDIV_MASK                                        0x00380000
#define CPU_DPLL2_OUTDIV_GET(x)                                      (((x) & CPU_DPLL2_OUTDIV_MASK) >> CPU_DPLL2_OUTDIV_LSB)
#define CPU_DPLL2_OUTDIV_SET(x)                                      (((x) << CPU_DPLL2_OUTDIV_LSB) & CPU_DPLL2_OUTDIV_MASK)
#define CPU_DPLL2_OUTDIV_RESET                                       0x1 // 1
#define CPU_DPLL2_PHASE_SHIFT_MSB                                    18
#define CPU_DPLL2_PHASE_SHIFT_LSB                                    12
#define CPU_DPLL2_PHASE_SHIFT_MASK                                   0x0007f000
#define CPU_DPLL2_PHASE_SHIFT_GET(x)                                 (((x) & CPU_DPLL2_PHASE_SHIFT_MASK) >> CPU_DPLL2_PHASE_SHIFT_LSB)
#define CPU_DPLL2_PHASE_SHIFT_SET(x)                                 (((x) << CPU_DPLL2_PHASE_SHIFT_LSB) & CPU_DPLL2_PHASE_SHIFT_MASK)
#define CPU_DPLL2_PHASE_SHIFT_RESET                                  0x0 // 0
#define CPU_DPLL2_TESTIN_MSB                                         11
#define CPU_DPLL2_TESTIN_LSB                                         2
#define CPU_DPLL2_TESTIN_MASK                                        0x00000ffc
#define CPU_DPLL2_TESTIN_GET(x)                                      (((x) & CPU_DPLL2_TESTIN_MASK) >> CPU_DPLL2_TESTIN_LSB)
#define CPU_DPLL2_TESTIN_SET(x)                                      (((x) << CPU_DPLL2_TESTIN_LSB) & CPU_DPLL2_TESTIN_MASK)
#define CPU_DPLL2_TESTIN_RESET                                       0x0 // 0
#define CPU_DPLL2_SEL_COUNT_MSB                                      1
#define CPU_DPLL2_SEL_COUNT_LSB                                      1
#define CPU_DPLL2_SEL_COUNT_MASK                                     0x00000002
#define CPU_DPLL2_SEL_COUNT_GET(x)                                   (((x) & CPU_DPLL2_SEL_COUNT_MASK) >> CPU_DPLL2_SEL_COUNT_LSB)
#define CPU_DPLL2_SEL_COUNT_SET(x)                                   (((x) << CPU_DPLL2_SEL_COUNT_LSB) & CPU_DPLL2_SEL_COUNT_MASK)
#define CPU_DPLL2_SEL_COUNT_RESET                                    0x0 // 0
#define CPU_DPLL2_RESET_TEST_MSB                                     0
#define CPU_DPLL2_RESET_TEST_LSB                                     0
#define CPU_DPLL2_RESET_TEST_MASK                                    0x00000001
#define CPU_DPLL2_RESET_TEST_GET(x)                                  (((x) & CPU_DPLL2_RESET_TEST_MASK) >> CPU_DPLL2_RESET_TEST_LSB)
#define CPU_DPLL2_RESET_TEST_SET(x)                                  (((x) << CPU_DPLL2_RESET_TEST_LSB) & CPU_DPLL2_RESET_TEST_MASK)
#define CPU_DPLL2_RESET_TEST_RESET                                   0x0 // 0
#define CPU_DPLL2_ADDRESS                                            0x181161c4

#define DDR_RD_DATA_THIS_CYCLE_ADDRESS                               0x18000018

#define TAP_CONTROL_0_ADDRESS                                        0x1800001c
#define TAP_CONTROL_1_ADDRESS                                        0x18000020
#define TAP_CONTROL_2_ADDRESS                                        0x18000024
#define TAP_CONTROL_3_ADDRESS                                        0x18000028

#define DDR_BURST_CPU_PRIORITY_MSB                                   31
#define DDR_BURST_CPU_PRIORITY_LSB                                   31
#define DDR_BURST_CPU_PRIORITY_MASK                                  0x80000000
#define DDR_BURST_CPU_PRIORITY_GET(x)                                (((x) & DDR_BURST_CPU_PRIORITY_MASK) >> DDR_BURST_CPU_PRIORITY_LSB)
#define DDR_BURST_CPU_PRIORITY_SET(x)                                (((x) << DDR_BURST_CPU_PRIORITY_LSB) & DDR_BURST_CPU_PRIORITY_MASK)
#define DDR_BURST_CPU_PRIORITY_RESET                                 0x0 // 0
#define DDR_BURST_CPU_PRIORITY_BE_MSB                                30
#define DDR_BURST_CPU_PRIORITY_BE_LSB                                30
#define DDR_BURST_CPU_PRIORITY_BE_MASK                               0x40000000
#define DDR_BURST_CPU_PRIORITY_BE_GET(x)                             (((x) & DDR_BURST_CPU_PRIORITY_BE_MASK) >> DDR_BURST_CPU_PRIORITY_BE_LSB)
#define DDR_BURST_CPU_PRIORITY_BE_SET(x)                             (((x) << DDR_BURST_CPU_PRIORITY_BE_LSB) & DDR_BURST_CPU_PRIORITY_BE_MASK)
#define DDR_BURST_CPU_PRIORITY_BE_RESET                              0x1 // 1
#define DDR_BURST_ENABLE_RWP_MASK_MSB                                29
#define DDR_BURST_ENABLE_RWP_MASK_LSB                                28
#define DDR_BURST_ENABLE_RWP_MASK_MASK                               0x30000000
#define DDR_BURST_ENABLE_RWP_MASK_GET(x)                             (((x) & DDR_BURST_ENABLE_RWP_MASK_MASK) >> DDR_BURST_ENABLE_RWP_MASK_LSB)
#define DDR_BURST_ENABLE_RWP_MASK_SET(x)                             (((x) << DDR_BURST_ENABLE_RWP_MASK_LSB) & DDR_BURST_ENABLE_RWP_MASK_MASK)
#define DDR_BURST_ENABLE_RWP_MASK_RESET                              0x3 // 3
#define DDR_BURST_MAX_WRITE_BURST_MSB                                27
#define DDR_BURST_MAX_WRITE_BURST_LSB                                24
#define DDR_BURST_MAX_WRITE_BURST_MASK                               0x0f000000
#define DDR_BURST_MAX_WRITE_BURST_GET(x)                             (((x) & DDR_BURST_MAX_WRITE_BURST_MASK) >> DDR_BURST_MAX_WRITE_BURST_LSB)
#define DDR_BURST_MAX_WRITE_BURST_SET(x)                             (((x) << DDR_BURST_MAX_WRITE_BURST_LSB) & DDR_BURST_MAX_WRITE_BURST_MASK)
#define DDR_BURST_MAX_WRITE_BURST_RESET                              0x4 // 4
#define DDR_BURST_MAX_READ_BURST_MSB                                 23
#define DDR_BURST_MAX_READ_BURST_LSB                                 20
#define DDR_BURST_MAX_READ_BURST_MASK                                0x00f00000
#define DDR_BURST_MAX_READ_BURST_GET(x)                              (((x) & DDR_BURST_MAX_READ_BURST_MASK) >> DDR_BURST_MAX_READ_BURST_LSB)
#define DDR_BURST_MAX_READ_BURST_SET(x)                              (((x) << DDR_BURST_MAX_READ_BURST_LSB) & DDR_BURST_MAX_READ_BURST_MASK)
#define DDR_BURST_MAX_READ_BURST_RESET                               0x4 // 4
#define DDR_BURST_CPU_MAX_BL_MSB                                     19
#define DDR_BURST_CPU_MAX_BL_LSB                                     16
#define DDR_BURST_CPU_MAX_BL_MASK                                    0x000f0000
#define DDR_BURST_CPU_MAX_BL_GET(x)                                  (((x) & DDR_BURST_CPU_MAX_BL_MASK) >> DDR_BURST_CPU_MAX_BL_LSB)
#define DDR_BURST_CPU_MAX_BL_SET(x)                                  (((x) << DDR_BURST_CPU_MAX_BL_LSB) & DDR_BURST_CPU_MAX_BL_MASK)
#define DDR_BURST_CPU_MAX_BL_RESET                                   0x3 // 3
#define DDR_BURST_USB_MAX_BL_MSB                                     15
#define DDR_BURST_USB_MAX_BL_LSB                                     12
#define DDR_BURST_USB_MAX_BL_MASK                                    0x0000f000
#define DDR_BURST_USB_MAX_BL_GET(x)                                  (((x) & DDR_BURST_USB_MAX_BL_MASK) >> DDR_BURST_USB_MAX_BL_LSB)
#define DDR_BURST_USB_MAX_BL_SET(x)                                  (((x) << DDR_BURST_USB_MAX_BL_LSB) & DDR_BURST_USB_MAX_BL_MASK)
#define DDR_BURST_USB_MAX_BL_RESET                                   0x4 // 4
#define DDR_BURST_PCIE_MAX_BL_MSB                                    11
#define DDR_BURST_PCIE_MAX_BL_LSB                                    8
#define DDR_BURST_PCIE_MAX_BL_MASK                                   0x00000f00
#define DDR_BURST_PCIE_MAX_BL_GET(x)                                 (((x) & DDR_BURST_PCIE_MAX_BL_MASK) >> DDR_BURST_PCIE_MAX_BL_LSB)
#define DDR_BURST_PCIE_MAX_BL_SET(x)                                 (((x) << DDR_BURST_PCIE_MAX_BL_LSB) & DDR_BURST_PCIE_MAX_BL_MASK)
#define DDR_BURST_PCIE_MAX_BL_RESET                                  0x3 // 3
#define DDR_BURST_GE1_MAX_BL_MSB                                     7
#define DDR_BURST_GE1_MAX_BL_LSB                                     4
#define DDR_BURST_GE1_MAX_BL_MASK                                    0x000000f0
#define DDR_BURST_GE1_MAX_BL_GET(x)                                  (((x) & DDR_BURST_GE1_MAX_BL_MASK) >> DDR_BURST_GE1_MAX_BL_LSB)
#define DDR_BURST_GE1_MAX_BL_SET(x)                                  (((x) << DDR_BURST_GE1_MAX_BL_LSB) & DDR_BURST_GE1_MAX_BL_MASK)
#define DDR_BURST_GE1_MAX_BL_RESET                                   0x3 // 3
#define DDR_BURST_GE0_MAX_BL_MSB                                     3
#define DDR_BURST_GE0_MAX_BL_LSB                                     0
#define DDR_BURST_GE0_MAX_BL_MASK                                    0x0000000f
#define DDR_BURST_GE0_MAX_BL_GET(x)                                  (((x) & DDR_BURST_GE0_MAX_BL_MASK) >> DDR_BURST_GE0_MAX_BL_LSB)
#define DDR_BURST_GE0_MAX_BL_SET(x)                                  (((x) << DDR_BURST_GE0_MAX_BL_LSB) & DDR_BURST_GE0_MAX_BL_MASK)
#define DDR_BURST_GE0_MAX_BL_RESET                                   0x3 // 3
#define DDR_BURST_ADDRESS                                            0x180000c4

#define DDR_BURST2_WMAC_MAX_BL_MSB                                   3
#define DDR_BURST2_WMAC_MAX_BL_LSB                                   0
#define DDR_BURST2_WMAC_MAX_BL_MASK                                  0x0000000f
#define DDR_BURST2_WMAC_MAX_BL_GET(x)                                (((x) & DDR_BURST2_WMAC_MAX_BL_MASK) >> DDR_BURST2_WMAC_MAX_BL_LSB)
#define DDR_BURST2_WMAC_MAX_BL_SET(x)                                (((x) << DDR_BURST2_WMAC_MAX_BL_LSB) & DDR_BURST2_WMAC_MAX_BL_MASK)
#define DDR_BURST2_WMAC_MAX_BL_RESET                                 0x3 // 3
#define DDR_BURST2_ADDRESS                                           0x180000c8

#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_MSB                         19
#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_LSB                         0
#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_MASK                        0x000fffff
#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_GET(x)                      (((x) & DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_MASK) >> DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_LSB)
#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_SET(x)                      (((x) << DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_LSB) & DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_MASK)
#define DDR_AHB_MASTER_TIMEOUT_MAX_VALUE_RESET                       0x8000 // 32768
#define DDR_AHB_MASTER_TIMEOUT_MAX_ADDRESS                           0x180000cc

#define PMU1_ADDRESS                                                 0x18116c40

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
#define PMU2_ADDRESS                                                 0x18116c44

#define PHY_CTRL0_LOOPBACK_ERR_CNT_MSB                               31
#define PHY_CTRL0_LOOPBACK_ERR_CNT_LSB                               24
#define PHY_CTRL0_LOOPBACK_ERR_CNT_MASK                              0xff000000
#define PHY_CTRL0_LOOPBACK_ERR_CNT_GET(x)                            (((x) & PHY_CTRL0_LOOPBACK_ERR_CNT_MASK) >> PHY_CTRL0_LOOPBACK_ERR_CNT_LSB)
#define PHY_CTRL0_LOOPBACK_ERR_CNT_SET(x)                            (((x) << PHY_CTRL0_LOOPBACK_ERR_CNT_LSB) & PHY_CTRL0_LOOPBACK_ERR_CNT_MASK)
#define PHY_CTRL0_LOOPBACK_ERR_CNT_RESET                             0x0 // 0
#define PHY_CTRL0_DIG_LOOPBACK_EN_MSB                                23
#define PHY_CTRL0_DIG_LOOPBACK_EN_LSB                                23
#define PHY_CTRL0_DIG_LOOPBACK_EN_MASK                               0x00800000
#define PHY_CTRL0_DIG_LOOPBACK_EN_GET(x)                             (((x) & PHY_CTRL0_DIG_LOOPBACK_EN_MASK) >> PHY_CTRL0_DIG_LOOPBACK_EN_LSB)
#define PHY_CTRL0_DIG_LOOPBACK_EN_SET(x)                             (((x) << PHY_CTRL0_DIG_LOOPBACK_EN_LSB) & PHY_CTRL0_DIG_LOOPBACK_EN_MASK)
#define PHY_CTRL0_DIG_LOOPBACK_EN_RESET                              0x0 // 0
#define PHY_CTRL0_ANA_LOOPBACK_EN_MSB                                22
#define PHY_CTRL0_ANA_LOOPBACK_EN_LSB                                22
#define PHY_CTRL0_ANA_LOOPBACK_EN_MASK                               0x00400000
#define PHY_CTRL0_ANA_LOOPBACK_EN_GET(x)                             (((x) & PHY_CTRL0_ANA_LOOPBACK_EN_MASK) >> PHY_CTRL0_ANA_LOOPBACK_EN_LSB)
#define PHY_CTRL0_ANA_LOOPBACK_EN_SET(x)                             (((x) << PHY_CTRL0_ANA_LOOPBACK_EN_LSB) & PHY_CTRL0_ANA_LOOPBACK_EN_MASK)
#define PHY_CTRL0_ANA_LOOPBACK_EN_RESET                              0x0 // 0
#define PHY_CTRL0_TX_PATTERN_EN_MSB                                  21
#define PHY_CTRL0_TX_PATTERN_EN_LSB                                  21
#define PHY_CTRL0_TX_PATTERN_EN_MASK                                 0x00200000
#define PHY_CTRL0_TX_PATTERN_EN_GET(x)                               (((x) & PHY_CTRL0_TX_PATTERN_EN_MASK) >> PHY_CTRL0_TX_PATTERN_EN_LSB)
#define PHY_CTRL0_TX_PATTERN_EN_SET(x)                               (((x) << PHY_CTRL0_TX_PATTERN_EN_LSB) & PHY_CTRL0_TX_PATTERN_EN_MASK)
#define PHY_CTRL0_TX_PATTERN_EN_RESET                                0x0 // 0
#define PHY_CTRL0_RX_PATTERN_EN_MSB                                  20
#define PHY_CTRL0_RX_PATTERN_EN_LSB                                  20
#define PHY_CTRL0_RX_PATTERN_EN_MASK                                 0x00100000
#define PHY_CTRL0_RX_PATTERN_EN_GET(x)                               (((x) & PHY_CTRL0_RX_PATTERN_EN_MASK) >> PHY_CTRL0_RX_PATTERN_EN_LSB)
#define PHY_CTRL0_RX_PATTERN_EN_SET(x)                               (((x) << PHY_CTRL0_RX_PATTERN_EN_LSB) & PHY_CTRL0_RX_PATTERN_EN_MASK)
#define PHY_CTRL0_RX_PATTERN_EN_RESET                                0x0 // 0
#define PHY_CTRL0_TEST_SPEED_SELECT_MSB                              19
#define PHY_CTRL0_TEST_SPEED_SELECT_LSB                              19
#define PHY_CTRL0_TEST_SPEED_SELECT_MASK                             0x00080000
#define PHY_CTRL0_TEST_SPEED_SELECT_GET(x)                           (((x) & PHY_CTRL0_TEST_SPEED_SELECT_MASK) >> PHY_CTRL0_TEST_SPEED_SELECT_LSB)
#define PHY_CTRL0_TEST_SPEED_SELECT_SET(x)                           (((x) << PHY_CTRL0_TEST_SPEED_SELECT_LSB) & PHY_CTRL0_TEST_SPEED_SELECT_MASK)
#define PHY_CTRL0_TEST_SPEED_SELECT_RESET                            0x0 // 0
#define PHY_CTRL0_PLL_OVERIDE_MSB                                    18
#define PHY_CTRL0_PLL_OVERIDE_LSB                                    18
#define PHY_CTRL0_PLL_OVERIDE_MASK                                   0x00040000
#define PHY_CTRL0_PLL_OVERIDE_GET(x)                                 (((x) & PHY_CTRL0_PLL_OVERIDE_MASK) >> PHY_CTRL0_PLL_OVERIDE_LSB)
#define PHY_CTRL0_PLL_OVERIDE_SET(x)                                 (((x) << PHY_CTRL0_PLL_OVERIDE_LSB) & PHY_CTRL0_PLL_OVERIDE_MASK)
#define PHY_CTRL0_PLL_OVERIDE_RESET                                  0x0 // 0
#define PHY_CTRL0_PLL_MOD_MSB                                        17
#define PHY_CTRL0_PLL_MOD_LSB                                        15
#define PHY_CTRL0_PLL_MOD_MASK                                       0x00038000
#define PHY_CTRL0_PLL_MOD_GET(x)                                     (((x) & PHY_CTRL0_PLL_MOD_MASK) >> PHY_CTRL0_PLL_MOD_LSB)
#define PHY_CTRL0_PLL_MOD_SET(x)                                     (((x) << PHY_CTRL0_PLL_MOD_LSB) & PHY_CTRL0_PLL_MOD_MASK)
#define PHY_CTRL0_PLL_MOD_RESET                                      0x0 // 0
#define PHY_CTRL0_PLL_DIV_MSB                                        14
#define PHY_CTRL0_PLL_DIV_LSB                                        6
#define PHY_CTRL0_PLL_DIV_MASK                                       0x00007fc0
#define PHY_CTRL0_PLL_DIV_GET(x)                                     (((x) & PHY_CTRL0_PLL_DIV_MASK) >> PHY_CTRL0_PLL_DIV_LSB)
#define PHY_CTRL0_PLL_DIV_SET(x)                                     (((x) << PHY_CTRL0_PLL_DIV_LSB) & PHY_CTRL0_PLL_DIV_MASK)
#define PHY_CTRL0_PLL_DIV_RESET                                      0x0 // 0
#define PHY_CTRL0_PLL_RS_MSB                                         5
#define PHY_CTRL0_PLL_RS_LSB                                         3
#define PHY_CTRL0_PLL_RS_MASK                                        0x00000038
#define PHY_CTRL0_PLL_RS_GET(x)                                      (((x) & PHY_CTRL0_PLL_RS_MASK) >> PHY_CTRL0_PLL_RS_LSB)
#define PHY_CTRL0_PLL_RS_SET(x)                                      (((x) << PHY_CTRL0_PLL_RS_LSB) & PHY_CTRL0_PLL_RS_MASK)
#define PHY_CTRL0_PLL_RS_RESET                                       0x2 // 2
#define PHY_CTRL0_PLL_ICP_MSB                                        2
#define PHY_CTRL0_PLL_ICP_LSB                                        0
#define PHY_CTRL0_PLL_ICP_MASK                                       0x00000007
#define PHY_CTRL0_PLL_ICP_GET(x)                                     (((x) & PHY_CTRL0_PLL_ICP_MASK) >> PHY_CTRL0_PLL_ICP_LSB)
#define PHY_CTRL0_PLL_ICP_SET(x)                                     (((x) << PHY_CTRL0_PLL_ICP_LSB) & PHY_CTRL0_PLL_ICP_MASK)
#define PHY_CTRL0_PLL_ICP_RESET                                      0x5 // 5
#define PHY_CTRL0_ADDRESS                                            0x18116c80
#define PHY_CTRL0_OFFSET                                             0x0000
// SW modifiable bits
#define PHY_CTRL0_SW_MASK                                            0xffffffff
// bits defined at reset
#define PHY_CTRL0_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL0_RESET                                              0x00000015

#define PHY_CTRL1_PLL_OBS_MODE_N_MSB                                 31
#define PHY_CTRL1_PLL_OBS_MODE_N_LSB                                 31
#define PHY_CTRL1_PLL_OBS_MODE_N_MASK                                0x80000000
#define PHY_CTRL1_PLL_OBS_MODE_N_GET(x)                              (((x) & PHY_CTRL1_PLL_OBS_MODE_N_MASK) >> PHY_CTRL1_PLL_OBS_MODE_N_LSB)
#define PHY_CTRL1_PLL_OBS_MODE_N_SET(x)                              (((x) << PHY_CTRL1_PLL_OBS_MODE_N_LSB) & PHY_CTRL1_PLL_OBS_MODE_N_MASK)
#define PHY_CTRL1_PLL_OBS_MODE_N_RESET                               0x1 // 1
#define PHY_CTRL1_DISABLE_CLK_GATING_MSB                             27
#define PHY_CTRL1_DISABLE_CLK_GATING_LSB                             27
#define PHY_CTRL1_DISABLE_CLK_GATING_MASK                            0x08000000
#define PHY_CTRL1_DISABLE_CLK_GATING_GET(x)                          (((x) & PHY_CTRL1_DISABLE_CLK_GATING_MASK) >> PHY_CTRL1_DISABLE_CLK_GATING_LSB)
#define PHY_CTRL1_DISABLE_CLK_GATING_SET(x)                          (((x) << PHY_CTRL1_DISABLE_CLK_GATING_LSB) & PHY_CTRL1_DISABLE_CLK_GATING_MASK)
#define PHY_CTRL1_DISABLE_CLK_GATING_RESET                           0x0 // 0
#define PHY_CTRL1_ENABLE_REFCLK_GATE_MSB                             26
#define PHY_CTRL1_ENABLE_REFCLK_GATE_LSB                             26
#define PHY_CTRL1_ENABLE_REFCLK_GATE_MASK                            0x04000000
#define PHY_CTRL1_ENABLE_REFCLK_GATE_GET(x)                          (((x) & PHY_CTRL1_ENABLE_REFCLK_GATE_MASK) >> PHY_CTRL1_ENABLE_REFCLK_GATE_LSB)
#define PHY_CTRL1_ENABLE_REFCLK_GATE_SET(x)                          (((x) << PHY_CTRL1_ENABLE_REFCLK_GATE_LSB) & PHY_CTRL1_ENABLE_REFCLK_GATE_MASK)
#define PHY_CTRL1_ENABLE_REFCLK_GATE_RESET                           0x1 // 1
#define PHY_CTRL1_CLKOBS_SEL_MSB                                     25
#define PHY_CTRL1_CLKOBS_SEL_LSB                                     23
#define PHY_CTRL1_CLKOBS_SEL_MASK                                    0x03800000
#define PHY_CTRL1_CLKOBS_SEL_GET(x)                                  (((x) & PHY_CTRL1_CLKOBS_SEL_MASK) >> PHY_CTRL1_CLKOBS_SEL_LSB)
#define PHY_CTRL1_CLKOBS_SEL_SET(x)                                  (((x) << PHY_CTRL1_CLKOBS_SEL_LSB) & PHY_CTRL1_CLKOBS_SEL_MASK)
#define PHY_CTRL1_CLKOBS_SEL_RESET                                   0x0 // 0
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_MSB                           22
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_LSB                           21
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_MASK                          0x00600000
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_GET(x)                        (((x) & PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_MASK) >> PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_LSB)
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_SET(x)                        (((x) << PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_LSB) & PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_MASK)
#define PHY_CTRL1_USE_PLL_LOCK_DLY_SEL_RESET                         0x3 // 3
#define PHY_CTRL1_USE_PLL_LOCKDETECT_MSB                             20
#define PHY_CTRL1_USE_PLL_LOCKDETECT_LSB                             20
#define PHY_CTRL1_USE_PLL_LOCKDETECT_MASK                            0x00100000
#define PHY_CTRL1_USE_PLL_LOCKDETECT_GET(x)                          (((x) & PHY_CTRL1_USE_PLL_LOCKDETECT_MASK) >> PHY_CTRL1_USE_PLL_LOCKDETECT_LSB)
#define PHY_CTRL1_USE_PLL_LOCKDETECT_SET(x)                          (((x) << PHY_CTRL1_USE_PLL_LOCKDETECT_LSB) & PHY_CTRL1_USE_PLL_LOCKDETECT_MASK)
#define PHY_CTRL1_USE_PLL_LOCKDETECT_RESET                           0x0 // 0
#define PHY_CTRL1_TX_PATTERN_SEL_MSB                                 19
#define PHY_CTRL1_TX_PATTERN_SEL_LSB                                 18
#define PHY_CTRL1_TX_PATTERN_SEL_MASK                                0x000c0000
#define PHY_CTRL1_TX_PATTERN_SEL_GET(x)                              (((x) & PHY_CTRL1_TX_PATTERN_SEL_MASK) >> PHY_CTRL1_TX_PATTERN_SEL_LSB)
#define PHY_CTRL1_TX_PATTERN_SEL_SET(x)                              (((x) << PHY_CTRL1_TX_PATTERN_SEL_LSB) & PHY_CTRL1_TX_PATTERN_SEL_MASK)
#define PHY_CTRL1_TX_PATTERN_SEL_RESET                               0x0 // 0
#define PHY_CTRL1_FORCE_SUSPEND_MSB                                  13
#define PHY_CTRL1_FORCE_SUSPEND_LSB                                  13
#define PHY_CTRL1_FORCE_SUSPEND_MASK                                 0x00002000
#define PHY_CTRL1_FORCE_SUSPEND_GET(x)                               (((x) & PHY_CTRL1_FORCE_SUSPEND_MASK) >> PHY_CTRL1_FORCE_SUSPEND_LSB)
#define PHY_CTRL1_FORCE_SUSPEND_SET(x)                               (((x) << PHY_CTRL1_FORCE_SUSPEND_LSB) & PHY_CTRL1_FORCE_SUSPEND_MASK)
#define PHY_CTRL1_FORCE_SUSPEND_RESET                                0x0 // 0
#define PHY_CTRL1_NO_PLL_PWD_MSB                                     12
#define PHY_CTRL1_NO_PLL_PWD_LSB                                     12
#define PHY_CTRL1_NO_PLL_PWD_MASK                                    0x00001000
#define PHY_CTRL1_NO_PLL_PWD_GET(x)                                  (((x) & PHY_CTRL1_NO_PLL_PWD_MASK) >> PHY_CTRL1_NO_PLL_PWD_LSB)
#define PHY_CTRL1_NO_PLL_PWD_SET(x)                                  (((x) << PHY_CTRL1_NO_PLL_PWD_LSB) & PHY_CTRL1_NO_PLL_PWD_MASK)
#define PHY_CTRL1_NO_PLL_PWD_RESET                                   0x0 // 0
#define PHY_CTRL1_RX_RSVD_MSB                                        11
#define PHY_CTRL1_RX_RSVD_LSB                                        9
#define PHY_CTRL1_RX_RSVD_MASK                                       0x00000e00
#define PHY_CTRL1_RX_RSVD_GET(x)                                     (((x) & PHY_CTRL1_RX_RSVD_MASK) >> PHY_CTRL1_RX_RSVD_LSB)
#define PHY_CTRL1_RX_RSVD_SET(x)                                     (((x) << PHY_CTRL1_RX_RSVD_LSB) & PHY_CTRL1_RX_RSVD_MASK)
#define PHY_CTRL1_RX_RSVD_RESET                                      0x0 // 0
#define PHY_CTRL1_RX_SELVREF0P25_MSB                                 8
#define PHY_CTRL1_RX_SELVREF0P25_LSB                                 8
#define PHY_CTRL1_RX_SELVREF0P25_MASK                                0x00000100
#define PHY_CTRL1_RX_SELVREF0P25_GET(x)                              (((x) & PHY_CTRL1_RX_SELVREF0P25_MASK) >> PHY_CTRL1_RX_SELVREF0P25_LSB)
#define PHY_CTRL1_RX_SELVREF0P25_SET(x)                              (((x) << PHY_CTRL1_RX_SELVREF0P25_LSB) & PHY_CTRL1_RX_SELVREF0P25_MASK)
#define PHY_CTRL1_RX_SELVREF0P25_RESET                               0x0 // 0
#define PHY_CTRL1_RX_SELVREF0P6_MSB                                  7
#define PHY_CTRL1_RX_SELVREF0P6_LSB                                  7
#define PHY_CTRL1_RX_SELVREF0P6_MASK                                 0x00000080
#define PHY_CTRL1_RX_SELVREF0P6_GET(x)                               (((x) & PHY_CTRL1_RX_SELVREF0P6_MASK) >> PHY_CTRL1_RX_SELVREF0P6_LSB)
#define PHY_CTRL1_RX_SELVREF0P6_SET(x)                               (((x) << PHY_CTRL1_RX_SELVREF0P6_LSB) & PHY_CTRL1_RX_SELVREF0P6_MASK)
#define PHY_CTRL1_RX_SELVREF0P6_RESET                                0x1 // 1
#define PHY_CTRL1_RX_SELIR_100M_MSB                                  6
#define PHY_CTRL1_RX_SELIR_100M_LSB                                  5
#define PHY_CTRL1_RX_SELIR_100M_MASK                                 0x00000060
#define PHY_CTRL1_RX_SELIR_100M_GET(x)                               (((x) & PHY_CTRL1_RX_SELIR_100M_MASK) >> PHY_CTRL1_RX_SELIR_100M_LSB)
#define PHY_CTRL1_RX_SELIR_100M_SET(x)                               (((x) << PHY_CTRL1_RX_SELIR_100M_LSB) & PHY_CTRL1_RX_SELIR_100M_MASK)
#define PHY_CTRL1_RX_SELIR_100M_RESET                                0x0 // 0
#define PHY_CTRL1_RX_LOWR_PDET_MSB                                   4
#define PHY_CTRL1_RX_LOWR_PDET_LSB                                   4
#define PHY_CTRL1_RX_LOWR_PDET_MASK                                  0x00000010
#define PHY_CTRL1_RX_LOWR_PDET_GET(x)                                (((x) & PHY_CTRL1_RX_LOWR_PDET_MASK) >> PHY_CTRL1_RX_LOWR_PDET_LSB)
#define PHY_CTRL1_RX_LOWR_PDET_SET(x)                                (((x) << PHY_CTRL1_RX_LOWR_PDET_LSB) & PHY_CTRL1_RX_LOWR_PDET_MASK)
#define PHY_CTRL1_RX_LOWR_PDET_RESET                                 0x1 // 1
#define PHY_CTRL1_RX_BYPASSEQ_MSB                                    3
#define PHY_CTRL1_RX_BYPASSEQ_LSB                                    3
#define PHY_CTRL1_RX_BYPASSEQ_MASK                                   0x00000008
#define PHY_CTRL1_RX_BYPASSEQ_GET(x)                                 (((x) & PHY_CTRL1_RX_BYPASSEQ_MASK) >> PHY_CTRL1_RX_BYPASSEQ_LSB)
#define PHY_CTRL1_RX_BYPASSEQ_SET(x)                                 (((x) << PHY_CTRL1_RX_BYPASSEQ_LSB) & PHY_CTRL1_RX_BYPASSEQ_MASK)
#define PHY_CTRL1_RX_BYPASSEQ_RESET                                  0x0 // 0
#define PHY_CTRL1_RX_FORCERXON_MSB                                   2
#define PHY_CTRL1_RX_FORCERXON_LSB                                   2
#define PHY_CTRL1_RX_FORCERXON_MASK                                  0x00000004
#define PHY_CTRL1_RX_FORCERXON_GET(x)                                (((x) & PHY_CTRL1_RX_FORCERXON_MASK) >> PHY_CTRL1_RX_FORCERXON_LSB)
#define PHY_CTRL1_RX_FORCERXON_SET(x)                                (((x) << PHY_CTRL1_RX_FORCERXON_LSB) & PHY_CTRL1_RX_FORCERXON_MASK)
#define PHY_CTRL1_RX_FORCERXON_RESET                                 0x1 // 1
#define PHY_CTRL1_RX_FILBW_SEL_MSB                                   1
#define PHY_CTRL1_RX_FILBW_SEL_LSB                                   0
#define PHY_CTRL1_RX_FILBW_SEL_MASK                                  0x00000003
#define PHY_CTRL1_RX_FILBW_SEL_GET(x)                                (((x) & PHY_CTRL1_RX_FILBW_SEL_MASK) >> PHY_CTRL1_RX_FILBW_SEL_LSB)
#define PHY_CTRL1_RX_FILBW_SEL_SET(x)                                (((x) << PHY_CTRL1_RX_FILBW_SEL_LSB) & PHY_CTRL1_RX_FILBW_SEL_MASK)
#define PHY_CTRL1_RX_FILBW_SEL_RESET                                 0x1 // 1
#define PHY_CTRL1_ADDRESS                                            0x18116c84
#define PHY_CTRL1_OFFSET                                             0x0004
// SW modifiable bits
#define PHY_CTRL1_SW_MASK                                            0x8ffc3fff
// bits defined at reset
#define PHY_CTRL1_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL1_RESET                                              0x84600095

#define PHY_CTRL2_PWD_EXTBIAS_MSB                                    31
#define PHY_CTRL2_PWD_EXTBIAS_LSB                                    31
#define PHY_CTRL2_PWD_EXTBIAS_MASK                                   0x80000000
#define PHY_CTRL2_PWD_EXTBIAS_GET(x)                                 (((x) & PHY_CTRL2_PWD_EXTBIAS_MASK) >> PHY_CTRL2_PWD_EXTBIAS_LSB)
#define PHY_CTRL2_PWD_EXTBIAS_SET(x)                                 (((x) << PHY_CTRL2_PWD_EXTBIAS_LSB) & PHY_CTRL2_PWD_EXTBIAS_MASK)
#define PHY_CTRL2_PWD_EXTBIAS_RESET                                  0x0 // 0
#define PHY_CTRL2_TX_RSVD_MSB                                        30
#define PHY_CTRL2_TX_RSVD_LSB                                        27
#define PHY_CTRL2_TX_RSVD_MASK                                       0x78000000
#define PHY_CTRL2_TX_RSVD_GET(x)                                     (((x) & PHY_CTRL2_TX_RSVD_MASK) >> PHY_CTRL2_TX_RSVD_LSB)
#define PHY_CTRL2_TX_RSVD_SET(x)                                     (((x) << PHY_CTRL2_TX_RSVD_LSB) & PHY_CTRL2_TX_RSVD_MASK)
#define PHY_CTRL2_TX_RSVD_RESET                                      0x0 // 0
#define PHY_CTRL2_TX_LCKDET_OVR_MSB                                  26
#define PHY_CTRL2_TX_LCKDET_OVR_LSB                                  26
#define PHY_CTRL2_TX_LCKDET_OVR_MASK                                 0x04000000
#define PHY_CTRL2_TX_LCKDET_OVR_GET(x)                               (((x) & PHY_CTRL2_TX_LCKDET_OVR_MASK) >> PHY_CTRL2_TX_LCKDET_OVR_LSB)
#define PHY_CTRL2_TX_LCKDET_OVR_SET(x)                               (((x) << PHY_CTRL2_TX_LCKDET_OVR_LSB) & PHY_CTRL2_TX_LCKDET_OVR_MASK)
#define PHY_CTRL2_TX_LCKDET_OVR_RESET                                0x0 // 0
#define PHY_CTRL2_TX_MAN_CAL_MSB                                     25
#define PHY_CTRL2_TX_MAN_CAL_LSB                                     22
#define PHY_CTRL2_TX_MAN_CAL_MASK                                    0x03c00000
#define PHY_CTRL2_TX_MAN_CAL_GET(x)                                  (((x) & PHY_CTRL2_TX_MAN_CAL_MASK) >> PHY_CTRL2_TX_MAN_CAL_LSB)
#define PHY_CTRL2_TX_MAN_CAL_SET(x)                                  (((x) << PHY_CTRL2_TX_MAN_CAL_LSB) & PHY_CTRL2_TX_MAN_CAL_MASK)
#define PHY_CTRL2_TX_MAN_CAL_RESET                                   0x3 // 3
#define PHY_CTRL2_TX_CAL_SEL_MSB                                     21
#define PHY_CTRL2_TX_CAL_SEL_LSB                                     21
#define PHY_CTRL2_TX_CAL_SEL_MASK                                    0x00200000
#define PHY_CTRL2_TX_CAL_SEL_GET(x)                                  (((x) & PHY_CTRL2_TX_CAL_SEL_MASK) >> PHY_CTRL2_TX_CAL_SEL_LSB)
#define PHY_CTRL2_TX_CAL_SEL_SET(x)                                  (((x) << PHY_CTRL2_TX_CAL_SEL_LSB) & PHY_CTRL2_TX_CAL_SEL_MASK)
#define PHY_CTRL2_TX_CAL_SEL_RESET                                   0x1 // 1
#define PHY_CTRL2_TX_CAL_EN_MSB                                      20
#define PHY_CTRL2_TX_CAL_EN_LSB                                      20
#define PHY_CTRL2_TX_CAL_EN_MASK                                     0x00100000
#define PHY_CTRL2_TX_CAL_EN_GET(x)                                   (((x) & PHY_CTRL2_TX_CAL_EN_MASK) >> PHY_CTRL2_TX_CAL_EN_LSB)
#define PHY_CTRL2_TX_CAL_EN_SET(x)                                   (((x) << PHY_CTRL2_TX_CAL_EN_LSB) & PHY_CTRL2_TX_CAL_EN_MASK)
#define PHY_CTRL2_TX_CAL_EN_RESET                                    0x1 // 1
#define PHY_CTRL2_PWD_ISP_MSB                                        13
#define PHY_CTRL2_PWD_ISP_LSB                                        8
#define PHY_CTRL2_PWD_ISP_MASK                                       0x00003f00
#define PHY_CTRL2_PWD_ISP_GET(x)                                     (((x) & PHY_CTRL2_PWD_ISP_MASK) >> PHY_CTRL2_PWD_ISP_LSB)
#define PHY_CTRL2_PWD_ISP_SET(x)                                     (((x) << PHY_CTRL2_PWD_ISP_LSB) & PHY_CTRL2_PWD_ISP_MASK)
#define PHY_CTRL2_PWD_ISP_RESET                                      0x1b // 27
#define PHY_CTRL2_PWD_IPLL_MSB                                       7
#define PHY_CTRL2_PWD_IPLL_LSB                                       2
#define PHY_CTRL2_PWD_IPLL_MASK                                      0x000000fc
#define PHY_CTRL2_PWD_IPLL_GET(x)                                    (((x) & PHY_CTRL2_PWD_IPLL_MASK) >> PHY_CTRL2_PWD_IPLL_LSB)
#define PHY_CTRL2_PWD_IPLL_SET(x)                                    (((x) << PHY_CTRL2_PWD_IPLL_LSB) & PHY_CTRL2_PWD_IPLL_MASK)
#define PHY_CTRL2_PWD_IPLL_RESET                                     0x1b // 27
#define PHY_CTRL2_HSRXPHASE_PS_EN_MSB                                1
#define PHY_CTRL2_HSRXPHASE_PS_EN_LSB                                1
#define PHY_CTRL2_HSRXPHASE_PS_EN_MASK                               0x00000002
#define PHY_CTRL2_HSRXPHASE_PS_EN_GET(x)                             (((x) & PHY_CTRL2_HSRXPHASE_PS_EN_MASK) >> PHY_CTRL2_HSRXPHASE_PS_EN_LSB)
#define PHY_CTRL2_HSRXPHASE_PS_EN_SET(x)                             (((x) << PHY_CTRL2_HSRXPHASE_PS_EN_LSB) & PHY_CTRL2_HSRXPHASE_PS_EN_MASK)
#define PHY_CTRL2_HSRXPHASE_PS_EN_RESET                              0x0 // 0
#define PHY_CTRL2_HSTXBIAS_PS_EN_MSB                                 0
#define PHY_CTRL2_HSTXBIAS_PS_EN_LSB                                 0
#define PHY_CTRL2_HSTXBIAS_PS_EN_MASK                                0x00000001
#define PHY_CTRL2_HSTXBIAS_PS_EN_GET(x)                              (((x) & PHY_CTRL2_HSTXBIAS_PS_EN_MASK) >> PHY_CTRL2_HSTXBIAS_PS_EN_LSB)
#define PHY_CTRL2_HSTXBIAS_PS_EN_SET(x)                              (((x) << PHY_CTRL2_HSTXBIAS_PS_EN_LSB) & PHY_CTRL2_HSTXBIAS_PS_EN_MASK)
#define PHY_CTRL2_HSTXBIAS_PS_EN_RESET                               0x0 // 0
#define PHY_CTRL2_ADDRESS                                            0x18116c88
#define PHY_CTRL2_OFFSET                                             0x0008
// SW modifiable bits
#define PHY_CTRL2_SW_MASK                                            0xfff03fff
// bits defined at reset
#define PHY_CTRL2_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL2_RESET                                              0x00f01b6c

#define PHY_CTRL3_SPARE_BITS_MSB                                     31
#define PHY_CTRL3_SPARE_BITS_LSB                                     27
#define PHY_CTRL3_SPARE_BITS_MASK                                    0xf8000000
#define PHY_CTRL3_SPARE_BITS_GET(x)                                  (((x) & PHY_CTRL3_SPARE_BITS_MASK) >> PHY_CTRL3_SPARE_BITS_LSB)
#define PHY_CTRL3_SPARE_BITS_SET(x)                                  (((x) << PHY_CTRL3_SPARE_BITS_LSB) & PHY_CTRL3_SPARE_BITS_MASK)
#define PHY_CTRL3_SPARE_BITS_RESET                                   0x0 // 0
#define PHY_CTRL3_SUS_RES_FIX_DIS_MSB                                26
#define PHY_CTRL3_SUS_RES_FIX_DIS_LSB                                26
#define PHY_CTRL3_SUS_RES_FIX_DIS_MASK                               0x04000000
#define PHY_CTRL3_SUS_RES_FIX_DIS_GET(x)                             (((x) & PHY_CTRL3_SUS_RES_FIX_DIS_MASK) >> PHY_CTRL3_SUS_RES_FIX_DIS_LSB)
#define PHY_CTRL3_SUS_RES_FIX_DIS_SET(x)                             (((x) << PHY_CTRL3_SUS_RES_FIX_DIS_LSB) & PHY_CTRL3_SUS_RES_FIX_DIS_MASK)
#define PHY_CTRL3_SUS_RES_FIX_DIS_RESET                              0x0 // 0
#define PHY_CTRL3_TX_STARTCAL_MSB                                    25
#define PHY_CTRL3_TX_STARTCAL_LSB                                    25
#define PHY_CTRL3_TX_STARTCAL_MASK                                   0x02000000
#define PHY_CTRL3_TX_STARTCAL_GET(x)                                 (((x) & PHY_CTRL3_TX_STARTCAL_MASK) >> PHY_CTRL3_TX_STARTCAL_LSB)
#define PHY_CTRL3_TX_STARTCAL_SET(x)                                 (((x) << PHY_CTRL3_TX_STARTCAL_LSB) & PHY_CTRL3_TX_STARTCAL_MASK)
#define PHY_CTRL3_TX_STARTCAL_RESET                                  0x0 // 0
#define PHY_CTRL3_TX_SELTEST_MSB                                     24
#define PHY_CTRL3_TX_SELTEST_LSB                                     22
#define PHY_CTRL3_TX_SELTEST_MASK                                    0x01c00000
#define PHY_CTRL3_TX_SELTEST_GET(x)                                  (((x) & PHY_CTRL3_TX_SELTEST_MASK) >> PHY_CTRL3_TX_SELTEST_LSB)
#define PHY_CTRL3_TX_SELTEST_SET(x)                                  (((x) << PHY_CTRL3_TX_SELTEST_LSB) & PHY_CTRL3_TX_SELTEST_MASK)
#define PHY_CTRL3_TX_SELTEST_RESET                                   0x0 // 0
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_MSB                           21
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_LSB                           21
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_MASK                          0x00200000
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_GET(x)                        (((x) & PHY_CTRL3_TX_DISABLE_SHORT_DET_MASK) >> PHY_CTRL3_TX_DISABLE_SHORT_DET_LSB)
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_SET(x)                        (((x) << PHY_CTRL3_TX_DISABLE_SHORT_DET_LSB) & PHY_CTRL3_TX_DISABLE_SHORT_DET_MASK)
#define PHY_CTRL3_TX_DISABLE_SHORT_DET_RESET                         0x0 // 0
#define PHY_CTRL3_PWD_ITX_MSB                                        18
#define PHY_CTRL3_PWD_ITX_LSB                                        0
#define PHY_CTRL3_PWD_ITX_MASK                                       0x0007ffff
#define PHY_CTRL3_PWD_ITX_GET(x)                                     (((x) & PHY_CTRL3_PWD_ITX_MASK) >> PHY_CTRL3_PWD_ITX_LSB)
#define PHY_CTRL3_PWD_ITX_SET(x)                                     (((x) << PHY_CTRL3_PWD_ITX_LSB) & PHY_CTRL3_PWD_ITX_MASK)
#define PHY_CTRL3_PWD_ITX_RESET                                      0x14765 // 83813
#define PHY_CTRL3_ADDRESS                                            0x18116c8c
#define PHY_CTRL3_OFFSET                                             0x000c
// SW modifiable bits
#define PHY_CTRL3_SW_MASK                                            0xffe7ffff
// bits defined at reset
#define PHY_CTRL3_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL3_RESET                                              0x00014765

#define PHY_CTRL4_PPRBS_ERR_CNT_MSB                                  31
#define PHY_CTRL4_PPRBS_ERR_CNT_LSB                                  24
#define PHY_CTRL4_PPRBS_ERR_CNT_MASK                                 0xff000000
#define PHY_CTRL4_PPRBS_ERR_CNT_GET(x)                               (((x) & PHY_CTRL4_PPRBS_ERR_CNT_MASK) >> PHY_CTRL4_PPRBS_ERR_CNT_LSB)
#define PHY_CTRL4_PPRBS_ERR_CNT_SET(x)                               (((x) << PHY_CTRL4_PPRBS_ERR_CNT_LSB) & PHY_CTRL4_PPRBS_ERR_CNT_MASK)
#define PHY_CTRL4_PPRBS_ERR_CNT_RESET                                0x0 // 0
#define PHY_CTRL4_LS_PRBS_EN_MSB                                     21
#define PHY_CTRL4_LS_PRBS_EN_LSB                                     21
#define PHY_CTRL4_LS_PRBS_EN_MASK                                    0x00200000
#define PHY_CTRL4_LS_PRBS_EN_GET(x)                                  (((x) & PHY_CTRL4_LS_PRBS_EN_MASK) >> PHY_CTRL4_LS_PRBS_EN_LSB)
#define PHY_CTRL4_LS_PRBS_EN_SET(x)                                  (((x) << PHY_CTRL4_LS_PRBS_EN_LSB) & PHY_CTRL4_LS_PRBS_EN_MASK)
#define PHY_CTRL4_LS_PRBS_EN_RESET                                   0x0 // 0
#define PHY_CTRL4_PPRBS_TERM_SEL_MSB                                 20
#define PHY_CTRL4_PPRBS_TERM_SEL_LSB                                 20
#define PHY_CTRL4_PPRBS_TERM_SEL_MASK                                0x00100000
#define PHY_CTRL4_PPRBS_TERM_SEL_GET(x)                              (((x) & PHY_CTRL4_PPRBS_TERM_SEL_MASK) >> PHY_CTRL4_PPRBS_TERM_SEL_LSB)
#define PHY_CTRL4_PPRBS_TERM_SEL_SET(x)                              (((x) << PHY_CTRL4_PPRBS_TERM_SEL_LSB) & PHY_CTRL4_PPRBS_TERM_SEL_MASK)
#define PHY_CTRL4_PPRBS_TERM_SEL_RESET                               0x0 // 0
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_MSB                              19
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_LSB                              19
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_MASK                             0x00080000
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_GET(x)                           (((x) & PHY_CTRL4_PPRBS_DIG_LPBK_EN_MASK) >> PHY_CTRL4_PPRBS_DIG_LPBK_EN_LSB)
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_SET(x)                           (((x) << PHY_CTRL4_PPRBS_DIG_LPBK_EN_LSB) & PHY_CTRL4_PPRBS_DIG_LPBK_EN_MASK)
#define PHY_CTRL4_PPRBS_DIG_LPBK_EN_RESET                            0x0 // 0
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_MSB                              18
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_LSB                              18
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_MASK                             0x00040000
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_GET(x)                           (((x) & PHY_CTRL4_PPRBS_ANA_LPBK_EN_MASK) >> PHY_CTRL4_PPRBS_ANA_LPBK_EN_LSB)
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_SET(x)                           (((x) << PHY_CTRL4_PPRBS_ANA_LPBK_EN_LSB) & PHY_CTRL4_PPRBS_ANA_LPBK_EN_MASK)
#define PHY_CTRL4_PPRBS_ANA_LPBK_EN_RESET                            0x0 // 0
#define PHY_CTRL4_PPRBS_PAT_SEL_MSB                                  17
#define PHY_CTRL4_PPRBS_PAT_SEL_LSB                                  16
#define PHY_CTRL4_PPRBS_PAT_SEL_MASK                                 0x00030000
#define PHY_CTRL4_PPRBS_PAT_SEL_GET(x)                               (((x) & PHY_CTRL4_PPRBS_PAT_SEL_MASK) >> PHY_CTRL4_PPRBS_PAT_SEL_LSB)
#define PHY_CTRL4_PPRBS_PAT_SEL_SET(x)                               (((x) << PHY_CTRL4_PPRBS_PAT_SEL_LSB) & PHY_CTRL4_PPRBS_PAT_SEL_MASK)
#define PHY_CTRL4_PPRBS_PAT_SEL_RESET                                0x0 // 0
#define PHY_CTRL4_PPRBS_TX_EN_MSB                                    15
#define PHY_CTRL4_PPRBS_TX_EN_LSB                                    15
#define PHY_CTRL4_PPRBS_TX_EN_MASK                                   0x00008000
#define PHY_CTRL4_PPRBS_TX_EN_GET(x)                                 (((x) & PHY_CTRL4_PPRBS_TX_EN_MASK) >> PHY_CTRL4_PPRBS_TX_EN_LSB)
#define PHY_CTRL4_PPRBS_TX_EN_SET(x)                                 (((x) << PHY_CTRL4_PPRBS_TX_EN_LSB) & PHY_CTRL4_PPRBS_TX_EN_MASK)
#define PHY_CTRL4_PPRBS_TX_EN_RESET                                  0x0 // 0
#define PHY_CTRL4_PPRBS_RX_EN_MSB                                    14
#define PHY_CTRL4_PPRBS_RX_EN_LSB                                    14
#define PHY_CTRL4_PPRBS_RX_EN_MASK                                   0x00004000
#define PHY_CTRL4_PPRBS_RX_EN_GET(x)                                 (((x) & PHY_CTRL4_PPRBS_RX_EN_MASK) >> PHY_CTRL4_PPRBS_RX_EN_LSB)
#define PHY_CTRL4_PPRBS_RX_EN_SET(x)                                 (((x) << PHY_CTRL4_PPRBS_RX_EN_LSB) & PHY_CTRL4_PPRBS_RX_EN_MASK)
#define PHY_CTRL4_PPRBS_RX_EN_RESET                                  0x0 // 0
#define PHY_CTRL4_PPRBS_SPEED_SEL_MSB                                13
#define PHY_CTRL4_PPRBS_SPEED_SEL_LSB                                13
#define PHY_CTRL4_PPRBS_SPEED_SEL_MASK                               0x00002000
#define PHY_CTRL4_PPRBS_SPEED_SEL_GET(x)                             (((x) & PHY_CTRL4_PPRBS_SPEED_SEL_MASK) >> PHY_CTRL4_PPRBS_SPEED_SEL_LSB)
#define PHY_CTRL4_PPRBS_SPEED_SEL_SET(x)                             (((x) << PHY_CTRL4_PPRBS_SPEED_SEL_LSB) & PHY_CTRL4_PPRBS_SPEED_SEL_MASK)
#define PHY_CTRL4_PPRBS_SPEED_SEL_RESET                              0x0 // 0
#define PHY_CTRL4_PPRBS_RX_INV_MSB                                   12
#define PHY_CTRL4_PPRBS_RX_INV_LSB                                   12
#define PHY_CTRL4_PPRBS_RX_INV_MASK                                  0x00001000
#define PHY_CTRL4_PPRBS_RX_INV_GET(x)                                (((x) & PHY_CTRL4_PPRBS_RX_INV_MASK) >> PHY_CTRL4_PPRBS_RX_INV_LSB)
#define PHY_CTRL4_PPRBS_RX_INV_SET(x)                                (((x) << PHY_CTRL4_PPRBS_RX_INV_LSB) & PHY_CTRL4_PPRBS_RX_INV_MASK)
#define PHY_CTRL4_PPRBS_RX_INV_RESET                                 0x0 // 0
#define PHY_CTRL4_PWD_IRX_MSB                                        11
#define PHY_CTRL4_PWD_IRX_LSB                                        0
#define PHY_CTRL4_PWD_IRX_MASK                                       0x00000fff
#define PHY_CTRL4_PWD_IRX_GET(x)                                     (((x) & PHY_CTRL4_PWD_IRX_MASK) >> PHY_CTRL4_PWD_IRX_LSB)
#define PHY_CTRL4_PWD_IRX_SET(x)                                     (((x) << PHY_CTRL4_PWD_IRX_LSB) & PHY_CTRL4_PWD_IRX_MASK)
#define PHY_CTRL4_PWD_IRX_RESET                                      0x6dd // 1757
#define PHY_CTRL4_ADDRESS                                            0x18116c90
#define PHY_CTRL4_OFFSET                                             0x0010
// SW modifiable bits
#define PHY_CTRL4_SW_MASK                                            0xff3fffff
// bits defined at reset
#define PHY_CTRL4_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL4_RESET                                              0x000006dd

#define PHY_CTRL5_SPARE_BITS_MSB                                     31
#define PHY_CTRL5_SPARE_BITS_LSB                                     30
#define PHY_CTRL5_SPARE_BITS_MASK                                    0xc0000000
#define PHY_CTRL5_SPARE_BITS_GET(x)                                  (((x) & PHY_CTRL5_SPARE_BITS_MASK) >> PHY_CTRL5_SPARE_BITS_LSB)
#define PHY_CTRL5_SPARE_BITS_SET(x)                                  (((x) << PHY_CTRL5_SPARE_BITS_LSB) & PHY_CTRL5_SPARE_BITS_MASK)
#define PHY_CTRL5_SPARE_BITS_RESET                                   0x0 // 0
#define PHY_CTRL5_HOST_RES_FIX_EN_MSB                                29
#define PHY_CTRL5_HOST_RES_FIX_EN_LSB                                29
#define PHY_CTRL5_HOST_RES_FIX_EN_MASK                               0x20000000
#define PHY_CTRL5_HOST_RES_FIX_EN_GET(x)                             (((x) & PHY_CTRL5_HOST_RES_FIX_EN_MASK) >> PHY_CTRL5_HOST_RES_FIX_EN_LSB)
#define PHY_CTRL5_HOST_RES_FIX_EN_SET(x)                             (((x) << PHY_CTRL5_HOST_RES_FIX_EN_LSB) & PHY_CTRL5_HOST_RES_FIX_EN_MASK)
#define PHY_CTRL5_HOST_RES_FIX_EN_RESET                              0x1 // 1
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_MSB                       28
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_LSB                       26
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_MASK                      0x1c000000
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_GET(x)                    (((x) & PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_MASK) >> PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_LSB)
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_SET(x)                    (((x) << PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_LSB) & PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_MASK)
#define PHY_CTRL5_HOST_DISCON_SAMPLE_WIDTH_RESET                     0x6 // 6
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_MSB                          25
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_LSB                          25
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_MASK                         0x02000000
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_GET(x)                       (((x) & PHY_CTRL5_HOST_DISCON_DETECT_ON_MASK) >> PHY_CTRL5_HOST_DISCON_DETECT_ON_LSB)
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_SET(x)                       (((x) << PHY_CTRL5_HOST_DISCON_DETECT_ON_LSB) & PHY_CTRL5_HOST_DISCON_DETECT_ON_MASK)
#define PHY_CTRL5_HOST_DISCON_DETECT_ON_RESET                        0x1 // 1
#define PHY_CTRL5_HOST_DISCON_FIX_ON_MSB                             24
#define PHY_CTRL5_HOST_DISCON_FIX_ON_LSB                             24
#define PHY_CTRL5_HOST_DISCON_FIX_ON_MASK                            0x01000000
#define PHY_CTRL5_HOST_DISCON_FIX_ON_GET(x)                          (((x) & PHY_CTRL5_HOST_DISCON_FIX_ON_MASK) >> PHY_CTRL5_HOST_DISCON_FIX_ON_LSB)
#define PHY_CTRL5_HOST_DISCON_FIX_ON_SET(x)                          (((x) << PHY_CTRL5_HOST_DISCON_FIX_ON_LSB) & PHY_CTRL5_HOST_DISCON_FIX_ON_MASK)
#define PHY_CTRL5_HOST_DISCON_FIX_ON_RESET                           0x1 // 1
#define PHY_CTRL5_DM_PULLDOWN_MSB                                    23
#define PHY_CTRL5_DM_PULLDOWN_LSB                                    23
#define PHY_CTRL5_DM_PULLDOWN_MASK                                   0x00800000
#define PHY_CTRL5_DM_PULLDOWN_GET(x)                                 (((x) & PHY_CTRL5_DM_PULLDOWN_MASK) >> PHY_CTRL5_DM_PULLDOWN_LSB)
#define PHY_CTRL5_DM_PULLDOWN_SET(x)                                 (((x) << PHY_CTRL5_DM_PULLDOWN_LSB) & PHY_CTRL5_DM_PULLDOWN_MASK)
#define PHY_CTRL5_DM_PULLDOWN_RESET                                  0x0 // 0
#define PHY_CTRL5_DP_PULLDOWN_MSB                                    22
#define PHY_CTRL5_DP_PULLDOWN_LSB                                    22
#define PHY_CTRL5_DP_PULLDOWN_MASK                                   0x00400000
#define PHY_CTRL5_DP_PULLDOWN_GET(x)                                 (((x) & PHY_CTRL5_DP_PULLDOWN_MASK) >> PHY_CTRL5_DP_PULLDOWN_LSB)
#define PHY_CTRL5_DP_PULLDOWN_SET(x)                                 (((x) << PHY_CTRL5_DP_PULLDOWN_LSB) & PHY_CTRL5_DP_PULLDOWN_MASK)
#define PHY_CTRL5_DP_PULLDOWN_RESET                                  0x0 // 0
#define PHY_CTRL5_SUSPEND_N_MSB                                      21
#define PHY_CTRL5_SUSPEND_N_LSB                                      21
#define PHY_CTRL5_SUSPEND_N_MASK                                     0x00200000
#define PHY_CTRL5_SUSPEND_N_GET(x)                                   (((x) & PHY_CTRL5_SUSPEND_N_MASK) >> PHY_CTRL5_SUSPEND_N_LSB)
#define PHY_CTRL5_SUSPEND_N_SET(x)                                   (((x) << PHY_CTRL5_SUSPEND_N_LSB) & PHY_CTRL5_SUSPEND_N_MASK)
#define PHY_CTRL5_SUSPEND_N_RESET                                    0x1 // 1
#define PHY_CTRL5_TERM_SEL_MSB                                       20
#define PHY_CTRL5_TERM_SEL_LSB                                       20
#define PHY_CTRL5_TERM_SEL_MASK                                      0x00100000
#define PHY_CTRL5_TERM_SEL_GET(x)                                    (((x) & PHY_CTRL5_TERM_SEL_MASK) >> PHY_CTRL5_TERM_SEL_LSB)
#define PHY_CTRL5_TERM_SEL_SET(x)                                    (((x) << PHY_CTRL5_TERM_SEL_LSB) & PHY_CTRL5_TERM_SEL_MASK)
#define PHY_CTRL5_TERM_SEL_RESET                                     0x0 // 0
#define PHY_CTRL5_XCVR_SEL_MSB                                       19
#define PHY_CTRL5_XCVR_SEL_LSB                                       18
#define PHY_CTRL5_XCVR_SEL_MASK                                      0x000c0000
#define PHY_CTRL5_XCVR_SEL_GET(x)                                    (((x) & PHY_CTRL5_XCVR_SEL_MASK) >> PHY_CTRL5_XCVR_SEL_LSB)
#define PHY_CTRL5_XCVR_SEL_SET(x)                                    (((x) << PHY_CTRL5_XCVR_SEL_LSB) & PHY_CTRL5_XCVR_SEL_MASK)
#define PHY_CTRL5_XCVR_SEL_RESET                                     0x0 // 0
#define PHY_CTRL5_TEST_JK_OVERRIDE_MSB                               17
#define PHY_CTRL5_TEST_JK_OVERRIDE_LSB                               17
#define PHY_CTRL5_TEST_JK_OVERRIDE_MASK                              0x00020000
#define PHY_CTRL5_TEST_JK_OVERRIDE_GET(x)                            (((x) & PHY_CTRL5_TEST_JK_OVERRIDE_MASK) >> PHY_CTRL5_TEST_JK_OVERRIDE_LSB)
#define PHY_CTRL5_TEST_JK_OVERRIDE_SET(x)                            (((x) << PHY_CTRL5_TEST_JK_OVERRIDE_LSB) & PHY_CTRL5_TEST_JK_OVERRIDE_MASK)
#define PHY_CTRL5_TEST_JK_OVERRIDE_RESET                             0x0 // 0
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_MSB                             16
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_LSB                             16
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_MASK                            0x00010000
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_GET(x)                          (((x) & PHY_CTRL5_FORCE_TEST_SE0_NAK_MASK) >> PHY_CTRL5_FORCE_TEST_SE0_NAK_LSB)
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_SET(x)                          (((x) << PHY_CTRL5_FORCE_TEST_SE0_NAK_LSB) & PHY_CTRL5_FORCE_TEST_SE0_NAK_MASK)
#define PHY_CTRL5_FORCE_TEST_SE0_NAK_RESET                           0x0 // 0
#define PHY_CTRL5_FORCE_TEST_K_MSB                                   15
#define PHY_CTRL5_FORCE_TEST_K_LSB                                   15
#define PHY_CTRL5_FORCE_TEST_K_MASK                                  0x00008000
#define PHY_CTRL5_FORCE_TEST_K_GET(x)                                (((x) & PHY_CTRL5_FORCE_TEST_K_MASK) >> PHY_CTRL5_FORCE_TEST_K_LSB)
#define PHY_CTRL5_FORCE_TEST_K_SET(x)                                (((x) << PHY_CTRL5_FORCE_TEST_K_LSB) & PHY_CTRL5_FORCE_TEST_K_MASK)
#define PHY_CTRL5_FORCE_TEST_K_RESET                                 0x0 // 0
#define PHY_CTRL5_FORCE_TEST_J_MSB                                   14
#define PHY_CTRL5_FORCE_TEST_J_LSB                                   14
#define PHY_CTRL5_FORCE_TEST_J_MASK                                  0x00004000
#define PHY_CTRL5_FORCE_TEST_J_GET(x)                                (((x) & PHY_CTRL5_FORCE_TEST_J_MASK) >> PHY_CTRL5_FORCE_TEST_J_LSB)
#define PHY_CTRL5_FORCE_TEST_J_SET(x)                                (((x) << PHY_CTRL5_FORCE_TEST_J_LSB) & PHY_CTRL5_FORCE_TEST_J_MASK)
#define PHY_CTRL5_FORCE_TEST_J_RESET                                 0x0 // 0
#define PHY_CTRL5_FORCE_IDDQ_MSB                                     13
#define PHY_CTRL5_FORCE_IDDQ_LSB                                     13
#define PHY_CTRL5_FORCE_IDDQ_MASK                                    0x00002000
#define PHY_CTRL5_FORCE_IDDQ_GET(x)                                  (((x) & PHY_CTRL5_FORCE_IDDQ_MASK) >> PHY_CTRL5_FORCE_IDDQ_LSB)
#define PHY_CTRL5_FORCE_IDDQ_SET(x)                                  (((x) << PHY_CTRL5_FORCE_IDDQ_LSB) & PHY_CTRL5_FORCE_IDDQ_MASK)
#define PHY_CTRL5_FORCE_IDDQ_RESET                                   0x0 // 0
#define PHY_CTRL5_EB_WATERMARK_MSB                                   12
#define PHY_CTRL5_EB_WATERMARK_LSB                                   7
#define PHY_CTRL5_EB_WATERMARK_MASK                                  0x00001f80
#define PHY_CTRL5_EB_WATERMARK_GET(x)                                (((x) & PHY_CTRL5_EB_WATERMARK_MASK) >> PHY_CTRL5_EB_WATERMARK_LSB)
#define PHY_CTRL5_EB_WATERMARK_SET(x)                                (((x) << PHY_CTRL5_EB_WATERMARK_LSB) & PHY_CTRL5_EB_WATERMARK_MASK)
#define PHY_CTRL5_EB_WATERMARK_RESET                                 0x14 // 20
#define PHY_CTRL5_TX_BIAS_DELAY_MSB                                  6
#define PHY_CTRL5_TX_BIAS_DELAY_LSB                                  0
#define PHY_CTRL5_TX_BIAS_DELAY_MASK                                 0x0000007f
#define PHY_CTRL5_TX_BIAS_DELAY_GET(x)                               (((x) & PHY_CTRL5_TX_BIAS_DELAY_MASK) >> PHY_CTRL5_TX_BIAS_DELAY_LSB)
#define PHY_CTRL5_TX_BIAS_DELAY_SET(x)                               (((x) << PHY_CTRL5_TX_BIAS_DELAY_LSB) & PHY_CTRL5_TX_BIAS_DELAY_MASK)
#define PHY_CTRL5_TX_BIAS_DELAY_RESET                                0x32 // 50
#define PHY_CTRL5_ADDRESS                                            0x18116c94
#define PHY_CTRL5_OFFSET                                             0x0014
// SW modifiable bits
#define PHY_CTRL5_SW_MASK                                            0xffffffff
// bits defined at reset
#define PHY_CTRL5_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL5_RESET                                              0x3b200a32
#define PHY_CTRL5_RESET_1					     0x3b202a58

#define PHY_CTRL6_SPARE_BITS_MSB                                     31
#define PHY_CTRL6_SPARE_BITS_LSB                                     9
#define PHY_CTRL6_SPARE_BITS_MASK                                    0xfffffe00
#define PHY_CTRL6_SPARE_BITS_GET(x)                                  (((x) & PHY_CTRL6_SPARE_BITS_MASK) >> PHY_CTRL6_SPARE_BITS_LSB)
#define PHY_CTRL6_SPARE_BITS_SET(x)                                  (((x) << PHY_CTRL6_SPARE_BITS_LSB) & PHY_CTRL6_SPARE_BITS_MASK)
#define PHY_CTRL6_SPARE_BITS_RESET                                   0x0 // 0
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_MSB                            8
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_LSB                            8
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_MASK                           0x00000100
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_GET(x)                         (((x) & PHY_CTRL6_DIS_SETUP_RETRY_FIX_MASK) >> PHY_CTRL6_DIS_SETUP_RETRY_FIX_LSB)
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_SET(x)                         (((x) << PHY_CTRL6_DIS_SETUP_RETRY_FIX_LSB) & PHY_CTRL6_DIS_SETUP_RETRY_FIX_MASK)
#define PHY_CTRL6_DIS_SETUP_RETRY_FIX_RESET                          0x0 // 0
#define PHY_CTRL6_XCVR_SEL_MSB                                       7
#define PHY_CTRL6_XCVR_SEL_LSB                                       6
#define PHY_CTRL6_XCVR_SEL_MASK                                      0x000000c0
#define PHY_CTRL6_XCVR_SEL_GET(x)                                    (((x) & PHY_CTRL6_XCVR_SEL_MASK) >> PHY_CTRL6_XCVR_SEL_LSB)
#define PHY_CTRL6_XCVR_SEL_SET(x)                                    (((x) << PHY_CTRL6_XCVR_SEL_LSB) & PHY_CTRL6_XCVR_SEL_MASK)
#define PHY_CTRL6_XCVR_SEL_RESET                                     0x0 // 0
#define PHY_CTRL6_XCVRSEL_OVERRIDE_MSB                               5
#define PHY_CTRL6_XCVRSEL_OVERRIDE_LSB                               5
#define PHY_CTRL6_XCVRSEL_OVERRIDE_MASK                              0x00000020
#define PHY_CTRL6_XCVRSEL_OVERRIDE_GET(x)                            (((x) & PHY_CTRL6_XCVRSEL_OVERRIDE_MASK) >> PHY_CTRL6_XCVRSEL_OVERRIDE_LSB)
#define PHY_CTRL6_XCVRSEL_OVERRIDE_SET(x)                            (((x) << PHY_CTRL6_XCVRSEL_OVERRIDE_LSB) & PHY_CTRL6_XCVRSEL_OVERRIDE_MASK)
#define PHY_CTRL6_XCVRSEL_OVERRIDE_RESET                             0x0 // 0
#define PHY_CTRL6_IDDIG_MSB                                          4
#define PHY_CTRL6_IDDIG_LSB                                          4
#define PHY_CTRL6_IDDIG_MASK                                         0x00000010
#define PHY_CTRL6_IDDIG_GET(x)                                       (((x) & PHY_CTRL6_IDDIG_MASK) >> PHY_CTRL6_IDDIG_LSB)
#define PHY_CTRL6_IDDIG_SET(x)                                       (((x) << PHY_CTRL6_IDDIG_LSB) & PHY_CTRL6_IDDIG_MASK)
#define PHY_CTRL6_IDDIG_RESET                                        0x0 // 0
#define PHY_CTRL6_SESSEND_MSB                                        3
#define PHY_CTRL6_SESSEND_LSB                                        3
#define PHY_CTRL6_SESSEND_MASK                                       0x00000008
#define PHY_CTRL6_SESSEND_GET(x)                                     (((x) & PHY_CTRL6_SESSEND_MASK) >> PHY_CTRL6_SESSEND_LSB)
#define PHY_CTRL6_SESSEND_SET(x)                                     (((x) << PHY_CTRL6_SESSEND_LSB) & PHY_CTRL6_SESSEND_MASK)
#define PHY_CTRL6_SESSEND_RESET                                      0x0 // 0
#define PHY_CTRL6_VBUSVALID_MSB                                      2
#define PHY_CTRL6_VBUSVALID_LSB                                      2
#define PHY_CTRL6_VBUSVALID_MASK                                     0x00000004
#define PHY_CTRL6_VBUSVALID_GET(x)                                   (((x) & PHY_CTRL6_VBUSVALID_MASK) >> PHY_CTRL6_VBUSVALID_LSB)
#define PHY_CTRL6_VBUSVALID_SET(x)                                   (((x) << PHY_CTRL6_VBUSVALID_LSB) & PHY_CTRL6_VBUSVALID_MASK)
#define PHY_CTRL6_VBUSVALID_RESET                                    0x1 // 1
#define PHY_CTRL6_BVALID_MSB                                         1
#define PHY_CTRL6_BVALID_LSB                                         1
#define PHY_CTRL6_BVALID_MASK                                        0x00000002
#define PHY_CTRL6_BVALID_GET(x)                                      (((x) & PHY_CTRL6_BVALID_MASK) >> PHY_CTRL6_BVALID_LSB)
#define PHY_CTRL6_BVALID_SET(x)                                      (((x) << PHY_CTRL6_BVALID_LSB) & PHY_CTRL6_BVALID_MASK)
#define PHY_CTRL6_BVALID_RESET                                       0x1 // 1
#define PHY_CTRL6_AVALID_MSB                                         0
#define PHY_CTRL6_AVALID_LSB                                         0
#define PHY_CTRL6_AVALID_MASK                                        0x00000001
#define PHY_CTRL6_AVALID_GET(x)                                      (((x) & PHY_CTRL6_AVALID_MASK) >> PHY_CTRL6_AVALID_LSB)
#define PHY_CTRL6_AVALID_SET(x)                                      (((x) << PHY_CTRL6_AVALID_LSB) & PHY_CTRL6_AVALID_MASK)
#define PHY_CTRL6_AVALID_RESET                                       0x1 // 1
#define PHY_CTRL6_ADDRESS                                            0x18116c98
#define PHY_CTRL6_OFFSET                                             0x0018
// SW modifiable bits
#define PHY_CTRL6_SW_MASK                                            0xffffffff
// bits defined at reset
#define PHY_CTRL6_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL6_RESET                                              0x00000007

#define PHY_STATUS_TX_CAL_MSB                                        3
#define PHY_STATUS_TX_CAL_LSB                                        0
#define PHY_STATUS_TX_CAL_MASK                                       0x0000000f
#define PHY_STATUS_TX_CAL_GET(x)                                     (((x) & PHY_STATUS_TX_CAL_MASK) >> PHY_STATUS_TX_CAL_LSB)
#define PHY_STATUS_TX_CAL_SET(x)                                     (((x) << PHY_STATUS_TX_CAL_LSB) & PHY_STATUS_TX_CAL_MASK)
#define PHY_STATUS_TX_CAL_RESET                                      0x0 // 0
#define PHY_STATUS_ADDRESS                                           0x18116c9c
#define PHY_STATUS_OFFSET                                            0x001c
// SW modifiable bits
#define PHY_STATUS_SW_MASK                                           0x0000000f
// bits defined at reset
#define PHY_STATUS_RSTMASK                                           0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_STATUS_RESET                                             0x00000000

#define PHY_CTRL7_PPRBS_ERROR_RATE_MSB                               31
#define PHY_CTRL7_PPRBS_ERROR_RATE_LSB                               11
#define PHY_CTRL7_PPRBS_ERROR_RATE_MASK                              0xfffff800
#define PHY_CTRL7_PPRBS_ERROR_RATE_GET(x)                            (((x) & PHY_CTRL7_PPRBS_ERROR_RATE_MASK) >> PHY_CTRL7_PPRBS_ERROR_RATE_LSB)
#define PHY_CTRL7_PPRBS_ERROR_RATE_SET(x)                            (((x) << PHY_CTRL7_PPRBS_ERROR_RATE_LSB) & PHY_CTRL7_PPRBS_ERROR_RATE_MASK)
#define PHY_CTRL7_PPRBS_ERROR_RATE_RESET                             0xa000 // 40960
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_MSB                          10
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_LSB                          1
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_MASK                         0x000007fe
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_GET(x)                       (((x) & PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_MASK) >> PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_LSB)
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_SET(x)                       (((x) << PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_LSB) & PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_MASK)
#define PHY_CTRL7_PPRBS_TOTAL_NUMOF_ERR_RESET                        0x0 // 0
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_MSB                            0
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_LSB                            0
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_MASK                           0x00000001
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_GET(x)                         (((x) & PHY_CTRL7_PPRBS_TRIGGER_ERROR_MASK) >> PHY_CTRL7_PPRBS_TRIGGER_ERROR_LSB)
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_SET(x)                         (((x) << PHY_CTRL7_PPRBS_TRIGGER_ERROR_LSB) & PHY_CTRL7_PPRBS_TRIGGER_ERROR_MASK)
#define PHY_CTRL7_PPRBS_TRIGGER_ERROR_RESET                          0x0 // 0
#define PHY_CTRL7_ADDRESS                                            0x18116ca0
#define PHY_CTRL7_OFFSET                                             0x0020
// SW modifiable bits
#define PHY_CTRL7_SW_MASK                                            0xffffffff
// bits defined at reset
#define PHY_CTRL7_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL7_RESET                                              0x05000000

#define PHY_CTRL8_USBPLL_PWD_MSB                                     7
#define PHY_CTRL8_USBPLL_PWD_LSB                                     7
#define PHY_CTRL8_USBPLL_PWD_MASK                                    0x00000080
#define PHY_CTRL8_USBPLL_PWD_GET(x)                                  (((x) & PHY_CTRL8_USBPLL_PWD_MASK) >> PHY_CTRL8_USBPLL_PWD_LSB)
#define PHY_CTRL8_USBPLL_PWD_SET(x)                                  (((x) << PHY_CTRL8_USBPLL_PWD_LSB) & PHY_CTRL8_USBPLL_PWD_MASK)
#define PHY_CTRL8_USBPLL_PWD_RESET                                   0x0 // 0
#define PHY_CTRL8_TX_FASTRISE_MSB                                    6
#define PHY_CTRL8_TX_FASTRISE_LSB                                    4
#define PHY_CTRL8_TX_FASTRISE_MASK                                   0x00000070
#define PHY_CTRL8_TX_FASTRISE_GET(x)                                 (((x) & PHY_CTRL8_TX_FASTRISE_MASK) >> PHY_CTRL8_TX_FASTRISE_LSB)
#define PHY_CTRL8_TX_FASTRISE_SET(x)                                 (((x) << PHY_CTRL8_TX_FASTRISE_LSB) & PHY_CTRL8_TX_FASTRISE_MASK)
#define PHY_CTRL8_TX_FASTRISE_RESET                                  0x5 // 5
#define PHY_CTRL8_TX_ENPRE_MSB                                       3
#define PHY_CTRL8_TX_ENPRE_LSB                                       2
#define PHY_CTRL8_TX_ENPRE_MASK                                      0x0000000c
#define PHY_CTRL8_TX_ENPRE_GET(x)                                    (((x) & PHY_CTRL8_TX_ENPRE_MASK) >> PHY_CTRL8_TX_ENPRE_LSB)
#define PHY_CTRL8_TX_ENPRE_SET(x)                                    (((x) << PHY_CTRL8_TX_ENPRE_LSB) & PHY_CTRL8_TX_ENPRE_MASK)
#define PHY_CTRL8_TX_ENPRE_RESET                                     0x0 // 0
#define PHY_CTRL8_RX_SQ_HYST_EN_MSB                                  1
#define PHY_CTRL8_RX_SQ_HYST_EN_LSB                                  1
#define PHY_CTRL8_RX_SQ_HYST_EN_MASK                                 0x00000002
#define PHY_CTRL8_RX_SQ_HYST_EN_GET(x)                               (((x) & PHY_CTRL8_RX_SQ_HYST_EN_MASK) >> PHY_CTRL8_RX_SQ_HYST_EN_LSB)
#define PHY_CTRL8_RX_SQ_HYST_EN_SET(x)                               (((x) << PHY_CTRL8_RX_SQ_HYST_EN_LSB) & PHY_CTRL8_RX_SQ_HYST_EN_MASK)
#define PHY_CTRL8_RX_SQ_HYST_EN_RESET                                0x0 // 0
#define PHY_CTRL8_RX_SKIP2_MSB                                       0
#define PHY_CTRL8_RX_SKIP2_LSB                                       0
#define PHY_CTRL8_RX_SKIP2_MASK                                      0x00000001
#define PHY_CTRL8_RX_SKIP2_GET(x)                                    (((x) & PHY_CTRL8_RX_SKIP2_MASK) >> PHY_CTRL8_RX_SKIP2_LSB)
#define PHY_CTRL8_RX_SKIP2_SET(x)                                    (((x) << PHY_CTRL8_RX_SKIP2_LSB) & PHY_CTRL8_RX_SKIP2_MASK)
#define PHY_CTRL8_RX_SKIP2_RESET                                     0x0 // 0
#define PHY_CTRL8_ADDRESS                                            0x18116ca4
#define PHY_CTRL8_OFFSET                                             0x0024
// SW modifiable bits
#define PHY_CTRL8_SW_MASK                                            0x000000ff
// bits defined at reset
#define PHY_CTRL8_RSTMASK                                            0xffffffff
// reset value (ignore bits undefined at reset)
#define PHY_CTRL8_RESET                                              0x00000050
#define CPU_DDR_CLOCK_CONTROL_SPARE_MSB                              31
#define CPU_DDR_CLOCK_CONTROL_SPARE_LSB                              25
#define CPU_DDR_CLOCK_CONTROL_SPARE_MASK                             0xfe000000
#define CPU_DDR_CLOCK_CONTROL_SPARE_GET(x)                           (((x) & CPU_DDR_CLOCK_CONTROL_SPARE_MASK) >> CPU_DDR_CLOCK_CONTROL_SPARE_LSB)
#define CPU_DDR_CLOCK_CONTROL_SPARE_SET(x)                           (((x) << CPU_DDR_CLOCK_CONTROL_SPARE_LSB) & CPU_DDR_CLOCK_CONTROL_SPARE_MASK)
#define CPU_DDR_CLOCK_CONTROL_SPARE_RESET                            0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MSB                 24
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB                 24
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK                0x01000000
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_LSB) & CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_RESET               0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MSB            23
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB            23
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK           0x00800000
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_GET(x)         (((x) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_SET(x)         (((x) << CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_DEASSRT_RESET          0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MSB               22
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB               22
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK              0x00400000
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_GET(x)            (((x) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_SET(x)            (((x) << CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_RESET_EN_BP_ASRT_RESET             0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MSB                 21
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB                 21
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK                0x00200000
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_LSB) & CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_RESET               0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MSB                 20
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB                 20
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK                0x00100000
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_GET(x)              (((x) & CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK) >> CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_SET(x)              (((x) << CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_LSB) & CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_RESET               0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MSB                       19
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB                       15
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK                      0x000f8000
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHB_POST_DIV_RESET                     0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MSB                       14
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB                       10
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK                      0x00007c00
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDR_POST_DIV_RESET                     0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MSB                       9
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB                       5
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK                      0x000003e0
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_POST_DIV_RESET                     0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MSB                     4
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB                     4
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK                    0x00000010
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_AHB_PLL_BYPASS_RESET                   0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MSB                     3
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB                     3
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK                    0x00000008
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_DDR_PLL_BYPASS_RESET                   0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MSB                     2
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB                     2
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK                    0x00000004
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_GET(x)                  (((x) & CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK) >> CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB)
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_SET(x)                  (((x) << CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_LSB) & CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_MASK)
#define CPU_DDR_CLOCK_CONTROL_CPU_PLL_BYPASS_RESET                   0x1 // 1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MSB                       1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB                       1
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK                      0x00000002
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK) >> CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB)
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_LSB) & CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_MASK)
#define CPU_DDR_CLOCK_CONTROL_RESET_SWITCH_RESET                     0x0 // 0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MSB                       0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB                       0
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK                      0x00000001
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_GET(x)                    (((x) & CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK) >> CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB)
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_SET(x)                    (((x) << CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_LSB) & CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_MASK)
#define CPU_DDR_CLOCK_CONTROL_CLOCK_SWITCH_RESET                     0x0 // 0
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
#define PCIE_PLL_CONFIG_ADDRESS                                      0x18050010

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
#define PCIE_PLL_DITHER_DIV_MAX_ADDRESS                              0x18050014

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
#define PCIE_PLL_DITHER_DIV_MIN_ADDRESS                              0x18050018

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
#define PCIE_PLL_DITHER_STEP_ADDRESS                                 0x1805001c



// 32'h180f0008 (PCIE_PWR_MGMT)
#define PCIE_PWR_MGMT_PME_INT_MSB                                    8
#define PCIE_PWR_MGMT_PME_INT_LSB                                    8
#define PCIE_PWR_MGMT_PME_INT_MASK                                   0x00000100
#define PCIE_PWR_MGMT_PME_INT_GET(x)                                 (((x) & PCIE_PWR_MGMT_PME_INT_MASK) >> PCIE_PWR_MGMT_PME_INT_LSB)
#define PCIE_PWR_MGMT_PME_INT_SET(x)                                 (((x) << PCIE_PWR_MGMT_PME_INT_LSB) & PCIE_PWR_MGMT_PME_INT_MASK)
#define PCIE_PWR_MGMT_PME_INT_RESET                                  0x0 // 0
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_MSB                             7
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB                             7
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK                            0x00000080
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_GET(x)                          (((x) & PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK) >> PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB)
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_SET(x)                          (((x) << PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB) & PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK)
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_MSB                             6
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB                             6
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK                            0x00000040
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_GET(x)                          (((x) & PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK) >> PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB)
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_SET(x)                          (((x) << PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB) & PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK)
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_RADM_PM_PME_MSB                                5
#define PCIE_PWR_MGMT_RADM_PM_PME_LSB                                5
#define PCIE_PWR_MGMT_RADM_PM_PME_MASK                               0x00000020
#define PCIE_PWR_MGMT_RADM_PM_PME_GET(x)                             (((x) & PCIE_PWR_MGMT_RADM_PM_PME_MASK) >> PCIE_PWR_MGMT_RADM_PM_PME_LSB)
#define PCIE_PWR_MGMT_RADM_PM_PME_SET(x)                             (((x) << PCIE_PWR_MGMT_RADM_PM_PME_LSB) & PCIE_PWR_MGMT_RADM_PM_PME_MASK)
#define PCIE_PWR_MGMT_RADM_PM_PME_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_AUX_PM_EN_MSB                                  4
#define PCIE_PWR_MGMT_AUX_PM_EN_LSB                                  4
#define PCIE_PWR_MGMT_AUX_PM_EN_MASK                                 0x00000010
#define PCIE_PWR_MGMT_AUX_PM_EN_GET(x)                               (((x) & PCIE_PWR_MGMT_AUX_PM_EN_MASK) >> PCIE_PWR_MGMT_AUX_PM_EN_LSB)
#define PCIE_PWR_MGMT_AUX_PM_EN_SET(x)                               (((x) << PCIE_PWR_MGMT_AUX_PM_EN_LSB) & PCIE_PWR_MGMT_AUX_PM_EN_MASK)
#define PCIE_PWR_MGMT_AUX_PM_EN_RESET                                0x0 // 0
#define PCIE_PWR_MGMT_READY_ENTR_L23_MSB                             3
#define PCIE_PWR_MGMT_READY_ENTR_L23_LSB                             3
#define PCIE_PWR_MGMT_READY_ENTR_L23_MASK                            0x00000008
#define PCIE_PWR_MGMT_READY_ENTR_L23_GET(x)                          (((x) & PCIE_PWR_MGMT_READY_ENTR_L23_MASK) >> PCIE_PWR_MGMT_READY_ENTR_L23_LSB)
#define PCIE_PWR_MGMT_READY_ENTR_L23_SET(x)                          (((x) << PCIE_PWR_MGMT_READY_ENTR_L23_LSB) & PCIE_PWR_MGMT_READY_ENTR_L23_MASK)
#define PCIE_PWR_MGMT_READY_ENTR_L23_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_REQ_EXIT_L1_MSB                                2
#define PCIE_PWR_MGMT_REQ_EXIT_L1_LSB                                2
#define PCIE_PWR_MGMT_REQ_EXIT_L1_MASK                               0x00000004
#define PCIE_PWR_MGMT_REQ_EXIT_L1_GET(x)                             (((x) & PCIE_PWR_MGMT_REQ_EXIT_L1_MASK) >> PCIE_PWR_MGMT_REQ_EXIT_L1_LSB)
#define PCIE_PWR_MGMT_REQ_EXIT_L1_SET(x)                             (((x) << PCIE_PWR_MGMT_REQ_EXIT_L1_LSB) & PCIE_PWR_MGMT_REQ_EXIT_L1_MASK)
#define PCIE_PWR_MGMT_REQ_EXIT_L1_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_MSB                               1
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB                               1
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK                              0x00000002
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_GET(x)                            (((x) & PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK) >> PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB)
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_SET(x)                            (((x) << PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB) & PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK)
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_RESET                             0x0 // 0
#define PCIE_PWR_MGMT_AUX_PWR_DET_MSB                                0
#define PCIE_PWR_MGMT_AUX_PWR_DET_LSB                                0
#define PCIE_PWR_MGMT_AUX_PWR_DET_MASK                               0x00000001
#define PCIE_PWR_MGMT_AUX_PWR_DET_GET(x)                             (((x) & PCIE_PWR_MGMT_AUX_PWR_DET_MASK) >> PCIE_PWR_MGMT_AUX_PWR_DET_LSB)
#define PCIE_PWR_MGMT_AUX_PWR_DET_SET(x)                             (((x) << PCIE_PWR_MGMT_AUX_PWR_DET_LSB) & PCIE_PWR_MGMT_AUX_PWR_DET_MASK)
#define PCIE_PWR_MGMT_AUX_PWR_DET_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_ADDRESS                                        0x180f0008
#define PCIE_PWR_MGMT_OFFSET                                         0x0008
// SW modifiable bits
#define PCIE_PWR_MGMT_SW_MASK                                        0x000001ff
// bits defined at reset
#define PCIE_PWR_MGMT_RSTMASK                                        0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PWR_MGMT_RESET                                          0x00000000


// 32'h180600c0 (RST_CLKGAT_EN)
#define RST_CLKGAT_EN_SPARE_MSB                                      31
#define RST_CLKGAT_EN_SPARE_LSB                                      12
#define RST_CLKGAT_EN_SPARE_MASK                                     0xfffff000
#define RST_CLKGAT_EN_SPARE_GET(x)                                   (((x) & RST_CLKGAT_EN_SPARE_MASK) >> RST_CLKGAT_EN_SPARE_LSB)
#define RST_CLKGAT_EN_SPARE_SET(x)                                   (((x) << RST_CLKGAT_EN_SPARE_LSB) & RST_CLKGAT_EN_SPARE_MASK)
#define RST_CLKGAT_EN_SPARE_RESET                                    0x0 // 0
#define RST_CLKGAT_EN_WMAC_MSB                                       9
#define RST_CLKGAT_EN_WMAC_LSB                                       9
#define RST_CLKGAT_EN_WMAC_MASK                                      0x00000200
#define RST_CLKGAT_EN_WMAC_GET(x)                                    (((x) & RST_CLKGAT_EN_WMAC_MASK) >> RST_CLKGAT_EN_WMAC_LSB)
#define RST_CLKGAT_EN_WMAC_SET(x)                                    (((x) << RST_CLKGAT_EN_WMAC_LSB) & RST_CLKGAT_EN_WMAC_MASK)
#define RST_CLKGAT_EN_WMAC_RESET                                     0x1 // 1
#define RST_CLKGAT_EN_USB1_MSB                                       7
#define RST_CLKGAT_EN_USB1_LSB                                       7
#define RST_CLKGAT_EN_USB1_MASK                                      0x00000080
#define RST_CLKGAT_EN_USB1_GET(x)                                    (((x) & RST_CLKGAT_EN_USB1_MASK) >> RST_CLKGAT_EN_USB1_LSB)
#define RST_CLKGAT_EN_USB1_SET(x)                                    (((x) << RST_CLKGAT_EN_USB1_LSB) & RST_CLKGAT_EN_USB1_MASK)
#define RST_CLKGAT_EN_USB1_RESET                                     0x1 // 1
#define RST_CLKGAT_EN_GE1_MSB                                        6
#define RST_CLKGAT_EN_GE1_LSB                                        6
#define RST_CLKGAT_EN_GE1_MASK                                       0x00000040
#define RST_CLKGAT_EN_GE1_GET(x)                                     (((x) & RST_CLKGAT_EN_GE1_MASK) >> RST_CLKGAT_EN_GE1_LSB)
#define RST_CLKGAT_EN_GE1_SET(x)                                     (((x) << RST_CLKGAT_EN_GE1_LSB) & RST_CLKGAT_EN_GE1_MASK)
#define RST_CLKGAT_EN_GE1_RESET                                      0x1 // 1
#define RST_CLKGAT_EN_GE0_MSB                                        5
#define RST_CLKGAT_EN_GE0_LSB                                        5
#define RST_CLKGAT_EN_GE0_MASK                                       0x00000020
#define RST_CLKGAT_EN_GE0_GET(x)                                     (((x) & RST_CLKGAT_EN_GE0_MASK) >> RST_CLKGAT_EN_GE0_LSB)
#define RST_CLKGAT_EN_GE0_SET(x)                                     (((x) << RST_CLKGAT_EN_GE0_LSB) & RST_CLKGAT_EN_GE0_MASK)
#define RST_CLKGAT_EN_GE0_RESET                                      0x1 // 1
#define RST_CLKGAT_EN_PCIE_RC_MSB                                    1
#define RST_CLKGAT_EN_PCIE_RC_LSB                                    1
#define RST_CLKGAT_EN_PCIE_RC_MASK                                   0x00000002
#define RST_CLKGAT_EN_PCIE_RC_GET(x)                                 (((x) & RST_CLKGAT_EN_PCIE_RC_MASK) >> RST_CLKGAT_EN_PCIE_RC_LSB)
#define RST_CLKGAT_EN_PCIE_RC_SET(x)                                 (((x) << RST_CLKGAT_EN_PCIE_RC_LSB) & RST_CLKGAT_EN_PCIE_RC_MASK)
#define RST_CLKGAT_EN_PCIE_RC_RESET                                  0x1 // 1
#define RST_CLKGAT_EN_ADDRESS                                        0x180600c0
#define RST_CLKGAT_EN_OFFSET                                         0x00c0
// SW modifiable bits
#define RST_CLKGAT_EN_SW_MASK                                        0xfffff2e2
// bits defined at reset
#define RST_CLKGAT_EN_RSTMASK                                        0xffffffff
// reset value (ignore bits undefined at reset)
#define RST_CLKGAT_EN_RESET                                          0x000002e2



#define PCIE_PHY_REG_1_ADDRESS                                       0x18116cc0
#define PCIE_PHY_REG_3_ADDRESS                                       0x18116cc8





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
#define LDO_POWER_CONTROL_ADDRESS                                    0x18050020

#define SWITCH_CLOCK_SPARE_SPARE_MSB                                 31
#define SWITCH_CLOCK_SPARE_SPARE_LSB                                 12
#define SWITCH_CLOCK_SPARE_SPARE_MASK                                0xfffff000
#define SWITCH_CLOCK_SPARE_SPARE_GET(x)                              (((x) & SWITCH_CLOCK_SPARE_SPARE_MASK) >> SWITCH_CLOCK_SPARE_SPARE_LSB)
#define SWITCH_CLOCK_SPARE_SPARE_SET(x)                              (((x) << SWITCH_CLOCK_SPARE_SPARE_LSB) & SWITCH_CLOCK_SPARE_SPARE_MASK)
#define SWITCH_CLOCK_SPARE_SPARE_RESET                               0x0 // 0
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
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MSB                          6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB                          6
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK                         0x00000040
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_GET(x)                       (((x) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_SET(x)                       (((x) << SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_LSB) & SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_MDIO_CLK_SEL_RESET                        0x0 // 0
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MSB                       5
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB                       5
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK                      0x00000020
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_GET(x)                    (((x) & SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK) >> SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB)
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_SET(x)                    (((x) << SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_LSB) & SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_MASK)
#define SWITCH_CLOCK_SPARE_OEN_CLK125M_PLL_RESET                     0x1 // 1
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_MSB                            4
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB                            4
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK                           0x00000010
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_GET(x)                         (((x) & SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK) >> SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB)
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_SET(x)                         (((x) << SWITCH_CLOCK_SPARE_EN_PLL_TOP_LSB) & SWITCH_CLOCK_SPARE_EN_PLL_TOP_MASK)
#define SWITCH_CLOCK_SPARE_EN_PLL_TOP_RESET                          0x1 // 1
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_MSB                            3
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB                            3
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK                           0x00000008
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_GET(x)                         (((x) & SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK) >> SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB)
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_SET(x)                         (((x) << SWITCH_CLOCK_SPARE_EEE_ENABLE_LSB) & SWITCH_CLOCK_SPARE_EEE_ENABLE_MASK)
#define SWITCH_CLOCK_SPARE_EEE_ENABLE_RESET                          0x0 // 0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MSB             2
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB             2
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK            0x00000004
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_GET(x)          (((x) & SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK) >> SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_SET(x)          (((x) << SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_LSB) & SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_MASK)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_FROM_PYTHON_OFF_RESET           0x0 // 0
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MSB                  1
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB                  1
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK                 0x00000002
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_GET(x)               (((x) & SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK) >> SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB)
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_SET(x)               (((x) << SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_LSB) & SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_MASK)
#define SWITCH_CLOCK_SPARE_SWITCH_FUNC_TST_MODE_RESET                0x0 // 0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MSB                         0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB                         0
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK                        0x00000001
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_GET(x)                      (((x) & SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK) >> SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_SET(x)                      (((x) << SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_LSB) & SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_MASK)
#define SWITCH_CLOCK_SPARE_SWITCHCLK_SEL_RESET                       0x1 // 1
#define SWITCH_CLOCK_SPARE_ADDRESS                                   0x18050024

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
#define CURRENT_PCIE_PLL_DITHER_ADDRESS                              0x18050028

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
#define ETH_XMII_ADDRESS                                             0x1805002c

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
#define BB_PLL_CONFIG_ADDRESS                                        0x18050040

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
#define DDR_PLL_DITHER_ADDRESS                                       0x18050044

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
#define CPU_PLL_DITHER_ADDRESS                                       0x18050048

#define RST_RESET_USB_EXT_PWR_SEQ_MSB                                29
#define RST_RESET_USB_EXT_PWR_SEQ_LSB                                29
#define RST_RESET_USB_EXT_PWR_SEQ_MASK                               0x20000000
#define RST_RESET_USB_EXT_PWR_SEQ_GET(x)                             (((x) & RST_RESET_USB_EXT_PWR_SEQ_MASK) >> RST_RESET_USB_EXT_PWR_SEQ_LSB)
#define RST_RESET_USB_EXT_PWR_SEQ_SET(x)                             (((x) << RST_RESET_USB_EXT_PWR_SEQ_LSB) & RST_RESET_USB_EXT_PWR_SEQ_MASK)
#define RST_RESET_USB_EXT_PWR_SEQ_RESET                              0x1 // 1
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
#define RST_RESET_GE1_MAC_RESET_MSB                                  13
#define RST_RESET_GE1_MAC_RESET_LSB                                  13
#define RST_RESET_GE1_MAC_RESET_MASK                                 0x00002000
#define RST_RESET_GE1_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE1_MAC_RESET_MASK) >> RST_RESET_GE1_MAC_RESET_LSB)
#define RST_RESET_GE1_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE1_MAC_RESET_LSB) & RST_RESET_GE1_MAC_RESET_MASK)
#define RST_RESET_GE1_MAC_RESET_RESET                                0x1 // 1
#define RST_RESET_ETH_SWITCH_ARESET_MSB                              12
#define RST_RESET_ETH_SWITCH_ARESET_LSB                              12
#define RST_RESET_ETH_SWITCH_ARESET_MASK                             0x00001000
#define RST_RESET_ETH_SWITCH_ARESET_GET(x)                           (((x) & RST_RESET_ETH_SWITCH_ARESET_MASK) >> RST_RESET_ETH_SWITCH_ARESET_LSB)
#define RST_RESET_ETH_SWITCH_ARESET_SET(x)                           (((x) << RST_RESET_ETH_SWITCH_ARESET_LSB) & RST_RESET_ETH_SWITCH_ARESET_MASK)
#define RST_RESET_ETH_SWITCH_ARESET_RESET                            0x1 // 1
#define RST_RESET_USB_PHY_ARESET_MSB                                 11
#define RST_RESET_USB_PHY_ARESET_LSB                                 11
#define RST_RESET_USB_PHY_ARESET_MASK                                0x00000800
#define RST_RESET_USB_PHY_ARESET_GET(x)                              (((x) & RST_RESET_USB_PHY_ARESET_MASK) >> RST_RESET_USB_PHY_ARESET_LSB)
#define RST_RESET_USB_PHY_ARESET_SET(x)                              (((x) << RST_RESET_USB_PHY_ARESET_LSB) & RST_RESET_USB_PHY_ARESET_MASK)
#define RST_RESET_USB_PHY_ARESET_RESET                               0x1 // 1
#define RST_RESET_GE0_MAC_RESET_MSB                                  9
#define RST_RESET_GE0_MAC_RESET_LSB                                  9
#define RST_RESET_GE0_MAC_RESET_MASK                                 0x00000200
#define RST_RESET_GE0_MAC_RESET_GET(x)                               (((x) & RST_RESET_GE0_MAC_RESET_MASK) >> RST_RESET_GE0_MAC_RESET_LSB)
#define RST_RESET_GE0_MAC_RESET_SET(x)                               (((x) << RST_RESET_GE0_MAC_RESET_LSB) & RST_RESET_GE0_MAC_RESET_MASK)
#define RST_RESET_GE0_MAC_RESET_RESET                                0x1 // 1
#define RST_RESET_ETH_SWITCH_RESET_MSB                               8
#define RST_RESET_ETH_SWITCH_RESET_LSB                               8
#define RST_RESET_ETH_SWITCH_RESET_MASK                              0x00000100
#define RST_RESET_ETH_SWITCH_RESET_GET(x)                            (((x) & RST_RESET_ETH_SWITCH_RESET_MASK) >> RST_RESET_ETH_SWITCH_RESET_LSB)
#define RST_RESET_ETH_SWITCH_RESET_SET(x)                            (((x) << RST_RESET_ETH_SWITCH_RESET_LSB) & RST_RESET_ETH_SWITCH_RESET_MASK)
#define RST_RESET_ETH_SWITCH_RESET_RESET                             0x1 // 1
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
#define RST_RESET_ADDRESS                                            0x1806001c


#define RST_MISC2_SPARE_MSB                                          31
#define RST_MISC2_SPARE_LSB                                          26
#define RST_MISC2_SPARE_MASK                                         0xfc000000
#define RST_MISC2_SPARE_GET(x)                                       (((x) & RST_MISC2_SPARE_MASK) >> RST_MISC2_SPARE_LSB)
#define RST_MISC2_SPARE_SET(x)                                       (((x) << RST_MISC2_SPARE_LSB) & RST_MISC2_SPARE_MASK)
#define RST_MISC2_SPARE_RESET                                        0x0 // 0
#define RST_MISC2_PCIE_CLKOBS1_SEL_MSB                               19
#define RST_MISC2_PCIE_CLKOBS1_SEL_LSB                               19
#define RST_MISC2_PCIE_CLKOBS1_SEL_MASK                              0x00080000
#define RST_MISC2_PCIE_CLKOBS1_SEL_GET(x)                            (((x) & RST_MISC2_PCIE_CLKOBS1_SEL_MASK) >> RST_MISC2_PCIE_CLKOBS1_SEL_LSB)
#define RST_MISC2_PCIE_CLKOBS1_SEL_SET(x)                            (((x) << RST_MISC2_PCIE_CLKOBS1_SEL_LSB) & RST_MISC2_PCIE_CLKOBS1_SEL_MASK)
#define RST_MISC2_PCIE_CLKOBS1_SEL_RESET                             0x0 // 0
#define RST_MISC2_EXT_HOST_WASP_RST_EN_MSB                           18
#define RST_MISC2_EXT_HOST_WASP_RST_EN_LSB                           18
#define RST_MISC2_EXT_HOST_WASP_RST_EN_MASK                          0x00040000
#define RST_MISC2_EXT_HOST_WASP_RST_EN_GET(x)                        (((x) & RST_MISC2_EXT_HOST_WASP_RST_EN_MASK) >> RST_MISC2_EXT_HOST_WASP_RST_EN_LSB)
#define RST_MISC2_EXT_HOST_WASP_RST_EN_SET(x)                        (((x) << RST_MISC2_EXT_HOST_WASP_RST_EN_LSB) & RST_MISC2_EXT_HOST_WASP_RST_EN_MASK)
#define RST_MISC2_EXT_HOST_WASP_RST_EN_RESET                         0x0 // 0
#define RST_MISC2_PERSTN_RCPHY_MSB                                   13
#define RST_MISC2_PERSTN_RCPHY_LSB                                   13
#define RST_MISC2_PERSTN_RCPHY_MASK                                  0x00002000
#define RST_MISC2_PERSTN_RCPHY_GET(x)                                (((x) & RST_MISC2_PERSTN_RCPHY_MASK) >> RST_MISC2_PERSTN_RCPHY_LSB)
#define RST_MISC2_PERSTN_RCPHY_SET(x)                                (((x) << RST_MISC2_PERSTN_RCPHY_LSB) & RST_MISC2_PERSTN_RCPHY_MASK)
#define RST_MISC2_PERSTN_RCPHY_RESET                                 0x1 // 1
#define RST_MISC2_RESERVED_MSB                                       3
#define RST_MISC2_RESERVED_LSB                                       1
#define RST_MISC2_RESERVED_MASK                                      0x0000000e
#define RST_MISC2_RESERVED_GET(x)                                    (((x) & RST_MISC2_RESERVED_MASK) >> RST_MISC2_RESERVED_LSB)
#define RST_MISC2_RESERVED_SET(x)                                    (((x) << RST_MISC2_RESERVED_LSB) & RST_MISC2_RESERVED_MASK)
#define RST_MISC2_RESERVED_RESET                                     0x0 // 0
#define RST_MISC2_ADDRESS                                            0x180600bc

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

#define PCIE_PWR_MGMT_PME_INT_MSB                                    8
#define PCIE_PWR_MGMT_PME_INT_LSB                                    8
#define PCIE_PWR_MGMT_PME_INT_MASK                                   0x00000100
#define PCIE_PWR_MGMT_PME_INT_GET(x)                                 (((x) & PCIE_PWR_MGMT_PME_INT_MASK) >> PCIE_PWR_MGMT_PME_INT_LSB)
#define PCIE_PWR_MGMT_PME_INT_SET(x)                                 (((x) << PCIE_PWR_MGMT_PME_INT_LSB) & PCIE_PWR_MGMT_PME_INT_MASK)
#define PCIE_PWR_MGMT_PME_INT_RESET                                  0x0 // 0
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_MSB                             7
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB                             7
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK                            0x00000080
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_GET(x)                          (((x) & PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK) >> PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB)
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_SET(x)                          (((x) << PCIE_PWR_MGMT_ASSERT_CLKREQN_LSB) & PCIE_PWR_MGMT_ASSERT_CLKREQN_MASK)
#define PCIE_PWR_MGMT_ASSERT_CLKREQN_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_MSB                             6
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB                             6
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK                            0x00000040
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_GET(x)                          (((x) & PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK) >> PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB)
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_SET(x)                          (((x) << PCIE_PWR_MGMT_RADM_PM_TO_ACK_LSB) & PCIE_PWR_MGMT_RADM_PM_TO_ACK_MASK)
#define PCIE_PWR_MGMT_RADM_PM_TO_ACK_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_RADM_PM_PME_MSB                                5
#define PCIE_PWR_MGMT_RADM_PM_PME_LSB                                5
#define PCIE_PWR_MGMT_RADM_PM_PME_MASK                               0x00000020
#define PCIE_PWR_MGMT_RADM_PM_PME_GET(x)                             (((x) & PCIE_PWR_MGMT_RADM_PM_PME_MASK) >> PCIE_PWR_MGMT_RADM_PM_PME_LSB)
#define PCIE_PWR_MGMT_RADM_PM_PME_SET(x)                             (((x) << PCIE_PWR_MGMT_RADM_PM_PME_LSB) & PCIE_PWR_MGMT_RADM_PM_PME_MASK)
#define PCIE_PWR_MGMT_RADM_PM_PME_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_AUX_PM_EN_MSB                                  4
#define PCIE_PWR_MGMT_AUX_PM_EN_LSB                                  4
#define PCIE_PWR_MGMT_AUX_PM_EN_MASK                                 0x00000010
#define PCIE_PWR_MGMT_AUX_PM_EN_GET(x)                               (((x) & PCIE_PWR_MGMT_AUX_PM_EN_MASK) >> PCIE_PWR_MGMT_AUX_PM_EN_LSB)
#define PCIE_PWR_MGMT_AUX_PM_EN_SET(x)                               (((x) << PCIE_PWR_MGMT_AUX_PM_EN_LSB) & PCIE_PWR_MGMT_AUX_PM_EN_MASK)
#define PCIE_PWR_MGMT_AUX_PM_EN_RESET                                0x0 // 0
#define PCIE_PWR_MGMT_READY_ENTR_L23_MSB                             3
#define PCIE_PWR_MGMT_READY_ENTR_L23_LSB                             3
#define PCIE_PWR_MGMT_READY_ENTR_L23_MASK                            0x00000008
#define PCIE_PWR_MGMT_READY_ENTR_L23_GET(x)                          (((x) & PCIE_PWR_MGMT_READY_ENTR_L23_MASK) >> PCIE_PWR_MGMT_READY_ENTR_L23_LSB)
#define PCIE_PWR_MGMT_READY_ENTR_L23_SET(x)                          (((x) << PCIE_PWR_MGMT_READY_ENTR_L23_LSB) & PCIE_PWR_MGMT_READY_ENTR_L23_MASK)
#define PCIE_PWR_MGMT_READY_ENTR_L23_RESET                           0x0 // 0
#define PCIE_PWR_MGMT_REQ_EXIT_L1_MSB                                2
#define PCIE_PWR_MGMT_REQ_EXIT_L1_LSB                                2
#define PCIE_PWR_MGMT_REQ_EXIT_L1_MASK                               0x00000004
#define PCIE_PWR_MGMT_REQ_EXIT_L1_GET(x)                             (((x) & PCIE_PWR_MGMT_REQ_EXIT_L1_MASK) >> PCIE_PWR_MGMT_REQ_EXIT_L1_LSB)
#define PCIE_PWR_MGMT_REQ_EXIT_L1_SET(x)                             (((x) << PCIE_PWR_MGMT_REQ_EXIT_L1_LSB) & PCIE_PWR_MGMT_REQ_EXIT_L1_MASK)
#define PCIE_PWR_MGMT_REQ_EXIT_L1_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_MSB                               1
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB                               1
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK                              0x00000002
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_GET(x)                            (((x) & PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK) >> PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB)
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_SET(x)                            (((x) << PCIE_PWR_MGMT_REQ_ENTRY_L1_LSB) & PCIE_PWR_MGMT_REQ_ENTRY_L1_MASK)
#define PCIE_PWR_MGMT_REQ_ENTRY_L1_RESET                             0x0 // 0
#define PCIE_PWR_MGMT_AUX_PWR_DET_MSB                                0
#define PCIE_PWR_MGMT_AUX_PWR_DET_LSB                                0
#define PCIE_PWR_MGMT_AUX_PWR_DET_MASK                               0x00000001
#define PCIE_PWR_MGMT_AUX_PWR_DET_GET(x)                             (((x) & PCIE_PWR_MGMT_AUX_PWR_DET_MASK) >> PCIE_PWR_MGMT_AUX_PWR_DET_LSB)
#define PCIE_PWR_MGMT_AUX_PWR_DET_SET(x)                             (((x) << PCIE_PWR_MGMT_AUX_PWR_DET_LSB) & PCIE_PWR_MGMT_AUX_PWR_DET_MASK)
#define PCIE_PWR_MGMT_AUX_PWR_DET_RESET                              0x0 // 0
#define PCIE_PWR_MGMT_ADDRESS                                        0x180f0008
#define PCIE_PWR_MGMT_OFFSET                                         0x0008
// SW modifiable bits
#define PCIE_PWR_MGMT_SW_MASK                                        0x000001ff
// bits defined at reset
#define PCIE_PWR_MGMT_RSTMASK                                        0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PWR_MGMT_RESET                                          0x00000000

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
#define PCIE_PHY_REG_1_OFFSET                                        0x0000
// SW modifiable bits
#define PCIE_PHY_REG_1_SW_MASK                                       0xffffffff
// bits defined at reset
#define PCIE_PHY_REG_1_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PHY_REG_1_RESET                                         0x1021265e
#define PCIE_PHY_REG_1_RESET_1                                       0x0061060e  

// 32'h18116cc4 (PCIE_PHY_REG_2)
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_MSB                          31
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_LSB                          24
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_MASK                         0xff000000
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_GET(x)                       (((x) & PCIE_PHY_REG_2_PRBS_ERROR_COUNT_MASK) >> PCIE_PHY_REG_2_PRBS_ERROR_COUNT_LSB)
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_SET(x)                       (((x) << PCIE_PHY_REG_2_PRBS_ERROR_COUNT_LSB) & PCIE_PHY_REG_2_PRBS_ERROR_COUNT_MASK)
#define PCIE_PHY_REG_2_PRBS_ERROR_COUNT_RESET                        0x0 // 0
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_MSB                        23
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_LSB                        23
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_MASK                       0x00800000
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_GET(x)                     (((x) & PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_MASK) >> PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_LSB)
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_SET(x)                     (((x) << PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_LSB) & PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_MASK)
#define PCIE_PHY_REG_2_SDS_SDM_RXELECIDLE_RESET                      0x0 // 0
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_MSB                        22
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_LSB                        22
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_MASK                       0x00400000
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_GET(x)                     (((x) & PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_MASK) >> PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_LSB)
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_SET(x)                     (((x) << PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_LSB) & PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_MASK)
#define PCIE_PHY_REG_2_SDS_SDM_RXDETECTED_RESET                      0x0 // 0
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_MSB                             21
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_LSB                             21
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_MASK                            0x00200000
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_GET(x)                          (((x) & PCIE_PHY_REG_2_PRBS_SCRAMBLE_MASK) >> PCIE_PHY_REG_2_PRBS_SCRAMBLE_LSB)
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_SET(x)                          (((x) << PCIE_PHY_REG_2_PRBS_SCRAMBLE_LSB) & PCIE_PHY_REG_2_PRBS_SCRAMBLE_MASK)
#define PCIE_PHY_REG_2_PRBS_SCRAMBLE_RESET                           0x0 // 0
#define PCIE_PHY_REG_2_PRBS_START_MSB                                20
#define PCIE_PHY_REG_2_PRBS_START_LSB                                20
#define PCIE_PHY_REG_2_PRBS_START_MASK                               0x00100000
#define PCIE_PHY_REG_2_PRBS_START_GET(x)                             (((x) & PCIE_PHY_REG_2_PRBS_START_MASK) >> PCIE_PHY_REG_2_PRBS_START_LSB)
#define PCIE_PHY_REG_2_PRBS_START_SET(x)                             (((x) << PCIE_PHY_REG_2_PRBS_START_LSB) & PCIE_PHY_REG_2_PRBS_START_MASK)
#define PCIE_PHY_REG_2_PRBS_START_RESET                              0x0 // 0
#define PCIE_PHY_REG_2_PRBS_TS_NUM_MSB                               19
#define PCIE_PHY_REG_2_PRBS_TS_NUM_LSB                               13
#define PCIE_PHY_REG_2_PRBS_TS_NUM_MASK                              0x000fe000
#define PCIE_PHY_REG_2_PRBS_TS_NUM_GET(x)                            (((x) & PCIE_PHY_REG_2_PRBS_TS_NUM_MASK) >> PCIE_PHY_REG_2_PRBS_TS_NUM_LSB)
#define PCIE_PHY_REG_2_PRBS_TS_NUM_SET(x)                            (((x) << PCIE_PHY_REG_2_PRBS_TS_NUM_LSB) & PCIE_PHY_REG_2_PRBS_TS_NUM_MASK)
#define PCIE_PHY_REG_2_PRBS_TS_NUM_RESET                             0x40 // 64
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_MSB                           12
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_LSB                           12
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_MASK                          0x00001000
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_GET(x)                        (((x) & PCIE_PHY_REG_2_TXDETRXOVRVALUE_MASK) >> PCIE_PHY_REG_2_TXDETRXOVRVALUE_LSB)
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_SET(x)                        (((x) << PCIE_PHY_REG_2_TXDETRXOVRVALUE_LSB) & PCIE_PHY_REG_2_TXDETRXOVRVALUE_MASK)
#define PCIE_PHY_REG_2_TXDETRXOVRVALUE_RESET                         0x0 // 0
#define PCIE_PHY_REG_2_TXDETRXOVREN_MSB                              11
#define PCIE_PHY_REG_2_TXDETRXOVREN_LSB                              11
#define PCIE_PHY_REG_2_TXDETRXOVREN_MASK                             0x00000800
#define PCIE_PHY_REG_2_TXDETRXOVREN_GET(x)                           (((x) & PCIE_PHY_REG_2_TXDETRXOVREN_MASK) >> PCIE_PHY_REG_2_TXDETRXOVREN_LSB)
#define PCIE_PHY_REG_2_TXDETRXOVREN_SET(x)                           (((x) << PCIE_PHY_REG_2_TXDETRXOVREN_LSB) & PCIE_PHY_REG_2_TXDETRXOVREN_MASK)
#define PCIE_PHY_REG_2_TXDETRXOVREN_RESET                            0x0 // 0
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_MSB                            10
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_LSB                            10
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_MASK                           0x00000400
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_GET(x)                         (((x) & PCIE_PHY_REG_2_DATAOBSPRBSERR_MASK) >> PCIE_PHY_REG_2_DATAOBSPRBSERR_LSB)
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_SET(x)                         (((x) << PCIE_PHY_REG_2_DATAOBSPRBSERR_LSB) & PCIE_PHY_REG_2_DATAOBSPRBSERR_MASK)
#define PCIE_PHY_REG_2_DATAOBSPRBSERR_RESET                          0x0 // 0
#define PCIE_PHY_REG_2_CDRREADYTIMER_MSB                             9
#define PCIE_PHY_REG_2_CDRREADYTIMER_LSB                             6
#define PCIE_PHY_REG_2_CDRREADYTIMER_MASK                            0x000003c0
#define PCIE_PHY_REG_2_CDRREADYTIMER_GET(x)                          (((x) & PCIE_PHY_REG_2_CDRREADYTIMER_MASK) >> PCIE_PHY_REG_2_CDRREADYTIMER_LSB)
#define PCIE_PHY_REG_2_CDRREADYTIMER_SET(x)                          (((x) << PCIE_PHY_REG_2_CDRREADYTIMER_LSB) & PCIE_PHY_REG_2_CDRREADYTIMER_MASK)
#define PCIE_PHY_REG_2_CDRREADYTIMER_RESET                           0x7 // 7
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_MSB                        5
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_LSB                        1
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_MASK                       0x0000003e
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_GET(x)                     (((x) & PCIE_PHY_REG_2_TXDETRXTARGETDELAY_MASK) >> PCIE_PHY_REG_2_TXDETRXTARGETDELAY_LSB)
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_SET(x)                     (((x) << PCIE_PHY_REG_2_TXDETRXTARGETDELAY_LSB) & PCIE_PHY_REG_2_TXDETRXTARGETDELAY_MASK)
#define PCIE_PHY_REG_2_TXDETRXTARGETDELAY_RESET                      0xc // 12
#define PCIE_PHY_REG_2_FORCEDETECT_MSB                               0
#define PCIE_PHY_REG_2_FORCEDETECT_LSB                               0
#define PCIE_PHY_REG_2_FORCEDETECT_MASK                              0x00000001
#define PCIE_PHY_REG_2_FORCEDETECT_GET(x)                            (((x) & PCIE_PHY_REG_2_FORCEDETECT_MASK) >> PCIE_PHY_REG_2_FORCEDETECT_LSB)
#define PCIE_PHY_REG_2_FORCEDETECT_SET(x)                            (((x) << PCIE_PHY_REG_2_FORCEDETECT_LSB) & PCIE_PHY_REG_2_FORCEDETECT_MASK)
#define PCIE_PHY_REG_2_FORCEDETECT_RESET                             0x0 // 0
#define PCIE_PHY_REG_2_ADDRESS                                       0x18116cc4
#define PCIE_PHY_REG_2_OFFSET                                        0x0004
// SW modifiable bits
#define PCIE_PHY_REG_2_SW_MASK                                       0xffffffff
// bits defined at reset
#define PCIE_PHY_REG_2_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PHY_REG_2_RESET                                         0x000801d8

#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_MSB                         31
#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_LSB                         28
#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_MASK                        0xf0000000
#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_GET(x)                      (((x) & PCIE_PHY_REG_3_PRBS_COMMA_STATUS_MASK) >> PCIE_PHY_REG_3_PRBS_COMMA_STATUS_LSB)
#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_SET(x)                      (((x) << PCIE_PHY_REG_3_PRBS_COMMA_STATUS_LSB) & PCIE_PHY_REG_3_PRBS_COMMA_STATUS_MASK)
#define PCIE_PHY_REG_3_PRBS_COMMA_STATUS_RESET                       0x0 // 0
#define PCIE_PHY_REG_3_SPARE_MSB                                     27
#define PCIE_PHY_REG_3_SPARE_LSB                                     11
#define PCIE_PHY_REG_3_SPARE_MASK                                    0x0ffff800
#define PCIE_PHY_REG_3_SPARE_GET(x)                                  (((x) & PCIE_PHY_REG_3_SPARE_MASK) >> PCIE_PHY_REG_3_SPARE_LSB)
#define PCIE_PHY_REG_3_SPARE_SET(x)                                  (((x) << PCIE_PHY_REG_3_SPARE_LSB) & PCIE_PHY_REG_3_SPARE_MASK)
#define PCIE_PHY_REG_3_SPARE_RESET                                   0xa0b // 2571
#define PCIE_PHY_REG_3_SEL_CLK100_MSB                                10
#define PCIE_PHY_REG_3_SEL_CLK100_LSB                                10
#define PCIE_PHY_REG_3_SEL_CLK100_MASK                               0x00000400
#define PCIE_PHY_REG_3_SEL_CLK100_GET(x)                             (((x) & PCIE_PHY_REG_3_SEL_CLK100_MASK) >> PCIE_PHY_REG_3_SEL_CLK100_LSB)
#define PCIE_PHY_REG_3_SEL_CLK100_SET(x)                             (((x) << PCIE_PHY_REG_3_SEL_CLK100_LSB) & PCIE_PHY_REG_3_SEL_CLK100_MASK)
#define PCIE_PHY_REG_3_SEL_CLK100_RESET                              0x0 // 0
#define PCIE_PHY_REG_3_EN_BEACONGEN_MSB                              9
#define PCIE_PHY_REG_3_EN_BEACONGEN_LSB                              9
#define PCIE_PHY_REG_3_EN_BEACONGEN_MASK                             0x00000200
#define PCIE_PHY_REG_3_EN_BEACONGEN_GET(x)                           (((x) & PCIE_PHY_REG_3_EN_BEACONGEN_MASK) >> PCIE_PHY_REG_3_EN_BEACONGEN_LSB)
#define PCIE_PHY_REG_3_EN_BEACONGEN_SET(x)                           (((x) << PCIE_PHY_REG_3_EN_BEACONGEN_LSB) & PCIE_PHY_REG_3_EN_BEACONGEN_MASK)
#define PCIE_PHY_REG_3_EN_BEACONGEN_RESET                            0x0 // 0
#define PCIE_PHY_REG_3_TXELECIDLE_MSB                                8
#define PCIE_PHY_REG_3_TXELECIDLE_LSB                                8
#define PCIE_PHY_REG_3_TXELECIDLE_MASK                               0x00000100
#define PCIE_PHY_REG_3_TXELECIDLE_GET(x)                             (((x) & PCIE_PHY_REG_3_TXELECIDLE_MASK) >> PCIE_PHY_REG_3_TXELECIDLE_LSB)
#define PCIE_PHY_REG_3_TXELECIDLE_SET(x)                             (((x) << PCIE_PHY_REG_3_TXELECIDLE_LSB) & PCIE_PHY_REG_3_TXELECIDLE_MASK)
#define PCIE_PHY_REG_3_TXELECIDLE_RESET                              0x0 // 0
#define PCIE_PHY_REG_3_SEL_CLK_MSB                                   7
#define PCIE_PHY_REG_3_SEL_CLK_LSB                                   6
#define PCIE_PHY_REG_3_SEL_CLK_MASK                                  0x000000c0
#define PCIE_PHY_REG_3_SEL_CLK_GET(x)                                (((x) & PCIE_PHY_REG_3_SEL_CLK_MASK) >> PCIE_PHY_REG_3_SEL_CLK_LSB)
#define PCIE_PHY_REG_3_SEL_CLK_SET(x)                                (((x) << PCIE_PHY_REG_3_SEL_CLK_LSB) & PCIE_PHY_REG_3_SEL_CLK_MASK)
#define PCIE_PHY_REG_3_SEL_CLK_RESET                                 0x0 // 0
#define PCIE_PHY_REG_3_RX_DET_REQ_MSB                                5
#define PCIE_PHY_REG_3_RX_DET_REQ_LSB                                5
#define PCIE_PHY_REG_3_RX_DET_REQ_MASK                               0x00000020
#define PCIE_PHY_REG_3_RX_DET_REQ_GET(x)                             (((x) & PCIE_PHY_REG_3_RX_DET_REQ_MASK) >> PCIE_PHY_REG_3_RX_DET_REQ_LSB)
#define PCIE_PHY_REG_3_RX_DET_REQ_SET(x)                             (((x) << PCIE_PHY_REG_3_RX_DET_REQ_LSB) & PCIE_PHY_REG_3_RX_DET_REQ_MASK)
#define PCIE_PHY_REG_3_RX_DET_REQ_RESET                              0x0 // 0
#define PCIE_PHY_REG_3_MODE_OCLK_IN_MSB                              4
#define PCIE_PHY_REG_3_MODE_OCLK_IN_LSB                              4
#define PCIE_PHY_REG_3_MODE_OCLK_IN_MASK                             0x00000010
#define PCIE_PHY_REG_3_MODE_OCLK_IN_GET(x)                           (((x) & PCIE_PHY_REG_3_MODE_OCLK_IN_MASK) >> PCIE_PHY_REG_3_MODE_OCLK_IN_LSB)
#define PCIE_PHY_REG_3_MODE_OCLK_IN_SET(x)                           (((x) << PCIE_PHY_REG_3_MODE_OCLK_IN_LSB) & PCIE_PHY_REG_3_MODE_OCLK_IN_MASK)
#define PCIE_PHY_REG_3_MODE_OCLK_IN_RESET                            0x0 // 0
#define PCIE_PHY_REG_3_EN_PLL_MSB                                    3
#define PCIE_PHY_REG_3_EN_PLL_LSB                                    3
#define PCIE_PHY_REG_3_EN_PLL_MASK                                   0x00000008
#define PCIE_PHY_REG_3_EN_PLL_GET(x)                                 (((x) & PCIE_PHY_REG_3_EN_PLL_MASK) >> PCIE_PHY_REG_3_EN_PLL_LSB)
#define PCIE_PHY_REG_3_EN_PLL_SET(x)                                 (((x) << PCIE_PHY_REG_3_EN_PLL_LSB) & PCIE_PHY_REG_3_EN_PLL_MASK)
#define PCIE_PHY_REG_3_EN_PLL_RESET                                  0x1 // 1
#define PCIE_PHY_REG_3_EN_LCKDT_MSB                                  2
#define PCIE_PHY_REG_3_EN_LCKDT_LSB                                  2
#define PCIE_PHY_REG_3_EN_LCKDT_MASK                                 0x00000004
#define PCIE_PHY_REG_3_EN_LCKDT_GET(x)                               (((x) & PCIE_PHY_REG_3_EN_LCKDT_MASK) >> PCIE_PHY_REG_3_EN_LCKDT_LSB)
#define PCIE_PHY_REG_3_EN_LCKDT_SET(x)                               (((x) << PCIE_PHY_REG_3_EN_LCKDT_LSB) & PCIE_PHY_REG_3_EN_LCKDT_MASK)
#define PCIE_PHY_REG_3_EN_LCKDT_RESET                                0x1 // 1
#define PCIE_PHY_REG_3_EN_BUFS_RX_MSB                                1
#define PCIE_PHY_REG_3_EN_BUFS_RX_LSB                                1
#define PCIE_PHY_REG_3_EN_BUFS_RX_MASK                               0x00000002
#define PCIE_PHY_REG_3_EN_BUFS_RX_GET(x)                             (((x) & PCIE_PHY_REG_3_EN_BUFS_RX_MASK) >> PCIE_PHY_REG_3_EN_BUFS_RX_LSB)
#define PCIE_PHY_REG_3_EN_BUFS_RX_SET(x)                             (((x) << PCIE_PHY_REG_3_EN_BUFS_RX_LSB) & PCIE_PHY_REG_3_EN_BUFS_RX_MASK)
#define PCIE_PHY_REG_3_EN_BUFS_RX_RESET                              0x0 // 0
#define PCIE_PHY_REG_3_EN_MSB                                        0
#define PCIE_PHY_REG_3_EN_LSB                                        0
#define PCIE_PHY_REG_3_EN_MASK                                       0x00000001
#define PCIE_PHY_REG_3_EN_GET(x)                                     (((x) & PCIE_PHY_REG_3_EN_MASK) >> PCIE_PHY_REG_3_EN_LSB)
#define PCIE_PHY_REG_3_EN_SET(x)                                     (((x) << PCIE_PHY_REG_3_EN_LSB) & PCIE_PHY_REG_3_EN_MASK)
#define PCIE_PHY_REG_3_EN_RESET                                      0x0 // 0
#define PCIE_PHY_REG_3_ADDRESS                                       0x18116cc8
#define PCIE_PHY_REG_3_OFFSET                                        0x0008
// SW modifiable bits
#define PCIE_PHY_REG_3_SW_MASK                                       0xffffffff
// bits defined at reset
#define PCIE_PHY_REG_3_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PHY_REG_3_RESET                                         0x0050580c
#define PCIE_PHY_REG_3_RESET_1 		               		     0x00505900

#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_MSB                           31
#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_LSB                           11
#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_MASK                          0xfffff800
#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_GET(x)                        (((x) & PCIE_PHY_REG_4_PRBS_ERROR_RATE_MASK) >> PCIE_PHY_REG_4_PRBS_ERROR_RATE_LSB)
#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_SET(x)                        (((x) << PCIE_PHY_REG_4_PRBS_ERROR_RATE_LSB) & PCIE_PHY_REG_4_PRBS_ERROR_RATE_MASK)
#define PCIE_PHY_REG_4_PRBS_ERROR_RATE_RESET                         0xa000 // 40960
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_MSB                      10
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_LSB                      1
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_MASK                     0x000007fe
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_GET(x)                   (((x) & PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_MASK) >> PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_LSB)
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_SET(x)                   (((x) << PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_LSB) & PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_MASK)
#define PCIE_PHY_REG_4_PRBS_TOTAL_NUMOF_ERR_RESET                    0x0 // 0
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_MSB                        0
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_LSB                        0
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_MASK                       0x00000001
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_GET(x)                     (((x) & PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_MASK) >> PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_LSB)
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_SET(x)                     (((x) << PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_LSB) & PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_MASK)
#define PCIE_PHY_REG_4_PRBS_TRIGGER_ERROR_RESET                      0x0 // 0
#define PCIE_PHY_REG_4_ADDRESS                                       0x18116ccc
#define PCIE_PHY_REG_4_OFFSET                                        0x000c
// SW modifiable bits
#define PCIE_PHY_REG_4_SW_MASK                                       0xffffffff
// bits defined at reset
#define PCIE_PHY_REG_4_RSTMASK                                       0xffffffff
// reset value (ignore bits undefined at reset)
#define PCIE_PHY_REG_4_RESET                                         0x05000000

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
#define XTAL_XTAL_BIAS2X_RESET                                       0x0 // 0
#define XTAL_XTAL_LBIAS2X_MSB                                        10
#define XTAL_XTAL_LBIAS2X_LSB                                        10
#define XTAL_XTAL_LBIAS2X_MASK                                       0x00000400
#define XTAL_XTAL_LBIAS2X_GET(x)                                     (((x) & XTAL_XTAL_LBIAS2X_MASK) >> XTAL_XTAL_LBIAS2X_LSB)
#define XTAL_XTAL_LBIAS2X_SET(x)                                     (((x) << XTAL_XTAL_LBIAS2X_LSB) & XTAL_XTAL_LBIAS2X_MASK)
#define XTAL_XTAL_LBIAS2X_RESET                                      0x0 // 0
#define XTAL_XTAL_SELVREG_MSB                                        9
#define XTAL_XTAL_SELVREG_LSB                                        9
#define XTAL_XTAL_SELVREG_MASK                                       0x00000200
#define XTAL_XTAL_SELVREG_GET(x)                                     (((x) & XTAL_XTAL_SELVREG_MASK) >> XTAL_XTAL_SELVREG_LSB)
#define XTAL_XTAL_SELVREG_SET(x)                                     (((x) << XTAL_XTAL_SELVREG_LSB) & XTAL_XTAL_SELVREG_MASK)
#define XTAL_XTAL_SELVREG_RESET                                      0x0 // 0
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
#define XTAL_LOCAL_EXT_CLK_OUT_EN_MSB                                4
#define XTAL_LOCAL_EXT_CLK_OUT_EN_LSB                                4
#define XTAL_LOCAL_EXT_CLK_OUT_EN_MASK                               0x00000010
#define XTAL_LOCAL_EXT_CLK_OUT_EN_GET(x)                             (((x) & XTAL_LOCAL_EXT_CLK_OUT_EN_MASK) >> XTAL_LOCAL_EXT_CLK_OUT_EN_LSB)
#define XTAL_LOCAL_EXT_CLK_OUT_EN_SET(x)                             (((x) << XTAL_LOCAL_EXT_CLK_OUT_EN_LSB) & XTAL_LOCAL_EXT_CLK_OUT_EN_MASK)
#define XTAL_LOCAL_EXT_CLK_OUT_EN_RESET                              0x0 // 0
#define XTAL_EXT_CLK_OUT_EN_MSB                                      3
#define XTAL_EXT_CLK_OUT_EN_LSB                                      3
#define XTAL_EXT_CLK_OUT_EN_MASK                                     0x00000008
#define XTAL_EXT_CLK_OUT_EN_GET(x)                                   (((x) & XTAL_EXT_CLK_OUT_EN_MASK) >> XTAL_EXT_CLK_OUT_EN_LSB)
#define XTAL_EXT_CLK_OUT_EN_SET(x)                                   (((x) << XTAL_EXT_CLK_OUT_EN_LSB) & XTAL_EXT_CLK_OUT_EN_MASK)
#define XTAL_EXT_CLK_OUT_EN_RESET                                    0x0 // 0
#define XTAL_XTAL_SVREG_MSB                                          2
#define XTAL_XTAL_SVREG_LSB                                          2
#define XTAL_XTAL_SVREG_MASK                                         0x00000004
#define XTAL_XTAL_SVREG_GET(x)                                       (((x) & XTAL_XTAL_SVREG_MASK) >> XTAL_XTAL_SVREG_LSB)
#define XTAL_XTAL_SVREG_SET(x)                                       (((x) << XTAL_XTAL_SVREG_LSB) & XTAL_XTAL_SVREG_MASK)
#define XTAL_XTAL_SVREG_RESET                                        0x0 // 0
#define XTAL_RBK_UDSEL_MSB                                           1
#define XTAL_RBK_UDSEL_LSB                                           1
#define XTAL_RBK_UDSEL_MASK                                          0x00000002
#define XTAL_RBK_UDSEL_GET(x)                                        (((x) & XTAL_RBK_UDSEL_MASK) >> XTAL_RBK_UDSEL_LSB)
#define XTAL_RBK_UDSEL_SET(x)                                        (((x) << XTAL_RBK_UDSEL_LSB) & XTAL_RBK_UDSEL_MASK)
#define XTAL_RBK_UDSEL_RESET                                         0x0 // 0
#define XTAL_SPARE_MSB                                               0
#define XTAL_SPARE_LSB                                               0
#define XTAL_SPARE_MASK                                              0x00000001
#define XTAL_SPARE_GET(x)                                            (((x) & XTAL_SPARE_MASK) >> XTAL_SPARE_LSB)
#define XTAL_SPARE_SET(x)                                            (((x) << XTAL_SPARE_LSB) & XTAL_SPARE_MASK)
#define XTAL_SPARE_RESET                                             0x0 // 0
#define XTAL_ADDRESS                                                 0x181162c0

#define XTAL2_TDC_COUNT_MSB                                          31
#define XTAL2_TDC_COUNT_LSB                                          26
#define XTAL2_TDC_COUNT_MASK                                         0xfc000000
#define XTAL2_TDC_COUNT_GET(x)                                       (((x) & XTAL2_TDC_COUNT_MASK) >> XTAL2_TDC_COUNT_LSB)
#define XTAL2_TDC_COUNT_SET(x)                                       (((x) << XTAL2_TDC_COUNT_LSB) & XTAL2_TDC_COUNT_MASK)
#define XTAL2_TDC_COUNT_RESET                                        0x0 // 0
#define XTAL2_TDC_PH_COUNT_MSB                                       25
#define XTAL2_TDC_PH_COUNT_LSB                                       21
#define XTAL2_TDC_PH_COUNT_MASK                                      0x03e00000
#define XTAL2_TDC_PH_COUNT_GET(x)                                    (((x) & XTAL2_TDC_PH_COUNT_MASK) >> XTAL2_TDC_PH_COUNT_LSB)
#define XTAL2_TDC_PH_COUNT_SET(x)                                    (((x) << XTAL2_TDC_PH_COUNT_LSB) & XTAL2_TDC_PH_COUNT_MASK)
#define XTAL2_TDC_PH_COUNT_RESET                                     0x0 // 0
#define XTAL2_DUTY_UP_MSB                                            20
#define XTAL2_DUTY_UP_LSB                                            16
#define XTAL2_DUTY_UP_MASK                                           0x001f0000
#define XTAL2_DUTY_UP_GET(x)                                         (((x) & XTAL2_DUTY_UP_MASK) >> XTAL2_DUTY_UP_LSB)
#define XTAL2_DUTY_UP_SET(x)                                         (((x) << XTAL2_DUTY_UP_LSB) & XTAL2_DUTY_UP_MASK)
#define XTAL2_DUTY_UP_RESET                                          0x0 // 0
#define XTAL2_DUTY_DN_MSB                                            15
#define XTAL2_DUTY_DN_LSB                                            11
#define XTAL2_DUTY_DN_MASK                                           0x0000f800
#define XTAL2_DUTY_DN_GET(x)                                         (((x) & XTAL2_DUTY_DN_MASK) >> XTAL2_DUTY_DN_LSB)
#define XTAL2_DUTY_DN_SET(x)                                         (((x) << XTAL2_DUTY_DN_LSB) & XTAL2_DUTY_DN_MASK)
#define XTAL2_DUTY_DN_RESET                                          0x0 // 0
#define XTAL2_DCA_BYPASS_MSB                                         10
#define XTAL2_DCA_BYPASS_LSB                                         10
#define XTAL2_DCA_BYPASS_MASK                                        0x00000400
#define XTAL2_DCA_BYPASS_GET(x)                                      (((x) & XTAL2_DCA_BYPASS_MASK) >> XTAL2_DCA_BYPASS_LSB)
#define XTAL2_DCA_BYPASS_SET(x)                                      (((x) << XTAL2_DCA_BYPASS_LSB) & XTAL2_DCA_BYPASS_MASK)
#define XTAL2_DCA_BYPASS_RESET                                       0x1 // 1
#define XTAL2_DCA_SWCAL_MSB                                          9
#define XTAL2_DCA_SWCAL_LSB                                          9
#define XTAL2_DCA_SWCAL_MASK                                         0x00000200
#define XTAL2_DCA_SWCAL_GET(x)                                       (((x) & XTAL2_DCA_SWCAL_MASK) >> XTAL2_DCA_SWCAL_LSB)
#define XTAL2_DCA_SWCAL_SET(x)                                       (((x) << XTAL2_DCA_SWCAL_LSB) & XTAL2_DCA_SWCAL_MASK)
#define XTAL2_DCA_SWCAL_RESET                                        0x0 // 0
#define XTAL2_FSM_UD_HOLD_MSB                                        8
#define XTAL2_FSM_UD_HOLD_LSB                                        8
#define XTAL2_FSM_UD_HOLD_MASK                                       0x00000100
#define XTAL2_FSM_UD_HOLD_GET(x)                                     (((x) & XTAL2_FSM_UD_HOLD_MASK) >> XTAL2_FSM_UD_HOLD_LSB)
#define XTAL2_FSM_UD_HOLD_SET(x)                                     (((x) << XTAL2_FSM_UD_HOLD_LSB) & XTAL2_FSM_UD_HOLD_MASK)
#define XTAL2_FSM_UD_HOLD_RESET                                      0x0 // 0
#define XTAL2_FSM_START_L_MSB                                        7
#define XTAL2_FSM_START_L_LSB                                        7
#define XTAL2_FSM_START_L_MASK                                       0x00000080
#define XTAL2_FSM_START_L_GET(x)                                     (((x) & XTAL2_FSM_START_L_MASK) >> XTAL2_FSM_START_L_LSB)
#define XTAL2_FSM_START_L_SET(x)                                     (((x) << XTAL2_FSM_START_L_LSB) & XTAL2_FSM_START_L_MASK)
#define XTAL2_FSM_START_L_RESET                                      0x1 // 1
#define XTAL2_FSM_DN_READBACK_MSB                                    6
#define XTAL2_FSM_DN_READBACK_LSB                                    2
#define XTAL2_FSM_DN_READBACK_MASK                                   0x0000007c
#define XTAL2_FSM_DN_READBACK_GET(x)                                 (((x) & XTAL2_FSM_DN_READBACK_MASK) >> XTAL2_FSM_DN_READBACK_LSB)
#define XTAL2_FSM_DN_READBACK_SET(x)                                 (((x) << XTAL2_FSM_DN_READBACK_LSB) & XTAL2_FSM_DN_READBACK_MASK)
#define XTAL2_FSM_DN_READBACK_RESET                                  0x0 // 0
#define XTAL2_TDC_SAT_FLAG_MSB                                       1
#define XTAL2_TDC_SAT_FLAG_LSB                                       1
#define XTAL2_TDC_SAT_FLAG_MASK                                      0x00000002
#define XTAL2_TDC_SAT_FLAG_GET(x)                                    (((x) & XTAL2_TDC_SAT_FLAG_MASK) >> XTAL2_TDC_SAT_FLAG_LSB)
#define XTAL2_TDC_SAT_FLAG_SET(x)                                    (((x) << XTAL2_TDC_SAT_FLAG_LSB) & XTAL2_TDC_SAT_FLAG_MASK)
#define XTAL2_TDC_SAT_FLAG_RESET                                     0x0 // 0
#define XTAL2_FSM_READY_MSB                                          0
#define XTAL2_FSM_READY_LSB                                          0
#define XTAL2_FSM_READY_MASK                                         0x00000001
#define XTAL2_FSM_READY_GET(x)                                       (((x) & XTAL2_FSM_READY_MASK) >> XTAL2_FSM_READY_LSB)
#define XTAL2_FSM_READY_SET(x)                                       (((x) << XTAL2_FSM_READY_LSB) & XTAL2_FSM_READY_MASK)
#define XTAL2_FSM_READY_RESET                                        0x0 // 0
#define XTAL2_ADDRESS                                                0x181162c4

#define XTAL3_FSM_UP_READBACK_MSB                                    31
#define XTAL3_FSM_UP_READBACK_LSB                                    27
#define XTAL3_FSM_UP_READBACK_MASK                                   0xf8000000
#define XTAL3_FSM_UP_READBACK_GET(x)                                 (((x) & XTAL3_FSM_UP_READBACK_MASK) >> XTAL3_FSM_UP_READBACK_LSB)
#define XTAL3_FSM_UP_READBACK_SET(x)                                 (((x) << XTAL3_FSM_UP_READBACK_LSB) & XTAL3_FSM_UP_READBACK_MASK)
#define XTAL3_FSM_UP_READBACK_RESET                                  0x0 // 0
#define XTAL3_EVAL_LENGTH_MSB                                        26
#define XTAL3_EVAL_LENGTH_LSB                                        16
#define XTAL3_EVAL_LENGTH_MASK                                       0x07ff0000
#define XTAL3_EVAL_LENGTH_GET(x)                                     (((x) & XTAL3_EVAL_LENGTH_MASK) >> XTAL3_EVAL_LENGTH_LSB)
#define XTAL3_EVAL_LENGTH_SET(x)                                     (((x) << XTAL3_EVAL_LENGTH_LSB) & XTAL3_EVAL_LENGTH_MASK)
#define XTAL3_EVAL_LENGTH_RESET                                      0x400 // 1024
#define XTAL3_TDC_ERROR_FLAG_MSB                                     15
#define XTAL3_TDC_ERROR_FLAG_LSB                                     15
#define XTAL3_TDC_ERROR_FLAG_MASK                                    0x00008000
#define XTAL3_TDC_ERROR_FLAG_GET(x)                                  (((x) & XTAL3_TDC_ERROR_FLAG_MASK) >> XTAL3_TDC_ERROR_FLAG_LSB)
#define XTAL3_TDC_ERROR_FLAG_SET(x)                                  (((x) << XTAL3_TDC_ERROR_FLAG_LSB) & XTAL3_TDC_ERROR_FLAG_MASK)
#define XTAL3_TDC_ERROR_FLAG_RESET                                   0x0 // 0
#define XTAL3_HARMONIC_NUMBER_MSB                                    14
#define XTAL3_HARMONIC_NUMBER_LSB                                    2
#define XTAL3_HARMONIC_NUMBER_MASK                                   0x00007ffc
#define XTAL3_HARMONIC_NUMBER_GET(x)                                 (((x) & XTAL3_HARMONIC_NUMBER_MASK) >> XTAL3_HARMONIC_NUMBER_LSB)
#define XTAL3_HARMONIC_NUMBER_SET(x)                                 (((x) << XTAL3_HARMONIC_NUMBER_LSB) & XTAL3_HARMONIC_NUMBER_MASK)
#define XTAL3_HARMONIC_NUMBER_RESET                                  0x51 // 81
#define XTAL3_SPARE_MSB                                              1
#define XTAL3_SPARE_LSB                                              0
#define XTAL3_SPARE_MASK                                             0x00000003
#define XTAL3_SPARE_GET(x)                                           (((x) & XTAL3_SPARE_MASK) >> XTAL3_SPARE_LSB)
#define XTAL3_SPARE_SET(x)                                           (((x) << XTAL3_SPARE_LSB) & XTAL3_SPARE_MASK)
#define XTAL3_SPARE_RESET                                            0x0 // 0
#define XTAL3_ADDRESS                                                0x181162c8

#define RST_REVISION_ID_ADDRESS                                      0x18060090
#define is_drqfn()	(!(ath_reg_rd(RST_REVISION_ID_ADDRESS) & 0x1000))

#define RST_BOOTSTRAP_RES4_MSB                                       15
#define RST_BOOTSTRAP_RES4_LSB                                       13
#define RST_BOOTSTRAP_RES4_MASK                                      0x0000e000
#define RST_BOOTSTRAP_RES4_GET(x)                                    (((x) & RST_BOOTSTRAP_RES4_MASK) >> RST_BOOTSTRAP_RES4_LSB)
#define RST_BOOTSTRAP_RES4_SET(x)                                    (((x) << RST_BOOTSTRAP_RES4_LSB) & RST_BOOTSTRAP_RES4_MASK)
#define RST_BOOTSTRAP_RES4_RESET                                     0x0 // 0
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
#define RST_BOOTSTRAP_TESTROM_ENABLE_MSB                             10
#define RST_BOOTSTRAP_TESTROM_ENABLE_LSB                             10
#define RST_BOOTSTRAP_TESTROM_ENABLE_MASK                            0x00000400
#define RST_BOOTSTRAP_TESTROM_ENABLE_GET(x)                          (((x) & RST_BOOTSTRAP_TESTROM_ENABLE_MASK) >> RST_BOOTSTRAP_TESTROM_ENABLE_LSB)
#define RST_BOOTSTRAP_TESTROM_ENABLE_SET(x)                          (((x) << RST_BOOTSTRAP_TESTROM_ENABLE_LSB) & RST_BOOTSTRAP_TESTROM_ENABLE_MASK)
#define RST_BOOTSTRAP_TESTROM_ENABLE_RESET                           0x0 // 0
#define RST_BOOTSTRAP_RES3_MSB                                       9
#define RST_BOOTSTRAP_RES3_LSB                                       9
#define RST_BOOTSTRAP_RES3_MASK                                      0x00000200
#define RST_BOOTSTRAP_RES3_GET(x)                                    (((x) & RST_BOOTSTRAP_RES3_MASK) >> RST_BOOTSTRAP_RES3_LSB)
#define RST_BOOTSTRAP_RES3_SET(x)                                    (((x) << RST_BOOTSTRAP_RES3_LSB) & RST_BOOTSTRAP_RES3_MASK)
#define RST_BOOTSTRAP_RES3_RESET                                     0x0 // 0
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
#define RST_BOOTSTRAP_RES2_MSB                                       6
#define RST_BOOTSTRAP_RES2_LSB                                       6
#define RST_BOOTSTRAP_RES2_MASK                                      0x00000040
#define RST_BOOTSTRAP_RES2_GET(x)                                    (((x) & RST_BOOTSTRAP_RES2_MASK) >> RST_BOOTSTRAP_RES2_LSB)
#define RST_BOOTSTRAP_RES2_SET(x)                                    (((x) << RST_BOOTSTRAP_RES2_LSB) & RST_BOOTSTRAP_RES2_MASK)
#define RST_BOOTSTRAP_RES2_RESET                                     0x0 // 0
#define RST_BOOTSTRAP_EJTAG_MODE_MSB                                 5
#define RST_BOOTSTRAP_EJTAG_MODE_LSB                                 5
#define RST_BOOTSTRAP_EJTAG_MODE_MASK                                0x00000020
#define RST_BOOTSTRAP_EJTAG_MODE_GET(x)                              (((x) & RST_BOOTSTRAP_EJTAG_MODE_MASK) >> RST_BOOTSTRAP_EJTAG_MODE_LSB)
#define RST_BOOTSTRAP_EJTAG_MODE_SET(x)                              (((x) << RST_BOOTSTRAP_EJTAG_MODE_LSB) & RST_BOOTSTRAP_EJTAG_MODE_MASK)
#define RST_BOOTSTRAP_EJTAG_MODE_RESET                               0x0 // 0
#define RST_BOOTSTRAP_REF_CLK_MSB                                    4
#define RST_BOOTSTRAP_REF_CLK_LSB                                    4
#define RST_BOOTSTRAP_REF_CLK_MASK                                   0x00000010
#define RST_BOOTSTRAP_REF_CLK_GET(x)                                 (((x) & RST_BOOTSTRAP_REF_CLK_MASK) >> RST_BOOTSTRAP_REF_CLK_LSB)
#define RST_BOOTSTRAP_REF_CLK_SET(x)                                 (((x) << RST_BOOTSTRAP_REF_CLK_LSB) & RST_BOOTSTRAP_REF_CLK_MASK)
#define RST_BOOTSTRAP_REF_CLK_RESET                                  0x0 // 0
#define RST_BOOTSTRAP_RES1_MSB                                       3
#define RST_BOOTSTRAP_RES1_LSB                                       3
#define RST_BOOTSTRAP_RES1_MASK                                      0x00000008
#define RST_BOOTSTRAP_RES1_GET(x)                                    (((x) & RST_BOOTSTRAP_RES1_MASK) >> RST_BOOTSTRAP_RES1_LSB)
#define RST_BOOTSTRAP_RES1_SET(x)                                    (((x) << RST_BOOTSTRAP_RES1_LSB) & RST_BOOTSTRAP_RES1_MASK)
#define RST_BOOTSTRAP_RES1_RESET                                     0x0 // 0
#define RST_BOOTSTRAP_RES0_MSB                                       2
#define RST_BOOTSTRAP_RES0_LSB                                       2
#define RST_BOOTSTRAP_RES0_MASK                                      0x00000004
#define RST_BOOTSTRAP_RES0_GET(x)                                    (((x) & RST_BOOTSTRAP_RES0_MASK) >> RST_BOOTSTRAP_RES0_LSB)
#define RST_BOOTSTRAP_RES0_SET(x)                                    (((x) << RST_BOOTSTRAP_RES0_LSB) & RST_BOOTSTRAP_RES0_MASK)
#define RST_BOOTSTRAP_RES0_RESET                                     0x0 // 0
#define RST_BOOTSTRAP_SDRAM_SELECT_MSB                               1
#define RST_BOOTSTRAP_SDRAM_SELECT_LSB                               1
#define RST_BOOTSTRAP_SDRAM_SELECT_MASK                              0x00000002
#define RST_BOOTSTRAP_SDRAM_SELECT_GET(x)                            (((x) & RST_BOOTSTRAP_SDRAM_SELECT_MASK) >> RST_BOOTSTRAP_SDRAM_SELECT_LSB)
#define RST_BOOTSTRAP_SDRAM_SELECT_SET(x)                            (((x) << RST_BOOTSTRAP_SDRAM_SELECT_LSB) & RST_BOOTSTRAP_SDRAM_SELECT_MASK)
#define RST_BOOTSTRAP_SDRAM_SELECT_RESET                             0x0 // 0
#define RST_BOOTSTRAP_DDR_SELECT_MSB                                 0
#define RST_BOOTSTRAP_DDR_SELECT_LSB                                 0
#define RST_BOOTSTRAP_DDR_SELECT_MASK                                0x00000001
#define RST_BOOTSTRAP_DDR_SELECT_GET(x)                              (((x) & RST_BOOTSTRAP_DDR_SELECT_MASK) >> RST_BOOTSTRAP_DDR_SELECT_LSB)
#define RST_BOOTSTRAP_DDR_SELECT_SET(x)                              (((x) << RST_BOOTSTRAP_DDR_SELECT_LSB) & RST_BOOTSTRAP_DDR_SELECT_MASK)
#define RST_BOOTSTRAP_DDR_SELECT_RESET                               0x0 // 0
#define RST_BOOTSTRAP_ADDRESS                                        0x180600b0

#define RST_CLKGAT_EN_SPARE_MSB                                      31
#define RST_CLKGAT_EN_SPARE_LSB                                      12
#define RST_CLKGAT_EN_SPARE_MASK                                     0xfffff000
#define RST_CLKGAT_EN_SPARE_GET(x)                                   (((x) & RST_CLKGAT_EN_SPARE_MASK) >> RST_CLKGAT_EN_SPARE_LSB)
#define RST_CLKGAT_EN_SPARE_SET(x)                                   (((x) << RST_CLKGAT_EN_SPARE_LSB) & RST_CLKGAT_EN_SPARE_MASK)
#define RST_CLKGAT_EN_SPARE_RESET                                    0x0 // 0
#define RST_CLKGAT_EN_WMAC_MSB                                       9
#define RST_CLKGAT_EN_WMAC_LSB                                       9
#define RST_CLKGAT_EN_WMAC_MASK                                      0x00000200
#define RST_CLKGAT_EN_WMAC_GET(x)                                    (((x) & RST_CLKGAT_EN_WMAC_MASK) >> RST_CLKGAT_EN_WMAC_LSB)
#define RST_CLKGAT_EN_WMAC_SET(x)                                    (((x) << RST_CLKGAT_EN_WMAC_LSB) & RST_CLKGAT_EN_WMAC_MASK)
#define RST_CLKGAT_EN_WMAC_RESET                                     0x1 // 1
#define RST_CLKGAT_EN_USB1_MSB                                       7
#define RST_CLKGAT_EN_USB1_LSB                                       7
#define RST_CLKGAT_EN_USB1_MASK                                      0x00000080
#define RST_CLKGAT_EN_USB1_GET(x)                                    (((x) & RST_CLKGAT_EN_USB1_MASK) >> RST_CLKGAT_EN_USB1_LSB)
#define RST_CLKGAT_EN_USB1_SET(x)                                    (((x) << RST_CLKGAT_EN_USB1_LSB) & RST_CLKGAT_EN_USB1_MASK)
#define RST_CLKGAT_EN_USB1_RESET                                     0x1 // 1
#define RST_CLKGAT_EN_GE1_MSB                                        6
#define RST_CLKGAT_EN_GE1_LSB                                        6
#define RST_CLKGAT_EN_GE1_MASK                                       0x00000040
#define RST_CLKGAT_EN_GE1_GET(x)                                     (((x) & RST_CLKGAT_EN_GE1_MASK) >> RST_CLKGAT_EN_GE1_LSB)
#define RST_CLKGAT_EN_GE1_SET(x)                                     (((x) << RST_CLKGAT_EN_GE1_LSB) & RST_CLKGAT_EN_GE1_MASK)
#define RST_CLKGAT_EN_GE1_RESET                                      0x1 // 1
#define RST_CLKGAT_EN_GE0_MSB                                        5
#define RST_CLKGAT_EN_GE0_LSB                                        5
#define RST_CLKGAT_EN_GE0_MASK                                       0x00000020
#define RST_CLKGAT_EN_GE0_GET(x)                                     (((x) & RST_CLKGAT_EN_GE0_MASK) >> RST_CLKGAT_EN_GE0_LSB)
#define RST_CLKGAT_EN_GE0_SET(x)                                     (((x) << RST_CLKGAT_EN_GE0_LSB) & RST_CLKGAT_EN_GE0_MASK)
#define RST_CLKGAT_EN_GE0_RESET                                      0x1 // 1
#define RST_CLKGAT_EN_PCIE_RC_MSB                                    1
#define RST_CLKGAT_EN_PCIE_RC_LSB                                    1
#define RST_CLKGAT_EN_PCIE_RC_MASK                                   0x00000002
#define RST_CLKGAT_EN_PCIE_RC_GET(x)                                 (((x) & RST_CLKGAT_EN_PCIE_RC_MASK) >> RST_CLKGAT_EN_PCIE_RC_LSB)
#define RST_CLKGAT_EN_PCIE_RC_SET(x)                                 (((x) << RST_CLKGAT_EN_PCIE_RC_LSB) & RST_CLKGAT_EN_PCIE_RC_MASK)
#define RST_CLKGAT_EN_PCIE_RC_RESET                                  0x1 // 1
#define RST_CLKGAT_EN_ADDRESS                                        0x180600c0
#define RST_CLKGAT_EN_OFFSET                                         0x00c0
// SW modifiable bits
#define RST_CLKGAT_EN_SW_MASK                                        0xfffff2e2
// bits defined at reset
#define RST_CLKGAT_EN_RSTMASK                                        0xffffffff
// reset value (ignore bits undefined at reset)
#define RST_CLKGAT_EN_RESET                                          0x000002e2

#define GPIO_OE_ADDRESS                                              0x18040000
#define GPIO_IN_ADDRESS                                              0x18040004/*  by huangwenzhong, 03Sep13 */
#define GPIO_OUT_ADDRESS                                             0x18040008
#define GPIO_SPARE_ADDRESS                                           0x18040070


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
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_7_RESET                       0xc // 12
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MSB                         23
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB                         16
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK                        0x00ff0000
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_GET(x)                      (((x) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK) >> GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_SET(x)                      (((x) << GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_LSB) & GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_MASK)
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_6_RESET                       0x8 // 8
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
#define GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_RESET                       0x5d // 93
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
#define GPIO_OUT_FUNCTION3_ADDRESS                                   0x18040038

#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MSB                        15
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB                        8
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK                       0x0000ff00
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_RESET                      0x1 // 1
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MSB                        7
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB                        0
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK                       0x000000ff
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_GET(x)                     (((x) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK) >> GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_SET(x)                     (((x) << GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_LSB) & GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_MASK)
#define GPIO_OUT_FUNCTION4_ENABLE_GPIO_16_RESET                      0x0 // 0
#define GPIO_OUT_FUNCTION4_ADDRESS                                   0x1804003c

#define GPIO_IN_ENABLE0_UART_SIN_MSB                                 15
#define GPIO_IN_ENABLE0_UART_SIN_LSB                                 8
#define GPIO_IN_ENABLE0_UART_SIN_MASK                                0x0000ff00
#define GPIO_IN_ENABLE0_UART_SIN_GET(x)                              (((x) & GPIO_IN_ENABLE0_UART_SIN_MASK) >> GPIO_IN_ENABLE0_UART_SIN_LSB)
#define GPIO_IN_ENABLE0_UART_SIN_SET(x)                              (((x) << GPIO_IN_ENABLE0_UART_SIN_LSB) & GPIO_IN_ENABLE0_UART_SIN_MASK)
#define GPIO_IN_ENABLE0_UART_SIN_RESET                               0x80 // 128
#define GPIO_IN_ENABLE0_SPI_DATA_IN_MSB                              7
#define GPIO_IN_ENABLE0_SPI_DATA_IN_LSB                              0
#define GPIO_IN_ENABLE0_SPI_DATA_IN_MASK                             0x000000ff
#define GPIO_IN_ENABLE0_SPI_DATA_IN_GET(x)                           (((x) & GPIO_IN_ENABLE0_SPI_DATA_IN_MASK) >> GPIO_IN_ENABLE0_SPI_DATA_IN_LSB)
#define GPIO_IN_ENABLE0_SPI_DATA_IN_SET(x)                           (((x) << GPIO_IN_ENABLE0_SPI_DATA_IN_LSB) & GPIO_IN_ENABLE0_SPI_DATA_IN_MASK)
#define GPIO_IN_ENABLE0_SPI_DATA_IN_RESET                            0x8 // 8
#define GPIO_IN_ENABLE0_ADDRESS                                      0x18040044

#define GPIO_IN_ENABLE1_RES_MSB                                      31
#define GPIO_IN_ENABLE1_RES_LSB                                      0
#define GPIO_IN_ENABLE1_RES_MASK                                     0xffffffff
#define GPIO_IN_ENABLE1_RES_GET(x)                                   (((x) & GPIO_IN_ENABLE1_RES_MASK) >> GPIO_IN_ENABLE1_RES_LSB)
#define GPIO_IN_ENABLE1_RES_SET(x)                                   (((x) << GPIO_IN_ENABLE1_RES_LSB) & GPIO_IN_ENABLE1_RES_MASK)
#define GPIO_IN_ENABLE1_RES_RESET                                    0x0 // 0
#define GPIO_IN_ENABLE1_ADDRESS                                      0x18040048

#define GPIO_IN_ENABLE2_RES_MSB                                      31
#define GPIO_IN_ENABLE2_RES_LSB                                      0
#define GPIO_IN_ENABLE2_RES_MASK                                     0xffffffff
#define GPIO_IN_ENABLE2_RES_GET(x)                                   (((x) & GPIO_IN_ENABLE2_RES_MASK) >> GPIO_IN_ENABLE2_RES_LSB)
#define GPIO_IN_ENABLE2_RES_SET(x)                                   (((x) << GPIO_IN_ENABLE2_RES_LSB) & GPIO_IN_ENABLE2_RES_MASK)
#define GPIO_IN_ENABLE2_RES_RESET                                    0x0 // 0
#define GPIO_IN_ENABLE2_ADDRESS                                      0x1804004c

#define GPIO_IN_ENABLE3_RES_MSB                                      31
#define GPIO_IN_ENABLE3_RES_LSB                                      0
#define GPIO_IN_ENABLE3_RES_MASK                                     0xffffffff
#define GPIO_IN_ENABLE3_RES_GET(x)                                   (((x) & GPIO_IN_ENABLE3_RES_MASK) >> GPIO_IN_ENABLE3_RES_LSB)
#define GPIO_IN_ENABLE3_RES_SET(x)                                   (((x) << GPIO_IN_ENABLE3_RES_LSB) & GPIO_IN_ENABLE3_RES_MASK)
#define GPIO_IN_ENABLE3_RES_RESET                                    0x0 // 0
#define GPIO_IN_ENABLE3_ADDRESS                                      0x18040050

#define GPIO_IN_ENABLE4_RES_MSB                                      31
#define GPIO_IN_ENABLE4_RES_LSB                                      0
#define GPIO_IN_ENABLE4_RES_MASK                                     0xffffffff
#define GPIO_IN_ENABLE4_RES_GET(x)                                   (((x) & GPIO_IN_ENABLE4_RES_MASK) >> GPIO_IN_ENABLE4_RES_LSB)
#define GPIO_IN_ENABLE4_RES_SET(x)                                   (((x) << GPIO_IN_ENABLE4_RES_LSB) & GPIO_IN_ENABLE4_RES_MASK)
#define GPIO_IN_ENABLE4_RES_RESET                                    0x0 // 0
#define GPIO_IN_ENABLE4_ADDRESS                                      0x18040054

#define GPIO_IN_ENABLE5_WMAC_IN3_MSB                                 31
#define GPIO_IN_ENABLE5_WMAC_IN3_LSB                                 24
#define GPIO_IN_ENABLE5_WMAC_IN3_MASK                                0xff000000
#define GPIO_IN_ENABLE5_WMAC_IN3_GET(x)                              (((x) & GPIO_IN_ENABLE5_WMAC_IN3_MASK) >> GPIO_IN_ENABLE5_WMAC_IN3_LSB)
#define GPIO_IN_ENABLE5_WMAC_IN3_SET(x)                              (((x) << GPIO_IN_ENABLE5_WMAC_IN3_LSB) & GPIO_IN_ENABLE5_WMAC_IN3_MASK)
#define GPIO_IN_ENABLE5_WMAC_IN3_RESET                               0x80 // 128
#define GPIO_IN_ENABLE5_WMAC_IN2_MSB                                 23
#define GPIO_IN_ENABLE5_WMAC_IN2_LSB                                 16
#define GPIO_IN_ENABLE5_WMAC_IN2_MASK                                0x00ff0000
#define GPIO_IN_ENABLE5_WMAC_IN2_GET(x)                              (((x) & GPIO_IN_ENABLE5_WMAC_IN2_MASK) >> GPIO_IN_ENABLE5_WMAC_IN2_LSB)
#define GPIO_IN_ENABLE5_WMAC_IN2_SET(x)                              (((x) << GPIO_IN_ENABLE5_WMAC_IN2_LSB) & GPIO_IN_ENABLE5_WMAC_IN2_MASK)
#define GPIO_IN_ENABLE5_WMAC_IN2_RESET                               0x80 // 128
#define GPIO_IN_ENABLE5_WMAC_IN1_MSB                                 15
#define GPIO_IN_ENABLE5_WMAC_IN1_LSB                                 8
#define GPIO_IN_ENABLE5_WMAC_IN1_MASK                                0x0000ff00
#define GPIO_IN_ENABLE5_WMAC_IN1_GET(x)                              (((x) & GPIO_IN_ENABLE5_WMAC_IN1_MASK) >> GPIO_IN_ENABLE5_WMAC_IN1_LSB)
#define GPIO_IN_ENABLE5_WMAC_IN1_SET(x)                              (((x) << GPIO_IN_ENABLE5_WMAC_IN1_LSB) & GPIO_IN_ENABLE5_WMAC_IN1_MASK)
#define GPIO_IN_ENABLE5_WMAC_IN1_RESET                               0x80 // 128
#define GPIO_IN_ENABLE5_WMAC_IN0_MSB                                 7
#define GPIO_IN_ENABLE5_WMAC_IN0_LSB                                 0
#define GPIO_IN_ENABLE5_WMAC_IN0_MASK                                0x000000ff
#define GPIO_IN_ENABLE5_WMAC_IN0_GET(x)                              (((x) & GPIO_IN_ENABLE5_WMAC_IN0_MASK) >> GPIO_IN_ENABLE5_WMAC_IN0_LSB)
#define GPIO_IN_ENABLE5_WMAC_IN0_SET(x)                              (((x) << GPIO_IN_ENABLE5_WMAC_IN0_LSB) & GPIO_IN_ENABLE5_WMAC_IN0_MASK)
#define GPIO_IN_ENABLE5_WMAC_IN0_RESET                               0x80 // 128
#define GPIO_IN_ENABLE5_ADDRESS                                      0x18040058

#define GPIO_IN_ENABLE6_WMAC_IN7_MSB                                 31
#define GPIO_IN_ENABLE6_WMAC_IN7_LSB                                 24
#define GPIO_IN_ENABLE6_WMAC_IN7_MASK                                0xff000000
#define GPIO_IN_ENABLE6_WMAC_IN7_GET(x)                              (((x) & GPIO_IN_ENABLE6_WMAC_IN7_MASK) >> GPIO_IN_ENABLE6_WMAC_IN7_LSB)
#define GPIO_IN_ENABLE6_WMAC_IN7_SET(x)                              (((x) << GPIO_IN_ENABLE6_WMAC_IN7_LSB) & GPIO_IN_ENABLE6_WMAC_IN7_MASK)
#define GPIO_IN_ENABLE6_WMAC_IN7_RESET                               0x80 // 128
#define GPIO_IN_ENABLE6_WMAC_IN6_MSB                                 23
#define GPIO_IN_ENABLE6_WMAC_IN6_LSB                                 16
#define GPIO_IN_ENABLE6_WMAC_IN6_MASK                                0x00ff0000
#define GPIO_IN_ENABLE6_WMAC_IN6_GET(x)                              (((x) & GPIO_IN_ENABLE6_WMAC_IN6_MASK) >> GPIO_IN_ENABLE6_WMAC_IN6_LSB)
#define GPIO_IN_ENABLE6_WMAC_IN6_SET(x)                              (((x) << GPIO_IN_ENABLE6_WMAC_IN6_LSB) & GPIO_IN_ENABLE6_WMAC_IN6_MASK)
#define GPIO_IN_ENABLE6_WMAC_IN6_RESET                               0x80 // 128
#define GPIO_IN_ENABLE6_WMAC_IN5_MSB                                 15
#define GPIO_IN_ENABLE6_WMAC_IN5_LSB                                 8
#define GPIO_IN_ENABLE6_WMAC_IN5_MASK                                0x0000ff00
#define GPIO_IN_ENABLE6_WMAC_IN5_GET(x)                              (((x) & GPIO_IN_ENABLE6_WMAC_IN5_MASK) >> GPIO_IN_ENABLE6_WMAC_IN5_LSB)
#define GPIO_IN_ENABLE6_WMAC_IN5_SET(x)                              (((x) << GPIO_IN_ENABLE6_WMAC_IN5_LSB) & GPIO_IN_ENABLE6_WMAC_IN5_MASK)
#define GPIO_IN_ENABLE6_WMAC_IN5_RESET                               0x80 // 128
#define GPIO_IN_ENABLE6_WMAC_IN4_MSB                                 7
#define GPIO_IN_ENABLE6_WMAC_IN4_LSB                                 0
#define GPIO_IN_ENABLE6_WMAC_IN4_MASK                                0x000000ff
#define GPIO_IN_ENABLE6_WMAC_IN4_GET(x)                              (((x) & GPIO_IN_ENABLE6_WMAC_IN4_MASK) >> GPIO_IN_ENABLE6_WMAC_IN4_LSB)
#define GPIO_IN_ENABLE6_WMAC_IN4_SET(x)                              (((x) << GPIO_IN_ENABLE6_WMAC_IN4_LSB) & GPIO_IN_ENABLE6_WMAC_IN4_MASK)
#define GPIO_IN_ENABLE6_WMAC_IN4_RESET                               0x80 // 128
#define GPIO_IN_ENABLE6_ADDRESS                                      0x1804005c

#define GPIO_IN_ENABLE7_WMAC_IN11_MSB                                31
#define GPIO_IN_ENABLE7_WMAC_IN11_LSB                                24
#define GPIO_IN_ENABLE7_WMAC_IN11_MASK                               0xff000000
#define GPIO_IN_ENABLE7_WMAC_IN11_GET(x)                             (((x) & GPIO_IN_ENABLE7_WMAC_IN11_MASK) >> GPIO_IN_ENABLE7_WMAC_IN11_LSB)
#define GPIO_IN_ENABLE7_WMAC_IN11_SET(x)                             (((x) << GPIO_IN_ENABLE7_WMAC_IN11_LSB) & GPIO_IN_ENABLE7_WMAC_IN11_MASK)
#define GPIO_IN_ENABLE7_WMAC_IN11_RESET                              0x80 // 128
#define GPIO_IN_ENABLE7_WMAC_IN10_MSB                                23
#define GPIO_IN_ENABLE7_WMAC_IN10_LSB                                16
#define GPIO_IN_ENABLE7_WMAC_IN10_MASK                               0x00ff0000
#define GPIO_IN_ENABLE7_WMAC_IN10_GET(x)                             (((x) & GPIO_IN_ENABLE7_WMAC_IN10_MASK) >> GPIO_IN_ENABLE7_WMAC_IN10_LSB)
#define GPIO_IN_ENABLE7_WMAC_IN10_SET(x)                             (((x) << GPIO_IN_ENABLE7_WMAC_IN10_LSB) & GPIO_IN_ENABLE7_WMAC_IN10_MASK)
#define GPIO_IN_ENABLE7_WMAC_IN10_RESET                              0x80 // 128
#define GPIO_IN_ENABLE7_WMAC_IN9_MSB                                 15
#define GPIO_IN_ENABLE7_WMAC_IN9_LSB                                 8
#define GPIO_IN_ENABLE7_WMAC_IN9_MASK                                0x0000ff00
#define GPIO_IN_ENABLE7_WMAC_IN9_GET(x)                              (((x) & GPIO_IN_ENABLE7_WMAC_IN9_MASK) >> GPIO_IN_ENABLE7_WMAC_IN9_LSB)
#define GPIO_IN_ENABLE7_WMAC_IN9_SET(x)                              (((x) << GPIO_IN_ENABLE7_WMAC_IN9_LSB) & GPIO_IN_ENABLE7_WMAC_IN9_MASK)
#define GPIO_IN_ENABLE7_WMAC_IN9_RESET                               0x80 // 128
#define GPIO_IN_ENABLE7_WMAC_IN8_MSB                                 7
#define GPIO_IN_ENABLE7_WMAC_IN8_LSB                                 0
#define GPIO_IN_ENABLE7_WMAC_IN8_MASK                                0x000000ff
#define GPIO_IN_ENABLE7_WMAC_IN8_GET(x)                              (((x) & GPIO_IN_ENABLE7_WMAC_IN8_MASK) >> GPIO_IN_ENABLE7_WMAC_IN8_LSB)
#define GPIO_IN_ENABLE7_WMAC_IN8_SET(x)                              (((x) << GPIO_IN_ENABLE7_WMAC_IN8_LSB) & GPIO_IN_ENABLE7_WMAC_IN8_MASK)
#define GPIO_IN_ENABLE7_WMAC_IN8_RESET                               0x80 // 128
#define GPIO_IN_ENABLE7_ADDRESS                                      0x18040060

#define GPIO_IN_ENABLE8_SRIF_SRESET_MSB                              31
#define GPIO_IN_ENABLE8_SRIF_SRESET_LSB                              24
#define GPIO_IN_ENABLE8_SRIF_SRESET_MASK                             0xff000000
#define GPIO_IN_ENABLE8_SRIF_SRESET_GET(x)                           (((x) & GPIO_IN_ENABLE8_SRIF_SRESET_MASK) >> GPIO_IN_ENABLE8_SRIF_SRESET_LSB)
#define GPIO_IN_ENABLE8_SRIF_SRESET_SET(x)                           (((x) << GPIO_IN_ENABLE8_SRIF_SRESET_LSB) & GPIO_IN_ENABLE8_SRIF_SRESET_MASK)
#define GPIO_IN_ENABLE8_SRIF_SRESET_RESET                            0x80 // 128
#define GPIO_IN_ENABLE8_SRIF_SIN_MSB                                 23
#define GPIO_IN_ENABLE8_SRIF_SIN_LSB                                 16
#define GPIO_IN_ENABLE8_SRIF_SIN_MASK                                0x00ff0000
#define GPIO_IN_ENABLE8_SRIF_SIN_GET(x)                              (((x) & GPIO_IN_ENABLE8_SRIF_SIN_MASK) >> GPIO_IN_ENABLE8_SRIF_SIN_LSB)
#define GPIO_IN_ENABLE8_SRIF_SIN_SET(x)                              (((x) << GPIO_IN_ENABLE8_SRIF_SIN_LSB) & GPIO_IN_ENABLE8_SRIF_SIN_MASK)
#define GPIO_IN_ENABLE8_SRIF_SIN_RESET                               0x80 // 128
#define GPIO_IN_ENABLE8_SRIF_SOT_MSB                                 15
#define GPIO_IN_ENABLE8_SRIF_SOT_LSB                                 8
#define GPIO_IN_ENABLE8_SRIF_SOT_MASK                                0x0000ff00
#define GPIO_IN_ENABLE8_SRIF_SOT_GET(x)                              (((x) & GPIO_IN_ENABLE8_SRIF_SOT_MASK) >> GPIO_IN_ENABLE8_SRIF_SOT_LSB)
#define GPIO_IN_ENABLE8_SRIF_SOT_SET(x)                              (((x) << GPIO_IN_ENABLE8_SRIF_SOT_LSB) & GPIO_IN_ENABLE8_SRIF_SOT_MASK)
#define GPIO_IN_ENABLE8_SRIF_SOT_RESET                               0x80 // 128
#define GPIO_IN_ENABLE8_SRIF_SCLK_MSB                                7
#define GPIO_IN_ENABLE8_SRIF_SCLK_LSB                                0
#define GPIO_IN_ENABLE8_SRIF_SCLK_MASK                               0x000000ff
#define GPIO_IN_ENABLE8_SRIF_SCLK_GET(x)                             (((x) & GPIO_IN_ENABLE8_SRIF_SCLK_MASK) >> GPIO_IN_ENABLE8_SRIF_SCLK_LSB)
#define GPIO_IN_ENABLE8_SRIF_SCLK_SET(x)                             (((x) << GPIO_IN_ENABLE8_SRIF_SCLK_LSB) & GPIO_IN_ENABLE8_SRIF_SCLK_MASK)
#define GPIO_IN_ENABLE8_SRIF_SCLK_RESET                              0x80 // 128
#define GPIO_IN_ENABLE8_ADDRESS                                      0x18040064

#define GPIO_IN_ENABLE9_RES_MSB                                      31
#define GPIO_IN_ENABLE9_RES_LSB                                      0
#define GPIO_IN_ENABLE9_RES_MASK                                     0xffffffff
#define GPIO_IN_ENABLE9_RES_GET(x)                                   (((x) & GPIO_IN_ENABLE9_RES_MASK) >> GPIO_IN_ENABLE9_RES_LSB)
#define GPIO_IN_ENABLE9_RES_SET(x)                                   (((x) << GPIO_IN_ENABLE9_RES_LSB) & GPIO_IN_ENABLE9_RES_MASK)
#define GPIO_IN_ENABLE9_RES_RESET                                    0x0 // 0
#define GPIO_IN_ENABLE9_ADDRESS                                      0x18040068

#define GPIO_FUNCTION_EXT_MDIO_SEL_MSB                               11
#define GPIO_FUNCTION_EXT_MDIO_SEL_LSB                               11
#define GPIO_FUNCTION_EXT_MDIO_SEL_MASK                              0x00000800
#define GPIO_FUNCTION_EXT_MDIO_SEL_GET(x)                            (((x) & GPIO_FUNCTION_EXT_MDIO_SEL_MASK) >> GPIO_FUNCTION_EXT_MDIO_SEL_LSB)
#define GPIO_FUNCTION_EXT_MDIO_SEL_SET(x)                            (((x) << GPIO_FUNCTION_EXT_MDIO_SEL_LSB) & GPIO_FUNCTION_EXT_MDIO_SEL_MASK)
#define GPIO_FUNCTION_EXT_MDIO_SEL_RESET                             0x0 // 0
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
#define GPIO_FUNCTION_CLK_OBS5_ENABLE_RESET                          0x0 // 0
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
#define GPIO_FUNCTION_CLK_OBS3_ENABLE_RESET                          0x1 // 1
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

#define ETH_CFG_ETH_SPARE_MSB                                        31
#define ETH_CFG_ETH_SPARE_LSB                                        22
#define ETH_CFG_ETH_SPARE_MASK                                       0xffc00000
#define ETH_CFG_ETH_SPARE_GET(x)                                     (((x) & ETH_CFG_ETH_SPARE_MASK) >> ETH_CFG_ETH_SPARE_LSB)
#define ETH_CFG_ETH_SPARE_SET(x)                                     (((x) << ETH_CFG_ETH_SPARE_LSB) & ETH_CFG_ETH_SPARE_MASK)
#define ETH_CFG_ETH_SPARE_RESET                                      0x0 // 0
#define ETH_CFG_SW_ACC_MSB_FIRST_MSB                                 13
#define ETH_CFG_SW_ACC_MSB_FIRST_LSB                                 13
#define ETH_CFG_SW_ACC_MSB_FIRST_MASK                                0x00002000
#define ETH_CFG_SW_ACC_MSB_FIRST_GET(x)                              (((x) & ETH_CFG_SW_ACC_MSB_FIRST_MASK) >> ETH_CFG_SW_ACC_MSB_FIRST_LSB)
#define ETH_CFG_SW_ACC_MSB_FIRST_SET(x)                              (((x) << ETH_CFG_SW_ACC_MSB_FIRST_LSB) & ETH_CFG_SW_ACC_MSB_FIRST_MASK)
#define ETH_CFG_SW_ACC_MSB_FIRST_RESET                               0x1 // 1
#define ETH_CFG_SW_APB_ACCESS_MSB                                    9
#define ETH_CFG_SW_APB_ACCESS_LSB                                    9
#define ETH_CFG_SW_APB_ACCESS_MASK                                   0x00000200
#define ETH_CFG_SW_APB_ACCESS_GET(x)                                 (((x) & ETH_CFG_SW_APB_ACCESS_MASK) >> ETH_CFG_SW_APB_ACCESS_LSB)
#define ETH_CFG_SW_APB_ACCESS_SET(x)                                 (((x) << ETH_CFG_SW_APB_ACCESS_LSB) & ETH_CFG_SW_APB_ACCESS_MASK)
#define ETH_CFG_SW_APB_ACCESS_RESET                                  0x0 // 0
#define ETH_CFG_SW_PHY_ADDR_SWAP_MSB                                 8
#define ETH_CFG_SW_PHY_ADDR_SWAP_LSB                                 8
#define ETH_CFG_SW_PHY_ADDR_SWAP_MASK                                0x00000100
#define ETH_CFG_SW_PHY_ADDR_SWAP_GET(x)                              (((x) & ETH_CFG_SW_PHY_ADDR_SWAP_MASK) >> ETH_CFG_SW_PHY_ADDR_SWAP_LSB)
#define ETH_CFG_SW_PHY_ADDR_SWAP_SET(x)                              (((x) << ETH_CFG_SW_PHY_ADDR_SWAP_LSB) & ETH_CFG_SW_PHY_ADDR_SWAP_MASK)
#define ETH_CFG_SW_PHY_ADDR_SWAP_RESET                               0x0 // 0
#define ETH_CFG_SW_PHY_SWAP_MSB                                      7
#define ETH_CFG_SW_PHY_SWAP_LSB                                      7
#define ETH_CFG_SW_PHY_SWAP_MASK                                     0x00000080
#define ETH_CFG_SW_PHY_SWAP_GET(x)                                   (((x) & ETH_CFG_SW_PHY_SWAP_MASK) >> ETH_CFG_SW_PHY_SWAP_LSB)
#define ETH_CFG_SW_PHY_SWAP_SET(x)                                   (((x) << ETH_CFG_SW_PHY_SWAP_LSB) & ETH_CFG_SW_PHY_SWAP_MASK)
#define ETH_CFG_SW_PHY_SWAP_RESET                                    0x0 // 0
#define ETH_CFG_SW_ONLY_MODE_MSB                                     6
#define ETH_CFG_SW_ONLY_MODE_LSB                                     6
#define ETH_CFG_SW_ONLY_MODE_MASK                                    0x00000040
#define ETH_CFG_SW_ONLY_MODE_GET(x)                                  (((x) & ETH_CFG_SW_ONLY_MODE_MASK) >> ETH_CFG_SW_ONLY_MODE_LSB)
#define ETH_CFG_SW_ONLY_MODE_SET(x)                                  (((x) << ETH_CFG_SW_ONLY_MODE_LSB) & ETH_CFG_SW_ONLY_MODE_MASK)
#define ETH_CFG_SW_ONLY_MODE_RESET                                   0x0 // 0
#define ETH_CFG_ADDRESS                                              0x18070000

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
//#define ATH_NAND_FLASH_BASE		0x1b800000u


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
#define ATH_USB_FLADJ_VAL		ATH_USB_CONFIG_BASE
#define ATH_USB_CONFIG			ATH_USB_CONFIG_BASE+0x4
#define ATH_USB_WINDOW			0x10000
#define ATH_USB_MODE			ATH_USB_EHCI_BASE+0x1a8

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
#define ATH_PCI_CRP			0x180c0000
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
#define ATH_RESET_GE0_PHY	RST_RESET_ETH_SWITCH_RESET_SET(1)
#define ATH_RESET_GE1_MAC	RST_RESET_GE1_MAC_RESET_SET(1)
#define ATH_RESET_GE1_PHY	RST_RESET_ETH_SWITCH_ARESET_SET(1)
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

#define CPU_CLK_FROM_DDR_PLL	CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_SET(0)
#define CPU_CLK_FROM_CPU_PLL	CPU_DDR_CLOCK_CONTROL_CPUCLK_FROM_CPUPLL_SET(1)

#define DDR_CLK_FROM_DDR_PLL	CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_SET(1)
#define DDR_CLK_FROM_CPU_PLL	CPU_DDR_CLOCK_CONTROL_DDRCLK_FROM_DDRPLL_SET(0)

#if CPU_DDR_SYNC_MODE

#	define both_from_cpu		0
#	define both_from_ddr		1

#	if both_from_ddr
#		define CLK_SRC_CONTROL		(CPU_CLK_FROM_DDR_PLL | DDR_CLK_FROM_DDR_PLL)
#		define AHB_CLK_FROM_DDR		CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_SET(1)
#	elif both_from_cpu
#		define CLK_SRC_CONTROL		(CPU_CLK_FROM_CPU_PLL | DDR_CLK_FROM_CPU_PLL)
#		define AHB_CLK_FROM_DDR		CPU_DDR_CLOCK_CONTROL_AHBCLK_FROM_DDRPLL_SET(0)
#	else
#		error "Invalid sync mode settings"
#	endif
#else
#	define CLK_SRC_CONTROL		(CPU_CLK_FROM_CPU_PLL | DDR_CLK_FROM_DDR_PLL)
#endif


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

#endif /* _QCA953X_H */
