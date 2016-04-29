/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2016 PC Engines GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <string.h>
#include "programmer.h"
#include "hwaccess.h"
#include "flash.h"

static void *gpiobase;
static enum part partno;

static int apu1_detect(enum chipbustype dongle);
static int apu2_detect(enum chipbustype dongle);
static void override_flash_bus(enum chipbustype bus);

int apu_open(enum part pn)
{
	enum chipbustype dongle = BUS_NONE;
	char *param = extract_programmer_param("recovery_dongle");
	if (param) {
		if (!strcmp(param, "SPI"))
			dongle = BUS_SPI;
		else if (!strcmp(param, "LPC"))
			dongle = BUS_LPC;
		else if (!strcmp(param, "FWH"))
			dongle = BUS_FWH;
		else
			return -1;
	}

	uintptr_t acpibase = 0xfed80000;

	partno = pn;
	if (partno == pn_apu1)
		gpiobase = physmap(NULL, acpibase, 0x1000);
	else if (partno == pn_apu2)
		gpiobase = physmap(NULL, acpibase, 0x2000);

	if (gpiobase == NULL)
		return -1;

	if (partno == pn_apu1)
		return apu1_detect(dongle);
	else if (partno == pn_apu2)
		return apu2_detect(dongle);

	return 0;
}

void apu_close(void)
{
	if (partno == pn_apu1)
		physunmap(gpiobase, 0x1000);
	else if (partno == pn_apu2)
		physunmap(gpiobase, 0x2000);

	override_flash_bus(BUS_NONE);
}

static void override_flash_bus(enum chipbustype bus)
{
	uint8_t reg;

	OUTB(0xca, 0xcd6);
	reg = INB(0xcd7);
	reg &= ~0x07;

	switch (bus) {
	case BUS_LPC:
		reg |= 0x04;
		disable_masters(BUS_SPI);
		disable_masters(BUS_FWH);
		break;
	case BUS_FWH:
		reg |= 0x06;
		disable_masters(BUS_LPC);
		disable_masters(BUS_SPI);
		break;
	case BUS_SPI:
		reg |= 0x07;
		disable_masters(BUS_LPC);
		disable_masters(BUS_FWH);
		break;
	case BUS_NONE:
	default:
		break;
	}

	OUTB(reg, 0xcd7);
}

/* PC Engines APU1 product */

static int apu1_detect(enum chipbustype dongle)
{
	int lpc_recovery;
	uint32_t *straps;
	uint32_t val;
	bool EC_PWM2, EC_PWM3;

	straps = gpiobase + 0xE00 + 0x80;

	/* Unset override to read straps correctly. */
	override_flash_bus(BUS_NONE);

	val = mmio_readl(straps);
	EC_PWM3 = (val & 1);
	EC_PWM2 = !(val & 2);

	lpc_recovery = (EC_PWM2 == 1) && (EC_PWM3 == 0);
	if (lpc_recovery)
		msg_cinfo(" (LPC recovery) ");

	if (dongle == BUS_SPI)
		return -1;
	else if (dongle == BUS_LPC)
		override_flash_bus(BUS_LPC);
	else if (dongle == BUS_FWH)
		override_flash_bus(BUS_FWH);
	else
		override_flash_bus(BUS_SPI);

	return 0;
}

/* PC Engines APU2 product */

static int apu2_detect(enum chipbustype dongle)
{
	int spi_recovery;
	uint32_t *gpio;
	uint32_t val;

	gpio = gpiobase + 0x1500 + 76 * sizeof(u32);

	/* Set input with pull-down enable. */
	val = mmio_readl(gpio);
	mmio_writel((val & ~(0xf << 20)) | (0x2<<20), gpio);

	val = mmio_readl(gpio);
	spi_recovery = !!(val & (1<<16));

	if (spi_recovery)
		msg_cinfo(" (SPI recovery) ");
	if (!spi_recovery && (dongle == BUS_SPI))
		return -1;

	if (dongle == BUS_NONE) {
		/* Drive SPICTL output low. */
		mmio_writel((val & ~(0xf << 20)) | (0x8<<20), gpio);
		override_flash_bus(BUS_SPI);
	} else if (dongle == BUS_SPI) {
		/* Drive SPICTL output high. */
		mmio_writel((val & ~(0xf << 20)) | (0xc<<20), gpio);
		override_flash_bus(BUS_SPI);
	} else if (dongle == BUS_LPC) {
		override_flash_bus(BUS_LPC);
	} else {
		return -1;
	}

	return 0;
}
