/*
 * Copyright (C) 2017 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <soc/qca_soc_common.h>

#ifndef _CMD_QCAGPIO_H_
#define _CMD_QCAGPIO_H_

#if defined(CONFIG_CMD_GPIO)

#if (SOC_TYPE & QCA_AR933X_SOC)

typedef struct {
	u32 reg_mask;
	u32 gpio_mask;
	char *name;
} gpio_func;

static const gpio_func gpio_funcs_1[] = {
	{
		.reg_mask  = QCA_GPIO_FUNC_1_UART_EN_MASK,
		.gpio_mask = GPIO9 | GPIO10,
		.name      = "uart"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_UART_RTS_CTS_EN_MASK,
		.gpio_mask = GPIO11 | GPIO12,
		.name      = "uart_rts_cts"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED0_EN_MASK,
		.gpio_mask = GPIO13,
		.name      = "switch_led0"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED1_EN_MASK,
		.gpio_mask = GPIO14,
		.name      = "switch_led1"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED2_EN_MASK,
		.gpio_mask = GPIO15,
		.name      = "switch_led2"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED3_EN_MASK,
		.gpio_mask = GPIO16,
		.name      = "switch_led3"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED4_EN_MASK,
		.gpio_mask = GPIO17,
		.name      = "switch_led4"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_SPI_CS_EN1_MASK,
		.gpio_mask = GPIO9,
		.name      = "spi_cs1"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_SPI_CS_EN2_MASK,
		.gpio_mask = GPIO10,
		.name      = "spi_cs2"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_SPI_EN_MASK,
		.gpio_mask = GPIO2 | GPIO3 | GPIO4 | GPIO5,
		.name      = "spi"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED_ACT_MASK,
		.gpio_mask = 0,
		.name      = "switch_led_act"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED_COLL_MASK,
		.gpio_mask = 0,
		.name      = "switch_led_col"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_ETH_SW_LED_DUPL_MASK,
		.gpio_mask = 0,
		.name      = "switch_led_dup"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_I2S_EN_MASK,
		.gpio_mask = GPIO6 | GPIO7 | GPIO8 | GPIO11 | GPIO12,
		.name      = "i2s"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_I2S_MCLK_EN_MASK,
		.gpio_mask = GPIO21,
		.name      = "i2s_mck_on21"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_I2S_22_18_EN_MASK,
		.gpio_mask = GPIO18 | GPIO19 | GPIO20 | GPIO21 | GPIO22,
		.name      = "i2s_on_18_22"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_SPDIF_EN_MASK,
		.gpio_mask = 0,
		.name      = "spdif"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_1_SPDIF_TCK_EN_MASK,
		.gpio_mask = 0,
		.name      = "spdif_on_tck"
	},
};

static const gpio_func gpio_funcs_2[] = {
	{
		.reg_mask  = QCA_GPIO_FUNC_2_MIC_DIS_MASK,
		.gpio_mask = 0,
		.name      = "mic_dis"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_I2S_ON_LED_MASK,
		.gpio_mask = GPIO14 | GPIO15 | GPIO16,
		.name      = "i2s_on_led"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_SPDIF_ON23_MASK,
		.gpio_mask = GPIO23,
		.name      = "spdif_on_23"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_I2SCK_ON1_MASK,
		.gpio_mask = GPIO1,
		.name      = "i2s_clk_on_1"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_I2SWS_ON0_MASK,
		.gpio_mask = GPIO0,
		.name      = "i2s_ws_on_0"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_I2SSD_ON12_MASK,
		.gpio_mask = GPIO12,
		.name      = "i2s_sd_on_12"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_WPS_DIS_MASK,
		.gpio_mask = GPIO12,
		.name      = "wps_dis"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_JUMPSTART_DIS_MASK,
		.gpio_mask = GPIO11,
		.name      = "jumpstart_dis"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_WLAN_LED_ON0_MASK,
		.gpio_mask = GPIO0,
		.name      = "wlan_led1_on_0"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_USB_LED_ON1_MASK,
		.gpio_mask = GPIO1,
		.name      = "wlan_led2_on_1"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_LNA_ON28_MASK,
		.gpio_mask = GPIO28,
		.name      = "ext_lna_on_28"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_SLIC_EN_MASK,
		.gpio_mask = GPIO6 | GPIO7 | GPIO8 | GPIO11 | GPIO12,
		.name      = "slic"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_SLIC_ON18_22_MASK,
		.gpio_mask = GPIO18 | GPIO19 | GPIO20 | GPIO21 | GPIO22,
		.name      = "slic_on_18_22"
	}, {
		.reg_mask  = QCA_GPIO_FUNC_2_SLIC_DIO_MUX_EN_MASK,
		.gpio_mask = 0,
		.name      = "slic_dio_mux"
	},
};

static u32 gpio_funcs_1_cnt = sizeof(gpio_funcs_1) / sizeof(gpio_func);
static u32 gpio_funcs_2_cnt = sizeof(gpio_funcs_2) / sizeof(gpio_func);

#else

typedef struct {
	u8 offset;
	char *name;
} gpio_in_func;

typedef struct {
	u8 value;
	char *name;
} gpio_out_func;

/*
 * TODO:
 * split gpio input functions per SoC version, not just family
 */
