#include "proj_tasks.h"
#include "cmsis_os.h"
#include "defines.h"
#include "class_init.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "proj_paras.h"
#include "debug.h"
#include "mem_malloc.h"
#include "de_protocol.h"
#include "trdp_data.h"
#include "crc32.h"
#include "iap.h"

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
uint8_t paras_reload = false;
#define QUEUE_SEND_TIMEOUT (100)
#define TRDP_RECV_BUFF_SIZE   (1600)
#define TRDP_COMMNET_MSG_FIX_SIZE   (124)
#define CELL_POWERUP_DELAY (3000)

// data acquire, include adc data and contactor detect
TaskHandle_t Data_acq_handle = NULL;
void Data_acq(void *pvParameters);

TaskHandle_t Cell_comm_handle = NULL;
void Cell_comm_process(void *pvParameters);

TaskHandle_t Cell_comm_rx_handle = NULL;
void Cell_comm_rx_process(void *pvParameters);
static bool cellRequsetTransfer = false; 

TaskHandle_t Soh_update_handle = NULL;
void Soh_update_process(void *pvParameters);

#if USE_MVB
TaskHandle_t Mvb_init_handle = NULL;
void Mvb_init(void *pvParameters);
TaskHandle_t Mvb_process_handle = NULL;
TaskHandle_t Mvb_rx_handle = NULL;
void Mvb_process(void *pvParameters);
void Mvb_rx_process(void *pvParameters);
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


TaskHandle_t get_logger_handle = NULL;
void get_logger_process(void *pvParameters);

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

bool Usb_debug_mode = false;//true;
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
  xTaskCreate(Cell_comm_process, "Cell_comm", 512, NULL, TASK_PRIORITY_MAX - 2, &Cell_comm_handle);
  task_create_ok = task_create_ok && (Cell_comm_handle != NULL);
    
  xTaskCreate(Cell_comm_rx_process, "Cell_comm_rx", 512, NULL, TASK_PRIORITY_MAX - 2, &Cell_comm_rx_handle);
  task_create_ok = task_create_ok && (Cell_comm_rx_handle != NULL);
  
  xTaskCreate(Soh_update_process, "Soh_update", 512, NULL, TASK_PRIORITY_MAX - 4, &Soh_update_handle);
  task_create_ok = task_create_ok && (Soh_update_handle != NULL);
#if USE_MVB
  // MVB init
  xTaskCreate(Mvb_init, "Mvb_init", 512, NULL, TASK_PRIORITY_MAX - 3, &Mvb_init_handle);
  task_create_ok = task_create_ok && (Mvb_init_handle != NULL);

  xTaskCreate(Mvb_process, "Mvb_process", 512, NULL, TASK_PRIORITY_MAX - 4, &Mvb_process_handle);
  task_create_ok = task_create_ok && (Mvb_process_handle != NULL);
    
  xTaskCreate(Mvb_rx_process, "Mvb_rx_thread", 512, NULL, TASK_PRIORITY_MAX - 4, &Mvb_rx_handle);
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
  
  xTaskCreate(get_logger_process, "get_logger", 1024, NULL, TASK_PRIORITY_MAX - 3, &get_logger_handle);
  task_create_ok = task_create_ok && (get_logger_handle != NULL);
  
#endif

  xTaskCreate(Batt_data_obs_proc, "Batt_data_obs_proc", 1024, NULL, TASK_PRIORITY_MAX - 3, &Batt_data_obs_process_handle);
  task_create_ok = task_create_ok && (Batt_data_obs_process_handle != NULL);

  xTaskCreate(Alarm_obs_proc, "Alarm_obs_proc", 512, NULL, TASK_PRIORITY_MAX - 1, &Alm_obs_process_handle);
  task_create_ok = task_create_ok && (Alm_obs_process_handle != NULL);

  xTaskCreate(Batt_cap_update, "Battery_capacity_update", 512, NULL, TASK_PRIORITY_MAX - 1, &Batt_cap_update_handle);
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
  if(Eth_train_idx > 1) {
    Eth_train_idx = 0;
  }
  Mvb_port_idx = Eth_train_idx;

  
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
  //xTimerStart(Cell_comm_timer_handle, 0);

  Batt_data_obs_queue = xQueueCreate(QM_CNT_MAX, sizeof(Queue_msg));
  Alarm_obs_queue = xQueueCreate(QM_CNT_MAX, sizeof(Queue_msg));

  Batt_hist_data_store->set_store_interval(User_paras.period.store / User_paras.period.cell_comm);
  
  // for test
  //Batt_hist_data_store->set_store_interval(1);

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
    //xTimerStop(Cell_comm_timer_handle, 0);
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
    
  osDelay(15000);
    
    while(Batt_data_obs_queue == NULL) {
        osDelay(100);
    }

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
  osDelay(15000);
    
    while(Alarm_obs_queue == NULL) {
        osDelay(100);
    }
    
  xTimerStart(Cell_comm_timer_handle, 0);
    
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
    
  osDelay(15000);

  
    
  while (1)
  { 
     vTaskDelayUntil(&last_waketime, SECONDS_TO_MILLISECONDS(User_paras.period.acquire));
      
      if(Pt1000_adc == NULL || tb_adc == NULL) {
          continue;
      }
    //2路温度
    pt1000_temp = Pt1000_adc->get_eng_data(); 
      
    //1路总电压,2路总电路  
    total_volt_cur = tb_adc->get_eng_data();
      
    if(total_volt_cur[0] < 0) {
        total_volt_cur[0] = 0;
    }
    //数据填充更新
    Batt_data_buff.total_data.total_volt = total_volt_cur[0];
    Batt_data_buff.total_data.total_cur[0] = total_volt_cur[1];
    Batt_data_buff.total_data.total_cur[1] = total_volt_cur[2];
    Batt_data_buff.total_data.avg_curr = total_volt_cur[1];
    Batt_data_buff.total_data.temp[0] = pt1000_temp[0];    
    Batt_data_buff.total_data.temp[1] = pt1000_temp[1];
      
    //SOH填充更新  
    Batt_data_buff.soh = Soh_record.soh < 0 ? 0 : Soh_record.soh; 
      
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
   

    // only update total battery data
    Monitoring_data->set_data(&Batt_data_buff, false);
    eth_data_update_time++;
    if(eth_data_update_time % 5 == 0 && Data_ready)
    {
      eth_data_update_time = 0;
      Train_data->update(&Batt_data_buff, true);
    }
    
    
    
  }
}

void Soh_update_process(void *pvParameters)
{
  osDelay(15000);
  
  
  while (1)
  {
      
    if(Rtc == NULL || Soh_record_file == NULL) {
       osDelay(1000);
       continue;
    }
    
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
    Batt_data_buff.soh = Soh_record.soh < 0 ? 0 : Soh_record.soh;                                     
    paraNoInitSave();
    
    DELAY_MS(SOH_UPDATE_DELAY);
        
  }
}

extern "C" errStatus_t cell_module_query_status(uint8_t id,uint8_t query_what);
#if 1
extern "C" void de_protocol_master_process(COMM_TYPE_t type,uint8_t *pdate,uint16_t length);
ProtocolMsg_t protocolRxMsg = {0};
void Cell_comm_rx_process(void *pvParameters) {
    
    while(1) {
        
        osDelay(PROTOCOL_TIME_OUT);

        if(protocolRxMsg.length > 0 && osKernelSysTick() > protocolRxMsg.tick) {
            
            if(cellRequsetTransfer) {
                cellRequsetTransfer = false;
                eth_sendbytes(protocolRxMsg.buffer,protocolRxMsg.length);
            } else {
                de_protocol_master_process(COMM_TYPE_485,protocolRxMsg.buffer,protocolRxMsg.length);
            }
            memset((void *)&protocolRxMsg,0,sizeof(protocolRxMsg));
        }
    }
}
#endif

