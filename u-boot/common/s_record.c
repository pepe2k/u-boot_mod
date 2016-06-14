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

#include <common.h>
#include <s_record.h>

static int hex1_bin(char  c);
static int hex2_bin(char *s);

int srec_decode(char *input, int *count, ulong *addr, char *data)
{
	int	i;
	int	v;					/* conversion buffer */
	int	srec_type;			/* S-Record type */
	unsigned char chksum;	/* buffer for checksum */

	chksum = 0;

	/* skip anything before 'S', and the 'S' itself.
	 * Return error if not found
	 */

	for(; *input; ++input){
		/* skip 'S' */
		if(*input == 'S'){
			++input;
			break;
		}
	}

	/* no more data? */
	if(*input == '\0'){
		return(SREC_EMPTY);
	}

	/* record type */
	v = *input++;

	if((*count = hex2_bin(input)) < 0){
		return(SREC_E_NOSREC);
	}

	chksum += *count;
	input  += 2;

	/* record type */
	switch(v){
	/* start record */
	case '0':
		srec_type = SREC_START;	/* 2 byte addr field */
		*count   -= 3;			/* - checksum and addr */
		break;
	case '1':
		srec_type = SREC_DATA2;	/* 2 byte addr field */
		*count   -= 3;			/* - checksum and addr */
		break;
	case '2':
		srec_type = SREC_DATA3;	/* 3 byte addr field */
		*count   -= 4;			/* - checksum and addr */
		break;
	/* data record with a */
	case '3':
		srec_type = SREC_DATA4;	/* 4 byte addr field */
		*count   -= 5;			/* - checksum and addr */
		break;
	/* count record, addr field contains */
	case '5':
		srec_type = SREC_COUNT;	/* a 2 byte record counter */
		*count    = 0;			/* no data */
		break;
	/* end record with a */
	case '7':
		srec_type = SREC_END4;	/* 4 byte addr field */
		*count   -= 5;			/* - checksum and addr */
		break;
	/* end record with a */
	case '8':
		srec_type = SREC_END3;	/* 3 byte addr field */
		*count   -= 4;			/* - checksum and addr */
		break;
	/* end record with a */
	case '9':
		srec_type = SREC_END2;	/* 2 byte addr field */
		*count   -= 3;			/* - checksum and addr */
		break;
	default:
		return(SREC_E_BADTYPE);
	}

	/* read address field */
	*addr = 0;

	switch(v){
	/* 4 byte addr field */
	case '3':
	case '7':
		if((v = hex2_bin(input)) < 0){
			return(SREC_E_NOSREC);
		}

		*addr  += v;
		chksum += v;
		input  += 2;
		/* FALL THRU */
	/* 3 byte addr field */
	case '2':
	case '8':
		if((v = hex2_bin(input)) < 0){
			return(SREC_E_NOSREC);
		}

		*addr <<= 8;
		*addr  += v;
		chksum += v;
		input  += 2;
		/* FALL THRU */
	/* 2 byte addr field */
	case '0':
	case '1':
	case '5':
	case '9':
		if((v = hex2_bin(input)) < 0){
			return(SREC_E_NOSREC);
		}

		*addr <<= 8;
		*addr  += v;
		chksum += v;
		input  += 2;

		if((v = hex2_bin(input)) < 0){
			return(SREC_E_NOSREC);
		}

		*addr <<= 8;
		*addr  += v;
		chksum += v;
		input  += 2;
		break;
	default:
		return(SREC_E_BADTYPE);
	}

	/* convert data and calculate checksum */
	for(i=0; i < *count; ++i){
		if((v = hex2_bin(input)) < 0){
			return(SREC_E_NOSREC);
		}

		data[i] = v;
		chksum += v;
		input  += 2;
	}

	/* read anc check checksum */
	if((v = hex2_bin(input)) < 0){
		return(SREC_E_NOSREC);
	}

	if((unsigned char)v != (unsigned char)~chksum){
		return(SREC_E_BADCHKS);
	}

	return(srec_type);
}

static int hex1_bin(char c)
{
	if(c >= '0' && c <= '9')
		return(c - '0');

	if(c >= 'a' && c <= 'f')
		return(c + 10 - 'a');

	if(c >= 'A' && c <= 'F')
		return(c + 10 - 'A');

	return(-1);
}

static int hex2_bin(char *s)
{
	int i, j;

	if((i = hex1_bin(*s++)) < 0)
		return(-1);

	if((j = hex1_bin(*s)) < 0)
		return(-1);

	return((i<<4) + j);
}
