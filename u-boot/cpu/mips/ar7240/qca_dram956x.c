/*
 * Copyright (C) 2008-2013 Atheros Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <atheros.h>
#include <soc/qca956x_pll_init.h>
#include <soc/qca_soc_common.h>

uint32_t *ath_ddr_tap_cal(void);

/* Notice the value CFG_DDR2_DRAGONFLY_CAS_LATENCY
 * Should Sync with CFG_PLL_FREQ
 * */
#ifndef CFG_DDR2_DRAGONFLY_CAS_LATENCY
#define CFG_DDR2_DRAGONFLY_CAS_LATENCY	5
#endif

#ifdef CONFIG_TB614
#	define DDR_CONFIG2_SWAP_A26_A27_VAL	(0x1)
#else
#	define DDR_CONFIG2_SWAP_A26_A27_VAL	(0x0)
#endif

#if CFG_DDR2_DRAGONFLY_CAS_LATENCY == 3

#define CFG_DDR2_CONFIG_VAL			DDR_CONFIG_CAS_LATENCY_MSB_SET(0x0) | \
						DDR_CONFIG_OPEN_PAGE_SET(0x1) | \
						DDR_CONFIG_CAS_LATENCY_SET(0x7) | \
						DDR_CONFIG_TMRD_SET(0x6) | \
						DDR_CONFIG_TRFC_SET(0x10) | \
						DDR_CONFIG_TRRD_SET(0x5) | \
						DDR_CONFIG_TRP_SET(0x8) | \
						DDR_CONFIG_TRCD_SET(0x8) | \
						DDR_CONFIG_TRAS_SET(0x17)

#define CFG_DDR2_CONFIG2_VAL			DDR_CONFIG2_HALF_WIDTH_LOW_SET(0x1) | \
						DDR_CONFIG2_SWAP_A26_A27_SET(DDR_CONFIG2_SWAP_A26_A27_VAL) | \
						DDR_CONFIG2_GATE_OPEN_LATENCY_SET(0x6) | \
						DDR_CONFIG2_TWTR_SET(0x12) | \
						DDR_CONFIG2_TRTP_SET(0xa) | \
						DDR_CONFIG2_TRTW_SET(0xe) | \
						DDR_CONFIG2_TWR_SET(0xf) | \
						DDR_CONFIG2_CKE_SET(0x1) | \
						DDR_CONFIG2_CNTL_OE_EN_SET(0x1) | \
						DDR_CONFIG2_BURST_LENGTH_SET(0x8)

#define CFG_DDR2_CONFIG3_VAL			0x00000002
#define CFG_DDR2_EXT_MODE_VAL1			0x782
#define CFG_DDR2_EXT_MODE_VAL2			0x402
#define CFG_DDR2_MODE_VAL_INIT			0x733
#define CFG_DDR2_MODE_VAL			0x633
#define CFG_DDR2_TAP_VAL			0x10
#define CFG_DDR2_EN_TWL_VAL			0x00000e65
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16	0xffff
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32	0xff

#elif CFG_DDR2_DRAGONFLY_CAS_LATENCY == 4

#define CFG_DDR2_CONFIG_VAL			DDR_CONFIG_CAS_LATENCY_MSB_SET(0x1) | \
						DDR_CONFIG_OPEN_PAGE_SET(0x1) | \
						DDR_CONFIG_CAS_LATENCY_SET(0x1) | \
						DDR_CONFIG_TMRD_SET(0x6) | \
						DDR_CONFIG_TRFC_SET(0x11) | \
						DDR_CONFIG_TRRD_SET(0x6) | \
						DDR_CONFIG_TRP_SET(0x8) | \
						DDR_CONFIG_TRCD_SET(0x8) | \
						DDR_CONFIG_TRAS_SET(0x18)

