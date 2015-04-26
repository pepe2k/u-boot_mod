#ifndef _PHY_H
#define _PHY_H

#include <config.h>
/*
 * This file defines the interface between MAC and various phy switches.
 */
extern int ag7240_miiphy_read(char *devname, uint32_t phaddr, uint8_t reg);
extern int ag7240_miiphy_write(char *devname, uint32_t phaddr, uint8_t reg, uint16_t data);

#define ag7240_unit2name(_unit)					_unit ?  "eth1" : "eth0"
#define phy_reg_read(base, addr, reg)			ag7240_miiphy_read(ag7240_unit2name(base), addr, reg)
#define phy_reg_write(base, addr, reg, data)	ag7240_miiphy_write(ag7240_unit2name(base), addr, reg, data)

#endif /* ifndef _PHY_H */
