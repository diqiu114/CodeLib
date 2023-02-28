#include "hist_data_store.h"
#include "crc32.h"
#include <string.h>

Hist_data_store::Hist_data_store(File *file)
{
  this->file = file;
  rtc = NULL;
  cur_cnt = 0;
  interval_cnt = 1;
#if (USE_FREE_RTOS)
  queue = NULL;
  msg = QM_CNT_MAX;
  timeout = 0;
#endif
}

void Hist_data_store::set_rtc_handle(Rtc_ops *handle)
{
  rtc = handle;
}

bool Hist_data_store::store_data(void)
{
  if (rtc != NULL)
  {
    hist_data_buff.ts = rtc->get_ts();
  }
  
  History_data_t temp_logger = {0};
  
  memcpy((void *)&temp_logger,(void *)(&hist_data_buff),sizeof(History_data_t));
  temp_logger.crc32 = CRC_Get32(((const uint8_t *)(&temp_logger)) + 4,sizeof(History_data_t) - 4);

  if (file->write((unsigned char *)(&temp_logger), sizeof(History_data_t)) == FR_OK)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// opt = 1 means immediately
void Hist_data_store::update(Batt_data_t *data, unsigned char opt)
{
  if (data == NULL)
  {
    return;
  }

  cur_cnt++;

  if ((cur_cnt == interval_cnt) || (opt == 1))
  {
    memcpy(&hist_data_buff.batt_data, data, sizeof(Batt_data_t));
#if (USE_FREE_RTOS)
    if (queue != NULL)
    {
      xQueueSend(queue, &msg, timeout);
    }

#else
    store_data();
#endif

    cur_cnt = 0;
  }
}

#if (USE_FREE_RTOS)
void Hist_data_store::set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  queue = handle;
  msg = _msg;
  timeout = _timeout;
}
#endif

void Hist_data_store::set_store_interval(unsigned int cnt)
{
  interval_cnt = cnt;
}

Hist_data_store::~Hist_data_store()
{
}
