#include <common.h>
#include <jffs2/jffs2.h>
#include <asm/addrspace.h>
#include <asm/types.h>
#include "ar7240_soc.h"
#include "ar7240_flash.h"

#define	SIZE_INBYTES_4MBYTES	(4 * 1024 * 1024)
#define	SIZE_INBYTES_8MBYTES	(2 * SIZE_INBYTES_4MBYTES)
#define	SIZE_INBYTES_16MBYTES	(2 * SIZE_INBYTES_8MBYTES)

#define	SIZE_INBYTES_4KBYTES	(4 * 1024)
#define	SIZE_INBYTES_64KBYTES	(16 * SIZE_INBYTES_4KBYTES)

#ifndef DEFAULT_FLASH_SIZE_IN_MB
#error "DEFAULT_FLASH_SIZE_IN_MB not defined!"
#endif

extern void led_toggle(void);
extern void all_led_off(void);
extern int reset_button_status(void);

/*
 * globals
 */
flash_info_t flash_info[CFG_MAX_FLASH_BANKS];

/*
 * statics
 */
static void ar7240_spi_write_enable(void);
static void ar7240_spi_poll(void);
static void ar7240_spi_write_page(uint32_t addr, uint8_t * data, int len);
static void ar7240_spi_sector_erase(uint32_t addr);

/*
 * Returns JEDEC ID from SPI flash
 */
static ulong read_id(void){
	unsigned int flashid = 0;

	ar7240_reg_wr_nf(AR7240_SPI_FS, 1);
	ar7240_reg_wr_nf(AR7240_SPI_WRITE, AR7240_SPI_CS_DIS);

	ar7240_spi_bit_banger(0x9F);

	ar7240_spi_delay_8();
	ar7240_spi_delay_8();
	ar7240_spi_delay_8();
	ar7240_spi_delay_8();

	flashid = ar7240_reg_rd(AR7240_SPI_RD_STATUS);

	/*
	 * We have 3 bytes:
	 * - manufacture ID (1b)
	 * - product ID (2b)
	 */
	flashid = flashid >> 8;

	ar7240_spi_done();

	return((ulong)flashid);
}

static void flash_set_geom(int size, int sector_count, int sector_size){
	int i;
	flash_info_t *info = &flash_info[0];

	info->size = size;
	info->sector_count = sector_count;
	info->sector_size = sector_size;

	for(i = 0; i < info->sector_count; i++){
		info->start[i] = CFG_FLASH_BASE + (i * info->sector_size);
		info->protect[i] = 0;
	}
}

unsigned long flash_init(void){
	flash_info_t *info;
#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
	u32 pll_magic, spi_control;

	pll_magic = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET);

	// read SPI CONTROL Configuration register (SPI_CONTROL) value stored in FLASH (PLL_IN_FLASH_MAGIC_OFFSET + 12)
	spi_control = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 12);
#endif

	info = &flash_info[0];

	// spi flash clock
	ar7240_reg_wr(AR7240_SPI_FS,	0x01);

	// if reset button is pressed -> write default CLOCK_DIVIDER for SPI CLOCK
	if(reset_button_status()){
		ar7240_reg_wr(AR7240_SPI_CLOCK,	AR7240_SPI_CONTROL_DEFAULT);
	} else {
#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
		// do we have PLL_MAGIC in FLASH?
		if(pll_magic == PLL_IN_FLASH_MAGIC){
			ar7240_reg_wr(AR7240_SPI_CLOCK,	spi_control);
		} else {
#endif
			ar7240_reg_wr(AR7240_SPI_CLOCK,	AR7240_SPI_CONTROL);
#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
		}
#endif
	}

	ar7240_reg_wr(AR7240_SPI_FS,	0x0);

	// get flash id
	info->flash_id = read_id();

	puts("FLASH:  ");

	// fill flash info based on JEDEC ID
	switch(info->flash_id){
		/*
		 * 4M flash chips
		 */
		case 0x010215:	// tested
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Spansion S25FL032P (4 MB)");
			break;

		case 0x1F4700:
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Atmel AT25DF321 (4 MB)");
			break;

		case 0x1C3016:	// tested
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("EON EN25Q32 (4 MB)");
			break;

		case 0x1C3116:	// tested
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("EON EN25F32 (4 MB)");
			break;

		case 0x202016:
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Micron M25P32 (4 MB)");
			break;

		case 0xEF4016:
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Winbond W25Q32 (4 MB)");
			break;

		case 0xC22016:
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Macronix MX25L320 (4 MB)");
			break;

			/*
			 * 8M flash chips
			 */
		case 0x010216:
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Spansion S25FL064P (8 MB)");
			break;

		case 0x1F4800:
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Atmel AT25DF641 (8 MB)");
			break;

		case 0x1C3017:	// tested
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("EON EN25Q64 (8 MB)");
			break;

		case 0x202017:
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Micron M25P64 (8 MB)");
			break;

		case 0xEF4017:	// tested
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Winbond W25Q64 (8 MB)");
			break;

		case 0xC22017:	// tested
		case 0xC22617:
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Macronix MX25L64 (8 MB)");
			break;

			/*
			 * 16M flash chips
			 */
		case 0xEF4018:	// tested
			flash_set_geom(SIZE_INBYTES_16MBYTES, 256, SIZE_INBYTES_64KBYTES);
			puts("Winbond W25Q128 (16 MB)");
			break;

		case 0xC22018:
		case 0xC22618:
			flash_set_geom(SIZE_INBYTES_16MBYTES, 256, SIZE_INBYTES_64KBYTES);
			puts("Macronix MX25L128 (16 MB)");
			break;

		case 0x012018:
 			flash_set_geom(SIZE_INBYTES_16MBYTES, 256, SIZE_INBYTES_64KBYTES);
 			puts("Spansion S25FL127S (16 MB)");
 			break;

		case 0x20BA18:
 			flash_set_geom(SIZE_INBYTES_16MBYTES, 256, SIZE_INBYTES_64KBYTES);
 			puts("Micron N25Q128 (16 MB)");
 			break;

			/*
			 * Unknown flash
			 */
		default:
#if (DEFAULT_FLASH_SIZE_IN_MB == 4)
			flash_set_geom(SIZE_INBYTES_4MBYTES, 64, SIZE_INBYTES_64KBYTES);
			puts("Unknown type (using only 4 MB)\n");
#elif (DEFAULT_FLASH_SIZE_IN_MB == 8)
			flash_set_geom(SIZE_INBYTES_8MBYTES, 128, SIZE_INBYTES_64KBYTES);
			puts("Unknown type (using only 8 MB)\n");
#elif (DEFAULT_FLASH_SIZE_IN_MB == 16)
			flash_set_geom(SIZE_INBYTES_16MBYTES, 256, SIZE_INBYTES_64KBYTES);
			puts("Unknown type (using only 16 MB)\n");
#endif
			printf("\nPlease, send request to add support\nfor your flash - JEDEC ID: 0x%06lX\n", info->flash_id);
			info->flash_id = FLASH_CUSTOM;
			break;
	}

	puts("\n");

	return(info->size);
}

