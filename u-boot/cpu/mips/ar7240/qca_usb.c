/*
 * Copyright (C) 2017 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

#if defined(CONFIG_USB)

void usb_init(void)
{
#if (SOC_TYPE & QCA_QCA953X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC)
	u32 val;

	/* Select REFCLK USB PLL input */
	val = qca_soc_reg_read(QCA_PLL_SWITCH_CLK_CTRL_REG);
	val &= ~QCA_PLL_SWITCH_CLK_CTRL_USB_CLK_SEL_MASK;

	if (qca_xtal_is_40mhz())
		val |= (QCA_PLL_SWITCH_CLK_CTRL_USB_CLK_SEL_40M_VAL
			<< QCA_PLL_SWITCH_CLK_CTRL_USB_CLK_SEL_SHIFT);
	else
		val |= (QCA_PLL_SWITCH_CLK_CTRL_USB_CLK_SEL_25M_VAL
			<< QCA_PLL_SWITCH_CLK_CTRL_USB_CLK_SEL_SHIFT);

	qca_soc_reg_write(QCA_PLL_SWITCH_CLK_CTRL_REG, val);
	udelay(1000);

	/* Take out USB PHY/HOST/PLL out of reset */
#if (SOC_TYPE & QCA_QCA953X_SOC)
	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_USB_PHY_SUSPEND_ORIDE_MASK);
#else
	qca_soc_reg_read_set(QCA_RST_RESET_REG,
			     QCA_RST_RESET_USB_PHY_SUSPEND_ORIDE_MASK);
#endif
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_USB_PHY_ARST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_USB_PHY_RST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_USB_HOST_RST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_USB_PHY_PLLPWD_EXT_MASK);
	udelay(10);
#endif

#if (SOC_TYPE & QCA_QCA953X_SOC)
	qca_soc_reg_read_set(QCA_RST_RESET2_REG,
			     QCA_RST_RESET2_USB_EXT_PWR_SHIFT);
	udelay(10);

	qca_soc_reg_read_set(QCA_RST_RESET2_REG,
			     QCA_RST_RESET2_USB2_MODE_DEV_MASK);
	udelay(10);

	qca_soc_reg_read_set(QCA_RST_RESET2_REG,
			     QCA_RST_RESET2_USB2_PHY_SUSPEND_ORIDE_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET2_REG,
			       QCA_RST_RESET2_USB2_PHY_ARST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET2_REG,
			       QCA_RST_RESET2_USB2_PHY_RST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET2_REG,
			       QCA_RST_RESET2_USB2_HOST_RST_MASK);
	udelay(1000);

	qca_soc_reg_read_clear(QCA_RST_RESET2_REG,
			       QCA_RST_RESET2_USB2_PHY_PLLPWD_EXT_MASK);
	udelay(10);

	qca_soc_reg_read_set(QCA_RST_RESET2_REG,
			     QCA_RST_RESET2_USB2_EXT_PWR_MASK);
	udelay(10);
#endif
}

#endif /* defined(CONFIG_USB) */
