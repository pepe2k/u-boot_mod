include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).a

OBJS	= $(BOARD).o ../common/spi_flash.o ../common/common.o

ifeq ($(ETH_CONFIG), _s17)
OBJS	+= ../common/athrs17_phy.o
endif

ifeq ($(ETH_CONFIG), _s27)
OBJS	+= ../common/athrs27_phy.o
endif

$(LIB):	.depend $(OBJS) $(SOBJS)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(SOBJS:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(SOBJS:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