int flash_erase(flash_info_t *info, int s_first, int s_last){
	int i, j, sector_size = info->size / info->sector_count;

	printf("Erasing: ");

	j = 0;

	for(i = s_first; i <= s_last; i++){
		ar7240_spi_sector_erase(i * sector_size);

		if(j == 39){
			puts("\n         ");
			j = 0;
		}
		puts("#");
		led_toggle();
		j++;
	}

	ar7240_spi_done();
	all_led_off();
	printf("\n\n");

	return(0);
}

/*
 * Write a buffer from memory to flash:
 * 0. Assumption: Caller has already erased the appropriate sectors.
 * 1. call page programming for every 256 bytes
 */
int write_buff(flash_info_t *info, uchar *source, ulong addr, ulong len){
	int total = 0, len_this_lp, bytes_this_page;
	ulong dst;
	uchar *src;

	printf("Writting at address: 0x%08lX\n", addr);
	addr = addr - CFG_FLASH_BASE;

	while(total < len){
		src = source + total;
		dst = addr + total;
		bytes_this_page = AR7240_SPI_PAGE_SIZE - (addr % AR7240_SPI_PAGE_SIZE);
		len_this_lp = ((len - total) > bytes_this_page) ? bytes_this_page : (len - total);
		ar7240_spi_write_page(dst, src, len_this_lp);
		total += len_this_lp;
	}

	ar7240_spi_done();
	printf("\n");

	return(0);
}

static void ar7240_spi_write_enable(){
	ar7240_reg_wr_nf(AR7240_SPI_FS, 1);
	ar7240_reg_wr_nf(AR7240_SPI_WRITE, AR7240_SPI_CS_DIS);
	ar7240_spi_bit_banger(AR7240_SPI_CMD_WREN);
	ar7240_spi_go();
}

static void ar7240_spi_poll(){
	int rd;

	do {
		ar7240_reg_wr_nf(AR7240_SPI_WRITE, AR7240_SPI_CS_DIS);
		ar7240_spi_bit_banger(AR7240_SPI_CMD_RD_STATUS);
		ar7240_spi_delay_8();
		rd = (ar7240_reg_rd(AR7240_SPI_RD_STATUS) & 1);
	} while(rd);
}

static void ar7240_spi_write_page(uint32_t addr, uint8_t *data, int len){
	int i;
	uint8_t ch;

	ar7240_spi_write_enable();
	ar7240_spi_bit_banger(AR7240_SPI_CMD_PAGE_PROG);
	ar7240_spi_send_addr(addr);

	for(i = 0; i < len; i++){
		ch = *(data + i);
		ar7240_spi_bit_banger(ch);
	}

	ar7240_spi_go();
	ar7240_spi_poll();
}

static void ar7240_spi_sector_erase(uint32_t addr){
	ar7240_spi_write_enable();
	ar7240_spi_bit_banger(AR7240_SPI_CMD_SECTOR_ERASE);
	ar7240_spi_send_addr(addr);
	ar7240_spi_go();
	ar7240_spi_poll();
}
