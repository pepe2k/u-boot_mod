/*
 * (C) Copyright 2000
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

/* #define DEBUG */

#include <common.h>
#include <flash.h>

#if !defined(CFG_NO_FLASH)

extern flash_info_t flash_info[]; /* info for FLASH chips */

/*-----------------------------------------------------------------------
 * Functions
 */
flash_info_t * addr2info(ulong addr){
	flash_info_t *info;
	int i;

	for(i = 0, info = &flash_info[0]; i < CFG_MAX_FLASH_BANKS; ++i, ++info){
		/* WARNING - The '- 1' is needed if the flash
		 * is at the end of the address space, since
		 * info->start[0] + info->size wraps back to 0.
		 * Please don't change this unless you understand this.
		 */
		if(info->flash_id != FLASH_UNKNOWN && addr >= info->start[0] && addr <= info->start[0] + info->size - 1){
			return(info);
		}
	}
	return(NULL);
}

/*-----------------------------------------------------------------------
 * Copy memory to flash.
 * Make sure all target addresses are within Flash bounds,
 * and no protected sectors are hit.
 * Returns:
 * ERR_OK          0 - OK
 * ERR_TIMOUT      1 - write timeout
 * ERR_NOT_ERASED  2 - Flash not erased
 * ERR_PROTECTED   4 - target range includes protected sectors
 * ERR_INVAL       8 - target address not in Flash memory
 * ERR_ALIGN       16 - target address not aligned on boundary
 *			(only some targets require alignment)
 */
int flash_write(char *src, ulong addr, ulong cnt){
	int i;
	ulong end = addr + cnt - 1;
	flash_info_t *info_first = addr2info(addr);
	flash_info_t *info_last = addr2info(end);
	flash_info_t *info;

	if(cnt == 0){
		return(ERR_OK);
	}

	if(!info_first || !info_last){
		return(ERR_INVAL);
	}

	/* finally write data to flash */
	for(info = info_first; info <= info_last && cnt > 0; ++info){
		ulong len;

		len = info->start[0] + info->size - addr;
		if(len > cnt){
			len = cnt;
		}
		if((i = write_buff(info, (uchar *)src, addr, len)) != 0){
			return(i);
		}
		cnt -= len;
		addr += len;
		src += len;
	}
	return(ERR_OK);
}

/*-----------------------------------------------------------------------
 */

void flash_perror(int err){
	switch(err){
		case ERR_OK:
			break;
		case ERR_TIMOUT:
			puts("## Error: timeout writing to FLASH\n");
			break;
		case ERR_NOT_ERASED:
			puts("## Error: FLASH not erased\n");
			break;
		case ERR_INVAL:
			puts("## Error: outside available FLASH\n");
			break;
		case ERR_ALIGN:
			puts("## Error: start and/or end address not on sector boundary\n");
			break;
		case ERR_UNKNOWN_FLASH_VENDOR:
			puts("## Error: unknown vendor of FLASH\n");
			break;
		case ERR_UNKNOWN_FLASH_TYPE:
			puts("## Error: unknown type of FLASH\n");
			break;
		case ERR_PROG_ERROR:
			puts("## Error: general FLASH programming error\n");
			break;
		default:
			printf("## Error: %s[%d] FIXME: rc=%d\n", __FILE__, __LINE__, err);
			break;
	}
}

/*-----------------------------------------------------------------------
 */
#endif /* !CFG_NO_FLASH */
