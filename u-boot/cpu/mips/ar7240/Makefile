include $(TOPDIR)/config.mk

LIB	= lib$(SOC).a

START	=
#OBJS	= ar7240_serial.o ag7240.o ar7240_flash.o meminit.o

OBJS	= meminit.o 

ifeq ($(BOARD), ap121)
OBJS	+= hornet_serial.o
SOBJS	+= hornet_ddr_init.o
else
OBJS	+= ar7240_serial.o
endif

ifeq ($(BOARD), db12x)
OBJS    += ag934x.o
else
OBJS    += ag7240.o
endif

SOBJS	+= 

all:	.depend $(START) $(LIB)

$(LIB):	$(OBJS) $(SOBJS) $(OBJS-0)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(START:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(START:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
