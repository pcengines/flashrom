/*
 * Copyright (C) 2019 PC Engines GmbH
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

/* at25dfxx-specific commands */
#define CMD_AT25DF_WREN		0x06	/* Write Enable */
#define CMD_AT25DF_WRDI		0x04	/* Write Disable */
#define CMD_AT25DF_RDSR1	0x05	/* Read Status Register 1 */
#define CMD_AT25DF_RDSR2	0x35	/* Read Status Register 2 */
#define CMD_AT25DF_WRSR1	0x01	/* Write Status Register 1 */
#define CMD_AT25DF_WRSR2	0x31	/* Write Status Register 2 */
#define CMD_AT25DF_READ		0x03	/* Read Data Bytes */
#define CMD_AT25DF_FAST_READ	0x0b	/* Read Data Bytes at Higher Speed */
#define CMD_AT25DF_PP		0x02	/* Page Program */
#define CMD_AT25DF_SE		0x20	/* Sector (4K) Erase */
#define CMD_AT25DF_BE		0xd8	/* Block (64K) Erase */
#define CMD_AT25DF_CE		0xc7	/* Chip Erase */
#define CMD_AT25DF_DP		0xb9	/* Deep Power-down */
#define CMD_AT25DF_RES		0xab	/* Release from DP, and Read Signature */

#define REG_W25_BP0        (1 << 2)
#define REG_W25_BP1        (1 << 3)
#define REG_W25_BP2        (1 << 4)
#define REG_W25_TB         (1 << 5)
#define REG_W25_SEC        (1 << 6)
#define REG_W25_SRP0       (1 << 7)
#define REG_W25_SRP1       (1 << 0)
#define REG_W25_CMP        (1 << 6)
#define REG_W25_WPS        (1 << 2)
#define REG_W25_LB1        (1 << 3)
#define REG_W25_LB2        (1 << 4)
#define REG_W25_LB3        (1 << 5)
