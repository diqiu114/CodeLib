/*
 * Copyright (c) 2020, Armink, <armink.ztl@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <fal.h>
#include "class_init.h"

#define FLASH_BLOCK_SIZE (512)

static unsigned char erase_buffer[FLASH_BLOCK_SIZE] = {0};

static int init(void)
{
  // buffer for fram erase initialize
  memset(erase_buffer, 0xff, sizeof(erase_buffer));

  return 1;
}

static int read(long offset, uint8_t *buf, size_t size)
{
  uint32_t addr = Fram_flash.addr + offset;

  Fm25_flash->read_bytes(addr, buf, size);

  return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
  uint32_t addr = Fram_flash.addr + offset;

  Fm25_flash->write_bytes(addr, (unsigned char *)buf, size);

  return size;
}

static int erase(long offset, size_t size)
{
  uint32_t addr = Fram_flash.addr + offset;

  Fm25_flash->write_bytes(addr, erase_buffer, size);

  return size;
}

//1.定义 flash 设备

const struct fal_flash_dev Fram_flash =
    {
        "fm25l256",
        1024,
        62 * FLASH_BLOCK_SIZE,
        FLASH_BLOCK_SIZE,
        {init, read, write, erase},
        1};
