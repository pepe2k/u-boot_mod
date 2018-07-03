/*
 * Qualcomm/Atheros WiSoCs PCIE RC related
 * functions for WiSoC families:
 * - Atheros AR934x
 * - Qualcomm/Atheros QCA953x
 * - Qualcomm/Atheros QCA955x
 * - Qualcomm/Atheros QCA956x
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

#if defined(CONFIG_PCI)

#define ATHEROS_VENDOR_ID    0x168c

static const struct {
	const char name[10];
	u16 id;
} qca_pci_names[] = {
#if !defined(CONFIG_DISABLE_PCI_NAME)
	//sorted for better compression
	{"AR5416", 0x0024},
	{"AR9160", 0x0027},
	{"AR9280", 0x0029},
	{"AR9280", 0x002a},
	{"AR9285", 0x002b},
	{"AR2427", 0x002c},
	{"AR9287", 0x002d},
	{"AR9287", 0x002e},
	{"AR9300", 0x0030},
	{"AR9300", 0x0031},
	{"AR9300", 0x0032},
	{"AR9300", 0x0033},
	{"AR9300", 0x0034},
	{"AR9300", 0x0035},
	{"AR9300", 0x0036},
	{"AR9300", 0x0038},
	{"AR9300", 0x003d},
	{"AR9300", 0x003f},
	{"AR9485", 0x0037},
	{"QCA6164", 0x0041},	//ath10k
	{"QCA6174", 0x003e},	//ath10k
	{"QCA9377", 0x0042},	//ath10k
	{"QCA988X", 0x003c},	//ath10k
	{"QCA9887", 0x0050},	//ath10k
	{"QCA9888", 0x0056},	//ath10k
	{"QCA99X0", 0x0040},	//ath10k
	{"QCA9984", 0x0046},	//ath10k
#endif
};

const char *qca_pcie_dev_name(u32 vid, u32 did) {
	static char qca_pci_txt_num[4+1+4+1];
	int i;

	if( vid != ATHEROS_VENDOR_ID)
		goto fallback;

	for(i = 0; i < (sizeof(qca_pci_names)/sizeof(*qca_pci_names)); i++) {
		if(qca_pci_names[i].id == did)
			return qca_pci_names[i].name;
	}

fallback:
	sprintf(qca_pci_txt_num, "%04X:%04X", vid, did);
	return qca_pci_txt_num;
}

/*
 * Returns 1 if PCIE0 is in EP mode
 */
#if (SOC_TYPE & QCA_AR934X_SOC) |\
    (SOC_TYPE & QCA_QCA955X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
u32 qca_pcie0_in_ep_mode(void)
{
	if (!(qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG)
	    & QCA_RST_BOOTSTRAP_PCIE_RC_MODE_MASK))
		return 1;

	return 0;
}
#endif

/*
 * Returns 1 if link is up and provides
 * vendor and device IDs of endpoint
 */
u32 qca_pcie_dev_info(u32 rc_num, u32 *vid, u32 *did)
{
	u32 reg;

	if (rc_num == 0)
		reg = qca_soc_reg_read(QCA_PCIE_RC0_CTRL_RST_REG);
	else
		reg = qca_soc_reg_read(QCA_PCIE_RC1_CTRL_RST_REG);

	if (reg & QCA_PCIE_RCX_CTRL_RST_LINK_UP_MASK) {
		if (rc_num == 0)
			reg = qca_soc_reg_read(QCA_PCIE_RC0_SLAVE_CFG_BASE_REG);
		else
			reg = qca_soc_reg_read(QCA_PCIE_RC1_SLAVE_CFG_BASE_REG);

		/* Vendor (lower 16-bit) and device (higher 16-bit) ID */
		*vid = reg & BITS(0, 16);
		*did = (reg >> 16) & BITS(0, 16);

		return 1;
	}

	return 0;
}

/*
 * This allows to define custom NFRAC range for SSC clocking
 */
#ifndef CONFIG_QCA_PCIE_PLL_NFRAC_MAX_VAL
	#define CONFIG_QCA_PCIE_PLL_NFRAC_MAX_VAL	0x3FFF
#endif

#ifndef CONFIG_QCA_PCIE_PLL_NFRAC_MIN_VAL
	#define CONFIG_QCA_PCIE_PLL_NFRAC_MIN_VAL	0x3F84
#endif

/*
 * Setups PCIE PLL
 *
 * Recommended target clock should be ~100 MHz
 *
 * PCIE PLL clock formula:
 *            REF_CLK    NFRAC            1
 * PCIE_PLL = ------- x (----- + NINT) x ---
 *            REF_DIV    2^14            DIV
 *
 * For  AR934x/QCA955x, default DIV is 8
 * For QCA953x/QCA956x, default DIV is 6
 *
 * TODO: confirm formula for QCA953x/QCA956x
 *       because datasheets have different
 *       and strange formulas, especially
 *       for QCA956x
 *
 * TODO: PLL tune/test (SQSUM_DVC)?
 */
