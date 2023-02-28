/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      file operation class
*
* 版本:
* V1.2 2019-05-10 重新写入固定长度后，清空文件内容
* V1.1 2019-05-06 将文件头读写设置访问级别为protected
* V1.0 2019-04-29 初始版本程序编写 
***********************************************************/
#ifndef _FILE_H_
#define _FILE_H_

#include <stdbool.h>
#include "ff.h"
#include "modules_def.h"
#include "..\crc\crc16_if.h"

typedef struct _tag_file_header_ 
{
  unsigned int data_idx;
  unsigned int data_cnt;  
  unsigned int data_fixed_len;
  unsigned int data_cnt_max;
  bool data_overwrite;
  unsigned short crc;
}File_header;

typedef enum _tag_f_ret_ 
{
  F_OK =  0,
  F_ERROR =  1
}F_RET;

typedef enum _tag_f_status_ 
{
  FS_OK =  0,
  FS_NOT_EXIST
}F_STATUS;

typedef UINT (*forwrad_callback) (const BYTE* data, UINT data_len);


class File 
{
  public:
    File(FIL &fil, const char * file_str);
    F_RET create(File_header* f_header);
    bool header_need_init(void);
    F_RET remove(void );
    F_RET write(unsigned char *data, unsigned int data_len);

    F_RET read(unsigned char* data, unsigned int data_len, unsigned int from = 0);
    F_RET read(unsigned char* data, unsigned int data_len, bool open , bool close, unsigned int from = 0);
    F_RET read_last(unsigned char* data, unsigned int data_len);
    F_RET clear(void );
    F_RET clear_from(unsigned int from = 0);  
    unsigned int get_count(void );
    unsigned int get_index(void);
    unsigned int get_max_count(void );
    bool write_max_count(unsigned int cnt);
    unsigned int get_fixed_data_cnt(void);
    bool write_fixed_count(unsigned int cnt);
    unsigned int get_free_count(void );
    unsigned int get_fixed_data_len(void );
    bool get_overwrite(void );
    bool set_overwrite(bool flag = true);
    ~File();
    F_RET read_header(File_header* head, bool open_file = false);
    void set_forward_callback(forwrad_callback func);
    bool forward_data(void);
    Crc16_if* crc;
    
protected:
    F_RET write_header(File_header* head, bool open_file = false);
    

  private:
    bool exist(void );
    void inc_data_record(void);
    void rollback_data_record(void);
    char * file_name;
    F_STATUS file_status;
    File_header header;
    FIL& fp;
    forwrad_callback f_callback;
    bool header_initialized;
};
#endif //_FILE_H_
