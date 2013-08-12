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
#include <asm/addrspace.h>
#include <ar7240_soc.h>

#define ATH_SPI_CLOCK	0xbf000004

#define RVECENT(f,n) \
   b f; nop

#define XVECENT(f,bev) \
   b f     ;           \
   li k0,bev

	.set noreorder
#ifdef COMPRESSED_UBOOT
	.align 4
#endif
	.globl _start
	.text
_start:

#ifndef COMPRESSED_UBOOT
	RVECENT(reset,0)			/* U-boot entry point */
	RVECENT(reset,1)			/* software reboot */
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
#if !defined(CONFIG_WASP_SUPPORT)
	mtc0	zero, $17
#endif
	mtc0	zero, $18
	mtc0	zero, $19
#if !defined(CONFIG_WASP_SUPPORT)
	mtc0	zero, $20
	mtc0	zero, $21
	mtc0	zero, $22
#endif
	mtc0	zero, $23
	mtc0	zero, $24
	mtc0	zero, $25
	mtc0	zero, $26
	mtc0	zero, $27
	mtc0	zero, $28
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
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

#endif /* #ifndef COMPRESSED_UBOOT */

    /* Initialize GOT pointer.*/
	bal     1f
	nop
	.word   _GLOBAL_OFFSET_TABLE_
	1:
	move    gp, ra
	lw      t1, 0(ra)
	move	gp, t1

#ifndef COMPRESSED_UBOOT

#if defined(CONFIG_MACH_HORNET) && defined(CONFIG_HORNET_1_1_WAR)
/**************************************************************************/
/*
 * WAR: Hornet 1.1 currently need a reset once we boot to let the resetb has
 *      enough time to stable, so that trigger reset at 1st boot, system team
 *      is investigaing the issue, will remove in short
 */

do_reset_normal:

    li  t7, 0xbd000000
    lw  t8, 0(t7)            // t8 : value of 0xb8050024
    li  t9, 0x12345678
    sw  t9, 0(t7)
    bne t8, t9, do_reset      // if 0xb8050024 == 0x19 , go to do_cpld
    nop
    b normal_path

do_reset:
    li t7, 0xb806001c       // load reset register 0x1806001c
    lw t8, 0(t7)
    li t9, 0x1000000        // bit24, fullchip reset
    or t8, t8, t9         // t8:  set bit 18
    sw t8, 0(t7)

normal_path:
#endif /* CONFIG_MACH_HORNET */

/**************************************************************************/

	/* Initialize any external memory.
	 */
#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240) || defined(CONFIG_ATHEROS)
	la      t9, lowlevel_init
	jalr    t9
	nop
	nop

#if defined(CONFIG_MACH_HORNET)
	la      t9, hornet_ddr_init
	jalr    t9
	nop
	nop
#endif

	la	t0, rel_start
	j	t0
	nop
#endif

rel_start:

#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240) || defined(CONFIG_ATHEROS)
	/* REMAP_DISABLE */
	li	a0,	KSEG1ADDR(ATH_SPI_CLOCK)
#if defined(CONFIG_MACH_QCA955x)
	li	t0,	0x246
#elif defined(CONFIG_WASP_SUPPORT)
	li	t0,	0x243
#else
	li	t0,	0x43
#endif
	sw	t0,	0(a0)
#endif

	/* Initialize caches...
	 */
	la      t9, simple_mips_cache_reset
	jalr    t9
	nop

	/* ... and enable them.
	 */
#if defined(CONFIG_WASP_SUPPORT) && !defined(CONFIG_ATH_NAND_BR)
	li	t7,	KSEG1ADDR(AR7240_REV_ID)
	lw	t7,	0(t7)
	andi	t9,	t7,	0xf
	bne	zero,	t9,	1f
	nop

	li	t0,	CONF_CM_UNCACHED
	j	2f
	nop
#endif

1:	li	t0,	CONF_CM_CACHABLE_NONCOHERENT
2:	mtc0	t0,	CP0_CONFIG

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

#endif /* #ifndef COMPRESSED_UBOOT */

#ifdef CONFIG_WASP_SUPPORT
	li	t0, 0xbd007000	/* Setup stack in SRAM */
#else
	li	t0, CFG_SDRAM_BASE + CFG_INIT_SP_OFFSET
#endif
	la	sp, 0(t0)

	la	t9, board_init_f
	j	t9
	nop

