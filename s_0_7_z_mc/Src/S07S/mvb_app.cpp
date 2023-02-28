#include <stdlib.h>
#include "mvb_app.h"
#include "string.h"
#include "paras.h"

#define  MAX_DEST_CNT      (8)
#define  RECV_DATA_PERIOD  (2)

Mvb_app::Mvb_app(Mvb_module *_mvb, unsigned char train_inx ,unsigned int rec_data_len)
{
  mvb = _mvb;
  Train_index = train_inx;
  send_frame = NULL;
  memset(&rec_frame, 0, sizeof(rec_frame));
  rec_frame.data = new unsigned char[rec_data_len];
  memset(rec_frame.data, 0, rec_data_len);
  pre_vital = 0;
  rtc = NULL;
  comm_err = false;
  comm_err_cnt = 0;
}

void Mvb_app::set_rtc_handle(Rtc_ops *handle)
{
  rtc = handle;
}

bool Mvb_app::send_msg(unsigned char *data, unsigned int data_len)
{
    bool ret = true;
    if (data == NULL || data_len == 0 || send_frame == NULL)
    {
        return false;
    }
    uint16_t data_index = 0;
    uint8_t  temp_length;
    for(unsigned char i = 0; i < MAX_DEST_CNT; i++)
    {
        if(i < 1)
        {
            send_frame->sc = 0XEE;
            send_frame->inc_offset = 0;
        }
        else
        {
            send_frame->sc = 0X81;
            //send_frame->sc = 0XEE;
        }
        
        send_frame->dest_addr = (Dev_paras.mvb[Train_index].dest_port[i].addr[0] << 8 ) | \
                                (Dev_paras.mvb[Train_index].dest_port[i].addr[1] << 0);
        send_frame->data = data + data_index;
        
        switch(Dev_paras.mvb[Train_index].dest_port[i].data_len) {
            case MVB_MODULE_DATA_LEN_2BYTES:
                temp_length = 2;
                break;
            case MVB_MODULE_DATA_LEN_4BYTES:
                temp_length = 4;
                break;
            case MVB_MODULE_DATA_LEN_8BYTES:
                temp_length = 8;
                break;
            case MVB_MODULE_DATA_LEN_16BYTES:
                temp_length = 16;
                break;
            case MVB_MODULE_DATA_LEN_32BYTES:
                temp_length = 32;
                break;
            default:
                return false;

        }

        
        send_frame->data_cnt = temp_length;

        ret &= mvb->send_data(send_frame);
        
        data_index += temp_length;
        
        if(data_index >= data_len) {
            break;
        }
        
        osDelay(1000);
    }

    return  ret;
}
#if S07Y
bool Mvb_app::handle_rec_msg(unsigned short dest_addr) {
    if (mvb->receive(dest_addr, RECV_DATA_PERIOD, MVB_RECV_ON, &rec_frame))
    {
        static uint16_t last_heart = 0;
        static uint32_t last_tick = 0;
        
        int diff_tick = osKernelSysTick() - last_tick;
        if(abs(diff_tick) < 60000) {
            return true;
        } 
        
        uint16_t current_heart = (uint16_t)rec_frame.data[0] << 8 | rec_frame.data[1];
        if(last_heart == current_heart) {
            return false;
        }
        
        if(last_heart != 0) {
            last_tick = osKernelSysTick();
            
            if (dest_addr == DATE_TIME_ADDR)
            {
                uint8_t year = rec_frame.data[6];
                uint8_t month = rec_frame.data[7];
                uint8_t day = rec_frame.data[8];
                uint8_t hour = rec_frame.data[9];
                uint8_t min = rec_frame.data[10];
                uint8_t sec = rec_frame.data[11];

                if (rtc != NULL)
                {
                    Rtc_t datetime;
                   
                    datetime.date.year = year;
                    datetime.date.month = month;
                    datetime.date.date = day;
                    datetime.time.hours = hour;
                    datetime.time.minutes = min;
                    datetime.time.seconds = sec;
                    
                    uint32_t ts1 = rtc->get_ts_with8zone(&datetime);
                    uint32_t ts2 = rtc->get_ts();
                    int diff = ts1 - ts2;
                    if(abs(diff) > 60){
                        rtc->set_datetime(ts1);
                    } 
                }
            }
        }
        
        last_heart = current_heart;
        
        
        return true;
    }
    else
    {
        return false;
    }
}
#else
bool Mvb_app::handle_rec_msg(unsigned short dest_addr)
{ 
  if (mvb->receive(dest_addr, RECV_DATA_PERIOD, MVB_RECV_ON, &rec_frame))
  {
    if (dest_addr == DATE_TIME_ADDR)
    {
      unsigned short vital = rec_frame.data[0] << 8 | rec_frame.data[1];
      if (pre_vital == vital)
      {
        comm_err_cnt++;
        if (comm_err_cnt > VITAL_ERR_DELAY)
        {
          comm_err = true;
        }
      }
      else
      {
        comm_err_cnt = 0;
        comm_err = false;
        pre_vital = vital;
      }
      if(comm_err)
      {
        return false;
      }
      // set rtc if needed
      if ((rec_frame.data[TIME_SET_FLAG_IDX] & TIME_SET_AVALIBLE) == TIME_SET_AVALIBLE)
      {
        if (rtc != NULL)
        {
          Rtc_t datetime;
          unsigned char *date_time = &rec_frame.data[9];
          datetime.date.year = *date_time++;
          datetime.date.month = *date_time++;
          datetime.date.date = *date_time++;
          datetime.time.hours = *date_time++;
          datetime.time.minutes = *date_time++;
          datetime.time.seconds = *date_time++;

          rtc->set_datetime(&datetime);
        }
      }
      if((rec_frame.data[TIME_TRAIN_NUM_FLAG_IDX] & TRAIN_NUM_SET_AVALIBLE) == TRAIN_NUM_SET_AVALIBLE)
      {
//        unsigned char train_num = (rec_frame.data[8] + 1) / 2;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}
#endif




bool Mvb_app::comm_error(void)
{
  return comm_err;
}

void Mvb_app::set_send_frame(Mvb_data *frame)
{
  send_frame = frame;
}

Mvb_app::~Mvb_app()
{
}
