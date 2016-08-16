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

/*
 * Manage the atheros ethernet PHY.
 *
 * All definitions in this file are operating system independent!
 */

#include <config.h>
#include <linux/types.h>
#include <common.h>
#include <miiphy.h>

#include <asm/addrspace.h>
#include <atheros.h>
#include "athr_s27_phy.h"


//#include "phy.h" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define ath_gmac_unit2name(_unit) (_unit ?  "eth1" : "eth0")

extern int ath_gmac_miiphy_read(char *devname, uint32_t phaddr, uint8_t reg, uint16_t *data);
extern int ath_gmac_miiphy_write(char *devname, uint32_t phaddr, uint8_t reg, uint16_t data);

void athrs27_reg_rmw(unsigned int s27_addr, unsigned int s27_write_data);

#define phy_reg_read(base, addr, reg)	\
	ath_gmac_miiphy_read(ath_gmac_unit2name(base), addr, reg, NULL)

#define phy_reg_write(base, addr, reg, data)	\
	ath_gmac_miiphy_write(ath_gmac_unit2name(base), addr, reg, data)


#ifdef S27_PHY_DEBUG
	#undef S27_PHY_DEBUG
#endif




/* PHY selections and access functions */

typedef enum {
    PHY_SRCPORT_INFO,
    PHY_PORTINFO_SIZE,
} PHY_CAP_TYPE;

typedef enum {
    PHY_SRCPORT_NONE,
    PHY_SRCPORT_VLANTAG,
    PHY_SRCPORT_TRAILER,
} PHY_SRCPORT_TYPE;

#define DRV_LOG(DBG_SW, X0, X1, X2, X3, X4, X5, X6)
#define DRV_MSG(x,a,b,c,d,e,f)
#define DRV_PRINT(DBG_SW,X)

#define ATHR_LAN_PORT_VLAN          1
#define ATHR_WAN_PORT_VLAN          2
#define ENET_UNIT_LAN 1
#define ENET_UNIT_WAN 0

#define TRUE    1
#define FALSE   0

#define ATHR_PHY0_ADDR   0x0
#define ATHR_PHY1_ADDR   0x1
#define ATHR_PHY2_ADDR   0x2
#define ATHR_PHY3_ADDR   0x3
#define ATHR_PHY4_ADDR   0x4

#define MODULE_NAME "ATHRS27"

/*
 * Track per-PHY port information.
 */


typedef struct {
    BOOL   isEnetPort;       /* normal enet port */
    BOOL   isPhyAlive;       /* last known state of link */
    int    ethUnit;          /* MAC associated with this phy port */
    uint32_t phyBase;
    uint32_t phyAddr;          /* PHY registers associated with this phy port */
    uint32_t VLANTableSetting; /* Value to be written to VLAN table */
} athrPhyInfo_t;

/*
 * Per-PHY information, indexed by PHY unit number.
 */
static athrPhyInfo_t athrPhyInfo[] = {

    {TRUE,   /* port 1 -- LAN port 1 */
     FALSE,
     ENET_UNIT_LAN,
     0,
     ATHR_PHY0_ADDR,
     ATHR_LAN_PORT_VLAN
    },

    {TRUE,   /* port 2 -- LAN port 2 */
     FALSE,
     ENET_UNIT_LAN,
     0,
     ATHR_PHY1_ADDR,
     ATHR_LAN_PORT_VLAN
    },

    {TRUE,   /* port 3 -- LAN port 3 */
     FALSE,
     ENET_UNIT_LAN,
     0,
     ATHR_PHY2_ADDR,
     ATHR_LAN_PORT_VLAN
    },


   {TRUE,   /* port 4 --  LAN port 4 */
     FALSE,
     ENET_UNIT_LAN,
     0,
     ATHR_PHY3_ADDR,
     ATHR_LAN_PORT_VLAN   /* Send to all ports */
    },

    {TRUE,  /* port 5 -- WAN Port 5 */
     FALSE,
     ENET_UNIT_WAN,
     0,
     ATHR_PHY4_ADDR,
     ATHR_LAN_PORT_VLAN    /* Send to all ports */
    },

    {FALSE,   /* port 0 -- cpu port 0 */
     TRUE,
     ENET_UNIT_LAN,
     0,
     0x00,
     ATHR_LAN_PORT_VLAN
    },

};


