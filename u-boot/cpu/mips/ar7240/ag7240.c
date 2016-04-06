#include <config.h>
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <command.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <asm/types.h>
#include "ar7240_soc.h"
#include "ag7240.h"
#include "ag7240_phy.h"

DECLARE_GLOBAL_DATA_PTR;

#if (CONFIG_COMMANDS & CFG_CMD_MII)
#include <miiphy.h>
#else
#define _1000BASET	1000
#define _100BASET	100
#define _10BASET	10
#endif

#define ag7240_unit2mac(_unit)	ag7240_macs[(_unit)]
#define ag7240_name2mac(name)	strcmp(name,"eth0") ? ag7240_unit2mac(1) : ag7240_unit2mac(0)

uint16_t ag7240_miiphy_read(char *devname, uint32_t phaddr, uint8_t reg);
void ag7240_miiphy_write(char *devname, uint32_t phaddr, uint8_t reg, uint16_t data);
ag7240_mac_t *ag7240_macs[CFG_AG7240_NMACS];

/* TODO: remove extern and include header file*/
extern void qca_sys_clocks(u32 *cpu_clk, u32 *ddr_clk, u32 *ahb_clk,
						   u32 *spi_clk, u32 *ref_clk);

extern void athrs26_reg_init(void);
extern void athrs26_reg_init_lan(void);
extern int athrs26_mdc_check(void);

#ifdef CONFIG_F1E_PHY
extern void athr_reg_init(void);
#endif

//#define AG7240_DEBUG

static int ag7240_send(struct eth_device *dev, volatile void *packet, int length)
{
	int i;

	ag7240_mac_t *mac = (ag7240_mac_t *)dev->priv;

	ag7240_desc_t *f = mac->fifo_tx[mac->next_tx];

	f->pkt_size = length;
	f->res1 = 0;
	f->pkt_start_addr = virt_to_phys(packet);

	ag7240_tx_give_to_dma(f);
	flush_cache((u32)packet, length);
	ag7240_reg_wr(mac, AG7240_DMA_TX_DESC, virt_to_phys(f));
	ag7240_reg_wr(mac, AG7240_DMA_TX_CTRL, AG7240_TXE);

	for (i = 0; i < MAX_WAIT; i++) {
		udelay(10);
		if (!ag7240_tx_owned_by_dma(f)) {
			break;
		}
	}

	if (i == MAX_WAIT) {
		printf("Tx Timed out\n");
	}

	f->pkt_start_addr = 0;
	f->pkt_size = 0;

	if (++mac->next_tx >= NO_OF_TX_FIFOS) {
		mac->next_tx = 0;
	}

	return 0;
}

static int ag7240_recv(struct eth_device *dev)
{
	int length;
	ag7240_desc_t *f;
	ag7240_mac_t *mac;

	mac = (ag7240_mac_t *)dev->priv;

	for (;;) {
		f = mac->fifo_rx[mac->next_rx];
		if (ag7240_rx_owned_by_dma(f)) {
			break;
		}

		length = f->pkt_size;

		NetReceive(NetRxPackets[mac->next_rx], length - 4);
		flush_cache((u32)NetRxPackets[mac->next_rx], PKTSIZE_ALIGN);

		ag7240_rx_give_to_dma(f);

		if (++mac->next_rx >= NO_OF_RX_FIFOS) {
			mac->next_rx = 0;
		}
	}

	if (!(ag7240_reg_rd(mac, AG7240_DMA_RX_CTRL))) {
		ag7240_reg_wr(mac, AG7240_DMA_RX_DESC, virt_to_phys(f));
		ag7240_reg_wr(mac, AG7240_DMA_RX_CTRL, 1);
	}

	return 0;
}

/*
 * Called in ag7240_hw_start() function
 */
