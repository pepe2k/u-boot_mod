/*
 * Qualcomm/Atheros Serial SPI FLASH driver utilizing SHIFT registers
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

/* Basic SPI FLASH commands */
#define SPI_FLASH_CMD_WRSR		0x01
#define SPI_FLASH_CMD_PP		0x02
#define SPI_FLASH_CMD_READ		0x03
#define SPI_FLASH_CMD_WRDI		0x04
#define SPI_FLASH_CMD_RDSR		0x05
#define SPI_FLASH_CMD_WREN		0x06

/* SPI FLASH erase related commands */
#define SPI_FLASH_CMD_ES_4KB	0x20
#define SPI_FLASH_CMD_ES_32KB	0x52
#define SPI_FLASH_CMD_ES_64KB	0xD8
#define SPI_FLASH_CMD_ES_ALL	0xC7

/* Other SPI FLASH commands */
#define SPI_FLASH_CMD_JEDEC		0x9F

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
u32 qca_sf_sect_erase(u32 bank, u32 address, u32 sect_size)
{
	u32 data_out;

	qca_sf_bank_to_cs_mask(bank);

	switch (sect_size) {
	case 4 * 1024:
		data_out = SPI_FLASH_CMD_ES_4KB << 24;
		break;
	case 32 * 1024:
		data_out = SPI_FLASH_CMD_ES_32KB << 24;
		break;
	case 64 * 1024:
		data_out = SPI_FLASH_CMD_ES_64KB << 24;
		break;
	default:
		return 1;
	}

	/* TODO: 4-byte addressing support */
	data_out = data_out | (address & 0x00FFFFFF);

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

/* Returns JEDEC ID for selected FLASH chip */
u32 qca_sf_jedec_id(u32 bank)
{
	volatile u32 data_in = 0;

	qca_sf_bank_to_cs_mask(bank);

	qca_sf_spi_en();
	qca_sf_shift_out(SPI_FLASH_CMD_JEDEC << 24, 32, 1);

	do {
		data_in = qca_sf_shift_in();
	} while (data_in == 0);

	qca_sf_spi_di();

	return (data_in & 0x00FFFFFF);
}
