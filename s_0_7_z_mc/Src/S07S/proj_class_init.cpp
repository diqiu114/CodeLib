#include "proj_class_init.h"
#include "main.h"
#include <map>
#include "paras.h"
#include "proj_batt_data.h"
#include "proj_alarm_store.h"
#include "proj_batt_alarm.h"
//#include "proj_batt_cap.h"

#include "soc\batt_cap_adj.h"
#include "soc\batt_cap_init.h"
#include "soc\batt_cap.h"
#include "soc\self_discharge.h"
#include "data_convert\lookup_table.h"
#include "data_convert\Polynomial1.h"
#include "data_convert\Polynomial6.h"
#include "batt_cap\soc_table.h"
#include "stm32_uart.h"
#include "soc\nicd_cutoff_volt.h"
#include "soc\vrla_soc\vrla_floating_volt.h"

unsigned char* cur_table = NULL;
unsigned char* temp_table = NULL;
unsigned char* init_table = NULL;

Rtc_ops *Rtc = NULL;
Adc_app *tb_adc = NULL;
Adc_app *Pt1000_adc = NULL;
Gpi *addr_sw = NULL;

Paras_file *Sys_para_file = NULL;
Paras_file *Dev_para_file = NULL;
Paras_file *Cell_config_para_file = NULL;
Paras_file *User_para_file = NULL;
Paras_file *Soh_record_file = NULL;
Paras_file *Discharged_cap_file = NULL;
float Discharged_cap = 0;

File *Hist_data_file = NULL;
File *Alm_data_file = NULL;
Alarm_handler *Alarm = NULL;
Modbus_master * Comm_cell_modbuse = NULL;
Batt_state *Battery_status = NULL;
Batt_data *Monitoring_data = NULL;
Alarm_state  *alarm_state = NULL;
Alarm_data_store *Alarm_store = NULL;
Hist_data_store *Batt_hist_data_store = NULL;
extern QueueHandle_t Eth_comm_queue;

//SW3 = switch board 1
Gpi_Info as_gpio[ADDR_SW_CNT] = {
    SW3_GPIO_Port, SW3_Pin,
    SW4_GPIO_Port, SW4_Pin,
    SW1_GPIO_Port, SW1_Pin,
    SW2_GPIO_Port, SW2_Pin,
};

ADC_HandleTypeDef *tb_handle = &hadc1;
ADC_HandleTypeDef *Pt1000_handle = &hadc3;

Cell_comm *Cell_node = NULL;
UART_HandleTypeDef *Cell_node_uart = &huart6;
		
#if USE_MVB
Mvb_module *Mvb = NULL;
Stm32_uart * Mvb_uart  = NULL;
UART_HandleTypeDef *Mvb_uart_handle = &huart1;
Mvb_app *Train_mvb = NULL;
Mvb_data Mvb_send_frame;
unsigned char Mvb_send_buff[MVB_SEND_BUFF_SIZE];
unsigned char Mvb_port_idx = 0;

#endif

#if USE_ETH	
Eth_board* Trdp = NULL;
UART_HandleTypeDef *Eth_uart = &huart5;
Stm32_uart *Trdp_uart = NULL;
unsigned char Eth_send_buff[ETH_SEND_BUFF_SIZE];
unsigned char Eth_train_idx = 0;
#endif	

#if (USE_485)
  RS485 *Rs485_comm = NULL;
  Data_tranceiver_if *Data_tranceiver = NULL;
#endif


FIL Fil;

Batt_cap *Batt_soc = NULL;
Discharged_cap_record* Discharge_soc_record = NULL;
Recharge_method* Variable_charge_effi_method = NULL;
Batt_discharge_proc_if *Soc_discharge_method = NULL;
#if S07Y
S07Y_Upload_data* Train_data = NULL;
#elif S07S
S07S_Upload_data* Train_data = NULL;
#elif S07R
S07R_Upload_data* Train_data = NULL;
#endif

vector<Data_convert_if*> total_data_rate;
vector<Data_convert_if*> total_data_calib;

vector<Data_convert_if*> pt1000_rate;
vector<Data_convert_if*> pt1000_calib;


bool Store_init_cap_flag_callback(bool flag)
{
  Dev_paras.soc_init = flag;
  return Dev_para_file->write(&Dev_paras);
}
uint8_t paras_count = 0;

