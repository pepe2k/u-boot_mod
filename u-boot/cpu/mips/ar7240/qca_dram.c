/*
 * Qualcomm/Atheros WiSoCs DRAM related
 * functions for WiSoC families:
 * - Atheros AR933x
 * - Atheros AR934x
 * - Qualcomm/Atheros QCA953x
 * - Qualcomm/Atheros QCA955x
 * - Qualcomm/Atheros QCA956x
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2015-2016 Wills Wang <wills.wang@live.com>
 * Copyright (C) 2014 Qualcomm Atheros, Inc.
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>
#include <soc/qca_dram.h>

#define QCA_DDR_SIZE_INCREMENT	(8 * 1024 * 1024)

/*
 * Returns size (in bytes) of the DRAM memory
 *
 * DDR wraps around, write a pattern to 0x00000000
 * at 8M, 16M, 32M etc. and check when it gets overwritten
 */
u32 qca_dram_size(void)
{
	u8 *p = (u8 *)KSEG1;
	u8 pattern = 0x77;
	u32 i;

	*p = pattern;

	#define max_i	(QCA_DRAM_MAX_SIZE_VAL / QCA_DDR_SIZE_INCREMENT)

	for (i = 1; (i < max_i); i++) {
		*(p + i * QCA_DDR_SIZE_INCREMENT) = (u8)i;

		if (*p != pattern) {
			break;
		}
	}

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	return ((i < max_i) ?
		(i * QCA_DDR_SIZE_INCREMENT) : QCA_DRAM_MAX_SIZE_VAL);
#else
	/*
	 * TODO:
	 * something is wrong with relocation,
	 * need to fix it for boards with > 32M of RAM
	 *
	 * For now just return 1 MB smaller size
	 */
	return ((i < max_i) ?
		(i * QCA_DDR_SIZE_INCREMENT) : QCA_DRAM_MAX_SIZE_VAL) - 1024 * 1024;
#endif
}

/*
 * Return memory type value from BOOT_STRAP register
 */
u32 qca_dram_type(void)
{
#if defined(CONFIG_BOARD_DRAM_TYPE_SDR)
	#error "SDRAM is not supported!"
	return RAM_MEMORY_TYPE_SDR;
#elif defined(CONFIG_BOARD_DRAM_TYPE_DDR1)
	return RAM_MEMORY_TYPE_DDR1;
#elif defined(CONFIG_BOARD_DRAM_TYPE_DDR2)
	return RAM_MEMORY_TYPE_DDR2;
#else
	u32 dram_type;

	dram_type = ((qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG)
		      & QCA_RST_BOOTSTRAP_MEM_TYPE_MASK)
		     >> QCA_RST_BOOTSTRAP_MEM_TYPE_SHIFT);

	switch (dram_type) {
	case QCA_RST_BOOTSTRAP_MEM_TYPE_SDR_VAL:
		dram_type = RAM_MEMORY_TYPE_SDR;
		break;
	case QCA_RST_BOOTSTRAP_MEM_TYPE_DDR1_VAL:
		dram_type = RAM_MEMORY_TYPE_DDR1;
		break;
	case QCA_RST_BOOTSTRAP_MEM_TYPE_DDR2_VAL:
		dram_type = RAM_MEMORY_TYPE_DDR2;
		break;
	default:
		dram_type = RAM_MEMORY_TYPE_UNKNOWN;
		break;
	}

	return dram_type;
#endif
}

/*
 * Returns DDR width (16 or 32)
 */
u32 qca_dram_ddr_width(void)
{
#ifndef CONFIG_BOARD_DRAM_DDR_WIDTH
	#if (SOC_TYPE & QCA_AR933X_SOC)
	return 16;
	#else
	if (qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG)
	    & QCA_RST_BOOTSTRAP_DDR_WIDTH_32_MASK)
		return 32;

	return 16;
	#endif
#else
	return CONFIG_BOARD_DRAM_DDR_WIDTH;
#endif
}

/*
 * Returns CAS latency, based on setting in DDR_CONFIG register
 */
u32 qca_dram_cas_lat(void)
{
#ifndef CONFIG_BOARD_DRAM_CAS_LATENCY
	u32 reg;

	reg = (qca_soc_reg_read(QCA_DDR_CFG_REG) & QCA_DDR_CFG_CAS_3LSB_MASK)
	      >> QCA_DDR_CFG_CAS_3LSB_SHIFT;

	if (qca_soc_reg_read(QCA_DDR_CFG_REG) & QCA_DDR_CFG_CAS_MSB_MASK)
		reg = reg + 8;

	/* CAS_LATENCY value in DDR_CONFIG register == 2 * MEM_CAS */
	return reg / 2;
#else
	return CONFIG_BOARD_DRAM_CAS_LATENCY;
#endif
}

