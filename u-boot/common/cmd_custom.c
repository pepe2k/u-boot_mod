/*
 * (C) Copyright 2013
 * Piotr Dymacz (pepe2k), Real Time Systems, piotr@realtimesystems.pl, pepe2k@gmail.com
 * Custom commands for U-Boot 1.1.4 modification.
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
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>
#include "../board/ar7240/common/ar7240_flash.h"

extern void ar7240_sys_frequency(u32 *cpu_freq, u32 *ddr_freq, u32 *ahb_freq);

#if defined(OFFSET_MAC_ADDRESS)
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
#if defined(CFG_LONGHELP)
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
		puts("## Error: given MAC address has wrong format (should be: xx:xx:xx:xx:xx:xx)!\n");
		return(1);
	}

	// backup block with MAC address from flash in RAM
	data_pointer = (unsigned char *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS;

	if(!data_pointer){
		puts("## Error: couldn't allocate RAM for data block backup!\n");
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
			WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
			CFG_FLASH_BASE + OFFSET_MAC_DATA_BLOCK,
			OFFSET_MAC_DATA_BLOCK_LENGTH);

	printf("Executing: %s\n\n", buf);

	return(run_command(buf, 0));
}

U_BOOT_CMD(setmac, 2, 0, do_set_mac, "save new MAC address in FLASH\n", "xx:xx:xx:xx:xx:xx\n\t- change MAC address stored in FLASH (xx - value in hex format)\n");

#endif /* if defined(OFFSET_MAC_ADDRESS) */

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

#if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || \
    defined(CONFIG_FOR_DRAGINO_V2)          || \
    defined(CONFIG_FOR_MESH_POTATO_V2)
/*
 * Erase environment sector
 */
int do_default_env(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	int	rc, rcode = 0;
#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	unsigned char env_buffer[CFG_ENV_SECT_SIZE];
#endif

#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	/* copy whole env sector to temporary buffer */
	memcpy(env_buffer, (void *)CFG_ENV_ADDR, CFG_ENV_SECT_SIZE);

	/* clear env part */
	memset(env_buffer, 0xFF, CFG_ENV_SIZE);
#endif

	/* erase whole env sector */
	if(flash_sect_erase(CFG_ENV_ADDR, CFG_ENV_ADDR + CFG_ENV_SECT_SIZE - 1)){
		rcode = 1;
	}

#if defined(CFG_ENV_SECT_SIZE) && (CFG_ENV_SECT_SIZE > CFG_ENV_SIZE)
	/* restore data from buffer in FLASH */
	rc = flash_write((char *)env_buffer, CFG_ENV_ADDR, CFG_ENV_SECT_SIZE);

	if(rc != 0){
		flash_perror(rc);
		rcode = 1;
	}
#endif

	return(rcode);
}

U_BOOT_CMD(defenv, 1, 0, do_default_env, "reset environment variables to their default values\n", NULL);
#endif /* if defined(CONFIG_FOR_8DEVICES_CARAMBOLA2) || defined(CONFIG_FOR_DRAGINO_V2) || defined(CONFIG_FOR_MESH_POTATO_V2) */

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)

typedef struct {
	// Clocks in MHz
	unsigned short cpu_clock;
	unsigned short ram_clock;
	unsigned short ahb_clock;
	unsigned short spi_clock;

	// Registers values
	// (more info in includes/configs/ap121.h)
	unsigned int cpu_clk_control;
	unsigned int cpu_pll_config;
	unsigned int spi_control;
} ar9331_clock_profile;

