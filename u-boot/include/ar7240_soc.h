/*
 * Atheror AR7240 series processor SOC registers
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

#ifndef _AR7240_SOC_H
#define _AR7240_SOC_H

#include <config.h>

#ifdef CONFIG_WASP_SUPPORT
#include <ar934x_soc.h>
#endif

#ifdef CONFIG_AR7240_EMU
#define AR7240_EMU 1
#endif

#ifdef CONFIG_WASP_EMU
#define WASP_EMU 1
#endif
/*
 * Address map
 */
#define AR7240_PCI_MEM_BASE					0x10000000  /* 128M */
#define AR7240_APB_BASE						0x18000000  /* 384M */
#define AR7240_GE0_BASE						0x19000000  /* 16M */
#define AR7240_GE1_BASE						0x1a000000  /* 16M */
#define AR7240_USB_EHCI_BASE				0x1b000000
#define AR7240_USB_OHCI_BASE				0x1c000000
#define AR7240_SPI_BASE						0x1f000000
#define ATH_NAND_FLASH_BASE					0x1b000000u

/*
 * APB block
 */
#define AR7240_DDR_CTL_BASE					AR7240_APB_BASE+0x00000000
#define AR7240_CPU_BASE						AR7240_APB_BASE+0x00010000
#define AR7240_UART_BASE					AR7240_APB_BASE+0x00020000
#define AR7240_USB_CONFIG_BASE				AR7240_APB_BASE+0x00030000
#define AR7240_GPIO_BASE					AR7240_APB_BASE+0x00040000
#define AR7240_PLL_BASE						AR7240_APB_BASE+0x00050000
#define AR7240_RESET_BASE					AR7240_APB_BASE+0x00060000
#define AR7240_PCI_LCL_BASE					AR7240_APB_BASE+0x000f0000

/*
 * DDR block
 */
#define AR7240_DDR_CONFIG					AR7240_DDR_CTL_BASE+0
#define AR7240_DDR_CONFIG2					AR7240_DDR_CTL_BASE+4
#define AR7240_DDR_MODE						AR7240_DDR_CTL_BASE+0x08
#define AR7240_DDR_EXT_MODE					AR7240_DDR_CTL_BASE+0x0c
#define AR7240_DDR_CONTROL					AR7240_DDR_CTL_BASE+0x10
#define AR7240_DDR_REFRESH					AR7240_DDR_CTL_BASE+0x14
#define AR7240_DDR_RD_DATA_THIS_CYCLE		AR7240_DDR_CTL_BASE+0x18
#define AR7240_DDR_TAP_CONTROL0				AR7240_DDR_CTL_BASE+0x1c
#define AR7240_DDR_TAP_CONTROL1				AR7240_DDR_CTL_BASE+0x20
#define AR7240_DDR_TAP_CONTROL2				AR7240_DDR_CTL_BASE+0x24
#define AR7240_DDR_TAP_CONTROL3				AR7240_DDR_CTL_BASE+0x28

#ifdef CONFIG_WASP
#define AR7240_DDR_DDR2_CONFIG				AR7240_DDR_CTL_BASE+0xb8
#else
#define AR7240_DDR_DDR2_CONFIG				AR7240_DDR_CTL_BASE+0x8c
#endif

#define AR7240_DDR_BURST					AR7240_DDR_CTL_BASE+0xc4
#define AR7240_DDR_BURST2					AR7240_DDR_CTL_BASE+0xc8
#define AR7240_AHB_MASTER_TIMEOUT			AR7240_DDR_CTL_BASE+0xcc
#define AR7240_DDR_CTL_CONFIG				AR7240_DDR_CTL_BASE+0x108
#define AR7240_DDR_DEBUG_RD_CNTL			AR7240_DDR_CTL_BASE+0x118

#define AR7240_DDR_CONFIG_16BIT				(1 << 31)
#define AR7240_DDR_CONFIG_PAGE_OPEN			(1 << 30)
#define AR7240_DDR_CONFIG_CAS_LAT_SHIFT		27
#define AR7240_DDR_CONFIG_TMRD_SHIFT		23
#define AR7240_DDR_CONFIG_TRFC_SHIFT		17
#define AR7240_DDR_CONFIG_TRRD_SHIFT		13
#define AR7240_DDR_CONFIG_TRP_SHIFT			9
#define AR7240_DDR_CONFIG_TRCD_SHIFT		5
#define AR7240_DDR_CONFIG_TRAS_SHIFT		0

