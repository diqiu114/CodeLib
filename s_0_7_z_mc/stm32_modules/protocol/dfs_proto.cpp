#include "dfs_proto.h"
#include "string.h"

DFS_proto::DFS_proto(Dfs_prot_ver ver)
{
  proto_ver = ver;
  if (proto_ver == PROT_VER2)
  {
    pack_len_bytes = 2;
  }
  else
  {
    pack_len_bytes = 1;
  }

  protocol_bytes_without_data = DFS_PROTO_HEADER_LEN + pack_len_bytes + DFS_PROTO_CRC_LEN;
  data_idx = DFS_PROTO_HEADER_LEN + pack_len_bytes;
  pack_buffer = NULL;
  pack_max_len = 0;
}

unsigned int DFS_proto::pack(unsigned char *data, unsigned int data_cnt, unsigned char *pack, bool delete_pack_buffer)
{
  if ((data_cnt == 0) || (data == NULL) || (pack == NULL))
  {
    return 0;
  }

  unsigned short pack_len = data_cnt + protocol_bytes_without_data;
  if(pack_len > pack_max_len)
  {
    pack_max_len = pack_len;
    
    if(pack_buffer != NULL)
    {
      delete[]pack_buffer;
      pack_buffer = NULL;
    }
    
    if(pack_buffer == NULL)
    {
      pack_buffer = new unsigned char[pack_max_len];
      if (pack_buffer == NULL)
      {
        return 0;
      }
    }
  }

  memset(pack_buffer, 0, pack_len);

  // fill header and length
  pack_buffer[0] = DFS_PROTO_HEADER;
  if (proto_ver == PROT_VER2)
  {
    pack_buffer[1] = (pack_len >> 8);
    pack_buffer[2] = (pack_len >> 0);
  }
  else
  {
    pack_buffer[1] = pack_len;
  }

  // fill data
  memcpy(pack_buffer + data_idx, data, data_cnt);

  // calc crc
  unsigned short crc = crc16(pack_buffer, pack_len - DFS_PROTO_CRC_LEN);

  // append crc
  pack_buffer[pack_len - 2] = (unsigned char)(crc);
  pack_buffer[pack_len - 1] = (unsigned char)(crc >> 8);

  // copy data
  memcpy(pack, pack_buffer, pack_len);

//  delete[] pack_buffer;

  return pack_len;
}

unsigned int DFS_proto::prot_len(void)
{
  return protocol_bytes_without_data;
}

unsigned int DFS_proto::unpack(unsigned char *pack, unsigned int pack_cnt, unsigned char *data, unsigned int msg_fix_cnt)
{
  if ((pack_cnt < DFS_PROTO_PACK_LEN_MIN) ||
      (data == NULL) || (pack == NULL))
  {
    return 0;
  }

  int offset = header_offset(pack, pack_cnt);
  if (offset < 0)
  {
    return 0;
  }

  unsigned char *n_pack = pack + offset;
  unsigned short n_pack_len = pack_cnt - offset;

  if (pack_complete(n_pack, n_pack_len))
  {
    unsigned short data_len = 0;
    // copy data to ret_data
    if (proto_ver == PROT_VER2)
    {
      data_len = ((n_pack[DFS_PROTO_PACK_LEN_IDX] << 8) | n_pack[DFS_PROTO_PACK_LEN_IDX + 1]) - protocol_bytes_without_data;
    }
    else
    {
      data_len = n_pack[DFS_PROTO_PACK_LEN_IDX] - protocol_bytes_without_data;
    }

    memcpy(data, n_pack + data_idx, data_len);

    return data_len;
  }
  else
  {
    return 0;
  }
}

bool DFS_proto::pack_complete(unsigned char *pack, unsigned int pack_len)
{
  unsigned short crc = 0;
  crc = crc16(pack, pack_len - sizeof(crc));

  bool crc_correct = (pack[pack_len - 2] == (unsigned char)(crc)) && (pack[pack_len - 1] == (unsigned char)(crc >> 8));
  bool header_correct = (pack[DFS_PROTO_HEADER_IDX] == DFS_PROTO_HEADER);
  bool pack_len_correct = false;
  if (proto_ver == PROT_VER2)
  {
    pack_len_correct = (((pack[DFS_PROTO_PACK_LEN_IDX] << 8) | pack[DFS_PROTO_PACK_LEN_IDX + 1]) == pack_len);
  }

  else
  {
    pack_len_correct = (pack[DFS_PROTO_PACK_LEN_IDX] == pack_len);
  }

  return (crc_correct && header_correct && pack_len_correct);
}

int DFS_proto::header_offset(unsigned char *pack, unsigned int pack_len)
{
  int ret = -1;
  int i = 0;

  for (i = 0; i < pack_len; i++)
  {
    if (pack[i] == DFS_PROTO_HEADER)
    {
      ret = i;
      break;
    }
  }

  return ret;
}

unsigned short DFS_proto::crc16(unsigned char *pBuff, unsigned int len)
{
  unsigned int i, j;
  unsigned short crc = 0xffff;

  for (i = 0; i < len; i++)
  {
    crc ^= (unsigned short)(pBuff[i]);
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
      {
        crc >>= 1;
        crc ^= 0xa001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}

DFS_proto::~DFS_proto()
{
}
