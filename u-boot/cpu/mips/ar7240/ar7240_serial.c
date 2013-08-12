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

void ar7240_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq){
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
}

int serial_init(void){
	u32 div, val;
	u32 ahb_freq, ddr_freq, cpu_freq;

#ifdef CONFIG_WASP
	val = ar7240_reg_rd(WASP_BOOTSTRAP_REG);

	if((val & WASP_REF_CLK_25) == 0){
		div = (25 * 1000000) / (16 * CONFIG_BAUDRATE);
	} else {
		div = (40 * 1000000) / (16 * CONFIG_BAUDRATE);
	}
#else
	ar7240_sys_frequency(&cpu_freq, &ddr_freq, &ahb_freq);

	div = ahb_freq/(16 * CONFIG_BAUDRATE);

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
