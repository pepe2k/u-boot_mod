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

#ifndef _QCA_ETH_955x_PHY_H
#define _QCA_ETH_955x_PHY_H
#include <miiphy.h>


#ifdef CONFIG_ATHR_8033_PHY
extern int athr_ar8033_reg_init(int ethUnit);
extern int athr_ar8033_phy_setup(int ethUnit);
extern int athr_ar8033_phy_is_up(int ethUnit);
extern int athr_ar8033_phy_is_fdx(int ethUnit);
extern int athr_ar8033_phy_speed(int ethUnit);
#endif

#ifdef CONFIG_ATHRS17_PHY
extern int athrs17_phy_setup(int ethUnit);
extern int athrs17_phy_is_up(int ethUnit);
extern int athrs17_phy_is_fdx(int ethUnit);
extern int athrs17_phy_speed(int ethUnit);
#endif

#ifdef CFG_ATHRS26_PHY
extern int athrs26_phy_setup(int ethUnit);
extern int athrs26_phy_is_up(int ethUnit);
extern int athrs26_phy_is_fdx(int ethUnit);
extern int athrs26_phy_speed(int ethUnit);
#endif

#ifdef CFG_ATHRS27_PHY
extern int athrs27_phy_setup(int ethUnit);
extern int athrs27_phy_is_up(int ethUnit);
extern int athrs27_phy_is_fdx(int ethUnit);
extern int athrs27_phy_speed(int ethUnit);
#endif
 
static inline void ath_gmac_phy_setup(int unit)
{
#ifdef CONFIG_ATHRS17_PHY
		if (unit == 0) {
			athrs17_phy_setup(unit);
		} else
#endif
		{
#ifdef CFG_ATHRS26_PHY
        		athrs26_phy_setup(unit);
#endif

#ifdef CFG_ATHRS27_PHY
        		athrs27_phy_setup(unit);
#endif

#ifdef CONFIG_VIR_PHY
			athr_vir_phy_setup(unit);
#endif
#if defined(CONFIG_ATHRS17_PHY) && !defined (CFG_DUAL_PHY_SUPPORT)
			athrs17_phy_setup(unit);
#endif

#ifdef CONFIG_ATHR_8033_PHY
                        athr_ar8033_phy_setup(unit);
#endif
		}
}

static inline void ath_gmac_phy_link(int unit, int *link)
{
#ifdef CONFIG_ATHRS17_PHY
		if (unit == 0) {
			*link = athrs17_phy_is_up(unit);
		} else
#endif
		{
#ifdef CFG_ATHRS26_PHY
         		*link = athrs26_phy_is_up(unit);
#endif
#ifdef CFG_ATHRS27_PHY
         		*link = athrs27_phy_is_up(unit);
#endif

#ifdef CONFIG_VIR_PHY
			*link = athr_vir_phy_is_up(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*link = athr_ar8033_phy_is_up(unit);
#endif
#if defined(CONFIG_ATHRS17_PHY) && !defined (CFG_DUAL_PHY_SUPPORT)
			*link = athrs17_phy_is_up(unit);
#endif

		}
}

static inline void ath_gmac_phy_duplex(int unit, int *duplex)
{
#ifdef CONFIG_ATHRS17_PHY
		if (unit == 0) {
			*duplex = athrs17_phy_is_fdx(unit);
		} else
#endif
		{
#ifdef CFG_ATHRS26_PHY
			*duplex = athrs26_phy_is_fdx(unit);
#endif
#ifdef CFG_ATHRS27_PHY
			*duplex = athrs27_phy_is_fdx(unit);
#endif

#ifdef CONFIG_VIR_PHY
			*duplex = athr_vir_phy_is_fdx(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*duplex = athr_ar8033_phy_is_fdx(unit);
#endif
#if defined(CONFIG_ATHRS17_PHY) && !defined(CFG_DUAL_PHY_SUPPORT)
			*duplex = athrs17_phy_is_fdx(unit);
#endif
		}
}

static inline void ath_gmac_phy_speed(int unit, int *speed)
{
#ifdef CONFIG_ATHRS17_PHY
		if (unit == 0) {
			*speed = _1000BASET;
		} else
#endif
		{
#ifdef CFG_ATHRS26_PHY
			*speed = athrs26_phy_speed(unit);
#endif
#ifdef CFG_ATHRS27_PHY
			*speed = athrs27_phy_speed(unit);
#endif

#ifdef CONFIG_VIR_PHY
			*speed = athr_vir_phy_speed(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*speed = athr_ar8033_phy_speed(unit);
#endif

#if defined(CONFIG_ATHRS17_PHY) && !defined (CFG_DUAL_PHY_SUPPORT)
			*speed = _1000BASET;
#endif
		}
}

#endif /* _QCA_ETH_955x_PHY_H */
