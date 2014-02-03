#
# Makefile for http stuff
#

include $(TOPDIR)/config.mk

LIB   = libhttpd.a
OBJS += uip.o uip_arch.o uip_arp.o httpd.o fs.o

all:    $(LIB)

fs.c:   fsdata.c

fsdata.c:
	    ./vendors/makefsdatac $(DEVICE_VENDOR)

$(LIB): $(START) $(OBJS)
	    $(AR) crv $@ $(OBJS)

#########################################################################

.depend: Makefile $(OBJS:.o=.c)
	     $(CC) -M $(CFLAGS) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################

