/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      成都9号线以太网协议
*
* 版本:
* V1.1 2019-04-26 在pack(), unpack()函数前加上virtual关键字
* V1.0 2018-04-03 初始版本程序编写 
***********************************************************/

#ifndef _TRAIN_ETH_PROTO_H_
#define _TRAIN_ETH_PROTO_H_

#include "stdbool.h"
#include "protocol.h"

#define TRAIN_EP_MSG_TYPE_IDX     ( 3 )
#define TRAIN_EP_MSG_ID_IDX       ( 4 )
#define TRAIN_EP_MSG_DEST_ID_IDX  ( 18 )
#define TRAIN_EP_MSG_SRC_DEV_STR_IDX  ( 27 )
#define TRAIN_EP_DATA_LEN_IDX     ( 7 )

#define TRAIN_EP_MSG_TYPE_TICK    ( 0x03 )
#define TRAIN_EP_MSG_TYPE_STATE   ( 0x01 )
#define TRAIN_EP_PROTOCOL_TYPE    ( 0x01 )
#define TRAIN_EP_PROTOCOL_VER     ( 0x10 )
#define TRAIN_EP_CITY             ( 0x01 )
#define TRAIN_EP_LINE             ( 0x07 )
#define TRAIN_EP_TRAIN_NUM_HI     ( 0x1B )
#define TRAIN_EP_TRAIN_NUM_LO     ( 0x5A )
#define TRAIN_EP_DEST_DEV1        ( 0X01 )
#define TRAIN_EP_DEST_DEV2        ( 0x02 )

#define TRAIN_EP_MSG_ID_BYTES       ( 4 )
#define TRAIN_EP_CRC_BYTES          ( 2 )
#define TRAIN_EP_SRC_DEV_STR_BYTES  ( 9 )


extern const char* TRAIN_EP_SRC_STR[4];

extern const unsigned char TRAIN_EP_HEADER[3];
extern const unsigned char TRAIN_EP_TAIL[3];

class Train_eth_proto : public Protocol
{
public:

  Train_eth_proto();
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack);
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data);
  virtual unsigned int prot_len(void);
  virtual ~Train_eth_proto();
private:
  unsigned short crc16(unsigned char* data, unsigned int len);
  bool pack_complelte(unsigned char* pack, unsigned int len);
};


#endif // _TRAIN_ETH_PROTO_H_
