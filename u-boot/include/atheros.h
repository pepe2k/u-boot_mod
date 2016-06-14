/*
 * vim: tabstop=8 : noexpandtab
 */

/* 
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ATHEROS_H
#define _ATHEROS_H

/*
 * Set everything to zero. The corresponding header will
 * undef and re-define the appropriate ones
 */
#define is_ar7100()	(0)


#define is_ar7240()	(0)
#define is_ar7241()	(0)
#define is_ar7242()	(0)

#define is_ar9330()	(0)
#define is_ar933x()	(0)
#define is_hornet()	(0)

#define is_ar934x()	(0)
#define is_wasp()	(0)

#define is_qca955x()	(0)
#define is_sco()	(0)

#define is_qca953x()	(0)
#define is_hb()		(0)

#define is_qca956x()	(0)

#define ATH_CONSOLE_BAUD	115200

#define AR7240_REV_1_2		0xc2

#ifdef CONFIG_ATH_EMULATION
#define is_emu()	(1)
#else
#define is_emu()	(0)
#endif

#ifdef CONFIG_F1E_PHY
#define is_f1e()	1
#else
#define is_f1e()	0
#endif
#ifdef CONFIG_F2E_PHY
#define is_f2e()	1
#else
#define is_f2e()	0
#endif
#ifdef CONFIG_ATHRS16_PHY
#define is_s16()	1
#else
#define is_s16()	0
#endif

#ifdef CONFIG_ATHRS17_PHY
#define is_s17()        1
#else
#define is_s17()        0
#endif

#ifdef CONFIG_ATHR_8033_PHY
#define is_ar8033() 1
#else
#define is_ar8033() 0
#endif

#ifdef CONFIG_VIR_PHY
#define is_vir_phy()	1
#else
#define is_vir_phy() 	0
#endif

#ifdef CFG_ATHRS27_PHY
#define is_s27()        1
#else
#define is_s27()        0
#endif

#define ath_arch_init_irq() /* nothing */

#ifndef __ASSEMBLY__

int ath_uart_freq(void);

typedef unsigned int ath_reg_t;

#ifdef COMPRESSED_UBOOT
#	define prmsg(...)
#else
#	define prmsg	printf
#endif

#endif /* __ASSEMBLY__ */

#define ath_reg_rd(_phys)	(*(volatile ath_reg_t *)KSEG1ADDR(_phys))

#define ath_reg_wr_nf(_phys, _val) \
	((*(volatile ath_reg_t *)KSEG1ADDR(_phys)) = (_val))

#define ath_reg_wr(_phys, _val) do {	\
	ath_reg_wr_nf(_phys, _val);	\
	ath_reg_rd(_phys);		\
} while(0)

#define ath_reg_rmw_set(_reg, _mask)	do {			\
	ath_reg_wr((_reg), (ath_reg_rd((_reg)) | (_mask)));	\
	ath_reg_rd((_reg));					\
} while(0)

#define ath_reg_rmw_clear(_reg, _mask) do {			\
	ath_reg_wr((_reg), (ath_reg_rd((_reg)) & ~(_mask)));	\
	ath_reg_rd((_reg));					\
} while(0)

#define ath_uart_rd(y)		ath_reg_rd((ATH_UART_BASE+y))
#define ath_uart_wr(x, z)	ath_reg_wr((ATH_UART_BASE+x), z)

#define REG_OFFSET		4

#define OFS_RCV_BUFFER		(0 * REG_OFFSET)
#define OFS_TRANS_HOLD		(0 * REG_OFFSET)
#define OFS_SEND_BUFFER		(0 * REG_OFFSET)
#define OFS_INTR_ENABLE		(1 * REG_OFFSET)
#define OFS_INTR_ID		(2 * REG_OFFSET)
#define OFS_DATA_FORMAT		(3 * REG_OFFSET)
#define OFS_LINE_CONTROL	(3 * REG_OFFSET)
#define OFS_MODEM_CONTROL	(4 * REG_OFFSET)
#define OFS_RS232_OUTPUT	(4 * REG_OFFSET)
#define OFS_LINE_STATUS		(5 * REG_OFFSET)
#define OFS_MODEM_STATUS	(6 * REG_OFFSET)
#define OFS_RS232_INPUT		(6 * REG_OFFSET)
#define OFS_SCRATCH_PAD		(7 * REG_OFFSET)

