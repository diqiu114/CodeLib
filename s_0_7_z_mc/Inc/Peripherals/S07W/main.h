/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CELL_POWER_Pin GPIO_PIN_4
#define CELL_POWER_GPIO_Port GPIOF
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOF
#define SW2_Pin GPIO_PIN_13
#define SW2_GPIO_Port GPIOF
#define SW3_Pin GPIO_PIN_14
#define SW3_GPIO_Port GPIOF
#define SW4_Pin GPIO_PIN_15
#define SW4_GPIO_Port GPIOF
#define LED_FAULT_Pin GPIO_PIN_12
#define LED_FAULT_GPIO_Port GPIOE
#define LED_TEST_Pin GPIO_PIN_14
#define LED_TEST_GPIO_Port GPIOE
#define LED_RUN_Pin GPIO_PIN_15
#define LED_RUN_GPIO_Port GPIOE
#define USART3_DE_Pin GPIO_PIN_10
#define USART3_DE_GPIO_Port GPIOD
#define USART6_DE_Pin GPIO_PIN_8
#define USART6_DE_GPIO_Port GPIOC
#define USB_PWR_OUT_EN_Pin GPIO_PIN_15
#define USB_PWR_OUT_EN_GPIO_Port GPIOA
#define ETH_RST_Pin GPIO_PIN_3
#define ETH_RST_GPIO_Port GPIOD
#define MVB_RESET_Pin GPIO_PIN_5
#define MVB_RESET_GPIO_Port GPIOB
#define ETH_ON_Pin GPIO_PIN_0
#define ETH_ON_GPIO_Port GPIOF
#define MVB_ON_Pin GPIO_PIN_1
#define MVB_ON_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
