/*
 * (C) Copyright 2000-2002
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
#include <command.h>
#include <net.h>
#include "nfs.h"
#include "bootp.h"
#include "rarp.h"
#include "tftp.h"

#if defined(CONFIG_CMD_NET)

DECLARE_GLOBAL_DATA_PTR;

#define TIMEOUT	5	/* Seconds before trying BOOTP again */

#if !defined(CONFIG_NET_RETRY_COUNT)
	/* # of timeouts before giving up  */
	#define TIMEOUT_COUNT	5
#else
	#define TIMEOUT_COUNT	(CONFIG_NET_RETRY_COUNT)
#endif

int RarpTry;

/* Handle a RARP received packet */
static void RarpHandler(uchar   *dummi0,
			unsigned dummi1,
			unsigned dummi2,
			unsigned dummi3)
{
	char *s;

#if defined(DEBUG)
	puts ("Got good RARP\n");
#endif

	if ((s = getenv("autoload")) != NULL) {
		if (*s == 'n') {
			/*
			 * Just use RARP to configure system;
			 * Do not use TFTP/NFS to to load the bootfile.
			 */
			NetState = NETLOOP_SUCCESS;
			return;
#if defined(CONFIG_CMD_NFS)
		} else if ((s != NULL) && !strcmp(s, "NFS")) {
			NfsStart();
			return;
#endif
		}
	}

	TftpStart(TFTPGET);
}

/* Timeout on BOOTP request */
static void RarpTimeout(void)
{
	bd_t *bd = gd->bd;

	if (RarpTry >= TIMEOUT_COUNT) {
		puts("\nRetry count exceeded; starting again\n");
		NetStartAgain();
	} else {
		NetSetTimeout(TIMEOUT * CFG_HZ, RarpTimeout);
		RarpRequest();
	}
}

void RarpRequest(void)
{
	int i;
	ARP_t *rarp;
	bd_t *bd = gd->bd;
	volatile uchar *pkt;

	printf("RARP broadcast %d\n", ++RarpTry);
	pkt = NetTxPacket;

	pkt += NetSetEther(pkt, NetBcastAddr, PROT_RARP);

	rarp = (ARP_t *)pkt;

	rarp->ar_hrd = htons(ARP_ETHER);
	rarp->ar_pro = htons(PROT_IP);
	rarp->ar_hln = 6;
	rarp->ar_pln = 4;
	rarp->ar_op  = htons(RARPOP_REQUEST);

	memcpy(&rarp->ar_data[0],  NetOurEther, 6);	/* source ET addr */
	memcpy(&rarp->ar_data[6],  &NetOurIP,   4);	/* source IP addr */
	memcpy(&rarp->ar_data[10], NetOurEther, 6);	/* dest ET addr = source ET addr ??*/

	/* Dest. IP addr set to broadcast */
	for (i = 0; i <= 3; i++)
		rarp->ar_data[16 + i] = 0xff;

	NetSendPacket(NetTxPacket, (pkt - NetTxPacket) + ARP_HDR_SIZE);

	NetSetTimeout(TIMEOUT * CFG_HZ, RarpTimeout);
	NetSetHandler(RarpHandler);
}
#endif /* CONFIG_CMD_NET */
