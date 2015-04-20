#ifndef _ATHRS17_PHY_H
#define _ATHRS17_PHY_H

/*****************/
/* PHY Registers */
/*****************/
#define ATHR_PHY_CONTROL					0
#define ATHR_PHY_STATUS						1
#define ATHR_PHY_ID1						2
#define ATHR_PHY_ID2						3
#define ATHR_AUTONEG_ADVERT					4
#define ATHR_LINK_PARTNER_ABILITY			5
#define ATHR_AUTONEG_EXPANSION				6
#define ATHR_NEXT_PAGE_TRANSMIT				7
#define ATHR_LINK_PARTNER_NEXT_PAGE			8
#define ATHR_1000BASET_CONTROL				9
#define ATHR_1000BASET_STATUS				10
#define ATHR_PHY_SPEC_CONTROL				16
#define ATHR_PHY_SPEC_STATUS				17
#define ATHR_DEBUG_PORT_ADDRESS				29
#define ATHR_DEBUG_PORT_DATA				30

/* ATHR_PHY_CONTROL fields */
#define ATHR_CTRL_SOFTWARE_RESET			0x8000
#define ATHR_CTRL_SPEED_LSB					0x2000
#define ATHR_CTRL_AUTONEGOTIATION_ENABLE	0x1000
#define ATHR_CTRL_RESTART_AUTONEGOTIATION	0x0200
#define ATHR_CTRL_SPEED_FULL_DUPLEX			0x0100
#define ATHR_CTRL_SPEED_MSB					0x0040

#define ATHR_RESET_DONE(phy_control)		(((phy_control) & (ATHR_CTRL_SOFTWARE_RESET)) == 0)
    
/* Phy status fields */
#define ATHR_STATUS_AUTO_NEG_DONE			0x0020
#define ATHR_AUTONEG_DONE(ip_phy_status)	(((ip_phy_status) & (ATHR_STATUS_AUTO_NEG_DONE)) == (ATHR_STATUS_AUTO_NEG_DONE))

/* Link Partner ability */
#define ATHR_LINK_100BASETX_FULL_DUPLEX		0x0100
#define ATHR_LINK_100BASETX					0x0080
#define ATHR_LINK_10BASETX_FULL_DUPLEX		0x0040
#define ATHR_LINK_10BASETX					0x0020

/* Advertisement register. */
#define ATHR_ADVERTISE_NEXT_PAGE			0x8000
#define ATHR_ADVERTISE_ASYM_PAUSE			0x0800
#define ATHR_ADVERTISE_PAUSE				0x0400
#define ATHR_ADVERTISE_100FULL				0x0100
#define ATHR_ADVERTISE_100HALF				0x0080  
#define ATHR_ADVERTISE_10FULL				0x0040  
#define ATHR_ADVERTISE_10HALF				0x0020  

#define ATHR_ADVERTISE_ALL (ATHR_ADVERTISE_ASYM_PAUSE | ATHR_ADVERTISE_PAUSE | \
                            ATHR_ADVERTISE_10HALF | ATHR_ADVERTISE_10FULL | \
                            ATHR_ADVERTISE_100HALF | ATHR_ADVERTISE_100FULL)
                       
/* 1000BASET_CONTROL */
#define ATHR_ADVERTISE_1000FULL				0x0200

/* Phy Specific status fields */
#define ATHER_STATUS_LINK_MASK				0xC000
#define ATHER_STATUS_LINK_SHIFT				14
#define ATHER_STATUS_FULL_DEPLEX			0x2000
#define ATHR_STATUS_LINK_PASS				0x0400 
#define ATHR_STATUS_RESOVLED				0x0800

/*phy debug port register */
#define ATHER_DEBUG_SERDES_REG				5

/* Serdes debug fields */
#define ATHER_SERDES_BEACON					0x0100

/* S17 CSR Registers */
#define S17_ENABLE_CPU_BROADCAST			(1 << 26)
#define S17_PHY_LINK_CHANGE_REG				0x4
#define S17_PHY_LINK_UP						0x400
#define S17_PHY_LINK_DOWN					0x800
#define S17_PHY_LINK_DUPLEX_CHANGE			0x2000
#define S17_PHY_LINK_SPEED_CHANGE			0x4000
#define S17_PHY_LINK_INTRS					(PHY_LINK_UP | PHY_LINK_DOWN | PHY_LINK_DUPLEX_CHANGE | PHY_LINK_SPEED_CHANGE)

#ifdef CONFIG_AR7242_S17_PHY
#undef HEADER_REG_CONF
#undef HEADER_EN
#endif

void	athrs17_reg_init(void);
int		athrs17_phy_is_up(int unit);
int		athrs17_phy_is_fdx(int unit);
int		athrs17_phy_speed(int unit);
int		athrs17_phy_setup(int unit);

#endif
