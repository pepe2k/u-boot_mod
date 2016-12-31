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
#include "athrs17_phy.h"

#define ATHR_LAN_PORT_VLAN	1
#define ATHR_WAN_PORT_VLAN	2
#define ENET_UNIT_GE0		0
#define ENET_UNIT_GE1		1
#define TRUE				1
#define FALSE				0

#define ATHR_PHY0_ADDR		0x0
#define ATHR_PHY1_ADDR		0x1
#define ATHR_PHY2_ADDR		0x2
#define ATHR_PHY3_ADDR		0x3
#define ATHR_PHY4_ADDR		0x4
#define ATHR_IND_PHY		4

#define MODULE_NAME			"ATHRS17"
#define S17_PHY_DEBUG		1

/*
 * Track per-PHY port information.
 */
typedef struct {
	int			isEnetPort;       /* normal enet port */
	int			isPhyAlive;       /* last known state of link */
    int			ethUnit;          /* MAC associated with this phy port */
    uint32_t	phyBase;
    uint32_t	phyAddr;          /* PHY registers associated with this phy port */
    uint32_t	VLANTableSetting; /* Value to be written to VLAN table */
} athrPhyInfo_t;

/*
 * Per-PHY information, indexed by PHY unit number.
 */
static athrPhyInfo_t athrPhyInfo[] = {
	/* phy port 0 -- LAN port 0 */
	{TRUE, FALSE, ENET_UNIT_GE0, 0, ATHR_PHY0_ADDR, ATHR_LAN_PORT_VLAN},
	
	/* phy port 1 -- LAN port 1 */
	{TRUE, FALSE, ENET_UNIT_GE0, 0, ATHR_PHY1_ADDR, ATHR_LAN_PORT_VLAN},

	/* phy port 2 -- LAN port 2 */
	{TRUE, FALSE, ENET_UNIT_GE0, 0, ATHR_PHY2_ADDR, ATHR_LAN_PORT_VLAN},

	/* phy port 3 -- LAN port 3 */
	{TRUE, FALSE, ENET_UNIT_GE0, 0, ATHR_PHY3_ADDR, ATHR_LAN_PORT_VLAN},

	/* phy port 4 -- WAN port or LAN port 4 */
	/* Send to all ports */
	{TRUE, FALSE, ENET_UNIT_GE0, 0, ATHR_PHY4_ADDR, ATHR_LAN_PORT_VLAN},

	/* phy port 5 -- CPU port (no RJ45 connector) */
	/* Send to all ports */
	{FALSE, TRUE, ENET_UNIT_GE0, 0, 0x00, ATHR_LAN_PORT_VLAN},
};

static uint8_t athr17_init_flag = 0;

#define ATHR_PHY_MAX	5

/* Range of valid PHY IDs is [MIN..MAX] */
#define ATHR_ID_MIN		0
#define ATHR_ID_MAX		(ATHR_PHY_MAX-1)

/* Convenience macros to access myPhyInfo */
#define ATHR_IS_ENET_PORT(phyUnit) (athrPhyInfo[phyUnit].isEnetPort)
#define ATHR_IS_PHY_ALIVE(phyUnit) (athrPhyInfo[phyUnit].isPhyAlive)
#define ATHR_ETHUNIT(phyUnit) (athrPhyInfo[phyUnit].ethUnit)
#define ATHR_PHYBASE(phyUnit) (athrPhyInfo[phyUnit].phyBase)
#define ATHR_PHYADDR(phyUnit) (athrPhyInfo[phyUnit].phyAddr)
#define ATHR_VLAN_TABLE_SETTING(phyUnit) (athrPhyInfo[phyUnit].VLANTableSetting)

#define ATHR_IS_ETHUNIT(phyUnit, ethUnit) \
            (ATHR_IS_ENET_PORT(phyUnit) &&        \
            ATHR_ETHUNIT(phyUnit) == (ethUnit))

#define ATHR_IS_WAN_PORT(phyUnit) (!(ATHR_ETHUNIT(phyUnit)==ENET_UNIT_GE0))
            
/* Forward references */
int athrs17_phy_is_link_alive(int phyUnit);
uint32_t athrs17_reg_read(uint32_t reg_addr);
void athrs17_reg_write(uint32_t reg_addr, uint32_t reg_val);

