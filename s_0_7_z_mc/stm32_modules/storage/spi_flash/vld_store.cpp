#include "vld_store.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 将数值转换为最近的2^n次方值, 比如 65 --> 128, 120 --> 128
#define DATA_ALIGN(x) (pow(2, (ceil(log((float)x) / log(2.0f)))))

#define FLASH_UNUSED ((unsigned short)(0xFFFF))

#define RECORD_LEN_BYTES (sizeof(short))

/**
 * @brief Construct a new Vld_store::Vld_store object
 * 
 * @param spi_flash spi flash interface
 * @param _flash_info flash infomation
 * @param slice_size max record data length, must less than flash_info.sector size
 * @param _rh record header
 * @param _crc crc calculate
 */
Vld_store::Vld_store(Spi_flash_if *spi_flash,
                     Vld_flash_info &_flash_info,
                     unsigned short slice_size,
                     Vld_record_header &_rh,
                     Crc16_if *_crc)
{
  crc = _crc;
  func = NULL;
  rh = _rh;
  flash = spi_flash;
  flash_info = _flash_info;

  // 每条信息的最大长度需小于Flash sector大小
  slice_size = slice_size > flash_info.sector_size ? flash_info.sector_size : slice_size;
  slice_size = slice_size == 0 ? RECORD_LEN_BYTES + 1: slice_size;
  
  // 信息最大长度对齐为2^n次方
  slice = DATA_ALIGN(slice_size);
  
  record_cnt_max = flash_info.flash_size / slice;

  buff = new unsigned char[slice];
  if (buff != NULL)
  {
    memset(buff, 0, slice);
  }

  init_ok = (crc != NULL) && (buff != NULL) && (flash != NULL);
}

Vld_store::~Vld_store()
{
  if (crc != NULL)
  {
    delete crc;
    crc = NULL;
  }

  if (flash != NULL)
  {
    delete flash;
    flash = NULL;
  }
}

/**
 * @brief get record count
 * 
 * @return unsigned int record count store in flash
 */
unsigned int Vld_store::get_record_cnt(void)
{
  return rh.cnt;
}

bool Vld_store::store_record_info(void)
{
  if (func == NULL)
  {
    return false;
  }

  return func(rh);
}

bool Vld_store::set_store_cb(Vld_header_store _func)
{
  if (_func == NULL)
  {
    return false;
  }

  func = _func;

  return true;
}

/**
 * @brief append data record to flash
 * 
 * @param data data pointer
 * @param data_len data length, if data type is string, data length = 0
 * @return true append success
 * @return false append failed
 */
bool Vld_store::append(char *data, unsigned short data_len)
{
  if ((!init_ok) || (data == NULL))
  {
    return false;
  }

  bool ret = true;

  // 确定写入地址
  unsigned int write_addr = flash_info.start_addr + rh.idx * slice;

  // 确定写入地址是否可用
  unsigned short tmp = 0;
  flash->read_bytes(write_addr, (unsigned char *)&tmp, sizeof(tmp));
  if (tmp != FLASH_UNUSED)
  {
    flash->erase(write_addr);
    // at over-write situation, decrease total storage count,
    if (rh.cnt == record_cnt_max)
    {
      rh.cnt -= flash_info.sector_size / slice + (flash_info.sector_size % slice == 0 ? 0 : 1);
    }
  }

  // 写入数据
  unsigned short write_data_len = data_len == 0 ? strlen(data) : data_len;
  unsigned short write_data_len_max = slice - sizeof(write_data_len);

  write_data_len = write_data_len <= write_data_len_max ? write_data_len : write_data_len_max;

  // write data length
  flash->write_bytes(write_addr, (unsigned char *)(&write_data_len), sizeof(write_data_len));
  // write data
  flash->write_bytes(write_addr + sizeof(write_data_len), (unsigned char *)data, write_data_len);

  // 更新header
  rh.idx++;

  if (rh.idx >= record_cnt_max)
  {
    rh.idx = 0;
  }

  if (rh.cnt < record_cnt_max)
  {
    rh.cnt++;
  }

  // update header crc
  rh.crc = crc->calc((unsigned char *)&rh, sizeof(rh) - sizeof(short));

  return ret;
}

/**
 * @brief pop data from flash
 * 
 * @param data return data pointer
 * @return true pop success
 * @return false pop failed
 */
bool Vld_store::pop(char *data)
{
  if ((!init_ok) || (data == NULL) || (rh.cnt == 0))
  {
    return false;
  }

  bool ret = false;

  unsigned short read_idx = 0;
  if (rh.idx != 0)
  {
    read_idx = rh.idx - 1;
  }
  else if ((rh.idx == 0) && (rh.cnt == record_cnt_max))
  {
    read_idx = record_cnt_max - 1;
  }

  unsigned int read_addr = flash_info.start_addr + read_idx * slice;
  memset(buff, 0, slice);

  flash->read_bytes(read_addr, buff, slice);
  unsigned short data_len = buff[0] | (buff[1] << 8);

  if ((data_len != FLASH_UNUSED) && (data_len < slice))
  {
    strncpy(data, (char *)buff + 2, data_len);
    ret = true;
    rh.cnt--;

    if (rh.idx != 0)
    {
      rh.idx--;
    }
    else
    {
      rh.idx = record_cnt_max;
    }
  }

  // update header crc
  rh.crc = crc->calc((unsigned char *)&rh, sizeof(rh) - sizeof(short));

  return ret;
}

/**
 * @brief clear all record from flash
 * 
 * @return true clear success
 * @return false clear failed
 */
bool Vld_store::clear(void)
{
  bool ret = true;

  rh.idx = 0;
  rh.cnt = 0;

  // update header crc
  rh.crc = crc->calc((unsigned char *)&rh, sizeof(rh) - sizeof(short));

  if (func == NULL)
  {
    ret = store_record_info();
  }
  
  return ret;
}
