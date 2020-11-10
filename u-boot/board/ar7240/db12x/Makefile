include $(TOPDIR)/config.mk

BOOTSTRAPOBJ-y += $(BOARD).o

OBJS-y += $(BOARD).o
OBJS-y += ../common/spi_flash.o
OBJS-y += ../common/common.o

ifeq ($(ETH_CONFIG), _s17)
	OBJS-y += ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
	OBJS-y += ../common/athrs27_phy.o
endif

include $(TOPDIR)/end.mk