#define OFS_DIVISOR_LSB		(0 * REG_OFFSET)
#define OFS_DIVISOR_MSB		(1 * REG_OFFSET)

/*
 * PLL Config for different CPU/DDR/AHB frequencies
 */
#define CFG_PLL_720_600_200	0x01
#define CFG_PLL_720_680_240	0x02
#define CFG_PLL_720_600_240	0x03
#define CFG_PLL_680_680_226	0x04
#define CFG_PLL_720_600_300	0x05
#define CFG_PLL_400_400_200	0x06
#define CFG_PLL_560_450_220	0x07
#define CFG_PLL_550_400_200	0x08
#define CFG_PLL_550_600_200	0x09
#define CFG_PLL_600_600_200	0x0a
#define CFG_PLL_750_400_250	0x0b
#define CFG_PLL_800_400_266	0x0c
#define CFG_PLL_750_667_250	0x0d
#define CFG_PLL_800_600_266	0x0e
#define CFG_PLL_800_667_266	0x0f
#define CFG_PLL_810_700_270	0x10
#define CFG_PLL_810_666_270	0x11
#define CFG_PLL_775_650_258	0x12
#define CFG_PLL_650_400_200	0x13
#define CFG_PLL_650_600_200	0x14

#define UBOOT_SIZE                      (256 * 1024)
#define PLL_FLASH_ADDR                  (CFG_FLASH_BASE + UBOOT_SIZE)
#define PLL_CONFIG_VAL_F                (PLL_FLASH_ADDR + CFG_FLASH_SECTOR_SIZE - 0x20)
#define PLL_MAGIC                        0xaabbccdd
#define SRIF_PLL_CONFIG_VAL_F           (PLL_CONFIG_VAL_F - 12)
#define SRIF_PLL_MAGIC                  0x73726966 /* srif */

#include <config.h>

#if defined(CONFIG_MACH_AR724x)
#	include <724x.h>
#elif defined(CONFIG_MACH_AR933x)
#	include <933x.h>
#elif defined(CONFIG_MACH_AR934x)
#	include <934x.h>
#elif defined(CONFIG_MACH_QCA955x)
#	include <955x.h>
#elif defined(CONFIG_MACH_QCA953x)
#	include <953x.h>
#elif defined(CONFIG_MACH_QCA956x)
#	include <956x.h>
#else
#	error "Building U-Boot for unknown device"
#endif

#ifndef __ASSEMBLY__

#define ATH_MEM_SDRAM		1
#define ATH_MEM_DDR1		2
#define ATH_MEM_DDR2		3
/*
 * GPIO Access & Control
 */
void ath_gpio_init(void);
void ath_gpio_down(void);
void ath_gpio_up(void);

void ath_gpio_irq_init(int);
/*
 * GPIO Helper Functions
 */
void ath_gpio_enable_slic(void);

/* enable UART block, takes away GPIO 10 and 9 */
void ath_gpio_enable_uart(void);

/* enable STEREO block, takes away GPIO 11,8,7, and 6 */
void ath_gpio_enable_stereo(void);

/* allow CS0/CS1 to be controlled via SPI register, takes away GPIO0/GPIO1 */
void ath_gpio_enable_spi_cs1_cs0(void);

/* allow GPIO0/GPIO1 to be used as SCL/SDA for software based i2c */
void ath_gpio_enable_i2c_on_gpio_0_1(void);

/*
 * GPIO General Functions
 */
void ath_gpio_drive_low(unsigned int mask);
void ath_gpio_drive_high(unsigned int mask);

unsigned int ath_gpio_float_high_test(unsigned int mask);

