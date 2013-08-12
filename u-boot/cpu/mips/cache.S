/*
 *  Cache-handling routined for MIPS 4K CPUs
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
#include <asm/cacheops.h>


	/* 64K is the maximum size of instruction and data caches on
	 * MIPS 24K.
	 */
#define MIPS_MAX_CACHE_SIZE	65536


/*
 * cacheop macro to automate cache operations
 * first some helpers...
 */
#define _mincache(size, maxsize) \
   bltu  size,maxsize,9f ; \
   move  size,maxsize ;    \
9:

#define _align(minaddr, maxaddr, linesize) \
   .set noat ; \
   subu  AT,linesize,1 ;   \
   not   AT ;        \
   and   minaddr,AT ;      \
   addu  maxaddr,-1 ;      \
   and   maxaddr,AT ;      \
   .set at

/* general operations */
#define doop1(op1) \
   cache op1,0(a0)
#define doop2(op1, op2) \
   cache op1,0(a0) ;    \
   nop ;          \
   cache op2,0(a0)

/* specials for cache initialisation */
#define doop1lw(op1) \
   lw zero,0(a0)
#define doop1lw1(op1) \
   cache op1,0(a0) ;    \
   lw zero,0(a0) ;      \
   cache op1,0(a0)
#define doop121(op1,op2) \
   cache op1,0(a0) ;    \
   nop;           \
   cache op2,0(a0) ;    \
   nop;           \
   cache op1,0(a0)

#define _oploopn(minaddr, maxaddr, linesize, tag, ops) \
   .set  noreorder ;    \
10:   doop##tag##ops ;  \
   bne     minaddr,maxaddr,10b ; \
   add      minaddr,linesize ;   \
   .set  reorder

/* finally the cache operation macros */
#define vcacheopn(kva, n, cacheSize, cacheLineSize, tag, ops) \
   blez  n,11f ;        \
   addu  n,kva ;        \
   _align(kva, n, cacheLineSize) ; \
   _oploopn(kva, n, cacheLineSize, tag, ops) ; \
11:

#define icacheopn(kva, n, cacheSize, cacheLineSize, tag, ops) \
   _mincache(n, cacheSize);   \
   blez  n,11f ;        \
   addu  n,kva ;        \
   _align(kva, n, cacheLineSize) ; \
   _oploopn(kva, n, cacheLineSize, tag, ops) ; \
11:

#define vcacheop(kva, n, cacheSize, cacheLineSize, op) \
   vcacheopn(kva, n, cacheSize, cacheLineSize, 1, (op))

#define icacheop(kva, n, cacheSize, cacheLineSize, op) \
   icacheopn(kva, n, cacheSize, cacheLineSize, 1, (op))


.globl simple_mips_cache_reset
.ent   simple_mips_cache_reset

simple_mips_cache_reset:
        li      t2, CFG_ICACHE_SIZE
        li      t3, CFG_DCACHE_SIZE
        li      t4, CFG_CACHELINE_SIZE

        mtc0    zero, CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif

        li      t0, K0BASE
    	add     t2, t2, t0

_arai_icache_loop:
    	cache   Index_Store_Tag_I, 0(t0)
    	add     t0, t0, t4
    	bne     t0, t2, _arai_icache_loop

        li      t0, K0BASE
    	add     t3, t3, t0
_arai_dcache_loop:
    	cache   Index_Store_Tag_D, 0(t0)
    	add     t0, t0, t4
    	bne     t0, t3, _arai_dcache_loop
	
	j  ra
	.end  simple_mips_cache_reset
	

/*******************************************************************************
*
* mips_cache_reset - low level initialisation of the primary caches
*
* This routine initialises the primary caches to ensure that they
* have good parity.  It must be called by the ROM before any cached locations
* are used to prevent the possibility of data with bad parity being written to
* memory.
* To initialise the instruction cache it is essential that a source of data
* with good parity is available. This routine
* will initialise an area of memory starting at location zero to be used as
* a source of parity.
*
* RETURNS: N/A
*
*/
	.globl	mips_cache_reset
	.ent	mips_cache_reset
mips_cache_reset:

	li	t2, CFG_ICACHE_SIZE
	li	t3, CFG_DCACHE_SIZE
	li	t4, CFG_CACHELINE_SIZE
	move	t5, t4


	li	v0, MIPS_MAX_CACHE_SIZE

	/* Now clear that much memory starting from zero.
	 */

	li	a0, KSEG1
	addu	a1, a0, v0

2:	sw	zero, 0(a0)
	sw	zero, 4(a0)
	sw	zero, 8(a0)
	sw	zero, 12(a0)
	sw	zero, 16(a0)
	sw	zero, 20(a0)
	sw	zero, 24(a0)
	sw	zero, 28(a0)
	addu	a0, 32
	bltu	a0, a1, 2b

	/* Set invalid tag.
	 */
	mtc0	zero, CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif


   /*
    * The caches are probably in an indeterminate state,
    * so we force good parity into them by doing an
    * invalidate, load/fill, invalidate for each line.
    */

	/* Assume bottom of RAM will generate good parity for the cache.
	 */

	li	a0, K0BASE
	move	a2, t2		# icacheSize
	move	a3, t4		# icacheLineSize
	move	a1, a2
	icacheopn(a0,a1,a2,a3,121,(Index_Store_Tag_I,Fill))

	/* To support Orion/R4600, we initialise the data cache in 3 passes.
	 */

	/* 1: initialise dcache tags.
	 */

	li	a0, K0BASE
	move	a2, t3		# dcacheSize
	move	a3, t5		# dcacheLineSize
	move	a1, a2
	icacheop(a0,a1,a2,a3,Index_Store_Tag_D)


	/* 2: fill dcache.
	 */

	li	a0, K0BASE
	move	a2, t3		# dcacheSize
	move	a3, t5		# dcacheLineSize
	move	a1, a2
	icacheopn(a0,a1,a2,a3,1lw,(dummy))


	/* 3: clear dcache tags.
	 */

	li	a0, K0BASE
	move	a2, t3		# dcacheSize
	move	a3, t5		# dcacheLineSize
	move	a1, a2
	icacheop(a0,a1,a2,a3,Index_Store_Tag_D)


	j  ra
	.end  mips_cache_reset


