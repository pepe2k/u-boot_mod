include $(TOPDIR)/config.mk

LIB	= lib$(SOC).a

START	=

OBJS	=  meminit.o
OBJS	+= qca_common.o
OBJS	+= qca_clocks.o

ifeq ($(BOARD), ap121)
	OBJS	+= qca_hs_uart.o
	SOBJS	+= hornet_ddr_init.o
else
	OBJS	+= qca_ls_uart.o
endif

ifeq ($(BOARD), db12x)
	OBJS	+= ag934x.o
else
	OBJS	+= ag7240.o
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
