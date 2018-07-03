include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

OBJS = $(BOARD).o ../common/spi_flash.o ../common/ar7240_s26_phy.o ../common/common.o

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

#########################################################################

-include $(OBJS:.o=.d)  $(SOBJS:.o=.d)

#########################################################################
