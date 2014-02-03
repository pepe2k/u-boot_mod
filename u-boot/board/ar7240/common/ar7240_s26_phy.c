/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright © 2007 Atheros Communications, Inc.,  All Rights Reserved.
 */

/*
 * Manage the atheros ethernet PHY.
 *
 * All definitions in this file are operating system independent!
 */

#include <config.h>
#include <linux/types.h>
#include <common.h>
#include <miiphy.h>
#include "phy.h"
#include <asm/addrspace.h>
#include "ar7240_soc.h"
#include "ar7240_s26_phy.h"

/* PHY selections and access functions */
#define DRV_PRINT(DBG_SW,X)

#define ATHR_LAN_PORT_VLAN	1
#define ATHR_WAN_PORT_VLAN	2
#define ENET_UNIT_LAN		1
#define ENET_UNIT_WAN		0

#define ATHR_PHY0_ADDR		0x0
#define ATHR_PHY1_ADDR		0x1
#define ATHR_PHY2_ADDR		0x2
#define ATHR_PHY3_ADDR		0x3
#define ATHR_PHY4_ADDR		0x4

#define TRUE	1
#define FALSE	0

/*
 * Track per-PHY port information.
 */
typedef struct {
	int isEnetPort;			/* normal enet port */
	int isPhyAlive;			/* last known state of link */
	int ethUnit;				/* MAC associated with this phy port */
	uint32_t phyBase;
	uint32_t phyAddr;			/* PHY registers associated with this phy port */
	uint32_t VLANTableSetting;	/* Value to be written to VLAN table */
} athrPhyInfo_t;

/*
 * Per-PHY information, indexed by PHY unit number.
 */
static athrPhyInfo_t athrPhyInfo[] = {
	/* port 1 -- LAN port 1 */
	{ TRUE, FALSE, ENET_UNIT_LAN, 0, ATHR_PHY0_ADDR, ATHR_LAN_PORT_VLAN },

	/* port 2 -- LAN port 2 */
	{ TRUE, FALSE, ENET_UNIT_LAN, 0, ATHR_PHY1_ADDR, ATHR_LAN_PORT_VLAN },

	/* port 3 -- LAN port 3 */
	{ TRUE, FALSE, ENET_UNIT_LAN, 0, ATHR_PHY2_ADDR, ATHR_LAN_PORT_VLAN },

	/* port 4 --  LAN port 4 */
	{ TRUE, FALSE, ENET_UNIT_LAN, 0, ATHR_PHY3_ADDR, ATHR_LAN_PORT_VLAN	},

	/* port 5 -- WAN Port 5 */
	{ TRUE, FALSE, ENET_UNIT_WAN, 0, ATHR_PHY4_ADDR, ATHR_LAN_PORT_VLAN },

	/* port 0 -- cpu port 0 */
	{ FALSE, TRUE, ENET_UNIT_LAN, 0, 0x00, ATHR_LAN_PORT_VLAN },
};

static uint8_t athr26_init_flag = 0;
static uint8_t athr26_init_flag1 = 0;

/* Range of valid PHY IDs is [MIN..MAX] */
#define ATHR_PHY_MAX	5
#define ATHR_ID_MIN		0
#define ATHR_ID_MAX		(ATHR_PHY_MAX-1)

/* Convenience macros to access myPhyInfo */
#define ATHR_IS_ENET_PORT(phyUnit)			(athrPhyInfo[phyUnit].isEnetPort)
#define ATHR_IS_PHY_ALIVE(phyUnit)			(athrPhyInfo[phyUnit].isPhyAlive)
#define ATHR_ETHUNIT(phyUnit)				(athrPhyInfo[phyUnit].ethUnit)
#define ATHR_PHYBASE(phyUnit)				(athrPhyInfo[phyUnit].phyBase)
#define ATHR_PHYADDR(phyUnit)				(athrPhyInfo[phyUnit].phyAddr)
#define ATHR_VLAN_TABLE_SETTING(phyUnit)	(athrPhyInfo[phyUnit].VLANTableSetting)
#define ATHR_IS_ETHUNIT(phyUnit, ethUnit)	(ATHR_IS_ENET_PORT(phyUnit) && ATHR_ETHUNIT(phyUnit) == (ethUnit))
#define ATHR_IS_WAN_PORT(phyUnit)			(!(ATHR_ETHUNIT(phyUnit) == ENET_UNIT_LAN))

