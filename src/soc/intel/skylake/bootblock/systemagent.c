/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 * Copyright (C) 2016 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <soc/bootblock.h>
#include <soc/pci_devs.h>
#include <soc/systemagent.h>

void bootblock_systemagent_early_init(void)
{
	uint32_t reg;

	/*
	 * The "io" variant of the config access is explicitly used to
	 * setup the PCIEXBAR because CONFIG_MMCONF_SUPPORT_DEFAULT is set to
	 * to true. That way all subsequent non-explicit config accesses use
	 * MCFG. This code also assumes that bootblock_northbridge_init() is
	 * the first thing called in the non-asm boot block code. The final
	 * assumption is that no assembly code is using the
	 * CONFIG_MMCONF_SUPPORT_DEFAULT option to do PCI config acceses.
	 *
	 * The PCIEXBAR is assumed to live in the memory mapped IO space under
	 * 4GiB.
	 */
	reg = 0;
	pci_io_write_config32(SA_DEV_ROOT, PCIEXBAR + 4, reg);
	reg = CONFIG_MMCONF_BASE_ADDRESS | 4 | 1; /* 64MiB - 0-63 buses. */
	pci_io_write_config32(SA_DEV_ROOT, PCIEXBAR, reg);
}
