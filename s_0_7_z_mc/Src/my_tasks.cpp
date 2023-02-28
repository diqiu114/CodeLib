#include "my_tasks.h"
#include "defines.h"
#include "class_init.h"
#include "fatfs.h"
#include "iwdg.h"
#include "rtc.h"
#include "usb_device.h"
#include "fmc.h"
#include "nand_driver.h"
#include "my_stm32_ftl.h"
#include "gpio.h"
#include "tim.h"
#include "logger.h"
#include "proj_paras.h"

bool paras_need_reconfig_flag = false;
extern Flag_t Nand_format_flag;

#define TASK_PRIORITY_MAX (configMAX_PRIORITIES - 1)
#define TASK_PRIORITY_MIN (1)

// tasks creation
TaskHandle_t Task_create_handle = NULL;
void Task_create(void *pvParameters);

// hardware configuration
TaskHandle_t HW_init_handle = NULL;
void HW_init(void *pvParameters);

// usb VCP communication
TaskHandle_t Usb_vcp_comm_handle = NULL;
void Usb_vcp_comm(void *pvParameters);
unsigned int Usb_idle_cnt = 0;

TaskHandle_t Usb_connected_handle = NULL;
void Usb_connected(void *pvParameters);

#if (TASK_DEBUG)
TaskHandle_t Task_debug_handle = NULL;
void Task_debug(void *pvParameters);
#endif

// queue handle declare
QueueHandle_t Usb_comm_queue = NULL;

#if (USE_IWDG)
TimerHandle_t Iwdg_timer_handle = NULL;

void iwdg_timer_callback(TimerHandle_t xTimer);
#endif

