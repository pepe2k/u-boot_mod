/*
 *	Copyright 1994, 1995, 2000 Neil Russell.
 *	(See License)
 *	Copyright 2000, 2001 DENX Software Engineering, Wolfgang Denk, wd@denx.de
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include "tftp.h"
#include "bootp.h"

#undef	ET_DEBUG

#if defined(CONFIG_CMD_NET)

DECLARE_GLOBAL_DATA_PTR;

#define WELL_KNOWN_PORT		69	/* Well known TFTP port # */
#define TIMEOUT			5	/* Seconds to timeout for a lost pkt */

#if !defined(CONFIG_NET_RETRY_COUNT)
	#define TIMEOUT_COUNT	10	/* # of timeouts before giving up */
#else
	#define TIMEOUT_COUNT	(CONFIG_NET_RETRY_COUNT * 2)
#endif

#define HASHES_PER_LINE		40	/* Number of "loading"/"saving" hashes per line */

/*
 * TFTP operations
 */
#define TFTP_RRQ	1
#define TFTP_WRQ	2
#define TFTP_DATA	3
#define TFTP_ACK	4
#define TFTP_ERROR	5
#define TFTP_OACK	6

static int TftpServerPort;		/* The UDP port at their end */
static int TftpOurPort;			/* The UDP port at our end */
static int TftpTimeoutCount;
static int TftpState;
static int TftpWriting;			/* 1 if writing, else 0 */
static int TftpFinalBlock;		/* 1 if we have sent the last block */

static ulong TftpBlock;			/* Packet sequence number */
static ulong TftpLastBlock;		/* Last packet sequence number received */
static ulong TftpBlockWrap;		/* Count of sequence number wraparounds */
static ulong TftpBlockWrapOffset;	/* Memory offset due to wrapping */

#define STATE_RRQ	1
#define STATE_DATA	2
#define STATE_TOO_LARGE	3
#define STATE_BAD_MAGIC	4
#define STATE_OACK	5
#define STATE_WRQ	7

#define TFTP_BLOCK_SIZE		512			/* Default TFTP block size */
#define TFTP_SEQUENCE_SIZE	((ulong)(1<<16))	/* Sequence number is 16 bit */

#define DEFAULT_NAME_LEN	(8 + 4 + 1)

static char default_filename[DEFAULT_NAME_LEN];
static char *tftp_filename;

#if defined(CFG_DIRECT_FLASH_TFTP)
	extern flash_info_t flash_info[];
#endif

static __inline__ void store_block(unsigned block, uchar *src, unsigned len)
{
	ulong offset  = block * TFTP_BLOCK_SIZE + TftpBlockWrapOffset;
	ulong newsize = offset + len;

#if defined(CFG_DIRECT_FLASH_TFTP)
	int i, rc = 0;

	for (i = 0; i < CFG_MAX_FLASH_BANKS; i++) {
		/* Start address in flash? */
		if (load_addr + offset >= flash_info[i].start[0]) {
			rc = 1;
			break;
		}
	}

	/* Flash is destination for this packet */
	if (rc) {
		rc = flash_write((char *)src, (ulong)(load_addr + offset),
				 len);

		if (rc) {
			flash_perror(rc);
			NetState = NETLOOP_FAIL;
			return;
		}
	} else
#endif /* CFG_DIRECT_FLASH_TFTP */
	{
		(void)memcpy((void *)(load_addr + offset), src, len);
	}

	if (NetBootFileXferSize < newsize)
		NetBootFileXferSize = newsize;
}

/* Load the next block from memory to be sent over tftp */
static int load_block(unsigned block, uchar *dst, unsigned len)
{
	ulong offset = (block - 1) * len + TftpBlockWrapOffset;
	ulong tosend = len;

	tosend = min(NetBootFileXferSize - offset, tosend);
	(void)memcpy(dst, (void *)(save_addr + offset), tosend);

	return tosend;
}

/* Show download/upload progress */
static void show_progress(const ulong TftpBlock)
{
	if (((TftpBlock - 1) % 10) == 0)
		putc('#');
	else if ((TftpBlock % (10 * HASHES_PER_LINE)) == 0)
		puts("\n              ");
}

static void show_success(void)
{
	puts("\n\nTFTP transfer complete!\n");
	NetState = NETLOOP_SUCCESS;
}

static void TftpSend(void);
static void TftpTimeout(void);