#define sysMsDelay(_x) udelay((_x) * 1000)

void athrs17_reg_init(){
	int phy_addr = 0;

	/* if using header for register configuration, we have to     */
	/* configure s17 register after frame transmission is enabled */
	if(athr17_init_flag){
		return;
	}

	/* configure the RGMII */
	athrs17_reg_write(0x624 , 0x7f7f7f7f);
	athrs17_reg_write(0x10  , 0x40000000);
	athrs17_reg_write(0x4   , 0x07600000);
	athrs17_reg_write(0xc   , 0x01000000);
	athrs17_reg_write(0x7c  , 0x0000007e);

	/* AR8327/AR8328 v1.0 fixup */
	if((athrs17_reg_read(0x0) & 0xffff) == 0x1201){
		for(phy_addr = 0x0; phy_addr <= ATHR_PHY_MAX; phy_addr++){
			/* For 100M waveform */
			phy_reg_write(0, phy_addr, 0x1d, 0x0);
			phy_reg_write(0, phy_addr, 0x1e, 0x02ea);
			
			/* Turn On Gigabit Clock */
			phy_reg_write(0, phy_addr, 0x1d, 0x3d);
			phy_reg_write(0, phy_addr, 0x1e, 0x68a0);
		}
	}

	/* set the WAN Port(Port1) Disable Mode(can not receive or transmit any frames) */
	// TODO: why WAN should be disabled?
	//athrs17_reg_write(0x066c, athrs17_reg_read(0x066c) & 0xfff8ffff);

	athr17_init_flag = 1;
}

/******************************************************************************
*
* athrs17_phy_is_link_alive - test to see if the specified link is alive
*
* RETURNS:
*    TRUE  --> link is alive
*    FALSE --> link is down
*/
int athrs17_phy_is_link_alive(int phyUnit){
	uint16_t phyHwStatus;
	//uint32_t phyBase;
	//uint32_t phyAddr;

	//phyBase = ATHR_PHYBASE(phyUnit);
	//phyAddr = ATHR_PHYADDR(phyUnit);

	phyHwStatus = phy_reg_read(ATHR_PHYBASE(phyUnit), ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS);

	if(phyHwStatus & ATHR_STATUS_LINK_PASS){
		return(TRUE);
	}

	return(FALSE);
}

/******************************************************************************
*
* athrs17_phy_setup - reset and setup the PHY associated with
* the specified MAC unit number.
*
* Resets the associated PHY port.
*
* RETURNS:
*    TRUE  --> associated PHY is alive
*    FALSE --> no LINKs on this ethernet unit
*/
int athrs17_phy_setup(int ethUnit){
	int			phyUnit;
	uint16_t	phyHwStatus;
	uint16_t	timeout;
	int			liveLinks = 0;
	uint32_t	phyBase = 0;
	int			foundPhy = FALSE;
	uint32_t	phyAddr = 0;

	/* See if there's any configuration data for this enet */
	/* start auto negogiation on each phy */
	for(phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		foundPhy = TRUE;
		phyBase = ATHR_PHYBASE(phyUnit);
		phyAddr = ATHR_PHYADDR(phyUnit);

		phy_reg_write(phyBase, phyAddr, ATHR_AUTONEG_ADVERT, ATHR_ADVERTISE_ALL);
		phy_reg_write(phyBase, phyAddr, ATHR_1000BASET_CONTROL, ATHR_ADVERTISE_1000FULL);
		
		/* Reset PHYs*/
		phy_reg_write(phyBase, phyAddr, ATHR_PHY_CONTROL, ATHR_CTRL_AUTONEGOTIATION_ENABLE | ATHR_CTRL_SOFTWARE_RESET);
	}

	if(!foundPhy){
		/* No PHY's configured for this ethUnit */
		return(FALSE);
	}

	/*
	* After the phy is reset, it takes a little while before
	* it can respond properly.
	*/
	sysMsDelay(1000);

	/*
	* Wait up to 3 seconds for ALL associated PHYs to finish
	* autonegotiation.  The only way we get out of here sooner is
	* if ALL PHYs are connected AND finish autonegotiation.
	*/
	for(phyUnit = 0; (phyUnit < ATHR_PHY_MAX); phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		// TODO: maybe we can lower this value
		timeout = 10;

		for(;;){
			phyHwStatus = phy_reg_read(phyBase, phyAddr, ATHR_PHY_CONTROL);

			if(ATHR_RESET_DONE(phyHwStatus)){
				//printf("Port %d, Neg Success\n", phyUnit);
				break;
			}
			
			sysMsDelay(20);

			timeout--;
			
			if(timeout <= 0){
				break;
			}
		}
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
	for(phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs17_phy_is_link_alive(phyUnit)){
			liveLinks++;
			ATHR_IS_PHY_ALIVE(phyUnit) = TRUE;
		} else {
			ATHR_IS_PHY_ALIVE(phyUnit) = FALSE;
		}

		//printf("eth%d: Phy Specific Status=%4.4x\n", ethUnit, phy_reg_read(ATHR_PHYBASE(phyUnit), ATHR_PHYADDR(phyUnit), ATHR_PHY_SPEC_STATUS));
	}

	return(liveLinks > 0);
}

