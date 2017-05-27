/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <flash.h>
#include <asm/addrspace.h>
#include <asm/types.h>
#include <soc/qca_soc_common.h>

/* Use 4 MB by default */
#ifndef CONFIG_DEFAULT_FLASH_SIZE_IN_MB
	#define CONFIG_DEFAULT_FLASH_SIZE_IN_MB	4
#endif

/*
 * Find SPI NOR FLASH chip info for selected bank,
 * based on JEDEC ID and copy data to global flash_info variable
 */
static u32 flash_info_find(flash_info_t *info, u32 jedec_id)
{
	u32 i;

	for (i = 0; i < spi_nor_ids_count; i++) {
		if (jedec_id == spi_nor_ids[i].flash_id) {
			info->model_name   = spi_nor_ids[i].model_name;
			info->size         = spi_nor_ids[i].size;
			info->sector_size  = spi_nor_ids[i].sector_size;
			info->page_size    = spi_nor_ids[i].page_size;
			info->erase_cmd    = spi_nor_ids[i].erase_cmd;
			info->sector_count = info->size / info->sector_size;

			return 0;
		}
	}

	return 1;
}

/*
 * Scan all configured FLASH banks one by one
 * and try to get information about the chips
 */
u32 flash_init(void)
{
	u32 bank, i, jedec_id, sfdp_size, sfdp_ss;
	u32 total_size = 0;
	flash_info_t *info;
	u8 sfdp_ec;

	for (bank = 0; bank < CFG_MAX_FLASH_BANKS; bank++) {
		info = &flash_info[bank];

		jedec_id = qca_sf_jedec_id(bank);

		if (jedec_id == 0) {
			printf_err("SPI NOR FLASH chip in bank #%d\n"
				   "   is not responding, skipping\n\n", bank + 1);
			continue;
		}

		info->manuf_name = (char *)flash_manuf_name(jedec_id);
		info->flash_id   = jedec_id;
		info->bank       = bank;

		if (flash_info_find(info, jedec_id) != 0) {
			/* Try to get some info about FLASH from SFDP */
			if (qca_sf_sfdp_info(bank, &sfdp_size, &sfdp_ss, &sfdp_ec) == 0) {
				info->size        = sfdp_size;
				info->sector_size = sfdp_ss;
				info->erase_cmd   = sfdp_ec;

				printf_wrn("SPI NOR FLASH in bank #%d is\n"
					   "   unknown, JEDEC ID: 0x%06X\n\n", bank + 1, jedec_id);

				printf("   Information provided in SFDP:\n"
					   "   - FLASH size: ");
				print_size(sfdp_size, "\n");

				printf("   - erase sector size: ");
				print_size(sfdp_ss, "\n");

				printf("   - erase sector command: 0x%02X\n\n", sfdp_ec);
			} else {
				#if (CONFIG_DEFAULT_FLASH_SIZE_IN_MB == 4)
				info->size = SIZE_4MiB;
				#elif (CONFIG_DEFAULT_FLASH_SIZE_IN_MB == 8)
				info->size = SIZE_8MiB;
				#elif (CONFIG_DEFAULT_FLASH_SIZE_IN_MB == 16)
				info->size = SIZE_16MiB;
				#else
					#error "Not supported CONFIG_DEFAULT_FLASH_SIZE_IN_MB value!"
				#endif

				printf_err("SPI NOR FLASH chip in bank #%d\n"
					   "   is unknown, JEDEC ID: 0x%06X, will\n"
					   "   use fixed/predefined size: ", bank + 1, jedec_id);
				print_size(info->size, "\n\n");

				/*
				 * Use 64 KiB erase sector/block size for unknown chip
				 * Hopefully will work in most cases
				 */
				info->sector_size = SIZE_64KiB;
				info->erase_cmd   = SPI_FLASH_CMD_ES_64KB;
				info->flash_id    = FLASH_CUSTOM;
			}

			/* We assume page size to be 256 bytes */
			info->page_size    = 256;
			info->model_name   = "unknown model";
			info->sector_count = info->size / info->sector_size;
		}

		for (i = 0; i < info->sector_count; i++) {
			info->start[i] = CFG_FLASH_BASE
							 + total_size + (i * info->sector_size);
		}

		total_size += flash_info[bank].size;
	}

	return total_size;
}

/*
 * Erase all FLASH sectors in provided range
 *
 * TODO:
 * - use some LED for indication that we are erasing?
 */
u32 flash_erase(flash_info_t *info,
				u32 s_first,
				u32 s_last)
{
	u32 i, j;

	printf("Erasing: ");

	j = 0;
	for (i = s_first; i <= s_last; i++) {
		qca_sf_sect_erase(info->bank, i * info->sector_size,
						  info->sector_size, info->erase_cmd);

		if (j == 39) {
			puts("\n         ");
			j = 0;
		}
		puts("#");

		j++;
	}

	printf("\n\n");

	return 0;
}

/*
 * Write a buffer from memory to a FLASH:
 * call page program for every <= 256 bytes
 *
 * Assumption: caller has already erased the appropriate sectors
 */
u32 write_buff(flash_info_t *info, uchar *source, ulong addr, ulong len)
{
	u32 total = 0, len_this_lp, bytes_this_page;
	u32 dst;
	u8 *src;

	printf("Writing at address: 0x%08lX\n", addr);
	addr = addr - CFG_FLASH_BASE;

	while (total < len) {
		src = source + total;
		dst = addr + total;
		bytes_this_page = info->page_size - (addr % info->page_size);
		len_this_lp = ((len - total) > bytes_this_page) ? bytes_this_page : (len - total);

		qca_sf_write_page(info->bank, dst, len_this_lp, src);

		total += len_this_lp;
	}

	puts("\n");

	return 0;
}
