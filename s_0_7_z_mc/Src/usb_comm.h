/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      USB VCP与上位机通讯类
*
* 版本:
* V1.0 2019-05-09 初始程序编写 
***********************************************************/

#ifndef _USB_COMM_H_
#define _USB_COMM_H_
#include <stdbool.h>
#include "usb_tranceiver.h"

class Usb_comm : public Usb_tranceiver
{
public:
  Usb_comm(USBD_HandleTypeDef *usb_handle, unsigned int buff_size,unsigned int send_buff_size, usb_idle_callback callback=NULL);
  virtual void process(void);
  virtual ~Usb_comm();
};

#endif // _USB_COMM_H_
