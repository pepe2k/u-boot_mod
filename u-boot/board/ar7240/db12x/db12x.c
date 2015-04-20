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

	gpio = ar7240_reg_rd(AR934X_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1) || \
	defined(CONFIG_FOR_TPLINK_WDR3500_V1) || \
	defined(CONFIG_FOR_TPLINK_WR841N_V8) || \
	defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2) || \
	defined(CONFIG_FOR_TPLINK_MR3420_V2)
	gpio ^= 1 << GPIO_SYS_LED_BIT;
#else
	#error "Custom GPIO in leg_toggle() not defined!"
#endif

	ar7240_reg_wr(AR934X_GPIO_OUT, gpio);
}

void all_led_on(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR934X_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_2G_LED_BIT,  GPIO_WLAN_2G_LED_ON);
	SETBITVAL(gpio, GPIO_USB1_LED_BIT,     GPIO_USB1_LED_ON);
	SETBITVAL(gpio, GPIO_USB2_LED_BIT,     GPIO_USB2_LED_ON);
	//SETBITVAL(gpio, GPIO_QSS_LED_BIT,      GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_2G_LED_BIT,  GPIO_WLAN_2G_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      GPIO_QSS_LED_ON);
	SETBITVAL(gpio, GPIO_USB_LED_BIT,      GPIO_USB_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_USB_LED_BIT,      GPIO_USB_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_LAN_LED_BIT,      GPIO_LAN_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      GPIO_QSS_LED_ON);
#else
	#error "Custom GPIO in all_led_on() not defined!"
#endif

	ar7240_reg_wr(AR934X_GPIO_OUT, gpio);
}

void all_led_off(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR934X_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_2G_LED_BIT,  !GPIO_WLAN_2G_LED_ON);
	SETBITVAL(gpio, GPIO_USB1_LED_BIT,     !GPIO_USB1_LED_ON);
	SETBITVAL(gpio, GPIO_USB2_LED_BIT,     !GPIO_USB2_LED_ON);
	//SETBITVAL(gpio, GPIO_QSS_LED_BIT,      !GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_2G_LED_BIT,  !GPIO_WLAN_2G_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     !GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     !GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     !GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     !GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      !GPIO_QSS_LED_ON);
	SETBITVAL(gpio, GPIO_USB_LED_BIT,      !GPIO_USB_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     !GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     !GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     !GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     !GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      !GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT,     !GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT,     !GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT,     !GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT,     !GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_USB_LED_BIT,      !GPIO_USB_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      !GPIO_QSS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT,      !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_LAN_LED_BIT,      !GPIO_LAN_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT,     !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT,      !GPIO_QSS_LED_ON);
#else
	#error "Custom GPIO in all_led_off() not defined!"
#endif

	ar7240_reg_wr(AR934X_GPIO_OUT, gpio);
}

// get button status
#ifndef GPIO_RST_BUTTON_BIT
	#error "GPIO_RST_BUTTON_BIT not defined!"
#endif
int reset_button_status(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR934X_GPIO_IN);

	if(gpio & (1 << GPIO_RST_BUTTON_BIT)){
#if defined(GPIO_RST_BUTTON_IS_ACTIVE_LOW)
		return(0);
#else
		return(1);
#endif
	} else {
#if defined(GPIO_RST_BUTTON_IS_ACTIVE_LOW)
		return(1);
#else
		return(0);
#endif
	}
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
	return(ar7240_ddr_find_size());
}

long int initdram(){
	return((long int)wasp_mem_config());
}

#ifndef COMPRESSED_UBOOT
int checkboard(void){
	printf(BOARD_CUSTOM_STRING"\n\n");
	return(0);
}
#endif

/*
 * Returns a string with memory type preceded by a space sign
 */
const char* print_mem_type(void){
	unsigned int reg;

	reg = ar7240_reg_rd(WASP_BOOTSTRAP_REG);

	// if SDRAM is disabled -> we are using DDR
	if(reg & WASP_BOOTSTRAP_SDRAM_DISABLE_MASK){

		// 1 -> DDR1
		if(reg & WASP_BOOTSTRAP_DDR_SELECT_MASK){
			if(reg & WASP_BOOTSTRAP_DDR_WIDTH_MASK){
				return " DDR 32-bit";
			} else {
				return " DDR 16-bit";
			}
		} else {
			if(reg & WASP_BOOTSTRAP_DDR_WIDTH_MASK){
				return " DDR2 32-bit";
			} else {
				return " DDR2 16-bit";
			}
		}

	} else {
		return " SDRAM";
	}
}