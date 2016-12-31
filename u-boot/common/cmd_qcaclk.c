/*
 * Commands related with PLL/clocks settings
 * for Qualcomm/Atheros WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <cmd_qcaclk.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>

#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET

static void print_reg_values(const clk_cfg_flash *cfg)
{
	puts("Target values:\n");

#if (SOC_TYPE & QCA_AR933X_SOC)
	printf("         SPI_CTRL: 0x%08lX\n", cfg->spi_ctrl);
	printf("      CPU_PLL_CFG: 0x%08lX\n", cfg->regs.cpu_pll_cfg);
	printf("CPU_CLOCK_CONTROL: 0x%08lX\n", cfg->regs.cpu_clk_ctrl);
	puts("\n");
	printf("NFRAC_MIN in PLL_DITHER_FRAC: %d/%d\n",
		(cfg->regs.cpu_pll_dit & QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK)
		>> QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_SHIFT,
		(QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_MASK
		 >> QCA_PLL_CPU_PLL_DITHER_FRAC_NFRAC_MIN_SHIFT) + 1);
#else
	printf("        SPI_CTRL: 0x%08lX\n", cfg->spi_ctrl);
	printf("     CPU_PLL_CFG: 0x%08lX\n", cfg->regs.cpu_pll_cfg);
	printf("     DDR_PLL_CFG: 0x%08lX\n", cfg->regs.ddr_pll_cfg);
	printf("CPU_DDR_CLK_CTRL: 0x%08lX\n", cfg->regs.cpu_ddr_clk_ctrl);
	puts("\n");
	printf("NFRAC_MIN in CPU_PLL_DITHER: %d/%d\n",
		(cfg->regs.cpu_pll_dit & QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK)
		>> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_SHIFT,
		(QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_MASK
		 >> QCA_PLL_CPU_PLL_DITHER_NFRAC_MIN_SHIFT) + 1);

	printf("NFRAC_MIN in DDR_PLL_DITHER: %d/%d\n",
		(cfg->regs.ddr_pll_dit & QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK)
		>> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_SHIFT,
		(QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_MASK
		 >> QCA_PLL_DDR_PLL_DITHER_NFRAC_MIN_SHIFT) + 1);
#endif /* SOC_TYPE & QCA_AR933X_SOC */

	puts("\n");
}

static u32 compare_pll_regs(const pll_regs *from_flash,
							const pll_regs *to_compare)
{
#if (SOC_TYPE & QCA_AR933X_SOC)
	if (from_flash->cpu_pll_cfg == to_compare->cpu_pll_cfg &&
		from_flash->cpu_pll_dit == to_compare->cpu_pll_dit &&
		from_flash->cpu_clk_ctrl == to_compare->cpu_clk_ctrl)
		return 1;
#else
	if (from_flash->cpu_pll_cfg == to_compare->cpu_pll_cfg &&
		from_flash->ddr_pll_cfg == to_compare->ddr_pll_cfg &&
		from_flash->cpu_pll_dit == to_compare->cpu_pll_dit &&
		from_flash->ddr_pll_dit == to_compare->ddr_pll_dit &&
		from_flash->cpu_ddr_clk_ctrl == to_compare->cpu_ddr_clk_ctrl)
		return 1;
#endif /* SOC_TYPE & QCA_AR933X_SOC */

	return 0;
}

