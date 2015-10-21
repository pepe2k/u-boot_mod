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

/* #define DEBUG */

#include <common.h>

#if defined(CFG_ENV_IS_IN_FLASH) /* Environment is in Flash */

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <tinf.h>

DECLARE_GLOBAL_DATA_PTR;

#if ((CONFIG_COMMANDS & (CFG_CMD_ENV | CFG_CMD_FLASH)) == (CFG_CMD_ENV | CFG_CMD_FLASH))
	#define CMD_SAVEENV
#elif defined(CFG_ENV_ADDR_REDUND)
	#error Cannot use CFG_ENV_ADDR_REDUND without CFG_CMD_ENV & CFG_CMD_FLASH
#endif

#if defined(CFG_ENV_SIZE_REDUND) && (CFG_ENV_SIZE_REDUND < CFG_ENV_SIZE)
	#error CFG_ENV_SIZE_REDUND should not be less then CFG_ENV_SIZE
#endif

const char *env_name_spec = "FLASH";

#ifdef ENV_IS_EMBEDDED

extern uchar environment[];
env_t *env_ptr = (env_t *)(&environment[0]);

#ifdef CMD_SAVEENV
/* static env_t *flash_addr = (env_t *)(&environment[0]);-broken on ARM-wd-*/
static env_t *flash_addr = (env_t *)CFG_ENV_ADDR;
#endif

#else /* ! ENV_IS_EMBEDDED */

env_t *env_ptr = (env_t *)CFG_ENV_ADDR;

#ifdef CMD_SAVEENV
static env_t *flash_addr = (env_t *)CFG_ENV_ADDR;
#endif

#endif /* ENV_IS_EMBEDDED */

#ifdef CFG_ENV_ADDR_REDUND
static env_t *flash_addr_new = (env_t *)CFG_ENV_ADDR_REDUND;

/* CFG_ENV_ADDR is supposed to be on sector boundary */
static ulong end_addr = CFG_ENV_ADDR + CFG_ENV_SECT_SIZE - 1;
static ulong end_addr_new = CFG_ENV_ADDR_REDUND + CFG_ENV_SECT_SIZE - 1;

#define ACTIVE_FLAG   1
#define OBSOLETE_FLAG 0
#endif /* CFG_ENV_ADDR_REDUND */

extern uchar default_environment[];
extern int default_environment_size;

uchar env_get_char_spec(int index){
	return(*((uchar *)(gd->env_addr + index)));
}

#ifdef CFG_ENV_ADDR_REDUND

int env_init(void){
	int crc1_ok = 0, crc2_ok = 0;

	uchar flag1 = flash_addr->flags;
	uchar flag2 = flash_addr_new->flags;

	ulong addr_default = (ulong)&default_environment[0];
	ulong addr1 = (ulong)&(flash_addr->data);
	ulong addr2 = (ulong)&(flash_addr_new->data);

	crc1_ok = (tinf_crc32(flash_addr->data, ENV_SIZE) == flash_addr->crc);
	crc2_ok = (tinf_crc32(flash_addr_new->data, ENV_SIZE) == flash_addr_new->crc);

	if(crc1_ok && !crc2_ok){
		gd->env_addr  = addr1;
		gd->env_valid = 1;
	} else if(!crc1_ok && crc2_ok){
		gd->env_addr  = addr2;
		gd->env_valid = 1;
	} else if(!crc1_ok && !crc2_ok){
		gd->env_addr  = addr_default;
		gd->env_valid = 0;
	} else if(flag1 == ACTIVE_FLAG && flag2 == OBSOLETE_FLAG){
		gd->env_addr  = addr1;
		gd->env_valid = 1;
	} else if(flag1 == OBSOLETE_FLAG && flag2 == ACTIVE_FLAG){
		gd->env_addr  = addr2;
		gd->env_valid = 1;
	} else if(flag1 == flag2){
		gd->env_addr  = addr1;
		gd->env_valid = 2;
	} else if(flag1 == 0xFF){
		gd->env_addr  = addr1;
		gd->env_valid = 2;
	} else if(flag2 == 0xFF){
		gd->env_addr  = addr2;
		gd->env_valid = 2;
	}

	return(0);
}

