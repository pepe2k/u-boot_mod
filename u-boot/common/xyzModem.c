/*
 *==========================================================================
 *
 *	  xyzModem.c
 *
 *	  RedBoot stream handler for xyzModem protocol
 *
 *==========================================================================
 *####ECOSGPLCOPYRIGHTBEGIN####
 * -------------------------------------------
 * This file is part of eCos, the Embedded Configurable Operating System.
 * Copyright (C) 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.
 * Copyright (C) 2002 Gary Thomas
 *
 * eCos is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 or (at your option) any later version.
 *
 * eCos is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with eCos; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * As a special exception, if other files instantiate templates or use macros
 * or inline functions from this file, or you compile this file and link it
 * with other works to produce a work based on this file, this file does not
 * by itself cause the resulting work to be covered by the GNU General Public
 * License. However the source code for this file must still be made available
 * in accordance with section (3) of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 *
 * Alternative licenses for eCos may be arranged by contacting Red Hat, Inc.
 * at http: *sources.redhat.com/ecos/ecos-license/
 * -------------------------------------------
 *####ECOSGPLCOPYRIGHTEND####
 *==========================================================================
 *#####DESCRIPTIONBEGIN####
 *
 * Author(s):	gthomas
 * Contributors: gthomas, tsmith, Yoshinori Sato
 * Date:		 2000-07-14
 * Purpose:
 * Description:
 *
 * This code is part of RedBoot (tm).
 *
 *####DESCRIPTIONEND####
 *
 *==========================================================================
 */
#include <common.h>
#include <xyzModem.h>
#include <stdarg.h>
#include <crc.h>

/* Assumption - run xyzModem protocol over the console port */

/* Values magic to the protocol */
#define SOH 0x01
#define STX 0x02
#define EOT 0x04
#define ACK 0x06
#define BSP 0x08
#define NAK 0x15
#define CAN 0x18
#define EOF 0x1A /* ^Z for DOS officionados */

#define USE_YMODEM_LENGTH

/* Data & state local to the protocol */
static struct {
	int *__chan;
	unsigned char pkt[1024], *bufp;
	unsigned char blk,cblk,crc1,crc2;
	unsigned char next_blk;  /* Expected block */
	int len, mode, total_retries;
	int total_SOH, total_STX, total_CAN;
	unsigned int crc_mode, at_eof, tx_ack;
#ifdef USE_YMODEM_LENGTH
	unsigned long file_length, read_length;
#endif
} xyz;

#define xyzModem_CHAR_TIMEOUT			2000	/* 2 seconds */
#define xyzModem_MAX_RETRIES			20
#define xyzModem_MAX_RETRIES_WITH_CRC	10
#define xyzModem_CAN_COUNT				3		/* Wait for 3 CAN before quitting */

int comm_if_getc_tout(char *c)
{
	unsigned long counter=0;
	#define DELAY 20

	while(!tstc() && (counter < xyzModem_CHAR_TIMEOUT*1000/DELAY)){
		udelay(DELAY);
		counter++;
	}

	if(tstc()){
		*c=getc();
		return 1;
	}

	return 0;
}

/* Validate a hex character */
inline static unsigned int _is_hex(char c)
{
	return(((c >= '0') && (c <= '9')) ||
		   ((c >= 'A') && (c <= 'F')) ||
		   ((c >= 'a') && (c <= 'f')));
}

/* Convert a single hex nibble */
inline static int _from_hex(char c)
{
	int ret = 0;

	if((c >= '0') && (c <= '9')){
		ret = (c - '0');
	} else if((c >= 'a') && (c <= 'f')){
		ret = (c - 'a' + 0x0a);
	} else if((c >= 'A') && (c <= 'F')){
		ret = (c - 'A' + 0x0A);
	}

	return ret;
}

/* Convert a character to lower case */
inline static char _tolower(char c)
{
	if((c >= 'A') && (c <= 'Z')){
		c = (c - 'A') + 'a';
	}

	return c;
}

