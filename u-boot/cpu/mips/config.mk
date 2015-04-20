#
# (C) Copyright 2003
# Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
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
#v=$(shell \
mips-openwrt-linux-uclibc-as --version|grep "GNU assembler"|awk '{print $$3}'|awk -F . '{print $$2}')

v=22
MIPSFLAGS=$(shell \
if [ "$v" -lt "14" ]; then \
	echo "-mcpu=mips32"; \
else \
	echo "-mips32 -march=mips32 -mtune=mips32"; \
fi)

ifndef ENDIANNESS
ifneq (,$(findstring 4KCle,$(CROSS_COMPILE)))
ENDIANNESS = -EL
else
ENDIANNESS = -EB
endif
endif

#PLATFORM_CPPFLAGS      += -G 0 -mabicalls -fpic -g
PLATFORM_CPPFLAGS      += -G 0 -mabicalls -fpic
PLATFORM_CPPFLAGS      += -msoft-float
PLATFORM_LDFLAGS       += -G 0 -static -n -nostdlib
MIPSFLAGS += $(ENDIANNESS) -fno-schedule-insns -fno-schedule-insns2

PLATFORM_CPPFLAGS += $(MIPSFLAGS)