static void TftpSend(void)
{
	int len = 0;
	uchar *pkt, *xp;
	volatile ushort *s;

	/*
	 * We will always be sending some sort of packet, so
	 * cobble together the packet headers now.
	 */
	pkt = (uchar *)(NetTxPacket + NetEthHdrSize() + IP_HDR_SIZE);

	switch (TftpState) {
	case STATE_RRQ:
	case STATE_WRQ:
		xp = pkt;
		s = (ushort *)pkt;
		*s++ = htons(TftpState == STATE_RRQ ? TFTP_RRQ : TFTP_WRQ);

		pkt = (uchar *)s;
		strcpy((char *)pkt, tftp_filename);

		pkt += strlen(tftp_filename) + 1;
		strcpy((char *)pkt, "octet");

		pkt += 6; /* strlen("octet") + 1 */
		strcpy((char *)pkt, "timeout");

		pkt += 8; /* strlen("timeout") + 1 */
		sprintf((char *)pkt, "%d", TIMEOUT);

#if defined(ET_DEBUG)
		printf("send option \"timeout %s\"\n", (char *)pkt);
#endif

		pkt += strlen((char *)pkt) + 1;
		len = pkt - xp;
		break;
	case STATE_DATA:
	case STATE_OACK:
		xp = pkt;
		s = (ushort *)pkt;

		s[0] = htons(TFTP_ACK);
		s[1] = htons(TftpBlock);
		pkt = (uchar *)(s + 2);

		if (TftpWriting) {
			int toload = TFTP_BLOCK_SIZE;
			int loaded = load_block(TftpBlock, pkt, toload);

			s[0] = htons(TFTP_DATA);
			pkt += loaded;

			TftpFinalBlock = (loaded < toload);
		}

		len = pkt - xp;
		break;
	case STATE_TOO_LARGE:
		xp = pkt;
		s = (ushort *)pkt;
		*s++ = htons(TFTP_ERROR);
		*s++ = htons(3);
		pkt = (uchar *)s;
		strcpy((char *)pkt, "File too large");
		pkt += 15; /* strlen("File too large") + 1 */
		len = pkt - xp;
		break;
	case STATE_BAD_MAGIC:
		xp = pkt;
		s = (ushort *)pkt;
		*s++ = htons(TFTP_ERROR);
		*s++ = htons(2);
		pkt = (uchar *)s;
		strcpy((char *)pkt, "File has bad magic");
		pkt += 19; /* strlen("File has bad magic") + 1 */
		len = pkt - xp;
		break;
	}

	NetSendUDPPacket(NetServerEther, NetServerIP, TftpServerPort,
			 TftpOurPort, len);
}

static void TftpHandler(uchar *pkt, unsigned dest, unsigned src, unsigned len)
{
	int block;
	ushort proto, *s;
	bd_t *bd = gd->bd;

	if (dest != TftpOurPort)
		return;

	if (TftpState != STATE_RRQ && TftpState != STATE_WRQ &&
	    src != TftpServerPort)
		return;

	if (len < 2)
		return;

	len -= 2;

	/* Warning: don't use increment (++) in ntohs() macros!! */
	s = (ushort *)pkt;
	proto = *s++;
	pkt = (uchar *)s;

	block = ntohs(*s);

	switch (ntohs(proto)) {
	case TFTP_RRQ:
	case TFTP_WRQ:
		break;
	case TFTP_ACK:
		if (TftpWriting) {
			if (TftpFinalBlock) {
				show_success();
			} else {
				show_progress(TftpBlock);
				TftpBlock = block + 1;

				NetSetTimeout(TIMEOUT * CFG_HZ, TftpTimeout);

				TftpSend();
			}
		}

		break;
	case TFTP_OACK:
#if defined(ET_DEBUG)
		printf("Got OACK: %s %s\n", pkt, pkt+strlen(pkt)+1);
#endif
		TftpState = STATE_OACK;
		TftpServerPort = src;

		if (TftpWriting) {
			/* Get ready to send the first block */
			TftpState = STATE_DATA;
			TftpBlock++;
		}

		NetSetTimeout(TIMEOUT * CFG_HZ, TftpTimeout);

		TftpSend();
		break;
	case TFTP_DATA:
		if (len < 2)
			return;

		len -= 2;
		TftpBlock = ntohs(*(ushort *)pkt);

		/*
		 * RFC1350 specifies that the first data packet will
		 * have sequence number 1. If we receive a sequence
		 * number of 0 this means that there was a wrap
		 * around of the (16 bit) counter.
		 */
		if (TftpBlock == 0) {
			TftpBlockWrap++;
			TftpBlockWrapOffset += TFTP_BLOCK_SIZE * TFTP_SEQUENCE_SIZE;

			puts("\n");
			puts("\n              ");
			printf("[ %lu MB ]\n",
			       TftpBlockWrapOffset >> 20);
			puts("\n              ");
		} else
			show_progress(TftpBlock);

#if defined(ET_DEBUG)
		if (TftpState == STATE_RRQ)
			printf_err("server did not ACK timeout option!\n");
#endif

		if (TftpState == STATE_RRQ || TftpState == STATE_OACK) {
			/* First block received */
			TftpState = STATE_DATA;
			TftpServerPort = src;
			TftpLastBlock = 0;
			TftpBlockWrap = 0;
			TftpBlockWrapOffset = 0;

			if (TftpBlock != 1) {
				puts("\n");
				printf_err("first block is not block 1 (%ld), starting again!\n\n", TftpBlock);
				NetStartAgain();
				break;
			}
		}

		/* Same block again; ignore it */
		if (TftpBlock == TftpLastBlock)
			break;

		TftpLastBlock = TftpBlock;
		NetSetTimeout(TIMEOUT * CFG_HZ, TftpTimeout);

		store_block(TftpBlock - 1, pkt + 2, len);

		/*
		 * Acknoledge the block just received, which will prompt
		 * the server for the next one.
		 */
		TftpSend();

		if (len < TFTP_BLOCK_SIZE)
			show_success();

		break;
	case TFTP_ERROR:
		puts("\n");
		printf_err("'%s' (%d), starting again!\n\n",
			   pkt + 2, ntohs(*(ushort *)pkt));

		NetStartAgain();
		break;
	default:
		break;
	}
}

