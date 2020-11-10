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

// ----------------------------------
// S17 Initialization
// author : subha@atheros.com
// adapted: Abishek Goda <Abishek.Goda at atheros dot com>
// ----------------------------------

//#include <prototypes.h>
//#include <gmac_defines.h>
#include <config.h>
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <command.h>
#include <asm/io.h>
#include <asm/addrspace.h>
#include <asm/types.h>

#include <atheros.h>
#include "qca-eth-955x.h"
#include "qca-eth-955x_phy.h"
#include "phy.h"
#include "athrs17_phy.h"

uint32_t athrs17_reg_read(uint32_t reg_addr);
void athrs17_reg_write(uint32_t reg_addr, uint32_t reg_val);

#ifdef ATH_RGMII_CAL

# define ATHR_PHY_MAX 1

#if 0
void s17_phy_write( unsigned int phy_address, 
                    unsigned int reg_address, 
                    unsigned int write_data ) {

    unsigned int rddata;
    unsigned int address;

    address = ((phy_address << 8) & 0x1f00) | (reg_address & 0x1f);

    reg_write(GE0_MAC_MII_MGMT_CFG, 0x7);

    rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    while(rddata){
        rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    }
    reg_write(GE0_MAC_MII_MGMT_CMD, 0x0);
    reg_write(GE0_MAC_MII_MGMT_ADDR, address);
    reg_write(GE0_MAC_MII_MGMT_CNTR, write_data);
    while(rddata){
        rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    }
}

unsigned int s17_phy_read(unsigned int phy_address, unsigned int reg_address) {

    unsigned int rddata;
    unsigned int address;
    unsigned int phy_rddata;

    address = ((phy_address << 8) & 0x1f00) | (reg_address & 0x1f);

    reg_write(GE0_MAC_MII_MGMT_CFG, 0x7);

    rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    while(rddata){
        rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    }
    reg_write(GE0_MAC_MII_MGMT_CMD, 0x0);
    reg_write(GE0_MAC_MII_MGMT_ADDR, address);
    reg_write(GE0_MAC_MII_MGMT_CMD, 0x1);

    rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    while(rddata){
        rddata = reg_read(GE0_MAC_MII_MGMT_PSTAT) & 0x1;
    }

    phy_rddata = reg_read(GE0_MAC_MII_MGMT_STAT);
    reg_write(GE0_MAC_MII_MGMT_CMD, 0x0);

    return(phy_rddata);

}

void s17_reg_write(unsigned int reg_addr, unsigned int reg_val) {

    unsigned int reg_word_addr;
    unsigned int phy_addr;
    unsigned int phy_val;
    unsigned int phy_reg;

    /* change reg_addr to 16-bit word address, 32-bit aligned */
    reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

    /* configure register high address */
    phy_addr = 0x18;
    phy_reg = 0x0;
    /* bit16-8 of reg address          */
    phy_val = (unsigned int) ((reg_word_addr >> 8) & 0x3ff);  
    s17_phy_write(phy_addr, phy_reg, phy_val);

    /* For S17 registers such as ARL and VLAN, since they include BUSY bit   */
    /* in higher address, we should write the lower 16-bit register then the */
    /* higher one */

    /* write register in lower address */
    phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7);  /* bit7-5 of reg address */
    phy_reg = (unsigned int) (reg_word_addr & 0x1f); /* bit4-0 of reg address */
    phy_val = (unsigned int) (reg_val & 0xffff);
    s17_phy_write( phy_addr, phy_reg, phy_val);

    /* read register in higher address */
    reg_word_addr++;
    phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7);  /* bit7-5 of reg address */
    phy_reg = (unsigned int) (reg_word_addr & 0x1f); /* bit4-0 of reg address */
    phy_val = (unsigned int) ((reg_val >> 16) & 0xffff);
    s17_phy_write( phy_addr, phy_reg, phy_val);
}

unsigned int s17_reg_read(unsigned int reg_addr) 
{
    unsigned int reg_word_addr;
    unsigned int phy_addr, tmp_val, reg_val;
    unsigned int phy_val;
    unsigned int phy_reg;

    /* change reg_addr to 16-bit word address, 32-bit aligned */
    reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

    /* configure register high address */
    phy_addr = 0x18;
    phy_reg = 0x0;
    /* bit16-8 of reg address */
    phy_val = (unsigned int) ((reg_word_addr >> 8) & 0x3ff); 
    s17_phy_write( phy_addr, phy_reg, phy_val);

    /* For some registers such as MIBs, since it is read/clear, we should */
    /* read the lower 16-bit register then the higher one */

    /* read register in lower address */
    phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7);  /* bit7-5 of reg address */
    phy_reg = (unsigned int) (reg_word_addr & 0x1f); /* bit4-0 of reg address */
    reg_val = (unsigned int) s17_phy_read( phy_addr, phy_reg);

    /* read register in higher address */
    reg_word_addr++;
    phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7);  /* bit7-5 of reg address */
    phy_reg = (unsigned int) (reg_word_addr & 0x1f); /* bit4-0 of reg address */
    tmp_val = (unsigned int) s17_phy_read( phy_addr, phy_reg);
    reg_val |= (tmp_val << 16);

    return reg_val;
}
#endif

void s17_reg_rmw(unsigned int reg_addr, unsigned int reg_val) 
{

    reg_val |= athrs17_reg_read(reg_addr);
    athrs17_reg_write(reg_addr,reg_val);
}

