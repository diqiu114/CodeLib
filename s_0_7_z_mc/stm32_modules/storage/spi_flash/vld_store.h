/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-09-08
 * 
 * @brief variable length data storage
 * 通过外部flash存储不定长数据, 通过设置最大存储长度,将flash划分为固定长度存储.
 * 比如:存储的长度为100-200之前的固定长度,那么将按照256字节固定长度存储.
 * 注意:1. 存储每条数目的最大长度为flash secotr大小.
 *      2. 每次erase sector会将sector内存储的数据全部清除,
 *         会造成部分数据丢失,丢失的数目为sector size 除以 最大存储长度.
 * 
 * // 添加数据
 * Data_record->append((char*)test);
 * // 弹出数据, 先进后出(stack)
 * Data_record->pop((char*)test1);
 * // 存储记录头
 * Data_record->store_record_info();
 * // 清除所有存储的数据
 * Data_record->clear();
 *
 * ***********************************************************
 */

#ifndef _VLD_STORE_H_
#define _VLD_STORE_H_

#include "crc\crc16_if.h"
#include "spi_flash_if.h"

/**
 * @brief record header
 * idx, record index
 * cnt, record count
 * ver, header version
 * crc, crc check, length from idx to ver 
 */
typedef struct _tag_record_header_ 
{
  unsigned short idx;
  unsigned short cnt;  
  unsigned short ver;
  unsigned short crc;
}Vld_record_header;

/**
 * @brief flash infomation
 * start addr, flash start address for VLD storage, must be 2^n
 * flash size, flash size for VLD storage, must be 2^n
 * sector size, flash sector size(erase size)
 */
typedef struct _tag_vld_flash_info_
{
  unsigned int start_addr;
  unsigned int flash_size;
  unsigned int sector_size;
}Vld_flash_info;

typedef bool(*Vld_header_store) (Vld_record_header &rh);

class Vld_store
{
public:
  Vld_store(Spi_flash_if* spi_flash, Vld_flash_info &_flash_info, unsigned short slice_size, Vld_record_header &_rh, Crc16_if* _crc);
  ~Vld_store();

  unsigned int get_record_cnt(void);
  bool store_record_info(void);
  bool set_store_cb(Vld_header_store _func);

  bool append(char *data, unsigned short data_len = 0);
  bool pop(char *data);
  bool clear(void);

private:
  bool init_ok;
  Vld_record_header rh;
  Vld_header_store func;
  Crc16_if* crc;
  unsigned short slice;
  Vld_flash_info flash_info;
  Spi_flash_if* flash;
  unsigned char* buff;
  unsigned int record_cnt_max;
};

#endif // _VLD_STORE_H_
