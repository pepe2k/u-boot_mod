#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include "ar7240_soc.h"

#ifndef COMPRESSED_UBOOT
extern void	ar7240_ddr_initial_config(uint32_t refresh);
#endif
extern int ar7240_ddr_find_size(void);
extern void hornet_ddr_tap_init(void);

#define SETBITVAL(val, pos, bit) do {ulong bitval = (bit) ? 0x1 : 0x0; (val) = ((val) & ~(0x1 << (pos))) | ( (bitval) << (pos));} while(0)

void led_toggle(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_MR3020_V1)
	gpio ^= 1 << GPIO_WPS_LED_BIT;
#elif defined(CONFIG_FOR_TPLINK_WR703N_V1) || defined(CONFIG_FOR_TPLINK_WR720N_V3) || defined(CONFIG_FOR_TPLINK_WR710N_V1)
	gpio ^= 1 << GPIO_SYS_LED_BIT;
#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)
	gpio ^= 1 << GPIO_INTERNET_LED_BIT;
#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)
	gpio ^= 1 << GPIO_SYS_LED_BIT;
#elif defined(CONFIG_FOR_TPLINK_WR740N_V4) || defined(CONFIG_FOR_TPLINK_MR3220_V2)
	gpio ^= 1 << GPIO_SYS_LED_BIT;
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	gpio ^= 1 << GPIO_WLAN_LED_BIT;
#else
	#error "Custom GPIO in leg_toggle() not defined!"
#endif

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

void all_led_on(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_MR3020_V1)
	SETBITVAL(gpio, GPIO_WPS_LED_BIT, GPIO_WPS_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_ETH_LED_BIT, GPIO_ETH_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR703N_V1) || defined(CONFIG_FOR_TPLINK_WR720N_V3) || defined (CONFIG_FOR_TPLINK_WR710N_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, GPIO_SYS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_ETH_LED_BIT, GPIO_ETH_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, GPIO_SYS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR740N_V4) || defined(CONFIG_FOR_TPLINK_MR3220_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT, GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT, GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT, GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT, GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT, GPIO_QSS_LED_ON);

	#ifdef CONFIG_FOR_TPLINK_MR3220_V2
	SETBITVAL(gpio, GPIO_USB_LED_BIT, GPIO_USB_LED_ON);
	#endif
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, GPIO_WLAN_LED_ON);
#else
	#error "Custom GPIO in all_led_on() not defined!"
#endif

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

void all_led_off(void){
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

#if defined(CONFIG_FOR_TPLINK_MR3020_V1)
	SETBITVAL(gpio, GPIO_WPS_LED_BIT, !GPIO_WPS_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_ETH_LED_BIT, !GPIO_ETH_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR703N_V1) || defined(CONFIG_FOR_TPLINK_WR720N_V3) || defined (CONFIG_FOR_TPLINK_WR710N_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, !GPIO_SYS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_ETH_LED_BIT, !GPIO_ETH_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, !GPIO_SYS_LED_ON);
#elif defined(CONFIG_FOR_TPLINK_WR740N_V4) || defined(CONFIG_FOR_TPLINK_MR3220_V2)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, !GPIO_SYS_LED_ON);
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, !GPIO_WLAN_LED_ON);
	SETBITVAL(gpio, GPIO_LAN1_LED_BIT, !GPIO_LAN1_LED_ON);
	SETBITVAL(gpio, GPIO_LAN2_LED_BIT, !GPIO_LAN2_LED_ON);
	SETBITVAL(gpio, GPIO_LAN3_LED_BIT, !GPIO_LAN3_LED_ON);
	SETBITVAL(gpio, GPIO_LAN4_LED_BIT, !GPIO_LAN4_LED_ON);
	SETBITVAL(gpio, GPIO_INTERNET_LED_BIT, !GPIO_INTERNET_LED_ON);
	SETBITVAL(gpio, GPIO_QSS_LED_BIT, !GPIO_QSS_LED_ON);

	#ifdef CONFIG_FOR_TPLINK_MR3220_V2
	SETBITVAL(gpio, GPIO_USB_LED_BIT, !GPIO_USB_LED_ON);
	#endif
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	SETBITVAL(gpio, GPIO_WLAN_LED_BIT, !GPIO_WLAN_LED_ON);
#else
	#error "Custom GPIO in all_led_off() not defined!"
#endif

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);
}

// get button status
#ifndef GPIO_RST_BUTTON_BIT
	#error "GPIO_RST_BUTTON_BIT not defined!"
#endif
int reset_button_status(void){
	if(ar7240_reg_rd(AR7240_GPIO_IN) & (1 << GPIO_RST_BUTTON_BIT)){
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

void gpio_config(void){
#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
    /* Disable clock obs
     * clk_obs1(gpio13/bit8),  clk_obs2(gpio14/bit9), clk_obs3(gpio15/bit10),
     * clk_obs4(gpio16/bit11), clk_obs5(gpio17/bit12)
     * clk_obs0(gpio1/bit19), 6(gpio11/bit20)
     */
    ar7240_reg_wr(AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & ~((0x1f<<8)|(0x3<<19))));


    /* Enable eth Switch LEDs */
    ar7240_reg_wr(AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) | (0x1f<<3)));


    //Turn on status leds:
    //set output enable
    ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) |(1<<0)));

    //set WLAN LED output to low (reverse polarity LED)
    //ar7240_reg_wr(AR7240_GPIO_CLEAR, (1<<0));

    /* Clear AR7240_GPIO_FUNC BIT2 to ensure that software can control LED5(GPIO16) and LED6(GPIO17)  */
    ar7240_reg_wr(AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & ~(0x1<<2)));
