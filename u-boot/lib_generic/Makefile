#
# Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de
#
# SPDX-License-Identifier: GPL-2.0
#

include $(TOPDIR)/config.mk

BOOTSTRAPOBJ-y += string.o
BOOTSTRAPOBJ-y += unlzma_tiny.o

OBJS-y += crc32.o
OBJS-y += ctype.o
OBJS-y += display_options.o
OBJS-y += string.o
OBJS-y += unlzma_tiny.o
OBJS-y += vsprintf.o

CPPFLAGS += -DCONFIG_LZMA=1

include $(TOPDIR)/end.mk
