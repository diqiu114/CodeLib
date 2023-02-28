#include "trdp_app.h"

Trdp_app::Trdp_app()
{
  rev_buff = new unsigned char[TRDP_REV_BUFF_SIZE];
  send_buff = new unsigned char[TRDP_SEND_BUFF_SIZE];
  if (rev_buff != NULL)
  {
    memset(rev_buff, 0, TRDP_REV_BUFF_SIZE);
  }

  if (send_buff != NULL)
  {
    memset(send_buff, 0, TRDP_SEND_BUFF_SIZE);
  }
}

Trdp_app::Trdp_app(Trdp_module *module, Trdp_data *data)
{
  trdp = module;
  trdp_data = data;
  rev_buff = new unsigned char[TRDP_REV_BUFF_SIZE];
  send_buff = new unsigned char[TRDP_SEND_BUFF_SIZE];
  if (rev_buff != NULL)
  {
    memset(rev_buff, 0, TRDP_REV_BUFF_SIZE);
  }

  if (send_buff != NULL)
  {
    memset(send_buff, 0, TRDP_SEND_BUFF_SIZE);
  }
}
void Trdp_app::app_send_pd(void)
{
  unsigned int data_cnt = trdp_data->get_update_buff(send_buff);
  trdp->send_pd(0, send_buff, data_cnt);
  trdp->send_pd(1, send_buff, data_cnt);

}
void Trdp_app::process(void)
{
  unsigned int rev_cnt = trdp->rev_pd(rev_buff);
  if (rev_cnt < TRDP_CRC_CALC_BYTES)
  {
    return;
  }

  // crc check
//  unsigned char crc = crc8(rev_buff + 1, TRDP_CRC_CALC_BYTES);
//  if (crc != rev_buff[TRDP_CRC_IDX])
//  {
//    return;
//  }
  
  // reply data
//  unsigned char eth_num = rev_buff[0];
//  unsigned int data_cnt = trdp_data->get_update_buff(send_buff);
//  trdp->send_pd(eth_num, send_buff, data_cnt);
  
  // date time set
  if ((rev_buff[TRDP_TIME_SET_IDX] & (1 << TRDP_TIME_SET_BIT)) == 1)
  {
    set_time_delay++;
  }
  else
  {
    set_time_delay = 0;
  }

  if ((set_time_delay >= TRDP_SET_TIME_DELAY_MAX) && (rtc != NULL))
  {
    set_time_delay = 0;
    unsigned char start_idx = TRDP_TIME_START_IDX;
    date_time.date.year = rev_buff[start_idx++];
    date_time.date.month = rev_buff[start_idx++];
    date_time.date.date = rev_buff[start_idx++];
    date_time.time.hours = rev_buff[start_idx++];
    date_time.time.minutes = rev_buff[start_idx++];
    date_time.time.seconds = rev_buff[start_idx++];
    rtc->set_datetime(&date_time);
  }

  // vital check
}

void Trdp_app::set_rtc_handle(Rtc_ops *rtc)
{
  this->rtc = rtc;
}

unsigned char Trdp_app::crc8(unsigned char *buff, int buff_len)
{
  if ((buff == NULL) || (buff_len <= 0))
  {
    return 0;
  }

  unsigned char crc = 0, inbyte, i, mix;
  unsigned char *p = buff;
  while (buff_len--)
  {
    inbyte = *p++;
    for (i = 8; i; i--)
    {
      mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix)
      {
        crc ^= 0x8C;
      }
      inbyte >>= 1;
    }
  }

  // Return calculated CRC
  return crc;
}

Trdp_app::~Trdp_app()
{
}