void ag7240_mii_setup(ag7240_mac_t *mac)
{
	u32 mgmt_cfg_val;
	u32 cpu_freq, ddr_freq, ahb_freq;
	u32 check_cnt;

#ifdef CFG_ATHRS27_PHY
	if (is_wasp()) {
		printf("WASP ----> S27 PHY \n");
		mgmt_cfg_val = 2;
		ar7240_reg_wr(0xb8050024, 0x271); // 25MHz ref clock
		//ar7240_reg_wr(0xb8050024, 0x570);	// 40MHz ref clock
		ag7240_reg_wr(ag7240_macs[1], AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ag7240_reg_wr(ag7240_macs[1], AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
		return;
	}
#endif

#ifdef CONFIG_AR7242_S16_PHY
	if (is_wasp()) {
		printf("WASP  ----> S16 PHY *\n");
		mgmt_cfg_val = 4;
		if(mac->mac_unit == 0)
		ar7240_reg_wr(AG7240_ETH_CFG, AG7240_ETH_CFG_RGMII_GE0);

		ar7240_reg_rmw_clear(AG7240_ETH_SWITCH_CLK_SPARE, (1 << 6));
		ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);

		return;
	}
#endif

#ifdef CONFIG_F1E_PHY
	if (is_wasp()) {
		printf("WASP  ----> F1 PHY *\n");
		mgmt_cfg_val = 6;
		if(mac->mac_unit == 0)
		ar7240_reg_wr(AG7240_ETH_CFG, AG7240_ETH_CFG_RGMII_GE0);

		ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
		ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);

		return;
	}
#endif

	if ((ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK) == AR7240_REV_1_2) {
		mgmt_cfg_val = 0x2;
		if (mac->mac_unit == 0) {
			ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
			ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
		}
	} else {
		qca_sys_clocks(&cpu_freq, &ddr_freq, &ahb_freq, NULL, NULL);

		switch (ahb_freq / 1000000) {
		case 150:
			mgmt_cfg_val = 0x7;
			break;
		case 175:
			mgmt_cfg_val = 0x5;
			break;
		case 200:
			mgmt_cfg_val = 0x4;
			break;
		case 210:
			mgmt_cfg_val = 0x9;
			break;
		case 220:
			mgmt_cfg_val = 0x9;
			break;
		default:
			mgmt_cfg_val = 0x7;
		}

		if ((is_ar7241() || is_ar7242())) {
			/* External MII mode */
			if (mac->mac_unit == 0 && is_ar7242()) {
				mgmt_cfg_val = 0x6;
				ar7240_reg_rmw_set(AG7240_ETH_CFG, AG7240_ETH_CFG_RGMII_GE0);
				ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
				ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
			}

			/* Virian */
			mgmt_cfg_val = 0x4;
			ag7240_reg_wr(ag7240_macs[1], AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
			ag7240_reg_wr(ag7240_macs[1], AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
			printf("Virian MDC CFG Value ==> %x\n", mgmt_cfg_val);
		} else if (is_ar933x()) {
			//GE0 receives Rx/Tx clock, and use S26 phy
			ar7240_reg_rmw_set(AG7240_ETH_CFG, AG7240_ETH_CFG_MII_GE0_SLAVE);
			mgmt_cfg_val = 0xF;
			if (mac->mac_unit == 1) {
				check_cnt = 0;
				while (check_cnt++ < 10) {
					ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
					ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
#ifdef CFG_ATHRS26_PHY
					if (athrs26_mdc_check() == 0) {
						break;
					}
#endif
				}
				if (check_cnt == 11) {
					printf("%s: MDC check failed\n", __func__);
				}
			}
		} else { /* Python 1.0 & 1.1 */
			if (mac->mac_unit == 0) {
				check_cnt = 0;

				while (check_cnt++ < 10) {
					ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val | (1 << 31));
					ag7240_reg_wr(mac, AG7240_MAC_MII_MGMT_CFG, mgmt_cfg_val);
#ifdef CFG_ATHRS26_PHY
					if (athrs26_mdc_check() == 0) {
						break;
					}
#endif
				}

				if (check_cnt == 11) {
					printf("%s: MDC check failed\n", __func__);
				}
			}
		}
	}
}

static void ag7240_hw_start(ag7240_mac_t *mac)
{
	if (mac->mac_unit) {
		ag7240_reg_wr(mac, AG7240_MAC_CFG1, (AG7240_MAC_CFG1_RX_EN | AG7240_MAC_CFG1_TX_EN));
		ag7240_reg_rmw_set(mac, AG7240_MAC_CFG2, (AG7240_MAC_CFG2_PAD_CRC_EN | AG7240_MAC_CFG2_LEN_CHECK | AG7240_MAC_CFG2_IF_1000));
	} else {
		ag7240_reg_wr(mac, AG7240_MAC_CFG1, (AG7240_MAC_CFG1_RX_EN | AG7240_MAC_CFG1_TX_EN));
		ag7240_reg_rmw_set(mac, AG7240_MAC_CFG2, (AG7240_MAC_CFG2_PAD_CRC_EN | AG7240_MAC_CFG2_LEN_CHECK | AG7240_MAC_CFG2_IF_10_100));
	}

	ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_0, 0x1f00);
	ag7240_mii_setup(mac);

	ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_1, 0x10ffff);
	ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_2, 0xAAA0555);

	ag7240_reg_rmw_set(mac, AG7240_MAC_FIFO_CFG_4, 0x3ffff);

	// TODO: check this register
	/*
	 * When enable the web failsafe mode in uboot,you can't drop the broadcast
	 * frames now,the PC first will tx a ARP request packet, it's a broadcast packet.
	 */
	ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_5, 0x66b82);
	/*
	 * Setting Drop CRC Errors, Pause Frames, Length Error frames
	 * and Multi/Broad cast frames.
	 */
	//ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_5, 0x7eccf);

	ag7240_reg_wr(mac, AG7240_MAC_FIFO_CFG_3, 0x1f00140);
	//printf("cfg1:\t%#x\ncfg2:\t%#x\n", ag7240_reg_rd(mac, AG7240_MAC_CFG1), ag7240_reg_rd(mac, AG7240_MAC_CFG2));
}