#define ATHR_GLOBALREGBASE    0

#define ATHR_PHY_MAX 5

/* Range of valid PHY IDs is [MIN..MAX] */
#define ATHR_ID_MIN 0
#define ATHR_ID_MAX (ATHR_PHY_MAX-1)


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

#define ATHR_IS_WAN_PORT(phyUnit) (!(ATHR_ETHUNIT(phyUnit)==ENET_UNIT_LAN))

/* Forward references */
BOOL athrs27_phy_is_link_alive(int phyUnit);
uint32_t athrs27_reg_read(uint32_t reg_addr);
void athrs27_reg_write(uint32_t reg_addr, uint32_t reg_val);
unsigned int s27_rd_phy(unsigned int phy_addr, unsigned int reg_addr);
void s27_wr_phy(unsigned int phy_addr, unsigned int reg_addr, unsigned int write_data);


void athrs27_powersave_off(int phy_addr)
{
    s27_wr_phy(phy_addr,ATHR_DEBUG_PORT_ADDRESS,0x29);
    s27_wr_phy(phy_addr,ATHR_DEBUG_PORT_DATA,0x36c0);

}
void athrs27_sleep_off(int phy_addr)
{
    s27_wr_phy(phy_addr,ATHR_DEBUG_PORT_ADDRESS,0xb);
    s27_wr_phy(phy_addr,ATHR_DEBUG_PORT_DATA,0x3c00);
}

void athrs27_force_100M(int phyAddr,int duplex)
{
   /*
    *  Force MDI and MDX to alternate ports 
    *  Phy 0,2 and 4 -- MDI
    *  Phy 1 and 3 -- MDX
    */

    if(phyAddr%2) {
        s27_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x820);
    }
    else {
        s27_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x800);
    }

    s27_wr_phy(phyAddr,0x1d,0x29);
    s27_wr_phy(phyAddr,0x1e,0x0);
    s27_wr_phy(phyAddr,0x10,0xc60);
    s27_wr_phy(phyAddr,ATHR_PHY_CONTROL,(0xa000|(duplex << 8)));
}

void athrs27_force_10M(int phyAddr,int duplex)
{

    athrs27_powersave_off(phyAddr);
    athrs27_sleep_off(phyAddr);

    s27_wr_phy(phyAddr,ATHR_PHY_CONTROL,(0x8000 |(duplex << 8)));
}

int athrs27_reg_init(void)
{
#ifdef S27_PHY_DEBUG
    uint32_t rd_val;
#endif

    /* if using header for register configuration, we have to     */
    /* configure s27 register after frame transmission is enabled */
    athrs27_reg_rmw(0x8,(1<<28));  /* Set WAN port is connected to GE0 */

#if defined(S27_FORCE_100M)
    athrs27_force_100M(ATHR_PHY4_ADDR,1);
#elif  defined(S27_FORCE_10M)
    athrs27_force_10M(ATHR_PHY4_ADDR,1);
#else
    s27_wr_phy(ATHR_PHY4_ADDR,ATHR_PHY_CONTROL,0x9000);

#endif
#ifdef S27_PHY_DEBUG
    printf(MODULE_NAME":OPERATIONAL_MODE_REG0:%x\n",athrs27_reg_read(OPERATIONAL_MODE_REG0));
    printf(MODULE_NAME":REG 0x4-->:%x\n",athrs27_reg_read(0x4));
    printf(MODULE_NAME":REG 0x2c-->:%x\n",athrs27_reg_read(0x2c));
    printf(MODULE_NAME":REG 0x8-->:%x\n",athrs27_reg_read(0x8));
#endif

    return 0;
}
 
