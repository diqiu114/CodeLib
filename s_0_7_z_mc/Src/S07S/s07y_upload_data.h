/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp and ethenet upload data 
*
* 版本:
* V1.0 2021-03-19 初始程序编写 
***********************************************************/

#ifndef _S07Y_UPLOAD_DATA_H_
#define _S07Y_UPLOAD_DATA_H_

#include <stdbool.h>
#include "data_type.h"
#include "batt_data_observer.h"
#include "alarm_data_observer.h"
#include <bitset>
#include "rtc_ops.h"
#include "alarm_state.h"


#define ALARM_ETH_POS_VOLT_DROP_HI (1)
#define ALARM_ETH_POS_TEMP_HI (2)
#define ALARM_ETH_POS_SOH_LOW (3)
#define ALARM_ETH_POS_SOC_LOW (4)
#define ALARM_ETH_POS_CHARG_CURR_HI (5)
#define ALARM_ETH_POS_TOTAL_VOLT_LOW (6)
#define ALARM_ETH_POS_VOLT_DEVI_HI (7)
#define ALARM_ETH_POS_UNKNOWN (8)

#define ALARM_ETH_POS_CELL_VOLT_HI (1)
#define ALARM_ETH_POS_CELL_VOLT_LOW (0)

#define POWER_ON_START_CHECK_SELF        (0)
#define POWER_ON_CHECK_SELF_SUC          (1)
#define POWER_ON_CHECK_SELF_END          (2)
#define POWER_ON_CHECK_SELF_FAIL         (3)
#define COMPLEX_ALARM_SLIGHT             (5)
#define COMPLEX_ALARM_MODERATE           (6)
#define COMPLEX_ALARM_SERIOUS            (7)

#define CELL_TEMP_RATE   (10.0f)
#define SCALE(val, rate) ((float)((float)(val) / (float)(rate)))
    
#define ALARM_MAX_BYTES              21

typedef struct {
    uint32_t temp_err     : 1;
    uint32_t volt_err     : 1;
    uint32_t comm_err     : 1;
    uint32_t res          : 29;
}AlarmSelfFlagBit_t;

typedef union {
    AlarmSelfFlagBit_t bits;
    uint32_t           all;
}AlarmSelfFlag_t;