/*
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 * a0 = addr_sp
 * a1 = gd
 * a2 = destination address
 */
	.globl	relocate_code
	.ent	relocate_code
relocate_code:
	move	sp, a0		/* Set new stack pointer		*/

	li	t0, CFG_MONITOR_BASE
	la	t3, in_ram
	lw	t2, -12(t3)	/* t2 <-- uboot_end_data	*/
	move	t1, a2

	/*
	 * Fix GOT pointer:
	 *
	 * New GOT-PTR = (old GOT-PTR - CFG_MONITOR_BASE) + Destination Address
	 */
	move	t6, gp
	sub	gp, CFG_MONITOR_BASE
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
	addi	t0, a2, in_ram - _start
	j	t0
	nop

	.word	uboot_end_data
	.word	uboot_end
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
	lw	t1, -12(t0)	/* t1 <-- uboot_end_data	*/
	lw	t2, -8(t0)	/* t2 <-- uboot_end		*/
	add	t1, t6		/* adjust pointers		*/
	add	t2, t6

	sub	t1, 4
1:	addi	t1, 4
	bltl	t1, t2, 1b
	sw	zero, 0(t1)	/* delay slot			*/

	move	a0, a1
	la	t9, board_init_r
	j	t9
	move	a1, a2		/* delay slot			*/

	.end	relocate_code

#if !defined(CONFIG_WASP_SUPPORT) && defined(CONFIG_AR7240)
/*
 * void ar7240_ddr_tap_init(void)
 *
 * This "function" is used to find the tap settings for the DDR
 */
	.globl	ar7240_ddr_tap_init
	.ent	ar7240_ddr_tap_init
ar7240_ddr_tap_init: /* { */
	li	t1,0x80500000
	li	t0,0xffffffff

	sw	t0,0x0(t1)
	sw	t0,0x4(t1)
	sw	t0,0x8(t1)
	sw	t0,0xc(t1)

	nop
	nop

