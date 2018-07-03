/*
 * Copyright (C) 2017 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <cmd_qcagpio.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <linux/ctype.h>

#if defined(CONFIG_CMD_GPIO)

#define _GPIO_OUT_MUX_MAX	127
#define _GPIO_NUM_MAX		(QCA_GPIO_COUNT - 1)

#if (SOC_TYPE & QCA_AR933X_SOC)
static void gpio_set_func(u32 func, u32 enable)
{
	u32 val;

	if (func < gpio_funcs_1_cnt) {
		val = qca_soc_reg_read(QCA_GPIO_FUNC_1_REG);

		if (enable)
			val |= gpio_funcs_1[func].reg_mask;
		else
			val &= ~gpio_funcs_1[func].reg_mask;

		qca_soc_reg_write(QCA_GPIO_FUNC_1_REG, val);

		return;
	}

	func -= gpio_funcs_1_cnt;
	val = qca_soc_reg_read(QCA_GPIO_FUNC_2_REG);

	if (enable)
		val |= gpio_funcs_2[func].reg_mask;
	else
		val &= ~gpio_funcs_2[func].reg_mask;

	qca_soc_reg_write(QCA_GPIO_FUNC_2_REG, val);
}
#else
static void gpio_func_gate(u8 disable, u8 enable)
{
	u32 val;

	switch (disable) {
	case QCA_GPIO_OUT_MUX_CLK_OBS0_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS0_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS1_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS1_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS2_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS2_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS3_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS3_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS4_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS4_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS5_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS5_EN_MASK;
		break;
#if (SOC_TYPE & QCA_AR934X_SOC)  ||\
    (SOC_TYPE & QCA_QCA953X_SOC) ||\
    (SOC_TYPE & QCA_QCA956X_SOC)
	case QCA_GPIO_OUT_MUX_CLK_OBS6_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS6_EN_MASK;
		break;
#endif
#if (SOC_TYPE & QCA_AR934X_SOC)
	case QCA_GPIO_OUT_MUX_CLK_OBS7_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS7_EN_MASK;
		break;
#endif
#if (SOC_TYPE & QCA_QCA953X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC) ||\
    (SOC_TYPE & QCA_QCA956X_SOC)
	case QCA_GPIO_OUT_MUX_SRIF_OUT_VAL:
		val = QCA_GPIO_FUNC_GPIO_SRIF_EN_MASK;
		break;
#endif
	default:
		val = 0;
		break;
	}

	if (val)
		qca_soc_reg_read_clear(QCA_GPIO_FUNC_REG, val);

	switch (enable) {
	case QCA_GPIO_OUT_MUX_CLK_OBS0_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS0_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS1_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS1_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS2_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS2_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS3_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS3_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS4_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS4_EN_MASK;
		break;
	case QCA_GPIO_OUT_MUX_CLK_OBS5_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS5_EN_MASK;
		break;
#if (SOC_TYPE & QCA_AR934X_SOC)  ||\
    (SOC_TYPE & QCA_QCA953X_SOC) ||\
    (SOC_TYPE & QCA_QCA956X_SOC)
	case QCA_GPIO_OUT_MUX_CLK_OBS6_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS6_EN_MASK;
		break;
#endif
#if (SOC_TYPE & QCA_AR934X_SOC)
	case QCA_GPIO_OUT_MUX_CLK_OBS7_VAL:
		val = QCA_GPIO_FUNC_CLK_OBS7_EN_MASK;
		break;
#endif
#if (SOC_TYPE & QCA_QCA953X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC) ||\
    (SOC_TYPE & QCA_QCA956X_SOC)
	case QCA_GPIO_OUT_MUX_SRIF_OUT_VAL:
		val = QCA_GPIO_FUNC_GPIO_SRIF_EN_MASK;
		break;
#endif
	default:
		val = 0;
		break;
	}

	if (val)
		qca_soc_reg_read_set(QCA_GPIO_FUNC_REG, val);
}

static u32 gpio_in_func_to_gpio(u8 func)
{
	u32 val, reg, shift;

	if (func > (gpio_in_funcs_cnt - 1))
		return _GPIO_OUT_MUX_MAX;

	reg = QCA_GPIO_IN_EN0_REG + (4 * (gpio_in_funcs[func].offset / 4));
	shift = 8 * (gpio_in_funcs[func].offset % 4);

	val = qca_soc_reg_read(reg);
	val &= (0xff << shift);
	val = val >> shift;

	return val;
}

static u8 gpio_get_out_func(u32 gpio_num)
{
	u32 val, reg, shift;

	reg = QCA_GPIO_OUT_FUNC0_REG + (4 * (gpio_num / 4));
	shift = 8 * (gpio_num % 4);

	val = qca_soc_reg_read(reg);
	val &= (0xff << shift);
	val = val >> shift;

	return (u8)val;
}

static void gpio_set_in_out_func(u32 gpio_num, u8 func, u32 output)
{
	u32 val, reg, shift;

	if (output) {
		reg = QCA_GPIO_OUT_FUNC0_REG + (4 * (gpio_num / 4));
		shift = 8 * (gpio_num % 4);
	} else {
		if (func > (gpio_in_funcs_cnt - 1))
			return;

		reg = QCA_GPIO_IN_EN0_REG + (4 * (gpio_in_funcs[func].offset / 4));
		shift = 8 * (gpio_in_funcs[func].offset % 4);
	}

	val = qca_soc_reg_read(reg);
	val &= ~(0xff << shift);

	if (output)
		val |= (func << shift);
	else
		val |= (gpio_num << shift);

	qca_soc_reg_write(reg, val);
}
#endif /* SOC_TYPE & QCA_AR933X_SOC */

