/*
 * Qualcomm/Atheros Serial SPI FLASH driver utilizing SHIFT registers
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <flash.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/* Use CS0 by default */
static u32 qca_sf_cs_mask = QCA_SPI_SHIFT_CNT_CHNL_CS0_MASK;

static inline void qca_sf_spi_en(void)
{
	qca_soc_reg_write(QCA_SPI_FUNC_SEL_REG, 1);
}

static inline void qca_sf_spi_di(void)
{
	qca_soc_reg_write(QCA_SPI_SHIFT_CNT_REG, 0);
	qca_soc_reg_write(QCA_SPI_FUNC_SEL_REG, 0);
}

static inline u32 qca_sf_shift_in(void)
{
	return qca_soc_reg_read(QCA_SPI_SHIFT_DATAIN_REG);
}

/*
 * Shifts out 'bits_cnt' bits from 'data_out' value
 * If 'terminate' is zero, then CS is not driven high at end of transaction
 */
static void qca_sf_shift_out(u32 data_out, u32 bits_cnt, u32 terminate)
{
	u32 reg_val = 0;

	qca_soc_reg_write(QCA_SPI_SHIFT_CNT_REG, 0);

	/* Data to shift out */
	qca_soc_reg_write(QCA_SPI_SHIFT_DATAOUT_REG, data_out);

	reg_val = reg_val | bits_cnt
					  | qca_sf_cs_mask
					  | QCA_SPI_SHIFT_CNT_SHIFT_EN_MASK;

	if (terminate)
		reg_val = reg_val | QCA_SPI_SHIFT_CNT_TERMINATE_MASK;

	/* Enable shifting in/out */
	qca_soc_reg_write(QCA_SPI_SHIFT_CNT_REG, reg_val);
}

static u32 qca_sf_sfdp_bfpt_dword(u32 ptp_offset, u32 dword_num)
{
	u32 data_out;

	data_out = (SPI_FLASH_CMD_SFDP << 24);
	data_out = data_out | (ptp_offset + ((dword_num - 1) * 4));

	qca_sf_shift_out(data_out, 32, 0);
	qca_sf_shift_out(0x0, 40, 1);

	return cpu_to_le32(qca_sf_shift_in());
}

static inline void qca_sf_write_en(void)
{
	qca_sf_shift_out(SPI_FLASH_CMD_WREN, 8, 1);
}

static inline void qca_sf_write_di(void)
{
	qca_sf_shift_out(SPI_FLASH_CMD_WRDI, 8, 1);
}

static void qca_sf_bank_to_cs_mask(u32 bank)
{
	switch (bank) {
	case 0:
		qca_sf_cs_mask = QCA_SPI_SHIFT_CNT_CHNL_CS0_MASK;
		break;
	case 1:
		qca_sf_cs_mask = QCA_SPI_SHIFT_CNT_CHNL_CS1_MASK;
		break;
	case 2:
		qca_sf_cs_mask = QCA_SPI_SHIFT_CNT_CHNL_CS2_MASK;
		break;
	default:
		qca_sf_cs_mask = QCA_SPI_SHIFT_CNT_CHNL_CS0_MASK;
		break;
	}
}

/* Poll status register and wait till busy bit is cleared */
static void qca_sf_busy_wait(void)
{
	volatile u32 data_in;

	/* Poll status register continuously (keep CS low during whole loop) */
	qca_sf_shift_out(SPI_FLASH_CMD_RDSR, 8, 0);

	do {
		qca_sf_shift_out(0x0, 8, 0);
		data_in = qca_sf_shift_in() & 0x1;
	} while (data_in);

	/* Disable CS chip */
	qca_sf_shift_out(0x0, 0, 1);
}

/* Bulk (whole) FLASH erase */
void qca_sf_bulk_erase(u32 bank)
{
	qca_sf_bank_to_cs_mask(bank);
	qca_sf_spi_en();
	qca_sf_write_en();
	qca_sf_shift_out(SPI_FLASH_CMD_ES_ALL, 8, 1);
	qca_sf_busy_wait();
	qca_sf_spi_di();
}

/* Erase one sector at provided address */
u32 qca_sf_sect_erase(u32 bank, u32 address, u32 sect_size, u8 erase_cmd)
{
	u32 data_out;

	qca_sf_bank_to_cs_mask(bank);

	/* TODO: 4-byte addressing support */
	data_out = (erase_cmd << 24) | (address & 0x00FFFFFF);

	qca_sf_spi_en();
	qca_sf_write_en();
	qca_sf_shift_out(data_out, 32, 1);
	qca_sf_busy_wait();
	qca_sf_spi_di();

	return 0;
}

