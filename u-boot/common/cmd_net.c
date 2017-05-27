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

/*
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

#if defined(CONFIG_CMD_NET)

u32 save_addr;	/* Default save address for TFTPPUT */
u32 save_size;	/* Default save size (in bytes) for TFTPPUT */

extern int do_bootm(cmd_tbl_t *, int, int, char *[]);
static int netboot_common(proto_t, cmd_tbl_t *, int, char *[]);

#if defined(CONFIG_CMD_HTTPD)
int do_httpd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	return NetLoopHttpd();
}

U_BOOT_CMD(httpd, 1, 1, do_httpd,
	   "start web server for firmware recovery\n",
	   NULL);
#endif /* CONFIG_CMD_HTTPD */

#if defined(CONFIG_CMD_DHCP)
int do_dhcp(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	return netboot_common(DHCP, cmdtp, argc, argv);
}

U_BOOT_CMD(dhcp, 3, 1, do_dhcp,
	   "invoke DHCP client to obtain IP/boot params\n",
	   NULL);
#endif /* CONFIG_CMD_DHCP */

#if defined(CONFIG_CMD_NFS)
int do_nfs(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	return netboot_common(NFS, cmdtp, argc, argv);
}
U_BOOT_CMD(nfs, 3, 1, do_nfs,
	   "boot image via network using NFS protocol\n",
	   "[address] [host ip addr:filename]\n"
	   "\t- loads 'filename' at 'address' using NFS protocol");
#endif /* CONFIG_CMD_NFS */

#if defined(CONFIG_CMD_PING)
int do_ping(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc < 2) {
		print_cmd_help(cmdtp);
		return -1;
	}

	NetPingIP = string_to_ip(argv[1]);

	if (NetPingIP == 0) {
		print_cmd_help(cmdtp);
		return -1;
	}

	if (NetLoop(PING) < 0) {
		puts("\n");
		printf_err("ping failed, host %s is not alive!\n\n", argv[1]);
		return 1;
	}

	printf("\nPing OK, host %s is alive!\n\n", argv[1]);

	return 0;
}

U_BOOT_CMD(ping, 2, 1, do_ping,
	   "send ICMP ECHO_REQUEST to network host\n",
	   "host IP\n"
	   "\t- sends ping to IP 'host IP'\n");
#endif /* CONFIG_CMD_PING */

#if defined(CONFIG_CMD_SNTP)
int do_sntp(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *toff;

	if (argc < 2) {
		print_cmd_help(cmdtp);
		return -1;
	} else {
		NetNtpServerIP = string_to_ip(argv[1]);

		if (NetNtpServerIP == 0) {
			printf_err("bad SNTP server IP address\n");
			return 1;
		}
	}

	toff = getenv("timeoffset");

	if (toff == NULL)
		NetTimeOffset = 0;
	else
		NetTimeOffset = simple_strtol(toff, NULL, 10);

	if (NetLoop(SNTP) < 0) {
		printf_err("SNTP host %s not responding\n", argv[1]);
		return 1;
	}

	return 0 ;
}

U_BOOT_CMD(sntp, 2, 1, do_sntp,
	   "send NTP request to NTP server\n",
	   "ntpserverip\n"
	   "\t- sends NTP request to NTP server 'ntpserverip'\n");
#endif /* CONFIG_CMD_SNTP */

int do_tftpb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	return netboot_common(TFTPGET, cmdtp, argc, argv);
}

U_BOOT_CMD(tftpboot, 3, 1, do_tftpb,
	   "boot image via network using TFTP protocol\n",
	   "[address] [filename]\n"
	   "\t- loads 'filename' at 'address' from TFTP server");

int do_tftpput(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc < 4) {
		print_cmd_help(cmdtp);
		return -1;
	}

	return netboot_common(TFTPPUT, cmdtp, argc, argv);
}

U_BOOT_CMD(tftpput, 4, 1, do_tftpput,
	   "send file to TFTP server\n",
	   "address size filename\n"
	   "\t- sends 'size' of data from 'address' as 'filename' to TFTP server");