static void qca_pcie_pll_init(void)
{
	u32 nfrac_max, nfrac_min, nint, reg;
	u32 ref_div = 1;

#if (SOC_TYPE & QCA_QCA953X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
	if (qca_xtal_is_40mhz()) {
		nint = 29;
		ref_div = 2;
	} else {
		nint = 23;
	}
#else
	if (qca_xtal_is_40mhz()) {
		nint = 39;
		ref_div = 2;
	} else {
		nint = 31;
	}
#endif

#if (SOC_TYPE & QCA_QCA956X_SOC)
	qca_soc_reg_read_set(QCA_PLL_SRIF_PCIE_PHY_REG_1_REG,
	                     (u32)QCA_PLL_SRIF_PCIE_PHY_REG_1_S_RESET << QCA_PLL_SRIF_PCIE_PHY_REG_1_S_SHIFT);
#endif

	/* Power down and bypass PLL, setup ref_div */
	reg = QCA_PLL_PCIE_PLL_CFG_PLLPWD_MASK |
	      QCA_PLL_PCIE_PLL_CFG_BYPASS_MASK |
	      (ref_div << QCA_PLL_PCIE_PLL_CFG_REFDIV_SHIFT);

	qca_soc_reg_write(QCA_PLL_PCIE_PLL_CFG_REG, reg);
	udelay(100);

	/*
	 * Use dithering/SSC (spread spectrum clocking)
	 * as in QC/A SDK (for minimize/reduce EMI)
	 */
	nfrac_max = (u32)CONFIG_QCA_PCIE_PLL_NFRAC_MAX_VAL
		    << QCA_PLL_PCIE_PLL_DITHER_MAX_NFRAC_MAX_SHIFT;
	nfrac_max = nfrac_max & QCA_PLL_PCIE_PLL_DITHER_MAX_NFRAC_MAX_MASK;

	nfrac_min = (u32)CONFIG_QCA_PCIE_PLL_NFRAC_MIN_VAL
		    << QCA_PLL_PCIE_PLL_DITHER_MIN_NFRAC_MIN_SHIFT;
	nfrac_min = nfrac_max & QCA_PLL_PCIE_PLL_DITHER_MIN_NFRAC_MIN_MASK;

#if (SOC_TYPE & QCA_QCA956X_SOC)
	/* QC/A SDK does not set QCA_PLL_PCIE_PLL_DITHER_MAX_DITHER_EN_MASK on QCA956x */
	reg = QCA_PLL_PCIE_PLL_DITHER_MAX_USE_MAX_MASK |
	      (nint << QCA_PLL_PCIE_PLL_DITHER_MAX_NINT_MAX_SHIFT) | nfrac_max;
#else
	reg = QCA_PLL_PCIE_PLL_DITHER_MAX_DITHER_EN_MASK |
	      QCA_PLL_PCIE_PLL_DITHER_MAX_USE_MAX_MASK |
	      (nint << QCA_PLL_PCIE_PLL_DITHER_MAX_NINT_MAX_SHIFT) | nfrac_max;
#endif

	qca_soc_reg_write(QCA_PLL_PCIE_PLL_DITHER_MAX_REG, reg);

	reg = (nint << QCA_PLL_PCIE_PLL_DITHER_MIN_NINT_MIN_SHIFT) | nfrac_min;
	qca_soc_reg_write(QCA_PLL_PCIE_PLL_DITHER_MIN_REG, reg);

	/* Power up PLL ... */
	qca_soc_reg_read_clear(QCA_PLL_PCIE_PLL_CFG_REG,
			       QCA_PLL_PCIE_PLL_CFG_PLLPWD_MASK);
	udelay(100);

	/* ... and wait for update complete */
	do {
		udelay(10);
		reg = qca_soc_reg_read(QCA_PLL_PCIE_PLL_CFG_REG);
	} while (reg & QCA_PLL_PCIE_PLL_CFG_UPDATING_MASK);

	/* Disable PLL bypassing */
	qca_soc_reg_read_clear(QCA_PLL_PCIE_PLL_CFG_REG,
			       QCA_PLL_PCIE_PLL_CFG_BYPASS_MASK);
	udelay(100);
}

