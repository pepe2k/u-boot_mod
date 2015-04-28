/*
 * Atheros AR933x UART driver
 *
 * Copyright (C) 2014 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2008-2010 Atheros Communications Inc.
 *
 * Values for UART_SCALE and UART_STEP:
 * https://www.mail-archive.com/openwrt-devel@lists.openwrt.org/msg22371.html
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <asm/ar933x.h>

DECLARE_GLOBAL_DATA_PTR;

static void ar933x_serial_get_scale_step(u32 *uart_scale, u32 *uart_step)
{
	if(ar933x_40MHz_xtal() == 1){
		switch(gd->baudrate){
		case 9600:
			*uart_scale = 34;
			*uart_step = 1101;
			break;
		case 14400:
			*uart_scale = 26;
			*uart_step = 1274;
			break;
		case 19200:
			*uart_scale = 22;
			*uart_step = 1447;
			break;
		case 28800:
			*uart_scale = 26;
			*uart_step = 2548;
			break;
		case 38400:
			*uart_scale = 28;
			*uart_step = 3649;
			break;
		case 56000:
			*uart_scale = 1;
			*uart_step = 367;
			break;
		case 57600:
			*uart_scale = 34;
			*uart_step = 6606;
			break;
		case 115200:
			*uart_scale = 28;
			*uart_step = 10947;
			break;
		case 128000:
			*uart_scale = 6;
			*uart_step = 2936;
			break;
		case 230400:
			*uart_scale = 16;
			*uart_step = 12834;
			break;
		case 256000:
			*uart_scale = 6;
			*uart_step = 5872;
			break;
		case 460800:
			*uart_scale = 7;
			*uart_step = 12079;
			break;
		case 921600:
			*uart_scale = 3;
			*uart_step = 12079;
			break;
		default:
			*uart_scale = (40000000 / (16 * gd->baudrate)) - 1;
			*uart_step = 8192;
		}
	} else {
		switch(gd->baudrate){
		case 9600:
			*uart_scale = 78;
			*uart_step = 3976;
			break;
		case 14400:
			*uart_scale = 98;
			*uart_step = 7474;
			break;
		case 19200:
			*uart_scale = 55;
			*uart_step = 5637;
			break;
		case 28800:
			*uart_scale = 77;
			*uart_step = 11777;
			break;
		case 38400:
			*uart_scale = 36;
			*uart_step = 7449;
			break;
		case 56000:
			*uart_scale = 4;
			*uart_step = 1468;
			break;
		case 57600:
			*uart_scale = 35;
			*uart_step = 10871;
			break;
		case 115200:
			*uart_scale = 20;
			*uart_step = 12683;
			break;
		case 128000:
			*uart_scale = 11;
			*uart_step = 8053;
			break;
		case 230400:
			*uart_scale = 9;
			*uart_step = 12079;
			break;
		case 256000:
			*uart_scale = 5;
			*uart_step = 8053;
			break;
		case 460800:
			*uart_scale = 4;
			*uart_step = 12079;
			break;
		case 921600:
			*uart_scale = 1;
			*uart_step = 9663;
			break;
		default:
			*uart_scale = (25000000 / (16 * gd->baudrate)) - 1;
			*uart_step = 8192;
		}
	}
}

void serial_setbrg(void)
{
	/* TODO: better clock calculation, baudrate, etc. */
	u32 uart_clock;
	u32 uart_scale;
	u32 uart_step;

	ar933x_serial_get_scale_step(&uart_scale, &uart_step);

	uart_clock  = (uart_scale << UART_CLOCK_SCALE_SHIFT);
	uart_clock |= (uart_step  << UART_CLOCK_STEP_SHIFT);

	ar933x_reg_write(UART_CLOCK_REG, uart_clock);
}

int serial_init(void)
{
	u32 uart_cs;

	/*
	 * Set GPIO10 (UART_SO) as output and enable UART,
	 * BIT(15) in GPIO_FUNCTION_1 register must be written with 1
	 */
	ar933x_reg_read_set(GPIO_OE_REG, GPIO10);

	ar933x_reg_read_set(GPIO_FUNCTION_1_REG,
		(1 << GPIO_FUNCTION_1_UART_EN_SHIFT) |
		(1 << 15));

	/*
	 * UART controller configuration:
	 * - no DMA
	 * - no interrupt
	 * - DCE mode
	 * - no flow control
	 * - set RX ready oride
	 * - set TX ready oride
	 */
	uart_cs = (0 << UART_CS_DMA_EN_SHIFT) |
		  (0 << UART_CS_HOST_INT_EN_SHIFT) |
		  (1 << UART_CS_RX_READY_ORIDE_SHIFT) |
		  (1 << UART_CS_TX_READY_ORIDE_SHIFT) |
		  (UART_CS_IFACE_MODE_DCE_VAL << UART_CS_IFACE_MODE_SHIFT) |
		  (UART_CS_FLOW_MODE_NO_VAL   << UART_CS_FLOW_MODE_SHIFT);

	ar933x_reg_write(UART_CS_REG, uart_cs);

	serial_setbrg();

	return 0;
}

void serial_putc(const char c)
{
	u32 uart_data;

	if(c == '\n')
		serial_putc('\r');

	/* Wait for FIFO */
	do{
		uart_data = ar933x_reg_read(UART_DATA_REG);
	} while(((uart_data & UART_TX_CSR_MASK) >> UART_TX_CSR_SHIFT)  == 0);

	/* Put data in buffer and set CSR bit */
	uart_data  = (u32)c | (1 << UART_TX_CSR_SHIFT);

	ar933x_reg_write(UART_DATA_REG, uart_data);
}

int serial_getc(void)
{
	u32 uart_data;

	while(!serial_tstc())
		;

	uart_data = ar933x_reg_read(UART_DATA_REG);

	ar933x_reg_write(UART_DATA_REG, (1 << UART_RX_CSR_SHIFT));

	return (uart_data & UART_TX_RX_DATA_MASK);
}

int serial_tstc(void)
{
	u32 uart_data = ar933x_reg_read(UART_DATA_REG);

	if((uart_data & UART_RX_CSR_MASK) >> UART_RX_CSR_SHIFT){
		return 1;
	}

	return 0;
}

void serial_puts(const char *s)
{
	while(*s){
		serial_putc(*s++);
	}
}