int athrs27_reg_init_lan(void)
{
    int i = 60;
#if S26_PHY_DEBUG
    uint32_t rd_val;
#endif
    int       phyUnit;
    uint32_t  phyAddr = 0;


    /* reset switch */
    //printf(MODULE_NAME ": resetting s27\n");
    athrs27_reg_write(0x0, athrs27_reg_read(0x0)|0x80000000);

    while(i--) {
        //sysMsDelay(100);
        if(!(athrs27_reg_read(0x0)&0x80000000))
            break;
    }
    //printf(MODULE_NAME ": s27 reset done\n");
    athrs27_reg_write(PORT_STATUS_REGISTER0,0x4e);

    athrs27_reg_rmw(OPERATIONAL_MODE_REG0,(1<<6));  /* Set GMII mode */

    if (is_emu() || is_wasp()) {
       athrs27_reg_rmw(0x2c,((1<<26)| (1<<16) | 0x1)); /* FiX ME: EBU debug */
    }

    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {

        phyAddr = ATHR_PHYADDR(phyUnit);

#if defined(S27_FORCE_100M)
        athrs27_force_100M(phyAddr,1);
#elif defined(S27_FORCE_10M)
        athrs27_force_10M(phyAddr,1);
#else
        s27_wr_phy(phyAddr,ATHR_PHY_CONTROL,0x9000);
#endif

#ifdef S27_PHY_DEBUG
        rd_val = s27_rd_phy(phyAddr,ATHR_PHY_FUNC_CONTROL);
        printf("S27 ATHR_PHY_FUNC_CONTROL (%d):%x\n",phyAddr,rd_val);
        rd_val = s27_rd_phy(phyAddr,ATHR_PHY_ID1);
        printf("S27 PHY ID  (%d) :%x\n",phyAddr, rd_val);
        rd_val = s27_rd_phy(phyAddr,ATHR_PHY_SPEC_STATUS);
        printf("S27 PHY CTRL  (%d) :%x\n",phyAddr, rd_val);
        rd_val = s27_rd_phy(phyAddr,ATHR_PHY_STATUS);
        printf("S27 ATHR PHY STATUS  (%d) :%x\n",phyAddr, rd_val);
#endif
    }

    /* 
     * status[1:0]=2'h2;   - (0x10 - 1000 Mbps , 0x01 - 100Mbps, 0x0 - 10 Mbps)
     * status[2]=1'h1;     - Tx Mac En
     * status[3]=1'h1;     - Rx Mac En
     * status[4]=1'h1;     - Tx Flow Ctrl En
     * status[5]=1'h1;     - Rx Flow Ctrl En
     * status[6]=1'h1;     - Duplex Mode
     */
    athrs27_reg_write(PORT_STATUS_REGISTER1, 0x200);  /* LAN - 1 */
    athrs27_reg_write(PORT_STATUS_REGISTER2, 0x200);  /* LAN - 2 */
    athrs27_reg_write(PORT_STATUS_REGISTER3, 0x200);  /* LAN - 3 */
    athrs27_reg_write(PORT_STATUS_REGISTER4, 0x200);  /* LAN - 4 */

    if (is_emu()) {
        athrs27_reg_write(PORT_STATUS_REGISTER1, 0x4C);  /* LAN - 1 */
        athrs27_reg_write(PORT_STATUS_REGISTER2, 0x4c);  /* LAN - 2 */
        athrs27_reg_write(PORT_STATUS_REGISTER3, 0x4c);  /* LAN - 3 */
        athrs27_reg_write(PORT_STATUS_REGISTER4, 0x4c);  /* LAN - 4 */
    }

    /* QM Control */
    athrs27_reg_write(0x38, 0xc000050e);

    /*
     * status[11]=1'h0;    - CPU Disable
     * status[7] = 1'b1;   - Learn One Lock
     * status[14] = 1'b0;  - Learn Enable
     */
#ifdef ATHEROS_HEADER_EN
    athrs27_reg_write(PORT_CONTROL_REGISTER0, 0x4804);
#else
   /* Atheros Header Disable */
    athrs27_reg_write(PORT_CONTROL_REGISTER0, 0x4004);
#endif

    /* Tag Priority Mapping */
    athrs27_reg_write(0x70, 0xfa50);

    /* Enable ARP packets to CPU port */
    athrs27_reg_write(S27_ARL_TBL_CTRL_REG,(athrs27_reg_read(S27_ARL_TBL_CTRL_REG) | 0x100000));

   /* Enable Broadcast packets to CPU port */
    athrs27_reg_write(S27_FLD_MASK_REG,(athrs27_reg_read(S27_FLD_MASK_REG) |
                           S27_ENABLE_CPU_BROADCAST | S27_ENABLE_CPU_BCAST_FWD ));

    return 0;
}