#define AR7240_DDR_CONFIG2_BL2				(2 << 0)
#define AR7240_DDR_CONFIG2_BL4				(4 << 0)
#define AR7240_DDR_CONFIG2_BL8				(8 << 0)

#define AR7240_DDR_CONFIG2_BT_IL			(1 << 4)
#define AR7240_DDR_CONFIG2_CNTL_OE_EN		(1 << 5)
#define AR7240_DDR_CONFIG2_PHASE_SEL		(1 << 6)
#define AR7240_DDR_CONFIG2_DRAM_CKE			(1 << 7)
#define AR7240_DDR_CONFIG2_TWR_SHIFT		8
#define AR7240_DDR_CONFIG2_TRTW_SHIFT		12
#define AR7240_DDR_CONFIG2_TRTP_SHIFT		17
#define AR7240_DDR_CONFIG2_TWTR_SHIFT		21
#define AR7240_DDR_CONFIG2_HALF_WIDTH_L		(1 << 31)

#define AR7240_DDR_TAP_DEFAULT				0x18

/*
 * PLL
 */
#define AR7240_CPU_PLL_CONFIG				AR7240_PLL_BASE
#define AR7240_USB_PLL_CONFIG				AR7240_PLL_BASE+0x4
#define AR7240_PCIE_PLL_CONFIG				AR7240_PLL_BASE+0x10
#define AR7240_CPU_CLOCK_CONTROL			AR7240_PLL_BASE+8

#ifndef CONFIG_WASP_SUPPORT
#define AR7240_USB_PLL_GE0_OFFSET			AR7240_PLL_BASE+0x10
#define AR7240_USB_PLL_GE1_OFFSET			AR7240_PLL_BASE+0x14
#define AR7240_S26_CLK_CTRL_OFFSET			AR7240_PLL_BASE+0x24
#endif

#define AR7242_ETH_XMII_CONFIG					AR7240_PLL_BASE+0x2c
#define AR934X_CPU_PLL_DITHER					AR7240_PLL_BASE+0x0048
#define AR934X_DDR_PLL_DITHER					AR7240_PLL_BASE+0x0044
#define AR934X_BB_PLL_CONFIG					AR7240_PLL_BASE+0x0040
#define AR934X_CURRENT_AUDIO_PLL_MODULATION		AR7240_PLL_BASE+0x003c
#define AR934X_AUDIO_PLL_MOD_STEP				AR7240_PLL_BASE+0x0038
#define AR934X_AUDIO_PLL_MODULATION				AR7240_PLL_BASE+0x0034
#define AR934X_AUDIO_PLL_CONFIG					AR7240_PLL_BASE+0x0030
#define AR934X_ETH_XMII							AR7240_PLL_BASE+0x002c
#define AR934X_CURRENT_PCIE_PLL_DITHER			AR7240_PLL_BASE+0x0028
#define AR934X_SWITCH_CLOCK_SPARE				AR7240_PLL_BASE+0x0024
#define AR934X_LDO_POWER_CONTROL				AR7240_PLL_BASE+0x0020
#define AR934X_PCIE_PLL_DITHER_STEP				AR7240_PLL_BASE+0x001c
#define AR934X_PCIE_PLL_DITHER_DIV_MIN			AR7240_PLL_BASE+0x0018
#define AR934X_PCIE_PLL_DITHER_DIV_MAX			AR7240_PLL_BASE+0x0014
#define AR934X_PCIE_PLL_CONFIG					AR7240_PLL_BASE+0x0010
#define AR934X_CPU_SYNC							AR7240_PLL_BASE+0x000c
#define AR934X_CPU_DDR_CLOCK_CONTROL			AR7240_PLL_BASE+0x0008
#define AR934X_DDR_PLL_CONFIG					AR7240_PLL_BASE+0x0004
#define AR934X_CPU_PLL_CONFIG					AR7240_PLL_BASE+0x0000