/*
 * Returns tRCD latency
 */
u32 qca_dram_trcd_lat(void)
{
	u32 reg;

	reg = (qca_soc_reg_read(QCA_DDR_CFG_REG) & QCA_DDR_CFG_TRCD_MASK)
	      >> QCA_DDR_CFG_TRCD_SHIFT;

	return reg / 2;
}

/*
 * Returns tRP latency
 */
u32 qca_dram_trp_lat(void)
{
	u32 reg;

	reg = (qca_soc_reg_read(QCA_DDR_CFG_REG) & QCA_DDR_CFG_TRP_MASK)
	      >> QCA_DDR_CFG_TRP_SHIFT;

	return reg / 2;
}

/*
 * Returns tRAS latency
 */
u32 qca_dram_tras_lat(void)
{
	u32 reg;

	reg = (qca_soc_reg_read(QCA_DDR_CFG_REG) & QCA_DDR_CFG_TRAS_MASK)
	      >> QCA_DDR_CFG_TRAS_SHIFT;

	return reg / 2;
}

/*
 * ===============================================
 * DQS delay tap controller tune related functions
 * ===============================================
 */
#define DQS_DELAY_TAP_DEFAULT_VAL	8

#if (SOC_TYPE & QCA_AR933X_SOC) |\
    (SOC_TYPE & QCA_AR934X_SOC)
	#define DQS_DELAY_TAP_MAX_VAL	62
#else
	#define DQS_DELAY_TAP_MAX_VAL	63
#endif

/*
 * Setup DQS_{0,1,2,3} delay tap control register/s
 */
static void qca_ddr_tap_save(u32 tap, u32 ddr_width)
{
#if (SOC_TYPE & QCA_AR933X_SOC) |\
    (SOC_TYPE & QCA_AR934X_SOC)
	u32 tap_h;

	/* It seems that AR93xx SoCs have two delay chains */
	if (tap > (DQS_DELAY_TAP_MAX_VAL / 2)) {
		tap_h = tap - (DQS_DELAY_TAP_MAX_VAL / 2);
		tap = tap & QCA_DDR_TAP_CTRL_TAP_L_MASK;
		tap = tap | (tap_h << QCA_DDR_TAP_CTRL_TAP_H_SHIFT);
	}
#endif

	qca_soc_reg_write(QCA_DDR_TAP_CTRL_0_REG, tap);
	qca_soc_reg_write(QCA_DDR_TAP_CTRL_1_REG, tap);

	/* Setup DQS2 and DQS3 only for 32-bit DDR interface width */
	if (ddr_width == 32) {
		qca_soc_reg_write(QCA_DDR_TAP_CTRL_2_REG, tap);
		qca_soc_reg_write(QCA_DDR_TAP_CTRL_3_REG, tap);
	}
}

/*
 * Only for AR933x we will use different code
 * for delay tap controller tune as it seems
 * that this SoC doesn't have DDR BIST.
 *
 * Below function is universal, so it should
 * work also for other QC/A WiSoCs and give
 * same (or very similar) results. The only
 * difference is that the DDR BIST based
 * version seems to be much faster.
 */
#if (SOC_TYPE & QCA_AR933X_SOC)

	#define DQS_DELAY_TAP_PATTERN_OFFSET	0x2000
	#define DQS_DELAY_TAP_PATTERN_SIZE	0x1000
	#define DQS_DELAY_TAP_TEST_LOOPS	2

/*
 * Prepare pattern for further tests
 */
static inline void qca_ddr_tap_patt(void)
{
	u32 i, j, pat;
	u32 *addr;

	/* Prepare 4M (256 x 4 x 4 bytes) pattern */
	addr = (void *)KSEG1ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);

	for (i = 0; i < 256; i++) {
		pat = 0;

		for (j = 0; j < 8; j++) {
			if (i & (1 << j)) {
				if (j % 2)
					pat |= 0xFFFF0000;
				else
					pat |= 0x0000FFFF;
			}

			if (j % 2) {
				*addr++ = pat;
				pat = 0;
			}
		}
	}
}

/*
 * This function is a modified C version of the original
 * ar933x_ddr_tap_init() function, written in asm,
 * included in Atheros (Q)SDK code.
 *
 * Below is a modified version, partially based on:
 * https://patchwork.ozlabs.org/patch/569046/
 */
