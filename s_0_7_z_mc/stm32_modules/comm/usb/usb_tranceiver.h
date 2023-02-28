/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      USB CDC(VCP)通讯类
*
* 版本:
* V1.4 2019-06-14 将connected函数修改为public
* V1.3 2019-06-11 收到数据后，先存入rev_buffer，然后切换buffer，保证数据完整性
* V1.2 2019-05-16 增加收到数据后callback函数 
* V1.1 2019-05-14 增加查询USB发送状态函数 
* V1.0 2018-12-02 初始版本程序编写 
***********************************************************
                          ##### 如何使用 #####
==============================================================================
1.使用前将要使用的USB配置为USB_CDC设备
2.实例化对象,将要实例的USB handle及接收buffer的大小(字节)传入类
3.将usbd_cdc_if.c改为usbd_cdc_if.cpp,在对应的USB接收函数中添加数据接收处理,如下所示:

static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  if( Usb_comm != NULL )
  {
    Usb_comm->rev_data_handle(Buf, *Len);
  }
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
  return (USBD_OK);
}

4.调用read_all()/readout()读取已接收到的数据
5.调用send()发送数据
***********************************************************/

#ifndef _USB_TRANCERIVER_H_
#define _USB_TRANCERIVER_H_

#include <stdbool.h>
#include "comm\Double_buffered_comm.h"
#include "usb_device.h"
#include "usbd_cdc.h"

typedef enum _usb_receive_mode_
{
  // 固定 64字节
  USB_REV_MODE_FIXED_LEN,
  USB_REV_MODE_VARIABLE_LEN
}Usb_rev_mode;

#define USB_IDLE_TIMEOUT_MS (3)
#define USB_SEND_TIMEOUT_MS (100)

typedef void (*usb_idle_callback)(void);

class Usb_tranceiver : public Double_buffered_comm
{
public:
  Usb_tranceiver(USBD_HandleTypeDef *usb_handle,
                 unsigned int rev_buff_size,
                 unsigned int send_buff_size,
                 usb_idle_callback callback = NULL,
                 Usb_rev_mode _rev_mode = USB_REV_MODE_VARIABLE_LEN,
                 int _send_timeout = USB_SEND_TIMEOUT_MS);

  bool tx_ready(void);

  virtual bool send(unsigned char *data, unsigned int data_len);
  virtual unsigned int read(unsigned char *data, unsigned int data_len);
  virtual unsigned int read_all(unsigned char *data);

  virtual bool rev_data_handle(unsigned char *data = NULL, unsigned int data_cnt = 0);
  virtual void idle_handle(void);
  void set_send_timeout(int timeout);
  bool connected(void);
  bool forward(unsigned char data);
  bool get_rev_data_flag(void);
  void clear_rev_data_flag(bool flg = true);
  virtual ~Usb_tranceiver();

private:
  Circular_buffer *send_buff;
  USBD_HandleTypeDef *husb;
  USBD_CDC_HandleTypeDef *hcdc;
  usb_idle_callback usb_callback;
  bool send_process(void);
  bool send_process(unsigned int wait_time);
  unsigned char *send_tmp_buff;
  unsigned short send_buff_len;
  bool received_data_flag;
  Usb_rev_mode rev_mode;
  int send_timeout;
};

#endif // _USB_TRANCERIVER_H_
