/*
 *  Startup Code for MIPS32 CPU-core
 *
 *  Copyright (c) 2003	Wolfgang Denk <wd@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>

#define AR7100_SPI_CLOCK  0xbf000004

#ifdef CONFIG_WASP_SUPPORT
	#define ATH_APB_BASE				0xB8000000  /* KSEG1ADDR(0x18000000) */
	#define ATH_GPIO_BASE				ATH_APB_BASE+0x00040000
	#define ATH_GPIO_OE					ATH_GPIO_BASE+0x0
	#define ATH_GPIO_OUT				ATH_GPIO_BASE+0x8
	#define ATH_GPIO_OUT_FUNCTION0		ATH_GPIO_BASE+0x2c
	#define ATH_GPIO_OUT_FUNCTION1		ATH_GPIO_BASE+0x30
	#define ATH_GPIO_OUT_FUNCTION2		ATH_GPIO_BASE+0x34
	#define ATH_GPIO_OUT_FUNCTION3		ATH_GPIO_BASE+0x38
	#define ATH_GPIO_OUT_FUNCTION4		ATH_GPIO_BASE+0x3c
	#define ATH_GPIO_OUT_FUNCTION5		ATH_GPIO_BASE+0x40
#endif


#define RVECENT(f,n) \
   b f; nop

#define XVECENT(f,bev) \
   b f     ;           \
   li k0,bev

	.set noreorder

	.globl _start_bootstrap
	.text
_start_bootstrap:
	RVECENT(reset,0)	/* U-boot entry point */
	RVECENT(reset,1)	/* software reboot */
	RVECENT(romReserved,2)
	RVECENT(romReserved,3)
	RVECENT(romReserved,4)
	RVECENT(romReserved,5)
	RVECENT(romReserved,6)
	RVECENT(romReserved,7)
	RVECENT(romReserved,8)
	RVECENT(romReserved,9)
	RVECENT(romReserved,10)
	RVECENT(romReserved,11)
	RVECENT(romReserved,12)
	RVECENT(romReserved,13)
	RVECENT(romReserved,14)
	RVECENT(romReserved,15)
	RVECENT(romReserved,16)
	RVECENT(romReserved,17)
	RVECENT(romReserved,18)
	RVECENT(romReserved,19)
	RVECENT(romReserved,20)
	RVECENT(romReserved,21)
	RVECENT(romReserved,22)
	RVECENT(romReserved,23)
	RVECENT(romReserved,24)
	RVECENT(romReserved,25)
	RVECENT(romReserved,26)
	RVECENT(romReserved,27)
	RVECENT(romReserved,28)
	RVECENT(romReserved,29)
	RVECENT(romReserved,30)
	RVECENT(romReserved,31)
	RVECENT(romReserved,32)
	RVECENT(romReserved,33)
	RVECENT(romReserved,34)
	RVECENT(romReserved,35)
	RVECENT(romReserved,36)
	RVECENT(romReserved,37)
	RVECENT(romReserved,38)
	RVECENT(romReserved,39)
	RVECENT(romReserved,40)
	RVECENT(romReserved,41)
	RVECENT(romReserved,42)
	RVECENT(romReserved,43)
	RVECENT(romReserved,44)
	RVECENT(romReserved,45)
	RVECENT(romReserved,46)
	RVECENT(romReserved,47)
	RVECENT(romReserved,48)
	RVECENT(romReserved,49)
	RVECENT(romReserved,50)
	RVECENT(romReserved,51)
	RVECENT(romReserved,52)
	RVECENT(romReserved,53)
	RVECENT(romReserved,54)
	RVECENT(romReserved,55)
	RVECENT(romReserved,56)
	RVECENT(romReserved,57)
	RVECENT(romReserved,58)
	RVECENT(romReserved,59)
	RVECENT(romReserved,60)
	RVECENT(romReserved,61)
	RVECENT(romReserved,62)
	RVECENT(romReserved,63)
	XVECENT(romExcHandle,0x200)	/* bfc00200: R4000 tlbmiss vector */
	RVECENT(romReserved,65)
	RVECENT(romReserved,66)
	RVECENT(romReserved,67)
	RVECENT(romReserved,68)
	RVECENT(romReserved,69)
	RVECENT(romReserved,70)
	RVECENT(romReserved,71)
	RVECENT(romReserved,72)
	RVECENT(romReserved,73)
	RVECENT(romReserved,74)
	RVECENT(romReserved,75)
	RVECENT(romReserved,76)
	RVECENT(romReserved,77)
	RVECENT(romReserved,78)
	RVECENT(romReserved,79)
	XVECENT(romExcHandle,0x280)	/* bfc00280: R4000 xtlbmiss vector */
	RVECENT(romReserved,81)
	RVECENT(romReserved,82)
	RVECENT(romReserved,83)
	RVECENT(romReserved,84)
	RVECENT(romReserved,85)
	RVECENT(romReserved,86)
	RVECENT(romReserved,87)
	RVECENT(romReserved,88)
	RVECENT(romReserved,89)
	RVECENT(romReserved,90)
	RVECENT(romReserved,91)
	RVECENT(romReserved,92)
	RVECENT(romReserved,93)
	RVECENT(romReserved,94)
	RVECENT(romReserved,95)
	XVECENT(romExcHandle,0x300)	/* bfc00300: R4000 cache vector */
	RVECENT(romReserved,97)
	RVECENT(romReserved,98)
	RVECENT(romReserved,99)
	RVECENT(romReserved,100)
	RVECENT(romReserved,101)
	RVECENT(romReserved,102)
	RVECENT(romReserved,103)
	RVECENT(romReserved,104)
	RVECENT(romReserved,105)
	RVECENT(romReserved,106)
	RVECENT(romReserved,107)
	RVECENT(romReserved,108)
	RVECENT(romReserved,109)
	RVECENT(romReserved,110)
	RVECENT(romReserved,111)
	XVECENT(romExcHandle,0x380)	/* bfc00380: R4000 general vector */
	RVECENT(romReserved,113)
	RVECENT(romReserved,114)
	RVECENT(romReserved,115)
	RVECENT(romReserved,116)
	RVECENT(romReserved,116)
	RVECENT(romReserved,118)
	RVECENT(romReserved,119)
	RVECENT(romReserved,120)
	RVECENT(romReserved,121)
	RVECENT(romReserved,122)
	RVECENT(romReserved,123)
	RVECENT(romReserved,124)
	RVECENT(romReserved,125)
	RVECENT(romReserved,126)
	RVECENT(romReserved,127)

	/* We hope there are no more reserved vectors!
	 * 128 * 8 == 1024 == 0x400
	 * so this is address R_VEC+0x400 == 0xbfc00400
	 */
	.align 4
