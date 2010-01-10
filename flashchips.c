/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2000 Silicon Integrated System Corporation
 * Copyright (C) 2004 Tyan Corp
 * Copyright (C) 2005-2008 coresystems GmbH <stepan@openbios.org>
 * Copyright (C) 2006-2009 Carl-Daniel Hailfinger
 * Copyright (C) 2009 Sean Nelson <audiohacked@gmail.com>
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

#include "flash.h"
#include "flashchips.h"

/**
 * List of supported flash chips.
 *
 * Please keep the list sorted by vendor name and chip name, so that
 * the output of 'flashrom -L' is alphabetically sorted.
 */
struct flashchip flashchips[] = {

	/*
	 * .vendor		= Vendor name
	 * .name		= Chip name
	 * .bustype		= Supported flash bus types (Parallel, LPC...)
	 * .manufacture_id	= Manufacturer chip ID
	 * .model_id		= Model chip ID
	 * .total_size		= Total size in (binary) kbytes
	 * .page_size		= Page or eraseblock(?) size in bytes
	 * .tested		= Test status
	 * .probe		= Probe function
	 * .probe_timing	= Probe function delay
	 * .erase		= Chip erase function
	 * .block_erasers[]	= Array of erase layouts and erase functions
	 * {
	 *	.eraseblocks[]	= Array of { blocksize, blockcount }
	 *	.block_erase	= Block erase function
	 * }
	 * .write		= Chip write function
	 * .read		= Chip read function
	 */

	{
		.vendor		= "AMD",
		.name		= "Am29F010A/B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F010B,	/* Same as Am29F010A */
		.total_size	= 128,
		.page_size	= 16 * 1024,
		.tested		= TEST_OK_PRW,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {16 * 1024, 8} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_pm29f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29F002(N)BB",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F002BB,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 3},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29F002(N)BT",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F002BT,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_OK_PR,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 3},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29F016D",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F016D,
		.total_size	= 2 * 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {2048 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29F040B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PRW,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29F080B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29F080B,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29LV040B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29LV040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMD",
		.name		= "Am29LV081B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMD_ID,
		.model_id	= AM_29LV080B,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ASD",
		.name		= "AE49F2008",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ASD_ID,
		.model_id	= ASD_AE49F2008,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME, 
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{128 * 1024, 1},
					{96 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF021",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF021,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 8} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF041A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF041A,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF081",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF081,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF161",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF161,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF321",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF321,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF321A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF321A,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25DF641",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25DF641,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25F512B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25F512B,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25FS010",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25FS010,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25FS040",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_25FS040,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF041",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26DF041,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}
		},
		.write		= NULL /* Incompatible Page write */,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF081A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26DF081A,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF161",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26DF161,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF161A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26DF161A,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	/*The AT26DF321 has the same ID as the AT25DF321. */
	/*{
		.vendor		= "Atmel",
		.name		= "AT26DF321",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26DF321,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_60_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	  },*/

	{
		.vendor		= "Atmel",
		.name		= "AT26F004",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_26F004,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= NULL /* Incompatible Page write */,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT29C512",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_29C512,
		.total_size	= 64,
		.page_size	= 128,
		.tested		= TEST_OK_PRW,
		.probe		= probe_jedec,
		.probe_timing	= 10000, /* 10mS, Enter=Exec */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_jedec,
		.read		= read_memmapped,

	},