/* Parse (scan) a number */
unsigned int parse_num(char *s, unsigned long *val, char **es, char *delim)
{
	unsigned int first = 1;
	int radix = 10;
	char c;
	unsigned long result = 0;
	int digit;

	while(*s == ' ')
		s++;

	while(*s){
		if(first && (s[0] == '0') && (_tolower(s[1]) == 'x')){
			radix = 16;
			s += 2;
		}

		first = 0;
		c = *s++;

		if(_is_hex(c) && ((digit = _from_hex(c)) < radix)){
			/* Valid digit */
			result = (result * radix) + digit;
		} else {
			if(delim != (char *)0){
				/* See if this character is one of the delimiters */
				char *dp = delim;

				while(*dp && (c != *dp))
					dp++;

				/* Found a good delimiter */
				if(*dp)
					break;
			}

			/* Malformatted number */
			return 0;
		}
	}

	*val = result;

	if(es != (char **)0){
		*es = s;
	}

	return 1;
}

/* Wait for the line to go idle */
static void xyzModem_flush(void)
{
	int res;
	char c;

	while(1){
		res = comm_if_getc_tout(&c);
		if(!res)
			return;
	}
}

static int xyzModem_get_hdr(void)
{
	char c;
	int res;
	unsigned int hdr_found = 0;
	int i, can_total, hdr_chars;
	unsigned short cksum;

	/* Find the start of a header */
	can_total = 0;
	hdr_chars = 0;

	if(xyz.tx_ack){
		putc(ACK);
		xyz.tx_ack = 0;
	}

	while(!hdr_found){
		res = comm_if_getc_tout(&c);

		if(res){
			hdr_chars++;

			switch(c){
			case SOH:
				xyz.total_SOH++;
			case STX:
				if(c == STX)
					xyz.total_STX++;

				hdr_found = 1;
				break;
			case CAN:
				xyz.total_CAN++;

				if(++can_total == xyzModem_CAN_COUNT){
					return xyzModem_cancel;
				} else {
					/* Wait for multiple CAN to avoid early quits */
					break;
				}
			case EOT:
				/* EOT only supported if no noise */
				if(hdr_chars == 1){
					putc(ACK);
					return xyzModem_eof;
				}
			default:
				/* Ignore, waiting for start of header */
				;
			}
		} else {
			/* Data stream timed out */
			xyzModem_flush(); /* Toss any current input */
			udelay(250000);
			return xyzModem_timeout;
		}
	}

	/* Header found, now read the data */
	res = comm_if_getc_tout((char *)&xyz.blk);
	if(!res){
		return xyzModem_timeout;
	}

	res = comm_if_getc_tout((char *)&xyz.cblk);
	if(!res){
		return xyzModem_timeout;
	}

	xyz.len = (c == SOH) ? 128 : 1024;
	xyz.bufp = xyz.pkt;
	for(i = 0;  i < xyz.len;  i++){
		res = comm_if_getc_tout(&c);
		if(res){
			xyz.pkt[i] = c;
		} else {
			return xyzModem_timeout;
		}
	}

	res = comm_if_getc_tout((char *)&xyz.crc1);
	if(!res){
		return xyzModem_timeout;
	}

	if(xyz.crc_mode){
		res = comm_if_getc_tout((char *)&xyz.crc2);
		if(!res){
			return xyzModem_timeout;
		}
	}

	/* Validate the message */
	if((xyz.blk ^ xyz.cblk) != (unsigned char)0xFF){
		xyzModem_flush();
		return xyzModem_frame;
	}

	/* Verify checksum/CRC */
	if(xyz.crc_mode){
		cksum = cyg_crc16(xyz.pkt, xyz.len);
		if(cksum != ((xyz.crc1 << 8) | xyz.crc2)){
			return xyzModem_cksum;
		}
	} else {
		cksum = 0;
		for(i = 0;  i < xyz.len;  i++){
			cksum += xyz.pkt[i];
		}

		if(xyz.crc1 != (cksum & 0xFF)){
			return xyzModem_cksum;
		}
	}

	/* If we get here, the message passes [structural] muster */
	return 0;
}