static int ag7240_check_link(ag7240_mac_t *mac)
{
	int link = 0, duplex = 0, speed = 0;
	char *s;

	s = getenv("stdin");

	ag7240_phy_link(mac->mac_unit, &link);
	ag7240_phy_duplex(mac->mac_unit, &duplex);
	ag7240_phy_speed(mac->mac_unit, &speed);

	mac->link = link;

	if (!mac->link) {
		if ((s != NULL) && (strcmp(s, "nc") != 0)){
			printf("Link down: %s\n", mac->dev->name);
		}
		return 0;
	}

	switch (speed) {
	case _1000BASET:
		ag7240_set_mac_if(mac, 1);
		ag7240_reg_rmw_set(mac, AG7240_MAC_FIFO_CFG_5, (1 << 19));
		if (is_ar7242() && (mac->mac_unit == 0)) {
			ar7240_reg_wr(AR7242_ETH_XMII_CONFIG, 0x1c000000);
		}
#ifdef CONFIG_F1E_PHY
		if (is_wasp() && (mac->mac_unit == 0)) {
			ar7240_reg_wr(AR7242_ETH_XMII_CONFIG,0x0e000000);
		}
#else
		if (is_wasp() && (mac->mac_unit == 0)) {
			ar7240_reg_wr(AR7242_ETH_XMII_CONFIG, 0x06000000);
		}
#endif
		break;

	case _100BASET:
		ag7240_set_mac_if(mac, 0);
		ag7240_set_mac_speed(mac, 1);
		ag7240_reg_rmw_clear(mac, AG7240_MAC_FIFO_CFG_5, (1 << 19));

		if ((is_ar7242() || is_wasp()) && (mac->mac_unit == 0)) {
			ar7240_reg_wr(AR7242_ETH_XMII_CONFIG, 0x0101);
		}
		break;

	case _10BASET:
		ag7240_set_mac_if(mac, 0);
		ag7240_set_mac_speed(mac, 0);
		ag7240_reg_rmw_clear(mac, AG7240_MAC_FIFO_CFG_5, (1 << 19));
		if ((is_ar7242() || is_wasp()) && (mac->mac_unit == 0)){
			ar7240_reg_wr(AR7242_ETH_XMII_CONFIG, 0x1616);
		}
		break;

	default:
		if((s != NULL) && (strcmp(s, "nc") != 0)){
			printf("## Error: invalid speed detected\n");
		}
		return 0;
	}

	if (mac->link && (duplex == mac->duplex) && (speed == mac->speed)) {
		return 1;
	}

	mac->duplex = duplex;
	mac->speed = speed;

	if((s != NULL) && (strcmp(s, "nc") != 0)){
		printf("Ethernet mode (duplex/speed): %d/%d Mbps\n", duplex, speed);
	}

	ag7240_set_mac_duplex(mac, duplex);

	return 1;
}

