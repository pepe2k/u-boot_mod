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

#define ATH_SPI_CLOCK	0x1F000004

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

#if defined(CONFIG_WASP_SUPPORT)

	// Disable JTAG (bit 1 set) and ALL clock observation (bit 2~9 reset)
	// Do not do this in RAM version!
	li  a1, AR934X_GPIO_FUNCTION
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	li  v1, 0x2
#else
	li  v1, 0x0
#endif
	sw  v1, 0(a1)

#if defined(CONFIG_FOR_TPLINK_WDR3600_WDR43X0_V1)
	/*
	 * LEDs and buttons GPIOs on WDR3600/WDR43x0 v1:
	 *
	 * 11 => USB1 LED
	 * 12 => USB2 LED
	 * 13 => WLAN2G
	 * 14 => SYS
	 * 15 => QSS
	 * 21 => USB2 POWER (active high)
	 * 22 => USB1 POWER (active high)
	 *
	 * 16 => Reset button
	 * 17 => Wi-Fi ON/OFF switch
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	// GPIO Init
	li  a1, AR934X_GPIO_OE
	lw  v1, 0(a1)
	// Set GPIOs 11~15 and 21~22 as outputs
	and v1, v1, 0xFF9F07FF
	// Set GPIOs 16~17 as inputs
	or  v1, v1, 0x30000
	sw  v1, 0(a1)

	// Set GPIO function for GPIO 11
	li	a1, AR934X_GPIO_OUT_FUNCTION2
	lw	v1, 0(a1)
	and v1, v1, 0x00FFFFFF
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 12~15
	li	a1, AR934X_GPIO_OUT_FUNCTION3
	li	v1, 0x0
	sw	v1, 0(a1)

	// Turn on power on both USB
	li  a1, AR934X_GPIO_SET
	li	v1, 0x600000
	sw	v1, 0(a1)

	// Turn off all LEDs
	li  a1, AR934X_GPIO_SET
	li	v1, 0xF800
	sw	v1, 0(a1)

#elif defined(CONFIG_FOR_TPLINK_WDR3500_V1)
	/*
	 * LEDs and buttons GPIOs on WDR3500 v1:
	 *
	 * 11 => USB LED
	 * 12 => USB POWER (active high)
	 * 13 => WLAN2G
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 * 22 => LAN4
	 *
	 * 16 => Reset button
	 * 17 => Wi-Fi ON/OFF switch
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	// GPIO Init
	li  a1, AR934X_GPIO_OE
	lw  v1, 0(a1)
	// Set GPIOs 11~15 and 18~22 as outputs
	and v1, v1, 0xFF8307FF
	// Set GPIOs 16~17 as inputs
	or  v1, v1, 0x30000
	sw  v1, 0(a1)

	// Set GPIO function for GPIO 11
	li	a1, AR934X_GPIO_OUT_FUNCTION2
	lw	v1, 0(a1)
	and v1, v1, 0x00FFFFFF
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 12~15
	li	a1, AR934X_GPIO_OUT_FUNCTION3
	li	v1, 0x0
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 18~19
	li	a1, AR934X_GPIO_OUT_FUNCTION4
	lw	v1, 0(a1)
	and v1, v1, 0xFFFF
	sw	v1, 0(a1)

	// Turn on power on USB
	li  a1, AR934X_GPIO_SET
	li	v1, 0x1000
	sw	v1, 0(a1)

	// Turn off all LEDs
	li  a1, AR934X_GPIO_SET
	li	v1, 0x7CF800
	sw	v1, 0(a1)

#elif defined(CONFIG_FOR_TPLINK_WR841N_V8)
	/*
	 * LEDs and buttons GPIOs on WR841N/D v8:
	 *
	 * 12 => LAN4
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 *
	 * 16 => Wi-Fi ON/OFF switch
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	// GPIOs init
	li  a1, AR934X_GPIO_OE
	lw  v1, 0(a1)
	// Set GPIOs 12~15 and 18~21 as outputs
	and v1, v1, 0xFFC30FFF
	// Set GPIOs 16~17 as inputs
	or  v1, v1, 0x30000
	sw  v1, 0(a1)

	// Set gpio function for GPIOs 12~15
	li	a1, AR934X_GPIO_OUT_FUNCTION3
	li	v1, 0x0
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 18~19
	li	a1, AR934X_GPIO_OUT_FUNCTION4
	lw	v1, 0(a1)
	and v1, v1, 0xFFFF
	sw	v1, 0(a1)

	// Turn off all LEDs
	li  a1, AR934X_GPIO_SET
	li	v1, 0x3CF000
	sw	v1, 0(a1)

#elif defined(CONFIG_FOR_TPLINK_MR3420_V2)
	/*
	 * LEDs and buttons GPIOs on MR3420 v2:
	 *
	 * 4  => USB Power (active high)
	 * 11 => USB/3G LED
	 * 12 => LAN4
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => WAN
	 * 19 => LAN1
	 * 20 => LAN2
	 * 21 => LAN3
	 *
	 * 16 => WPS button
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	// GPIOs init
	li  a1, AR934X_GPIO_OE
	lw  v1, 0(a1)
	// Set GPIOs 4, 11~15 and 18~21 as outputs
	and v1, v1, 0xFFC307EF
	// Set GPIOs 16~17 as inputs
	or  v1, v1, 0x30000
	sw  v1, 0(a1)

	// Set GPIO function for GPIO 4
	li	a1, AR934X_GPIO_OUT_FUNCTION1
	lw	v1, 0(a1)
	and v1, v1, 0xFFFFFF00
	sw	v1, 0(a1)

	// Set GPIO function for GPIO 11
	li	a1, AR934X_GPIO_OUT_FUNCTION2
	lw	v1, 0(a1)
	and v1, v1, 0x00FFFFFF
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 12~15
	li	a1, AR934X_GPIO_OUT_FUNCTION3
	li	v1, 0x0
	sw	v1, 0(a1)

	// Set GPIO function for GPIOs 18~19
	li	a1, AR934X_GPIO_OUT_FUNCTION4
	lw	v1, 0(a1)
	and v1, v1, 0xFFFF
	sw	v1, 0(a1)

	// Turn on power on USB
	li  a1, AR934X_GPIO_SET
	li	v1, 0x10
	sw	v1, 0(a1)

	// Turn off all LEDs
	li  a1, AR934X_GPIO_SET
	li	v1, 0x3CF800
	sw	v1, 0(a1)

#elif defined(CONFIG_FOR_TPLINK_WA830RE_V2_WA801ND_V2)
	/*
	 * LEDs and buttons GPIOs on WA830REv2 and WA801ND v2:
	 *
	 * 13 => WLAN
	 * 14 => SYS
	 * 15 => QSS
	 * 18 => LAN
	 *
	 * 16 => Range Extender
	 * 17 => Reset button
	 *
	 * All OUT GPIOs are active LOW if not stated otherwise
	 */

	// GPIOs init
	li  a1, AR934X_GPIO_OE
	lw  v1, 0(a1)
	// Set GPIOs 13~15 and 18 as outputs
	and v1, v1, 0xFFFB1FFF
	// Set GPIOs 16~17 as inputs
	or  v1, v1, 0x30000
	sw  v1, 0(a1)

	// Set GPIO function for GPIOs 13~15
	li	a1, AR934X_GPIO_OUT_FUNCTION3
	lw	v1, 0(a1)
	and v1, v1, 0xFF
	sw	v1, 0(a1)

	// Set GPIO function for GPIO 18
	li	a1, AR934X_GPIO_OUT_FUNCTION4
	lw	v1, 0(a1)
	and v1, v1, 0xFF00FFFF
	sw	v1, 0(a1)

	// Turn off all LEDs
	li  a1, AR934X_GPIO_SET
	li	v1, 0x4E000
	sw	v1, 0(a1)

#endif

#endif /* #if defined(CONFIG_WASP_SUPPORT) */

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

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* CONFIG0 register */
	li	t0, CONF_CM_UNCACHED
	mtc0	t0, CP0_CONFIG
#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */

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

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
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
#endif

/**************************************************************************/

	/* Initialize any external memory.
	 */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
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
#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */

rel_start:

#if defined(CONFIG_AR7100) || defined(CONFIG_AR7240) || defined(CONFIG_ATHEROS)
	/* REMAP_DISABLE */
	li	a0,	KSEG1ADDR(ATH_SPI_CLOCK)
#if defined(CONFIG_MACH_QCA955x)
	li	t0,	0x246
#elif defined(CONFIG_WASP_SUPPORT)
	li	t0,	0x243
#else
	// TODO: SPI clock from FLASH?
	// for now we will use divider = 10 ( (4+1)*2 )
	li	t0,	0x44
#endif
	sw	t0,	0(a0)
#endif

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
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
#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */

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

#ifndef COMPRESSED_UBOOT
	/* Exception handlers */
romReserved:
	b romReserved

romExcHandle:
	b romExcHandle
#endif /* #ifndef COMPRESSED_UBOOT */
