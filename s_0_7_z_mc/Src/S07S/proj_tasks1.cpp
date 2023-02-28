#include "proj_tasks.h"
#include "cmsis_os.h"
#include "defines.h"
#include "class_init.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "proj_paras.h"
#include "debug.h"

#define TIME_SET_AVAILIBLE              (0x03)
#define TIME_JUDGED_AVAILIBEL_OFFSET    (8)
#define YEAR_OFFSET                     (9)
#define MONTH_OFFSET                    (10)
#define DAY_OFFSET                      (11)
#define HOUR_OFFSET                     (12)
#define MINUTE_OFFSET                   (13)
#define SECOND_OFFSET                   (14)

#define TASK_PRIORITY_MAX (configMAX_PRIORITIES - 1)
#define TASK_PRIORITY_MIN (1)

#define LED_FLASH_DELAY (1000)
#define SOH_UPDATE_DELAY (1800000)
#define HOUR_TO_SECONDS(x) ((x)*60 * 60)
#define DAY_TO_SECONDS(x) ((x)*HOUR_TO_SECONDS(24))
#define MONTH_TO_SECONDS(x) ((x)*DAY_TO_SECONDS(30))
#define SECONDS_TO_MILLISECONDS(x) (x * 1000)
#define SOH_ATTENUATION_VALUE_PER_MONTH   (1.0f / 12)
unsigned int Led_flash_delay_max = LED_FLASH_DELAY / SECONDS_TO_MILLISECONDS(User_paras.period.acquire);
unsigned int acquire_cnt = 0;

#define QUEUE_SEND_TIMEOUT (100)
#define TRDP_RECV_BUFF_SIZE   (125)
#define TRDP_COMMNET_MSG_FIX_SIZE   (124)
#define CELL_POWERUP_DELAY (3000)

// data acquire, include adc data and contactor detect
TaskHandle_t Data_acq_handle = NULL;
void Data_acq(void *pvParameters);

TaskHandle_t Cell_comm_handle = NULL;
void Cell_comm_process(void *pvParameters);

TaskHandle_t Soh_update_handle = NULL;
void Soh_update_process(void *pvParameters);

#if USE_MVB
TaskHandle_t Mvb_init_handle = NULL;
void Mvb_init(void *pvParameters);
TaskHandle_t Mvb_process_handle = NULL;
void Mvb_process(void *pvParameters);
QueueHandle_t Mvb_comm_queue = NULL;
#endif
#if USE_ETH
TaskHandle_t Eth_init_handle = NULL;
void Eth_init(void *pvParameters);
TaskHandle_t Eth_process_handle = NULL;
TaskHandle_t Eth_rev_handle = NULL;
void Eth_process(void *pvParameters);
void Eth_rev_data(void *pvParameters);
QueueHandle_t Eth_comm_queue = NULL;
#endif

bool is_first = true;


TaskHandle_t Batt_data_obs_process_handle = NULL;
void Batt_data_obs_proc(void *pvParameters);

TaskHandle_t Alm_obs_process_handle = NULL;
void Alarm_obs_proc(void *pvParameters);

TaskHandle_t Batt_cap_update_handle = NULL;
void Batt_cap_update(void *pvParameters);

QueueHandle_t Cell_comm_queue = NULL;
QueueHandle_t Cell_comm_cpl_queue = NULL;

QueueHandle_t Batt_data_obs_queue = NULL;
QueueHandle_t Alarm_obs_queue = NULL;

bool Usb_debug_mode = true;
TimerHandle_t Cell_comm_timer_handle = NULL;

void cell_comm_timer_callback(TimerHandle_t xTimer);

