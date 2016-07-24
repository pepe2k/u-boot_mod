SHELL = bash

HOSTARCH := $(shell uname -m | \
	sed -e s/i.86/i386/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/powerpc/ppc/ \
	    -e s/macppc/ppc/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

ifneq ($(HOSTOS), darwin) 
ifneq ($(HOSTOS), linux)
$(error Error! Unsupported Host Operating System $(HOSTOS) - $(HOSTARCH)!)
endif
endif

export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

# -------------------------------------------------------------------------
# Place the location to your toolchain here, for example: -
#
# export TOOLCHAIN_DIR:=$(BUILD_TOPDIR)/../tools/$(HOSTOS)/toolchain-mips_34kc_gcc-5.3.0_musl-1.1.14
# export PATH:=$(TOOLCHAIN_DIR)/bin:$(PATH)
# -------------------------------------------------------------------------

ifndef CROSS_COMPILE
CROSS_COMPILE = mips-openwrt-linux-musl-
endif
export CROSS_COMPILE

export MAKECMD=make --silent --no-print-directory ARCH=mips

# boot delay (time to autostart boot command)
export CONFIG_BOOTDELAY=1

# uncomment following line, to disable output in U-Boot console
#export DISABLE_CONSOLE_OUTPUT=1

# uncomment following line, to build RAM version images (without low level initialization)
#export CONFIG_SKIP_LOWLEVEL_INIT=1

tplink_mr3020:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr3020
tplink_mr3020:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr3020:	export COMPRESSED_UBOOT=1
endif
tplink_mr3020:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3020_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr703n:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr703n
tplink_wr703n:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr703n:	export COMPRESSED_UBOOT=1
endif
tplink_wr703n:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr703n_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr720n_v3_CN:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr720n_v3_CN
tplink_wr720n_v3_CN:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr720n_v3_CN:	export COMPRESSED_UBOOT=1
endif
tplink_wr720n_v3_CN:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr720n_v3_CN_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr710n:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr710n
tplink_wr710n:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr710n:	export COMPRESSED_UBOOT=1
endif
tplink_wr710n:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr710n_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_mr3040:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr3040
tplink_mr3040:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr3040:	export COMPRESSED_UBOOT=1
endif
tplink_mr3040:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3040_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_mr10u:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr10u
tplink_mr10u:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr10u:	export COMPRESSED_UBOOT=1
endif
tplink_mr10u:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr10u_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_mr13u:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr13u
tplink_mr13u:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr13u:	export COMPRESSED_UBOOT=1
endif
tplink_mr13u:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr13u_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr740n_v4:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr740n_v4
tplink_wr740n_v4:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr740n_v4:	export COMPRESSED_UBOOT=1
endif
tplink_wr740n_v4:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr740n_v4_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_mr3220_v2:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr3220_v2
tplink_mr3220_v2:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr3220_v2:	export COMPRESSED_UBOOT=1
endif
tplink_mr3220_v2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3220_v2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wdr3600_43x0:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wdr3600-43x0
tplink_wdr3600_43x0:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wdr3600_43x0:	export COMPRESSED_UBOOT=1
endif
tplink_wdr3600_43x0:	export ETH_CONFIG=_s17
tplink_wdr3600_43x0:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wdr3600_43x0_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wdr3500:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wdr3500
tplink_wdr3500:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wdr3500:	export COMPRESSED_UBOOT=1
endif
tplink_wdr3500:	export ETH_CONFIG=_s27
tplink_wdr3500:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wdr3500_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_mr3420_v2:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-mr3420_v2
tplink_mr3420_v2:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_mr3420_v2:	export COMPRESSED_UBOOT=1
endif
tplink_mr3420_v2:	export ETH_CONFIG=_s27
tplink_mr3420_v2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) mr3420_v2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr841n_v8:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr841n_v8
tplink_wr841n_v8:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr841n_v8:	export COMPRESSED_UBOOT=1
endif
tplink_wr841n_v8:	export ETH_CONFIG=_s27
tplink_wr841n_v8:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr841n_v8_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr841n_v9:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr841n_v9
tplink_wr841n_v9:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr841n_v9:	export COMPRESSED_UBOOT=1
endif
tplink_wr841n_v9:	export ETH_CONFIG=_s27
tplink_wr841n_v9:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr841n_v9_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wa830re_v2_wa801nd_v2:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wa830re_v2_tl-wa801nd_v2
tplink_wa830re_v2_wa801nd_v2:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wa830re_v2_wa801nd_v2:	export COMPRESSED_UBOOT=1
endif
tplink_wa830re_v2_wa801nd_v2:	export ETH_CONFIG=_s27
tplink_wa830re_v2_wa801nd_v2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wa830re_v2_wa801nd_v2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr820n_CN:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr820n_CN
tplink_wr820n_CN:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr820n_CN:	export COMPRESSED_UBOOT=1
endif
tplink_wr820n_CN:	export ETH_CONFIG=_s27
tplink_wr820n_CN:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr820n_CN_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

tplink_wr802n:	export UBOOT_FILE_NAME=uboot_for_tp-link_tl-wr802n
tplink_wr802n:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
tplink_wr802n:	export COMPRESSED_UBOOT=1
endif
tplink_wr802n:	export ETH_CONFIG=_s27
tplink_wr802n:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) wr802n_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

dlink_dir505:	export UBOOT_FILE_NAME=uboot_for_d-link_dir-505
dlink_dir505:	export CONFIG_MAX_UBOOT_SIZE_KB=64
ifndef CONFIG_SKIP_LOWLEVEL_INIT
dlink_dir505:	export COMPRESSED_UBOOT=1
endif
dlink_dir505:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) dir505_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

