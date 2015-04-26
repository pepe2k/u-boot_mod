#include <asm/addrspace.h>
#include <asm/types.h>
#include <config.h>
#include <ar7240_soc.h>

#define		REG_OFFSET		4

/* === END OF CONFIG === */

/* register offset */
#define         OFS_RCV_BUFFER          (0*REG_OFFSET)
#define         OFS_TRANS_HOLD          (0*REG_OFFSET)
#define         OFS_SEND_BUFFER         (0*REG_OFFSET)
#define         OFS_INTR_ENABLE         (1*REG_OFFSET)
#define         OFS_INTR_ID             (2*REG_OFFSET)
#define         OFS_DATA_FORMAT         (3*REG_OFFSET)
#define         OFS_LINE_CONTROL        (3*REG_OFFSET)
#define         OFS_MODEM_CONTROL       (4*REG_OFFSET)
#define         OFS_RS232_OUTPUT        (4*REG_OFFSET)
#define         OFS_LINE_STATUS         (5*REG_OFFSET)
#define         OFS_MODEM_STATUS        (6*REG_OFFSET)
#define         OFS_RS232_INPUT         (6*REG_OFFSET)
#define         OFS_SCRATCH_PAD         (7*REG_OFFSET)

#define         OFS_DIVISOR_LSB         (0*REG_OFFSET)
#define         OFS_DIVISOR_MSB         (1*REG_OFFSET)

#define         MY_WRITE(y, z)			((*((volatile u32*)(y))) = z)
#define         UART16550_READ(y)		ar7240_reg_rd((AR7240_UART_BASE+y))
#define         UART16550_WRITE(x, z)	ar7240_reg_wr((AR7240_UART_BASE+x), z)

/*
 * This is taken from [Linux]/include/linux/kernel.h
 * Keep the name unchanged here
 * When this project decides to include that kernel.h some time,
 * this would be found "automatically" and be removed hopefully
 */
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(divisor) __divisor = divisor;		\
	(((x) + ((__divisor) / 2)) / (__divisor));	\
}							\
)

/*
 * Get CPU, RAM and AHB clocks
 * Based on: Linux/arch/mips/ath79/clock.c
 */
void ar7240_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq){
#ifdef CONFIG_WASP
	u32 ref_rate, pll, out_div, ref_div, nint, nfrac, frac, clk_ctrl, postdiv, cpu_pll, ddr_pll;

	// determine reference clock (25 or 40 MHz)
	pll = ar7240_reg_rd(RST_BOOTSTRAP_ADDRESS);

	if(pll & 0x10){	// bit 4 == 1 -> REF_CLK == 40 MHz
		ref_rate = 40000000;
	} else {
		ref_rate = 25000000;
	}

	pll = ar7240_reg_rd(DPLL2_ADDRESS_c4);

	// CPU PLL from SRIF?
	if(pll & (1 << 30)){

		out_div = (pll >> 13) & 0x7;
		pll = ar7240_reg_rd(0x181161c0);
		nint = (pll >> 18) & 0x1ff;
		//nfrac = pll & 0x0003ffff;
		ref_div = (pll >> 27) & 0x1f;
		//frac = 1 << 18;

	} else {
		// only for tests
		// TODO: fix me
		*cpu_freq = 560000000;
		*ddr_freq = 400000000;
		*ahb_freq = 200000000;
		return;
	}

	cpu_pll = (ref_rate / ref_div) * nint;
	cpu_pll /= (1 << out_div);

	// DDR PLL from SRIF?
	pll = ar7240_reg_rd(DPLL2_ADDRESS_44);

	if (pll & (1 << 30)) {

		out_div = (pll >> 13) & 0x7;
		pll = ar7240_reg_rd(0x18116240);
		nint = (pll >> 18) & 0x1ff;
		//nfrac = pll & 0x0003ffff;
		ref_div = (pll >> 27) & 0x1f;
		//frac = 1 << 18;

	} else {
		// only for tests
		// TODO: fix me
		*cpu_freq = 560000000;
		*ddr_freq = 400000000;
		*ahb_freq = 200000000;
		return;
	}

	ddr_pll = (ref_rate / ref_div) * nint;
	ddr_pll /= (1 << out_div);

	clk_ctrl = ar7240_reg_rd(AR934X_CPU_DDR_CLOCK_CONTROL);

	postdiv = (clk_ctrl >> 5) & 0x1f;

	// CPU CLK
	if(clk_ctrl & (1 << 2)){			// CPU_PLL_BYPASS
		*cpu_freq = ref_rate;
	} else if(clk_ctrl & (1 << 20)){	// CPU CLK is derived from CPU_PLL
		*cpu_freq = cpu_pll / (postdiv + 1);
	} else {							// CPU CLK is derived from DDR_PLL
		*cpu_freq = ddr_pll / (postdiv + 1);
	}

	postdiv = (clk_ctrl >> 10) & 0x1f;

	// DDR CLK
	if(clk_ctrl & (1 << 3)){			// DDR_PLL_BYPASS
		*ddr_freq = ref_rate;
	} else if(clk_ctrl & (1 << 21)){	// DDR CLK is derived from DDR_PLL
		*ddr_freq = ddr_pll / (postdiv + 1);
	} else {							// DDR CLK is derived from CPU_PLL
		*ddr_freq = cpu_pll / (postdiv + 1);
	}

	postdiv = (clk_ctrl >> 15) & 0x1f;

	// AHB CLK
	if(clk_ctrl & (1 << 4)){			// AHB_PLL_BYPASS
		*ahb_freq = ref_rate;
	} else if(clk_ctrl & (1 << 24)){	// AHB CLK is derived from DDR_PLL
		*ahb_freq = ddr_pll / (postdiv + 1);
	} else {							// AHB CLK is derived from CPU_PLL
		*ahb_freq = cpu_pll / (postdiv + 1);
	}

#else
    u32 pll, pll_div, ref_div, ahb_div, ddr_div, freq;

    pll = ar7240_reg_rd(AR7240_CPU_PLL_CONFIG);

    pll_div = ((pll & PLL_CONFIG_PLL_DIV_MASK)		>> PLL_CONFIG_PLL_DIV_SHIFT);
    ref_div = ((pll & PLL_CONFIG_PLL_REF_DIV_MASK)	>> PLL_CONFIG_PLL_REF_DIV_SHIFT);
    ddr_div = ((pll & PLL_CONFIG_DDR_DIV_MASK)		>> PLL_CONFIG_DDR_DIV_SHIFT) + 1;
    ahb_div = (((pll & PLL_CONFIG_AHB_DIV_MASK)		>> PLL_CONFIG_AHB_DIV_SHIFT) + 1) * 2;

    freq = pll_div * ref_div * 5000000;

    if(cpu_freq){
		*cpu_freq = freq;
	}

    if(ddr_freq){
		*ddr_freq = freq/ddr_div;
	}

    if(ahb_freq){
		*ahb_freq = freq/ahb_div;
	}
#endif
}

