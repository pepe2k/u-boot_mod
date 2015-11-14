#include <config.h>
#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

#define ALIGN_SIZE		"8"

DECLARE_GLOBAL_DATA_PTR;

static u32 mac_is_not_valid = 1;

/*
 * Prints available information about the board
 */
void print_board_info(void)
{
	u32 ahb_clk, cpu_clk, ddr_clk, spi_clk, ref_clk;
	bd_t *bd = gd->bd;
	char buffer[24];

	/* Board name */
#ifdef BOARD_CUSTOM_STRING
	printf("%" ALIGN_SIZE "s %s\n", "BOARD:", BOARD_CUSTOM_STRING);
#endif

	/* SOC name, version and revision */
	qca_soc_name_rev(buffer);
	printf("%" ALIGN_SIZE "s %s\n", "SOC:", buffer);

	/* MIPS CPU type */
	cpu_name(buffer);
	printf("%" ALIGN_SIZE "s %s\n", "CPU:", buffer);

	/* RAM size and type */
	printf("%" ALIGN_SIZE "s ", "RAM:");
	print_size(bd->bi_memsize, "");

	switch (qca_mem_type()) {
		case QCA_RST_BOOTSTRAP_MEM_TYPE_SDR_VAL:
			puts(" SDR\n");
			break;
		case QCA_RST_BOOTSTRAP_MEM_TYPE_DDR1_VAL:
			puts(" DDR1\n");
			break;
		case QCA_RST_BOOTSTRAP_MEM_TYPE_DDR2_VAL:
			puts(" DDR2\n");
			break;
		default:
			puts("\n");
			break;
	}

	/* FLASH size and type */
	printf("%" ALIGN_SIZE "s ", "FLASH:");
	flash_print_name();
	puts("\n");

	/* MAC address */
	printf("%" ALIGN_SIZE "s %02X:%02X:%02X:%02X:%02X:%02X", "MAC:",
		bd->bi_enetaddr[0],bd->bi_enetaddr[1], bd->bi_enetaddr[2],
		bd->bi_enetaddr[3], bd->bi_enetaddr[4], bd->bi_enetaddr[5]);

	if (mac_is_not_valid) {
		puts(" (fixed)\n");
	} else {
		puts("\n");
	}

	/* System clocks */
	printf("%" ALIGN_SIZE "s CPU/RAM/AHB/SPI/REF\n", "CLOCKS:");

	qca_sys_clocks(&cpu_clk, &ddr_clk, &ahb_clk, &spi_clk, &ref_clk);
	cpu_clk = cpu_clk / 1000000;
	ddr_clk = ddr_clk / 1000000;
	ahb_clk = ahb_clk / 1000000;
	spi_clk = spi_clk / 1000000;
	ref_clk = ref_clk / 1000000;

	printf("%" ALIGN_SIZE "s %d/%d/%d/%3d/%3d MHz\n",
		" ", cpu_clk, ddr_clk, ahb_clk, spi_clk, ref_clk);

	puts("\n");
}

/*
 * Reads MAC address if available or uses fixed one
 */
void macaddr_init(u8 *mac_addr)
{
	u8 buffer[6];
	u8 fixed_mac[6] = {0x00, 0x03, 0x7F, 0x09, 0x0B, 0xAD};

#if defined(OFFSET_MAC_ADDRESS)
	memcpy(buffer, (void *)(CFG_FLASH_BASE
		+ OFFSET_MAC_DATA_BLOCK + OFFSET_MAC_ADDRESS), 6);

	/*
	 * Check first LSBit (I/G bit) and second LSBit (U/L bit) in MSByte of vendor part
	 * both of them should be 0:
	 * I/G bit == 0 -> Individual MAC address (unicast address)
	 * U/L bit == 0 -> Burned-In-Address (BIA) MAC address
	 */
	if (CHECK_BIT((buffer[0] & 0xFF), 0) != 0 ||
		CHECK_BIT((buffer[0] & 0xFF), 1) != 0) {
		memcpy(buffer, fixed_mac, 6);
	} else {
		mac_is_not_valid = 0;
	}
#else
	memcpy(buffer, fixed_mac, 6);
#endif

	memcpy(mac_addr, buffer, 6);
}

/*
 * Returns main CPU clock in Hz
 */
u32 main_cpu_clk(void)
{
	u32 cpu_clk;

	qca_sys_clocks(&cpu_clk, NULL, NULL, NULL, NULL);

	return cpu_clk;
}
