#include "paras_file.h"
#include <string.h>

Paras_file::Paras_file(FIL &fil, const char *file_name, unsigned int data_len) : File(fil, file_name)
{
  memset(&header, 0, sizeof(header));
  
  if (header_need_init())
  {
    header.data_cnt = 0;
    header.data_cnt_max = 1;
    header.data_fixed_len = data_len + sizeof(unsigned short);
    header.data_idx = 0;
    header.data_overwrite = true;
    header.crc = crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));

    create(&header);
  }
  else
  {
    read_header(&header);
    unsigned short crc_verify = crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));

    if( crc_verify != header.crc || header.data_fixed_len != (data_len + sizeof(unsigned short)) 
      || header.data_cnt_max != 1)
    {
      header.data_fixed_len = data_len + sizeof(unsigned short);
      header.data_cnt_max = 1;
      write_header(&header, true);
    }
  }

  buff = new unsigned char[data_len + sizeof(unsigned short)];
  memset(buff, 0, data_len + sizeof(unsigned short));
}

bool Paras_file::clear(void)
{
  header.data_cnt_max = 1;
  header.data_cnt = 0;
  header.data_idx = 0;
  return (write_header(&header, true) == F_OK);
}

bool Paras_file::read(void *data)
{
  bool ret = false;
  unsigned short crc_len = sizeof(unsigned short);
  unsigned int data_len = header.data_fixed_len - crc_len;

  if (File::read(buff, header.data_fixed_len) == F_OK)
  {
    unsigned short crc = crc16(buff, data_len);
    if (memcmp(&crc, &buff[data_len], crc_len) == 0)
    {
      memcpy(data, buff, data_len);
      ret = true;
    }
  }

  return ret;
}

bool Paras_file::write(void *data)
{
  bool ret = false;
  unsigned short crc_len = sizeof(unsigned short);
  unsigned int data_len = header.data_fixed_len - crc_len;
  

  // copy data and crc to buffer
  memcpy(buff, data, data_len);

  unsigned short crc = crc16(buff, data_len);

  memcpy(&buff[data_len], &crc, crc_len);

  if( File::write(buff, header.data_fixed_len) == F_OK)
  {
    ret = true;
  }

  return ret;
}

unsigned int Paras_file::read_para_len(void)
{
  return get_fixed_data_len();
}

unsigned short Paras_file::crc16(unsigned char *buff, unsigned int len)
{
  unsigned int i, j;
  unsigned short crc = 0xffff;

  for (i = 0; i < len; i++)
  {
    crc ^= (unsigned short)(buff[i]);
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

Paras_file::~Paras_file()
{
}
