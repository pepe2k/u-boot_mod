#
# Makefile for http stuff
#

include $(TOPDIR)/config.mk

# Suppress warnings when building with size optimization
CFLAGS += -fno-strict-aliasing

LIB   = $(obj)libhttpd.a

OBJS-y	:= uip.o
OBJS-y	+= uip_arch.o
OBJS-y  += uip_arp.o
OBJS-y  += httpd.o
OBJS-y  += fs.o

OBJS	:= $(addprefix $(obj),$(OBJS-y))

all: $(LIB)

fs.c:	$(obj)fsdata.c

$(obj)fsdata.c:
	./vendors/makefsdatac $(obj)fsdata.c $(DEVICE_VENDOR)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