bool Proj_class_init(void)
{
  
    
  Rtc = new Rtc_ops(&hrtc);
  if (Rtc == NULL)
  {
    return false;
  }

  // system parameter, hist ory data and alarm data read/wrie
  Sys_para_file = new Paras_file(Fil, SYS_PARA_FILE_NAME, sizeof(Sys_paras.dev_id));
  if (Sys_para_file == NULL)
  {
    return false;
  }

  if (Sys_para_file->get_count() != 0)
  {
    bool read_ok = Sys_para_file->read(&Sys_paras.dev_id);
    if (!read_ok)
    {
      // write default system parameters
      Sys_para_file->write(&Sys_paras.dev_id);
      paras_count++;
    }
  }
  else
  {
      // write default system parameters
      Sys_para_file->write(&Sys_paras.dev_id);
      paras_count++;
  }

  
  Cell_config_para_file = new Paras_file(Fil, AFE_CONFIG_PARAS_FILE_NAME, sizeof(Cell_adc_config_paras_t));
  if (Cell_config_para_file == NULL)
  {
    return false;
  }

  // for test
//   Cell_config_para_file->clear();

  

  Dev_para_file = new Paras_file(Fil, DEV_PARA_FILE_NAME, sizeof(Dev_paras_t));
  if (Dev_para_file == NULL)
  {
    return false;
  }

  // for test
//   Dev_para_file->clear();

  if (Dev_para_file->get_count() != 0)
  {
    bool read_ok = Dev_para_file->read(&Dev_paras);
    if (!read_ok)
    {
      // write default system parameters
      Dev_para_file->write(&Dev_paras);
      paras_count++;
    }
  }
  else
  {
    // write default system parameters
    Dev_para_file->write(&Dev_paras);
    paras_count++;
  }

  
  Dev_paras.volt_cnt = 0;
  Dev_paras.temp_cnt = 0;

  for(int i = 0; i < ACQ_MAX_CNT; i++)
  {
    if(Cell_adc_config_paras[i].is_enable)
    {
      if(Cell_adc_config_paras[i].acq_type == TYPE_TEMP)
      {
        Dev_paras.temp_cnt++;
      }
      else if(Cell_adc_config_paras[i].acq_type == TYPE_VOLT)
      {
        Dev_paras.volt_cnt++;
      }
    }
  }
  
  Dev_paras.temp_cnt = CELL_CNT * Dev_paras.temp_cnt;
  Dev_paras.volt_cnt = CELL_CNT * Dev_paras.volt_cnt;

  User_para_file = new Paras_file(Fil, USER_PARA_FILE_NAME, sizeof(User_paras_t));
  if (User_para_file == NULL)
  {
    return false;
  }

  //  User_para_file->clear();
  if (User_para_file->get_count() != 0)
  {
    bool read_ok = User_para_file->read(&User_paras);
    if (!read_ok)
    {
      // write default system parameters
      User_para_file->write(&User_paras);
        paras_count++;
    }
  }
  else
  {
    // write default system parameters
    User_para_file->write(&User_paras);
      paras_count++;
  }
  
  if(User_paras.period.cell_comm == 0 || User_paras.period.cell_comm > 600) {
    User_paras.period.cell_comm = 1;
  }
  
  if(User_paras.period.acquire == 0 || User_paras.period.cell_comm > 600) {
    User_paras.period.acquire = 1;
  }
  
  if(User_paras.period.store  < User_paras.period.cell_comm) {
    User_paras.period.store = User_paras.period.cell_comm;
  }
  
  
  Soh_record.soh = 100;
  Soh_record.last_update_ts = Rtc->get_ts();
  Soh_record_file = new Paras_file(Fil, SOH_RECORD_FILE_NAME, sizeof(Soh_record_t));
  if (Soh_record_file == NULL)
  {
    return false;
  }
  if (Soh_record_file->get_count() != 0)
  {
    bool read_ok = Soh_record_file->read(&Soh_record);
    if (!read_ok)
    {
      Soh_record_file->write(&Soh_record);
        paras_count++;
    }
  }
  else
  {
    Soh_record_file->write(&Soh_record);
      paras_count++;
  }

  // discharged capacity store file
  Discharged_cap_file = new Paras_file(Fil, DISCHARGED_CAP_FILE_NAME, sizeof(float));
  if (Discharged_cap_file == NULL)
  {
    return false;
  }

  if (Discharged_cap_file->get_count() != 0)
  {
    bool read_ok = Discharged_cap_file->read(&Discharged_cap);
    if (!read_ok)
    {
      // write default system parameters
      Discharged_cap_file->write(&Discharged_cap);
        paras_count++;
    }
  }
  else
  {
    // write default system parameters
    Discharged_cap_file->write(&Discharged_cap);
      paras_count++;
  }

	
  Hist_data_file = new File(Fil, HISTORY_DATA_FILE_NAME);
  if (Hist_data_file == NULL)
  {
    return false;
  }
  if (Hist_data_file->header_need_init())
  {
    File_header header = {
        0, 0, sizeof(History_data_t),
        HISTORY_DATA_STORE_CNT,
        true, FILE_DATA_VER};

    Hist_data_file->create(&header);
  }

  Alm_data_file = new File(Fil, ALARM_DATA_FILE_NAME);
  if (Alm_data_file == NULL)
  {
    return false;
  }

  if (Alm_data_file->header_need_init())
  {
    File_header header = {
        0, 0, sizeof(Alarm_store_data_t),
        ALARM_DATA_STORE_CNT,
        true, FILE_DATA_VER};

    Alm_data_file->create(&header);
  }

  addr_sw = new Gpi(as_gpio, ADDR_SW_CNT);
  if (addr_sw == NULL)
  {
    return false;
  }
  addr_sw->reverse();

  Batt_hist_data_store = new Hist_data_store(Hist_data_file);
  if (Batt_hist_data_store == NULL)
  {
    return false;
  }

  Alarm_store = new Proj_alarm_store(Alm_data_file);
  if (Alarm_store == NULL)
  {
    return false;
  }

  Alarm = new Batt_alarm(User_paras.alm_thr, User_paras.period.cell_comm);
  if (Alarm == NULL)
  {
    return false;
  }

  Battery_status = new Batt_state(&User_paras.batt_state_thr);
  if (Battery_status == NULL)
  {
    return false;
  }
	
  Monitoring_data = new Proj_batt_data();
  if (Monitoring_data == NULL)
  {
    return false;
  }	
  
  tb_adc = new Adc_app(new Sar_adc(tb_handle, new Adc_para(TB_CH_CNT, TB_CH_SAMP_CNT, AD_MAX, AD_REF_VOLT,FT_RMS), &htim5, TIM_CHANNEL_1));
  if (tb_adc == NULL)
  {
    return false;
  }

   for(int i = 0; i < VOLT_CH_CNT + CUR_CH_CNT; i++)
  {
    total_data_rate.push_back(new Polynomial1(new Py1_params(&Dev_paras.rate.total_batt[i])));
    total_data_calib.push_back(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[i])));
  }
  
  tb_adc->set_rate(total_data_rate);
  tb_adc->set_calib(total_data_calib);
  
	Pt1000_adc = new Adc_app(new Sar_adc(Pt1000_handle, new Adc_para(PT1000_CH_CNT, PT1000_CH_SAMP_CNT, AD_MAX, AD_REF_VOLT)));
  if (Pt1000_adc == NULL)
  {
    return false;
  }
  unsigned char temp_para_offset = VOLT_CH_CNT + CUR_CH_CNT;
  
  for(int i = 0; i < COUNT_OF_TEMP; i++)
  {
    pt1000_rate.push_back(new Polynomial3(new Py3_params(&Dev_paras.rate.temp_rate[i])));
    pt1000_calib.push_back(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[temp_para_offset + i])));
  }
  
  Pt1000_adc->set_rate(pt1000_rate);
  Pt1000_adc->set_calib(pt1000_calib);
  
