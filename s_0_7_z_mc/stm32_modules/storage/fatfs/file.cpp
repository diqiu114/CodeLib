
#include "file.h"
#include "string.h"
#include "modules_def.h"
#include "pvd.h"
#include "..\crc\crc16_modbus.h"

File::File(FIL &fil, const char *file_str) : fp(fil)
{
  unsigned char str_len = strlen(file_str) + 1;
  file_name = new char[str_len];
  memcpy(file_name,file_str,str_len);
  crc = new Crc16_modbus();
  
  file_status = FS_NOT_EXIST;
  unsigned int bytes_read = 0;
  header_initialized = false;
  f_callback = NULL;
  memset(&header, 0, sizeof(header));
  memset(&fp,0,sizeof(fp));
  
  if( f_open(&fp, file_name, FA_READ | FA_OPEN_EXISTING) == FR_OK )
  {
    if ((f_read(&fp, (unsigned char *)(&header), sizeof(File_header), &bytes_read) == FR_OK) && (bytes_read == sizeof(File_header)))
    {
      unsigned short crc_verify = crc->calc((unsigned char *)(&header), sizeof(File_header)-sizeof(header.crc));
      
      if (crc_verify == header.crc && header.data_cnt_max != 0)
      {
        header_initialized = true;
      }

      file_status = FS_OK;
    }

    f_close(&fp);

  }
}

void File::set_forward_callback(forwrad_callback func)
{
  f_callback = func;
}
#ifndef USE_LITTLE_FS
bool File::forward_data(void)
{
  FRESULT rc = FR_OK;
  UINT dmy;
  if (f_callback == NULL)
  {
    return false;
  }

  /* Open the file in read only mode */
  if (fp.obj.fs != 0)
  {
    f_close(&fp);
  }

  rc = f_open(&fp, file_name, FA_READ);
  if (rc != FR_OK)
  {
    return false;
  }

  // skip header
  if (f_lseek(&fp, sizeof(File_header)) != FR_OK)
  {
    f_close(&fp);
    return F_ERROR;
  }

  unsigned int data_cnt = header.data_cnt;

  // forward data
  while ((rc == FR_OK) && (data_cnt > 0)) //!f_eof(&Fil)
                                          //  while ((rc == FR_OK) && !f_eof(&fp))
  {
    /* Fill output stream periodicaly or on-demand */
    rc = f_forward(&fp, f_callback, header.data_fixed_len, &dmy);
    data_cnt--;
    DELAY_MS(2);
  }

  //  f_forward(&fp, f_callback, 0, &dmy);

  /* Close the file and return */
  f_close(&fp);

  if ((rc == FR_OK) & (data_cnt == 0))
  {
    return true;
  }
  else
  {
    return false;
  }
}
#else
bool File::forward_data(void)
{
  FRESULT rc = FR_OK;
  return rc;
}
#endif
bool File::header_need_init(void)
{
  return !header_initialized;
}

