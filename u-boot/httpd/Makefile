#
# Makefile for http stuff
#

#include $(TOPDIR)/config.mk

CFLAGS += -I../include -I../httpd

LIB   = libhttpd.a

OBJS += uip.o uip_arch.o uip_arp.o httpd.o fs.o

all:  $(LIB)

$(LIB):  $(START) $(OBJS)
	   $(AR) crv $@ $(OBJS)


#%.o:
#	   $(CC) $(CFLAGS) -c $(<:.o=.c)

#########################################################################

.depend: Makefile $(OBJS:.o=.c)
	      $(CC) -M $(CFLAGS) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################

