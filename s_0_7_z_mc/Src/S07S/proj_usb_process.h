/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      USB process
*
* 版本:
* V1.0 2019-06-20 初始程序编写 
***********************************************************/

#ifndef _PROJ_USB_PROCESS_H_
#define _PROJ_USB_PROCESS_H_
#include <stdbool.h>
#include "usb_comm.h"
#include "protocol.h"
#include "file.h"
#include "defines.h"
#include "modbus_master.h"
#include "proj_paras.h"
typedef enum _usb_comm_cmd_
{
  USB_READ_TIME = 0x10,
  USB_READ_SYS_PARA,
  USB_READ_DEV_PARA,
  USB_READ_USER_PARA,
  USB_READ_REAL_DATA,
  USB_READ_HIST_DATA_HEADER,
  USB_READ_HIST_DATA,
  USB_READ_ALARM_DATA_HEADER,
  USB_READ_ALARM_DATA,
  USB_READ_FLASH_SIZE,
  USB_CELL_COMM,
  USB_READ_MC_REAL_DATA,

  USB_SET_TIME = 0x80,
  USB_WRITE_SYS_PARA,
  USB_WRITE_SOC,
  USB_CLEAR_HIST_DATA,
  USB_PROGRAM_UPDATE,
  USB_RESET_MC,
  USB_FORMAT_FLASH,

  USB_WRITE_DEV_PARA,
  USB_WRITE_USER_PARA,
  USB_WRITE_SOC_INIT_FLAG,
  USB_READ_CELL_PARA,
  USB_WRITE_SOH
} Usb_cmd;

#define USB_COMM_BUFF_SIZE (700)
#define USB_COMM_CMD_LEN (1)

typedef enum _tag_usb_status_
{
  USB_FAIL = 0,
  USB_OK,
} Usb_status;

class Usb_process : public Usb_comm
{
public:
  Usb_process(USBD_HandleTypeDef *usb_handle, usb_idle_callback callback = NULL);
  virtual void process(void);
  virtual ~Usb_process();

private:
  bool cell_comm(unsigned char *data, unsigned int data_len);
  void modbus_comm_pross(short cmd);
  void reply_date_time(void);
  void reply_data(Usb_cmd cmd, void *data, unsigned int len);
  void reply_flash_size(void);
  bool reply_file_header(File *file);
  bool reply_file_data(File *file);
  void write_soc(void* data);
  void reply_status(Usb_cmd cmd, Usb_status status);
  void set_date_time(unsigned char *data);

  Protocol *usb_prot;
  Usb_cmd cmd;
  unsigned char uc_rev_buff[USB_COMM_BUFF_SIZE];
  unsigned char *uc_send_buff;
};

#endif // _PROJ_USB_PROCESS_H_