F_RET File::create(File_header *f_header)
{
  if(pvd_get_power_flag()) {
    return F_ERROR;
  } 
      
  F_RET ret = F_ERROR;
  unsigned int bytes_write = 0;

  if (header_initialized)
  {
    return ret;
  }
  
  // calculate header crc
  f_header->crc = crc->calc((unsigned char*)f_header, sizeof(File_header) - sizeof(unsigned short));
  
  if (f_open(&fp, file_name, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
  {
      
    logger_infor_save_more(LOGGER_OPERATE,LOGGER_MORE_FILE_CREATE,0,file_name,(char *)__FILE__,__LINE__);
      
    memcpy(&header, f_header, sizeof(File_header));
    if ((f_write(&fp, (unsigned char *)(&header), sizeof(File_header), &bytes_write) == FR_OK) && (bytes_write == sizeof(File_header)))
    {
      file_status = FS_OK;
      ret = F_OK;
    }

    f_close(&fp);
  }

  return ret;
}

F_RET File::remove(void)
{

  if (f_unlink(file_name) == FR_OK)
  {
    file_status = FS_NOT_EXIST;
    header_initialized = false;
    return F_OK;
  }
  else
  {
    return F_ERROR;
  }
}

F_RET File::write(unsigned char *data, unsigned int data_len)
{
    
  if(pvd_get_power_flag()) {
    return F_ERROR;
  } 
    
  FRESULT ret = FR_OK;
  unsigned int bytes_write = 0;
  unsigned int w_len = data_len;

  // arguments check
  if ((data == NULL) || ((header.data_fixed_len != 0) && (data_len == 0)))
  {
    return F_ERROR;
  }

  // open file
  if (f_open(&fp, file_name, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND) != FR_OK)
  {
      logger_infor_save_more(LOGGER_OPERATE,LOGGER_MOER_FILE_WIRTE_OPEN_FAILED,0,file_name,(char *)__FILE__,__LINE__);
      return F_ERROR;
  }

  // check if file full
  if ((header.data_overwrite != true) && (header.data_cnt >= header.data_cnt_max))
  {
    f_close(&fp);
    return F_ERROR;
  }

  // move file pointer
  if (header.data_fixed_len != 0)
  {
    w_len = header.data_fixed_len;

    if (f_lseek(&fp, header.data_idx * header.data_fixed_len + sizeof(File_header)) != FR_OK)
    {
      f_close(&fp);
      return F_ERROR;
    }
  }

  // write data
  ret = f_write(&fp, data, w_len, &bytes_write);
  if ((ret != FR_OK) || (w_len != bytes_write))
  {
    f_close(&fp);
    return F_ERROR;
  }

  // update header
  inc_data_record();

  // move file pointer to start
  ret = f_lseek(&fp, 0);
  if (ret != FR_OK)
  {
    f_close(&fp);
    rollback_data_record();
    return F_ERROR;
  }

  // write updated header back to file
  ret = f_write(&fp, (char *)(&header), sizeof(header), &bytes_write);
  if ((ret != FR_OK) || (sizeof(header) != bytes_write))
  {
    f_close(&fp);
    rollback_data_record();
    return F_ERROR;
  }

  if (f_close(&fp) == FR_OK)
  {
    return F_OK;
  }
  else
  {
    rollback_data_record();
    return F_ERROR;
  }
}

void File::inc_data_record(void)
{
  header.data_idx++;

  // increase data count
  if (header.data_cnt < header.data_cnt_max)
  {
    header.data_cnt++;
  }

  // increase data index
  if (header.data_idx >= header.data_cnt_max)
  {
    header.data_idx = 0;
  }
  
  header.crc = crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));
  
}

void File::rollback_data_record(void)
{
  // decrease data index
  if (header.data_idx != 0)
  {
    header.data_idx--;
  }

  // decrease data count
  if (header.data_cnt != 0)
  {
    header.data_cnt--;
  }
  
  header.crc = crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));
}
F_RET File::read(unsigned char* data, unsigned int data_len, bool open , bool close, unsigned int from)
{
  FRESULT ret = FR_OK;
  unsigned int bytes_read = 0;
  unsigned int r_len = data_len;

  // arguments check
  if ((data == NULL) || ((header.data_fixed_len != 0) && (data_len == 0)))
  {
    return F_ERROR;
  }

  // open file
  if (open && f_open(&fp, file_name, FA_READ | FA_OPEN_EXISTING) != FR_OK)
  {
    f_close(&fp);
    return F_ERROR;
  }

  // move file pointer
  if (header.data_fixed_len != 0)
  {
    r_len = header.data_fixed_len;

    if (f_lseek(&fp, from * header.data_fixed_len + sizeof(File_header)) != FR_OK)
    {
      f_close(&fp);
      return F_ERROR;
    }
  }
  else
  {
    if (f_lseek(&fp, from + sizeof(File_header)) != FR_OK)
    {
      f_close(&fp);
      return F_ERROR;
    }
  }

  // read data
  ret = f_read(&fp, data, r_len, &bytes_read);
  if ((ret != FR_OK) || (r_len != bytes_read))
  {
    f_close(&fp);
    return F_ERROR;
  }
  if(close)
  {
    f_close(&fp);
  }

  return F_OK;

}

