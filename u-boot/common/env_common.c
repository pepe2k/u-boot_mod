/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>

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

#include <common.h>
#include <command.h>
#include <environment.h>
#include <env_scripts.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <tinf.h>

DECLARE_GLOBAL_DATA_PTR;

#undef DEBUG_ENV

#if defined(DEBUG_ENV)
	#define DEBUGF(fmt,args...) printf(fmt ,##args)
#else
	#define DEBUGF(fmt,args...)
#endif

extern env_t *env_ptr;

extern void env_relocate_spec(void);
extern uchar env_get_char_spec(int);

static uchar env_get_char_init(int index);
uchar (*env_get_char)(int) = env_get_char_init;

/************************************************************************
 * Default settings to be used when no valid environment is found
 */
#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)

uchar default_environment[] = {
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
#if defined(CONFIG_CLOCKS_IN_MHZ)
	"clocks_in_mhz=1\0"
#endif
#if defined(CONFIG_PCI_BOOTDELAY) && (CONFIG_PCI_BOOTDELAY > 0)
	"pcidelay=" MK_STR(CONFIG_PCI_BOOTDELAY) "\0"
#endif
#if defined(CONFIG_NETCONSOLE_PORT)
	"ncport=" MK_STR(CONFIG_NETCONSOLE_PORT) "\0"
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
};

/* Environment is in Nand Flash */
#if defined(CFG_ENV_IS_IN_NAND)
int default_environment_size = sizeof(default_environment);
#endif

void env_crc_update(void)
{
	env_ptr->crc = tinf_crc32(env_ptr->data, ENV_SIZE);
}

static uchar env_get_char_init(int index)
{
	uchar c;

	/* if crc was bad, use the default environment */
	if (gd->env_valid)
		c = env_get_char_spec(index);
	else
		c = default_environment[index];

	return c;
}

uchar env_get_char_memory(int index)
{
	if (gd->env_valid)
		return *((uchar *)(gd->env_addr + index));
	else
		return default_environment[index];
}

uchar *env_get_addr(int index)
{
	if (gd->env_valid)
		return ((uchar *)(gd->env_addr + index));
	else
		return &default_environment[index];
}

void env_relocate(void)
{
	DEBUGF("%s[%d] offset = 0x%lx\n", __FUNCTION__,__LINE__, gd->reloc_off);

#if defined(ENV_IS_EMBEDDED)
	/*
	 * The environment buffer is embedded with the text segment,
	 * just relocate the environment pointer
	 */
	env_ptr = (env_t *)((ulong)env_ptr + gd->reloc_off);
	DEBUGF("%s[%d] embedded ENV at %p\n", __FUNCTION__,__LINE__,env_ptr);
#else
	/* We must allocate a buffer for the environment */
	env_ptr = (env_t *)malloc(CFG_ENV_SIZE);
	DEBUGF("%s[%d] malloced ENV at %p\n", __FUNCTION__,__LINE__,env_ptr);
#endif

	/* After relocation to RAM, we can always use the "memory" functions */
	env_get_char = env_get_char_memory;

	if (gd->env_valid == 0) {
#if !defined(CFG_ENV_IS_NOWHERE)
		printf_wrn("bad env CRC, using default,\n"
			   "   use 'saveenv' to save it in FLASH\n\n");
#endif

		if (sizeof(default_environment) > ENV_SIZE) {
			printf_err("default env is too big!\n");
			return;
		}

		memset(env_ptr, 0, sizeof(env_t));
		memcpy(env_ptr->data, default_environment,
			sizeof(default_environment));

#if defined(CFG_REDUNDAND_ENVIRONMENT)
		env_ptr->flags = 0xFF;
#endif

		env_crc_update();
		gd->env_valid = 1;
	} else {
		env_relocate_spec();
	}

	gd->env_addr = (ulong)&(env_ptr->data);
}
