#ifndef _PROJ_BATT_ALARM_H_
#define _PROJ_BATT_ALARM_H_

#include <stdbool.h>
#include "alarm.h"

#define MULTI_CELL_ERROR_MAX (3)

#define SCALE(val, rate) ((float)((float)(val) / (float)(rate)))

class Batt_alarm : public Alarm_handler
{
public:
  Batt_alarm(Alarm_thres_t &_alarm_thresholds, int data_update_time);
  virtual void update(Batt_data_t *data, unsigned char opt = 0);
  virtual void alarm_check(void);

private:
  vector<Alarm_data_t> continue_alarm;
  virtual void send_alarm(Alarm_data *alarm);
  bool float_zero(float &val);
  void send_alarm(Alarm_data_t *alarm);
  Alarm_data *check_low(float val, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl, int id = 0);
  Alarm_data *check_high(float val, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl, int id = 0);
  Alarm_data *check_data_zero(Cell_data_t &cell_data, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl);
  Alarm_data *check_alarm_status(enum ALARM_STATUS alm_state, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl);

  void check_total_under_volt(float &volt);
  void check_total_over_volt(float &volt);
  void check_total_over_volt(Batt_state_t &state, float &volt, float &temp);
  void check_total_volt_deviate_hi(Batt_state_t &state, float &volt, float &temp);
  void check_overtemp(Batt_data_t *batt_data);
  void check_drop_temp_over(Cell_data_t *cell_data);
  void check_charge_over_cur(float &cur, Batt_state_t &state);
  void check_discharge_over_cur(float &cur, Batt_state_t &state);
  void check_low_soc(float &val, Batt_state_t &state);
  void check_low_soh(float &val);
  void check_cell_overvolt(Cell_data_t *cell_data, float &temp, Batt_state_t &state);
  void check_cell_overvolt(Cell_data_t *cell_data, float &temp, Batt_state_t &state,uint8_t bat_cnt);
  Alarm_data *cell_volt_whether_hi(float volt, float &temp, unsigned int index);
  void check_cell_undervolt(Cell_data_t *cell_data);
  void check_cell_undervolt(Cell_data_t *cell_data,uint8_t bat_cnt);
  void check_cell_comm_error(Cell_data_t *cell_data);
  void check_drop_volt_over( Cell_data_t *cell_data , Batt_state_t &state);
  void check_drop_volt_over(Cell_data_t *cell_data, Batt_state_t &state,uint8_t bat_cnt);
  float find_max_volt_val(Cell_data_t *cell_data);
  float find_min_volt_val(Cell_data_t *cell_data);
  float find_max_temp_val(Cell_data_t *cell_data);
  float find_min_temp_val(Cell_data_t *cell_data);
  float find_max_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt);
  float find_min_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt);
};

#endif // _BATT_ALARM_H_
