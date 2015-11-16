#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

	.globl lowlevel_init
	.type  lowlevel_init, @function
	.text
	.align 4

#define CLEAR_BIT(val, bit)				((val) & ~(1 << (bit)))
#define SET_BIT(val, bit)				((val) |  (1 << (bit)))

#define CLEAR_PLL_POWER_DOWN(reg_val)	CLEAR_BIT(reg_val, 30)
#define SET_PLL_POWER_DOWN(reg_val)		SET_BIT(reg_val, 30)
#define SET_AHB_DIV_TO_4(reg_val)		SET_BIT(SET_BIT(reg_val, 15), 16)
#define CLEAR_PLL_BYPASS(reg_val)		CLEAR_BIT(reg_val, 2)
#define SET_PLL_BYPASS(reg_val)			SET_BIT(reg_val, 2)

/*
 * Helper macros.
 * These Clobber t7, t8 and t9
 * or  t8, t8, t9;
 */
#define set_reg(_reg, _val) \
	li t7, KSEG1ADDR(_reg); \
	lw t8, 0(t7);           \
	li t9, _val;            \
	sw t9, 0(t7);

/* if reset button is active low -> use bne (branch on not equal) */
#ifdef GPIO_RST_BUTTON_IS_ACTIVE_LOW
	#define recovery_jump(_branch) \
		bne t1, (1 << GPIO_RST_BUTTON_BIT), _branch;
#else
	#define recovery_jump(_branch) \
		beq t1, (1 << GPIO_RST_BUTTON_BIT), _branch;
#endif

lowlevel_init:

#if 1
/* These three wlan reset will avoid original issue,
 * so full chip reset isn't needed here.
 *
 * WLAN_RESET in RST_RESET (AR7240_RESET) register
 * 0x00C06B30 -> BIT(11) is set
 * 0x00C06330 -> BIT(11) is not set
 */
	set_reg(AR7240_RESET, 0x00C06B30)
	nop
	set_reg(AR7240_RESET, 0x00C06330)
	nop
	set_reg(AR7240_RESET, 0x00C06B30)
	nop
	set_reg(AR7240_RESET, 0x00C06330)
	nop

reset_wlan:
	set_reg(AR7240_RESET, 0x00C06B30)
	nop
	set_reg(AR7240_RESET, 0x00C06330)
	nop
	li t5, 0x20

check_val:
	beq  zero, t5, reset_wlan
	addi t5,   t5, -1
	li   t6,   KSEG1ADDR(HORNET_BOOTSTRAP_STATUS)
	lw   t7,   0(t6)
	li   t8,   0x10
	and  t7,   t7, t8
	bne  zero, t7, check_val
	set_reg(HORNET_BOOTSTRAP_STATUS, 0x0002110E)
	nop
#else
/* clear wlan reset bit in RESET_Register 0x1c */
	set_reg(AR7240_RESET, 0x00C06B30)
	nop
	set_reg(AR7240_RESET, 0x00C06330)
	nop

/* cleck bootstrap status, wait for bit4 on, then clear bit16 */
wait_loop0:
	li  t6,   KSEG1ADDR(HORNET_BOOTSTRAP_STATUS)
	lw  t7,   0(t6)
	li  t8,   0x10
	and t7,   t7, t8
	bne zero, t7, wait_loop0
	nop
	set_reg(HORNET_BOOTSTRAP_STATUS, 0x0002110E)
	nop
#endif

/* RTC reset */
/* 0x1810704C -> RTC_FORCE_WAKE (RTC Force Wake) */
	set_reg(0x1810704C, 0x00000003)
	nop
	nop
/* 0x18107040 -> RTC_RESET (RTC Reset and Force Sleep and Force Wakeup) */
	set_reg(0x18107040, 0x00000000)
	nop
	nop
	set_reg(0x18107040, 0x00000001)
	nop

wait_loop1:
/* 0x18107044 -> RTC_STATUS (RTC Sleep Status) */
	li  t6, KSEG1ADDR(0x18107044)
	lw  t7, 0(t6)
	li  t8, 0x2
	and t7, t7, t8
	bne t8, t7, wait_loop1
	nop

/*
 * AHB/APH reset
 * TODO: 0x18104000 is "Reset the Host Interface (HOST_INTF_RESET_CONTROL)" and bits 0:7 are RESERVED!
 */
/*
	set_reg(0x18104000, 0x00000003)
	nop
	set_reg(0x18104000, 0x00000000)
	nop
*/
/*
 * MAC reset (TODO: ?? AR9344 has 0x18107000 register -> AR9344_RTC_BASE)
 */
/*
	set_reg(0x18107000, 0x0000000F)
	nop
	set_reg(0x18107000, 0x00000000)
	nop
*/

