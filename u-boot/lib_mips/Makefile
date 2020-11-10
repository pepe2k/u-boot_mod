#
# Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de
#
# SPDX-License-Identifier: GPL-2.0
#

include $(TOPDIR)/config.mk

BOOTSTRAPOBJ-y += bootstrap_board.o
BOOTSTRAPOBJ-y += time.o

OBJS-y	+= board.o
OBJS-y	+= mips_linux.o
OBJS-y	+= time.o

CPPFLAGS += -DCONFIG_LZMA

include $(TOPDIR)/end.mk