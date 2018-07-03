#########################################################################
BOOTSTRAPOBJ := $(addprefix $(obj),$(BOOTSTRAPOBJ-y))
OBJS	:= $(addprefix $(obj),$(OBJS-y))

$(obj).built-in.o: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -r -o $@

$(obj).bootstrap-built-in.o: $(BOOTSTRAPOBJ)
	$(LD) $(LDFLAGS) $(BOOTSTRAPOBJ) -r -o $@

$(obj).built-in.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(obj).bootstrap-built-in.a: $(BOOTSTRAPOBJ)
	$(AR) $(ARFLAGS) $@ $(BOOTSTRAPOBJ)

$(obj).built-in.lst: $(OBJS)
	echo $(OBJS) > $@

$(obj).bootstrap-built-in.lst: $(BOOTSTRAPOBJ)
	echo $(BOOTSTRAPOBJ) > $@

-include $(OBJS:.o=.d) $(BOOTSTRAPOBJ:.o=.d)
#########################################################################
