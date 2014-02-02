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

	.globl hornet_ddr_init
	.text
	.align 4

#define set_mem(_mem, _val) \
	li t9,   _mem;          \
	sw _val, 0(t9);

//============================================
//   init DDR1 parameter before rel_start
//===========================================
hornet_ddr_init:
	// 0x18000000 (DDR_CONFIG, p. 54)
	// CFG_DDR_CONFIG_VAL = 0x7fbc8cd0 (ap121.h)
	li t8, CFG_DDR_CONFIG_VAL;
	set_mem(0xB8000000, t8);

	// 0x18000004 (DDR_CONFIG2, p. 55)
	// CFG_DDR_CONFIG2_VAL = 0x99d0e6a8 (ap121.h)
	li t8, CFG_DDR_CONFIG2_VAL;
	set_mem(0xB8000004, t8);

mem_type:
	// TODO: what about SDRAM?
	// 0x180600AC (BOOT_STRAP, p. 81)
	li  t8, 0xB80600AC			// load BOOT_STRAP reg address
	lw  t9, 0(t8)				// and its value
	li  t8, 0x1000				// 0x1000 -> BIT12 is set
	and t9, t9, t8
	bne t9, zero, ddr1_config	// jump if we have DDR1

ddr2_config:
	// Enable DDR2
	// 0x1800008C (DDR_DDR2_CONFIG, p. 58)
	li t8, 0xA59;
	set_mem(0xB800008C, t8);

	// Precharge All
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x8;
	set_mem(0xB8000010, t8);

	// Disable High Temperature Self-Refresh Rate
	// 0x18000090 (DDR_EMR2, p. 58)
	li t8, 0x0;
	set_mem(0xB8000090, t8);

	// Extended Mode Register 2 Set (EMR2S)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x10;
	set_mem(0xB8000010, t8);

	// 0x18000094 (DDR_EMR3, p. 58)
	li t8, 0x0;
	set_mem(0xB8000094, t8);

	// Extended Mode Register 3 Set (EMR3S)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x20;
	set_mem(0xB8000010, t8);

	// Enable DLL
	// 0x1800000C (DDR_EXTENDED_MODE_REGISTER, p. 55)
	li t8, 0x0;
	set_mem(0xB800000C, t8);

	// Extended Mode Register Set (EMRS)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x2;
	set_mem(0xB8000010, t8);

	// Reset DLL
	// 0x18000008 (DDR_MODE_REGISTER, p. 55)
	li t8, 0x100;
	set_mem(0xB8000008, t8);

	// Mode Register Set (MRS)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x1;
	set_mem(0xB8000010, t8);

	// Precharge All
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x8;
	set_mem(0xB8000010, t8);

	// Auto Refresh
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x4;
	set_mem(0xB8000010, t8);

	// Auto Refresh
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x4;
	set_mem(0xB8000010, t8);

	// Write recovery (WR) 6 clock, CAS Latency 3, Burst Length 8
	// 0x18000008 (DDR_MODE_REGISTER, p. 55)
	li t8, 0xa33;
	set_mem(0xB8000008, t8);

	// Mode Register Set (MRS)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x1;
	set_mem(0xB8000010, t8);

	// E7,E8,E9 equal to 1(Enable OCD defaults), Enable DLL, Reduced Drive Strength
	// 0x1800000C (DDR_EXTENDED_MODE_REGISTER, p. 55)
	li t8, 0x382;
	set_mem(0xB800000C, t8);

	// Extended Mode Register Set (EMRS)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x2;
	set_mem(0xB8000010, t8);

	// E7,E8,E9 equal to 0(OCD exit), Enable DLL, Reduced Drive Strength
	// 0x1800000C (DDR_EXTENDED_MODE_REGISTER, p. 55)
	li t8, 0x402;
	set_mem(0xB800000C, t8);

	// Extended Mode Register Set (EMRS)
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x2;
	set_mem(0xB8000010, t8);

	// Refresh control. Bit 14 is enable. Bits<13:0> Refresh time
	// 0x18000014 (DDR_REFRESH, p. 56)
	li t8, CFG_DDR_REFRESH_VAL;
	set_mem(0xB8000014, t8);

	// DQS 0 Tap Control (needs tuning)
	// 0x1800001C (TAP_CONTROL_0, p. 56)
	li t8, CFG_DDR_TAP0_VAL;
	set_mem(0xB800001C, t8);

	// DQS 1 Tap Control (needs tuning)
	// 0x18000020 (TAP_CONTROL_1, p. 57)
	li t8, CFG_DDR_TAP1_VAL;
	set_mem(0xB8000020, t8);

	// For 16-bit DDR
	// 0x18000018 (DDR_RD_DATA_THIS_CYCLE, p. 56)
	li t8, 0x00ff;
	set_mem(0xB8000018, t8);

	nop
	jr ra