/******************************************************************************
*
* athrs27_phy_is_link_alive - test to see if the specified link is alive
*
* RETURNS:
*    TRUE  --> link is alive
*    FALSE --> link is down
*/
BOOL
athrs27_phy_is_link_alive(int phyUnit)
{
    uint16_t phyHwStatus;
    uint32_t phyAddr;

    phyAddr = ATHR_PHYADDR(phyUnit);
    phyHwStatus = s27_rd_phy(phyAddr, ATHR_PHY_SPEC_STATUS);

    if (phyHwStatus & ATHR_STATUS_LINK_PASS)
        return TRUE;

    return FALSE;
}

/******************************************************************************
*
* athrs27_phy_setup - reset and setup the PHY associated with
* the specified MAC unit number.
*   
* Resets the associated PHY port.
*   
* RETURNS:
*    TRUE  --> associated PHY is alive
*    FALSE --> no LINKs on this ethernet unit
*/
BOOL
athrs27_phy_setup(int ethUnit)
{
    int       phyUnit;
    uint16_t  phyHwStatus;
    uint16_t  timeout;
    int       liveLinks = 0;
    BOOL      foundPhy = FALSE;
    uint32_t  phyAddr = 0;

    /* See if there's any configuration data for this enet */
    /* start auto negogiation on each phy */
    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {

        foundPhy = TRUE;
        phyAddr = ATHR_PHYADDR(phyUnit);

        if (!ATHR_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }
        if (!is_emu()) {
           s27_wr_phy(phyAddr, ATHR_AUTONEG_ADVERT,ATHR_ADVERTISE_ALL);

           s27_wr_phy(phyAddr, ATHR_PHY_CONTROL,ATHR_CTRL_AUTONEGOTIATION_ENABLE
                         | ATHR_CTRL_SOFTWARE_RESET);
        }
        else  {
		//printf("############ is emulation ############\n");

           if(ATHR_ETHUNIT(phyUnit) == ENET_UNIT_WAN) {
               s27_wr_phy(phyAddr, ATHR_AUTONEG_ADVERT,ATHR_ADVERTISE_ALL);
               s27_wr_phy(phyAddr,0x9, 0x0); //donot advertise 1000Mbps mode
               s27_wr_phy(phyAddr, ATHR_PHY_CONTROL,0x0);
               s27_wr_phy(phyAddr, ATHR_PHY_CONTROL,ATHR_CTRL_AUTONEGOTIATION_ENABLE
                         | ATHR_CTRL_SOFTWARE_RESET);
           }
           else { 

               s27_wr_phy(phyAddr, ATHR_AUTONEG_ADVERT,(ATHR_ADVERTISE_ASYM_PAUSE | ATHR_ADVERTISE_PAUSE |
                            ATHR_ADVERTISE_10HALF | ATHR_ADVERTISE_10FULL));
               s27_wr_phy(phyAddr,0x9, 0x0); //donot advertise 1000Mbps mode
               s27_wr_phy(phyAddr, ATHR_PHY_CONTROL,0x0);
               s27_wr_phy(phyAddr, ATHR_PHY_CONTROL,ATHR_CTRL_AUTONEGOTIATION_ENABLE
                         | ATHR_CTRL_SOFTWARE_RESET);
           }
       }
    }
    if (!foundPhy) {
        return FALSE; /* No PHY's configured for this ethUnit */
    }

    /*
     * After the phy is reset, it takes a little while before
     * it can respond properly.
     */
	/*
    if (ethUnit == ENET_UNIT_LAN)
        sysMsDelay(100);
    else
        sysMsDelay(300);
	*/

    /*
     * Wait up to 3 seconds for ALL associated PHYs to finish
     * autonegotiation.  The only way we get out of here sooner is
     * if ALL PHYs are connected AND finish autonegotiation.
     */
    for (phyUnit=0; (phyUnit < ATHR_PHY_MAX) /*&& (timeout > 0) */; phyUnit++) {
        if (ATHR_ETHUNIT(phyUnit) == ENET_UNIT_WAN)
            continue;

        timeout=20;
        for (;;) {
            phyHwStatus =  s27_rd_phy(phyAddr, ATHR_PHY_CONTROL);

            if (ATHR_RESET_DONE(phyHwStatus)) {
                DRV_PRINT(DRV_DEBUG_PHYSETUP,
                          ("Port %d, Neg Success\n", phyUnit));
                break;
            }
            if (timeout == 0) {
                DRV_PRINT(DRV_DEBUG_PHYSETUP,
                          ("Port %d, Negogiation timeout\n", phyUnit));
                break;
            }
            if (--timeout == 0) {
                DRV_PRINT(DRV_DEBUG_PHYSETUP,
                          ("Port %d, Negogiation timeout\n", phyUnit));
                break;
            }

            //sysMsDelay(150);
        }
        /* extend the cable length */
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_ADDRESS, 0x14);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_DATA, 0xf52);

       /* Force Class A setting phys */
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_ADDRESS, 4);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_DATA, 0xebbb);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_ADDRESS, 5);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_DATA, 0x2c47);

        /* fine-tune PHYs */
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_ADDRESS, 0x3c);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_DATA, 0x1c1);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_ADDRESS, 0x37);
        s27_wr_phy(phyUnit, ATHR_DEBUG_PORT_DATA, 0xd600);


