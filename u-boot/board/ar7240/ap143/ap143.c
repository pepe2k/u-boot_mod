#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include <atheros.h>
#include <soc/qca_soc_common.h>

extern int ath_ddr_initial_config(uint32_t refresh);
extern int ath_ddr_find_size(void);

#define SETBITVAL(val, pos, bit) do {ulong bitval = (bit) ? 0x1 : 0x0; (val) = ((val) & ~(0x1 << (pos))) | ( (bitval) << (pos));} while(0)

void led_toggle(void)
{
	u32 gpio = qca_soc_reg_read(QCA_GPIO_OUT_REG);

#if defined(CONFIG_FOR_TPLINK_WR820N_CH)
	gpio ^= 1 << GPIO_SYS_LED_BIT;
#else
	#error "Custom GPIO in leg_toggle() not defined!"
#endif

	qca_soc_reg_write(QCA_GPIO_OUT_REG, gpio);
}

void all_led_on(void)
{
	u32 gpio = qca_soc_reg_read(QCA_GPIO_OUT_REG);

#if defined(CONFIG_FOR_TPLINK_WR820N_CH)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, GPIO_SYS_LED_ON);
#else
	#error "Custom GPIO in all_led_on() not defined!"
#endif

	qca_soc_reg_write(QCA_GPIO_OUT_REG, gpio);
}

void all_led_off(void)
{
	u32 gpio = qca_soc_reg_read(QCA_GPIO_OUT_REG);

#if defined(CONFIG_FOR_TPLINK_WR820N_CH)
	SETBITVAL(gpio, GPIO_SYS_LED_BIT, !GPIO_SYS_LED_ON);
#else
	#error "Custom GPIO in all_led_on() not defined!"
#endif

	qca_soc_reg_write(QCA_GPIO_OUT_REG, gpio);
}

int reset_button_status(void)
{
#ifndef GPIO_RST_BUTTON_BIT
	return 0;
#else
	u32 gpio = qca_soc_reg_read(QCA_GPIO_IN_REG);

	if(gpio & (1 << GPIO_RST_BUTTON_BIT)){
  #if defined(GPIO_RST_BUTTON_IS_ACTIVE_LOW)
		return 0 ;
  #else
		return 1 ;
  #endif
	} else {
  #if defined(GPIO_RST_BUTTON_IS_ACTIVE_LOW)
		return 1;
  #else
		return 0;
  #endif
	}
#endif
}

int gpio_init(void)
{
	return 0;
}

void ath_set_tuning_caps(void)
{
	typedef struct {
		u_int8_t	pad[0x28],
				params_for_tuning_caps[2],
				featureEnable;
	} __attribute__((__packed__)) ar9300_eeprom_t;

	ar9300_eeprom_t	*eep;
	uint32_t	val;

	eep = (ar9300_eeprom_t *)WLANCAL;

	val =	XTAL_TCXODET_SET(0x0) |
		XTAL_XTAL_CAPINDAC_SET(0x4b) |
		XTAL_XTAL_CAPOUTDAC_SET(0x4b) |
		XTAL_XTAL_DRVSTR_SET(0x3) |
		XTAL_XTAL_SHORTXIN_SET(0x0) |
		XTAL_XTAL_LOCALBIAS_SET(0x1) |
		XTAL_XTAL_PWDCLKD_SET(0x0) |
		XTAL_XTAL_BIAS2X_SET(0x0) |
		XTAL_XTAL_LBIAS2X_SET(0x0) |
		XTAL_XTAL_OSCON_SET(0x1) |
		XTAL_XTAL_PWDCLKIN_SET(0x0) |
		XTAL_LOCAL_XTAL_SET(0x0) |
		XTAL_PWD_SWREGCLK_SET(0x0) |
		XTAL_SPARE_SET(0x0);

	/* checking feature enable bit 6 and caldata is valid */
	if ((eep->featureEnable & 0x40) && (eep->pad[0x0] != 0xff)) {
		val &= ~(XTAL_XTAL_CAPINDAC_MASK | XTAL_XTAL_CAPOUTDAC_MASK);
		val |=	XTAL_XTAL_CAPINDAC_SET(eep->params_for_tuning_caps[0]) |
			XTAL_XTAL_CAPOUTDAC_SET(eep->params_for_tuning_caps[0]);
	}

	ath_reg_wr(XTAL_ADDRESS, val);
	ath_reg_wr(XTAL2_ADDRESS, XTAL2_DCA_BYPASS_SET(0x1) |
					XTAL2_FSM_START_L_SET(0x1));
	ath_reg_wr(XTAL3_ADDRESS, XTAL3_EVAL_LENGTH_SET(0x400) |
					XTAL3_HARMONIC_NUMBER_SET(0x51));

#define __str(x)	# x
#define str(x)		__str(x)

	//printf("Setting " str(XTAL_ADDRESS) " to 0x%x\n", val);
	return;
}