reset:

#ifdef CONFIG_WASP_SUPPORT
	/* GPIO Init */
	li a1, ATH_GPIO_OE
	lw v1, 0(a1)
	/* GPIO 11-15 as output */
	li  v0, ~((1 << 15) | (1 << 14) | (1 << 13) | (1 << 12) | (1 << 11))
	and v1, v1, v0
	/* save GPIO Config Value */
	sw  v1, 0(a1)
	lw  v0, 0(a1)

	/* set gpio funtion for gpio11 */
	li	a1, ATH_GPIO_OUT_FUNCTION2
	lw	v1, 0(a1)
	li	v0, 0x00ffffff
	and v1, v1, v0
	/* set v1 value to ATH_GPIO_OUT_FUNCTION2 */
	sw	v1, 0(a1)

	/* set gpio funtion for gpio12~15 */
	li	a1, ATH_GPIO_OUT_FUNCTION3
	lw	v1, 0(a1)
	li	v0, 0x0
	and v1, v1, v0
	/* set v1 value to ATH_GPIO_OUT_FUNCTION3 */
	sw	v1, 0(a1)

	/* turn on gpio11-15 */
	li	a1, ATH_GPIO_OUT
	lw	v1, 0(a1)
	li	v0, ~((1 << 15) | (1 << 14) | (1 << 13) | (1 << 12) | (1 << 11))
	and	v1, v1, v0
	/* set v1 value to ATH_GPIO_OUT */
	sw	v1, 0(a1)

	/* wait for a while, for leds' bootup blink*/
	li a1, 0
	li v1, 0x70000