/*******************************************************************************
*
* dcache_status - get cache status
*
* RETURNS: 0 - cache disabled; 1 - cache enabled
*
*/
	.globl	dcache_status
	.ent	dcache_status
dcache_status:

	mfc0	v0, CP0_CONFIG
	andi	v0, v0, 1
	j	ra

	.end  dcache_status

/*******************************************************************************
*
* dcache_disable - disable cache
*
* RETURNS: N/A
*
*/
	.globl	dcache_disable
	.ent	dcache_disable
dcache_disable:

	mfc0	t0, CP0_CONFIG
	li	t1, -8
	and	t0, t0, t1
	ori	t0, t0, CONF_CM_UNCACHED
	mtc0    t0, CP0_CONFIG
	j	ra

	.end  dcache_disable


/*******************************************************************************
*
* mips_cache_lock - lock RAM area pointed to by a0 in cache.
*
* RETURNS: N/A
*
*/
#define	CACHE_LOCK_SIZE	(CFG_DCACHE_SIZE)
	.globl	mips_cache_lock
	.ent	mips_cache_lock
mips_cache_lock:
	li	a1, K0BASE - CACHE_LOCK_SIZE
	addu	a0, a1
	li	a2, CACHE_LOCK_SIZE
	li	a3, CFG_CACHELINE_SIZE
	move	a1, a2
	icacheop(a0,a1,a2,a3,0x1d)

	j	ra
	.end	mips_cache_lock

/*****************************************************************************
 * flushes a range in dcache
 * a0 = start
 * a1 = end
 */
    .globl  dcache_flush_range
    .ent    dcache_flush_range
dcache_flush_range:
    move    t0, a0
    li      t1, CFG_CACHELINE_SIZE
    move    t2, a1
cache_loop_d_flush_range:
    cache   Hit_Writeback_Inv_D, 0(t0)
    addu    t0, t1
    bne     t0, t2, cache_loop_d_flush_range
    nop
	j  ra
    .end    dcache_flush_range

/****************************************************************************
 *
 * mips_cache_flush_all - flushes entire I and D caches.
 */

    .globl  mips_cache_flush
    .ent    mips_cache_flush
mips_cache_flush:
	/* Flush caches...
	 */
    li      t0, (CFG_ICACHE_SIZE)
    li      t1, CFG_CACHELINE_SIZE
    li      t2, KSEG0
    addu    t3, t0, t2
    mtc0    zero, CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif
cache_loop_flush:
    cache   Hit_Invalidate_I, 0(t2)
    addu    t2, t1
    bne     t2, t3, cache_loop_flush
    nop

    li      t0, (CFG_DCACHE_SIZE)
    li      t1, CFG_CACHELINE_SIZE
    li      t2, KSEG0
    addu    t3, t0, t2
cache_loop_d_flush:
    cache   Hit_Writeback_Inv_D, 0(t2)
    addu    t2, t1
    bne     t2, t3, cache_loop_d_flush
    nop
	j  ra
	.end  mips_cache_flush

/*
 * Invalidate the I-Cache.
 * Note:If this is executed from cached address space,
 *      the cache would still have the addresses of this
 *      function.
 */
	.globl	mips_icache_flush_ix
	.ent	mips_icache_flush_ix

mips_icache_flush_ix:	/* Flush caches Index Invalidate */
	li	t0,	(CFG_ICACHE_SIZE)
	li	t1,	CFG_CACHELINE_SIZE
	li	t2,	KUSEG
	addu	t3,	t0,	t2
	mtc0	zero,	CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif
icache_loop_flush_ix:
	cache	Index_Invalidate_I,	0(t2)
	addu	t2,	t1
	bne	t2,	t3,	icache_loop_flush_ix
	nop

	j	ra
	.end	mips_icache_flush_ix



/*********************************************************
 * mips_cache_lock_24k
 */

    .globl  mips_cache_lock_24k
    .ent    mips_cache_lock_24k

mips_cache_lock_24k:
    li      t0, 7936 
    li      t1, CFG_CACHELINE_SIZE
    li      t2, KSEG0
    addu    t3, t0, t2
    mtc0    zero, CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif
cache_loop_lock:

    li      t5, 0xfffff000
    and     t4, t2, t5
    ori     t4, t4, (1 << 7)
    mtc0    t4, CP0_TAGLO
#ifdef CONFIG_WASP_SUPPORT
	mtc0	zero, $29	# C0_TagHi
	mtc0	zero, $28, 2	# C0_DTagLo
	mtc0	zero, $29, 2	# C0_DTagHi
#endif

    cache   Index_Load_Tag_D, 0(t2)
    cache   0x1d, 0(t2)
    addu    t2, t1
    bne     t2, t3, cache_loop_lock
    nop
	j  ra
    .end    mips_cache_lock_24k

