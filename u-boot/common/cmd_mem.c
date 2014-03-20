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

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#if (CONFIG_COMMANDS & CFG_CMD_MMC)
#include <mmc.h>
#endif

#if (CONFIG_COMMANDS & (CFG_CMD_MEMORY	| \
						CFG_CMD_ITEST	| \
						CFG_CMD_PCI		| \
						CMD_CMD_PORTIO) )

DECLARE_GLOBAL_DATA_PTR;

/*
 * Check for a size specification .b, .w or .l.
 */
int cmd_get_data_size(char* arg, int default_size){
	int len = strlen(arg);

	if(len > 2 && arg[len - 2] == '.'){
		switch(arg[len - 1]){
			case 'b':
				return(1);
			case 'w':
				return(2);
			case 'l':
				return(4);
			case 's':
				return(-2);
			default:
				return(-1);
		}
	}

	return(default_size);
}
#endif

#if (CONFIG_COMMANDS & CFG_CMD_MEMORY)

static int mod_mem(cmd_tbl_t *, int, int, int, char *[]);

/*
 * Display values from last command.
 * Memory modify remembered values are different from display memory.
 */
uint dp_last_addr, dp_last_size;
uint dp_last_length = 0x40;
uint mm_last_addr, mm_last_size;

/*
 * Memory Display
 *
 * Syntax:
 *	md{.b, .w, .l} {addr} {len}
 */