#if USE_485
#if S07S
  Rs485_comm = new RS485(Cell_node_uart, CELL_COMM_BUFF_SIZE, new Stm32_gpio(USART6_DE_GPIO_Port,USART6_DE_Pin), GPIO_HI,uart_rev_callback);
#elif S07R
	Rs485_comm = new RS485(Cell_node_uart, CELL_COMM_BUFF_SIZE, new Stm32_gpio(USART6_DE_GPIO_Port,USART6_DE_Pin), GPIO_LOW, uart_rev_callback);
#endif	
#endif
  
#if USE_485
  if(Rs485_comm == NULL)
  {
    return false;
  }
  
  Comm_cell_modbuse = new  Modbus_master(Rs485_comm,MODBUS_MAX_DELAY);
  if(Comm_cell_modbuse == NULL)
  {
    return false;
  }
#endif
  char bit =  ((addr_sw->read(0)) << 3) | ((addr_sw->read(1)) << 2) | ((addr_sw->read(2)) << 1) | ((addr_sw->read(3)));
  switch((bit & 0x0f))    
  {
    case 8: Eth_train_idx = 0; break;
    case 4: Eth_train_idx = 1; break;
    default: Eth_train_idx = 0; break;
  }
  
#if USE_MVB
  Mvb_uart = new Stm32_uart(Mvb_uart_handle, MVB_COMM_BUFF_SIZE, uart_rev_callback);
  if (Mvb_uart == NULL)
  {
    return false;
  }
  Mvb = new Mvb_module(Mvb_uart, Eth_train_idx);
  if (Mvb == NULL)
  {
    return false;
  }
  
  Mvb->set_rst_pin(new Stm32_gpio(MVB_RESET_GPIO_Port,MVB_RESET_Pin));
	
  Train_mvb = new Mvb_app(Mvb, Eth_train_idx, MVB_REC_BUFF_SIZE);
  if (Train_mvb == NULL)
  {
    return false;
  }
