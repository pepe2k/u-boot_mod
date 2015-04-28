/*
 * (C) Copyright 2000-2005
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _FLASH_H_
#define _FLASH_H_

#ifndef CFG_NO_FLASH
/*-----------------------------------------------------------------------
 * FLASH Info: contains chip specific data, per FLASH bank
 */

typedef struct {
	ulong	size;							/* total bank size in bytes		*/
	ulong	sector_size;					/* size of erase unit in bytes */
	ushort	sector_count;					/* number of erase units		*/
	ulong	flash_id;						/* combined device & manufacturer code	*/
	ulong	start[CFG_MAX_FLASH_SECT];		/* physical sector start addresses */
} flash_info_t;


/* Prototypes */
extern unsigned long flash_init (void);
extern int flash_erase(flash_info_t *, int, int);
extern int flash_sect_erase(ulong addr_first, ulong addr_last);

/* common/flash.c */
extern int flash_write(char *, ulong, ulong);
extern flash_info_t *addr2info(ulong);
extern int write_buff(flash_info_t *info, uchar *src, ulong addr, ulong cnt);

/*-----------------------------------------------------------------------
 * return codes from flash_write():
 */
#define ERR_OK						0
#define ERR_TIMOUT					1
#define ERR_NOT_ERASED				2
#define ERR_PROTECTED				4
#define ERR_INVAL					8
#define ERR_ALIGN					16
#define ERR_UNKNOWN_FLASH_VENDOR	32
#define ERR_UNKNOWN_FLASH_TYPE		64
#define ERR_PROG_ERROR				128

/*-----------------------------------------------------------------------
 * Device IDs
 */
#define FLASH_CUSTOM    0x1111
#define FLASH_UNKNOWN	0xFFFF		/* unknown flash type */

#endif /* !CFG_NO_FLASH */

#endif /* _FLASH_H_ */
