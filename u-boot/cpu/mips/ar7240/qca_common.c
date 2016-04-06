/*
 * Qualcomm/Atheros WiSoCs common/helper functions
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/*
 * Returns 1 if reference clock is 40 MHz
 */
u32 qca_xtal_is_40mhz(void)
{
	return ((qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG) &
			QCA_RST_BOOTSTRAP_REF_CLK_MASK) >> QCA_RST_BOOTSTRAP_REF_CLK_SHIFT);
}

/*
 * Performs full chip reset
 */
void qca_full_chip_reset(void)
{
	volatile u32 i = 1;

	do {
		qca_soc_reg_write(QCA_RST_RESET_REG,
						  QCA_RST_RESET_FULL_CHIP_RST_MASK
						  | QCA_RST_RESET_DDR_RST_MASK);
	} while (i);
}
