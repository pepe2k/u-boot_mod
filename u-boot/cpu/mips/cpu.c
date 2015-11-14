/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
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

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>

#if defined(CONFIG_AR7100)
#include <asm/addrspace.h>
#include <ar7100_soc.h>
#endif

#if defined(CONFIG_AR7240)
#include <asm/addrspace.h>
#include <ar7240_soc.h>
#endif

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
#if defined(CONFIG_AR7100)
	for(;;){
		ar7100_reg_wr(AR7100_RESET, (AR7100_RESET_FULL_CHIP | AR7100_RESET_DDR));
	}
#elif defined(CONFIG_AR7240)
#ifndef COMPRESSED_UBOOT
	fprintf(stdout, "\nResetting the board...\n");
	milisecdelay(500);
#endif  /* #ifndef COMPRESSED_UBOOT */
	for(;;){
	#ifdef CONFIG_WASP
		if(ar7240_reg_rd(AR7240_REV_ID) & 0xf){
			ar7240_reg_wr(AR7240_RESET, (AR7240_RESET_FULL_CHIP | AR7240_RESET_DDR));
		} else {
	/*
	* WAR for full chip reset spi vs. boot-rom selection
	* bug in wasp 1.0
	*/
			ar7240_reg_wr(AR7240_GPIO_OE, ar7240_reg_rd(AR7240_GPIO_OE) & (~(1 << 17)));
		}
	#else
		ar7240_reg_wr(AR7240_RESET, (AR7240_RESET_FULL_CHIP | AR7240_RESET_DDR));
	#endif
	}
#endif
#ifndef COMPRESSED_UBOOT
	fprintf(stderr, "\n*** ERROR: RESET FAILED! ***\n");
#endif  /* #ifndef COMPRESSED_UBOOT */
	return(0);
}

extern void dcache_flush_range(u32 a, u32 end);

void flush_cache(ulong start_addr, ulong size){
	u32 end, a;

	a = start_addr & ~(CFG_CACHELINE_SIZE - 1);
	size = (size + CFG_CACHELINE_SIZE - 1) & ~(CFG_CACHELINE_SIZE - 1);
	end = a + size;

	dcache_flush_range(a, end);
}

/*
 * Read CPU type and put its name into buffer
 * For now only 24/74Kc are supported as all
 * supported SOCs are based on one of them
 */
void cpu_name(char *name)
{
	u32 cpu_id = read_c0_prid();

	switch (cpu_id & PRID_IMP_MASK) {
	case PRID_IMP_24K:
		sprintf(name, "MIPS 24Kc");
		break;
	case PRID_IMP_74K:
		sprintf(name, "MIPS 74Kc");
		break;
	default:
		sprintf(name, "MIPS Unknown");
		break;
	}
}