uint16_t get_alarm_his_data_one(uint8_t type,
                                uint8_t lvl,
                                uint32_t start_time,
                                uint32_t end_time,
                                uint32_t *offset,
                                uint16_t count,
                                uint8_t *p) {
    
    FIL fp;
    
    UINT bytes_read;
    
    *offset = 0; 
    
    uint16_t index = 0;
                                    
    uint8_t valid_count = 0;
    
    if (f_open(&fp, "alm_data.txt", FA_READ | FA_OPEN_EXISTING ) != FR_OK)
    {
        return 0;
    }
    
    Alarm_store_data_t alarmInfor;
    
    if (f_lseek(&fp, sizeof(File_header)) != FR_OK)
    {
        f_close(&fp);
        return 0;
    }

	*offset = sizeof(File_header);
  	FI_Conv_t conv;
    while(1) {
        if(f_read(&fp,(void *)&alarmInfor,sizeof(Alarm_store_data_t),&bytes_read) != FR_OK) {
            break;
        }

		if(bytes_read < sizeof(Alarm_store_data_t)) {
            *offset = 0;
            break;
        }

		*offset += bytes_read;
        
        if(type != 0xff && type != alarmInfor.alm_code) {
            osDelay(1);
            continue;
        }
        
        if(lvl != 0xff && lvl != alarmInfor.alm_lvl) {
            osDelay(1);
            continue;
        }
        
        if(start_time != 0 || end_time != 0) {
            if(!(alarmInfor.ts >= start_time && alarmInfor.ts <= end_time)) {
                osDelay(1);
                continue;
            }
        }
		
        p[index++] = 0x01;//dataid

		p[index++] = alarmInfor.ts >> 24;
		p[index++] = alarmInfor.ts >> 16;
		p[index++] = alarmInfor.ts >> 8;
		p[index++] = alarmInfor.ts ;

		p[index++] = alarmInfor.alm_status;

		p[index++] = alarmInfor.alm_code;

		p[index++] = alarmInfor.alm_lvl;

		
		conv.f = alarmInfor.total_data.total_volt;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.total_cur[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.total_cur[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.temp[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.temp[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.soc;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.soh;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		p[index++] = alarmInfor.state;

		p[index++] = alarmInfor.cell_data.id;

		for(int i=0;i<ACQ_MAX_CNT;i++) {
			p[index++] = alarmInfor.cell_data.acq_val[i] >> 8;
			p[index++] = alarmInfor.cell_data.acq_val[i];
		}
        
        valid_count++;
        
        if(valid_count >= count) {
            break;
        }
    }
    
    f_close(&fp);
	
    return index;
}
                     
static uint8_t logger_ack_msgid = 0xFF;
static uint8_t logger_tag = 0xFF;
bool logger_set_ack(uint8_t msgId,uint8_t tag) {
    logger_ack_msgid = (msgId & 0x3F);
    logger_tag = tag;
    return true;
}
            
bool logger_wait_ack(int timeout,uint8_t msgId) {
    bool ret = false;

    while(timeout >= 0) {
        osDelay(50);
        timeout -= 50;
        
        if(msgId == logger_ack_msgid && logger_tag == TAG_Logger) {
            ret = true;
            break;
        }
    }
    
    return ret;
}

uint16_t  get_logger_his_data_all(
                                uint32_t start_time,
                                uint32_t end_time,
                                uint32_t *offset) {
    #define TRDP_FRAME_DELAY 10
                                    
    uint8_t msgId = 0;      
                                    
    FIL fp;
    
    UINT bytes_read;

    uint16_t index = 0;
                                    
    uint8_t valid_count = 0;
                                    
    uint8_t *p = (uint8_t *)sys_malloc(8 * sizeof(History_data_t) + 4);
    if(p == NULL) {
        return 0;
    }                              

    if (f_open(&fp, HISTORY_DATA_FILE_NAME, FA_READ | FA_OPEN_EXISTING ) != FR_OK)
    {
        sys_free(p);
        return 0;
    }
    
    History_data_t infor;
    
    if (f_lseek(&fp, *offset) != FR_OK)
    {
        f_close(&fp);
        sys_free(p);
        return 0;
    }

  	FI_Conv_t conv;
    
    //osDelay(150);
    
    while(1) {
        
#if (USE_IWDG)
        extern  IWDG_HandleTypeDef hiwdg;
        HAL_IWDG_Refresh(&hiwdg);
#endif
        if(f_read(&fp,(void *)&infor,sizeof(History_data_t),&bytes_read) != FR_OK) {
            break;
        }

		if(bytes_read < sizeof(History_data_t)) {

            uint8_t *txbuf = (uint8_t *)sys_malloc(index + 24);
            if(txbuf == NULL) {
                f_close(&fp);
                sys_free(p);
                return index;
            }
            uint16_t send_length = de_protocol_slave_package_fill(txbuf,
											    CTRL_Response,
			                                    Sys_paras.dev_id,
												0,
												SER_EOF | (++msgId & 0x3F),
												TAG_MASK_Logger,
												p,
												index);

            if(send_length > 0) {
                protocol_send_bytes(COMM_TYPE_ETH,txbuf,send_length);
            }
            
            osDelay(TRDP_FRAME_DELAY);

            sys_free(txbuf);
            f_close(&fp);
            index = 0;
            valid_count = 0;
            return 0;
        }

		*offset += bytes_read;
        
        uint32_t crc_check = CRC_Get32(((const uint8_t *)(&infor)) + 4,sizeof(History_data_t) - 4);
       
        if(crc_check != infor.crc32) {
            osDelay(1);
            continue;
        }

        if(start_time != 0 || end_time != 0) {
            if(!(infor.ts >= start_time && infor.ts <= end_time)) {
                osDelay(1);
                continue;
            }
        }
		
        p[index++] = DataId_Hist_Data;//dataid
		p[index++] = infor.ts >> 24;
		p[index++] = infor.ts >> 16;
		p[index++] = infor.ts >> 8;
		p[index++] = infor.ts ;

		
		conv.f = infor.batt_data.total_data.total_volt;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.total_data.total_cur[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.total_data.total_cur[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.total_data.temp[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.total_data.temp[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.soc;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = infor.batt_data.soh;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		p[index++] = infor.batt_data.state;

        for(int cell = 0;cell < CELL_CNT;cell++) {
            p[index++] = infor.batt_data.cell_data[cell].id;

            for(int i=0;i<ACQ_MAX_CNT;i++) {
                p[index++] = infor.batt_data.cell_data[cell].acq_val[i] >> 8;
                p[index++] = infor.batt_data.cell_data[cell].acq_val[i];
            }
        }
		
        
        valid_count++;
        
        if(valid_count >= 8) {

            uint8_t *txbuf = (uint8_t *)sys_malloc(index + 24);
            if(txbuf == NULL) {
                f_close(&fp);
                sys_free(p);
                return index;
            }
            
          uint16_t send_length = de_protocol_slave_package_fill(txbuf,
                                            CTRL_Request,
                                            Sys_paras.dev_id,
                                            0,
                                            /*SER_EOF | SER_SOF | */(++msgId & 0x3F),
                                            TAG_MASK_Logger,
                                            p,
                                            index);

            if(send_length > 0) {
                protocol_send_bytes(COMM_TYPE_ETH,txbuf,send_length);
            }
            

            osDelay(TRDP_FRAME_DELAY);

            sys_free(txbuf);
            
            index = 0;
            valid_count = 0;
        }
        
       
    }
    
    f_close(&fp);
	sys_free(p);
    return index;
}
                                
uint16_t  get_alarm_his_data_all(uint8_t type,
                                uint8_t lvl,
                                uint32_t start_time,
                                uint32_t end_time,
                                uint32_t *offset) {
    #define TRDP_FRAME_DELAY 10
    uint8_t msgId = 0;      
                                    
    FIL fp;
    
    UINT bytes_read;

    uint16_t index = 0;
                                    
    uint8_t valid_count = 0;
                                    
    uint8_t *p = (uint8_t *)sys_malloc(10 * sizeof(Alarm_store_data_t) + 4);
    if(p == NULL) {
        return 0;
    }                              
                                    
    
    if (f_open(&fp, "alm_data.txt", FA_READ | FA_OPEN_EXISTING ) != FR_OK)
    {
        sys_free(p);
        return 0;
    }
    
    Alarm_store_data_t alarmInfor;
    
    if (f_lseek(&fp, *offset) != FR_OK)
    {
        f_close(&fp);
        sys_free(p);
        return 0;
    }

  	FI_Conv_t conv;
    
    //osDelay(150);
    
    while(1) {
        
#if (USE_IWDG)
        extern  IWDG_HandleTypeDef hiwdg;
        HAL_IWDG_Refresh(&hiwdg);
#endif
        
        if(f_read(&fp,(void *)&alarmInfor,sizeof(Alarm_store_data_t),&bytes_read) != FR_OK) {
            break;
        }

		if(bytes_read < sizeof(Alarm_store_data_t)) {

            uint8_t *txbuf = (uint8_t *)sys_malloc(index + 24);
            if(txbuf == NULL) {
                f_close(&fp);
                sys_free(p);
                return index;
            }
            uint16_t send_length = de_protocol_slave_package_fill(txbuf,
											    CTRL_Response,
			                                    Sys_paras.dev_id,
												0,
												SER_EOF | (++msgId & 0x3F),
												TAG_MASK_Logger,
												p,
												index);
#if 0
            logger_set_ack(0xff,0xff);
            
            for(uint8_t i=0;i<3;i++) {
                if(send_length > 0) {
                    protocol_send_bytes(COMM_TYPE_ETH,txbuf,send_length);
                }
                //char buff[32] = {0};
                //sprintf(buff,"tx times:%d,msgId:d\r\n",i+1,msgId);
                //Bsp_Rs485SendBytes((uint8_t *)buff,strlen(buff));
                
                //if(logger_wait_ack(3000,msgId)) {
                //    break;
                //}
            }
#else
            if(send_length > 0) {
                protocol_send_bytes(COMM_TYPE_ETH,txbuf,send_length);
            }
            
            osDelay(TRDP_FRAME_DELAY);
#endif
             
            
            sys_free(txbuf);
            f_close(&fp);
            index = 0;
            valid_count = 0;
            return 0;
        }

		*offset += bytes_read;
        
        
        uint32_t crc_check = CRC_Get32(((const uint8_t *)(&alarmInfor)) + 4,sizeof(Alarm_store_data_t) - 4);
       
        if(crc_check != alarmInfor.crc32) {
            continue;
        }
        
        if(type != 0xff && type != alarmInfor.alm_code) {
            continue;
        }
        
        if(lvl != 0xff && lvl != alarmInfor.alm_lvl) {
            continue;
        }
        
        if(start_time != 0 || end_time != 0) {
            if(!(alarmInfor.ts >= start_time && alarmInfor.ts <= end_time)) {
                continue;
            }
        }
		
        p[index++] = DataId_Alarm_Data;//dataid
		p[index++] = alarmInfor.ts >> 24;
		p[index++] = alarmInfor.ts >> 16;
		p[index++] = alarmInfor.ts >> 8;
		p[index++] = alarmInfor.ts ;

		p[index++] = alarmInfor.alm_status;

		p[index++] = alarmInfor.alm_code;

		p[index++] = alarmInfor.alm_lvl;

		
		conv.f = alarmInfor.total_data.total_volt;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.total_cur[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.total_cur[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.temp[0];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.total_data.temp[1];
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.soc;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		conv.f = alarmInfor.soh;
		p[index++] = conv.i >> 24;
		p[index++] = conv.i >> 16;
		p[index++] = conv.i >> 8;
		p[index++] = conv.i;

		p[index++] = alarmInfor.state;

		p[index++] = alarmInfor.cell_data.id;

		for(int i=0;i<ACQ_MAX_CNT;i++) {
			p[index++] = alarmInfor.cell_data.acq_val[i] >> 8;
			p[index++] = alarmInfor.cell_data.acq_val[i];
		}
        
        valid_count++;
        
        if(valid_count >= 10) {

            uint8_t *txbuf = (uint8_t *)sys_malloc(index + 24);
            if(txbuf == NULL) {
                f_close(&fp);
                sys_free(p);
                return index;
            }
            
             uint16_t send_length = de_protocol_slave_package_fill(txbuf,
											    CTRL_Request,
			                                    Sys_paras.dev_id,
												0,
												/*SER_EOF | SER_SOF | */(++msgId & 0x3F),
												TAG_MASK_Logger,
												p,
												index);
            
            logger_set_ack(0xff,0xff);
            for(uint8_t trytimes = 0;trytimes < 1;trytimes ++) {
                
                //char buff[64] = {0};
                //sprintf(buff,"tx tick:%08d,tx times:%d,msgId:%02d\r\n",osKernelSysTick(),trytimes+1,msgId);
                //Bsp_Rs485SendBytes((uint8_t *)buff,strlen(buff));
                
                if(send_length > 0) {
                    protocol_send_bytes(COMM_TYPE_ETH,txbuf,send_length);
                }
                
                #if 0
                if(logger_wait_ack(3000,(msgId & 0x3F))) {
                    //sprintf(buff,"rx tick:%08d,tx times:%d,msgId:%02d\r\n",osKernelSysTick(),trytimes+1,msgId);
                    //Bsp_Rs485SendBytes((uint8_t *)buff,strlen(buff));
                    break;
                }
                #else
                osDelay(TRDP_FRAME_DELAY);
                #endif
                

            }
             
            
            sys_free(txbuf);
            
            index = 0;
            valid_count = 0;
        }
        
       
    }
    
    f_close(&fp);
	sys_free(p);
    return index;
}
             


uint16_t get_logger_header(uint8_t dataId,uint8_t *p) {
    uint16_t index = 0;
    File_header header;
    bool ret = true;
    
    File * file_handle = NULL;
    switch(dataId) {
        case DataId_Alarm_Header:
            file_handle = Alm_data_file;
            break;
        case DataId_Hist_Header:
            file_handle = Hist_data_file;
            break;
        default:
            return 0;
    }
    ret = file_handle->read_header(&header);
    if (ret != F_OK)
    {
        return 0;
    }
    uint16_t crc_check;
    crc_check = file_handle->crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));
    //header.crc = Alm_data_file->crc(unsigned char*)&header, sizeof(header) - sizeof(header.crc));//crc->calc((unsigned char*)&header, sizeof(header) - sizeof(header.crc));
    if(crc_check != header.crc) {
    
    }
	
    p[index++] = header.data_idx >> 24;
    p[index++] = header.data_idx >> 16;
    p[index++] = header.data_idx >> 8;
    p[index++] = header.data_idx ;
    
    p[index++] = header.data_cnt >> 24;
    p[index++] = header.data_cnt >> 16;
    p[index++] = header.data_cnt >> 8;
    p[index++] = header.data_cnt ;
    
    p[index++] = header.data_fixed_len >> 24;
    p[index++] = header.data_fixed_len >> 16;
    p[index++] = header.data_fixed_len >> 8;
    p[index++] = header.data_fixed_len ;

    p[index++] = header.data_cnt_max >> 24;
    p[index++] = header.data_cnt_max >> 16;
    p[index++] = header.data_cnt_max >> 8;
    p[index++] = header.data_cnt_max ;
    
    p[index++] = header.data_overwrite;
    
    return index;

}
void LoggerRequest(Logger_Msg_t logger);
uint16_t fill_query_logger(uint8_t which,
                           uint8_t alarm_type,
                           uint8_t alarm_lvl,
                           uint32_t start_time,
                           uint32_t end_time,
                           uint8_t *p) {
    uint16_t index = 0;
    switch(which) {
        case DataId_Alarm_Header: 
        case DataId_Hist_Header:
            {
                p[index++] = which;//data id
                index += get_logger_header(which,p + index);
            }
            break;

        
        case DataId_Alarm_Data:
        case DataId_Hist_Data:
            {
                Logger_Msg_t logger = {0};
                logger.logger_type = which;
                logger.para8_1 = alarm_type;
                logger.para8_2 = alarm_lvl;
                logger.para32_1 = start_time;
                logger.para32_2 = end_time;
                logger.para32_3 = sizeof(File_header);
                
                LoggerRequest(logger);
                
            }
            return 0;
        default:
            break;
    }
    return  index;
}

uint16_t fill_query_status(uint8_t which_one,uint8_t *p) {
    uint16_t index = 0;
    
    uint16_t ext_chans = 0;
    uint16_t inter_chans = 0;
    uint8_t inter_voltage_chans = 0;
    uint8_t inter_temp_chans = 0;
    uint8_t inter_current_chans = 0;
    FI_Conv_t conv;
    
    if(which_one <= CELL_CNT) {

        uint8_t start_cell = 0;
        uint8_t end_cell = CELL_CNT - 1;
        
        if(which_one != 0) {
            start_cell = which_one - 1;
            end_cell = which_one - 1;
        }
        
        for(int cell = start_cell;cell <= end_cell;cell++) {
            inter_chans = 0;
            for(int i=0;i<ACQ_MAX_CNT;i++) {
                if(!Cell_adc_config_paras[i].is_enable) {
                    continue;
                }
                
                p[index++] = 0x01;//data id 
                p[index++] = Cell_adc_config_paras[i].acq_type;
                switch(Cell_adc_config_paras[i].acq_type) {
                    case TYPE_TEMP:
                        inter_temp_chans++;
                        inter_chans = inter_temp_chans;
                        break;
                    case TYPE_VOLT:
                        inter_voltage_chans++;
                        inter_chans = inter_voltage_chans;
                        break;
                    case TYPE_CURRENT:
                        inter_current_chans++;
                        inter_chans = inter_current_chans;
                        break;
                    default:
                        inter_voltage_chans++;
                        inter_chans = inter_voltage_chans;
                        break;
                }
                
                ext_chans++;
                p[index++] = ext_chans >> 8;
                p[index++] = ext_chans;
                
               
                p[index++] = inter_chans >> 8;
                p[index++] = inter_chans;
                
                p[index++] = Batt_data_buff.cell_data[cell].acq_val[i] >> 24;
                p[index++] = Batt_data_buff.cell_data[cell].acq_val[i] >> 16;
                p[index++] = Batt_data_buff.cell_data[cell].acq_val[i] >> 8;
                p[index++] = Batt_data_buff.cell_data[cell].acq_val[i];
                
                FI_Conv_t conv = {0};

                conv.f = cell_data_adc_voltage[cell].acq_val[i];

                
                p[index++] = conv.i >> 24;
                p[index++] = conv.i >> 16;
                p[index++] = conv.i >> 8;
                p[index++] = conv.i;
              
            }
        }
    }
    
    ext_chans = 0;
    inter_chans = 0;
    p[index++] = 0x02;//data id 
    p[index++] = TYPE_VOLT;
    
    ext_chans++;
    p[index++] = ext_chans >> 8;
    p[index++] = ext_chans;
    
    inter_chans++;
    p[index++] = inter_chans >> 8;
    p[index++] = inter_chans;
    
    p[index++] = (int)(Batt_data_buff.total_data.total_volt * 10) >> 24; //0.1V
    p[index++] = (int)(Batt_data_buff.total_data.total_volt * 10) >> 16;
    p[index++] = (int)(Batt_data_buff.total_data.total_volt * 10) >> 8;
    p[index++] = (int)(Batt_data_buff.total_data.total_volt * 10);
    
    conv.f = Batt_data_buff.total_data.total_volt;
    p[index++] = conv.i >> 24; //mA
    p[index++] = conv.i >> 16;
    p[index++] = conv.i >> 8;
    p[index++] = conv.i;
    
    
    p[index++] = 0x02;//data id 
    p[index++] = TYPE_CURRENT;
    
    ext_chans++;
    p[index++] = ext_chans >> 8;
    p[index++] = ext_chans;
    
     
    inter_chans = 1;
    p[index++] = inter_chans >> 8;
    p[index++] = inter_chans;
    inter_chans++;
    
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[0] * 1000) >> 24; //mA
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[0] * 1000) >> 16;
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[0] * 1000) >> 8;
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[0] * 1000);
    
    
   
    conv.f = Batt_data_buff.total_data.total_cur[0];
    p[index++] = conv.i >> 24; //mA
    p[index++] = conv.i >> 16;
    p[index++] = conv.i >> 8;
    p[index++] = conv.i;
    
    
    p[index++] = 0x02;//data id 
    p[index++] = TYPE_CURRENT;
    
    ext_chans++;
    p[index++] = ext_chans >> 8;
    p[index++] = ext_chans;
    
     
    inter_chans = 2;
    p[index++] = inter_chans >> 8;
    p[index++] = inter_chans;
    inter_chans++;
    
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[1] * 1000) >> 24; //mA
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[1] * 1000) >> 16;
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[1] * 1000) >> 8;
    p[index++] = (int)(Batt_data_buff.total_data.total_cur[1] * 1000);
    
    conv.f = Batt_data_buff.total_data.total_cur[1];
    p[index++] = conv.i >> 24; //mA
    p[index++] = conv.i >> 16;
    p[index++] = conv.i >> 8;
    p[index++] = conv.i;
    
    
    p[index++] = 0x03;//data id 
    uint32_t ts = Rtc->get_ts();
    p[index++] = ts >> 24;
    p[index++] = ts >> 16;
    p[index++] = ts >> 8;
    p[index++] = ts;
    
    return index;    
    
    
}

uint16_t fill_query_config(uint8_t *p) {
    int index = 0;
    int temp;
    p[index++] = 0x01;//
    p[index++] = Sys_paras.dev_id >> 24;
    p[index++] = Sys_paras.dev_id >> 16;
    p[index++] = Sys_paras.dev_id >> 8;
    p[index++] = Sys_paras.dev_id;
    
    p[index++] = 0x02;
    p[index++] = Sys_paras.batt_info.line >> 8;
    p[index++] = Sys_paras.batt_info.line;
    
    p[index++] = 0x03;
    p[index++] = ((int)Sys_paras.batt_info.nomial_cap) >> 8;
    p[index++] = ((int)Sys_paras.batt_info.nomial_cap);
    
    p[index++] = 0x04;
    p[index++] = Sys_paras.batt_info.group_cnt >> 8;
    p[index++] = Sys_paras.batt_info.group_cnt;
    
    p[index++] = 0x05;
    p[index++] = (Sys_paras.batt_info.group_volt * 10) >> 8; //0.1V
    p[index++] = Sys_paras.batt_info.group_volt * 10; //0.1V
    
    
    p[index++] = 0x06;
    p[index++] = Sys_paras.ver.MC_HW_major;
    p[index++] = Sys_paras.ver.MC_HW_minjor;
    p[index++] = Sys_paras.ver.MC_HW_revision;
    p[index++] = Sys_paras.ver.MC_SW_major;
    p[index++] = Sys_paras.ver.MC_SW_minjor;
    p[index++] = Sys_paras.ver.MC_SW_revision;
    p[index++] = Sys_paras.ver.MC_EX_SW_major;
    p[index++] = Sys_paras.ver.MC_EX_SW_minjor;
    p[index++] = Sys_paras.ver.MC_EX_SW_revision;
    
    p[index++] = 0x07;
    p[index++] = Sys_paras.ver.node_HW_major;
    p[index++] = Sys_paras.ver.node_HW_minjor;
    p[index++] = Sys_paras.ver.node_HW_revision;
    p[index++] = Sys_paras.ver.node_SW_major;
    p[index++] = Sys_paras.ver.node_SW_minjor;
    p[index++] = Sys_paras.ver.node_SW_revision;
    
    p[index++] = 0x08;
    p[index++] = Dev_paras.soc_init;
    
    p[index++] = 0x09;
    p[index++] = ((int)Dev_paras.soc_actual) >> 8;
    p[index++] = ((int)Dev_paras.soc_actual);
    
    p[index++] = 10;
    p[index++] = Dev_paras.volt_cnt >> 8;
    p[index++] = Dev_paras.volt_cnt;
    
    p[index++] = 11;
    p[index++] = Dev_paras.temp_cnt >> 8;
    p[index++] = Dev_paras.temp_cnt;
    
    p[index++] = 12;
    p[index++] = User_paras.period.acquire >> 8;
    p[index++] = User_paras.period.acquire;
    
    p[index++] = 13;
    p[index++] = User_paras.period.cell_comm >> 8;
    p[index++] = User_paras.period.cell_comm; 

    p[index++] = 14;
    p[index++] = User_paras.period.store >> 8;
    p[index++] = User_paras.period.store; 
    
    temp = (int)(User_paras.batt_state_thr.fast_to_float_thr * 1000);//mA
    p[index++] = 30;
    p[index++] = temp >> 24; //
    p[index++] = temp >> 16; //
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.batt_state_thr.float_to_fast_thr * 1000);
    p[index++] = 31;
    p[index++] = temp >> 24; //
    p[index++] = temp >> 16; //
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.batt_state_thr.charge_to_discharge_thr * 1000);
    p[index++] = 32;
    p[index++] = temp >> 24; //
    p[index++] = temp >> 16; //
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.batt_state_thr.discharge_to_charge_thr * 1000);
    p[index++] = 33;
    p[index++] = temp >> 24; //
    p[index++] = temp >> 16; //
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    
    p[index++] = 40;
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_HI][ALARM_LVL_1] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_HI][ALARM_LVL_2]* 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[TOTAL_VOLT_HI]* 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_LOW][ALARM_LVL_1] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_LOW][ALARM_LVL_2] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[TOTAL_VOLT_LOW] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_DEVIATE_HI][ALARM_LVL_1] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[TOTAL_VOLT_DEVIATE_HI][ALARM_LVL_2] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[TOTAL_VOLT_DEVIATE_HI] * 10);//0.1V
    p[index++] = temp >> 8; //
    p[index++] = temp; //  
    
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_HI][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_HI][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_delays[TOTAL_VOLT_HI]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //  
    
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_LOW][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_LOW][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_delays[TOTAL_VOLT_LOW]);
    p[index++] = temp >> 8; //
    p[index++] = temp; // 
    
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_DEVIATE_HI][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[TOTAL_VOLT_DEVIATE_HI][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_delays[TOTAL_VOLT_DEVIATE_HI]);
    p[index++] = temp >> 8; //
    p[index++] = temp; // 
    
    
    p[index++] = 41;
    temp = (int)User_paras.alm_thr.trigger_thress[TEMP_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[TEMP_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[TEMP_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)User_paras.alm_thr.trigger_delays[TEMP_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[TEMP_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[TEMP_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    p[index++] = 42;
    temp = (int)User_paras.alm_thr.trigger_thress[CHARGE_CUR_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[CHARGE_CUR_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[CHARGE_CUR_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[CHARGE_CUR_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[CHARGE_CUR_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[CHARGE_CUR_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; // 
    
    p[index++] = 43;
    temp = (int)User_paras.alm_thr.trigger_thress[DISCHARGE_CUR_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[DISCHARGE_CUR_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[DISCHARGE_CUR_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[DISCHARGE_CUR_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[DISCHARGE_CUR_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[DISCHARGE_CUR_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; // 
    
    p[index++] = 44;
    temp = (int)User_paras.alm_thr.trigger_thress[SOC_LOW][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[SOC_LOW][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[SOC_LOW];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[SOC_LOW][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[SOC_LOW][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[SOC_LOW];
    p[index++] = temp >> 8; //
    p[index++] = temp; // 
    
    p[index++] = 45;
    temp = (int)User_paras.alm_thr.trigger_thress[SOH_LOW][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[SOH_LOW][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[SOH_LOW];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[SOH_LOW][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[SOH_LOW][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[SOH_LOW];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    
    
    p[index++] = 46;
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_HIGH][ALARM_LVL_1] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_HIGH][ALARM_LVL_2] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[CELL_VOLT_HIGH] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_LOW][ALARM_LVL_1] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_LOW][ALARM_LVL_2] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[CELL_VOLT_LOW] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_DIFF_HIGH][ALARM_LVL_1] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_thress[CELL_VOLT_DIFF_HIGH][ALARM_LVL_2] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)(User_paras.alm_thr.reset_thress[CELL_VOLT_DIFF_HIGH] * 10);
    p[index++] = temp >> 8; //
    p[index++] = temp; //  
    
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_HIGH][ALARM_LVL_1]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_HIGH][ALARM_LVL_2]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[CELL_VOLT_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_LOW][ALARM_LVL_1]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_LOW][ALARM_LVL_2]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[CELL_VOLT_LOW];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_DIFF_HIGH][ALARM_LVL_1]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)(User_paras.alm_thr.trigger_delays[CELL_VOLT_DIFF_HIGH][ALARM_LVL_2]);
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[CELL_VOLT_DIFF_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    
    p[index++] = DataId_CellTempDiffConfig;
    temp = (int)User_paras.alm_thr.trigger_thress[CELL_TEMP_DIFF_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_thress[CELL_TEMP_DIFF_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_thress[CELL_TEMP_DIFF_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    temp = (int)User_paras.alm_thr.trigger_delays[CELL_TEMP_DIFF_HIGH][ALARM_LVL_1];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    temp = (int)User_paras.alm_thr.trigger_delays[CELL_TEMP_DIFF_HIGH][ALARM_LVL_2];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    p[index++] = 0; //
    p[index++] = 0; //
    temp = (int)User_paras.alm_thr.reset_delays[CELL_TEMP_DIFF_HIGH];
    p[index++] = temp >> 8; //
    p[index++] = temp; //
    
    p[index++] = DataId_CalibKBConfig;
    p[index++] = TYPE_VOLT;
    p[index++] = 1;//
    KB_t kb = {0};
    kb.f = Dev_paras.calib.total_batt[0].k;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    kb.f = Dev_paras.calib.total_batt[0].b;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    
    p[index++] = DataId_CalibKBConfig;
    p[index++] = TYPE_CURRENT;
    p[index++] = 1;//
    kb.f = Dev_paras.calib.total_batt[1].k;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    kb.f = Dev_paras.calib.total_batt[1].b;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    
    p[index++] = DataId_CalibKBConfig;
    p[index++] = TYPE_CURRENT;
    p[index++] = 2;//
    kb.f = Dev_paras.calib.total_batt[2].k;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    kb.f = Dev_paras.calib.total_batt[2].b;
    p[index++] = kb.i >> 24;
    p[index++] = kb.i >> 16;
    p[index++] = kb.i >> 8;
    p[index++] = kb.i;
    
    

    return index;
    
    
}


#include "de_protocol.h"
errStatus_t de_protocol_handle_config(uint8_t *pdata,uint16_t length) {
    uint16_t index = 0;

	int result_cnt = 0;

	uint8_t err_count = 0;
    uint8_t data_id = 0;
	int32_t temp_value_int;
    uint8_t i=0;
    
    
    User_paras_t *temp_user_confing = (User_paras_t *)sys_malloc(sizeof(User_paras_t));
    if(temp_user_confing == NULL) {
        return errErr;
    }
    
    memcpy((void *)temp_user_confing,&User_paras,sizeof(User_paras_t));

	while(index < length) {
        data_id = pdata[index++];
        switch(data_id) {
            case DataId_SetId:
                Sys_paras.dev_id = (uint32_t)pdata[index] << 24 \
                                 | (uint32_t)pdata[index + 1] << 16 \
                                 | (uint32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                Sys_para_file->write(&Sys_paras.dev_id);
            
                paraNoInitSave();
            
                index += 4;
                break;

			case DataId_TrainLine:
				index += 2;
				break;//
				
			case DataId_Cap:
				index += 2;
				break;//
				
			case DataId_Group:
				index += 2;
				break;//
				
			case DataId_TotalVoltage:
				index += 2;
				break;//
				
			case DataId_MCVersion:
				index += 9;
				break;//
				
			case DataId_CellVersion:
				index += 6;
				break;//
				
			case DataId_SocInitFlag:
				Dev_paras.soc_init = pdata[index++];
				break;//
				
			case DataId_Soc:
                {
                    FI_Conv_t conv = {0};
                    conv.i = (uint32_t)pdata[index] << 24 \
                                 | (uint32_t)pdata[index + 1] << 16 \
                                 | (uint32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                    index += 4;
                    Batt_soc->set_cap(conv.f, true);

                    // modify dishcarged capacity
                    if (Discharge_soc_record != NULL)
                    {
                      float nomial_cap = Batt_soc->get_nomial_cap();

                      Discharge_soc_record->set_discharged_cap(((conv.f / 100 * nomial_cap ) - nomial_cap) / Discharge_soc_record->get_charge_efficiency(), true);
                    }
                }
				
				break;//
            
            case DataId_SoH:
                {
                    FI_Conv_t conv = {0};
                    conv.i = (uint32_t)pdata[index] << 24 \
                                 | (uint32_t)pdata[index + 1] << 16 \
                                 | (uint32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                    index += 4;
                    Soh_record.soh = conv.f;
                    
                    Soh_record_file->write(&Soh_record);
                }
                break;
				
			case DataId_CellPackNumber:
				index += 2;
				break;//
				
			case DataId_CellTempNumber:
				index += 2;
				break;//

			case DataId_MCSamplePeriod:
                temp_user_confing->period.acquire = (uint16_t)pdata[index] << 8 | pdata[index+1];
				index += 2;
				break;//主控采集周期
				
			case DataId_CellCommPeriod:
				temp_user_confing->period.cell_comm = (uint16_t)pdata[index] << 8 | pdata[index+1];
				index += 2;
				break;//采集板通讯周期
				
			case DataId_StorePeriod:
				temp_user_confing->period.store = (uint16_t)pdata[index] << 8 | pdata[index+1];
				index += 2;
                break;//数据存储周期

			case DataId_Fast2Float://mA
				temp_value_int =  (int32_t)pdata[index] << 24 \
                                 | (int32_t)pdata[index + 1] << 16 \
                                 | (int32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                index += 4;
				temp_user_confing->batt_state_thr.fast_to_float_thr = (float)temp_value_int / 1000.0f;
                break;//快充转浮充阈值
                
			case DataId_Float2Fast:
				temp_value_int =  (int32_t)pdata[index] << 24 \
                                 | (int32_t)pdata[index + 1] << 16 \
                                 | (int32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                index += 4;
				temp_user_confing->batt_state_thr.float_to_fast_thr = (float)temp_value_int / 1000.0f;
                break;//浮充转快充阈值
                
			case DataId_Charge2DisCharge:
				temp_value_int =  (int32_t)pdata[index] << 24 \
                 | (int32_t)pdata[index + 1] << 16 \
                 | (int32_t)pdata[index + 2] << 8 \
                 | pdata[index + 3];
                index += 4;
				temp_user_confing->batt_state_thr.charge_to_discharge_thr = (float)temp_value_int / 1000.0f;
                break;//充电转放电阈值
                
			case DataId_Discharge2Charge:
				temp_value_int =  (int32_t)pdata[index] << 24 \
                 | (int32_t)pdata[index + 1] << 16 \
                 | (int32_t)pdata[index + 2] << 8 \
                 | pdata[index + 3];
                index += 4;
				temp_user_confing->batt_state_thr.discharge_to_charge_thr = (float)temp_value_int / 1000.0f;
                break;//放电转充电阈值

			case DataId_VolageAlarmConfig:
				for(i=TOTAL_VOLT_HI;i<=TOTAL_VOLT_DEVIATE_HI;i++) { //总电压阈值
					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//一级
					temp_user_confing->alm_thr.trigger_thress[i][ALARM_LVL_1] = temp_value_int * 0.1f;

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//二级
					temp_user_confing->alm_thr.trigger_thress[i][ALARM_LVL_2] = temp_value_int * 0.1f;

					index += 2;//三级

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//撤销
					temp_user_confing->alm_thr.reset_thress[i] = temp_value_int * 0.1f;

				}

				for(i=TOTAL_VOLT_HI;i<=TOTAL_VOLT_DEVIATE_HI;i++)  {//总电压延时
					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//一级
					temp_user_confing->alm_thr.trigger_delays[i][ALARM_LVL_1] = temp_value_int;

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//二级
					temp_user_confing->alm_thr.trigger_delays[i][ALARM_LVL_2] = temp_value_int;

					index += 2;//三级

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//撤销
					temp_user_confing->alm_thr.reset_delays[i] = temp_value_int;
				}
                break;//总电压告警配置
                
			case DataId_TempAlarmConfig:
				//告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[TEMP_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[TEMP_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[TEMP_HIGH] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[TEMP_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[TEMP_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[TEMP_HIGH] = temp_value_int;
                break;//温度告警配置
                
			case DataId_ChargeCurrentAlarmConfig:
				//告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[CHARGE_CUR_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[CHARGE_CUR_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[CHARGE_CUR_HIGH] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[CHARGE_CUR_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[CHARGE_CUR_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[CHARGE_CUR_HIGH] = temp_value_int;
                break;//充电电流告警配置
                
			case DataId_DischarageCurrentAlarmConfig:
				//告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[DISCHARGE_CUR_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[DISCHARGE_CUR_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[DISCHARGE_CUR_HIGH] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[DISCHARGE_CUR_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[DISCHARGE_CUR_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[DISCHARGE_CUR_HIGH] = temp_value_int;
                break;//放电电流告警配置
                
			case DataId_SOCLowAlarmConfig:
				//告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[SOC_LOW][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[SOC_LOW][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[SOC_LOW] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[SOC_LOW][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[SOC_LOW][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[SOC_LOW] = temp_value_int;
                break;//SOC过低告警配置
                
			case DataId_SOHLowAlarmConfig:
                //告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[SOH_LOW][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[SOH_LOW][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[SOH_LOW] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[SOH_LOW][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[SOH_LOW][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[SOH_LOW] = temp_value_int;
                break;//SOC过低告警配置
                
			case DataId_CellVoltageAlarmConfig:
				for(i=CELL_VOLT_HIGH;i<=CELL_VOLT_DIFF_HIGH;i++) { 
					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//一级
					temp_user_confing->alm_thr.trigger_thress[i][ALARM_LVL_1] = temp_value_int * 0.1f;

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//二级
					temp_user_confing->alm_thr.trigger_thress[i][ALARM_LVL_2] = temp_value_int * 0.1f;

					index += 2;//三级

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//撤销
					temp_user_confing->alm_thr.reset_thress[i] = temp_value_int * 0.1f;

				}

				for(i=CELL_VOLT_HIGH;i<=CELL_VOLT_DIFF_HIGH;i++) {
					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//一级
					temp_user_confing->alm_thr.trigger_delays[i][ALARM_LVL_1] = temp_value_int;

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//二级
					temp_user_confing->alm_thr.trigger_delays[i][ALARM_LVL_2] = temp_value_int;

					index += 2;//三级

					temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
					index += 2;//撤销
					temp_user_confing->alm_thr.reset_delays[i] = temp_value_int;
				}
                break;//单体电压告警配置
                
			case DataId_CellCommErrAlarmConfig:
                break;//单体通讯告警配置

            case DataId_CellTempDiffConfig:
                				//告警配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_thress[CELL_TEMP_DIFF_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_thress[CELL_TEMP_DIFF_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_thress[CELL_TEMP_DIFF_HIGH] = temp_value_int;

				//延时配置
				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//一级
				temp_user_confing->alm_thr.trigger_delays[CELL_TEMP_DIFF_HIGH][ALARM_LVL_1] = temp_value_int;

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//二级
				temp_user_confing->alm_thr.trigger_delays[CELL_TEMP_DIFF_HIGH][ALARM_LVL_2] = temp_value_int;

				index += 2;//三级

				temp_value_int = (int32_t)pdata[index] << 8 | pdata[index + 1];
				index += 2;//撤销
				temp_user_confing->alm_thr.reset_delays[CELL_TEMP_DIFF_HIGH] = temp_value_int;
                break;//
				
            case DataId_CalibKBConfig:
            {
                uint8_t type = pdata[index++];
                uint8_t ch = pdata[index++];
                KB_t k = {0};
                KB_t b = {0};
                k.i = (uint32_t)pdata[index] << 24 \
                                 | (uint32_t)pdata[index + 1] << 16 \
                                 | (uint32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                index += 4;
                b.i = (uint32_t)pdata[index] << 24 \
                                 | (uint32_t)pdata[index + 1] << 16 \
                                 | (uint32_t)pdata[index + 2] << 8 \
                                 | pdata[index + 3];
                index += 4;

                switch(type) {
                    case TYPE_TEMP:
                        switch(ch) {
                            case 1:
                                Dev_paras.calib.total_batt[3].k = k.f;
                                Dev_paras.calib.total_batt[3].b = b.f;
                                Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[3])), 0);
                                break;
                            case 2:
                                Dev_paras.calib.total_batt[4].k = k.f;
                                Dev_paras.calib.total_batt[4].b = b.f;
                                Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[4])), 1);
                                break;
                        }
                        break;
                    case TYPE_VOLT:
                        Dev_paras.calib.total_batt[0].k = k.f;
                        Dev_paras.calib.total_batt[0].b = b.f;
                        tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[0])), 0);
                        break;
                    case TYPE_CURRENT:
                        switch(ch) {
                            case 1:
                                Dev_paras.calib.total_batt[1].k = k.f;
                                Dev_paras.calib.total_batt[1].b = b.f;
                                tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[1])), 1);
                                break;
                            case 2:
                                Dev_paras.calib.total_batt[2].k = k.f;
                                Dev_paras.calib.total_batt[2].b = b.f;
                                tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[2])), 2);
                                break;
                        }
                        
                        
                        break;
                }
                
                
                break;
            }
            case DataId_CalibTime:
                {
                    uint32_t ts_second =(uint32_t) pdata[index] << 24   \
                                        | (uint32_t)pdata[index + 1] << 16\
                                        | (uint32_t)pdata[index + 2] << 8\
                                        | pdata[index + 3];
                    Rtc->set_datetime(ts_second);
                    index += 4;
                   
                }
                break;
                
            default:
                err_count++;
                break;
        }
        
       
		result_cnt++;

		if(err_count) {
			break;
		}
    }
    
    if(!err_count) {
        memcpy(&User_paras,(void *)temp_user_confing,sizeof(User_paras_t));
        sys_free(temp_user_confing);
        
        taskENTER_CRITICAL();  
        Dev_para_file->write(&Dev_paras);
        User_para_file->write(&User_paras);
        taskEXIT_CRITICAL();
        
        paraNoInitSave();
        
        return errOK;
    } 
    sys_free(temp_user_confing);
    return errErr;
}

errStatus_t cell_data_update(uint8_t id,uint8_t *pdata,uint16_t length) {
    uint16_t index = 0;
    errStatus_t err = errOK;
    if(id > 2 || id < 1) {
        return errErr;
    } 
    uint8_t id_temp = id - 1;
    uint8_t ch = 0;
    uint8_t in_ch = 0;
    Batt_data_buff.cell_data[id_temp].id = id;
    int16_t temp;
    uint8_t type;
    
    bool temp_err = false;
    while(index < length) {
        
		uint8_t data_id = pdata[index++];
        if(data_id == 1) {
            type = pdata[index++];//Type
            
            index += 2;//ext ch

            in_ch = pdata[index] << 8 | pdata[index+1];
            index += 2;// inter ch number
            if(in_ch > 12) {
                return errErr;
            }
            
            
            index += 2;//values.
            temp = pdata[index] << 8 | pdata[index+1];//mV or 0.1degree.
            if(type == TYPE_TEMP) {
                ch = ACQ_TEMP_OFFSET + in_ch;
                if(ch > ACQ_MAX_CNT) {
                    return errErr;
                }
                if((float)(temp * 0.1f) > TEMP_SENSOR_ERR_VAL_MAX || (float)(temp * 0.1f) < TEMP_SENSOR_ERR_VAL_MIN) {
                    Batt_data_buff.cell_data[id_temp].acq_val[ch-1] = 250;
                    temp_err = true;
                } else {
                    Batt_data_buff.cell_data[id_temp].acq_val[ch-1] = temp;
                }
            } else if(type == TYPE_VOLT){
                ch = ACQ_VOLT_OFFSET + in_ch;
                if(ch > ACQ_MAX_CNT) {
                    return errErr;
                }
                Batt_data_buff.cell_data[id_temp].acq_val[ch-1] = temp;
            } else if (type >= TYPE_MAX) {
                index += 6;
                continue;
            }
            
            index += 2;

            FI_Conv_t conv = {0};

            conv.i = (uint32_t)pdata[index] << 24 \
                    | (uint32_t)pdata[index+1] << 16\
                    | (uint32_t)pdata[index+2] << 8 \
                    |           pdata[index+3];
            
            cell_data_adc_voltage[id_temp].acq_val[ch-1] = conv.f;
            
            index += 4;

        } else {
            err = errErr;
            break;
        }   
    }
    
    if(temp_err) {
        Train_data->alarm_self_flag.bits.temp_err = 1;
    } else {
        Train_data->alarm_self_flag.bits.temp_err = 0;
    }
    return err;
}

osMessageQId  mid_CellRequest = NULL;                       // message queue id
osMessageQDef(msgCellRequest, 12, ModuleTxMsg_t);            // message queue object

void CellRequestMsgInit(void) {
    mid_CellRequest = osMessageCreate(osMessageQ(msgCellRequest), NULL);
}

void CellTranferRequest(uint8_t *pMsg,uint16_t length) {
    ModuleTxMsg_t *p = (ModuleTxMsg_t *)sys_malloc(sizeof(ModuleTxMsg_t));
    if(p == NULL) {
        return;
    }
    p->pdata = (uint8_t *)sys_malloc(length);
    if(p->pdata == NULL) {
        sys_free(p);
        return;
    }
    memcpy(p->pdata,pMsg,length);
    p->length = length;
    
    osStatus  st = osMessagePut(mid_CellRequest,(uint32_t)p,100);
    if(st != osOK) {
        sys_free(p->pdata);
        sys_free(p);
    }
    
}
#define DEBUG_RS485 0
void Cell_comm_process(void *pvParameters)
{
    CellRequestMsgInit();
    
    vTaskDelay(5000);

    HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_SET);

    vTaskDelay(CELL_POWERUP_DELAY);
    
    uint32_t delay_save;
    if(User_paras.period.cell_comm == 0 || User_paras.period.cell_comm > 600) {
        User_paras.period.cell_comm = 1;
    }
    delay_save = User_paras.period.cell_comm;
    
    while (1)
    {
        osEvent evt = osMessageGet(mid_CellRequest,SECONDS_TO_MILLISECONDS(delay_save));
        
        if(evt.status == osEventMessage) { 

            memset((void *)&protocolRxMsg,0,sizeof(protocolRxMsg));
            
            ModuleTxMsg_t *p = (ModuleTxMsg_t *)evt.value.p;
            if(p != NULL) {
                if(p->pdata != NULL) {
                    
                    cellRequsetTransfer = true;
                    
                    Bsp_Rs485SendBytes(p->pdata,p->length);
                    
                    sys_free(p->pdata);
                }
                sys_free(p);
            }
            
            delay_save = 3;
            
        } else {
#if 1
            if(User_paras.period.cell_comm == 0 || User_paras.period.cell_comm > 600) {
                User_paras.period.cell_comm = 1;
            }
            delay_save = User_paras.period.cell_comm;
            
            HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_SET);
            //轮流读取总线上挂载的采集板的数据
            errStatus_t err = errOK;
            
#if DEBUG_RS485 == 0
            
            for (int i = 0; i < CELL_CNT; i++)
            {
                if(cell_module_query_status(i+1,5) == errOK) {
                    
                } else {
                    //comm err.
                    err = errErr;  
                    memset(Batt_data_buff.cell_data[i].acq_val,0,sizeof(Batt_data_buff.cell_data[i].acq_val));
                    //
                }
            }
#endif
            if(err == errErr) {
                Train_data->alarm_self_flag.bits.comm_err = 1;
                HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
            } else {
                Train_data->alarm_self_flag.bits.comm_err = 0;
                HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
            }
            
            Train_data->alarm_self_check(&Batt_data_buff);
            
            //如果USB有读取指令，则向USB发送消息
            if (Cell_comm_cpl_queue != NULL)
            {
                char msg = 'c';
                xQueueOverwrite(Cell_comm_cpl_queue, &msg);
            }

            //HAL_GPIO_TogglePin(LED_TEST_GPIO_Port,LED_TEST_Pin);
            
            //Monitoring_data->set_data(&Batt_data_buff, !Usb_debug_mode);

            
#endif
            Data_ready = true;
        }
        
#if !S07Y
        //在定时器中被定时唤醒。
        vTaskSuspend(Cell_comm_handle);
#endif
        }
}


#if 0
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
      //HAL_GPIO_WritePin(CELL_POWER_GPIO_Port, CELL_POWER_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
    }

    //在定时器中被定时唤醒。
    vTaskSuspend(Cell_comm_handle);
  }
}
#endif



void Batt_cap_update(void *pvParameters)
{
    portTickType last_waketime = 0;
    Batt_info cap_para;
    float multiple = 2.6;//260AH
    osDelay(15000);
#if S07R
    multiple = 1.8;
#endif
    
    while (1)
    {
        if (!Usb_debug_mode && Batt_soc != NULL)
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
            
            paraNoInitSave();

        }
        
        vTaskDelayUntil(&last_waketime, BATT_CAP_CALC_PERIOD_MS);
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
  else if (uart_handle == Mvb_uart_handle)
  {
    if (Mvb_comm_queue != NULL)
    {
      xQueueOverwriteFromISR(Mvb_comm_queue, &msg, &xHigherPriorityTaskWoken);
    }
  }

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

#if USE_MVB
void Mvb_init(void *pvParameters)
{
  vTaskSuspend(Mvb_process_handle);
  vTaskSuspend(Mvb_rx_handle);

  while (1)
  {

    if(Mvb != NULL) {
        Mvb->reset();
        if (Mvb->config(&Dev_paras.mvb[Mvb_port_idx]))
        {
          vTaskResume(Mvb_process_handle);
          vTaskResume(Mvb_rx_handle);
          vTaskSuspend(Mvb_init_handle);
          
        }
    }

    vTaskDelay(5000);
  }
}

void Mvb_process(void *pvParameters)
{
  unsigned int send_len = 0;
    
    uint16_t heart = 0;
    
  //unsigned short datetime_addr = (Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[0] << 8) | Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[1];
 
  //unsigned short vital_addr = (Dev_paras.mvb[Mvb_port_idx].src_port[1].addr[0] << 8) | Dev_paras.mvb[Mvb_port_idx].src_port[1].addr[1];
  
  while (1)
  {
      if(Train_data != NULL) {

        memset(Mvb_send_buff, 0, sizeof(Mvb_send_buff));
          
        send_len = Train_data->get_mvb_update_buff(Mvb_send_buff,heart++);
              
        if (send_len > 0)
        {
            if(Train_mvb != NULL) {
                Train_mvb->send_msg(Mvb_send_buff, send_len);
            }
        }
      }
    
      
 
      vTaskDelay(1000);
  }
}

void Mvb_rx_process(void *pvParameters) {
    
    vTaskDelay(5000);
    
    unsigned short datetime_addr = 0x01;//(Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[0] << 8) | Dev_paras.mvb[Mvb_port_idx].src_port[0].addr[1];

    while(1) 
    {   
        if(Mvb_comm_queue != NULL) {
            unsigned char data = 0;
            if (xQueueReceive(Mvb_comm_queue, &data, 600000/*portMAX_DELAY*/)) {
                if (data == 'u') {     
                    Train_mvb->handle_rec_msg(datetime_addr);
                }
            } else {
                vTaskSuspend(Mvb_process_handle);
        
                Mvb->reset();
                
                osDelay(2000);
                
                Mvb->config(&Dev_paras.mvb[Mvb_port_idx]);
                
                vTaskResume(Mvb_process_handle);
            }
        } else {
            osDelay(1000);
        }
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
      if(Trdp != NULL) {
         if(Trdp->init())
        {
          vTaskResume(Eth_process_handle);
          vTaskResume(Eth_rev_handle);
          vTaskSuspend(Eth_init_handle);
        }
      }

    vTaskDelay(5000);
  }
}

osSemaphoreId  sid_ethTxLock = NULL;
osSemaphoreDef(ethTxLock);

void eth_sendbytes(uint8_t *pdata,uint16_t length) {
    if(sid_ethTxLock == NULL) {
        sid_ethTxLock = osSemaphoreCreate(osSemaphore(ethTxLock), 1);
    }
    
    if(Trdp != NULL) {
        osSemaphoreWait(sid_ethTxLock,osWaitForever);
        Trdp->trdp_pd_tx_handle(0,50000,pdata,length);
        osSemaphoreRelease(sid_ethTxLock);
    } 
}

void eth_trdp_protocol_sendbytes(uint8_t train,uint16_t comm_id, uint8_t *pdata,uint16_t length) {
    if(sid_ethTxLock == NULL) {
        sid_ethTxLock = osSemaphoreCreate(osSemaphore(ethTxLock), 1);
    }
    
    if(Trdp != NULL) {
        osSemaphoreWait(sid_ethTxLock,osWaitForever);
        Trdp->trdp_pd_tx_handle(train,comm_id,pdata,length);
        osSemaphoreRelease(sid_ethTxLock);
    } 
}

void sys_infor_print(COMM_TYPE_t commType) {
    debug_printf(commType,"-----sys infor-----\r\n");
    debug_printf(commType,"Version:%d.%d.%d Compile @%s %s\r\n",Sys_paras.ver.MC_SW_major,Sys_paras.ver.MC_SW_minjor,Sys_paras.ver.MC_SW_revision,__DATE__,__TIME__);
    debug_printf(commType,"paraReload:%d\r\n",paras_reload);


}



void bat_infor_print(COMM_TYPE_t commType) {
	debug_printf(commType,"-----bat infor-----\r\n");
    debug_printf(commType,(char *)"总电压:%.3f,总电流[1]:%.3f,总电流[2]:%.3f\r\n",\
										Batt_data_buff.total_data.total_volt,\
										Batt_data_buff.total_data.total_cur[0],\
										Batt_data_buff.total_data.total_cur[1]);
	for(int i=0;i<COUNT_OF_TEMP;i++) {
		debug_printf(commType, "温度[%d]:%.3f\r\n",i,Batt_data_buff.total_data.temp[i]);
	}

	debug_printf(commType, "SOC:%.1f,",Batt_data_buff.soc);
    debug_printf(commType, "SOH:%.1f\r\n",Batt_data_buff.soh);
    
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
		debug_printf(commType,"\r\n采集器[%d] Id:%d\r\n",Batt_data_buff.cell_data[i].id);
		for(int j=0;j<ACQ_MAX_CNT;j++) {
            if(j % 8 == 0) {
                debug_printf(commType,"\r\n");
            }
			debug_printf(commType,"通道[%02d],Value:%5d,",j,Batt_data_buff.cell_data[i].acq_val[j]);
		}
	}
}


bool recv_over = true;
void Eth_process(void *pvParameters)
{  
  unsigned int send_len = 0;
  unsigned char send_delay = 100;
    uint16_t heart = 0;
    osDelay(5000);
  while (1)
  {
    if (Data_ready && Train_data != NULL)
    {
      memset(Eth_send_buff, 0, sizeof(Eth_send_buff));
      send_len = Train_data->get_eth_update_buff(Eth_send_buff,heart++);
        
      memset(Mvb_send_buff, 0 ,sizeof(Mvb_send_buff));
      Train_data->get_mvb_update_buff(Mvb_send_buff,heart++);
        
      for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
      {
        while(send_delay-- && !recv_over)
        {
            DELAY_MS(1);
        }
        
        if(!IAP_GetStatus()) {
            if(recv_over)
            {
                eth_trdp_protocol_sendbytes(i, Dev_paras.eth_paras[i].trdp_paras.bms[i].bms_commid, Eth_send_buff, send_len);
            }
        } else {
            IAP_ClearStatus();
        }
        
      }
    }
    vTaskDelay(1000);
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

extern "C" bool de_protocol_process(COMM_TYPE_t type,uint8_t *pdate,uint16_t length);
unsigned char recv_buff[TRDP_RECV_BUFF_SIZE];
unsigned short len = 0;


osMessageQId  mid_LoggerRead = NULL;                       // message queue id
osMessageQDef(msgLoggerRead, 4, Logger_Msg_t);            // message queue object

void System_SoftReset(void) {
    Logger_Msg_t logger = {0};
    logger.logger_type = DataId_Reset;
    logger.para8_1 = 0;
    logger.para8_2 = 0;
    logger.para32_1 = 0;
    logger.para32_2 = 0;
    logger.para32_3 = 0;

    LoggerRequest(logger);
}

void LoggerRequest(Logger_Msg_t logger);
void LoggerRequest(Logger_Msg_t logger) {
    Logger_Msg_t *p = (Logger_Msg_t *)sys_malloc(sizeof(Logger_Msg_t));
    if(p == NULL) {
        return;
    }
   
    memcpy(p,&logger,sizeof(Logger_Msg_t));
    
    osStatus  st = osMessagePut(mid_LoggerRead,(uint32_t)p,100);
    if(st != osOK) {
        sys_free(p);
    }
    
}

void LoggerMsgInit(void) {
    mid_LoggerRead = osMessageCreate(osMessageQ(msgLoggerRead), NULL);
}

void get_logger_process(void *pvParameters) {
    
    if(mid_LoggerRead == NULL) {
        LoggerMsgInit();
    }
    
    osDelay(5000);
    
    logger_set_reset_reg();
    
    while(1)  {
        osEvent evt = osMessageGet(mid_LoggerRead,osWaitForever);
        
        if(evt.status == osEventMessage) { 

            Logger_Msg_t *p = (Logger_Msg_t *)evt.value.p;
            
            if(p != NULL) {
                switch(p->logger_type) {
                    case DataId_Alarm_Data://alarm
                        get_alarm_his_data_all(p->para8_1,p->para8_2,p->para32_1,p->para32_2,&p->para32_3);
                        break;
                    case DataId_Hist_Data://his
                        get_logger_his_data_all(p->para32_1,p->para32_2,&p->para32_3);
                        break;
                    case DataId_Reset:
                        osDelay(100);
                        NVIC_SystemReset();
                        break;
                }
                sys_free(p);
            }
        }
    }


}

void Eth_rev_data(void *pvParameters)
{
  unsigned char data = 0;
    osDelay(5000);
    
    while(Eth_comm_queue == NULL) {
        osDelay(100);
    }
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
#if 0
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
#endif
                              }
                              break;
                          
                          case 20001:
                              if(de_protocol_process(COMM_TYPE_ETH,(uint8_t *)recv_buff+index,app_data_length)) {
                                  break;
                              }
                          
                              commandHandle(COMM_TYPE_ETH,(char *)recv_buff+index,NULL);
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
        }
      }
    }
    //DELAY_MS(2000);
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
#if USE_USB_DEBUG == 1
      Host_comm->forward(*(unsigned char *)p++);
#endif
      cnt++;
    } while (cnt < btf);
  }

  return cnt;
}