/* Writes 'length' bytes at 'address' using page program command */
void qca_sf_write_page(u32 bank, u32 address, u32 length, u8 *data)
{
	u32 data_out, i;

	qca_sf_bank_to_cs_mask(bank);

	data_out = SPI_FLASH_CMD_PP << 24;
	data_out = data_out | (address & 0x00FFFFFF);

	qca_sf_spi_en();
	qca_sf_write_en();
	qca_sf_shift_out(data_out, 32, 0);

	length--;
	for (i = 0; i < length; i++) {
		qca_sf_shift_out(*(data + i), 8, 0);
	}

	/* Last byte and terminate */
	qca_sf_shift_out(*(data + i), 8, 1);

	qca_sf_busy_wait();
	qca_sf_spi_di();
}

/*
 * Checks if FLASH supports SFDP and if yes, tries to get following data:
 * - chip size
 * - erase sector size
 * - erase command
 */
u32 qca_sf_sfdp_info(u32 bank,
					 u32 *flash_size,
					 u32 *sect_size,
					 u8  *erase_cmd)
{
	u8 buffer[12];
	u8 ss = 0, ec = 0;
	u32 data_in, i;
	u32 ptp_length, ptp_offset;

	qca_sf_bank_to_cs_mask(bank);

	qca_sf_spi_en();

	/* Shift out SFDP command with 0x0 address */
	qca_sf_shift_out(SPI_FLASH_CMD_SFDP << 24, 32, 0);

	/* 1 dummy byte and 4 bytes for SFDP signature */
	qca_sf_shift_out(0x0, 40, 0);
	data_in = qca_sf_shift_in();

	if (cpu_to_le32(data_in) != SPI_FLASH_SFDP_SIGN) {
		qca_sf_shift_out(0x0, 0, 1);
		qca_sf_spi_di();
		return 1;
	}

	/*
	 * We need to check SFDP and first parameter header major versions,
	 * because we support now only v1, exit also if ptp_length is < 9
	 */
	for (i = 0; i < 3; i++) {
		qca_sf_shift_out(0x0, 32, 0);
		data_in = qca_sf_shift_in();

		memcpy(&buffer[i * 4], &data_in, 4);
	}

	ptp_length = buffer[7];
	ptp_offset = buffer[8] | (buffer[10] << 16) | (buffer[9] << 8);

	if (buffer[1] != 1 || buffer[6] != 1 || ptp_length < 9) {
		qca_sf_shift_out(0x0, 0, 1);
		qca_sf_spi_di();
		return 1;
	}

	qca_sf_shift_out(0x0, 0, 1);

	/* FLASH density (2nd DWORD in JEDEC basic FLASH parameter table) */
	data_in = qca_sf_sfdp_bfpt_dword(ptp_offset, 2);

	/* We do not support >= 4 Gbits chips */
	if ((data_in & (1 << 31)) || data_in == 0)
		return 1;

	/* TODO: it seems that density is 0-based, like max. available address? */
	if (flash_size != NULL)
		*flash_size = ((data_in & 0x7FFFFFFF) + 1) / 8;

	/* Sector/block erase size and command: 8th and 9th DWORD */
	data_in = qca_sf_sfdp_bfpt_dword(ptp_offset, 8);
	memcpy(&buffer[0], &data_in, 4);

	data_in = qca_sf_sfdp_bfpt_dword(ptp_offset, 9);
	memcpy(&buffer[4], &data_in, 4);

	/* We prefer bigger erase sectors */
	for (i = 0; i < 7; i += 2) {
		if ((buffer[i + 1] != 0) && buffer[i + 1] > ss) {
			ss = buffer[i + 1];
			ec = buffer[i];
		}
	}

	if (ss == 0)
		return 1;

	if (sect_size != NULL)
		*sect_size = 1 << ss;

	if (erase_cmd != NULL)
		*erase_cmd = ec;

	qca_sf_spi_di();

	return 0;
}

/* Returns JEDEC ID for selected FLASH chip */
u32 qca_sf_jedec_id(u32 bank)
{
	u32 data_in;

	qca_sf_bank_to_cs_mask(bank);

	qca_sf_spi_en();
	qca_sf_shift_out(SPI_FLASH_CMD_JEDEC << 24, 32, 1);
	data_in = qca_sf_shift_in();
	qca_sf_spi_di();

	return (data_in & 0x00FFFFFF);
}