#define PLL_CONFIG_PLL_DIV_SHIFT				0
#define PLL_CONFIG_PLL_DIV_MASK					(0x3ff<< PLL_CONFIG_PLL_DIV_SHIFT)
#define PLL_CONFIG_PLL_REF_DIV_SHIFT			10
#define PLL_CONFIG_PLL_REF_DIV_MASK				(0xf << PLL_CONFIG_PLL_REF_DIV_SHIFT)
#define PLL_CONFIG_PLL_BYPASS_SHIFT				16
#define PLL_CONFIG_PLL_BYPASS_MASK				(0x1 << PLL_CONFIG_PLL_BYPASS_SHIFT)
#define PLL_CONFIG_PLL_UPDATE_SHIFT				17
#define PLL_CONFIG_PLL_UPDATE_MASK				(0x1 << PLL_CONFIG_PLL_UPDATE_SHIFT)
#define PLL_CONFIG_PLL_NOPWD_SHIFT				18
#define PLL_CONFIG_PLL_NOPWD_MASK				(0x1 << PLL_CONFIG_PLL_NOPWD_SHIFT)
#define PLL_CONFIG_AHB_DIV_SHIFT				19
#define PLL_CONFIG_AHB_DIV_MASK					(0x1 << PLL_CONFIG_AHB_DIV_SHIFT)
#define PLL_CONFIG_DDR_DIV_SHIFT				22
#define PLL_CONFIG_DDR_DIV_MASK					(0x1 << PLL_CONFIG_DDR_DIV_SHIFT)
#define PLL_CONFIG_PLL_RESET_SHIFT				25
#define PLL_CONFIG_PLL_RESET_MASK				(0x1 << PLL_CONFIG_PLL_RESET_SHIFT)

/* Hornet's CPU PLL Configuration Register */
#define HORNET_PLL_CONFIG_NINT_SHIFT			10
#define HORNET_PLL_CONFIG_NINT_MASK				(0x3f << HORNET_PLL_CONFIG_NINT_SHIFT)
#define HORNET_PLL_CONFIG_REFDIV_SHIFT			16
#define HORNET_PLL_CONFIG_REFDIV_MASK			(0x1f << HORNET_PLL_CONFIG_REFDIV_SHIFT)
#define HORNET_PLL_CONFIG_OUTDIV_SHIFT			23
#define HORNET_PLL_CONFIG_OUTDIV_MASK			(0x7 << HORNET_PLL_CONFIG_OUTDIV_SHIFT)
#define HORNET_PLL_CONFIG_PLLPWD_SHIFT			30
#define HORNET_PLL_CONFIG_PLLPWD_MASK			(0x1 << HORNET_PLL_CONFIG_PLLPWD_SHIFT)
#define HORNET_PLL_CONFIG_UPDATING_SHIFT		31
#define HORNET_PLL_CONFIG_UPDATING_MASK			(0x1 << HORNET_PLL_CONFIG_UPDATING_SHIFT)

/* Hornet's CPU PLL Configuration 2 Register */
#define HORNET_PLL_CONFIG2_SETTLE_TIME_SHIFT	0
#define HORNET_PLL_CONFIG2_SETTLE_TIME_MASK		(0xfff << HORNET_PLL_CONFIG2_SETTLE_TIME_SHIFT)

/* Hornet's CPU Clock Control Register */
#define HORNET_CLOCK_CONTROL_BYPASS_SHIFT		2
#define HORNET_CLOCK_CONTROL_BYPASS_MASK		(0x1 << HORNET_CLOCK_CONTROL_BYPASS_SHIFT)
#define HORNET_CLOCK_CONTROL_CPU_POST_DIV_SHIFT	5
#define HORNET_CLOCK_CONTROL_CPU_POST_DIV_MASK	(0x3 << HORNET_CLOCK_CONTROL_CPU_POST_DIV_SHIFT)
#define HORNET_CLOCK_CONTROL_DDR_POST_DIV_SFIFT	10
#define HORNET_CLOCK_CONTROL_DDR_POST_DIV_MASK	(0x3 << HORNET_CLOCK_CONTROL_DDR_POST_DIV_SFIFT)
#define HORNET_CLOCK_CONTROL_AHB_POST_DIV_SFIFT	15
#define HORNET_CLOCK_CONTROL_AHB_POST_DIV_MASK	(0x3 << HORNET_CLOCK_CONTROL_AHB_POST_DIV_SFIFT)