/*
 * For every command we re-setup the ring and start with clean h/w rx state
 */
static int ag7240_clean_rx(struct eth_device *dev, bd_t * bd)
{
	int i;
	ag7240_desc_t *fr;
	ag7240_mac_t *mac = (ag7240_mac_t*)dev->priv;

	if (!ag7240_check_link(mac)) {
		return 0;
	}

	mac->next_rx = 0;

	for (i = 0; i < NO_OF_RX_FIFOS; i++) {
		fr = mac->fifo_rx[i];
		fr->pkt_start_addr = virt_to_phys(NetRxPackets[i]);
		flush_cache((u32)NetRxPackets[i], PKTSIZE_ALIGN);
		ag7240_rx_give_to_dma(fr);
	}

	ag7240_reg_wr(mac, AG7240_DMA_RX_DESC, virt_to_phys(mac->fifo_rx[0]));
	ag7240_reg_wr(mac, AG7240_DMA_RX_CTRL, AG7240_RXE);
	/* rx start */

	if (!is_ar933x()){
		// TODO: do we need this?
		udelay(1000 * 1000);
	}

	return 1;
}

static int ag7240_alloc_fifo(int ndesc, ag7240_desc_t ** fifo)
{
	int i;
	u32 size;
	uchar *p = NULL;

	size = sizeof(ag7240_desc_t) * ndesc;
	size += CFG_CACHELINE_SIZE - 1;

	if ((p = malloc(size)) == NULL) {
		printf("Cant allocate fifos\n");
		return -1;
	}

	p = (uchar *)(((u32)p + CFG_CACHELINE_SIZE - 1) & ~(CFG_CACHELINE_SIZE - 1));
	p = UNCACHED_SDRAM(p);

	for (i = 0; i < ndesc; i++) {
		fifo[i] = (ag7240_desc_t *)p + i;
	}

	return 0;
}

static int ag7240_setup_fifos(ag7240_mac_t *mac)
{
	int i;

	if (ag7240_alloc_fifo(NO_OF_TX_FIFOS, mac->fifo_tx)) {
		return 1;
	}

	for (i = 0; i < NO_OF_TX_FIFOS; i++) {
		mac->fifo_tx[i]->next_desc = (i == NO_OF_TX_FIFOS - 1) ? virt_to_phys(mac->fifo_tx[0]) : virt_to_phys(mac->fifo_tx[i + 1]);
		ag7240_tx_own(mac->fifo_tx[i]);
	}

	if (ag7240_alloc_fifo(NO_OF_RX_FIFOS, mac->fifo_rx)) {
		return 1;
	}

	for (i = 0; i < NO_OF_RX_FIFOS; i++) {
		mac->fifo_rx[i]->next_desc = (i == NO_OF_RX_FIFOS - 1) ? virt_to_phys(mac->fifo_rx[0]) : virt_to_phys(mac->fifo_rx[i + 1]);
	}

	return 1;
}

static void ag7240_halt(struct eth_device *dev)
{
	ag7240_mac_t *mac = (ag7240_mac_t *)dev->priv;
	ag7240_reg_wr(mac, AG7240_DMA_RX_CTRL, 0);
	while (ag7240_reg_rd(mac, AG7240_DMA_RX_CTRL))
		;
}

/*
 * Get MAC address stored in flash
 */
static void ag7240_get_ethaddr(struct eth_device *dev)
{
	unsigned char *mac = dev->enetaddr;
	bd_t *bd = gd->bd;

	memcpy(mac, (void *)bd->bi_enetaddr, 6);
}

int ag7240_enet_initialize(bd_t * bis)
{
	struct eth_device *dev[CFG_AG7240_NMACS];
	u32 mask, mac_h, mac_l;
	int i;

#ifdef AG7240_DEBUG
	printf("ag7240_enet_initialize...\n");
#endif

	// TODO check this register!
	ar7240_reg_wr(HORNET_BOOTSTRAP_STATUS, ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) & ~HORNET_BOOTSTRAP_MDIO_SLAVE_MASK);

	if (is_ar933x()) {
		u32 rd = 0x0;

		/* 
		 * To get s26 out of reset, we have to...
		 * bit0~bit3: has to be deasserted
		 * bit4:      has to be asserted
		 */
		rd = ar7240_reg_rd(AR7240_S26_CLK_CTRL_OFFSET) & ~(0x1f);
		rd |= 0x10;
		ar7240_reg_wr(AR7240_S26_CLK_CTRL_OFFSET, rd);

		if (ar7240_reg_rd(AR7240_RESET) != 0) {
			ar7240_reg_wr(AR7240_RESET, 0);
		}
	}

	for (i = 0; i < CFG_AG7240_NMACS; i++) {

		if ((dev[i] = (struct eth_device *) malloc(sizeof(struct eth_device))) == NULL) {
			puts("## Error: malloc failed\n");
			return 0;
		}

		if ((ag7240_macs[i] = (ag7240_mac_t *) malloc(sizeof(ag7240_mac_t))) == NULL) {
			puts("## Error: malloc failed\n");
			return 0;
		}

		memset(ag7240_macs[i], 0, sizeof(*ag7240_macs[i]));
		memset(dev[i], 0, sizeof(*dev[i]));

		sprintf(dev[i]->name, "eth%d", i);
		ag7240_get_ethaddr(dev[i]);

		ag7240_macs[i]->mac_unit = i;
		ag7240_macs[i]->mac_base = i ? AR7240_GE1_BASE : AR7240_GE0_BASE;
		ag7240_macs[i]->dev = dev[i];

		dev[i]->iobase = 0;
		dev[i]->init = ag7240_clean_rx;
		dev[i]->halt = ag7240_halt;
		dev[i]->send = ag7240_send;
		dev[i]->recv = ag7240_recv;
		dev[i]->priv = (void *)ag7240_macs[i];
	}

	for (i = 0; i < CFG_AG7240_NMACS; i++) {

		eth_register(dev[i]);

#if(CONFIG_COMMANDS & CFG_CMD_MII)
		miiphy_register(dev[i]->name, ag7240_miiphy_read, ag7240_miiphy_write);
#endif

		ag7240_reg_rmw_set(ag7240_macs[i], AG7240_MAC_CFG1, AG7240_MAC_CFG1_SOFT_RST | AG7240_MAC_CFG1_RX_RST | AG7240_MAC_CFG1_TX_RST);

		if (!i) {
			mask = (AR7240_RESET_GE0_MAC | AR7240_RESET_GE0_PHY | AR7240_RESET_GE1_MAC | AR7240_RESET_GE1_PHY);

			if (is_ar7241() || is_ar7242() || is_wasp()) {
				mask = mask | AR7240_RESET_GE0_MDIO | AR7240_RESET_GE1_MDIO;
			}

			ar7240_reg_rmw_set(AR7240_RESET, mask);

			if (!is_ar933x()){
				udelay(1000 * 100);
			}

			ar7240_reg_rmw_clear(AR7240_RESET, mask);

			if (!is_ar933x()){
				udelay(1000 * 100);
			}

			if (!is_ar933x()){
				udelay(10 * 1000);
			}
		}

		ag7240_hw_start(ag7240_macs[i]);

		ag7240_setup_fifos(ag7240_macs[i]);

		if (!is_ar933x()){
			udelay(100 * 1000);
		}

#ifdef AG7240_DEBUG
		unsigned char *mac = dev[i]->enetaddr;
		printf("\nInterface %s MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", dev[i]->name, mac[0] & 0xff, mac[1] & 0xff, mac[2] & 0xff, mac[3] & 0xff, mac[4] & 0xff, mac[5] & 0xff);
#endif

		mac_l = (dev[i]->enetaddr[4] << 8) | (dev[i]->enetaddr[5]);
		mac_h = (dev[i]->enetaddr[0] << 24) | (dev[i]->enetaddr[1] << 16) | (dev[i]->enetaddr[2] << 8) | (dev[i]->enetaddr[3] << 0);

		ag7240_reg_wr(ag7240_macs[i], AG7240_GE_MAC_ADDR1, mac_l);
		ag7240_reg_wr(ag7240_macs[i], AG7240_GE_MAC_ADDR2, mac_h);

		/* if using header for register configuration, we have to     */
		/* configure s26 register after frame transmission is enabled */
		if (ag7240_macs[i]->mac_unit == 0) { /* WAN Phy */
#ifdef CONFIG_AR7242_S16_PHY
			if (is_ar7242() || is_wasp()) {
				athrs16_reg_init();
			} else
#endif
			{
#ifdef CFG_ATHRS26_PHY
	#ifdef AG7240_DEBUG
				printf("s26 reg init \n");
	#endif
				athrs26_reg_init();
#endif
#ifdef CFG_ATHRS27_PHY
	#ifdef AG7240_DEBUG
				printf("s27 reg init \n");
	#endif
				athrs27_reg_init();
#endif
#ifdef CONFIG_F1E_PHY
	#ifdef AG7240_DEBUG
				printf("F1Phy reg init \n");
	#endif
				athr_reg_init();
#endif
			}
		} else {
#ifdef CFG_ATHRS26_PHY
	#ifdef AG7240_DEBUG
			printf("athrs26_reg_init_lan\n");
	#endif
			athrs26_reg_init_lan();
#endif
#ifdef CFG_ATHRS27_PHY
	#ifdef AG7240_DEBUG
			printf("s27 reg init lan \n");
	#endif
			athrs27_reg_init_lan();
#endif
		}

#ifdef AG7240_DEBUG
		printf("ag7240_phy_setup\n");
#endif
		//udelay(100*1000);

		ag7240_phy_setup(ag7240_macs[i]->mac_unit);

#ifdef AG7240_DEBUG
		printf("Interface %s is up\n", dev[i]->name);
#endif
	}

	return 1;
}