/* Set and store PLL configuration in FLASH */
int do_set_clk(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	u32 ahb_clk, cpu_clk, ddr_clk, ref_clk, reg, spi_clk;
	clk_cfg_flash from_flash, to_flash;
	const pll_regs *pll_registers;
	char buf[128];
	int i;
	u8 *c;

	/* Read current clocks and make MHz from Hz */
	qca_sys_clocks(&cpu_clk, &ddr_clk, &ahb_clk, &spi_clk, &ref_clk);

	cpu_clk /= 1000000;
	ddr_clk /= 1000000;
	ahb_clk /= 1000000;
	spi_clk /= 1000000;
	ref_clk /= 1000000;

	/* Print all available profiles and current settings */
	if (argc == 1) {
		printf("Current configuration:\n");
		printf("- CPU: %3d MHz\n", cpu_clk);
		printf("- RAM: %3d MHz\n", ddr_clk);
		printf("- AHB: %3d MHz\n", ahb_clk);
		printf("- SPI: %3d MHz\n", spi_clk);
		printf("- REF: %3d MHz\n", ref_clk);
		puts("\n");

		/* If we have PLL_MAGIC in FLASH, copy configuration from FLASH */
		reg = qca_soc_reg_read(CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET);

		/* PLL configuration starts _after_ PLL_MAGIC value */
		if (reg == QCA_PLL_IN_FLASH_MAGIC) {
			c = (u8 *)(CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET + 4);
			memcpy(&from_flash, (void *)c, sizeof(clk_cfg_flash));
		}

		puts("Clocks in MHz, run 'setclk #' to select\n");
		puts("one configuration from the below table:\n\n");
		puts("    # [ ] | CPU | RAM | AHB | SPI \n"
			 " ---------------------------------\n");

		for (i = 0; i < clk_profiles_cnt; i++) {
			printf("%5d", i + 1);

			if (reg == QCA_PLL_IN_FLASH_MAGIC) {
				if (ref_clk == 25) {
					pll_registers = &(clk_profiles[i].xtal_25mhz);
				} else {
					pll_registers = &(clk_profiles[i].xtal_40mhz);
				}

				if (from_flash.spi_ctrl == clk_profiles[i].spi_ctrl &&
					compare_pll_regs(&(from_flash.regs), pll_registers)) {
					puts(" [*] |");
				} else {
					puts(" [ ] |");
				}
			} else {
				puts(" [ ] |");
			}

			printf("%4d |%4d |%4d |%4d\n",
				   clk_profiles[i].cpu_clk,
				   clk_profiles[i].ddr_clk,
				   clk_profiles[i].ahb_clk,
				   clk_profiles[i].spi_clk);
		}

		puts("\n[*] profile currently stored in FLASH\n\n");

		/* Show some additional information */
		puts("** Notice:\n");
		printf("   configuration is stored in FLASH at: 0x%08lX\n",
			   CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET);

		printf("   magic value is: 0x%08lX, block size is: %2d B\n",
			   QCA_PLL_IN_FLASH_MAGIC, sizeof(clk_cfg_flash));

		puts("\n");

		puts("** Notice:\n");
		puts("   you should always make a backup of your devices\n");
		puts("   entire FLASH content, before making any changes\n");

#ifndef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
		puts("\n");
		printf_wrn("\n   your device does not support O/C revovery mode!\n");
#endif

		puts("\n");
	} else {
		/* Configuration selected by user */
		i = simple_strtoul(argv[1], NULL, 10);

		if (i > clk_profiles_cnt || i < 1) {
			printf_err("selected profile should be in range 1..%d!\n\n",
				   clk_profiles_cnt);
			return 1;
		}

		/* Array is zero-based indexed */
		printf("Selected profile %d:\n", i);
		i--;

		/* Copy target values */
		to_flash.spi_ctrl = clk_profiles[i].spi_ctrl;

		if (ref_clk == 25) {
			to_flash.regs = clk_profiles[i].xtal_25mhz;
		} else {
			to_flash.regs = clk_profiles[i].xtal_40mhz;
		}

		printf("- CPU: %3d MHz\n", clk_profiles[i].cpu_clk);
		printf("- RAM: %3d MHz\n", clk_profiles[i].ddr_clk);
		printf("- AHB: %3d MHz\n", clk_profiles[i].ahb_clk);
		printf("- SPI: %3d MHz\n", clk_profiles[i].spi_clk);
		puts("\n");

		print_reg_values(&to_flash);

		/* First, backup in RAM entire block where we store PLL config */
		sprintf(buf, "cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_LOADADDR,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE);

		if (run_command(buf, 0) < 0) {
			printf_err("could not make data backup in RAM!\n\n");
			return 1;
		}

		/* Overwrite PLL configuration block in RAM */
		c = (u8 *)(CONFIG_LOADADDR +
				   (CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
					- CFG_FLASH_BASE
					- CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET));

		reg = QCA_PLL_IN_FLASH_MAGIC;
		memcpy((void *)c, &reg, sizeof(reg));

		c += 4;

		if (ref_clk == 25) {
			memcpy((void *)c, &to_flash, sizeof(clk_cfg_flash));
		} else {
			memcpy((void *)c, &to_flash, sizeof(clk_cfg_flash));
		}

		/* Erase FLASH and copy modified data back */
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE,
				CONFIG_LOADADDR,
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE);

		if (run_command(buf, 0) < 0) {
			printf_err("could not erase FLASH and copy data back from RAM!\n\n");
			return 1;
		}

		puts("** Notice:\n");
		puts("   selected clocks configuration saved in FLASH,\n"
			 "   you can restart the device with 'res' command\n");

#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN
		puts("\n");
		puts("   If the device does not start, use recovery mode\n");
	#ifdef CONFIG_QCA_GPIO_OC_RECOVERY_BTN_ACTIVE_LOW
		printf("   with button connected to GPIO%d (active in low)\n",
			   CONFIG_QCA_GPIO_OC_RECOVERY_BTN);
	#else
		printf("   with button connected to GPIO%d (active in high)\n",
			   CONFIG_QCA_GPIO_OC_RECOVERY_BTN);
	#endif
#else
		puts("\n");
		printf_wrn("\n   your device does not support O/C revovery mode!\n");
#endif /* CONFIG_QCA_GPIO_OC_RECOVERY_BTN */

		puts("\n");
	}

	return 0;
}

/* Remove clock configuration from FLASH */
int do_clear_clk(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char buf[128];
	u32 reg;
	u8 *c;

	/* Do we have PLL_MAGIC in FLASH? */
	reg = qca_soc_reg_read(CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET);

	if (reg == QCA_PLL_IN_FLASH_MAGIC) {
		/* First, backup in RAM entire block where we store PLL config */
		sprintf(buf, "cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_LOADADDR,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE);

		if (run_command(buf, 0) < 0) {
			printf_err("could not make data backup in RAM!\n\n");
			return 1;
		}

		/* Clear magic value and whole configuration */
		c = (u8 *)(CONFIG_LOADADDR +
				   (CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET
					- CFG_FLASH_BASE
					- CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET));

		memset((void *)c, 0xFF, sizeof(clk_cfg_flash) + 4);

		/* Erase FLASH and copy modified data back */
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE,
				CONFIG_LOADADDR,
				CFG_FLASH_BASE + CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET,
				CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE);

		if (run_command(buf, 0) < 0) {
			printf_err("could not erase FLASH and copy data back from RAM!\n\n");
			return 1;
		}
	} else {
		printf_wrn("clock configuration is not stored in FLASH!\n\n");
		return 1;
	}

	return 0;
}

U_BOOT_CMD(setclk, 2, 0, do_set_clk,
		   "select clocks configuration from predefined list\n",
		   "index\n"
		   "\t- save 'index' configuration in FLASH\n"
		   "setclk\n"
		   "\t- prints available clocks configurations and current settings\n");

U_BOOT_CMD(clearclk, 1, 0, do_clear_clk,
		   "remove PLL and clocks configuration from FLASH\n", NULL);

#endif /* CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET */
