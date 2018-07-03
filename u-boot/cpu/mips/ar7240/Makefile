include $(TOPDIR)/config.mk

OBJS-y +=  qca_common.o
OBJS-y += qca_clocks.o
OBJS-y += qca_sf.o
OBJS-y += qca_dram.o
OBJS-y += qca_pci.o
OBJS-y += qca_usb.o
OBJS-y += qca_gpio_init.o

ifeq ($(BOARD), ap121)
	OBJS-y += qca_hs_uart.o
	OBJS-y += ag7240.o
	OBJS-y += ar933x_pll_init.o
else
	OBJS-y += qca_ls_uart.o
endif

ifeq ($(BOARD), db12x)
	OBJS-y += ag934x.o
	OBJS-y += qca95xx_pll_init.o
endif

ifeq ($(BOARD), ap143)
	OBJS-y += qca95xx_pll_init.o
endif

ifeq ($(BOARD), ap152)
	OBJS-y += qca_dram956x.o
	OBJS-y += qca956x_tap.o
	OBJS-y += qca956x_pll_init.o
else

endif

include $(TOPDIR)/end.mk