#define CFG_DDR2_CONFIG2_VAL			DDR_CONFIG2_HALF_WIDTH_LOW_SET(0x1) | \
						DDR_CONFIG2_SWAP_A26_A27_SET(DDR_CONFIG2_SWAP_A26_A27_VAL) | \
						DDR_CONFIG2_GATE_OPEN_LATENCY_SET(0x8) | \
						DDR_CONFIG2_TWTR_SET(0x12) | \
						DDR_CONFIG2_TRTP_SET(0xa) | \
						DDR_CONFIG2_TRTW_SET(0xe) | \
						DDR_CONFIG2_TWR_SET(0xf) | \
						DDR_CONFIG2_CKE_SET(0x1) | \
						DDR_CONFIG2_CNTL_OE_EN_SET(0x1) | \
						DDR_CONFIG2_BURST_LENGTH_SET(0x8)

#define CFG_DDR2_CONFIG3_VAL			0x0000000a
#define CFG_DDR2_EXT_MODE_VAL1			0x782
#define CFG_DDR2_EXT_MODE_VAL2			0x402
#define CFG_DDR2_MODE_VAL_INIT			0x743
#define CFG_DDR2_MODE_VAL			0x643
#define CFG_DDR2_TAP_VAL			0x10
#define CFG_DDR2_EN_TWL_VAL			0x0000166d
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16	0xffff
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32	0xff

#elif CFG_DDR2_DRAGONFLY_CAS_LATENCY == 5

#define CFG_DDR2_CONFIG_VAL			DDR_CONFIG_CAS_LATENCY_MSB_SET(0x1) | \
						DDR_CONFIG_OPEN_PAGE_SET(0x1) | \
						DDR_CONFIG_CAS_LATENCY_SET(0x4) | \
						DDR_CONFIG_TMRD_SET(0x6) | \
						DDR_CONFIG_TRFC_SET(0x16) | \
						DDR_CONFIG_TRRD_SET(0x7) | \
						DDR_CONFIG_TRP_SET(0xb) | \
						DDR_CONFIG_TRCD_SET(0xb) | \
						DDR_CONFIG_TRAS_SET(0)

#define CFG_DDR2_CONFIG2_VAL			DDR_CONFIG2_HALF_WIDTH_LOW_SET(0x1) | \
						DDR_CONFIG2_SWAP_A26_A27_SET(DDR_CONFIG2_SWAP_A26_A27_VAL) | \
						DDR_CONFIG2_GATE_OPEN_LATENCY_SET(0xa) | \
						DDR_CONFIG2_TWTR_SET(0x16) | \
						DDR_CONFIG2_TRTP_SET(0xa) | \
						DDR_CONFIG2_TRTW_SET(0xe) | \
						DDR_CONFIG2_TWR_SET(0x2) | \
						DDR_CONFIG2_CKE_SET(0x1) | \
						DDR_CONFIG2_CNTL_OE_EN_SET(0x1) | \
						DDR_CONFIG2_BURST_LENGTH_SET(0x8)


#define CFG_DDR2_CONFIG3_VAL            0x0000000e
#define CFG_DDR2_EXT_MODE_VAL1			0x782
#define CFG_DDR2_EXT_MODE_VAL2          0x402
#define CFG_DDR2_MODE_VAL_INIT          0xb53
#define CFG_DDR2_MODE_VAL               0xa53
#define CFG_DDR2_TAP_VAL                0x10
#define CFG_DDR2_EN_TWL_VAL             0x00001e91
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16	0xffff
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32	0xff

#elif CFG_DDR2_DRAGONFLY_CAS_LATENCY == 6

#define CFG_DDR2_CONFIG_VAL			DDR_CONFIG_CAS_LATENCY_MSB_SET(0x1) | \
						DDR_CONFIG_OPEN_PAGE_SET(0x1) | \
						DDR_CONFIG_CAS_LATENCY_SET(0x6) | \
						DDR_CONFIG_TMRD_SET(0x6) | \
						DDR_CONFIG_TRFC_SET(0x16) | \
						DDR_CONFIG_TRRD_SET(0x7) | \
						DDR_CONFIG_TRP_SET(0xb) | \
						DDR_CONFIG_TRCD_SET(0xb) | \
						DDR_CONFIG_TRAS_SET(0)

