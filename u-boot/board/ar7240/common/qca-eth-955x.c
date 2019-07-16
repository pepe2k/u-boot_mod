/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <config.h>
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <command.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <asm/types.h>

#ifdef CONFIG_ATH_NAND_BR
#include <nand.h>
#endif

#include <atheros.h>
#include "qca-eth-955x.h"
#include "qca-eth-955x_phy.h"
#define SGMII_LINK_WAR_MAX_TRY 10

#if defined(CONFIG_CMD_MII)
#include <miiphy.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define ath_gmac_unit2mac(_unit)     ath_gmac_macs[(_unit)]
#define ath_gmac_name2mac(name)	   is_drqfn() ? ath_gmac_unit2mac(1):strcmp(name,"eth0") ? ath_gmac_unit2mac(1) : ath_gmac_unit2mac(0)

int ath_gmac_miiphy_read(char *devname, uint32_t phaddr, uint8_t reg, uint16_t *data);
int ath_gmac_miiphy_write(char *devname, uint32_t phaddr, uint8_t reg, uint16_t data);
extern void ath_sys_frequency(uint32_t *, uint32_t *, uint32_t *);

#ifndef CFG_ATH_GMAC_NMACS
#define CFG_ATH_GMAC_NMACS	1
#endif /* CFG_ATH_GMAC_NMACS */

ath_gmac_mac_t *ath_gmac_macs[CFG_ATH_GMAC_NMACS];

#ifdef CONFIG_VIR_PHY
extern int athr_vir_phy_setup(int unit);
extern int athr_vir_phy_is_up(int unit);
extern int athr_vir_phy_is_fdx(int unit);
extern int athr_vir_phy_speed(int unit);
extern void athr_vir_reg_init(void);
#endif

#ifdef CONFIG_ATHRS17_PHY
extern void athrs17_reg_init(void);
extern void athrs17_reg_init_wan(void);
#endif

#ifdef CONFIG_ATHR_8033_PHY
extern int athrs_ar8033_reg_init(int ethUnit);
extern int athrs_ar8033_phy_setup(int ethUnit);
extern int athrs_ar8033_phy_is_up(int ethUnit);
extern int athrs_ar8033_phy_is_fdx(int ethUnit);
extern int athrs_ar8033_phy_speed(int ethUnit);
#endif

#ifdef CONFIG_ATH_NAND_BR

#define ATH_ETH_MAC_READ_SIZE 4096
extern unsigned long long
ath_nand_get_cal_offset(const char *ba);
#endif

static int
ath_gmac_send(struct eth_device *dev, volatile void *packet, int length)
{
	int i;

	ath_gmac_mac_t *mac = (ath_gmac_mac_t *)dev->priv;

	ath_gmac_desc_t *f = mac->fifo_tx[mac->next_tx];

	f->pkt_size = length;
	f->res1 = 0;
	f->pkt_start_addr = virt_to_phys(packet);

	ath_gmac_tx_give_to_dma(f);
	flush_cache((u32) packet, length);
	ath_gmac_reg_wr(mac, ATH_DMA_TX_DESC, virt_to_phys(f));
	ath_gmac_reg_wr(mac, ATH_DMA_TX_CTRL, ATH_TXE);

	for (i = 0; i < MAX_WAIT; i++) {
		udelay(10);
		if (!ath_gmac_tx_owned_by_dma(f))
			break;
	}
	if (i == MAX_WAIT)
		printf("Tx Timed out\n");

	f->pkt_start_addr = 0;
	f->pkt_size = 0;

	if (++mac->next_tx >= NO_OF_TX_FIFOS)
		mac->next_tx = 0;

	return (0);
}