int serial_init(void){
	u32 div, val;
#ifdef CONFIG_WASP
	val = ar7240_reg_rd(WASP_BOOTSTRAP_REG);

	if((val & WASP_REF_CLK_25) == 0){
		div = DIV_ROUND_CLOSEST((25 * 1000000), (16 * CONFIG_BAUDRATE));
	} else {
		div = DIV_ROUND_CLOSEST((40 * 1000000), (16 * CONFIG_BAUDRATE));
	}
#else
	u32 ahb_freq, ddr_freq, cpu_freq;

	ar7240_sys_frequency(&cpu_freq, &ddr_freq, &ahb_freq);

	div = DIV_ROUND_CLOSEST(ahb_freq, (16 * CONFIG_BAUDRATE));

	MY_WRITE(0xb8040000, 0xcff);
	MY_WRITE(0xb8040008, 0x3b);

	val = ar7240_reg_rd(0xb8040028);
	MY_WRITE(0xb8040028,(val | 0x8002));

	MY_WRITE(0xb8040008, 0x2f);
#endif

	/*
	* set DIAB bit
	*/
	UART16550_WRITE(OFS_LINE_CONTROL, 0x80);

	/* set divisor */
	UART16550_WRITE(OFS_DIVISOR_LSB, (div & 0xff));
	UART16550_WRITE(OFS_DIVISOR_MSB, ((div >> 8) & 0xff));

	/* clear DIAB bit*/
	UART16550_WRITE(OFS_LINE_CONTROL, 0x00);

	/* set data format */
	UART16550_WRITE(OFS_DATA_FORMAT, 0x3);

	UART16550_WRITE(OFS_INTR_ENABLE, 0);

	return(0);
}

int serial_tstc(void){
	return(UART16550_READ(OFS_LINE_STATUS) & 0x1);
}

u8 serial_getc(void){
	while(!serial_tstc());
	return(UART16550_READ(OFS_RCV_BUFFER));
}

void serial_putc(u8 byte){
	if(byte == '\n'){
		serial_putc('\r');
	}

	while(((UART16550_READ(OFS_LINE_STATUS)) & 0x20) == 0x0);

	UART16550_WRITE(OFS_SEND_BUFFER, byte);
}

void serial_puts(const char *s){
	while(*s){
		serial_putc(*s++);
	}
}