/* Forward references */
int athrs26_phy_is_link_alive(int phyUnit);
uint32_t athrs26_reg_read(uint32_t reg_addr);
unsigned int s26_rd_phy(unsigned int phy_addr, unsigned int reg_addr);
void athrs26_reg_write(uint32_t reg_addr, uint32_t reg_val);
void s26_wr_phy(unsigned int phy_addr, unsigned int reg_addr, unsigned int write_data);

void athrs26_powersave_off(int phy_addr){
	s26_wr_phy(phy_addr, ATHR_DEBUG_PORT_ADDRESS, 0x29);
	s26_wr_phy(phy_addr, ATHR_DEBUG_PORT_DATA, 0x36c0);
}

void athrs26_sleep_off(int phy_addr){
	s26_wr_phy(phy_addr, ATHR_DEBUG_PORT_ADDRESS, 0xb);
	s26_wr_phy(phy_addr, ATHR_DEBUG_PORT_DATA, 0x3c00);
}

void athrs26_reg_init(void){
	uint32_t ar7240_revid;
#if S26_PHY_DEBUG
	uint32_t rd_val;
#endif

	/* if using header for register configuration, we have to     */
	/* configure s26 register after frame transmission is enabled */
	if(athr26_init_flag){
		return;
	}

	ar7240_revid = ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK;

	if(ar7240_revid == AR7240_REV_1_0){
#ifdef S26_FORCE_100M
		s26_wr_phy(ATHR_PHY4_ADDR, ATHR_PHY_FUNC_CONTROL, 0x800);
		s26_wr_phy(ATHR_PHY4_ADDR, ATHR_PHY_CONTROL, 0xa100);
#endif
#ifdef S26_FORCE_10M
		athrs26_powersave_off(ATHR_PHY4_ADDR);
		athrs26_sleep_off(ATHR_PHY4_ADDR);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_PHY_FUNC_CONTROL,0x800);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_PHY_CONTROL,0x8100);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_DEBUG_PORT_ADDRESS,0x0);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_DEBUG_PORT_DATA,0x12ee);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_DEBUG_PORT_ADDRESS,0x3);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_DEBUG_PORT_DATA,0x3bf0);
		s26_wr_phy(ATHR_PHY4_ADDR,ATHR_PHY_CONTROL,0x8100);
#endif
	} else {
		s26_wr_phy(ATHR_PHY4_ADDR, ATHR_PHY_CONTROL, 0x9000);
	}

#if S26_PHY_DEBUG
	rd_val = s26_rd_phy(ATHR_PHY4_ADDR,ATHR_PHY_FUNC_CONTROL);
	printf("S26 PHY FUNC CTRL  (%d) :%x\n",ATHR_PHY4_ADDR, rd_val);

	rd_val = s26_rd_phy(ATHR_PHY4_ADDR,ATHR_PHY_CONTROL);
	printf("S26 PHY CTRL  (%d) :%x\n",ATHR_PHY4_ADDR, rd_val);
#endif

	athr26_init_flag = 1;
}