static const ar9331_clock_profile oc_profiles[] = {
	{
	 200, 200, 100, 25,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 2),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 2),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},

	{
	 200, 200, 200, 33,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 2),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(32, 1, 0, 2),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 225, 225, 112, 28,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 2),
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},

	{
	 225, 225, 225, 28,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 2),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

	{
	 250, 250, 125, 31,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 2),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},

	{
	 250, 250, 250, 31,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 1),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 2),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(20, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},

	{
	 300, 300, 150, 25,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(15, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(24, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 325, 325, 162, 27,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(26, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},

	{
	 350, 350, 175, 29,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(28, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},
#endif

	{
	 360, 360, 180, 30,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(18, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(29, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 380, 380, 190, 32,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(19, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},
#endif

	{
	 400, 400, 200, 33,
	 CPU_CLK_CONTROL_VAL_DEFAULT,
	 CPU_PLL_CONFIG_VAL_DEFAULT,
	 AR7240_SPI_CONTROL_DEFAULT
	},

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 412, 412, 206, 34,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(33, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},
#endif

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 420, 420, 210, 35,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(21, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},
#endif

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 425, 425, 212, 35,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(34, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},

	{
	 437, 437, 218, 27,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(35, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 440, 440, 220, 27,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(22, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 450, 450, 225, 28,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(36, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

	{
	 460, 460, 230, 29,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(23, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(37, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 475, 475, 237, 30,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(38, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 480, 480, 240, 30,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(24, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 487, 487, 243, 30,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(39, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

	{
	 500, 500, 250, 31,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(40, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},

	{
	 500, 250, 250, 31,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 2),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(25, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(40, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 520, 520, 260, 32,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 1, 2),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(26, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(8)
	},
#endif

#if !defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 525, 262, 131, 33,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(42, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},
#endif

	{
	 560, 280, 140, 35,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4),
#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(28, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(45, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},

#if defined(CONFIG_40MHZ_XTAL_SUPPORT)
	{
	 580, 290, 145, 36,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 4),
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(29, 1, 0, 1),
	 MAKE_AR9331_SPI_CONTROL_VAL(4)
	},
#endif

	{
	 600, 300, 200, 33,
	 MAKE_AR9331_CPU_CLK_CONTROL_VAL(1, 2, 3),
#if CONFIG_40MHZ_XTAL_SUPPORT
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(30, 1, 0, 1),
#else
	 MAKE_AR9331_CPU_PLL_CONFIG_VAL(48, 1, 0, 1),
#endif
	 MAKE_AR9331_SPI_CONTROL_VAL(6)
	},
};

/*
 * Set and store PLL configuration in FLASH
 */
int do_set_clocks(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned int cpu_pll_config_flash, cpu_clock_control_flash, spi_control_flash, reg;
	unsigned int ahb_freq, ddr_freq, cpu_freq, spi_freq;
	unsigned int *data_pointer;
	int i, index, profiles_count;
	char buf[128];

	profiles_count = sizeof(oc_profiles) / sizeof(ar9331_clock_profile);

	// print all available profiles and current settings
	if(argc == 1){

		// read clocks
		ar7240_sys_frequency(&cpu_freq, &ddr_freq, &ahb_freq);

		// calculate SPI clock (we need to set bit 0 to 1 in SPI_FUNC_SELECT to access SPI registers)
		ar7240_reg_wr(AR7240_SPI_FS, 0x01);
		spi_freq = ahb_freq / (((ar7240_reg_rd(AR7240_SPI_CLOCK) & 0x3F) + 1) * 2);
		ar7240_reg_wr(AR7240_SPI_FS, 0x0);

		// make MHz from Hz
		cpu_freq /= 1000000;
		ddr_freq /= 1000000;
		ahb_freq /= 1000000;
		spi_freq /= 1000000;

		printf("Current clocks (approximated):\n- CPU: %3d MHz\n", cpu_freq);
		printf("- RAM: %3d MHz\n", ddr_freq);
		printf("- AHB: %3d MHz\n", ahb_freq);
		printf("- SPI: %3d MHz\n", spi_freq);

		// reference clock
		if(ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) & HORNET_BOOTSTRAP_SEL_25M_40M_MASK){
			puts("- REF:  40 MHz\n\n");
		} else {
			puts("- REF:  25 MHz\n\n");
		}

		// do we have PLL_MAGIC in FLASH?
		reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET);

		// read all register values stored in FLASH
		cpu_pll_config_flash = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 4);
		cpu_clock_control_flash = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 8);
		spi_control_flash = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 12);

		printf("Available PLL and clocks configurations: %d\n\n", profiles_count);

		puts("      | CPU | RAM | AHB | SPI | [ ]\n  ---------------------------------\n");

		for(i = 0; i <  profiles_count; i++){
			printf("%4d. |%4d |%4d |%4d |%4d | ", i + 1,
												  oc_profiles[i].cpu_clock,
												  oc_profiles[i].ram_clock,
												  oc_profiles[i].ahb_clock,
												  oc_profiles[i].spi_clock);

			if(reg == PLL_IN_FLASH_MAGIC &&
			   oc_profiles[i].cpu_pll_config == cpu_pll_config_flash &&
			   oc_profiles[i].cpu_clk_control == cpu_clock_control_flash &&
			   oc_profiles[i].spi_control == spi_control_flash){
				puts("[*]\n");
			} else {
				puts("[ ]\n");
			}
		}

		puts("\n[*] = currently selected profile (stored in FLASH).\nAll clocks in MHz, run 'setclk X' to choose one.\n\n");
		puts("** Notice:\n   you should always make a backup of your device\n   entire FLASH content before making any changes\n\n");

		return(0);
	} else {
		// selected index
		index = simple_strtoul(argv[1], NULL, 10);

		if(index > profiles_count || index < 1){
			printf("## Error: selected index should be in range 1..%d!\n", profiles_count);
			return(1);
		}

		printf("You have selected profile: %d.\n\n", index);

		// array is zero-based indexing
		index--;

		// backup entire block in which we store PLL/CLK settings
		data_pointer = (unsigned int *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS;

		if(!data_pointer){
			puts("## Error: couldn't allocate RAM for data block backup!\n");
			return(1);
		}

		memcpy((void *)data_pointer, (void *)(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET), PLL_IN_FLASH_DATA_BLOCK_LENGTH);

		// save PLL_IN_FLASH_MAGIC and PLL/clocks registers values
		data_pointer = (unsigned int *)(WEBFAILSAFE_UPLOAD_RAM_ADDRESS + PLL_IN_FLASH_MAGIC_OFFSET);
		*data_pointer = PLL_IN_FLASH_MAGIC;

		data_pointer++;
		*data_pointer = oc_profiles[index].cpu_pll_config;

		data_pointer++;
		*data_pointer = oc_profiles[index].cpu_clk_control;

		data_pointer++;
		*data_pointer = oc_profiles[index].spi_control;

		// erase FLASH, copy data from RAM
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET,
				PLL_IN_FLASH_DATA_BLOCK_LENGTH,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET,
				PLL_IN_FLASH_DATA_BLOCK_LENGTH);

		printf("Executing: %s\n\n", buf);

		return(run_command(buf, 0));
	}
}

U_BOOT_CMD(setclk, 2, 0, do_set_clocks, "select clocks configuration from predefined list\n",
		"index\n"
		"\t- save 'index' configuration in FLASH\n"
		"setclk\n"
		"\t- prints available clocks configurations and current settings");

/*
 * Remove (clear) PLL and clock settings in FLASH
 */
int do_clear_clocks(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned char *data_pointer;
	int i;
	char buf[128];
	unsigned int reg = 0;

	// do we have PLL_MAGIC in FLASH?
	reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET);

	if(reg == PLL_IN_FLASH_MAGIC){
		// backup entire block in which we store PLL/CLK settings
		data_pointer = (unsigned char *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS;

		if(!data_pointer){
			puts("## Error: couldn't allocate RAM for data block backup!\n");
			return(1);
		}

		memcpy((void *)data_pointer, (void *)(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET), PLL_IN_FLASH_DATA_BLOCK_LENGTH);

		// 16 bytes (4x 32-bit values)
		for(i = 0; i < 16; i++){
			data_pointer[PLL_IN_FLASH_MAGIC_OFFSET + i] = 0xFF;
		}

		// erase FLASH, copy data from RAM
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET,
				PLL_IN_FLASH_DATA_BLOCK_LENGTH,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET,
				PLL_IN_FLASH_DATA_BLOCK_LENGTH);

		printf("Executing: %s\n\n", buf);

		return(run_command(buf, 0));
	} else {
		puts("** Warning: there is no PLL and clocks configuration in FLASH!\n");
		return(1);
	}
}

U_BOOT_CMD(clearclk, 1, 0, do_clear_clocks, "remove PLL and clocks configuration from FLASH\n", NULL);
#endif /* #if defined(PLL_IN_FLASH_MAGIC_OFFSET) */
