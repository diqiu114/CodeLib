  /***********************************************************
  * @copyright  (C) COPYRIGHT DANFINSWE
  * @author      DFS Technology Department
  *
  * @brief      MVB模块通讯协议
  *
  *  本协议用于众志诚MVB模块通讯,格式如下:
  *  协议头(1字节)   包长度(1字节)  数据(1~N字节,最少包含1个字节的命令号)    CRC_MODBUS_RTU校验码(2字节) 协议尾(1字节)
  *
  * 说明:
  *     协议头: 0xFE(固定)
  *     包长度: 整个数据包的长度(从协议头到CRC校验)
  *     数据:   要发送的数据,1字节的命令号用于标示整个包的作用.
  *     CRC:   计算协议头~数据末端CRC,采用标准的MODBUS_RTU x16+x15+x2+1算法.
  *     协议尾: 0XFF(固定)
  * 版本:
  * V1.0 2018-11-05 初始程序编写 
  *
  ***********************************************************/

#ifndef _MVB_MODULE_PROTO_H_
#define _MVB_MODULE_PROTO_H_

#include "stdbool.h"
#include "protocol.h"



// pack header
#define MVB_MP_HEADER       ( 0xFE )
#define MVB_MP_TAIL         ( 0xFF )
#define MVB_MP_HEADER_IDX   ( 0 )
#define MVB_MP_HEADER_LEN   ( 1 )
#define MVB_MP_TAIL_LEN     ( 1 )
  
// pack length
#define MVB_MP_PACK_LEN_IDX ( 1 )
#define MVB_MP_PACK_LEN_LEN ( 1 )

// crc
#define MVB_MP_CRC_LEN      ( 2 )

// non-data length = header_length + pack_length + crc_length + tail_length
#define MVB_MP_NON_DATA_LEN ( (MVB_MP_HEADER_LEN) + (MVB_MP_PACK_LEN_LEN) + (MVB_MP_CRC_LEN) + (MVB_MP_TAIL_LEN))

// non-data length
#define MVB_MP_PACK_LEN_MIN ( MVB_MP_NON_DATA_LEN)

// data
#define MVB_MP_DATA_IDX     ( 2 )
#define MVB_MP_DATA_LEN_MIN ( 1 )



class MVB_module_proto : public Protocol
{
public:
  MVB_module_proto();
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer = true);
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt = 0);
  virtual unsigned int prot_len(void);
  virtual bool delete_pack_buffer();
  virtual ~MVB_module_proto();
private:
  unsigned int max_len;
  unsigned char *buff;
  unsigned short crc16(unsigned char* data, unsigned int len);
  bool pack_complete(unsigned char* pack, unsigned int len);
  int header_offset(unsigned char* pack, unsigned int pack_len);

};

#endif // _MVB_MODULE_PROTO_H_
