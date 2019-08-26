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

#ifndef FLASH_ACCESS_H
#define FLASH_ACCESS_H

#include <stdint.h>

#define MAX_DEVICES        64
#define MAX_LENGTH         64
#define NEWLINE            0x0A
#define NUL                0x00

int init_flash(void);
int is_flash_locked(void);
int lock_flash(void);
int unlock_flash(void);
int read_sec_status(void);
int read_sec(uint8_t reg, uint8_t addr, void *buf, size_t len);
int erase_sec(uint8_t reg, uint8_t addr, size_t len);
int prog_sec(uint8_t reg, uint8_t addr, const void *buf, size_t len);
int lock_sec(uint8_t reg);
int send_flash_cmd(uint8_t cmd, void *response, size_t len);
int send_flash_cmd_write(uint8_t command, size_t cmd_len, const void *data,
			 size_t data_len);
void save_flash(void *flash_address, char buffer[MAX_DEVICES][MAX_LENGTH],
		uint8_t max_lines);

#endif
