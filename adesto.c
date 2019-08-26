/*
 * adesto.c
 * Driver for Adesto Technologies SPI flash
 * Copyright 2014 Orion Technologies, LLC
 * Author: Chris Douglass <cdouglass <at> oriontechnologies.com>
 *
 * based on winbond.c
 * Copyright 2008, Network Appliance Inc.
 * Author: Jason McMullan <mcmullan <at> netapp.com>
 * Licensed under the GPL-2 or later.
 */

#include <stdlib.h>
#include <spi_flash.h>
#include <spi.h>
#include <spi_flash_internal.h>
#include <adesto_flash.h>

struct adesto_spi_flash_params {
	uint16_t	id;
	/* Log2 of page size in power-of-two mode */
	uint8_t		l2_page_size;
	uint16_t	pages_per_sector;
	uint16_t	sectors_per_block;
	uint16_t	nr_blocks;
	const char	*name;
};

/* spi_flash needs to be first so upper layers can free() it */
struct adesto_spi_flash {
	struct spi_flash flash;
	const struct adesto_spi_flash_params *params;
};

static inline struct adesto_spi_flash *
to_adesto_spi_flash(struct spi_flash *flash)
{
	return container_of(flash, struct adesto_spi_flash, flash);
}

static const struct adesto_spi_flash_params adesto_spi_flash_table[] = {
	{
		.id			= 0x4218,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 256,
		.name			= "AT25SL128A",
	},
	{
		.id			= 0x4501,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 16,
		.name			= "AT25DF081A", /* Yes, 81A id < 81 */
	},
	{
		.id			= 0x4502,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 16,
		.name			= "AT25DF081",
	},
	{
		.id			= 0x4602,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 32,
		.name			= "AT25DF161",
	},
	{
		.id			= 0x4603,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 32,
		.name			= "AT25DL161",
	},
	{
		.id			= 0x4700,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 64,
		.name			= "AT25DF321",
	},
	{
		.id			= 0x4701,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 64,
		.name			= "AT25DF321A",
	},
	{
		.id			= 0x4800,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 128,
		.name			= "AT25DF641",
	},
	{
		.id			= 0x3217,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 128,
		.name			= "AT25QF641",
	},
	{
		.id			= 0x8501,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 16,
		.name			= "AT25SF081",
	},
	{
		.id			= 0x8600,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 32,
		.name			= "AT25DQ161",
	},
	{
		.id			= 0x8601,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 32,
		.name			= "AT25SF161",
	},
	{
		.id			= 0x8700,
		.l2_page_size		= 8,
		.pages_per_sector	= 16,
		.sectors_per_block	= 16,
		.nr_blocks		= 64,
		.name			= "AT25DQ321",
	},
};

static int adesto_write(struct spi_flash *flash, uint32_t offset, size_t len, const void *buf)
{
	struct adesto_spi_flash *stm = to_adesto_spi_flash(flash);
	unsigned long byte_addr;
	unsigned long page_size;
	size_t chunk_len;
	size_t actual;
	int ret;
	uint8_t cmd[4];

	page_size = min(1 << stm->params->l2_page_size, CONTROLLER_PAGE_LIMIT);
	byte_addr = offset % page_size;

	flash->spi->rw = SPI_WRITE_FLAG;
	ret = spi_claim_bus(flash->spi);
	if (ret) {
		spi_debug("SF: Unable to claim SPI bus\n");
		return ret;
	}

	for (actual = 0; actual < len; actual += chunk_len) {
		chunk_len = min(len - actual, page_size - byte_addr);

		cmd[0] = CMD_AT25DF_PP;
		cmd[1] = (offset >> 16) & 0xff;
		cmd[2] = (offset >> 8) & 0xff;
		cmd[3] = offset & 0xff;

		spi_debug("PP: 0x%p => cmd = { 0x%02x 0x%02x%02x%02x }"
		        " chunk_len = %u\n", buf + actual,
			cmd[0], cmd[1], cmd[2], cmd[3], chunk_len);

		ret = spi_flash_cmd(flash->spi, CMD_AT25DF_WREN, NULL, 0);
		if (ret < 0) {
			spi_debug("SF: Enabling Write failed\n");
			goto out;
		}

		ret = spi_flash_cmd_write(flash->spi, cmd, 4,
				buf + actual, chunk_len);
		if (ret < 0) {
			spi_debug("SF: Adesto Page Program failed\n");
			goto out;
		}

		ret = spi_flash_cmd_wait_ready(flash, SPI_FLASH_PROG_TIMEOUT);
		if (ret)
			goto out;

		offset += chunk_len;
		byte_addr = 0;
	}

	spi_debug("SF: Adesto: Successfully programmed %u bytes @"
			" 0x%lx\n", len, (unsigned long)(offset - len));

	ret = 0;

out:
	spi_release_bus(flash->spi);
	return ret;
}

