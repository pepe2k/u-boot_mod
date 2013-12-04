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
 * Set and store PLL configuration in FLASH
 */
int do_set_clocks(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	unsigned int outdiv, range, refdiv, divint, cpu_div, ram_div, ahb_div, spi_div;
	unsigned int cpu_pll_config_reg_val = 0;
	unsigned int clock_control_reg_val  = 0;
	unsigned int spi_control_reg_val    = 0;
	unsigned char *data_pointer;
	int i;
	char buf[128];

	// allow only 9 arg (command name + range refdiv divint outdiv cpu_div ram_div ahb_div spi_div)
	if(argc != 9){
		puts("** Notice: you should always make a backup of your device\n           entire FLASH content before making any changes\n\n");

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

	// range validation
	range = simple_strtoul(argv[1], NULL, 10);

	if(range != 1 && range != 0){
		puts("## Error: range should be 0 or 1!\n");
		return(1);
	}

	// refdiv validation (5 bits)
	refdiv = simple_strtoul(argv[2], NULL, 10);

	if(refdiv > 31 || refdiv < 1){
		puts("## Error: refdiv should be in range 1..31!\n");
		return(1);
	}

	// divint validation (6 bits)
	divint = simple_strtoul(argv[3], NULL, 10);

	if(divint > 63 || divint < 1){
		puts("## Error: divint should be in range 1..63!\n");
		return(1);
	}

	// outdiv validation (3 bits)
	outdiv = simple_strtoul(argv[4], NULL, 10);

	if(outdiv > 7 || outdiv < 1){
		puts("## Error: outdiv should be in range 1..7!\n");
		return(1);
	}

	// cpu_div validation (2 bits)
	cpu_div = simple_strtoul(argv[5], NULL, 10);

	if(cpu_div > 4 || cpu_div < 1){
		puts("## Error: cpu_div should be in range 1..4!\n");
		return(1);
	}

	// ram_div validation (2 bits)
	ram_div = simple_strtoul(argv[6], NULL, 10);

	if(ram_div > 4 || ram_div < 1){
		puts("## Error: ram_div should be in range 1..4!\n");
		return(1);
	}

	// ahb_div validation (2 bits)
	ahb_div = simple_strtoul(argv[7], NULL, 10);

	if(ahb_div > 4 || ahb_div < 1){
		puts("## Error: ahb_div should be in range 1..4!\n");
		return(1);
	}

	// spi_div validation (6 bits)
	spi_div = simple_strtoul(argv[8], NULL, 10);

	if(spi_div > 128 || spi_div < 4 || (spi_div % 2)){
		puts("## Error: spi_div should be even and in range 4..128!\n");
		return(1);
	}

	// SPI CLK = (AHB_CLK / ((CLOCK_DIVIDER + 1) * 2)),
	// spi_div = 2 * (CLOCK_DIVIDER + 1)
	// we need CLOCK_DIVIDER:
	spi_div /= 2;
	spi_div--;

	puts("Calculated registers values:\n");

	// calculate registers values
	// MAKE_CPU_PLL_CONFIG_VAL(divint, refdiv, range, outdiv)
	cpu_pll_config_reg_val = (unsigned int)(MAKE_CPU_PLL_CONFIG_VAL(divint, refdiv, range, outdiv));
	printf("- CPU_PLL_CONFIG: 0x%08X\n", cpu_pll_config_reg_val);

	// MAKE_CPU_CLK_CONTROL_VAL(cpudiv, ddrdiv, ahbdiv)
	clock_control_reg_val = (unsigned int)(MAKE_CPU_CLK_CONTROL_VAL(cpu_div, ram_div, ahb_div));
	printf("- CLOCK_CONTROL:  0x%08X\n", clock_control_reg_val);

	// SPI_CONTROL
	spi_control_reg_val = (unsigned int)(0x40 | spi_div);
	printf("- SPI_CONTROL:    0x%08X\n\n", spi_control_reg_val);

	// backup entire block in which we store PLL/CLK settings
	data_pointer = (unsigned char *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS;

	if(!data_pointer){
		puts("## Error: couldn't allocate RAM for data block backup!\n");
		return(1);
	}

	puts("** Notice: you should always make a backup of your device\n           entire FLASH content before making any changes\n\n");

	memcpy((void *)data_pointer, (void *)(CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET), PLL_IN_FLASH_DATA_BLOCK_LENGTH);

	// save PLL_IN_FLASH_MAGIC
	for(i = 0; i < 4; i++){
		data_pointer[PLL_IN_FLASH_MAGIC_OFFSET + i] = 0xFF & (PLL_IN_FLASH_MAGIC >> (8 * (3 - i)));
	}

	// save CPU_PLL_CONFIG
	for(i = 0; i < 4; i++){
		data_pointer[PLL_IN_FLASH_MAGIC_OFFSET + 4 + i] = 0xFF & (cpu_pll_config_reg_val >> (8 * (3 - i)));
	}

	// save CLOCK_CONTROL
	for(i = 0; i < 4; i++){
		data_pointer[PLL_IN_FLASH_MAGIC_OFFSET + 8 + i] = 0xFF & (clock_control_reg_val >> (8 * (3 - i)));
	}

	// save SPI_CONTROL
	for(i = 0; i < 4; i++){
		data_pointer[PLL_IN_FLASH_MAGIC_OFFSET + 12 + i] = 0xFF & (spi_control_reg_val >> (8 * (3 - i)));
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
}

U_BOOT_CMD(setclocks, 9, 0, do_set_clocks, "set PLL and clocks configuration in FLASH\n",
		"range refdiv divint outdiv cpu_div ram_div ahb_div spi_div\n"
		"\t- calculates and stores CPU_PLL_CONFIG and CLOCK_CONTROL registers in FLASH\n"
		"\t- default configuration for 400/400/200/33 MHz:\n"
		"\t  0 1 32 1 1 1 2 6 (25 MHz ref, PLL -> ((25 / 1) * 32) / (1 / 2 ^ 1) = 400 MHz)\n"
		"\t  0 1 20 1 1 1 2 6 (40 MHz ref, PLL -> ((40 / 1) * 20) / (1 / 2 ^ 1) = 400 MHz)\n\n"
		"\t- formulas for PLL and clocks calculations:\n"
		"\t  PLL = ((ref / refdiv) * divint) / (1 / (2 ^ outdiv))\n"
		"\t  CPU = PLL / cpu_div\n"
		"\t  RAM = PLL / ram_div\n"
		"\t  AHB = PLL / ahb_div\n"
		"\t  SPI = AHB / spi_div\n\n"
		"\t  *ref - reference clock (25 or 40 MHz)\n");

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