bool Data_ready = false;
bool Proj_task_create(void)
{

  bool task_create_ok = true;

  // adc acquire battery array voltage, totoal voltage, current and temperature
  xTaskCreate(Data_acq, "Adc_acq_task", 512, NULL, TASK_PRIORITY_MAX - 3, &Data_acq_handle);
  task_create_ok = task_create_ok && (Data_acq_handle != NULL);

  // cell communication
  xTaskCreate(Cell_comm_process, "Cell_comm", 512, NULL, TASK_PRIORITY_MAX - 1, &Cell_comm_handle);
  task_create_ok = task_create_ok && (Cell_comm_handle != NULL);
  
  xTaskCreate(Soh_update_process, "Soh_update", 512, NULL, TASK_PRIORITY_MAX - 4, &Soh_update_handle);
  task_create_ok = task_create_ok && (Soh_update_handle != NULL);
#if USE_MVB
  // MVB init
  xTaskCreate(Mvb_init, "Mvb_init", 512, NULL, TASK_PRIORITY_MAX - 3, &Mvb_init_handle);
  task_create_ok = task_create_ok && (Mvb_init_handle != NULL);

  xTaskCreate(Mvb_process, "Mvb_process", 512, NULL, TASK_PRIORITY_MAX - 4, &Mvb_process_handle);
  task_create_ok = task_create_ok && (Mvb_process_handle != NULL);
#endif

#if USE_ETH
  // Ethenet init
  xTaskCreate(Eth_init, "Ethenet_init", 512, NULL, TASK_PRIORITY_MAX - 2, &Eth_init_handle);
  task_create_ok = task_create_ok && (Eth_init_handle != NULL);

  xTaskCreate(Eth_process, "Eth_process", 512, NULL, TASK_PRIORITY_MAX - 4, &Eth_process_handle);
  task_create_ok = task_create_ok && (Eth_process_handle != NULL);

  xTaskCreate(Eth_rev_data, "Eth_rev_data", 512, NULL, TASK_PRIORITY_MAX - 3, &Eth_rev_handle);
  task_create_ok = task_create_ok && (Eth_rev_handle != NULL);
#endif

  xTaskCreate(Batt_data_obs_proc, "Batt_data_obs_proc", 512, NULL, TASK_PRIORITY_MAX - 2, &Batt_data_obs_process_handle);
  task_create_ok = task_create_ok && (Batt_data_obs_process_handle != NULL);

  xTaskCreate(Alarm_obs_proc, "Alarm_obs_proc", 512, NULL, TASK_PRIORITY_MAX - 1, &Alm_obs_process_handle);
  task_create_ok = task_create_ok && (Alm_obs_process_handle != NULL);

  xTaskCreate(Batt_cap_update, "Battery_capacity_update", 512, NULL, TASK_PRIORITY_MAX - 3, &Batt_cap_update_handle);
  task_create_ok = task_create_ok && (Batt_cap_update_handle != NULL);

  return task_create_ok;
}

void Proj_hw_init(void)
{
  MX_DMA_Init();

  MX_ADC1_Init();

  MX_ADC3_Init();
  // uart ethenet communication
#if USE_ETH
  MX_UART5_Init();
#endif
#if USE_WIFI_4g
  // wifi/4g module communication
  MX_UART7_Init();
#endif
#if USE_MVB
  // uart MVB communication
  MX_USART1_UART_Init();
#endif
#if USE_485
  // backup RS485 communication
  MX_USART3_UART_Init();
#endif
  // cell node communication
  MX_USART6_UART_Init();
}

History_data_t Data_buff;

