/*
 * Copyright (C) 2001 Gerald Van Baren, Custom IDEAS, vanbaren@cideas.com.
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2018 Julien Dusser <julien.dusser@free.fr>
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * This provides a bit-banged interface to the ethernet MII management
 * channel for QCA devices.
 */

#include <config.h>
#include <common.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

#define MII_INIT	do{qca_soc_reg_read_clear(QCA_GPIO_OE_REG,1<<CONFIG_QCA_GPIO_MDC);}while(0)
#define MDIO_ACTIVE	do{qca_soc_reg_read_clear(QCA_GPIO_OE_REG,1<<CONFIG_QCA_GPIO_MDIO);}while(0)
#define MDIO_TRISTATE	do{qca_soc_reg_read_set(QCA_GPIO_OE_REG,1<<CONFIG_QCA_GPIO_MDIO);}while(0)
#define MDIO_READ	(!!(qca_soc_reg_read(QCA_GPIO_IN_REG)&(1<<CONFIG_QCA_GPIO_MDIO)))
#define MDIO(v)		do{if(v) qca_soc_reg_read_set(QCA_GPIO_OUT_REG,1<<CONFIG_QCA_GPIO_MDIO); else qca_soc_reg_read_clear(QCA_GPIO_OUT_REG,1<<CONFIG_QCA_GPIO_MDIO);}while(0)
#define MDC(v)		do{if(v) qca_soc_reg_read_set(QCA_GPIO_OUT_REG,1<<CONFIG_QCA_GPIO_MDC); else qca_soc_reg_read_clear(QCA_GPIO_OUT_REG,1<<CONFIG_QCA_GPIO_MDC);}while(0)
#define MIIDELAY	udelay(50);

enum {
  MIIPHYBB_WRITE = 0,
  MIIPHYBB_READ = 1
};

/*****************************************************************************
 *
 * Utility to send the preamble, address, and register (common to read
 * and write).
 */
static void miiphybb_preamble(char read, unsigned char addr, unsigned char reg)
{
	int j;			/* counter */

	/*
	 * Send a 32 bit preamble ('1's) with an extra '1' bit for good measure.
	 * The IEEE spec says this is a PHY optional requirement.  The AMD
	 * 79C874 requires one after power up and one after a MII communications
	 * error.  This means that we are doing more preambles than we need,
	 * but it is safer and will be much more robust.
	 */

	MDIO_ACTIVE;
	MDIO (1);
	for (j = 0; j < 32; j++) {
		MDC (0);
		MIIDELAY;
		MDC (1);
		MIIDELAY;
	}

	/* send the start bit (01) and the read opcode (10) or write (10) */
	MDC (0);
	MDIO (0);
	MIIDELAY;
	MDC (1);
	MIIDELAY;
	MDC (0);
	MDIO (1);
	MIIDELAY;
	MDC (1);
	MIIDELAY;
	MDC (0);
	MDIO (read);
	MIIDELAY;
	MDC (1);
	MIIDELAY;
	MDC (0);
	MDIO (!read);
	MIIDELAY;
	MDC (1);
	MIIDELAY;

	/* send the PHY address */
	for (j = 0; j < 5; j++) {
		MDC (0);
		if ((addr & 0x10) == 0) {
			MDIO (0);
		} else {
			MDIO (1);
		}
		MIIDELAY;
		MDC (1);
		MIIDELAY;
		addr <<= 1;
	}

	/* send the register address */
	for (j = 0; j < 5; j++) {
		MDC (0);
		if ((reg & 0x10) == 0) {
			MDIO (0);
		} else {
			MDIO (1);
		}
		MIIDELAY;
		MDC (1);
		MIIDELAY;
		reg <<= 1;
	}
}


/*****************************************************************************
 *
 * Read a MII PHY register.
 *
 * Returns:
 *   0 on success
 */
int bb_miiphy_read (char *devname, unsigned char addr,
		unsigned char reg, unsigned short *value)
{
	short rdreg;		/* register working value */
	int j;			/* counter */

	miiphybb_preamble(MIIPHYBB_READ, addr, reg);

	/* tri-state our MDIO I/O pin so we can read */
	MDC (0);
	MDIO_TRISTATE;
	MIIDELAY;
	MDC (1);
	MIIDELAY;

	/* check the turnaround bit: the PHY should be driving it to zero */
	if (MDIO_READ != 0) {
		/* puts ("PHY didn't drive TA low\n"); */
		for (j = 0; j < 32; j++) {
			MDC (0);
			MIIDELAY;
			MDC (1);
			MIIDELAY;
		}
		return (-1);
	}

	MDC (0);
	MIIDELAY;

	/* read 16 bits of register data, MSB first */
	rdreg = 0;
	for (j = 0; j < 16; j++) {
		MDC (1);
		MIIDELAY;
		rdreg <<= 1;
		rdreg |= MDIO_READ;
		MDC (0);
		MIIDELAY;
	}

	/* Fix end of communication on QCA */
	MDIO_ACTIVE;
	MDIO(1);
	MDC(0);
	MIIDELAY;
	MDC(1);
	MIIDELAY;
	
	MDIO(0);
	MDC(0);
	MIIDELAY;

	*value = rdreg;


	return 0;
}


/*****************************************************************************
 *
 * Write a MII PHY register.
 *
 * Returns:
 *   0 on success
 */
int bb_miiphy_write (char *devname, unsigned char addr,
		unsigned char reg, unsigned short value)
{
	int j;			/* counter */

	miiphybb_preamble(MIIPHYBB_WRITE, addr, reg);

	/* send the turnaround (10) */
	MDC (0);
	MDIO (1);
	MIIDELAY;
	MDC (1);
	MIIDELAY;
	MDC (0);
	MDIO (0);
	MIIDELAY;
	MDC (1);
	MIIDELAY;

	/* write 16 bits of register data, MSB first */
	for (j = 0; j < 16; j++) {
		MDC (0);
		if ((value & 0x00008000) == 0) {
			MDIO (0);
		} else {
			MDIO (1);
		}
		MIIDELAY;
		MDC (1);
		MIIDELAY;
		value <<= 1;
	}

	/* Fix end of communication on QCA */
	MDIO(0);
	MDC(0);
	MIIDELAY;

	return 0;
}