static void TftpTimeout(void)
{
	bd_t *bd = gd->bd;

	if (++TftpTimeoutCount > TIMEOUT_COUNT) {
		puts("\n\n");
		printf_err("retry count exceeded, starting again!\n\n");
		NetStartAgain();
	} else {
		puts("T ");
		NetSetTimeout(TIMEOUT * CFG_HZ, TftpTimeout);
		TftpSend();
	}
}

void TftpStart(proto_t protocol)
{
	bd_t *bd = gd->bd;

#ifdef CONFIG_TFTP_PORT
	/* Environment pointer */
	char *ep;
#endif

	if (BootFile[0] == '\0') {
		sprintf(default_filename,
			"%02lX%02lX%02lX%02lX.img",
			(NetOurIP >> 0)  & 0xFF,
			(NetOurIP >> 8)  & 0xFF,
			(NetOurIP >> 16) & 0xFF,
			(NetOurIP >> 24) & 0xFF);

		tftp_filename = default_filename;

		printf_wrn("no boot file name, using: '%s'\n", tftp_filename);
	} else
		tftp_filename = BootFile;

	printf("\n%s ", protocol == TFTPPUT ? "  TFTP to IP:" : "TFTP from IP:");
	print_IPaddr(NetServerIP);

	puts("\n      Our IP: ");
	print_IPaddr(NetOurIP);

	/* Check if we need to send across this subnet */
	if (NetOurGatewayIP && NetOurSubnetMask) {
		IPaddr_t OurNet    = NetOurIP    & NetOurSubnetMask;
		IPaddr_t ServerNet = NetServerIP & NetOurSubnetMask;

		if (OurNet != ServerNet) {
			puts("\n  Gateway IP: ");
			print_IPaddr(NetOurGatewayIP) ;
		}
	}

	printf("\n    Filename: %s", tftp_filename);

#if defined(CONFIG_NET_MULTI)
	printf("\n       Using: %s", eth_get_name());
#endif

	TftpWriting = (protocol == TFTPPUT);

	if (TftpWriting) {
		printf("\nSave address: 0x%lX", save_addr);
		printf("\n   Save size: 0x%lX (", save_size);
		print_size(save_size, ")");
		puts("\n\n     Sending: *\b");

		NetBootFileXferSize = save_size;
		TftpFinalBlock = 0;

		TftpState = STATE_WRQ;
	} else {
		printf("\nLoad address: 0x%lX", load_addr);

		if (NetBootFileSize) {
			printf("\n   Load size: 0x%lX (", NetBootFileSize << 9);
			print_size(NetBootFileSize << 9, ")");
		}

		puts("\n\n     Loading: *\b");

		TftpState = STATE_RRQ;
	}

	NetSetTimeout(TIMEOUT * CFG_HZ, TftpTimeout);
	NetSetHandler(TftpHandler);

	TftpServerPort   = WELL_KNOWN_PORT;
	TftpTimeoutCount = 0;

	/* Use a pseudo-random port unless a specific port is set */
	TftpOurPort = 1024 + (get_timer(0) % 3072);

#if defined(CONFIG_TFTP_PORT)
	if ((ep = getenv("tftpdstp")) != NULL)
		TftpServerPort = simple_strtol(ep, NULL, 10);

	if ((ep = getenv("tftpsrcp")) != NULL)
		TftpOurPort= simple_strtol(ep, NULL, 10);
#endif

	TftpBlock = 0;

	/* Zero out server ether in case the server ip has changed */
	memset(NetServerEther, 0, 6);

	TftpSend();
}
#endif /* CONFIG_CMD_NET */
