/*
 *	Copyright 1994, 1995, 2000 Neil Russell.
 *	(See License)
 *	Copyright 2000, 2001 DENX Software Engineering, Wolfgang Denk, wd@denx.de
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include <asm/byteorder.h>
#include "httpd.h"

#include "../httpd/uipopt.h"
#include "../httpd/uip.h"
#include "../httpd/uip_arp.h"

#if !defined(WEBFAILSAFE_UPLOAD_ART_ADDRESS)
extern flash_info_t flash_info[];
#endif

static int arptimer = 0;

void HttpdHandler(void){
	int i;

	for(i = 0; i < UIP_CONNS; i++){
		uip_periodic(i);

		if(uip_len > 0){
			uip_arp_out();
			NetSendHttpd();
		}
	}

	if(++arptimer == 20){
		uip_arp_timer();
		arptimer = 0;
	}
}

// start http daemon
void HttpdStart(void){
	uip_init();
	httpd_init();
}

int do_http_upgrade(const ulong size, const int upgrade_type){
	char buf[96];	// erase 0xXXXXXXXX +0xXXXXXXXX; cp.b 0xXXXXXXXX 0xXXXXXXXX 0xXXXXXXXX (68 signs)
#if !defined(WEBFAILSAFE_UPLOAD_ART_ADDRESS)
	flash_info_t *info = &flash_info[0];
#endif

	if(upgrade_type == WEBFAILSAFE_UPGRADE_TYPE_UBOOT){

		printf("\n\n****************************\n*     U-BOOT UPGRADING     *\n* DO NOT POWER OFF DEVICE! *\n****************************\n\n");
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS,
				WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS,
				WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES);

	} else if(upgrade_type == WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE){

		printf("\n\n****************************\n*    FIRMWARE UPGRADING    *\n* DO NOT POWER OFF DEVICE! *\n****************************\n\n");
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS,
				size,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS,
				size);

	} else if(upgrade_type == WEBFAILSAFE_UPGRADE_TYPE_ART){

		// TODO: add option to change ART partition offset,
		// for those who want to use OFW on router with replaced/bigger FLASH
		printf("\n\n****************************\n*      ART  UPGRADING      *\n* DO NOT POWER OFF DEVICE! *\n****************************\n\n");
#if defined(WEBFAILSAFE_UPLOAD_ART_ADDRESS)
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				WEBFAILSAFE_UPLOAD_ART_ADDRESS,
				WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				WEBFAILSAFE_UPLOAD_ART_ADDRESS,
				WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES);
#else
		sprintf(buf,
				"erase 0x%lX +0x%lX; cp.b 0x%lX 0x%lX 0x%lX",
				WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + (info->size - WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES),
				WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES,
				WEBFAILSAFE_UPLOAD_RAM_ADDRESS,
				WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + (info->size - WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES),
				WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES);
#endif

	} else {
		return(-1);
	}

	printf("Executing: %s\n\n", buf);
	return(run_command(buf, 0));

	return(-1);
}

// info about current progress of failsafe mode
int do_http_progress(const int state){
	unsigned char i = 0;

	/* toggle LED's here */
	switch(state){
		case WEBFAILSAFE_PROGRESS_START:

			// blink LED fast 10 times
			for(i = 0; i < 10; ++i){
				all_led_on();
				milisecdelay(25);
				all_led_off();
				milisecdelay(25);
			}

			printf("HTTP server is ready!\n\n");
			break;

		case WEBFAILSAFE_PROGRESS_TIMEOUT:
			//printf("Waiting for request...\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPLOAD_READY:
			printf("HTTP upload is done! Upgrading...\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPGRADE_READY:
			printf("HTTP ugrade is done! Rebooting...\n\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPGRADE_FAILED:
			printf("## Error: HTTP ugrade failed!\n\n");

			// blink LED fast for 4 sec
			for(i = 0; i < 80; ++i){
				all_led_on();
				milisecdelay(25);
				all_led_off();
				milisecdelay(25);
			}

			// wait 1 sec
			milisecdelay(1000);

			break;
	}

	return(0);
}
