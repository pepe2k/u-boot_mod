#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <ar7240_soc.h>

/*
 * Helper macros.
 * These Clobber t7, t8 and t9
 */
#define clear_mask(_reg, _mask)                     \
    li  t7, KSEG1ADDR(_reg);                        \
    lw  t8, 0(t7);                                  \
    li  t9, ~_mask;                                 \
    and t8, t8, t9;                                 \
    sw  t8, 0(t7)            

#define set_val(_reg, _mask, _val)                  \
    li  t7, KSEG1ADDR(_reg);                        \
    lw  t8, 0(t7);                                  \
    li  t9, ~_mask;                                 \
    and t8, t8, t9;                                 \
    li  t9, _val;                                   \
    or  t8, t8, t9;                                 \
    sw  t8, 0(t7)            

#define set_val_f(_reg, _mask, _val)                \
    li  t7, KSEG1ADDR(_reg);                        \
    lw  t8, 0(t7);                                  \
    li  t9, ~_mask;                                 \
    and t8, t8, t9;                                 \
    li  t6, KSEG1ADDR(_val);                        \
    lw  t9, 0(t6);                                  \
    or  t8, t8, t9;                                 \
    sw  t8, 0(t7)            


#define get_val(_reg, _mask, _shift, _res_reg)      \
    li  t7, KSEG1ADDR(_reg);                        \
    lw  t8, 0(t7);                                  \
    li  t9, _mask;                                  \
    and t8, t8, t9;                                 \
    srl _res_reg, t8, _shift                        \

#define pll_clr(_mask)                              \
    clear_mask(AR7240_CPU_PLL_CONFIG, _mask)

#define pll_set(_mask, _val)                        \
    set_val(AR7240_CPU_PLL_CONFIG,  _mask, _val)

#define pll_set_f(_mask, _val)                      \
    set_val_f(AR7240_CPU_PLL_CONFIG,  _mask, _val)

#define pll_get(_mask, _shift, _res_reg)            \
    get_val(AR7240_CPU_PLL_CONFIG, _mask, _shift, _res_reg)

#define clk_clr(_mask)                              \
    clear_mask(AR7240_CPU_CLOCK_CONTROL, _mask)

#define clk_set(_mask, _val)                        \
    set_val(AR7240_CPU_CLOCK_CONTROL,  _mask, _val)

#define clk_get(_mask, _shift, _res_reg)            \
    get_val(AR7240_CPU_CLOCK_CONTROL, _mask, _shift, _res_reg)


/******************************************************************************
 * first level initialization:
 * 
 * 0) If clock cntrl reset switch is already set, we're recovering from 
 *    "divider reset"; goto 3.
 * 1) Setup divide ratios.
 * 2) Reset.
 * 3) Setup pll's, wait for lock.
 * 
 *****************************************************************************/

.globl lowlevel_init

lowlevel_init:
    /*
     * The code below is for the real chip. Wont work on FPGA
     */

    b hornet_pll_init
    jr ra
    nop

