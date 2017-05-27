/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

/*
 * Custom/miscellaneous commands
 */

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

/* TODO: remove extern and include header file*/
extern void qca_sys_clocks(u32 *cpu_clk, u32 *ddr_clk, u32 *ahb_clk,
						   u32 *spi_clk, u32 *ref_clk);

#if defined(CONFIG_CMD_MAC) &&\
    defined(OFFSET_MAC_ADDRESS)
/*
 * Show MAC address(es)
 */
int do_print_mac(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	char buffer[6];
#if defined(OFFSET_MAC_ADDRESS2)
	char buffer2[6];
#endif

#if defined(OFFSET_MAC_ADDRESS2)
	// get MAC1 and MAC2 addresses from flash and print them
	memcpy(buffer,  (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS),  6);
	memcpy(buffer2, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS2), 6);

	puts("Current MAC addresses stored in FLASH:\n");
	printf("MAC1 at 0x%X: %02X:%02X:%02X:%02X:%02X:%02X\n", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS,
															buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF);

	printf("MAC2 at 0x%X: %02X:%02X:%02X:%02X:%02X:%02X\n\n", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS2,
															  buffer2[0] & 0xFF, buffer2[1] & 0xFF, buffer2[2] & 0xFF, buffer2[3] & 0xFF, buffer2[4] & 0xFF, buffer2[5] & 0xFF);
#else
	// get MAC address from flash and print it
	memcpy(buffer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS), 6);

	printf("Current MAC address stored in FLASH at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS);
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n\n", buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF);
#endif

	return(0);
}

#if defined(OFFSET_MAC_ADDRESS2)
U_BOOT_CMD(printmac, 1, 1, do_print_mac, "print MAC addresses stored in FLASH\n", NULL);
#else
U_BOOT_CMD(printmac, 1, 1, do_print_mac, "print MAC address stored in FLASH\n", NULL);
#endif

/*
 * Change MAC address(es)
 */
int do_set_mac(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char *data_pointer;
	char buf[128];
	int i = 0, j = 0;

	// allow only 2 arg (command name + mac), second argument length should be 17 (xx:xx:xx:xx:xx:xx)
	if(argc != 2 || strlen(argv[1]) != 17){
		print_cmd_help(cmdtp);
		return(1);
	}

	// count ':'
	for(i = 0; i< 17; i++){
		if(argv[1][i] == ':'){
			j++;
		}
	}

	if(j != 5){
		printf_err("given MAC address has wrong format (should be: xx:xx:xx:xx:xx:xx)!\n");
		return(1);
	}

	// backup block with MAC address from flash in RAM
	data_pointer = (unsigned char *)CONFIG_LOADADDR;

	if(!data_pointer){
		printf_err("couldn't allocate RAM for data block backup!\n");
		return(1);
	}

	puts("** Notice:\n   you should always make a backup of your device\n           entire FLASH content before making any changes\n\n");

	memcpy((void *)data_pointer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK), OFFSET_MAC_DATA_BLOCK_LENGTH);

	// store new MAC address in RAM
	for(i = 0; i < 6; i++){
		data_pointer[OFFSET_MAC_ADDRESS + i] = simple_strtoul((char *)(argv[1] + i*3), NULL, 16);
	}

	// now we can erase flash and write data from RAM
	sprintf(buf,
			"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
			CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK,
			OFFSET_MAC_DATA_BLOCK_LENGTH,
			CONFIG_LOADADDR,
			CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK,
			OFFSET_MAC_DATA_BLOCK_LENGTH);

	printf("Executing: %s\n\n", buf);

	return(run_command(buf, 0));
}

U_BOOT_CMD(setmac, 2, 0, do_set_mac, "save new MAC address in FLASH\n", "xx:xx:xx:xx:xx:xx\n\t- change MAC address stored in FLASH (xx - value in hex format)\n");

#endif /* if defined(CONFIG_CMD_MAC) && defined(OFFSET_MAC_ADDRESS) */

#if defined(OFFSET_ROUTER_MODEL)
/*
 * Show TP-Link router model
 */
int do_print_model(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char buffer[8];

	// get router model from flash and print it
	memcpy(buffer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_ROUTER_MODEL), 8);

	printf("Router model stored in FLASH at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_ROUTER_MODEL);
	printf("%02X%02X%02X%02X%02X%02X%02X%02X\n\n", buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF, buffer[6] & 0xFF, buffer[7] & 0xFF);

	return(0);
}

U_BOOT_CMD(printmodel, 1, 1, do_print_model, "print router model stored in FLASH\n", NULL);

#endif /* if defined(OFFSET_ROUTER_MODEL) */

#if defined(OFFSET_PIN_NUMBER)
/*
 * Show pin number
 */