gs-oolite_v1_dev:	export UBOOT_FILE_NAME=uboot_for_gs-oolite_v1_dev
gs-oolite_v1_dev:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
gs-oolite_v1_dev:	export COMPRESSED_UBOOT=1
endif
gs-oolite_v1_dev:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) gs_oolite_v1_dev_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

8devices_carambola2:	export UBOOT_FILE_NAME=uboot_for_8devices_carambola2
8devices_carambola2:	export CONFIG_MAX_UBOOT_SIZE_KB=256
8devices_carambola2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) carambola2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

dragino_v2_ms14:	export UBOOT_FILE_NAME=uboot_for_dragino_v2_ms14
dragino_v2_ms14:	export CONFIG_MAX_UBOOT_SIZE_KB=192
dragino_v2_ms14:	export DEVICE_VENDOR=dragino
dragino_v2_ms14:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) dragino_v2_ms14_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

black_swift_board:	export UBOOT_FILE_NAME=uboot_for_black_swift_board
black_swift_board:	export CONFIG_MAX_UBOOT_SIZE_KB=128
black_swift_board:	export COMPRESSED_UBOOT=1
black_swift_board:	export DEVICE_VENDOR=SE
black_swift_board:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) black_swift_board_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

villagetelco_mp2:	export UBOOT_FILE_NAME=uboot_for_villagetelco_mp2
villagetelco_mp2:	export CONFIG_MAX_UBOOT_SIZE_KB=192
villagetelco_mp2:	export DEVICE_VENDOR=villagetelco
villagetelco_mp2:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) villagetelco_mp2_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

gl-inet:	export UBOOT_FILE_NAME=uboot_for_gl-inet
gl-inet:	export CONFIG_MAX_UBOOT_SIZE_KB=123
ifndef CONFIG_SKIP_LOWLEVEL_INIT
gl-inet:	export COMPRESSED_UBOOT=1
endif
gl-inet:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) gl-inet_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

wallys_dr531:	export UBOOT_FILE_NAME=uboot_for_wallys_dr531
wallys_dr531:	export CONFIG_MAX_UBOOT_SIZE_KB=192
ifndef CONFIG_SKIP_LOWLEVEL_INIT
wallys_dr531:	export COMPRESSED_UBOOT=1
endif
wallys_dr531:	export ETH_CONFIG=_s27
wallys_dr531:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) dr531_config
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) ENDIANNESS=-EB V=1 all
	@make --no-print-directory show_size

ifdef CONFIG_SKIP_LOWLEVEL_INIT
  ifdef DISABLE_CONSOLE_OUTPUT
show_size:	export UBOOT_FILE_NAME_SUFFIX=__SILENT-CONSOLE__RAM
  else
show_size:	export UBOOT_FILE_NAME_SUFFIX=__RAM
  endif
else
  ifdef DISABLE_CONSOLE_OUTPUT
show_size:	export UBOOT_FILE_NAME_SUFFIX=__SILENT-CONSOLE
  endif
endif
show_size:
ifdef COMPRESSED_UBOOT
	@cp $(BUILD_TOPDIR)/u-boot/tuboot.bin $(BUILD_TOPDIR)/bin/temp.bin
else
	@cp $(BUILD_TOPDIR)/u-boot/u-boot.bin $(BUILD_TOPDIR)/bin/temp.bin
endif
	@echo -ne "\e[32m"
ifndef CONFIG_SKIP_LOWLEVEL_INIT
	@echo "> Preparing $(CONFIG_MAX_UBOOT_SIZE_KB)KB file filled with 0xFF..."
	@`tr "\000" "\377" < /dev/zero | dd ibs=1k count=$(CONFIG_MAX_UBOOT_SIZE_KB) of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin 2> /dev/null`
	@echo "> Copying U-Boot image..."
	@`dd if=$(BUILD_TOPDIR)/bin/temp.bin of=$(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin conv=notrunc 2> /dev/null`
	@`rm $(BUILD_TOPDIR)/bin/temp.bin`
else
	@echo "> Copying U-Boot image..."
	@`mv $(BUILD_TOPDIR)/bin/temp.bin $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`
endif
	@echo "> U-Boot image ready, size:" `wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`" bytes"
	@`md5sum $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin | awk '{print $$1}' | tr -d '\n' > $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).md5`
	@`echo ' *'$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin >> $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).md5`
# Do not check image size for RAM version
ifndef CONFIG_SKIP_LOWLEVEL_INIT
	@if [ "`wc -c < $(BUILD_TOPDIR)/bin/$(UBOOT_FILE_NAME)$(UBOOT_FILE_NAME_SUFFIX).bin`" -gt "`echo '$(CONFIG_MAX_UBOOT_SIZE_KB)*1024' | bc`" ]; then \
			echo -e "\e[31m\n**************************************************"; \
			echo "*     WARNING: U-BOOT IMAGE SIZE IS TOO BIG!     *"; \
			echo -e "**************************************************"; \
	fi;
endif
	@echo -ne "\e[0m"

clean:
	@cd $(BUILD_TOPDIR)/u-boot/ && $(MAKECMD) --no-print-directory distclean
	@rm -f $(BUILD_TOPDIR)/u-boot/httpd/fsdata.c

clean_all:	clean
	@echo -e "\e[32m> Removing all binary images...\e[0m"
	@rm -f $(BUILD_TOPDIR)/bin/*.bin
	@rm -f $(BUILD_TOPDIR)/bin/*.md5