#define DISP_LINE_LEN	16
int do_mem_md(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr, length;
	ulong i, nbytes, linebytes;
	u_char *cp;
	int size;
	int rc = 0;

	/*
	 * We use the last specified parameters, unless new ones are
	 * entered.
	 */
	addr = dp_last_addr;
	size = dp_last_size;
	length = dp_last_length;

	if(argc < 2){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	if((flag & CMD_FLAG_REPEAT) == 0){
		/*
		 * New command specified.  Check for a size specification.
		 * Defaults to long if no or incorrect specification.
		 */
		if((size = cmd_get_data_size(argv[0], 4)) < 0){
			return(1);
		}

		/*
		 * Address is specified since argc > 1
		 */
		addr = simple_strtoul(argv[1], NULL, 16);

		/*
		 * If another parameter, it is the length to display.
		 * Length is the number of objects, not number of bytes.
		 */
		if(argc > 2){
			length = simple_strtoul(argv[2], NULL, 16);
		}
	}

	/*
	 * Print the lines.
	 *
	 * We buffer all read data, so we can make sure data is read only
	 * once, and all accesses are with the specified bus width.
	 */
	nbytes = length * size;

	do {
		char linebuf[DISP_LINE_LEN];
		uint *uip = (uint *)linebuf;
		ushort *usp = (ushort *)linebuf;
		u_char *ucp = (u_char *)linebuf;

		printf("%08lX:", addr);

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;

		for(i = 0; i < linebytes; i += size){
			if(size == 4){
				printf(" %08X", (*uip++ = *((uint *)addr)));
			} else if(size == 2){
				printf(" %04X", (*usp++ = *((ushort *)addr)));
			} else {
				printf(" %02X", (*ucp++ = *((u_char *)addr)));
			}
			addr += size;
		}

		puts("    ");
		cp = (u_char *)linebuf;

		for(i = 0; i < linebytes; i++){
			if((*cp < 0x20) || (*cp > 0x7e)){
				putc('.');
			} else {
				printf("%c", *cp);
			}
			cp++;
		}

		putc('\n');
		nbytes -= linebytes;

		if(ctrlc()){
			rc = 1;
			break;
		}

	} while(nbytes > 0);

	dp_last_addr = addr;
	dp_last_length = length;
	dp_last_size = size;

	return(rc);
}

int do_mem_mm(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	return(mod_mem(cmdtp, 1, flag, argc, argv));
}
int do_mem_nm(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	return(mod_mem(cmdtp, 0, flag, argc, argv));
}

int do_mem_mw(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr, writeval, count;
	int size;

	if((argc < 3) || (argc > 4)){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	/*
	 * Check for size specification.
	 */
	if((size = cmd_get_data_size(argv[0], 4)) < 1){
		return(1);
	}

	/*
	 * Address is specified since argc > 1
	 */
	addr = simple_strtoul(argv[1], NULL, 16);

	/*
	 * Get the value to write.
	 */
	writeval = simple_strtoul(argv[2], NULL, 16);

	/* Count ? */
	if(argc == 4){
		count = simple_strtoul(argv[3], NULL, 16);
	} else {
		count = 1;
	}

	while(count-- > 0){
		if(size == 4){
			*((ulong *)addr) = (ulong)writeval;
		} else if(size == 2){
			*((ushort *)addr) = (ushort)writeval;
		} else {
			*((u_char *)addr) = (u_char)writeval;
		}
		addr += size;
	}

	return(0);
}

int do_mem_cp(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr, dest, count;
	int size;

	if(argc != 4){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	/*
	 * Check for size specification.
	 */
	if((size = cmd_get_data_size(argv[0], 4)) < 0){
		return(1);
	}

	addr  = simple_strtoul(argv[1], NULL, 16);
	dest  = simple_strtoul(argv[2], NULL, 16);
	count = simple_strtoul(argv[3], NULL, 16);

	if(count == 0){
		puts("## Error: zero length?\n");
		return(1);
	}

#ifndef CFG_NO_FLASH
	/* check if we are copying to Flash */
	if(addr2info(dest) != NULL){
		int rc;

		puts("Copying to FLASH...\n");

		rc = flash_write((char *)addr, dest, count * size);

		if(rc != 0){
			flash_perror(rc);
			return(1);
		}

		puts("Done!\n\n");
		return(0);
	}
#endif

	while(count-- > 0){
		if(size == 4){
			*((ulong *)dest) = *((ulong *)addr);
		} else if(size == 2){
			*((ushort *)dest) = *((ushort *)addr);
		} else {
			*((u_char *)dest) = *((u_char *)addr);
		}
		addr += size;
		dest += size;
	}

	return(0);
}

/*
 * Perform a memory test. A more complete alternative test can be
 * configured using CFG_ALT_MEMTEST. The complete test loops until
 * interrupted by ctrl-c or by a failure of one of the sub-tests.
 */
int do_mem_mtest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	bd_t *bd = gd->bd;
	vu_long *addr, *start, *end;
	ulong val;
	ulong readback;

#if defined(CFG_ALT_MEMTEST)
	vu_long addr_mask;
	vu_long offset;
	vu_long test_offset;
	vu_long pattern;
	vu_long temp;
	vu_long anti_pattern;
	vu_long num_words;
#if defined(CFG_MEMTEST_SCRATCH)
	vu_long *dummy = (vu_long*)CFG_MEMTEST_SCRATCH;
#else
	vu_long *dummy = NULL;
#endif
	int j;
	int iterations = 1;

	static const ulong bitpattern[] = {
		0x00000001, /* single bit */
		0x00000003, /* two adjacent bits */
		0x00000007, /* three adjacent bits */
		0x0000000F, /* four adjacent bits */
		0x00000005, /* two non-adjacent bits */
		0x00000015, /* three non-adjacent bits */
		0x00000055, /* four non-adjacent bits */
		0xaaaaaaaa, /* alternating 1/0 */
	};
#else
	ulong incr;
	ulong pattern;
	int rcode = 0;
#endif

	if(argc > 1){
		start = (ulong *)simple_strtoul(argv[1], NULL, 16);
	} else {
		start = (ulong *)CFG_MEMTEST_START;
	}

	if(argc > 2){
		end = (ulong *)simple_strtoul(argv[2], NULL, 16);
	} else {
		end = (ulong *)CFG_MEMTEST_END;
	}

	if((uint)start >= (uint)end){
		puts("## Error: end address must be bigger than start address!\n");
		return(1);
	}

	if(((uint)start < (uint)CFG_MEMTEST_START) || ((uint)end > (uint)CFG_MEMTEST_END)){
		printf("## Error: start and end addresses should be in 0x%08X...0x%08X range!\n", (uint)CFG_MEMTEST_START, (uint)CFG_MEMTEST_END);
		return(1);
	}

#if !defined(CFG_ALT_MEMTEST)
	if(argc > 3){
		pattern = (ulong)simple_strtoul(argv[3], NULL, 16);
	} else {
		pattern = 0;
	}
#endif

#if defined(CFG_ALT_MEMTEST)
	printf("Testing RAM 0x%08X...0x%08X:\n", (uint)start, (uint)end);

	for(;;){
		if(ctrlc()){
			putc('\n');
			return(1);
		}

		printf("Iteration: %6d\r", iterations);

		iterations++;

		/*
		 * Data line test: write a pattern to the first
		 * location, write the 1's complement to a 'parking'
		 * address (changes the state of the data bus so a
		 * floating bus doen't give a false OK), and then
		 * read the value back. Note that we read it back
		 * into a variable because the next time we read it,
		 * it might be right (been there, tough to explain to
		 * the quality guys why it prints a failure when the
		 * "is" and "should be" are obviously the same in the
		 * error message).
		 *
		 * Rather than exhaustively testing, we test some
		 * patterns by shifting '1' bits through a field of
		 * '0's and '0' bits through a field of '1's (i.e.
		 * pattern and ~pattern).
		 */
		addr = start;

		for(j = 0; j < sizeof(bitpattern)/sizeof(bitpattern[0]); j++){
			val = bitpattern[j];

			for(; val != 0; val <<= 1){
				*addr = val;
				*dummy = ~val; /* clear the test data off of the bus */
				readback = *addr;

				if(readback != val){
					printf("## Error (data line): expected 0x%08lX, found 0x%08lX\n", val, readback);
				}

				*addr = ~val;
				*dummy = val;
				readback = *addr;

				if(readback != ~val){
					printf("## Error (data line): expected %08lX, found %08lX\n", ~val, readback);
				}
			}
		}

		/*
		 * Based on code whose Original Author and Copyright
		 * information follows: Copyright (c) 1998 by Michael
		 * Barr. This software is placed into the public
		 * domain and may be used for any purpose. However,
		 * this notice must not be changed or removed and no
		 * warranty is either expressed or implied by its
		 * publication or distribution.
		 */

		/*
		 * Address line test
		 *
		 * Description: Test the address bus wiring in a
		 *              memory region by performing a walking
		 *              1's test on the relevant bits of the
		 *              address and checking for aliasing.
		 *              This test will find single-bit
		 *              address failures such as stuck -high,
		 *              stuck-low, and shorted pins. The base
		 *              address and size of the region are
		 *              selected by the caller.
		 *
		 * Notes:	For best results, the selected base
		 *              address should have enough LSB 0's to
		 *              guarantee single address bit changes.
		 *              For example, to test a 64-Kbyte
		 *              region, select a base address on a
		 *              64-Kbyte boundary. Also, select the
		 *              region size as a power-of-two if at
		 *              all possible.
		 *
		 * Returns:     0 if the test succeeds, 1 if the test fails.
		 *
		 * ## NOTE ##	Be sure to specify start and end
		 *              addresses such that addr_mask has
		 *              lots of bits set. For example an
		 *              address range of 01000000 02000000 is
		 *              bad while a range of 01000000
		 *              01ffffff is perfect.
		 */
		addr_mask = ((ulong)end - (ulong)start)/sizeof(vu_long);
		pattern = (vu_long)0xaaaaaaaa;
		anti_pattern = (vu_long)0x55555555;

		/*
		 * Write the default pattern at each of the
		 * power-of-two offsets.
		 */
		for(offset = 1; (offset & addr_mask) != 0; offset <<= 1){
			start[offset] = pattern;
		}

		/*
		 * Check for address bits stuck high.
		 */
		test_offset = 0;
		start[test_offset] = anti_pattern;

		for(offset = 1; (offset & addr_mask) != 0; offset <<= 1){
			temp = start[offset];

			if(temp != pattern){
				printf("\n## Error: address bit stuck high @ 0x%.8lX, expected 0x%.8lX, found 0x%.8lX\n", (ulong)&start[offset], pattern, temp);
				return(1);
			}
		}
		start[test_offset] = pattern;

		/*
		 * Check for addr bits stuck low or shorted.
		 */
		for(test_offset = 1; (test_offset & addr_mask) != 0; test_offset <<= 1){
			start[test_offset] = anti_pattern;

			for(offset = 1; (offset & addr_mask) != 0; offset <<= 1){
				temp = start[offset];

				if((temp != pattern) && (offset != test_offset)){
					printf("\n## Error: address bit stuck low or shorted @ 0x%.8lX, expected 0x%.8lX, found 0x%.8lX\n", (ulong)&start[offset], pattern, temp);
					return(1);
				}
			}
			start[test_offset] = pattern;
		}

		/*
		 * Description: Test the integrity of a physical
		 *		memory device by performing an
		 *		increment/decrement test over the
		 *		entire region. In the process every
		 *		storage bit in the device is tested
		 *		as a zero and a one. The base address
		 *		and the size of the region are
		 *		selected by the caller.
		 *
		 * Returns:     0 if the test succeeds, 1 if the test fails.
		 */
		num_words = ((ulong)end - (ulong)start)/sizeof(vu_long) + 1;

		/*
		 * Fill memory with a known pattern.
		 */
		for(pattern = 1, offset = 0; offset < num_words; pattern++, offset++){
			start[offset] = pattern;
		}

		/*
		 * Check each location and invert it for the second pass.
		 */
		for(pattern = 1, offset = 0; offset < num_words; pattern++, offset++){
			temp = start[offset];

			if(temp != pattern){
				printf("\n## Error (read/write) @ 0x%.8lX: expected 0x%.8lX, found 0x%.8lX)\n", (ulong)&start[offset], pattern, temp);
				return(1);
			}

			anti_pattern = ~pattern;
			start[offset] = anti_pattern;
		}

		/*
		 * Check each location for the inverted pattern and zero it.
		 */
		for(pattern = 1, offset = 0; offset < num_words; pattern++, offset++){
			anti_pattern = ~pattern;
			temp = start[offset];

			if(temp != anti_pattern){
				printf("\n## Error (read/write): @ 0x%.8lX: expected 0x%.8lX, found 0x%.8lX)\n", (ulong)&start[offset], anti_pattern, temp);
				return(1);
			}
			start[offset] = 0;
		}
	}

#else /* The original, quickie test */
	incr = 1;
	for(;;){
		if(ctrlc()){
			putc('\n');
			return(1);
		}

		printf("\rPattern %08lX  Writing...%12s\b\b\b\b\b\b\b\b\b\b", pattern, "");

		for(addr = start, val = pattern; addr < end; addr++){
			*addr = val;
			val += incr;
		}

		puts("Reading...");

		for(addr = start, val = pattern; addr < end; addr++){
			readback = *addr;
			if(readback != val){
				printf("\n## Error @ 0x%08X: found %08lX, expected %08lX\n", (uint)addr, readback, val);
				rcode = 1;
			}
			val += incr;
		}

		/*
		 * Flip the pattern each time to make lots of zeros and
		 * then, the next time, lots of ones.  We decrement
		 * the "negative" patterns and increment the "positive"
		 * patterns to preserve this feature.
		 */
		if(pattern & 0x80000000){
			pattern = -pattern; /* complement & increment */
		} else {
			pattern = ~pattern;
		}
		incr = -incr;
	}
	return(rcode);
#endif
}

/* Modify memory.
 *
 * Syntax:
 *	mm{.b, .w, .l} {addr}
 *	nm{.b, .w, .l} {addr}
 */
static int mod_mem(cmd_tbl_t *cmdtp, int incrflag, int flag, int argc, char *argv[]){
	ulong addr, i;
	int nbytes, size;
	extern char console_buffer[];

	if(argc != 2){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	/* We use the last specified parameters, unless new ones are
	 * entered.
	 */
	addr = mm_last_addr;
	size = mm_last_size;

	if((flag & CMD_FLAG_REPEAT) == 0){
		/* New command specified.  Check for a size specification.
		 * Defaults to long if no or incorrect specification.
		 */
		if((size = cmd_get_data_size(argv[0], 4)) < 0){
			return(1);
		}

		/* Address is specified since argc > 1
		 */
		addr = simple_strtoul(argv[1], NULL, 16);
	}

	/* Print the address, followed by value.  Then accept input for
	 * the next value.  A non-converted value exits.
	 */
	do {
		printf("%08lX:", addr);

		if(size == 4){
			printf(" %08X", *((uint *)addr));
		} else if(size == 2){
			printf(" %04X", *((ushort *)addr));
		} else{
			printf(" %02X", *((u_char *)addr));
		}

		nbytes = readline(" ? ");
		if(nbytes == 0 || (nbytes == 1 && console_buffer[0] == '-')){
			/* <CR> pressed as only input, don't modify current
			 * location and move to next. "-" pressed will go back.
			 */
			if(incrflag){
				addr += nbytes ? -size : size;
			}
			nbytes = 1;
		} else {
			char *endp;
			i = simple_strtoul(console_buffer, &endp, 16);
			nbytes = endp - console_buffer;
			if(nbytes){
				if(size == 4){
					*((uint *)addr) = i;
				} else if(size == 2){
					*((ushort *)addr) = i;
				} else {
					*((u_char *)addr) = i;
				}
				if(incrflag){
					addr += size;
				}
			}
		}
	} while(nbytes);

	mm_last_addr = addr;
	mm_last_size = size;

	return(0);
}

/**************************************************/
U_BOOT_CMD(md, 3, 1, do_mem_md, "memory display\n", "[.b, .w, .l] address [# of objects]\n\t- memory display\n");
U_BOOT_CMD(mm, 2, 1, do_mem_mm, "memory modify (auto-incrementing)\n", "[.b, .w, .l] address\n\t- memory modify, auto increment address\n");
U_BOOT_CMD(nm, 2, 1, do_mem_nm, "memory modify (constant address)\n", "[.b, .w, .l] address\n\t- memory modify, read and keep address\n");
U_BOOT_CMD(mw, 4, 1, do_mem_mw, "memory write (fill)\n", "[.b, .w, .l] address value [count]\n\t- write memory\n");
#if defined(CFG_ALT_MEMTEST)
U_BOOT_CMD(mtest, 3, 1, do_mem_mtest, "RAM test\n", "[start [end]]\n\t- complete, alternative RAM test\n");
#else
U_BOOT_CMD(mtest, 4, 1, do_mem_mtest, "simple RAM test\n", "[start [end [pattern]]]\n\t- simple RAM read/write test\n");
#endif
U_BOOT_CMD(cp, 4, 1, do_mem_cp, "memory copy\n", "[.b, .w, .l] source target count\n\t- copy memory\n");

#endif	/* CFG_CMD_MEMORY */
