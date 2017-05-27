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

MIPSFLAGS := -fno-schedule-insns -fno-schedule-insns2
MIPSFLAGS += -mips32r2 -march=mips32r2 -mtune=34kc

PLATFORM_CPPFLAGS += -G 0 -mabicalls -fpic -msoft-float
PLATFORM_CPPFLAGS += $(MIPSFLAGS)

PLATFORM_LDFLAGS += -G 0 -static -n -nostdlib
