/*
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 *
 * (C) Copyright 2002, 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 * PCI routines
 */
#include <common.h>

#ifdef CONFIG_PCI

#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <pci.h>

void pci_init(void) {
#if defined(CONFIG_PCI_BOOTDELAY)
	char *s;
	int i;

	/* wait "pcidelay" ms (if defined)... */
	s = getenv ("pcidelay");
	
	if (s) {
		int val = simple_strtoul(s, NULL, 10);
		
		for (i = 0; i < val; i++){
			udelay (1000);
		}
	}
#endif /* CONFIG_PCI_BOOTDELAY */

	/* now call board specific pci_init()... */
	pci_init_board();
}

#endif /* CONFIG_PCI */
