#
# Copyright (c) 2013 Qualcomm Atheros, Inc.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).a

OBJS = $(BOARD).o ../../ar7240/common/spi_flash.o ../common/common.o \
	../common/miiphybb.o	\
	../common/qca-eth-956x.o

#
# The files included in EXTRA_OBJS use some functions that are not
# available in the `bootstrap' portion of tuboot.bin resulting in
# compile/link errors. Hence have them separate (i.e. don't include
# into lib$(BOARD).a and include them only in `u-boot' portion of
# tuboot.bin.
#

ifdef COMPRESSED_UBOOT
OBJS	+= $(BOARD_EXTRA_OBJS_tmp)
else
EXTRA_OBJS = $(BOARD_EXTRA_OBJS_tmp)
endif

ifeq ($(ATH_DUAL_FLASH),1)
OBJS	+= ../common/ath_nand.o ../../../drivers/nand/nand_ids.o
endif

ifndef BOOT_FROM_NAND
#OBJS	+= ../common/ath_flash.o
endif

ifeq ($(ATH_RGMII_CAL),1)
OBJS	+= ../common/rgmii-cal-956x.o	
OBJS	+= ../common/athrs17_lpbk.o
endif

ifeq ($(ETH_CONFIG2), _s17)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG2), _s17_hwaccel)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17_hwaccel)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s16)
OBJS	+= ../common/athrs16_phy.o
endif

ifeq ($(ETH_CONFIG), _f1e)
OBJS	+= ../common/athrsf1_phy.o
endif

ifeq ($(ETH_CONFIG), _f2e)
OBJS	+= ../common/athrsf2_phy.o
endif

ifeq ($(ETH_CONFIG), _vir)
OBJS	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG2), _vir)
OBJS	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
OBJS	+= ../common/athr_s27_phy.o
endif

ifeq ($(ETH_CONFIG), _ar8033)
OBJS	+= ../common/athr_ar8033_phy.o
endif


$(LIB):	.depend $(OBJS) $(SOBJS) $(EXTRA_OBJS)
	$(AR) crv $@ $(OBJS) $(SOBJS) $(EXTRA_OBJS)

#########################################################################

.depend:	Makefile $(SOBJS:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(SOBJS:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
