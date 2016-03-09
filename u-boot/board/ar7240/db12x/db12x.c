#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include <soc/qca_soc_common.h>
#include "ar7240_soc.h"

extern int wasp_ddr_initial_config(uint32_t refresh);

void ath_set_tuning_caps(void)
{
	typedef struct {
		u_int8_t pad[0x28];
		u_int8_t params_for_tuning_caps[2];
		u_int8_t featureEnable;
	} __attribute__((__packed__)) ar9300_eeprom_t;

	ar9300_eeprom_t	*eep = (ar9300_eeprom_t *)WLANCAL;
	uint32_t val = 0;

	/* checking feature enable bit 6 and caldata is valid */
	if((eep->featureEnable & 0x40) && (eep->pad[0x0] != 0xff)){
		/* xtal_capin -bit 17:23 and xtag_capout -bit 24:30*/
		val = (eep->params_for_tuning_caps[0] & 0x7f) << 17;
		val |= (eep->params_for_tuning_caps[0] & 0x7f) << 24;
	} else {
		/* default when no caldata available*/
		/* checking clock in bit 4 */
		if(ar7240_reg_rd(RST_BOOTSTRAP_ADDRESS) & 0x10){
			val = (0x1020 << 17);	/*default 0x2040 for 40Mhz clock*/
		} else {
			val = (0x2040 << 17);	/*default 0x4080 for 25Mhz clock*/
		}
	}

	val |= (ar7240_reg_rd(XTAL_ADDRESS) & (((1 << 17) - 1) | (1 << 31)));
	ar7240_reg_wr(XTAL_ADDRESS, val);

	//prmsg("Setting 0xb8116290 to 0x%x\n", val);
	return;
}

int wasp_mem_config(void)
{
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	unsigned int reg32;

	wasp_ddr_initial_config(CFG_DDR_REFRESH_VAL);

	/* Take WMAC out of reset */
	reg32 = ar7240_reg_rd(AR7240_RESET);
	reg32 = reg32 & ~AR7240_RESET_WMAC;

	ar7240_reg_wr_nf(AR7240_RESET, reg32);

	/* Switching regulator settings */
	ar7240_reg_wr_nf(0x18116c40, 0x633c8176); /* AR_PHY_PMU1 */
	ar7240_reg_wr_nf(0x18116c44, 0x10380000); /* AR_PHY_PMU2 */

	//wasp_usb_initial_config();

	/* Needed here not to mess with Ethernet clocks */
	ath_set_tuning_caps();

#endif
	// return memory size
	return (int)qca_dram_size();
}

long int dram_init()
{
	return (long int)wasp_mem_config();
}