void cell_comm_timer_callback(TimerHandle_t xTimer)
{
#if !S07Y
  vTaskResume(Cell_comm_handle);
#endif
    
#if S07Y
    if(Data_ready) {
        Monitoring_data->set_data(&Batt_data_buff, true);
    }
#endif
    
}

uint32_t get_ts_1(Rtc_t* date_time);
bool ts_to_datetime_1(unsigned int ts, Rtc_t* datetime);
void rtc_get_time(DATE_yymmddhhmmss_t *time) {
    Rtc_t datetime;
    Rtc->get_datetime(&datetime);
//    uint32_t ts = get_ts_1(&datetime);

//    ts_to_datetime_1(ts,&datetime);
    
    time->bits.year = datetime.date.year;
    time->bits.month = datetime.date.month;
    time->bits.min = datetime.date.date;
    time->bits.hour = datetime.time.hours;
    time->bits.min = datetime.time.minutes;
    time->bits.sec = datetime.time.seconds;
    
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

/*

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
*/
 

extern FIL Fil;
bool clear_history_data(void) {
    taskENTER_CRITICAL();  
    FRESULT res = f_unlink(HISTORY_DATA_FILE_NAME);
    
    if(res != FR_OK) {
        goto Exit;
    }
    if(Hist_data_file) {
        delete Hist_data_file;
    }

    Hist_data_file = new File(Fil, HISTORY_DATA_FILE_NAME);
    if (Hist_data_file == NULL)
    {
        goto Exit;
    }
    if (Hist_data_file->header_need_init())
    {
        File_header header = {
        0, 0, sizeof(History_data_t),
        HISTORY_DATA_STORE_CNT,
        true, FILE_DATA_VER};

        Hist_data_file->create(&header);
    }
  
    taskEXIT_CRITICAL();
    
    return true;
    
Exit:
    taskEXIT_CRITICAL();
    return false;
  
  
}


bool clear_alarm_data(void) {
    taskENTER_CRITICAL();  
    
    FRESULT res = f_unlink(ALARM_DATA_FILE_NAME);
    
    if(res != FR_OK) {
        goto Exit;
    }
    if(Alm_data_file) {
        delete Alm_data_file;
    }
    
    Alm_data_file = new File(Fil, ALARM_DATA_FILE_NAME);
    if (Alm_data_file == NULL)
    {
        goto Exit;
    }
    if (Alm_data_file->header_need_init())
    {
        File_header header = {
        0, 0, sizeof(Alarm_store_data_t),
        ALARM_DATA_STORE_CNT,
        true, FILE_DATA_VER};

        Alm_data_file->create(&header);
    }
    
    taskEXIT_CRITICAL();
    return true;

Exit:
    taskEXIT_CRITICAL();
    return false;
}
#include "pvd.h"
void paraNoInitSave(void) {

    if(pvd_get_power_flag()) {
        return;
    }
    taskENTER_CRITICAL();  
    paraNoInit.device_id = Sys_paras.dev_id;
    if(Batt_soc != NULL) {
        paraNoInit.soc = Batt_soc->get_cap();
    }
    
    paraNoInit.soh = Soh_record.soh;
    
    memcpy(&paraNoInit.user_para,&User_paras,sizeof(User_paras));
    
    memcpy(&paraNoInit.calib,&Dev_paras.calib,sizeof(Calib_t));
    
    paraNoInit.crc32 = CRC_Get32(((uint8_t *)&paraNoInit) + 4,sizeof(paraNoInit) - 4);
    
    taskEXIT_CRITICAL();
}

bool paraNoInitReload(void) {
    taskENTER_CRITICAL();  
    uint32_t crc1 = paraNoInit.crc32;
    uint32_t crc2 = CRC_Get32(((uint8_t *)&paraNoInit) + 4,sizeof(paraNoInit) - 4);
    
    if (crc1 == crc2) {
        
        paras_reload = true;
        Sys_paras.dev_id = paraNoInit.device_id;
        Soh_record.soh = paraNoInit.soh;
        Batt_soc->set_cap(paraNoInit.soc, true);

        // modify dishcarged capacity
        if (Discharge_soc_record != NULL)
        {
            float nomial_cap = Batt_soc->get_nomial_cap();
            Discharge_soc_record->set_discharged_cap(((paraNoInit.soc / 100 * nomial_cap ) - nomial_cap) / Discharge_soc_record->get_charge_efficiency(), true);
        }
        
        Soh_record.soh = paraNoInit.soh;
        Soh_record_file->write(&Soh_record);
        
        memcpy(&User_paras,&paraNoInit.user_para,sizeof(User_paras));
        memcpy(&Dev_paras.calib,&paraNoInit.calib,sizeof(Calib_t));
        

        Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[3])), 0);
        Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[4])), 1);
        tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[0])), 0);
        tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[1])), 1);
        tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[2])), 2);
        
        Dev_para_file->write(&Dev_paras);
        User_para_file->write(&User_paras);
    }
    
    taskEXIT_CRITICAL();
    
    return paras_reload;
}