static void qca_ddr_tap_tune(u32 ddr_width)
{
	u32 *addr, *addr_k0, *addr_k1;
	u32 tap, tap_hi, tap_lo;
	u32 err, got_lo, i;

	/* Pattern */
	qca_ddr_tap_patt();

	got_lo = 0;
	tap_hi = 0;
	tap_lo = 0;

	addr = (void *)KSEG1ADDR(DQS_DELAY_TAP_PATTERN_OFFSET
				 + DQS_DELAY_TAP_PATTERN_SIZE);

	/*
	 * Idea here is to test all possible tap values, one by one,
	 * starting from the lowest. We are looking for a range within
	 * the written and read back data is the same. We assume here
	 * that the valid tap range is continuous.
	 *
	 * From hardware POV, delay tap controller is used to adjust
	 * the data window.
	 */
	for (tap = 0; tap <= DQS_DELAY_TAP_MAX_VAL; tap++) {
		qca_ddr_tap_save(tap, ddr_width);

		err = 0;

		for (i = 0; i < DQS_DELAY_TAP_TEST_LOOPS; i++) {
			addr_k1 = (void *)KSEG1ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);
			addr_k0 = (void *)KSEG0ADDR(DQS_DELAY_TAP_PATTERN_OFFSET);

			while (addr_k1 < addr) {
				if (*addr_k1++ != *addr_k0++) {
					err = 1;
					break;
				}
			}

			if (err)
				break;
		}

		if (err) {
			if (got_lo) {
				if (tap > 0)
					tap_hi = tap - 1;

				break;
			}
		} else {
			if (!got_lo) {
				tap_lo = tap;
				got_lo = 1;
			} else {
				tap_hi = tap;
			}
		}
	}

	/* Calculate final tap value (rounded up average) */
	if (got_lo) {
		tap = (tap_hi + tap_lo + 1) / 2;
	} else {
		tap = DQS_DELAY_TAP_DEFAULT_VAL;
	}

	qca_ddr_tap_save(tap, ddr_width);
}

#else /* SOC_TYPE & QCA_AR933X_SOC */

	#define DQS_DELAY_TAP_TEST_LOOPS	8

/*
 * Unknown magic values and registers from Atheros (Q)SDK.
 *
 * It looks like some test patterns and masks setup,
 * but it's not confirmed. Used here values are
 * different, but were tested on real hardware.
 */
static inline void qca_ddr_tap_bist_init(void)
{
	qca_soc_reg_write(QCA_DDR_PERF_COMP_AHB_GE0_0_REG, 0xAAAAAAAA);
	qca_soc_reg_write(QCA_DDR_PERF_MASK_AHB_GE0_0_REG, 0xAAAAAAAA);

	qca_soc_reg_write(QCA_DDR_PERF_COMP_AHB_GE0_1_REG, 0x55555555);
	qca_soc_reg_write(QCA_DDR_PERF_MASK_AHB_GE0_1_REG, 0x55555555);

	qca_soc_reg_write(QCA_DDR_PERF_COMP_AHB_GE1_0_REG, 0xAAAAAAAA);
	qca_soc_reg_write(QCA_DDR_PERF_MASK_AHB_GE1_0_REG, 0xAAAAAAAA);

	qca_soc_reg_write(QCA_DDR_PERF_COMP_AHB_GE1_1_REG, 0x55555555);
	qca_soc_reg_write(QCA_DDR_PERF_MASK_AHB_GE1_1_REG, 0x55555555);
}

/*
 * This function is a modified C version of the original
 * ath_ddr_tap_cal() function, written in asm,
 * included in Atheros (Q)SDK code.
 *
 * It seems that newer QC/A WiSoCs have some kind of
 * built-in self-test (BIST) for DDR controller, but
 * none of the used registers or their values are
 * described in datasheets, so for now, we will just
 * use them as in original code.
 *
 * Below is a modified version, partially based on:
 * https://patchwork.ozlabs.org/patch/569047/
 */
