/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
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
 */


#include <config.h>
#include <linux/types.h>
#include <common.h>
#include <miiphy.h>
#include "phy.h"
#include <asm/addrspace.h>
#include <atheros.h>
#include "athr_ar8033_phy.h"

int athr_ar8033_mgmt_init(int ethUnit)
{
	return bb_miiphy_write(NULL, CONFIG_MII_PHY_ADDR, 0x00, 0x9000);
}

int athr_ar8033_phy_setup(int ethUnit)
{
	return bb_miiphy_write(NULL, CONFIG_MII_PHY_ADDR, 0x00, 0x9000);
}

int athr_ar8033_phy_is_fdx(int ethUnit)
{
    unsigned short phy_hw_status;
    bb_miiphy_read(NULL, CONFIG_MII_PHY_ADDR, 0x11, &phy_hw_status);

    if ((phy_hw_status & (1<<13))>>13 == 1)
    {
        printf("Checking Duplex: Full\n");
        return 1;
    }
    printf("Checking Duplex: Half\n");

    return 0;
	
}


int athr_ar8033_phy_is_up(int ethUnit)
{
    unsigned short phy_hw_status;
    bb_miiphy_read(NULL, CONFIG_MII_PHY_ADDR, 0x11, &phy_hw_status);

    if ((phy_hw_status & (1<<10))>>10 == 1)
    {
        printf("Checking Link: Up\n");
        return 1;
    }
    printf("Checking Link: Down\n");
    return 0;
}

int athr_ar8033_phy_speed(int ethUnit)
{
    unsigned short phy_hw_status = (3 << 14), speed;
    bb_miiphy_read(NULL, CONFIG_MII_PHY_ADDR, 0x11, &phy_hw_status);
    speed = (phy_hw_status & (3<<14)) >> 14;

    switch (speed) {
         case 0:
                 printf("Checking Speed 10BaseT\n");
                 return _10BASET;
                 break;
         case 1:
                 printf("Checking Speed 100BaseT\n");
                 return _100BASET;
                 break;
         case 2:
                 printf("Checking Speed 1000BaseT\n");
                 return _1000BASET;
                 break;
         default:
                 printf("Checking Speed Unknown\n");
                 return -1;
                 break;
    }

    return -1;
}

int athr_ar8033_reg_init(int ethUnit)
{
    return athr_ar8033_mgmt_init(ethUnit);
}
