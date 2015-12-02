include $(TOPDIR)/config.mk

LIB	= lib$(SOC).a

START	=
OBJS	=
SOBJS	=

OBJS	+= meminit.o
OBJS	+= qca_common.o
OBJS	+= qca_clocks.o
OBJS	+= qca_sf.o
SOBJS	+= qca_gpio_init.o

ifeq ($(BOARD), ap121)
	OBJS	+= qca_hs_uart.o
	OBJS	+= ag7240.o
	SOBJS	+= ar933x_ddr_init.o
	SOBJS	+= ar933x_pll_init.o
else
	OBJS	+= qca_ls_uart.o
endif

ifeq ($(BOARD), db12x)
	OBJS	+= ag934x.o
	SOBJS	+= ar934x_pll_init.o
endif

all:	.depend $(START) $(LIB)

$(LIB):	$(OBJS) $(SOBJS) $(OBJS-0)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(START:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(START:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