int do_print_pin(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char buffer[9];

	// get pin number from flash and print it
	memcpy(buffer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_PIN_NUMBER), 8);
	buffer[8] = 0;

	printf("Router pin number stored in FLASH at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_PIN_NUMBER);
	printf("%s\n\n", buffer);

	return(0);
}

U_BOOT_CMD(printpin, 1, 1, do_print_pin, "print WPS pin stored in FLASH\n", NULL);

#endif /* if defined(OFFSET_PIN_NUMBER) */

#if defined(CONFIG_NETCONSOLE)
/*
 * Start NetConsole
 */
int do_start_nc(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	return(run_command("setenv stdin nc;setenv stdout nc;setenv stderr nc;version;", 0));
}

U_BOOT_CMD(startnc, 1, 0, do_start_nc, "start net console\n", NULL);

/*
 * Start Serial Console
 */
int do_start_sc(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	return(run_command("setenv stdin serial;setenv stdout serial;setenv stderr serial;version;", 0));
}

U_BOOT_CMD(startsc, 1, 0, do_start_sc, "start serial console\n", NULL);

#endif /* if defined(CONFIG_NETCONSOLE) */

#if defined(CONFIG_CMD_ENV) && defined(CONFIG_CMD_FLASH)
/*
 * Erase environment sector
 */
int do_default_env(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	int	rc, rcode = 0;
	int len;
	ulong end_addr, flash_sect_addr;
#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	ulong flash_offset;
	unsigned char env_buffer[CFG_ENV_SECT_SIZE];
#endif

#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	flash_offset    = CFG_ENV_ADDR & (CFG_ENV_SECT_SIZE-1);
	flash_sect_addr = CFG_ENV_ADDR & ~(CFG_ENV_SECT_SIZE-1);

	/* copy whole env sector to temporary buffer */
	memcpy(env_buffer, (void *)flash_sect_addr, CFG_ENV_SECT_SIZE);

	/* clear env part */
	memset((uchar *)((unsigned long)env_buffer + flash_offset), 0xFF, CFG_ENV_SIZE);

	len	 = CFG_ENV_SECT_SIZE;
#else
	flash_sect_addr = CFG_ENV_ADDR;
	len = CFG_ENV_SIZE;
#endif

	end_addr = flash_sect_addr + len - 1;

	/* erase whole env sector */
	if(flash_sect_erase(flash_sect_addr, end_addr)){
		rcode = 1;
	}

#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	/* restore data from buffer in FLASH */
	rc = flash_write((char *)env_buffer, flash_sect_addr, len);

	if(rc != 0){
		flash_perror(rc);
		rcode = 1;
	}
#endif

	return(rcode);
}

U_BOOT_CMD(defenv, 1, 0, do_default_env, "reset environment variables to their default values\n", NULL);
#endif /* if CONFIG_CMD_ENV && CONFIG_CMD_FLASH */

/*
 * Allows to get reset button status:
 * - returns 0 if button is pressed
 * - returns 1 if button is not pressed
 *
 * Logic here must be inverted as in shell
 * 0 means success/true
 *
 * This allows to use it in scripts, ex.:
 * if button; then ...; else ...; fi ...
 *
 * or, simply:
 * button && echo pressed!
 * button || echo not pressed!
 */
#if defined(CONFIG_CMD_BUTTON)
int do_button(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
#if defined(CFG_HUSH_PARSER)
	return !reset_button_status();
#else
	int btn = reset_button_status();

	if (btn)
		puts("Reset button is pressed\n");
	else
		puts("Reset button is not pressed\n");

	return !btn;
#endif
}

U_BOOT_CMD(button, 1, 1, do_button,
	"get reset button status\n", NULL);
#endif /* CONFIG_CMD_BUTTON */

/*
 * Allows to delay execution
 * for a given/specified time (in ms)
 */
#if defined(CONFIG_CMD_SLEEP)
int do_sleep(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	if (argc != 2) {
		print_cmd_help(cmdtp);
		return 1;
	}

	milisecdelay(simple_strtoul(argv[1], NULL, 10));

	return 0;
}

U_BOOT_CMD(sleep, 2, 1, do_sleep,
	"sleep for specified time\n", "ms\n"
	"\t- sleep for 'ms' number of milliseconds\n");
#endif /* CONFIG_CMD_SLEEP */

/*
 * Turns on/off LED/s
 */
#if defined(CONFIG_CMD_LED)
int do_ledon(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	all_led_on();

	return 0;
}

int do_ledoff(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	all_led_off();

	return 0;
}

U_BOOT_CMD(ledon,  1, 1, do_ledon,  "turn LED/s on\n", NULL);
U_BOOT_CMD(ledoff, 1, 1, do_ledoff, "turn LED/s off\n", NULL);
#endif /* CONFIG_CMD_LED */
