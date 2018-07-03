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

//#include <gmac_defines.h>
//#include <prototypes.h>

#include <config.h>
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <command.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <asm/types.h>

#include <atheros.h>
#include "qca-eth-956x.h"
#include "qca-eth-956x_phy.h"

#ifdef ATH_RGMII_CAL

#define NUM_DESCRIPTORS		10	//Number of packets to be looped back
#define node_tx_buf_len		100	// No of bytes per packet to be looped back

#define DEBUG		0
#define DEBUG_1 	1

#define GE0_PEMSTAT_RBYT	(0x9c + ATH_GE0_BASE)
#define GE0_PEMSTAT_RPKT	(0xA0 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RFCS	(0xA4 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RMCA	(0xA8 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RBCA	(0xAC + ATH_GE0_BASE)
#define GE0_PEMSTAT_RXCF	(0xB0 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RXPF	(0xB4 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RXUO	(0xB8 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RALN	(0xBC + ATH_GE0_BASE)
#define GE0_PEMSTAT_RFLR	(0xC0 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RCDE	(0xC4 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RCSE	(0xC8 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RUND	(0xCC + ATH_GE0_BASE)
#define GE0_PEMSTAT_ROVR	(0xD0 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RFRG	(0xD4 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RJBR	(0xD8 + ATH_GE0_BASE)
#define GE0_PEMSTAT_RDRP	(0xDC + ATH_GE0_BASE)
#define GE0_PEMSTAT_TPKT	(0xE0 + ATH_GE0_BASE)

#define NUM_DESCS 10

void init_s17_lpbk(void);
uint32_t athrs17_reg_read(uint32_t reg_addr);
void athrs17_reg_write(uint32_t reg_addr, uint32_t reg_val);

int results[5] = { 0, 1, 1, 1, 0 };

int find;

void big_del(void)
{
	int i;
	for (i = 0; i < 10000; i++) ;
}

// This should tell us what the best of the 4 values is. It should also tell us what the longest sequence is.
// Since only four bits are used the best of 4 values can be easily arrived at by a truth table.
// Presently we have an algorithm though.
int find_value(void)
{
	int i;
	int start_ok = 9;
	int end_ok = 9;
	int longest_start_ok = 0;
	int longest_end_ok = 0;
	int longest_ok_cnt = -1;
	int first = 0;

	for (i = 0; i < 5; i++) {
#if DEBUG
		printf("results [%d]: %d\n", i, results[i]);
#endif
		if (results[i] == 1) {
			if (start_ok == 9) {
				start_ok = i;
				if (first == 0) {
					longest_start_ok = i;
					longest_end_ok = i;
					first = 1;
				}
			}
		}
		if (results[i] == 0) {
			if (end_ok == 9) {
				end_ok = i - 1;
			}
			if ((end_ok - start_ok) > longest_ok_cnt) {
				longest_start_ok = start_ok;
				longest_end_ok = end_ok;
				longest_ok_cnt = (end_ok - start_ok);
			}
			start_ok = 9;
			end_ok = 9;
		}
	}

#if DEBUG
	printf("FINAL VALUE - ");
#endif
	find = (longest_end_ok + longest_start_ok) / 2;
#if DEBUG
	printf("find - %d\n", find);
	printf("FINAL OK COUNT - %d\n", longest_ok_cnt + 1);
#endif
	return (longest_ok_cnt + 1);
}