#define CLOCK_CONTROL_CLOCK_SWITCH_SHIFT		0
#define CLOCK_CONTROL_CLOCK_SWITCH_MASK			(1 << CLOCK_CONTROL_CLOCK_SWITCH_SHIFT)
#define CLOCK_CONTROL_RST_SWITCH_SHIFT			1
#define CLOCK_CONTROL_RST_SWITCH_MASK			(1 << CLOCK_CONTROL_RST_SWITCH_SHIFT)

/*
** PLL config for different CPU/DDR/AHB frequencies
*/
#define PLL_CONFIG_PLL_NOPWD_VAL				(1 << PLL_CONFIG_PLL_NOPWD_SHIFT)

#define UBOOT_SIZE								(256 * 1024)
#define PLL_FLASH_ADDR							(CFG_FLASH_BASE + UBOOT_SIZE)
#define PLL_CONFIG_VAL_F						(PLL_FLASH_ADDR + CFG_FLASH_SECTOR_SIZE - 0x20)
#define PLL_MAGIC								0xaabbccdd
#define SRIF_PLL_CONFIG_VAL_F					(PLL_CONFIG_VAL_F - 12)
#define SRIF_PLL_MAGIC							0x73726966 /* srif */

/*
 * PLL block
 */
#define AR7240_PLL_CONFIG				AR7240_PLL_BASE+0x0

/*
 * CLOCK
 */
#define AR7240_CPU_CLOCK_CONTROL		AR7240_PLL_BASE+8

/*
 * FIFO flushes
 */
#define AR7240_DDR_GE0_FLUSH			AR7240_DDR_CTL_BASE+0x9c
#define AR7240_DDR_GE1_FLUSH			AR7240_DDR_CTL_BASE+0xa0
#define AR7240_DDR_PCI_FLUSH			AR7240_DDR_CTL_BASE+0xa8

/*
 * USB block
 */
#define AR7240_USB_FLADJ_VAL			AR7240_USB_CONFIG_BASE
#define AR7240_USB_CONFIG				AR7240_USB_CONFIG_BASE+0x4
#define AR7240_USB_WINDOW				0x1000000

/*
 * PCI block
 */
#define AR7240_PCI_WINDOW				0x8000000       /* 128MB */
#define AR7240_PCI_WINDOW0_OFFSET		AR7240_DDR_CTL_BASE+0x7c
#define AR7240_PCI_WINDOW1_OFFSET		AR7240_DDR_CTL_BASE+0x80
#define AR7240_PCI_WINDOW2_OFFSET		AR7240_DDR_CTL_BASE+0x84
#define AR7240_PCI_WINDOW3_OFFSET		AR7240_DDR_CTL_BASE+0x88
#define AR7240_PCI_WINDOW4_OFFSET		AR7240_DDR_CTL_BASE+0x8c
#define AR7240_PCI_WINDOW5_OFFSET		AR7240_DDR_CTL_BASE+0x90
#define AR7240_PCI_WINDOW6_OFFSET		AR7240_DDR_CTL_BASE+0x94
#define AR7240_PCI_WINDOW7_OFFSET		AR7240_DDR_CTL_BASE+0x98

#define AR7240_PCI_WINDOW0_VAL			0x10000000
#define AR7240_PCI_WINDOW1_VAL			0x11000000
#define AR7240_PCI_WINDOW2_VAL			0x12000000
#define AR7240_PCI_WINDOW3_VAL			0x13000000
#define AR7240_PCI_WINDOW4_VAL			0x14000000
#define AR7240_PCI_WINDOW5_VAL			0x15000000
#define AR7240_PCI_WINDOW6_VAL			0x16000000
#define AR7240_PCI_WINDOW7_VAL			0x07000000

