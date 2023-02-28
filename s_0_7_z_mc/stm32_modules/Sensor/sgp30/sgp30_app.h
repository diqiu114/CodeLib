/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Sensirion SGP30 application
* datasheet link:
* https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/9_Gas_Sensors/Datasheets/Sensirion_Gas_Sensors_SGP30_Datasheet.pdf
*
***********************************************************/
#ifndef _SGP30_APP_H_
#define _SGP30_APP_H_

#include <stdbool.h>
#include "sgp30.h"
#define MAX_CONNECTION_FAILED_TIMES 3
#define TVOC_FIXED_VALUE 0
#define CO2_FIXED_VALUE 400
#define TVOC_LOWER_RANGE  (0)
#define TVOC_UPPER_RANGE  (60000)
#define SGP30_CO2_LOWER_RANGE (400)
#define SGP30_CO2_UPPER_RANGE (60000)

// base line storage seconds (2 hour)
#define SGP_BASELINE_STORE_PERIOD_IN_SECONDS (7200)

// sensor raw signals
typedef struct _tag_gas_raw_data_{
  unsigned short ethanol_raw_signal;
  unsigned short h2_raw_signal;
} Gas_raw_data_t;

typedef struct _tag_iaq_data_{
  unsigned short tvoc_ppb;
  unsigned short co2_eq_ppm;
}Iaq_data_t;

typedef struct _tag_sgp30_verision_{
  unsigned short feature_set_version;
  unsigned char product_type;
}Sgp30_verision;

class Sgp30_app
{
public:
  Sgp30_app();
  ~Sgp30_app();

  bool init(void);
  bool is_error(void);
  unsigned short get_iaq_data(unsigned short *tvoc, unsigned short *co2);
  unsigned short get_gas_raw_data(unsigned short *ethanol_signal, unsigned short *h2_signal);
  unsigned short get_iaq_baseline(unsigned int *baseline_data);
  unsigned short set_iaq_baseline(unsigned int baseline_data);
  unsigned short set_absolute_humidity(unsigned int humidity_data);

private:
  unsigned long long get_sgp30_serial_id();
  unsigned int iaq_baseline;
  Gas_raw_data_t gas_raw_data;
  Iaq_data_t iaq_data;
  Sgp30_verision spg30_verison;
  unsigned char error_times;
};

#endif // _Sgp30_APP_H_
