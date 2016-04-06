/*
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2005 Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#ifndef _FLASH_H_
#define _FLASH_H_

#ifndef CFG_NO_FLASH

/*
 * Struct for info about FLASH chip/bank, with:
 * - manufacturer and model names
 * - JEDEC ID (combined device & manufacturer code)
 * - total bank size in bytes
 * - size of erase unit in bytes
 * - bank number
 * - size of program page in bytes
 * - number of erase units
 * - erase command
 * - physical sector start addresses
 */
typedef struct {
	char *manuf_name;
	char *model_name;
	u32 flash_id;
	u32 size;
	u32 sector_size;
	u32 bank;
	u16 page_size;
	u16 sector_count;
	u8  erase_cmd;
	u32 start[CFG_MAX_FLASH_SECT];
} flash_info_t;

extern flash_info_t flash_info[];

/*
 * Struct for info about supported SPI NOR FLASH chips, with:
 * - model names
 * - JEDEC ID (combined device & manufacturer code)
 * - total size in bytes
 * - size of erase unit in bytes
 * - size of program page in bytes
 * - erase command
 */
typedef struct {
	char *model_name;
	u32 flash_id;
	u32 size;
	u32 sector_size;
	u16 page_size;
	u8  erase_cmd;
} spi_nor_ids_info_t;

extern const spi_nor_ids_info_t spi_nor_ids[];
extern const u32 spi_nor_ids_count;

/* Prototypes */
u32 flash_init(void);
u32 flash_erase(flash_info_t *info, u32 s_first, u32 s_last);
const char *flash_manuf_name(u32 jedec_id);

extern int flash_sect_erase(ulong addr_first, ulong addr_last);

/* common/flash.c */
extern int flash_write(char *, ulong, ulong);
extern flash_info_t *addr2info(ulong);
extern u32 write_buff(flash_info_t *info, uchar *src, ulong addr, ulong cnt);

/* Useful size */
#define SIZE_4KiB	 4 * 1024
#define SIZE_64KiB	64 * 1024

#define SIZE_4MiB	 4 * 1024 * 1024
#define SIZE_8MiB	 8 * 1024 * 1024
#define SIZE_16MiB	16 * 1024 * 1024
#define SIZE_32MiB	32 * 1024 * 1024
#define SIZE_64MiB	64 * 1024 * 1024

/* Return codes from flash_write(): */
#define ERR_OK							0
#define ERR_TIMOUT						1
#define ERR_NOT_ERASED					2
#define ERR_PROTECTED					4
#define ERR_INVAL						8
#define ERR_ALIGN						16
#define ERR_UNKNOWN_FLASH_VENDOR		32
#define ERR_UNKNOWN_FLASH_TYPE			64
#define ERR_PROG_ERROR					128

/* FLASH vendors IDs */
#define FLASH_VENDOR_JEDEC_ATMEL		0x1F
#define FLASH_VENDOR_JEDEC_EON			0x1C
#define FLASH_VENDOR_JEDEC_MACRONIX		0xC2
#define FLASH_VENDOR_JEDEC_MICRON		0x20
#define FLASH_VENDOR_JEDEC_SPANSION		0x01
#define FLASH_VENDOR_JEDEC_WINBOND		0xEF

/* Device IDs */
#define FLASH_UNKNOWN	0xFFFFFF
#define FLASH_CUSTOM	0x111111

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
#define SPI_FLASH_CMD_SFDP		0x5A

/* SFDP related defines */
#define SPI_FLASH_SFDP_SIGN		0x50444653

#endif /* !CFG_NO_FLASH */

#endif /* _FLASH_H_ */
