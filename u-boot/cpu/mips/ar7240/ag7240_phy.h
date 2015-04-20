#ifndef _AG7240_PHY_H
#define _AG7240_PHY_H

extern int athrs16_phy_is_up(int unit);
extern int athrs16_phy_is_fdx(int unit);
extern int athrs16_phy_speed(int unit);
extern int athrs16_phy_setup(int unit);

extern int athrs26_phy_is_up(int unit);
extern int athrs26_phy_speed(int unit);
extern int athrs26_phy_setup(int unit);
extern int athrs26_phy_is_fdx(int unit);

static inline void ag7240_phy_setup(int unit) {
#ifdef CONFIG_AR7242_S16_PHY
	if ((is_ar7242() || is_wasp()) && (unit==0)) {
		athrs16_phy_setup(unit);
	} else
#endif
	{
		athrs26_phy_setup(unit);
#ifdef CONFIG_F1E_PHY
		athr_phy_setup(unit);
#endif
	}
}

static inline void ag7240_phy_link(int unit, int *link) {
#ifdef CONFIG_AR7242_S16_PHY
	if ((is_ar7242() || is_wasp()) && (unit==0)) {
		*link = athrs16_phy_is_up(unit);
	} else
#endif
	{
		*link = athrs26_phy_is_up(unit);
#ifdef CONFIG_F1E_PHY
		*link = athr_phy_is_up(unit);
#endif
	}
}

static inline void ag7240_phy_duplex(int unit, int *duplex) {
#ifdef CONFIG_AR7242_S16_PHY
	if ((is_ar7242() || is_wasp()) && (unit==0)) {
		*duplex = athrs16_phy_is_fdx(unit);
	} else
#endif
	{
		*duplex = athrs26_phy_is_fdx(unit);
#ifdef CONFIG_F1E_PHY
		*duplex = athr_phy_is_fdx(unit);
#endif
	}
}

static inline void ag7240_phy_speed(int unit, int *speed) {
#ifdef CONFIG_AR7242_S16_PHY
	if ((is_ar7242() || is_wasp()) && (unit==0)) {
		*speed = athrs16_phy_speed(unit);
	} else
#endif
	{
		*speed = athrs26_phy_speed(unit);
#ifdef CONFIG_F1E_PHY
		*speed = athr_phy_speed(unit);
#endif
	}
}

#endif /*_AG7240_PHY_H*/
