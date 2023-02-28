#include "mvb_module_proto.h"
#include "string.h"

MVB_module_proto::MVB_module_proto()
{
  max_len = 0;
  buff = NULL;
}

bool MVB_module_proto::delete_pack_buffer()
{
  if(buff == NULL)
  {
    return false;
  }
  max_len = 0;
  delete[] buff;
  buff = NULL;
  return true;
}

unsigned int MVB_module_proto::pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer)
{
  if( (data_cnt == 0) || (data == NULL) || (pack == NULL) )
  {
    return 0;
  }

  unsigned char  pack_len = data_cnt + MVB_MP_NON_DATA_LEN;
  
  if(max_len < pack_len)
  {    
    if(buff != NULL)
    {
      delete[] buff;
      buff = NULL;
    }
    buff = new unsigned char[pack_len];
    if(buff == NULL)
    {
      max_len = 0;
      return 0;
    }
    max_len = pack_len;
  }

  memset(buff, 0, pack_len);

  // fill header and length
  buff[0] = MVB_MP_HEADER;
  buff[1] = pack_len;

  // fill data
  memcpy(buff + MVB_MP_DATA_IDX, data, data_cnt);

  // calc crc
  unsigned short crc = crc16(buff, pack_len - MVB_MP_CRC_LEN - MVB_MP_TAIL_LEN);

  // append crc
  buff[pack_len - 3] = (unsigned char)( crc >> 8 );
  buff[pack_len - 2] = (unsigned char)( crc >> 0 );

  // append tail
  buff[pack_len - 1] = MVB_MP_TAIL;

  // copy data
  memcpy(pack, buff, pack_len);

  if(delete_pack_buffer)
  {
    delete[] buff;
    buff = NULL;
    max_len = 0;
  }
  
  return pack_len;
}

unsigned int MVB_module_proto::unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt)
{
  if( (pack_cnt <= MVB_MP_PACK_LEN_MIN ) || 
      (data == NULL) || (pack == NULL) )
  {
    return 0;
  }

  int offset        = header_offset(pack, pack_cnt);
  if(  offset < 0 )
  {
    return 0;
  }

  unsigned char *n_pack    = pack + offset;
  unsigned char n_pack_len = pack_cnt - offset;

  if( pack_complete(n_pack, n_pack_len) )
  {
    // copy data to ret_data
    unsigned char data_len = n_pack[MVB_MP_PACK_LEN_IDX] - MVB_MP_NON_DATA_LEN;

    memcpy(data, n_pack + MVB_MP_DATA_IDX, data_len);

    return data_len;
  }
  else
  {
    return 0;
  }
}

unsigned int MVB_module_proto::prot_len(void)
{
  return MVB_MP_NON_DATA_LEN;
}

bool MVB_module_proto::pack_complete(unsigned char *pack, unsigned int pack_len)
{
  unsigned short crc = crc16(pack, pack_len - MVB_MP_CRC_LEN - MVB_MP_TAIL_LEN);

  bool crc_correct      = ( pack[pack_len - 3] == (unsigned char)( crc >> 8))
                          && ( pack[pack_len - 2] == (unsigned char)( crc >> 0 ));
  bool header_correct   = ( pack[MVB_MP_HEADER_IDX] == MVB_MP_HEADER );
  bool pack_len_correct = ( pack[MVB_MP_PACK_LEN_IDX] == pack_len );
  bool tail_correct     = ( pack[pack_len-1] == MVB_MP_TAIL);

  return ( crc_correct && header_correct && pack_len_correct && tail_correct);
}

int MVB_module_proto::header_offset(unsigned char* pack, unsigned int pack_len)
{
  int ret = -1;
  int i   = 0;

  for(i = 0; i < pack_len; i++)
  {
    if( pack[i] == MVB_MP_HEADER )
    {
      ret = i;
      break;
    }
  }

  return ret;
}

const unsigned short crc_table[] =
{
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

unsigned short MVB_module_proto::crc16(unsigned char* data, unsigned int len)
{
  int counter;
  unsigned char *p =data;
  unsigned short crc = 0x0000;
  
  for( counter = 0; counter < len; counter++)
  {
    crc = (crc<<8) ^ crc_table[((crc>>8) ^ *(char *)p++)&0x00FF];
  }
  
  return crc;
}


MVB_module_proto::~MVB_module_proto()
{

}
