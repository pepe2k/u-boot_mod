#
# Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de
#
# SPDX-License-Identifier: GPL-2.0
#

include $(TOPDIR)/config.mk

OBJS-y += uip.o
OBJS-y += uip_arch.o
OBJS-y += uip_arp.o
OBJS-y += httpd.o
OBJS-y += fs.o

# Suppress warnings when building with size optimization
CFLAGS += -fno-strict-aliasing

fs.c:	$(obj)fsdata.c

$(obj)fsdata.c:
	./vendors/makefsdatac $(obj)fsdata.c $(DEVICE_VENDOR)

include $(TOPDIR)/end.mk