static const gpio_in_func gpio_in_funcs[] = {
#if (SOC_TYPE & QCA_AR934X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC)
	/* QCA_GPIO_IN_EN0_REG (0x18040044) */
	{
		.offset = 0,
		.name   = "spi_miso"
	}, {
		.offset = 1,
		.name   = "uart0_rx"
	},
	/* QCA_GPIO_IN_EN1_REG (0x18040048) */
	{
		.offset = 4,
		.name   = "i2s_mic_ws"
	}, {
		.offset = 5,
		.name   = "i2s_mic_sd"
	}, {
		.offset = 6,
		.name   = "i2s_ext_clk"
	}, {
		.offset = 7,
		.name   = "i2s_ext_mck"
	},
	/* QCA_GPIO_IN_EN2_REG (0x1804004C) */
	{
		.offset = 8,
		.name   = "eth_rx_err"
	}, {
		.offset = 9,
		.name   = "eth_rx_col"
	}, {
		.offset = 10,
		.name   = "eth_rx_crs"
	},
#if (SOC_TYPE & QCA_QCA955X_SOC)
	{
		.offset = 11,
		.name   = "slic_ext_mclk"
	},
#endif
	/* QCA_GPIO_IN_EN3_REG (0x18040050) */
#if (SOC_TYPE & QCA_AR934X_SOC)
	{
		.offset = 14,
		.name   = "boot_ext_mdo"
	}, {
		.offset = 15,
		.name   = "boot_ext_mdc"
	},
#elif (SOC_TYPE & QCA_QCA955X_SOC)
	{
		.offset = 12,
		.name   = "boot_ext_mdo"
	}, {
		.offset = 13,
		.name   = "boot_ext_mdc"
	}, {
		.offset = 14,
		.name   = "mii_ge1_mdi"
	},
#endif
	/* QCA_GPIO_IN_EN4_REG (0x18040054) */
	{
		.offset = 16,
		.name   = "slic_data_in"
	}, {
		.offset = 17,
		.name   = "slic_pcm_fs_in"
	},
#if (SOC_TYPE & QCA_QCA955X_SOC)
	{
		.offset = 18,
		.name   = "i2c_clk"
	}, {
		.offset = 19,
		.name   = "i2c_sda"
	},
#endif
	/* QCA_GPIO_IN_EN9_REG (0x18040068) */
	{
		.offset = 38,
		.name   = "uart1_rx"
	}, {
		.offset = 39,
		.name   = "uart1_cts"
	},
#elif (SOC_TYPE & QCA_QCA953X_SOC)
	/* QCA_GPIO_IN_EN0_REG (0x18040044) */
	{
		.offset = 0,
		.name   = "spi_miso"
	}, {
		.offset = 1,
		.name   = "uart0_rx"
	},
#elif (SOC_TYPE & QCA_QCA956X_SOC)
	/* QCA_GPIO_IN_EN0_REG (0x18040044) */
	{
		.offset = 1,
		.name   = "uart0_rx"
	},
	/* QCA_GPIO_IN_EN3_REG (0x18040050) */
	{
		.offset = 14,
		.name   = "mii_ge0_mdi"
	},
#endif
};

