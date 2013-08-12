#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

    .globl hornet_pll_init
	.text
	.align 4

/*
 * Helper macros.
 * These Clobber t7, t8 and t9
 */ 
/*     or  t8, t8, t9;                                 \ */
#define set_reg(_reg, _val)                         \
    li  t7, KSEG1ADDR(_reg);                        \
    lw  t8, 0(t7);                                  \
    li  t9, _val;                                   \
    sw  t9, 0(t7);

hornet_pll_init:

#if 1
/* These three wlan reset will avoid original issue, 
so full chip reset isn't needed here. */
    set_reg(0xb806001c, 0x00c06b30)
    nop
    set_reg(0xb806001c, 0x00c06330)
    nop    
    set_reg(0xb806001c, 0x00c06b30)
    nop    
    set_reg(0xb806001c, 0x00c06330)  
    nop  
reset_wlan:
    set_reg(0xb806001c, 0x00c06b30) 
    nop    
    set_reg(0xb806001c, 0x00c06330)
    nop

    li  t5, 0x20
check_val:
    beq zero, t5, reset_wlan
    addi t5, t5, -1    
    li  t6, 0xb80600ac
    lw  t7, 0(t6)
    li  t8, 0x10
    and t7, t7, t8
    bne zero, t7, check_val 
    
    set_reg(HORNET_BOOTSTRAP_STATUS, 0x0002110e)
    nop
#else
/* clear wlan reset bit in RESET_Register 0x1c */
    set_reg(AR7240_RESET, 0x00c06b30)
    nop
    set_reg(AR7240_RESET, 0x00c06330)
    nop

/* cleck bootstrap status, wait for bit4 on, then clear bit16 */
wait_loop0:
    li  t6, KSEG1ADDR(HORNET_BOOTSTRAP_STATUS)
    lw  t7, 0(t6)
    li  t8, 0x10
    and t7, t7, t8
    bne zero, t7, wait_loop0
    nop
    set_reg(HORNET_BOOTSTRAP_STATUS, 0x0002110e)
    nop
#endif    
    
/* RTC reset */
    set_reg(0x1810704c, 0x00000003)
    nop
    nop
    set_reg(0x18107040, 0x00000000)
    nop
    nop
    set_reg(0x18107040, 0x00000001)
    nop
wait_loop1:
    li  t6, KSEG1ADDR(0x18107044)
    lw  t7, 0(t6)
    li  t8, 0x2
    and t7, t7, t8
    bne t8, t7, wait_loop1
    nop

    /* AHB/APH reset */    
    set_reg(0x18104000, 0x00000003)
    nop
    set_reg(0x18104000, 0x00000000)
    nop

    /* MAC reset */
    set_reg(0x18107000, 0x0000000F)
    nop
    set_reg(0x18107000, 0x00000000)
    nop

#if 1  /* fetch pmu1.refv and ctrl2.tx from OTP */
    li  t1, KSEG1ADDR(0x18114014)
    lw  t2, 0(t1)
otp_loop0:
    li  t3, KSEG1ADDR(0x18115f18)
    lw  t4, 0(t3)
    nop
    li  t5, 0x7
    and t4, t4, t5
    li  t5, 0x4
    bne t4, t5, otp_loop0
    nop

    li  t6, KSEG1ADDR(0x18115f1c)
    lw  t7, 0(t6)
    nop
    li  t8, 0x80000080
    and t9, t7, t8
    beq t8, t9, fetch_otp
otp_loop0_end:

    li  t1, KSEG1ADDR(0x18114004)
    lw  t2, 0(t1)
otp_loop1:
    li  t3, KSEG1ADDR(0x18115f18)
    lw  t4, 0(t3)
    nop
    li  t5, 0x7
    and t4, t4, t5
    li  t5, 0x4
    bne t4, t5, otp_loop1
    nop

    li  t6, KSEG1ADDR(0x18115f1c)
    lw  t7, 0(t6)
    nop
    li  t8, 0x80000080
    and t9, t7, t8
default_pmu:
    li  t5, 0x80             /* default 0x031c4386 */
    bne t8, t9, otp_end
otp_loop1_end:

fetch_otp:
    srl t8, t7, 0x18
    li  t1, 0xf
    and t2, t1 , t7         /* USB */
    and t5, t1 , t8         /* PMU */

check_pmu:
    li t0, 0x4                         /* PMU range should be 0x4~0xa */
    bgt t0, t5, default_pmu
    nop
    li t0, 0xa                         /* PMU range should be 0x4~0xa */
    blt t0, t5, default_pmu
    nop
    li  t0, 0x4
    sll t5, t5, t0

otp_end:
#endif

#if 1 /* Program PMU */
#define PMU_TEST_NO 1000
    li  t6, KSEG1ADDR(0x18116c40)
    li  t9, 0xbd000010
    li  t0, 0
    li  t1, 0
    li  t2, 0
    
    li  t3, PMU_TEST_NO
    sw  t3, 12(t9) 
pmu_loop0:
    beq zero, t3, pmu_loop0_end
    nop    
    addi t3, t3, -1
            
    li  t7, 0x10180000  /* ldo_tune 0x3 */
    nop
    sw  t7, 4(t6)
    nop   
    lw  t8, 4(t6)
    nop
    beq t8, t7, pmu_loop0_end
    nop
   
    addiu  t0, t0, 1
    b   pmu_loop0
    nop