typedef enum {

    Group01TempHiLvl_1 = 0,Group01TempHiLvl_2,
    Group02TempHiLvl_1,Group02TempHiLvl_2,
    Group03TempHiLvl_1,Group03TempHiLvl_2,
    Group04TempHiLvl_1,Group04TempHiLvl_2,
    
    Group05TempHiLvl_1,Group05TempHiLvl_2,
    Group06TempHiLvl_1,Group06TempHiLvl_2,
    Group07TempHiLvl_1,Group07TempHiLvl_2,
    Group08TempHiLvl_1,Group08TempHiLvl_2,
    
    Group09TempHiLvl_1,Group09TempHiLvl_2,
    Group10TempHiLvl_1,Group10TempHiLvl_2,
    Group11TempHiLvl_1,Group11TempHiLvl_2,
    Group12TempHiLvl_1,Group12TempHiLvl_2,
    
    Group13TempHiLvl_1,Group13TempHiLvl_2,
    Group14TempHiLvl_1,Group14TempHiLvl_2,
    Group15TempHiLvl_1,Group15TempHiLvl_2,
    Group16TempHiLvl_1,Group16TempHiLvl_2,
    
    Group17TempHiLvl_1,Group17TempHiLvl_2,
    Group18TempHiLvl_1,Group18TempHiLvl_2,
    Group19TempHiLvl_1,Group19TempHiLvl_2,
    Group20TempHiLvl_1,Group20TempHiLvl_2,
    
    Group21TempHiLvl_1,Group21TempHiLvl_2,
    Group22TempHiLvl_1,Group22TempHiLvl_2,
    Group23TempHiLvl_1,Group23TempHiLvl_2,
    Group24TempHiLvl_1,Group24TempHiLvl_2,

    Cell01VolLoLvl_1,Cell01VolLoLvl_2,
    Cell01VolHiLvl_1,Cell01VolHiLvl_2,
    Cell02VolLoLvl_1,Cell02VolLoLvl_2,
    Cell02VolHiLvl_1,Cell02VolHiLvl_2,
    Cell03VolLoLvl_1,Cell03VolLoLvl_2,
    Cell03VolHiLvl_1,Cell03VolHiLvl_2,
    Cell04VolLoLvl_1,Cell04VolLoLvl_2,
    Cell04VolHiLvl_1,Cell04VolHiLvl_2,
    Cell05VolLoLvl_1,Cell05VolLoLvl_2,
    Cell05VolHiLvl_1,Cell05VolHiLvl_2,
    Cell06VolLoLvl_1,Cell06VolLoLvl_2,
    Cell06VolHiLvl_1,Cell06VolHiLvl_2,
    Cell07VolLoLvl_1,Cell07VolLoLvl_2,
    Cell07VolHiLvl_1,Cell07VolHiLvl_2,
    Cell08VolLoLvl_1,Cell08VolLoLvl_2,
    Cell08VolHiLvl_1,Cell08VolHiLvl_2,
    Cell09VolLoLvl_1,Cell09VolLoLvl_2,
    Cell09VolHiLvl_1,Cell09VolHiLvl_2,
    Cell10VolLoLvl_1,Cell10VolLoLvl_2,
    Cell10VolHiLvl_1,Cell10VolHiLvl_2,
    Cell11VolLoLvl_1,Cell11VolLoLvl_2,
    Cell11VolHiLvl_1,Cell11VolHiLvl_2,
    Cell12VolLoLvl_1,Cell12VolLoLvl_2,
    Cell12VolHiLvl_1,Cell12VolHiLvl_2,
    Cell13VolLoLvl_1,Cell13VolLoLvl_2,
    Cell13VolHiLvl_1,Cell13VolHiLvl_2,
    Cell14VolLoLvl_1,Cell14VolLoLvl_2,
    Cell14VolHiLvl_1,Cell14VolHiLvl_2,
    Cell15VolLoLvl_1,Cell15VolLoLvl_2,
    Cell15VolHiLvl_1,Cell15VolHiLvl_2,
    Cell16VolLoLvl_1,Cell16VolLoLvl_2,
    Cell16VolHiLvl_1,Cell16VolHiLvl_2,
    Cell17VolLoLvl_1,Cell17VolLoLvl_2,
    Cell17VolHiLvl_1,Cell17VolHiLvl_2,
    Cell18VolLoLvl_1,Cell18VolLoLvl_2,
    Cell18VolHiLvl_1,Cell18VolHiLvl_2,
    Cell19VolLoLvl_1,Cell19VolLoLvl_2,
    Cell19VolHiLvl_1,Cell19VolHiLvl_2,
    Cell20VolLoLvl_1,Cell20VolLoLvl_2,
    Cell20VolHiLvl_1,Cell20VolHiLvl_2,
    Cell21VolLoLvl_1,Cell21VolLoLvl_2,
    Cell21VolHiLvl_1,Cell21VolHiLvl_2,
    Cell22VolLoLvl_1,Cell22VolLoLvl_2,
    Cell22VolHiLvl_1,Cell22VolHiLvl_2,
    Cell23VolLoLvl_1,Cell23VolLoLvl_2,
    Cell23VolHiLvl_1,Cell23VolHiLvl_2,
    Cell24VolLoLvl_1,Cell24VolLoLvl_2,
    Cell24VolHiLvl_1,Cell24VolHiLvl_2,

    ChargeOverLvl_1,
    ChargeOverLvl_2,
    DischargeOverLvl_1,
    DischargeOverLvl_2,
    TotalVolLoLvl_1,
    TotalVolLoLvl_2,
    TotalVolHiLvl_1,
    TotalVolHiLvl_2,
    
    TotalVolDeLvl_1,
    TotalVolDeLvl_2,
    CellAVolDiffHi_Lvl_1,//
    CellAVolDiffHi_Lvl_2,//
    CellBVolDiffHi_Lvl_1,//
    CellBVolDiffHi_Lvl_2,//
    CellTempDiffHi_Lvl_1,//
    CellTempDiffHi_Lvl_2,//
    
    SOCLoLvl_1,
    SOCLoLvl_2,
    SOHLoLvl_1,
    SOHLoLvl_2,

    AlarmMaxType,
}AlarmType_t;

