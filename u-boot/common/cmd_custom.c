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

#if defined(OFFSET_MAC_ADDRESS2)
U_BOOT_CMD(printmac, 1, 1, do_print_mac, "print MAC addresses stored in flash\n", NULL);
#else
U_BOOT_CMD(printmac, 1, 1, do_print_mac, "print MAC address stored in flash\n", NULL);
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

	puts("** Notice: you should always make a backup of your device\n           entire FLASH content before making any changes\n\n");

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

#if defined(CONFIG_MACH_HORNET)
// TODO: AR9344 support
/*
 * Show current CPU/RAM/AHB/SPI/REF clocks
 */
int do_print_clocks(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned int ahb_freq, ddr_freq, cpu_freq, spi_freq;
#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
	unsigned int pll, ref, reg;
#endif

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

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
	if(ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) & HORNET_BOOTSTRAP_SEL_25M_40M_MASK){
		ref = 40000000;
	} else {
		ref = 25000000;
	}

	// do we have PLL_MAGIC in FLASH?
	reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET);

	if(reg == PLL_IN_FLASH_MAGIC){
		puts("\nClocks configuration stored in FLASH (approximated):\n");

		// read CPU PLL Configuration register (CPU_PLL_CONFIG) value stored in FLASH (PLL_IN_FLASH_MAGIC_OFFSET + 4)
		reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 4);

		// refdiv
		pll = ref / ((reg & HORNET_PLL_CONFIG_REFDIV_MASK) >> HORNET_PLL_CONFIG_REFDIV_SHIFT);

		// div_int
		pll *= ((reg & HORNET_PLL_CONFIG_NINT_MASK) >> HORNET_PLL_CONFIG_NINT_SHIFT);

		// outdiv
		pll >>= ((reg & HORNET_PLL_CONFIG_OUTDIV_MASK) >> HORNET_PLL_CONFIG_OUTDIV_SHIFT);

		// read CLOCK CONTROL Configuration register (CLOCK_CONTROL) value stored in FLASH (PLL_IN_FLASH_MAGIC_OFFSET + 8)
		reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 8);

		// cpu, ram, ahb
		cpu_freq = pll / (((reg & HORNET_CLOCK_CONTROL_CPU_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_CPU_POST_DIV_SHIFT) + 1);
		ddr_freq = pll / (((reg & HORNET_CLOCK_CONTROL_DDR_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_DDR_POST_DIV_SFIFT) + 1);
		ahb_freq = pll / (((reg & HORNET_CLOCK_CONTROL_AHB_POST_DIV_MASK) >> HORNET_CLOCK_CONTROL_AHB_POST_DIV_SFIFT) + 1);

		// read SPI CONTROL Configuration register (SPI_CONTROL) value stored in FLASH (PLL_IN_FLASH_MAGIC_OFFSET + 12)
		reg = ar7240_reg_rd(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET + 12);

		// spi
		spi_freq = ahb_freq / (2 * ((reg & 0x3F) + 1));

		// make MHz from Hz
		cpu_freq /= 1000000;
		ddr_freq /= 1000000;
		ahb_freq /= 1000000;
		spi_freq /= 1000000;

		printf("- CPU: %3d MHz\n", cpu_freq);
		printf("- RAM: %3d MHz\n", ddr_freq);
		printf("- AHB: %3d MHz\n", ahb_freq);
		printf("- SPI: %3d MHz\n", spi_freq);
	} else {
		puts("\nPLL and clocks configuration in FLASH is empty,\nuse 'setclocks' to set them and store in FLASH.\n");
	}
#endif

	if(ar7240_reg_rd(HORNET_BOOTSTRAP_STATUS) & HORNET_BOOTSTRAP_SEL_25M_40M_MASK){
		puts("\nReference clock: 40 MHz\n");
	} else {
		puts("\nReference clock: 25 MHz\n");
	}

	return(0);
}

U_BOOT_CMD(printclocks, 1, 1, do_print_clocks, "print CPU, RAM, AHB, SPI and REF clocks\n", NULL);
#endif /* #if defined(CONFIG_MACH_HORNET) */

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
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

U_BOOT_CMD(clearclocks, 1, 0, do_clear_clocks, "remove PLL and clocks configuration from FLASH\n", NULL);
#endif /* #if defined(PLL_IN_FLASH_MAGIC_OFFSET) */
