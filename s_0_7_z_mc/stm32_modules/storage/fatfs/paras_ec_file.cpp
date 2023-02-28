#include "paras_ec_file.h"
#include <string.h>

/**
 * @brief Construct a new Paras_ec_file::Paras_ec_file object
 * 
 * @param fil file system file struct
 * @param file_name file name pointer
 * @param data_len fixed data length
 */
Paras_ec_file::Paras_ec_file(FIL &fil, const char *file_name, unsigned int data_len)
{
  char *bak_file_name = new char[strlen(file_name) + strlen(PARAS_BAK_FILE_SUFFIX)];
  strcpy(bak_file_name, file_name);
  strcat(bak_file_name, PARAS_BAK_FILE_SUFFIX);

  main_file = new Paras_file(fil, file_name, data_len);
  backup_file = new Paras_file(fil, bak_file_name, data_len);

  buff_len = data_len + sizeof(unsigned short);
  buff = new unsigned char[buff_len];
  memset(buff, 0, buff_len);
}

Paras_ec_file::~Paras_ec_file()
{
  if (main_file != NULL)
  {
    delete main_file;
    main_file = NULL;
  }

  if (backup_file != NULL)
  {
    delete backup_file;
    backup_file = NULL;
  }

  if (buff != NULL)
  {
    delete[] buff;
    buff = NULL;
  }
}

/**
 * @brief read data from file
 * 
 * @param data return data pointer
 * @return true read ok
 * @return false read fail
 */
bool Paras_ec_file::read(void *data)
{
  bool ret = false;
  ret = main_file->read(buff);
  if( !ret )
  {
    ret = backup_file->read(buff);
    if (ret)
    {
      main_file->clear();
      main_file->write(buff);
    }
  }

  if(ret)
  {
    memcpy(data, buff, buff_len);
  }

  return ret;
}

/**
 * @brief write data to file
 * 
 * @param data data to be write
 * @return true write ok
 * @return false write failed
 */
bool Paras_ec_file::write(void *data)
{
  bool ret1 = false;
  bool ret2 = false;
  
  ret1 = main_file->write(data);
  ret2 = backup_file->write(data);
  
  return (ret1 || ret2);
}

/**
 * @brief get data count, usually 1
 * 
 * @return unsigned int data count in file
 */
unsigned int Paras_ec_file::get_count(void)
{
  if(main_file->get_count() > 0)
  {
    return main_file->get_count();
  }
  else
  {
    return backup_file->get_count();
  }
}

/**
 * @brief get parameter data length
 * 
 * @return unsigned int data length
 */
unsigned int Paras_ec_file::read_para_len(void)
{
  if ( main_file->get_fixed_data_len() > 0 )
  {
    return main_file->get_fixed_data_len();
  }
  else
  {
    return backup_file->get_fixed_data_len();
  }
}

/**
 * @brief clear header 
 * 
 * @return true 
 * @return false 
 */
bool Paras_ec_file::clear(void)
{
  return (main_file->clear() && backup_file->clear());
}

bool Paras_ec_file::remove(void)
{
  return (main_file->remove() && backup_file->remove());
}