/* Functions to access SPI through software. Example:
 *
 * ath_spi_down(); ---------------------- disable others from accessing SPI bus taking semaphore
 * ath_spi_enable_soft_access(); -------- disable HW control of SPI
 *
 * <board specific chip select routine>
 *
 * <read/write SPI using using custom routine or general purposeflash routines
 * Custom routine may use:
 *
 *	ath_spi_raw_output_u8(unsigned char)
 *	ath_spi_raw_output_u32(unsigned int)
 *	ath_spi_raw_input_u32()
 *
 * General purpose flash routines:
 *	ath_spi_flash_read_page(unsigned int addr, unsigned char *data, int len);
 *	ath_spi_flash_write_page(unsigned int addr, unsigned char *data, int len);
 *	ath_spi_flash_sector_erase(unsigned int addr);
 * >
 *
 * <board specific chip deselect routine>
 *
 * ath_spi_disable_soft_acess(); ------- enable HW control of SPI bus
 * ath_spi_up(); ----------------------- enable others to access SPI bus releasing semaphore
 */
void ath_spi_init(void);
void ath_spi_down(void);
void ath_spi_up(void);

static inline void
ath_spi_enable_soft_access(void)
{
	ath_reg_wr_nf(ATH_SPI_FS, 1);
}

static inline void
ath_spi_disable_soft_access(void)
{
	ath_reg_wr_nf(ATH_SPI_WRITE, ATH_SPI_CS_DIS);
	ath_reg_wr_nf(ATH_SPI_FS, 0);
}

void ath_spi_raw_output_u8(unsigned char val);
void ath_spi_raw_output_u32(unsigned int val);
unsigned int ath_spi_raw_input_u8(void);
unsigned int ath_spi_raw_input_u32(void);

void ath_spi_flash_read_page(unsigned int addr, unsigned char *data, int len);
void ath_spi_flash_write_page(unsigned int addr, unsigned char *data, int len);
void ath_spi_flash_sector_erase(unsigned int addr);

/*
 * Allow access to cs0-2 when GPIO Function enables cs0-2 through SPI register.
 */
static inline void
ath_spi_enable_cs0(void)
{
	unsigned int cs;
	ath_spi_down();
	ath_spi_enable_soft_access();
	cs = ath_reg_rd(ATH_SPI_WRITE) & ~ATH_SPI_CS_DIS;
	ath_reg_wr_nf(ATH_SPI_WRITE, ATH_SPI_CS_ENABLE_0 | cs);
}

static inline void
ath_spi_enable_cs1(void)
{
	unsigned int cs;
#if defined(CONFIG_MACH_AR934x)	|| \
    defined(CONFIG_MACH_QCA955x)
	ath_spi_down();
	ath_spi_init();
	ath_spi_enable_soft_access();
	cs = ath_reg_rd(ATH_SPI_WRITE) & ATH_SPI_CS_DIS;
	ath_reg_wr_nf(ATH_SPI_WRITE, cs | ATH_SPI_CLK_HIGH);
	cs = ath_reg_rd(ATH_SPI_WRITE) & ~ATH_SPI_CS_DIS;
	ath_reg_wr_nf(ATH_SPI_WRITE, ATH_SPI_CS_ENABLE_1 | cs | ATH_SPI_CLK_HIGH);
	ath_reg_wr_nf(ATH_SPI_WRITE, ATH_SPI_CS_ENABLE_1 | cs);
#else
	ath_spi_down();
	ath_spi_enable_soft_access();
	cs = ath_reg_rd(ATH_SPI_WRITE) & ~ATH_SPI_CS_DIS;
	ath_reg_wr_nf(ATH_SPI_WRITE, ATH_SPI_CS_ENABLE_1 | cs);
#endif
}

static inline void
ath_spi_disable_cs(void)
{
	unsigned int cs = ath_reg_rd(ATH_SPI_WRITE) | ATH_SPI_CS_DIS;
	ath_reg_wr_nf(ATH_SPI_WRITE, cs);
	ath_spi_disable_soft_access();
	ath_spi_up();
}

/*
 * Example usage to access BOOT flash
 */
static inline void
ath_spi_flash_cs0_sector_erase(unsigned int addr)
{
	ath_spi_enable_cs0();
	ath_spi_flash_sector_erase(addr);
	ath_spi_disable_cs();
}

static inline void
ath_spi_flash_cs0_write_page(unsigned int addr, unsigned char *data, int len)
{
	ath_spi_enable_cs0();
	ath_spi_flash_write_page(addr, data, len);
	ath_spi_disable_cs();
}

#endif /* __ASSEMBLY__ */


#endif /* _ATHEROS_H */