ddr_pat_init:
	li 	t0, 0xa0002000

	li 	t1, 0x00000000
	sw 	t1, 0x0(t0)
	nop

	li 	t1, 0x00000000
	sw 	t1, 0x4(t0)
	nop

	li 	t1, 0x00000000
	sw	t1, 0x8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x14(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x18(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x24(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x28(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x34(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x38(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x44(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x48(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x54(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x58(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x64(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x68(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x74(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x78(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x84(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x88(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x94(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x98(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xbc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xdc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xfc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x100(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x104(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x108(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x10c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x110(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x114(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x118(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x11c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x120(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x124(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x128(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x12c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x130(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x134(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x138(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x13c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x140(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x144(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x148(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x14c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x150(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x154(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x158(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x15c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x160(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x164(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x168(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x16c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x170(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x174(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x178(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x17c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x180(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x184(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x188(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x18c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x190(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x194(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x198(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x19c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x1a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x1a4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1a8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x1b4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1b8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1c4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1c8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1d4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1d8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x1e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1e4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1e8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x1f4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x1f8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x1fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x200(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x204(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x208(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x20c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x210(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x214(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x218(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x21c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x220(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x224(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x228(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x22c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x230(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x234(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x238(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x23c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x240(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x244(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x248(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x24c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x250(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x254(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x258(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x25c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x260(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x264(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x268(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x26c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x270(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x274(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x278(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x27c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x280(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x284(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x288(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x28c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x290(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x294(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x298(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x29c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2a4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2a8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2b4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2b8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2c4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2c8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x2d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2d4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2d8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2e4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2e8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x2f4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x2f8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x2fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x300(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x304(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x308(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x30c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x310(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x314(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x318(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x31c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x320(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x324(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x328(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x32c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x330(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x334(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x338(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x33c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x340(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x344(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x348(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x34c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x350(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x354(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x358(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x35c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x360(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x364(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x368(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x36c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x370(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x374(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x378(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x37c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x380(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x384(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x388(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x38c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x390(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x394(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x398(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x39c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x3a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x3a4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3a8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x3b4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3b8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3c4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3c8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x3d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3d4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3d8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x3e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3e4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3e8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3f4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x3f8(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x3fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x400(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x404(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x408(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x40c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x410(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x414(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x418(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x41c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x420(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x424(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x428(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x42c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x430(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x434(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x438(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x43c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x440(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x444(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x448(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x44c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x450(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x454(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x458(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x45c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x460(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x464(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x468(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x46c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x470(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x474(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x478(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x47c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x480(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x484(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x488(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x48c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x490(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x494(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x498(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x49c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x4a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x4a4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4a8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x4b4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4b8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4c4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4c8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4d4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4d8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x4e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4e4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4e8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x4f4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x4f8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x4fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x500(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x504(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x508(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x50c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x510(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x514(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x518(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x51c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x520(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x524(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x528(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x52c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x530(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x534(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x538(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x53c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x540(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x544(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x548(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x54c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x550(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x554(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x558(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x55c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x560(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x564(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x568(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x56c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x570(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x574(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x578(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x57c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x580(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x584(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x588(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x58c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x590(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x594(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x598(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x59c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x5a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x5a4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5a8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x5b4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5b8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x5c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5c4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5c8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5d4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5d8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x5e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5e4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5e8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x5f4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5f8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x5fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x600(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x604(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x608(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x60c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x610(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x614(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x618(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x61c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x620(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x624(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x628(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x62c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x630(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x634(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x638(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x63c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x640(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x644(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x648(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x64c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x650(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x654(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x658(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x65c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x660(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x664(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x668(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x66c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x670(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x674(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x678(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x67c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x680(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x684(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x688(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x68c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x690(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x694(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x698(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x69c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6a4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6a8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6b4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6b8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x6c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6c4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6c8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6d4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6d8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6e4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6e8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x6f4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x6f8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x6fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x700(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x704(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x708(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x70c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x710(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x714(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x718(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x71c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x720(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x724(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x728(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x72c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x730(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x734(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x738(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x73c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x740(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x744(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x748(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x74c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x750(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x754(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x758(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x75c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x760(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x764(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x768(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x76c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x770(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x774(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x778(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x77c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x780(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x784(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x788(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x78c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x790(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x794(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x798(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x79c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x7a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x7a4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7a8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x7b4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7b8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x7c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7c4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7c8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7d4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7d8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x7e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7e4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7e8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7f4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x7f8(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x7fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x800(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x804(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x808(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x80c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x810(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x814(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x818(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x81c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x820(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x824(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x828(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x82c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x830(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x834(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x838(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x83c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x840(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x844(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x848(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x84c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x850(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x854(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x858(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x85c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x860(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x864(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x868(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x86c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x870(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x874(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x878(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x87c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x880(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x884(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x888(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x88c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x890(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x894(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x898(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x89c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8a4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8a8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8b4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8b8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8c4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8c8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x8d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8d4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8d8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8e4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8e8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x8f4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x8f8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x8fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x900(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x904(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x908(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x90c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x910(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x914(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x918(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x91c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x920(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x924(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x928(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x92c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x930(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x934(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x938(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x93c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x940(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x944(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x948(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x94c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x950(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x954(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x958(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x95c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x960(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x964(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x968(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x96c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x970(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x974(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x978(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x97c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x980(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x984(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x988(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x98c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x990(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x994(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x998(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x99c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9a0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9a4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9a8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9ac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9b0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9b4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9b8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9bc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0x9c0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9c4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9c8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9cc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9d0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9d4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9d8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9dc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9e0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9e4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9e8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9ec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9f0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0x9f4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0x9f8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0x9fc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa04(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa08(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa14(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa18(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa24(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa28(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xa30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa34(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa38(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa44(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa48(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa54(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa58(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa64(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa68(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xa70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa74(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa78(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xa80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa84(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa88(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xa90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa94(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa98(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xa9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaa0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaa4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaa8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xab0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xab4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xab8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xabc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xac0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xac4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xac8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xacc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xad0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xad4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xad8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xadc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xae0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xae4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xae8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xaf0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xaf4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xaf8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xafc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb04(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb08(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb14(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb18(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb24(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb28(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb34(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb38(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb44(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb48(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb54(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb58(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb64(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb68(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb74(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb78(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xb80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb84(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb88(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xb90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb94(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xb98(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xb9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xba0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xba4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xba8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbb4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbb8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbbc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xbc0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbc4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbc8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbcc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xbd0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbd4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbd8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbdc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbe0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbe4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbe8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbf0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbf4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xbf8(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xbfc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc04(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc08(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc14(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc18(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xc20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc24(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc28(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc34(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc38(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc44(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc48(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc54(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc58(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xc60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc64(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc68(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc74(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc78(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xc84(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc88(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xc90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xc94(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xc98(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xc9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xca0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xca4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xca8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xcb4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcb8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcbc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcc0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcc4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcc8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xccc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xcd0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcd4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcd8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcdc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xce0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xce4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xce8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcf0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcf4(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xcf8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xcfc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd04(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd08(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd14(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd18(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xd20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd24(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd28(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd34(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd38(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd44(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd48(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd54(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd58(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xd60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd64(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd68(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd74(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd78(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xd80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xd84(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd88(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xd94(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xd98(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xd9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xda0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xda4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xda8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xdb4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xdb8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdbc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xdc0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdc4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xdc8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdcc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xdd0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdd4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xdd8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xddc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xde0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xde4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xde8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdf0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdf4(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xdf8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xdfc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe04(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe08(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe14(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe18(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe24(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe28(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe34(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe38(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe44(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe48(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe54(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe58(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe64(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe68(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe74(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe78(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xe80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe84(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe88(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xe90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe94(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xe98(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xe9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xea0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xea4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xea8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xeac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xeb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xeb4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xeb8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xebc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xec0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xec4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xec8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xecc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xed0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xed4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xed8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xedc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xee0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xee4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xee8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xeec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xef0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xef4(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xef8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xefc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf00(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf04(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf08(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf0c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf10(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf14(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf18(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf1c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xf20(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf24(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf28(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf2c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf30(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf34(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf38(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf3c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf40(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf44(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf48(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf4c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf50(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf54(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf58(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf5c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xf60(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf64(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf68(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf6c(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf70(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf74(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf78(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf7c(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xf80(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xf84(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf88(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf8c(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xf90(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xf94(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf98(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xf9c(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xfa0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xfa4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfa8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfac(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfb0(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xfb4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfb8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfbc(t0)
	nop

	li	t1, 0x00000000
	sw	t1, 0xfc0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfc4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfc8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfcc(t0)
	nop

	li	t1, 0x0000ffff
	sw	t1, 0xfd0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfd4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfd8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfdc(t0)
	nop

	li	t1, 0xffff0000
	sw	t1, 0xfe0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfe4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfe8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xfec(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xff0(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xff4(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xff8(t0)
	nop

	li	t1, 0xffffffff
	sw	t1, 0xffc(t0)
	nop


//###### ddr init over #########

	li	a0, 0xa0002000
	li	a1, 0x80002000	     //### Start address of the pattern   200
	li	a2, 0x80003000	     //### End Address of the pattern     220
	li	t0, 0xb800001c	//## Tap settings addr
	lw	a3, 0x0(t0)		//## loading default tap value
	nop
	ori	t0, a3, 0x0
	nop
	li	t1, 0x1		//# t1=1 indicates increasing tap value, 0 = decreasing

load_tap:

# TODO: 0x2 in hornet_ddr_init.S (speed up inicialization)
	#li	t7, 0x200	//## No. of times read has to happen for 1 tap setting
	li	t7, 0x2	//## No. of times read has to happen for 1 tap setting
	li	t8, 0xb8000000	//#### Loading Tap Setting
	sw	t0, 0x1c(t8)
	nop
	sw	t0, 0x20(t8)
	nop

pat_read:
	ori	t2, a0, 0x0
	nop
	ori	t3, a1, 0x0
	nop
	ori	t4, a2, 0x0
	nop

tap_addr_loop:
	lw	t5, 0x0(t2)
	nop
	lw	t6, 0x0(t3)
	nop
	nop

	bne	t5, t6, tap_fail
	nop
	nop
	nop

	addiu	t2, t2, 0x4  //#incrementing addr
	addiu	t3, t3, 0x4
	nop
	nop

	bne	t3, t4, tap_addr_loop
	nop

	addiu	t7, t7, -1
	nop
	bnez	t7, pat_read
	nop
	nop

	bnez	t1, tap_incr
	nop
	nop

	bnez	t0, tap_decr	//# t0=0 implies tap=0 works
	nop		 //# so low limit=0, else decrement tap value
	nop
	li	t8, 0x80500000
	sw	t0, 0x0(t8)
	add	t9, t9, t0 //#adding lower limit to upper limit (used to calc mid value)
	nop
	nop

	b tap_calc
	nop
	nop

tap_decr:
	addiu	t0, t0 , -1
	nop
	b load_tap
	nop
	nop

tap_incr:
	addiu	t0, t0 , 0x1
	nop
	xori	v1, t0, 0x20
	nop
	bnez	v1, load_tap
	nop
	nop
	b up_limit
	nop
	nop

tap_fail:
	bnez	t1, up_limit
	nop
	nop
	nop
	addiu	t0, t0, 0x1
	nop
	li	t8, 0x80500000
	nop
	sw	t0, 0x0(t8)
	add	t9, t9, t0
	nop
	nop
	nop

	b tap_calc
	nop
	nop

up_limit:
	addiu	t0, t0, -1
	li	t1, 0x0	 //## changing to decreasing tap mode
	li	t8, 0x80500000 //## storing upper limit
	sw	t0, 0x4(t8)
	ori	t9, t0, 0x0
	nop
	nop
	nop

	ori	t0, a3, 0x0 	//# loading default tap value
	nop
	b load_tap
	nop
	nop

tap_calc:  //## calculating mid value of the tap, storing DQS0, DQS1 in 0x80500008, 0x8050000c resp.
	li	t7, 0x2
	nop
	div	t9, t7
	nop
	mfhi	t6
	mflo	t5
	nop
	nop
	add	t6, t6, t5
	li	t8, 0x80500000
	nop
	sw	t5, 0x8(t8)
	nop
	sw	t6, 0xc(t8)
	nop
	nop
        li      t8, 0xb8000000  //#### Loading Tap Setting
	nop
        sw      t5, 0x1c(t8)
        nop
        sw      t6, 0x20(t8)
        nop
	nop
	nop

end:
	nop
	nop
	nop
	jr 	ra

	.end	ar7240_ddr_tap_init

/* } */
#else

/*
.globl	ath_ddr_tap_cal
.type   ath_ddr_tap_cal, @function

ath_ddr_tap_cal:

	li	a0,	0xbd007f00
	sw	zero,	0x0(a0)			// Place where the tap values are saved and used for SWEEP
	sw	zero,	0x4(a0)			// Place where the number of passing taps are saved.
	sw	zero,	0x14(a0)		// Place where the last pass tap value is stored
	li	a1,	0xaa55aa55		// Indicates that the First pass tap value is not found
	sw	a1,	0x10(a0)		// Place where the First pass tap value is stored
	nop

	li	a0,	0xb8060000		// RESET_BASE_ADDRESS
	lw	a1,	0x1c(a0)		// Reading the RST_RESET_ADDRESS
	li	a2,	0x08000000		// Setting the RST_RESET_RTC_RESET
	or	a1,	a1,	a2
	sw	a1,	0x1c(a0)

	li	a3,	0xffffffff
	xor	a2,	a2,	a3
	and	a1,	a1,	a2
	sw	a1,	0x1c(a0)		// Taking the RTC out of RESET
	nop

	li	a0,	0xb8107000		// RTC_BASE_ADDRESS
	li	a1,	0x1
	sw	a1,	0x0040(a0)		// RTC_SYNC_RESET_ADDRESS

	li	a2,	0x2

_poll_for_RTC_ON:
	lw	a1,	0x0044(a0)		// RTC_SYNC_STATUS_ADDRESS
	and	a1,	a2,	a1
	bne	a1,	a2,	_poll_for_RTC_ON


_CHANGE_TAPS:

	li	t0,	0xbd007f00		// Read the current value of the TAP for programming
	lw	t1,	0x0(t0)
	li	t2,	0x00000000
	or	t3,	t1,	t2


	li	t0,	0xb8000000		// DDR_BASE_ADDRESS

	sw	t3,	0x1c(t0)		// TAP_CONTROL_0_ADDRESS
	sw	t3,	0x20(t0)		// TAP_CONTROL_1_ADDRESS
	sw	t3,	0x24(t0)		// TAP_CONTROL_2_ADDRESS
	sw	t3,	0x28(t0)		// TAP_CONTROL_3_ADDRESS

	li	t1,	0x00000010		// Running the test 8 times
	sw	t1,	0x0068(t0)		// PERF_COMP_ADDR_1_ADDRESS

	li	t1,	0xfa5de83f		// 4 Row Address Bits, 4 Column Address Bits, 2 BA bits
	sw	t1,	0x002c(t0)		// PERF_MASK_ADDR_0_ADDRESS

	li	t1,	0x545fc332
	sw	t1,	0x0070(t0)		// PERF_COMP_AHB_GE0_1_ADDRESS

	li	t1,	0xaba03ccd
	sw	t1,	0x0040(t0)		// PERF_COMP_AHB_GE1_0_ADDRESS

	li	t1,	0x545fc332
	sw	t1,	0x0078(t0)		// PERF_COMP_AHB_GE1_1_ADDRESS

	li	t1,	0xaba03ccd
	sw	t1,	0x0034(t0)		// PERF_MASK_AHB_GE0_0_ADDRESS

	li	t1,	0x545fc332
	sw	t1,	0x006c(t0)		// PERF_MASK_AHB_GE0_1_ADDRESS

	li	t1,	0xaba03ccd
	sw	t1,	0x003c(t0)		// PERF_MASK_AHB_GE1_0_ADDRESS

	li	t1,	0x545fc332
	sw	t1,	0x0074(t0)		// PERF_MASK_AHB_GE1_1_ADDRESS

	li	t1,	0xaba03ccd
	sw	t1,	0x0038(t0)		// PERF_COMP_AHB_GE0_0_ADDRESS

	li	t1,	0x00000001
	sw	t1,	0x011c(t0)		// DDR_BIST_ADDRESS

	li	t2,	0x1
_bist_done_poll:
	lw	t1,	0x0120(t0)		// DDR_BIST_STATUS_ADDRESS
	and	t1,	t1,	t2
	bne	t1,	t2,	_bist_done_poll

	lw	t1,	0x0120(t0)		// DDR_BIST_STATUS_ADDRESS
	li	t4,	0x000001fe
	and	t2,	t1,	t4
	srl	t2,	t2,	0x1		// no. of Pass Runs

	li	t5,	0x00000000
	sw	t5,	0x011c(t0)		//DDR_BIST_ADDRESS	- Stop the DDR BIST test

	li	t5,	0x0001fe00
	and	t5,	t5,	t1
	bnez	t5,	_iterate_tap		// This is a redundant compare but nevertheless - Comparing the FAILS

	lw	t1,	0x0068(t0)		// PERF_COMP_ADDR_1_ADDRESS
	li	t3,	0x000001fe
	and	t3,	t3,	t1
	srl	t3,	t3,	0x1		// No. of runs in the config register.

	bne	t3,	t2,	_iterate_tap

pass_tap:
	li	t0,	0xbd007f00
	lw	t1,	0x4(t0)
	addiu	t1,	t1,	0x1
	sw	t1,	0x4(t0)

	li	t0,	0xbd007f10
	lw	t1,	0x0(t0)
	li	t2,	0xaa55aa55
	beq	t1,	t2,	_first_pass
	nop
	li	t0,	0xbd007f00
	lw	t1,	0x0(t0)
	li	t0,	0xbd007f10
	sw	t1,	0x4(t0)
	nop
	b	_iterate_tap
	nop

_first_pass:
	li	t0,	0xbd007f00
	lw	t1,	0x0(t0)
	li	t0,	0xbd007f10
	sw	t1,	0x0(t0)
	sw	t1,	0x4(t0)
	nop

_iterate_tap:

	li	t0,	0xbd007f00
	lw	t1,	0x0(t0)
	li	t2,	0x1f
	beq	t1,	t2,	_STOP_TEST
	nop
	addiu	t1,	t1,	0x1
	sw	t1,	0x0(t0)
	nop
	b	_CHANGE_TAPS

_STOP_TEST:
	li	t0,	0xbd007f00
	lw	t1,	0x4(t0)
	bnez	t1,	_load_center_tap
	nop
	li	t3,	0x8			// Default Tap to be used
	b	_load_tap_into_reg

_load_center_tap:
	li	t0,	0xbd007f10
	lw	t1,	0x0(t0)
	lw	t2,	0x4(t0)
	add	t3,	t1,	t2
	srl	t3,	t3,	0x1
	li	t4,	0x1f
	and	t3,	t3,	t4

_load_tap_into_reg:
	li	t0,	0xb8000000
	sw	t3,	0x1c(t0)		// TAP_CONTROL_0_ADDRESS
	sw	t3,	0x20(t0)		// TAP_CONTROL_1_ADDRESS
	sw	t3,	0x24(t0)		// TAP_CONTROL_2_ADDRESS
	sw	t3,	0x28(t0)		// TAP_CONTROL_3_ADDRESS

	jr	ra
	nop
*/

#endif

#ifndef COMPRESSED_UBOOT
	/* Exception handlers */
romReserved:
	b romReserved

romExcHandle:
	b romExcHandle
#endif /* #ifndef COMPRESSED_UBOOT */