1:
	addi a1, a1, 1
	bne a1, v1, 1b
	nop

	/* turn off gpio11-15 */
	li	a1, ATH_GPIO_OUT
	lw	v1, 0(a1)
	li	v0, ((1 << 15) | (1 << 14) | (1 << 13) | (1 << 12) | (1 << 11))
	or	v1, v1, v0
	/* set v1 value to ATH_GPIO_OUT */
	sw	v1, 0(a1)
#endif

	/*
	 * Clearing CP0 registers - This is generally required for the MIPS-24k
     * core used by Atheros.
	 */
	mtc0	zero, $0
	mtc0	zero, $1
	mtc0	zero, $2
	mtc0	zero, $3
	mtc0	zero, $4
	mtc0	zero, $5
	mtc0	zero, $6
	mtc0	zero, $7
	mtc0	zero, $8
	mtc0	zero, $9
	mtc0	zero, $10
	mtc0	zero, $11
	li	t0, 0x10000004
	mtc0	t0, $12
	mtc0	zero, $13
	mtc0	zero, $14
	mtc0	zero, $15
	mtc0	zero, $16
	mtc0	zero, $17
	mtc0	zero, $18
	mtc0	zero, $19
	mtc0	zero, $20
	mtc0	zero, $21
	mtc0	zero, $22
	mtc0	zero, $23
	mtc0	zero, $24
	mtc0	zero, $25
	mtc0	zero, $26
	mtc0	zero, $27
	mtc0	zero, $28

#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29		# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif

	/*
	 * Clear watch registers.
	 */

	mtc0	zero, CP0_WATCHLO
	mtc0	zero, CP0_WATCHHI

	/* STATUS register */
	mfc0	k0, CP0_STATUS
	li	k1, ~ST0_IE
	and	k0, k1
        mtc0	zero, CP0_CAUSE
	mtc0	k0, CP0_STATUS

	/* CAUSE register */
	mtc0	zero, CP0_CAUSE

	/* Init Timer */
	mtc0	zero, CP0_COUNT
	mtc0	zero, CP0_COMPARE

	/* CONFIG0 register */
	li	t0, CONF_CM_UNCACHED
	mtc0	t0, CP0_CONFIG


    /* Initialize GOT pointer.*/
	bal     1f
	nop
	.word   _GLOBAL_OFFSET_TABLE_
	1:
	move    gp, ra
	lw      t1, 0(ra)
	move	gp, t1

#if defined(CONFIG_MACH_HORNET) && defined(CONFIG_HORNET_1_1_WAR)
/**************************************************************************/
/*
 * WAR: Hornet 1.1 currently need a reset once we boot to let the resetb has
 *      enough time to stable, so that trigger reset at 1st boot, system team
 *      is investigaing the issue, will remove in short
 */

do_reset_normal:

    li  t7, 0xbd000000
    lw  t8, 0(t7)            // t8 : value of 0xbd000000
    li  t9, 0x12345678
    bne t8, t9, do_reset     // if value of 0xbd000000 != 0x12345678 , go to do_reset
    nop
    li  t9, 0xffffffff
    sw  t9, 0(t7) 
    b   normal_path
    nop

do_reset:
    sw  t9, 0(t7)
    li  t7, 0xb806001c       // load reset register 0x1806001c
    lw  t8, 0(t7)
    li  t9, 0x1000000        // bit24, fullchip reset
    or  t8, t8, t9
    sw  t8, 0(t7)
do_reset_loop:    
    b   do_reset_loop
    nop

normal_path:
#endif /* CONFIG_MACH_HORNET */

/**************************************************************************/

	/* Initialize any external memory.
	 */
#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240)
	la      t9, lowlevel_init
	jalr    t9
	nop
	nop

#if defined(CONFIG_MACH_HORNET)
	la      t9, hornet_ddr_init
	jalr    t9
	nop
	nop

#if 0
	la      t9, hornet_ddr_tap_init
	jalr    t9
	nop
#endif

#endif

	la	t0, rel_start
	j	t0
	nop
#endif

rel_start:

#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240)
	/* REMAP_DISABLE */
	// TODO: SPI flash clock?
	li	a0, AR7100_SPI_CLOCK
	li	t0, 0x42		// was 0x43
	sw	t0, 0(a0)
#endif