int pkt_compare_data(void)
{
	unsigned int i, j;
	//unsigned int k,rddata;
	unsigned int node_rx_buf_len;
	//unsigned int * node_tx_desc_ptr = (unsigned int *) 0xa0280000;
	unsigned int *node_rx_desc_ptr = (unsigned int *)0xa0380000;
	unsigned int *node_tx_buf_addr = (unsigned int *)0xa0680000;
	unsigned int *node_rx_buf_addr = (unsigned int *)0xa0580000;
	unsigned int error = 0;
	unsigned pkt_err[NUM_DESCS];

	node_rx_buf_len = (*(node_rx_desc_ptr + 0x1) & 0xfff) - 0x4;
	// node_tx_buf_len = *(node_tx_desc_ptr + (NUM_DESCS-1)*0x3+0x1) & 0xfff;

	for (j = 0; j < NUM_DESCS; j++) {
		node_rx_buf_len = (*(node_rx_desc_ptr + (NUM_DESCS - 1) * 0x3 + 0x1) & 0xfff) - 0x4;
		pkt_err[j] = 0;
		for (i = 0; i < (node_rx_buf_len / 4); i++) {
			if (((*(node_rx_buf_addr + i + (j * 0x100))) != *(node_tx_buf_addr + i))) {
				error = error + 0x1;
				pkt_err[j] = 1;
			}
		}
		//node_rx_buf_addr = node_rx_buf_addr + 0x100;
	}
	if (error == 0) {
		return 0;
	} else {
		for (j = 0; j < NUM_DESCS; j++) {
			node_rx_buf_len = (*(node_rx_desc_ptr + (NUM_DESCS - 1) * 0x3 + 0x1) & 0xfff) - 0x4;
			if (pkt_err[j] == 1) {
#if DEBUG
				printf("PKT %d\n", j);
				printf("---------------------------------\n");

				for (i = 0; i < (node_rx_buf_len / 4); i++) {
					//if(((*(node_rx_buf_addr + i )) != *(node_tx_buf_addr + i)))
					if (((*(node_rx_buf_addr + i + (j * 0x100))) != *(node_tx_buf_addr + i))) {
						printf("->");
					} else {
						printf("  ");
					}
					printf("%x", (*(node_rx_buf_addr + i + (j * 0x100))));
					printf("  ");
					printf("%x\n", (*(node_tx_buf_addr + i)));
				}
				printf("---------------------------------\n");
#endif
			}
			//node_rx_buf_addr = node_rx_buf_addr + 0x100;
		}
		return 1;
	}
}

void rgmii_calib(ath_gmac_mac_t * mac)
{

	unsigned int i;
	unsigned int j;
	unsigned int k, l, m;
	unsigned int rddata, error = 0;
    volatile unsigned int * rd_register;
	unsigned int node_rx_buf_len = 1600;
	unsigned int node_rx_buf_len1;
	unsigned int *node_tx_desc_ptr = (unsigned int *)0xa0280000;
	unsigned int *node_rx_desc_ptr = (unsigned int *)0xa0380000;
	unsigned int *node_rx_buf_addr = (unsigned int *)0xa0580000;
	unsigned int *node_tx_buf_addr = (unsigned int *)0xa0680000;
	unsigned int *node_comp_result = (unsigned int *)0xa0200000;
	unsigned int s17_tx_pkt = 0;
	unsigned int s17_rx_pkt = 0;
	unsigned int to;
	unsigned int pass = 1;
	unsigned int fail = 0;
	int lgst = 0;
	int old_lgst = 0;
	unsigned int xmii[16];
	unsigned int eth_cfg[16];
	unsigned int xmii_val = 0;
	unsigned int eth_cfg_val = 1;
	unsigned int tx_fix = 0;


	// GIGE Enable
	ath_reg_wr(ETH_XMII_ADDRESS,	ETH_XMII_TX_INVERT_SET(0x1) |
					ETH_XMII_RX_DELAY_SET(0x2) |
					ETH_XMII_TX_DELAY_SET(0x1) |
					ETH_XMII_GIGE_SET(0x1));

	while ((ath_reg_rd(SGMII_SERDES_ADDRESS) & SGMII_SERDES_LOCK_DETECT_STATUS_SET(1)) == 0) {
		printf("TEST: WAIT FOR LOCK\n");
	}

	big_del();

	// MAC INITS
	// RGMII Enable on GE0
	//eth_init();
	init_s17_lpbk();
	athrs17_reg_write(0x30, 1);

	ath_reg_wr(ETH_CFG_ADDRESS,	ETH_CFG_ETH_RXDV_DELAY_SET(0x3) |
					ETH_CFG_ETH_RXD_DELAY_SET(0x3) |
					ETH_CFG_RGMII_GE0_SET(0x1));

	ath_reg_rmw_clear(QCA_RST_RESET_REG, RST_RESET_GE0_MAC_RESET_MASK);	// Bringing GE0 out of RESET
	ath_gmac_reg_wr(mac, ATH_MAC_CFG2, 0x7235);	//for 1000mbps
	//ath_reg_wr(GE0_MAC_CONFIG_2,0x7135);  //for 100mbps
	ath_gmac_reg_wr(mac, ATH_MAC_IFCTL, 0x00000);
	ath_gmac_reg_wr(mac, ATH_MAC_CFG1, 0x005);
	//ath_reg_wr(GE0_MAC_CONFIG_1,0x105);  // For MAC Loopback
	ath_gmac_reg_wr(mac, ATH_DMA_INTR_MASK, 0);	// Disable interrupt mask
	ath_gmac_reg_wr(mac, ATH_GE_MAC_ADDR1, 0x003fffff);	//ethernet mac address
	ath_gmac_reg_wr(mac, ATH_GE_MAC_ADDR2, 0xfffe0000);	//ethernet mac address
	ath_gmac_reg_wr(mac, ATH_MAC_MII_MGMT_CFG, 0x6);	//clock/20= 2MHz
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_0, 0x1f00);	// Enable the FIFO modules
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_1, 0x10ffff);
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_3, 0x1f00140);
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_4, 0x1000);
	//ath_reg_wr(GE0_FIFO_CFG_REG_5, 0xbefff); //enable drop
	ath_gmac_reg_wr(mac, ATH_MAC_FIFO_CFG_5, 0xfffff);	//for 1000Mbps
	//ath_reg_wr(GE0_FIFO_CFG_REG_5, 0x7ffff);//for 100Mbps

	//************
	// PACKETS
	//***********

	// Initialise Data in Memory for TX and RX
	for (i = 0; i < node_tx_buf_len; i++)
		*(node_tx_buf_addr + i) = i | (i + 1) << 8 | (i + 2) << 16 | (i + 3) << 24;

