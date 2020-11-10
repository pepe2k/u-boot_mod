#
# Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier: GPL-2.0
#

include $(TOPDIR)/config.mk

BOOTSTRAPOBJ-y += $(BOARD).o

OBJS-y += $(BOARD).o
OBJS-y += ../common/spi_flash.o
OBJS-y += ../common/common.o
OBJS-y += ../common/qca-eth-953x.o

ifeq ($(ETH_CONFIG), _s27)
  OBJS-y += ../common/athr_s27_phy.o
endif

include $(TOPDIR)/end.mk