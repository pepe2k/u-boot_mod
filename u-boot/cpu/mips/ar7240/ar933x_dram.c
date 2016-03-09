/*
 * Atheros AR933x WiSoC DRAM related functions
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2015-2016 Wills Wang <wills.wang@live.com>
 * Copyright (C) 2013 Qualcomm Atheros, Inc.
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>
#include <soc/qca_dram.h>

/*
 * DQS delay tap tune
 *
 * This function is a modified C version of the original
 * ar933x_ddr_tap_init(void) function, written in asm,
 * included in Atheros SDK code
 *
 * Below is, slightly modified version based on:
 * https://patchwork.ozlabs.org/patch/569046/
 */

#define DQS_DELAY_TAP_LIMIT_VAL			31
#define DQS_DELAY_TAP_START_VAL			(DQS_DELAY_TAP_LIMIT_VAL / 2)
#define DQS_DELAY_TAP_PATTERN_OFFSET	0x2000
#define DQS_DELAY_TAP_PATTERN_SIZE		0x1000

/* Setup DQS_{0,1} tap setting */
static inline void ar933x_ddr_tap_save(u32 tap)
{
	/* Awlays bypass higher 32-level delay chain (use only lower) */
	tap = tap | QCA_DDR_TAP_CTRL_TAP_H_BYPASS_MASK;

	qca_soc_reg_write(QCA_DDR_TAP_CTRL_0_REG, tap);
	qca_soc_reg_write(QCA_DDR_TAP_CTRL_1_REG, tap);
}

static void ar933x_ddr_tap_tune(void)
{
	u32 *addr, *addr_k0, *addr_k1;
	u32 cnt_up, done, err, i, j;
	u32 tap, tap_hi, tap_lo;

	/* Use middle value as starting point */
	ar933x_ddr_tap_save(DQS_DELAY_TAP_START_VAL);

	/* Prepare 4M (256 x 4 x 4 bytes) pattern */
	addr = (void *)KSEG0ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);

	for (i = 0; i < 256; i++) {
		tap = 0;

		for (j = 0; j < 8; j++) {
			if (i & (1 << j)) {
				if (j % 2)
					tap |= 0xFFFF0000;
				else
					tap |= 0x0000FFFF;
			}

			if (j % 2) {
				*addr++ = tap;
				tap = 0;
			}
		}
	}

	tap = DQS_DELAY_TAP_START_VAL;

	/* 1 -> incrementing, 0 -> decrementing */
	cnt_up = 1;
	tap_lo = 0;
	tap_hi = DQS_DELAY_TAP_LIMIT_VAL;

	addr = (void *)KSEG0ADDR(DQS_DELAY_TAP_PATTERN_OFFSET
							 + DQS_DELAY_TAP_PATTERN_SIZE);

	done = 0;

	while (!done) {
		ar933x_ddr_tap_save(tap);

		err = 0;

		/* 2 passes per each tested tap value */
		for (i = 0; i < 2; i++) {
			addr_k1 = (void *)KSEG1ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);
			addr_k0 = (void *)KSEG0ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);

			while (addr_k0 < addr) {
				if (*addr_k1++ != *addr_k0++) {
					err = 1;
					break;
				}
			}

			if (err)
				break;
		}

		if (err) {
			if (cnt_up) {
				/* Upper value found */
				tap--;
				tap_hi = tap;

				cnt_up = 0;
				tap = DQS_DELAY_TAP_START_VAL;
			} else {
				/* Lower value found */
				tap++;
				tap_lo = tap;
				done = 1;
			}
		} else {
			if (cnt_up) {
				if (tap < DQS_DELAY_TAP_LIMIT_VAL) {
					tap++;
				} else {
					/* Reached max. possible value */
					tap_hi = tap;

					cnt_up = 0;
					tap = DQS_DELAY_TAP_START_VAL;
				}
			} else {
				if (tap == 0) {
					/* Reached min. possible value */
					tap_lo = tap;
					done = 1;
				} else {
					tap--;
				}
			}
		}
	}

	/* Use average value as target tap */
	tap = (tap_hi + tap_lo) / 2;
	ar933x_ddr_tap_save(tap);
}

/*
 * Initial DRAM configuration
 */
void qca_dram_init(void)
{
	u32 mem_type = qca_dram_type();

	/* DDR timings (if not defined, use values from old SDK code) */
#ifdef CONFIG_QCA_DDR_CFG_REG_VAL
	qca_soc_reg_write(QCA_DDR_CFG_REG, CONFIG_QCA_DDR_CFG_REG_VAL);
#else
	/*
	 * tRAS = 16, tRCD = 6, tRP = 6, tRRD = 4, tRFC = 30, tMRD = 15
	 * CAS = 7, page closed
	 */
	qca_soc_reg_write(QCA_DDR_CFG_REG,
					  _qca_ddr_cfg_reg_val(16, 6, 6, 4, 30, 15, 7, 1));
#endif

#ifdef CONFIG_QCA_DDR_CFG2_REG_VAL
	qca_soc_reg_write(QCA_DDR_CFG2_REG, CONFIG_QCA_DDR_CFG2_REG_VAL);
#else
	/*
	 * Burst length always 8, burst type: sequential,
	 * 3-state addr/ctrl outputs, output phase 0, CKE = 1,
	 * tWR = 6, tRTW = 14, tRTP = 8, tWTR = 14,
	 * gate open latency = 7, use low half width of DQ bus
	 */
	qca_soc_reg_write(QCA_DDR_CFG2_REG,
					  _qca_ddr_cfg2_reg_val(0, 1, 0, 1, 6, 14, 8, 14, 7, 1));
#endif

	if (mem_type == RAM_MEMORY_TYPE_SDR) {
		/* Enable SDR */
		qca_soc_reg_write(QCA_SDR_CFG_REG, 1);
	}

	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* Enable DDR2 */
		qca_soc_reg_write(QCA_DDR_DDR2_CFG_REG,
						  _qca_ddr_ddr2_cfg_reg_val(1, 22, 2));
	}

	/* Precharge all */
	qca_dram_force_preall();

	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* Setup target EMR2 (full array, no dcc, no srf) */
		qca_dram_set_emr2(_ddr_sdram_emr2_val(0, 0, 0));

		/* Setup target EMR3 */
		qca_dram_set_emr3(_ddr_sdram_emr2_val(0, 0, 0));
	}

	/* Enable and reset DLL */
	qca_dram_set_emr(_ddr_sdram_emr_val(0, 1, 0, 0, 0, 0));

	qca_dram_set_mr(_ddr_sdram_mr_val(0, 0, 1, 0));

	/* Precharge all and 2x auto refresh */
	qca_dram_force_preall();

	qca_dram_force_aref();
	qca_dram_force_aref();

	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* Setup target MR (burst sequential, CAS3, wr recoery 6) */
		qca_dram_set_mr(_ddr_sdram_mr_val(0, 3, 0, 6));

		/* OCD calibration, target EMR (nDQS disable, weak strength) */
		qca_dram_set_emr(
			_ddr_sdram_emr_val(0, 1, DDR_SDRAM_EMR_OCD_DEFAULT_VAL, 1, 0, 0));

		qca_dram_set_emr(
			_ddr_sdram_emr_val(0, 1, DDR_SDRAM_EMR_OCD_EXIT_VAL,    1, 0, 0));
	} else {
		/* Setup target MR (burst sequential, CAS3) */
		qca_dram_set_mr(_ddr_sdram_mr_val(0, 3, 0, 0));
	}

	/* Enable DDR refresh and setup refresh period */
	qca_dram_set_en_refresh();

	/* AR933x supports only 16-bit memory */
	qca_soc_reg_write(QCA_DDR_RD_DATA_THIS_CYCLE_REG, 0xFF);

	ar933x_ddr_tap_tune();
}
