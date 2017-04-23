#
# (C) Copyright 2000
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#########################################################################

# clean the slate ...
PLATFORM_RELFLAGS =
PLATFORM_CPPFLAGS =
PLATFORM_LDFLAGS  =

# include architecture dependend rules
ifdef ARCH
  sinclude $(TOPDIR)/$(ARCH)_config.mk
endif

# include CPU specific rules
ifdef CPU
  sinclude $(TOPDIR)/cpu/$(CPU)/config.mk
endif

# include SoC specific rules
ifdef SOC
  sinclude $(TOPDIR)/cpu/$(CPU)/$(SOC)/config.mk
endif

# include vendor/board specific rules
ifdef VENDOR
  BOARDDIR = $(VENDOR)/$(BOARD)
else
  BOARDDIR = $(BOARD)
endif

ifdef BOARD
  sinclude $(TOPDIR)/board/$(BOARDDIR)/config.mk
endif

#########################################################################

CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH;          \
			else if [ -x /bin/bash ]; then echo /bin/bash; \
			else echo sh; fi; fi)

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
  HOSTCC = cc
else
  HOSTCC = gcc
endif

HOSTCFLAGS = -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer
HOSTSTRIP  = strip

#########################################################################

# Include the make variables (CC, etc...)
AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CC) -E
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm
STRIP   = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB  = $(CROSS_COMPILE)RANLIB

.depend : CC = @$(CROSS_COMPILE)gcc

RELFLAGS = $(PLATFORM_RELFLAGS)
OPTFLAGS = -O

ifndef LDSCRIPT
  LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds
endif
LDFLAGS += -Bstatic -T $(LDSCRIPT) -Ttext $(TEXT_BASE) $(PLATFORM_LDFLAGS)

ifdef COMPRESSED_UBOOT
  ifndef LDSCRIPT_BOOTSTRAP
    LDSCRIPT_BOOTSTRAP := $(TOPDIR)/board/$(BOARDDIR)/u-boot-bootstrap.lds
  endif
  LDFLAGS_BOOTSTRAP := -Bstatic -T $(LDSCRIPT_BOOTSTRAP)
  LDFLAGS_BOOTSTRAP += -Ttext $(BOOTSTRAP_TEXT_BASE) $(PLATFORM_LDFLAGS)
endif

OBJCFLAGS += --gap-fill=0xff

gccincdir := $(shell $(CC) -print-file-name=include)

CPPFLAGS := $(DBGFLAGS) $(OPTFLAGS) $(RELFLAGS)            \
	    -D__KERNEL__ -DTEXT_BASE=$(TEXT_BASE)          \
	    -I$(TOPDIR)/include                            \
	    -fno-builtin -ffreestanding -nostdinc -isystem \
	    $(gccincdir) -pipe $(PLATFORM_CPPFLAGS)

CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes

ifdef COMPRESSED_UBOOT
  CFLAGS += -DCOMPRESSED_UBOOT=1
endif

ifeq ($(BUILD_OPTIMIZED),y)
  CFLAGS += -Os -fno-reorder-functions -fno-delete-null-pointer-checks
  CPPFLAGS += -Os -fno-reorder-functions -fno-delete-null-pointer-checks
endif

AFLAGS_DEBUG :=
AFLAGS := $(AFLAGS_DEBUG) -D__ASSEMBLY__ $(CPPFLAGS)

ifdef COMPRESSED_UBOOT
  AFLAGS += -DCOMPRESSED_UBOOT=1
endif

#########################################################################

export AFLAGS AR AS CC CFLAGS CONFIG_SHELL CPP CPPFLAGS CROSS_COMPILE HOSTCC \
       HOSTCFLAGS HPATH LD MAKE NM OBJCOPY OBJDUMP PLATFORM_CPPFLAGS         \
       PLATFORM_RELFLAGS STRIP TEXT_BASE

ifeq ($(V),1)
  Q =
else
  Q = @
endif

export quiet Q V

#########################################################################

%.s:	%.S
ifneq ($(V),1)
	@echo [CPP] $(CURDIR)/$<
endif
	$(Q)$(CPP) $(AFLAGS) -o $@ $(CURDIR)/$<

%.o:	%.S
ifneq ($(V),1)
	@echo [CC] $(CURDIR)/$<
endif
	$(Q)$(CC) $(AFLAGS) -c -o $@ $(CURDIR)/$<

%.o:	%.c
ifneq ($(V),1)
	@echo [CC] $(CURDIR)/$<
endif
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

#########################################################################