static int ath_gmac_recv(struct eth_device *dev)
{
	int length;
	ath_gmac_desc_t *f;
	ath_gmac_mac_t *mac;
	volatile int dmaed_pkt=0;
	int count = 0;

	mac = (ath_gmac_mac_t *)dev->priv;

	for (;;) {
		f = mac->fifo_rx[mac->next_rx];
		if (ath_gmac_rx_owned_by_dma(f)) {
			/* check if the current Descriptor is_empty is 1,But the DMAed count is not-zero
			   then move to desciprot where the packet is available */
			dmaed_pkt = (ath_gmac_reg_rd(mac, 0x194) >> 16);
			if (!dmaed_pkt) {
				break;
			} else {
				if (f->is_empty == 1) {
					while (count < NO_OF_RX_FIFOS) {
						if (++mac->next_rx >= NO_OF_RX_FIFOS) {
							mac->next_rx = 0;
						}
						f = mac->fifo_rx[mac->next_rx];
						/*
						 * Break on valid data in the desc by checking
						 * empty bit.
						 */
						if (!f->is_empty) {
							count = 0;
							break;
						}
						count++;
					}
				}
			}
		}

		length = f->pkt_size;

		NetReceive(NetRxPackets[mac->next_rx] , length - 4);
		flush_cache((u32) NetRxPackets[mac->next_rx] , PKTSIZE_ALIGN);

		ath_gmac_reg_wr(mac,0x194,1);
		ath_gmac_rx_give_to_dma(f);

		if (++mac->next_rx >= NO_OF_RX_FIFOS)
			mac->next_rx = 0;
	}

	if (!(ath_gmac_reg_rd(mac, ATH_DMA_RX_CTRL))) {
		ath_gmac_reg_wr(mac, ATH_DMA_RX_DESC, virt_to_phys(f));
		ath_gmac_reg_wr(mac, ATH_DMA_RX_CTRL, 1);
	}

	return (0);
}

void ath_gmac_mii_setup(ath_gmac_mac_t *mac)
{
	u32 mgmt_cfg_val;

	ath_reg_wr(SWITCH_CLOCK_SPARE_ADDRESS, 0x520);

	if ((is_s17()  && mac->mac_unit == 0) || is_drqfn()) {
		printf("Scorpion  ----> S17 PHY *\n");
		mgmt_cfg_val = 7;
#ifndef ATH_RGMII_CAL
		ath_reg_wr(ATH_ETH_CFG, ETH_CFG_ETH_RXDV_DELAY_SET(3) |
#if defined(CONFIG_QCA_ETH_PHY_SWAP)
					ATH_ETH_CFG_SW_PHY_SWAP |
#endif
					ETH_CFG_ETH_RXD_DELAY_SET(3)|
					ETH_CFG_RGMII_GE0_SET(1));

		ath_reg_wr(ETH_XMII_ADDRESS, ETH_XMII_TX_INVERT_SET(1) |
                			     ETH_XMII_RX_DELAY_SET(2)  |
                			     ETH_XMII_TX_DELAY_SET(1)  |
					     ETH_XMII_GIGE_SET(1));
#else
        rgmii_cal_alg()
#endif
		udelay(1000);
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val);
		return;
	}

	if (is_ar8033 () && mac->mac_unit == 1) {
        	printf("Scorpion ---->8033 PHY*\n");

		mgmt_cfg_val = 7;
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val);
		return;
        }
        if (is_vir_phy()) {
        	printf("Scorpion ---->VIR PHY*\n");

		ath_reg_wr(ATH_ETH_CFG, ETH_CFG_ETH_RXDV_DELAY_SET(3) |
#if defined(CONFIG_QCA_ETH_PHY_SWAP)
					ATH_ETH_CFG_SW_PHY_SWAP |
#endif
					ETH_CFG_ETH_RXD_DELAY_SET(3)|
					ETH_CFG_RGMII_GE0_SET(1));
		ath_reg_wr(ETH_XMII_ADDRESS, ETH_XMII_TX_INVERT_SET(1) |
                			     ETH_XMII_RX_DELAY_SET(2)  |
                			     ETH_XMII_TX_DELAY_SET(1)  |
					     ETH_XMII_GIGE_SET(1));
		udelay(1000);
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, mgmt_cfg_val);
		return;
	}
}

