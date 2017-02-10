/*
 *	Copied from Linux Monitor (LiMon) - Networking.
 *
 *	Copyright 1994 - 2000 Neil Russell.
 *	(See License)
 *	Copyright 2000 Roland Borde
 *	Copyright 2000 Paolo Scaffardi
 *	Copyright 2000-2002 Wolfgang Denk, wd@denx.de
 */

/*
 * General Desription:
 *
 * The user interface supports commands for BOOTP, RARP, and TFTP.
 * Also, we support ARP internally. Depending on available data,
 * these interact as follows:
 *
 * BOOTP:
 *
 *	Prerequisites:	- own ethernet address
 *	We want:	- own IP address
 *			- TFTP server IP address
 *			- name of bootfile
 *	Next step:	ARP
 *
 * RARP:
 *
 *	Prerequisites:	- own ethernet address
 *	We want:	- own IP address
 *			- TFTP server IP address
 *	Next step:	ARP
 *
 * ARP:
 *
 *	Prerequisites:	- own ethernet address
 *			- own IP address
 *			- TFTP server IP address
 *	We want:	- TFTP server ethernet address
 *	Next step:	TFTP
 *
 * DHCP:
 *
 *     Prerequisites:	- own ethernet address
 *     We want:		- IP, Netmask, ServerIP, Gateway IP
 *			- bootfilename, lease time
 *     Next step:	- TFTP
 *
 * TFTP:
 *
 *	Prerequisites:	- own ethernet address
 *			- own IP address
 *			- TFTP server IP address
 *			- TFTP server ethernet address
 *			- name of bootfile (if unknown, we use a default name
 *			  derived from our own IP address)
 *	We want:	- load the boot file
 *	Next step:	none
 *
 * NFS:
 *
 *	Prerequisites:	- own ethernet address
 *			- own IP address
 *			- name of bootfile (if unknown, we use a default name
 *			  derived from our own IP address)
 *	We want:	- load the boot file
 *	Next step:	none
 *
 * SNTP:
 *
 *	Prerequisites:	- own ethernet address
 *			- own IP address
 *	We want:	- network time
 *	Next step:	none
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include "bootp.h"
#include "tftp.h"
#include "rarp.h"
#include "nfs.h"
#if defined(CONFIG_CMD_HTTPD)
#include "httpd.h"
#endif

#if defined(CONFIG_CMD_SNTP)
#include "sntp.h"
#endif

#if defined(CONFIG_CMD_HTTPD)
#include "../httpd/uipopt.h"
#include "../httpd/uip.h"
#include "../httpd/uip_arp.h"
#endif

#if defined(CONFIG_CMD_NET)

DECLARE_GLOBAL_DATA_PTR;

#define ARP_TIMEOUT				5		/* Seconds before trying ARP again */

#ifndef	CONFIG_NET_RETRY_COUNT
	#define ARP_TIMEOUT_COUNT	5		/* # of timeouts before giving up  */
#else
	#define ARP_TIMEOUT_COUNT  (CONFIG_NET_RETRY_COUNT)
#endif

#if defined(CONFIG_CMD_HTTPD)
unsigned char *webfailsafe_data_pointer = NULL;
int	webfailsafe_is_running = 0;
int	webfailsafe_ready_for_upgrade = 0;
int	webfailsafe_upgrade_type = WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE;

void NetReceiveHttpd(volatile uchar * inpkt, int len);

extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
#endif

/** BOOTP EXTENTIONS **/
IPaddr_t NetOurSubnetMask = 0;		/* Our subnet mask (0=unknown) */
IPaddr_t NetOurGatewayIP = 0;		/* Our gateways IP address */
IPaddr_t NetOurDNSIP = 0;			/* Our DNS IP address */

#if (CONFIG_BOOTP_MASK & CONFIG_BOOTP_DNS2)
IPaddr_t NetOurDNS2IP = 0;			/* Our 2nd DNS IP address */
#endif

char NetOurNISDomain[32] = {0,};	/* Our NIS domain */
char NetOurHostName[32] = {0,};		/* Our hostname */
char NetOurRootPath[64] = {0,};		/* Our bootpath */
ushort NetBootFileSize = 0;			/* Our bootfile size in blocks */
/** END OF BOOTP EXTENTIONS **/

ulong NetBootFileXferSize;						/* The actual transferred size of the bootfile (in bytes) */
uchar NetOurEther[6];							/* Our ethernet address */
uchar NetServerEther[6] = {0, 0, 0, 0, 0, 0};	/* Boot server enet address */
IPaddr_t NetOurIP;								/* Our IP addr (0 = unknown) */
IPaddr_t NetServerIP;							/* Server IP addr (0 = unknown) */
volatile uchar *NetRxPkt;						/* Current receive packet */
int NetRxPktLen;								/* Current rx packet length */
unsigned NetIPID;								/* IP packet ID */

uchar NetBcastAddr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};	/* Ethernet bcast address */
uchar NetEtherNullAddr[6] = {0, 0, 0, 0, 0, 0};

int NetState;	/* Network loop state */

#ifdef CONFIG_NET_MULTI
int NetRestartWrap = 0;			/* Tried all network devices */
static int NetRestarted = 0;	/* Network loop restarted */
static int NetDevExists = 0;	/* At least one device configured */
#endif

/* XXX in both little & big endian machines 0xFFFF == ntohs(-1) */
ushort NetOurVLAN = 0xFFFF;			/* default is without VLAN */
ushort NetOurNativeVLAN = 0xFFFF;	/* ditto */

char BootFile[128]; /* Boot File name */

#if defined(CONFIG_CMD_PING)
IPaddr_t NetPingIP;	/* the ip address to ping */
static void PingStart(void);
#endif /* CONFIG_CMD_PING */

#if defined(CONFIG_CMD_SNTP)
IPaddr_t NetNtpServerIP;	/* NTP server IP address */
int NetTimeOffset = 0;		/* offset time from UTC */
#endif /* CONFIG_CMD_SNTP */

#ifdef CONFIG_NETCONSOLE
void NcStart(void);
int nc_input_packet(uchar *pkt, unsigned dest, unsigned src, unsigned len);
#endif /* CONFIG_NETCONSOLE */

