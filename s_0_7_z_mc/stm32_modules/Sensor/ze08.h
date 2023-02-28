/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      纬盛科技 甲醛模块 ze08被动模式 串口驱动程序
*
*================= 模块被动模式协议如下 ======================
* 一、设置被动（问答）模式：
* 用户发送
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  保留   命令  问答  保留  保留  保留  保留  校验值 
*         0xFF  0x01  0x78  0x41   0x0  0x0   0x0   0x0   0x46
*
* 二、获取甲醛数据：
* 用户发送
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  保留   命令  保留  保留  保留  保留  保留  校验值 
*         0xFF  0x01  0x86  0x0   0x0  0x0   0x0   0x0   0x79
* 用户接收
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  命令  气体浓度   保留  保留  气体浓度   校验值 
*                     （ug/m3）               （ppb）
*                      H     L                H     L
*         0xFF  0x86  0x0  0x2A   0x0  0x0   0x0  0x20  0x30
***********************************************************/
#ifndef _ZE_08_H_
#define _ZE_08_H_

#include <stdbool.h>
#include "comm\double_buffered_comm.h"

#define CH2O_UG_LOWER_RANGE (0)
#define CH2O_UG_UPPER_RANGE (6250)

#define ZE08_COMM_TIMEOUT (200)

class Ze08
{
public:
  Ze08(Double_buffered_comm *_comm);
  ~Ze08();

  bool init(void);
  bool refresh_all_data(unsigned int timeout = ZE08_COMM_TIMEOUT);
  unsigned short get_ug_data(void);
  unsigned short get_ppb_data(void);
  bool is_error();

private:
  unsigned short ch2o_ug;
  unsigned short ch2o_ppb;
  unsigned char error_times;

  bool set_passive_mode();
  bool received_data(int timeout);
  bool pack_complete(unsigned char* data, unsigned int data_len);
  unsigned char crc8(unsigned char* data, unsigned int data_len);
  
  Double_buffered_comm *comm;
  unsigned char *buffer;
};

#endif // _ZE_08_H_
