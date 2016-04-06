/*
 * Startup Code for MIPS32 CPU-core
 *
 * Copyright (C) 2015 Piotr Dymacz <piotr@dymacz.pl>
 * Copyright (C) 2013 Qualcomm Atheros, Inc.
 * Copyright (C) 2003 Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:GPL-2.0
 */

#include <config.h>
#include <version.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <soc/qca_soc_common.h>

#define RVECENT(f,n)	\
	b f; nop

#define XVECENT(f,bev)	\
	b f;				\
	li k0, bev

	.set noreorder
#ifdef COMPRESSED_UBOOT
	.align 4
#endif
	.globl _start
	.text

_start:
#ifndef COMPRESSED_UBOOT
	RVECENT(reset,0)			/* U-boot entry point */
	RVECENT(reset,1)			/* Software reboot */
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

	/*
	 * We hope there are no more reserved vectors!
	 * 128 * 8 == 1024 == 0x400
	 * so this is address R_VEC+0x400 == 0xbfc00400
	 */

	.align 4
reset:
	/*
	 * Clearing CP0 registers - This is generally required for the MIPS-24k
	 * core used by Atheros.
	 */
	mtc0 zero, $0
	mtc0 zero, $1
	mtc0 zero, $2
	mtc0 zero, $3
	mtc0 zero, $4
	mtc0 zero, $5
	mtc0 zero, $6
	mtc0 zero, $7
	mtc0 zero, $8
	mtc0 zero, $9
	mtc0 zero, $10
	mtc0 zero, $11
	li   t0,   0x10000004
	mtc0 t0,   $12
	mtc0 zero, $13
	mtc0 zero, $14
	mtc0 zero, $15
	mtc0 zero, $16
	mtc0 zero, $17
	mtc0 zero, $18
	mtc0 zero, $19
	mtc0 zero, $20
	mtc0 zero, $21
	mtc0 zero, $22
	mtc0 zero, $23
	mtc0 zero, $24
	mtc0 zero, $25
	mtc0 zero, $26
	mtc0 zero, $27
	mtc0 zero, $28

#if (SOC_TYPE & QCA_AR934X_SOC)  | \
	(SOC_TYPE & QCA_QCA953X_SOC) | \
	(SOC_TYPE & QCA_QCA955X_SOC) | \
	(SOC_TYPE & QCA_QCA956X_SOC)
	mtc0 zero, $29		# C0_TagHi
	mtc0 zero, $28, 2	# C0_DTagLo
	mtc0 zero, $29, 2	# C0_DTagHi
#endif

	/* Clear watch registers */
	mtc0 zero, CP0_WATCHLO
	mtc0 zero, CP0_WATCHHI

	/* STATUS register */
	mfc0 k0,   CP0_STATUS
	li   k1,   ~ST0_IE
	and  k0,   k1
	mtc0 zero, CP0_CAUSE
	mtc0 k0,   CP0_STATUS

	/* CAUSE register */
	mtc0 zero, CP0_CAUSE

	/* Init Timer */
	mtc0 zero, CP0_COUNT
	mtc0 zero, CP0_COMPARE

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* CONFIG0 register */
	li   t0, CONF_CM_UNCACHED
	mtc0 t0, CP0_CONFIG
#endif

#endif /* #ifndef COMPRESSED_UBOOT */

	 /* Initialize GOT pointer.*/
	bal   1f
	nop
	.word _GLOBAL_OFFSET_TABLE_
1:
	move  gp, ra
	lw    t1, 0(ra)
	move  gp, t1

#ifndef COMPRESSED_UBOOT
	/* Lowlevel initialization of GPIO */
	la   t7, lowlevel_gpio_init
	jalr t7
	nop

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* Initialize any external memory */
	la   t9, lowlevel_init
	jalr t9
	nop

	la t0, rel_start
	j  t0
	nop
#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */

rel_start:
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* Initialize caches... */
	la   t9, simple_mips_cache_reset
	jalr t9
	nop

	/* ... and enable them */
#if (SOC_TYPE & QCA_AR934X_SOC)
	li   t7,   KSEG1ADDR(QCA_RST_REVISION_ID_REG)
	lw   t7,   0(t7)
	andi t9,   t7, 0xf
	bne  zero, t9, 1f
	nop

	li t0, CONF_CM_UNCACHED
	j  2f
	nop
#endif

1:
	li   t0, CONF_CM_CACHABLE_NONCOHERENT
2:
	mtc0 t0, CP0_CONFIG

#if (SOC_TYPE & QCA_AR933X_SOC) || \
	(SOC_TYPE & QCA_AR934X_SOC)
	la   t9, mips_cache_lock_24k
	jalr t9
	nop
#endif

#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */

#endif /* #ifndef COMPRESSED_UBOOT */

#if (SOC_TYPE & QCA_AR934X_SOC) | \
	(SOC_TYPE & QCA_QCA953X_SOC)
	/* Setup stack in SRAM */
	li t0, CONFIG_INIT_SRAM_SP_OFFSET
#else
	li t0, CFG_SDRAM_BASE + CFG_INIT_SP_OFFSET
#endif
	la sp, 0(t0)

	la t9, board_init_f
	j  t9
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
	.globl relocate_code
	.ent   relocate_code

relocate_code:
	/* Set new stack pointer */
	move sp, a0

	li   t0, CFG_MONITOR_BASE
	la   t3, in_ram
	lw   t2, -12(t3)	/* t2 - uboot_end_data */
	move t1, a2

	/*
	 * Fix GOT pointer:
	 * New GOT-PTR = (old GOT-PTR - CFG_MONITOR_BASE) + Destination Address
	 */
	move t6, gp
	sub  gp, CFG_MONITOR_BASE
	add  gp, a2			/* gp now adjusted */
	sub  t6, gp, t6		/* t6 - relocation offset */

	/*
	 * t0 = source address
	 * t1 = target address
	 * t2 = source end address
	 */
1:
	lw   t3, 0(t0)
	sw   t3, 0(t1)
	addu t0, 4
	ble  t0, t2, 1b
	addu t1, 4			/* Delay slot */

	/* If caches were enabled, we would have to flush them here */

	/* Jump to where we've relocated ourselves */
	addi t0, a2, in_ram - _start
	j    t0
	nop

	.word uboot_end_data
	.word uboot_end
	.word num_got_entries

in_ram:
	/* Now we want to update GOT */
	lw   t3, -4(t0)		/* t3 - num_got_entries */
	addi t4, gp, 8		/* Skipping first two entries */
	li   t2, 2
1:
	lw   t1, 0(t4)
	beqz t1, 2f
	add  t1, t6
	sw   t1, 0(t4)
2:
	addi t2, 1
	blt  t2, t3, 1b
	addi t4, 4			/* Delay slot */

	/* Clear BSS */
	lw  t1, -12(t0)		/* t1 - uboot_end_data */
	lw  t2, -8(t0)		/* t2 - uboot_end */
	add t1, t6			/* Adjust pointers */
	add t2, t6

	sub t1, 4
1:
	addi t1, 4
	bltl t1, t2, 1b
	sw   zero, 0(t1)	/* Delay slot */

	move a0, a1
	la   t9, board_init_r
	j    t9
	move a1, a2			/* Delay slot */

	.end relocate_code

#ifndef COMPRESSED_UBOOT
	/* Exception handlers */
romReserved:
	b romReserved

romExcHandle:
	b romExcHandle
#endif /* #ifndef COMPRESSED_UBOOT */