void Proj_hw_config(void)
{
  if (Hist_data_file->read_last((unsigned char *)(&Data_buff), sizeof(Data_buff)) == F_OK)
  {
    Batt_soc->set_cap(Data_buff.batt_data.soc);

    // self discharge
    //    unsigned int ts_now = 0;
    //    ts_now = Rtc->get_ts();

    //    if (ts_now > Data_buff.ts)
    //    {
    //      Batt_soc->get_self_discharge_cap(ts_now - Data_buff.ts);
    //    }
  }
  else
  {
    // default 100% capacity
    Batt_soc->set_cap(100);
  }
  
#if USE_MVB
  Mvb_port_idx = addr_sw->read(0);
  Mvb_send_frame.dest_addr = Dev_paras.mvb[Mvb_port_idx].dest_port[0].addr[0] << 8 | Dev_paras.mvb[Mvb_port_idx].dest_port[0].addr[1];
  Mvb_send_frame.inc_offset = MVB_INC_OFFSET;
  Mvb_send_frame.sc = MVB_SPECIAL_DATA;

  Train_mvb->set_send_frame(&Mvb_send_frame);
  Train_mvb->set_rtc_handle(Rtc);
  Mvb_comm_queue = xQueueCreate(1, 1);
#endif

#if USE_ETH
  //  Train_eth->init_defualt_value(Eth_train_idx);
  Eth_comm_queue = xQueueCreate(1, 1);
#endif

  Cell_comm_timer_handle = xTimerCreate("cell_comm_timer", SECONDS_TO_MILLISECONDS(User_paras.period.cell_comm), pdTRUE, 0, cell_comm_timer_callback);

  // for test
  // Cell_comm_timer_handle = xTimerCreate("cell_comm_timer", 30000, pdTRUE, 0, cell_comm_timer_callback);
  //  xTimerStart(Cell_comm_timer_handle, 0);

  Batt_data_obs_queue = xQueueCreate(QM_CNT_MAX, sizeof(Queue_msg));
  Alarm_obs_queue = xQueueCreate(QM_CNT_MAX, sizeof(Queue_msg));

  Batt_hist_data_store->set_store_interval(User_paras.period.store / User_paras.period.cell_comm);
  // for test
  // Batt_hist_data_store->set_store_interval(1);

  Batt_hist_data_store->set_rtc_handle(Rtc);
  Alarm_store->set_rtc_handle(Rtc);

  Batt_hist_data_store->set_queue_handle(Batt_data_obs_queue, QM_HIST_DATA_STORE, QUEUE_SEND_TIMEOUT);
  Alarm->set_queue_handle(Batt_data_obs_queue, QM_ALM_CHK, QUEUE_SEND_TIMEOUT);
  Train_data->set_data_update_queue_handle(Batt_data_obs_queue, QM_UPLOAD_DATA_UPDATE, QUEUE_SEND_TIMEOUT);

  Alarm_store->set_queue_handle(Alarm_obs_queue, QM_ALM_DATA_STORE, QUEUE_SEND_TIMEOUT);
  Train_data->set_alm_update_queue_handle(Alarm_obs_queue, QM_UPLOAD_ALM_DATA_UPDATE, QUEUE_SEND_TIMEOUT);

  //  Cell_comm_queue = xQueueCreate(1, 1);
  Cell_comm_cpl_queue = xQueueCreate(1, 1);

  //  Cell_node->set_queue_handle(Cell_comm_queue);
  //  Cell_node->set_rev_timeout(CELL_DEFAULT_REV_DELAY);

  Hist_data_file->set_forward_callback(out_stream);
  Alm_data_file->set_forward_callback(out_stream);

  Monitoring_data->set_soc_handle(Batt_soc);
  Monitoring_data->set_state_handle(Battery_status);
  Monitoring_data->register_observer(Batt_hist_data_store);
  Monitoring_data->register_observer(Alarm);
  Monitoring_data->register_observer(Train_data);

  Alarm->register_observer(Alarm_store);
  Alarm->register_observer(alarm_state);
  Alarm->register_observer(Train_data);

  Batt_soc->set_cap_store_callback(batt_cap_store);
}

void Usb_connected_process(void)
{
  if (!Usb_debug_mode)
  {
    Usb_debug_mode = true;
    xTimerStop(Cell_comm_timer_handle, 0);
#if USE_MVB
    vTaskSuspend(Mvb_process_handle);
#endif

#if USE_ETH
    vTaskSuspend(Eth_init_handle);
    vTaskSuspend(Eth_process_handle);
    vTaskSuspend(Eth_rev_handle);
#endif
    HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_SET);
  }
}

void Usb_disconnected_process(void)
{
  if (Usb_debug_mode)
  {
    Usb_debug_mode = false;
    xTimerStart(Cell_comm_timer_handle, 0);
#if USE_MVB
    vTaskResume(Mvb_init_handle);
#endif

#if USE_ETH
    vTaskResume(Eth_init_handle);
#endif
    HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_RESET);
  }
}

