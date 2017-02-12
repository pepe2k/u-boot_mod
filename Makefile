#
# Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
#
# SPDX-License-Identifier: GPL-2.0
#

SHELL = bash

HOSTARCH := $(shell uname -m |        \
	      sed -e s/i.86/x86_32/   \
		  -e s/sun4u/sparc64/ \
		  -e s/arm.*/arm/     \
		  -e s/sa110/arm/     \
		  -e s/powerpc/ppc/   \
		  -e s/macppc/ppc/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

ifneq ($(HOSTOS), darwin)
  ifneq ($(HOSTOS), linux)
    $(error Error! Unsupported host operating system/arch: "$(HOSTOS)-$(HOSTARCH)")
  endif
endif

export HOSTOS
export HOSTARCH
export BUILD_TOPDIR = $(PWD)
export STAGING_DIR  = $(BUILD_TOPDIR)/tmp
export SOURCE_DIR   = $(BUILD_TOPDIR)/u-boot
export BIN_DIR      = $(BUILD_TOPDIR)/bin
export SUB_MAKE_CMD = $(MAKE) --silent --no-print-directory \
                      ARCH=mips V=1 SHELL=$(SHELL)

# ==========================================================================
# You can override some default configuration options below or pass them on
# command line, for example:
# make ... IMG_SIZE=256 IMG_LZMA=0 CROSS_COMPILE=...

# Set to 1 if you want to build RAM-loadable image, without low level
# initialization of the hardware (PLL/clocks, DRAM):
# IMG_RAM =

# You can change limit of the image size in KB with below option (image will
# be filled up to the selected size with 0xFF):
# IMG_SIZE =

# If you don't want LZMA compressed image, set below option to 1 (by default
# images for all targets are LZMA compressed):
# IMG_LZMA =

# Define _absolute_ path to your toolchain directory, for example:
# export TOOLCHAIN_DIR:=/home/user/toolchain-mips_24kc_gcc-5.4.0_musl-1.1.15
# export PATH:=$(TOOLCHAIN_DIR)/bin:$(PATH)

ifndef CROSS_COMPILE
  CROSS_COMPILE = mips-openwrt-linux-musl-
endif
export CROSS_COMPILE

# ==========================================================================

# =======================
# CUSTOM HELPER FUNCTIONS
# =======================

define echo_green
  echo -e "\e[92m$(1)\e[0m"
endef

define echo_red
  echo -e "\e[91m$(1)\e[0m"
endef

define echo_blue
  echo -e "\e[96m$(1)\e[0m"
endef

# $(1): size
define img_size
$(if $(IMG_SIZE),$(strip $(IMG_SIZE)),$(strip $(1)))
endef

# $(1): value
define is_lzma
$(if $(IMG_LZMA),\
  $(if $(filter $(strip $(IMG_LZMA)),1),1,0),\
  $(if $(filter $(strip $(1)),1),1,0)\
)
endef

define git_branch
$(shell git symbolic-ref --short -q HEAD 2>/dev/null || echo "unknown")
endef

define git_hash
$(shell git rev-parse --short=8 -q HEAD 2>/dev/null || echo "unknown")
endef

define git_branch_hash
git_$(call git_branch)-$(call git_hash)
endef

# $(1): file extension
define img_name
u-boot_mod__$@__$(shell date +"%Y%m%d")__$(call git_branch_hash)$(if \
$(filter $(IMG_RAM),1),__RAM-LOAD-ONLY)$(if $(1),.$(1))
endef

define md5_sum
  $(call echo_green,Calculating MD5 sum for the final image...)

  md5sum $(BIN_DIR)/$(call img_name,bin) | \
         awk '{print $$1}' | \
         tr -d '\n' > $(BIN_DIR)/$(call img_name).md5

  echo ' *'$(call img_name,bin) >> $(BIN_DIR)/$(call img_name,md5)
endef

# $(1): size
define padded_img
  $(call echo_green,Preparing $(1) KB image padded with 0xFF...)
  tr "\000" "\377" < /dev/zero | dd ibs=1k count=$(1) \
     of=$(BIN_DIR)/$(call img_name,bin) 2> /dev/null
endef

define final_img
  $(call echo_green,Preparing final image...)
  dd if=$(BIN_DIR)/temp.bin of=$(BIN_DIR)/$(call img_name,bin) \
     conv=notrunc 2> /dev/null

  rm -f $(BIN_DIR)/temp.bin
endef

# $(1): path to image
# $(2): size limit in KB
define size_chk
  $(call echo_green,Checking size of the image...)

  if [ `wc -c < $(1)` -gt $$(($(2) * 1024)) ]; then \
    echo; \
    $(call echo_red,  ======================); \
    $(call echo_red,  IMAGE SIZE IS TOO BIG!); \
    $(call echo_red,  ======================); \
    echo; \
    rm -f $(1); \
    exit 1; \
  fi;
endef

# $(1): filename of image to copy
# $(2): image size limit (check if set)
define copy_img
  echo;
  $(call echo_green,Copying compiled image...)

  cp $(SOURCE_DIR)/$(strip $(1)).bin $(BIN_DIR)/temp.bin
  $(if $(2),$(call size_chk,$(BIN_DIR)/temp.bin,$(2)))
endef

# $(1): size limit in KB
# $(2): if set to 1, use LZMA
# $(3): other parameters passed to subdir make
define build
  args="IMG_SIZE=$$((1024*$(call img_size,$(1)))) \
        IMG_LZMA=$(strip $(call is_lzma,$(2))) \
        $(strip $(3))"; \
  cd $(SOURCE_DIR) && \
     $(SUB_MAKE_CMD) $@ $$args && \
     $(SUB_MAKE_CMD) all $$args

  $(if $(filter $(IMG_RAM),1),\
    $(call copy_img,u-boot), \
    $(if $(filter $(strip $(call is_lzma,$(2))),1), \
      $(call copy_img,tuboot,$(call img_size,$(1))), \
      $(call copy_img,u-boot,$(call img_size,$(1))) \
    ) \
  )

  $(if $(filter $(IMG_RAM),1),,$(call padded_img,$(1)))
  $(call final_img)
  $(call md5_sum)
  echo;
  $(call echo_green,DONE!)
  $(call echo_green,Image 'bin/$(call img_name,bin)' is ready!)

  if [ "x$$IMG_RAM" = "x1" ]; then \
    echo; \
    $(call echo_blue,  ================================); \
    $(call echo_blue,  THIS IMAGE IS ONLY FOR RAM LOAD!); \
    $(call echo_blue,  DO NOT WRITE IT INTO FLASH CHIP!); \
    $(call echo_blue,  ================================); \
    echo; \
  fi;
endef

# ===========================================
# TARGETS IN ALPHABETICAL ORDER, SHARED FIRST
# ===========================================

COMMON_AR933X_TARGETS = \
	gainstrong_oolite_v1_dev \
	gl-innovations_gl-inet-6416 \
	tp-link_tl-mr10u \
	tp-link_tl-mr13u \
	tp-link_tl-mr3020 \
	tp-link_tl-mr3040 \
	tp-link_tl-mr3220_v2 \
	tp-link_tl-wr703n \
	tp-link_tl-wr710n \
	tp-link_tl-wr720n_v3_CN \
	tp-link_tl-wr740n_v4

$(COMMON_AR933X_TARGETS):
	@$(call build,123,1)

COMMON_ETHS27_TARGETS = \
	tp-link_tl-mr3420_v2 \
	tp-link_tl-wa801nd_v2 \
	tp-link_tl-wa850re_v2 \
	tp-link_tl-wa830re_v2 \
	tp-link_tl-wdr3500 \
	tp-link_tl-wr802n \
	tp-link_tl-wr810n \
	tp-link_tl-wr820n_CN \
	tp-link_tl-wr841n_v10 \
	tp-link_tl-wr841n_v11 \
	tp-link_tl-wr841n_v8 \
	tp-link_tl-wr841n_v9

$(COMMON_ETHS27_TARGETS):
	@$(call build,123,1,ETH_CONFIG=_s27)

8devices_carambola2 \
alfa-network_hornet-ub \
gl-innovations_gl-ar150:
	@$(call build,256,1)

comfast_cf-e314n \
comfast_cf-e320n_v2 \
comfast_cf-e520n \
comfast_cf-e530n:
	@$(call build,64,1,ETH_CONFIG=_s27)

d-link_dir-505:
	@$(call build,64,1)

dragino_v2_ms14:
	@$(call build,192,1,DEVICE_VENDOR=dragino)

p2w_cpe505n \
p2w_r602n \
yuncore_ap90q \
yuncore_cpe830 \
zbtlink_zbt-we1526:
	@$(call build,256,1,ETH_CONFIG=_s27)

tp-link_tl-wdr3600 \
tp-link_tl-wdr43x0:
	@$(call build,123,1,ETH_CONFIG=_s17)

unwireddevices_unwired-one:
	@$(call build,128,1,DEVICE_VENDOR=SE)

village-telco_mesh-potato_v2:
	@$(call build,192,1,DEVICE_VENDOR=villagetelco)

wallys_dr531:
	@$(call build,192,1,ETH_CONFIG=_s27)

yuncore_cpe870:
	@$(call build,64,1,ETH_CONFIG=_s27)

# =============
# CLEAN TARGETS
# =============

lzma_host_clean:
	@cd $(SOURCE_DIR) && $(SUB_MAKE_CMD) $@

clean:
	@cd $(SOURCE_DIR) && $(SUB_MAKE_CMD) distclean
	@rm -f $(SOURCE_DIR)/httpd/fsdata.c

clean_all: clean
	@$(call echo_green,Removing all binary images...)
	@rm -f $(BIN_DIR)/*.bin
	@rm -f $(BIN_DIR)/*.md5
