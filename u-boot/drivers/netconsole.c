/*
 * (C) Copyright 2004
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

#ifdef CONFIG_NETCONSOLE
#include <command.h>
#include <devices.h>
#include <net.h>

DECLARE_GLOBAL_DATA_PTR;

static char input_buffer[512];
static int input_size = 0;			/* char count in input buffer */
static int input_offset = 0;		/* offset to valid chars in input buffer */
static int input_recursion = 0;
static int output_recursion = 0;
static int net_timeout;
static uchar nc_ether[6];			/* server enet address */
static IPaddr_t nc_ip;				/* server ip */
static short nc_port;				/* source/target port */
static const char *output_packet;	/* used by first send udp */
static int output_packet_len = 0;

/*
 * Start with a default last protocol.
 * We are only interested in NETCONS or not.
 */
proto_t net_loop_last_protocol = BOOTP;

static void nc_wait_arp_handler(uchar * pkt, unsigned dest, unsigned src, unsigned len){
	NetState = NETLOOP_SUCCESS; /* got arp reply - quit net loop */
}

static void nc_handler(uchar * pkt, unsigned dest, unsigned src, unsigned len){
	if(input_size){ /* got input - quit net loop */
		NetState = NETLOOP_SUCCESS;
	}
}

static void nc_timeout(void){
	NetState = NETLOOP_SUCCESS;
}

void NcStart(void){
	if(!output_packet_len || memcmp(nc_ether, NetEtherNullAddr, 6)){
		/* going to check for input packet */
		NetSetHandler(nc_handler);
		NetSetTimeout(net_timeout, nc_timeout);
	} else {
		/* send arp request */
		uchar *pkt;
		NetSetHandler(nc_wait_arp_handler);
		pkt = (uchar *)NetTxPacket + NetEthHdrSize() + IP_HDR_SIZE;
		memcpy(pkt, output_packet, output_packet_len);
		NetSendUDPPacket(nc_ether, nc_ip, nc_port, nc_port, output_packet_len);
	}
}

int nc_input_packet(uchar * pkt, unsigned dest, unsigned src, unsigned len){
	int end, chunk;

	if(dest != nc_port || !len){ /* not for us */
		return(0);
	}

	if(input_size == sizeof(input_buffer)){ /* no space */
		return(1);
	}

	if(len > sizeof input_buffer - input_size){
		len = sizeof input_buffer - input_size;
	}

	end = input_offset + input_size;

	if(end > sizeof input_buffer){
		end -= sizeof input_buffer;
	}

	chunk = len;

	if(end + len > sizeof input_buffer){
		chunk = sizeof input_buffer - end;
		memcpy(input_buffer, pkt + chunk, len - chunk);
	}

	memcpy(input_buffer + end, pkt, chunk);

	input_size += len;

	return(1);
}

static void nc_send_packet(const char *buf, int len){
	struct eth_device *eth;
	int inited = 0;
	uchar *pkt;
	uchar *ether;
	IPaddr_t ip;

	if((eth = eth_get_dev()) == NULL){
		return;
	}

	if(!memcmp(nc_ether, NetEtherNullAddr, 6)){
		if(eth->state == ETH_STATE_ACTIVE){
			return;
		}

		output_packet = buf;
		output_packet_len = len;
		NetLoop(NETCONS); /* wait for arp reply and send packet */
		output_packet_len = 0;

		return;
	}

	if(eth->state != ETH_STATE_ACTIVE){
		if(eth_is_on_demand_init()){
			if(eth_init(gd->bd) < 0){
				return;
			}
			eth_set_last_protocol(NETCONS);
		} else {
			eth_init_state_only(gd->bd);
		}

		inited = 1;
	}

	pkt = (uchar *)NetTxPacket + NetEthHdrSize() + IP_HDR_SIZE;
	memcpy(pkt, buf, len);
	ether = nc_ether;
	ip = nc_ip;
	NetSendUDPPacket(ether, ip, nc_port, nc_port, len);

	if(inited){
		if(eth_is_on_demand_init()){
			eth_halt();
		} else {
			eth_halt_state_only();
		}
	}
}

int nc_start(void){
	int netmask, our_ip;
	char *p;

	p = getenv("ncport");
	nc_port = p ? (short)simple_strtol(p, NULL, 10) : 6666; /* default NetConsole port */

	if(getenv("serverip")){

		nc_ip = getenv_IPaddr("serverip");

		if(!nc_ip){
			return(-1);
		}

	} else {
		nc_ip = ~0; /* ncip is not set */
	}

	our_ip = getenv_IPaddr("ipaddr");
	netmask = getenv_IPaddr("netmask");

	if(nc_ip == ~0 || /* 255.255.255.255 */
	   ((netmask & our_ip) == (netmask & nc_ip) && /* on the same net */
	   (netmask | nc_ip) == ~0)) /* broadcast to our net */{
		memset(nc_ether, 0xff, sizeof nc_ether);
	} else {
		memset(nc_ether, 0, sizeof nc_ether); /* force arp request */
	}

	return(0);
}

void nc_putc(char c){
	if(output_recursion){
		return;
	}

	output_recursion = 1;

	nc_send_packet(&c, 1);

	output_recursion = 0;
}

void nc_puts(const char *s){
	int len;

	if(output_recursion){
		return;
	}

	output_recursion = 1;

	if((len = strlen(s)) > 512){
		len = 512;
	}

	nc_send_packet(s, len);

	output_recursion = 0;
}

int nc_getc(void){
	uchar c;

	input_recursion = 1;

	net_timeout = 0; /* no timeout */
	while(!input_size){
		NetLoop(NETCONS);
	}

	input_recursion = 0;

	c = input_buffer[input_offset++];

	if(input_offset >= sizeof input_buffer){
		input_offset -= sizeof input_buffer;
	}

	input_size--;

	return(c);
}

int nc_tstc(void){
	struct eth_device *eth;

	if(input_recursion){
		return(0);
	}

	if(input_size){
		return(1);
	}

	eth = eth_get_dev();

	if(eth && eth->state == ETH_STATE_ACTIVE){
		return(0); /* inside net loop */
	}

	input_recursion = 1;

	net_timeout = 1;
	NetLoop(NETCONS); /* kind of poll */

	input_recursion = 0;

	return(input_size != 0);
}

int drv_nc_init(void){
	device_t dev;
	int rc;

	memset(&dev, 0, sizeof(dev));

	strcpy(dev.name, "nc");
	dev.flags = DEV_FLAGS_OUTPUT | DEV_FLAGS_INPUT | DEV_FLAGS_SYSTEM;
	dev.start = nc_start;
	dev.putc = nc_putc;
	dev.puts = nc_puts;
	dev.getc = nc_getc;
	dev.tstc = nc_tstc;

	rc = device_register(&dev);

	return((rc == 0) ? 1 : rc);
}

#endif /* CONFIG_NETCONSOLE */