#ifdef S27_VER_1_0
        /* turn off power saving */
        s27_wr_phy(phyUnit, 29, 41);
        s27_wr_phy(phyUnit, 30, 0);
        //printf("def_ S27_VER_1_0\n");
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
    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {
        if (!ATHR_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }

        if (athrs27_phy_is_link_alive(phyUnit)) {
            liveLinks++;
            ATHR_IS_PHY_ALIVE(phyUnit) = TRUE;
        } else {
            ATHR_IS_PHY_ALIVE(phyUnit) = FALSE;
        }
        DRV_PRINT(DRV_DEBUG_PHYSETUP,
            ("eth%d: Phy Specific Status=%4.4x\n",
            ethUnit,
            s27_rd_phy(ATHR_PHYADDR(phyUnit),ATHR_PHY_SPEC_STATUS)));
    }

    return (liveLinks > 0);
}

/******************************************************************************
*
* athrs27_phy_is_fdx - Determines whether the phy ports associated with the
* specified device are FULL or HALF duplex.
*
* RETURNS:
*    1 --> FULL
*    0 --> HALF
*/
int
athrs27_phy_is_fdx(int ethUnit,int phyUnit)
{
    uint32_t  phyAddr;
    uint16_t  phyHwStatus;
    int       ii = 200;

    if (ethUnit == ENET_UNIT_LAN)
        return TRUE;

    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {
        if (!ATHR_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }

        if (athrs27_phy_is_link_alive(phyUnit)) {

            phyAddr = ATHR_PHYADDR(phyUnit);

            do {
                phyHwStatus = s27_rd_phy (phyAddr, ATHR_PHY_SPEC_STATUS);
                        if(phyHwStatus & ATHR_STATUS_RESOVLED)
                                break;
                sysMsDelay(10);
            } while(--ii);
            if (phyHwStatus & ATHER_STATUS_FULL_DUPLEX) {
                return TRUE;
            }
        }
    }

    return FALSE;
}
/******************************************************************************
*
* athrs27_phy_speed - Determines the speed of phy ports associated with the
* specified device.
*
* RETURNS:
*               ATHR_PHY_SPEED_10T, AG7240_PHY_SPEED_100T;
*               ATHR_PHY_SPEED_1000T;
*/

