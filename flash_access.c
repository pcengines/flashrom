/*
 * Copyright (C) 2017 PC Engines GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#define CONFIG_SPI_FLASH_NO_FAST_READ

#include <spi_flash.h>
#include <flash_access.h>
#include <spi_flash_internal.h>

#define FLASH_SIZE_CHUNK   0x1000 //4k

static struct spi_flash *flash_device;
/*******************************************************************************/
// inline int unlock_flash(void)
// {
// 	return spi_flash_unlock(flash_device);
// }

// inline int read_sec_status(void)
// {
// 	return spi_flash_sec_sts(flash_device);
// }

// inline int read_sec(uint8_t reg, uint8_t addr, void *buf, size_t len)
// {
// 	return spi_flash_sec_read(flash_device, sec_addr(reg, addr), len, buf);
// }

// inline int erase_sec(uint8_t reg, uint8_t addr, size_t len)
// {
// 	return spi_flash_sec_erase(flash_device, sec_addr(reg, addr), len);
// }

// inline int prog_sec(uint8_t reg, uint8_t addr, const void *buf, size_t len)
// {
// 	return spi_flash_sec_prog(flash_device, sec_addr(reg, addr), len, buf);
// }

// inline int lock_sec(uint8_t reg)
// {
// 	return spi_flash_sec_lock(flash_device, reg);
// }

inline int send_flash_cmd(uint8_t cmd, void *response, size_t len)
{
	return spi_flash_cmd(flash_device->spi, cmd, response, len);
}

inline int send_flash_cmd_write(uint8_t command, size_t cmd_len, const void *data,
				size_t data_len)
{
	const uint8_t cmd = command;
	return spi_flash_cmd_write(flash_device->spi, &cmd, cmd_len, data,
				   data_len);
}

