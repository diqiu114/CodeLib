#include "sgp30_app.h"
#include "string.h"

#define ERROR_TIMES 2

Sgp30_app::Sgp30_app()
{
  memset((void*)&gas_raw_data, 0, sizeof(gas_raw_data));
  memset((void*)&iaq_data, 0, sizeof(iaq_data));
  memset((void*)&spg30_verison, 0, sizeof(spg30_verison));
  error_times = 0;
}

Sgp30_app::~Sgp30_app()
{
}

bool Sgp30_app::init(void)
{ 
  short err = SGP30_ERR_UNSUPPORTED_FEATURE_SET;
  unsigned long long serial_id;
  unsigned short found_cnt = 0;
  // 循环等待3秒，检测3次未成功做失败处理，请检测spg30硬件上电是否成功
  while (found_cnt < MAX_CONNECTION_FAILED_TIMES)
  {
    found_cnt++;
    err = sgp30_probe();

    if(err == STATUS_OK)
      break;
    sensirion_sleep_usec(1000000);
  }
  err = sgp30_get_feature_set_version(&spg30_verison.feature_set_version, &spg30_verison.product_type);
  if(err != STATUS_OK)
    return false;
  err = sgp30_get_serial_id(&serial_id);
  if(err != STATUS_OK)
    return false;
  err = sgp30_iaq_init();
  return (err == STATUS_OK);
}

unsigned short Sgp30_app::get_iaq_data(unsigned short *tvoc, unsigned short *co2)
{
  unsigned short err;
  err = sgp30_measure_iaq_blocking_read(&iaq_data.tvoc_ppb, &iaq_data.co2_eq_ppm);
  if (err == STATUS_OK) 
  {
    *tvoc = iaq_data.tvoc_ppb;
    *co2 = iaq_data.co2_eq_ppm;
    error_times = 0;
  }
  else
  {
    if (error_times <= ERROR_TIMES)
    {
      error_times++;
    }
    *tvoc = TVOC_FIXED_VALUE;
    *co2 = CO2_FIXED_VALUE;
  }
  return err;
}  

bool Sgp30_app::is_error()
{
  if(error_times > ERROR_TIMES)
  {
    init();
    return true;
  }
  return false;
}


unsigned short Sgp30_app::get_gas_raw_data(unsigned short *ethanol_signal, unsigned short *h2_signal)
{
  unsigned short err;
  
  err = sgp30_measure_raw_blocking_read(&gas_raw_data.ethanol_raw_signal, &gas_raw_data.h2_raw_signal);
  if (err == STATUS_OK) 
  {
    *ethanol_signal = gas_raw_data.ethanol_raw_signal;
    *h2_signal = gas_raw_data.h2_raw_signal;
  }
  else
  {
    *ethanol_signal = 0;
    *h2_signal = 0;
  }
  return err;
}
unsigned long long get_spg30_serial_id()
{
  unsigned short err;
  unsigned long long serial_id;
  err = sgp30_get_serial_id(&serial_id);
  if (err == STATUS_OK)
  {
    return serial_id;
  }
  else
  {
    return 0;
  }
}
unsigned short Sgp30_app::get_iaq_baseline(unsigned int *baseline_data)
{
  unsigned short err;
  err = sgp30_get_iaq_baseline(&iaq_baseline);
  if (err == STATUS_OK)
  {
    *baseline_data = iaq_baseline;
  }
  return err;
}

unsigned short Sgp30_app::set_iaq_baseline(unsigned int baseline_data)
{
  return sgp30_set_iaq_baseline(baseline_data);
}

unsigned short Sgp30_app::set_absolute_humidity(unsigned int humidity_data)
{
  return sgp30_set_absolute_humidity(humidity_data);
}