void
athrs_sgmii_res_cal(void)
{
	unsigned int read_data, read_data_otp, otp_value, otp_per_val, rbias_per;
	unsigned int read_data_spi;
	unsigned int *address_spi = (unsigned int *)0xbffffffc;
	unsigned int rbias_pos_or_neg, res_cal_val;
	unsigned int sgmii_pos, sgmii_res_cal_value;
	unsigned int reversed_sgmii_value, use_value;

	ath_reg_wr(OTP_INTF2_ADDRESS, 0x7d);
	ath_reg_wr(OTP_LDO_CONTROL_ADDRESS, 0x0);

	while (ath_reg_rd(OTP_LDO_STATUS_ADDRESS) & OTP_LDO_STATUS_POWER_ON_MASK);

	read_data = ath_reg_rd(OTP_MEM_0_ADDRESS + 4);

	while (!(ath_reg_rd(OTP_STATUS0_ADDRESS) & OTP_STATUS0_EFUSE_READ_DATA_VALID_MASK));

	read_data_otp = ath_reg_rd(OTP_STATUS1_ADDRESS);

	if (read_data_otp & 0x1fff) {
		read_data = read_data_otp;
	} else {
		read_data_spi = *(address_spi);
		if ((read_data_spi & 0xffff0000) == 0x5ca10000) {
			read_data = read_data_spi;
		} else {
			read_data = read_data_otp;
		}
	}

	if (read_data & 0x00001000) {
		otp_value = (read_data & 0xfc0) >> 6;
	} else {
		otp_value = read_data & 0x3f;
	}

	if (otp_value > 31) {
		otp_per_val = 63 - otp_value;
		rbias_pos_or_neg = 1;
	} else {
		otp_per_val = otp_value;
		rbias_pos_or_neg = 0;
	}

	rbias_per = otp_per_val * 15;

	if (rbias_pos_or_neg == 1) {
		res_cal_val = (rbias_per + 34) / 21;
		sgmii_pos = 1;
	} else {
		if (rbias_per > 34) {
			res_cal_val = (rbias_per - 34) / 21;
			sgmii_pos = 0;
		} else {
			res_cal_val = (34 - rbias_per) / 21;
			sgmii_pos = 1;
		}
	}

	if (sgmii_pos == 1) {
		sgmii_res_cal_value = 8 + res_cal_val;
	} else {
		sgmii_res_cal_value = 8 - res_cal_val;
	}

	reversed_sgmii_value = 0;
	use_value = 0x8;
	reversed_sgmii_value = reversed_sgmii_value | ((sgmii_res_cal_value & use_value) >> 3);
	use_value = 0x4;
	reversed_sgmii_value = reversed_sgmii_value | ((sgmii_res_cal_value & use_value) >> 1);
	use_value = 0x2;
	reversed_sgmii_value = reversed_sgmii_value | ((sgmii_res_cal_value & use_value) << 1);
	use_value = 0x1;
	reversed_sgmii_value = reversed_sgmii_value | ((sgmii_res_cal_value & use_value) << 3);

	reversed_sgmii_value &= 0xf;

	printf("%s: cal value = 0x%x\n", __func__, reversed_sgmii_value);

	// To Check the locking of the SGMII PLL

	read_data = (ath_reg_rd(SGMII_SERDES_ADDRESS) &
				~SGMII_SERDES_RES_CALIBRATION_MASK) |
			SGMII_SERDES_RES_CALIBRATION_SET(reversed_sgmii_value);

	ath_reg_wr(SGMII_SERDES_ADDRESS, read_data);

	ath_reg_wr(ETH_SGMII_SERDES_ADDRESS,
			ETH_SGMII_SERDES_EN_LOCK_DETECT_MASK |
			ETH_SGMII_SERDES_PLL_REFCLK_SEL_MASK |
			ETH_SGMII_SERDES_EN_PLL_MASK);

	ath_reg_rmw_set(SGMII_SERDES_ADDRESS,
			SGMII_SERDES_CDR_BW_SET(3) |
			SGMII_SERDES_TX_DR_CTRL_SET(1) |
			SGMII_SERDES_PLL_BW_SET(1) |
			SGMII_SERDES_EN_SIGNAL_DETECT_SET(1) |
			SGMII_SERDES_FIBER_SDO_SET(1) |
			SGMII_SERDES_VCO_REG_SET(3));

	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_ETH_SGMII_ARESET_MASK);
	udelay(25);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_ETH_SGMII_RESET_MASK);

	while (!(ath_reg_rd(SGMII_SERDES_ADDRESS) & SGMII_SERDES_LOCK_DETECT_STATUS_MASK));
}