volatile uchar PktBuf[(PKTBUFSRX + 1) * PKTSIZE_ALIGN + PKTALIGN];
volatile uchar *NetRxPackets[PKTBUFSRX];	/* Receive packets */

static rxhand_f *packetHandler;		/* Current RX packet handler */
static thand_f *timeHandler;		/* Current timeout handler */
static ulong timeStart;				/* Time base value */
static ulong timeDelta;				/* Current timeout value */
volatile uchar *NetTxPacket = 0;	/* THE transmit packet */

static int net_check_prereq(proto_t protocol);

/**********************************************************************/

IPaddr_t NetArpWaitPacketIP;
IPaddr_t NetArpWaitReplyIP;

uchar *NetArpWaitPacketMAC;	/* MAC address of waiting packet's destination */
uchar *NetArpWaitTxPacket;	/* THE transmit packet */
uchar NetArpWaitPacketBuf[PKTSIZE_ALIGN + PKTALIGN];
ulong NetArpWaitTimerStart;

int NetArpWaitTry;
int NetArpWaitTxPacketSize;

void ArpRequest(void){
	int i;
	volatile uchar *pkt;
	ARP_t *arp;

#ifdef ET_DEBUG
	printf("ARP broadcast %d\n", NetArpWaitTry);
#endif

	pkt = NetTxPacket;
	pkt += NetSetEther(pkt, NetBcastAddr, PROT_ARP);

	arp = (ARP_t *)pkt;

	arp->ar_hrd = htons(ARP_ETHER);
	arp->ar_pro = htons(PROT_IP);
	arp->ar_hln = 6;
	arp->ar_pln = 4;
	arp->ar_op  = htons(ARPOP_REQUEST);

	memcpy(&arp->ar_data[0], NetOurEther, 6);			/* source ET addr */
	NetWriteIP((uchar *)&arp->ar_data[6], NetOurIP);	/* source IP addr */

	for(i = 10; i < 16; ++i){
		arp->ar_data[i] = 0; /* dest ET addr = 0 */
	}

	if((NetArpWaitPacketIP & NetOurSubnetMask) != (NetOurIP & NetOurSubnetMask)){
		if(NetOurGatewayIP == 0){
			printf_wrn("gatewayip needed but not set\n");
			NetArpWaitReplyIP = NetArpWaitPacketIP;
		} else {
			NetArpWaitReplyIP = NetOurGatewayIP;
		}
	} else {
		NetArpWaitReplyIP = NetArpWaitPacketIP;
	}

	NetWriteIP((uchar *)&arp->ar_data[16], NetArpWaitReplyIP);
	(void)eth_send(NetTxPacket, (pkt - NetTxPacket) + ARP_HDR_SIZE);
}

void ArpTimeoutCheck(void){
	ulong t;
	bd_t *bd = gd->bd;

	if(!NetArpWaitPacketIP){
		return;
	}

	t = get_timer(0);

	/* check for arp timeout */
	if((t - NetArpWaitTimerStart) > ARP_TIMEOUT * CFG_HZ){
		NetArpWaitTry++;

		if(NetArpWaitTry >= ARP_TIMEOUT_COUNT){
			printf_err("ARP retry count exceeded, starting again\n");
			NetArpWaitTry = 0;
			NetStartAgain();
		} else {
			NetArpWaitTimerStart = t;
			ArpRequest();
		}
	}
}

/**********************************************************************/
/*
 *	Main network processing loop.
 */