int
athrs27_phy_speed(int ethUnit,int phyUnit)
{
    uint16_t  phyHwStatus;
    uint32_t  phyAddr;
    int       ii = 200;
    int       phySpeed = _100BASET;
    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {
        if (!ATHR_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }

        phyAddr = ATHR_PHYADDR(phyUnit);
        phySpeed = _10BASET;

        if (athrs27_phy_is_link_alive(phyUnit)) {

            do {
                phyHwStatus = s27_rd_phy(phyAddr,
                                              ATHR_PHY_SPEC_STATUS);
                        if(phyHwStatus & ATHR_STATUS_RESOVLED)
                                break;
                sysMsDelay(10);
            }while(--ii);

            phyHwStatus = ((phyHwStatus & ATHER_STATUS_LINK_MASK) >>
                           ATHER_STATUS_LINK_SHIFT);

            switch(phyHwStatus) {
            case 0:
                phySpeed = _10BASET;
		break;
            case 1:
                phySpeed = _100BASET;
		break;
            case 2:
                phySpeed = _1000BASET;
		break;
            default:
                printf("Unkown speed read!\n");
            }
        }

        phy_reg_write(1,phyAddr, ATHR_DEBUG_PORT_ADDRESS, 0x18);

        if(phySpeed == _100BASET) {
            phy_reg_write(1,phyAddr, ATHR_DEBUG_PORT_DATA, 0xba8);
        } else {
            phy_reg_write(1,phyAddr, ATHR_DEBUG_PORT_DATA, 0x2ea);
        }
    }

    if (ethUnit == ENET_UNIT_LAN)
         phySpeed = _1000BASET;

    return phySpeed;
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

int
athrs27_phy_is_up(int ethUnit)
{

    uint16_t      phyHwStatus, phyHwControl;
    athrPhyInfo_t *lastStatus;
    int           linkCount   = 0;
    int           lostLinks   = 0;
    int           gainedLinks = 0;
    uint32_t      phyAddr;
    int           phyUnit;

    for (phyUnit=0; phyUnit < ATHR_PHY_MAX; phyUnit++) {
        if (!ATHR_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }

        phyAddr = ATHR_PHYADDR(phyUnit);

        lastStatus = &athrPhyInfo[phyUnit];
        if (lastStatus->isPhyAlive) { /* last known link status was ALIVE */
            phyHwStatus = s27_rd_phy(phyAddr, ATHR_PHY_SPEC_STATUS);

            /* See if we've lost link */
            if (phyHwStatus & ATHR_STATUS_LINK_PASS) {
                linkCount++;
            } else {
                lostLinks++;
                DRV_PRINT(DRV_DEBUG_PHYCHANGE,("\nenet%d port%d down\n",
                                               ethUnit, phyUnit));
                printf("enet%d port%d down\n",ethUnit, phyUnit);
                lastStatus->isPhyAlive = FALSE;
            }
        } else { /* last known link status was DEAD */
            /* Check for reset complete */
            if(is_emu())
            {
                phyHwStatus = s27_rd_phy(phyAddr, ATHR_PHY_STATUS);
                if(phyAddr%2) {
                    s27_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x820);
                }
                else {
                    s27_wr_phy(phyAddr,ATHR_PHY_FUNC_CONTROL,0x800);
                }

                if((phyHwStatus & 0x4)==0)
                {
                   s27_wr_phy(phyAddr,0x9,0x0);
                   if(phyAddr !=0x4)
                       s27_wr_phy(phyAddr,0x4,0x41);
                   s27_wr_phy(phyAddr,0x0,0x9000);
                }
            }

            phyHwStatus = s27_rd_phy(phyAddr, ATHR_PHY_CONTROL);
            if (!ATHR_RESET_DONE(phyHwStatus))
                continue;

             phyHwControl = s27_rd_phy(phyAddr, ATHR_PHY_CONTROL);
             phyHwStatus = s27_rd_phy(phyAddr, ATHR_PHY_STATUS);

            /* Check for AutoNegotiation complete */
            if ((!(phyHwControl & ATHR_CTRL_AUTONEGOTIATION_ENABLE))
                 || ATHR_AUTONEG_DONE(phyHwStatus)) {
                phyHwStatus = s27_rd_phy(phyAddr,
                                           ATHR_PHY_SPEC_STATUS);

                if (phyHwStatus & ATHR_STATUS_LINK_PASS) {
                gainedLinks++;
                linkCount++;
                printf("enet%d port%d up\n",ethUnit, phyUnit);
                DRV_PRINT(DRV_DEBUG_PHYCHANGE,("\nenet%d port%d up\n",
                                               ethUnit, phyUnit));
                lastStatus->isPhyAlive = TRUE;
                }
            }
        }
    }
    return (linkCount);
}