/*
 * TODO:
 * split gpio output functions per SoC version, not just family
 */
static const gpio_out_func gpio_out_funcs[] = {
	{
		.value = 0,
		.name  = "gpio"
	},
#if (SOC_TYPE & QCA_AR934X_SOC)
	{
		.value = QCA_GPIO_OUT_MUX_NAND_CS0_VAL,			/* 1 */
		.name  = "nand_cs"
	}, {
		.value = 2,
		.name  = "boot_rxt_mdi"
	}, {
		.value = 4,
		.name  = "slic_data_out"
	}, {
		.value = 5,
		.name  = "slic_pcm_fs"
	}, {
		.value = 6,
		.name  = "slic_pcm_clk"
	}, {
		.value = 7,
		.name  = "spi_cs1"
	}, {
		.value = 8,
		.name  = "spi_cs2"
	}, {
		.value = 9,
		.name  = "spi_cs0"
	}, {
		.value = QCA_GPIO_OUT_MUX_SPI_CLK_VAL,			/* 10 */
		.name  = "spi_clk"
	}, {
		.value = 11,
		.name  = "spi_mosi"
	}, {
		.value = 12,
		.name  = "i2s_clk"
	}, {
		.value = 13,
		.name  = "i2s_ws"
	}, {
		.value = 14,
		.name  = "i2s_sd"
	}, {
		.value = 15,
		.name  = "i2s_mck"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS0_VAL,			/* 16 */
		.name  = "clk_obs0"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS1_VAL,			/* 17 */
		.name  = "clk_obs1"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS2_VAL,			/* 18 */
		.name  = "clk_obs2"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS3_VAL,			/* 19 */
		.name  = "clk_obs3"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS4_VAL,			/* 20 */
		.name  = "clk_obs4"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS5_VAL,			/* 21 */
		.name  = "clk_obs5"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS6_VAL,			/* 22 */
		.name  = "clk_obs6"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS7_VAL,			/* 23 */
		.name  = "clk_obs7"
	}, {
		.value = 24,
		.name  = "uart0_tx"
	}, {
		.value = 25,
		.name  = "spdif_out"
	}, {
		.value = 26,
		.name  = "led_act0"
	}, {
		.value = 27,
		.name  = "led_act1"
	}, {
		.value = 28,
		.name  = "led_act2"
	}, {
		.value = 29,
		.name  = "led_act3"
	}, {
		.value = 30,
		.name  = "led_act4"
	}, {
		.value = 31,
		.name  = "led_col0"
	}, {
		.value = 32,
		.name  = "led_col1"
	}, {
		.value = 33,
		.name  = "led_col2"
	}, {
		.value = 34,
		.name  = "led_col3"
	}, {
		.value = 35,
		.name  = "led_col4"
	}, {
		.value = 36,
		.name  = "led_dup0"
	}, {
		.value = 37,
		.name  = "led_dup1"
	}, {
		.value = 38,
		.name  = "led_dup2"
	}, {
		.value = 39,
		.name  = "led_dup3"
	}, {
		.value = 40,
		.name  = "led_dup4"
	}, {
		.value = 41,
		.name  = "led_link0"
	}, {
		.value = 42,
		.name  = "led_link1"
	}, {
		.value = 43,
		.name  = "led_link2"
	}, {
		.value = 44,
		.name  = "led_link3"
	}, {
		.value = 45,
		.name  = "led_link4"
	}, {
		.value = 46,
		.name  = "ext_lna0"
	}, {
		.value = 47,
		.name  = "ext_lna1"
	}, {
		.value = 48,
		.name  = "tx_frame"
	}, {
		.value = 49,
		.name  = "wlan_act"
	}, {
		.value = 50,
		.name  = "led_net_en"
	}, {
		.value = 51,
		.name  = "led_pwr_en"
	}, {
		.value = 72,
		.name  = "wmac_glue_wow"
	}, {
		.value = 73,
		.name  = "bt_act"
	}, {
		.value = 74,
		.name  = "rx_clear_extension"
	}, {
		.value = 78,
		.name  = "eth_tx_err"
	}, {
		.value = 79,
		.name  = "uart1_tx"
	}, {
		.value = 80,
		.name  = "uart1_rts"
	}, {
		.value = 84,
		.name  = "ddr_dq_oe"
	}, {
		.value = 87,
		.name  = "usb_suspend"
	},
#elif (SOC_TYPE & QCA_QCA953X_SOC)
	{
		.value = QCA_GPIO_OUT_MUX_SYS_RST_L_VAL,		/* 1 */
		.name  = "sys_rst_l"
	}, {
		.value = QCA_GPIO_OUT_MUX_SPI_CLK_VAL,			/* 8 */
		.name  = "spi_clk"
	}, {
		.value = 9,
		.name  = "spi_cs0"
	}, {
		.value = 10,
		.name  = "spi_cs1"
	}, {
		.value = 11,
		.name  = "spi_cs2"
	}, {
		.value = 12,
		.name  = "spi_mosi"
	}, {
		.value = QCA_GPIO_OUT_MUX_LSUART_TXD_VAL,		/* 22 */
		.name  = "uart0_tx"
	}, {
		.value = QCA_GPIO_OUT_MUX_SRIF_OUT_VAL,			/* 23 */
		.name  = "srif_out"
	}, {
		.value = 26,
		.name  = "led_act0"
	}, {
		.value = 27,
		.name  = "led_act1"
	}, {
		.value = 28,
		.name  = "led_act2"
	}, {
		.value = 29,
		.name  = "led_act3"
	}, {
		.value = 30,
		.name  = "led_act4"
	}, {
		.value = 31,
		.name  = "led_col0"
	}, {
		.value = 32,
		.name  = "led_col1"
	}, {
		.value = 33,
		.name  = "led_col2"
	}, {
		.value = 34,
		.name  = "led_col3"
	}, {
		.value = 35,
		.name  = "led_col4"
	}, {
		.value = 36,
		.name  = "led_dup0"
	}, {
		.value = 37,
		.name  = "led_dup1"
	}, {
		.value = 38,
		.name  = "led_dup2"
	}, {
		.value = 39,
		.name  = "led_dup3"
	}, {
		.value = 40,
		.name  = "led_dup4"
	}, {
		.value = 41,
		.name  = "led_link0"
	}, {
		.value = 42,
		.name  = "led_link1"
	}, {
		.value = 43,
		.name  = "led_link2"
	}, {
		.value = 44,
		.name  = "led_link3"
	}, {
		.value = 45,
		.name  = "led_link4"
	}, {
		.value = QCA_GPIO_OUT_MUX_SMART_ANT_CTRL_BIT2_VAL,	/* 48 */
		.name  = "smart_ant_ctl_b2"
	}, {
		.value = QCA_GPIO_OUT_MUX_SMART_ANT_CTRL_BIT3_VAL,	/* 49 */
		.name  = "smart_ant_ctl_b3"
	}, {
		.value = 50,
		.name  = "ext_lna0"
	}, {
		.value = 51,
		.name  = "ext_lna1"
	}, {
		.value = 52,
		.name  = "tx_frame"
	}, {
		.value = 53,
		.name  = "wlan_act"
	}, {
		.value = 54,
		.name  = "led_net_en"
	}, {
		.value = 55,
		.name  = "led_pwr_en"
	}, {
		.value = 78,
		.name  = "rx_clear_extension"
	}, {
		.value = 86,
		.name  = "usb_suspend"
	}, {
		.value = 88,
		.name  = "ddr_dq_oe"
	}, {
		.value = 89,
		.name  = "clk_req_rc_n"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS0_VAL,			/* 90 */
		.name  = "clk_obs0"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS1_VAL,			/* 91 */
		.name  = "clk_obs1"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS2_VAL,			/* 92 */
		.name  = "clk_obs2"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS3_VAL,			/* 93 */
		.name  = "clk_obs3"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS4_VAL,			/* 94 */
		.name  = "clk_obs4"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS5_VAL,			/* 95 */
		.name  = "clk_obs5"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS6_VAL,			/* 96 */
		.name  = "clk_obs6"
	},
#elif (SOC_TYPE & QCA_QCA955X_SOC)
	{
		.value = 1,
		.name  = "mii_ext_mdi"
	}, {
		.value = 3,
		.name  = "slic_data_out"
	}, {
		.value = 4,
		.name  = "slic_pcm_fs"
	}, {
		.value = 5,
		.name  = "slic_pcm_clk"
	}, {
		.value = QCA_GPIO_OUT_MUX_SPI_CLK_VAL,			/* 8 */
		.name  = "spi_clk"
	}, {
		.value = 9,
		.name  = "spi_cs0"
	}, {
		.value = 10,
		.name  = "spi_cs1"
	}, {
		.value = 11,
		.name  = "spi_cs2"
	}, {
		.value = 12,
		.name  = "spi_mosi"
	}, {
		.value = 13,
		.name  = "i2s_clk"
	}, {
		.value = 14,
		.name  = "i2s_ws"
	}, {
		.value = 15,
		.name  = "i2s_sd"
	}, {
		.value = 16,
		.name  = "i2s_mck"
	}, {
		.value = 17,
		.name  = "spdif_out"
	}, {
		.value = 18,
		.name  = "uart1_tx"
	}, {
		.value = 19,
		.name  = "uart1_rts"
	}, {
		.value = QCA_GPIO_OUT_MUX_LSUART_TXD_VAL,		/* 22 */
		.name  = "uart0_tx"
	}, {
		.value = QCA_GPIO_OUT_MUX_SRIF_OUT_VAL,			/* 23 */
		.name  = "srif_out"
	}, {
		.value = 24,
		.name  = "led_sgmii_speed0"
	}, {
		.value = 25,
		.name  = "led_sgmii_speed1"
	}, {
		.value = 26,
		.name  = "led_sgmii_dup"
	}, {
		.value = 27,
		.name  = "led_sgmii_link"
	}, {
		.value = 28,
		.name  = "led_sgmii_speed0_inv"
	}, {
		.value = 29,
		.name  = "led_sgmii_speed1_inv"
	}, {
		.value = 30,
		.name  = "led_sgmii_dup_inv"
	}, {
		.value = 31,
		.name  = "led_sgmii_link_inv"
	}, {
		.value = 32,
		.name  = "ge1_mii_mdo"
	}, {
		.value = 33,
		.name  = "ge1_mii_mdc"
	}, {
		.value = 38,
		.name  = "swcom_b2"
	}, {
		.value = 39,
		.name  = "swcom_b3"
	}, {
		.value = QCA_GPIO_OUT_MUX_SMART_ANT_CTRL_BIT2_VAL,	/* 40 */
		.name  = "smart_ant_ctl_b2"
	}, {
		.value = QCA_GPIO_OUT_MUX_SMART_ANT_CTRL_BIT3_VAL,	/* 41 */
		.name  = "smart_ant_ctl_b3"
	}, {
		.value = 42,
		.name  = "ext_lna0"
	}, {
		.value = 43,
		.name  = "ext_lna1"
	}, {
		.value = 44,
		.name  = "tx_frame"
	}, {
		.value = 45,
		.name  = "wlan_act"
	}, {
		.value = 46,
		.name  = "led_net_en"
	}, {
		.value = 47,
		.name  = "led_pwr_en"
	}, {
		.value = 68,
		.name  = "wmac_glue_wow"
	}, {
		.value = 70,
		.name  = "rx_clear_extension"
	}, {
		.value = 71,
		.name  = "shift_strobe"
	}, {
		.value = 72,
		.name  = "shift_data"
	}, {
		.value = 73,
		.name  = "nand_cs1"
	}, {
		.value = 74,
		.name  = "usb_suspend"
	}, {
		.value = 75,
		.name  = "eth_tx_err"
	}, {
		.value = 76,
		.name  = "ddr_dq_oe"
	}, {
		.value = 77,
		.name  = "clk_req_ep_n"
	}, {
		.value = 78,
		.name  = "clk_req_rc_n"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS0_VAL,			/* 79 */
		.name  = "clk_obs0"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS1_VAL,			/* 80 */
		.name  = "clk_obs1"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS2_VAL,			/* 81 */
		.name  = "clk_obs2"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS3_VAL,			/* 82 */
		.name  = "clk_obs3"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS4_VAL,			/* 83 */
		.name  = "clk_obs4"
	}, {
		.value = QCA_GPIO_OUT_MUX_CLK_OBS5_VAL,			/* 84 */
		.name  = "clk_obs5"
	},
#elif (SOC_TYPE & QCA_QCA956X_SOC)
	{
		.value = 1,
		.name  = "led_act0"
	}, {
		.value = 2,
		.name  = "led_act1"
	}, {
		.value = 3,
		.name  = "led_act2"
	}, {
		.value = 4,
		.name  = "led_act3"
	}, {
		.value = 5,
		.name  = "led_act4"
	}, {
		.value = 6,
		.name  = "led_col0"
	}, {
		.value = 7,
		.name  = "led_col1"
	}, {
		.value = 8,
		.name  = "led_col2"
	}, {
		.value = 9,
		.name  = "led_col3"
	}, {
		.value = 10,
		.name  = "led_col4"
	}, {
		.value = 11,
		.name  = "led_dup0"
	}, {
		.value = 12,
		.name  = "led_dup1"
	}, {
		.value = 13,
		.name  = "led_dup2"
	}, {
		.value = 14,
		.name  = "led_dup3"
	}, {
		.value = 15,
		.name  = "led_dup4"
	}, {
		.value = 16,
		.name  = "led_link0"
	}, {
		.value = 17,
		.name  = "led_link1"
	}, {
		.value = 18,
		.name  = "uart1_tx"
	}, {
		.value = 19,
		.name  = "uart1_rts"
	}, {
		.value = QCA_GPIO_OUT_MUX_LSUART_TXD_VAL,		/* 22 */
		.name  = "uart0_tx"
	}, {
		.value = 23,
		.name  = "srif_out"
	}, {
		.value = 24,
		.name  = "led_sgmii_speed0"
	}, {
		.value = 25,
		.name  = "led_sgmii_speed1"
	}, {
		.value = 26,
		.name  = "led_sgmii_dup"
	}, {
		.value = 27,
		.name  = "led_sgmii_link"
	}, {
		.value = 28,
		.name  = "led_sgmii_speed0_inv"
	}, {
		.value = 29,
		.name  = "led_sgmii_speed1_inv"
	}, {
		.value = 30,
		.name  = "led_sgmii_dup_inv"
	}, {
		.value = 31,
		.name  = "led_sgmii_link_inv"
	}, {
		.value = 32,
		.name  = "ge0_mii_mdo"
	}, {
		.value = 33,
		.name  = "ge0_mii_mdc"
	}, {
		.value = 34,
		.name  = "led_link2"
	}, {
		.value = 35,
		.name  = "led_link3"
	}, {
		.value = 36,
		.name  = "led_link4"
	}, {
		.value = 37,
		.name  = "spi_cs1"
	}, {
		.value = 38,
		.name  = "swcom_b2"
	}, {
		.value = 39,
		.name  = "swcom_b3"
	}, {
		.value = 40,
		.name  = "smart_ant_ctl_b2"
	}, {
		.value = 41,
		.name  = "smart_ant_ctl_b3"
	}, {
		.value = 42,
		.name  = "ext_lna0"
	}, {
		.value = 43,
		.name  = "ext_lna1"
	}, {
		.value = 44,
		.name  = "tx_frame"
	}, {
		.value = 45,
		.name  = "wlan_act"
	}, {
		.value = 46,
		.name  = "led_net_en"
	}, {
		.value = 47,
		.name  = "led_pwr_en"
	}, {
		.value = 69,
		.name  = "bt_act"
	}, {
		.value = 70,
		.name  = "rx_clear_extension"
	}, {
		.value = 73,
		.name  = "i2c_clk"
	}, {
		.value = 74,
		.name  = "usb_suspend"
	}, {
		.value = 77,
		.name  = "i2c_sda"
	}, {
		.value = 78,
		.name  = "clk_req_rc_n"
	}, {
		.value = 89,
		.name  = "sgmii_lckdt"
	}, {
		.value = 115,
		.name  = "pcie2_rst_l"
	},
#endif
};

static u32 gpio_in_funcs_cnt  = sizeof(gpio_in_funcs)  / sizeof(gpio_in_func);
static u32 gpio_out_funcs_cnt = sizeof(gpio_out_funcs) / sizeof(gpio_out_func);

#endif /* SOC_TYPE & QCA_AR933X_SOC */

#endif /* CONFIG_CMD_GPIO */

#endif /* _CMD_QCAGPIO_H_ */