int NetLoop(proto_t protocol){
	bd_t *bd = gd->bd;

#ifdef CONFIG_NET_MULTI
	NetRestarted = 0;
	NetDevExists = 0;
#endif

	/* XXX problem with bss workaround */
	NetArpWaitPacketMAC	= NULL;
	NetArpWaitTxPacket	= NULL;
	NetArpWaitPacketIP	= 0;
	NetArpWaitReplyIP	= 0;
	NetArpWaitTxPacket	= NULL;
	NetTxPacket			= NULL;

	if(!NetTxPacket){
		int i;
		/*
		 *	Setup packet buffers, aligned correctly.
		 */
		NetTxPacket = &PktBuf[0] + (PKTALIGN - 1);
		NetTxPacket -= (ulong)NetTxPacket % PKTALIGN;

		for(i = 0; i < PKTBUFSRX; i++){
			NetRxPackets[i] = NetTxPacket + (i + 1) * PKTSIZE_ALIGN;
		}
	}

	if(!NetArpWaitTxPacket){
		NetArpWaitTxPacket = &NetArpWaitPacketBuf[0] + (PKTALIGN - 1);
		NetArpWaitTxPacket -= (ulong)NetArpWaitTxPacket % PKTALIGN;
		NetArpWaitTxPacketSize = 0;
	}

	if(eth_is_on_demand_init() || protocol != NETCONS){
		eth_halt();
#ifdef CONFIG_NET_MULTI
		eth_set_current();
#endif
		if(!eth_init(bd)){
			eth_halt();
			return(-1);
		}
	} else {
		eth_init_state_only(bd);
	}

	/* restart label */
	restart:

#ifdef CONFIG_NET_MULTI
	memcpy(NetOurEther, eth_get_dev()->enetaddr, 6);
#else
	memcpy(NetOurEther, bd->bi_enetaddr, 6);
#endif

	NetState = NETLOOP_CONTINUE;

	/*
	 *	Start the ball rolling with the given start function.  From
	 *	here on, this code is a state machine driven by received
	 *	packets and timer events.
	 */

	switch(protocol){
#if defined(CONFIG_CMD_NFS)
		case NFS:
#endif
#if defined(CONFIG_CMD_PING)
		case PING:
#endif
#if defined(CONFIG_CMD_SNTP)
		case SNTP:
#endif
		case NETCONS:
		case TFTPGET:
		case TFTPPUT:
			NetCopyIP(&NetOurIP, &bd->bi_ip_addr);

			NetOurGatewayIP		= getenv_IPaddr("gatewayip");
			NetOurSubnetMask	= getenv_IPaddr("netmask");
			NetOurVLAN			= getenv_VLAN("vlan");
			NetOurNativeVLAN	= getenv_VLAN("nvlan");

			switch(protocol){
#if defined(CONFIG_CMD_NFS)
				case NFS:
#endif
				case NETCONS:
				case TFTPGET:
				case TFTPPUT:
					NetServerIP = getenv_IPaddr("serverip");
					break;
#if defined(CONFIG_CMD_PING)
				case PING:
					/* nothing */
					break;
#endif
#if defined(CONFIG_CMD_SNTP)
				case SNTP:
					/* nothing */
					break;
#endif
				default:
					break;
			}

			break;

		case BOOTP:
		case RARP:
			/*
			 * initialize our IP addr to 0 in order to accept ANY
			 * IP addr assigned to us by the BOOTP / RARP server
			 */
			NetOurIP			= 0;
			NetServerIP			= getenv_IPaddr("serverip");
			NetOurVLAN			= getenv_VLAN("vlan"); /* VLANs must be read */
			NetOurNativeVLAN	= getenv_VLAN("nvlan");

		case CDP:
			NetOurVLAN			= getenv_VLAN("vlan"); /* VLANs must be read */
			NetOurNativeVLAN	= getenv_VLAN("nvlan");
			break;

		default:
			break;
	}

	switch(net_check_prereq(protocol)){
		case 1:
			/* network not configured */
			eth_halt();
			return(-1);

#ifdef CONFIG_NET_MULTI
		case 2:
			/* network device not configured */
			break;
#endif /* CONFIG_NET_MULTI */

		case 0:
#ifdef CONFIG_NET_MULTI
			NetDevExists = 1;
#endif
			NetBootFileXferSize = 0;

			switch(protocol){
				case TFTPGET:
				case TFTPPUT:
					/* always use ARP to get server ethernet address */
					TftpStart(protocol);
					break;

#if defined(CONFIG_CMD_DHCP)
				case DHCP:
					/* Start with a clean slate... */
					BootpTry = 0;
					NetOurIP = 0;
					NetServerIP = getenv_IPaddr("serverip");
					DhcpRequest(); /* Basically same as BOOTP */
					break;

#endif /* CONFIG_CMD_DHCP */

#if defined(CONFIG_CMD_PING)
				case PING:
					PingStart();
					break;
#endif

#if defined(CONFIG_CMD_NFS)
				case NFS:
					NfsStart();
					break;
#endif

#ifdef CONFIG_NETCONSOLE
				case NETCONS:
					NcStart();
					break;
#endif

#if defined(CONFIG_CMD_SNTP)
				case SNTP:
					SntpStart();
					break;
#endif

				default:
					break;
			}

			break;
	}

	/*
	 *	Main packet reception loop.  Loop receiving packets until
	 *	someone sets `NetState' to a state that terminates.
	 */
	for(;;){
		/*
		 *	Check the ethernet for a new packet.  The ethernet
		 *	receive routine will process it.
		 */
		eth_rx();

		/*
		 *	Abort if ctrl-c was pressed.
		 */
		if(ctrlc()){
			eth_halt();

			/* Invalidate the last protocol */
			eth_set_last_protocol(BOOTP);

			puts("\nAbort\n");
			return(-1);
		}

		ArpTimeoutCheck();

		/*
		 *	Check for a timeout, and run the timeout handler
		 *	if we have one.
		 */
		if(timeHandler && ((get_timer(0) - timeStart) > timeDelta)){
			thand_f *x;
			x = timeHandler;
			timeHandler = (thand_f *)0;
			(*x)();
		}

		switch(NetState){

			case NETLOOP_RESTART:
#ifdef CONFIG_NET_MULTI
				NetRestarted = 1;
#endif
				goto restart;

			case NETLOOP_SUCCESS:
				if(NetBootFileXferSize > 0){
					char buf[10];
					printf("\nBytes transferred: %ld (0x%lx)\n", NetBootFileXferSize, NetBootFileXferSize);

					sprintf(buf, "%lx", NetBootFileXferSize);
					setenv("filesize", buf);

					sprintf(buf, "%lX", (unsigned long)load_addr);
					setenv("fileaddr", buf);
				}

				if(protocol != NETCONS){
					eth_halt();
				} else {
					eth_halt_state_only();
				}

				eth_set_last_protocol(protocol);

				return(NetBootFileXferSize);

			case NETLOOP_FAIL:
				/* Invalidate the last protocol */
				eth_set_last_protocol(BOOTP);
				return(-1);
		}
	}
}

/**********************************************************************/

static void startAgainTimeout(void){
	NetState = NETLOOP_RESTART;
}

static void startAgainHandler(uchar * pkt, unsigned dest, unsigned src, unsigned len){
	/* Totally ignore the packet */
}

void NetStartAgain(void){
	char *nretry;
	int noretry = 0, once = 0;
	bd_t *bd = gd->bd;

	if((nretry = getenv("netretry")) != NULL){
		noretry = (strcmp(nretry, "no") == 0);
		once = (strcmp(nretry, "once") == 0);
	}

	if(noretry){
		eth_halt();
		NetState = NETLOOP_FAIL;
		return;
	}

#ifndef CONFIG_NET_MULTI
	NetSetTimeout(10 * CFG_HZ, startAgainTimeout);
	NetSetHandler(startAgainHandler);
#else	/* !CONFIG_NET_MULTI*/
	eth_halt();
	eth_try_another(!NetRestarted);
	eth_init(gd->bd);

	if(NetRestartWrap){
		NetRestartWrap = 0;
		if(NetDevExists && !once){
			NetSetTimeout(10 * CFG_HZ, startAgainTimeout);
			NetSetHandler(startAgainHandler);
		} else {
			NetState = NETLOOP_FAIL;
		}
	} else {
		NetState = NETLOOP_RESTART;
	}
#endif /* CONFIG_NET_MULTI */
}

/**********************************************************************/
/*
 *	Miscelaneous bits.
 */

void NetSetHandler(rxhand_f * f){
	packetHandler = f;
}

void NetSetTimeout(ulong iv, thand_f * f){
	if(iv == 0){
		timeHandler = (thand_f *)0;
	} else {
		timeHandler = f;
		timeStart = get_timer(0);
		timeDelta = iv;
	}
}

void NetSendPacket(volatile uchar * pkt, int len){
	(void)eth_send(pkt, len);
}