#endif

#if USE_ETH	

  Trdp_uart = new Stm32_uart(&huart5, ETH_COMM_BUFF_SIZE, uart_rev_callback);
  if (Trdp_uart == NULL)
  {
    return false;
  }

#if S07Y
  Train_data = new S07Y_Upload_data();
#elif S07S
  Train_data = new S07S_Upload_data();
#elif S07R
  Train_data = new S07R_Upload_data();
#endif
	if (Train_data == NULL)
	{
		return false;
	}
	Train_data->set_alarm_state_handle(alarm_state);
  
  Trdp = new Eth_board(Trdp_uart, new Stm32_gpio(ETH_RST_GPIO_Port,ETH_RST_Pin), Eth_train_idx, &Dev_paras.eth_paras[Eth_train_idx].trdp_paras);
  if (Trdp == NULL)
  {
    return false;
  }
#if S07R 
  if(!Trdp->set_user_proto_handle_func(Train_data->user_proto_fill))
  {
    return false;
  }
#endif 
  if(!Trdp->set_recv_queue(&Eth_comm_queue))
  {
    return false;
  }
#endif

  // battery capacity
  Batt_cap_params *batt_cap_params = new Batt_cap_params( BATT_NOMIAN_CAP, 
                                                          BATT_CUR_MAX, 
                                                          BATT_CUR_MIN, 
                                                          User_paras.batt_state_thr.discharge_to_charge_thr, 
                                                          User_paras.batt_state_thr.charge_to_discharge_thr, 
                                                          BATT_CAP_CALC_PERIOD_MS, 
                                                          Dev_paras.soc_actual / NEW_MRX100_CAP);
  if(batt_cap_params == NULL)
  {
    return false;
  }
  
  Batt_cap_init *batt_cap_init = new Batt_cap_init(new Batt_cap_init_params(BATT_INIT_DATA_BUFFER_SIZE, 
                                                                            BATT_NOMIAN_CAP, 
                                                                            BATT_INIT_VOLT_UPPER_LIMIT, 
                                                                            BATT_INIT_VOLT_LOWER_LIMIT, 
                                                                            BATT_INIT_CUR_UPPER_LIMIT, 
                                                                            BATT_INIT_CUR_LOWER_LIMIT, 
                                                                            BATT_INIT_VOLT_DIFF, 
                                                                            BATT_INIT_CUR_DIFF), 
                                                    new Lookup_table<unsigned short>((unsigned short*)Soc_init_table, 
                                                                                     new Lookup_table_params(BATT_INIT_TABLE_LINE_SIZE, 
                                                                                     BATT_INIT_TABLE_ROW_SIZE, 
                                                                                     BATT_INIT_TABLE_LINE_OFFSET, 
                                                                                     BATT_INIT_TABLE_ROW_OFFSET, 
                                                                                     BATT_INIT_TABLE_LINE_RATE, 
                                                                                     BATT_INIT_TABLE_ROW_RATE, 
                                                                                     BATT_INIT_TABLE_VAL_RATE,
                                                                                     BATT_INIT_TABLE_LINE_ORDER)));
  if(batt_cap_init == NULL)
  {
    return false;
  }
  
  batt_cap_init->set_init_flag_store_callback(Store_init_cap_flag_callback);
  batt_cap_init->set_init_cap_flag(Dev_paras.soc_init);
    
  Data_convert_if* cur_format = new Lookup_table<unsigned short>((unsigned short*)Batt_cur_table, new Lookup_table_params(BATT_CUR_TABLE_LINE_SIZE, BATT_CUR_TABLE_ROW_SIZE, BATT_CUR_TABLE_LINE_OFFSET, BATT_CUR_TABLE_ROW_OFFSET, BATT_CUR_TABLE_LINE_RATE, BATT_CUR_TABLE_ROW_RATE, BATT_CUR_TABLE_VAL_RATE));
  Data_convert_if* temp_compen = new Lookup_table<float>((float*)Soc_temp_compensation_table, 
                                                          new Lookup_table_params(BATT_TEMP_COMPENSATION_TABLE_LINE_SIZE, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_ROW_SIZE, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_LINE_OFFSET, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_ROW_OFFSET, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_LINE_RATE, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_ROW_RATE, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_VAL_RATE, 
                                                                                  BATT_TEMP_COMPENSATION_TABLE_LINE_ORDER));
  if(cur_format == NULL || temp_compen == NULL)
  {
    return false;
  }
  
  Batt_cap_adj* batt_cap_adj = new Batt_cap_adj(BATT_ADJ_CAP_MIN, BATT_ADJ_CAP_MAX);
  if(batt_cap_adj == NULL)
  {
    return false;
  }
  
  Batt_cap_adj_params charge_adj(new Batt_info(BATT_CHARGE_ADJ_VOLT, BATT_CHARGE_ADJ_CUR, BATT_CHARGE_ADJ_TEMP),
                                 BATT_CHARGE_ADJ_RATE, BATT_CHARGE_ADJ_TERMINAL,
                                 BATT_CHARGE_ADJ_TEMP_MIN, BATT_CHARGE_ADJ_TEMP_MAX,
                                 new Polynomial1(new Py1_params(BATT_CHARGE_ADJ_VOLT_CURVE_K, BATT_CHARGE_ADJ_VOLT_CURVE_B))
                                 );
  Batt_cap_adj_params discharge_adj(new Batt_info(BATT_DISCHARGE_ADJ_VOLT, BATT_DISCHARGE_ADJ_CUR, BATT_DISCHARGE_ADJ_TEMP),
                                    BATT_DISCHARGE_ADJ_RATE, BATT_DISCHARGE_ADJ_TERMINAL, BATT_CHARGE_ADJ_TEMP_MIN, BATT_CHARGE_ADJ_TEMP_MAX, NULL, new Nicd_cutoff_volt());
  
  
  batt_cap_adj->add_charge_condition(charge_adj);
  batt_cap_adj->add_discharge_condition(discharge_adj);
  
  Discharge_soc_record = new Discharged_cap_record(-Sys_paras.batt_info.nomial_cap * 1.5);
  Discharge_soc_record->set_discharged_cap(Discharged_cap);
  Discharge_soc_record->set_discharged_cap_store_callback(batt_discharged_cap_store);
  Discharge_soc_record->set_charge_efficiency(BATT_CHARGE_EFFI);

  Variable_charge_effi_method = new Recharge_method(Sys_paras.batt_info.nomial_cap);

  Variable_charge_effi_method->set_discharged_cap(Discharged_cap);
  if(Variable_charge_effi_method == NULL)
  {
    return false;
  }
  Soc_discharge_method = new Ah_method_discharge(Sys_paras.batt_info.nomial_cap, cur_format, temp_compen);
  
  Batt_soc = new Batt_cap(batt_cap_params, Soc_discharge_method, Variable_charge_effi_method, batt_cap_adj);
  if (Batt_soc == NULL)
  {
    return false;
  }
  Batt_soc->set_cap_init(batt_cap_init);
  Batt_soc->set_discharged_cap_record(Discharge_soc_record);


	alarm_state = new  Alarm_state();
	if (alarm_state == NULL)
  {
    return false;
  }
  
  return true;
};

