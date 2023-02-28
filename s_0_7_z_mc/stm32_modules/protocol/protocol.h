/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      协议类
*
* 版本:
* V1.0 2018-04-03 
***********************************************************/

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "stdbool.h"

class Protocol
{
public:
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer = true) = 0;
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt = 0) = 0;
  virtual unsigned int prot_len(void) = 0;
  virtual bool delete_pack_buffer() = 0;
  virtual ~Protocol(){};
};


#endif // _PROTOCOL_H_