static void gpio_set_jtag(u32 enable)
{
#if (SOC_TYPE & QCA_AR933X_SOC)
	if (enable)
		qca_soc_reg_read_clear(QCA_GPIO_FUNC_1_REG,
				       QCA_GPIO_FUNC_1_JTAG_DIS_MASK);
	else
		qca_soc_reg_read_set(QCA_GPIO_FUNC_1_REG,
				     QCA_GPIO_FUNC_1_JTAG_DIS_MASK);
#else
	if (enable)
		qca_soc_reg_read_clear(QCA_GPIO_FUNC_REG,
				       QCA_GPIO_FUNC_JTAG_DIS_MASK);
	else
		qca_soc_reg_read_set(QCA_GPIO_FUNC_REG,
				     QCA_GPIO_FUNC_JTAG_DIS_MASK);
#endif
}

static void gpio_set_val(u32 gpio_mask, u32 high)
{
	if (high)
		qca_soc_reg_write(QCA_GPIO_SET_REG, gpio_mask);
	else
		qca_soc_reg_write(QCA_GPIO_CLEAR_REG, gpio_mask);
}

static void gpio_set_dir(u32 gpio_mask, u32 output)
{
	if (gpio_mask & QCA_GPIO_JTAG_MASK)
		gpio_set_jtag(0);

#if (SOC_TYPE & QCA_AR933X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC)
	if (output)
		qca_soc_reg_read_set(QCA_GPIO_OE_REG, gpio_mask);
	else
		qca_soc_reg_read_clear(QCA_GPIO_OE_REG, gpio_mask);
#else
	if (output)
		qca_soc_reg_read_clear(QCA_GPIO_OE_REG, gpio_mask);
	else
		qca_soc_reg_read_set(QCA_GPIO_OE_REG, gpio_mask);
#endif
}

static void gpio_list_cfg(void)
{
	u32 gpio_in_reg, gpio_out_reg, gpio_oe_reg;
	u32 gpio_num, gpio_mask;
	u32 output, val;
	u32 jtag_en = 1;

#if (SOC_TYPE & ~QCA_AR933X_SOC)
	u8 func, i;
#endif

#if defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_H) ||\
    defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_L) ||\
    defined(CONFIG_QCA_GPIO_MASK_LED_ACT_H)  ||\
    defined(CONFIG_QCA_GPIO_MASK_LED_ACT_L)

	#if defined(CONFIG_QCA_GPIO_MASK_LED_ACT_H)
		u32 mask_led_h = CONFIG_QCA_GPIO_MASK_LED_ACT_H;
	#else
		u32 mask_led_h = 0;
	#endif

	#if defined(CONFIG_QCA_GPIO_MASK_LED_ACT_L)
		u32 mask_led_l = CONFIG_QCA_GPIO_MASK_LED_ACT_L;
	#else
		u32 mask_led_l = 0;
	#endif

	#if defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_H)
		u32 mask_out_h = CONFIG_QCA_GPIO_MASK_OUT_INIT_H;
	#else
		u32 mask_out_h = 0;
	#endif

	#if defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_L)
		u32 mask_out_l = CONFIG_QCA_GPIO_MASK_OUT_INIT_L;
	#else
		u32 mask_out_l = 0;
	#endif

	mask_out_l |= mask_led_h;
	mask_out_h |= mask_led_l;