void init_s17(void) 
{
    int phyUnit = 0;
    int phyBase = 0;
    int phyAddr = 0;
    unsigned int rddata;

    athrs17_reg_write(0x624 , 0x003f3f3f);
    athrs17_reg_write(0x10  , 0x40000000);
    athrs17_reg_write(0x4   , 0x07500000);
    athrs17_reg_write(0xc   , 0x01000000);
    athrs17_reg_write(0x7c  , 0x000000fe); // 1gbps
    //athrs17_reg_write(0x7c  , 0x0000007d); // 100 mbps
    //athrs17_reg_write(0x7c  , 0x0000007c); // 10 mbps

    for (phyUnit= 0; phyUnit <= ATHR_PHY_MAX; phyUnit++)
    {
        phyBase = 0;
        phyAddr = phyUnit;
        // To enable loopback on a phy
        // rddata = s17_phy_read(phyAddr, 0x0);
        // s17_phy_write(phyAddr, 0x0, (rddata | BIT(14)));
        /* For 100M waveform */
        phy_reg_write(0, phyAddr, 0x1d, 0x18);
        phy_reg_write(0, phyAddr, 0x1e, 0x02ea);
        /* Turn On Gigabit Clock */
        phy_reg_write(0, phyAddr, 0x1d, 0x3d);
        phy_reg_write(0, phyAddr, 0x1e, 0x48a0);

    }

    /* Enable flow control */
    s17_reg_rmw(0x80,0x30);
    s17_reg_rmw(0x84,0x30);
    s17_reg_rmw(0x88,0x30);
    s17_reg_rmw(0x8c,0x30);
    s17_reg_rmw(0x90,0x30);
}

void vlan_config(void)
{
    athrs17_reg_write(S17_P0LOOKUP_CTRL_REG, 0x0014001e);
    athrs17_reg_write(S17_P0VLAN_CTRL0_REG, 0x10001);

    athrs17_reg_write(S17_P1LOOKUP_CTRL_REG, 0x0014001d);
    athrs17_reg_write(S17_P1VLAN_CTRL0_REG, 0x10001);

    athrs17_reg_write(S17_P2LOOKUP_CTRL_REG, 0x0014001b);
    athrs17_reg_write(S17_P2VLAN_CTRL0_REG, 0x10001);

    athrs17_reg_write(S17_P3LOOKUP_CTRL_REG, 0x00140017);
    athrs17_reg_write(S17_P3VLAN_CTRL0_REG, 0x10001);

    athrs17_reg_write(S17_P4LOOKUP_CTRL_REG, 0x0014000f);
    athrs17_reg_write(S17_P4VLAN_CTRL0_REG, 0x10001);

    athrs17_reg_write(S17_P5LOOKUP_CTRL_REG, 0x00140040);
    athrs17_reg_write(S17_P5VLAN_CTRL0_REG, 0x20001);

    athrs17_reg_write(S17_P6LOOKUP_CTRL_REG, 0x00140020);
    athrs17_reg_write(S17_P6VLAN_CTRL0_REG, 0x20001);

}

void init_s17_lpbk(void) 
{
    int phyUnit = 0;
    int phyBase = 0;
    int phyAddr = 0;
    unsigned int rddata;

#ifdef ATH_S17_MAC0_SGMII
    athrs17_reg_write(0x4   , 0x080080);
    athrs17_reg_write(0xc   , 0x07600000);
    athrs17_reg_write(0x94  , 0x000000fe); // 1gbps
    athrs17_reg_write(0x624 , 0x007f7f7f);
    printf ("Vlan config...\n");
    vlan_config();
#else
    athrs17_reg_write(0x624 , 0x003f3f3f);
    athrs17_reg_write(0x4   , 0x07500000);
    athrs17_reg_write(0xc   , 0x01000000);
#endif
    athrs17_reg_write(0x10  , 0x4000000);
    athrs17_reg_write(0x7c  , 0x000000fe); // 1gbps
    //athrs17_reg_write(0x7c  , 0x0000007d); // 100 mbps
    //athrs17_reg_write(0x7c  , 0x0000007c); // 10 mbps

    phyBase = 0;
#ifdef ATH_S17_MAC0_SGMII
    phyAddr = 4;
#else
    phyAddr = 0;
#endif
    // To enable loopback on single phy
    phy_reg_write(0, phyAddr, 0x0, 0xc140);
    for(rddata=0; rddata<1000; rddata++);
    phy_reg_write(0, phyAddr, 0x0, 0x4140);
    for(rddata=0; rddata<1000; rddata++);
    rddata = phy_reg_read(0, phyAddr, 0x0);
#ifdef DEBUG
    printf("s17 phy0 register value 0x%08x\n", rddata);
#endif
    // power down other phys
#ifdef ATH_S17_MAC0_SGMII
    phy_reg_write(0, 0x0, 0x0, 0x8800);
#else
    phy_reg_write(0, 0x4, 0x0, 0x8800);
#endif
    phy_reg_write(0, 0x1, 0x0, 0x8800);
    phy_reg_write(0, 0x2, 0x0, 0x8800);
    phy_reg_write(0, 0x3, 0x0, 0x8800);
    /* For 100M waveform */
    phy_reg_write(0, phyAddr, 0x1d, 0x18);
    phy_reg_write(0, phyAddr, 0x1e, 0x02ea);
    /* Turn On Gigabit Clock */
    phy_reg_write(0, phyAddr, 0x1d, 0x3d);
    phy_reg_write(0, phyAddr, 0x1e, 0x48a0);

    /* Enable flow control */
    s17_reg_rmw(0x80,0x30);
    s17_reg_rmw(0x84,0x30);
    s17_reg_rmw(0x88,0x30);
    s17_reg_rmw(0x8c,0x30);
    s17_reg_rmw(0x90,0x30);
}

#endif /* #ifdef RGMII_CAL */
