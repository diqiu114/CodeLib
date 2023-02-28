/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author       dfs_ww@163.com
*
* @brief      参数文件读写类
*
* 版本:
* V1.0 2019-05-06 初始化版本编写 
***********************************************************/

#ifndef _PARAS_FILE_H_
#define _PARAS_FILE_H_

#include <stdbool.h>
#include "file.h"

class Paras_file : public File
{
public:
  Paras_file(FIL& fil, const char *file_name, unsigned int data_len);
  bool read(void *data);
  bool write(void *data);
  unsigned int read_para_len(void);
  bool clear(void);
  ~Paras_file();

private:
  unsigned short crc16(unsigned char *buff, unsigned int len);
  File_header header;
  unsigned char* buff;
};

#endif // _PARAS_FILE_H_