#endif

	puts("\n");
#if (SOC_TYPE & ~QCA_AR933X_SOC)
	puts("   # | DIR | VAL | DEF | LED | BTN | JTAG | FUNCTION\n"
	     " ----+-----+-----+-----+-----+-----+------+----------\n");
#else
	puts("   # | DIR | VAL | DEF | LED | BTN | JTAG\n"
	     " ----+-----+-----+-----+-----+-----+------\n");
#endif

	gpio_oe_reg  = qca_soc_reg_read(QCA_GPIO_OE_REG);
	gpio_in_reg  = qca_soc_reg_read(QCA_GPIO_IN_REG);
	gpio_out_reg = qca_soc_reg_read(QCA_GPIO_OUT_REG);

#if (SOC_TYPE & QCA_AR933X_SOC)
	val = qca_soc_reg_read(QCA_GPIO_FUNC_1_REG);
	if (val & QCA_GPIO_FUNC_1_JTAG_DIS_MASK)
		jtag_en = 0;
#else
	val = qca_soc_reg_read(QCA_GPIO_FUNC_REG);
	if (val & QCA_GPIO_FUNC_JTAG_DIS_MASK)
		jtag_en = 0;
#endif

	for (gpio_num = 0; gpio_num < QCA_GPIO_COUNT; gpio_num++) {
		gpio_mask = (1 << gpio_num);

		/* GPIO number */
		printf("%4d", gpio_num);
		puts(" | ");

#if (SOC_TYPE & QCA_AR933X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC)
		output = 0;
		if (gpio_mask & gpio_oe_reg)
			output = 1;
#else
		output = 1;
		if (gpio_mask & gpio_oe_reg)
			output = 0;
#endif

		/* GPIO direction */
		if (output) {
			printf("%-3s", "out");
			val = gpio_mask & gpio_out_reg;
		} else {
			printf("%-3s", "in");
			val = gpio_mask & gpio_in_reg;
		}

		puts(" | ");

		/* GPIO value */
		if (val)
			printf("%-3s", "hi");
		else
			printf("%-3s", "lo");

		puts(" | ");

		/* GPIO default value */
#if defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_H) ||\
    defined(CONFIG_QCA_GPIO_MASK_OUT_INIT_L) ||\
    defined(CONFIG_QCA_GPIO_MASK_LED_ACT_H)  ||\
    defined(CONFIG_QCA_GPIO_MASK_LED_ACT_L)
		if (output) {
			if (gpio_mask & mask_out_h)
				printf("%-3s", "hi");
			else if (gpio_mask & mask_out_l)
				printf("%-3s", "lo");
			else
				printf("%-3s", "-");
		} else
			printf("%-3s", "-");
#else
		printf("%-3s", "-");
#endif
		puts(" | ");

		/* GPIO in LED mask */
#if defined(CONFIG_QCA_GPIO_MASK_LED_ACT_H) ||\
    defined(CONFIG_QCA_GPIO_MASK_LED_ACT_L)
		if (output) {
			if (gpio_mask & mask_led_h)
				printf("%-3s", "hi");
			else if (gpio_mask & mask_led_l)
				printf("%-3s", "lo");
			else
				printf("%-3s", "-");
		} else
			printf("%-3s", "-");
#else
		printf("%-3s", "-");
#endif
		puts(" | ");

		/* GPIO configured as RST button */
#if defined(CONFIG_GPIO_RESET_BTN)
		if (!output && (gpio_mask & (1 << CONFIG_GPIO_RESET_BTN)))
	#if defined(CONFIG_GPIO_RESET_BTN_ACTIVE_LOW)
			printf("%-3s", "lo");
	#else
			printf("%-3s", "hi");
	#endif
		else
			printf("%-3s", "-");
#else
		printf("%-3s", "-");
#endif
		puts(" | ");

		/* JTAG enabled? */
		if (jtag_en && (gpio_mask & QCA_GPIO_JTAG_MASK))
			printf("%-4s", "en");
		else
			printf("%-4s", "-");

#if (SOC_TYPE & ~QCA_AR933X_SOC)
		puts(" | ");

		/* GPIO input/output function */
		val = 0;
		if (output) {
			func = gpio_get_out_func(gpio_num);
			for (i = 0; i < gpio_out_funcs_cnt; i++)
				if (gpio_out_funcs[i].value == func) {
					printf("%s (%d)",
					       gpio_out_funcs[i].name, func);

					val = 1;
				}

			if (!val)
				printf("%s (%d)", "unknown", func);
		} else {
			for (i = 0; i < gpio_in_funcs_cnt; i++) {
				if (gpio_num == gpio_in_func_to_gpio((u8)i)) {
					if (val)
						printf(",\n%43s %s (%d)", "|",
						       gpio_in_funcs[i].name, i);
					else
						printf("%s (%d)",
						       gpio_in_funcs[i].name, i);

					val = 1;
				}
			}

			if (!val)
				puts("gpio (-)");
		}
#endif

		puts("\n");
	}

	puts("\n");
}

