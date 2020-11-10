/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __QCA_ETH_956X_H
#define __QCA_ETH_956X_H

#include <linux/types.h>

#ifndef CONFIG_MACH_QCA956x
#ifdef ATH_RGMII_CAL
#define rgmii_cal_alg()    rgmii_calib(mac);
#else
#define rgmii_cal_alg()
#endif
#endif

/*
 * h/w descriptor
 */
typedef struct {
	uint32_t	pkt_start_addr,
			is_empty	:  1,
			res1		: 10,
			ftpp_override	:  5,
			res2		:  4,
			pkt_size	: 12,
			next_desc;
} ath_gmac_desc_t;

#define NO_OF_TX_FIFOS			8
#define NO_OF_RX_FIFOS			8

typedef struct {
	ath_gmac_desc_t		*fifo_tx[NO_OF_TX_FIFOS],
				*fifo_rx[NO_OF_RX_FIFOS];
	struct eth_device	*dev;
	uint32_t		next_tx,
				next_rx,
				link,
				duplex,
				speed,
				mac_unit,
				mac_base;
} ath_gmac_mac_t;

#define ath_gmac_reg_wr(_mac, _x, _y)	ath_reg_wr(((_x) + _mac->mac_base), (_y))
#define ath_gmac_reg_rd(_mac, _x)	ath_reg_rd(((_x) + _mac->mac_base))

#define ath_gmac_reg_rmw_set(_mac, _x, _y)	\
	ath_reg_rmw_set(((_x) + _mac->mac_base ), (_y))
#define ath_gmac_reg_rmw_clear(_mac, _x, _y)	\
	ath_reg_rmw_clear(((_x) + _mac->mac_base), (_y))

#ifdef COMPRESSED_UBOOT
#define _1000BASET		1000
#define _100BASET		100
#define _10BASET		10
#endif /* #ifdef COMPRESSED_UBOOT */

/*
 * spd is _1000BASET, _100BASET etc. defined in include/miiphy.h
 */
#define mii_reg(_mac)	(ATH_MII0_CTRL + ((_mac)->mac_unit * 4))
#define mii_if(_mac)	(((_mac)->mac_unit == 0) ? mii0_if : mii1_if)

#define ath_gmac_set_mii_ctrl_speed(_mac, _spd)	do {	\
	ath_reg_rmw_clear(mii_reg(_mac), (3 << 4));	\
	ath_reg_rmw_set(mii_reg(_mac), ((_spd) << 4));	\
} while (0)

#if defined (CFG_MII0_GMII)
#	define ath_gmac_get_mii_if()	0
#elif defined (CFG_MII0_MII)
#	define ath_gmac_get_mii_if()	0
#elif defined (CFG_MII0_RGMII)
#	define ath_gmac_get_mii_if()	0
#elif defined (CFG_MII0_RMII)
#	define ath_gmac_get_mii_if()	0
#endif

#define MAX_WAIT			1000

/*
 * Config/Mac Register definitions
 */
#define ATH_MAC_CFG1			0x00
#define ATH_MAC_CFG2			0x04
#define ATH_MAC_IFCTL			0x38

/*
 * fifo control registers
 */
#define ATH_MAC_FIFO_CFG_0		0x48
#define ATH_MAC_FIFO_CFG_1		0x4c
#define ATH_MAC_FIFO_CFG_2		0x50
#define ATH_MAC_FIFO_CFG_3		0x54
#define ATH_MAC_FIFO_CFG_4		0x58

#define ATH_MAC_FIFO_CFG_5		0x5c
#define ATH_BYTE_PER_CLK_EN		BIT(19)

#define ATH_MAC_FIFO_RAM_0		0x60
#define ATH_MAC_FIFO_RAM_1		0x64
#define ATH_MAC_FIFO_RAM_2		0x68
#define ATH_MAC_FIFO_RAM_3		0x6c
#define ATH_MAC_FIFO_RAM_4		0x70
#define ATH_MAC_FIFO_RAM_5		0x74
#define ATH_MAC_FIFO_RAM_6		0x78
#define ATH_MAC_FIFO_RAM_7		0x7c

/*
 * fields
 */
#define ATH_MAC_CFG1_SOFT_RST		BIT(31)
#define ATH_MAC_CFG1_RX_RST		BIT(19)
#define ATH_MAC_CFG1_TX_RST		BIT(18)
#define ATH_MAC_CFG1_LOOPBACK		BIT(8)
#define ATH_MAC_CFG1_RX_EN		BIT(2)
#define ATH_MAC_CFG1_TX_EN		BIT(0)

#define ATH_MAC_CFG2_FDX		BIT(0)
#define ATH_MAC_CFG2_PAD_CRC_EN		BIT(2)
#define ATH_MAC_CFG2_LEN_CHECK		BIT(4)
#define ATH_MAC_CFG2_HUGE_FRAME_EN	BIT(5)
#define ATH_MAC_CFG2_IF_1000		BIT(9)
#define ATH_MAC_CFG2_IF_10_100		BIT(8)

#define ATH_MAC_IFCTL_SPEED		BIT(16)

/*
 * DMA (tx/rx) register defines
 */
#define ATH_DMA_TX_CTRL			0x180
#define ATH_DMA_TX_DESC			0x184
#define ATH_DMA_TX_STATUS		0x188
#define ATH_DMA_RX_CTRL			0x18c
#define ATH_DMA_RX_DESC			0x190
#define ATH_DMA_RX_STATUS		0x194
#define ATH_DMA_INTR_MASK		0x198
#define ATH_DMA_INTR			0x19c

/*
 * tx/rx ctrl and status bits
 */
#define ATH_TXE				BIT(0)
#define ATH_TX_STATUS_PKTCNT_SHIFT	16
#define ATH_TX_STATUS_PKT_SENT		0x1
#define ATH_TX_STATUS_URN		0x2
#define ATH_TX_STATUS_BUS_ERROR		0x8

#define ATH_RXE				BIT(0)

#define ATH_RX_STATUS_PKTCNT_MASK	0xff0000
#define ATH_RX_STATUS_PKT_RCVD		BIT(0)
#define ATH_RX_STATUS_OVF		BIT(2)
#define ATH_RX_STATUS_BUS_ERROR		BIT(3)

/*
 * Int and int mask
 */
#define ATH_INTR_TX			BIT(0)
#define ATH_INTR_TX_URN			BIT(1)
#define ATH_INTR_TX_BUS_ERROR		BIT(3)
#define ATH_INTR_RX			BIT(4)
#define ATH_INTR_RX_OVF			BIT(6)
#define ATH_INTR_RX_BUS_ERROR		BIT(7)

/*
 * MII registers
 */
#define ATH_MAC_MII_MGMT_CFG		0x20
#define ATH_MGMT_CFG_CLK_DIV_20		0x07

#define ATH_MII_MGMT_CMD		0x24
#define ATH_MGMT_CMD_READ		0x1

#define ATH_MII_MGMT_ADDRESS		0x28
#define ATH_ADDR_SHIFT			8

#define ATH_MII_MGMT_CTRL		0x2c
#define ATH_MII_MGMT_STATUS		0x30

#define ATH_MII_MGMT_IND		0x34
#define ATH_MGMT_IND_BUSY		BIT(0)
#define ATH_MGMT_IND_INVALID		BIT(2)

#define ATH_GE_MAC_ADDR1		0x40
#define ATH_GE_MAC_ADDR2		0x44

/*
 * Ethernet config registers
 */
#define ATH_ETH_CFG			0x18070000
#define ATH_ETH_CFG_RGMII_GE0		BIT(0)
#define ATH_ETH_CFG_MII_GE0		BIT(1)
#define ATH_ETH_CFG_GMII_GE0		BIT(2)
#define ATH_ETH_CFG_RMII_GE0		BIT(10)
#define ATH_ETH_CFG_RMII_HISPD_GE0	BIT(11)
#define ATH_ETH_CFG_RMII_MASTER_MODE	BIT(12)
#define ATH_ETH_CFG_MII_GE0_MASTER	BIT(3)
#define ATH_ETH_CFG_MII_GE0_SLAVE	BIT(4)
#define ATH_ETH_CFG_GE0_ERR_EN		BIT(5)
#define ATH_ETH_CFG_SW_ONLY_MODE	BIT(6)
#define ATH_ETH_CFG_SW_PHY_SWAP		BIT(7)
#define ATH_ETH_CFG_SW_PHY_ADDR_SWAP	BIT(8)
#define ATH_ETH_CFG_RXD_DELAY		BIT(14)
#define ATH_ETH_CFG_RDV_DELAY		BIT(16)
#define ATH_ETH_SWITCH_CLK_SPARE	0x18050024

#define ETH_XMII_TX_INVERT_MSB                                       31
#define ETH_XMII_TX_INVERT_LSB                                       31
#define ETH_XMII_TX_INVERT_MASK                                      0x80000000
#define ETH_XMII_TX_INVERT_GET(x)                                    (((x) & ETH_XMII_TX_INVERT_MASK) >> ETH_XMII_TX_INVERT_LSB)
#define ETH_XMII_TX_INVERT_SET(x)                                    (((x) << ETH_XMII_TX_INVERT_LSB) & ETH_XMII_TX_INVERT_MASK)
#define ETH_XMII_TX_INVERT_RESET                                     0x0 // 0
#define ETH_XMII_GIGE_QUAD_MSB                                       30
#define ETH_XMII_GIGE_QUAD_LSB                                       30
#define ETH_XMII_GIGE_QUAD_MASK                                      0x40000000
#define ETH_XMII_GIGE_QUAD_GET(x)                                    (((x) & ETH_XMII_GIGE_QUAD_MASK) >> ETH_XMII_GIGE_QUAD_LSB)
#define ETH_XMII_GIGE_QUAD_SET(x)                                    (((x) << ETH_XMII_GIGE_QUAD_LSB) & ETH_XMII_GIGE_QUAD_MASK)
#define ETH_XMII_GIGE_QUAD_RESET                                     0x0 // 0
#define ETH_XMII_RX_DELAY_MSB                                        29
#define ETH_XMII_RX_DELAY_LSB                                        28
#define ETH_XMII_RX_DELAY_MASK                                       0x30000000
#define ETH_XMII_RX_DELAY_GET(x)                                     (((x) & ETH_XMII_RX_DELAY_MASK) >> ETH_XMII_RX_DELAY_LSB)
#define ETH_XMII_RX_DELAY_SET(x)                                     (((x) << ETH_XMII_RX_DELAY_LSB) & ETH_XMII_RX_DELAY_MASK)
#define ETH_XMII_RX_DELAY_RESET                                      0x0 // 0
#define ETH_XMII_TX_DELAY_MSB                                        27
#define ETH_XMII_TX_DELAY_LSB                                        26
#define ETH_XMII_TX_DELAY_MASK                                       0x0c000000
#define ETH_XMII_TX_DELAY_GET(x)                                     (((x) & ETH_XMII_TX_DELAY_MASK) >> ETH_XMII_TX_DELAY_LSB)
#define ETH_XMII_TX_DELAY_SET(x)                                     (((x) << ETH_XMII_TX_DELAY_LSB) & ETH_XMII_TX_DELAY_MASK)
#define ETH_XMII_TX_DELAY_RESET                                      0x0 // 0
#define ETH_XMII_GIGE_MSB                                            25
#define ETH_XMII_GIGE_LSB                                            25
#define ETH_XMII_GIGE_MASK                                           0x02000000
#define ETH_XMII_GIGE_GET(x)                                         (((x) & ETH_XMII_GIGE_MASK) >> ETH_XMII_GIGE_LSB)
#define ETH_XMII_GIGE_SET(x)                                         (((x) << ETH_XMII_GIGE_LSB) & ETH_XMII_GIGE_MASK)
#define ETH_XMII_GIGE_RESET                                          0x0 // 0
#define ETH_XMII_OFFSET_PHASE_MSB                                    24
#define ETH_XMII_OFFSET_PHASE_LSB                                    24
#define ETH_XMII_OFFSET_PHASE_MASK                                   0x01000000
#define ETH_XMII_OFFSET_PHASE_GET(x)                                 (((x) & ETH_XMII_OFFSET_PHASE_MASK) >> ETH_XMII_OFFSET_PHASE_LSB)
#define ETH_XMII_OFFSET_PHASE_SET(x)                                 (((x) << ETH_XMII_OFFSET_PHASE_LSB) & ETH_XMII_OFFSET_PHASE_MASK)
#define ETH_XMII_OFFSET_PHASE_RESET                                  0x0 // 0
#define ETH_XMII_OFFSET_COUNT_MSB                                    23
#define ETH_XMII_OFFSET_COUNT_LSB                                    16
#define ETH_XMII_OFFSET_COUNT_MASK                                   0x00ff0000
#define ETH_XMII_OFFSET_COUNT_GET(x)                                 (((x) & ETH_XMII_OFFSET_COUNT_MASK) >> ETH_XMII_OFFSET_COUNT_LSB)
#define ETH_XMII_OFFSET_COUNT_SET(x)                                 (((x) << ETH_XMII_OFFSET_COUNT_LSB) & ETH_XMII_OFFSET_COUNT_MASK)
#define ETH_XMII_OFFSET_COUNT_RESET                                  0x0 // 0
#define ETH_XMII_PHASE1_COUNT_MSB                                    15
#define ETH_XMII_PHASE1_COUNT_LSB                                    8
#define ETH_XMII_PHASE1_COUNT_MASK                                   0x0000ff00
#define ETH_XMII_PHASE1_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE1_COUNT_MASK) >> ETH_XMII_PHASE1_COUNT_LSB)
#define ETH_XMII_PHASE1_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE1_COUNT_LSB) & ETH_XMII_PHASE1_COUNT_MASK)
#define ETH_XMII_PHASE1_COUNT_RESET                                  0x1 // 1
#define ETH_XMII_PHASE0_COUNT_MSB                                    7
#define ETH_XMII_PHASE0_COUNT_LSB                                    0
#define ETH_XMII_PHASE0_COUNT_MASK                                   0x000000ff
#define ETH_XMII_PHASE0_COUNT_GET(x)                                 (((x) & ETH_XMII_PHASE0_COUNT_MASK) >> ETH_XMII_PHASE0_COUNT_LSB)
#define ETH_XMII_PHASE0_COUNT_SET(x)                                 (((x) << ETH_XMII_PHASE0_COUNT_LSB) & ETH_XMII_PHASE0_COUNT_MASK)
#define ETH_XMII_PHASE0_COUNT_RESET                                  0x1 // 1
#define ETH_XMII_ADDRESS                                             0x18050030