#ifdef CMD_SAVEENV
int saveenv(void){
	char *saved_data = NULL;
	int rc = 1;
	char flag = OBSOLETE_FLAG, new_flag = ACTIVE_FLAG;
#if CFG_ENV_SECT_SIZE > CFG_ENV_SIZE
	ulong up_data = 0;

	up_data = (end_addr_new + 1 - ((long)flash_addr_new + CFG_ENV_SIZE));

	if(up_data){
		if((saved_data = malloc(up_data)) == NULL){
			printf("## Error: unable to save the rest of sector (%ld)\n", up_data);
			goto Done;
		}

		memcpy(saved_data, (void *)((long)flash_addr_new + CFG_ENV_SIZE), up_data);
	}
#endif
	if(flash_sect_erase((ulong)flash_addr_new, end_addr_new)){
		goto Done;
	}

	if((rc = flash_write((char *)env_ptr->data, (ulong)&(flash_addr_new->data), sizeof(env_ptr->data))) ||
	   (rc = flash_write((char *)&(env_ptr->crc), (ulong)&(flash_addr_new->crc), sizeof(env_ptr->crc))) ||
	   (rc = flash_write(&flag, (ulong)&(flash_addr->flags), sizeof(flash_addr->flags))) ||
	   (rc = flash_write(&new_flag, (ulong)&(flash_addr_new->flags), sizeof(flash_addr_new->flags)))){
		flash_perror(rc);
		goto Done;
	}

#if CFG_ENV_SECT_SIZE > CFG_ENV_SIZE
	if(up_data){ /* restore the rest of sector */
		if(flash_write(saved_data, (long)flash_addr_new + CFG_ENV_SIZE, up_data)){
			flash_perror(rc);
			goto Done;
		}
	}
#endif
	env_t * etmp = flash_addr;
	ulong ltmp = end_addr;

	flash_addr = flash_addr_new;
	flash_addr_new = etmp;

	end_addr = end_addr_new;
	end_addr_new = ltmp;

	rc = 0;

Done:

	if(saved_data){
		free(saved_data);
	}

	return(rc);
}
#endif /* CMD_SAVEENV */

#else /* ! CFG_ENV_ADDR_REDUND */
int env_init(void){
	if(tinf_crc32(env_ptr->data, ENV_SIZE) == env_ptr->crc){
		gd->env_addr = (ulong)&(env_ptr->data);
		gd->env_valid = 1;

		return(0);
	}

	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 0;

	return(0);
}

#ifdef CMD_SAVEENV
int saveenv(void){
	int	len, rc;
	ulong end_addr, flash_sect_addr;
#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	ulong flash_offset;
	uchar env_buffer[CFG_ENV_SECT_SIZE];
#else
	uchar *env_buffer = (uchar *)env_ptr;
#endif /* CFG_ENV_SECT_SIZE */
	int rcode = 0;

#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)

	flash_offset    = ((ulong)flash_addr) & (CFG_ENV_SECT_SIZE-1);
	flash_sect_addr = ((ulong)flash_addr) & ~(CFG_ENV_SECT_SIZE-1);

	//debug("copy old content: sect_addr: %08lX  env_addr: %08lX  offset: %08lX\n", flash_sect_addr, (ulong)flash_addr, flash_offset);

	/* copy old contents to temporary buffer */
	memcpy(env_buffer, (void *)flash_sect_addr, CFG_ENV_SECT_SIZE);

	/* copy current environment to temporary buffer */
	memcpy((uchar *)((unsigned long)env_buffer + flash_offset), env_ptr, CFG_ENV_SIZE);

	len	 = CFG_ENV_SECT_SIZE;
#else
	flash_sect_addr = (ulong)flash_addr;
	len = CFG_ENV_SIZE;
#endif	/* CFG_ENV_SECT_SIZE */

	end_addr = flash_sect_addr + len - 1;

	if(flash_sect_erase(flash_sect_addr, end_addr)){
		return(1);
	}

	rc = flash_write((char *)env_buffer, flash_sect_addr, len);

	if(rc != 0){
		flash_perror(rc);
		rcode = 1;
	} else {
		//debug("done\n");
	}

	return(rcode);
}

#endif /* CMD_SAVEENV */

#endif /* CFG_ENV_ADDR_REDUND */

void env_relocate_spec(void){
#if !defined(ENV_IS_EMBEDDED) || defined(CFG_ENV_ADDR_REDUND)
	#ifdef CFG_ENV_ADDR_REDUND
	if(gd->env_addr != (ulong)&(flash_addr->data)){
		env_t * etmp = flash_addr;
		ulong ltmp = end_addr;

		flash_addr = flash_addr_new;
		flash_addr_new = etmp;

		end_addr = end_addr_new;
		end_addr_new = ltmp;
	}

	if(flash_addr_new->flags != OBSOLETE_FLAG && tinf_crc32(flash_addr_new->data, ENV_SIZE) == flash_addr_new->crc){
		char flag = OBSOLETE_FLAG;

		gd->env_valid = 2;

		flash_write(&flag, (ulong)&(flash_addr_new->flags), sizeof(flash_addr_new->flags));
	}

	if(flash_addr->flags != ACTIVE_FLAG && (flash_addr->flags & ACTIVE_FLAG) == ACTIVE_FLAG){
		char flag = ACTIVE_FLAG;

		gd->env_valid = 2;

		flash_write(&flag, (ulong)&(flash_addr->flags), sizeof(flash_addr->flags));
	}

	if(gd->env_valid == 2){
		puts("** Warning: some problems detected reading environment, recovered successfully\n");
	}
	#endif /* CFG_ENV_ADDR_REDUND */

	memcpy(env_ptr, (void*)flash_addr, CFG_ENV_SIZE);

#endif /* ! ENV_IS_EMBEDDED || CFG_ENV_ADDR_REDUND */
}

#endif /* CFG_ENV_IS_IN_FLASH */