#define CFG_DDR2_CONFIG2_VAL			DDR_CONFIG2_HALF_WIDTH_LOW_SET(0x1) | \
						DDR_CONFIG2_SWAP_A26_A27_SET(DDR_CONFIG2_SWAP_A26_A27_VAL) | \
						DDR_CONFIG2_GATE_OPEN_LATENCY_SET(0xc) | \
						DDR_CONFIG2_TWTR_SET(0x18) | \
						DDR_CONFIG2_TRTP_SET(0xa) | \
						DDR_CONFIG2_TRTW_SET(0xe) | \
						DDR_CONFIG2_TWR_SET(0x2) | \
						DDR_CONFIG2_CKE_SET(0x1) | \
						DDR_CONFIG2_CNTL_OE_EN_SET(0x1) | \
						DDR_CONFIG2_BURST_LENGTH_SET(0x8)


#define CFG_DDR2_CONFIG3_VAL            0x0000000e
#define CFG_DDR2_EXT_MODE_VAL1		    0x782
#define CFG_DDR2_EXT_MODE_VAL2          0x402
#define CFG_DDR2_MODE_VAL_INIT          0xb63
#define CFG_DDR2_MODE_VAL               0xa63
#define CFG_DDR2_TAP_VAL                0x10
#define CFG_DDR2_EN_TWL_VAL             0x00002691
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16	0xffff
#define CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_32	0xff

#endif

/* CAL = 3 FOR DDR */
#define CFG_DDR1_CONFIG_VAL			DDR_CONFIG_OPEN_PAGE_SET(0x1) | \
						DDR_CONFIG_CAS_LATENCY_SET(0x7) | \
						DDR_CONFIG_TMRD_SET(0x6) | \
						DDR_CONFIG_TRFC_SET(0x9) | \
						DDR_CONFIG_TRRD_SET(0x5) | \
						DDR_CONFIG_TRP_SET(0x8) | \
						DDR_CONFIG_TRCD_SET(0x8) | \
						DDR_CONFIG_TRAS_SET(0x15)


#define CFG_DDR1_CONFIG2_VAL			DDR_CONFIG2_HALF_WIDTH_LOW_SET(0x1) | \
						DDR_CONFIG2_GATE_OPEN_LATENCY_SET(0x6) | \
						DDR_CONFIG2_TWTR_SET(0x10) | \
						DDR_CONFIG2_TRTP_SET(0xa) | \
						DDR_CONFIG2_TRTW_SET(0x10) | \
						DDR_CONFIG2_TWR_SET(0xf) | \
						DDR_CONFIG2_CKE_SET(0x1) | \
						DDR_CONFIG2_CNTL_OE_EN_SET(0x1) | \
						DDR_CONFIG2_BURST_LENGTH_SET(0x8)
#define CFG_DDR1_CONFIG3_VAL			0x0
#define CFG_DDR1_EXT_MODE_VAL			0x2
#define CFG_DDR1_MODE_VAL_INIT			0x133
#define CFG_DDR1_MODE_VAL			0x33
#define CFG_DDR1_RD_DATA_THIS_CYCLE_VAL_16	0xffff
#define CFG_DDR1_RD_DATA_THIS_CYCLE_VAL_32	0xff
#define CFG_DDR1_TAP_VAL			0x10
#define CFG_DDR1_EN_TWL_VAL			0x00000664

#define CFG_DDR_CTL_CONFIG			DDR_CTL_CONFIG_SRAM_TSEL_SET(0x1) | \
						DDR_CTL_CONFIG_GE0_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_GE1_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_USB_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_PCIE_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_WMAC_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_MISC_SRC1_SRAM_SYNC_SET(0x1) | \
						DDR_CTL_CONFIG_MISC_SRC2_SRAM_SYNC_SET(0x1)

