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
OBJS-y += ../common/miiphybb.o
OBJS-y += ../common/qca-eth-956x.o

ifeq ($(ATH_RGMII_CAL),1)
  OBJS-y	+= ../common/rgmii-cal-956x.o
  OBJS-y	+= ../common/athrs17_lpbk.o
endif

ifeq ($(ETH_CONFIG2), _s17)
  OBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17)
  OBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG2), _s17_hwaccel)
  OBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s17_hwaccel)
  OBJS-y	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s16)
  OBJS-y	+= ../common/athrs16_phy.o
endif

ifeq ($(ETH_CONFIG), _f1e)
  OBJS-y	+= ../common/athrsf1_phy.o
endif

ifeq ($(ETH_CONFIG), _f2e)
  OBJS-y	+= ../common/athrsf2_phy.o
endif

ifeq ($(ETH_CONFIG), _vir)
  OBJS-y	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG2), _vir)
  OBJS-y	+= ../common/athrs_vir_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
  OBJS-y	+= ../common/athr_s27_phy.o
endif

ifeq ($(ETH_CONFIG), _ar8033)
  OBJS-y	+= ../common/athr_ar8033_phy.o
endif

include $(TOPDIR)/end.mk