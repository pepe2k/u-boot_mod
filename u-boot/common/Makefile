#
# (C) Copyright 2004
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= libcommon.a

AOBJS	=

COBJS	= main.o \
		  cmd_bootm.o \
		  cmd_boot.o \
		  cmd_flash.o \
		  cmd_mem.o \
		  cmd_custom.o \
		  cmd_net.o \
		  cmd_nvedit.o \
		  cmd_itest.o \
		  cmd_load.o \
		  cmd_qcaclk.o \
		  command.o \
		  console.o \
		  devices.o \
		  dlmalloc.o \
		  environment.o \
		  env_common.o \
		  env_nowhere.o \
		  exports.o \
		  flash.o \
		  lists.o \
		  env_flash.o \
		  hush.o \
		  xyzModem.o \
		  crc16.o \
		  s_record.o

OBJS	= $(AOBJS) $(COBJS)

CPPFLAGS += -I..

ifeq ($(DUAL_FIRMWAREIMAGE_SUPPORT),1)
CFLAGS += -DCONFIG_DUALIMAGE_SUPPORT
OBJS += cmd_bdr.o
endif

all:	$(LIB) $(AOBJS)

$(LIB): .depend $(OBJS)
	$(AR) crv $@ $(OBJS)

environment.o: environment.c ../tools/envcrc
	$(CC) $(AFLAGS) -Wa,--no-warn \
		-DENV_CRC=$(shell ../tools/envcrc) \
		-c -o $@ environment.c

../tools/envcrc:
	$(MAKE) -C ../tools

#########################################################################

.depend:	Makefile $(AOBJS:.o=.S) $(COBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(AOBJS:.o=.S) $(COBJS:.o=.c) > $@

sinclude .depend

#########################################################################
