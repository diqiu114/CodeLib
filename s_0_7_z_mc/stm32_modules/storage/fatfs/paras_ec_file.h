/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author       dfs_ww@163.com
*
* @brief      参数文件读写类,使用备份文件保存关键参数,具备主文件失败时,使用备份文件回写功能
*
* 版本:
* V1.0 2019-05-06 初始化版本编写 
***********************************************************/

#ifndef _PARAS_EC_FILE_H_
#define _PARAS_EC_FILE_H_

#include "paras_file.h"

#define PARAS_BAK_FILE_SUFFIX ("_bak")

class Paras_ec_file
{
public:
  Paras_ec_file(FIL& fil, const char *file_name, unsigned int data_len);
  ~Paras_ec_file();
  
  bool read(void *data);
  bool write(void *data);
  
  unsigned int get_count(void);
  bool clear(void);
  unsigned int read_para_len(void);
  bool remove(void);

private:
  Paras_file *main_file;
  Paras_file *backup_file;
  unsigned char *buff;
  int buff_len;
};

#endif // _PARAS_EC_FILE_H_