int NetSendUDPPacket(uchar *ether, IPaddr_t dest, int dport, int sport, int len){
	uchar *pkt;

	/* convert to new style broadcast */
	if(dest == 0){
		dest = 0xFFFFFFFF;
	}

	/* if broadcast, make the ether address a broadcast and don't do ARP */
	if(dest == 0xFFFFFFFF){
		ether = NetBcastAddr;
	}

	/* if MAC address was not discovered yet, save the packet and do an ARP request */
	if(memcmp(ether, NetEtherNullAddr, 6) == 0){

#ifdef ET_DEBUG
		printf("Sending ARP for %08lx\n", dest);
#endif
		NetArpWaitPacketIP = dest;
		NetArpWaitPacketMAC = ether;

		pkt = NetArpWaitTxPacket;
		pkt += NetSetEther(pkt, NetArpWaitPacketMAC, PROT_IP);

		NetSetIP(pkt, dest, dport, sport, len);
		memcpy(pkt + IP_HDR_SIZE, (uchar *)NetTxPacket + (pkt - (uchar *)NetArpWaitTxPacket) + IP_HDR_SIZE, len);

		/* size of the waiting packet */
		NetArpWaitTxPacketSize = (pkt - NetArpWaitTxPacket) + IP_HDR_SIZE + len;

		/* and do the ARP request */
		NetArpWaitTry = 1;
		NetArpWaitTimerStart = get_timer(0);
		ArpRequest();

		return(1); /* waiting */
	}

#ifdef ET_DEBUG
	printf("Sending UDP to %08lx/%02x:%02x:%02x:%02x:%02x:%02x\n", dest, ether[0], ether[1], ether[2], ether[3], ether[4], ether[5]);
#endif

	pkt = (uchar *)NetTxPacket;
	pkt += NetSetEther(pkt, ether, PROT_IP);
	NetSetIP(pkt, dest, dport, sport, len);
	(void)eth_send(NetTxPacket, (pkt - NetTxPacket) + IP_HDR_SIZE + len);

	return(0); /* transmitted */
}

#if defined(CONFIG_CMD_PING)
static ushort PingSeqNo;

int PingSend(void){
	static uchar mac[6];
	volatile IP_t *ip;
	volatile ushort *s;
	uchar *pkt;

	/* XXX always send arp request */

	memcpy(mac, NetEtherNullAddr, 6);

#ifdef ET_DEBUG
	printf("Sending ARP for %08lx\n", NetPingIP);
#endif

	NetArpWaitPacketIP = NetPingIP;
	NetArpWaitPacketMAC = mac;

	pkt = NetArpWaitTxPacket;
	pkt += NetSetEther(pkt, mac, PROT_IP);

	ip = (volatile IP_t *)pkt;

	/*
	 *	Construct an IP and ICMP header.  (need to set no fragment bit - XXX)
	 */
	ip->ip_hl_v	= 0x45; /* IP_HDR_SIZE / 4 (not including UDP) */
	ip->ip_tos	= 0;
	ip->ip_len	= htons(IP_HDR_SIZE_NO_UDP + 8);
	ip->ip_id	= htons(NetIPID++);
	ip->ip_off	= htons(0x4000); /* No fragmentation */
	ip->ip_ttl	= 255;
	ip->ip_p	= 0x01; /* ICMP */
	ip->ip_sum	= 0;

	NetCopyIP((void*)&ip->ip_src, &NetOurIP); /* already in network byte order */
	NetCopyIP((void*)&ip->ip_dst, &NetPingIP); /* - "" - */

	ip->ip_sum = ~NetCksum((uchar *)ip, IP_HDR_SIZE_NO_UDP / 2);

	s = &ip->udp_src; /* XXX ICMP starts here */

	s[0] = htons(0x0800); /* echo-request, code */
	s[1] = 0; /* checksum */
	s[2] = 0; /* identifier */
	s[3] = htons(PingSeqNo++); /* sequence number */
	s[1] = ~NetCksum((uchar *)s, 8/2);

	/* size of the waiting packet */
	NetArpWaitTxPacketSize = (pkt - NetArpWaitTxPacket) + IP_HDR_SIZE_NO_UDP + 8;

	/* and do the ARP request */
	NetArpWaitTry = 1;
	NetArpWaitTimerStart = get_timer(0);
	ArpRequest();

	return(1); /* waiting */
}

static void PingTimeout(void){
	eth_halt();
	NetState = NETLOOP_FAIL; /* we did not get the reply */
}

static void PingHandler(uchar * pkt, unsigned dest, unsigned src, unsigned len){
	IPaddr_t tmp;
	volatile IP_t *ip = (volatile IP_t *)pkt;

	tmp = NetReadIP((void *)&ip->ip_src);

	if(tmp != NetPingIP){
		return;
	}

	NetState = NETLOOP_SUCCESS;
}

static void PingStart(void){
	bd_t *bd = gd->bd;
#if defined(CONFIG_NET_MULTI)
	printf("Using %s device\n", eth_get_name());
#endif /* CONFIG_NET_MULTI */

	NetSetTimeout(10 * CFG_HZ, PingTimeout);
	NetSetHandler(PingHandler);

	PingSend();
}
#endif /* CONFIG_CMD_PING */