#if (SOC_TYPE & QCA_AR933X_SOC)
static void gpio_list_funcs(void)
{
	u32 i, j, n, val;
	u32 found;

	puts("\n");
	puts("   # | EN | FUNCTION       | RELATED GPIOs\n"
	     " ----+----+----------------+---------------\n");

	val = qca_soc_reg_read(QCA_GPIO_FUNC_1_REG);
	for (i = 0; i < gpio_funcs_1_cnt; i++) {
		printf("%4d", i);
		puts(" | ");

		if (val & gpio_funcs_1[i].reg_mask)
			puts("en");
		else
			puts("  ");

		puts(" | ");
		printf("%-14s", gpio_funcs_1[i].name);
		puts(" | ");

		found = 0;
		if (gpio_funcs_1[i].gpio_mask) {
			for (n = 0; n < _GPIO_NUM_MAX; n++) {
				if (gpio_funcs_1[i].gpio_mask & (1 << n)) {
					if (found)
						puts(", ");

					printf("%2d", n);
					found = 1;
				}
			}
		}

		if (found)
			puts("\n");
		else
			puts("-\n");
	}

	j = gpio_funcs_1_cnt;
	val = qca_soc_reg_read(QCA_GPIO_FUNC_2_REG);
	for (i = 0; i < gpio_funcs_2_cnt; i++) {
		printf("%4d", j);
		puts(" | ");

		if (val & gpio_funcs_2[i].reg_mask)
			puts("en");
		else
			puts("  ");

		puts(" | ");
		printf("%-14s", gpio_funcs_2[i].name);
		puts(" | ");

		found = 0;
		if (gpio_funcs_2[i].gpio_mask) {
			for (n = 0; n < _GPIO_NUM_MAX; n++) {
				if (gpio_funcs_2[i].gpio_mask & (1 << n)) {
					if (found)
						puts(", ");

					printf("%2d", n);
					found = 1;
				}
			}
		}

		if (found)
			puts("\n");
		else
			puts("-\n");

		j++;
	}

	puts("\n");
}
#else
static void gpio_list_in_out_funcs(void)
{
	u32 i;

	puts("\n");
	puts("    # | DIR | FUNCTION\n"
	     " -----+-----+----------\n");

	for (i = 0; i < gpio_in_funcs_cnt; i++) {
		printf("%5d", i);
		puts(" | ");
		printf("%-3s", "in");
		puts(" | ");
		printf("%s\n", gpio_in_funcs[i].name);
	}

	puts(" -----+-----+---------\n");

	for (i = 0; i < gpio_out_funcs_cnt; i++) {
		printf("%5d", gpio_out_funcs[i].value);
		puts(" | ");
		printf("%-3s", "out");
		puts(" | ");
		printf("%s\n", gpio_out_funcs[i].name);
	}

	puts("\n");
}
#endif