void athrs26_reg_init_lan(void){
	int i = 60;
	int phyUnit;
	//uint32_t phyBase = 0;
	uint32_t phyAddr = 0;
	uint32_t ar7240_revid;
#if S26_PHY_DEBUG
	uint32_t rd_val;
#endif

	/* if using header for register configuration, we have to     */
	/* configure s26 register after frame transmission is enabled */
	if(athr26_init_flag1){
		return;
	}

	/* reset switch */
	athrs26_reg_write(0x0, athrs26_reg_read(0x0) | 0x80000000);

	while(i--){
		if(!is_ar933x()){
			sysMsDelay(100);
		}

		if(!(athrs26_reg_read(0x0) & 0x80000000)){
			break;
		}
	}

	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX - 1; phyUnit++){
		//phyBase = ATHR_PHYBASE(phyUnit);
		phyAddr = ATHR_PHYADDR(phyUnit);

		ar7240_revid = ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK;
		if(ar7240_revid == AR7240_REV_1_0){
#ifdef S26_FORCE_100M 
			/*
			 *  Force MDI and MDX to alternate ports
			 *  Phy 0 and 2 -- MDI
			 *  Phy 1 and 3 -- MDX
			 */
			if(phyUnit % 2){
				s26_wr_phy(phyAddr, ATHR_PHY_FUNC_CONTROL, 0x820);
			} else {
				s26_wr_phy(phyAddr, ATHR_PHY_FUNC_CONTROL, 0x800);
			}

			s26_wr_phy(phyAddr, ATHR_PHY_CONTROL, 0xa100);
#endif

#ifdef S26_FORCE_10M
			/*
			 *  Force MDI and MDX to alternate ports
			 *  Phy 0 and 2 -- MDI
			 *  Phy 1 and 3 -- MDX
			 */
			if(phyUnit%2){
				s26_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x820);
			} else {
				s26_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x800);
			}

			athrs26_powersave_off(phyAddr);
			athrs26_sleep_off(phyAddr);

			s26_wr_phy(phyAddr,ATHR_PHY_CONTROL,0x8100);
			s26_wr_phy(phyAddr,ATHR_DEBUG_PORT_ADDRESS,0x0);
			s26_wr_phy(phyAddr,ATHR_DEBUG_PORT_DATA,0x12ee);
			s26_wr_phy(phyAddr,ATHR_DEBUG_PORT_ADDRESS,0x3);
			s26_wr_phy(phyAddr,ATHR_DEBUG_PORT_DATA,0x3bf0);
			s26_wr_phy(phyAddr,ATHR_PHY_CONTROL,0x8100);
#endif
		} else {
			s26_wr_phy(phyAddr, ATHR_PHY_CONTROL, 0x9000);
		}

#if S26_PHY_DEBUG
		rd_val = s26_rd_phy(phyAddr,ATHR_PHY_ID1);
		printf("S26 PHY ID  (%d) :%x\n",phyAddr,rd_val);

		rd_val = s26_rd_phy(phyAddr,ATHR_PHY_CONTROL);
		printf("S26 PHY CTRL  (%d) :%x\n",phyAddr,rd_val);

		rd_val = s26_rd_phy(phyAddr,ATHR_PHY_STATUS);
		printf("S26 ATHR PHY STATUS  (%d) :%x\n",phyAddr,rd_val);
#endif
	}

	/*
	 * CPU port Enable
	 */
	athrs26_reg_write(CPU_PORT_REGISTER, (1 << 8));

	/*
	 * status[1:0]=2'h2;   - (0x10 - 1000 Mbps , 0x0 - 10 Mbps)
	 * status[2]=1'h1;     - Tx Mac En
	 * status[3]=1'h1;     - Rx Mac En
	 * status[4]=1'h1;     - Tx Flow Ctrl En
	 * status[5]=1'h1;     - Rx Flow Ctrl En
	 * status[6]=1'h1;     - Duplex Mode
	 */
	athrs26_reg_write(PORT_STATUS_REGISTER1, 0x200); /* LAN - 1 */
	athrs26_reg_write(PORT_STATUS_REGISTER2, 0x200); /* LAN - 2 */
	athrs26_reg_write(PORT_STATUS_REGISTER3, 0x200); /* LAN - 3 */
	athrs26_reg_write(PORT_STATUS_REGISTER4, 0x200); /* LAN - 4 */

	/* QM Control */
	athrs26_reg_write(0x38, 0xc000050e);

	/*
	 * status[11]=1'h0;    - CPU Disable
	 * status[7] = 1'b1;   - Learn One Lock
	 * status[14] = 1'b0;  - Learn Enable
	 */
	/* Atheros Header Disable */
	athrs26_reg_write(PORT_CONTROL_REGISTER0, 0x4004);

	/* Tag Priority Mapping */
	athrs26_reg_write(0x70, 0xfa50);

	/* Enable ARP packets to CPU port */
	athrs26_reg_write(S26_ARL_TBL_CTRL_REG, (athrs26_reg_read(S26_ARL_TBL_CTRL_REG) | 0x100000));

	/* Enable Broadcast packets to CPU port */
	athrs26_reg_write(S26_FLD_MASK_REG, (athrs26_reg_read(S26_FLD_MASK_REG) | S26_ENABLE_CPU_BROADCAST));

#if S26_PHY_DEBUG
	rd_val = athrs26_reg_read ( CPU_PORT_REGISTER );
	printf("S26 CPU_PORT_REGISTER :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_STATUS_REGISTER0 );
	printf("S26 PORT_STATUS_REGISTER0  :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_STATUS_REGISTER1 );
	printf("S26 PORT_STATUS_REGISTER1  :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_STATUS_REGISTER2 );
	printf("S26 PORT_STATUS_REGISTER2  :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_STATUS_REGISTER3 );
	printf("S26 PORT_STATUS_REGISTER3  :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_STATUS_REGISTER4 );
	printf("S26 PORT_STATUS_REGISTER4  :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_CONTROL_REGISTER0 );
	printf("S26 PORT_CONTROL_REGISTER0 :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_CONTROL_REGISTER1 );
	printf("S26 PORT_CONTROL_REGISTER1 :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_CONTROL_REGISTER2 );
	printf("S26 PORT_CONTROL_REGISTER2 :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_CONTROL_REGISTER3 );
	printf("S26 PORT_CONTROL_REGISTER3 :%x\n",rd_val);

	rd_val = athrs26_reg_read ( PORT_CONTROL_REGISTER4 );
	printf("S26 PORT_CONTROL_REGISTER4 :%x\n",rd_val);
#endif

	athr26_init_flag1 = 1;
}

/******************************************************************************
 *
 * athrs26_phy_is_link_alive - test to see if the specified link is alive
 *
 * RETURNS:
 *    TRUE  --> link is alive
 *    FALSE --> link is down
 */
int athrs26_phy_is_link_alive(int phyUnit){
	uint16_t phyHwStatus;
	//uint32_t phyBase;
	uint32_t phyAddr;

	//phyBase = ATHR_PHYBASE(phyUnit);
	phyAddr = ATHR_PHYADDR(phyUnit);

	phyHwStatus = s26_rd_phy(phyAddr, ATHR_PHY_SPEC_STATUS);

	if(phyHwStatus & ATHR_STATUS_LINK_PASS){
		return(TRUE);
	}

	return(FALSE);
}

/******************************************************************************
 *
 * athrs26_phy_setup - reset and setup the PHY associated with
 * the specified MAC unit number.
 *
 * Resets the associated PHY port.
 *
 * RETURNS:
 *    TRUE  --> associated PHY is alive
 *    FALSE --> no LINKs on this ethernet unit
 */
int athrs26_phy_setup(int ethUnit){
	int phyUnit;
	int liveLinks = 0;
	uint16_t phyHwStatus;
	uint16_t timeout;
	//uint32_t phyBase = 0;
	uint32_t phyAddr = 0;
	uint32_t ar7240_revid;
	int foundPhy = FALSE;
#if S26_PHY_DEBUG
	uint32_t rd_val = 0;
#endif

	/* See if there's any configuration data for this enet */
	/* start auto negogiation on each phy */
	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		foundPhy = TRUE;
		//phyBase = ATHR_PHYBASE(phyUnit);
		phyAddr = ATHR_PHYADDR(phyUnit);

		s26_wr_phy(phyAddr, ATHR_AUTONEG_ADVERT, ATHR_ADVERTISE_ALL);

#if S26_PHY_DEBUG
		rd_val = s26_rd_phy(phyAddr,ATHR_AUTONEG_ADVERT );
		printf("%s ATHR_AUTONEG_ADVERT %d :%x\n",__func__,phyAddr, rd_val);
#endif

		ar7240_revid = ar7240_reg_rd(AR7240_REV_ID) & AR7240_REV_ID_MASK;

		if(ar7240_revid != AR7240_REV_1_0){
			s26_wr_phy(phyAddr, ATHR_PHY_CONTROL, ATHR_CTRL_AUTONEGOTIATION_ENABLE | ATHR_CTRL_SOFTWARE_RESET);
		}

#if S26_PHY_DEBUG
		rd_val = s26_rd_phy(phyAddr,ATHR_AUTONEG_ADVERT );
		rd_val = s26_rd_phy(phyAddr,ATHR_PHY_CONTROL);
		printf("%s ATHR_PHY_CONTROL %d :%x\n",__func__,phyAddr, rd_val);
#endif
	}

	if(!foundPhy){
		/* No PHY's configured for this ethUnit */
		return(FALSE);
	}

	/*
	 * After the phy is reset, it takes a little while before
	 * it can respond properly.
	 */
	if(!is_ar933x()){
		if(ethUnit == ENET_UNIT_LAN){
			sysMsDelay(1000);
		} else {
			sysMsDelay(3000);
		}
	}

	/*
	 * Wait up to 3 seconds for ALL associated PHYs to finish
	 * autonegotiation.  The only way we get out of here sooner is
	 * if ALL PHYs are connected AND finish autonegotiation.
	 */
	for(phyUnit = 0; (phyUnit < ATHR_PHY_MAX); phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		timeout = 20;

		for(;;){
			phyHwStatus = s26_rd_phy(phyAddr, ATHR_PHY_CONTROL);

			if(ATHR_RESET_DONE(phyHwStatus)){
				DRV_PRINT(DRV_DEBUG_PHYSETUP, ("Port %d, Neg Success\n", phyUnit));
				break;
			}

			if(timeout == 0){
				DRV_PRINT(DRV_DEBUG_PHYSETUP, ("Port %d, Negogiation timeout\n", phyUnit));
				break;
			}

			if(--timeout == 0){
				DRV_PRINT(DRV_DEBUG_PHYSETUP, ("Port %d, Negogiation timeout\n", phyUnit));
				break;
			}

			if(!is_ar933x()){
				sysMsDelay(150);
			}
		}

		/* fix IOT */
		s26_wr_phy(phyUnit, 29, 0x14);
		s26_wr_phy(phyUnit, 30, 0x1352);

#ifdef S26_VER_1_0
		//turn off power saving
		s26_wr_phy(phyUnit, 29, 41);
		s26_wr_phy(phyUnit, 30, 0);
		printf("def_ S26_VER_1_0\n");
#endif
	}

	/*
	 * All PHYs have had adequate time to autonegotiate.
	 * Now initialize software status.
	 *
	 * It's possible that some ports may take a bit longer
	 * to autonegotiate; but we can't wait forever.  They'll
	 * get noticed by mv_phyCheckStatusChange during regular
	 * polling activities.
	 */
	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs26_phy_is_link_alive(phyUnit)){
			liveLinks++;
			ATHR_IS_PHY_ALIVE(phyUnit) = TRUE;
		} else {
			ATHR_IS_PHY_ALIVE(phyUnit) = FALSE;
		}

		DRV_PRINT(DRV_DEBUG_PHYSETUP, ("eth%d: Phy Specific Status=%4.4x\n", ethUnit, s26_rd_phy(ATHR_PHYADDR(phyUnit),ATHR_PHY_SPEC_STATUS)));
	}

	return(liveLinks > 0);
}

/******************************************************************************
 *
 * athrs26_phy_is_fdx - Determines whether the phy ports associated with the
 * specified device are FULL or HALF duplex.
 *
 * RETURNS:
 *    1 --> FULL
 *    0 --> HALF
 */
int athrs26_phy_is_fdx(int ethUnit){
	int phyUnit;
	//uint32_t phyBase;
	//uint32_t phyAddr;
	uint16_t phyHwStatus;
	int ii = 200;

	if(ethUnit == ENET_UNIT_LAN){
		return(TRUE);
	}

	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs26_phy_is_link_alive(phyUnit)){

			//phyBase = ATHR_PHYBASE(phyUnit);
			//phyAddr = ATHR_PHYADDR(phyUnit);

			do {
				phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS);
				sysMsDelay(10);
			} while((!(phyHwStatus & ATHR_STATUS_RESOVLED)) && --ii);

			if(phyHwStatus & ATHER_STATUS_FULL_DEPLEX){
				return(TRUE);
			}
		}
	}

	return(FALSE);
}

/******************************************************************************
 *
 * athrs26_phy_speed - Determines the speed of phy ports associated with the
 * specified device.
 *
 * RETURNS:
 *               _10BASET, _100BASET;
 *               _1000BASET;
 */

int athrs26_phy_speed(int ethUnit){
	int phyUnit;
	uint16_t phyHwStatus;
	//uint32_t phyBase;
	uint32_t phyAddr;
	int ii = 200;

	if(ethUnit == ENET_UNIT_LAN){
		return(_1000BASET);
	}

	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs26_phy_is_link_alive(phyUnit)){

			//phyBase = ATHR_PHYBASE(phyUnit);
			phyAddr = ATHR_PHYADDR(phyUnit);
			do {
				phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS);
				sysMsDelay(10);
			} while((!(phyHwStatus & ATHR_STATUS_RESOVLED)) && --ii);

			phyHwStatus = ((phyHwStatus & ATHER_STATUS_LINK_MASK) >> ATHER_STATUS_LINK_SHIFT);

			switch(phyHwStatus){
				case 0:
					return(_10BASET);
				case 1:
#ifdef CONFIG_MACH_HORNET
					/* For IEEE 100M voltage test */
					s26_wr_phy(phyAddr, ATHR_DEBUG_PORT_ADDRESS, 0x4);
					s26_wr_phy(phyAddr, ATHR_DEBUG_PORT_DATA, 0xebbb);
					s26_wr_phy(phyAddr, ATHR_DEBUG_PORT_ADDRESS, 0x5);
					s26_wr_phy(phyAddr, ATHR_DEBUG_PORT_DATA, 0x2c47);
#endif /* CONFIG_MACH_HORNET */
					return(_100BASET);
				case 2:
					return(_1000BASET);
				default:
					printf("## Error: unknown eth speed!\n");
			}
		}
	}

	return(_10BASET);
}

/*****************************************************************************
 *
 * athr_phy_is_up -- checks for significant changes in PHY state.
 *
 * A "significant change" is:
 *     dropped link (e.g. ethernet cable unplugged) OR
 *     autonegotiation completed + link (e.g. ethernet cable plugged in)
 *
 * When a PHY is plugged in, phyLinkGained is called.
 * When a PHY is unplugged, phyLinkLost is called.
 */

int athrs26_phy_is_up(int ethUnit){
	int phyUnit;
	int linkCount = 0;
	int lostLinks = 0;
	int gainedLinks = 0;
	uint16_t phyHwStatus, phyHwControl;
	athrPhyInfo_t *lastStatus;
	//uint32_t phyBase;
	//uint32_t phyAddr;

	for(phyUnit = 0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		//phyBase = ATHR_PHYBASE(phyUnit);
		//phyAddr = ATHR_PHYADDR(phyUnit);

		lastStatus = &athrPhyInfo[phyUnit];

		if(lastStatus->isPhyAlive){ /* last known link status was ALIVE */

			phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS);

			/* See if we've lost link */
			if(phyHwStatus & ATHR_STATUS_LINK_PASS){ /* check realtime link */
				linkCount++;
			} else {
				phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_STATUS);
				/* If realtime failed check link in latch register before
				 * asserting link down.
				 */
				if(phyHwStatus & ATHR_LATCH_LINK_PASS){
					linkCount++;
				} else {
					lostLinks++;
				}

				DRV_PRINT(DRV_DEBUG_PHYCHANGE,("\nenet%d port%d down\n", ethUnit, phyUnit));
				lastStatus->isPhyAlive = FALSE;
			}
		} else { /* last known link status was DEAD */

			/* Check for reset complete */
			phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_STATUS);

			if(!ATHR_RESET_DONE(phyHwStatus)){
				continue;
			}

			phyHwControl = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_CONTROL);

			/* Check for AutoNegotiation complete */
			if((!(phyHwControl & ATHR_CTRL_AUTONEGOTIATION_ENABLE)) || ATHR_AUTONEG_DONE(phyHwStatus)){
				phyHwStatus = s26_rd_phy(ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS);

				if(phyHwStatus & ATHR_STATUS_LINK_PASS){
					gainedLinks++;
					linkCount++;
					DRV_PRINT(DRV_DEBUG_PHYCHANGE,("\nenet%d port%d up\n", ethUnit, phyUnit));
					lastStatus->isPhyAlive = TRUE;
				}
			}
		}
	}

	return(linkCount);

