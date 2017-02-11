U-Boot 1.1.4 modification for routers
==========

Ready snapshot/test images
--------------------------
Starting from 24.09.2016, ready images, built on **Raspberry Pi 3** with **LEDE** toolchain, are available **[on my server](http://projects.dymacz.pl)**.

Images are built and uploaded on FTP only when master branch in repository was updated - custom script checks this once per day. On the FTP you will find also toolchain which is used to build images.

Table of contents
-----------------

- [Introduction](#introduction)
- [Supported devices](#supported-devices)
- [Known issues](#known-issues)
- [Modifications, changes](#modifications-changes)
	- [Web server](#web-server)
	- [Network Console](#network-console)
	- [Writable environment variables](#writable-environment-variables)
	- [Other](#other)
	- [Supported FLASH chips](#supported-flash-chips)
- [How to install it?](#how-to-install-it)
	- [Cautions, backups](#cautions-backups)
	- [Using external programmer](#using-external-programmer)
	- [Using UART, U-Boot console and TFTP server](#using-uart-u-boot-console-and-tftp-server)
		- [Important notice!](#important-notice)
		- [Step by step instructions](#step-by-step-instructions)
	- [Using OpenWrt](#using-openwrt)
	- [Using DD-WRT](#using-dd-wrt)
- [How to use it?](#how-to-use-it)
- [How to compile the code?](#how-to-compile-the-code)
    - [Building on Linux](#building-on-linux)
    - [Building on OS X](#building-on-macos-os-x)
- [FAQ](#faq)
- [License, outdated sources etc.](#license-outdated-sources-etc)
- [Credits](#credits)

Introduction
------------

In short, this project is a deep modification of **U-Boot 1.1.4** sources, mostly from **TP-Link**, but some code fragments were taken also from **D-Link**, **Netgear**, **ZyXEL** and **Belkin**. All these companies are using SDK from Qualcomm/Atheros which includes modified version of **U-Boot 1.1.4**.

You can download original sources from the following pages:

- [TP-Link GPL Code Center](http://www.tp-link.com/en/support/gpl/ "TP-Link GPL Code Center")
- [D-Link GPL Source Code Support](http://tsd.dlink.com.tw/GPL.asp "D-Link GPL Source Code Support")
- [NETGEAR Open Source Code for Programmers (GPL)](http://kb.netgear.com/app/answers/detail/a_id/2649/~/netgear-open-source-code-for-programmers-%28gpl%29 "NETGEAR Open Source Code for Programmers (GPL)")
- [ZyXEL GPL-OSS](http://www.zyxel.com/us/en/form/gpl_oss_form.shtml "ZyXEL GPL-OSS")
- [Belkin Open Source Code Center](http://www.belkin.com/us/support-article?articleNum=51238 "Belkin Open Source Code Center")

The concept for this project came from another U-Boot modification, dedicated to a small and very popular TP-Link router - model **TL-WR703N**, which includes web fail safe mode: **[wr703n-uboot-with-web-failsafe](http://code.google.com/p/wr703n-uboot-with-web-failsafe/)**. I was using it and decided to make my own version, which could have some improvements, additional capabilities, support for different models and work with all modern web browsers.

First version of this modification was introduced on **OpenWrt** forum in [this thread](https://forum.openwrt.org/viewtopic.php?id=43237), at the end of March 2013 and was dedicated only for TP-Link routers with **Atheros AR9331** SoC. Now, it supports also models from different manufacturers, devices with **Atheros AR934x**, **Qualcomm Atheros QCA953x**, **Qualcomm Atheros QCA955x** and other (in the near future **Qualcomm Atheros QCA956x** and **MediaTek MT762x**) are under development.

You can find some information about previous versions of this project also on my [blog](http://www.tech-blog.pl), in [this article](http://www.tech-blog.pl/2013/03/29/zmodyfikowany-u-boot-dla-routerow-tp-link-z-atheros-ar9331-z-trybem-aktualizacji-oprogramowania-przez-www-i-konsola-sieciowa-netconsole/). It is in Polish, but [Google Translator](http://translate.google.com/translate?hl=pl&sl=pl&tl=en&u=http%3A%2F%2Fwww.tech-blog.pl%2F2013%2F03%2F29%2Fzmodyfikowany-u-boot-dla-routerow-tp-link-z-atheros-ar9331-z-trybem-aktualizacji-oprogramowania-przez-www-i-konsola-sieciowa-netconsole%2F&sandbox=1) will help you to understand it.

If you like this project, you may [buy me a beer](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=FN3XW36YHSY2S&lc=US&item_name=For%20a%20great%20job%21&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_LG%2egif%3aNonHosted)!

Supported devices
-----------------

Currently supported devices:

- **Atheros AR9331**:
  - 8devices Carambola 2 (for version with development board, [photos in my gallery](http://galeria.tech-blog.pl/8devices_Carambola_2/))
  - ALFA NETWORK Hornet-UB/Hornet-UB-64 (aka Hornet-UB x2)
  - Black Swift
  - Dragino 2 (MS14)
  - GL Innovations GL-AR150
  - GL Innovations GL.iNet 64xxA ([photos in my gallery](http://galeria.tech-blog.pl/GLiNet/))
  - GS-Oolite/Elink EL-M150 module with dev board ([photos in my gallery](http://galeria.tech-blog.pl/Elink_EL-M150_Development-Board/))
  - TP-Link TL-MR10U v1 ([photos in my gallery](http://galeria.tech-blog.pl/TP-Link_TL-MR10U/))
  - TP-Link TL-MR13U v1
  - TP-Link TL-MR3020 v1 ([photos in my gallery](http://galeria.tech-blog.pl/TPLINK_TL-MR3020/))
  - TP-Link TL-MR3040 v1 and v2
  - TP-Link TL-MR3220 v2
  - TP-Link TL-WR703N v1, ([photos in my gallery](http://galeria.tech-blog.pl/TPLINK_TL-WR703N/))
  - TP-Link TL-WR710N v1 (version for European market, [photos in my gallery](http://galeria.tech-blog.pl/TP-Link_TL-WR710N-EU/))
  - TP-Link TL-WR720N v3 (version for Chinese market)
  - TP-Link TL-WR740N v4 (and similar, like TL-WR741ND v4)
  - Village Telco Mesh Potato 2 (based on Dragino MS14)

- **Atheros AR1311 (similar to AR9331)**
  - D-Link DIR-505 H/W ver. A1 ([photos in my gallery](http://galeria.tech-blog.pl/D-Link_DIR-505/))

- **Atheros AR9341**:
  - TP-Link TL-MR3420 v2
  - TP-Link TL-WA801ND v2
  - TP-Link TL-WA830RE v2
  - TP-Link TL-WR841N/D v8
  - YunCore CPE870

- **Atheros AR9344**:
  - TP-Link TL-WDR3500 v1
  - TP-Link TL-WDR3600 v1
  - TP-Link TL-WDR43x0 v1

- **Qualcomm Atheros QCA953x**:
  - Comfast CF-E314N
  - Comfast CF-E320N v2
  - Comfast CF-E520N/CF-E530N
  - P&W CPE505N
  - P&W R602N
  - TP-Link TL-WA850RE v2
  - TP-Link TL-WR802N
  - TP-Link TL-WR810N
  - TP-Link TL-WR820N (version for Chinese market)
  - TP-Link TL-WR841N/D v9, v10, v11
  - Wallys DR531
  - YunCore AP90Q
  - YunCore CPE830
  - Zbtlink ZBT-WE1526

I tested this modification on most of these devices, with OpenWrt and OFW firmware. If you are not sure about the version of your device, please contact with me **before** you try to make an upgrade. Changing bootloader to a wrong version will probably damage your router and you will need special hardware to fix it, so please, **be very careful**.

More information about supported devices:

| Model | SoC | FLASH | RAM | U-Boot image | U-Boot env |
|:--- | :--- | ---: | ---: | ---: | ---: |
| [8devices Carambola 2](http://8devices.com/carambola-2) | AR9331 | 16 MiB | 64 MiB DDR2 | 256 KiB | 64 KiB, R/W |
| [ALFA NETWORK Hornet-UB](https://wiki.openwrt.org/toh/alfa.network/hornet-ub) | AR9331 | 8/16 MiB | 32/64 MiB DDR1 | 256 KiB | R/W |
| [Black Swift](http://www.black-swift.com) | AR9331 | 16 MiB | 64 MiB DDR2 | 128 KiB, LZMA | R/W |
| Comfast CF-E314N | QCA9531 | 16 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| Comfast CF-E320N v2 | QCA9531 | 16 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| Comfast CF-E520N/CF-E530N | QCA9531 | 8 MiB | 32 MiB DDR2 | 64 KiB, LZMA | RO |
| [D-Link DIR-505 H/W ver. A1](http://wiki.openwrt.org/toh/d-link/dir-505) | AR1311 | 8 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [Dragino 2 (MS14)](http://wiki.openwrt.org/toh/dragino/ms14) | AR9331 | 16 MiB | 64 MiB DDR1 | 192 KiB | R/W |
| GL Innovations GL-AR150 | AR9331 | 16 MiB | 64 MiB DDR2 | 256 KiB | 64 KiB, R/W |
| [GL Innovations GL.iNet 64xxA](http://wiki.openwrt.org/toh/gl-inet/gl-inet) | AR9331 | 8/16 MiB | 64 MiB DDR1 | 64 KiB | RO |
| GS-Oolite/Elink EL-M150 module | AR9331 | 4/8/16 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| P&W CPE505N | QCA9531 | 16 MiB | 64 MiB DDR2 | 256 KiB | R/W |
| P&W R602N | QCA9531 | 16 MiB | 64 MiB DDR2 | 256 KiB | R/W |
| [TP-Link TL-MR10U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr10u) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR13U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr13u) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3020 v1](http://wiki.openwrt.org/toh/tp-link/tl-mr3020) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3040 v1/2](http://wiki.openwrt.org/toh/tp-link/tl-mr3040) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3220 v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3420) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3420 v2](http://wikidevi.com/wiki/TP-LINK_TL-MR3420_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WA801ND v2](http://wikidevi.com/wiki/TP-LINK_TL-WA801ND_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WA830RE v2](http://wikidevi.com/wiki/TP-LINK_TL-WA830RE_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| TP-Link TL-WA850RE v2 | QCA9533 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR3500 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3500) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR3600 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3600) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR43x0 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr4300) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR703N](http://wiki.openwrt.org/toh/tp-link/tl-wr703n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR710N v1](http://wiki.openwrt.org/toh/tp-link/tl-wr710n) | AR9331 | 8 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR720N v3](http://wiki.openwrt.org/toh/tp-link/tl-wr720n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR740N v4](http://wiki.openwrt.org/toh/tp-link/tl-wr740n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR802N](https://wikidevi.com/wiki/TP-LINK_TL-WR802N_v1.0) | QCA9533 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR810N](https://wiki.openwrt.org/toh/tp-link/tl-wr810n) | QCA9531 | 8 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR820N](https://wiki.openwrt.org/toh/tp-link/tl-wr820n) | QCA9531 | 4 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR841N/D v8](http://wiki.openwrt.org/toh/tp-link/tl-wr841nd) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR841N/D v9/10/11](https://wiki.openwrt.org/toh/tp-link/tl-wr841nd) | QCA9533 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| Village Telco Mesh Potato 2 | AR9331 | 16 MiB | 64 MiB DDR1 | 192 KiB | R/W |
| Wallys DR531 | QCA9531 | 8 MiB | 64 MiB DDR2 | 192 KiB | R/W |
| YunCore AP90Q | QCA9531 | 16 MiB | 128 MiB DDR2 | 256 KiB | R/W |
| YunCore CPE830 | QCA9531 | 16 MiB | 64 MiB DDR2 | 256 KiB | R/W |
| YunCore CPE870 | AR9341 | 8 MiB | 64 MiB DDR2 | 64 KiB, LZMA | R/W |
| Zbtlink ZBT-WE1526 | QCA9531 | 16 MiB | 128 MiB DDR2 | 256 KiB | R/W |

*(LZMA) - U-Boot binary image is compressed with LZMA.*  
*(R/W) - environment exists in separate FLASH block which allows you to save it and keep after power down.*
*(RO) - environment is read only, you can change and add new variables only during runtime.*

Known issues
------------

Current release is not loading kernel from some versions of TP-Link's official firmware. If you want to use the so-called OFW in any of supported TP-Link's router, do not use this modification. I am working on a solution for this issue.

Modifications, changes
----------------------

### Web server

The most important change is an inclusion of a web server, based on **[uIP 0.9 TCP/IP stack](https://github.com/adamdunkels/uip/tags)**. It allows to upgrade **firmware**, **U-Boot** and **ART** (Atheros Radio Test) images, directly from your web browser, without need to access serial console and running a TFTP server. You can find similar firmware recovery mode, also based on uIP 0.9 TCP/IP stack, in **D-Link** routers.

Web server contains 7 pages:

1. index.html (allows to upgrade firmware image, screenshot below)
2. uboot.html (allows to upgrade U-Boot image)
3. art.html (allows to upgrade ART image)
4. flashing.html
5. 404.html
6. fail.html
7. style.css

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_firmware_upgrade.jpg)

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_firmware_upgrade_progress.jpg)

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_uboot_upgrade.jpg)


### Network Console

Second, very useful modification is a network console (it is a part of original U-Boot sources, but none of the manufacturers included it). It allows you to communicate with U-Boot console over the Ethernet, using UDP protocol (default UDP port: 6666, router IP: 192.168.1.1).

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/04/u-boot_mod_for_tp-link_with_ar9331_netconsole.jpg)

You could also use netcat instead of Hercules utility on Mac/Linux:
```
# nc -u -p 6666 192.168.1.1 6666
```

### Writable environment variables

U-Boot uses special "**environment variables**" which are used for storing values of many different settings, like IP addresses of device and remote server for TFTP transaction, serial console baud rate, boot command, etc. Environment is usually stored in separate FLASH sector or its part, so all changes can be saved permanently.

None of the popular manufacturers provides this feature and use so called "**read-only environment**" (embedded in U-Boot image), which means that all changes made during a runtime will be lost after device restart and there is no way to store them in FLASH.

This modification uses writable environment variables in almost all supported devices, so you can do for example:

```
uboot> setenv ipaddr 192.168.1.100
uboot> saveenv
Saving environment to FLASH...

Erase FLASH from 0x9F010000 to 0x9F01FFFF in bank #1
Erasing: #

Erased sectors: 1

Writing at address: 0x9F010000

uboot> reset
```

Which will change device IP address and save updated environment variables in FLASH. From next power up, the device will use new value for its IP address.

Using command **run** and writable environment variables you are able to write custom, small scripts like below example, used for firmware upgrade using TFTP method:

```
uboot> printenv
[...]
firmware_addr=0x9F020000
firmware_name=firmware.bin
firmware_upg=if ping $serverip; then tftp $loadaddr $firmware_name && erase $firmware_addr +$filesize && cp.b $loadaddr $firmware_addr $filesize && echo OK!; else echo ERROR! Server not reachable!; fi
[...]

uboot> run firmware_upg
Ethernet mode (duplex/speed): 1/100 Mbps
Using eth0 device

Ping OK, host 192.168.1.2 is alive!


TFTP from IP: 192.168.1.2
      Our IP: 192.168.1.1
    Filename: 'firmware.bin'
Load address: 0x80800000
       Using: eth0

     Loading: ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              ########################################
              #########

TFTP transfer complete!

Bytes transferred: 3932160 (0x3c0000)
Erase FLASH from 0x9F020000 to 0x9F3DFFFF in bank #1
Erasing: #######################################
         #####################

Erased sectors: 60

Copying to FLASH...
Writing at address: 0x9F020000

Done!

OK!
uboot>
```

### Other

Moreover:

- Faster boot up
- Unnecessary information from boot up sequence were removed
- FLASH chip is automatically recognized (using JEDEC ID)
- Ethernet MAC is set from FLASH (no more "No valid address in FLASH. Using fixed address")
- Automatic kernel booting can be interrupted using any key
- Better UART serial console driver with support for different baud rates
- Press and hold reset button to run:
  - Web server (min. 3 seconds)
  - U-Boot serial console (min. 5 seconds)
  - U-Boot network console (min. 7 seconds)
- Additional commands (in comparison to the default version; availability depends on router model):
  -  defenv
  -  httpd
  -  itest
  -  loadb
  -  loady
  -  printmac
  -  setmac
  -  printmodel
  -  printpin
  -  startnc
  -  startsc
  -  ping
  -  dhcp
  -  sntp
  -  iminfo
- Overclocking and underclocking possibilities (for now, only routers with AR9331)

### Supported FLASH chips

FLASH type detection may be very useful for people who has exchanged the FLASH chip in their routers. You will not need to recompile U-Boot sources, to have access to overall FLASH space in U-Boot console.

If you use FLASH type which is not listed below, this version of U-Boot will try to get information about the chip using **Serial Flash Discoverable Parameter** (**SFDP**, more information: https://www.jedec.org/standards-documents/docs/jesd216b) standard. If your chip does not support SFDP, it will use default size for your router and, in most supported models, updating the ART image will not be available.

Currently supported FLASH types:

**4 MiB**:

- Spansion S25FL032P (4 MiB, JEDEC ID: 01 0215)*
- Atmel AT25DF321 (4 MiB, JEDEC ID: 1F 4700)
- EON EN25Q32 (4 MiB, JEDEC ID: 1C 3016)*
- EON EN25F32 (4 MiB, JEDEC ID: 1C 3116)*
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

**16 MiB**:

- Winbond W25Q128 (16 MB, JEDEC ID: EF 4018)*
- Winbond W25Q128FW (16 MB, JEDEC ID: EF 6018, 1,8 V)*
- Macronix MX25L128 (16 MB, JEDEC ID: C2 2018, C2 2618)
- Spansion S25FL127S (16 MB, JEDEC ID: 01 2018)*
- Micron N25Q128 (16 MB, JEDEC ID: 20 BA18)

(*) tested

If you want to use other type, please contact with me or make changes in the code, test them and send a pull request or a patch.

How to install it?
------------------

### Cautions, backups

**You do so at your own risk!**   
**If you make any mistake or something goes wrong during upgrade, in worst case, your router will not boot again!**

It is a good practice to backup your original U-Boot image/partition (especially for TP-Link devices) **before** you make any changes. For example, using OpenWrt (TP-Link TL-WR703N with 16 MiB FLASH):

```
cat /proc/mtd
```

This command will show you all **MTD** (Memory Technology Device) partitions:

```
dev:    size   erasesize  name
mtd0: 00020000 00010000 "u-boot"
mtd1: 000eeb70 00010000 "kernel"
mtd2: 00ee1490 00010000 "rootfs"
mtd3: 00c60000 00010000 "rootfs_data"
mtd4: 00010000 00010000 "art"
mtd5: 00fd0000 00010000 "firmware"
```

As you can see, `u-boot` partition size is **0x20000** (128 KiB) and my image for this model has smaller size: **0x1EC00** (123 KiB) - it is a very important difference! You should remember about this if you want to use `mtd` utility or serial console and U-Boot command line, to change the bootloader.

To backup `u-boot` partition in RAM, run:

```
cat /dev/mtd0 > /tmp/uboot_backup.bin
```

And then connect to your router using `SCP protocol` and download from `/tmp` the `uboot_backup.bin` file.

### Using external programmer

If you have an external FLASH programmer (all supported devices have **SPI NOR FLASH** chips), you probably know how to use it. Download package with prebuilt images or compile the code, choose right file for your device and put it on FLASH at the beginning (offset `0x00000`). Remember to first erase block(s) - with high probability, if you use some kind of automatic mode, the programmer will do it for you.

All prebuilt images are padded with 0xFF and since change "**![Extend maximum U-Boot image size up to 123 KB](https://github.com/pepe2k/u-boot_mod/commit/7829f50c0e92024fde613cb01e65cbdeae1f126b)**", in most supported devices, **their size is no longer a multiple of 64 KiB block**. For example, **TP-Link** uses only first **64 KiB** block to store compressed U-Boot image (in most of their modern devices). In the second 64 KiB block they store additional information like MAC address, model number and WPS pin number. This modification will use both sectors for U-Boot image and also other data, including small block for writable environment variables.

Below image with beginning part of FLASH memory map for TP-Link TL-MR3020 shows differences between stock version and this modification.

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2016/03/mr3020_u-boot-modification_flash-map_comparison.png)

On the other hand, U-Boot image in **Carambola 2** from **8devices** may have up to **256 KiB** (4x 64 KiB block), they use uncompressed version and environment stored in FLASH. Immediately after the Carambola 2 U-Boot partition is an area which contains U-Boot environment variables (1x 64 KiB block), called `u-boot-env`:

```
dev:    size   erasesize  name
mtd0: 00040000 00010000 "u-boot"
mtd1: 00010000 00010000 "u-boot-env"
mtd2: 00f90000 00010000 "firmware"
mtd3: 00e80000 00010000 "rootfs"
mtd4: 00cc0000 00010000 "rootfs_data"
mtd5: 00010000 00010000 "nvram"
mtd6: 00010000 00010000 "art"
```

### Using UART, U-Boot console and TFTP server

**WARNING! This method is highly not recommended!**

It is probably the most common method to change firmware in case of any problems. Main disadvantage of this approach is the need to connect with device using a serial port (this does not apply to Carambola 2 with development board, which already has a built-in USB-UART adapter, based on FTDI FT232RQ).

#### Important notice!

All these devices have an UART interface integrated inside the SoC, which operates at TTL 3.3 V (in fact, GPIO pins can work at this voltage, but their real range is < 3 V)!

Please, **do not** connect any RS232 +/- 12 V cable or any adapter without logic level converter, because it may damage your device. It would be the best if you use any USB to UART adapter with integrated 3.3 V logic level converter. And please, remember that **you should connect only RX, TX and GND signals**. **DO NOT** connect together 3.3 V signals from router and from adapter if you do not know what are you doing, because you may burn out your adapter and/or router! Connect the adapter using USB port in your PC and router with original power supply.

For a long time I have been using without any problems a small and very cheap (about 1-2 USD) **CP2102** based adapter. Go to [Serial Console article in OpenWrt Wiki](http://wiki.openwrt.org/doc/hardware/port.serial) for more, detailed information.

#### Step by step instructions

1. Install and configure any **TFTP server** on your PC (on Windows, you can use [TFTP32](http://tftpd32.jounin.net)).

2. Set a fixed IP address on your PC (in this tutorial we will use **192.168.1.2** for the PC and **192.168.1.1** for the router) and connect it to the router, using RJ45 network cable (in most case you will need to use one of the available LAN ports, but WAN port should also work).

3. Connect USB to UART adapter to the router and start any application to communicate with it, like [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html).   
Configure adapter to use the following settings:
  * Baud rate: 115200
  * Data bits: 8
  * Parity control: none
  * Stop bits: 1
  * Handshaking: none
4. Power on the router, wait for a line like one of the following and interrupt the process of loading a kernel:

  `Autobooting in 1 seconds` (for most **TP-Link** routers, you should enter `tpl` at this point)   
  `Hit ESC key to stop autoboot:  1` (for **8devices Carambola 2**, use `ESC` key)   
  `Hit any key to stop autoboot:  1` (for **D-Link DIR-505**, use any key)

5. Set `ipaddr` and `serverip` environment variables:

  ```
  hornet> setenv ipaddr 192.168.1.1
  hornet> setenv serverip 192.168.1.2
  ```
6. Check the changes:

  ```
  hornet> printenv ipaddr
  ipaddr=192.168.1.1
  hornet> printenv serverip
  serverip=192.168.1.2
  ```

7. Due to differences in FLASH memory map and sizes of original and modified version of U-Boot, you must first make a backup of the partition with original version in RAM. **If you skip this step or make a mistake, your device will be probably broken!**

  This step is different between supported models, so you should pay attention to the size of image with modified version of U-Boot, **round it to the nearest multiple of 64 KiB** and use this value in all next steps.

  For example, if image of the modified version is **123 KiB** (**0x1EC00**) you must first make a backup of **128 KiB** (**0x20000**) in RAM, at the same address where you are going to download the image:

  ```
  hornet> cp.b 0x9F000000 0x80800000 0x20000
  ```

  Using the same offset address in RAM for backup and new image will end up with combination of both images and preserve additional data like MAC address, model number and PIN.

8. Download and store in RAM proper image for your router, using `tftpboot` command in U-Boot console (in this example, for **TP-Link TL-MR3020**):

  ```
  hornet> tftpboot 0x80800000 uboot_for_tp-link_tl-mr3020.bin
  eth1 link down
  Using eth0 device
  TFTP from server 192.168.1.2; our IP address is 192.168.1.1
  Filename 'uboot_for_tp-link_tl-mr3020.bin'.
  Load address: 0x80800000
  Loading: #########################
  done
  Bytes transferred = 125952 (1ec00 hex)

  hornet>
  ```

9. Next step is very risky! You are going to delete existing U-Boot image from FLASH in your device and copy from RAM the new one. If something goes wrong (for example, a power failure), your router, without bootloader, will not boot again!

  You should also note the size of image and use value from step 7. In all cases, the start address of FLASH is **0x9F000000** and for RAM: **0x80000000** (as you may noticed, I did not use start address of RAM to store image and you should follow this approach).

  Please, do not make any mistake with offsets and sizes during next steps!

10. Erase appropriate FLASH space for new U-Boot image (this command will remove default U-Boot image!):

  ```
  hornet> erase 0x9F000000 +0x20000

  First 0x0 last 0x1 sector size 0x10000
  Erased 2 sectors
  hornet>
  ```

11. Now your router does not have U-Boot, so do not wait and copy to FLASH the new one, stored earlier in RAM:

  ```
  hornet> cp.b 0x80800000 0x9F000000 0x20000

  Copy to Flash... write addr: 9f000000
  done
  ```

12. If you want, you can check content of the newly written FLASH and compare it to the image on your PC (or better also do such a "legit memory content" comparison prior to writing!), using `md` command in U-Boot console, which prints indicated memory area (press only ENTER after first execution of this command to move further in memory):

  ```
  hornet> md 0x9F000000

  9f000000: 100000ff 00000000 100000fd 00000000    ................
  9f000010: 10000222 00000000 10000220 00000000    ..."....... ....
  9f000020: 1000021e 00000000 1000021c 00000000    ................
  9f000030: 1000021a 00000000 10000218 00000000    ................
  9f000040: 10000216 00000000 10000214 00000000    ................
  9f000050: 10000212 00000000 10000210 00000000    ................
  9f000060: 1000020e 00000000 1000020c 00000000    ................
  9f000070: 1000020a 00000000 10000208 00000000    ................
  9f000080: 10000206 00000000 10000204 00000000    ................
  9f000090: 10000202 00000000 10000200 00000000    ................
  9f0000a0: 100001fe 00000000 100001fc 00000000    ................
  9f0000b0: 100001fa 00000000 100001f8 00000000    ................
  9f0000c0: 100001f6 00000000 100001f4 00000000    ................
  9f0000d0: 100001f2 00000000 100001f0 00000000    ................
  9f0000e0: 100001ee 00000000 100001ec 00000000    ................
  9f0000f0: 100001ea 00000000 100001e8 00000000    ................
  ```

12. If you are sure that everything went OK, you may reset the board using below command or just reset power:

  ```
  hornet> reset
  ```

### Using OpenWrt

**This method is recommended!**

Starting from official release "**[2014-11-19](https://github.com/pepe2k/u-boot_mod/releases/tag/2014-11-19)**", you will find ready **OpenWrt** images, with unlocked `u-boot` partition, embedded U-Boot image and dedicated small script for easy update process inside release tarball. All you need to do is download last release, select proper OpenWrt image for your device, install it and invoke one command: `u-boot-upgrade`:

```
root@OpenWrt:/# u-boot-upgrade

=================================================================
     DISCLAIMER: you are using this script at your own risk!

     The author of U-Boot modification and this script takes
     no responsibility for any of the results of using them.

          Updating U-Boot is a very dangerous operation
        and may damage your device! You have been warned!
=================================================================
   Are you sure you want to continue (type 'yes' or 'no')? yes
=================================================================

[ ok ] Found U-Boot image file: uboot_for_tp-link_tl-mr3020.bin
       Do you want to use this file (type 'yes' or 'no')? yes
[ ok ] MD5 checksum of new U-Boot image file is correct
[ ok ] Backup of /dev/mtd0 successfully created
       Do you want to store backup in /etc/u-boot_mod/backup/ (recommended, type 'yes' or 'no')? no
[ ok ] New U-Boot image successfully combined with backup file
[info] New U-Boot image is ready to be written into FLASH
       Are you sure you want to continue (type 'yes' or 'no')? yes
[ ok ] New U-Boot image successfully written info FLASH
[ ok ] MD5 checksum of mtd0 and new U-Boot image are equal
[info] Done!
```

### Using DD-WRT

**WARNING! This method is not recommended!**

1. Login into the router using telnet or SSH and find out which of the mtd partitions is the first one. In DD-WRT it is usally called `RedBoot`:

  ```
  root@DD-WRT:~# cat /proc/mtd
  dev:    size   erasesize  name
  mtd0: 00020000 00010000 "RedBoot"
  mtd1: 003c0000 00010000 "linux"
  mtd2: 002c0000 00010000 "rootfs"
  mtd3: 00010000 00010000 "ddwrt"
  mtd4: 00010000 00010000 "nvram"
  mtd5: 00010000 00010000 "board_config"
  mtd6: 00400000 00010000 "fullflash"
  mtd7: 00020000 00010000 "fullboot"
  ```

  In this case, for **TP-Link TL-MR3020**, the `RedBoot` partition is the one, which contains U-Boot and additional data (MAC address, model number, PIN).

  **Warning!** If size of the first partition is smaller than the size of the modified U-Boot image, you should not continue!

2. Using SCP or other method, transfer the new U-Boot image and corresponding MD5 file to the `/tmp` folder in device.

  ```
  root@DD-WRT:/tmp# ls -la
  [...]
  -rw-r--r--    1 root     root        125952 Nov  5  2015 uboot_for_tp-link_tl-mr3020.bin
  -rw-r--r--    1 root     root            66 Nov  5  2015 uboot_for_tp-link_tl-mr3020.md5
  [...]
  ```

3. Verify the MD5 sum of the image:

  ```
  root@DD-WRT:/tmp# md5sum uboot_for_tp-link_tl-mr3020.bin
  aaae0f772ce007f7d1542b9233dd765b  uboot_for_tp-link_tl-mr3020.bin

  root@DD-WRT:/tmp# cat uboot_for_tp-link_tl-mr3020.md5
  aaae0f772ce007f7d1542b9233dd765b *uboot_for_tp-link_tl-mr3020.bin
  ```

4. Make a backup of the current `RedBoot` partition (`mtd0`):

  ```
  root@DD-WRT:/tmp# dd if=/dev/mtd0 of=uboot_factory.bin
  256+0 records in
  256+0 records out
  ```

5. Using SCP or other method, transfer backuped `RedBoot` original partition to some safe place (I highly recommended you to save backup somewhere!).

6. You need to combine together original image and the one with U-Boot modification, but it seems that `dd` from DD-WRT does not support `conv=notrunc`, so we will use different approach:

  ```
  root@DD-WRT:/tmp# dd if=uboot_factory.bin of=uboot_rest.bin bs=1 skip=$(wc -c < uboot_for_tp-link_tl-mr3020.bin)
  5120+0 records in
  5120+0 records out

  root@DD-WRT:/tmp# cat uboot_for_tp-link_tl-mr3020.bin uboot_rest.bin > uboot_new.bin
  ```

7. **Danger**: This is the point of no return, if you have any errors or problems, please revert the original image at any time using:

  ```
  root@DD-WRT:/tmp# mtd write uboot_factory.bin "RedBoot"
  Unlocking RedBoot ...
  Writing from uboot_orig.bin to RedBoot ...
  ```

8. Now, to actually flash the new image, run:

  ```
  root@DD-WRT:/tmp# mtd write uboot_new.bin "RedBoot"
  Unlocking RedBoot ...
  Writing from uboot_new.bin to RedBoot ...
  ```

9. If you are sure that everything went OK, you may reboot the device:

  ```
  root@DD-WRT:/tmp# reboot
  ```

How to use it?
--------------

[TODO]

How to compile the code?
------------------------

### Building on Linux

You can use one of the free toolchains:

- Recommended and used for snapshots build: [LEDE SDK for AR71xx MIPS (trunk snapshot)](https://downloads.lede-project.org/snapshots/targets/ar71xx/generic/lede-sdk-ar71xx-generic_gcc-5.4.0_musl-1.1.15.Linux-x86_64.tar.bz2),
- [OpenWrt SDK for AR71xx MIPS (Chaos Calmer release)](https://downloads.openwrt.org/chaos_calmer/15.05.1/ar71xx/generic/OpenWrt-SDK-15.05.1-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64.tar.bz2),
- [OpenWrt Toolchain for AR71xx MIPS (trunk snapshot)](https://downloads.openwrt.org/snapshots/trunk/ar71xx/generic/OpenWrt-Toolchain-ar71xx-generic_gcc-5.3.0_musl-1.1.15.Linux-x86_64.tar.bz2),
- [ELDK (Embedded Linux Development Kit)](http://bit.ly/2djaTMn),
- or any others...

I am using **OpenWrt Toolchain for AR71xx MIPS** (32-bit, virtual machine) and all released binary images were/will be built using this set.

All you need to do, after choosing a toolchain, is to modify [Makefile](Makefile) - change or remove `export MAKECMD` and if needed add `export PATH`. For example, to use OpenWrt Toolchain instead of Sourcery CodeBench Lite, download it and extract into `toolchain` folder, inside the top dir and change first lines in [Makefile](Makefile):

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

### Building on macOS (OS X)

You can build using the OpenWrt/LEDE toolchain as above under macOS (OS X) as long as you install several gnu command line tools via brew. Note that bash is required to correct the usage of colorized echo output within the Makefiles (I was suprised how inconsistent FreeBSD is with Linux/GNU in this regard).

```
brew install bash coreutils gnu-sed
```

Subsequently, in addition to the toolchain being in your path, you will need to point your path as instructed by brew to the gnu binaries (only required for the build).

```
export PATH=/usr/local/opt/coreutils/libexec/gnubin:/usr/local/opt/gnu-sed/libexec/gnubin:$PATH
```

This process was tested on Yosemite and El Capitan.

FAQ
---

#### 1. My device is not supported, but has the same hardware as one in the list, can I use this modification?

*It could be dangerous! I know that a lot of routers uses the same hardware - for example, TP-Link has a battery powered routers set, which contains: TL-MR10U, TL-MR11U (TL-MR3040 in Europe) TL-MR12U and TL-MR13U. All of them has the same platform: Atheros AR9331 with 32 MiB of DDR RAM and 4 MiB of SPI NOR FLASH. But, there may exist a slight difference, like GPIO pin number for reset button or LED(s), that may cause problems.*

*You can try, but remember that you are doing this only at your own risk!*

#### 2. I want to overclock my router, how can I do this?

*Currently, this option is available only for routers with Atheros AR9331 (please, look at [ap121.h](u-boot/include/configs/ap121.h) file which contains all information about PLL register configuration and an untypical clocks for CPU, RAM and AHB). What more, you will need to compile the code yourself, because I will not publish images with non-default clocks.*

*And again, remember that you are doing this only at your own risk!*

#### 3. Do you test all prebuilt images before you publish them?

*No, because I do not have all supported devices, only few of them. But, I make tests for every supported SoC types.*

#### 4. I would like you to add support for device X.

*You can do it yourself and send me a pull request or a patch. If you do not want to, or do not know how to do it, please contact with me directly.*

#### 5. My device does not boot after upgrade!

*I told you... bootloader, in this case U-Boot, is the most important piece of code inside your device. It is responsible for hardware initialization and booting an OS (kernel in this case), i.e. it is the bridge head for delegating to / flashing kernel and rootfs images. So, if during the upgrade something went wrong, your device will not boot any more. The only way to recover from such a situation in a mild way is via a JTAG adapter connection. In case of a lack of JTAG connection, you would even need to remove the FLASH chip, load proper image using an external programmer and solder it back.*

License, outdated sources etc.
------------------------------

**[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** project is Free Software, licensed under version 2 of the **GNU General Public License**. All information about license, contributors etc., are included with sources, inside *u-boot* folder.

You should know, that most routers, especially those based on Atheros SoCs, uses very old versions of U-Boot (1.1.4 is from 2005/2006). So, *these sources are definitely outdated* (do not even try to merge them with official release), but it was easier for me to modify them, than move TP-Link/Atheros changes to the current version. Moreover, lot of unnecessary code fragments and source files were removed for ease of understanding the code.

Credits
-------

- Thanks to M-K O'Connell for donating a router with QCA9563
- Thanks to Krzysztof M. for donating a TL-WDR3600 router
- Thanks to *pupie* from OpenWrt forum for his great help
- Thanks for all donators and for users who contributed in code development