/* Modified by lsz for reduceing CMD_MII, but ag7240 need this 090306 */
uint16_t ag7240_miiphy_read(char *devname, uint32_t phy_addr, uint8_t reg)
{
	ag7240_mac_t *mac = ag7240_name2mac(devname);
	uint16_t addr = (phy_addr << AG7240_ADDR_SHIFT) | reg, val;
	volatile int rddata;
	uint16_t ii = 0xFFFF;

	/*
	 * Check for previous transactions are complete. Added to avoid
	 * race condition while running at higher frequencies.
	 */
	do {
		udelay(5);
		rddata = ag7240_reg_rd(mac, AG7240_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("ERROR:%s:%d transaction failed\n", __func__, __LINE__);

	ag7240_reg_wr(mac, AG7240_MII_MGMT_CMD, 0x0);
	ag7240_reg_wr(mac, AG7240_MII_MGMT_ADDRESS, addr);
	ag7240_reg_wr(mac, AG7240_MII_MGMT_CMD, AG7240_MGMT_CMD_READ);

	do {
		udelay(5);
		rddata = ag7240_reg_rd(mac, AG7240_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("ERROR! Leave ag7240_miiphy_read without polling correct status!\n");

	val = ag7240_reg_rd(mac, AG7240_MII_MGMT_STATUS);
	ag7240_reg_wr(mac, AG7240_MII_MGMT_CMD, 0x0);

	return val;
}

void ag7240_miiphy_write(char *devname, uint32_t phy_addr, uint8_t reg, uint16_t data)
{
	ag7240_mac_t *mac = ag7240_name2mac(devname);
	uint16_t addr = (phy_addr << AG7240_ADDR_SHIFT) | reg;
	volatile int rddata;
	uint16_t ii = 0xFFFF;

	/*
	 * Check for previous transactions are complete. Added to avoid
	 * race condition while running at higher frequencies.
	 */
	do {
		udelay(5);
		rddata = ag7240_reg_rd(mac, AG7240_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("ERROR:%s:%d transaction failed\n", __func__, __LINE__);

	ag7240_reg_wr(mac, AG7240_MII_MGMT_ADDRESS, addr);
	ag7240_reg_wr(mac, AG7240_MII_MGMT_CTRL, data);

	do {
		rddata = ag7240_reg_rd(mac, AG7240_MII_MGMT_IND) & 0x1;
	} while (rddata && --ii);

	if (ii == 0)
		printf("ERROR! Leave ag7240_miiphy_write without polling correct status!\n");
}