/*
 * CRP. To access the host controller config and status registers
 */
#define AR7240_PCI_CRP					0x180c0000
#define AR7240_PCI_DEV_CFGBASE			0x14000000

#define AR7240_PCI_CRP_AD_CBE			AR7240_PCI_CRP
#define AR7240_PCI_CRP_WRDATA			AR7240_PCI_CRP+0x4
#define AR7240_PCI_CRP_RDDATA			AR7240_PCI_CRP+0x8
#define AR7240_PCI_ERROR				AR7240_PCI_CRP+0x1c
#define AR7240_PCI_ERROR_ADDRESS		AR7240_PCI_CRP+0x20
#define AR7240_PCI_AHB_ERROR			AR7240_PCI_CRP+0x24
#define AR7240_PCI_AHB_ERROR_ADDRESS	AR7240_PCI_CRP+0x28

#define AR7240_CRP_CMD_WRITE			0x00010000
#define AR7240_CRP_CMD_READ				0x00000000

/*
 * PCI CFG. To generate config cycles
 */
#define AR7240_PCI_CFG_AD				AR7240_PCI_CRP+0xc
#define AR7240_PCI_CFG_CBE				AR7240_PCI_CRP+0x10
#define AR7240_PCI_CFG_WRDATA			AR7240_PCI_CRP+0x14
#define AR7240_PCI_CFG_RDDATA			AR7240_PCI_CRP+0x18
#define AR7240_CFG_CMD_READ				0x0000000a
#define AR7240_CFG_CMD_WRITE			0x0000000b

#define AR7240_PCI_IDSEL_ADLINE_START	17
#define AR7240_PCI_LCL_RESET			AR7240_PCI_LCL_BASE+0x18

/*
 * gpio configs
 */
#define AR7240_GPIO_OE					AR7240_GPIO_BASE+0x0
#define AR7240_GPIO_IN					AR7240_GPIO_BASE+0x4
#define AR7240_GPIO_OUT					AR7240_GPIO_BASE+0x8
#define AR7240_GPIO_SET					AR7240_GPIO_BASE+0xc
#define AR7240_GPIO_CLEAR				AR7240_GPIO_BASE+0x10
#define AR7240_GPIO_INT_ENABLE			AR7240_GPIO_BASE+0x14
#define AR7240_GPIO_INT_TYPE			AR7240_GPIO_BASE+0x18
#define AR7240_GPIO_INT_POLARITY		AR7240_GPIO_BASE+0x1c
#define AR7240_GPIO_INT_PENDING			AR7240_GPIO_BASE+0x20
#define AR7240_GPIO_INT_MASK			AR7240_GPIO_BASE+0x24
#define AR7240_GPIO_FUNC				AR7240_GPIO_BASE+0x28

/*
 * IRQ Map.
 * There are 4 conceptual ICs in the system. We generally give a block of 16
 * irqs to each IC.
 * CPU:                     0    - 0xf
 *      MISC:               0x10 - 0x1f
 *          GPIO:           0x20 - 0x2f
 *      PCI :               0x30 - 0x40
 *
 */
#define AR7240_CPU_IRQ_BASE				0x00
#define AR7240_MISC_IRQ_BASE			0x10
#define AR7240_GPIO_IRQ_BASE			0x20
#define AR7240_PCI_IRQ_BASE				0x30

/*
 * The IPs. Connected to CPU (hardware IP's; the first two are software)
 */
#define AR7240_CPU_IRQ_PCI				AR7240_CPU_IRQ_BASE+2
#define AR7240_CPU_IRQ_USB				AR7240_CPU_IRQ_BASE+3
#define AR7240_CPU_IRQ_GE0				AR7240_CPU_IRQ_BASE+4
#define AR7240_CPU_IRQ_GE1				AR7240_CPU_IRQ_BASE+5
#define AR7240_CPU_IRQ_MISC				AR7240_CPU_IRQ_BASE+6
#define AR7240_CPU_IRQ_TIMER			AR7240_CPU_IRQ_BASE+7

/*
 * Interrupts connected to the CPU->Misc line.
 */