int do_gpio(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 gpio_mask, gpio_num = 0;
	u32 output = 1;
	u32 func = 0;
	u32 val = 0;

#if (SOC_TYPE & QCA_AR933X_SOC)
	u32 func_max = gpio_funcs_1_cnt + gpio_funcs_2_cnt - 2;
	u32 func_en;
#else
	u32 func_max = gpio_in_funcs_cnt - 1;
	u32 func_old;
#endif

	/* We need at least one arg */
	if (argc == 1) {
usage:
		print_cmd_help(cmdtp);
		return 1;
	}

	switch (*argv[1]) {
	case 'f':
		if (argc < 4)
			goto usage;

#if (SOC_TYPE & QCA_AR933X_SOC)
		func = simple_strtoul(argv[2], NULL, 10);
		if (func > func_max) {
			printf_err("GPIO function is out of range (0~%d)\n",
				   func_max);

			return 1;
		}

		switch (*argv[3]) {
		case 'e':
			func_en = 1;
			break;
		case 'd':
			func_en = 0;
			break;
		default:
			goto usage;
		}

		gpio_set_func(func, func_en);

		return 0;
#else
		if (strcmp(argv[1], "fin") == 0)
			output = 0;
		else if (strcmp(argv[1], "fout") == 0)
			func_max = _GPIO_OUT_MUX_MAX;
		else
			goto usage;

		func = simple_strtoul(argv[3], NULL, 10);
		if (func > func_max) {
			printf_err("GPIO function is out of range (0~%d)\n",
				   func_max);

			return 1;
		}

		break;
#endif
	case 'j':
		if (argc < 2)
			goto usage;

		switch (*argv[2]) {
		case 'e':
			gpio_set_jtag(1);
			break;
		case 'd':
			gpio_set_jtag(0);
			break;
		default:
			goto usage;
		}

		return 0;
	case 'l':
		if (argc < 3)
			gpio_list_cfg();
		else if (*argv[2] == 'f')
#if (SOC_TYPE & QCA_AR933X_SOC)
			gpio_list_funcs();
#else
			gpio_list_in_out_funcs();
#endif
		else
			goto usage;

		return 0;
	case 's':
	case 'c':
	case 't':
	case 'i':
		if (argc < 3)
			goto usage;

		if (*argv[1] == 's')
			val = 1;

		break;
	default:
		goto usage;
	}

	gpio_num = simple_strtoul(argv[2], NULL, 10);
	if (gpio_num > _GPIO_NUM_MAX) {
		printf_err("GPIO must be in range 0~%d\n", _GPIO_NUM_MAX);
		return 1;
	}

	gpio_mask = (1 << gpio_num);

	switch (*argv[1]) {
	case 's':
	case 'c':
#if (SOC_TYPE & ~QCA_AR933X_SOC)
	case 'f':
		if (output)
			func_old = gpio_get_out_func(gpio_num);
#endif

		gpio_set_dir(gpio_mask, output);

#if (SOC_TYPE & ~QCA_AR933X_SOC)
		gpio_set_in_out_func(gpio_num, (u8)func, output);
#endif

		if ((*argv[1] == 's') || (*argv[1] == 'c'))
			gpio_set_val(gpio_mask, val);

#if (SOC_TYPE & ~QCA_AR933X_SOC)
		if (output && (func != func_old))
			gpio_func_gate(func_old, func);
#endif

		break;
	case 't':
		val = qca_soc_reg_read(QCA_GPIO_OE_REG);
#if (SOC_TYPE & QCA_AR933X_SOC) ||\
    (SOC_TYPE & QCA_QCA955X_SOC)
		if (!(gpio_mask & val)) {
#else
		if (gpio_mask & val) {
#endif
			printf_err("GPIO is not set as output\n");
			return 1;
		}

#if (SOC_TYPE & ~QCA_AR933X_SOC)
		func = (u32)gpio_get_out_func(gpio_num);
		if (func > 0) {
			printf_err("GPIO out function is not set to GPIO\n");
			return 1;
		}
#endif

		val = qca_soc_reg_read(QCA_GPIO_OUT_REG);
		if (gpio_mask & val)
			gpio_set_val(gpio_mask, 0);
		else
			gpio_set_val(gpio_mask, 1);

		break;
	case 'i':
		gpio_set_dir(gpio_mask, 0);

		if (!(gpio_mask & qca_soc_reg_read(QCA_GPIO_IN_REG)))
			return 1;
	}

	return 0;
}

U_BOOT_CMD(gpio, 4, 0, do_gpio,
	   "control GPIO",
	   "<c>lear|<i>nput|<s>et|<t>oggle <gpio>\n"
	   "\t- setup <gpio> as in/out and change/get its value\n"
#if (SOC_TYPE & QCA_AR933X_SOC)
	   "gpio <f>unction <func> <e>nable|<d>isable\n"
	   "\t- enable/disable function <func>\n"
#else
	   "gpio <fin|fout> <gpio> <func>\n"
	   "\t- set <gpio> in/out function to <func>\n"
#endif
	   "gpio <j>tag <e>nable|<d>isable\n"
	   "\t- enable/disable JTAG\n"
	   "gpio <l>ist\n"
	   "\t- show current GPIO configuration\n"
	   "gpio <l>ist <f>unctions\n"
#if (SOC_TYPE & QCA_AR933X_SOC)
	   "\t- show all GPIO functions\n"
#else
	   "\t- show all known GPIO in/out functions"
#endif
);

#endif /* CONFIG_CMD_GPIO */