/******************************************************************************
*
* athrs17_phy_is_fdx - Determines whether the phy ports associated with the
* specified device are FULL or HALF duplex.
*
* RETURNS:
*    1 --> FULL
*    0 --> HALF
*/
int athrs17_phy_is_fdx(int ethUnit){
	int			phyUnit;
	uint32_t	phyBase;
	uint32_t	phyAddr;
	uint16_t	phyHwStatus;
	int			ii = 200;

	if(ethUnit == ENET_UNIT_GE0){
		return(TRUE);
	}

	for(phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs17_phy_is_link_alive(phyUnit)){
			phyBase = ATHR_PHYBASE(phyUnit);
			phyAddr = ATHR_PHYADDR(phyUnit);

			do {
				phyHwStatus = phy_reg_read(phyBase, phyAddr,
				ATHR_PHY_SPEC_STATUS);
				
				if(phyHwStatus & ATHR_STATUS_RESOVLED){
					break;
				}
				
				sysMsDelay(10);
			} while(--ii);

			if(phyHwStatus & ATHER_STATUS_FULL_DEPLEX){
				return(TRUE);
			}
		}
	}

	return(FALSE);
}

/******************************************************************************
*
* athrs17_phy_speed - Determines the speed of phy ports associated with the
* specified device.
*
* RETURNS:
*               AG7240_PHY_SPEED_10T, AG7240_PHY_SPEED_100TX;
*               AG7240_PHY_SPEED_1000T;
*/
int athrs17_phy_speed(int ethUnit){
	int			phyUnit;
	uint16_t	phyHwStatus;
	uint32_t	phyBase;
	uint32_t	phyAddr;
	int			ii = 200;

	if(ethUnit == ENET_UNIT_GE0){
		return(_1000BASET);
	}

	for(phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		if(athrs17_phy_is_link_alive(phyUnit)){
			phyBase = ATHR_PHYBASE(phyUnit);
			phyAddr = ATHR_PHYADDR(phyUnit);

			do {
				phyHwStatus = phy_reg_read(phyBase, phyAddr, ATHR_PHY_SPEC_STATUS);
				
				if(phyHwStatus & ATHR_STATUS_RESOVLED){
					break;
				}
				
				sysMsDelay(10);
			} while((!(phyHwStatus & ATHR_STATUS_RESOVLED)) && --ii);

			phyHwStatus = ((phyHwStatus & ATHER_STATUS_LINK_MASK) >> ATHER_STATUS_LINK_SHIFT);

			switch(phyHwStatus){
				case 0:
					return(_10BASET);
					break;
				case 1:
					return(_100BASET);
					break;
				case 2:
					return(_1000BASET);
					break;
				default:
					//printf("## Error: unkown speed read!\n");
					break;
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
int athrs17_phy_is_up(int ethUnit){
	int				phyUnit;
	uint16_t		phyHwStatus, phyHwControl;
	athrPhyInfo_t	*lastStatus;
	int				linkCount   = 0;
	int				lostLinks   = 0;
	int				gainedLinks = 0;
	uint32_t		phyBase;
	uint32_t		phyAddr;

	for(phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++){
		if(!ATHR_IS_ETHUNIT(phyUnit, ethUnit)){
			continue;
		}

		phyBase = ATHR_PHYBASE(phyUnit);
		phyAddr = ATHR_PHYADDR(phyUnit);

		lastStatus = &athrPhyInfo[phyUnit];

		if(lastStatus->isPhyAlive){ /* last known link status was ALIVE */
			phyHwStatus = phy_reg_read(phyBase, phyAddr, ATHR_PHY_SPEC_STATUS);

			/* See if we've lost link */
			if(phyHwStatus & ATHR_STATUS_LINK_PASS){
				linkCount++;
			} else {
				lostLinks++;
				//printf("\nenet%d port%d down\n", ethUnit, phyUnit);
				lastStatus->isPhyAlive = FALSE;
			}
		} else { /* last known link status was DEAD */
		/* Check for reset complete */
			phyHwStatus = phy_reg_read(phyBase, phyAddr, ATHR_PHY_STATUS);
			if(!ATHR_RESET_DONE(phyHwStatus)){
				continue;
			}

			phyHwControl = phy_reg_read(phyBase, phyAddr, ATHR_PHY_CONTROL);
			
			/* Check for AutoNegotiation complete */            
			if((!(phyHwControl & ATHR_CTRL_AUTONEGOTIATION_ENABLE)) || ATHR_AUTONEG_DONE(phyHwStatus)){
				phyHwStatus = phy_reg_read(phyBase, phyAddr, 
				ATHR_PHY_SPEC_STATUS);

				if(phyHwStatus & ATHR_STATUS_LINK_PASS){
					gainedLinks++;
					linkCount++;
					//printf("\nenet%d port%d up\n", ethUnit, phyUnit);
					lastStatus->isPhyAlive = TRUE;
				}
			}
		}
	}

	return(linkCount);
}

uint32_t athrs17_reg_read(uint32_t reg_addr){
	uint32_t reg_word_addr;
	uint32_t phy_addr, tmp_val, reg_val;
	uint16_t phy_val;
	uint8_t phy_reg;

	/* change reg_addr to 16-bit word address, 32-bit aligned */
	reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

	/* configure register high address */
	phy_addr = 0x18;
	phy_reg = 0x0;
	phy_val = (uint16_t)((reg_word_addr >> 8) & 0x1ff);  /* bit16-8 of reg address */
	phy_reg_write(0, phy_addr, phy_reg, phy_val);

	/* For some registers such as MIBs, since it is read/clear, we should */
	/* read the lower 16-bit register then the higher one */

	/* read register in lower address */
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (uint8_t)(reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	reg_val = (uint32_t)phy_reg_read(0, phy_addr, phy_reg);

	/* read register in higher address */
	reg_word_addr++;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (uint8_t)(reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	tmp_val = (uint32_t)phy_reg_read(0, phy_addr, phy_reg);
	reg_val |= (tmp_val << 16);

	return(reg_val);
}

void athrs17_reg_write(uint32_t reg_addr, uint32_t reg_val){
	uint32_t reg_word_addr;
	uint32_t phy_addr;
	uint16_t phy_val;
	uint8_t phy_reg;

	/* change reg_addr to 16-bit word address, 32-bit aligned */
	reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

	/* configure register high address */
	phy_addr = 0x18;
	phy_reg = 0x0;
	phy_val = (uint16_t)((reg_word_addr >> 8) & 0x1ff);  /* bit16-8 of reg address */
	phy_reg_write(0, phy_addr, phy_reg, phy_val);

	/* For some registers such as ARL and VLAN, since they include BUSY bit */
	/* in lower address, we should write the higher 16-bit register then the */
	/* lower one */

	/* read register in higher address */
	reg_word_addr++;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (uint8_t)(reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	phy_val = (uint16_t)((reg_val >> 16) & 0xffff);
	phy_reg_write(0, phy_addr, phy_reg, phy_val);

	/* write register in lower address */
	reg_word_addr--;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (uint8_t)(reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	phy_val = (uint16_t)(reg_val & 0xffff);
	phy_reg_write(0, phy_addr, phy_reg, phy_val);
}