pmu_loop0_end:      

    li  t3, PMU_TEST_NO    
pmu_loop1:
    beq zero, t3, pmu_loop1_end
    nop    
    addi t3, t3, -1

    //li  t7, 0x031c4326    /* 1.100V */
    //li  t7, 0x031c4336    /* 1.125V */
    //li  t7, 0x031c4346    /* 1.150V */
    //li  t7, 0x031c4356    /* 1.175V */     
    //li  t7, 0x031c4366    /* 1.200V */
    //li  t7, 0x031c4376    /* 1.225V */
    li  t7, 0x031c4386    /* 1.250V (DEFAULT) */
    //li  t7, 0x031c4396    /* 1.275V */
    //li  t7, 0x031c43a6    /* 1.300V */
    nop
#if 1 /* from OTP */
    li  t8, 0xffffff0f
    and t7, t7, t8
    or  t7, t7, t5
#endif
    sw  t7, 0(t6)
    nop   
    lw  t8, 0(t6)
    nop
    beq t8, t7, pmu_loop1_end
    nop  
    
    addiu  t1, t1, 1
    b   pmu_loop1    
    nop       
pmu_loop1_end:    

    li  t3, PMU_TEST_NO
pmu_loop2: 
    beq zero, t3, pmu_loop2_end
    nop    
    addi t3, t3, -1
    
    li  t7, 0x10380000  /* ldo_tune 0x3 */
    nop
    sw  t7, 4(t6)
    nop   
    lw  t8, 4(t6)
    nop
    beq t8, t7, pmu_loop2_end
    nop   
    
    addiu  t2, t2, 1
    b   pmu_loop2  
    nop       
pmu_loop2_end:    

    sw  t0, 0(t9) 
    nop  
    sw  t1, 4(t9) 
    nop  
    sw  t2, 8(t9) 
    nop
#endif

#if 1 /* Program ki, kd */
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
//	set_reg(0xb800009c, 0xfffff)
//	nop

/* set PLL bypass(Bit 2), CPU_POST_DIV, DDR_POST_DIV, AHB_POST_DIV in CPU clock control */
    set_reg(AR7240_CPU_CLOCK_CONTROL, CPU_CLK_CONTROL_VAL1)
	nop

/* set SETTLE_TIME in CPU PLL */
    set_reg(AR7240_USB_PLL_CONFIG, CPU_PLL_SETTLE_TIME_VAL)
    nop

pll_unlock_handler:

/* set nint, frac, refdiv, outdiv, range in CPU PLL configuration resiter */
    set_reg(AR7240_CPU_PLL_CONFIG, CPU_PLL_CONFIG_VAL1)
    nop

wait_loop2:
    li  t6, KSEG1ADDR(AR7240_CPU_PLL_CONFIG)
    lw  t7, 0(t6)
    li  t8, 0x80000000
    and t7, t7, t8
    bne zero, t7, wait_loop2
    nop
    
/* put frac bit19:10 configuration */
    set_reg(AR7240_PCIE_PLL_CONFIG, CPU_PLL_DITHER_FRAC_VAL)
    nop

/* clear PLL power down bit in CPU PLLl configuration */
    set_reg(AR7240_CPU_PLL_CONFIG, CPU_PLL_CONFIG_VAL2)
    nop
wait_loop3:
    li  t6, KSEG1ADDR(AR7240_CPU_PLL_CONFIG)
    lw  t7, 0(t6)
    li  t8, 0x80000000
    and t7, t7, t8
    bne zero, t7, wait_loop3
    nop

/* confirm DDR PLL lock */
    li  t3, 100
    li  t4, 0
start_meas0:
    addi t4, t4, 1
    bgt t4, t3, pll_unlock_handler
    nop
    li  t5, 5
start_meas:
    li  t6, KSEG1ADDR(0x18116248)
    lw  t7, 0(t6) 
    li  t8, 0xbfffffff  
    and t7, t7, t8
    sw  t7, 0(t6)
    nop

/* delay */
    li t9, 10
delayloop0:
    subu t9, t9, 1
    bne t9, zero, delayloop0
    nop

    li  t8, 0x40000000  
    or  t7, t7, t8
    sw  t7, 0(t6)
    nop    

meas_done_statue:
    li  t6, KSEG1ADDR(0x1811624c)
    lw  t7, 0(t6)
    li  t8, 0x8  
    and t7, t7, t8
    beq zero, t7, meas_done_statue
    nop
   
meas_result:
    li  t6, KSEG1ADDR(0x18116248)
    lw  t7, 0(t6)
    li  t8, 0x007ffff8
    and t7, t7, t8
    srl t7, t7, 3
    li  t8, 0x4000
    bgt t7, t8, start_meas0
    nop
    addi t5, t5, -1
    bne zero, t5, start_meas
    nop

/* clear PLL bypass(Bit 2), CPU_POST_DIV, DDR_POST_DIV, AHB_POST_DIV in CPU clock control */
    set_reg(AR7240_CPU_CLOCK_CONTROL, CPU_CLK_CONTROL_VAL2)
    nop

/* Sync mode , Set Bit 8 of DDR Tap Conrtol 3 register */
    set_reg(AR7240_DDR_TAP_CONTROL3, 0x10105);
    nop

    jr ra
    nop