typedef struct {
	Alarm_code_t alarm_code;
	Alarm_lvl_t  alarm_lvl;
    uint8_t      id;
	uint8_t      alarm_pos;
}AlarmInfor_t;


typedef struct {
    uint8_t bits[ALARM_MAX_BYTES];
}AlarmBits_t;

typedef struct _tag_max_data_
{
  unsigned char id;
  union {
      unsigned short volt;
               short temp;
  };
  
} Max_data_t;

typedef struct _tag_min_data_
{
  unsigned char id;
  union {
      unsigned short volt;
               short temp;
  };
} Min_data_t;

typedef struct {
    uint16_t version_z : 4;
    uint16_t verison_y : 4;
    uint16_t version_x : 4;
}S07Y_Version_t;

typedef enum _tag_op_para_
{
  OP_SET,
  OP_RESET
} Op_para_t;

typedef enum {
//1：未自检；2自检中；3自检成功；4自检失败
    AlarmSelfCheckNone = 0,
    AlarmSelfCheckNo,
    AlarmSelfChecking,
    AlarmSelfCheckOk,
    AlarmSelfCheckFailed,
}AlarmSelfCheckStatus_t;



typedef struct _tag_S30_eth_upload_data_
{
  Batt_data_t batt_data;
//  Max_data_t max_data;
//  Min_data_t min_data;
  Max_data_t max_volt_3;
  Min_data_t min_volt_3;
  Max_data_t max_volt_4;
  Min_data_t min_volt_4;
    
  Max_data_t max_temp;
  Min_data_t min_temp;
  
} Eth_upload_data_t;

extern bitset<8> complex_state;

using namespace ::std;

class S07Y_Upload_data : public Batt_data_observer, public Alarm_data_observer
{
public:
  S07Y_Upload_data();
  int get_eth_update_buff(unsigned char *buff);
  int get_mvb_update_buff(unsigned char *buff,uint16_t heart);
  int get_eth_update_buff(unsigned char *buff,uint16_t heart);
  virtual void update(Alarm_data_t *data, unsigned char opt = 0);
  virtual void update(Batt_data_t *data, unsigned char opt = 0);
  void set_alarm_state_handle(Alarm_state *_state_handle);
  void alarm_self_check(Batt_data_t *data);
  void alarm_self_check_set_status(AlarmSelfCheckStatus_t);
  void update_batt_data(void);
  void update_alarm_data(void);
  void alarm_pos_op(Alarm_data_t *data);
  bool get_alarm_flag(Alarm_data_t *data);
  AlarmSelfFlag_t alarm_self_flag;
#if (USE_FREE_RTOS)
  void set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
  void set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
#endif
  Max_data_t find_max_volt_val(Cell_data_t *cell_data);
  Min_data_t find_min_volt_val(Cell_data_t *cell_data);
  Max_data_t find_max_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt);
  Min_data_t find_min_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt);
  Max_data_t find_max_temp_val(Cell_data_t *cell_data);
  Min_data_t find_min_temp_val(Cell_data_t *cell_data);
  ~S07Y_Upload_data(void);

private:
  Eth_upload_data_t eth_data;
  Alarm_state *alarm_state_handle;
  AlarmBits_t alarmAllBits;
  //bitset<32> eth_total_alarm;
  //bitset<8> *eth_cell_alarm;
  unsigned short heartbeat;
  
  Alarm_data_t *alm_data;
  Batt_data_t *batt_data;

#if (USE_FREE_RTOS)
  QueueHandle_t alm_update_queue;
  QueueHandle_t data_update_queue;

  Queue_msg alm_update_msg;
  Queue_msg data_update_msg;
  unsigned int alm_update_timeout;
  unsigned int data_update_timeout;
#endif

  unsigned char crc8(unsigned char *buff, int buff_len);
  short eth_alarm_pos(Alarm_code_t alarm_code);
  void eth_alarm_bit_op(Op_para_t para, short pos);

  unsigned char judge_complex_alarm_state(Alarm_data_t *data);
  unsigned char slight_alarm_cnt;
  unsigned char moderate_alarm_cnt;
  unsigned char serious_alarm_cnt;
  AlarmSelfCheckStatus_t alarm_self_check_state;
  
  
};

#endif // _S07Y_Upload_data_H_
