#ifndef _ALARM_STATE_H_
#define _ALARM_STATE_H_

#include <stdbool.h>
#include "alarm_data_observer.h"
#include <bitset>
#include "alarm.h"
  
#define ALARM_POS_UNKNOW                   (0xFF)  
#if 0
#define ALARM_POS_MC_TOTAL_VOLT_LOW        (0)
#if S07S
#define ALARM_POS_MC_TOTAL_VOLT_DEVIATE_HI (1)
#define ALARM_POS_MC_SOH_LOW               (2)
#elif S07R
#define ALARM_POS_MC_TOTAL_VOLT_HI        (1)
#define ALARM_POS_MC_DISCHARGE_CUR_HI     (2)
#endif
#define ALARM_POS_MC_TEMP_HIGH             (3)
#define ALARM_POS_MC_CHARGE_CUR_HIGH       (4)
#define ALARM_POS_MC_SOC_LOW               (5)
#define ALARM_POS_CELL_VOLT_HIGH           (6)
#define ALARM_POS_CELL_VOLT_LOW            (7)
#define ALARM_POS_CELL_VOLT_DIFF_HIGH      (8)
#define ALARM_POS_CELL_COMM_ERROR          (9)
#endif


typedef struct _tag_alarm_cell_data_
{
  unsigned char alm_status;//02  05JIECHU
  Alarm_code_t alm_code;
  char id;
} Alarm_cell_data_t;

class Alarm_state :public Alarm_data_observer
{
public:
  Alarm_state();
  virtual void update(Alarm_data_t* data, unsigned char opt = 0);
  bool get_alarm_state();
  char alarm_set_pos(Alarm_code_t alarm_code);
  char alarm_reset_pos(Alarm_code_t alarm_code);
  ~Alarm_state();
private:
  int check_cell_volt_low();
  int check_cell_volt_hig( );
  int check_cell_temp_hig( );
  int check_cell_comm_error( );
  bitset<16> alarm;
  bool *cell_volt_over;
  bool *cell_volt_low;
  bool *cell_temp_over;
  bool *cell_comm_err;

};
  
#endif


