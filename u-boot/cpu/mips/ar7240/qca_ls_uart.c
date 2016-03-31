/*
 * Qualcomm/Atheros Low-Speed UART driver
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg(void)
{
	u32 div;

	/*
	 * TODO: prepare list of supported range of baudrate values
	 * For 40 MHz ref_clk, successfully tested up to 1152000 on AR9344
	 */

	/* Round to closest, final baudrate = ref_clk / (16 * div) */
	if (qca_xtal_is_40mhz() == 1) {
		div = (VAL_40MHz + (8 * gd->baudrate)) / (16 * gd->baudrate);
	} else {
		div = (VAL_25MHz + (8 * gd->baudrate)) / (16 * gd->baudrate);
	}

	/* Set DLAB bit in LCR register unlocks DLL/DLH registers */
	qca_soc_reg_read_set(QCA_LSUART_LCR_REG, QCA_LSUART_LCR_DLAB_MASK);

	/* Write div into DLL and DLH registers */
	qca_soc_reg_write(QCA_LSUART_DLL_REG, (div & 0xFF));
	qca_soc_reg_write(QCA_LSUART_DLH_REG, ((div >> 8) & 0xFF));

	/* Clear DLAB bit in LCR register */
	qca_soc_reg_read_clear(QCA_LSUART_LCR_REG, QCA_LSUART_LCR_DLAB_MASK);
}

int serial_init(void)
{
	serial_setbrg();

	/* No interrupt */
	qca_soc_reg_write(QCA_LSUART_IER_REG, 0x0);

	/* No FIFO/DMA */
	qca_soc_reg_write(QCA_LSUART_FCR_REG, 0x0);

	/*
	 * Low-Speed UART controller configuration:
	 * - data: 8bits
	 * - stop: 1bit
	 * - parity: no
	 */
	qca_soc_reg_write(QCA_LSUART_LCR_REG,
					  QCA_LSUART_LCR_CLS_8BIT_VAL << QCA_LSUART_LCR_CLS_SHIFT);

	return 0;
}

void serial_putc(const char c)
{
	u32 line_status;

	if (c == '\n')
		serial_putc('\r');

	/* Wait for empty THR */
	do {
		line_status = qca_soc_reg_read(QCA_LSUART_LSR_REG)
					  & QCA_LSUART_LSR_THRE_MASK;
	} while (line_status == 0);

	/* Put data in THR */
	qca_soc_reg_write(QCA_LSUART_THR_REG, (u32)c);
}

int serial_getc(void)
{
	while (!serial_tstc())
		;

	/* Get data from RBR */
	return qca_soc_reg_read(QCA_LSUART_RBR_REG)
		   & QCA_LSUART_RBR_RBR_MASK;
}

int serial_tstc(void)
{
	/* Check data ready bit */
	return qca_soc_reg_read(QCA_LSUART_LSR_REG)
		   & QCA_LSUART_LSR_DR_MASK;
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
