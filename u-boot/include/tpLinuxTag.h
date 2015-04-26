
/**************************************************************************************
* File Name  : tpLinuxTag.h
*
* Description: add tag with validation system to the firmware image file to be uploaded
*              via http
*
* Created    : 16Sep07,	Liang Qiming
**************************************************************************************/

#ifndef _TP_LINUX_TAG_H_
#define _TP_LINUX_TAG_H_

/*
 * File tag (head) structure all is in clear text
 * except validationTokens (crc, md5, sha1, etc).
 *
 * Total: 128 unsigned chars
 */
#define TAG_LEN			512
#define SIG_LEN			24
#define SIG_LEN_2		12 // Original second SIG = 20 is now devided into 14 for SIG_LEN_2 and 6 for CHIP_ID
#define CHIP_ID_LEN		8
#define TOKEN_LEN		20
#define BOARD_ID_LEN	16

/*
 * TAG for downloadable image (kernel plus file system)
 * integer in the structure is stored in Network-Byte order (BIG-endian)
 */
typedef struct _tplink_image_header_t {
	unsigned long	tagVersion;
    char			signiture_1[SIG_LEN];				// text line for company info
	char			signiture_2[SIG_LEN_2];				// additional info (can be version number)
    char			chipId[CHIP_ID_LEN];				// chip id
    char			boardId[BOARD_ID_LEN];				// board id
    unsigned long	productId;							// product id
    unsigned long	productVer;							// product version
    unsigned long	reserved1;							// reserved for future

    unsigned char	imageValidationToken[TOKEN_LEN];	// image validation token - md5 checksum
    unsigned char	kernelValidationToken[TOKEN_LEN];	// kernel+tag validation token - md5 checksum

	unsigned long	kernelTextAddr;						// text section address of kernel
	unsigned long	kernelEntryPoint;					// entry point address of kernel
	
	unsigned long	totalImageLen;						// the sum of kernelLen+rootfsLen+tagLen

	unsigned long	kernelAddress;						// starting address (offset from the beginning of FILE_TAG) of kernel image
	unsigned long	kernelLen;							// length of kernel image

	unsigned long	rootfsAddress;						// starting address (offset) of filesystem image
	unsigned long	rootfsLen;							// length of filesystem image

	unsigned long	bootloaderAddress;					// starting address (offset) of boot loader image
	unsigned long	bootloaderLen;						// length of boot loader image
	
} tplink_image_header_t;

#endif /* ifndef _TP_LINUX_TAG_H_ */
