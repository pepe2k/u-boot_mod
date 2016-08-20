/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * Based on mktplinkfw.c from OpenWrt
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef __TPLINK_IMAGE_H__
#define __TPLINK_IMAGE_H__

#define TPL_IH_VERSION_V1	0x01000000
#define TPL_IH_VERSION_V2	0x02000000
#define TPL_IH_VERSION_V3	0x03000000

#define MD5SUM_LEN	16

/* For v1 version of header version */
typedef struct tplink_image_header {		/* ofs (size): what                     */
	uint32_t ih_version;			/* 0x0    (4): header version           */
	char     ih_vendor[24];			/* 0x4   (24): vendor name (text)       */
	char     ih_info[36];			/* 0x1C  (36): other info like version  */
	uint32_t ih_hw_id;			/* 0x40   (4): hardware ID              */
	uint32_t ih_hw_ver;			/* 0x44   (4): hardware version         */
	uint32_t ih_region;			/* 0x48   (4): region code              */
	uint8_t  ih_md5sum1[MD5SUM_LEN];	/* 0x4C  (16): MD5 sum #1               */
	uint32_t ih_ignore1;			/* 0x5C   (4): unknown                  */
	uint8_t  ih_md5sum2[MD5SUM_LEN];	/* 0x60  (16): MD5 sum #2               */
	uint32_t ih_ignore2;			/* 0x70   (4): unknown                  */
	uint32_t ih_kernel_load;		/* 0x74   (4): kernel load address      */
	uint32_t ih_kernel_ep;			/* 0x78   (4): kernel entry point       */
	uint32_t ih_fw_len;			/* 0x7C   (4): image size (with header) */
	uint32_t ih_kernel_ofs;			/* 0x80   (4): kernel data offset       */
	uint32_t ih_kernel_len;			/* 0x84   (4): kernel data size         */
	uint32_t ih_rootfs_ofs;			/* 0x88   (4): rootfs data offset       */
	uint32_t ih_rootfs_len;			/* 0x8C   (4): rootfs data size         */
	uint32_t ih_boot_ofs;			/* 0x90   (4): bootloader data offset   */
	uint32_t ih_boot_len;			/* 0x94   (4): bootloader data size     */
	uint16_t ih_fw_ver_hi;			/* 0x98   (2): firmware version hi      */
	uint16_t ih_fw_ver_mid;			/* 0x9A   (2): firmware version mid     */
	uint16_t ih_fw_ver_lo;			/* 0x9C   (2): firmware version lo      */
	uint8_t  ih_pad[354];			/* 0x9E (354): padding, not used...     */
} tplink_image_header_t;

#endif /* __TPLINK_IMAGE_H__ */