void Batt_data_obs_proc(void *pvParameters)
{
  Queue_msg msg;

  while (1)
  {
    if (xQueueReceive(Batt_data_obs_queue, &msg, portMAX_DELAY))
    {
      switch (msg)
      {
      case QM_HIST_DATA_STORE:
        taskENTER_CRITICAL();
        Batt_hist_data_store->store_data();

        // discharged capacity store
        Discharge_soc_record->store_discharged_cap();
        taskEXIT_CRITICAL();
        break;
      case QM_ALM_CHK:
        Alarm->alarm_check();
        break;
      // upload to train data update
      case QM_UPLOAD_DATA_UPDATE:
        Train_data->update_batt_data();
        break;
      default:
        break;
      }
    }
  }
}

void Alarm_obs_proc(void *pvParameters)
{
  Queue_msg msg;

  while (1)
  {
    if (xQueueReceive(Alarm_obs_queue, &msg, portMAX_DELAY))
    {
      switch (msg)
      {
      // alarm data store
      case QM_ALM_DATA_STORE:
        taskENTER_CRITICAL();
#if S07T
         Batt_hist_data_store->store_data();  //S07T项目 有故障时存一次数据 与5分钟存数据共存
#endif
        Alarm_store->store_data();
        taskEXIT_CRITICAL();
        break;
      // upload to train alarm data update
      case QM_UPLOAD_ALM_DATA_UPDATE:
        Train_data->update_alarm_data();
        break;
      default:
        break;
      }
    }
  }
}

void Data_acq(void *pvParameters)
{
  float *total_volt_cur = NULL;
  float *pt1000_temp = NULL;
  portTickType last_waketime  = 0;
  unsigned short eth_data_update_time = 0;
  bool fail_by_usb_mode = false;
  while (1)
  { 
    //2路温度
    pt1000_temp = Pt1000_adc->get_eng_data(); 
      
    //1路总电压,2路总电路  
    total_volt_cur = tb_adc->get_eng_data();
      
    //数据填充更新
    Batt_data_buff.total_data.total_volt = total_volt_cur[0];
    Batt_data_buff.total_data.total_cur[0] = total_volt_cur[1];
    Batt_data_buff.total_data.total_cur[1] = total_volt_cur[2];
    Batt_data_buff.total_data.avg_curr = (total_volt_cur[1] + total_volt_cur[2]) / CUR_CH_CNT;
    Batt_data_buff.total_data.temp[0] = pt1000_temp[0];    
    Batt_data_buff.total_data.temp[1] = pt1000_temp[1];
      
    //SOH填充更新  
    Batt_data_buff.soh = Soh_record.soh;
      
    //LED Flash.
    acquire_cnt++;
    if (acquire_cnt >= Led_flash_delay_max)
    {
      acquire_cnt = 0;
      HAL_GPIO_TogglePin(LED_RUN_GPIO_Port, LED_RUN_Pin);

      //如果当前有告警状态,则闪烁告警等
      if (alarm_state->get_alarm_state())
      {
        HAL_GPIO_TogglePin(LED_FAULT_GPIO_Port, LED_FAULT_Pin);
      }
      else
      {
        HAL_GPIO_WritePin(LED_FAULT_GPIO_Port, LED_FAULT_Pin, GPIO_PIN_RESET);
      }
    }
    
    //USB连接
    if(Usb_debug_mode)
    {
      fail_by_usb_mode = true;
      complex_state.set(POWER_ON_CHECK_SELF_FAIL);
      complex_state.reset(POWER_ON_START_CHECK_SELF);
      complex_state.reset(POWER_ON_CHECK_SELF_SUC);
#if S07S
      complex_state.reset(POWER_ON_CHECK_SELF_END);
#endif
      HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
    }
    else
    {
      if(fail_by_usb_mode)
      {
        fail_by_usb_mode = false;
        complex_state.reset(POWER_ON_CHECK_SELF_FAIL);
      }
      HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
    }

    // only update total battery data
    Monitoring_data->set_data(&Batt_data_buff, false);
    eth_data_update_time++;
    if(eth_data_update_time % 5 == 0 && Data_ready)
    {
      eth_data_update_time = 0;
      Train_data->update(&Batt_data_buff, true);
    }
    vTaskDelayUntil(&last_waketime, SECONDS_TO_MILLISECONDS(User_paras.period.acquire));
  }
}

