/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      纬盛科技 PM2.5模块 ZH03B被动模式 串口驱动程序
*
*================= 模块被动模式协议如下 ======================
* 一、设置被动（问答）模式：
* 用户发送
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  保留   命令  问答  保留  保留  保留  保留  校验值 
*         0xFF  0x01  0x78  0x41   0x0  0x0   0x0   0x0   0x46
*
* 二、获取PM数据：
* 用户发送
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  保留   命令  保留  保留  保留  保留  保留  校验值 
*         0xFF  0x01  0x86  0x0   0x0  0x0   0x0   0x0   0x79
* 用户接收
* 字节偏移  0    1     2     3     4     5    6     7     8
*         起始  命令    PM2.5        PM10       PM1.0    校验值 
*         0xFF  0x86  0x0  0x85   0x0  0x96   0x0  0x65  0xFA 
***********************************************************/
#ifndef _ZH_03B_H_
#define _ZH_03B_H_

#include <stdbool.h>
#include "comm\double_buffered_comm.h"

#define PM2_5_LOWER_RANGE (0)
#define PM2_5_UPPER_RANGE (1000)
#define PM10_LOWER_RANGE (0)
#define PM10_UPPER_RANGE (1000)

typedef struct _zh03b_data_
{
  unsigned short pm0_3;
  unsigned short pm0_5;
  unsigned short pm1;
  unsigned short pm2_5;
  unsigned short pm5;
  unsigned short pm10;
} Zh03b_data;

#define ZH03B_COMM_TIMEOUT (200)

class Zh03b
{
public:
  Zh03b(Double_buffered_comm *_comm);
  ~Zh03b();

  bool init(void);
  void exit_sleep(void);
  bool get_data(Zh03b_data *_data, unsigned int timeout = ZH03B_COMM_TIMEOUT);
  bool is_error();

private:
  bool set_passive_mode();
  bool received_data(int timeout);
  bool pack_complete(unsigned char* data, unsigned int data_len);
  unsigned char crc8(unsigned char* data, unsigned int data_len);
  
  Double_buffered_comm *comm;
  unsigned char *buffer;
  unsigned char error_times;
};

#endif // _ZH_03B_H_