bool MT_create_tasks(void)
{
  xTaskCreate(Task_create, "Task_create_task", 512, NULL, TASK_PRIORITY_MAX, &Task_create_handle);
  if (Task_create_handle != NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
#if 0
  if (htim->Instance == TIM14)
  {
    HAL_IncTick();
  }
  else 
#endif
    
#if USE_USB_DEBUG == 1
  if (htim == &htim2)
  {
    if (Host_comm->get_rev_data_flag())
    {
      Usb_idle_cnt++;
      if (Usb_idle_cnt > USB_IDLE_TIMEOUT_MS)
      {
        Usb_idle_cnt = 0;
        Host_comm->idle_handle();
        Host_comm->clear_rev_data_flag();
      }
    }
    else
    {
      Usb_idle_cnt = 0;
    }
  }
#endif
  
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

void Task_create(void *pvParameters)
{
  taskENTER_CRITICAL();

  bool task_create_ok = true;

  // hardware configuration task, just run once
  // NOTE: must be created
  xTaskCreate(HW_init, "Hardware_init_task", 512, NULL, TASK_PRIORITY_MAX, &HW_init_handle);
  task_create_ok = task_create_ok && (HW_init_handle != NULL);

#if USE_USB_DEBUG == 1
  // usb communication
  xTaskCreate(Usb_vcp_comm, "Usb_comm_task", 512, NULL, TASK_PRIORITY_MAX - 1, &Usb_vcp_comm_handle);
  task_create_ok = task_create_ok && (Usb_vcp_comm_handle != NULL);


  // usb connected process
  xTaskCreate(Usb_connected, "Usb_connected_process", 256, NULL, TASK_PRIORITY_MAX - 3, &Usb_connected_handle);
  task_create_ok = task_create_ok && (Usb_connected_handle != NULL);
  
  #if (TASK_DEBUG)
  // current switch process
  xTaskCreate(Task_debug, "Task_debug", 256, NULL, TASK_PRIORITY_MAX - 2, &Task_debug_handle);
  task_create_ok = task_create_ok && (Task_debug_handle != NULL);
  #endif
#endif

  // project tasks create
  task_create_ok = Proj_task_create();

  vTaskDelete(Task_create_handle);

  taskEXIT_CRITICAL();
}

extern FIL Fil;
extern uint8_t paras_count;
void HW_init(void *pvParameters)
{
  //taskENTER_CRITICAL();
    
  // master controller base hardware initialize
  MX_RTC_Init();
    
  MX_GPIO_Init();
    
#if USE_USB_DEBUG == 1
  MX_USB_DEVICE_Init();
#endif
    
  MX_FMC_Init();
    
  NAND_Init();
    
  MX_TIM5_Init(167, 999); // 1KHZ adc conv
    
#if USE_USB_DEBUG == 1
  MX_TIM2_Init(167, 999); // 1KHZ usb comm timeout 
#endif
    
  MX_FATFS_Init();

    //Nand_format = new Eeprom_flag(Nand_format_flag, 1);
    FRESULT f_ret;
    for(int trytimes = 0;trytimes < 3;trytimes++) {
        f_ret = f_mount(&USERFatFS, DRIVER_NAME, 1);
        if(f_ret == FR_OK) {
            break;
        }
    }
  // mount FATFS file system
  
  
  if (/*Nand_format->flag_set() ||*/ (f_ret != FR_OK))
  {
    //Nand_format->write_reset_val();
      
    FTL_Init();
      
    FTL_Format();
      
    FRESULT create_fs_rst = f_mkfs(DRIVER_NAME, FM_FAT32, 0, Fil.buf, sizeof(Fil.buf));
    
    f_mount(&USERFatFS, DRIVER_NAME, 1);
      
    logger_infor_save_more(LOGGER_OPERATE,LOGGER_MORE_FS_FORMAT,0,__FUNCTION__,__FILE__,__LINE__);

    taskENTER_CRITICAL(); 
    // 强制清空高端内存数据
    memset(&paraNoInit,0,sizeof(paraNoInit));
    paraNoInit.crc32 = 0;
    taskEXIT_CRITICAL(); 
  }

  // project hardware initialize
  Proj_hw_init();

  // usb communication task sync queue
  Usb_comm_queue = xQueueCreate(1, 1);

#if (USE_IWDG)
  MX_IWDG_Init();
  Iwdg_timer_handle = xTimerCreate("iwdg_timer", 2000, pdTRUE, 0, iwdg_timer_callback);
  if (Iwdg_timer_handle)
  {
    xTimerStart(Iwdg_timer_handle, 0);
  }
#endif

  // class initialize
  Class_init();

  // program upgrade flag check
  //Program_upgrade->check_reset_val();

  // project hardware configuration
  Proj_hw_config();
  
  if(paras_count > 0){
    paraNoInitReload();
  }

  vTaskDelete(HW_init_handle);

  //taskEXIT_CRITICAL();
}
#if USE_USB_DEBUG == 1
void Usb_vcp_comm(void *pvParameters)
{
  char data = 0;
  while (1)
  {
    if (xQueueReceive(Usb_comm_queue, &data, portMAX_DELAY))
    {
      if (data == 'u')
      {
        Host_comm->process();
      }
    }
  }
}

void Usb_connected(void *pvParameters)
{
  while (1)
  {
    if (Host_comm != NULL)
    {
      if (Host_comm->connected())
      {
        Usb_connected_process();
      }
      else
      {
        Usb_disconnected_process();
      }
    }
    vTaskDelay(1000);
  }
}

void usb_comm_callback(void)
{
  if (Usb_comm_queue)
  {
    char s = 'u';
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

    xQueueOverwriteFromISR(Usb_comm_queue, &s, &xHigherPriorityTaskWoken);
    
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}
#endif

#if (TASK_DEBUG)
#include "pvd.h"
void Task_debug(void *pvParameters)
{
  unsigned portBASE_TYPE uxHighWaterMark[10];

  while (1)
  {
#if 0
    taskENTER_CRITICAL();
    Batt_hist_data_store->store_data();
    Discharge_soc_record->store_discharged_cap();
    taskEXIT_CRITICAL();
    HAL_GPIO_TogglePin(LED_FAULT_GPIO_Port, LED_FAULT_Pin);
    vTaskDelay(10);
#endif
    vTaskDelay(1000);
  }
}
#endif



#if (USE_IWDG)
void iwdg_timer_callback(TimerHandle_t xTimer)
{
  HAL_IWDG_Refresh(&hiwdg);
}
#endif