static void athr_gmac_sgmii_setup(void)
{
	int status = 0, count = 0;

#ifdef ATH_SGMII_FORCED_MODE
        ath_reg_wr(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_SPEED_SEL1_SET(1) |
                                           MR_AN_CONTROL_PHY_RESET_SET(1)  |
                                           MR_AN_CONTROL_DUPLEX_MODE_SET(1));
        udelay(10);
        ath_reg_wr(SGMII_CONFIG_ADDRESS, SGMII_CONFIG_MODE_CTRL_SET(2)   |
                                          SGMII_CONFIG_FORCE_SPEED_SET(1) |
                                          SGMII_CONFIG_SPEED_SET(2));
        printf ("SGMII in forced mode\n");
#else
	ath_reg_wr(SGMII_CONFIG_ADDRESS, SGMII_CONFIG_MODE_CTRL_SET(2));
	ath_reg_wr(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_AN_ENABLE_SET(1)
                                      |MR_AN_CONTROL_PHY_RESET_SET(1));
	ath_reg_wr(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_AN_ENABLE_SET(1));
#endif

/*
 * SGMII reset sequence suggested by systems team.
 */
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_RX_CLK_N_RESET);
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_HW_RX_125M_N_SET(1));
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_HW_RX_125M_N_SET(1)
                                    |SGMII_RESET_RX_125M_N_SET(1));
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_HW_RX_125M_N_SET(1)
                                    |SGMII_RESET_TX_125M_N_SET(1)
                                    |SGMII_RESET_RX_125M_N_SET(1));
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_HW_RX_125M_N_SET(1)
                                    |SGMII_RESET_TX_125M_N_SET(1)
                                    |SGMII_RESET_RX_125M_N_SET(1)
                                    |SGMII_RESET_RX_CLK_N_SET(1));
	ath_reg_wr(SGMII_RESET_ADDRESS, SGMII_RESET_HW_RX_125M_N_SET(1)
                                    |SGMII_RESET_TX_125M_N_SET(1)
                                    |SGMII_RESET_RX_125M_N_SET(1)
                                    |SGMII_RESET_RX_CLK_N_SET(1)
                                    |SGMII_RESET_TX_CLK_N_SET(1));
        ath_reg_rmw_clear(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_PHY_RESET_SET(1));
	/*
	 * WAR::Across resets SGMII link status goes to weird
	 * state.
	 * if 0xb8070058 (SGMII_DEBUG register) reads other then 0x1f or 0x10
	 * for sure we are in bad  state.
	 * Issue a PHY reset in MR_AN_CONTROL_ADDRESS to keep going.
	 */
	status = (ath_reg_rd(SGMII_DEBUG_ADDRESS) & 0xff);
	while (!(status == 0xf || status == 0x10)) {

		ath_reg_rmw_set(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_PHY_RESET_SET(1));
		udelay(100);
		ath_reg_rmw_clear(MR_AN_CONTROL_ADDRESS, MR_AN_CONTROL_PHY_RESET_SET(1));
		if (count++ == SGMII_LINK_WAR_MAX_TRY) {
			printf ("Max resets limit reached exiting...\n");
			break;
	    	}
		status = (ath_reg_rd(SGMII_DEBUG_ADDRESS) & 0xff);
	}

	printf("%s SGMII done\n",__func__);
}

static void ath_gmac_hw_start(ath_gmac_mac_t *mac)
{
	if (mac->mac_unit)
	{
		ath_gmac_reg_rmw_set(mac, ATH_MAC_CFG2, (ATH_MAC_CFG2_PAD_CRC_EN |
					ATH_MAC_CFG2_LEN_CHECK | ATH_MAC_CFG2_IF_1000));
	} else {
		ath_gmac_reg_rmw_set(mac, ATH_MAC_CFG2, (ATH_MAC_CFG2_PAD_CRC_EN |
					ATH_MAC_CFG2_LEN_CHECK | ATH_MAC_CFG2_IF_10_100));
	}
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_0, 0x1f00);
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_1, 0x10ffff);
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_2, 0xAAA0555);

	ath_gmac_reg_rmw_set(mac, ATH_MAC_FIFO_CFG_4, 0x3ffff);
	/*
	 * Setting Drop CRC Errors, Pause Frames,Length Error frames
	 * and Multi/Broad cast frames.
	 */

#if defined(CONFIG_CMD_HTTPD)
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_5, 0x7efcf);
#else
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_5, 0x7eccf);
#endif

	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_3, 0x1f00140);

	printf(": cfg1 %#x cfg2 %#x\n", ath_gmac_reg_rd(mac, ATH_MAC_CFG1),
			ath_gmac_reg_rd(mac, ATH_MAC_CFG2));
}

static int ath_gmac_check_link(ath_gmac_mac_t *mac)
{
	int link, duplex, speed;

	ath_gmac_phy_link(mac->mac_unit, &link);
	ath_gmac_phy_duplex(mac->mac_unit, &duplex);
	ath_gmac_phy_speed(mac->mac_unit, &speed);

	mac->link = link;

	if(!mac->link) {
		printf("%s link down\n",mac->dev->name);
		return 0;
	}

	switch (speed)
	{
		case _1000BASET:
			ath_gmac_set_mac_if(mac, 1);
			ath_gmac_reg_rmw_set(mac, ATH_MAC_FIFO_CFG_5, (1 << 19));
			if (is_ar8033()) {
				ath_reg_wr(ETH_SGMII_ADDRESS, ETH_SGMII_GIGE_SET(1) |
                                           ETH_SGMII_CLK_SEL_SET(1));
			}
			break;
		case _100BASET:
			ath_gmac_set_mac_if(mac, 0);
			ath_gmac_set_mac_speed(mac, 1);
			ath_gmac_reg_rmw_clear(mac, ATH_MAC_FIFO_CFG_5, (1 << 19));
                        if (is_ar8033()) {
                        	ath_reg_wr(ETH_SGMII_ADDRESS, ETH_SGMII_PHASE0_COUNT_SET(1) |
                                           ETH_SGMII_PHASE1_COUNT_SET(1));
			}
			break;
		case _10BASET:
			ath_gmac_set_mac_if(mac, 0);
			ath_gmac_set_mac_speed(mac, 0);
			ath_gmac_reg_rmw_clear(mac, ATH_MAC_FIFO_CFG_5, (1 << 19));
			if (is_ar8033()) {
				ath_reg_wr(ETH_SGMII_ADDRESS, ETH_SGMII_PHASE0_COUNT_SET(19) |
					   ETH_SGMII_PHASE1_COUNT_SET(19));
			}
			break;
		default:
			printf("Invalid speed detected\n");
			return 0;
	}

	if (mac->link && (duplex == mac->duplex) && (speed == mac->speed))
		return 1;

	mac->duplex = duplex;
	mac->speed = speed;

	printf("dup %d speed %d\n", duplex, speed);

	ath_gmac_set_mac_duplex(mac,duplex);

	return 1;
}

/*
 * For every command we re-setup the ring and start with clean h/w rx state
 */
static int ath_gmac_clean_rx(struct eth_device *dev, bd_t * bd)
{
	int i;
	ath_gmac_desc_t *fr;
	ath_gmac_mac_t *mac = (ath_gmac_mac_t*)dev->priv;

	if (!ath_gmac_check_link(mac))
		return 0;

	mac->next_rx = 0;

        ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_0, 0x1f00);
        ath_gmac_reg_wr(mac, ATH_MAC_CFG1, (ATH_MAC_CFG1_RX_EN | ATH_MAC_CFG1_TX_EN));

	for (i = 0; i < NO_OF_RX_FIFOS; i++) {
		fr = mac->fifo_rx[i];
		fr->pkt_start_addr = virt_to_phys(NetRxPackets[i]);
		flush_cache((u32) NetRxPackets[i], PKTSIZE_ALIGN);
		ath_gmac_rx_give_to_dma(fr);
	}

	ath_gmac_reg_wr(mac, ATH_DMA_RX_DESC, virt_to_phys(mac->fifo_rx[0]));
	ath_gmac_reg_wr(mac, ATH_DMA_RX_CTRL, ATH_RXE);	/* rx start */
	udelay(1000 * 1000);

	return 1;
}

