#
# Copyright (C) 2000-2003 Wolfgang Denk, DENX Software Engineering, wd@denx.de
#
# SPDX-License-Identifier: GPL-2.0
#

BIN_FILES	= mkimage$(SFX) envcrc$(SFX)
OBJ_LINKS	= environment.o mkimage.o crc32.o envcrc.o

#-------------------------------------------------------------------------

HOSTARCH := $(shell uname -m | \
	sed -e s/i.86/i386/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/powerpc/ppc/ \
	    -e s/Power\ Macintosh/ppc/ \
	    -e s/macppc/ppc/)

HOSTOS := $(shell uname -s | tr A-Z a-z | \
	sed -e 's/\(cygwin\).*/cygwin/')

TOOLSUBDIRS =

#
# Mac OS X / Darwin's C preprocessor is Apple specific.  It
# generates numerous errors and warnings.  We want to bypass it
# and use GNU C's cpp.  To do this we pass the -traditional-cpp
# option to the compiler.  Note that the -traditional-cpp flag
# DOES NOT have the same semantics as GNU C's flag, all it does
# is invoke the GNU preprocessor in stock ANSI/ISO C fashion.
#
# Apple's linker is similar, thanks to the new 2 stage linking
# multiple symbol definitions are treated as errors, hence the
# -multiply_defined suppress option to turn off this error.
#
ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
HOST_CFLAGS = -traditional-cpp -Wall
HOST_LDFLAGS =-multiply_defined suppress
HOST_ENVIRO_CFLAGS =

else
ifeq ($(HOSTOS)-$(HOSTARCH),netbsd-ppc)
HOST_CFLAGS = -Wall -pedantic
HOST_LDFLAGS =
HOST_ENVIRO_CFLAGS =

#
# Everyone else
#
else
HOST_CFLAGS = -Wall -pedantic
HOST_LDFLAGS =
HOST_ENVIRO_CFLAGS =
endif
endif

#
# Cygwin needs .exe files :-(
#
ifeq ($(HOSTOS),cygwin)
SFX = .exe
HOST_CFLAGS += -ansi
else
SFX =
endif

#
# Include this after HOSTOS HOSTARCH check
# so that we can act intelligently.
#
include $(TOPDIR)/config.mk

# now $(obj) is defined
SRCS	:= $(addprefix $(obj),$(OBJ_LINKS:.o=.c)) $(OBJ_FILES:.o=.c)
BINS	:= $(addprefix $(obj),$(BIN_FILES))

#
# Use native tools and options
#
CPPFLAGS   = -I$(TOPDIR)/include \
		-I$(OBJTREE)/include2 \
		-I$(OBJTREE)/include \
		-DTEXT_BASE=$(TEXT_BASE) -DUSE_HOSTCC
CFLAGS     = $(HOST_CFLAGS) $(CPPFLAGS) -O2

# No -pedantic switch to avoid libfdt compilation warnings
FIT_CFLAGS = -Wall $(CPPFLAGS) -O

AFLAGS	   = -D__ASSEMBLY__ $(CPPFLAGS)
CC	   = $(HOSTCC)
STRIP	   = $(HOSTSTRIP)
MAKEDEPEND = makedepend

all:	$(BINS)

$(obj)envcrc$(SFX):	$(obj)envcrc.o $(obj)crc32.o $(obj)environment.o
		$(CC) -MMD $(CFLAGS) -o $@ $^

$(obj)mkimage$(SFX):	$(obj)mkimage.o $(obj)crc32.o
		$(CC) $(CFLAGS) $(HOST_LDFLAGS) -o $@ $^
		$(STRIP) $@

$(obj)envcrc.o:	$(src)envcrc.c
		$(CC) -MMD -g $(CFLAGS) -c -o $@ $<

$(obj)crc32.o:	$(obj)crc32.c
		$(CC) -MMD -g $(CFLAGS) -c -o $@ $<

$(obj)mkimage.o:	$(src)mkimage.c
		$(CC) -MMD -g $(FIT_CFLAGS) -c -o $@ $<


$(obj)environment.c:
		@rm -f $(obj)environment.c
		ln -s $(src)../common/environment.c $(obj)environment.c

$(obj)environment.o:	$(obj)environment.c
		$(CC) -MMD -g $(HOST_ENVIRO_CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(obj)crc32.c:
		@rm -f $(obj)crc32.c
		ln -s $(src)../lib_generic/crc32.c $(obj)crc32.c

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
