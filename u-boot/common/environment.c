/*
 * (C) Copyright 2001
 * Erik Theisen,  Wave 7 Optics, etheisen@mindspring.com.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* Dirty trick to get only #defines */
#ifndef __ASSEMBLY__
	#define __ASSEMBLY__
#endif

/* Don't include asm/processor */
#define __ASM_STUB_PROCESSOR_H__

#include <config.h>

#undef __ASSEMBLY__
#include <environment.h>
#include <env_scripts.h>

/*
 * Handle HOSTS that have prepended
 * crap on symbol names, not TARGETS.
 */
#if defined(__APPLE__)
	/* Leading underscore on symbols */
	#define SYM_CHAR "_"
#else
	/* No leading character on symbols */
	#define SYM_CHAR
#endif

/*
 * Generate embedded environment table
 * inside U-Boot image, if needed.
 */
#if defined(ENV_IS_EMBEDDED)
/*
 * Only put the environment in it's own section when we are building
 * U-Boot proper.  The host based program "tools/envcrc" does not need
 * a seperate section.  Note that ENV_CRC is only defined when building
 * U-Boot itself.
 */
#if (defined(CONFIG_CMI)      ||\
     defined(CONFIG_FADS)     ||\
     defined(CONFIG_HYMOD)    ||\
     defined(CONFIG_ICU862)   ||\
     defined(CONFIG_R360MPI)  ||\
     defined(CONFIG_TQM8xxL)  ||\
     defined(CONFIG_RRVISION) ||\
     defined(CONFIG_TRAB)     ||\
     defined(CONFIG_PPCHAMELEONEVB) \
    ) && defined(ENV_CRC) /* Environment embedded in U-Boot .ppcenv section */

	/* XXX - This only works with GNU C */
	#define __PPCENV__ __attribute__ ((section(".ppcenv")))
	#define __PPCTEXT__ __attribute__ ((section(".text")))

#elif defined(USE_HOSTCC) /* Native for 'tools/envcrc' */

	#define __PPCENV__ /*XXX DO_NOT_DEL_THIS_COMMENT*/
	#define __PPCTEXT__ /*XXX DO_NOT_DEL_THIS_COMMENT*/

#else /* Environment is embedded in U-Boot's .text section */

	/* XXX - This only works with GNU C */
	#define __PPCENV__ __attribute__ ((section(".text")))
	#define __PPCTEXT__ __attribute__ ((section(".text")))

#endif

/*
 * Macros to generate global absolutes.
 */
#define GEN_SYMNAME(str) SYM_CHAR #str
#define GEN_VALUE(str) #str
#define GEN_ABS(name, value) \
		asm (".globl " GEN_SYMNAME(name)); \
		asm (GEN_SYMNAME(name) " = " GEN_VALUE(value))

/*
 * Macros to transform values
 * into environment strings.
 */
#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)

/*
 * Check to see if we are building with a
 * computed CRC.  Otherwise define it as ~0.
 */
#if !defined(ENV_CRC)
	#define ENV_CRC	~0
#endif