#if DEBUG
	printf("TEST: Inits Done\n");
#endif
	// Set Up Transmit Descriptor Table

	for (i = 0; i < NUM_DESCRIPTORS; i++) {
		*(node_tx_desc_ptr + (i * 0x3)) = ((unsigned int)node_tx_buf_addr & 0x0fffffff);
		*(node_tx_desc_ptr + (i * 0x3) + 0x1) = (node_tx_buf_len & 0x7fffffff);

		if (i == (NUM_DESCRIPTORS - 1))
			*(node_tx_desc_ptr + (i * 0x3) + 0x2) = ((unsigned int)node_tx_desc_ptr & 0x0fffffff);
		else
			*(node_tx_desc_ptr + (i * 0x3) + 0x2) = ((unsigned int)node_tx_desc_ptr & 0x0fffffff) + (i * 0xc) + 0xc;
	}

	ath_gmac_reg_wr(mac, ATH_DMA_TX_DESC, ((unsigned int)node_tx_desc_ptr & 0x0fffffff));
	ath_gmac_reg_wr(mac, ATH_DMA_TX_STATUS, 0xfffffff);	// clear dma status

	for (i = 0; i < NUM_DESCRIPTORS; i++) {
		*(node_rx_desc_ptr + (i * 0x3)) = ((unsigned int)node_rx_buf_addr & 0x0fffffff);
		*(node_rx_desc_ptr + (i * 0x3) + 0x1) = (node_rx_buf_len & 0xfff) | BIT(31);
		if (i == (NUM_DESCRIPTORS - 1))
			*(node_rx_desc_ptr + (i * 0x3) + 0x2) = ((unsigned int)node_rx_desc_ptr & 0x0fffffff);
		else
			*(node_rx_desc_ptr + (i * 0x3) + 0x2) = ((unsigned int)node_rx_desc_ptr & 0x0fffffff) + (i * 0xc) + 0xc;
		node_rx_buf_addr = node_rx_buf_addr + 0x100;

	}

	ath_gmac_reg_wr(mac, ATH_DMA_RX_DESC, ((unsigned int)node_rx_desc_ptr & 0x0fffffff));
	ath_gmac_reg_wr(mac, ATH_DMA_RX_STATUS, 0xfffffff);	// clear dma status

	k = 0;

	// Enable TX and RX MAC
	ath_gmac_reg_wr(mac, ATH_MAC_CFG1, 0x005);

	// This routine will go through 16 combinations to find the best value for TX_DELAY, GIGE_QUAD, TX_INVERT
	for (l = 0; l < 16; l++) {
		// initialize pass. this will be made zero if there is a failure in packet reception compare
		pass = 1;
		// fail due to checks in rx etc. this is not the same as !pass
		fail = 0;

		// GIGE_QUAD  - 0
		// TX_INVERT  - 0
		// TX_DELAY   - 0,1,2,3
		if (l < 4) {
			// GIGE Enable and TX_DELAY
			rddata = ETH_XMII_GIGE_SET(0x1) |
				ETH_XMII_TX_DELAY_SET(l);
			ath_reg_wr(ETH_XMII_ADDRESS, rddata);
			rddata = ath_reg_rd(ETH_XMII_ADDRESS);
#if DEBUG
			printf("TEST: ETH_XMII - 0x%08x\n", rddata);
#endif
		}
		// GIGE_QUAD  - 1
		// TX_INVERT  - 0
		// TX_DELAY   - 0,1,2,3
		if ((l < 8) && (l > 3)) {
			// GIGE Enable and TX_DELAY & GIGE_QUAD
			rddata = ETH_XMII_GIGE_QUAD_SET(0x1) |
				ETH_XMII_GIGE_SET(0x1) |
				ETH_XMII_TX_DELAY_SET(l);
			ath_reg_wr(ETH_XMII_ADDRESS, rddata);
			rddata = ath_reg_rd(ETH_XMII_ADDRESS);
#if DEBUG
			printf("TEST: ETH_XMII - 0x%08x\n", rddata);
#endif
		}
		// GIGE_QUAD  - 0
		// TX_INVERT  - 1
		// TX_DELAY   - 0,1,2,3
		if ((l < 12) && (l > 7)) {
			// GIGE Enable and TX_DELAY and TX_INVERT
			rddata = ETH_XMII_TX_INVERT_SET(0x1) |
				ETH_XMII_GIGE_SET(0x1) |
				ETH_XMII_TX_DELAY_SET(l);
			ath_reg_wr(ETH_XMII_ADDRESS, rddata);
			rddata = ath_reg_rd(ETH_XMII_ADDRESS);
#if DEBUG
			printf("TEST: ETH_XMII - 0x%08x\n", rddata);
#endif
		}
		// GIGE_QUAD  - 0
		// TX_INVERT  - 1
		// TX_DELAY   - 0,1,2,3
		if ((l < 16) && (l > 11)) {
			// GIGE Enable and TX_DELAY and TX_INVERT and GIGE_QUAD
			rddata = ETH_XMII_TX_INVERT_SET(0x1) |
				ETH_XMII_GIGE_QUAD_SET(0x1) |
				ETH_XMII_GIGE_SET(0x1) |
				ETH_XMII_TX_DELAY_SET(l);
			ath_reg_wr(ETH_XMII_ADDRESS, rddata);
			rddata = ath_reg_rd(ETH_XMII_ADDRESS);
#if DEBUG
			printf("TEST: ETH_XMII - 0x%08x\n", rddata);
#endif
		}
		xmii[l] = rddata;

		// counts when to print out counter stats
		k++;
		// Set Up Receive Descriptor Table
		node_rx_buf_len = 0x0;
		ath_gmac_reg_wr(mac, ATH_DMA_RX_CTRL, 0x1);	// enable dma rx
		ath_gmac_reg_wr(mac, ATH_DMA_TX_CTRL, 0x1);	// enable dma tx

        rd_register = node_tx_desc_ptr + (NUM_DESCRIPTORS - 1) * 0x3 + 0x1; 
        rddata = (*(rd_register) & BIT(31));
		while (rddata != BIT(31))
			rddata = (*(rd_register) & BIT(31));
#if DEBUG
		printf("TEST: Tx Done \n");
#endif

		to = 0;
        rd_register = node_rx_desc_ptr + (NUM_DESCS - 1) * 0x3 + 0x1;
		rddata = (*(rd_register) & BIT(31));
		while (rddata != 0x0) {
			rddata = (*(rd_register) & BIT(31));
			to++;
			if (to > 100000) {
#if DEBUG
				printf("TEST: ERROR!! Atleast 1 packet in GE0 not seen.\n");
#endif
				fail = 1;
				break;
			}
		}
#if DEBUG
		printf("TEST: Rx Done \n");
#endif

		if (k % 1 == 0) {
			for (j = GE0_PEMSTAT_RBYT; j <= GE0_PEMSTAT_RDRP; j = j + 4) {
				rddata = ath_reg_rd(j);
				switch (j) {
#if DEBUG
				case GE0_PEMSTAT_RPKT:
					printf("TEST: RPKT - 0x%08x\n", rddata);
					break;
				case GE0_PEMSTAT_TPKT:
					printf("TEST: TPKT - 0x%08x\n", rddata);
					break;
#endif
				}
			}
#ifdef ATH_S17_MAC0_SGMII
			s17_rx_pkt = athrs17_reg_read(0x163c) + (athrs17_reg_read(0x1640) << 16);
#else
			s17_rx_pkt = athrs17_reg_read(0x103c) + (athrs17_reg_read(0x1040) << 16);
#endif
#if DEBUG
			printf("TEST: RPKT in S17 0x%08x\n", s17_rx_pkt);
#endif
#ifdef ATH_S17_MAC0_SGMII
			s17_tx_pkt = athrs17_reg_read(0x1684) + (athrs17_reg_read(0x1688) << 16);
#else
			s17_tx_pkt = athrs17_reg_read(0x1084) + (athrs17_reg_read(0x1088) << 16);
#endif
#if DEBUG
			printf("TEST: TPKT in S17 0x%08x\n", s17_tx_pkt);
#endif
			// Compare BYTES in TX
			if (s17_tx_pkt != 0x410) {
#if DEBUG
				printf("TEST: PKTS @ S17 - 0x%08x\n", rddata);
#endif
				pass = 0;
				fail = 1;
			}

		}
		if (fail == 0) {
			error = pkt_compare_data();
		}
		if (error == 0) {
#if DEBUG
			printf("TEST: PACKET COMPARISON PASS\n");
#endif
		} else {
#if DEBUG
			printf("TEST: ERROR!! PACKET COMPARISON FAIL\n");
#endif
			fail = 1;
		}

		for (i = 0; i < NUM_DESCRIPTORS; i++) {
			*(node_tx_desc_ptr + (i * 0x3) + 0x1) = (node_tx_buf_len & 0x7fffffff);
			*(node_rx_desc_ptr + (i * 0x3) + 0x1) = (node_rx_buf_len & 0xfff) | BIT(31);
		}

		// populate results and find the optimum value of programming
		results[(l % 4)] = pass;
		if (((l % 4) == 3)) {
			lgst = find_value();
			if (lgst > old_lgst) {
				old_lgst = lgst;
				xmii_val = xmii[(l - 3) + find];
			}
		}
	}