#if S26_PHY_DEBUG
	if(linkCount == 0){
		if(lostLinks){
			/* We just lost the last link for this MAC */
			phyLinkLost(ethUnit);
		}
	} else {
		if(gainedLinks == linkCount){
			/* We just gained our first link(s) for this MAC */
			phyLinkGained(ethUnit);
		}
	}
#endif
}

uint32_t athrs26_reg_read(unsigned int s26_addr){
	unsigned int addr_temp;
	unsigned int s26_rd_csr_low, s26_rd_csr_high, s26_rd_csr;
	unsigned int data, unit = 0;
	unsigned int phy_address, reg_address;

	addr_temp = (s26_addr & 0xfffffffc) >> 2;
	data = addr_temp >> 7;

	phy_address = 0x1f;
	reg_address = 0x10;

	if(is_ar7240()){
		unit = 0;
	} else if(is_ar7241() || is_ar7242() || is_ar933x()){
		unit = 1;
	}

	phy_reg_write(unit, phy_address, reg_address, data);

	phy_address = (0x17 & ((addr_temp >> 4) | 0x10));
	reg_address = ((addr_temp << 1) & 0x1e);
	s26_rd_csr_low = (uint32_t)phy_reg_read(unit, phy_address, reg_address);

	reg_address = reg_address | 0x1;
	s26_rd_csr_high = (uint32_t)phy_reg_read(unit, phy_address, reg_address);
	s26_rd_csr = (s26_rd_csr_high << 16) | s26_rd_csr_low;

	return(s26_rd_csr);
}

