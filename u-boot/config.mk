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
PLATFORM_LDFLAGS =

#
# When cross-compiling on NetBSD, we have to define __PPC__ or else we
# will pick up a va_list declaration that is incompatible with the
# actual argument lists emitted by the compiler.
#
# [Tested on NetBSD/i386 1.5 + cross-powerpc-netbsd-1.3]

ifeq ($(ARCH),ppc)
ifeq ($(CROSS_COMPILE),powerpc-netbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
ifeq ($(CROSS_COMPILE),powerpc-openbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
endif

ifeq ($(ARCH),arm)
ifeq ($(CROSS_COMPILE),powerpc-netbsd-)
PLATFORM_CPPFLAGS+= -D__ARM__
endif
ifeq ($(CROSS_COMPILE),powerpc-openbsd-)
PLATFORM_CPPFLAGS+= -D__ARM__
endif
endif

ifeq ($(ARCH),blackfin)
PLATFORM_CPPFLAGS+= -D__BLACKFIN__ -mno-underscore
endif

ifdef	ARCH
sinclude $(TOPDIR)/$(ARCH)_config.mk	# include architecture dependend rules
endif
ifdef	CPU
sinclude $(TOPDIR)/cpu/$(CPU)/config.mk	# include  CPU	specific rules
endif
ifdef	SOC
sinclude $(TOPDIR)/cpu/$(CPU)/$(SOC)/config.mk	# include  SoC	specific rules
endif
ifdef	VENDOR
BOARDDIR = $(VENDOR)/$(BOARD)
else
BOARDDIR = $(BOARD)
endif
ifdef	BOARD
sinclude $(TOPDIR)/board/$(BOARDDIR)/config.mk	# include board specific rules
endif

#########################################################################

CONFIG_SHELL	:= $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
		    else if [ -x /bin/bash ]; then echo /bin/bash; \
		    else echo sh; fi ; fi)

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
HOSTCC		= cc
else
HOSTCC		= gcc
endif
HOSTCFLAGS	= -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer
HOSTSTRIP	= strip

COMPRESS    = lzma
#########################################################################
#
# Option checker (courtesy linux kernel) to ensure
# only supported compiler options are used
#
cc-option = $(shell if $(CC) $(CFLAGS) $(1) -S -o /dev/null -xc /dev/null \
		> /dev/null 2>&1; then echo "$(1)"; else echo "$(2)"; fi ;)

#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB

.depend : CC = @$(CROSS_COMPILE)gcc

RELFLAGS= $(PLATFORM_RELFLAGS)
OPTFLAGS= -O
ifndef LDSCRIPT
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds
endif
OBJCFLAGS += --gap-fill=0xff

LDSCRIPT_BOOTSTRAP := $(TOPDIR)/board/$(BOARDDIR)/u-boot-bootstrap.lds

gccincdir := $(shell $(CC) -print-file-name=include)

CPPFLAGS := $(DBGFLAGS) $(OPTFLAGS) $(RELFLAGS)		\
	-D__KERNEL__ -DTEXT_BASE=$(TEXT_BASE)		\
	-I$(TOPDIR)/include				\
	-fno-builtin -ffreestanding -nostdinc -isystem	\
	$(gccincdir) -pipe $(PLATFORM_CPPFLAGS)

ifdef BUILD_TAG
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes \
	-DBUILD_TAG='"$(BUILD_TAG)"'
else
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes
ifdef COMPRESSED_UBOOT
CFLAGS += -DCOMPRESSED_UBOOT=1
endif

ifeq ($(BUILD_OPTIMIZED),y)
CFLAGS += -Os -funit-at-a-time -mips32r2 -mtune=mips32r2
endif
endif

ifeq ($(BUILD_TYPE),jffs2)
CFLAGS += -DROOTFS=1
else
ifeq ($(BUILD_TYPE),squashfs)
CFLAGS += -DROOTFS=2
endif
endif

# avoid trigraph warnings while parsing pci.h (produced by NIOS gcc-2.9)
# this option have to be placed behind -Wall -- that's why it is here
ifeq ($(ARCH),nios)
ifeq ($(findstring 2.9,$(shell $(CC) --version)),2.9)
CFLAGS := $(CPPFLAGS) -Wall -Wno-trigraphs
endif
endif

ifeq ($(BUILD_TYPE),jffs2)
CFLAGS += -DROOTFS=1
else
ifeq ($(BUILD_TYPE),squashfs)
CFLAGS += -DROOTFS=2
endif
endif

AFLAGS_DEBUG := -Wa,-gstabs

AFLAGS := $(AFLAGS_DEBUG) -D__ASSEMBLY__ $(CPPFLAGS)
ifdef COMPRESSED_UBOOT
AFLAGS += -DCOMPRESSED_UBOOT=1
endif

LDFLAGS += -Bstatic -T $(LDSCRIPT) -Ttext $(TEXT_BASE) $(PLATFORM_LDFLAGS)

ifdef COMPRESSED_UBOOT
LDFLAGS_BOOTSTRAP += -Bstatic -T $(LDSCRIPT_BOOTSTRAP) -Ttext $(BOOTSTRAP_TEXT_BASE) $(PLATFORM_LDFLAGS)
endif

# Location of a usable BFD library, where we define "usable" as
# "built for ${HOST}, supports ${TARGET}".  Sensible values are
# - When cross-compiling: the root of the cross-environment
# - Linux/ppc (native): /usr
# - NetBSD/ppc (native): you lose ... (must extract these from the
#   binutils build directory, plus the native and U-Boot include
#   files don't like each other)
#
# So far, this is used only by tools/gdb/Makefile.

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
BFD_ROOT_DIR =		/usr/local/tools
else
ifeq ($(HOSTARCH),$(ARCH))
# native
BFD_ROOT_DIR =		/usr
else
#BFD_ROOT_DIR =		/LinuxPPC/CDK		# Linux/i386
#BFD_ROOT_DIR =		/usr/pkg/cross		# NetBSD/i386
BFD_ROOT_DIR =		/opt/powerpc
endif
endif

ifeq ($(PCI_CLOCK),PCI_66M)
CFLAGS := $(CFLAGS) -DPCI_66M
endif

#CFLAGS += $(UBOOT_GCC_4_3_3_EXTRA_CFLAGS) -g
CFLAGS += $(UBOOT_GCC_4_3_3_EXTRA_CFLAGS)

#########################################################################

export	CONFIG_SHELL HPATH HOSTCC HOSTCFLAGS CROSS_COMPILE \
	AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP \
	MAKE
export	TEXT_BASE PLATFORM_CPPFLAGS PLATFORM_RELFLAGS CPPFLAGS CFLAGS AFLAGS

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
