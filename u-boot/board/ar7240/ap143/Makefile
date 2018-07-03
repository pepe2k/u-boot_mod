include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

OBJS	= $(BOARD).o ../common/spi_flash.o ../common/common.o ../common/qca-eth-953x.o

ifeq ($(ETH_CONFIG), _s27)
OBJS	+= ../common/athr_s27_phy.o
endif

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