#define AR7240_MISC_IRQ_TIMER			AR7240_MISC_IRQ_BASE+0
#define AR7240_MISC_IRQ_ERROR			AR7240_MISC_IRQ_BASE+1
#define AR7240_MISC_IRQ_GPIO			AR7240_MISC_IRQ_BASE+2
#define AR7240_MISC_IRQ_UART			AR7240_MISC_IRQ_BASE+3
#define AR7240_MISC_IRQ_WATCHDOG		AR7240_MISC_IRQ_BASE+4
#define AR7240_MISC_IRQ_COUNT			5

#define MIMR_TIMER						0x01
#define MIMR_ERROR						0x02
#define MIMR_GPIO						0x04
#define MIMR_UART						0x08
#define MIMR_WATCHDOG					0x10

#define MISR_TIMER						MIMR_TIMER
#define MISR_ERROR						MIMR_ERROR
#define MISR_GPIO						MIMR_GPIO
#define MISR_UART						MIMR_UART
#define MISR_WATCHDOG					MIMR_WATCHDOG

/*
 * Interrupts connected to the Misc->GPIO line
 */
#define AR7240_GPIO_IRQn(_gpio)			AR7240_GPIO_IRQ_BASE+(_gpio)
#define AR7240_GPIO_IRQ_COUNT			16

/*
 * Interrupts connected to CPU->PCI
 */
#define AR7240_PCI_IRQ_DEV0				AR7240_PCI_IRQ_BASE+0
#define AR7240_PCI_IRQ_DEV1				AR7240_PCI_IRQ_BASE+1
#define AR7240_PCI_IRQ_DEV2				AR7240_PCI_IRQ_BASE+2
#define AR7240_PCI_IRQ_CORE				AR7240_PCI_IRQ_BASE+3
#define AR7240_PCI_IRQ_COUNT			4

/*
 * PCI interrupt mask and status
 */
#define PIMR_DEV0						0x01
#define PIMR_DEV1						0x02
#define PIMR_DEV2						0x04
#define PIMR_CORE						0x10

#define PISR_DEV0						PIMR_DEV0
#define PISR_DEV1						PIMR_DEV1
#define PISR_DEV2						PIMR_DEV2
#define PISR_CORE						PIMR_CORE

#define AR7240_GPIO_COUNT				16

/*
 * Reset block
 */
#define AR7240_GENERAL_TMR					AR7240_RESET_BASE+0
#define AR7240_GENERAL_TMR_RELOAD			AR7240_RESET_BASE+4
#define AR7240_WATCHDOG_TMR_CONTROL			AR7240_RESET_BASE+8
#define AR7240_WATCHDOG_TMR					AR7240_RESET_BASE+0xc
#define AR7240_MISC_INT_STATUS				AR7240_RESET_BASE+0x10
#define AR7240_MISC_INT_MASK				AR7240_RESET_BASE+0x14
#define AR7240_GLOBAL_INT_STATUS			AR7240_RESET_BASE+0x18
#define AR7240_RESET						AR7240_RESET_BASE+0x1c
#define HORNET_BOOTSTRAP_STATUS				AR7240_RESET_BASE+0xac /* Hornet's bootstrap register */
#define AR7240_REV_ID						(AR7240_RESET_BASE + 0x90)
#define AR7240_REV_ID_MASK					0xffff
#define HORNET_REV_ID_MASK					0xfff
#define AR9344_REV_ID_MASK					0xfff0	/* Ignore minor id */
#define HORNET_BOOTSTRAP_SEL_25M_40M_MASK	0x00000001 /* Hornet's bootstrap register */
#define HORNET_BOOTSTRAP_MEM_TYPE_SHIFT		12
#define HORNET_BOOTSTRAP_MEM_TYPE_MASK		(0x3 << HORNET_BOOTSTRAP_MEM_TYPE_SHIFT) /* Hornet's bootstrap register */
#define HORNET_BOOTSTRAP_MDIO_SLAVE_MASK	0x00020000 /* Hornet's bootstrap register */