#define ETH_CFG_ETH_SPARE_MSB                                        31
#define ETH_CFG_ETH_SPARE_LSB                                        22
#define ETH_CFG_ETH_SPARE_MASK                                       0xffc00000
#define ETH_CFG_ETH_SPARE_GET(x)                                     (((x) & ETH_CFG_ETH_SPARE_MASK) >> ETH_CFG_ETH_SPARE_LSB)
#define ETH_CFG_ETH_SPARE_SET(x)                                     (((x) << ETH_CFG_ETH_SPARE_LSB) & ETH_CFG_ETH_SPARE_MASK)
#define ETH_CFG_ETH_SPARE_RESET                                      0x0 // 0
#define ETH_CFG_ETH_TXEN_DELAY_MSB                                   21
#define ETH_CFG_ETH_TXEN_DELAY_LSB                                   20
#define ETH_CFG_ETH_TXEN_DELAY_MASK                                  0x00300000
#define ETH_CFG_ETH_TXEN_DELAY_GET(x)                                (((x) & ETH_CFG_ETH_TXEN_DELAY_MASK) >> ETH_CFG_ETH_TXEN_DELAY_LSB)
#define ETH_CFG_ETH_TXEN_DELAY_SET(x)                                (((x) << ETH_CFG_ETH_TXEN_DELAY_LSB) & ETH_CFG_ETH_TXEN_DELAY_MASK)
#define ETH_CFG_ETH_TXEN_DELAY_RESET                                 0x0 // 0
#define ETH_CFG_ETH_TXD_DELAY_MSB                                    19
#define ETH_CFG_ETH_TXD_DELAY_LSB                                    18
#define ETH_CFG_ETH_TXD_DELAY_MASK                                   0x000c0000
#define ETH_CFG_ETH_TXD_DELAY_GET(x)                                 (((x) & ETH_CFG_ETH_TXD_DELAY_MASK) >> ETH_CFG_ETH_TXD_DELAY_LSB)
#define ETH_CFG_ETH_TXD_DELAY_SET(x)                                 (((x) << ETH_CFG_ETH_TXD_DELAY_LSB) & ETH_CFG_ETH_TXD_DELAY_MASK)
#define ETH_CFG_ETH_TXD_DELAY_RESET                                  0x0 // 0
#define ETH_CFG_ETH_RXDV_DELAY_MSB                                   17
#define ETH_CFG_ETH_RXDV_DELAY_LSB                                   16
#define ETH_CFG_ETH_RXDV_DELAY_MASK                                  0x00030000
#define ETH_CFG_ETH_RXDV_DELAY_GET(x)                                (((x) & ETH_CFG_ETH_RXDV_DELAY_MASK) >> ETH_CFG_ETH_RXDV_DELAY_LSB)
#define ETH_CFG_ETH_RXDV_DELAY_SET(x)                                (((x) << ETH_CFG_ETH_RXDV_DELAY_LSB) & ETH_CFG_ETH_RXDV_DELAY_MASK)
#define ETH_CFG_ETH_RXDV_DELAY_RESET                                 0x0 // 0
#define ETH_CFG_ETH_RXD_DELAY_MSB                                    15
#define ETH_CFG_ETH_RXD_DELAY_LSB                                    14
#define ETH_CFG_ETH_RXD_DELAY_MASK                                   0x0000c000
#define ETH_CFG_ETH_RXD_DELAY_GET(x)                                 (((x) & ETH_CFG_ETH_RXD_DELAY_MASK) >> ETH_CFG_ETH_RXD_DELAY_LSB)
#define ETH_CFG_ETH_RXD_DELAY_SET(x)                                 (((x) << ETH_CFG_ETH_RXD_DELAY_LSB) & ETH_CFG_ETH_RXD_DELAY_MASK)
#define ETH_CFG_ETH_RXD_DELAY_RESET                                  0x0 // 0
#define ETH_CFG_RMII_GE0_MASTER_MSB                                  12
#define ETH_CFG_RMII_GE0_MASTER_LSB                                  12
#define ETH_CFG_RMII_GE0_MASTER_MASK                                 0x00001000
#define ETH_CFG_RMII_GE0_MASTER_GET(x)                               (((x) & ETH_CFG_RMII_GE0_MASTER_MASK) >> ETH_CFG_RMII_GE0_MASTER_LSB)
#define ETH_CFG_RMII_GE0_MASTER_SET(x)                               (((x) << ETH_CFG_RMII_GE0_MASTER_LSB) & ETH_CFG_RMII_GE0_MASTER_MASK)
#define ETH_CFG_RMII_GE0_MASTER_RESET                                0x1 // 1
#define ETH_CFG_MII_CNTL_SPEED_MSB                                   11
#define ETH_CFG_MII_CNTL_SPEED_LSB                                   11
#define ETH_CFG_MII_CNTL_SPEED_MASK                                  0x00000800
#define ETH_CFG_MII_CNTL_SPEED_GET(x)                                (((x) & ETH_CFG_MII_CNTL_SPEED_MASK) >> ETH_CFG_MII_CNTL_SPEED_LSB)
#define ETH_CFG_MII_CNTL_SPEED_SET(x)                                (((x) << ETH_CFG_MII_CNTL_SPEED_LSB) & ETH_CFG_MII_CNTL_SPEED_MASK)
#define ETH_CFG_MII_CNTL_SPEED_RESET                                 0x0 // 0
#define ETH_CFG_RMII_GE0_MSB                                         10
#define ETH_CFG_RMII_GE0_LSB                                         10
#define ETH_CFG_RMII_GE0_MASK                                        0x00000400
#define ETH_CFG_RMII_GE0_GET(x)                                      (((x) & ETH_CFG_RMII_GE0_MASK) >> ETH_CFG_RMII_GE0_LSB)
#define ETH_CFG_RMII_GE0_SET(x)                                      (((x) << ETH_CFG_RMII_GE0_LSB) & ETH_CFG_RMII_GE0_MASK)
#define ETH_CFG_RMII_GE0_RESET                                       0x0 // 0
#define ETH_CFG_GE0_SGMII_MSB                                        6
#define ETH_CFG_GE0_SGMII_LSB                                        6
#define ETH_CFG_GE0_SGMII_MASK                                       0x00000040
#define ETH_CFG_GE0_SGMII_GET(x)                                     (((x) & ETH_CFG_GE0_SGMII_MASK) >> ETH_CFG_GE0_SGMII_LSB)
#define ETH_CFG_GE0_SGMII_SET(x)                                     (((x) << ETH_CFG_GE0_SGMII_LSB) & ETH_CFG_GE0_SGMII_MASK)
#define ETH_CFG_GE0_SGMII_RESET                                      0x0 // 0
#define ETH_CFG_GE0_ERR_EN_MSB                                       5
#define ETH_CFG_GE0_ERR_EN_LSB                                       5
#define ETH_CFG_GE0_ERR_EN_MASK                                      0x00000020
#define ETH_CFG_GE0_ERR_EN_GET(x)                                    (((x) & ETH_CFG_GE0_ERR_EN_MASK) >> ETH_CFG_GE0_ERR_EN_LSB)
#define ETH_CFG_GE0_ERR_EN_SET(x)                                    (((x) << ETH_CFG_GE0_ERR_EN_LSB) & ETH_CFG_GE0_ERR_EN_MASK)
#define ETH_CFG_GE0_ERR_EN_RESET                                     0x0 // 0
#define ETH_CFG_MII_GE0_SLAVE_MSB                                    4
#define ETH_CFG_MII_GE0_SLAVE_LSB                                    4
#define ETH_CFG_MII_GE0_SLAVE_MASK                                   0x00000010
#define ETH_CFG_MII_GE0_SLAVE_GET(x)                                 (((x) & ETH_CFG_MII_GE0_SLAVE_MASK) >> ETH_CFG_MII_GE0_SLAVE_LSB)
#define ETH_CFG_MII_GE0_SLAVE_SET(x)                                 (((x) << ETH_CFG_MII_GE0_SLAVE_LSB) & ETH_CFG_MII_GE0_SLAVE_MASK)
#define ETH_CFG_MII_GE0_SLAVE_RESET                                  0x0 // 0
#define ETH_CFG_MII_GE0_MASTER_MSB                                   3
#define ETH_CFG_MII_GE0_MASTER_LSB                                   3
#define ETH_CFG_MII_GE0_MASTER_MASK                                  0x00000008
#define ETH_CFG_MII_GE0_MASTER_GET(x)                                (((x) & ETH_CFG_MII_GE0_MASTER_MASK) >> ETH_CFG_MII_GE0_MASTER_LSB)
#define ETH_CFG_MII_GE0_MASTER_SET(x)                                (((x) << ETH_CFG_MII_GE0_MASTER_LSB) & ETH_CFG_MII_GE0_MASTER_MASK)
#define ETH_CFG_MII_GE0_MASTER_RESET                                 0x0 // 0
#define ETH_CFG_GMII_GE0_MSB                                         2
#define ETH_CFG_GMII_GE0_LSB                                         2
#define ETH_CFG_GMII_GE0_MASK                                        0x00000004
#define ETH_CFG_GMII_GE0_GET(x)                                      (((x) & ETH_CFG_GMII_GE0_MASK) >> ETH_CFG_GMII_GE0_LSB)
#define ETH_CFG_GMII_GE0_SET(x)                                      (((x) << ETH_CFG_GMII_GE0_LSB) & ETH_CFG_GMII_GE0_MASK)
#define ETH_CFG_GMII_GE0_RESET                                       0x0 // 0
#define ETH_CFG_MII_GE0_MSB                                          1
#define ETH_CFG_MII_GE0_LSB                                          1
#define ETH_CFG_MII_GE0_MASK                                         0x00000002
#define ETH_CFG_MII_GE0_GET(x)                                       (((x) & ETH_CFG_MII_GE0_MASK) >> ETH_CFG_MII_GE0_LSB)
#define ETH_CFG_MII_GE0_SET(x)                                       (((x) << ETH_CFG_MII_GE0_LSB) & ETH_CFG_MII_GE0_MASK)
#define ETH_CFG_MII_GE0_RESET                                        0x0 // 0
#define ETH_CFG_RGMII_GE0_MSB                                        0
#define ETH_CFG_RGMII_GE0_LSB                                        0
#define ETH_CFG_RGMII_GE0_MASK                                       0x00000001
#define ETH_CFG_RGMII_GE0_GET(x)                                     (((x) & ETH_CFG_RGMII_GE0_MASK) >> ETH_CFG_RGMII_GE0_LSB)
#define ETH_CFG_RGMII_GE0_SET(x)                                     (((x) << ETH_CFG_RGMII_GE0_LSB) & ETH_CFG_RGMII_GE0_MASK)
#define ETH_CFG_RGMII_GE0_RESET                                      0x0 // 0
#define ETH_CFG_ADDRESS                                              0x18070000




