include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

OBJS	=  qca_common.o
OBJS	+= qca_clocks.o
OBJS	+= qca_sf.o
OBJS	+= qca_dram.o
OBJS	+= qca_pci.o
OBJS	+= qca_usb.o
OBJS	+= qca_gpio_init.o

ifeq ($(BOARD), ap121)
	OBJS	+= qca_hs_uart.o
	OBJS	+= ag7240.o
	OBJS	+= ar933x_pll_init.o
else
	OBJS	+= qca_ls_uart.o
endif

ifeq ($(BOARD), db12x)
	OBJS	+= ag934x.o
	OBJS	+= qca95xx_pll_init.o
endif

ifeq ($(BOARD), ap143)
	OBJS	+= qca95xx_pll_init.o
endif

ifeq ($(BOARD), ap152)
	OBJS	+= qca_dram956x.o
	OBJS	+= qca956x_tap.o
	OBJS	+= qca956x_pll_init.o
else

endif

OBJS	:= $(addprefix $(obj),$(OBJS))

all:	$(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
