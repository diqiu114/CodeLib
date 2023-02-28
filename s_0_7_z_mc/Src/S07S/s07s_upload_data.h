/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp and ethenet upload data 
*
* 版本:
* V1.0 2021-03-19 初始程序编写 
***********************************************************/

#ifndef _S07S_UPLOAD_DATA_H_
#define _S07S_UPLOAD_DATA_H_

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


typedef struct _tag_max_data_
{
  unsigned char id;
  unsigned short volt;
} Max_data_t;

typedef struct _tag_min_data_
{
  unsigned char id;
  unsigned short volt;
} Min_data_t;

typedef enum _tag_op_para_
{
  OP_SET,
  OP_RESET
} Op_para_t;

typedef struct _tag_S30_eth_upload_data_
{
  Batt_data_t batt_data;
  Max_data_t max_data;
  Min_data_t min_data;
} Eth_upload_data_t;

extern bitset<8> complex_state;

using namespace ::std;

class S07S_Upload_data : public Batt_data_observer, public Alarm_data_observer
{
public:
  S07S_Upload_data();
  int get_eth_update_buff(unsigned char *buff);
  virtual void update(Alarm_data_t *data, unsigned char opt = 0);
  virtual void update(Batt_data_t *data, unsigned char opt = 0);
  void set_alarm_state_handle(Alarm_state *_state_handle);
  void update_batt_data(void);
  void update_alarm_data(void);
#if (USE_FREE_RTOS)
  void set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
  void set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
#endif

  ~S07S_Upload_data(void);

private:
  Eth_upload_data_t eth_data;
  Alarm_state *alarm_state_handle;
  bitset<32> eth_total_alarm;
  bitset<8> *eth_cell_alarm;
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
  Max_data_t find_max_volt_val(Cell_data_t *cell_data);
  Min_data_t find_min_volt_val(Cell_data_t *cell_data);
  unsigned char judge_complex_alarm_state(Alarm_data_t *data);
  unsigned char slight_alarm_cnt;
  unsigned char moderate_alarm_cnt;
  unsigned char serious_alarm_cnt;
};

#endif // _S07S_UPLOAD_DATA_H_
