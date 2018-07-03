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

LIB	= $(obj)libcommon.a

AOBJS	=

COBJS-y += main.o
COBJS-y += cmd_bootm.o
COBJS-y += cmd_boot.o
COBJS-y += cmd_echo.o
COBJS-y += cmd_elf.o
COBJS-y += cmd_flash.o
COBJS-y += cmd_help.o
COBJS-y += cmd_mem.o
COBJS-y += cmd_custom.o
COBJS-y += cmd_net.o
COBJS-y += cmd_nvedit.o
COBJS-y += cmd_itest.o
COBJS-y += cmd_load.o
COBJS-y += cmd_qcaclk.o
COBJS-y += cmd_qcagpio.o
COBJS-y += command.o
COBJS-y += console.o
COBJS-y += devices.o
COBJS-y += dlmalloc.o
COBJS-y += environment.o
COBJS-y += env_common.o
COBJS-y += env_nowhere.o
COBJS-y += exports.o
COBJS-y += flash.o
COBJS-y += lists.o
COBJS-y += env_flash.o
COBJS-y += hush.o
COBJS-y += xyzModem.o
COBJS-y += crc16.o
COBJS-y += s_record.o

COBJS	:= $(COBJS-y)
SRCS	:= $(AOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(AOBJS) $(COBJS))

CPPFLAGS += -I..

all:	$(LIB) $(AOBJS)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(obj)environment.o: $(src)environment.c $(obj)../tools/envcrc
	$(CC) $(AFLAGS) -Wa,--no-warn \
		-DENV_CRC=$(shell $(obj)../tools/envcrc) \
		-c -o $@ $(src)environment.c

$(obj)../tools/envcrc:
	$(MAKE) -C ../tools

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
