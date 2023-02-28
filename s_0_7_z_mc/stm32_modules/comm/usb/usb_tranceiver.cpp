#include "usb_tranceiver.h"
#include "usbd_cdc_if.h"
#include "modules_def.h"

Usb_tranceiver::Usb_tranceiver(USBD_HandleTypeDef *usb_handle,
                               unsigned int rev_buff_size,
                               unsigned int send_buff_size,
                               usb_idle_callback callback,
                               Usb_rev_mode _rev_mode,
                               int _send_timeout)
    : Double_buffered_comm(rev_buff_size)
{
  husb = usb_handle;
  hcdc = (USBD_CDC_HandleTypeDef *)husb->pClassData;

  data_buffer->buffer_reset();

  if (callback)
  {
    usb_callback = callback;
  }

  send_buff = new Circular_buffer(send_buff_size);
  send_tmp_buff = new unsigned char[send_buff_size];
  send_buff_len = send_buff_size;
  received_data_flag = false;
  rev_mode = _rev_mode;
  send_timeout = _send_timeout;

}

bool Usb_tranceiver::send(unsigned char *data, unsigned int len)
{
  unsigned char send_times = 1;
  unsigned short send_len = len;
  unsigned short max_send_len = send_buff_len - 1;
  bool ret = true;
  if(len > max_send_len)
  {
    send_times = len % max_send_len == 0 ? len / max_send_len : len / max_send_len + 1;
    send_len = max_send_len;
  }
  for(int times = 0; times < send_times; times++)
  {
    if(len % max_send_len != 0 && times == send_times - 1)
    {
      send_len = len % max_send_len;
    }
    if (send_buff->write(data + times * max_send_len, send_len))
    {
      // Process
      ret = ret && send_process(500);
      send_buff->reset();
    }
    else
    {
      ret = false;
    }
  }
  return ret;
}

bool Usb_tranceiver::forward(unsigned char data)
{
  send_process();

  if (send_buff->write(&data, 1))
  {
    // Process
    return send_process();
  }

  return false;
}

bool Usb_tranceiver::send_process(unsigned int wait_time)
{
  unsigned int wait_tims = wait_time;
  unsigned int data_len = send_buff->read(send_tmp_buff, send_buff_len);
  while(wait_tims--)
  {
    hcdc = (USBD_CDC_HandleTypeDef *)husb->pClassData;
    DELAY_MS(1);
    if (!hcdc->TxState)
    {
      // Check if read anything
      if (data_len > 0)
      {
        USBD_CDC_SetTxBuffer(husb, send_tmp_buff, data_len);
        if (USBD_CDC_TransmitPacket(husb) == USBD_OK)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    }
  }
  return false;
}

bool Usb_tranceiver::send_process(void)
{
  bool ret = false;
  hcdc = (USBD_CDC_HandleTypeDef *)husb->pClassData;

  if (!hcdc->TxState)
  {
    unsigned int data_len = send_buff->read(send_tmp_buff, send_buff_len);

    // Check if read anything
    if (data_len > 0)
    {
      USBD_CDC_SetTxBuffer(husb, send_tmp_buff, data_len);
      if (USBD_CDC_TransmitPacket(husb) == USBD_OK)
      {
        ret = true;
      }
    }
  }

  return ret;
}

void Usb_tranceiver::set_send_timeout(int timeout)
{
  send_timeout = timeout;
}

bool Usb_tranceiver::tx_ready(void)
{
  if (hcdc->TxState == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Usb_tranceiver::clear_rev_data_flag(bool flg)
{
  received_data_flag = !flg;
}

bool Usb_tranceiver::get_rev_data_flag(void)
{
  return received_data_flag;
}

bool Usb_tranceiver::rev_data_handle(unsigned char *data, unsigned int data_cnt)
{
  if ((data == NULL) || (data_cnt == 0))
  {
    return false;
  }
  if (rev_mode == USB_REV_MODE_FIXED_LEN)
  {
    data_buffer->write(data, data_cnt);
    data_buffer->buffer_switch();

    if (usb_callback)
    {
      usb_callback();
    }
  }
  else
  {
    // buffer已经满了,切换buffer
    if (data_buffer->write(data, data_cnt) == 0)
    {
      idle_handle();
    }

    received_data_flag = true;
  }

  return true;
}

void Usb_tranceiver::idle_handle(void)
{
  data_buffer->buffer_switch();
  if (usb_callback)
  {
    usb_callback();
  }
}

bool Usb_tranceiver::connected(void)
{
  if (husb->dev_state == USBD_STATE_CONFIGURED)
  {
    return true;
  }
  else
  {
    return false;
  }
}

unsigned int Usb_tranceiver::read(unsigned char *buffer, unsigned int len)
{
  unsigned int read_data_len = len >= data_buffer->buffer_used() ? data_buffer->buffer_used() : len;
  return data_buffer->read_out(buffer, len);
}

unsigned int Usb_tranceiver::read_all(unsigned char *buffer)
{
  return data_buffer->read_all(buffer);
}

Usb_tranceiver::~Usb_tranceiver()
{
}
