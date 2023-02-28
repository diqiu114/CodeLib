/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      项目类初始化
*
* 版本:
* V1.0 2019-06-20 
***********************************************************/

#ifndef _PROJ_CLASS_INIT_H_
#define _PROJ_CLASS_INIT_H_

#include "defines.h"
#include "rtc_ops.h"
#include "comm/Double_buffered_comm.h"
#include "adc_app.h"
#include "paras_file.h"
#include "file.h"
#include "batt_state.h"
#include "gpi.h"
#include "batt_data.h"
#include "alarm_data_store.h"
#include "hist_data_store.h"
#include "cell_comm.h"
#include "alarm.h"
#include "soc\batt_cap.h"
#include "modbus_master.h"
#include "alarm_state.h"
#include "adc.h"
#include "usart.h"
#include "sar_adc.h"
#include "hw_interface\gpio\stm32_gpio.h"
#include "tim.h"
#include "soc\charge\recharge_method.h"
#include "soc\discharge\ah_method\ah_method_discharge.h"
#include "soc\vrla_soc\vrla_discharge_cur.h"
#include "soc\vrla_soc\vrla_temp_comp.h"
#if S07Y
#include "s07y_upload_data.h"
#elif S07R
#include "s07r_upload_data.h"
#elif S07S
#include "s07s_upload_data.h"
#endif


// total battery
extern Adc_app *tb_adc;
extern Adc_app *Pt1000_adc;
extern Gpi *addr_sw;
extern Paras_file *Sys_para_file;
extern Paras_file *Dev_para_file;
extern Paras_file *Cell_config_para_file;
extern Paras_file *User_para_file;
extern Paras_file *Soh_record_file;
extern Paras_file *Discharged_cap_file;
extern File* Hist_data_file;
extern File* Alm_data_file;
extern Batt_data* Monitoring_data;
extern Hist_data_store* Batt_hist_data_store;
extern Alarm_data_store* Alarm_store;
extern Batt_state* Battery_status;
extern Batt_data* Monitoring_data;
extern Rtc_ops* Rtc;
extern Cell_comm* Cell_node; 
extern UART_HandleTypeDef* Cell_node_uart;
extern Alarm_handler *Alarm;
extern Alarm_state  *alarm_state;

#if USE_MVB
#include "mvb_module.h"
#include "mvb_app.h"
extern Mvb_module* Mvb; 
extern Stm32_uart * Mvb_uart ;
extern UART_HandleTypeDef* Mvb_uart_handle;
extern Mvb_app* Train_mvb;
extern Mvb_data Mvb_send_frame;
extern unsigned char Mvb_send_buff[MVB_SEND_BUFF_SIZE];
extern unsigned char Mvb_port_idx;
#endif

#if USE_ETH
#include "eth_board.h"
extern Eth_board* Trdp;
extern UART_HandleTypeDef* Eth_uart;
extern unsigned char Eth_send_buff[ETH_SEND_BUFF_SIZE];
extern unsigned char Eth_train_idx;
extern Stm32_uart *Trdp_uart ;
#endif

#if (USE_485)
#include "rs485_data_tranceiver.h"
  extern RS485 *Rs485_comm ;
  extern Data_tranceiver_if *Data_tranceiver ;
#endif
extern Batt_cap *Batt_soc;
extern Discharged_cap_record* Discharge_soc_record;
extern Recharge_method* Variable_charge_effi_method;
extern Modbus_master * Comm_cell_modbuse;
extern ADC_HandleTypeDef *tb_handle ;
extern ADC_HandleTypeDef *Pt1000_handle;

#if S07Y
extern S07Y_Upload_data* Train_data;
#elif S07S
extern S07S_Upload_data* Train_data;
#elif S07R
extern S07R_Upload_data* Train_data;
#endif
extern bool is_first;
bool Proj_class_init(void);

void uart_rev_callback(UART_HandleTypeDef* uart_handle);
// FATFS f_forward callback function
UINT out_stream (const BYTE *p, UINT btf);

bool batt_cap_store(float cap_rate);
bool batt_init_flag_store(bool flag);
bool batt_discharged_cap_store(float cap);

#endif // _PROJ_CLASS_INIT_H_