#if 1  /* fetch pmu1.refv and ctrl2.tx from OTP */
	li t1, KSEG1ADDR(0x18114014)
	lw t2, 0(t1)

otp_loop0:
	li  t3, KSEG1ADDR(0x18115F18)
	lw  t4, 0(t3)
	nop
	li  t5, 0x7
	and t4, t4, t5
	li  t5, 0x4
	bne t4, t5, otp_loop0
	nop
	li  t6, KSEG1ADDR(0x18115F1C)
	lw  t7, 0(t6)
	nop
	li  t8, 0x80000080
	and t9, t7, t8
	beq t8, t9, fetch_otp

otp_loop0_end:
	li  t1, KSEG1ADDR(0x18114004)
	lw  t2, 0(t1)

otp_loop1:
	li  t3, KSEG1ADDR(0x18115F18)
	lw  t4, 0(t3)
	nop
	li  t5, 0x7
	and t4, t4, t5
	li  t5, 0x4
	bne t4, t5, otp_loop1
	nop
	li  t6, KSEG1ADDR(0x18115F1C)
	lw  t7, 0(t6)
	nop
	li  t8, 0x80000080
	and t9, t7, t8

default_pmu:
	li  t5, 0x80			/* default 0x031c4386 */
	bne t8, t9, otp_end

fetch_otp:
	srl t8, t7, 0x18
	li  t1, 0xf
	and t2, t1, t7			/* USB */
	and t5, t1, t8			/* PMU */

check_pmu:
	li  t0, 0x4				/* PMU range should be 0x4~0xa */
	bgt t0, t5, default_pmu
	nop
	li  t0, 0xa				/* PMU range should be 0x4~0xa */
	blt t0, t5, default_pmu
	nop
	li  t0, 0x4
	sll t5, t5, t0

otp_end:
#endif

#if 1 /* Program PMU */
#define PMU_TEST_NO 1000
	li t6, KSEG1ADDR(0x18116C40)
	li t9, 0xbd000010
	li t0, 0
	li t1, 0
	li t2, 0
	li t3, PMU_TEST_NO
	sw t3, 12(t9)

pmu_loop0:
	beq   zero, t3, pmu_loop0_end
	nop
	addi  t3,   t3, -1
	li    t7,   0x10180000  /* ldo_tune 0x3 */
	nop
	sw    t7,   4(t6)
	nop
	lw    t8,   4(t6)
	nop
	beq   t8,   t7, pmu_loop0_end
	nop
	addiu t0,   t0, 1
	b     pmu_loop0
	nop

pmu_loop0_end:
	li t3, PMU_TEST_NO

pmu_loop1:
	beq  zero, t3, pmu_loop1_end
	nop
	addi t3,   t3, -1
	//li   t7,   0x031c4326    /* 1.100V */
	//li   t7,   0x031c4336    /* 1.125V */
	//li   t7,   0x031c4346    /* 1.150V */
	//li   t7,   0x031c4356    /* 1.175V */
	//li   t7,   0x031c4366    /* 1.200V */
	//li   t7,   0x031c4376    /* 1.225V */
	li   t7,   0x031c4386    /* 1.250V (DEFAULT) */
	//li   t7,   0x031c4396    /* 1.275V */
	//li   t7,   0x031c43a6    /* 1.300V */
	nop

#if 1 /* from OTP */
	li  t8, 0xFFFFFF0F
	and t7, t7, t8
	or  t7, t7, t5
#endif
	sw    t7, 0(t6)
	nop
	lw    t8, 0(t6)
	nop
	beq   t8, t7, pmu_loop1_end
	nop
	addiu t1, t1, 1
	b     pmu_loop1
	nop

pmu_loop1_end:
	li t3, PMU_TEST_NO

pmu_loop2:
	beq   zero, t3, pmu_loop2_end
	nop
	addi  t3,   t3, -1
	li    t7,   0x10380000  /* ldo_tune 0x3 */
	nop
	sw    t7,   4(t6)
	nop
	lw    t8,   4(t6)
	nop
	beq   t8,   t7, pmu_loop2_end
	nop
	addiu t2,   t2, 1
	b     pmu_loop2
	nop

pmu_loop2_end:
	sw t0, 0(t9)
	nop
	sw t1, 4(t9)
	nop
	sw t2, 8(t9)
	nop
#endif

#if 1 /* Program ki, kd */
// TODO: ??
/* Program ki/kd */
#if CONFIG_40MHZ_XTAL_SUPPORT
	set_reg(0x18116244, 0x19e82f01)
#else
	set_reg(0x18116244, 0x18e82f01)
#endif
	nop
    
/* Program phase shift */
	li  t6, KSEG1ADDR(0x18116248)
	lw  t7, 0(t6)
	li  t8, 0xc07fffff
	and t7, t7, t8
	li  t8, 0x800000
	or  t7, t7, t8
	sw  t7, 0(t6)
	nop