static int ath_gmac_alloc_fifo(int ndesc, ath_gmac_desc_t ** fifo)
{
	int i;
	u32 size;
	uchar *p = NULL;

	size = sizeof(ath_gmac_desc_t) * ndesc;
	size += CFG_CACHELINE_SIZE - 1;

	if ((p = malloc(size)) == NULL) {
		printf("Cant allocate fifos\n");
		return -1;
	}

	p = (uchar *) (((u32) p + CFG_CACHELINE_SIZE - 1) &
			~(CFG_CACHELINE_SIZE - 1));
	p = UNCACHED_SDRAM(p);

	for (i = 0; i < ndesc; i++)
		fifo[i] = (ath_gmac_desc_t *) p + i;

	return 0;
}

static int ath_gmac_setup_fifos(ath_gmac_mac_t *mac)
{
	int i;

	if (ath_gmac_alloc_fifo(NO_OF_TX_FIFOS, mac->fifo_tx))
		return 1;

	for (i = 0; i < NO_OF_TX_FIFOS; i++) {
		mac->fifo_tx[i]->next_desc = (i == NO_OF_TX_FIFOS - 1) ?
			virt_to_phys(mac->fifo_tx[0]) : virt_to_phys(mac->fifo_tx[i + 1]);
		ath_gmac_tx_own(mac->fifo_tx[i]);
	}

	if (ath_gmac_alloc_fifo(NO_OF_RX_FIFOS, mac->fifo_rx))
		return 1;

	for (i = 0; i < NO_OF_RX_FIFOS; i++) {
		mac->fifo_rx[i]->next_desc = (i == NO_OF_RX_FIFOS - 1) ?
			virt_to_phys(mac->fifo_rx[0]) : virt_to_phys(mac->fifo_rx[i + 1]);
	}

	return (1);
}

static void ath_gmac_halt(struct eth_device *dev)
{
	ath_gmac_mac_t *mac = (ath_gmac_mac_t *)dev->priv;
        ath_gmac_reg_rmw_clear(mac, ATH_MAC_CFG1,(ATH_MAC_CFG1_RX_EN | ATH_MAC_CFG1_TX_EN));
        ath_gmac_reg_wr(mac,ATH_MAC_FIFO_CFG_0,0x1f1f);
	ath_gmac_reg_wr(mac,ATH_DMA_RX_CTRL, 0);
	while (ath_gmac_reg_rd(mac, ATH_DMA_RX_CTRL));
}

void
athr_mgmt_init(void)
{

#ifdef CONFIG_MGMT_INIT
	uint32_t rddata;

	rddata = ath_reg_rd(GPIO_IN_ENABLE3_ADDRESS)&
		~GPIO_IN_ENABLE3_MII_GE1_MDI_MASK;
	rddata |= GPIO_IN_ENABLE3_MII_GE1_MDI_SET(19);
	ath_reg_wr(GPIO_IN_ENABLE3_ADDRESS, rddata);

	ath_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 19));
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 17));

	rddata = ath_reg_rd(GPIO_OUT_FUNCTION4_ADDRESS) &
		~ (GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_MASK |
		GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_MASK);

	rddata |= GPIO_OUT_FUNCTION4_ENABLE_GPIO_19_SET(0x20) |
	GPIO_OUT_FUNCTION4_ENABLE_GPIO_17_SET(0x21);

	ath_reg_wr(GPIO_OUT_FUNCTION4_ADDRESS, rddata);
#endif
	printf ("%s ::done\n",__func__);
}

/*
 * Get MAC address stored in flash
 */
static void ath_gmac_get_ethaddr(struct eth_device *dev)
{
	unsigned char *mac = dev->enetaddr;
	bd_t *bd = gd->bd;

	memcpy(mac, (void *)bd->bi_enetaddr, 6);
}

