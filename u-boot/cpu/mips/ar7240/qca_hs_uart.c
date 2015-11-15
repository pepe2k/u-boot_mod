/*
 * Qualcomm/Atheros High-Speed UART driver
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2014 Mantas Pucka <mantas@8devices.com>
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * Values for UART_SCALE and UART_STEP:
 * https://www.mail-archive.com/openwrt-devel@lists.openwrt.org/msg22371.html
 *
 * Partially based on:
 * Linux/drivers/tty/serial/ar933x_uart.c
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

DECLARE_GLOBAL_DATA_PTR;

/* HS UART baudrate = (REF_CLK / (CLOCK_SCALE + 1)) * (CLOCK_STEP * (1 / 2^17)) */
static u32 qca_hsuart_get_baud(u32 ref_clk, u32 uart_scale, u32 uart_step)
{
	u64 baudrate;
	u32 div;

	div = (uart_scale + 1) * (2 << 16);

	baudrate = (ref_clk * uart_step) + (div / 2);
	baudrate = baudrate / div;

	return (u32)baudrate;
}

static void qca_hsuart_get_scale_step(u32 baudrate,
									  u32 *uart_scale,
									  u32 *uart_step)
{
	s32 diff;
	u32 ref_clk;
	u32 tscale;
	u64 tstep;
	s32 min_diff;

	*uart_scale = 0;
	*uart_step = 0;

	min_diff = baudrate;

	if (qca_xtal_is_40mhz() == 1) {
		ref_clk = VAL_40MHz;
	} else {
		ref_clk = VAL_25MHz;
	}

	for (tscale = 0; tscale < QCA_HSUART_CLK_SCALE_MAX_VAL; tscale++) {
		tstep = baudrate * (tscale + 1);
		tstep = tstep * (2 << 16);
		tstep = tstep / ref_clk;

		if (tstep > QCA_HSUART_CLK_STEP_MAX_VAL)
			break;

		diff = qca_hsuart_get_baud(ref_clk, tscale, tstep) - baudrate;

		if (diff < 0)
			diff = -1 * diff;

		if (diff < min_diff) {
			min_diff = diff;
			*uart_scale = tscale;
			*uart_step = tstep;
		}
	}
}

void serial_setbrg(void)
{
	u32 uart_clock;
	u32 uart_scale;
	u32 uart_step;

	qca_hsuart_get_scale_step(gd->baudrate, &uart_scale, &uart_step);

	uart_clock  = (uart_scale << QCA_HSUART_CLK_SCALE_SHIFT);
	uart_clock |= (uart_step  << QCA_HSUART_CLK_STEP_SHIFT);

	qca_soc_reg_write(QCA_HSUART_CLK_REG, uart_clock);
}

int serial_init(void)
{
	u32 uart_cs;

#if (SOC_TYPE & QCA_AR933X_SOC)
	/*
	 * Set GPIO10 (UART_SO) as output and enable UART,
	 * BIT(15) in GPIO_FUNCTION_1 register must be written with 1
	 */
	qca_soc_reg_read_set(QCA_GPIO_OE_REG, GPIO10);

	qca_soc_reg_read_set(QCA_GPIO_FUNC_1_REG,
						 QCA_GPIO_FUNC_1_UART_EN_MASK | BIT(15));
#else
	#error "Missing GPIO configuration for HS UART"
#endif

	/*
	 * High-Speed UART controller configuration:
	 * - no DMA
	 * - no interrupt
	 * - no parity
	 * - DCE mode
	 * - no flow control
	 * - set RX ready oride
	 * - set TX ready oride
	 */
	uart_cs = (0 << QCA_HSUART_CS_DMA_EN_SHIFT) |
		(0 << QCA_HSUART_CS_HOST_INT_EN_SHIFT) |
		(1 << QCA_HSUART_CS_RX_READY_ORIDE_SHIFT) |
		(1 << QCA_HSUART_CS_TX_READY_ORIDE_SHIFT) |
		(QCA_HSUART_CS_PAR_MODE_NO_VAL << QCA_HSUART_CS_PAR_MODE_SHIFT) |
		(QCA_HSUART_CS_IFACE_MODE_DCE_VAL << QCA_HSUART_CS_IFACE_MODE_SHIFT) |
		(QCA_HSUART_CS_FLOW_MODE_NO_VAL << QCA_HSUART_CS_FLOW_MODE_SHIFT);

	qca_soc_reg_write(QCA_HSUART_CS_REG, uart_cs);

	serial_setbrg();

	return 0;
}

void serial_putc(const char c)
{
	u32 uart_data;

	if (c == '\n')
		serial_putc('\r');

	/* Wait for FIFO */
	do {
		uart_data = qca_soc_reg_read(QCA_HSUART_DATA_REG);
	} while (((uart_data & QCA_HSUART_DATA_TX_CSR_MASK)
			  >> QCA_HSUART_DATA_TX_CSR_SHIFT)  == 0);

	/* Put data in buffer and set CSR bit */
	uart_data  = (u32)c | (1 << QCA_HSUART_DATA_TX_CSR_SHIFT);

	qca_soc_reg_write(QCA_HSUART_DATA_REG, uart_data);
}

int serial_getc(void)
{
	u32 uart_data;

	while (!serial_tstc())
		;

	uart_data = qca_soc_reg_read(QCA_HSUART_DATA_REG);

	qca_soc_reg_write(QCA_HSUART_DATA_REG,
					  (1 << QCA_HSUART_DATA_RX_CSR_SHIFT));

	return (uart_data & QCA_HSUART_DATA_TX_RX_DATA_MASK);
}

int serial_tstc(void)
{
	u32 uart_data = qca_soc_reg_read(QCA_HSUART_DATA_REG);

	return ((uart_data & QCA_HSUART_DATA_RX_CSR_MASK)
			>> QCA_HSUART_DATA_RX_CSR_SHIFT);
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