env_t environment __PPCENV__ = {
	ENV_CRC,	/* CRC Sum */
#if defined(CFG_REDUNDAND_ENVIRONMENT)
	1,		/* Flags: valid */
#endif
	{
#if defined(CONFIG_BOOTARGS)
		"bootargs=" CONFIG_BOOTARGS "\0"
#endif
#if defined(CONFIG_BOOTCOMMAND)
		"bootcmd=" CONFIG_BOOTCOMMAND "\0"
#endif
#if defined(CONFIG_AUTOBOOT_STOP_STR)
		"bootstopkey=" CONFIG_AUTOBOOT_STOP_STR "\0"
#endif
#if defined(CONFIG_RAMBOOTCOMMAND)
		"ramboot=" CONFIG_RAMBOOTCOMMAND "\0"
#endif
#if defined(CONFIG_NFSBOOTCOMMAND)
		"nfsboot=" CONFIG_NFSBOOTCOMMAND "\0"
#endif
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
		"bootdelay=" MK_STR(CONFIG_BOOTDELAY) "\0"
#endif
#if defined(CONFIG_BAUDRATE) && (CONFIG_BAUDRATE >= 0)
		"baudrate=" MK_STR(CONFIG_BAUDRATE) "\0"
#endif
#if defined(CONFIG_LOADS_ECHO)
		"loads_echo=" MK_STR(CONFIG_LOADS_ECHO) "\0"
#endif
#if defined(CONFIG_ETHADDR)
		"ethaddr=" MK_STR(CONFIG_ETHADDR) "\0"
#endif
#if defined(CONFIG_ETH1ADDR)
		"eth1addr=" MK_STR(CONFIG_ETH1ADDR) "\0"
#endif
#if defined(CONFIG_ETH2ADDR)
		"eth2addr=" MK_STR(CONFIG_ETH2ADDR) "\0"
#endif
#if defined(CONFIG_ETH3ADDR)
		"eth3addr=" MK_STR(CONFIG_ETH3ADDR) "\0"
#endif
#if defined(CONFIG_ETHPRIME)
		"ethprime=" CONFIG_ETHPRIME "\0"
#endif
#if defined(CONFIG_IPADDR)
		"ipaddr=" MK_STR(CONFIG_IPADDR) "\0"
#endif
#if defined(CONFIG_SERVERIP)
		"serverip=" MK_STR(CONFIG_SERVERIP) "\0"
#endif
#if defined(CONFIG_AUTOLOAD)
		"autoload=" MK_STR(CONFIG_AUTOLOAD) "\0"
#endif
#if defined(CONFIG_ROOTPATH)
		"rootpath=" MK_STR(CONFIG_ROOTPATH) "\0"
#endif
#if defined(CONFIG_GATEWAYIP)
		"gatewayip=" MK_STR(CONFIG_GATEWAYIP) "\0"
#endif
#if defined(CONFIG_NETMASK)
		"netmask=" MK_STR(CONFIG_NETMASK) "\0"
#endif
#if defined(CONFIG_HOSTNAME)
		"hostname=" MK_STR(CONFIG_HOSTNAME) "\0"
#endif
#if defined(CONFIG_BOOTFILE)
		"bootfile=" MK_STR(CONFIG_BOOTFILE) "\0"
#endif
#if defined(CONFIG_LOADADDR)
		"loadaddr=" MK_STR(CONFIG_LOADADDR) "\0"
#endif
#if defined(CONFIG_NETCONSOLE_PORT)
		"ncport=" MK_STR(CONFIG_NETCONSOLE_PORT) "\0"
#endif
#if defined(CONFIG_CLOCKS_IN_MHZ)
		"clocks_in_mhz=1\0"
#endif
#if defined(CONFIG_PCI_BOOTDELAY) && (CONFIG_PCI_BOOTDELAY > 0)
		"pcidelay=" MK_STR(CONFIG_PCI_BOOTDELAY) "\0"
#endif
#if defined(CONFIG_LSDK_KERNEL)
		"lsdk_kernel=1\0"
#endif
#if defined(CONFIG_EXTRA_ENV_SETTINGS)
		CONFIG_EXTRA_ENV_SETTINGS
#endif
#if defined(CONFIG_ENV_UPG_SCRIPTS_UBOOT)
		CONFIG_ENV_UPG_SCRIPTS_UBOOT
#endif
#if defined(CONFIG_ENV_UPG_SCRIPTS_FW)
		CONFIG_ENV_UPG_SCRIPTS_FW
#endif
#if defined(CONFIG_ENV_BTN_RECOVERY_SCRIPT)
		CONFIG_ENV_BTN_RECOVERY_SCRIPT
#endif
	"\0"
	}
};

#if defined(CFG_ENV_ADDR_REDUND)
env_t redundand_environment __PPCENV__ = {
	0,	/* CRC Sum: invalid */
	0,	/* Flags:   invalid */
	{
		"\0"
	}
};
#endif /* CFG_ENV_ADDR_REDUND */

/*
 * These will end up in the .text section
 * if the environment strings are embedded
 * in the image.  When this is used for
 * tools/envcrc, they are placed in the
 * .data/.sdata section.
 */
unsigned long env_size __PPCTEXT__ = sizeof(env_t);

/* Add in absolutes */
GEN_ABS(env_offset, CFG_ENV_OFFSET);

#endif /* ENV_IS_EMBEDDED */