int xyzModem_stream_open(connection_info_t *info, int *err)
{
	int stat = 0;
	int retries = xyzModem_MAX_RETRIES;
	int crc_retries = xyzModem_MAX_RETRIES_WITH_CRC;

#ifdef xyzModem_zmodem
	if(info->mode == xyzModem_zmodem){
		*err = xyzModem_noZmodem;
		return -1;
	}
#endif

/* TODO: CHECK ! */
	int dummy;
	xyz.__chan=&dummy;
	xyz.len = 0;
	xyz.crc_mode = 1;
	xyz.at_eof = 0;
	xyz.tx_ack = 0;
	xyz.mode = info->mode;
	xyz.total_retries = 0;
	xyz.total_SOH = 0;
	xyz.total_STX = 0;
	xyz.total_CAN = 0;
#ifdef USE_YMODEM_LENGTH
	xyz.read_length = 0;
	xyz.file_length = 0;
#endif

	putc(xyz.crc_mode ? 'C' : NAK);

	if(xyz.mode == xyzModem_xmodem){
		/* X-modem doesn't have an information header - exit here */
		xyz.next_blk = 1;
		return 0;
	}

	while(retries-- > 0){
		stat = xyzModem_get_hdr();
		if(stat == 0){
			/* Y-modem file information header */
			if(xyz.blk == 0){
#ifdef USE_YMODEM_LENGTH
				/* skip filename */
				while(*xyz.bufp++);

				/* get the length */
				parse_num((char *)xyz.bufp, &xyz.file_length, NULL, " ");
#endif
				/* The rest of the file name data block quietly discarded */
				xyz.tx_ack = 1;
			}

			xyz.next_blk = 1;
			xyz.len = 0;

			return 0;
		} else if(stat == xyzModem_timeout){
			if(--crc_retries <= 0)
				xyz.crc_mode = 0;

			/* Extra delay for startup */
			udelay(5*100000);

			putc(xyz.crc_mode ? 'C' : NAK);
			xyz.total_retries++;
		}

		if(stat == xyzModem_cancel){
			break;
		}
	}

	*err = stat;

	return -1;
}

