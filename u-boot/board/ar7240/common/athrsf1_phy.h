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

#ifndef _ATHRS26_RGMII_H
#define _ATHRS26_RGMII_H
#define BOOL int
#include "athr_s27_phy.h"
int athr_phy_is_up(int unit);
int athr_phy_is_fdx(int unit,int phyUnit);
int athr_phy_speed(int unit,int phyUnit);
BOOL athr_phy_setup(int unit);
BOOL athr_phy_is_link_alive(int phyUnit);
#endif