void Soh_update_process(void *pvParameters)
{
  while (1)
  {
    if(Rtc->get_ts() < Soh_record.last_update_ts)
    {
      Soh_record.last_update_ts = Rtc->get_ts();
      Soh_record.soh = Data_buff.batt_data.soh;
      Soh_record_file->write(&Soh_record);
    }
    else if(Rtc->get_ts() > Soh_record.last_update_ts + MONTH_TO_SECONDS(1))
    {
      Soh_record.last_update_ts = Rtc->get_ts();
      Soh_record.soh -= SOH_ATTENUATION_VALUE_PER_MONTH;
      Soh_record_file->write(&Soh_record);
    }
    Batt_data_buff.soh = Soh_record.soh;
    DELAY_MS(SOH_UPDATE_DELAY);    
  }
}

void Cell_comm_process(void *pvParameters)
{
  int ret_len = 0;
  unsigned short recvbuff[300] = {0};
  Modbus_data reg_info = {0};
  // delay for USB CDC ready
  vTaskDelay(2000);
  while (1)
  {
    // enable cell power
    HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_SET);
    vTaskDelay(CELL_POWERUP_DELAY);
    memset(Batt_data_buff.cell_data,0,sizeof(Batt_data_buff.cell_data));
    
    //轮流读取总线上挂载的采集板的数据
    for (int i = 0; i < CELL_CNT; i++)
    {
      Batt_data_buff.cell_data[i].id = i + 1;
      memset(recvbuff, 0, sizeof(recvbuff));
      //采集板的Id  
      reg_info.id = i + 1; 
      //读命令
      reg_info.cmd = 0x04;
      //要读取的采集板ADC的通道数目  
      reg_info.reg_cnt = ACQ_MAX_CNT; 
      //起始寄存器地址
      reg_info.reg_addr = REG_ADDR_CH_DROP_VALUE_START;
      //modbus 协议通讯
      ret_len = Comm_cell_modbuse->read_reg(&reg_info, recvbuff);
      //通讯成功,填充数据
      if (ret_len > 0)
      {
        memcpy(&Batt_data_buff.cell_data[i].acq_val, recvbuff, sizeof(Batt_data_buff.cell_data[i].acq_val));
      }
      ret_len = 0;
      if(is_first)
      {
        //如果第一次读取，则获取采集板的配置信息
        reg_info.cmd = 0x03;
        reg_info.reg_cnt = (ACQ_MAX_CNT  / 2) * CH_CALIB_CONFIG_CNT_PER;
        reg_info.reg_addr = REG_ADDR_CH_ENABEL_START;
        ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
        reg_info.reg_cnt = (ACQ_MAX_CNT  / 2 + ACQ_MAX_CNT  % 2) * CH_CALIB_CONFIG_CNT_PER;
        reg_info.reg_addr = REG_ADDR_CH_ENABEL_START + (ACQ_MAX_CNT  / 2) * CH_CALIB_CONFIG_CNT_PER;
        ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
        if (ret_len  == ACQ_MAX_CNT * CH_CALIB_CONFIG_CNT_PER)
        {
          is_first = false;
          for(int j = 0; j < ACQ_MAX_CNT; j++)
          {
            Cell_adc_config_paras[j].is_enable = recvbuff[0 + CH_CALIB_CONFIG_CNT_PER * j];
            Cell_adc_config_paras[j].acq_mode = (Adc_acq_mode_e)recvbuff[1 + CH_CALIB_CONFIG_CNT_PER * j];
            Cell_adc_config_paras[j].acq_type = (Adc_acq_type_e)recvbuff[2 + CH_CALIB_CONFIG_CNT_PER * j];
          }
          //计算电压通道数据和温度通道数
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
          //更新采集器的配置文件
          Dev_para_file->write(&Dev_paras);
          Cell_config_para_file->write(&Cell_adc_config_paras);
        }
      }
      unsigned char cnt = 3;
      while(cnt)
      {
        cnt--;
        HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
        DELAY_MS(100);
      }
    }

    //如果USB有读取指令，则向USB发送消息
    if (Cell_comm_cpl_queue != NULL)
    {
      char msg = 'c';
      xQueueOverwrite(Cell_comm_cpl_queue, &msg);
    }

    //Train_data->reset();

    Data_ready = true;
    Monitoring_data->set_data(&Batt_data_buff, !Usb_debug_mode);

    // disable cell power  USB connet task higher comm
    if (!Usb_debug_mode)
    {
      HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
    }

    //在定时器中被定时唤醒。
    vTaskSuspend(Cell_comm_handle);
  }
}



