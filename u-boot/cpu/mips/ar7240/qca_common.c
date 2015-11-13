/*
 * Qualcomm/Atheros common/helper functions
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 *
 * Partially based on:
 * Linux/arch/mips/ath79/setup.c
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/*
 * Returns 1 if reference clock is 40 MHz
 */
inline u32 qca_xtal_is_40mhz(void)
{
	return ((qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG) &
			QCA_RST_BOOTSTRAP_REF_CLK_MASK) >> QCA_RST_BOOTSTRAP_REF_CLK_SHIFT);
}

/*
 * Return memory type value from BOOT_STRAP register
 */
inline u32 qca_mem_type(void)
{
	return ((qca_soc_reg_read(QCA_RST_BOOTSTRAP_REG) &
			QCA_RST_BOOTSTRAP_MEM_TYPE_MASK) >> QCA_RST_BOOTSTRAP_MEM_TYPE_SHIFT);
}

/*
 * Put QCA SOC name, version and revision in buffer
 */
void qca_soc_name_rev(char *buf)
{
	u32 id;
	u32 major;
	u32 rev = 0;

	/* Get revision ID value */
	id = qca_soc_reg_read(QCA_RST_REVISION_ID_REG);

	major = id & QCA_RST_REVISION_ID_MAJOR_MASK;
	rev = id & QCA_RST_REVISION_ID_REV_MASK;

	switch (major) {
#if (SOC_TYPE == QCA_AR933X_SOC)
	case QCA_RST_REVISION_ID_MAJOR_AR9330_VAL:
		sprintf(buf, "AR9330 rev. %d", rev);
		break;
	case QCA_RST_REVISION_ID_MAJOR_AR9331_VAL:
		sprintf(buf, "AR9331 rev. %d", rev);
		break;
#endif
#if (SOC_TYPE == QCA_AR9341_SOC)
	case QCA_RST_REVISION_ID_MAJOR_AR9341_VAL:
		sprintf(buf, "AR9341 rev. %d", rev);
		break;
#endif
#if (SOC_TYPE == QCA_AR9344_SOC)
	case QCA_RST_REVISION_ID_MAJOR_AR9344_VAL:
		sprintf(buf, "AR9344 rev. %d", rev);
		break;
#endif
#if (SOC_TYPE == QCA_QCA9531_SOC || SOC_TYPE == QCA_QCA9533_SOC)
	case QCA_RST_REVISION_ID_MAJOR_QCA9531_VAL:
	case QCA_RST_REVISION_ID_MAJOR_QCA9533_VAL:
		sprintf(buf, "QCA953x ver. 1 rev. %d", rev);
		break;
	case QCA_RST_REVISION_ID_MAJOR_QCA9533_V2_VAL:
		sprintf(buf, "QCA953x ver. 2 rev. %d", rev);
		break;
#endif
#if (SOC_TYPE == QCA_QCA9558_SOC)
	case QCA_RST_REVISION_ID_MAJOR_QCA9558_VAL:
		sprintf(buf, "QCA9558 rev. %d", rev);
		break;
#endif
	default:
		sprintf(buf, "Unknown");
		break;
	}
}
