/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

/*
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <image.h>
#include <tplink_image.h>
#include <malloc.h>
#include <LzmaWrapper.h>
#include <environment.h>
#include <asm/byteorder.h>
#include <tinf.h>

#ifdef CFG_HUSH_PARSER
#include <hush.h>
#endif

#if defined(CONFIG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
#include <rtc.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern void do_bootm_linux(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
extern int  do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
extern void eth_halt(void);

/* U-Boot type image header */
image_header_t header;

/* Default load address */
u32 load_addr = CFG_LOAD_ADDR;

#define TPL_ALIGN_SIZE		21
#define UBOOT_ALIGN_SIZE	14

/*
 * Clears console variable from command line
 */
#ifdef CONFIG_SILENT_CONSOLE
static void fixup_silent_linux(void)
{
	char buf[256];
	char *cmdline, *end, *start;

	/* Only fix cmdline when requested */
	if (!(gd->flags & GD_FLG_SILENT)) {
		return;
	}

	cmdline = getenv("bootargs");

	if (cmdline) {
		if ((start = strstr(cmdline, "console=")) != NULL) {
			end = strchr(start, ' ');
			strncpy(buf, cmdline, (start - cmdline + 8));

			if (end) {
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
}
#endif /* CONFIG_SILENT_CONSOLE */

/*
 * Prints information about TP-Link
 * firmware format from header
 */
static void print_tpl_ih_v1(tplink_image_header_t *hdr)
{
	puts("\n");

	/* Image/vendor name */
	printf("   %-*s ", TPL_ALIGN_SIZE, "Vendor/image name:");
	printf("%.*s %.*s\n",
		sizeof(hdr->ih_vendor), hdr->ih_vendor,
		sizeof(hdr->ih_info), hdr->ih_info);

	/* Version (for vendor firmware only) */
	if (hdr->ih_fw_ver_hi > 0) {
		printf("   %-*s ", TPL_ALIGN_SIZE, "Firmware version:");
		printf("%d.%d.%d\n",
			ntohl(hdr->ih_fw_ver_hi),
			ntohl(hdr->ih_fw_ver_mid),
			ntohl(hdr->ih_fw_ver_lo));
	}

	/* Hardware id */
	printf("   %-*s ", TPL_ALIGN_SIZE, "Hardware ID:");
	printf("0x%X\n", ntohl(hdr->ih_hw_id));

	/* Sizes of firmware parts */
	printf("   %-*s ", TPL_ALIGN_SIZE, "Whole image size:");
	print_size(ntohl(hdr->ih_fw_len), " ");
	printf("(%d bytes)\n", ntohl(hdr->ih_fw_len));

	printf("   %-*s ", TPL_ALIGN_SIZE, "Kernel size:");
	print_size(ntohl(hdr->ih_kernel_len), " ");
	printf("(%d bytes)\n", ntohl(hdr->ih_kernel_len));

	printf("   %-*s ", TPL_ALIGN_SIZE, "Rootfs size:");
	print_size(ntohl(hdr->ih_rootfs_len), " ");
	printf("(%d bytes)\n", ntohl(hdr->ih_rootfs_len));

	printf("   %-*s ", TPL_ALIGN_SIZE, "Kernel load address:");
	printf("0x%08X\n", ntohl(hdr->ih_kernel_load));

	printf("   %-*s ", TPL_ALIGN_SIZE, "Kernel entry point:");
	printf("0x%08X\n", ntohl(hdr->ih_kernel_ep));

	/* TODO: MD5 sum verify */

	puts("\n");
}

/*
 * Returns image type in text
 */
static char *ih_img_type(uint8_t img)
{
	switch (img) {
	case IH_TYPE_KERNEL:
		return "Kernel";
	case IH_TYPE_MULTI:
		return "Multi-File";
/*
	case IH_TYPE_INVALID:
		return "Invalid";
	case IH_TYPE_STANDALONE:
		return "Standalone program";
	case IH_TYPE_RAMDISK:
		return "RAMDisk";
	case IH_TYPE_FIRMWARE:
		return "Firmware";
	case IH_TYPE_SCRIPT:
		return "Script";
*/
	default:
		return "unknown";
	}
}

/*
 * Returns architecture type in text
 */
static char *ih_arch_type(uint8_t arch)
{
	switch (arch) {
	case IH_CPU_MIPS:
		return "MIPS";
/*
	case IH_CPU_INVALID:
		return "Invalid CPU";
	case IH_CPU_ALPHA:
		return "Alpha";
	case IH_CPU_ARM:
		return "ARM";
	case IH_CPU_I386:
		return "Intel x86";
	case IH_CPU_IA64:
		return "IA64";
	case IH_CPU_MIPS64:
		return "MIPS 64-bit";
	case IH_CPU_PPC:
		return "PowerPC";
	case IH_CPU_S390:
		return "IBM S390";
	case IH_CPU_SH:
		return "SuperH";
	case IH_CPU_SPARC:
		return "SPARC";
	case IH_CPU_SPARC64:
		return "SPARC 64-bit";
	case IH_CPU_M68K:
		return "M68K";
	case IH_CPU_MICROBLAZE:
		return "Microblaze";
	case IH_CPU_NIOS:
		return "Nios";
	case IH_CPU_NIOS2:
		return "Nios-II";
*/
	default:
		return "unknown";
	}
}

/*
 * Returns compression type in text
 */
static char *ih_comp_type(uint8_t comp)
{
	switch (comp) {
	case IH_COMP_LZMA:
		return "LZMA";
/*
	case IH_COMP_NONE:
		return "none";
	case IH_COMP_GZIP:
		return "GZIP";
	case IH_COMP_BZIP2:
		return "BZIP2";
*/
	default:
		return "unknown";
	}
}

/*
 * Returns operating system type in text
 */
static char *ih_os_type(uint8_t os)
{
	switch (os) {
	case IH_OS_LINUX:
		return "Linux";
/*
	case IH_OS_INVALID:
		return "Invalid OS";
	case IH_OS_NETBSD:
		return "NetBSD";
	case IH_OS_VXWORKS:
		return "VxWorks";
	case IH_OS_QNX:
		return "QNX";
	case IH_OS_U_BOOT:
		return "U-Boot";
	case IH_OS_RTEMS:
		return "RTEMS";
*/
	default:
		return "unknown";
	}
}

/*
 * Prints information about standard
 * U-Boot image format from header
 */
static void print_uboot_ih(image_header_t *hdr)
{
	int i;
	u32 len;
	u32 *len_ptr;
#if defined(CONFIG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
	struct rtc_time tm;
	time_t timestamp = (time_t)ntohl(hdr->ih_time);
#endif

	puts("\n");

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Image name:");
	printf("%.*s\n", sizeof(hdr->ih_name), hdr->ih_name);

#if defined(CONFIG_CMD_DATE) || defined(CONFIG_TIMESTAMP)
	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Build date:");
	to_tm(timestamp, &tm);
	printf("%4d-%02d-%02d %02d:%02d:%02d UTC\n",
		tm.tm_year, tm.tm_mon, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);
#endif

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Architecture:");
	printf("%s\n", ih_arch_type(hdr->ih_arch));

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "OS/image type:");
	printf("%s %s\n", ih_os_type(hdr->ih_os), ih_img_type(hdr->ih_type));

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Compression:");
	printf("%s\n", ih_comp_type(hdr->ih_comp));

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Data size:");
	print_size(ntohl(hdr->ih_size), " ");
	printf("(%d bytes)\n", ntohl(hdr->ih_size));

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Load address:");
	printf("0x%08X\n", ntohl(hdr->ih_load));

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Entry point:");
	printf("0x%08X\n", ntohl(hdr->ih_ep));

	if (hdr->ih_type == IH_TYPE_MULTI) {
		len_ptr = (u32 *)((u32)hdr + sizeof(image_header_t));

		printf("\n   %-*s\n", UBOOT_ALIGN_SIZE, "Multi-File:");

		for (i = 0; (len = ntohl(*len_ptr)); ++i, ++len_ptr) {
			puts("   > ");
			print_size(len, " ");
			printf("(%d bytes)\n", len);
		}
	}

	puts("\n");
}

/*
 * Verifies U-Boot image data checksum
 */
static int ih_data_crc(u32 addr, image_header_t *hdr, int tpl_type, int verify)
{
	int ret = 0;

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Data CRC...");

	if (tpl_type == 0 && verify == 1) {
		if (tinf_crc32((u8 *)addr, ntohl(hdr->ih_size))
		    != ntohl(hdr->ih_dcrc)) {
			puts("ERROR\n\n");
			ret = 1;
		} else {
			puts("OK!\n");
		}
	} else {
		puts("skipped\n");
	}

	return ret;
}

/*
 * Verifies U-Boot image header checksum
 */
static int ih_header_crc(image_header_t *hdr, int tpl_type)
{
	u32 crc;
	int ret = 0;

	printf("   %-*s ", UBOOT_ALIGN_SIZE, "Header CRC...");

	if (tpl_type == 0) {
		crc = ntohl(hdr->ih_hcrc);
		hdr->ih_hcrc = 0;

		if (tinf_crc32((u8 *)hdr, sizeof(image_header_t)) != crc) {
			puts("ERROR\n\n");
			ret = 1;
		} else {
			puts("OK!\n");
		}

		hdr->ih_hcrc = crc;
	} else {
		puts("skipped\n");
	}

	return ret;
}

/*
 * Converts TP-Link header to stanard
 * U-Boot image format header
 */
static void tpl_to_uboot_header(image_header_t *hdr,
				tplink_image_header_t *tpl_hdr)
{
	memset(hdr, 0, sizeof(image_header_t));

	/* Set only needed values */
	hdr->ih_hcrc = 0;
	hdr->ih_dcrc = 0;

	hdr->ih_ep   = htonl(tpl_hdr->ih_kernel_ep);
	hdr->ih_size = htonl(tpl_hdr->ih_kernel_len);
	hdr->ih_load = htonl(tpl_hdr->ih_kernel_load);

	hdr->ih_os   = IH_OS_LINUX;
	hdr->ih_arch = IH_CPU_MIPS;
	hdr->ih_type = IH_TYPE_KERNEL;
	hdr->ih_comp = IH_COMP_LZMA;
}

int do_bootm(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *s;
	u32 *len_ptr;
	u32 addr, data, len;
	int i, tpl_type, verify;
	u32 unc_len = CFG_BOOTM_LEN;
	image_header_t *hdr = &header;
	tplink_image_header_t *tpl_hdr;

	/*
	 * By default don't verify data CRC checksum,
	 * but allow to enable it, using environment
	 **/
	s = getenv("verify_data");
	verify = (s && (*s == 'y')) ? 1 : 0;

	if (argc < 2) {
		addr = load_addr;
	} else {
		addr = simple_strtoul(argv[1], NULL, 16);
	}

	printf("Booting image from 0x%08lX...\n", addr);

	/* Check what header type we have */
	memmove(&data, (char *)addr, sizeof(u32));
	tpl_type = 0;

	switch (ntohl(data)) {
	case TPL_IH_VERSION_V1:
	case TPL_IH_VERSION_V2:
		tpl_type = 1;

		tpl_hdr = (tplink_image_header_t *)addr;
		print_tpl_ih_v1(tpl_hdr);

		/* Convert to general format */
		tpl_to_uboot_header(hdr, tpl_hdr);
		break;
	case IH_MAGIC:
		print_uboot_ih((image_header_t *)addr);
		memmove(&header, (char *)addr, sizeof(image_header_t));
		break;
	case TPL_IH_VERSION_V3:
	default:
		printf_err("unsupported image header\n");
		return 1;
	}

	/* Always verify header CRC */
	if (ih_header_crc(hdr, tpl_type) != 0) {
		printf_err("header checksum mismatch!\n");
		return 1;
	}

	/* And data if enabled */
	if (tpl_type) {
		data = addr + sizeof(tplink_image_header_t);
	} else {
		data = addr + sizeof(image_header_t);
	}

	if (ih_data_crc(data, hdr, tpl_type, verify) != 0) {
		printf_err("data checksum mismatch!\n");
		return 1;
	}

	puts("\n");

	len = ntohl(hdr->ih_size);
	len_ptr = (u32 *)data;

	/* We support only MIPS */
	if (hdr->ih_arch != IH_CPU_MIPS) {
		printf_err("unsupported architecture!\n");
		return 1;
	}

	/* Image type... */
	switch (hdr->ih_type) {
	case IH_TYPE_KERNEL:
		break;
	case IH_TYPE_MULTI:
		/* OS kernel is always in first image */
		len = ntohl(len_ptr[0]);
		data += 8;

		/* Move over list to first image */
		for (i = 1; len_ptr[i]; ++i)
			data += 4;

		break;
	default:
		printf_err("unsupported image type!\n");
		return 1;
	}

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
	puts("Stopping network... ");
	eth_halt();
	puts("OK!\n");
#endif

	/* TODO: should we flush caches for kernel? */
	/*
	 * Flush everything, restore caches for linux
	 */
	//mips_cache_flush();
	//mips_icache_flush_ix();

	/* XXX - this causes problems when booting from flash */
	/* dcache_disable(); */

	/* Compression type... */
	switch (hdr->ih_comp) {
	case IH_COMP_LZMA:
		printf("Uncompressing %s... ", ih_img_type(hdr->ih_type));

		/* Try to extract LZMA data... */
		i = lzma_inflate((u8 *)data, len,
			(u8 *)ntohl(hdr->ih_load), (int *)&unc_len);

		/* TODO: more verbose LZMA errors */
		if (i != LZMA_RESULT_OK) {
			puts("ERROR\n");
			printf_err("LZMA error '%d'!\n", i);
			return 1;
		}

		puts("OK!\n");
		break;
	default:
		printf_err("unsupported compression type '%s'!\n",
			   ih_comp_type(hdr->ih_comp));

		return 1;
	}

#ifdef CONFIG_SILENT_CONSOLE
	fixup_silent_linux();
#endif

	do_bootm_linux(cmdtp, flag, argc, argv);

	return 1;
}

U_BOOT_CMD(bootm, 2, 1, do_bootm,
	"boot application image from memory\n", "[addr]\n"
	"\t- boot application image stored in memory at address 'addr'\n");

#if defined(CONFIG_CMD_BOOTD)
int do_bootd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
#ifndef CFG_HUSH_PARSER
	if (run_command(getenv("bootcmd"), flag) < 0)
		return 1;
#else
	if (parse_string_outer(getenv("bootcmd"),
		FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		return 1;
#endif

	return 0;
}

U_BOOT_CMD(boot, 1, 1, do_bootd, "boot default, run 'bootcmd'\n", NULL);
#endif /* CONFIG_CMD_BOOTD */

#if defined(CONFIG_CMD_IMI)
int do_iminfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int tpl_type;
	u32 addr, data;
	image_header_t *hdr = &header;
	tplink_image_header_t *tpl_hdr;

	tpl_type = 0;

	if (argc == 2) {
		addr = simple_strtoul(argv[1], NULL, 16);
	} else {
		print_cmd_help(cmdtp);
		return 1;
	}

	printf("\nChecking image at 0x%08lX...\n", addr);

	/* Check what header type we have */
	memmove(&data, (char *)addr, sizeof(u32));

	switch (ntohl(data)) {
	case TPL_IH_VERSION_V1:
	case TPL_IH_VERSION_V2:
		tpl_type = 1;

		tpl_hdr = (tplink_image_header_t *)addr;
		print_tpl_ih_v1(tpl_hdr);
		break;
	case IH_MAGIC:
		print_uboot_ih((image_header_t *)addr);
		memmove(&header, (char *)addr, sizeof(image_header_t));
		break;
	case TPL_IH_VERSION_V3:
	default:
		printf_err("unsupported image header\n");
		return 1;
	}

	/* Always verify header CRC */
	if (ih_header_crc(hdr, tpl_type) != 0) {
		printf_err("header checksum mismatch!\n");
		return 1;
	}

	/* And data.. here always */
	if (tpl_type) {
		data = addr + sizeof(tplink_image_header_t);
	} else {
		data = addr + sizeof(image_header_t);
	}

	if (ih_data_crc(data, hdr, tpl_type, 1) != 0) {
		printf_err("data checksum mismatch!\n");
		return 1;
	}

	puts("\n");

	return 0;
}

U_BOOT_CMD(iminfo, 2, 1, do_iminfo,
	"print firmware header\n", "address\n"
	"\t- print header information for image at 'address'\n");
#endif /* CONFIG_CMD_IMI */
