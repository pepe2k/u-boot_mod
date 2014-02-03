/*
 * SNTP support driver
 *
 * Masami Komiya <mkomiya@sonare.it> 2005
 *
 */
#include <common.h>
#include <command.h>
#include <net.h>
#include <rtc.h>
#include "sntp.h"

#if ((CONFIG_COMMANDS & CFG_CMD_NET) && (CONFIG_COMMANDS & CFG_CMD_SNTP))

DECLARE_GLOBAL_DATA_PTR;

//#define	DEBUG

#define SNTP_TIMEOUT	10

static int SntpOurPort;

static void SntpSend(void){
	struct sntp_pkt_t pkt;
	int pktlen = SNTP_PACKET_LEN;
	int sport;

#ifdef DEBUG
	printf("%s\n", __FUNCTION__);
#endif

	memset(&pkt, 0, sizeof(pkt));

	pkt.li = NTP_LI_NOLEAP;
	pkt.vn = NTP_VERSION;
	pkt.mode = NTP_MODE_CLIENT;

	memcpy((char *)NetTxPacket + NetEthHdrSize() + IP_HDR_SIZE, (char *)&pkt, pktlen);

	SntpOurPort = 10000 + (get_timer(0) % 4096);
	sport = NTP_SERVICE_PORT;

	puts("Sending SNTP request...\n");

	NetSendUDPPacket(NetServerEther, NetNtpServerIP, sport, SntpOurPort, pktlen);
}

static void SntpTimeout(void){
	puts("## Error: timeout\n");
	NetState = NETLOOP_FAIL;

	return;
}

static void SntpHandler(uchar *pkt, unsigned dest, unsigned src, unsigned len){
	struct sntp_pkt_t *rpktp = (struct sntp_pkt_t *)pkt;
	struct rtc_time tm;
	ulong seconds;

#ifdef DEBUG
	printf("%s\n", __FUNCTION__);
#endif

	if(dest != SntpOurPort){
		return;
	}

	/*
	 * As the RTC's used in U-Boot supports second resolution only
	 * we simply ignore the sub-second field.
	 */
	memcpy(&seconds, &rpktp->transmit_timestamp, sizeof(ulong));

	to_tm(ntohl(seconds) - 2208988800UL + NetTimeOffset, &tm);

#if (CONFIG_COMMANDS & CFG_CMD_DATE)
	// TODO: find out how to use RTC on
	//rtc_set(&tm);
#endif
	printf("Got SNTP response: %4d-%02d-%02d %2d:%02d:%02d\n\n", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	NetState = NETLOOP_SUCCESS;
}

void SntpStart(void){
	bd_t *bd = gd->bd;
#ifdef DEBUG
	printf("%s\n", __FUNCTION__);
#endif

	NetSetTimeout(SNTP_TIMEOUT * CFG_HZ, SntpTimeout);
	NetSetHandler(SntpHandler);

	memset(NetServerEther, 0, 6);

	SntpSend();
}

#endif /* CONFIG_COMMANDS & CFG_CMD_SNTP */