#else
	/* Disable clock obs 
	 * clk_obs1(gpio13/bit8),  clk_obs2(gpio14/bit9), clk_obs3(gpio15/bit10),
	 * clk_obs4(gpio16/bit11), clk_obs5(gpio17/bit12)
	 * clk_obs0(gpio1/bit19), 6(gpio11/bit20)
	 */

	ar7240_reg_wr(AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xEF84E0FB));

	/* Disable EJTAG functionality to enable GPIO functionality */
	ar7240_reg_wr(AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) | 0x8001));

	/* Set HORNET_BOOTSTRAP_STATUS BIT18 to ensure that software can control GPIO26 and GPIO27 */
	ar7240_reg_wr(HORNET_BOOTSTRAP_STATUS, (ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) | (0x1<<18)));
#endif

#if defined(CONFIG_FOR_TPLINK_MR3020_V1)

	/* LED's GPIOs on MR3020:
	 *
	 * 0	=> WLAN
	 * 17	=> ETH
	 * 26	=> WPS
	 * 27	=> INTERNET
	 *
	 */

	/* set OE, added by zcf, 20110509 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0xC020001));

	/* Disable clock obs, added by zcf, 20110509 */
	//ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e07f));
#elif defined(CONFIG_FOR_TPLINK_WR703N_V1) || defined(CONFIG_FOR_TPLINK_WR720N_V3) || defined(CONFIG_FOR_TPLINK_WR710N_V1)

	/* LED's GPIOs on WR703N/WR720Nv3/WR710N:
	 *
	 * 27	=> SYS
	 *
	 */

	/* set OE, added by zcf, 20110714 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0x8000000));
#elif defined(CONFIG_FOR_TPLINK_MR3040_V1V2)

	/* LED's GPIOs on MR3040:
	 *
	 * 26	=> WLAN
	 * 17	=> ETH
	 * 27	=> INTERNET
	 *
	 */

	/* set OE, added by zcf, 20110509 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0xC020000));

	/* Disable clock obs, added by zcf, 20110509 */
	//ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e07f));
#elif defined(CONFIG_FOR_TPLINK_MR10U_V1)

	/* LED's GPIOs on MR10U:
	 *
	 * 27	=> SYS
	 *
	 */

	/* set OE, added by zcf, 20110714 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0x8000000));
#elif defined(CONFIG_FOR_TPLINK_WR740N_V4)

	/* LED's GPIOs on WR740Nv4:
	 *
	 * 0	=> WLAN
	 * 1	=> QSS
	 * 13	=> INTERNET
	 * 14	=> LAN1
	 * 15	=> LAN2
	 * 16	=> LAN3
	 * 17	=> LAN4
	 * 27	=> SYS
	 *
	 */

	/* set OE, added by zcf, 20110509 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0x803E003));

	/* Disable clock obs, added by zcf, 20110509 */
	//ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e07f));
#elif defined(CONFIG_FOR_TPLINK_MR3220_V2)

	/* LED's GPIOs on MR3220v2:
	 *
	 * 0	=> WLAN
	 * 1	=> QSS
	 * 13	=> INTERNET
	 * 14	=> LAN1
	 * 15	=> LAN2
	 * 16	=> LAN3
	 * 17	=> LAN4
	 * 26	=> USB
	 * 27	=> SYS
	 *
	 */

	/* set OE, added by zcf, 20110509 */
	ar7240_reg_wr(AR7240_GPIO_OE, (ar7240_reg_rd(AR7240_GPIO_OE) | 0xC03E003));

	/* Disable clock obs, added by zcf, 20110509 */
	//ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e07f));
#elif defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
	// TODO: check GPIO config for C2
#else
	#error "Custom GPIO config in gpio_config() not defined!"
#endif
}

int ar7240_mem_config(void){
#ifndef COMPRESSED_UBOOT
	ar7240_ddr_initial_config(CFG_DDR_REFRESH_VAL);
#endif

	/* Default tap values for starting the tap_init*/
	ar7240_reg_wr(AR7240_DDR_TAP_CONTROL0, CFG_DDR_TAP0_VAL);
	ar7240_reg_wr(AR7240_DDR_TAP_CONTROL1, CFG_DDR_TAP1_VAL);

	gpio_config();
	all_led_off();

#ifndef COMPRESSED_UBOOT
	ar7240_ddr_tap_init();
#else
	hornet_ddr_tap_init();
#endif

	// return memory size
	return(ar7240_ddr_find_size());
}

long int initdram(){
	return((long int)ar7240_mem_config());
}

#ifndef COMPRESSED_UBOOT
int checkboard(void){
	printf(BOARD_CUSTOM_STRING"\n\n");
	return(0);
}
#endif
