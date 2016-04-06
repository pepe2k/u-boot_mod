include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).a

OBJS = $(BOARD).o ../common/spi_flash.o ../common/ar7240_s26_phy.o ../common/common.o

$(LIB):	.depend $(OBJS) $(SOBJS)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(SOBJS:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(SOBJS:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