static void netboot_update_env(void)
{
	char tmp[22];

	if (NetOurGatewayIP) {
		ip_to_string(NetOurGatewayIP, tmp);
		setenv("gatewayip", tmp);
	}

	if (NetOurSubnetMask) {
		ip_to_string(NetOurSubnetMask, tmp);
		setenv("netmask", tmp);
	}

	if (NetOurHostName[0])
		setenv("hostname", NetOurHostName);

	if (NetOurRootPath[0])
		setenv("rootpath", NetOurRootPath);

	if (NetOurIP) {
		ip_to_string(NetOurIP, tmp);
		setenv("ipaddr", tmp);
	}

	if (NetServerIP) {
		ip_to_string(NetServerIP, tmp);
		setenv("serverip", tmp);
	}

	if (NetOurDNSIP) {
		ip_to_string(NetOurDNSIP, tmp);
		setenv("dnsip", tmp);
	}

#if (CONFIG_BOOTP_MASK & CONFIG_BOOTP_DNS2)
	if (NetOurDNS2IP) {
		ip_to_string(NetOurDNS2IP, tmp);
		setenv("dnsip2", tmp);
	}
#endif

	if (NetOurNISDomain[0])
		setenv("domain", NetOurNISDomain);

#if defined(CONFIG_CMD_SNTP)
  #if (CONFIG_BOOTP_MASK & CONFIG_BOOTP_TIMEOFFSET)
	if (NetTimeOffset) {
		sprintf(tmp, "%d", NetTimeOffset);
		setenv("timeoffset", tmp);
	}
  #endif

  #if (CONFIG_BOOTP_MASK & CONFIG_BOOTP_NTPSERVER)
	if (NetNtpServerIP) {
		ip_to_string(NetNtpServerIP, tmp);
		setenv("ntpserverip", tmp);
	}
  #endif
#endif /* CONFIG_CMD_SNTP */
}

static int netboot_common(proto_t proto,
			  cmd_tbl_t *cmdtp,
			  int argc,
			  char *argv[])
{
	char *s;
	int size;
	ulong tmp;
	int rcode = 0;

	/* Pre-set load_addr */
	if ((s = getenv("loadaddr")) != NULL)
		load_addr = simple_strtoul(s, NULL, 16);

	switch (argc) {
	case 1:
		break;
	case 2:
		/*
		 * Don't allow to use loading address
		 * lower than RAM/FLASH base
		 */
		tmp = simple_strtoul(argv[1], NULL, 16);

#if defined(CFG_DIRECT_FLASH_TFTP)
		if ((tmp < CFG_SDRAM_BASE && tmp < CFG_FLASH_BASE) || tmp == 0)
#else
		if (tmp < CFG_SDRAM_BASE || tmp == 0)
#endif
			copy_filename(BootFile, argv[1], sizeof(BootFile));
		else
			load_addr = tmp;

		break;
	case 3:
		load_addr = simple_strtoul(argv[1], NULL, 16);
		copy_filename(BootFile, argv[2], sizeof(BootFile));
		break;
	case 4:
		save_addr = simple_strtoul(argv[1], NULL, 16);
		save_size = simple_strtoul(argv[2], NULL, 16);
		copy_filename(BootFile, argv[3], sizeof(BootFile));
		break;
	default:
		print_cmd_help(cmdtp);
		return 1;
	}

	if ((size = NetLoop(proto)) < 0)
		return 1;

	/* NetLoop ok, update environment */
	netboot_update_env();

	/* Done if no file was loaded (no errors though) */
	if (size == 0)
		return 0;

	/* Flush cache */
	flush_cache(load_addr, size);

	/* Loading ok, check if we should attempt an auto-start */
	if (((s = getenv("autostart")) != NULL) && (strcmp(s, "yes") == 0)) {
		char *local_args[2];
		local_args[0] = argv[0];
		local_args[1] = NULL;

		printf("Automatic boot of image at addr 0x%08lX ...\n",
		       load_addr);

		rcode = do_bootm(cmdtp, 0, 1, local_args);
	}

#if defined(CONFIG_AUTOSCRIPT)
	if (((s = getenv("autoscript")) != NULL) && (strcmp(s,"yes") == 0)) {
		printf("Running autoscript at addr 0x%08lX ...\n",
		       load_addr);

		rcode = autoscript(load_addr);
	}
#endif

	return rcode;
}
#endif /* CONFIG_CMD_NET */
