#include <config.h>
#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>

#include "ar7240_soc.h"

#if !defined(COMPRESSED_UBOOT)
extern void	ar933x_ddr_init(void);
#endif

extern int ar7240_ddr_find_size(void);
extern void ar933x_ddr_tap_init(void);

int ar7240_mem_config(void)
{
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	#ifndef COMPRESSED_UBOOT
	ar933x_ddr_init();
	#endif

	/* Default tap values for starting the tap_init*/
	ar7240_reg_wr(AR7240_DDR_TAP_CONTROL0, CFG_DDR_TAP0_VAL);
	ar7240_reg_wr(AR7240_DDR_TAP_CONTROL1, CFG_DDR_TAP1_VAL);
#endif

	all_led_off();

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	ar933x_ddr_tap_init();
#endif

	// return memory size
	return ar7240_ddr_find_size();
}

long int dram_init()
{
	return (long int)ar7240_mem_config();
}