void NetReceive(volatile uchar * inpkt, int len){
	Ethernet_t *et;
	IP_t *ip;
	ARP_t *arp;
	IPaddr_t tmp;
	int x;
	uchar *pkt;
	ushort cti = 0, vlanid = VLAN_NONE, myvlanid, mynvlanid;

#ifdef ET_DEBUG
	printf("Packet received\n");
#endif

	#if defined(CONFIG_CMD_HTTPD)
	if(webfailsafe_is_running){
		NetReceiveHttpd(inpkt, len);
		return;
	}
	#endif

	NetRxPkt = inpkt;
	NetRxPktLen = len;
	et = (Ethernet_t *)inpkt;

	/* too small packet? */
	if(len < ETHER_HDR_SIZE){
		return;
	}

	myvlanid = ntohs(NetOurVLAN);

	if(myvlanid == (ushort)-1){
		myvlanid = VLAN_NONE;
	}

	mynvlanid = ntohs(NetOurNativeVLAN);

	if(mynvlanid == (ushort)-1){
		mynvlanid = VLAN_NONE;
	}

	x = ntohs(et->et_protlen);

#ifdef ET_DEBUG
	printf("Packet received\n");
#endif

	if(x < 1514){
		/*
		 *	Got a 802 packet.  Check the other protocol field.
		 */
		x = ntohs(et->et_prot);

		ip = (IP_t *)(inpkt + E802_HDR_SIZE);
		len -= E802_HDR_SIZE;

	} else if(x != PROT_VLAN){ /* normal packet */
		ip = (IP_t *)(inpkt + ETHER_HDR_SIZE);
		len -= ETHER_HDR_SIZE;

	} else { /* VLAN packet */
		VLAN_Ethernet_t *vet = (VLAN_Ethernet_t *)et;

#ifdef ET_DEBUG
		printf("VLAN packet received\n");
#endif
		/* too small packet? */
		if(len < VLAN_ETHER_HDR_SIZE){
			return;
		}

		/* if no VLAN active */
		if((ntohs(NetOurVLAN) & VLAN_IDMASK) == VLAN_NONE){
			return;
		}

		cti = ntohs(vet->vet_tag);
		vlanid = cti & VLAN_IDMASK;
		x = ntohs(vet->vet_type);

		ip = (IP_t *)(inpkt + VLAN_ETHER_HDR_SIZE);
		len -= VLAN_ETHER_HDR_SIZE;
	}

#ifdef ET_DEBUG
	printf("Receive from protocol 0x%x\n", x);
#endif

	if((myvlanid & VLAN_IDMASK) != VLAN_NONE){
		if(vlanid == VLAN_NONE){
			vlanid = (mynvlanid & VLAN_IDMASK);
		}
		/* not matched? */
		if(vlanid != (myvlanid & VLAN_IDMASK)){
			return;
		}
	}

	switch(x){

		case PROT_ARP:
			/*
			 * We have to deal with two types of ARP packets:
			 * - REQUEST packets will be answered by sending  our
			 *   IP address - if we know it.
			 * - REPLY packates are expected only after we asked
			 *   for the TFTP server's or the gateway's ethernet
			 *   address; so if we receive such a packet, we set
			 *   the server ethernet address
			 */
#ifdef ET_DEBUG
			puts("Got ARP\n");
#endif
			arp = (ARP_t *)ip;

			if(len < ARP_HDR_SIZE){
				printf_err("bad length %d < %d\n", len, ARP_HDR_SIZE);
				return;
			}

			if(ntohs(arp->ar_hrd) != ARP_ETHER){
				return;
			}

			if(ntohs(arp->ar_pro) != PROT_IP){
				return;
			}

			if(arp->ar_hln != 6){
				return;
			}

			if(arp->ar_pln != 4){
				return;
			}

			if(NetOurIP == 0){
				return;
			}

			if(NetReadIP(&arp->ar_data[16]) != NetOurIP){
				return;
			}

			switch(ntohs(arp->ar_op)){
				case ARPOP_REQUEST: /* reply with our IP address	*/
#ifdef ET_DEBUG
					puts("Got ARP REQUEST, return our IP\n");
#endif
					pkt = (uchar *)et;
					pkt += NetSetEther(pkt, et->et_src, PROT_ARP);
					arp->ar_op = htons(ARPOP_REPLY);
					memcpy(&arp->ar_data[10], &arp->ar_data[0], 6);
					NetCopyIP(&arp->ar_data[16], &arp->ar_data[6]);
					memcpy(&arp->ar_data[0], NetOurEther, 6);
					NetCopyIP(&arp->ar_data[6], &NetOurIP);
					(void)eth_send((uchar *)et, (pkt - (uchar *)et) + ARP_HDR_SIZE);

					return;

				case ARPOP_REPLY: /* arp reply */
					/* are we waiting for a reply */
					if(!NetArpWaitPacketIP || !NetArpWaitPacketMAC){
						break;
					}
#ifdef ET_DEBUG
					printf("Got ARP REPLY, set server/gtwy eth addr (%02x:%02x:%02x:%02x:%02x:%02x)\n", arp->ar_data[0], arp->ar_data[1], arp->ar_data[2], arp->ar_data[3], arp->ar_data[4], arp->ar_data[5]);
#endif

					tmp = NetReadIP(&arp->ar_data[6]);

					/* matched waiting packet's address */
					if(tmp == NetArpWaitReplyIP){
#ifdef ET_DEBUG
						puts("Got it\n");
#endif
						/* save address for later use */
						memcpy(NetArpWaitPacketMAC, &arp->ar_data[0], 6);

#ifdef CONFIG_NETCONSOLE
						(*packetHandler)(0,0,0,0);
#endif
						/* modify header, and transmit it */
						memcpy(((Ethernet_t *)NetArpWaitTxPacket)->et_dest, NetArpWaitPacketMAC, 6);
						(void)eth_send(NetArpWaitTxPacket, NetArpWaitTxPacketSize);

						/* no arp request pending now */
						NetArpWaitPacketIP = 0;
						NetArpWaitTxPacketSize = 0;
						NetArpWaitPacketMAC = NULL;

					}

					return;
				default:
#ifdef ET_DEBUG
					printf_err("unexpected ARP opcode 0x%x\n", ntohs(arp->ar_op));
#endif
					return;
			}
			break;

		case PROT_RARP:
#ifdef ET_DEBUG
			puts("Got RARP\n");
#endif
			arp = (ARP_t *)ip;
			if(len < ARP_HDR_SIZE){
				printf_err("bad length %d < %d\n", len, ARP_HDR_SIZE);
				return;
			}

			if((ntohs(arp->ar_op) != RARPOP_REPLY) || (ntohs(arp->ar_hrd) != ARP_ETHER) || (ntohs(arp->ar_pro) != PROT_IP) || (arp->ar_hln != 6) || (arp->ar_pln != 4)){
				printf_err("invalid RARP header\n");
			} else {
				NetCopyIP(&NetOurIP, &arp->ar_data[16]);
				if(NetServerIP == 0){
					NetCopyIP(&NetServerIP, &arp->ar_data[6]);
				}
				memcpy(NetServerEther, &arp->ar_data[0], 6);
				(*packetHandler)(0, 0, 0, 0);
			}

			break;

		case PROT_IP:
#ifdef ET_DEBUG
			puts("Got IP\n");
#endif
			if(len < IP_HDR_SIZE){
				debug("## Error: len bad %d < %d\n", len, IP_HDR_SIZE);
				return;
			}

			if(len < ntohs(ip->ip_len)){
				printf_err("len bad %d < %d\n", len, ntohs(ip->ip_len));
				return;
			}

			len = ntohs(ip->ip_len);
#ifdef ET_DEBUG
			printf("Len=%d, v=%02x\n", len, ip->ip_hl_v & 0xff);
#endif
			if((ip->ip_hl_v & 0xf0) != 0x40){
				return;
			}

			if(ip->ip_off & htons(0x1fff)){ /* Can't deal w/ fragments */
				return;
			}

			if(!NetCksumOk((uchar *)ip, IP_HDR_SIZE_NO_UDP / 2)){
#ifdef ET_DEBUG
				puts("\n");
				printf_err("checksum bad\n");
#endif
				return;
			}

			tmp = NetReadIP(&ip->ip_dst);

			if(NetOurIP && tmp != NetOurIP && tmp != 0xFFFFFFFF){
				return;
			}
			/*
			 * watch for ICMP host redirects
			 *
			 * There is no real handler code (yet). We just watch
			 * for ICMP host redirect messages. In case anybody
			 * sees these messages: please contact me
			 * (wd@denx.de), or - even better - send me the
			 * necessary fixes :-)
			 *
			 * Note: in all cases where I have seen this so far
			 * it was a problem with the router configuration,
			 * for instance when a router was configured in the
			 * BOOTP reply, but the TFTP server was on the same
			 * subnet. So this is probably a warning that your
			 * configuration might be wrong. But I'm not really
			 * sure if there aren't any other situations.
			 */
			if(ip->ip_p == IPPROTO_ICMP){
				ICMP_t *icmph = (ICMP_t *) & (ip->udp_src);

				switch(icmph->type){
					case ICMP_REDIRECT:
						if(icmph->code != ICMP_REDIR_HOST){
							return;
						}

						puts(" ICMP Host Redirect to ");
						print_IPaddr(icmph->un.gateway);
						putc(' ');

						return;
#if defined(CONFIG_CMD_PING)
					case ICMP_ECHO_REPLY:
						/*
						 *	IP header OK.  Pass the packet to the current handler.
						 */
						/* XXX point to ip packet */
						(*packetHandler)((uchar *)ip, 0, 0, 0);
						return;
#endif
					default:
						return;
				}
			} else if(ip->ip_p != IPPROTO_UDP){ /* Only UDP packets */
				return;
			}

#ifdef CONFIG_UDP_CHECKSUM
			if(ip->udp_xsum != 0){
				ulong xsum;
				ushort *sumptr;
				ushort sumlen;

				xsum = ip->ip_p;
				xsum += (ntohs(ip->udp_len));
				xsum += (ntohl(ip->ip_src) >> 16) & 0x0000ffff;
				xsum += (ntohl(ip->ip_src) >> 0) & 0x0000ffff;
				xsum += (ntohl(ip->ip_dst) >> 16) & 0x0000ffff;
				xsum += (ntohl(ip->ip_dst) >> 0) & 0x0000ffff;

				sumlen = ntohs(ip->udp_len);
				sumptr = (ushort *)&(ip->udp_src);

				while(sumlen > 1){
					ushort sumdata;

					sumdata = *sumptr++;
					xsum += ntohs(sumdata);
					sumlen -= 2;
				}

				if(sumlen > 0){
					ushort sumdata;

					sumdata = *(unsigned char *)sumptr;
					sumdata = (sumdata << 8) & 0xff00;
					xsum += sumdata;
				}

				while((xsum >> 16) != 0){
					xsum = (xsum & 0x0000ffff) + ((xsum >> 16) & 0x0000ffff);
				}

				if((xsum != 0x00000000) && (xsum != 0x0000ffff)){
					printf_err("UDP wrong checksum %08x %08x\n", xsum, ntohs(ip->udp_xsum));
					return;
				}
			}
#endif

#ifdef CONFIG_NETCONSOLE
			nc_input_packet((uchar *)ip +IP_HDR_SIZE, ntohs(ip->udp_dst), ntohs(ip->udp_src), ntohs(ip->udp_len) - 8);
#endif
			/*
			 *	IP header OK.  Pass the packet to the current handler.
			 */
			(*packetHandler)((uchar *)ip + IP_HDR_SIZE, ntohs(ip->udp_dst), ntohs(ip->udp_src), ntohs(ip->udp_len) - 8);
			break;
	}
}