void Batt_cap_update(void *pvParameters)
{
  portTickType last_waketime = 0;
  Batt_info cap_para;
  float multiple = 2.6;
#if S07R
  multiple = 1.8;
#endif
  while (1)
  {
    if (!Usb_debug_mode)
    {
      cap_para.volt = Batt_data_buff.total_data.total_volt;
      cap_para.cur = Batt_data_buff.total_data.total_cur[0] / multiple;
      cap_para.temp = Batt_data_buff.total_data.amb_temp;
      Batt_soc->update_cap(cap_para);
      if (Batt_data_buff.state != DISCHARGE)
      {
          if ((Discharge_soc_record != NULL) && (Variable_charge_effi_method != NULL))
          {
            Variable_charge_effi_method->set_discharged_cap(Discharge_soc_record->get_discharged_cap());
          }
     }
     vTaskDelayUntil(&last_waketime, BATT_CAP_CALC_PERIOD_MS);
   }
  }
}

void uart_rev_callback(UART_HandleTypeDef *uart_handle)
{
  char msg = 'u';
  BaseType_t xHigherPriorityTaskWoken = pdTRUE;

  if (uart_handle == Cell_node_uart)
  {
    //    if (Cell_comm_queue != NULL)
    //    {
    //      xQueueOverwriteFromISR(Cell_comm_queue, &msg, &xHigherPriorityTaskWoken);
    //    }
  }
  else if (uart_handle == Eth_uart)
  {
    if (Eth_comm_queue != NULL)
    {
      xQueueOverwriteFromISR(Eth_comm_queue, &msg, &xHigherPriorityTaskWoken);
    }
  }

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

#if USE_MVB
void Mvb_init(void *pvParameters)
{
  vTaskSuspend(Mvb_process_handle);

  while (1)
  {
    //__HAL_UART_DISABLE_IT(Mvb_uart, UART_IT_RXNE);

    Mvb->reset();

    //__HAL_UART_ENABLE_IT(Mvb_uart, UART_IT_RXNE);

    if (Mvb->config(&Dev_paras.mvb[Mvb_port_idx]))
    {
      vTaskResume(Mvb_process_handle);
      vTaskSuspend(Mvb_init_handle);
    }
    vTaskDelay(5000);
  }
}

void Mvb_process(void *pvParameters)
{
  unsigned int send_len = 0;
    
  unsigned short datetime_addr = (Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[0] << 8) | Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[1];
 
  unsigned short vital_addr = (Dev_paras.mvb[Mvb_port_idx].src_port[1].addr[0] << 8) | Dev_paras.mvb[Mvb_port_idx].src_port[1].addr[1];
  
  while (1)
  {
    //send_len = Train_data->get_mvb_update_buff(Mvb_send_buff);
      
    if (send_len > 0)
    {
      // send mvb data
      Train_mvb->send_msg(Mvb_send_buff, send_len);

      // handle date & time from tcms
      Train_mvb->handle_rec_msg(datetime_addr);

      // handle vital from tcms
      Train_mvb->handle_rec_msg(vital_addr);
    }
    vTaskDelay(3000);
  }
}
#endif

#if USE_ETH
void Eth_init(void *pvParameters)
{
  vTaskSuspend(Eth_process_handle);
  vTaskSuspend(Eth_rev_handle);

  while (1)
  {
    if(Trdp->init())
    {
      vTaskResume(Eth_process_handle);
      vTaskResume(Eth_rev_handle);
      vTaskSuspend(Eth_init_handle);
    }
    vTaskDelay(5000);
  }
}


void eth_sendbytes(uint8_t *pdata,uint16_t length) {
    if(Trdp != NULL) {
        Trdp->trdp_pd_tx_handle(0,50000,pdata,length);
    } 
}

void bat_infor_print(DEBUG_COMM_TYPE_t commType) {
	debug_printf(commType,"-----bat infor-----\r\n");
    debug_printf(commType,(char *)"总电压:%.3f,总电流[1]:%.3f,总电流[2]:%.3f\r\n",\
										Batt_data_buff.total_data.total_volt,\
										Batt_data_buff.total_data.total_cur[0],\
										Batt_data_buff.total_data.total_cur[1]);
	for(int i=0;i<COUNT_OF_TEMP;i++) {
		debug_printf(commType, "温度[%d]:%.3f",i,Batt_data_buff.total_data.temp[i]);
	}
	debug_printf(commType, "\r\n");

	debug_printf(commType, "SOC:d,SOH:%d\r\n",Batt_data_buff.soc,Batt_data_buff.soh);

	switch(Batt_data_buff.state) {
	case FAST_CHARGE:
		debug_printf(commType, "快充中\r\n");
		break;
	case DISCHARGE:
		debug_printf(commType, "放电中\r\n");
		break;
	case FLOAT_CHARGE:
		debug_printf(commType, "浮充中\r\n");
		break;
	default:
		break;
	}

	for(int i=0;i<CELL_CNT;i++) {
		debug_printf(commType,"采集器[%d] Id:%d\r\n",Batt_data_buff.cell_data[i].id);
		for(int j=0;j<ACQ_MAX_CNT;j++) {
			debug_printf(commType,"通道[%d] Value:%d",j,Batt_data_buff.cell_data[i].acq_val[j]);
		}
	}
	
	debug_printf(commType, "\r\n");

	

	
}


bool recv_over = true;
void Eth_process(void *pvParameters)
{
  unsigned int send_len = 0;
  unsigned char send_delay = 100;
  while (1)
  {
    // send eth data
    if (Data_ready)
    {
      memset(Eth_send_buff, 0, sizeof(Eth_send_buff));
      send_len = Train_data->get_eth_update_buff(Eth_send_buff);
      for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
      {
        while(send_delay-- && !recv_over)
        {
            DELAY_MS(1);
        }
        
        if(recv_over)
        {
            Trdp->send_data(i, Eth_send_buff, send_len);
        }
      }
    }
    vTaskDelay(500);
  }
}

bool set_date_time(unsigned  char * eth_recv_buff)
{
  Rtc_t date_time;
  if((eth_recv_buff[TIME_JUDGED_AVAILIBEL_OFFSET] & TIME_SET_AVAILIBLE) == TIME_SET_AVAILIBLE)
  {
    date_time.date.year = eth_recv_buff[YEAR_OFFSET];
    date_time.date.month = eth_recv_buff[MONTH_OFFSET];
    date_time.date.date = eth_recv_buff[DAY_OFFSET];
    date_time.time.hours = eth_recv_buff[HOUR_OFFSET];
    date_time.time.minutes = eth_recv_buff[MINUTE_OFFSET];
    date_time.time.seconds = eth_recv_buff[SECOND_OFFSET];
    if(Rtc->set_datetime(&date_time))
    {
      return true;
    }
  }  
  return false;
}

unsigned char recv_buff[TRDP_RECV_BUFF_SIZE];
unsigned short len = 0;
void Eth_rev_data(void *pvParameters)
{
  unsigned char data = 0;
  while (1)
  {
    if (xQueueReceive(Eth_comm_queue, &data, portMAX_DELAY))
    {
      if (data == 'u')
      {
        recv_over  = false;
        memset(recv_buff, 0, sizeof(recv_buff));
        len = Trdp->trdp_rx_handle(recv_buff);//Trdp->recieve_data(recv_buff, TRDP_COMMNET_MSG_FIX_SIZE);
        recv_over  = true;
        if(len  > 0)
        {
            int index = 0;
            switch(recv_buff[index++]) {
              case 0x07://pd module one
              case 0x87://pd module two 
                  {
                       index += 2;//data length
                       index += 4;//SequenceCounter
                       index += 2;//ProtocolVersion
                      
                       uint32_t commId = (int32_t)recv_buff[index + 0] << 24 | \
                                         (int32_t)recv_buff[index + 1] << 16 | \
                                         (int16_t)recv_buff[index + 2] << 8  |\
                                         recv_buff[index + 3]; 
                      index += 4;
                      index += 4;//etbTopoCnt
                      index += 4;//opTrnTopoCnt
                      
                      uint32_t app_data_length = (int32_t)recv_buff[index + 0] << 24 | \
                                                 (int32_t)recv_buff[index + 1] << 16 | \
                                                 (int16_t)recv_buff[index + 2] << 8  | \
                                                          recv_buff[index + 3];
                      index += 4;
                      if(app_data_length > len - index) {
                          break;
                      }
                      switch(commId) {
                          case 20000://
                          case 10000://
                              {
                                  index += 7;
                                  if((recv_buff[index++] & 0x03) == 0x03) {
                                    Rtc_t date_time;
                                    date_time.date.year = recv_buff[index++];
                                    date_time.date.month = recv_buff[index++];
                                    date_time.date.date = recv_buff[index++];
                                    date_time.time.hours = recv_buff[index++];
                                    date_time.time.minutes = recv_buff[index++];
                                    date_time.time.seconds = recv_buff[index++];
                                    Rtc->set_datetime(&date_time);
                                  }
                              }
                              break;
                          
                          case 20001:
                              commandHandle(DEBUG_COMM_ETH,(char *)recv_buff+index,NULL);
                              break;
                          
                      }
                  }
                  break;

              default:
                  break;
            }
            Trdp->delete_recv_buff();
            //HAL_NVIC_DisableIRQ(UART5_IRQn);
            //vTaskSuspend(Eth_rev_handle);
#if 0
           if(set_date_time(recv_buff))
           {
              Trdp->delete_recv_buff();
              HAL_NVIC_DisableIRQ(UART5_IRQn);
              vTaskSuspend(Eth_rev_handle);
           }
#endif
        }
      }
    }
    DELAY_MS(2000);
  }
}
#endif

// callback function implement here
// file forward call back function
UINT out_stream(const BYTE *p, UINT btf)
{
  unsigned int cnt = 0;

  if (btf == 0)
  {
    // Sense call
    // Return stream status (0: Busy, 1: Ready)
    cnt = 1;
  }
  else
  {    // Transfer call
    do // Repeat while there is any data to be sent and the stream is ready
    {
      Host_comm->forward(*(unsigned char *)p++);
      cnt++;
    } while (cnt < btf);
  }

  return cnt;
}

void cell_comm_timer_callback(TimerHandle_t xTimer)
{
  vTaskResume(Cell_comm_handle);
}

bool batt_cap_store(float cap_rate)
{
  Batt_data_buff.soc = cap_rate;
  Batt_hist_data_store->update(&Batt_data_buff, 1);

  return true;
}

bool batt_init_flag_store(bool flag)
{
  Dev_paras.soc_init = flag;

  return Dev_para_file->write(&Dev_paras);
}

bool batt_discharged_cap_store(float cap)
{
  if (Discharged_cap_file != NULL)
  {
    return Discharged_cap_file->write(&cap);
  }
  else
  {
    return false;
  }
}
