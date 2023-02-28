#include "train_eth_proto.h"
#include "string.h"

const char* TRAIN_EP_SRC_STR[4] = {"TC1BMS", "MPBMS", "MBMS", "TC2BMS"};

const unsigned char TRAIN_EP_HEADER[3] = {0xAA, 0xAB, 0xAC};
const unsigned char TRAIN_EP_TAIL[3] = {0xBA, 0xBB, 0xBC};

Train_eth_proto::Train_eth_proto()
{

}

unsigned int Train_eth_proto::pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack)
{
  if( (data_cnt == 0) || (data == NULL) || (pack == NULL) )
  {
    return 0;
  }

  unsigned short crc = crc16(data, data_cnt);
  unsigned char header_len = sizeof(TRAIN_EP_HEADER);
  unsigned int data_index = header_len;
  unsigned int crc_index = header_len + data_cnt;
  unsigned int tail_index = crc_index + sizeof(crc);

  unsigned int pack_len = header_len + data_cnt + sizeof(crc) + sizeof(TRAIN_EP_TAIL);

  unsigned char* buffer = new unsigned char[pack_len];
  if( buffer == NULL )
  {
    return 0;
  }

  // append header
  memcpy(buffer, TRAIN_EP_HEADER, header_len);

  // append data
  memcpy(buffer+data_index, data, data_cnt);

  // append crc
  memcpy(buffer+crc_index, (unsigned char*)&crc, sizeof(crc));

  // append tail
  memcpy(buffer+tail_index, TRAIN_EP_TAIL, sizeof(TRAIN_EP_TAIL));
  
  memcpy(pack, buffer, pack_len);

  delete []buffer;

  return (pack_len);
}

unsigned int Train_eth_proto::unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data)
{
  if( ( pack_cnt <= ( sizeof(TRAIN_EP_HEADER) + sizeof(TRAIN_EP_TAIL) + TRAIN_EP_CRC_BYTES ) ) || 
      (data == NULL) || (pack == NULL) )
  {
    return 0;
  }

  if( pack_complelte(pack, pack_cnt) )
  {
    unsigned char header_len = sizeof(TRAIN_EP_HEADER);
    unsigned int data_cnt = pack_cnt - header_len - TRAIN_EP_CRC_BYTES - sizeof(TRAIN_EP_TAIL);

    memcpy(data, pack + header_len, data_cnt );

    return data_cnt;
  }
  else
  {
    return 0;
  }
}

unsigned int Train_eth_proto::prot_len(void)
{
  return sizeof(TRAIN_EP_HEADER) + sizeof(TRAIN_EP_TAIL) + TRAIN_EP_CRC_BYTES;
}

bool Train_eth_proto::pack_complelte(unsigned char* pack, unsigned int len)
{
  // compare header
  if( memcmp(pack, TRAIN_EP_HEADER, sizeof(TRAIN_EP_HEADER)) != 0 )
  {
    return false;
  }
  
  // compare tail
  if( memcmp(pack + (len - sizeof(TRAIN_EP_TAIL)), TRAIN_EP_TAIL, sizeof(TRAIN_EP_TAIL)) != 0 )
  {
    return false;
  }
    
  unsigned int data_cnt = len - sizeof(TRAIN_EP_HEADER) - TRAIN_EP_CRC_BYTES - sizeof(TRAIN_EP_TAIL);

  unsigned short crc = crc16(pack + sizeof(TRAIN_EP_HEADER), data_cnt);

  unsigned int crc_high_index = len - sizeof(TRAIN_EP_TAIL) -1;
  unsigned int crc_low_index = len - sizeof(TRAIN_EP_TAIL) -2;
  
  // crc check
  if( (unsigned char)(crc>>8) == pack[crc_high_index] && 
      (unsigned char)(crc>>0) == pack[crc_low_index] )
  {
    return true;
  }
  else
  {
    return false;
  }

}

unsigned short Train_eth_proto::crc16(unsigned char* data, unsigned int len)
{
  char b = 0;
  unsigned short crc = 0xFFFF;
  int i = 0;
  int j = 0;

  for(i = 0; i < len; i++)
  {
    for(j = 0; j < 8; j++)
    {
      b = ((data[i]<<j) & 0x80) ^ ((crc&0x8000) >> 8);
      crc <<= 1;
      if(b != 0)
      {
        crc ^= 0x1021;
      }
    }
  }

  return(crc);
}

Train_eth_proto::~Train_eth_proto()
{

}