void qca_dram_init(void)
{
	int		ddr_config, ddr_config2, ddr_config3, mod_val,
			mod_val_init, cycle_val, tap_val, type, ctl_config;
	uint32_t	refresh = CFG_DDR_REFRESH_VAL;

	switch(type = qca_dram_type()) {
	case RAM_MEMORY_TYPE_DDR2:
		ddr_config	= CFG_DDR2_CONFIG_VAL;
		ddr_config2	= CFG_DDR2_CONFIG2_VAL;
		ddr_config3	= CFG_DDR2_CONFIG3_VAL;
		mod_val_init	= CFG_DDR2_MODE_VAL_INIT;
		mod_val		= CFG_DDR2_MODE_VAL;
		tap_val		= CFG_DDR2_TAP_VAL;

		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x10);
		udelay(10);
		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x20);
		udelay(10);

        ctl_config =	CFG_DDR_CTL_CONFIG |
					DDR_CTL_CONFIG_PAD_DDR2_SEL_SET(0x1) |
					DDR_CTL_CONFIG_HALF_WIDTH_SET(0x1);

        cycle_val = CFG_DDR2_RD_DATA_THIS_CYCLE_VAL_16;


		ctl_config |= QCA_DDR_CTRL_CFG_SYNC_MODE;

		qca_soc_reg_write(QCA_DDR_CTRL_CFG_REG, ctl_config);

		debug("ddr2 init\n");
		udelay(10);
		break;
	case RAM_MEMORY_TYPE_DDR1:
		ddr_config	= CFG_DDR1_CONFIG_VAL;
		ddr_config2	= CFG_DDR1_CONFIG2_VAL;
		ddr_config3	= CFG_DDR1_CONFIG3_VAL;
		mod_val_init	= CFG_DDR1_MODE_VAL_INIT;
		mod_val		= CFG_DDR1_MODE_VAL;
		tap_val		= CFG_DDR1_TAP_VAL;

        cycle_val = CFG_DDR1_RD_DATA_THIS_CYCLE_VAL_16;
        ctl_config = CFG_DDR_CTL_CONFIG |
                         DDR_CTL_CONFIG_HALF_WIDTH_SET(0x1);

		ctl_config |= QCA_DDR_CTRL_CFG_SYNC_MODE;

		qca_soc_reg_write(QCA_DDR_CTRL_CFG_REG, ctl_config);
		udelay(10);
		debug("ddr1 init\n");

		break;
	default:
		debug("%s: invalid memory type\n", __func__);
		return;
	}
#if 0
	uint32_t	*pll = (unsigned *)CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET;
	if (*pll == PLL_MAGIC) {
		uint32_t cas = pll[5];
		if (cas == 3 || cas == 4) {
			cas = (cas * 2) + 2;
			ddr_config &= ~(DDR_CONFIG_CAS_LATENCY_MSB_MASK |
					DDR_CONFIG_CAS_LATENCY_MASK);
			ddr_config |= DDR_CONFIG_CAS_LATENCY_SET(cas & 0x7) |
				DDR_CONFIG_CAS_LATENCY_MSB_SET((cas >> 3) & 1);

			cas = pll[5];

			ddr_config2 &= ~DDR_CONFIG2_GATE_OPEN_LATENCY_MASK;
			ddr_config2 |= DDR_CONFIG2_GATE_OPEN_LATENCY_SET((2 * cas) + 1);

			if (type == RAM_MEMORY_TYPE_DDR2) {
				uint32_t tmp;
				tmp = qca_soc_reg_read(DDR2_CONFIG_ADDRESS);
				tmp &= ~DDR2_CONFIG_DDR2_TWL_MASK;
				tmp |= DDR2_CONFIG_DDR2_TWL_SET(cas == 3 ? 3 : 5);
				qca_soc_reg_write(DDR2_CONFIG_ADDRESS, tmp);
			}

			mod_val = (cas == 3 ? 0x33 : 0x43);
			mod_val_init = 0x100 | mod_val;
		}
	}
