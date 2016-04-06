/*
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2005 Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <common.h>
#include <flash.h>

#ifndef CFG_NO_FLASH

/* Info for FLASH chips */
flash_info_t flash_info[CFG_MAX_FLASH_BANKS];

/* List of supported and known SPI NOR FLASH chips */
static char VENDOR_ATMEL[]    = "Atmel";
static char VENDOR_EON[]      = "EON";
static char VENDOR_MACRONIX[] = "Macronix";
static char VENDOR_MICRON[]   = "Micron";
static char VENDOR_SPANSION[] = "Spansion";
static char VENDOR_WINBOND[]  = "Winbond";

const spi_nor_ids_info_t spi_nor_ids[] = {
	/* 4 MiB */
	{ "AT25DF321", 0x1F4700, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "EN25Q32",   0x1C3016, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "EN25F32",   0x1C3116, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "MX25L320",  0xC22016, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "M25P32",    0x202016, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "S25FL032P", 0x010215, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "W25Q32",    0xEF4016, SIZE_4MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },

	/* 8 MiB */
	{ "AT25DF641", 0x1F4800, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "EN25Q64",   0x1C3017, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "MX25L64",   0xC22017, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "MX25L64",   0xC22617, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "M25P64",    0x202017, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "S25FL064P", 0x010216, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "W25Q64",    0xEF4017, SIZE_8MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },

	/* 16 MiB */
	{ "MX25L128",  0xC22018, SIZE_16MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "MX25L128",  0xC22618, SIZE_16MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "N25Q128",   0x20BA18, SIZE_16MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "S25FL127S", 0x012018, SIZE_16MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
	{ "W25Q128",   0xEF4018, SIZE_16MiB, SIZE_64KiB, 256, SPI_FLASH_CMD_ES_64KB },
};

const u32 spi_nor_ids_count = sizeof(spi_nor_ids) / sizeof(spi_nor_ids_info_t);

const char *flash_manuf_name(u32 jedec_id)
{
	switch (jedec_id >> 16) {
	case FLASH_VENDOR_JEDEC_ATMEL:
		return VENDOR_ATMEL;
		break;
	case FLASH_VENDOR_JEDEC_EON:
		return VENDOR_EON;
		break;
	case FLASH_VENDOR_JEDEC_MACRONIX:
		return VENDOR_MACRONIX;
		break;
	case FLASH_VENDOR_JEDEC_MICRON:
		return VENDOR_MICRON;
		break;
	case FLASH_VENDOR_JEDEC_SPANSION:
		return VENDOR_SPANSION;
		break;
	case FLASH_VENDOR_JEDEC_WINBOND:
		return VENDOR_WINBOND;
		break;
	default:
		return "Unknown";
		break;
	}
}

flash_info_t *addr2info(ulong addr)
{
	flash_info_t *info;
	int i;

	for (i = 0, info = &flash_info[0]; i < CFG_MAX_FLASH_BANKS; ++i, ++info) {
		/*
		 * WARNING - The '- 1' is needed if the flash
		 * is at the end of the address space, since
		 * info->start[0] + info->size wraps back to 0.
		 * Please don't change this unless you understand this.
		 */
		if (info->flash_id != FLASH_UNKNOWN
			&& addr >= info->start[0]
			&& addr <= info->start[0] + info->size - 1) {
			return info;
		}
	}

	return NULL;
}

/*
 * Copy memory to flash.
 * Make sure all target addresses are within Flash bounds,
 * and no protected sectors are hit.
 * Returns:
 * ERR_OK          0 - OK
 * ERR_TIMOUT      1 - write timeout
 * ERR_NOT_ERASED  2 - Flash not erased
 * ERR_PROTECTED   4 - target range includes protected sectors
 * ERR_INVAL       8 - target address not in Flash memory
 * ERR_ALIGN       16 - target address not aligned on boundary
 *                      (only some targets require alignment)
 */
int flash_write(char *src, ulong addr, ulong cnt)
{
	int i;
	ulong end = addr + cnt - 1;
	flash_info_t *info_first = addr2info(addr);
	flash_info_t *info_last = addr2info(end);
	flash_info_t *info;

	if (cnt == 0)
		return ERR_OK;

	if (!info_first || !info_last)
		return ERR_INVAL;

	/* Finally write data to flash */
	for (info = info_first; info <= info_last && cnt > 0; ++info) {
		ulong len = info->start[0] + info->size - addr;

		if (len > cnt)
			len = cnt;

		if ((i = write_buff(info, (uchar *)src, addr, len)) != 0)
			return i;

		cnt  -= len;
		addr += len;
		src  += len;
	}

	return ERR_OK;
}

void flash_perror(int err)
{
	switch (err) {
	case ERR_OK:
		break;
	case ERR_TIMOUT:
		puts("## Error: timeout writing to FLASH\n");
		break;
	case ERR_NOT_ERASED:
		puts("## Error: FLASH not erased\n");
		break;
	case ERR_INVAL:
		puts("## Error: outside available FLASH\n");
		break;
	case ERR_ALIGN:
		puts("## Error: start and/or end address not on sector boundary\n");
		break;
	case ERR_UNKNOWN_FLASH_VENDOR:
		puts("## Error: unknown vendor of FLASH\n");
		break;
	case ERR_UNKNOWN_FLASH_TYPE:
		puts("## Error: unknown type of FLASH\n");
		break;
	case ERR_PROG_ERROR:
		puts("## Error: general FLASH programming error\n");
		break;
	default:
		printf("## Error: %s[%d] FIXME: rc=%d\n", __FILE__, __LINE__, err);
		break;
	}
}
#endif /* !CFG_NO_FLASH */
