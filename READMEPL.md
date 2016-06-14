Modyfikacja U-Boot 1.1.4 dla routerów
==========

Spis treści
-----------

- [Wstęp](#wstęp)
- [Wspierane urządzenia](#wspierane-urządzenia)
- [Znane błędy](#znane-błędy)
- [Modyfikacje, zmiany](#modyfikacje-zmiany)
	- [Serwer web](#serwer-web)
	- [Konsola sieciowa](#konsola-sieciowa)
	- [Zapisywalne zmienne środowiskowe](#zapisywalne-zmienne-środowiskowe)
	- [Inne](#inne)
	- [Automatycznie rozpoznawane kości FLASH](#automatycznie-rozpoznawane-kości-flash)
- [Jak to zainstalować?](#jak-to-zainstalować)
	- [Uwagi, kopie zapasowe](#uwagi-kopie-zapasowe)
	- [Przy pomocy programatora FLASH](#przy-pomocy-programatora-flash)
	- [Przy pomocy UART, konsoli U-Boot i serwera TFTP](#przy-pomocy-uart-konsoli-u-boot-i-serwera-tftp)
		- [Ważna informacja!](#ważna-informacja)
		- [Instrukcja krok po kroku](#instrukcja-krok-po-kroku)
	- [Przy pomocy OpenWrt](#przy-pomocy-openWrt)
	- [Przy pomocy DD-WRT](#przy-pomocy-dd-wrt)
- [Jak korzystać z tej modyfikacji?](#jak-korzystać-z-tej-modyfikacji)
- [Jak samodzielnie skompilować kod?](#jak-samodzielnie-skompilować-kod)
- [FAQ](#faq)
- [Licencja, przestarzałe źródła itd.](#licencja-przestarzałe-źródła-itd)
- [Podziękowania](#podziękowania)

Wstęp
-----

W dużym skrócie, projekt ten jest modyfikacją źródeł **U-Boot 1.1.4**, przede wszystkim z archiwum udostęþnionego przez firmę **TP-Link**. Niektóre fragmenty kodu zostały zaczerpnięte również ze źródeł innych producentów, takich jak **D-Link**, **Netgear**, **ZyXEL** i **Belkin**. Wszystkie te firmy korzystają z SDK Qualcomm/Atheros, które zawiera właśnie zmodyfikowane źródła **U-Boot 1.1.4**.

Oryginalne wersje źródeł można pobrać z poniższych stron:

- [TP-Link GPL Code Center](http://www.tp-link.com/en/support/gpl/ "TP-Link GPL Code Center")
- [D-Link GPL Source Code Support](http://tsd.dlink.com.tw/GPL.asp "D-Link GPL Source Code Support")
- [NETGEAR Open Source Code for Programmers (GPL)](http://kb.netgear.com/app/answers/detail/a_id/2649/~/netgear-open-source-code-for-programmers-%28gpl%29 "NETGEAR Open Source Code for Programmers (GPL)")
- [ZyXEL GPL-OSS](http://www.zyxel.com/us/en/form/gpl_oss_form.shtml "ZyXEL GPL-OSS")
- [Belkin Open Source Code Center](http://www.belkin.com/us/support-article?articleNum=51238 "Belkin Open Source Code Center")


Pomysł na tę modyfikację został zaczerpnięty z innego projektu, przeznaczonego dla bardzo popularnego, małego routera mobilnego **TP-Link TL-WR703N**, w którym autor umieścił tryb ratunkowy dostępny przez przeglądarkę: **[wr703n-uboot-with-web-failsafe](http://code.google.com/p/wr703n-uboot-with-web-failsafe/)**. Przez jakiś czas z powodzeniem używałem tej modyfikacji, ale postanowiłem ją ulepszyć, dodać kilka opcji i wsparcie dla innych modeli oraz wszystkich przeglądarek.

Pierwszą wersję mojej modyfikacji zaprezentowałem na forum **OpenWrt**, w [tym wątku](https://forum.openwrt.org/viewtopic.php?id=43237), pod koniec marca 2013 roku. Zawierała ona wsparcie wyłącznie dla modeli TP-Link z układem SoC **Atheros AR9331**. Obecnie, wspierane są również urządzenia innych producentów, w tym z układami SoC **Atheros AR934x**, **Qualcomm Atheros QCA953x**, **Qualcomm Atheros QCA955x**, a inne (w najbliższych planach jest wsparcie dla routerów z układami z serii **Qualcomm Atheros QCA956x** oraz **MediaTek MT762x**) są w trakcie opracowania.

Dodatkowe informacje o niniejszej modyfikacji można znaleźć również na [moim blogu](http://www.tech-blog.pl), w [tym artykule](http://www.tech-blog.pl/2013/03/29/zmodyfikowany-u-boot-dla-routerow-tp-link-z-atheros-ar9331-z-trybem-aktualizacji-oprogramowania-przez-www-i-konsola-sieciowa-netconsole/).

Jeżeli spodobał Ci się ten projekt i chciałbyś wspomóc mnie w jego dalszym rozwijaniu - [postaw mi piwo](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=FN3XW36YHSY2S&lc=US&item_name=For%20a%20great%20job%21&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_LG%2egif%3aNonHosted)!

Wspierane urządzenia
--------------------

Lista obecnie wspieranych urządzeń:

- **Atheros AR9331**:
  - 8devices Carambola 2 (w wersji z płytką developerską, [zdjęcia w mojej galerii](http://galeria.tech-blog.pl/8devices_Carambola_2/))
  - TP-Link TL-MR3020 v1 ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/TPLINK_TL-MR3020/))
  - TP-Link TL-MR3040 v1 i v2
  - TP-Link TL-WR703N v1, ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/TPLINK_TL-WR703N/))
  - TP-Link TL-WR720N v3 (wersja przeznaczona na rynek chiński)
  - TP-Link TL-WR710N v1 (wersja przeznaczona na rynek europejski, [zdjęcia w mojej galerii](http://galeria.tech-blog.pl/TP-Link_TL-WR710N-EU/))
  - TP-Link TL-MR10U v1 ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/TP-Link_TL-MR10U/))
  - TP-Link TL-MR13U v1
  - TP-Link TL-WR740N v4 (i podobne, jak na przykład TL-WR741ND v4)
  - TP-Link TL-MR3220 v2
  - Moduł GS-Oolite/Elink EL-M150 na płytce developerskiej ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/Elink_EL-M150_Development-Board/))
  - Dragino 2 (MS14)
  - Village Telco Mesh Potato 2 (bazuje na Dragino MS14)
  - GL.iNet 64xxA ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/GLiNet/))
  - Black Swift

- **Atheros AR1311 (bliźniaczy układ AR9331)**
  - D-Link DIR-505 H/W ver. A1 ([zdjęcia w mojej galerii](http://galeria.tech-blog.pl/D-Link_DIR-505/))

- **Atheros AR9341**:
  - TP-Link TL-MR3420 v2
  - TP-Link TL-WR841N/D v8
  - TP-Link TL-WA830RE v2
  - TP-Link TL-WA801ND v2

- **Atheros AR9344**:
  - TP-Link TL-WDR3600 v1
  - TP-Link TL-WDR43x0 v1
  - TP-Link TL-WDR3500 v1

- **Qualcomm Atheros QCA953x**:
  - TP-Link TL-WR841N/D v9
  - TP-Link TL-WR820N (wersja przeznaczona na rynek chiński)
  - TP-Link TL-WR802N
  - Wallys DR531

Przetestowałem swoją modyfikację na większości z wymienionych powyżej urządzeń, z obrazami OpenWrt i oficjalnym firmware producenta. Jeżeli nie jesteś pewien wersji sprzętowej swojego urządzenia, proszę skontaktuj się ze mną **zanim** dokonasz wymiany obrazu bootloadera. Zmiana na niewłaściwą wersję najprawdopodobniej doprowadzi do uszkodzenia Twojego urządzenia i jedyną możliwością jego ponownego uruchomienia będzie przeprogramowanie kości FLASH w zewnętrznym programatorze.

Dodatkowe informacje o wspieranych urządzeniach:

| Model | SoC | FLASH | RAM | Obraz U-Boot | U-Boot env |
|:--- | :--- | ---: | ---: | ---: | ---: |
| [8devices Carambola 2](http://8devices.com/carambola-2) | AR9331 | 16 MiB | 64 MiB DDR2 | 256 KiB | 64 KiB, R/W |
| [TP-Link TL-MR3020 v1](http://wiki.openwrt.org/toh/tp-link/tl-mr3020) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3040 v1/2](http://wiki.openwrt.org/toh/tp-link/tl-mr3040) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR703N](http://wiki.openwrt.org/toh/tp-link/tl-wr703n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR720N v3](http://wiki.openwrt.org/toh/tp-link/tl-wr720n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR710N v1](http://wiki.openwrt.org/toh/tp-link/tl-wr710n) | AR9331 | 8 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR10U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr10u) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR13U v1](http://wiki.openwrt.org/toh/tp-link/tl-mr13u) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR740N v4](http://wiki.openwrt.org/toh/tp-link/tl-wr740n) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-MR3220 v2](http://wiki.openwrt.org/toh/tp-link/tl-mr3420) | AR9331 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| GS-Oolite/Elink EL-M150 module | AR9331 | 4/8/16 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [Dragino 2 (MS14)](http://wiki.openwrt.org/toh/dragino/ms14) | AR9331 | 16 MiB | 64 MiB DDR1 | 192 KiB | R/W |
| Village Telco Mesh Potato 2 | AR9331 | 16 MiB | 64 MiB DDR1 | 192 KiB | R/W |
| [GL.iNet](http://wiki.openwrt.org/toh/gl-inet/gl-inet) | AR9331 | 8/16 MiB | 64 MiB DDR1 | 64 KiB | RO |
| [Black Swift](http://www.black-swift.com) | AR9331 | 16 MiB | 64 MiB DDR2 | 128 KiB, LZMA | R/W |
| [TP-Link TL-MR3420 v2](http://wikidevi.com/wiki/TP-LINK_TL-MR3420_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR841N/D v8](http://wiki.openwrt.org/toh/tp-link/tl-wr841nd) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WA830RE v2](http://wikidevi.com/wiki/TP-LINK_TL-WA830RE_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WA801ND v2](http://wikidevi.com/wiki/TP-LINK_TL-WA801ND_v2) | AR9341 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR3600 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3600) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR43x0 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr4300) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WDR3500 v1](http://wiki.openwrt.org/toh/tp-link/tl-wdr3500) | AR9344 | 8 MiB | 128 MiB DDR2 | 64 KiB, LZMA | RO |
| [D-Link DIR-505 H/W ver. A1](http://wiki.openwrt.org/toh/d-link/dir-505) | AR1311 | 8 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR841N/D v9](https://wiki.openwrt.org/toh/tp-link/tl-wr841nd) | QCA9533 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR820N](https://wiki.openwrt.org/toh/tp-link/tl-wr820n) | QCA9531 | 4 MiB | 64 MiB DDR2 | 64 KiB, LZMA | RO |
| [TP-Link TL-WR802N](https://wikidevi.com/wiki/TP-LINK_TL-WR802N_v1.0) | QCA9533 | 4 MiB | 32 MiB DDR1 | 64 KiB, LZMA | RO |
| Wallys DR531 | QCA9531 | 8 MiB | 64 MiB DDR2 | 192 KiB | R/W |

*(LZMA) - obraz binarny U-Boot został dodatkowo skompresowany przy pomocy LZMA.*  
*(R/W) - zmienne środowiskowe przechowywane są w osobnym bloku FLASH, co pozwala na ich zachowanie po odłączeniu zasilaniu.*  
*(RO) - zmienne środowiskowe są wbudowane w obraz binarny, można je zmieniać i dodawać nowe wyłącznie w trakcie pracy urządzenia, po ponownym uruchomieniu zostaną przywrócone domyślne wartości.*

Znane błędy
-----------

Dostępna obecnie wersja nie ładuje jądra Linuxa z niektórych wydań oficjalnego firmware TP-Link. Jeżeli zamierzasz używać OFW, w którymś ze wspieranych modeli tego producenta, nie używaj mojej modyfikacji. Pracuję nad rozwiązaniem tego problemu.

Modyfikacje, zmiany
-------------------

### Serwer web

Najistotniejszą zmianą jest dodanie serwera web, bazującego na **[stosie TCP/IP uIP 0.9](http://www.gaisler.com/doc/net/uip-0.9/doc/html/main.html)**. Umożliwia to aktualizację obrazów **firmware**, **U-Boot** i **ART** (Atheros Radio Test) bezpośrednio z poziomu przeglądarki, bez potrzeby dostępu do konsoli szeregowej i uruchamiania serwera TFTP. Podobny tryb ratunkowy, również bazujący na stosie TCP/IP uIP 0.9, dostępny jest od dawna w routerach **D-Link**.

Serwer posiada 7 stron www:

1. index.html (aktualizacja obrazu firmware, zrzut ekranu poniżej)
2. uboot.html (aktualizacja obrazu U-Boot)
3. art.html (aktualizacja danych kalibracyjnych ART)
4. flashing.html
5. 404.html
6. fail.html
7. style.css

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_firmware_upgrade.jpg)

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_firmware_upgrade_progress.jpg)

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2015/11/uboot_mod_uboot_upgrade.jpg)

### Konsola sieciowa

Drugą, równie użyteczną opcją, jest konsola sieciowa (wchodzi ona w skład oficjalnej gałęzi U-Boot, ale nie jest domyślnie dostępna w żadnym ze wspieranych urządzeń). Konsola sieciowa umożliwia komunikację z konsolą U-Boot przez sieć Ethernet, wykorzystując protokół UDP (domyślny port: 6666, adres IP routera: 192.168.1.1).

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2013/04/u-boot_mod_for_tp-link_with_ar9331_netconsole.jpg)

### Zapisywalne zmienne środowiskowe

U-Boot wykorzystuje tak zwane "**zmienne środowiskowe**", w których przechowywane są wartości wielu ustawień, takich jak adresy IP urządzenia i serwera zdalnego dla transakcji TFTP, prędkość konsoli szeregowej, polecenie do załadowania kernela itd. Zmienne te zapisywane są zazwyczaj w osobnym sektorze FLASH lub w jego części, co umożliwia zachowanie zmian na stałe.

Żaden z popularnych producentów nie udostępnia tej funkcjonalności i w swoich wersjach U-Boot wykorzystuje zmienne środowiskowe "**tylko do odczytu**" (wartości zmiennych są wbudowane w obraz U-Boot), co oznacza że wszelkie zmiany wprowadzone w trakcie pracy bootloadera zostaną utracone po ponownym uruchomieniu urządzenia i nie ma żadnej możliwość zapisania ich w pamięci FLASH.

Ta modyfikacja używa zapisywalnych zmiennych środowiskowych w prawie wszystkich wspieranych urządzeniach, co daje możliwość wykonania na przykład:

```
uboot> setenv ipaddr 192.168.1.100
uboot> saveenv
Saving environment to FLASH...

Erase FLASH from 0x9F010000 to 0x9F01FFFF in bank #1
Erasing: #

Erased sectors: 1

Writting at address: 0x9F010000

uboot> reset
```

Spowoduje to zmianę adresu IP urządzenia i zapisanie zmienionych zmiennych środowiskowych we FLASH. Od kolejnego uruchomienia urządzenie będzie wykorzystywać nowy adres.

Wykorzystując polecenie **run** i zmienne środowiskowe możesz pisać niestandardowe, niewielkie skrypty jak ten poniżej, wykorzystywany do aktualizacji firmware metodą TFTP:

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
Writting at address: 0x9F020000

Done!

OK!
uboot>
```

### Inne

Ponadto:

- Przyspieszony start
- Nieistotne informacje wyświetlane w konsoli podczas uruchamiania zostały usunięte
- Automatyczne rozpoznawanie zastosowanej kości FLASH na podstawie JEDEC ID
- MAC adres dla interfejsów sieciowych jest pobierany z FLASH, a nie ustawiany na sztywno
- Ładowanie firmware może być przerwane przy pomocy dowolnego klawisza
- Lepszy sterownik konsoli szeregowej UART ze wsparciem dla wielu prędkości
- Wciśnij i przytrzymaj przycisk aby uruchomić:
  - Werwer web (min. 3 sekundy)
  - Konsolę szeregową U-Boot (min. 5 sekundy)
  - Konsolę sieciową U-Boot (min. 7 sekundy)
- Dodatkowe komendy (w odniesieniu do wersji producenta; dostępność zależy od modelu):
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
- Możliwości overclockingu i underclockingu (aktualnie tylko w modelach z SoC AR9331)

### Automatycznie rozpoznawane kości FLASH

Automatyczna detekcja typu zastosowanej kości FLASH może być bardzo przydatna jeżeli wymieniłeś FLASH w swoim routerze. Nie musisz dokonywać zmian w oficjalnych źródłach i kompilować ich żeby mieć dostęp do całej zawartości FLASH z poziomu konsoli U-Boot.

Jeżeli wykorzystasz kość, której nie ma na poniższej liście, moja wersja U-Boot spróbuje odczytać jej parametry wykorzystując standard **Serial Flash Discoverable Parameter** (**SFDP**, więcej informacji: https://www.jedec.org/standards-documents/docs/jesd216b). Jeżeli Twoja kość nie wspiera SFDP, ta modyfikacja będzie traktować ją tak jakby miała rozmiar zgodny z rozmiarem domyślnie zastosowanej kości w danym modelu. W większości urządzeń nie będziesz też miał możliwości aktualizacji obrazu danych kalibracyjnych układu radiowego (ART).

Pełna lista obsługiwanych kości FLASH:

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
- Macronix MX25L128 (16 MB, JEDEC ID: C2 2018, C2 2618)
- Spansion S25FL127S (16 MB, JEDEC ID: 01 2018)*
- Micron N25Q128 (16 MB, JEDEC ID: 20 BA18)

(*) przetestowane

Jeżeli na powyższej liście nie ma kostki, którą chciałbyś zastosować, lub z jakiegoś innego powodu masz co do niej wątpliwości - skontaktuj się ze mną. Ewentualnie, możesz samemu dokonać odpowiednich zmian w kodzie i przesłać mi gotową łatę lub zgłosić pull request.

Jak to zainstalować?
--------------------

### Uwagi, kopie zapasowe

**Robisz to wyłącznie na własną odpowiedzialność!**   
**Jeżeli popełnisz jakiś błąd lub coś pójdzie nie tak w trakcie aktualizacji, w najgorszym przypadku, Twój router nie uruchomi się już ponownie!**

Wykonywanie kopii zapasowych jest dobrą praktyką, dlatego zalecam Ci skopiowanie zawartości oryginalnego obrazu/partycji U-Boot (szczególnie w przypadku routerów TP-Link), **zanim** wykonasz jakiekolwiek zmiany. Przykładowo, wykorzystując OpenWrt (na przykładzie TP-Link TL-WR703N z kością FLASH 16 MiB):

```
cat /proc/mtd
```

Komenda ta wyświetli listę wszystkich partycji **MTD** (Memory Technology Device):

```
dev:    size   erasesize  name
mtd0: 00020000 00010000 "u-boot"
mtd1: 000eeb70 00010000 "kernel"
mtd2: 00ee1490 00010000 "rootfs"
mtd3: 00c60000 00010000 "rootfs_data"
mtd4: 00010000 00010000 "art"
mtd5: 00fd0000 00010000 "firmware"
```

Jak widać powyżej, partycja o nazwie `u-boot` ma rozmiar **0x20000** (128 KiB), z kolei publikowane przeze mnie gotowe obrazy dla tego modelu mają mniejszy rozmiar: **0x1EC00** (123 KiB). Jest to bardzo istotna różnica i powinieneś o niej pamiętać, jeżeli do zmiany U-Boot zamierzasz wykorzystać narzędzie `mtd` lub konsolę szeregową i wiersz poleceń U-Boot.

W celu skopiowania zawartości partycji `u-boot` do pamięci RAM, wykonaj:

```
cat /dev/mtd0 > /tmp/uboot_backup.bin
```

Następnie połącz się z routerem przy pomocy `protokołu SCP` i pobierz `/tmp` na dysk lokalny plik `uboot_backup.bin`.

### Przy pomocy programatora FLASH

Jeżeli dysponujesz programatorem kości FLASH (wszystkie wspierane urządzenia posiadają kości typu **SPI NOR FLASH**), najpewniej wiesz jak z niego korzystać. Pobierz archiwum zawierające gotowe obrazy binarne lub samodzielnie skompiluj kod źródłowy, wybierz odpowiedni plik dla swojego urządzenia i wgraj go na sam początek kości (ofset `0x00000`). Musisz pamiętać jedynie o skasowaniu bloku(ów) przed wgraniem obrazu - jeżeli wykorzystujesz gotowe oprogramowanie dla programatora, w trybie automatycznym, prawdopodobnie odpowiedni obszar zostanie automatycznie wykasowany przed wgraniem wskazanego obrazu.

Wszystkie publikowane przeze mnie gotowe obrazy binarne są dopełnione wartościami 0xFF i od zmiany "**![Extend maximum U-Boot image size up to 123 KB](https://github.com/pepe2k/u-boot_mod/commit/7829f50c0e92024fde613cb01e65cbdeae1f126b)**", dla większości wspieranych urządzeń, **nie są już wielokrotnością rozmiaru pojedynczego bloku 64 KiB**. Przykładowo, **TP-Link** w większości swoich nowych urządzeń wykorzystuje tylko pierwszy **64 KiB** blok do przechowywania skompresowanego obrazu U-Boot. W kolejnym 64 KiB bloku umieszcza takie informacje jak adres MAC, numer i wersję modelu oraz czasami pin WPS. Ta modyfikacja wykorzystuje oba sektory na obraz U-Boot oraz dodatkowe dane, w tym niewielki blok na zapisywalne zmienne środowiskowe.

Poniższy fragment początkowy mapy pamięci FLASH dla modelu TP-Link TL-MR3020 pokazuje różnice pomiędzy wersją producenta i modyfikacją.

![](http://www.tech-blog.pl/wordpress/wp-content/uploads/2016/03/mr3020_u-boot-modification_flash-map_comparison.png)

Z drugiej strony, obraz U-Boot w module **8devices Carambola 2** może mieć maksymalnie **256 KiB** (4 bloki po 64 KiB każdy), ale obraz nie jest skompresowany. Zaraz za nim, w kolejnym 64 KiB bloku, znajdują się zmienne środowiskowe - partycja ta w OpenWrt, w tym konkretnym przypadku, nosi nazwę `u-boot-env`:

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

### Przy pomocy UART, konsoli U-Boot i serwera TFTP

**UWAGA! Ta metoda jest zdecydowanie niezalecana!**

Jest to prawdopodobnie najczęściej wykorzystywana metoda do wgrania firmware w przypadku problemów z uruchomieniem wersji znajdującej się w urządzeniu lub po nieudanej aktualizacji. Istotną wadą tego podejścia jest potrzeba rozebrania routera i połączenia się z nim przy pomocy interfejsu szeregowego UART (w przypadku Carambola 2 w wersji z płytką developerską sprawa jest ułatwiona, ponieważ adapter USB-UART bazujący na FTDI FT232RQ znajduje się już na PCB).

#### Ważna informacja!

Wszystkie wspierane urządzenia posiadają sprzętowy interfejs UART, zintegrowany wewnątrz układu SoC, pracujący w zakresie napięcia około 3,3 V (w istocie, wyprowadzenia GPIO mogą pracować przy takim napięciu, ale w rzeczywistości, zgodnie z dokumentacją części układów zastosowanych we wspieranych modelach, porty GPIO zasilane są z wewnętrznego stabilizatora o napięciu wyjściowym 2,62 V)!

**Nie podłączaj** bezpośrednio żadnego interfejsu RS232 pracującego przy napięciu +/- 12 V lub innego adaptera, bez odpowiedniego konwertera poziomów napięć, ponieważ może to doprowadzić do trwałego uszkodzenia Twojego routera. Najlepiej będzie jeżeli wykorzystasz dowolny adapter USB-UART, który posiada zintegrowany konwerter 3,3 V. Pamiętaj również, że w przypadku korzystania z takiego adaptera powinieneś **podłączyć wyłącznie sygnały RX, TX i GND**. **NIGDY** nie łącz razem sygnału zasilania (VCC) z routera i adaptera, chyba że wiesz co robisz! Połączenie tych sygnałów w najgorszym wypadku może spowodować uszkodzenie adaptera, a w najgorszym - również routera! Wykorzystując adapter USB-UART powinieneś zasilić go z gniazda USB w komputerze, a router z oryginalnego zasilacza sieciowego (lub z gniazda USB jeżeli urządzenie jest zasilane w taki sposób).

Od dłuższego czasu i bez żadnych problemów używam bardzo prostego i wyjątkowo taniego (w granicach 1-2 USD) adaptera bazującego na układzie **CP2102**. Po więcej informacji o interfejsie UART w routerach możesz sięgnąć do artykułu [Serial Console](http://wiki.openwrt.org/doc/hardware/port.serial) w OpenWrt Wiki.

#### Instrukcja krok po kroku

1. Zainstaluj i skonfiguruj na swoim PC dowolny **serwer TFTP** (dla systemów z rodziny Windows sugeruję [TFTP32](http://tftpd32.jounin.net)).

2. Ustaw stały adres IP na swoim PC (w poniższej instrukcji wykorzystamy **192.168.1.2** dla PC i **192.168.1.1** dla routera) i połącz go z routerem przy pomocy kabla sieciowego RJ45 (powinieneś wykorzystać w routerze jedno z gniazd LAN, ale WAN również powinien działać).

3. Podłącz do PC i skonfiguruj adapter USB-UART oraz uruchom program do komunikacji z nim, np. [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html).   
Skonfiguruj program do używania takich ustawień:
  * Baud rate: 115200
  * Data bits: 8
  * Parity control: none
  * Stop bits: 1
  * Handshaking: none
4. Uruchom router, zaczekaj na wyświetlenie się jednego z poniższych komunikatów i przerwij proces ładowania firmware:

  `Autobooting in 1 seconds` (głównie routery **TP-Link**, w tym momencie powinieneś wpisać `tpl`)   
  `Hit ESC key to stop autoboot:  1` (**8devices Carambola 2**, wciśnij klawisz `ESC`)   
  `Hit any key to stop autoboot:  1` (**D-Link DIR-505**, wciśnij dowolny klawisz)

5. Ustaw zmienne środowiskowe `ipaddr` i `serverip`, tak jak poniżej:

  ```
  hornet> setenv ipaddr 192.168.1.1
  hornet> setenv serverip 192.168.1.2
  ```
6. Sprawdź czy zmiany zostały wprowadzone:

  ```
  hornet> printenv ipaddr
  ipaddr=192.168.1.1
  hornet> printenv serverip
  serverip=192.168.1.2
  ```

7. Ze względu na różnice w mapie pamięci i rozmiarze obrazu oryginalnej i zmodyfikowanej wersji U-Boot, musisz najpierw wykonać kopię zapasową partycji z oryginalną wersją, w pamięci RAM. **Pominięcie lub nieprawidłowe wykonanie tego kroku prawdopodobnie zakończy się uszkodzeniem Twojego urządzenia!**

  Ten krok różni się w zależności od modelu, dlatego powinieneś zwrócić szczególną uwagę na rozmiar obrazu zmodyfikowanej wersji, **zaokrąglić go w górę, do najbliższej wielokrotności 64 KiB** i używać tej wartości we wszystkich kolejnych krokach.

  Przykładowo, jeżeli obraz modyfikacji ma **123 KiB** (**0x1EC00**) powinieneś najpierw wykonać kopię zapasową **128 KiB** (**0x20000**) w pamięci RAM, pod tym samym adresem, do którego później zostanie pobrany ten obraz:

  ```
  hornet> cp.b 0x9F000000 0x80800000 0x20000
  ```

  Wykorzystanie tego samego adresu w pamięci RAM spowoduje "sklejenie" obu obrazów i zachowanie dodatkowych, oryginalnych danych, takich jak adres MAC, numer modelu i PIN.

8. Pobierz z serwera TFTP i umieść w pamięci RAM urządzenia właściwy dla swojego modelu obraz U-Boot, wykorzystując polecenie `tftpboot` (na przykładzie **TP-Link TL-MR3020**):

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

9. Kolejny krok jest bardzo ryzykowny! Wykonując następne polecenia, najpierw skasujesz oryginalny obraz U-Boot z pamięci FLASH, a następnie skopiujesz w to miejsce nowy obraz, z pamięci RAM. Jeżeli w trakcie tego procesu coś pójdzie nie tak (na przykład dojdzie do awarii zasilania), Twój router najprawdopodobniej już się nie uruchomi ponownie!

  Powinieneś też zwrócić uwagę na rozmiar i wykorzystać wartość, którą obliczyłeś w kroku 7. We wszystkich przypadkach, adres początkowy pamięci FLASH i RAM to odpowiednio: **0x9F000000** i **0x80000000**. Jak mogłeś zauważyć, w poprzednim kroku, do zapisania pobranego przez sieć obrazu, nie wykorzystałem początkowego adresu pamięci RAM i również nie powinieneś tego robić.

  Nie popełnij żadnych błędów w rozmiarach i adresach (ofsetach), w kolejnych krokach!

10. Skasuj odpowiedni obszar w pamięci FLASH (to polecenie usunie oryginalny obraz U-Boot!):

  ```
  hornet> erase 0x9F000000 +0x20000

  First 0x0 last 0x1 sector size 0x10000
  Erased 2 sectors
  hornet>
  ```

11. W tej chwili Twój router nie posiada żadnego bootloadera, dlatego skopiuj do FLASH z pamięci RAM pobrany wcześniej, nowy obraz:

  ```
  hornet> cp.b 0x80800000 0x9F000000 0x20000

  Copy to Flash... write addr: 9f000000
  done
  ```

12. Jeżeli chcesz, możesz wyświetlić w konsoli U-Boot zawartość pamięci FLASH i porównać ją z obrazem na komputerze. W tym celu należy skorzystać z komendy `md`, która spowoduje wyświetlenie 256 bajtów danych w postaci szesnastkowej i tekstowej, począwszy od podanego w argumencie adresu. Kolejne wywołanie tego samego polecenia, tym razem bez parametru, spowoduje wyświetlenie kolejnej porcji danych.

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

13. Jeżeli jesteś pewien, że wszystko przebiegło prawidłowo, możesz zrestartować urządzenie przy pomocy poniższego polecenia lub restartując zasilanie:

  ```
  hornet> reset
  ```

### Przy pomocy OpenWrt

**Ta metoda jest zalecana!**

Począwszy od oficjalnego wydania "**[2014-11-19](https://github.com/pepe2k/u-boot_mod/releases/tag/2014-11-19)**", wewnątrz archiwum znajdziesz przygotowane obrazy **OpenWrt** z odblokowaną możliwością zapisu na partycji `u-boot`, gotowym obrazem U-Boot oraz niewielkim, dedykowanym skryptem do prostej aktualizacji bootloadera. Jedyne, co należy zrobić to pobrać ostatnie oficjalne wydanie tej modyfikacji, wybrać i zainstalować odpowiedni obraz OpenWrt i wywołać skrypt poleceniem `u-boot-upgrade`:

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

### Przy pomocy DD-WRT

**UWAGA! Ta metoda jest niezalecana!**

1. Zaloguj się do routera przy pomocy SSH lub telnetu i sprawdź, która z partycji mtd jest pierwsza. W DD-WRT najczęściej będzie to `RedBoot`:

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

  W przypadku **TP-Link TL-MR3020**, partycja `RedBoot` zawiera obraz U-Boot oraz dodatkowe dane, takie jak adres MAC, numer modelu oraz PIN.

  **Uwaga!** Jeżeli rozmiar pierwszej partycji jest mniejszy niż rozmiar obrazu zmodyfikowanej wersji U-Boot, nie kontynuuj!

2. Przy pomocy SCP lub innej metody skopiuj obraz U-Boot i odpowiedni plik z sumą MD5 do folderu `/tmp` na urządzeniu.

  ```
  root@DD-WRT:/tmp# ls -la
  [...]
  -rw-r--r--    1 root     root        125952 Nov  5  2015 uboot_for_tp-link_tl-mr3020.bin
  -rw-r--r--    1 root     root            66 Nov  5  2015 uboot_for_tp-link_tl-mr3020.md5
  [...]
  ```

3. Sprawdź sumę kontrolną MD5 pliku z obrazem:

  ```
  root@DD-WRT:/tmp# md5sum uboot_for_tp-link_tl-mr3020.bin
  aaae0f772ce007f7d1542b9233dd765b  uboot_for_tp-link_tl-mr3020.bin

  root@DD-WRT:/tmp# cat uboot_for_tp-link_tl-mr3020.md5
  aaae0f772ce007f7d1542b9233dd765b *uboot_for_tp-link_tl-mr3020.bin
  ```

4. Utwórz kopię zapasową partycji `RedBoot` (`mtd0`):

  ```
  root@DD-WRT:/tmp# dd if=/dev/mtd0 of=uboot_factory.bin
  256+0 records in
  256+0 records out
  ```

5. Przy pomocy SCP lub innej metody, skopiuj utworzoną kopię zapasową w jakieś bezpieczne miejsce (zdecydowanie zalecam zapisanie gdzieś tego pliku!).

6. Potrzebujesz utworzyć plik składający się z oryginalnego i zmodyfikowaneg obrazu, ale `dd` z DD-WRT prawdopodobnie nie obsługuje `conv=notrunc`, dlatego wykorzystamy inne podejście:

  ```
  root@DD-WRT:/tmp# dd if=uboot_factory.bin of=uboot_rest.bin bs=1 skip=$(wc -c < uboot_for_tp-link_tl-mr3020.bin)
  5120+0 records in
  5120+0 records out

  root@DD-WRT:/tmp# cat uboot_for_tp-link_tl-mr3020.bin uboot_rest.bin > uboot_new.bin
  ```

7. **Uwaga**: To jest punkt bez powrotu. Jeżeli podczas dotychczasowych kroków wystąpiły jakieś błędy lub problemy, wgraj kopię oryginalnej partycji z powrotem, przy pomocy polecenia:

  ```
  root@DD-WRT:/tmp# mtd write uboot_factory.bin "RedBoot"
  Unlocking RedBoot ...
  Writing from uboot_orig.bin to RedBoot ...
  ```

8. W celu wgrania nowego obrazu, wykonaj poniższe polecenie:

  ```
  root@DD-WRT:/tmp# mtd write uboot_new.bin "RedBoot"
  Unlocking RedBoot ...
  Writing from uboot_new.bin to RedBoot ...
  ```

9. Jeżeli jesteś pewien, że do tej pory wszystko przebiegło pomyślnie, możesz zrestartować urządzenie:

  ```
  root@DD-WRT:/tmp# reboot
  ```

### Jak korzystać z tej modyfikacji?

[TODO]

Jak samodzielnie skompilować kod?
---------------------------------

Możesz wykorzystać jeden z dostępnych, bezpłatnych i gotowych narzędzi (tzw. toolchain):

- [OpenWrt Toolchain for AR71xx MIPS](https://downloads.openwrt.org/snapshots/trunk/ar71xx/generic/OpenWrt-Toolchain-ar71xx-generic_gcc-5.3.0_musl-1.1.14.Linux-x86_64.tar.bz2),
- ~~[Sourcery CodeBench Lite Edition for MIPS GNU/Linux](https://sourcery.mentor.com/GNUToolchain/subscription3130?lite=MIPS)~~,
- [ELDK (Embedded Linux Development Kit)](ftp://ftp.denx.de/pub/eldk/),
- lub innych...

Do kompilacji korzystam z **OpenWrt Toolchain for AR71xx MIPS**, na maszynie wirtualnej z zainstalowanym **Ubuntu 12.04 LTS** (32-bit). Wszystkie publikowane przeze mnie obrazy budowane są na tej konfiguracji.

Wszystko co musisz zrobić, po wybraniu zestawu narzędzi, to dostosowanie pliku [Makefile](Makefile) do własnej konfiguracji (czyli zmiana lub usunięcie `export MAKECMD` i ewentualnie dodanie `export PATH`). Przykładowo, w celu zbudowania obrazów przy pomocy OpenWrt Toolchain, zamiast Sourcery CodeBench Lite, pobierz odpowiednie archiwum i rozpakuj jego zawartość do folderu `toolchain`, w głównym katalogu ze źródłami, a następnie zmień początek pliku [Makefile](Makefile), jak poniżej:

```
export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-openwrt-linux-uclibc-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)
```

W celu uruchomienia kompilacji, w głównym katalogu ze źródłami wydaj polecenie `make model`, na przykład:

```
make tplink_wr703n
```

Powyższe polecenie rozpocznie kompilację obrazu U-Boot dla modelu **TP-Link TL-WR703N**.

FAQ
---

#### 1. Moje urządzenie nie jest wspierane, ale posiada taki sam hardware jak jedno z tych na liście, mogę użyć tej modyfikacji?

*To może się źle skończyć! Oczywiście, wiele dostępnych na rynku routerów wykorzystuje praktycznie te same platformy sprzętowe - na przykład, TP-Link posiada w ofercie kilka mobilnych modeli z wbudowaną baterią: TL-MR10U, TL-MR11U (odpowiednik w Europie to TL-MR3040) TL-MR12U and TL-MR13U. Wszystkie wymienione urządzenia posiadają ten sam sprzęt: układ SoC Atheros AR9331 z 32 MiB pamięci RAM i 4 MiB pamięci SPI NOR FLASH. Ale diabeł jak zwykle tkwi w szczegółach, takich jak numery GPIO wykorzystanych do przycisków, diod LED, załączania zasilania w gnieździe USB itd., co może spowodować pewne problemy.*

*Możesz spróbować wgrać jeden z gotowych obrazów, ale pamiętaj że robisz to wyłącznie na własną odpowiedzialność!*

#### 2. Chciałbym podkręcić CPU w moim routerze, jak tego dokonać?

*W chwili obecnej, taka możliwość istnieje, ale wyłącznie dla modeli z układem Atheros AR9331 (powinieneś zapoznać się z plikiem [ap121.h](u-boot/include/configs/ap121.h), który zawiera wszelkie informacje dotyczące konfiguracji rejestrów PLL i kilka gotowych, niestandardowych ustawień zegarów dla CPU, RAM i magistrali AHB). Co więcej, wersję z podkręconymi (lub "skręconymi") zegarami będziesz musiał skompilować samodzielnie, ponieważ nie publikuję gotowych obrazów, z innymi niż domyślne, wartościami zegarów.*

*I ponownie, pamiętaj że robisz to wyłącznie na własną odpowiedzialność!*

#### 3. Czy testujesz wszystkie publikowane obrazy?

*Nie, ponieważ nie dysponuję wszystkimi wspieranymi modelami routerów/urządzeń. Testuję jedynie obrazy na wszystkich wspieranych typach układów SoC.*

#### 4. Chciałbym dodać wsparcie dla modelu X.

*Możesz to zrobić samemu, a potem przesłać mi gotową łatę lub zgłosić pull request. Jeżeli nie chcesz lub nie wiesz jak dodać wsparcie dla nowego modelu, skontaktuj się ze mną bezpośrednio, może pomogę.*

#### 5. Mój router nie uruchomił się ponownie po zmianie U-Boot!

*Ostrzegałem... bootloader, w tym przypadku U-Boot, to w praktyce najistotniejszy kawałek oprogramowania w Twoim urządzeniu. Jest on odpowiedzialny za inicjalizację sprzętu i załadowanie systemu operacyjnego (zazwyczaj jądra Linux). Dlatego, jeżeli podczas zmiany obrazu coś poszło źle, Twoje urządzenie nie uruchomi się ponownie i jedynym sposobem na jego naprawę jest zdemontowanie (wylutowanie) kości FLASH, zaprogramowanie jej poprawnym obrazem i ponowny montaż.*

Licencja, przestarzałe źródła itd.
----------------------------------

Projekt **[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** jest Wolnym Oprogramowaniem. Wszelkie informacje dotyczące licencji, pracujących nad nim osób itd., dostępne są folderze *u-boot* wraz z kodem źródłowym.

Powinieneś wiedzieć, że większość routerów, szczególnie tych z układami Atheros, używa bardzo starej wersji U-Boot (wersja 1.1.4 pochodzi z lat 2005/2006). Dlatego stwierdzenie, że *te źródła są zdecydowanie przestarzałe* nie jest błędne, ale dla mnie było łatwiej zmodyfikować je w tej postaci, niż przenosić zmiany wykonane przez programistów TP-Link/Atheros do aktualnej gałęzi projektu U-Boot. Co więcej, wprowadzając własne modyfikacje, usunąłem sporo niepotrzebnych elementów, fragmentów kodu i plików źródłowych, tak żeby kod był czytelniejszy dla osoby, która do tej pory nie miała do czynienia z tym projektem.

Podziękowania
-------------

- Dziękuję M-K O'Connell za przekazanie routera z QCA9563
- Dziękuję Krzysztofowi M. za przekazanie routera TL-WDR3600
- Dziękuję użytkownikowi *pupie* z forum OpenWrt za jego nieocenioną pomoc
- Dziękuję wszystkim darczyńcom i osobom wspierającym rozwój tej modyfikacji