#endif

	qca_soc_reg_write(DDR_RD_DATA_THIS_CYCLE_ADDRESS, cycle_val);
	udelay(100);
	qca_soc_reg_write(DDR_BURST_ADDRESS, 0x74444444);
	udelay(100);
	qca_soc_reg_write(DDR_BURST2_ADDRESS, 0x44444444);
	udelay(100);
	qca_soc_reg_write(QCA_DDR_FSM_WAIT_CTRL_REG, QCA_DDR_FSM_WAIT_CTRL_VAL);
	udelay(100);
	qca_soc_reg_write(DDR_AHB_MASTER_TIMEOUT_MAX_ADDRESS, 0xfffff);
	udelay(100);
	qca_soc_reg_write(DDR_CONFIG_ADDRESS, ddr_config);
	udelay(100);
	qca_soc_reg_write(DDR_CONFIG2_ADDRESS, ddr_config2);
	udelay(100);
	qca_soc_reg_write(DDR_CONFIG_3_ADDRESS, ddr_config3);
	udelay(100);

	if (type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_write(DDR2_CONFIG_ADDRESS, CFG_DDR2_EN_TWL_VAL);
		udelay(100);
	}
	if (type == RAM_MEMORY_TYPE_DDR1) {
		qca_soc_reg_write(DDR2_CONFIG_ADDRESS, CFG_DDR1_EN_TWL_VAL);
		udelay(100);
	}	

	qca_soc_reg_write(DDR_CONFIG2_ADDRESS, ddr_config2 | 0x80);	// CKE Enable
	udelay(100);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x8);	// Precharge
	udelay(10);

	if (type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_write(DDR_EMR2_ADDRESS, 0x80);
		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x10);	// EMR2
		udelay(10);
		qca_soc_reg_write(DDR_EMR3_ADDRESS, 0);
		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x20);	// EMR3
		udelay(10);
	}

	if (type == RAM_MEMORY_TYPE_DDR1 || type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_write(DDR_EXTENDED_MODE_REGISTER_ADDRESS, CFG_DDR2_EXT_MODE_VAL2); // EMR DLL enable, Reduced Driver Impedance control, Differential DQS disabled
		udelay(100);
		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x2); // EMR write
		udelay(10);
	}

	qca_soc_reg_write(DDR_MODE_REGISTER_ADDRESS, mod_val_init);
	udelay(1000);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x1);	// MR Write
	udelay(10);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x8);	// Precharge
	udelay(10);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x4);	// Auto Refresh
	udelay(10);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x4);	// Auto Refresh
	udelay(10);

	// Issue MRS to remove DLL out-of-reset
	qca_soc_reg_write(DDR_MODE_REGISTER_ADDRESS, mod_val);
	udelay(100);

	qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x1); // MR write
	udelay(100);

	if (type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_write(DDR_EXTENDED_MODE_REGISTER_ADDRESS, CFG_DDR2_EXT_MODE_VAL1);
		udelay(100);

		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x2); // EMR write
		udelay(100);

		qca_soc_reg_write(DDR_EXTENDED_MODE_REGISTER_ADDRESS, CFG_DDR2_EXT_MODE_VAL2);
		udelay(100);

		qca_soc_reg_write(DDR_CONTROL_ADDRESS, 0x2); // EMR write
		udelay(100);
		
		refresh = CFG_DDR2_REFRESH_VAL;
	}
	qca_soc_reg_write(DDR_REFRESH_ADDRESS, refresh);
	udelay(100);
	
    qca_soc_reg_write(TAP_CONTROL_0_ADDRESS, tap_val);
    qca_soc_reg_write(TAP_CONTROL_1_ADDRESS, tap_val);

    qca_soc_reg_write (TAP_CONTROL_2_ADDRESS, tap_val);
    qca_soc_reg_write (TAP_CONTROL_3_ADDRESS, tap_val);

	if (type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_write(PMU1_ADDRESS, 0x633c8176);
		// Set DDR2 Voltage to 1.8 volts
		qca_soc_reg_write(PMU2_ADDRESS, PMU2_SWREGMSB_SET(0x40) |
					 PMU2_PGM_SET(0x1));
	}

	/*
         * Based on SGMII validation for stucks, packet errors were  observed and it was 
         * mostly due to noise pickup on SGMII lines. Switching regulator register is to 
         * be programmed with proper setting to avoid such stucks.
	 */
	if (type == RAM_MEMORY_TYPE_DDR1){
		qca_soc_reg_write(PMU1_ADDRESS, 0x633c8176);
		qca_soc_reg_write(PMU2_ADDRESS, 0x10200000);
	}

	ath_ddr_tap_cal();
}
