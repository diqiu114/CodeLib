#include "adc_app.h"

Adc_app::Adc_app(Adc_acq *_adc_acq)
{
  channel_cnt = _adc_acq->para->ch_cnt;
  adc_acq = _adc_acq;
  eng_data = new float[sizeof(float) * _adc_acq->para->ch_cnt];
}

Adc_app::~Adc_app()
{
  if (eng_data != NULL)
  {
    delete[] eng_data;
    eng_data = NULL;
  }

  if (rate.size() > 0)
  {
    for (int i = 0; i < rate.size(); i++)
    {
      delete rate.at(i);
    }

    rate.clear();
  }

  if (calib.size() > 0)
  {
    for (int i = 0; i < calib.size(); i++)
    {
      delete calib.at(i);
    }

    calib.clear();
  }
}

float Adc_app::get_eng_data(unsigned int idx)
{
  if (idx > channel_cnt)
  {
    return 0;
  }

  float *adc_data = const_cast<float *>(adc_acq->adc_get_all());
  float ret = adc_data[idx];

  if (idx < rate.size())
  {
    ret = rate.at(idx)->convert(ret);
  }

  if (idx < calib.size())
  {
    ret = calib.at(idx)->convert(ret);
  }

  return ret;
}

float *Adc_app::get_eng_data(void)
{
  eng_data = const_cast<float *>(adc_acq->adc_get_all());

  unsigned char rate_cnt = rate.size() <= channel_cnt ? rate.size() : channel_cnt;

  for (int i = 0; i < rate_cnt; i++)
  {
    eng_data[i] = rate.at(i)->convert(eng_data[i]);
  }

  unsigned char calib_cnt = calib.size() <= channel_cnt ? calib.size() : channel_cnt;

  for (int i = 0; i < calib_cnt; i++)
  {
    eng_data[i] = calib.at(i)->convert(eng_data[i]);
  }

  return eng_data;
}

bool Adc_app::set_calib(vector<Data_convert_if *> &_calib)
{
  calib = _calib;
  return true;
}

bool Adc_app::set_rate(vector<Data_convert_if *> &_rate)
{
  rate = _rate;
  return true;
}

bool Adc_app::modify_calib(Data_convert_if *_calib, unsigned char idx)
{
  bool ret = false;

  if (idx < calib.size())
  {
    calib.at(idx) = _calib;
    ret = true;
  }

  return ret;
}

bool Adc_app::modify_rate(Data_convert_if *_rate, unsigned char idx)
{
  bool ret = false;

  if (idx < rate.size())
  {
    // free memory before reassign
//    delete rate.at(idx);
//    rate.at(idx) = NULL;

    rate.at(idx) = _rate;

    ret = true;
  }

  return ret;
}

void Adc_app::stop_acq(void)
{
  adc_acq->stop();
}