int ath_gmac_enet_initialize(bd_t * bis)
{
	struct eth_device *dev[CFG_ATH_GMAC_NMACS];
	u32 mask, mac_h, mac_l;
	int i;

	printf("%s...\n", __func__);

	athrs_sgmii_res_cal();

	for (i = 0;i < CFG_ATH_GMAC_NMACS;i++) {

		if ((dev[i] = (struct eth_device *) malloc(sizeof (struct eth_device))) == NULL) {
			puts("malloc failed\n");
			return 0;
		}

		if ((ath_gmac_macs[i] = (ath_gmac_mac_t *) malloc(sizeof (ath_gmac_mac_t))) == NULL) {
			puts("malloc failed\n");
			return 0;
		}

		memset(ath_gmac_macs[i], 0, sizeof(ath_gmac_macs[i]));
		memset(dev[i], 0, sizeof(dev[i]));

		sprintf(dev[i]->name, "eth%d", i);
		ath_gmac_get_ethaddr(dev[i]);

		ath_gmac_macs[i]->mac_unit = i;
		ath_gmac_macs[i]->mac_base = i ? ATH_GE1_BASE : ATH_GE0_BASE ;
		ath_gmac_macs[i]->dev = dev[i];

		dev[i]->iobase = 0;
		dev[i]->init = ath_gmac_clean_rx;
		dev[i]->halt = ath_gmac_halt;
		dev[i]->send = ath_gmac_send;
		dev[i]->recv = ath_gmac_recv;
		dev[i]->priv = (void *)ath_gmac_macs[i];
	}

#if !defined(CONFIG_ATH_NAND_BR)
	ath_reg_rmw_set(RST_RESET_ADDRESS,  RST_RESET_ETH_SGMII_ARESET_SET(1));
	udelay(1000 * 100);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_ETH_SGMII_ARESET_SET(1));
	udelay(100);
#endif
	ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_ETH_SGMII_RESET_SET(1) | RST_RESET_EXTERNAL_RESET_SET(1));
	udelay(1000 * 100);
	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_ETH_SGMII_RESET_SET(1) | RST_RESET_EXTERNAL_RESET_SET(1));
	udelay(1000 * 100);

	for (i = 0;i < CFG_ATH_GMAC_NMACS;i++) {

		ath_gmac_reg_rmw_set(ath_gmac_macs[i], ATH_MAC_CFG1, ATH_MAC_CFG1_SOFT_RST
				| ATH_MAC_CFG1_RX_RST | ATH_MAC_CFG1_TX_RST);

		if(!i) {
			mask = (ATH_RESET_GE0_MAC | ATH_RESET_GE1_MAC);

			mask = mask | ATH_RESET_GE0_MDIO | ATH_RESET_GE1_MDIO;

			printf("%s: reset mask:%x \n", __func__, mask);

			ath_reg_rmw_set(RST_RESET_ADDRESS, mask);
			udelay(1000 * 100);

			ath_reg_rmw_clear(RST_RESET_ADDRESS, mask);
			udelay(1000 * 100);

			udelay(10 * 1000);
		}
#if defined(CONFIG_MGMT_INIT) && defined (CONFIG_ATHR_SWITCH_ONLY_MODE) || defined ATH_MDC_GPIO
		if (!i)
			athr_mgmt_init();

		if (ath_gmac_macs[i]->mac_unit == 0)
                        continue;
#endif
		eth_register(dev[i]);
#if defined(CONFIG_CMD_MII)
		miiphy_register(dev[i]->name, ath_gmac_miiphy_read, ath_gmac_miiphy_write);
#endif
		ath_gmac_mii_setup(ath_gmac_macs[i]);

		/* if using header for register configuration, we have to     */
		/* configure s26 register after frame transmission is enabled */

		if (ath_gmac_macs[i]->mac_unit == 0) { /* WAN Phy */
#ifdef CONFIG_ATHRS17_PHY
			athrs17_reg_init();
#endif

#ifdef CONFIG_VIR_PHY
			printf("VIRPhy reg init \n");
			athr_vir_reg_init();
#endif
		} else {
#ifdef CONFIG_ATHR_8033_PHY
			printf("AR8033 PHY init \n");
			athrs_ar8033_reg_init(0);
#endif

#if defined(CONFIG_MGMT_INIT) && defined (CONFIG_ATHR_SWITCH_ONLY_MODE)
			athrs17_reg_init();
#elif defined (CONFIG_ATHRS17_PHY) && !defined(CFG_DUAL_PHY_SUPPORT)
			athrs17_reg_init_wan();
#endif
		}
#ifdef CONFIG_ATHRS_GMAC_SGMII
	/*
         * MAC unit 1 or drqfn package call sgmii setup.
	 */
	if (i == 1 || is_drqfn())
		athr_gmac_sgmii_setup();
#endif
		ath_gmac_hw_start(ath_gmac_macs[i]);
		ath_gmac_setup_fifos(ath_gmac_macs[i]);

		udelay(100 * 1000);

		mac_l = (dev[i]->enetaddr[4] << 8) | (dev[i]->enetaddr[5]);
		mac_h = (dev[i]->enetaddr[0] << 24) | (dev[i]->enetaddr[1] << 16) |
			(dev[i]->enetaddr[2] << 8) | (dev[i]->enetaddr[3] << 0);

		ath_gmac_reg_wr(ath_gmac_macs[i], ATH_GE_MAC_ADDR1, mac_l);
		ath_gmac_reg_wr(ath_gmac_macs[i], ATH_GE_MAC_ADDR2, mac_h);


	ath_gmac_phy_setup(ath_gmac_macs[i]->mac_unit);
		printf("%s up\n",dev[i]->name);
	}

	return 1;
}

