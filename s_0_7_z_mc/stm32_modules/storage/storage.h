/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      存储类
*
* 版本:
* V1.0 2018-11-09 初始版本程序编写 
***********************************************************/

#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "stdbool.h"

class Storage
{
public:
  virtual bool init(void) = 0;
  virtual bool read(unsigned short addr, unsigned short *data, unsigned int data_cnt) = 0;
  virtual bool write(unsigned short addr, unsigned short *data, unsigned int data_cnt) = 0;
};

#endif // _STORAGE_H_