#if DEBUG_1
	printf("TEST: FINAL REG VAL after TX Calibration - 0x%08x\n", xmii_val);
#endif
	tx_fix = xmii_val;

	old_lgst = 0;

	// Using the previously arrived at value of TX Calib we calibrate RX DELAYS. For this we use RX DAT and EN Delays
	for (l = 0; l < 16; l++) {
		// initialize pass. this will be made zero if there is a failure in packet reception compare
		pass = 1;
		// fail due to checks in rx etc. this is not the same as !pass
		fail = 0;
		rddata = ath_reg_rd(ETH_CFG_ADDRESS);
#if DEBUG
		printf("TEST: Initial ETH_CFG - 0x%08x\n", rddata);
#endif

		// RXD_DELAY  - l / 4 -> 0, 1, 2, 3
		// RXEN_DELAY - l / 4 -> 0, 1, 2, 3
		// RX_DELAY   - l & 3 -> 0, 1, 2, 3
		ath_reg_rmw_clear(ETH_CFG_ADDRESS,
					ETH_CFG_ETH_RXDV_DELAY_MASK |
					ETH_CFG_ETH_RXD_DELAY_MASK);
		ath_reg_rmw_set(ETH_CFG_ADDRESS,
					ETH_CFG_ETH_RXDV_DELAY_SET(l / 4) |
					ETH_CFG_ETH_RXD_DELAY_SET(l / 4));
		rddata = ath_reg_rd(ETH_CFG_ADDRESS);
#if DEBUG
		printf("TEST: ETH_CFG - 0x%08x\n", rddata);
#endif
		eth_cfg[l] = rddata;
		rddata = tx_fix | ETH_XMII_RX_DELAY_SET(l);
		ath_reg_wr(ETH_XMII_ADDRESS, rddata);

		xmii[l] = rddata;

		// counts when to print out counter stats
		k++;
		// Set Up Receive Descriptor Table
		node_rx_buf_len = 0x0;
		ath_gmac_reg_wr(mac, ATH_DMA_RX_CTRL, 0x1);	// enable dma rx
		ath_gmac_reg_wr(mac, ATH_DMA_TX_CTRL, 0x1);	// enable dma tx
        rd_register = node_tx_desc_ptr + (NUM_DESCRIPTORS - 1) * 0x3 + 0x1;
		rddata = (*(rd_register) & BIT(31));
		while (rddata != BIT(31))
			rddata = (*(rd_register) & BIT(31));
#if DEBUG
		printf("TEST: Tx Done \n");
#endif

		to = 0;
        rd_register = node_rx_desc_ptr + (NUM_DESCS - 1) * 0x3 + 0x1;
		rddata = (*(rd_register) & BIT(31));
		while (rddata != 0x0) {
			rddata = (*(rd_register) & BIT(31));
			to++;
			if (to > 100000) {
#if DEBUG
				printf("TEST: ERROR!! Atleast 1 packet in GE0 not seen.\n");
#endif
				// This check for RX.
				pass = 0;
				fail = 1;
				break;
			}
		}
#if DEBUG
		printf("TEST: Rx Done \n");
#endif

		if (k % 1 == 0) {
			for (j = GE0_PEMSTAT_RBYT; j <= GE0_PEMSTAT_RDRP; j = j + 4) {
				rddata = ath_reg_rd(j);
				switch (j) {
#if DEBUG
				case GE0_PEMSTAT_RPKT:
					printf("TEST: RPKT 0x%08x\n", rddata);
					break;
				case GE0_PEMSTAT_TPKT:
					printf("TEST: TPKT 0x%08x\n", rddata);
					break;
#endif
				}
			}
#ifdef ATH_S17_MAC0_SGMII
			s17_rx_pkt = athrs17_reg_read(0x163c) + (athrs17_reg_read(0x1640) << 16);
#else
			s17_rx_pkt = athrs17_reg_read(0x103c) + (athrs17_reg_read(0x1040) << 16);
#endif
#if DEBUG
			printf("TEST: RPKT in S17 0x%08x\n", s17_rx_pkt);
#endif
#ifdef ATH_S17_MAC0_SGMII
			s17_tx_pkt = athrs17_reg_read(0x1684) + (athrs17_reg_read(0x1688) << 16);
#else
			s17_tx_pkt = athrs17_reg_read(0x1084) + (athrs17_reg_read(0x1088) << 16);
#endif
#if DEBUG
			printf("TEST: TPKT in S17 0x%08x\n", s17_tx_pkt);
#endif
			// Compare BYTES in TX
			if (s17_tx_pkt != 0x410) {
#if DEBUG
				printf("TEST: PKTS @ S17 - 0x%08x\n", rddata);
#endif
				pass = 0;
				fail = 1;
			}

		}
		if (fail == 0) {
			error = pkt_compare_data();
		}
		if (error == 0) {
			//printf("TEST: PACKET COMPARISON PASS\n");
		} else {
#if DEBUG
			printf("TEST: ERROR!! PACKET COMPARISON FAIL\n");
#endif
			fail = 1;
			// Different from TX. This ensures packets are received back properly for a valid config.
			pass = 0;
		}

		for (i = 0; i < NUM_DESCRIPTORS; i++) {
			*(node_tx_desc_ptr + (i * 0x3) + 0x1) = (node_tx_buf_len & 0x7fffffff);
			*(node_rx_desc_ptr + (i * 0x3) + 0x1) = (node_rx_buf_len & 0xfff) | BIT(31);
		}

		// populate results and find the optimum value of programming
		// For every set of 4 configurations find longest valid configs and number.
		results[(l % 4)] = pass;
		if (((l % 4) == 3)) {
			lgst = find_value();
			if (lgst > old_lgst) {
				old_lgst = lgst;
				xmii_val = xmii[(l - 3) + find];
				eth_cfg_val = eth_cfg[(l - 3) + find];
			}
		}
	}
	// And write to these registers.
#if DEBUG_1
	printf("TEST: FINAL XMII VAL after RX Calibration - 0x%08x\n", xmii_val);
#endif
	ath_reg_wr(ETH_XMII_ADDRESS, xmii_val);
#if DEBUG_1
	printf("TEST: FINAL ETH_CFG VAL after RX Calibration - 0x%08x\n", eth_cfg_val);
#endif
	ath_reg_wr(ETH_CFG_ADDRESS, eth_cfg_val);
	ath_gmac_reg_wr(mac,ATH_MAC_CFG1, BIT(31));

}

#endif /* #ifdef RGMII_CAL */
