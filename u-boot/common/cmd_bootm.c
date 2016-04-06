/*
 * (C) Copyright 2000-2006
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
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <image.h>
#include <malloc.h>
#include <LzmaWrapper.h>
#include <environment.h>
#include <asm/byteorder.h>
#include <tinf.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CFG_HUSH_PARSER
#include <hush.h>
#endif

/* cmd_boot.c */
extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

/* net.c */
extern void eth_halt(void);

#if (CONFIG_COMMANDS & CFG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
#include <rtc.h>
#endif

/*
 *  Continue booting an OS image; caller already has:
 *  - copied image header to global variable `header'
 *  - checked header magic number, checksums (both header & image),
 *  - verified image architecture (PPC) and type (KERNEL or MULTI),
 *  - loaded (first part of) image to header load address,
 *  - disabled interrupts.
 */
extern void do_bootm_linux(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

#ifdef CONFIG_SILENT_CONSOLE
static void fixup_silent_linux(void);
#endif

#if (CONFIG_COMMANDS & CFG_CMD_IMI)
static int image_info(unsigned long addr);
#endif

image_header_t header;
ulong load_addr = CFG_LOAD_ADDR; /* default load address */

#ifdef CONFIG_TPLINK_IMAGE_HEADER
void fake_image_header(image_header_t *hdr, tplink_image_header_t *tpl_hdr){
	memset(hdr, 0, sizeof(image_header_t));

	/* Build new header */
	hdr->ih_magic	= htonl(IH_MAGIC);
	hdr->ih_hcrc	= 0;
	hdr->ih_time	= 0;
	hdr->ih_size	= htonl(tpl_hdr->kernelLen);
	hdr->ih_load	= htonl(tpl_hdr->kernelTextAddr);
	hdr->ih_ep		= htonl(tpl_hdr->kernelEntryPoint);
	hdr->ih_dcrc	= 0;
	hdr->ih_os		= IH_OS_LINUX;
	hdr->ih_arch	= IH_CPU_MIPS;
	hdr->ih_type	= IH_TYPE_KERNEL;
	hdr->ih_comp	= IH_COMP_LZMA;

	strncpy((char *)hdr->ih_name, (char *)tpl_hdr->signiture_1, IH_NMLEN);
}
#endif /* CONFIG_TPLINK_IMAGE_HEADER */

int do_bootm(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr, data, len;
	uint unc_len = CFG_BOOTM_LEN;
	int i;
	image_header_t *hdr = &header;
#ifdef CONFIG_TPLINK_IMAGE_HEADER
	tplink_image_header_t *fileTag;
#endif

	if(argc < 2){
		addr = load_addr;
	} else {
		addr = simple_strtoul(argv[1], NULL, 16);
	}

	printf("Booting image at: 0x%08lX\n", addr);

#ifndef CONFIG_TPLINK_IMAGE_HEADER
	memmove(&header, (char *)addr, sizeof(image_header_t));
	print_image_hdr(hdr);

	data = addr + sizeof(image_header_t);
#else
	fileTag = (tplink_image_header_t *)addr;
	print_image_hdr(fileTag);

	fake_image_header(hdr, fileTag);

	data = addr + TAG_LEN;
#endif /* !CONFIG_TPLINK_IMAGE_HEADER */

	len = ntohl(hdr->ih_size);

	/*
	 * We have reached the point of no return: we are going to
	 * overwrite all exception vector code, so we cannot easily
	 * recover from any failures any more...
	 */
#ifdef CONFIG_NETCONSOLE
	/*
	* Stop the ethernet stack if NetConsole could have
	* left it up
	*/
	eth_halt();
#endif

	/* TODO: should we flush caches for kernel? */
	/*
	 * Flush everything, restore caches for linux
	 */
	//mips_cache_flush();
	//mips_icache_flush_ix();

	/* XXX - this causes problems when booting from flash */
	/* dcache_disable(); */

	/*	case IH_COMP_LZMA:*/
	puts("Uncompressing kernel image... ");

	i = lzma_inflate((unsigned char *)data, len, (unsigned char*)ntohl(hdr->ih_load), (int *)&unc_len);

	if(i != LZMA_RESULT_OK){
		printf("## Error: LZMA error num: %d\n", i);
		return(-1);
	}

	puts("OK!\n");

#ifdef CONFIG_SILENT_CONSOLE
	fixup_silent_linux();
#endif

	do_bootm_linux(cmdtp, flag, argc, argv);

#ifdef DEBUG
	puts("\n## Error: control returned to monitor - resetting...\n");
	do_reset(cmdtp, flag, argc, argv);
#endif

	return(1);
}

U_BOOT_CMD(bootm, 2, 1, do_bootm, "boot application image from memory\n", "[addr]\n"
"\t- boot application image stored in memory at address 'addr'\n");

#ifdef CONFIG_SILENT_CONSOLE
static void fixup_silent_linux(){
	char buf[256], *start, *end;
	char *cmdline = getenv("bootargs");

	/* Only fix cmdline when requested */
	if(!(gd->flags & GD_FLG_SILENT)){
		return;
	}

#ifdef DEBUG
	printf("before silent fix-up: %s\n", cmdline);
#endif

	if(cmdline){
		if((start = strstr(cmdline, "console=")) != NULL){
			end = strchr(start, ' ');
			strncpy(buf, cmdline, (start - cmdline + 8));
			if(end){
				strcpy(buf + (start - cmdline + 8), end);
			} else {
				buf[start - cmdline + 8] = '\0';
			}
		} else {
			strcpy(buf, cmdline);
			strcat(buf, " console=");
		}
	} else {
		strcpy(buf, "console=");
	}

	setenv("bootargs", buf);
	debug("after silent fix-up: %s\n", buf);
}
#endif /* CONFIG_SILENT_CONSOLE */

#ifndef CONFIG_TPLINK_IMAGE_HEADER
static void print_type(image_header_t *hdr){
	char *os, *arch, *type, *comp;

	switch(hdr->ih_os){
		case IH_OS_INVALID:
			os = "Invalid OS";
			break;
		case IH_OS_NETBSD:
			os = "NetBSD";
			break;
		case IH_OS_LINUX:
			os = "Linux";
			break;
		case IH_OS_VXWORKS:
			os = "VxWorks";
			break;
		case IH_OS_QNX:
			os = "QNX";
			break;
		case IH_OS_U_BOOT:
			os = "U-Boot";
			break;
		case IH_OS_RTEMS:
			os = "RTEMS";
			break;
		default:
			os = "Unknown OS";
			break;
	}

	switch(hdr->ih_arch){
		case IH_CPU_INVALID:
			arch = "Invalid CPU";
			break;
		case IH_CPU_ALPHA:
			arch = "Alpha";
			break;
		case IH_CPU_ARM:
			arch = "ARM";
			break;
		case IH_CPU_I386:
			arch = "Intel x86";
			break;
		case IH_CPU_IA64:
			arch = "IA64";
			break;
		case IH_CPU_MIPS:
			arch = "MIPS";
			break;
		case IH_CPU_MIPS64:
			arch = "MIPS 64 Bit";
			break;
		case IH_CPU_PPC:
			arch = "PowerPC";
			break;
		case IH_CPU_S390:
			arch = "IBM S390";
			break;
		case IH_CPU_SH:
			arch = "SuperH";
			break;
		case IH_CPU_SPARC:
			arch = "SPARC";
			break;
		case IH_CPU_SPARC64:
			arch = "SPARC 64 Bit";
			break;
		case IH_CPU_M68K:
			arch = "M68K";
			break;
		case IH_CPU_MICROBLAZE:
			arch = "Microblaze";
			break;
		case IH_CPU_NIOS:
			arch = "Nios";
			break;
		case IH_CPU_NIOS2:
			arch = "Nios-II";
			break;
		default:
			arch = "Unknown Architecture";
			break;
	}

	switch(hdr->ih_type){
		case IH_TYPE_INVALID:
			type = "Invalid Image";
			break;
		case IH_TYPE_STANDALONE:
			type = "Standalone Program";
			break;
		case IH_TYPE_KERNEL:
			type = "Kernel Image";
			break;
		case IH_TYPE_RAMDISK:
			type = "RAMDisk Image";
			break;
		case IH_TYPE_MULTI:
			type = "Multi-File Image";
			break;
		case IH_TYPE_FIRMWARE:
			type = "Firmware";
			break;
		case IH_TYPE_SCRIPT:
			type = "Script";
			break;
		default:
			type = "Unknown Image";
			break;
	}

	switch(hdr->ih_comp){
		case IH_COMP_NONE:
			comp = "uncompressed";
			break;
		case IH_COMP_GZIP:
			comp = "gzip compressed";
			break;
		case IH_COMP_BZIP2:
			comp = "bzip2 compressed";
			break;
		case IH_COMP_LZMA:
			comp = "lzma compressed";
			break;
		default:
			comp = "unknown compression";
			break;
	}

	printf("%s %s %s (%s)", arch, os, type, comp);
}

void print_image_hdr(image_header_t *hdr){
#if (CONFIG_COMMANDS & CFG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
	time_t timestamp = (time_t)ntohl(hdr->ih_time);
	struct rtc_time tm;
#endif

	printf("\n   Image name:   %.*s\n", IH_NMLEN, hdr->ih_name);

#if (CONFIG_COMMANDS & CFG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
	to_tm(timestamp, &tm);
	printf("   Created:      %4d-%02d-%02d  %2d:%02d:%02d UTC\n", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
#endif	/* CFG_CMD_DATE, CONFIG_TIMESTAMP */

	puts("   Image type:   ");
	print_type(hdr);

	printf("\n   Data size:    %d Bytes = ", ntohl(hdr->ih_size));
	print_size(ntohl(hdr->ih_size), "\n");

	printf("   Load address: 0x%08X\n   Entry point:  0x%08X\n", ntohl(hdr->ih_load), ntohl(hdr->ih_ep));

	if(hdr->ih_type == IH_TYPE_MULTI){
		int i;
		ulong len;
		ulong *len_ptr = (ulong *)((ulong)hdr + sizeof(image_header_t));

		puts("   Contents:\n");

		for(i = 0; (len = ntohl(*len_ptr)); ++i, ++len_ptr){
			printf("      Image %d: %8ld Bytes = ", i, len);
			print_size(len, "\n");
		}
	}

	puts("\n");
}
#else
void print_image_hdr(tplink_image_header_t *hdr){
	printf("\n   Image name:   %.*s %.*s\n", SIG_LEN, hdr->signiture_1, SIG_LEN_2, hdr->signiture_2);
	  puts("   Image type:   MIPS Linux Kernel Image (lzma compressed)\n");
	printf("   Data size:    %d Bytes = ", ntohl(hdr->kernelLen));
	print_size(ntohl(hdr->kernelLen), "\n");
	printf("   Load address: 0x%08X\n   Entry point:  0x%08X\n\n", ntohl(hdr->kernelTextAddr), ntohl(hdr->kernelEntryPoint));
}
#endif /* !CONFIG_TPLINK_IMAGE_HEADER */

#if (CONFIG_COMMANDS & CFG_CMD_BOOTD)
int do_bootd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	int rcode = 0;
#ifndef CFG_HUSH_PARSER
	if(run_command (getenv ("bootcmd"), flag) < 0){
		rcode = 1;
	}
#else
	if(parse_string_outer(getenv("bootcmd"), FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0){
		rcode = 1;
	}
#endif
	return(rcode);
}

U_BOOT_CMD(boot, 1, 1, do_bootd, "boot default, i.e., run 'bootcmd'\n", NULL);

/* keep old command name "bootd" for backward compatibility */
U_BOOT_CMD(bootd, 1, 1, do_bootd, "boot default, i.e., run 'bootcmd'\n", NULL);

#endif /* CONFIG_COMMANDS & CFG_CMD_BOOTD */

#if (CONFIG_COMMANDS & CFG_CMD_IMI)
int do_iminfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]){
	ulong addr;
	int rcode = 0;

	if (argc == 2){
		addr = simple_strtoul(argv[1], NULL, 16);
		return image_info(addr);
	} else {
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

	return(rcode);
}

static int image_info(ulong addr){
	ulong data, len, checksum;
	image_header_t *hdr = &header;

	printf("\nChecking image at 0x%08lX...\n", addr);

	/* Copy header so we can blank CRC field for re-calculation */
	memmove(&header, (char *)addr, sizeof(image_header_t));

	data = (ulong)&header;
	len  = sizeof(image_header_t);

	checksum = ntohl(hdr->ih_hcrc);
	hdr->ih_hcrc = 0;

	if(tinf_crc32((uchar *)data, len) != checksum){
		puts("## Error: bad header checksum!\n");
		return 1;
	}

	/* for multi-file images we need the data part, too */
	print_image_hdr((image_header_t *)addr);

	data = addr + sizeof(image_header_t);
	len  = ntohl(hdr->ih_size);

	puts("   Verifying checksum... ");

	if(tinf_crc32((uchar *)data, len) != ntohl(hdr->ih_dcrc)){
		puts("bad data CRC!\n");
		return(1);
	}

	puts("OK!\n\n");

	return(0);
}

U_BOOT_CMD(iminfo, 2, 1, do_iminfo, "print firmware header\n", "address\n"
		"\t- print header information for firmware image startting at address 'address'\n"
);

#endif	/* CFG_CMD_IMI */
