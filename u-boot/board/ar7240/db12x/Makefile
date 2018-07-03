include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

OBJS	= $(BOARD).o ../common/spi_flash.o ../common/common.o

ifeq ($(ETH_CONFIG), _s17)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
OBJS	+= ../common/athrs27_phy.o
endif

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
