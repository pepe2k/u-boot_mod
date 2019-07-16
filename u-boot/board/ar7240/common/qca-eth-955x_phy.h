/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
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
 *
 */

#ifndef _QCA_ETH_955X_PHY_H
#define _QCA_ETH_955X_PHY_H
#include <miiphy.h>

#ifdef CONFIG_ATHR_8033_PHY
extern int athrs_ar8033_reg_init(int ethUnit);
extern int athrs_ar8033_phy_setup(int ethUnit);
extern int athrs_ar8033_phy_is_up(int ethUnit);
extern int athrs_ar8033_phy_is_fdx(int ethUnit);
extern int athrs_ar8033_phy_speed(int ethUnit);
#endif

#ifdef CONFIG_ATHRS17_PHY
extern int athrs17_phy_setup(int ethUnit);
extern int athrs17_phy_is_up(int ethUnit);
extern int athrs17_phy_is_fdx(int ethUnit);
extern int athrs17_phy_speed(int ethUnit);
#endif

static inline void ath_gmac_phy_setup(int unit)
{
#ifdef CONFIG_ATHRS17_PHY
		if (unit == 0) {
			athrs17_phy_setup(unit);
		} else
#endif
		{
#ifdef CONFIG_VIR_PHY
			athr_vir_phy_setup(unit);
#endif
#if defined(CONFIG_ATHRS17_PHY) && !defined (CFG_DUAL_PHY_SUPPORT)
			athrs17_phy_setup(unit);
#endif

#ifdef CONFIG_ATHR_8033_PHY
                        athrs_ar8033_phy_setup(unit);
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
#ifdef CONFIG_VIR_PHY
			*link = athr_vir_phy_is_up(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*link = athrs_ar8033_phy_is_up(unit);
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
#ifdef CONFIG_VIR_PHY
			*duplex = athr_vir_phy_is_fdx(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*duplex = athrs_ar8033_phy_is_fdx(unit);
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
#ifdef CONFIG_VIR_PHY
			*speed = athr_vir_phy_speed(unit);
#endif
#ifdef CONFIG_ATHR_8033_PHY
			*speed = athrs_ar8033_phy_speed(unit);
#endif

#if defined(CONFIG_ATHRS17_PHY) && !defined (CFG_DUAL_PHY_SUPPORT)
			*speed = _1000BASET;
#endif
		}
}

#endif /* _QCA_ETH_955X_PHY_H */
