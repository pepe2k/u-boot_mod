/*
 * SOC common registers and helper function/macro definitions
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _SOC_COMMON_H_
#define _SOC_COMMON_H_

#include <linux/bitops.h>

#ifndef SOC_TYPE
	#error "SOC_TYPE is not defined!"
#endif

/*
 * GPIO registers BIT fields
 */
#define GPIO_X_MASK(_gpio)	(1 << _gpio)

#define GPIO0	GPIO_X_MASK(0)
#define GPIO1	GPIO_X_MASK(1)
#define GPIO2	GPIO_X_MASK(2)
#define GPIO3	GPIO_X_MASK(3)
#define GPIO4	GPIO_X_MASK(4)
#define GPIO5	GPIO_X_MASK(5)
#define GPIO6	GPIO_X_MASK(6)
#define GPIO7	GPIO_X_MASK(7)
#define GPIO8	GPIO_X_MASK(8)
#define GPIO9	GPIO_X_MASK(9)
#define GPIO10	GPIO_X_MASK(10)
#define GPIO11	GPIO_X_MASK(11)
#define GPIO12	GPIO_X_MASK(12)
#define GPIO13	GPIO_X_MASK(13)
#define GPIO14	GPIO_X_MASK(14)
#define GPIO15	GPIO_X_MASK(15)
#define GPIO16	GPIO_X_MASK(16)
#define GPIO17	GPIO_X_MASK(17)
#define GPIO18	GPIO_X_MASK(18)
#define GPIO19	GPIO_X_MASK(19)
#define GPIO20	GPIO_X_MASK(20)
#define GPIO21	GPIO_X_MASK(21)
#define GPIO22	GPIO_X_MASK(22)
#define GPIO23	GPIO_X_MASK(23)
#define GPIO24	GPIO_X_MASK(24)
#define GPIO25	GPIO_X_MASK(25)
#define GPIO26	GPIO_X_MASK(26)
#define GPIO27	GPIO_X_MASK(27)
#define GPIO28	GPIO_X_MASK(28)
#define GPIO29	GPIO_X_MASK(29)
#define GPIO30	GPIO_X_MASK(30)
#define GPIO31	GPIO_X_MASK(31)
#define GPIO32	GPIO_X_MASK(32)
#define GPIO33	GPIO_X_MASK(33)
#define GPIO34	GPIO_X_MASK(34)
#define GPIO35	GPIO_X_MASK(35)
#define GPIO36	GPIO_X_MASK(36)
#define GPIO37	GPIO_X_MASK(37)
#define GPIO38	GPIO_X_MASK(38)
#define GPIO39	GPIO_X_MASK(39)
#define GPIO40	GPIO_X_MASK(40)
#define GPIO41	GPIO_X_MASK(41)
#define GPIO42	GPIO_X_MASK(42)
#define GPIO43	GPIO_X_MASK(43)
#define GPIO44	GPIO_X_MASK(44)
#define GPIO45	GPIO_X_MASK(45)
#define GPIO46	GPIO_X_MASK(46)
#define GPIO47	GPIO_X_MASK(47)
#define GPIO48	GPIO_X_MASK(48)
#define GPIO49	GPIO_X_MASK(49)
#define GPIO50	GPIO_X_MASK(50)

/*
 * Memory types
 */
#define RAM_MEMORY_TYPE_DDR1	1
#define RAM_MEMORY_TYPE_DDR2	2
#define RAM_MEMORY_TYPE_DDR3	3
#define RAM_MEMORY_TYPE_SDR	4
#define RAM_MEMORY_TYPE_UNKNOWN	5

/*
 * Useful clock variables
 */
#define VAL_40MHz	(40 * 1000 * 1000)
#define VAL_25MHz	(25 * 1000 * 1000)

#endif /* _SOC_COMMON_H_ */
