#include "alarm_data_store.h"
#include <string.h>

Alarm_data_store::Alarm_data_store(File *file)
{
  this->file = file;
  rtc = NULL;
  cur_cnt = 0;
#if (USE_FREE_RTOS)
  queue = NULL;
  msg = QM_CNT_MAX;
  timeout = 0;
#endif
}

void Alarm_data_store::set_rtc_handle(Rtc_ops *handle)
{
  rtc = handle;
}

bool Alarm_data_store::store_data(void)
{
  if (rtc != NULL)
  {
    alarm_data_buff.ts = rtc->get_ts();
  }

  //  return true;
  if (file->write((unsigned char *)(&alarm_data_buff), sizeof(alarm_data_buff)) == FR_OK)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Alarm_data_store::update(Alarm_data_t *data, unsigned char opt)
{
  if (data == NULL)
  {
    return;
  }
  memcpy(&alarm_data_buff, data, sizeof(Alarm_data_t));
#if (USE_FREE_RTOS)
  if (queue != NULL)
  {
    xQueueSend(queue, &msg, timeout);
  }
#else
  store_data();
#endif
}

#if (USE_FREE_RTOS)
void Alarm_data_store::set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  queue = handle;
  msg = _msg;
  timeout = _timeout;
}
#endif

Alarm_data_store::~Alarm_data_store()
{
}