static int adesto_erase(struct spi_flash *flash, uint32_t offset, size_t len)
{
	return spi_flash_cmd_erase(flash, CMD_AT25DF_SE, offset, len);
}

static int adesto_set_lock_flags(struct spi_flash *flash, int lock)
{
	int ret;
	uint8_t cmd;
	uint8_t status[2];

	flash->spi->rw = SPI_WRITE_FLAG;
	ret = spi_claim_bus(flash->spi);
	if (ret) {
		spi_debug("SF: Unable to claim SPI bus\n");
		return ret;
	}

	ret = spi_flash_cmd(flash->spi, CMD_AT25DF_RDSR1, &status[0], 1);
	if (ret) {
		spi_debug("SF: Unable to read Status Register 1\n");
		goto out;
	}

	ret = spi_flash_cmd(flash->spi, CMD_AT25DF_RDSR2, &status[1], 1);
	if (ret) {
		spi_debug("SF: Unable to read Status Register 2\n");
		goto out;
	}

	if (lock) {
		status[0] |= REG_W25_SRP0 | REG_W25_BP2 | REG_W25_BP1 | REG_W25_BP0;
	} else {
		status[0] &= ~(REG_W25_SRP0 | REG_W25_BP2 | REG_W25_BP1 | REG_W25_BP0);
	}

	status[0] &= ~(REG_W25_SEC | REG_W25_TB);
	status[1] &= ~(REG_W25_SRP1 | REG_W25_CMP);

	ret = spi_flash_cmd(flash->spi, CMD_AT25DF_WREN, NULL, 0);
	if (ret < 0) {
		spi_debug("SF: Enabling Write failed\n");
		goto out;
	}

	cmd = CMD_AT25DF_WRSR1;
	ret = spi_flash_cmd_write(flash->spi, &cmd, sizeof(cmd),
				  status, sizeof(status));
	if (ret < 0) {
		spi_debug("SF: Status register write failed\n");
		goto out;
	}

out:
	spi_release_bus(flash->spi);
	return ret;
}

static int adesto_unlock(struct spi_flash *flash)
{
	return adesto_set_lock_flags(flash, 0);
}

static int adesto_lock(struct spi_flash *flash)
{
	return adesto_set_lock_flags(flash, 1);
}

static int adesto_is_locked(struct spi_flash *flash)
{
	uint8_t status = 0;

	spi_flash_cmd(flash->spi, CMD_AT25DF_RDSR1, &status, 1);

	if ((status & (REG_W25_SRP0 | REG_W25_BP2 | REG_W25_BP1 | REG_W25_BP0))
	           == (REG_W25_SRP0 | REG_W25_BP2 | REG_W25_BP1 | REG_W25_BP0)) {
		return 1;
	}

	return 0;
}

struct spi_flash *spi_flash_probe_adesto(struct spi_slave *spi, uint8_t *idcode)
{
	const struct adesto_spi_flash_params *params;
	unsigned page_size;
	struct adesto_spi_flash *stm;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(adesto_spi_flash_table); i++) {
		params = &adesto_spi_flash_table[i];
		if (params->id == ((idcode[1] << 8) | idcode[2]))
			break;
	}

	if (i == ARRAY_SIZE(adesto_spi_flash_table)) {
		spi_debug("SF: Unsupported Adesto ID %02x%02x\n",
				idcode[1], idcode[2]);
		return NULL;
	}

	stm = malloc(sizeof(struct adesto_spi_flash));
	if (!stm) {
		spi_debug("SF: Failed to allocate memory\n");
		return NULL;
	}

	stm->params = params;
	stm->flash.spi = spi;
	stm->flash.name = params->name;

	/* Assuming power-of-two page size initially. */
	page_size = 1 << params->l2_page_size;

	stm->flash.write = adesto_write;
	stm->flash.spi_erase = adesto_erase;
	stm->flash.lock = adesto_lock;
	stm->flash.unlock = adesto_unlock;
	stm->flash.is_locked = adesto_is_locked;
	stm->flash.sec_sts = NULL;
	stm->flash.sec_read = NULL;
	stm->flash.sec_prog = NULL;
	stm->flash.sec_erase = NULL;
	stm->flash.sec_lock = NULL;
#if CONFIG_SPI_FLASH_NO_FAST_READ
	stm->flash.read = spi_flash_cmd_read_slow;
#else
	stm->flash.read = spi_flash_cmd_read_fast;
#endif
	stm->flash.sector_size = (1 << stm->params->l2_page_size) *
		stm->params->pages_per_sector;
	stm->flash.size = page_size * params->pages_per_sector
				* params->sectors_per_block
				* params->nr_blocks;

	return &stm->flash;
}
