/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
#include "class_init.h"
#include "my_tasks.h"
#include "debug.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

///**
//  * @brief This function handles Hard fault interrupt.
//  */
//void HardFault_Handler(void)
//{
//  /* USER CODE BEGIN HardFault_IRQn 0 */

//  /* USER CODE END HardFault_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
//    /* USER CODE END W1_HardFault_IRQn 0 */
//  }
//}


/**
  * @brief This function handles Hard fault interrupt.
  */

enum { r0, r1, r2, r3, r12, lr, pc, psr};

void stack_dump(uint32_t stack[])
{
	static char msg[80];
	sprintf(msg, "r0  = 0x%08x\n", stack[r0]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "r1  = 0x%08x\n", stack[r1]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "r2  = 0x%08x\n", stack[r2]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "r3  = 0x%08x\n", stack[r3]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "r12 = 0x%08x\n", stack[r12]); debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "lr  = 0x%08x\n", stack[lr]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "pc  = 0x%08x\n", stack[pc]);  debug_sendstring(COMM_TYPE_COM,msg);
	sprintf(msg, "psr = 0x%08x\n", stack[psr]); debug_sendstring(COMM_TYPE_COM,msg);
}

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "logger.h"

char msg[80];
osThreadId osThreadGetId (void);

void Hard_Fault_Handler(uint32_t stack[]) {
    logger_msg_t msg = {0};
    
    msg.type = LOGGER_EXCEPT;
    for(uint8_t i=0;i<8;i++) {
        msg.v.d4[i] = stack[i];
    }
    
    msg.v.d4[8] = (uint32_t)xTaskGetCurrentTaskHandle();
    strcpy((char *)msg.file,pcTaskGetTaskName((TaskHandle_t)msg.v.d4[8]));
    
    logger_infor_save(msg);

	__ASM volatile("BKPT #01");

    while(1) {
		
    }
}

#if defined(__CC_ARM)
__asm void HardFault_Handler(void)
{
  TST lr, #4     // Test for MSP or PSP
  ITE EQ
  MRSEQ r0, MSP
  MRSNE r0, PSP
  B __cpp(Hard_Fault_Handler)
}
#elif defined(__ICCARM__)
void HardFault_Handler(void)
{
   __asm(   "TST lr, #4          \n"
            "ITE EQ              \n"
            "MRSEQ r0, MSP       \n"
            "MRSNE r0, PSP       \n"
            "B Hard_Fault_Handler\n"
   );
}
#endif

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

///**
//  * @brief This function handles System service call via SWI instruction.
//  */
//void SVC_Handler(void)
//{
//  /* USER CODE BEGIN SVCall_IRQn 0 */

//  /* USER CODE END SVCall_IRQn 0 */
//  /* USER CODE BEGIN SVCall_IRQn 1 */

//  /* USER CODE END SVCall_IRQn 1 */
//}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

///**
//  * @brief This function handles Pendable request for system service.
//  */
//void PendSV_Handler(void)
//{
//  /* USER CODE BEGIN PendSV_IRQn 0 */

//  /* USER CODE END PendSV_IRQn 0 */
//  /* USER CODE BEGIN PendSV_IRQn 1 */

//  /* USER CODE END PendSV_IRQn 1 */
//}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles PVD interrupt through EXTI line 16.
  */
void PVD_IRQHandler(void)
{
  /* USER CODE BEGIN PVD_IRQn 0 */

  /* USER CODE END PVD_IRQn 0 */
  HAL_PWR_PVD_IRQHandler();
  /* USER CODE BEGIN PVD_IRQn 1 */

  /* USER CODE END PVD_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
#if USE_MVB
  if(Mvb_uart != NULL)
  {
    Mvb_uart->idle_handle();
  }
#endif
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */
#if USE_ETH
  if (Trdp_uart != NULL)
  {
    Trdp_uart->idle_handle();
  }
#endif
  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

  /* USER CODE END DMA2_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc3);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */

  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
#if 0
  /* USER CODE BEGIN USART6_IRQn 0 */
#if USE_485
  if(Rs485_comm != NULL)
  {
    Rs485_comm->idle_handle();
  }
#endif
  /* USER CODE END USART6_IRQn 0 */
  HAL_UART_IRQHandler(&huart6);
  /* USER CODE BEGIN USART6_IRQn 1 */

  /* USER CODE END USART6_IRQn 1 */
#endif
    
#if 1
    uint32_t isrflags = huart6.Instance->SR;
    uint32_t cr1its =  huart6.Instance->CR1;
    uint32_t cr3its = huart6.Instance->CR3;
    uint8_t temp;
    if(((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET)) {
         temp = (uint8_t)(huart6.Instance->DR & (uint8_t)0x00FF);
        if(protocolRxMsg.length < PROTOCOL_RX_SIZE) {
            protocolRxMsg.buffer[protocolRxMsg.length++] = temp;
            protocolRxMsg.tick = osKernelSysTick() + PROTOCOL_TIME_OUT;
        }
    } else if(((isrflags & USART_SR_IDLE) != RESET) && ((cr1its & USART_CR1_IDLEIE) != RESET)) {
        temp = huart6.Instance->DR;
    } else if((isrflags & USART_SR_ORE) != RESET) {
        temp = huart6.Instance->DR;
        temp = huart6.Instance->SR;
    } else {
        HAL_UART_IRQHandler(&huart6);
    }
#endif
}

/**
  * @brief This function handles UART7 global interrupt.
  */
void UART7_IRQHandler(void)
{
  /* USER CODE BEGIN UART7_IRQn 0 */

  /* USER CODE END UART7_IRQn 0 */
  HAL_UART_IRQHandler(&huart7);
  /* USER CODE BEGIN UART7_IRQn 1 */

  /* USER CODE END UART7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