#if (SOC_TYPE & QCA_AR934X_SOC)  |\
    (SOC_TYPE & QCA_QCA953X_SOC) |\
    (SOC_TYPE & QCA_QCA955X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
/*
 * Takes out PCIE0 RC from reset
 */
static void qca_pcie0_rst_di(void)
{
	/* Take PCIE PHY and core out of reset */
	qca_soc_reg_read_clear(QCA_RST_RESET_REG,
			       QCA_RST_RESET_PCIE_RST_MASK |
			       QCA_RST_RESET_PCIE_PHY_RST_MASK);
	milisecdelay(10);

#if !(SOC_TYPE & QCA_QCA956X_SOC)
	/* Enable LTSSM */
	qca_soc_reg_read_set(QCA_PCIE_RC0_CTRL_APP_REG,
			     QCA_PCIE_RCX_CTRL_APP_LTSSM_EN_MASK);

	/* Take EP out of reset (this sets PERSTn high) */
	qca_soc_reg_write(QCA_PCIE_RC0_CTRL_RST_REG,
			  QCA_PCIE_RCX_CTRL_RST_EP_RST_L_MASK);
#endif
	milisecdelay(100);
}

/*
 * Resets PCIE0 RC
 */
static void qca_pcie0_rst_en(void)
{
	/* Reset PCIE PHY and core */
	qca_soc_reg_read_set(QCA_RST_RESET_REG,
			     QCA_RST_RESET_PCIE_RST_MASK |
			     QCA_RST_RESET_PCIE_PHY_RST_MASK);
	milisecdelay(10);

#if !(SOC_TYPE & QCA_QCA956X_SOC)
	/* Put EP in reset (this sets PERSTn low) */
	qca_soc_reg_write(QCA_PCIE_RC0_CTRL_RST_REG, 0x0);
	milisecdelay(10);
#endif
}
#endif

#if (SOC_TYPE & QCA_QCA955X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
/*
 * Takes out PCIE1 RC from reset
 */
static void qca_pcie1_rst_di(void)
{
	/* Take PCIE PHY and core out of reset */
	qca_soc_reg_read_clear(QCA_RST_RESET2_REG,
			       QCA_RST_RESET2_PCIE2_RST_MASK |
			       QCA_RST_RESET2_PCIE2_PHY_RST_MASK);
	milisecdelay(10);

	/* Enable LTSSM */
	qca_soc_reg_read_set(QCA_PCIE_RC1_CTRL_APP_REG,
			     QCA_PCIE_RCX_CTRL_APP_LTSSM_EN_MASK);

	/* Take EP out of reset (this sets PERSTn high) */
	qca_soc_reg_write(QCA_PCIE_RC1_CTRL_RST_REG,
			  QCA_PCIE_RCX_CTRL_RST_EP_RST_L_MASK);
	milisecdelay(100);
}

/*
 * Resets PCIE1 RC
 */
static void qca_pcie1_rst_en(void)
{
	/* Reset PCIE PHY and core */
	qca_soc_reg_read_set(QCA_RST_RESET2_REG,
			     QCA_RST_RESET2_PCIE2_RST_MASK |
			     QCA_RST_RESET2_PCIE2_PHY_RST_MASK);
	milisecdelay(10);

	/* Put EP in reset (this sets PERSTn low) */
	qca_soc_reg_write(QCA_PCIE_RC1_CTRL_RST_REG, 0x0);
	milisecdelay(10);
}
#endif

/*
 * Initializes PCIE
 */
void pci_init(void)
{
#if (SOC_TYPE & QCA_AR934X_SOC)
	/*
	 * AR934x contains one PCIE bus controller
	 * which can work in both modes (RC and EP)
	 */
	if (qca_pcie0_in_ep_mode())
		return;
#endif

	/* Init PCIE PLL (common for both RC) */
	qca_pcie_pll_init();

#if (SOC_TYPE & QCA_QCA956X_SOC)
	/* From QC/A SDK. TODO: What is 0x73 ? */
	qca_soc_reg_read_clear(QCA_GPIO_OE_REG, GPIO0);
	qca_soc_reg_read_set(QCA_GPIO_OUT_FUNC0_REG, 0x73UL << QCA_GPIO_OUT_FUNCX_GPIO0_EN_SHIFT);
	milisecdelay(10);
#endif

	/* Reset PCIE */
#if (SOC_TYPE & QCA_AR934X_SOC) |\
    (SOC_TYPE & QCA_QCA953X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
	/* QCA956x always need a PCIE0 reset even not in EP Mode */
	qca_pcie0_rst_en();
	qca_pcie0_rst_di();
#elif (SOC_TYPE & QCA_QCA955X_SOC)
	if (!qca_pcie0_in_ep_mode()) {
		qca_pcie0_rst_en();
		qca_pcie0_rst_di();
	}
#endif

#if (SOC_TYPE & QCA_QCA955X_SOC) |\
    (SOC_TYPE & QCA_QCA956X_SOC)
	qca_pcie1_rst_en();
	qca_pcie1_rst_di();
#endif
}

#endif /* defined(CONFIG_PCI) */
