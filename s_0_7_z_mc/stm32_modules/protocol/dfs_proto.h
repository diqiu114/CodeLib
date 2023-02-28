  /***********************************************************
  * @copyright  (C) COPYRIGHT DANFINSWE
  * @author      DFS Technology Department
  *
  * @brief      communicate protocol
  *
  *  本协议用于DANFINSWE内部模块之间的通讯协议,格式如下:
  *  协议头(1字节)   包长度(1字节/2字节)  数据(1~N字节,最少包含1个字节的命令号)    CRC_MODBUS_RTU校验码(2字节)
  *
  * 说明:
  *     协议头: 0xFE(固定)
  *     包长度: 整个数据包的长度(从协议头到CRC校验)
  *     数据:   要发送的数据,1字节的命令号用于标示整个包的作用.
  *     CRC:   计算协议头~数据末端CRC。低字节在前，高字节在后。采用标准的MODBUS_RTU x16+x15+x2+1算法.
  *
  * 版本:
  * V1.4 2019-06-23 构造函数增加协议版本，区分数据长度
  * V1.3 2019-05-13 修复pack/unpack函数中数据长度类型定义错误     
  * V1.2 2019-05-11 将包长度修改为2个字节，扩展一个包可发送的长度  
  * V1.1 2018-12-02 增加将pack和unpack定义为虚函数               
  * V1.0 2018-03-30 增加包头位置检测,在包头前有无用字节时,自动滤除 
  *
  ***********************************************************/

#ifndef _DFS_PROTO_H_
#define _DFS_PROTO_H_

#include "stdbool.h"
#include "protocol.h"

// data min lenght + non-data length
#define DFS_PROTO_PACK_LEN_MIN ( 5 )

// pack header
#define DFS_PROTO_HEADER       ( 0xFE )
#define DFS_PROTO_HEADER_IDX   ( 0 )
#define DFS_PROTO_HEADER_LEN   ( 1 )

// pack length
#define DFS_PROTO_PACK_LEN_IDX ( 1 )

// crc
#define DFS_PROTO_CRC_LEN      ( 2 )

#define DFS_PROTO_DATA_LEN_MIN ( 1 )

typedef enum _tag_protocol_ver_
{
  PROT_VER1,
  PROT_VER2
}Dfs_prot_ver;

class DFS_proto : public Protocol
{
public:
  DFS_proto(Dfs_prot_ver ver = PROT_VER1);
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer = true);
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt = 0);
  virtual unsigned int prot_len(void);
  virtual bool delete_pack_buffer(){ return true;};
  virtual ~DFS_proto();
private: 
  unsigned char *pack_buffer;
  unsigned int pack_max_len;
  unsigned short crc16(unsigned char* data, unsigned int len);
  bool pack_complete(unsigned char* pack, unsigned int len);
  int header_offset(unsigned char* pack, unsigned int pack_len);
  unsigned int pack_len_bytes;
  unsigned int protocol_bytes_without_data;
  unsigned int data_idx;
  Dfs_prot_ver proto_ver;
};

#endif // _DFS_PROTO_H_
