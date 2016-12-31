/*
 * (C) Copyright 2001-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include <miiphy.h>

#if defined(CONFIG_CMD_NET) && defined(CONFIG_NET_MULTI)

#if defined(CONFIG_ATHEROS)
	extern int ath_gmac_enet_initialize(bd_t * bis);
#else
	extern int ag7240_enet_initialize(bd_t * bis);
#endif

/*
static struct eth_device *eth_devices, *eth_current;

struct eth_device *eth_get_dev(void){
	return eth_current;
}
*/

static struct eth_device *eth_devices;
struct eth_device *eth_current;


struct eth_device *eth_get_dev_by_name(char *devname){
	struct eth_device *dev, *target_dev;

	if(!eth_devices){
		return NULL;
	}

	dev = eth_devices;
	target_dev = NULL;

	do {
		if(strcmp(devname, dev->name) == 0){
			target_dev = dev;
			break;
		}
		dev = dev->next;
	} while(dev != eth_devices);

	return(target_dev);
}

int eth_get_dev_index(void){
	struct eth_device *dev;
	int num = 0;

	if (!eth_devices){
		return(-1);
	}

	for(dev = eth_devices; dev; dev = dev->next){
		if(dev == eth_current){
			break;
		}
		++num;
	}

	if(dev){
		return(num);
	}

	return(0);
}

int eth_register(struct eth_device* dev){
	struct eth_device *d;

	if(!eth_devices){
		eth_current = eth_devices = dev;
#ifdef CONFIG_NET_MULTI
		/* update current ethernet name */
		char *act = getenv("ethact");
		if(act == NULL || strcmp(act, eth_current->name) != 0){
			setenv("ethact", eth_current->name);
		}
#endif
	} else {
		for (d = eth_devices; d->next != eth_devices; d = d->next);
		d->next = dev;
	}

	dev->state = ETH_STATE_INIT;
	dev->next = eth_devices;

	return(0);
}

int eth_initialize(bd_t *bis){
	char enetvar[32];
	int i, eth_number = 0;
	char *tmp = NULL, *end = NULL;

	eth_devices = NULL;
	eth_current = NULL;

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	miiphy_init();
#endif

	// ag7240 initialization
#if defined(CONFIG_ATHEROS)
	ath_gmac_enet_initialize(bis);
#else
	ag7240_enet_initialize(bis);
#endif

	if(!eth_devices){
		printf_err("no ethernet found\n");
	} else {
		struct eth_device *dev = eth_devices;
		char *ethprime = getenv("ethprime");

		do {
			/*
			if (eth_number) {
				puts(", ");
			}

			printf("%s", dev->name);
			*/

			if(ethprime && strcmp(dev->name, ethprime) == 0){
				eth_current = dev;
				//puts(" [PRIME]");
			}

			sprintf(enetvar, eth_number ? "eth%daddr" : "ethaddr", eth_number);
			tmp = getenv(enetvar);

			for(i = 0; i < 6; i++){
				if(tmp){
					tmp = (*end) ? end + 1 : end;
				}
			}

			eth_number++;
			dev = dev->next;

		} while(dev != eth_devices);

#ifdef CONFIG_NET_MULTI
		/* update current ethernet name */
		if(eth_current){
			char *act = getenv("ethact");
			if(act == NULL || strcmp(act, eth_current->name) != 0){
				setenv("ethact", eth_current->name);
			}
		} else {
			setenv("ethact", NULL);
		}
#endif

		//putc('\n');
	}

	return(eth_number);
}

void eth_set_enetaddr(int num, char *addr){
	struct eth_device *dev;
	unsigned char enetaddr[6];
	char *end;
	int i;

	//debug("eth_set_enetaddr(num=%d, addr=%s)\n", num, addr);

	if(!eth_devices){
		return;
	}

	for(i = 0; i < 6; i++){
		enetaddr[i] = addr ? simple_strtoul(addr, &end, 16) : 0;
		if (addr){
			addr = (*end) ? end + 1 : end;
		}
	}

	dev = eth_devices;
	while(num-- > 0){
		dev = dev->next;

		if(dev == eth_devices){
			return;
		}
	}

	//debug("Setting new HW address on %s\nNew Address is %02X:%02X:%02X:%02X:%02X:%02X\n", dev->name, enetaddr[0], enetaddr[1], enetaddr[2], enetaddr[3], enetaddr[4], enetaddr[5]);
	memcpy(dev->enetaddr, enetaddr, 6);
}

int eth_init(bd_t *bis){
	struct eth_device* old_current;

	if (!eth_current){
		return(0);
	}

	old_current = eth_current;

	do {
#if !defined(CFG_ATHRS26_PHY) && !defined(CFG_ATHRHDR_EN)
		//debug("Trying %s\n", eth_current->name);
#endif
		if(eth_current->init(eth_current, bis)){
			eth_current->state = ETH_STATE_ACTIVE;
			return(1);
		}

		//debug("FAIL\n");

		eth_try_another(0);
	} while(old_current != eth_current);

	return(0);
}

void eth_halt(void){
	if(!eth_current){
		return;
	}

	eth_current->halt(eth_current);
	eth_current->state = ETH_STATE_PASSIVE;
}

int eth_send(volatile void *packet, int length){
	if(!eth_current){
		return(-1);
	}

	return(eth_current->send(eth_current, packet, length));
}

int eth_rx(void){
	if(!eth_current){
		return(-1);
	}

	return(eth_current->recv(eth_current));
}

void eth_try_another(int first_restart){
	static struct eth_device *first_failed = NULL;

	if(!eth_current){
		return;
	}

	if(first_restart){
		first_failed = eth_current;
	}

	eth_current = eth_current->next;

#ifdef CONFIG_NET_MULTI
	/* update current ethernet name */
	char *act = getenv("ethact");
	if(act == NULL || strcmp(act, eth_current->name) != 0){
		setenv("ethact", eth_current->name);
	}
#endif

	if (first_failed == eth_current){
		NetRestartWrap = 1;
	}
}

#ifdef CONFIG_NET_MULTI
void eth_set_current(void){

	char *act;
	struct eth_device* old_current;

	if (!eth_current){
		return;
	}

	act = getenv("ethact");

	if(act != NULL){
		old_current = eth_current;
		do {
			if(strcmp(eth_current->name, act) == 0){
				return;
			}
			eth_current = eth_current->next;
		} while(old_current != eth_current);
	}

	setenv("ethact", eth_current->name);
}
#endif

char *eth_get_name(void){
	return(eth_current ? eth_current->name : "unknown");
}
#elif defined(CONFIG_CMD_NET) && !defined(CONFIG_NET_MULTI)

int eth_initialize(bd_t *bis){
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	miiphy_init();
#endif
	return 0;
}
#endif
