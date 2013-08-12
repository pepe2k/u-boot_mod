#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include "ar7240_soc.h"

extern int wasp_ddr_initial_config(uint32_t refresh);
extern int ar7240_ddr_find_size(void);

#define SETBITVAL(val, pos, bit) do {ulong bitval = (bit) ? 0x1 : 0x0; (val) = ((val) & ~(0x1 << (pos))) | ( (bitval) << (pos));} while(0)

void led_toggle(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

	// SYS LED is connected to GPIO 14
	gpio ^= 1 << 14;

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

void all_led_on(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

	// SYS LED (GPIO 14) and WLAN24 (GPIO 13)
	SETBITVAL(gpio, 14, 0);
	SETBITVAL(gpio, 13, 0);

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

void all_led_off(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

	// SYS LED (GPIO 14) and WLAN24 (GPIO 13)
	SETBITVAL(gpio, 14, 1);
	SETBITVAL(gpio, 13, 1);

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

// get button status
int reset_button_status(void){
	// RESET BUTTON is connected to GPIO 16
	if(ar7240_reg_rd(AR7240_GPIO_IN) & (1 << 16)){
		return 0;
	} else {
		return 1;
	}
}

void gpio_config(void){
	/* disable the CLK_OBS on GPIO_4 and set GPIO4 as input */
	ar7240_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 4));
	ar7240_reg_rmw_clear(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK);
	ar7240_reg_rmw_set(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_SET(0x80));
	ar7240_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 4));
}

void ath_set_tuning_caps(void){
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

int wasp_mem_config(void){
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

	gpio_config();

	/* Needed here not to mess with Ethernet clocks */
	ath_set_tuning_caps();
	
	// return memory size
	return(ar7240_ddr_find_size());
}

long int initdram(){
	return((long int)wasp_mem_config());
}
