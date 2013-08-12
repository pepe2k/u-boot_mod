#include <asm/addrspace.h>
#include <asm/types.h>
#include <config.h>
#include <hornet_soc.h>

#define uart_reg_read(x)        ar7240_reg_rd( (AR7240_UART_BASE+x) )
#define uart_reg_write(x, y)    ar7240_reg_wr( (AR7240_UART_BASE+x), y)

static int AthrUartGet(char *__ch_data) {
	u32 rdata;

	rdata = uart_reg_read(UARTDATA_ADDRESS);

	if (UARTDATA_UARTRXCSR_GET(rdata)) {
		*__ch_data = (char) UARTDATA_UARTTXRXDATA_GET(rdata);
		rdata = UARTDATA_UARTRXCSR_SET(1);
		uart_reg_write(UARTDATA_ADDRESS, rdata);
		return 1;
	} else {
		return 0;
	}
}

static void AthrUartPut(char __ch_data) {
	u32 rdata;

	do {
		rdata = uart_reg_read(UARTDATA_ADDRESS);
	} while (UARTDATA_UARTTXCSR_GET(rdata) == 0);

	rdata = UARTDATA_UARTTXRXDATA_SET((u32)__ch_data);
	rdata |= UARTDATA_UARTTXCSR_SET(1);

	uart_reg_write(UARTDATA_ADDRESS, rdata);
}

void ar7240_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq) {
	// TODO: check the following code
	u32 ref_clock_rate, pll_freq;
	u32 pllreg, clockreg;
	u32 nint, refdiv, outdiv;
	u32 cpu_div, ahb_div, ddr_div;

	if (ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) & HORNET_BOOTSTRAP_SEL_25M_40M_MASK) {
		ref_clock_rate = 40 * 1000000;
	} else {
		ref_clock_rate = 25 * 1000000;
	}

	pllreg = ar7240_reg_rd(AR7240_CPU_PLL_CONFIG);
	clockreg = ar7240_reg_rd(AR7240_CPU_CLOCK_CONTROL);

	if (clockreg & HORNET_CLOCK_CONTROL_BYPASS_MASK) {
		/* Bypass PLL */
		pll_freq = ref_clock_rate;
		cpu_div = ahb_div = ddr_div = 1;
	} else {
		nint = (pllreg & HORNET_PLL_CONFIG_NINT_MASK) >> HORNET_PLL_CONFIG_NINT_SHIFT;
		refdiv = (pllreg & HORNET_PLL_CONFIG_REFDIV_MASK) >> HORNET_PLL_CONFIG_REFDIV_SHIFT;
		outdiv = (pllreg & HORNET_PLL_CONFIG_OUTDIV_MASK) >> HORNET_PLL_CONFIG_OUTDIV_SHIFT;

		pll_freq = (ref_clock_rate / refdiv) * nint;

		if (outdiv == 1)
			pll_freq /= 2;
		else if (outdiv == 2)
			pll_freq /= 4;
		else if (outdiv == 3)
			pll_freq /= 8;
		else if (outdiv == 4)
			pll_freq /= 16;
		else if (outdiv == 5)
			pll_freq /= 32;
		else if (outdiv == 6)
			pll_freq /= 64;
		else if (outdiv == 7)
			pll_freq /= 128;
		else
			/* outdiv == 0 --> illegal value */
			pll_freq /= 2;

		cpu_div = (clockreg & HORNET_CLOCK_CONTROL_CPU_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_CPU_POST_DIV_SHIFT;
		ddr_div = (clockreg & HORNET_CLOCK_CONTROL_DDR_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_DDR_POST_DIV_SFIFT;
		ahb_div = (clockreg & HORNET_CLOCK_CONTROL_AHB_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_AHB_POST_DIV_SFIFT;

		/*
		 * b00 : div by 1, b01 : div by 2, b10 : div by 3, b11 : div by 4
		 */
		cpu_div++;
		ddr_div++;
		ahb_div++;
	}

	*cpu_freq = pll_freq / cpu_div;
	*ddr_freq = pll_freq / ddr_div;
	*ahb_freq = pll_freq / ahb_div;
}

int serial_init(void) {
	u32 rdata;
	u32 baudRateDivisor, clock_step;
	u32 fcEnable = 0;
	u32 ahb_freq, ddr_freq, cpu_freq;

	ar7240_sys_frequency(&cpu_freq, &ddr_freq, &ahb_freq);

	/* GPIO Configuration */
	ar7240_reg_wr(AR7240_GPIO_OE, 0xcff);
	rdata = ar7240_reg_rd(AR7240_GPIO_OUT);
	rdata |= 0x400; // GPIO 10 (UART_SOUT) must output 1
	ar7240_reg_wr(AR7240_GPIO_OUT, rdata);

	rdata = ar7240_reg_rd(AR7240_GPIO_FUNC);
	/* GPIO_FUN, bit1/UART_EN, bit2/UART_RTS_CTS_EN, bit15(disable_s26_uart) */
	rdata |= (0x3 << 1) | (0x1 << 15);
	ar7240_reg_wr(AR7240_GPIO_FUNC, rdata);

	/* Get reference clock rate, then set baud rate to 115200 */
	// TODO: check the following code
	rdata = ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS);
	rdata &= HORNET_BOOTSTRAP_SEL_25M_40M_MASK;

	if (rdata) {
		baudRateDivisor = (40000000 / (16 * 115200)) - 1; // 40 MHz clock is taken as UART clock
	} else {
		baudRateDivisor = (25000000 / (16 * 115200)) - 1; // 25 MHz clock is taken as UART clock
	}

	clock_step = 8192;

	rdata = UARTCLOCK_UARTCLOCKSCALE_SET(baudRateDivisor) | UARTCLOCK_UARTCLOCKSTEP_SET(clock_step);
	uart_reg_write(UARTCLOCK_ADDRESS, rdata);

	/* Config Uart Controller */
	/* No interrupt */
	rdata = UARTCS_UARTDMAEN_SET(0) | UARTCS_UARTHOSTINTEN_SET(0) | UARTCS_UARTHOSTINT_SET(0) | UARTCS_UARTSERIATXREADY_SET(0) | UARTCS_UARTTXREADYORIDE_SET(~fcEnable) | UARTCS_UARTRXREADYORIDE_SET(~fcEnable) | UARTCS_UARTHOSTINTEN_SET(0);

	/* is_dte == 1 */
	rdata = rdata | UARTCS_UARTINTERFACEMODE_SET(2);

	if (fcEnable) {
		rdata = rdata | UARTCS_UARTFLOWCONTROLMODE_SET(2);
	}

	/* invert_fc ==0 (Inverted Flow Control) */
	//rdata = rdata | UARTCS_UARTFLOWCONTROLMODE_SET(3);
	/* parityEnable == 0 */
	//rdata = rdata | UARTCS_UARTPARITYMODE_SET(2); -->Parity Odd
	//rdata = rdata | UARTCS_UARTPARITYMODE_SET(3); -->Parity Even
	uart_reg_write(UARTCS_ADDRESS, rdata);

	return 0;
}

int serial_tstc(void) {
	return (UARTDATA_UARTRXCSR_GET(uart_reg_read(UARTDATA_ADDRESS)));
}

u8 serial_getc(void) {
	char ch_data;

	while (!AthrUartGet(&ch_data))
		;

	return (u8) ch_data;
}

void serial_putc(u8 byte) {
	if (byte == '\n') AthrUartPut('\r');

	AthrUartPut((char) byte);
}

void serial_puts(const char *s) {
	while (*s) {
		serial_putc(*s++);
	}
}