// WASP BootStrap Register
#define WASP_BOOTSTRAP_REG					(AR7240_RESET_BASE + 0xb0)
#define WASP_BOOTSTRAP_SDRAM_DISABLE_SHIFT	1
#define WASP_BOOTSTRAP_SDRAM_DISABLE_MASK	(1 << WASP_BOOTSTRAP_SDRAM_DISABLE_SHIFT)
#define WASP_BOOTSTRAP_DDR_SELECT_SHIFT		0
#define WASP_BOOTSTRAP_DDR_SELECT_MASK		(1 << WASP_BOOTSTRAP_DDR_SELECT_SHIFT)
#define WASP_BOOTSTRAP_DDR_WIDTH_SHIFT		21
#define WASP_BOOTSTRAP_DDR_WIDTH_MASK		(1 << WASP_BOOTSTRAP_DDR_WIDTH_SHIFT)
#define WASP_REF_CLK_25						(1 << 4) /* 0 - 25MHz	1 - 40 MHz */
#define WASP_RAM_TYPE(a)					((a) & 0x3)

#define AR7240_REV_ID_AR7130		0xa0
#define AR7240_REV_ID_AR7141		0xa1
#define AR7240_REV_ID_AR7161		0xa2
#define AR7240_REV_1_0				0xc0
#define AR7240_REV_1_1				0xc1
#define AR7240_REV_1_2				0xc2
#define AR7241_REV_1_0				0x0100
#define AR7242_REV_1_0				0x1100
#define AR7241_REV_1_1				0x0101
#define AR7242_REV_1_1				0x1101

#define AR9330_REV_1_0				0x0110                  /* 5-port:0x110, 4-port 0x1110 */
#define AR9331_REV_1_0				0x1110
#define AR9330_REV_1_1				0x0111                  /* 5-port:0x111, 4-port 0x1111 */
#define AR9331_REV_1_1				0x1111
#define AR9330_REV_1_2				0x0112
#define AR9331_REV_1_2				0x1112

#define AR9344_REV_1_x				0x2120	/* Wasp 1.x, ignore minor id */
#define AR9342_REV_1_x				0x1120
#define AR9341_REV_1_x				0x0120

#define AR9344_REV_1_0				0x2120	/* Wasp 1.0 */
#define AR9342_REV_1_0				0x1120
#define AR9341_REV_1_0				0x0120

#define AR9344_REV_1_1				0x2121	/* Wasp 1.1 */
#define AR9342_REV_1_1				0x1121
#define AR9341_REV_1_1				0x0121

#define is_ar7240()     (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7240_REV_1_2) || \
                         ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7240_REV_1_1) || \
                         ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7240_REV_1_0))

#define is_ar7241()     (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7241_REV_1_0) || \
                         ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7241_REV_1_1))

#define is_ar7242()     (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7242_REV_1_0) || \
                         ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7242_REV_1_1))

#define is_ar9330() (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_0) || \
                        ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_1) || \
                        ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_2))

#define is_ar9331() (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_0) || \
                        ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_1) || \
                        ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_2))

#define is_ar933x_10()  (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_0) || \
                            ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_0))

#define is_ar933x_11()  (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_1) || \
                            ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_1))
   
#define is_ar933x_12()  (((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9330_REV_1_2) || \
                            ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR9331_REV_1_2))
       

#define is_ar933x() (is_ar9330() || is_ar9331())

#define is_ar9344()	((ar7240_reg_rd(AR7240_REV_ID) & AR9344_REV_ID_MASK) == AR9344_REV_1_x)
#define is_ar9342()	((ar7240_reg_rd(AR7240_REV_ID) & AR9344_REV_ID_MASK) == AR9342_REV_1_x)
#define is_ar9341()	((ar7240_reg_rd(AR7240_REV_ID) & AR9344_REV_ID_MASK) == AR9341_REV_1_x)

#ifdef CONFIG_WASP_SUPPORT
	#define is_wasp()	1
	#define is_ar934x()	1
#else
	#define is_wasp()	0
	#define is_ar934x()	0
#endif

#ifdef CONFIG_AR7240_EMU
	#define is_emu()	1
#else
	#define is_emu()	0
#endif

#ifdef CONFIG_F1E_PHY
	#define is_f1e()	1
#else
	#define is_f1e()	0
#endif

#ifdef CONFIG_F2E_PHY
	#define is_f2e()	1
