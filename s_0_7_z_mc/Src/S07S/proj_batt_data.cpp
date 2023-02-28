#include "proj_batt_data.h"
#include <string.h>
#include "paras.h"

Proj_batt_data::Proj_batt_data(void) : Batt_data()
{
}

void Proj_batt_data::set_data(Batt_data_t *data, bool update)
{
  batt_data = data;

  if (state != NULL)
  {
    batt_data->state = state->get_state(batt_data->total_data.total_cur[0]);
  }
#if USE_MC_TEMP
  batt_data->total_data.amb_temp = avg_temp(batt_data, COUNT_OF_TEMP);
#else
  batt_data->total_data.amb_temp = avg_temp(batt_data, CELL_CNT);
#endif
  if (cap != NULL)
  {
    batt_data->soc = cap->get_cap_rate();  
  }

  if( update )
  {
    notify_observers();
  }
  
}


bool Proj_batt_data::is_zero(Cell_data_t &cell_data, unsigned int cnt)
{
  unsigned int sum = 0;
  for(int i = 0; i < cnt; i++)
  {
    sum += cell_data.acq_val[i];
  }
  
  return !sum;
}

float Proj_batt_data::avg_temp( Batt_data_t  *data, unsigned int temp_cnt)
{
  float ret = 0;
  unsigned int cnt = 0;
  for (int i = 0; i < temp_cnt; i++)
  {
#if USE_MC_TEMP
    if (data->total_data.temp[i] != 0)
    {
      ret += data->total_data.temp[i] * CELL_TEMP_RATE;
      ++cnt;
    }
#else
    for(int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if(Cell_adc_config_paras[j].acq_type == TYPE_TEMP && Cell_adc_config_paras[j].is_enable == true)
      { 
        if (!is_zero(data->cell_data[i], ACQ_MAX_CNT))
        {
          ret += data->cell_data[i].acq_val[j];
          ++cnt;
        }
      }
    }
#endif
  }
  if (cnt == 0)
  {
    return (ret / CELL_TEMP_RATE);
  }
  else
  {
    return (ret / CELL_TEMP_RATE / cnt);
  }

}

Proj_batt_data::~Proj_batt_data(void)
{
}