ddr1_config:
	// Precharge All
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x8;
	set_mem(0xB8000010, t8);

	// 0x18000008 (DDR_MODE_REGISTER, p. 55)
	li t8, CFG_DDR_MODE_VAL_INIT;
	set_mem(0xB8000008, t8);

	// Write Mode Word in DDR
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x1;
	set_mem(0xB8000010, t8);

	// Enable DLL, High drive strength from DDR
	// 0x1800000C (DDR_EXTENDED_MODE_REGISTER, p. 55)
	li t8, 0x2;
	set_mem(0xB800000C, t8);

	// Write Extended Mode Word of DDR
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x2;
	set_mem(0xB8000010, t8);

	// Precharge All
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x8;
	set_mem(0xB8000010, t8);

	// DLL out of reset, CAS Latency 3
	// 0x18000008 (DDR_MODE_REGISTER, p. 55)
	li t8, CFG_DDR_MODE_VAL;
	set_mem(0xB8000008, t8);

	// Write mode word
	// 0x18000010 (DDR_CONTROL, p. 56)
	li t8, 0x1;
	set_mem(0xB8000010, t8);

	// Refresh control. Bit 14 is enable. Bits<13:0> Refresh time
	// 0x18000014 (DDR_REFRESH, p. 56)
	li t8, CFG_DDR_REFRESH_VAL;
	set_mem(0xB8000014, t8);

	// DQS 0 Tap Control (needs tuning)
	// 0x1800001C (TAP_CONTROL_0, p. 56)
	li t8, CFG_DDR_TAP0_VAL;
	set_mem(0xB800001C, t8);

	// DQS 1 Tap Control (needs tuning)
	// 0x18000020 (TAP_CONTROL_1, p. 57)
	li t8, CFG_DDR_TAP1_VAL;
	set_mem(0xB8000020, t8);

	// For 16-bit DDR
	// 0x18000018 (DDR_RD_DATA_THIS_CYCLE, p. 56)
	li t8, 0x00ff;
	set_mem(0xB8000018, t8);

	nop
	jr ra
    
/*
 * void hornet_ddr_tap_init(void)
 *
 * This "function" is used to find the tap settings for the DDR
 */
	.globl	hornet_ddr_tap_init
	.ent	hornet_ddr_tap_init
hornet_ddr_tap_init: /* { */

#if NEW_DDR_TAP_CAL
	li	t1,0x80500000 
	li	t0,0xffffffff 
	 
	sw	t0,0x0(t1) 
	sw	t0,0x4(t1) 
	sw	t0,0x8(t1) 
	sw	t0,0xc(t1) 
	 
	nop 
	nop

ddr_pat_init:
	li 	t8, 0xa0002000
	li	t0, 0x00
	li	t1, 0x100	
write_loop_start:
	andi    t2, t0, 0x03
pat_000:
	li	t3, 0x00
	bne	t2, t3,pat_001
	li 	t9, 0x00000000
	sw	t9, 0x0 (t8)
	b	pat_004

pat_001:
	li	t3, 0x01
	bne	t2, t3,pat_002
	li 	t9, 0x0000ffff
	sw	t9, 0x0 (t8)
	b	pat_004

pat_002:
	li	t3, 0x02
	bne	t2, t3,pat_003
	li 	t9, 0xffff0000
	sw	t9, 0x0 (t8)
	b	pat_004

pat_003:
	li	t3, 0x03
	bne	t2, t3,pat_004
	li 	t9, 0xffffffff
	sw	t9, 0x0 (t8)

pat_004:
	andi    t2, t0, 0x0c
	li	t3, 0x00
	bne	t2, t3,pat_005
	li 	t9, 0x00000000
	sw	t9, 0x4 (t8)
	b	pat_008

pat_005:
	li	t3, 0x04
	bne	t2, t3,pat_006
	li 	t9, 0x0000ffff
	sw	t9, 0x4 (t8)
	b	pat_008

pat_006:
	li	t3, 0x08
	bne	t2, t3,pat_007
	li 	t9, 0xffff0000
	sw	t9, 0x4 (t8)
	b	pat_008

pat_007:
	li	t3, 0x0c
	bne	t2, t3,pat_008
	li 	t9, 0xffffffff
	sw	t9, 0x4 (t8)

pat_008:
	andi    t2, t0, 0x30
	li	t3, 0x00
	bne	t2, t3,pat_009
	li 	t9, 0x00000000
	sw	t9, 0x8 (t8)
	b	pat_00c

pat_009:
	li	t3, 0x10
	bne	t2, t3,pat_00a
	li 	t9, 0x0000ffff
	sw	t9, 0x8 (t8)
	b	pat_00c

pat_00a:
	li	t3, 0x20
	bne	t2, t3,pat_00b
	li 	t9, 0xffff0000
	sw	t9, 0x8 (t8)
	b	pat_00c

pat_00b:
	li	t3, 0x30
	bne	t2, t3,pat_00c
	li 	t9, 0xffffffff
	sw	t9, 0x8 (t8)

pat_00c:
	andi    t2, t0, 0xc0
	li	t3, 0x00
	bne	t2, t3,pat_00d
	li 	t9, 0x00000000
	sw	t9, 0xc (t8)
	b	pat_done