#else
	#define is_f2e()	0
#endif

#ifdef CONFIG_ATHRS16_PHY
	#define is_s16()	1
#else
	#define is_s16()	0
#endif

/*
 * AR7240_RESET bit defines
 */
#define AR7240_RESET_EXTERNAL				(1 << 28)
#define AR7240_RESET_WMAC					(1 << 27)
#define AR7240_RESET_FULL_CHIP				(1 << 24)
#define AR7240_RESET_CPU_NMI				(1 << 21)
#define AR7240_RESET_CPU_COLD_RESET_MASK	(1 << 20)
#define AR7240_RESET_DDR					(1 << 16)
#define AR7240_RESET_GE1_MAC				(1 << 13)
#define AR7240_RESET_GE1_MDIO				(1 << 23)
#define AR7240_RESET_GE1_PHY				(1 << 12) /* Not valid */
#define AR7240_RESET_PCIE_PHY_SERIAL		(1 << 10)
#define AR7240_RESET_GE0_MAC				(1 << 9)
#define AR7240_RESET_GE0_MDIO				(1 << 22)
#define AR7240_RESET_GE0_PHY				(1 << 8) /* Switch reset */
#define AR7240_RESET_PCIE_PHY				(1 << 7)
#define AR7240_RESET_PCIE					(1 << 6)
#define AR7240_RESET_USB_HOST				(1 << 5)
#define AR7240_RESET_USB_OHCI_DLL			(1 << 3)

#define AR7240_MII0_CTRL					0x18070000
#define AR7240_MII1_CTRL					0x18070004

#define K1BASE								KSEG1

#ifndef __ASSEMBLY__
typedef enum {
    AR7240_DDR_16B_LOW,
    AR7240_DDR_16B_HIGH,
    AR7240_DDR_32B,
}ar7240_ddr_width_t;

#define ar7240_reg_rd(_phys)			(*(volatile unsigned int *)KSEG1ADDR(_phys))
#define ar7240_reg_wr_nf(_phys, _val)	((*(volatile unsigned int *)KSEG1ADDR(_phys)) = (_val))

#define ar7240_reg_wr(_phys, _val)		do { ar7240_reg_wr_nf(_phys, _val); ar7240_reg_rd(_phys); } while(0);

#define ar7240_write_pci_window(_no)             \
  ar7240_reg_wr(AR7240_PCI_WINDOW##_no##_OFFSET, AR7240_PCI_WINDOW##_no##_VAL);

#define BIT(_x) (1 << (_x))

#define ar7240_reg_rmw_set(_reg, _mask)  do {                        \
    ar7240_reg_wr((_reg), (ar7240_reg_rd((_reg)) | (_mask)));      \
    ar7240_reg_rd((_reg));                                           \
}while(0);

#define ar7240_reg_rmw_clear(_reg, _mask)  do {                        \
    ar7240_reg_wr((_reg), (ar7240_reg_rd((_reg)) & ~(_mask)));      \
    ar7240_reg_rd((_reg));                                           \
}while(0);

#define ar7240_get_bit(_reg, _bit)  (ar7240_reg_rd((_reg)) & (1 << (_bit)))

#define ar7240_flush_ge(_unit) do {                             \
    u32     reg = (_unit) ? AR7240_DDR_GE1_FLUSH : AR7240_DDR_GE0_FLUSH;   \
    ar7240_reg_wr(reg, 1);                 \
    while((ar7240_reg_rd(reg) & 0x1));   \
    ar7240_reg_wr(reg, 1);                 \
    while((ar7240_reg_rd(reg) & 0x1));   \
}while(0);

#define ar7240_flush_pci() do {                             \
    ar7240_reg_wr(AR7240_DDR_PCI_FLUSH, 1);                 \
    while((ar7240_reg_rd(AR7240_DDR_PCI_FLUSH) & 0x1));   \
    ar7240_reg_wr(AR7240_DDR_PCI_FLUSH, 1);                 \
    while((ar7240_reg_rd(AR7240_DDR_PCI_FLUSH) & 0x1));   \
}while(0);

#endif  /*__ASSEMBLY*/
#endif
