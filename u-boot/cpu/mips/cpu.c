/*
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2003 Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>

extern void dcache_flush_range(u32 a, u32 end);

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	printf("Resetting the board...");
	milisecdelay(500);

	full_reset();

	/* After full chip reset we should not reach next step... */
	printf("\n## Error: RESET FAILED!\n");

	return 0;
}

void flush_cache(ulong start_addr, ulong size)
{
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

	if (name == NULL)
		return;

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
