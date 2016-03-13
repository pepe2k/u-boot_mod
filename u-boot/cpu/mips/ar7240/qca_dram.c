/*
 * Qualcomm/Atheros WiSoCs DRAM related common functions
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
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
	return RAM_MEMORY_TYPE_SDR;
#elif defined(CONFIG_BOARD_DRAM_TYPE_DDR1)
	return RAM_MEMORY_TYPE_DDR1;
#elif defined(CONFIG_BOARD_DRAM_TYPE_DDR2)
	return RAM_MEMORY_TYPE_DDR2;
#else
	u32 dram_type;

	dram_type = ((qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG)
				 & QCA_RST_BOOTSTRAP_MEM_TYPE_MASK) >> QCA_RST_BOOTSTRAP_MEM_TYPE_SHIFT);

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
	if (qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG)
		& QCA_RST_BOOTSTRAP_DDR_WIDTH_32_MASK)
		return 32;

	return 16;
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
	return CONFIG_BOARD_DRAM_CAS_LATENCY
#endif
}