/**********************************************************************/

static int net_check_prereq(proto_t protocol){
	switch(protocol){
		/* Fall through */
#if defined(CONFIG_CMD_PING)
		case PING:
			if(NetPingIP == 0){
				printf_err("ping address not given\n");
				return(1);
			}
			goto common;
#endif
#if defined(CONFIG_CMD_SNTP)
		case SNTP:
			if(NetNtpServerIP == 0){
				printf_err("NTP server address not given\n");
				return(1);
			}
			goto common;
#endif
#if defined(CONFIG_CMD_NFS)
		case NFS:
#endif
		case NETCONS:
		case TFTPGET:
		case TFTPPUT:
			if(NetServerIP == 0){
				printf_err("serverip not set\n");
				return(1);
			}
#if defined(CONFIG_CMD_PING) || defined(CONFIG_CMD_SNTP)
			common:
#endif
			if(NetOurIP == 0){
				printf_err("ipaddr not set\n");
				return(1);
			}
			/* Fall through */

		case DHCP:
		case RARP:
		case BOOTP:
		case CDP:
			if(memcmp(NetOurEther, "\0\0\0\0\0\0", 6) == 0){
#ifdef CONFIG_NET_MULTI
				extern int eth_get_dev_index(void);
				int num = eth_get_dev_index();

				switch(num){
					case -1:
						printf_err("no ethernet found\n");
						return(1);
					case 0:
						printf_err("ethaddr not set\n");
						break;
					default:
						printf_err("eth%daddr not set\n", num);
						break;
				}

				NetStartAgain();
				return(2);
#else
				printf_err("ethaddr not set\n");
				return(1);
#endif
			}
			/* Fall through */
		default:
			return(0);
	}

	return(0); /* OK */
}
/**********************************************************************/