int
ath_gmac_miiphy_read(char *devname, uint32_t phy_addr, uint8_t reg, uint16_t *data)
{
	ath_gmac_mac_t *mac   = ath_gmac_name2mac(devname);
	uint16_t      addr  = (phy_addr << ATH_ADDR_SHIFT) | reg, val;
	volatile int           rddata;
	uint16_t      ii = 0xFFFF;

	/*
	 * Check for previous transactions are complete. Added to avoid
	 * race condition while running at higher frequencies.
	 */
	do
	{
		udelay(5);
		rddata = ath_gmac_reg_rd(mac, ATH_MII_MGMT_IND) & 0x1;
	}while(rddata && --ii);

	if (ii == 0)
		printf("ERROR:%s:%d transaction failed\n",__func__,__LINE__);

	ath_gmac_reg_wr(mac, ATH_MII_MGMT_CMD, 0x0);
	ath_gmac_reg_wr(mac, ATH_MII_MGMT_ADDRESS, addr);
	ath_gmac_reg_wr(mac, ATH_MII_MGMT_CMD, ATH_MGMT_CMD_READ);

	do
	{
		udelay(5);
		rddata = ath_gmac_reg_rd(mac, ATH_MII_MGMT_IND) & 0x1;
	}while(rddata && --ii);

	if(ii==0)
		printf("Error!!! Leave ath_gmac_miiphy_read without polling correct status!\n");

	val = ath_gmac_reg_rd(mac, ATH_MII_MGMT_STATUS);
	ath_gmac_reg_wr(mac, ATH_MII_MGMT_CMD, 0x0);

	if (data != NULL)
	    *data = val;
	return val;
}

int
ath_gmac_miiphy_write(char *devname, uint32_t phy_addr, uint8_t reg, uint16_t data)
{
	ath_gmac_mac_t *mac   = ath_gmac_name2mac(devname);
	uint16_t      addr  = (phy_addr << ATH_ADDR_SHIFT) | reg;
	volatile int rddata;
	uint16_t      ii = 0xFFFF;

	/*
	 * Check for previous transactions are complete. Added to avoid
	 * race condition while running at higher frequencies.
	 */
	do {
		udelay(5);
		rddata = ath_gmac_reg_rd(mac, ATH_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("ERROR:%s:%d transaction failed\n",__func__,__LINE__);

	ath_gmac_reg_wr(mac, ATH_MII_MGMT_ADDRESS, addr);
	ath_gmac_reg_wr(mac, ATH_MII_MGMT_CTRL, data);

	do {
		rddata = ath_gmac_reg_rd(mac, ATH_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("Error!!! Leave ath_gmac_miiphy_write without polling correct status!\n");
	return 0;
}