#endif

/* max AHB Master wait time out ... */
	set_reg(0x1800009C, 0xfffff)
	nop

/*
 * O/C recovery mode
 *
 * If RESET BUTTON is pressed and hold during power on
 * we will use default PLL and clocks configuration (400/400/200)
 *
 * Using t0 and t1 (t1 indicates if recovery mode was turned on)
 */
pll_clock_control_oc_recovery:
	li  t0, KSEG1ADDR(AR7240_GPIO_IN)
	lw  t1, 0(t0)
	and t1, t1, (1 << GPIO_RST_BUTTON_BIT)
	recovery_jump(pll_clock_control_default)
	nop

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
/*
 * PLL and CLOCK configuration from FLASH
 *
 * Using t0, t2 and t3 (t2 stores magic value from flash)
 */
pll_clock_control_flash:
	li  t0, (CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET)	// load PLL_IN_FLASH_MAGIC address
	lw  t2, 0(t0)																			// load PLL_IN_FLASH_MAGIC value from FLASH
	bne t2, PLL_IN_FLASH_MAGIC, pll_clock_control											// jump if we don't have PLL_MAGIC value in FLASH
	nop
	lw  t3, 8(t0)																			// load CLOCK_CONTROL register value from FLASH
	or  t3, t3, 0x18004																		// set BYPASS bit and make AHB_POST_DIV = 4
	li  t0, KSEG1ADDR(AR7240_CPU_CLOCK_CONTROL)												// load CLOCK_CONTROL register address
	sw  t3, 0(t0)																			// store value in CLOCK_CONTROL register
	j   pll_settle_time																		// jump to pll_settle_time
	nop
#endif

pll_clock_control:
/* set PLL bypass(Bit 2), CPU_POST_DIV, DDR_POST_DIV, AHB_POST_DIV in CPU clock control */
/* in some cases, the SoC doesn't start with higher clock on AHB */
	set_reg(AR7240_CPU_CLOCK_CONTROL, SET_AHB_DIV_TO_4(SET_PLL_BYPASS(CPU_CLK_CONTROL_VAL)))
	j pll_settle_time
	nop

pll_clock_control_default:
/* set PLL bypass(Bit 2), CPU_POST_DIV, DDR_POST_DIV, AHB_POST_DIV in CPU clock control */
/* in some cases, the SoC doesn't start with higher clock on AHB */
	set_reg(AR7240_CPU_CLOCK_CONTROL, SET_AHB_DIV_TO_4(SET_PLL_BYPASS(CPU_CLK_CONTROL_VAL_DEFAULT)))
	nop

pll_settle_time:
/* set SETTLE_TIME in CPU PLL */
	set_reg(AR7240_USB_PLL_CONFIG, CPU_PLL_SETTLE_TIME_VAL)
	nop

pll_unlock_handler_oc_recovery:
	recovery_jump(pll_unlock_handler_default)
	nop

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
pll_unlock_handler_flash:
	bne t2, PLL_IN_FLASH_MAGIC, pll_unlock_handler											// jump if we don't have PLL_MAGIC value in FLASH
	nop
	li  t0, (CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET)	// load PLL_IN_FLASH_MAGIC address
	lw  t3, 4(t0)																			// load CPU_PLL_CONFIG register value from FLASH
	or  t3, t3, 0x40000000																	// set CPU_PLLPWD bit (power down for CPU PLL)
	li  t0, KSEG1ADDR(AR7240_CPU_PLL_CONFIG)												// load CPU_PLL_CONFIG register address
	sw  t3, 0(t0)																			// store value in CPU_PLL_CONFIG register
	j   wait_loop2																			// jump to wait_loop2
	nop
#endif

pll_unlock_handler:
/* set nint, frac, refdiv, outdiv, range in CPU PLL configuration resiter */
	set_reg(AR7240_CPU_PLL_CONFIG, SET_PLL_POWER_DOWN(CPU_PLL_CONFIG_VAL))
	j wait_loop2
	nop

pll_unlock_handler_default:
/* set nint, frac, refdiv, outdiv, range in CPU PLL configuration resiter */
	set_reg(AR7240_CPU_PLL_CONFIG, SET_PLL_POWER_DOWN(CPU_PLL_CONFIG_VAL_DEFAULT))
	nop

wait_loop2:
	li  t6,   KSEG1ADDR(AR7240_CPU_PLL_CONFIG)
	lw  t7,   0(t6)
	li  t8,   0x80000000
	and t7,   t7, t8
	bne zero, t7, wait_loop2
	nop
    
/* put frac bit19:10 configuration */
/* TODO: do we need this? */
	set_reg(AR7240_PCIE_PLL_CONFIG, CPU_PLL_DITHER_FRAC_VAL)
	nop