	{
		.vendor		= "Atmel",
		.name		= "AT29C010A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_29C010A,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_OK_PR,
		.probe		= probe_jedec,
		.probe_timing	= 10000, /* 10mS, Enter=Exec */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_jedec,	/* FIXME */
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT29C020",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_29C020,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_jedec,
		.probe_timing	= 10000,			/* 10ms */ 
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT29C040A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_29C040A,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= 10000,			/* 10 ms */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45CS1282",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45CS1282,
		.total_size	= 16896 /* No power of two sizes */,
		.page_size	= 1056 /* No power of two sizes */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL /* Incompatible Page write */,
		.read		= NULL /* Incompatible read */,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB011D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB011D,
		.total_size	= 128 /* Size can only be determined from status register */,
		.page_size	= 256 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB021D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB021D,
		.total_size	= 256 /* Size can only be determined from status register */,
		.page_size	= 256 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB041D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB041D,
		.total_size	= 512 /* Size can only be determined from status register */,
		.page_size	= 256 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB081D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB081D,
		.total_size	= 1024 /* Size can only be determined from status register */,
		.page_size	= 256 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB161D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB161D,
		.total_size	= 2048 /* Size can only be determined from status register */,
		.page_size	= 512 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB321C",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB321C,
		.total_size	= 4224 /* No power of two sizes */,
		.page_size	= 528 /* No power of two sizes */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL /* Incompatible read */,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB321D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB321D,
		.total_size	= 4096 /* Size can only be determined from status register */,
		.page_size	= 512 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT45DB642D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_45DB642D,
		.total_size	= 8192 /* Size can only be determined from status register */,
		.page_size	= 1024 /* Size can only be determined from status register */,
		.tested		= TEST_BAD_READ,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT49BV512",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_49BV512,
		.total_size	= 64,
		.page_size	= 64,
		.tested		= TEST_OK_PRW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT49F002(N)",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_49F002N,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{16 * 1024, 1},
					{8 * 1024, 2},
					{96 * 1024, 1},
					{128 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "AT49F002(N)T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ATMEL_ID,
		.model_id	= AT_49F002NT,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{128 * 1024, 1},
					{96 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	/* The next two chip definitions have top/bottom boot blocks, but has no
	device differenciation between the two */
	{
		.vendor		= "AMIC",
		.name		= "A25L40PT",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= AMIC_ID,
		.model_id	= AMIC_A25L40P,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid4,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 7},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L40PU",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= AMIC_ID,
		.model_id	= AMIC_A25L40P,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid4,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 7},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "AMIC",
		.name		= "A29002B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A29002B,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 3},
				},
				.block_erase = erase_sector_29f002,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMIC",
		.name		= "A29002T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A29002T,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{64 * 1024, 3},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_29f002,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMIC",
		.name		= "A29040B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A29040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "AMIC",
		.name		= "A49LF040A",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A49LF040A,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PRW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* routine is wrapper to probe_jedec (pm49fl00x.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_block_jedec,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_49fl00x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "EMST",
		.name		= "F49B002UA",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= EMST_ID,
		.model_id	= EMST_F49B002UA,
		.total_size	= 256,
		.page_size	= 4096,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{128 * 1024, 1},
					{96 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			}
		},
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B05",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B05,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B05T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B05,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B10",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B10,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 3},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B10T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B10,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{32 * 1024, 3},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B20",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 3}
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B20T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 3},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B40",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B40,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 7}
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B40T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B40,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 7},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B80",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 15}
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B80T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 15},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 31},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B16T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 31},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B32",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B32,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 63},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B32T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B32,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 63},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B64",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B64,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 127},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B64T",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25B64,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 127},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25D16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25D16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F05",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F05,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F10",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F10,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F20",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F40",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F40,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PROBE,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F80",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F32",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EN_25F32,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "EON",
		.name		= "EN29F002(A)(N)B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= EON_ID,
		.model_id	= EN_29F002B,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{64 * 1024, 3},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "EON",
		.name		= "EN29F002(A)(N)T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= EON_ID,
		.model_id	= EN_29F002T,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_OK_PR,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 3},
				},
				.block_erase = erase_sector_jedec,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_block_jedec,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Fujitsu",
		.name		= "MBM29F004BC",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= FUJITSU_ID,
		.model_id	= MBM29F004BC,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 7},
				},
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Fujitsu",
		.name		= "MBM29F004TC",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= FUJITSU_ID,
		.model_id	= MBM29F004TC,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{64 * 1024, 7},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Fujitsu",
		.name		= "MBM29F400BC",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= FUJITSU_ID,
		.model_id	= MBM29F400BC,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_m29f400bt,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (m29f400bt.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 7},
				},
				.block_erase = block_erase_m29f400bt,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = block_erase_chip_m29f400bt,
			},
		},
		.write		= write_coreboot_m29f400bt,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Fujitsu",
		.name		= "MBM29F400TC",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= FUJITSU_ID,
		.model_id	= MBM29F400TC,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_m29f400bt,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (m29f400bt.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{64 * 1024, 7},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = block_erase_m29f400bt,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = block_erase_chip_m29f400bt,
			},
		},
		.write		= write_coreboot_m29f400bt,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Intel",
		.name		= "28F001BX-B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= INTEL_ID,
		.model_id	= P28F001BXB,
		.total_size	= 128,
		.page_size	= 128 * 1024, /* 8k + 2x4k + 112k */
		.tested		= TEST_BAD_WRITE,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{8 * 1024, 1},
					{4 * 1024, 2},
					{112 * 1024, 1},
				},
				.block_erase = erase_82802ab_block,
			},
		},
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Intel",
		.name		= "28F001BX-T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= INTEL_ID,
		.model_id	= P28F001BXT,
		.total_size	= 128,
		.page_size	= 128 * 1024, /* 112k + 2x4k + 8k */
		.tested		= TEST_OK_PR|TEST_BAD_WRITE,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{112 * 1024, 1},
					{4 * 1024, 2},
					{8 * 1024, 1},
				},
				.block_erase = erase_82802ab_block,
			},
		},
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Intel",
		.name		= "82802AB",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= INTEL_ID,
		.model_id	= I_82802AB,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PRW,
		.probe		= probe_82802ab,
		.probe_timing	= TIMING_IGNORED, /* routine does not use probe_timing (82802ab.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_82802ab_block,
			},
		},
		.write		= write_82802ab,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Intel",
		.name		= "82802AC",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= INTEL_ID,
		.model_id	= I_82802AC,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PRW,
		.probe		= probe_82802ab,
		.probe_timing	= TIMING_IGNORED, /* routine does not use probe_timing (82802ab.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = erase_82802ab_block,
			},
		},
		.write		= write_82802ab,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L512",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L512,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1005",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L1005,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 2} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L2005",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L2005,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L4005",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L4005,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L8005",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L8005,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1605",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L1605,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,	/* This erase function has 64k blocksize for eLiteFlash */
			}, {
				.eraseblocks = { {64 * 1024, 32} },	/* Not supported in MX25L1605 (eLiteFlash) and MX25L1605D */
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1635D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L1635D,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3205",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L3205,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3235D",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L3235D,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L6405",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L6405,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_OK_PROBE,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L12805",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= MX_25L12805,
		.total_size	= 16384,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			}
		},
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX29F001B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= MX_ID,
		.model_id	= MX_29F001B,
		.total_size	= 128,
		.page_size	= 32 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{8 * 1024, 1},
					{4 * 1024, 2},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 1},
				},
				.block_erase = erase_sector_29f002,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			}
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX29F001T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= MX_ID,
		.model_id	= MX_29F001T,
		.total_size	= 128,
		.page_size	= 32 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { 
					{64 * 1024, 1},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{4 * 1024, 2},
					{8 * 1024, 1},
				},
				.block_erase = erase_sector_29f002,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			}
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX29F002B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= MX_ID,
		.model_id	= MX_29F002B,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{16 * 1024, 1},
					{8 * 1024, 2},
					{32 * 1024, 1},
					{64 * 1024, 3},
				},
				.block_erase = erase_sector_29f002,	/* This erase function has 64k blocksize for eLiteFlash */
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX29F002T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= MX_ID,
		.model_id	= MX_29F002T,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 3},
					{32 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_29f002,	/* This erase function has 64k blocksize for eLiteFlash */
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Macronix",
		.name		= "MX29LV040",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= MX_ID,
		.model_id	= MX_29LV040,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_29f002,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (mx29f002.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8}, },
				.block_erase = erase_sector_29f002,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = erase_chip_29f002,
			},
		},
		.write		= write_jedec_1,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Numonyx",
		.name		= "M25PE10",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE10,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_d8,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Numonyx",
		.name		= "M25PE20",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_d8,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Numonyx",
		.name		= "M25PE40",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE40,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_d8,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Numonyx",
		.name		= "M25PE80",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_d8,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Numonyx",
		.name		= "M25PE16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_d8,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV010",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV010,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV016B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV016B,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV020",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV020,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV040",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV040,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV080B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV080B,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LV512",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_25LV512,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm29F002T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_29F002T,
		.total_size	= 256,
		.page_size	= 8 * 1024,
		.tested		= TEST_OK_PRW,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_FIXME, 
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{128 * 1024, 1},
					{96 * 1024, 1},
					{8 * 1024, 2},
					{16 * 1024, 1},
				},
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_pm29f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm29F002B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_29F002B,
		.total_size	= 256,
		.page_size	= 8 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_FIXME, 
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{16 * 1024, 1},
					{8 * 1024, 2},
					{96 * 1024, 1},
					{128 * 1024, 1},
				},
				.block_erase = erase_sector_29f040b,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = erase_chip_29f040b,
			},
		},
		.write		= write_pm29f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm39LV010",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_39F010,
		.total_size	= 128,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm49FL002",
		.bustype	= CHIP_BUSTYPE_LPC|CHIP_BUSTYPE_FWH, /* A/A Mux*/
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_49FL002,
		.total_size	= 256,
		.page_size	= 16 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* routine is wrapper to probe_jedec (pm49fl00x.c) */
		.erase		= erase_49fl00x,
		.write		= write_49fl00x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "PMC",
		.name		= "Pm49FL004",
		.bustype	= CHIP_BUSTYPE_LPC|CHIP_BUSTYPE_FWH, /* A/A Mux*/
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_49FL004,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* routine is wrapper to probe_jedec (pm49fl00x.c) */
		.erase		= erase_49fl00x,
		.write		= write_49fl00x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Sanyo",
		.name		= "LF25FW203A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FW203A,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Sharp",
		.name		= "LHF00L04",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= SHARP_ID,
		.model_id	= SHARP_LHF00L04,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 15},
					{8 * 1024, 8}
				 },
				.block_erase = erase_lhf00l04_block,
			}, {
				.eraseblocks = {
					{1024 * 1024, 1}
				},
				.block_erase = NULL, /* 30 D0, only in PP mode */
			},
		},
		.write		= write_lhf00l04,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Spansion",
		.name		= "S25FL016A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SPANSION_ID,
		.model_id	= SPANSION_S25FL016A,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF016B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF016B,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF032B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF032B,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF040.REMS",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF040_REMS,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PR,
		.probe		= probe_spi_rems,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF040B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF040B,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF040B.REMS",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF040B_REMS,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PR,
		.probe		= probe_spi_rems,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF080B",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_25VF080B,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_OK_PRW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = spi_block_erase_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = spi_block_erase_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = spi_block_erase_d8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = spi_block_erase_c7,
			},
		},
		.write		= spi_chip_write_1,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "SST",
		.name		= "SST28SF040A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_28SF040,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_28sf040,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst28sf040.c) */
		.erase		= erase_28sf040,
		.write		= write_28sf040,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST29EE010",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_29EE010,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST29LE010",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_29LE010,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST29EE020A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_29EE020A,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10,
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST29LE020",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_29LE020,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39SF010A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39SF010,
		.total_size	= 128,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39SF020A",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39SF020,
		.total_size	= 256,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39SF040",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39SF040,
		.total_size	= 512,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39VF512",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39VF512,
		.total_size	= 64,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns*/ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39VF010",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39VF010,
		.total_size	= 128,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39VF020",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39VF020,
		.total_size	= 256,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39VF040",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39VF040,
		.total_size	= 512,
		.page_size	= 4096,
		.tested		= TEST_OK_PROBE,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST39VF080",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SST_ID,
		.model_id	= SST_39VF080,
		.total_size	= 1024,
		.page_size	= 4096,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF002A/B",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF002A,
		.total_size	= 256,
		.page_size	= 16 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_sst_fwhub,
		.probe_timing	= 1,		/* 150 ns | routine is wrapper to probe_jedec (sst_fwhub.c) */
		.erase		= erase_sst_fwhub,
		.write		= write_sst_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF003A/B",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF003A,
		.total_size	= 384,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PR,
		.probe		= probe_sst_fwhub,
		.probe_timing	= 1,		/* 150 ns | routine is wrapper to probe_jedec (sst_fwhub.c) */
		.erase		= erase_sst_fwhub,
		.write		= write_sst_fwhub,
		.read		= read_memmapped,
	},

	{
		/* Contrary to the data sheet, TBL# on the SST49LF004B affects the top 128kB (instead of 64kB)
		 * and is only honored for 64k block erase, but not 4k sector erase.
		 */
		.vendor		= "SST",
		.name		= "SST49LF004A/B",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF004A,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_sst_fwhub,
		.probe_timing	= 1,		/* 150 ns | routine is wrapper to probe_jedec (sst_fwhub.c) */
		.erase		= NULL,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = erase_sector_jedec, /* missing unlock */
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = erase_sst_fwhub_block, /* same as erase_block_jedec, but with unlock */
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = NULL, /* AA 55 80 AA 55 10, only in PP mode */
			},
		},
		.write		= write_sst_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF004C",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF004C,
		.total_size	= 512,
		.page_size	= 4 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst49lfxxxc.c) */
		.erase		= erase_49lfxxxc,
		.write		= write_49lfxxxc,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF008A",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF008A,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_sst_fwhub,
		.probe_timing	= 1,		/* 150 ns | routine is wrapper to probe_jedec (sst_fwhub.c) */
		.erase		= erase_sst_fwhub,
		.write		= write_sst_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF008C",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF008C,
		.total_size	= 1024,
		.page_size	= 4 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst49lfxxxc.c) */
		.erase		= erase_49lfxxxc,
		.write		= write_49lfxxxc,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF016C",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF016C,
		.total_size	= 2048,
		.page_size	= 4 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst49lfxxxc.c) */
		.erase		= erase_49lfxxxc,
		.write		= write_49lfxxxc,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF020",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF020,
		.total_size	= 256,
		.page_size	= 16 * 1024,
		.tested		= TEST_OK_PR,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_49lf040,
		.write		= write_49lf040,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF020A",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF020A,
		.total_size	= 256,
		.page_size	= 4 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_49lf040,
		.write		= write_49lf040,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF040",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF040,
		.total_size	= 512,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 1,			/* 150 ns */ 
		.erase		= erase_49lf040,
		.write		= write_49lf040,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF040B",
		.bustype	= CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_sst_fwhub,
		.probe_timing	= 1,		/* 150ns | routine is wrapper to probe_jedec (sst_fwhub.c) */
		.erase		= erase_sst_fwhub,
		.write		= write_sst_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF080A",
		.bustype	= CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= SST_ID,
 		.model_id	= SST_49LF080A,
		.total_size	= 1024,
		.page_size	= 4096,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME, 
		.erase		= erase_49lf040,
		.write		= write_49lf040,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SST",
		.name		= "SST49LF160C",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= SST_ID,
		.model_id	= SST_49LF160C,
		.total_size	= 2048,
		.page_size	= 4 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst49lfxxxc.c) */
		.erase		= erase_49lfxxxc,
		.write		= write_49lfxxxc,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M25P05-A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P05A,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	/* The ST M25P05 is a bit of a problem. It has the same ID as the
	 * ST M25P05-A in RES mode, but supports only 128 byte writes instead
	 * of 256 byte writes. We rely heavily on the fact that probe_spi_res
	 * only is successful if RDID does not work.
	 */
	{
		.vendor		= "ST",
		.name		= "M25P05.RES",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P05_RES,
		.total_size	= 64,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_res,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_1, /* 128 */
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P10-A",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P10A,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	/* The ST M25P10 has the same problem as the M25P05. */
	{
		.vendor		= "ST",
		.name		= "M25P10.RES",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P10_RES,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_res,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_1, /* 128 */
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P20",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P40",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P40,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P40-old",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P40_RES,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_res,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P80",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P32",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P32,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P64",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P64,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M25P128",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P128,
		.total_size	= 16384,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "ST",
		.name		= "M29F002B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29F002B,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_m29f002,
		.write		= write_m29f002b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M29F002T/NT",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29F002T,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_m29f002,
		.write		= write_m29f002t,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M29F040B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29F040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_29f040b,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (am29f040b.c) */
		.erase		= erase_29f040b,
		.write		= write_29f040b,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M29F400BT",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29F400BT,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_m29f400bt,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (m29f400bt.c) */
		.erase		= erase_m29f400bt,
		.write		= write_coreboot_m29f400bt,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M29W010B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29W010B,
		.total_size	= 128,
		.page_size	= 16 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M29W040B",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M29W040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FLW040A",
		.bustype	= CHIP_BUSTYPE_FWH|CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FLW040A,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_stm50flw0x0x,
		.write		= write_stm50flw0x0x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FLW040B",
		.bustype	= CHIP_BUSTYPE_FWH|CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FLW040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_stm50flw0x0x,
		.write		= write_stm50flw0x0x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FLW080A",
		.bustype	= CHIP_BUSTYPE_FWH|CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FLW080A,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_stm50flw0x0x,
		.write		= write_stm50flw0x0x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FLW080B",
		.bustype	= CHIP_BUSTYPE_FWH|CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FLW080B,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_stm50flw0x0x,
		.write		= write_stm50flw0x0x,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FW002",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FW002,
		.total_size	= 256,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_49lfxxxc,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (sst49lfxxxc.c) */
		.erase		= NULL,
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FW016",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FW016,
		.total_size	= 2048,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_82802ab,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (82802ab.c) */
		.erase		= erase_82802ab,
		.write		= write_82802ab,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FW040",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FW040,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_82802ab,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (82802ab.c) */
		.erase		= erase_82802ab,
		.write		= write_82802ab,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50FW080",
		.bustype	= CHIP_BUSTYPE_FWH, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50FW080,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_82802ab,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (82802ab.c) */
		.erase		= erase_82802ab,
		.write		= write_82802ab,
		.read		= read_memmapped,
	},

	{
		.vendor		= "ST",
		.name		= "M50LPW116",
		.bustype	= CHIP_BUSTYPE_LPC, /* A/A Mux */
		.manufacture_id	= ST_ID,
		.model_id	= ST_M50LPW116,
		.total_size	= 2048,
		.page_size	= 64 * 1024,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SyncMOS",
		.name		= "S29C31004T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SYNCMOS_ID,
		.model_id	= S29C31004T,
		.total_size	= 512,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SyncMOS",
		.name		= "S29C51001T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SYNCMOS_ID,
		.model_id	= S29C51001T,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SyncMOS",
		.name		= "S29C51002T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SYNCMOS_ID,
		.model_id	= S29C51002T,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "SyncMOS",
		.name		= "S29C51004T",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= SYNCMOS_ID,
		.model_id	= S29C51004T,
		.total_size	= 512,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "TI",
		.name		= "TMS29F002RB",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= TI_OLD_ID,
		.model_id	= TI_TMS29F002RB,
		.total_size	= 256,
		.page_size	= 16384, /* Non-uniform sectors */
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "TI",
		.name		= "TMS29F002RT",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= TI_OLD_ID,
		.model_id	= TI_TMS29F002RT,
		.total_size	= 256,
		.page_size	= 16384, /* Non-uniform sectors */
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_ZERO,	/* Datasheet has no timing info specified */
		.erase		= NULL,
		.write		= NULL,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x10",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X10,
		.total_size	= 128,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x20",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X20,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x40",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X40,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x80",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X80,
		.total_size	= 1024,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x16",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X16,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= TEST_OK_PR,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x32",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X32,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= TEST_OK_PROBE,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25x64",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= W_25X64,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= spi_chip_erase_c7,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	},

	{
		.vendor		= "Winbond",
		.name		= "W29C011",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_29C011,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10,		/* used datasheet for the W29C011A */
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W29C020C",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_29C020C,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W29C040P",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_29C040P,
		.total_size	= 512,
		.page_size	= 256,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W29EE011",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_29C011,
		.total_size	= 128,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_w29ee011,
		.probe_timing	= TIMING_IGNORED, /* routine don't use probe_timing (w29ee011.c) */
		.erase		= erase_chip_jedec,
		.write		= write_jedec,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V040A",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V040A,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V040B",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V040B,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PR | TEST_BAD_ERASE | TEST_BAD_WRITE,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V040C",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V040C,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_w39v040c,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_w39v040c,
		.write		= write_w39v040c,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V040FA",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V040FA,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V080A",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V080A,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W49F002U",
		.bustype	= CHIP_BUSTYPE_PARALLEL,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_49F002U,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10,
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W49V002A",
		.bustype	= CHIP_BUSTYPE_LPC,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_49V002A,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= 10, 
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W49V002FA",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_49V002FA,
		.total_size	= 256,
		.page_size	= 128,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= 10,
		.erase		= erase_chip_jedec,
		.write		= write_49f002,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V080FA",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V080FA,
		.total_size	= 1024,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_OK_PREW,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_winbond_fwhub,
		.write		= write_winbond_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Winbond",
		.name		= "W39V080FA (dual mode)",
		.bustype	= CHIP_BUSTYPE_FWH,
		.manufacture_id	= WINBOND_ID,
		.model_id	= W_39V080FA_DM,
		.total_size	= 512,
		.page_size	= 64 * 1024,
		.feature_bits	= FEATURE_REGISTERMAP,
		.tested		= TEST_UNTESTED,
		.probe		= probe_jedec,
		.probe_timing	= TIMING_FIXME,
		.erase		= erase_winbond_fwhub,
		.write		= write_winbond_fwhub,
		.read		= read_memmapped,
	},

	{
		.vendor		= "Atmel",
		.name		= "unknown Atmel SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "EON",
		.name		= "unknown EON SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Macronix",
		.name		= "unknown Macronix SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= MX_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "PMC",
		.name		= "unknown PMC SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "SST",
		.name		= "unknown SST SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "ST",
		.name		= "unknown ST SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Sanyo",
		.name		= "unknown Sanyo SPI chip",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.erase		= NULL,
		.write		= NULL,
		.read		= NULL,
	},

	{
		.vendor		= "Generic",
		.name		= "unknown SPI chip (RDID)",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= GENERIC_MANUF_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rdid,
		.erase		= NULL,
		.write		= NULL,
	},
	{
		.vendor		= "Generic",
		.name		= "unknown SPI chip (REMS)",
		.bustype	= CHIP_BUSTYPE_SPI,
		.manufacture_id	= GENERIC_MANUF_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		.probe		= probe_spi_rems,
		.erase		= NULL,
		.write		= NULL,
	},

	{ NULL 	}
};