int xyzModem_stream_read(char *buf, int size, int *err)
{
	int stat, total, len;
	int retries;

	total = 0;
	stat = xyzModem_cancel;

	/* Try and get 'size' bytes into the buffer */
	while(!xyz.at_eof && (size > 0)){
		if(xyz.len == 0){
			retries = xyzModem_MAX_RETRIES;

			while(retries-- > 0){
				stat = xyzModem_get_hdr();
				if(stat == 0){
					if(xyz.blk == xyz.next_blk){
						xyz.tx_ack = 1;
						xyz.next_blk = (xyz.next_blk + 1) & 0xFF;

#if defined(xyzModem_zmodem) || defined(USE_YMODEM_LENGTH)
						if(xyz.mode == xyzModem_xmodem || xyz.file_length == 0){
#else
						if(1){
#endif
							/* Data blocks can be padded with ^Z (EOF) characters */
							/* This code tries to detect and remove them */
							if( (xyz.bufp[xyz.len-1] == EOF) &&
								(xyz.bufp[xyz.len-2] == EOF) &&
								(xyz.bufp[xyz.len-3] == EOF) ){
								while(xyz.len && (xyz.bufp[xyz.len-1] == EOF)){
									xyz.len--;
								}
							}
						}

#ifdef USE_YMODEM_LENGTH
						/*
						 * See if accumulated length exceeds that of the file.
						 * If so, reduce size (i.e., cut out pad bytes)
						 * Only do this for Y-modem (and Z-modem should it ever
						 * be supported since it can fall back to Y-modem mode).
						 */
						if(xyz.mode != xyzModem_xmodem && 0 != xyz.file_length){
							xyz.read_length += xyz.len;
							if(xyz.read_length > xyz.file_length){
								xyz.len -= (xyz.read_length - xyz.file_length);
							}
						}
#endif
						break;
					} else if(xyz.blk == ((xyz.next_blk - 1) & 0xFF)){
						/* Just re-ACK this so sender will get on with it */
						putc(ACK);
						continue; /* Need new header */
					} else {
						stat = xyzModem_sequence;
					}
				}

				if(stat == xyzModem_cancel){
					break;
				}

				if(stat == xyzModem_eof){
					putc(ACK);

					if(xyz.mode == xyzModem_ymodem){
						putc(xyz.crc_mode ? 'C' : NAK);
						xyz.total_retries++;
						stat = xyzModem_get_hdr();
						putc(ACK);
					}

					xyz.at_eof = 1;

					break;
				}

				putc(xyz.crc_mode ? 'C' : NAK);
				xyz.total_retries++;
			}

			if(stat < 0){
				*err = stat;
				xyz.len = -1;

				return total;
			}

		}

		/* Don't "read" data from the EOF protocol package */
		if(!xyz.at_eof){
			len = xyz.len;
			if(size < len)
				len = size;

			memcpy(buf, xyz.bufp, len);
			size     -= len;
			buf      += len;
			total    += len;
			xyz.len  -= len;
			xyz.bufp += len;
		}
	}

	return total;
}

void xyzModem_stream_close(int *err)
{
	printf("\n\nxyzModem - %s mode, %d(SOH)/%d(STX)/%d(CAN) packets, %d retries\n",
				xyz.crc_mode ? "CRC" : "Cksum",
				xyz.total_SOH, xyz.total_STX, xyz.total_CAN,
				xyz.total_retries);
}

/* Need to be able to clean out the input buffer, so have to take the */
/* getc */
void xyzModem_stream_terminate(unsigned int abort, int (*getc)(void))
{
	int c;

	if(abort){
		switch(xyz.mode){
		case xyzModem_xmodem:
		case xyzModem_ymodem:
			/* The X/YMODEM Spec seems to suggest that multiple CAN followed by an equal */
			/* number of Backspaces is a friendly way to get the other end to abort. */
			putc(CAN);
			putc(CAN);
			putc(CAN);
			putc(CAN);
			putc(BSP);
			putc(BSP);
			putc(BSP);
			putc(BSP);
			/* Now consume the rest of what's waiting on the line. */
			xyzModem_flush();
			xyz.at_eof = 1;
			break;
#ifdef xyzModem_zmodem
		case xyzModem_zmodem:
			/* Might support it some day I suppose. */
#endif
			break;
		}
	} else {
		/*
		 * Consume any trailing crap left in the inbuffer from
		 * previous recieved blocks. Since very few files are an exact multiple
		 * of the transfer block size, there will almost always be some gunk here.
		 * If we don't eat it now, RedBoot will think the user typed it.
		 */

		while((c = (*getc)()) > -1);
		/*
		* Make a small delay to give terminal programs like minicom
		* time to get control again after their file transfer program
		* exits.
		*/
		udelay(250000);
	}
}

char *xyzModem_error(int err)
{
	switch (err) {
	case xyzModem_access:
		return "can't access file";
		break;
	case xyzModem_noZmodem:
		return "sorry, zModem not available yet";
		break;
	case xyzModem_timeout:
		return "timed out";
		break;
	case xyzModem_eof:
		return "end of file";
		break;
	case xyzModem_cancel:
		return "cancelled";
		break;
	case xyzModem_frame:
		return "invalid framing";
		break;
	case xyzModem_cksum:
		return "CRC/checksum error";
		break;
	case xyzModem_sequence:
		return "block sequence error";
		break;
	default:
		return "unknown error";
		break;
	}
}
