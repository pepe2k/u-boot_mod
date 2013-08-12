/*
 * (C) Copyright 2013
 * Piotr Dymacz (pepe2k), Real Time Systems, piotr@realtimesystems.pl, pepe2k@gmail.com
 * Custom commands for TP-Link U-Boot 1.1.4 modification.
 *
 * See file CREDITS for list of people who contributed to U-Boot project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <command.h>

#if defined(OFFSET_MAC_ADDRESS)
/*
 * Show MAC address(es)
 */
int do_print_mac(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	char buffer[6];
#ifdef OFFSET_MAC_ADDRESS2
	char buffer2[6];
#endif

#ifdef OFFSET_MAC_ADDRESS2
	// get MAC1 and MAC2 addresses from flash and print them
	memcpy(buffer,  (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS),  6);
	memcpy(buffer2, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS2), 6);

	puts("Current MAC addresses stored in flash:\n");
	printf("MAC1 at 0x%X: %02X:%02X:%02X:%02X:%02X:%02X\n", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS,
															buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF);

	printf("MAC2 at 0x%X: %02X:%02X:%02X:%02X:%02X:%02X\n\n", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS2,
															  buffer2[0] & 0xFF, buffer2[1] & 0xFF, buffer2[2] & 0xFF, buffer2[3] & 0xFF, buffer2[4] & 0xFF, buffer2[5] & 0xFF);
#else
	// get MAC address from flash and print it
	memcpy(buffer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS), 6);

	printf("Current MAC address stored in flash at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS);
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n\n", buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF);
#endif

	return(0);
}

U_BOOT_CMD(printmac, 1, 1, do_print_mac, "print MAC address(es) stored in flash\n", NULL);

/*
 * Change MAC address(es)
 */
int do_set_mac(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char *data_pointer;
	char buf[128];
	int i = 0, j = 0;

	// allow only 2 arg (command name + mac), second argument length should be 17 (xx:xx:xx:xx:xx:xx)
	if(argc != 2 || strlen(argv[1]) != 17){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	// count ':'
	for(i = 0; i< 17; i++){
		if(argv[1][i] == ':'){
			j++;
		}
	}

	if(j != 5){
#ifdef CFG_LONGHELP
		if(cmdtp->help != NULL){
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->help);
		} else {
			printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
		}
#else
		printf("Usage:\n%s %s\n", cmdtp->name, cmdtp->usage);
#endif
		return(1);
	}

	// backup block with MAC address from flash in RAM
	data_pointer = (unsigned char *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS;

	if(!data_pointer){
		printf("## Error: couldn't allocate RAM for data block backup!\n");
		return(1);
	}

	memcpy((void *)data_pointer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS), OFFSET_MAC_DATA_BLOCK_LENGTH);

	// store new MAC address in RAM
	for(i = 0; i < 6; i++){
		data_pointer[OFFSET_MAC_ADDRESS + i] = simple_strtoul((char *)(argv[1] + i*3), NULL, 16);
	}

	// now we can erase flash and write data from RAM
	sprintf(buf,
			"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
			CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK,
			OFFSET_MAC_DATA_BLOCK_LENGTH,
			WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
			CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK,
			OFFSET_MAC_DATA_BLOCK_LENGTH);

	printf("Executing: %s\n\n", buf);

	return(run_command(buf, 0));
}

U_BOOT_CMD(setmac, 2, 0, do_set_mac, "save new MAC address in flash\n", "xx:xx:xx:xx:xx:xx\n\t- change MAC address stored in flash (xx - value in hex format)\n");

#endif /* if defined(OFFSET_MAC_ADDRESS) */

#if defined(OFFSET_ROUTER_MODEL)
/*
 * Show TP-Link router model
 */
int do_print_model(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char buffer[8];

	// get router model from flash and print it
	memcpy(buffer, (void *)(CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_ROUTER_MODEL), 8);

	printf("Router model stored in flash at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_ROUTER_MODEL);
	printf("%02X%02X%02X%02X%02X%02X%02X%02X\n\n", buffer[0] & 0xFF, buffer[1] & 0xFF, buffer[2] & 0xFF, buffer[3] & 0xFF, buffer[4] & 0xFF, buffer[5] & 0xFF, buffer[6] & 0xFF, buffer[7] & 0xFF);

	return(0);
}

U_BOOT_CMD(printmodel, 1, 1, do_print_model, "print router model stored in flash\n", NULL);

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

	printf("Router pin number stored in flash at offset 0x%X: ", CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK + OFFSET_PIN_NUMBER);
	printf("%s\n\n", buffer);

	return(0);
}

U_BOOT_CMD(printpin, 1, 1, do_print_pin, "print WPS pin stored in flash\n", NULL);

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

#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2)
/*
 * Erase environment sector
 */
int do_erase_env(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	char buf[64];

	sprintf(buf,
			"erase 0x%lX +0x%lX",
			CFG_ENV_ADDR,
			CFG_ENV_SIZE);

	printf("Executing: %s\n\n", buf);

	return(run_command(buf, 0));
}

U_BOOT_CMD(eraseenv, 1, 1, do_erase_env, "erase environment sector in flash\n", NULL);
#endif /* if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) */
