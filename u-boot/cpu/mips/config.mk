#
# Copyright (C) 2003 Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier: GPL-2.0
#

# Jumps table seemed to be broken even without relocation
PLATFORM_CFLAGS += -mips32r2 -march=mips32r2 -fno-jump-tables