static void qca_ddr_tap_tune(u32 ddr_width)
{
	u32 tap, tap_hi, tap_lo;
	u32 fail, got_lo, reg;

	got_lo = 0;
	tap_hi = 0;
	tap_lo = 0;

	/* How many test loops per tested tap value */
	qca_soc_reg_write(QCA_DDR_PERF_COMP_ADDR_1_REG,
			  (DQS_DELAY_TAP_TEST_LOOPS
			   << QCA_DDR_PERF_COMP_ADDR_1_TEST_CNT_SHIFT));

	/*
	 * Unknown magic value, original comment:
	 * "4 Row Address Bits, 4 Column Address Bits, 2 BA bits"
	 */
	qca_soc_reg_write(QCA_DDR_PERF_MASK_ADDR_0_REG, 0xFA5DE83F);

	/*
	 * Test all possible tap values, try to find working range
	 * (minimum and maximum delays) and use average value
	 */
	for (tap = 0; tap <= DQS_DELAY_TAP_MAX_VAL; tap++) {
		qca_ddr_tap_save(tap, ddr_width);

		qca_ddr_tap_bist_init();

		/* Enable BIST test and wait for finish */
		qca_soc_reg_write(QCA_DDR_BIST_REG, QCA_DDR_BIST_TEST_EN_MASK);

		do {
			reg = qca_soc_reg_read(QCA_DDR_BIST_STATUS_REG);
		} while (!(reg & QCA_DDR_BIST_STATUS_DONE_MASK));

		/* Disable BIST test */
		qca_soc_reg_write(QCA_DDR_BIST_REG, 0);

		/* Check how many tests failed */
		fail = (reg & QCA_DDR_BIST_STATUS_FAIL_CNT_MASK)
		       >> QCA_DDR_BIST_STATUS_FAIL_CNT_SHIFT;

		if (fail == 0) {
			if (!got_lo) {
				tap_lo = tap;
				got_lo = 1;
			} else {
				tap_hi = tap;
			}
		} else {
			if (got_lo) {
				if (tap > 0)
					tap_hi = tap - 1;

				break;
			}
		}
	}

	/* Calculate final tap value (rounded up average) */
	if (got_lo) {
		tap = (tap_hi + tap_lo + 1) / 2;
	} else {
		tap = DQS_DELAY_TAP_DEFAULT_VAL;
	}

	qca_ddr_tap_save(tap, ddr_width);
}

#endif /* SOC_TYPE & QCA_AR933X_SOC */

/*
 * ===============================================
 * DDR controller initialization related functions
 * ===============================================
 */

/*
 * Below defines are "safe" DDR1/DDR2 timing parameters.
 * They should work for most chips, but not for all.
 *
 * For different values, user can define target value
 * of all memory controller related registers.
 *
 */
#define DDRx_tMRD_ns	10
#define DDRx_tRAS_ns	40
#define DDRx_tRCD_ns	15
#define DDRx_tRP_ns	15
#define DDRx_tRRD_ns	10
#define DDRx_tWR_ns	15
#define DDRx_tWTR_ns	10

#define DDR1_tRFC_ns	75
#define DDR2_tRFC_ns	120

#define DDR2_tFAW_ns	50
#define DDR2_tWL_ns	5

#define DDR_addit_lat	0
#define DDR_burst_len	8

/* All above values are safe for clocks not lower than below values */
#define DDR1_timing_clk_max	400
#define DDR2_timing_clk_max	533

/* Maximum timing values, based on register fields sizes */
#define MAX_tFAW	BITS(0, 6)
#define MAX_tMRD	BITS(0, 4)
#define MAX_tRAS	BITS(0, 5)
#define MAX_tRCD	BITS(0, 4)
#define MAX_tRFC	BITS(0, 6)
#define MAX_tRP		BITS(0, 4)
#define MAX_tRRD	BITS(0, 4)
#define MAX_tRTP	BITS(0, 4)
#define MAX_tRTW	BITS(0, 5)
#define MAX_tWL		BITS(0, 4)
#define MAX_tWR		BITS(0, 4)
#define MAX_tWTR	BITS(0, 5)

/*
 * Setup DDR_CONFIG register
 */
