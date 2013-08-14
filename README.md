U-Boot 1.1.4 modification for routers
==========

Introduction
------------

In short, this project is a deep modification of **U-Boot 1.1.4** sources, mostly from **TP-Link**, but some code fragments were taken also from **D-Link**.

You can download original sources from the following pages:

- [TP-Link GPL Code Center](http://www.tp-link.com/en/support/gpl/ "TP-Link GPL Code Center")
- [D-Link GPL Source Code Support](http://tsd.dlink.com.tw/GPL.asp "D-Link GPL Source Code Support")

The concept for this project came from another U-Boot modification, dedicated to small and very popular TP-Link router - model **TL-WR703N**, which includes web fail safe mode: **[wr703n-uboot-with-web-failsafe](http://code.google.com/p/wr703n-uboot-with-web-failsafe/)**. I was using it and decided to make my own version, which could have some improvements, additional capabilities, support for different models and work with all modern web browsers.

First version of this modification was introduced on **OpenWrt** forum in [this thread](https://forum.openwrt.org/viewtopic.php?id=43237), at the end of March 2013 and was dedicated only for TP-Link routers with **Atheros AR9331** SoC. Now, it supports also models from different manufacturers, devices with **Atheros AR9344** (like **TP-Link TL-WDR3600** and **TL-WDR43x0**) and other (in the near future **Atheros AR9341**) are under development.

You can find some information about previous versions of this project also on my [blog](http://www.tech-blog.pl), in [this article](http://www.tech-blog.pl/2013/03/29/zmodyfikowany-u-boot-dla-routerow-tp-link-z-atheros-ar9331-z-trybem-aktualizacji-oprogramowania-przez-www-i-konsola-sieciowa-netconsole/). It is in Polish, but [Google Translator](http://translate.google.com/translate?hl=pl&sl=pl&tl=en&u=http%3A%2F%2Fwww.tech-blog.pl%2F2013%2F03%2F29%2Fzmodyfikowany-u-boot-dla-routerow-tp-link-z-atheros-ar9331-z-trybem-aktualizacji-oprogramowania-przez-www-i-konsola-sieciowa-netconsole%2F&sandbox=1) will help you to understand it.

If you like this project, you may [buy me a beer](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=FN3XW36YHSY2S&lc=US&item_name=For%20a%20great%20job%21&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_LG%2egif%3aNonHosted)!

Supported devices
-----------------

Currently supported devices (default FLASH/RAM size):

- **Atheros AR9331**:
    - (16/64 MiB) [8devices Carambola 2](http://8devices.com/carambola-2) (version with development board!), [photos in my gallery](http://galeria.tech-blog.pl/8devices_Carambola_2/)
    - (4/32 MiB) [TP-Link TL-MR3020 v1](http://wiki.openwrt.org/toh/tp-link/tl-mr3020), [photos in my gallery](http://galeria.tech-blog.pl/TPLINK_TL-MR3020/)
    - (4/32 MiB) [TP-Link TL-MR3040 v1 and v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3040)
    - (4/32 MiB) [TP-Link TL-WR703N v1](http://wiki.openwrt.org/toh/tp-link/tl-wr703n), [photos in my gallery](http://galeria.tech-blog.pl/TPLINK_TL-WR703N/)
    - (4/32 MiB) [TP-Link TL-WR720N v3](http://wiki.openwrt.org/toh/tp-link/tl-wr720n) (version for Chinese market)
    - (8/32 MiB) [TP-Link TL-WR710N v1](http://www.tp-link.com/en/products/details/?model=TL-WR710N) (version for European market), [photos in my gallery](http://galeria.tech-blog.pl/TP-Link_TL-WR710N-EU/)
    - (4/32 MiB) [TP-Link TL-MR10U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr10u), [photos in my gallery](http://galeria.tech-blog.pl/TP-Link_TL-MR10U/)
    - (4/32 MiB) [TP-Link TL-WR740N v4](http://wiki.openwrt.org/toh/tp-link/tl-wr740n) (and similar, like TL-WR741ND v4)
    - (4/32 MiB) [TP-Link TL-MR3220 v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3420)
    - ~~(8/64 MiB) [D-Link DIR-505 H/W ver. A1](http://wiki.openwrt.org/toh/d-link/dir-505)~~, [photos in my gallery](http://galeria.tech-blog.pl/D-Link_DIR-505/)

- **Atheros AR9344**:
    - (8/128 MiB) [TP-Link TL-WDR3600 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3600)
    - (8/128 MiB) [TP-Link TL-WDR43x0 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr4300)

I tested this modification on most of these devices, with OpenWrt and OFW firmware. If you are not sure about the version of your device, please contact with me *before* you try to make an upgrade. Changing bootloader to a wrong version will probably damage your router and you will need a serial FLASH programmer to fix it, so please, **be very careful**.

Modifications, changes
----------------------

### Web server

The most important change is an inclusion of a web server, based on **[uIP 0.9 TCP/IP stack](http://www.gaisler.com/doc/net/uip-0.9/doc/html/main.html)**. It allows to upgrade **firmware**, **U-Boot** and **ART** (Atheros Radio Test) images, directly from your web browser, without need to access serial console and running a TFTP server. You can find similar firmware recovery mode, also based on uIP 0.9 TCP/IP stack, in **D-Link** routers.

Web server contains 7 pages:

1. index.html (allows to upgrade firmware image)
2. uboot.html (allows to upgrade U-Boot image)
3. art.html (allows to upgrade ART image)
4. flashing.html
5. 404.html
6. fail.html
7. style.css

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/08/uboot_mod_firmware_upgrade.jpg)

### Network Console

Second, very useful modification is a network console. It allows you to communicate with U-Boot console over the Ethernet, using UDP protocol (default UDP port: 6666, router IP: 192.168.1.1).

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/04/u-boot_mod_for_tp-link_with_ar9331_netconsole.jpg)

### Other

Moreover:

- Faster boot up
- Unnecessary information from boot up sequence were removed
- Flash chip is automatically recognized (using JEDEC ID)
- Ethernet MAC is set from flash (no more "No valid address in Flash. Using fixed address")
- Automatic kernel booting can be interrupted using any key
- Press and hold reset button to run:
    - web server (min. 3 seconds)
    - U-Boot serial console (min. 5 seconds)
    - U-Boot network console (min. 7 seconds)
- Additional commands (in comparison to the default version; availability depends on router model):
    -  httpd
    -  printmac
    -  setmac
    -  printmodel
    -  printpin
    -  startnc
    -  startsc
    -  eraseenv
    -  ping
    -  dhcp
    -  sntp
    -  iminfo
- Overclocking possibilities (for now, only routers with AR9331)

### Supported flash chips

Flash type detection may be very useful for people who has exchanged the flash chip in their routers. You will not need to recompile U-Boot sources, to have access to overall flash space in U-Boot console.

If you use flash type which is not listed below, this version of U-Boot will use default size for your router and, in most supported models, updating the ART image will not be available.

Currently supported flash types:

**4 MiB**:

- Spansion S25FL032P (4 MiB, JEDEC ID: 01 0215)*
- Atmel AT25DF321 (4 MiB, JEDEC ID: 1F 4700)
- EON EN25Q32 (4 MiB, JEDEC ID: 1C 3016)*
- Micron M25P32 (4 MiB, JEDEC ID: 20 2016)
- Windbond W25Q32 (4 MiB, JEDEC ID: EF 4016)
- Macronix MX25L320 (4 MiB, JEDEC ID: C2 2016)

**8 MiB**:

- Spansion S25FL064P (8 MiB, JEDEC ID: 01 0216)
- Atmel AT25DF641 (8 MiB, JEDEC ID: 1F 4800)
- EON EN25Q64 (8 MiB, JEDEC ID: 1C 3017)*
- Micron M25P64 (8 MiB, JEDEC ID: 20 2017)
- Windbond W25Q64 (8 MiB, JEDEC ID: EF 4017)*
- Macronix MX25L64 (8 MiB, JEDEC ID: C2 2017, C2 2617)
- SST 25VF064C (8 MiB, JEDEC ID: BF 254B)

**16 MiB**:

- Winbond W25Q128 (16 MB, JEDEC ID: EF 4018)*
- Macronix MX25L128 (16 MB, JEDEC ID: C2 2018, C2 2618)

(*) tested

If you want to use other type, please contact with me or make changes in the code, test them and send a pull request or a patch.

How to install it?
------------------

### Caution

**You do so at your own risk!**   
**If you make any mistake or something goes wrong during upgrade, in worst case your router will not boot again!**

### Using U-Boot console and TFTP server

[TODO]

### Using OpenWrt

[TODO]

### Using DD-WRT

[TODO]

How to use it?
--------------

[TODO]

How to compile the code?
------------------------

You can use one of the free toolchains:

- [Sourcery CodeBench Lite Edition for MIPS GNU/Linux](https://sourcery.mentor.com/GNUToolchain/subscription3130?lite=MIPS),
- [OpenWrt Toolchain for AR71xx MIPS](http://downloads.openwrt.org/attitude_adjustment/12.09/ar71xx/generic/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2),
- [ELDK (Embedded Linux Development Kit)](ftp://ftp.denx.de/pub/eldk/),
- or any others...

I am using **Sourcery CodeBench Lite Edition for MIPS GNU/Linux** on **Ubuntu 12.04 LTS** (32-bit, virtual machine) and all released binary images were/will be built using this set.

All you need to do, after choosing a toolchain, is to modify [Makefile](Makefile) - change or remove *export MAKECMD* and if need add *export PATH*. For example, to use OpenWrt Toolchain instead of Sourcery CodeBench Lite, download it and extract into *toolchain* folder, inside the top dir and change first lines in [Makefile](Makefile):

```
export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-openwrt-linux-uclibc-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)
```

To build image, run `make model` inside top dir, for example, command:

```
make tplink_wr703n
```

will start building U-Boot image for **TP-Link TL-WR703N**.

FAQ
---

#### 1. My device is not supported, but has the same hardware as one in the list, can I use this modification?

*It could be dangerous! I know that a lot of routers uses the same hardware - for example, TP-Link has a battery powered routers set, which contains: TL-MR10U, TL-MR11U (TL-MR3040 in Europe) TL-MR12U and TL-MR13U. All of them has the same platform: Atheros AR9331 with 32 MiB of DDR RAM and 4 MiB of SPI NOR FLASH. But, there may exist a slight difference, like GPIO pin number for reset button or LED(s), that may cause problems.*

*You can try, but remember that you are doing this only at your own risk!*

#### 2. I want to overclock my router, how can I do this?

*Currently, this option is available only for TP-Link routers with Atheros AR9331 (please, look at [ap121.h](u-boot/include/configs/ap121.h) file which contains all information about PLL register configuration and an untypical clocks for CPU, RAM and AHB). What more, you will need to compile the code yourself, because I will not publish images with non-default clocks.*

*And again, remember that you are doing this only at your own risk!*

#### 3. Do you test all prebuilt images before you publish them?

*No, because I don't have all supported devices, only few of them. But, I make tests for every supported SoC types.*

#### 4. I would like you to add support for device X.

*You can do it yourself and send me a pull request or a patch. If you do not want to, or do not know how to do it, please contact with me directly.*

#### 5. My device does not boot after upgrade!

*I told you... bootloader, in this case the U-Boot, is the most important piece of code inside your device. It is responsible for hardware initialization and booting an OS (kernel in this case). So, if during the upgrade something went wrong, your device will not boot any more. Now you need to remove the flash chip, load proper image using an external programmer and solder it back.*

License, outdated sources etc.
------------------------------

**[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** project is Free Software, licensed under version 2 of the **GNU General Public License**. All information about license, contributors etc., are included with sources, inside *u-boot* folder.

You should know, that most routers, especially those based on Atheros SoCs, uses very old versions of U-Boot (1.1.4 is from 2005/2006). So, *these sources are definitely outdated* (do not even try to merge them with official release), but it was easier for me to modify them, than move TP-Link/Atheros changes to the current version. Moreover, lot of unnecessary code fragments and source files were removed for ease of understanding the code.