unsigned int athrs27_reg_read(unsigned int s27_addr)
{
    unsigned int addr_temp;
    unsigned int s27_rd_csr_low, s27_rd_csr_high, s27_rd_csr;
    unsigned int data,unit = 0;
    unsigned int phy_address, reg_address;

    addr_temp = s27_addr >>2;
    data = addr_temp >> 7;

    phy_address = 0x1f;
    reg_address = 0x10;

    if (is_ar7240()) {
        unit = 0;
    }
    else if(is_ar7241() || is_ar7242() || is_wasp() || is_qca953x() || is_qca956x()) {
        unit = 1;
    }

    phy_reg_write(unit,phy_address, reg_address, data);

    phy_address = (0x17 & ((addr_temp >> 4) | 0x10));
    reg_address = ((addr_temp << 1) & 0x1e);
    s27_rd_csr_low = (uint32_t) phy_reg_read(unit,phy_address, reg_address);

    reg_address = reg_address | 0x1;
    s27_rd_csr_high = (uint32_t) phy_reg_read(unit,phy_address, reg_address);
    s27_rd_csr = (s27_rd_csr_high << 16) | s27_rd_csr_low ;
	
    return(s27_rd_csr);
}

void athrs27_reg_write(unsigned int s27_addr, unsigned int s27_write_data)
{
    unsigned int addr_temp;
    unsigned int data;
    unsigned int phy_address, reg_address,unit = 0;

    addr_temp = (s27_addr ) >>2;
    data = addr_temp >> 7;

    phy_address = 0x1f;
    reg_address = 0x10;

    if (is_ar7240()) {
        unit = 0;
    }
    else if(is_ar7241() || is_ar7242() || is_wasp() || is_qca953x() || is_qca956x()) {
        unit = 1;
    }
    phy_reg_write(unit,phy_address, reg_address, data);

    phy_address = (0x17 & ((addr_temp >> 4) | 0x10));

    reg_address = (((addr_temp << 1) & 0x1e) | 0x1);
    data = (s27_write_data >> 16) & 0xffff;
    phy_reg_write(unit,phy_address, reg_address, data);

    reg_address = ((addr_temp << 1) & 0x1e);
    data = s27_write_data  & 0xffff;
    phy_reg_write(unit,phy_address, reg_address, data);

}

void athrs27_reg_rmw(unsigned int s27_addr, unsigned int s27_write_data)
{
    int val = athrs27_reg_read(s27_addr);
    athrs27_reg_write(s27_addr,(val | s27_write_data));
}

unsigned int s27_rd_phy(unsigned int phy_addr, unsigned int reg_addr)
{
  int unit, val = 0; 
  
  if (is_ar7240()) {
    unit = 0;
  } else if(is_ar7241() || is_ar7242() || is_wasp() || is_qca953x() || is_qca956x()) {
    unit = 1;
  }
  val = (uint32_t) phy_reg_read(unit, phy_addr, reg_addr); 
  return val;
}

void s27_wr_phy(unsigned int phy_addr, unsigned int reg_addr, unsigned int write_data)
{
  int unit; 
  
  if (is_ar7240()) {
    unit = 0;
  } else if(is_ar7241() || is_ar7242() || is_wasp() || is_qca953x() || is_qca956x()) {
    unit = 1;
  }
  
  phy_reg_write(unit, phy_addr, reg_addr, write_data);   
}
int athrs27_mdc_check(void)
{
    int i;

    for (i=0; i<4000; i++) {
        if(athrs27_reg_read(0x10c) != 0x18007fff)
            return -1;
    }
    return 0;
}