#if defined(CONFIG_AR9100) && defined(CFG_HOWL_1_2)
    /* Disable remap for parallel flash */
    li  t7, AR9100_FLASH_CONFIG;
    lw  t8, 0(t7);
    li  t9, 0xffbf0000;
    and t8, t8, t9;
    li  t9, 0x22fc;
    or  t8, t8, t9;
    li  t9, 0xffcfffff; /* scale = 0 */
    and t8, t8, t9;
    sw  t8, 0(t7);

#endif

	/* Initialize caches...
	 */
	la      t9, simple_mips_cache_reset
	jalr    t9
	nop

	/* ... and enable them.
	 */
	li	t0, CONF_CM_CACHABLE_NONCOHERENT
	mtc0	t0, CP0_CONFIG

#if !defined(CONFIG_AR7100) && !defined(CONFIG_AR7240)
	/* Set up temporary stack.
	 */
	li	a0, CFG_INIT_SP_OFFSET
	la      t9, mips_cache_lock
	jalr    t9
	nop
#endif

#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240)
    la      t9, mips_cache_lock_24k
    jalr    t9
    nop
#endif

	li	t0, CFG_SDRAM_BASE + CFG_INIT_SP_OFFSET
	la	sp, 0(t0)

	la	t9, bootstrap_board_init_f
	j	t9
	nop


/*
 * void bootstrap_relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 * a0 = addr_sp
 * a1 = gd
 * a2 = destination address
 */
	.globl	bootstrap_relocate_code
	.ent	bootstrap_relocate_code
bootstrap_relocate_code:
	move	sp, a0		/* Set new stack pointer		*/

	li	t0, BOOTSTRAP_CFG_MONITOR_BASE
	la	t3, in_ram
	lw	t2, -12(t3)	/* t2 <-- uboot_end_data_bootsrap	*/

	/*
	 * Ideally, following line is not needed. However,
	 * the behaviour is flaky without it. U-boot boots on
	 * some boards, and doesn't on some boards. Even on the
	 * boards it boots, it doesn't boot all the time.
	 *
	 * Adding 256k to what needs to be read in actually.
	 * This introduces some delay that seems to help boot.
	 */
	li	t3, (256 << 10)

	add	t2, t3
	move	t1, a2

	/*
	 * Fix GOT pointer:
	 *
	 * New GOT-PTR = (old GOT-PTR - BOOTSTRAP_CFG_MONITOR_BASE) + Destination Address
	 */
	move	t6, gp
	sub	gp, BOOTSTRAP_CFG_MONITOR_BASE
	add	gp, a2			/* gp now adjusted		*/
	sub	t6, gp, t6		/* t6 <-- relocation offset	*/

	/*
	 * t0 = source address
	 * t1 = target address
	 * t2 = source end address
	 */
1:
	lw	t3, 0(t0)
	sw	t3, 0(t1)
	addu	t0, 4
	ble	t0, t2, 1b
	addu	t1, 4			/* delay slot			*/

	/* If caches were enabled, we would have to flush them here.
	 */

	/* Jump to where we've relocated ourselves.
	 */
	addi	t0, a2, in_ram - _start_bootstrap
	j	t0
	nop

	.word	uboot_end_data_bootstrap
	.word	uboot_end_bootstrap
	.word	num_got_entries

in_ram:
	/* Now we want to update GOT.
	 */
	lw	t3, -4(t0)	/* t3 <-- num_got_entries	*/
	addi	t4, gp, 8	/* Skipping first two entries.	*/
	li	t2, 2
1:
	lw	t1, 0(t4)
	beqz	t1, 2f
	add	t1, t6
	sw	t1, 0(t4)
2:
	addi	t2, 1
	blt	t2, t3, 1b
	addi	t4, 4		/* delay slot			*/

	/* Clear BSS.
	 */
	lw	t1, -12(t0)	/* t1 <-- uboot_end_data_bootstrap	*/
	lw	t2, -8(t0)	/* t2 <-- uboot_end_bootstrap		*/
	add	t1, t6		/* adjust pointers		*/
	add	t2, t6

	sub	t1, 4
1:	addi	t1, 4
	bltl	t1, t2, 1b
	sw	zero, 0(t1)	/* delay slot			*/

	move	a0, a1
	la	t9, bootstrap_board_init_r
	j	t9
	move	a1, a2		/* delay slot			*/

	.end	bootstrap_relocate_code

	/* Exception handlers.
	 */
romReserved:
	b romReserved

romExcHandle:
	b romExcHandle
