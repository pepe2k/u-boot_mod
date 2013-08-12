export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-linux-gnu-

# boot delay (time to autostart boot command)
export CONFIG_BOOTDELAY=1

mr3020:	export UBOOT_FILE_NAME=uboot_for_tl-mr3020
mr3020:	export MAX_UBOOT_SIZE=64
mr3020:	export COMPRESSED_UBOOT=1
mr3020:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3020_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size
	
wr703n:	export UBOOT_FILE_NAME=uboot_for_tl-wr703n
wr703n:	export MAX_UBOOT_SIZE=64
wr703n:	export COMPRESSED_UBOOT=1
wr703n:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr703n_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

wr720n_v3_CH:	export UBOOT_FILE_NAME=uboot_for_tl-wr720n_v3_CH
wr720n_v3_CH:	export MAX_UBOOT_SIZE=64
wr720n_v3_CH:	export COMPRESSED_UBOOT=1
wr720n_v3_CH:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr720n_v3_CH_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

wr710n:	export UBOOT_FILE_NAME=uboot_for_tl-wr710n
wr710n:	export MAX_UBOOT_SIZE=64
wr710n:	export COMPRESSED_UBOOT=1
wr710n:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr710n_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

mr3040:	export UBOOT_FILE_NAME=uboot_for_tl-mr3040
mr3040:	export MAX_UBOOT_SIZE=64
mr3040:	export COMPRESSED_UBOOT=1
mr3040:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3040_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

mr10u:	export UBOOT_FILE_NAME=uboot_for_tl-mr10u
mr10u:	export MAX_UBOOT_SIZE=64
mr10u:	export COMPRESSED_UBOOT=1
mr10u:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr10u_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

wr740n_v4:	export UBOOT_FILE_NAME=uboot_for_tl-wr740n_v4
wr740n_v4:	export MAX_UBOOT_SIZE=64
wr740n_v4:	export COMPRESSED_UBOOT=1
wr740n_v4:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr740n_v4_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

mr3220_v2:	export UBOOT_FILE_NAME=uboot_for_tl-mr3220_v2
mr3220_v2:	export MAX_UBOOT_SIZE=64
mr3220_v2:	export COMPRESSED_UBOOT=1
mr3220_v2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3220_v2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

wdr3600_43x0:	export UBOOT_FILE_NAME=uboot_for_tl-wdr3600-43x0
wdr3600_43x0:	export MAX_UBOOT_SIZE=64
wdr3600_43x0:	export COMPRESSED_UBOOT=1
wdr3600_43x0:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) db12x_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

carambola2:	export UBOOT_FILE_NAME=uboot_for_carambola2
carambola2:	export MAX_UBOOT_SIZE=256
carambola2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) carambola2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@cp $(BUILD_TOPDIR)/u-boot/u-boot.bin $(BUILD_TOPDIR)/bin/temp.bin
	@make show_size

show_size:
	@echo -e "\n======= Preparing $(MAX_UBOOT_SIZE)KB file filled with 0xFF... ======="
	@`tr "\000" "\377" < /dev/zero | dd ibs=1k count=$(MAX_UBOOT_SIZE) of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).bin`
	@echo -e "\n======= Copying U-Boot image... ======="
	@`dd if=$(BUILD_TOPDIR)/bin/temp.bin of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).bin conv=notrunc`
	@`rm $(BUILD_TOPDIR)/bin/temp.bin`
	@echo -e "\n======= U-Boot image ready, size:" `wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).bin`" bytes =======\n"
	@`md5sum $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).bin | awk '{print $$1}' | tr -d '\n' > $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).md5`
	@`echo ' *'$(UBOOT_FILE_NAME).bin >> $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).md5`
	@if [ "`wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME).bin`" -gt "`echo '$(MAX_UBOOT_SIZE)*1024' | bc`" ]; then \
			echo -e "\n     **********************************"; \
            echo "     *   U-BOOT IMAGE SIZE TOO BIG!   *"; \
            echo -e "     **********************************\n"; \
    fi;

clean:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) clean
	@rm -f $(BUILD_TOPDIR)/bin/*

clean_all:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) distclean
	@rm -f $(BUILD_TOPDIR)/bin/*