pll_lock_handler_oc_recovery:
	recovery_jump(pll_lock_handler_default)
	nop

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
pll_lock_handler_flash:
	bne t2, PLL_IN_FLASH_MAGIC, pll_lock_handler											// jump if we don't have PLL_MAGIC value in FLASH
	nop
	li  t0, (CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET)	// load PLL_IN_FLASH_MAGIC address
	lw  t3, 4(t0)																			// load CPU_PLL_CONFIG register value from FLASH
	li  t0, KSEG1ADDR(AR7240_CPU_PLL_CONFIG)												// load CPU_PLL_CONFIG register address
	sw  t3, 0(t0)																			// store value in CPU_PLL_CONFIG register
	j   wait_loop3																			// jump to wait_loop3
	nop
#endif

pll_lock_handler:
/* clear PLL power down bit in CPU PLL configuration */
	set_reg(AR7240_CPU_PLL_CONFIG, CPU_PLL_CONFIG_VAL)
	j wait_loop3
	nop

pll_lock_handler_default:
/* clear PLL power down bit in CPU PLL configuration */
	set_reg(AR7240_CPU_PLL_CONFIG, CPU_PLL_CONFIG_VAL_DEFAULT)
	nop

wait_loop3:
/* wait for PLL update -> bit 31 in CPU_PLL_CONFIG should be 0 */
	li  t6,   KSEG1ADDR(AR7240_CPU_PLL_CONFIG)
	lw  t7,   0(t6)
	li  t8,   0x80000000
	and t7,   t7, t8
	bne zero, t7, wait_loop3
	nop

/* confirm DDR PLL lock */
	li t3, 100
	li t4, 0

start_meas0:
	addi t4, t4, 1
	bgt  t4, t3, pll_unlock_handler_oc_recovery
	nop
	li   t5, 5

start_meas:
	li  t6, KSEG1ADDR(0x18116248)
	lw  t7, 0(t6)
	li  t8, 0xBFFFFFFF
	and t7, t7, t8
	sw  t7, 0(t6)
	nop

/* delay */
	li t9, 10

delayloop0:
	subu t9, t9,   1
	bne  t9, zero, delayloop0
	nop
	li   t8, 0x40000000
	or   t7, t7,   t8
	sw   t7, 0(t6)
	nop

meas_done_statue:
	li  t6,   KSEG1ADDR(0x1811624C)
	lw  t7,   0(t6)
	li  t8,   0x8
	and t7,   t7, t8
	beq zero, t7, meas_done_statue
	nop

meas_result:
	li   t6,   KSEG1ADDR(0x18116248)
	lw   t7,   0(t6)
	li   t8,   0x007FFFF8
	and  t7,   t7, t8
	srl  t7,   t7, 3
	li   t8,   0x4000
	bgt  t7,   t8, start_meas0
	nop
	addi t5,   t5, -1
	bne  zero, t5, start_meas
	nop

pll_clear_bypass_oc_recovery:
	recovery_jump(pll_clear_bypass_default)
	nop

#if defined(PLL_IN_FLASH_MAGIC_OFFSET)
pll_clear_bypass_flash:
	bne t2, PLL_IN_FLASH_MAGIC, pll_clear_bypass											// jump if we don't have PLL_MAGIC value in FLASH
	nop
	li  t0, (CFG_FLASH_BASE + PLL_IN_FLASH_DATA_BLOCK_OFFSET + PLL_IN_FLASH_MAGIC_OFFSET)	// load PLL_IN_FLASH_MAGIC address
	lw  t3, 8(t0)																			// load CLOCK_CONTROL register value from FLASH
	li  t0, KSEG1ADDR(AR7240_CPU_CLOCK_CONTROL)												// load CLOCK_CONTROL register address
	sw  t3, 0(t0)																			// store value in CLOCK_CONTROL register
	j   end																					// jump to end
	nop
#endif

pll_clear_bypass:
/* clear PLL bypass (bit 2) in CPU CLOCK CONTROL register */
	set_reg(AR7240_CPU_CLOCK_CONTROL, CPU_CLK_CONTROL_VAL)
	j end
	nop

pll_clear_bypass_default:
/* clear PLL bypass (bit 2) in CPU CLOCK CONTROL register */
	set_reg(AR7240_CPU_CLOCK_CONTROL, CPU_CLK_CONTROL_VAL_DEFAULT)
	nop

/* Sync mode, Set Bit 8 of DDR Tap Conrtol 3 register */
/*
 * TODO: something is wrong here?
 * There is no AR7240_DDR_TAP_CONTROL3 in AR9331 datasheet!
 */
/*
	set_reg(AR7240_DDR_TAP_CONTROL3, 0x10105);
	nop
*/

end:
	jr ra
	nop