static inline void qca_dram_set_ddr_cfg(u32 mem_cas,
					u32 ddr_clk,
					u32 mem_type)
{
#ifndef CONFIG_QCA_DDR_CFG_REG_VAL
	u32 reg = 0;
	u32 tmp = 0;

	reg = qca_soc_reg_read(QCA_DDR_CFG_REG);

	/* Always use page close policy */
	reg = reg | QCA_DDR_CFG_PAGE_CLOSE_MASK;

	/* CAS should be (2 * MEM_CAS) or (2 * MEM_CAS) + 1/2/3 */
	tmp = 2 * mem_cas;
	tmp = (tmp << QCA_DDR_CFG_CAS_3LSB_SHIFT) & QCA_DDR_CFG_CAS_3LSB_MASK;
	if (mem_cas > 3) {
		tmp = tmp | QCA_DDR_CFG_CAS_MSB_MASK;
	}

	reg = reg & ~QCA_DDR_CFG_CAS_3LSB_MASK;
	reg = reg | tmp;

	/*
	 * Calculate rest of timing related values,
	 * always round up to closest integer
	 */

	/* tMRD */
	tmp = ((DDRx_tMRD_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tMRD)
		tmp = MAX_tMRD;

	tmp = (tmp << QCA_DDR_CFG_TMRD_SHIFT) & QCA_DDR_CFG_TMRD_MASK;
	reg = reg & ~QCA_DDR_CFG_TMRD_MASK;
	reg = reg | tmp;

	/* tRFC */
	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		tmp = ((DDR2_tRFC_ns * ddr_clk) + 500) / 1000;
	} else {
		tmp = ((DDR1_tRFC_ns * ddr_clk) + 500) / 1000;
	}

	if (tmp > MAX_tRFC)
		tmp = MAX_tRFC;

	tmp = (tmp << QCA_DDR_CFG_TRFC_SHIFT) & QCA_DDR_CFG_TRFC_MASK;
	reg = reg & ~QCA_DDR_CFG_TRFC_MASK;
	reg = reg | tmp;

	/* tRRD */
	tmp = ((DDRx_tRRD_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tRRD)
		tmp = MAX_tRRD;

	tmp = (tmp << QCA_DDR_CFG_TRRD_SHIFT) & QCA_DDR_CFG_TRRD_MASK;
	reg = reg & ~QCA_DDR_CFG_TRRD_MASK;
	reg = reg | tmp;

	/* tRP */
	tmp = ((DDRx_tRP_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tRP)
		tmp = MAX_tRP;

	tmp = (tmp << QCA_DDR_CFG_TRP_SHIFT) & QCA_DDR_CFG_TRP_MASK;
	reg = reg & ~QCA_DDR_CFG_TRP_MASK;
	reg = reg | tmp;

	/* tRCD */
	tmp = ((DDRx_tRCD_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tRCD)
		tmp = MAX_tRCD;

	tmp = (tmp << QCA_DDR_CFG_TRCD_SHIFT) & QCA_DDR_CFG_TRCD_MASK;
	reg = reg & ~QCA_DDR_CFG_TRCD_MASK;
	reg = reg | tmp;

	/* tRAS */
	tmp = ((DDRx_tRAS_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tRAS)
		tmp = MAX_tRAS;

	tmp = (tmp << QCA_DDR_CFG_TRAS_SHIFT) & QCA_DDR_CFG_TRAS_MASK;
	reg = reg & ~QCA_DDR_CFG_TRAS_MASK;
	reg = reg | tmp;

	qca_soc_reg_write(QCA_DDR_CFG_REG, reg);
#else
	qca_soc_reg_write(QCA_DDR_CFG_REG, CONFIG_QCA_DDR_CFG_REG_VAL);
#endif
}

/*
 * Setup DDR_CONFIG2 register
 */
static inline void qca_dram_set_ddr_cfg2(u32 mem_cas,
					 u32 ddr_clk,
					 u32 mem_type,
					 u32 ddr_width)
{
#ifndef CONFIG_QCA_DDR_CFG2_REG_VAL
	u32 reg = 0;
	u32 tmp = 0;

	reg = qca_soc_reg_read(QCA_DDR_CFG2_REG);

	/* Enable CKE */
	reg = reg | QCA_DDR_CFG2_CKE_MASK;

	/* Gate open latency = 2 * MEM_CAS */
	tmp = 2 * mem_cas;
	tmp = (tmp << QCA_DDR_CFG2_GATE_OPEN_LATENCY_SHIFT)
	      & QCA_DDR_CFG2_GATE_OPEN_LATENCY_MASK;
	reg = reg & ~QCA_DDR_CFG2_GATE_OPEN_LATENCY_MASK;
	reg = reg | tmp;

	/* tWTR */
	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* tWTR = 2 * WL + BL + 2 * max(tWTR/tCK, 2) */
		tmp = 2 * (mem_cas + DDR_addit_lat - 1) + DDR_burst_len + 4;

		if (ddr_clk >= 600)
			tmp = tmp + 2;
	} else {
		/* tWTR = 2 + BL + (2 * tWTR/tCK) */
		tmp = 2 + DDR_burst_len
			+ (((DDRx_tWTR_ns * ddr_clk) + 500) / 1000);
	}

	if (tmp > MAX_tWTR)
		tmp = MAX_tWTR;

	tmp = (tmp << QCA_DDR_CFG2_TWTR_SHIFT) & QCA_DDR_CFG2_TWTR_MASK;
	reg = reg & ~QCA_DDR_CFG2_TWTR_MASK;
	reg = reg | tmp;

	/* tRTP */
	if (ddr_width == 32) {
		tmp = DDR_burst_len;
	} else {
		tmp = MAX_tRTP;
	}

	tmp = (tmp << QCA_DDR_CFG2_TRTP_SHIFT) & QCA_DDR_CFG2_TRTP_MASK;
	reg = reg & ~QCA_DDR_CFG2_TRTP_MASK;
	reg = reg | tmp;

	/* tRTW */
	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* tRTW = 2 * (RL + BL/2 + 1 -WL), RL = CL + AL, WL = RL - 1 */
		tmp = DDR_burst_len + 4;
	} else {
		/* tRTW = 2 * (CL + BL/2) */
		tmp = DDR_burst_len + (2 * mem_cas);
	}

	if (tmp > MAX_tRTW)
		tmp = MAX_tRTW;

	tmp = (tmp << QCA_DDR_CFG2_TRTW_SHIFT) & QCA_DDR_CFG2_TRTW_MASK;
	reg = reg & ~QCA_DDR_CFG2_TRTW_MASK;
	reg = reg | tmp;

	/* tWR */
	tmp = ((DDRx_tWR_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tWR)
		tmp = MAX_tWR;

	tmp = (tmp << QCA_DDR_CFG2_TWR_SHIFT) & QCA_DDR_CFG2_TWR_MASK;
	reg = reg & ~QCA_DDR_CFG2_TWR_MASK;
	reg = reg | tmp;

	/* Always use burst length = 8 and type: sequential */
	tmp = (DDR_burst_len << QCA_DDR_CFG2_BURST_LEN_SHIFT)
	      & QCA_DDR_CFG2_BURST_LEN_MASK;
	reg = reg & ~(QCA_DDR_CFG2_BURST_LEN_MASK
		      | QCA_DDR_CFG2_BURST_TYPE_MASK);
	reg = reg | tmp;

	qca_soc_reg_write(QCA_DDR_CFG2_REG, reg);
#else
	qca_soc_reg_write(QCA_DDR_CFG2_REG, CONFIG_QCA_DDR_CFG2_REG_VAL);
#endif
}

/*
 * Setup DDR2_CONFIG register (only for DDR2)
 */
static inline void qca_dram_set_ddr2_cfg(u32 mem_cas,
					 u32 ddr_clk)
{
#ifndef CONFIG_QCA_DDR_DDR2_CFG_REG_VAL
	u32 reg = 0;
	u32 tmp = 0;

	reg = qca_soc_reg_read(QCA_DDR_DDR2_CFG_REG);

	/* Enable DDR2 */
	reg = reg | QCA_DDR_DDR2_CFG_DDR2_EN_MASK;

	/* tFAW */
	tmp = ((DDR2_tFAW_ns * ddr_clk) + 500) / 1000;
	if (tmp > MAX_tFAW)
		tmp = MAX_tFAW;

	tmp = (tmp << QCA_DDR_DDR2_CFG_DDR2_TFAW_SHIFT)
	      & QCA_DDR_DDR2_CFG_DDR2_TFAW_MASK;
	reg = reg & ~QCA_DDR_DDR2_CFG_DDR2_TFAW_MASK;
	reg = reg | tmp;

	/* tWL */
	tmp = (2 * mem_cas) - 3;

	/* For some reason, odd value doesn't work on AR933x (FIXME) */
	#if (SOC_TYPE & QCA_AR933X_SOC)
	if (tmp % 2)
		tmp = tmp - 1;
	#endif

	tmp = (tmp << QCA_DDR_DDR2_CFG_DDR2_TWL_SHIFT)
	      & QCA_DDR_DDR2_CFG_DDR2_TWL_MASK;
	reg = reg & ~QCA_DDR_DDR2_CFG_DDR2_TWL_MASK;
	reg = reg | tmp;

	qca_soc_reg_write(QCA_DDR_DDR2_CFG_REG, reg);
#else
	qca_soc_reg_write(QCA_DDR_DDR2_CFG_REG,
			  CONFIG_QCA_DDR_DDR2_CFG_REG_VAL);
#endif
}

/*
 * Enables DDR refresh and sets
 * refresh period based on XTAL
 */
static inline void qca_dram_set_en_refresh(void)
{
	/*
	 * Enable DDR refresh and setup refresh period:
	 * 1. We assume 7.8 us maximum average period refresh interval
	 * 2. 7.8 us ~= 0.1282 MHz
	 * 3. For 25 MHz XTAL: (25 / 0.1282) ~= 195
	 * 4. For 40 MHz XTAL: (40 / 0.1282) ~= 312
	 */
	if (qca_xtal_is_40mhz()) {
		qca_soc_reg_write(QCA_DDR_REFRESH_REG,
				  QCA_DDR_REFRESH_EN_MASK
				  | (312 << QCA_DDR_REFRESH_PERIOD_SHIFT));
	} else {
		qca_soc_reg_write(QCA_DDR_REFRESH_REG,
				  QCA_DDR_REFRESH_EN_MASK
				  | (195 << QCA_DDR_REFRESH_PERIOD_SHIFT));
	}
}

/*
 * Initial DRAM configuration
 */
void qca_dram_init(void)
{
	u32 ahb_clk, cpu_clk, ddr_clk, mem_type, tmp_clk;
	u32 cas_lat, ddr_width, reg, tmp, wr_recovery;

	mem_type = qca_dram_type();

	qca_sys_clocks(&cpu_clk, &ddr_clk, &ahb_clk, NULL, NULL);
	cpu_clk = cpu_clk / 1000000;
	ddr_clk = ddr_clk / 1000000;
	ahb_clk = ahb_clk / 1000000;

	/* Set CAS based on clock, but allow to set static value */
#ifndef CONFIG_BOARD_DRAM_CAS_LATENCY
	if (mem_type == RAM_MEMORY_TYPE_DDR1) {
		if (ddr_clk <= 266) {
			cas_lat = 2;
		} else {
			cas_lat = 3;
		}
	} else {
		if (ddr_clk <= 400) {
			cas_lat = 3;
		} else if (ddr_clk <= 533) {
			cas_lat = 4;
		} else if (ddr_clk <= 666) {
			cas_lat = 5;
		} else if (ddr_clk <= 800) {
			cas_lat = 6;
		} else {
			cas_lat = 7;
		}
	}
#else
	cas_lat = CONFIG_BOARD_DRAM_CAS_LATENCY;
#endif

#if (SOC_TYPE & QCA_AR933X_SOC)
	/* AR933x supports only 16-bit memory */
	ddr_width = 16;
	qca_soc_reg_write(QCA_DDR_RD_DATA_THIS_CYCLE_REG, 0xFF);
#else
	/* For other WiSoCs we can determine DDR width, based on bootstrap */
	ddr_width = qca_dram_ddr_width();

	if (ddr_width == 32) {
		/* For 32-bit clear HALF_WIDTH and set VEC = 0xFF */
		qca_soc_reg_read_clear(QCA_DDR_CTRL_CFG_REG,
				       QCA_DDR_CTRL_CFG_HALF_WIDTH_MASK);

		qca_soc_reg_write(QCA_DDR_RD_DATA_THIS_CYCLE_REG, 0xFF);
	} else {
		qca_soc_reg_read_set(QCA_DDR_CTRL_CFG_REG,
				     QCA_DDR_CTRL_CFG_HALF_WIDTH_MASK);

		qca_soc_reg_write(QCA_DDR_RD_DATA_THIS_CYCLE_REG, 0xFFFF);
	}

	/* If DDR_CLK < 2 * AHB_CLK, set DDR FSM wait control to 0xA24 */
	if (ddr_clk < (2 * ahb_clk))
		qca_soc_reg_write(QCA_DDR_FSM_WAIT_CTRL_REG, 0xA24);

	/* If CPU clock < AHB clock, set SRAM REQ ACK */
	if (cpu_clk < ahb_clk)
		qca_soc_reg_read_set(QCA_DDR_CTRL_CFG_REG,
				     QCA_DDR_CTRL_CFG_SRAM_REQ_ACK_MASK);
	else
		qca_soc_reg_read_clear(QCA_DDR_CTRL_CFG_REG,
				       QCA_DDR_CTRL_CFG_SRAM_REQ_ACK_MASK);
#endif

	/*
	 * CPU/DDR sync mode only when we don't use
	 * fractional multipliers in PLL/clocks config
	 */
	tmp = 0;

#if (SOC_TYPE & QCA_AR933X_SOC)
	reg = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_FRAC_REG);
	reg = (reg & QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK)
	      >> QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_SHIFT;

	if (reg)
		tmp = 1;
#else
	reg = qca_soc_reg_read(QCA_PLL_CPU_PLL_DITHER_REG);
	reg = (reg & QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK)
	      >> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_SHIFT;

	if (reg)
		tmp = 1;

	reg = qca_soc_reg_read(QCA_PLL_DDR_PLL_DITHER_REG);
	reg = (reg & QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK)
	      >> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_SHIFT;

	if (reg)
		tmp = 1;
#endif

	if (!tmp && (cpu_clk == ddr_clk)) {
#if (SOC_TYPE & QCA_AR933X_SOC)
		qca_soc_reg_read_set(QCA_DDR_TAP_CTRL_3_REG, (1 << 8));
#else
		qca_soc_reg_read_set(QCA_DDR_CTRL_CFG_REG,
				     QCA_DDR_CTRL_CFG_CPU_DDR_SYNC_MASK);
#endif
	} else {
#if (SOC_TYPE & QCA_AR933X_SOC)
		qca_soc_reg_read_clear(QCA_DDR_TAP_CTRL_3_REG, (1 << 8));
#else
		qca_soc_reg_read_clear(QCA_DDR_CTRL_CFG_REG,
				       QCA_DDR_CTRL_CFG_CPU_DDR_SYNC_MASK);
#endif
	}

	/* Check if clock is not too low for our "safe" timing values */
	tmp_clk = ddr_clk;
	if (mem_type == RAM_MEMORY_TYPE_DDR1) {
		if (tmp_clk < DDR1_timing_clk_max)
			tmp_clk = DDR1_timing_clk_max;
	} else {
		if (tmp_clk < DDR2_timing_clk_max)
			tmp_clk = DDR2_timing_clk_max;
	}

	/* Enable DDR2 */
#if (SOC_TYPE & QCA_AR933X_SOC)
	if (mem_type == RAM_MEMORY_TYPE_DDR2)
		qca_dram_set_ddr2_cfg(cas_lat, tmp_clk);
#else
	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		qca_soc_reg_read_set(QCA_DDR_CTRL_CFG_REG,
				     QCA_DDR_CTRL_CFG_PAD_DDR2_SEL_MASK);

		qca_dram_set_ddr2_cfg(cas_lat, tmp_clk);
	} else {
		qca_soc_reg_read_clear(QCA_DDR_CTRL_CFG_REG,
				       QCA_DDR_CTRL_CFG_PAD_DDR2_SEL_MASK);
	}
#endif

	/* Setup DDR timing related registers */
	qca_dram_set_ddr_cfg(cas_lat, tmp_clk, mem_type);
	qca_dram_set_ddr_cfg2(cas_lat, tmp_clk, mem_type, ddr_width);

	/* Precharge all */
	qca_dram_force_preall();

	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* Setup target EMR2 and EMR3 */
		qca_dram_set_emr2(_ddr_sdram_emr2_val(0, 0, 0));
		qca_dram_set_emr3(0);
	}

	/* Enable and reset DLL */
	qca_dram_set_emr(_ddr_sdram_emr_val(0, 1, 0, 0, 0, 0));
	qca_dram_set_mr(_ddr_sdram_mr_val(0, 0, 1, 0));

	/* Precharge all, 2x auto refresh */
	qca_dram_force_preall();

	qca_dram_force_aref();
	qca_dram_force_aref();

	if (mem_type == RAM_MEMORY_TYPE_DDR2) {
		/* Setup target MR */
		wr_recovery = ((DDRx_tWR_ns * tmp_clk) + 1000) / 2000;
		qca_dram_set_mr(_ddr_sdram_mr_val(0, cas_lat, 0, wr_recovery));

		/* OCD calibration, target EMR (nDQS disable, weak strength) */
		qca_dram_set_emr(
			_ddr_sdram_emr_val(0, 1, DDR_SDRAM_EMR_OCD_DEFAULT_VAL,
					   1, 0, 0));

		qca_dram_set_emr(
			_ddr_sdram_emr_val(0, 1, DDR_SDRAM_EMR_OCD_EXIT_VAL,
					   1, 0, 0));
	} else {
		/* Setup target MR */
		qca_dram_set_mr(_ddr_sdram_mr_val(0, cas_lat, 0, 0));
	}

	/* Enable DDR refresh and setup refresh period */
	qca_dram_set_en_refresh();

	/*
	 * At this point memory should be fully configured,
	 * so we can perform delay tap controller tune.
	 */
	qca_ddr_tap_tune(ddr_width);
}