void athrs26_reg_write(unsigned int s26_addr, unsigned int s26_write_data){
	unsigned int addr_temp;
	unsigned int data, unit = 0;
	unsigned int phy_address, reg_address;

	addr_temp = (s26_addr & 0xfffffffc) >> 2;
	data = addr_temp >> 7;

	phy_address = 0x1f;
	reg_address = 0x10;

	if(is_ar7240()){
		unit = 0;
	} else if(is_ar7241() || is_ar7242() || is_ar933x()){
		unit = 1;
	}

#ifdef CONFIG_MACH_HORNET
	//The write sequence , 0x98: L->H, 0x40 H->L, 0x50 H->L , others should not care.
	if(s26_addr!=0x98){
		//printf("[%s:%d] unit=%d\n",__FUNCTION__,__LINE__,unit);
		phy_reg_write(unit, phy_address, reg_address, data);

		phy_address = 0x17 & ((addr_temp >> 4) | 0x10);
		reg_address = ((addr_temp << 1) & 0x1e) | 0x1;
		data = s26_write_data >> 16;
		phy_reg_write(unit, phy_address, reg_address, data);

		reg_address = reg_address & 0x1e;
		data = s26_write_data & 0xffff;
		phy_reg_write(unit, phy_address, reg_address, data);
	} else {
		phy_reg_write(unit, phy_address, reg_address, data);

		phy_address = (0x17 & ((addr_temp >> 4) | 0x10));
		reg_address = ((addr_temp << 1) & 0x1e);

		data = s26_write_data & 0xffff;
		phy_reg_write(unit, phy_address, reg_address, data);

		reg_address = (((addr_temp << 1) & 0x1e) | 0x1);
		data = s26_write_data >> 16;
		phy_reg_write(unit, phy_address, reg_address, data);
	}
#else
	phy_reg_write(unit, phy_address, reg_address, data);

	phy_address = (0x17 & ((addr_temp >> 4) | 0x10));
	reg_address = ((addr_temp << 1) & 0x1e);
	data = s26_write_data & 0xffff;
	phy_reg_write(unit, phy_address, reg_address, data);

	reg_address = (((addr_temp << 1) & 0x1e) | 0x1);
	data = s26_write_data >> 16;
	phy_reg_write(unit, phy_address, reg_address, data);
#endif
}

unsigned int s26_rd_phy(unsigned int phy_addr, unsigned int reg_addr){
	unsigned int rddata;
	unsigned int i = 0;

	// MDIO_CMD is set for read
	rddata = athrs26_reg_read(0x98);
	rddata = (rddata & 0x0) | (reg_addr << 16) | (phy_addr << 21) | (1 << 27) | (1 << 30) | (1 << 31);
	athrs26_reg_write(0x98, rddata);

	rddata = athrs26_reg_read(0x98);
	rddata = rddata & (1 << 31);

	// Check MDIO_BUSY status
	while(rddata){
		// TODO: do we need this?
		i++;

		if(i > 824)	{
			printf("## Error: MDIO_BUSY!\n");
			break;
		}

		rddata = athrs26_reg_read(0x98);
		rddata = rddata & (1 << 31);
	}

	// Read the data from phy
	rddata = athrs26_reg_read(0x98) & 0xffff;

	return(rddata);
}

void s26_wr_phy(unsigned int phy_addr, unsigned int reg_addr, unsigned int write_data){
	unsigned int rddata;
	unsigned int i = 0;

	// MDIO_CMD is set for read
	rddata = athrs26_reg_read(0x98);
	rddata = (rddata & 0x0) | (write_data & 0xffff) | (reg_addr << 16) | (phy_addr << 21) | (0 << 27) | (1 << 30) | (1 << 31);
	athrs26_reg_write(0x98, rddata);

	rddata = athrs26_reg_read(0x98);
	rddata = rddata & (1 << 31);

	// Check MDIO_BUSY status
	while(rddata){
		// TODO: do we need this?
		i++;

		if(i > 824)	{
			printf("## Error: MDIO_BUSY!\n");
			break;
		}

		rddata = athrs26_reg_read(0x98);
		rddata = rddata & (1 << 31);
	}

}

int athrs26_mdc_check(void){
	int i;

	for(i = 0; i < 4000; i++){
		if(athrs26_reg_read(0x10c) != 0x18007fff){
			return(-1);
		}
	}

	return(0);
}