pat_00d:
	li	t3, 0x40
	bne	t2, t3,pat_00e
	li 	t9, 0x0000ffff
	sw	t9, 0xc (t8)
	b	pat_done

pat_00e:
	li	t3, 0x80
	bne	t2, t3,pat_00f
	li 	t9, 0xffff0000
	sw	t9, 0xc (t8)
	b	pat_done

pat_00f:
	li	t3, 0xc0
	bne	t2, t3,pat_done
	li 	t9, 0xffffffff
	sw	t9, 0xc (t8)

pat_done:

	addiu	t0, t0, 0x1
	addiu	t8, t8, 0x10
	bne	t0, t1, write_loop_start
	



###### ddr init over #########

	li	a0, 0xa0002000
	li	a1, 0x80002000	     ### Start address of the pattern   200
	li	a2, 0x80003000	     ### End Address of the pattern     220
	li	t0, 0xb800001c	     ## Tap settings addr
	lw	a3, 0x0(t0)	     ## loading default tap value
	nop
	ori	t0, a3, 0x0
	nop
	li	t1, 0x1	     ## $t1=1 indicates increasing tap value, 0 = decreasing

load_tap:

	li	t7, 0x2
	#li	t7, 0x200	## No. of times read has to happen for 1 tap setting
	li	t8, 0xb8000000	#### Loading Tap Setting
	sw	t0, 0x1c(t8)
	nop
	sw	t0, 0x20(t8)
	nop
    #if 0 /* Hornet doesn't have DQS2, DQS3*/
	sw	t0, 0x24(t8)
	nop
	sw	t0, 0x28(t8)
	nop
    #endif	

###### t0 stores current tap setting under test
###### t1 indicates increment or decrement of tap 

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
	
	bne	t5, t6, tap_fail  # jump to fail if not equal
	nop
	nop
	nop

	addiu	t2, t2, 0x4  #incrementing addr
	addiu	t3, t3, 0x4
	nop
	nop
	
	bne	t3, t4, tap_addr_loop # compare new addr if end addr not reached
	nop	
	
	addiu	t7, t7, -1     # read passed for all locations once hence decrement t7
	nop
	bnez	t7, pat_read    # t7 = 0 represents passing of all locations for given tap
	nop
	nop
	
	bnez	t1, tap_incr     # increment tap if t1 = 1
	nop
	nop
	
	bnez	t0, tap_decr	  ## $t0=0 implies tap=0 works
	nop		          ## so low limit=0, else decrement tap value
	nop
	li	t8, 0x80500000   ## assigning lower limit = 0
	sw	t0, 0x0(t8)
	add	t9, t9, t0     ##adding lower limit to upper limit (used to calc mid value)
	nop
	nop
	
	b tap_calc
	nop
	nop

tap_decr: 			# decrement t0 by 1 and move to loading this new tap
	addiu	t0, t0 , -1
	nop
	b load_tap
	nop
	nop

tap_incr:
	addiu	t0, t0 , 0x1
	nop
	xori	v1, t0, 0x20	# limiting upper limit to 0x20
	nop
	bnez	v1, load_tap
	nop
	nop
	b up_limit
	nop
	nop

tap_fail:
	bnez	t1, up_limit 	# t1=0 means lower limit detected @ fail else upper limit
	nop
	nop
	nop
	addiu	t0, t0, 0x1
	nop
	li	t8, 0x80500000	# storing lower limit
	nop
	sw	t0, 0x0(t8)
	add	t9, t9, t0	# storing lower limit# adding lower limit and upper limit
	nop
	nop
	nop
	
	b tap_calc
	nop
	nop

up_limit:
	addiu	t0, t0, -1 
	li	t1, 0x0	 ## changing to decreasing tap mode	
	li	t8, 0x80500000 ## storing upper limit
	sw	t0, 0x4(t8)	
	ori	t9, t0, 0x0	
	nop
	nop
	nop
	
	ori	t0, a3, 0x0 	# loading default tap value 
	nop
	b load_tap
	nop
	nop

tap_calc:  ## calculating mid value of the tap, storing DQS0, DQS1 in 0x80500008, 0x8050000c resp.
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
	li      t8, 0xb8000000  #### Loading Tap Setting
	nop
	sw      t5, 0x1c(t8)
	nop
	sw      t6, 0x20(t8)
	nop
    #if 0 /* Hornet doesn't have DQS2, DQS3*/	
	sw      t5, 0x24(t8)
	nop
	sw      t6, 0x28(t8)
	nop
    #endif	
	nop
	nop
#else /* NEW_DDR_TAP_CAL */
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

	li	t7, 0x2
	#li	t7, 0x200	## No. of times read has to happen for 1 tap setting
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
#endif /* SIMPLE_DDR_TAP_CAL */

end:
	nop
	nop
	nop
	jr 	ra

	.end	hornet_ddr_tap_init
/* } */