int NetCksumOk(uchar * ptr, int len){
	return(!((NetCksum(ptr, len) + 1) & 0xfffe));
}

unsigned NetCksum(uchar * ptr, int len){
	ulong xsum;
	ushort *p = (ushort *)ptr;

	xsum = 0;

	while(len-- > 0){
		xsum += *p++;
	}

	xsum = (xsum & 0xffff) + (xsum >> 16);
	xsum = (xsum & 0xffff) + (xsum >> 16);

	return(xsum & 0xffff);
}

int NetEthHdrSize(void){
	ushort myvlanid;

	myvlanid = ntohs(NetOurVLAN);

	if(myvlanid == (ushort) -1){
		myvlanid = VLAN_NONE;
	}

	return(((myvlanid & VLAN_IDMASK) == VLAN_NONE) ? ETHER_HDR_SIZE : VLAN_ETHER_HDR_SIZE);
}

int NetSetEther(volatile uchar * xet, uchar * addr, uint prot){
	Ethernet_t *et = (Ethernet_t *)xet;
	ushort myvlanid;

	myvlanid = ntohs(NetOurVLAN);

	if(myvlanid == (ushort) -1){
		myvlanid = VLAN_NONE;
	}

	memcpy(et->et_dest, addr, 6);
	memcpy(et->et_src, NetOurEther, 6);

	if((myvlanid & VLAN_IDMASK) == VLAN_NONE){
		et->et_protlen = htons(prot);

		return(ETHER_HDR_SIZE);
	} else {
		VLAN_Ethernet_t *vet = (VLAN_Ethernet_t *)xet;

		vet->vet_vlan_type = htons(PROT_VLAN);
		vet->vet_tag = htons((0 << 5) | (myvlanid & VLAN_IDMASK));
		vet->vet_type = htons(prot);
		return(VLAN_ETHER_HDR_SIZE);
	}
}

void NetSetIP(volatile uchar * xip, IPaddr_t dest, int dport, int sport, int len){
	volatile IP_t *ip = (IP_t *)xip;

	/*
	 *	If the data is an odd number of bytes, zero the
	 *	byte after the last byte so that the checksum
	 *	will work.
	 */
	if(len & 1){
		xip[IP_HDR_SIZE + len] = 0;
	}

	/*
	 *	Construct an IP and UDP header.
	 *	(need to set no fragment bit - XXX)
	 */
	ip->ip_hl_v	= 0x45; /* IP_HDR_SIZE / 4 (not including UDP) */
	ip->ip_tos	= 0;
	ip->ip_len	= htons(IP_HDR_SIZE + len);
	ip->ip_id	= htons(NetIPID++);
	ip->ip_off	= htons(0x4000); /* No fragmentation */
	ip->ip_ttl	= 255;
	ip->ip_p	= 17; /* UDP */
	ip->ip_sum	= 0;

	NetCopyIP((void*)&ip->ip_src, &NetOurIP); /* already in network byte order */
	NetCopyIP((void*)&ip->ip_dst, &dest); /* - "" - */

	ip->udp_src  = htons(sport);
	ip->udp_dst  = htons(dport);
	ip->udp_len  = htons(8 + len);
	ip->udp_xsum = 0;
	ip->ip_sum   = ~NetCksum((uchar *)ip, IP_HDR_SIZE_NO_UDP / 2);
}

void copy_filename(char *dst, char *src, int size){
	if(*src && (*src == '"')){
		++src;
		--size;
	}

	while((--size > 0) && *src && (*src != '"')){
		*dst++ = *src++;
	}
	*dst = '\0';
}

#endif /* CONFIG_CMD_NET */

void ip_to_string(IPaddr_t x, char *s){
	x = ntohl(x);
	sprintf(s, "%d.%d.%d.%d", (int)((x >> 24) & 0xff), (int)((x >> 16) & 0xff), (int)((x >> 8) & 0xff), (int)((x >> 0) & 0xff));
}

IPaddr_t string_to_ip(char *s){
	IPaddr_t addr;
	char *e;
	int i;

	if(s == NULL){
		return(0);
	}

	for(addr = 0, i = 0; i < 4; ++i){
		ulong val = s ? simple_strtoul(s, &e, 10) : 0;
		addr <<= 8;
		addr |= (val & 0xFF);
		if(s){
			s = (*e) ? e + 1 : e;
		}
	}

	return(htonl(addr));
}

void VLAN_to_string(ushort x, char *s){
	x = ntohs(x);

	if(x == (ushort) -1){
		x = VLAN_NONE;
	}

	if(x == VLAN_NONE){
		strcpy(s, "none");
	} else {
		sprintf(s, "%d", x & VLAN_IDMASK);
	}
}

ushort string_to_VLAN(char *s){
	ushort id;

	if(s == NULL){
		return(htons(VLAN_NONE));
	}

	if(*s < '0' || *s > '9'){
		id = VLAN_NONE;
	} else {
		id = (ushort) simple_strtoul(s, NULL, 10);
	}

	return(htons(id));
}

void print_IPaddr(IPaddr_t x){
	char tmp[16];

	ip_to_string(x, tmp);

	puts(tmp);
}

IPaddr_t getenv_IPaddr(char *var){
	return(string_to_ip(getenv(var)));
}

ushort getenv_VLAN(char *var){
	return(string_to_VLAN(getenv(var)));
}


/**********************************************************************************
 * HTTPD section
 */

#if defined(CONFIG_CMD_HTTPD)

#define BUF	((struct uip_eth_hdr *)&uip_buf[0])

void NetSendHttpd(void){
	volatile uchar *tmpbuf = NetTxPacket;
	int i;

	for(i = 0; i < 40 + UIP_LLH_LEN; i++){
		tmpbuf[i] = uip_buf[i];
	}

	for(; i < uip_len; i++){
		tmpbuf[i] = uip_appdata[i - 40 - UIP_LLH_LEN];
	}

	eth_send(NetTxPacket, uip_len);
}

