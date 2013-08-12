U-Boot 1.1.4 modification for TP-Link, and not only, routers
==========

# Introduction #

In short, this project is a deep modification of **U-Boot 1.1.4** sources from **TP-Link**, which you can download from their **[GPL Code Center](http://www.tp-link.com/en/support/gpl/ "TP-Link GPL Code Center")**.

The concept for this project came from another U-Boot modification, dedicated to small and very popular TP-Link router - model **TL-WR703N**, which includes web fail safe mode: **[wr703n-uboot-with-web-failsafe](http://code.google.com/p/wr703n-uboot-with-web-failsafe/)**. I was using it and decided to make my own version, which could have some improvements, additional capabilities and support for different models.

First version of this modification was introduced on **OpenWrt** forum in [this thread](https://forum.openwrt.org/viewtopic.php?id=43237), at the end of March 2013 and it was dedicated only for TP-Link routers with **Atheros AR9331** SoC. Now, it supports also models with **Atheros AR9344** (like **TP-Link TL-WDR3600** and **TL-WDR43x0**) and other (in the near future **Atheros AR9341**) are under development.

# Supported devices #

Currently supported devices (default FLASH/RAM size):

- **Atheros AR9331**:
    - (16/64 MiB) [8devices Carambola 2](http://8devices.com/carambola-2) (version with development board!)
    - (4/32 MiB) [TP-Link TL-MR3020 v1](http://wiki.openwrt.org/toh/tp-link/tl-mr3020)
    - (4/32 MiB) [TP-Link TL-MR3040 v1 and v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3040)
    - (4/32 MiB) [TP-Link TL-WR703N v1](http://wiki.openwrt.org/toh/tp-link/tl-wr703n)
    - (4/32 MiB) [TP-Link TL-WR720N v3](http://wiki.openwrt.org/toh/tp-link/tl-wr720n) (version for Chinese market)
    - (8/32 MiB) [TP-Link TL-WR710N v1](http://www.tp-link.com/en/products/details/?model=TL-WR710N) (version for European market)
    - (4/32 MiB) [TP-Link TL-MR10U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr10u)
    - (4/32 MiB) [TP-Link TL-WR740N v4](http://wiki.openwrt.org/toh/tp-link/tl-wr740n) (and similar, like TL-WR741ND v4)
    - (4/32 MiB) [TP-Link TL-MR3220 v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3420)

- **Atheros AR9344**:
    - (8/128 MiB) [TP-Link TL-WDR3600 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3600)
    - (8/128 MiB) [TP-Link TL-WDR43x0 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr4300)

I tested this modification on most of these devices, with OpenWrt and OFW firmware. If you are not sure about the version of your device, please contact with me *before* you try to make an upgrade. Changing bootloader to a wrong version will probably damage your router and you will need a serial FLASH programmer to fix it, so be *very* careful.

# Modifications, changes #

## Web server  ##

The most important change is an inclusion of a web server, based on **[uIP 0.9 TCP/IP stack](http://www.gaisler.com/doc/net/uip-0.9/doc/html/main.html)**. It allows to upgrade **firmware**, **U-Boot** and **ART** (**Atheros Radio Test**) images, directly from your web browser, without need to access serial console and running a TFTP server. You can find similar firmware recovery mode, also based on uIP 0.9 TCP/IP stack, in **D-Link** routers.

Web server contains 7 pages:

1. index.html (allows to upgrade firmware image)
2. uboot.html (U-Boot image)
3. art.html (ART image)
4. flashing.html
5. 404.html
6. fail.html
7. style.css

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/08/uboot_mod_firmware_upgrade.jpg)

## Network Console ##

Second, very useful modification is a network console. It allows you to communicate with U-Boot console over the Ethernet, using UDP protocol (default UDP port: 6666, router IP: 192.168.1.1).

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/04/u-boot_mod_for_tp-link_with_ar9331_netconsole.jpg)

## Other ##

Moreover:

- faster boot up,
- unnecessary information from boot up sequence were removed,
- flash chip is automatically recognized (using JEDEC ID),
- Ethernet MAC is set from flash (no more "No valid address in Flash. Using fixed address"),
- automatic kernel booting can be interrupted using any key,
- press and hold reset button to run:
    - web server (min. 3 seconds),
    - U-Boot serial console (min. 5 seconds),
    - U-Boot network console (min. 7 seconds),
- additional commands (in comparison to the default version; availability depends on router model):
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
- overclocking possibilities (for now, only TP-Link routers with AR9331)

## Supported flash chips ##

Flash type detection may be very useful for people who has exchanged the flash chip in their routers. You will not need to recompile sources, to have access to overall flash space in U-Boot console.

If you use flash type which is not listed below, this version of U-Boot will use default size for your router.

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

If you want to use other type, please contact with me or make changes in code, test them and send a pull request.

# How to install it? #

[TODO]

# How to compile the code? #

You can use one of the free toolchains:


- [Sourcery CodeBench Lite Edition for MIPS GNU/Linux](https://sourcery.mentor.com/GNUToolchain/subscription3130?lite=MIPS),
- [OpenWrt Toolchain for AR71xx MIPS](http://downloads.openwrt.org/attitude_adjustment/12.09/ar71xx/generic/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2),
- [ELDK (Embedded Linux Development Kit)](ftp://ftp.denx.de/pub/eldk/),
- or any others...

I am using **Sourcery CodeBench Lite Edition for MIPS GNU/Linux** on **Ubuntu 12.04 LTS** and all released binary images were/will be built using this set.

# FAQ #

1. My device is not supported but has the same hardware as one in the list, can I use this modification?

	*It could be dangerous! I know that a lot of routers uses the same hardware - for example, TP-Link has a battery powered routers set, which contains: TL-MR10U, TL-MR11U (TL-MR3040 in Europe) TL-MR12U and TL-MR13U. All of them has the same platform: Atheros AR9331 with 32 MiB of DDR RAM and 4 MiB of SPI NOR FLASH. But, there may exist a slight difference, like GPIO pin number for reset button or LED(s), that may cause problems.*

	*You can try, but remember that you are doing this only at your own risk!*

2. I want to overclock my router, how can I do this?

	*Currently, this option is available only for TP-Link routers with Atheros AR9331 (please, see *ap121.h* file inside *u-boot/inlude/configs* folder. What more, you will need to compile the code, because I do not want to publish images with non-default clocks.*

	*And again, remember that you are doing this only at your own risk!*

# License, outdated sources etc. #

**[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** project is Free Software, licensed under version 2 of the **GNU General Public License**. All information about license, contributors etc., are included with sources, inside *u-boot* folder.

You should know, that most routers, especially those based on Atheros SoCs, uses very old versions of U-Boot (1.1.4 is from 2005/2006). So, *these sources are definitely outdated* (do not even try to merge them with official release), but it was easier for me to modify them, than move TP-Link/Atheros changes to the current version. Moreover, lot of unnecessary code fragments and source files were removed for ease of understanding the code.