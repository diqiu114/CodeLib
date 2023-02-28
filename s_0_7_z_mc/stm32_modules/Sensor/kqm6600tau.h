/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      深圳慧联智控 TVOC模块 串口驱动程序
* 模块为串口通讯,上电后默认往外发送VOC数据, 每1秒钟1次.使用的VOC芯片为敏源的MVOC.
* 默认通讯波特率为9600 
* VOC范围为:0-30PPM(数值再大不精准)
* 输出数值单位为0.1PPM
*================= 数据格式如下 ======================
* 
* 字节1  字节2   字节3    字节4
* 地址码 输出高位 输出低位 校验值
*
* 地址码:0x5F
* 输出高位:数据16进制输出高位
* 输出低位:数据16进制输出低位
* 校验值: 前3个字节校验和的低字节
* 
* 通讯举例:
* 模块输出数据 0x5F 0x01 0x2C 0x8C
* 地址码:0x5F
* 数据:0x012C = 300, 300 * 0.1PPM = 30PPM
* 校验值:0x5F+0x01+0x2C=0x8C
*
* ----注:模块上电时会进行一段时间预热,预热时数据高低均输出为0xFF,此时可忽略数据----
* 
***********************************************************/
#ifndef _KQM_6600TAU_H_
#define _KQM_6600TAU_H_

#include <stdbool.h>
#include "comm\double_buffered_comm.h"

#define KQM_HEADER (0x5F)
#define KQM_DATA_LEN (4)

class Kqm6600tau
{
public:
  Kqm6600tau(Double_buffered_comm *_comm);
  ~Kqm6600tau();

  bool update(void);
  unsigned short get_tvoc(void);

private:
  bool pack_complete(void);
  unsigned char crc8(unsigned char *data, unsigned int data_len);

  Double_buffered_comm *comm;
  unsigned char buffer[KQM_DATA_LEN];
  unsigned short tvoc;
};

#endif // _KQM_6600TAU_H_