void NetReceiveHttpd(volatile uchar * inpkt, int len){
	memcpy(uip_buf, (const void *)inpkt, len);
	uip_len = len;

	if(BUF->type == htons(UIP_ETHTYPE_IP)){
		uip_arp_ipin();
		uip_input();

		if(uip_len > 0){
			uip_arp_out();
			NetSendHttpd();
		}
	} else if(BUF->type == htons(UIP_ETHTYPE_ARP)){
		uip_arp_arpin();

		if(uip_len > 0){
			NetSendHttpd();
		}
	}
}

/* *************************************
 *
 * HTTP web server for web failsafe mode
 *
 ***************************************/
int NetLoopHttpd(void){
	bd_t *bd = gd->bd;
	unsigned short int ip[2];
	unsigned char ethinit_attempt = 0;
	struct uip_eth_addr eaddr;

#ifdef CONFIG_NET_MULTI
	NetRestarted = 0;
	NetDevExists = 0;
#endif

	/* XXX problem with bss workaround */
	NetArpWaitPacketMAC	= NULL;
	NetArpWaitTxPacket	= NULL;
	NetArpWaitPacketIP	= 0;
	NetArpWaitReplyIP	= 0;
	NetArpWaitTxPacket	= NULL;
	NetTxPacket			= NULL;

	if(!NetTxPacket){
		int i;
		// Setup packet buffers, aligned correctly.
		NetTxPacket = &PktBuf[0] + (PKTALIGN - 1);
		NetTxPacket -= (ulong)NetTxPacket % PKTALIGN;

		for(i = 0; i < PKTBUFSRX; i++){
			NetRxPackets[i] = NetTxPacket + (i + 1) * PKTSIZE_ALIGN;
		}
	}

	if(!NetArpWaitTxPacket){
		NetArpWaitTxPacket = &NetArpWaitPacketBuf[0] + (PKTALIGN - 1);
		NetArpWaitTxPacket -= (ulong)NetArpWaitTxPacket % PKTALIGN;
		NetArpWaitTxPacketSize = 0;
	}

	// restart label
	restart:

	eth_halt();

#ifdef CONFIG_NET_MULTI
	eth_set_current();
#endif

	while(ethinit_attempt < 10){
		if(eth_init(bd)){
			ethinit_attempt = 0;
			break;
		} else {
			ethinit_attempt++;
			eth_halt();
			milisecdelay(1000);
		}
	}

	if(ethinit_attempt > 0){
		eth_halt();
		printf_err("couldn't initialize eth (cable disconnected?)!\n\n");
		return(-1);
	}

	// get MAC address
#ifdef CONFIG_NET_MULTI
	memcpy(NetOurEther, eth_get_dev()->enetaddr, 6);
#else
	eth_getenv_enetaddr("ethaddr", NetOurEther);
#endif

	eaddr.addr[0] = NetOurEther[0];
	eaddr.addr[1] = NetOurEther[1];
	eaddr.addr[2] = NetOurEther[2];
	eaddr.addr[3] = NetOurEther[3];
	eaddr.addr[4] = NetOurEther[4];
	eaddr.addr[5] = NetOurEther[5];

	// set MAC address
	uip_setethaddr(eaddr);

	// set ip and other addresses
	// TODO: do we need this with uIP stack?
	NetCopyIP(&NetOurIP, &bd->bi_ip_addr);

	NetOurGatewayIP		= getenv_IPaddr("gatewayip");
	NetOurSubnetMask	= getenv_IPaddr("netmask");
	NetOurVLAN			= getenv_VLAN("vlan");
	NetOurNativeVLAN	= getenv_VLAN("nvlan");

	// start server...
	printf("HTTP server is starting at IP: %ld.%ld.%ld.%ld\n", (bd->bi_ip_addr & 0xff000000) >> 24, (bd->bi_ip_addr & 0x00ff0000) >> 16, (bd->bi_ip_addr & 0x0000ff00) >> 8, (bd->bi_ip_addr & 0x000000ff));

	HttpdStart();

	// set local host ip address
	ip[0] = ((bd->bi_ip_addr & 0xFFFF0000) >> 16);
	ip[1] = (bd->bi_ip_addr & 0x0000FFFF);

	uip_sethostaddr(ip);

	// set network mask (255.255.255.0 -> local network)
	ip[0] = ((0xFFFFFF00 & 0xFFFF0000) >> 16);
	ip[1] = (0xFFFFFF00 & 0x0000FFFF);

	uip_setnetmask(ip);

	// should we also set default router ip address?
	//uip_setdraddr();

	// show current progress of the process
	do_http_progress(WEBFAILSAFE_PROGRESS_START);

	webfailsafe_is_running = 1;

	// infinite loop
	for(;;){

		/*
		 *	Check the ethernet for a new packet.
		 *	The ethernet receive routine will process it.
		 */
		if(eth_rx() > 0){
			HttpdHandler();
		}

		// if CTRL+C was pressed -> return!
		if(ctrlc()){
			eth_halt();

			// reset global variables to default state
			webfailsafe_is_running = 0;
			webfailsafe_ready_for_upgrade = 0;
			webfailsafe_upgrade_type = WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE;

			/* Invalidate the last protocol */
			eth_set_last_protocol(BOOTP);

			printf("\nWeb failsafe mode aborted!\n\n");
			return(-1);
		}

		// until upload is not completed, get back to the start of the loop
		if(!webfailsafe_ready_for_upgrade){
			continue;
		}

		// stop eth interface
		eth_halt();

		// show progress
		do_http_progress(WEBFAILSAFE_PROGRESS_UPLOAD_READY);

		// try to make upgrade!
		if(do_http_upgrade(NetBootFileXferSize, webfailsafe_upgrade_type) >= 0){
			milisecdelay(500);

			do_http_progress(WEBFAILSAFE_PROGRESS_UPGRADE_READY);

			milisecdelay(500);

			/* reset the board */
			do_reset(NULL, 0, 0, NULL);
		}
		break;
	}

	// reset global variables to default state
	webfailsafe_is_running = 0;
	webfailsafe_ready_for_upgrade = 0;
	webfailsafe_upgrade_type = WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE;

	NetBootFileXferSize = 0;

	do_http_progress(WEBFAILSAFE_PROGRESS_UPGRADE_FAILED);

	// go to restart
	goto restart;

	return(-1);
}
#endif /* CONFIG_CMD_HTTPD */