/*
 * ownership of descriptors between DMA and cpu
 */
#define ath_gmac_rx_owned_by_dma(_ds)	((_ds)->is_empty == 1)
#define ath_gmac_rx_give_to_dma(_ds)	((_ds)->is_empty = 1)
#define ath_gmac_tx_owned_by_dma(_ds)	((_ds)->is_empty == 0)
#define ath_gmac_tx_give_to_dma(_ds)	((_ds)->is_empty = 0)
#define ath_gmac_tx_own(_ds)		((_ds)->is_empty = 1)

/*
 * link settings
 */
#define ath_gmac_set_mac_duplex(_mac, _fdx)	do {	\
	if ((_fdx)) {					\
		ath_gmac_reg_rmw_set(_mac,		\
			ATH_MAC_CFG2, ATH_MAC_CFG2_FDX);\
	} else {					\
		ath_gmac_reg_rmw_clear(_mac,		\
			ATH_MAC_CFG2, ATH_MAC_CFG2_FDX);\
	}						\
} while (0)

#define ath_gmac_set_mac_if(_mac, _isXGMII)	do {		\
	ath_gmac_reg_rmw_clear(_mac, ATH_MAC_CFG2,		\
				ATH_MAC_CFG2_IF_1000 |		\
				ATH_MAC_CFG2_IF_10_100);	\
	if ((_isXGMII)) {					\
		ath_gmac_reg_rmw_set(_mac, ATH_MAC_CFG2,	\
				ATH_MAC_CFG2_IF_1000);		\
		ath_gmac_reg_rmw_set(_mac, ATH_MAC_FIFO_CFG_5,	\
				ATH_BYTE_PER_CLK_EN);		\
	} else {						\
		ath_gmac_reg_rmw_set(_mac, ATH_MAC_CFG2,	\
				ATH_MAC_CFG2_IF_10_100);	\
		ath_gmac_reg_rmw_clear(_mac, ATH_MAC_FIFO_CFG_5,\
				ATH_BYTE_PER_CLK_EN);		\
	}							\
} while (0)

#define ath_gmac_set_mac_speed(_mac, _is100)	do {		\
	if ((_is100)) {						\
		ath_gmac_reg_rmw_set(_mac, ATH_MAC_IFCTL,	\
					ATH_MAC_IFCTL_SPEED);	\
	} else {						\
		ath_gmac_reg_rmw_clear(_mac, ATH_MAC_IFCTL,	\
					ATH_MAC_IFCTL_SPEED);	\
	}							\
} while (0)

#endif /* __QCA_ETH_956X_H */
