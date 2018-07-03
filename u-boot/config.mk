#
# Copyright (C) 2000-2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier: GPL-2.0
#

ifneq ($(OBJTREE),$(SRCTREE))
  ifeq ($(CURDIR),$(SRCTREE))
    dir :=
  else
    dir := $(subst $(SRCTREE)/,,$(CURDIR))
  endif
  obj := $(if $(dir),$(OBJTREE)/$(dir)/,$(OBJTREE)/)
  src := $(if $(dir),$(SRCTREE)/$(dir)/,$(SRCTREE)/)
  $(shell mkdir -p $(obj))
else
  obj :=
  src :=
endif

# clean the slate ...
PLATFORM_CPPFLAGS :=
PLATFORM_AFLAGS :=
PLATFORM_CFLAGS :=
PLATFORM_LDFLAGS :=

#########################################################################

CONFIG_SHELL	:= $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
                    else if [ -x /bin/bash ]; then echo /bin/bash; \
                    else echo sh; fi ; fi)

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
  HOSTCC		= cc
else
  HOSTCC		= gcc
endif
HOSTCFLAGS	:= -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer
HOSTSTRIP	= strip

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
AR	= $(CROSS_COMPILE)gcc-ar
NM	= $(CROSS_COMPILE)nm
LDR	= $(CROSS_COMPILE)ldr
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB

#########################################################################

# Load generated board configuration
-include $(OBJTREE)/include/autoconf.mk

ifdef	ARCH
  -include $(TOPDIR)/$(ARCH)_config.mk	# include architecture dependend rules
endif
ifdef	CPU
  -include $(TOPDIR)/cpu/$(CPU)/config.mk	# include  CPU	specific rules
endif
ifdef	SOC
  -include $(TOPDIR)/cpu/$(CPU)/$(SOC)/config.mk	# include  SoC	specific rules
endif
ifdef	VENDOR
  BOARDDIR = $(VENDOR)/$(BOARD)
else
  BOARDDIR = $(BOARD)
endif
ifdef	BOARD
  -include $(TOPDIR)/board/$(BOARDDIR)/config.mk	# include board specific rules
endif
#########################################################################

# User configurable FLAGS
CPPFLAGS	:=
AFLAGS		:=
CFLAGS		:= -Os -ggdb3 -Wall -Wextra -Wno-unused-parameter -Wstrict-prototypes $(cc-option,-Wshift-overflow=2) -ffunction-sections -flto=1 -flto-partition=1to1
LDFLAGS		:= -Wl,--gc-sections
ARFLAGS		:=
OBJCFLAGS	:=

ifneq ($(TEXT_BASE),)
  CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE)
endif

ifneq ($(OBJTREE),$(SRCTREE))
  CPPFLAGS += -I$(OBJTREE)/include2 -I$(OBJTREE)/include -I$(obj)
endif

# Mandatory FLAGS
CPPFLAGS	+= -D__KERNEL__ -nostdinc -I$(TOPDIR)/include -isystem $(shell $(CC) -print-file-name=include) $(PLATFORM_CPPFLAGS)
AFLAGS		+= -D__ASSEMBLY__ $(PLATFORM_AFLAGS)
CFLAGS		+= -fno-builtin -ffreestanding -pipe -fpic -fno-stack-protector $(PLATFORM_CFLAGS)
LDFLAGS		+= --static -nostdlib $(PLATFORM_LDFLAGS)
ARFLAGS		+= cr
OBJCFLAGS	+= --gap-fill=0xff

ifdef COMPRESSED_UBOOT
  CPPFLAGS += -DCOMPRESSED_UBOOT=1
endif

ifdef BUILD_TAG
  CPPFLAGS += -DBUILD_TAG='"$(BUILD_TAG)"'
endif

ifndef LDSCRIPT
  LDSCRIPT := $(TOPDIR)/cpu/$(CPU)/u-boot.lds
endif

LDFLAGS_UBOOT := $(LDFLAGS) -T $(LDSCRIPT)
ifneq ($(TEXT_BASE),)
  LDFLAGS_UBOOT += -Wl,-Ttext,$(TEXT_BASE)
endif

ifdef COMPRESSED_UBOOT
  ifndef LDSCRIPT_BOOTSTRAP
    LDSCRIPT_BOOTSTRAP := $(TOPDIR)/cpu/$(CPU)/u-boot-bootstrap.lds
  endif
  LDFLAGS_BOOTSTRAP := $(LDFLAGS) -fpic -T $(LDSCRIPT_BOOTSTRAP)
  ifneq ($(BOOTSTRAP_TEXT_BASE),)
    LDFLAGS_BOOTSTRAP += -Wl,-Ttext,$(BOOTSTRAP_TEXT_BASE)
  endif
endif


#########################################################################

$(obj)%.o:	%.S
	@mkdir -p $(dir $@)
	@echo "	[ASM]	$(CURDIR)/$<"
	$(CC) $(CPPFLAGS) $(AFLAGS) $(CFLAGS) -fno-lto -MMD -c -o $@ $<

$(obj)%.o:	%.c
	@mkdir -p $(dir $@)
	@echo "	[CC]	$(CURDIR)/$<"
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c -o $@ $<