F_RET File::read(unsigned char *data, unsigned int data_len, unsigned int from)
{
  FRESULT ret = FR_OK;
  unsigned int bytes_read = 0;
  unsigned int r_len = data_len;

  // arguments check
  if ((data == NULL) || ((header.data_fixed_len != 0) && (data_len == 0)))
  {
    return F_ERROR;
  }

  // open file
  if (f_open(&fp, file_name, FA_READ | FA_OPEN_EXISTING) != FR_OK)
  {
    f_close(&fp);
    return F_ERROR;
  }

  // move file pointer
  if (header.data_fixed_len != 0)
  {
    r_len = header.data_fixed_len;

    if (f_lseek(&fp, from * header.data_fixed_len + sizeof(File_header)) != FR_OK)
    {
      f_close(&fp);
      return F_ERROR;
    }
  }
  else
  {
    if (f_lseek(&fp, from + sizeof(File_header)) != FR_OK)
    {
      f_close(&fp);
      return F_ERROR;
    }
  }

  // read data
  ret = f_read(&fp, data, r_len, &bytes_read);
  if ((ret != FR_OK) || (r_len != bytes_read))
  {
    f_close(&fp);
    return F_ERROR;
  }

  f_close(&fp);

  return F_OK;
}

F_RET File::read_last(unsigned char *data, unsigned int data_len)
{
  unsigned int read_data_idx = 0;

  if (header.data_idx != 0)
  {

    read_data_idx = header.data_idx - 1;
  }
  else if ((header.data_idx == 0) && (header.data_cnt == header.data_cnt_max))
  {
    read_data_idx = header.data_cnt_max - 1;
  }

  return read(data, data_len, read_data_idx);
}

F_RET File::clear(void)
{
  header.data_idx = 0;
  header.data_cnt = 0;
  return write_header(&header, true);
}

F_RET File::clear_from(unsigned int from)
{
  header.data_idx = from;
  header.data_cnt = from;
  return write_header(&header, true);
}

unsigned int File::get_index(void)
{
  return header.data_idx;
}

unsigned int File::get_count(void)
{
  return header.data_cnt;
}

unsigned int File::get_max_count(void)
{
  return header.data_cnt_max;
}

bool File::write_max_count(unsigned int cnt)
{
  if (cnt == 0)
  {
    return false;
  }

  header.data_cnt_max = cnt;
  if (header.data_idx >= header.data_cnt_max)
  {
    header.data_idx = header.data_cnt_max - 1;
  }

  if (header.data_cnt >= header.data_cnt_max)
  {
    header.data_cnt = header.data_cnt_max;
  }
  
  return write_header(&header, true);
}

unsigned int File::get_fixed_data_cnt(void)
{
  return header.data_fixed_len;
}

bool File::write_fixed_count(unsigned int cnt)
{
  header.data_fixed_len = cnt;
  header.data_cnt = 0;
  header.data_idx = 0;
  return write_header(&header, true);
}

unsigned int File::get_free_count(void)
{
  return (header.data_cnt_max - header.data_idx);
}

unsigned int File::get_fixed_data_len(void)
{
  return header.data_fixed_len;
}

F_RET File::read_header(File_header *head, bool open_file)
{
  unsigned int bytes_read = 0;
  F_RET ret = F_OK;

  if (open_file)
  {
    if (f_open(&fp, file_name, FA_READ | FA_OPEN_EXISTING) != FR_OK)
    {
      return F_ERROR;
    }

    if ((f_read(&fp, (char *)head, sizeof(File_header), &bytes_read) != FR_OK) || (bytes_read != sizeof(File_header)))
    {
      ret = F_ERROR;
    }

    f_close(&fp);
  }
  else
  {
    memcpy(head, &header, sizeof(header));
  }

  return ret;
}

F_RET File::write_header(File_header *head, bool open_file)
{
  unsigned int bytes_write;
  F_RET ret = F_OK;
    
    
  if(pvd_get_power_flag()) {
    return F_ERROR;
  } 

  // arguments check
  if (head == NULL)
  {
    return F_ERROR;
  }

  if (open_file)
  {
    if (f_open(&fp, file_name, FA_WRITE | FA_OPEN_EXISTING) != FR_OK)
    {
      return F_ERROR;
    }

    head->crc = crc->calc((unsigned char*)head, sizeof(File_header)-sizeof(head->crc));
    if ((f_write(&fp, (char *)head, sizeof(File_header), &bytes_write) != FR_OK) || (bytes_write != sizeof(File_header)))
    {
      ret = F_ERROR;
    }

    f_close(&fp);
  }
  else
  {
    head->crc = crc->calc((unsigned char*)head, sizeof(File_header)-sizeof(head->crc));
    memcpy(&header, head, sizeof(header));
  }

  return ret;
}

bool File::get_overwrite(void )
{
  return header.data_overwrite;
}

bool File::set_overwrite(bool flag)
{
  header.data_overwrite = flag;
  return (write_header(&header, true) == F_OK);
}


File::~File()
{
}