void ath_usb_initial_config(void)
{
#define unset(a)	(~(a))

	if (ath_reg_rd(RST_BOOTSTRAP_ADDRESS) & RST_BOOTSTRAP_TESTROM_ENABLE_MASK) {

		ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_USB_HOST_RESET_SET(1));
		udelay(1000);
		ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_USB_PHY_RESET_SET(1));
		udelay(1000);

		ath_reg_wr(PHY_CTRL5_ADDRESS, PHY_CTRL5_RESET_1);
		udelay(1000);

		ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_USB_PHY_PLL_PWD_EXT_SET(1));
		udelay(1000);
		ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_USB_PHY_ARESET_SET(1));
		udelay(1000);

		ath_reg_rmw_clear(RST_CLKGAT_EN_ADDRESS, RST_CLKGAT_EN_USB1_SET(1));

		return;
	}

	ath_reg_wr_nf(SWITCH_CLOCK_SPARE_ADDRESS,
		ath_reg_rd(SWITCH_CLOCK_SPARE_ADDRESS) |
		SWITCH_CLOCK_SPARE_USB_REFCLK_FREQ_SEL_SET(2));
	udelay(1000);

	ath_reg_rmw_set(RST_RESET_ADDRESS,
				RST_RESET_USB_PHY_SUSPEND_OVERRIDE_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_ARESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_RESET_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_HOST_RESET_SET(1));
	udelay(1000);

	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_USB_PHY_PLL_PWD_EXT_SET(1));
	udelay(10);
}

void ath_gpio_config(void)
{
	/* disable the CLK_OBS on GPIO_4 and set GPIO4 as input */
#if 0
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 4));
	ath_reg_rmw_clear(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_MASK);
	ath_reg_rmw_set(GPIO_OUT_FUNCTION1_ADDRESS, GPIO_OUT_FUNCTION1_ENABLE_GPIO_4_SET(0x80));
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 4));
#endif

#if 0
	/* Set GPIO 13 as input for LED functionality to be OFF during bootup */
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 13));
	/* Turn off JUMPST_LED and 5Gz LED during bootup */
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 15));
#endif
	ath_reg_rmw_set(GPIO_OE_ADDRESS, (1 << 12));

}

int ath_mem_config(void)
{
	unsigned int type, reg32, *tap;
	extern uint32_t *ath_ddr_tap_cal(void);

#if !defined(CONFIG_ATH_EMULATION)

	type = ath_ddr_initial_config(CFG_DDR_REFRESH_VAL);

	tap = ath_ddr_tap_cal();
	//prmsg("tap = 0x%p\n", tap);

	tap = (uint32_t *)0xbd001f10;
	//prmsg("Tap (low, high) = (0x%x, 0x%x)\n", tap[0], tap[1]);

	tap = (uint32_t *)TAP_CONTROL_0_ADDRESS;
	//prmsg("Tap values = (0x%x, 0x%x, 0x%x, 0x%x)\n",
	//	tap[0], tap[2], tap[2], tap[3]);

	/* Take WMAC out of reset */
	reg32 = ath_reg_rd(RST_RESET_ADDRESS);
	reg32 = reg32 & ~RST_RESET_RTC_RESET_SET(1);
	ath_reg_wr_nf(RST_RESET_ADDRESS, reg32);

	ath_usb_initial_config();

	ath_gpio_config();
#endif /* !defined(CONFIG_ATH_EMULATION) */

	//ath_set_tuning_caps();

	return ath_ddr_find_size();
}

long int dram_init()
{
	return ath_mem_config();
}
