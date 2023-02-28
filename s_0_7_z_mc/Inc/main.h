/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define TEMP6_Pin GPIO_PIN_3
#define TEMP6_GPIO_Port GPIOF
#define TEMP1_Pin GPIO_PIN_6
#define TEMP1_GPIO_Port GPIOF
#define TEMP2_Pin GPIO_PIN_7
#define TEMP2_GPIO_Port GPIOF
#define TEMP3_Pin GPIO_PIN_8
#define TEMP3_GPIO_Port GPIOF
#define TEMP4_Pin GPIO_PIN_9
#define TEMP4_GPIO_Port GPIOF
#define TEMP5_Pin GPIO_PIN_10
#define TEMP5_GPIO_Port GPIOF
#define TEMP7_Pin GPIO_PIN_0
#define TEMP7_GPIO_Port GPIOC
#define TEMP8_Pin GPIO_PIN_1
#define TEMP8_GPIO_Port GPIOC
#define TEMP9_Pin GPIO_PIN_2
#define TEMP9_GPIO_Port GPIOC
#define TEMP10_Pin GPIO_PIN_3
#define TEMP10_GPIO_Port GPIOC
#define BATT_VOLT1_Pin GPIO_PIN_0
#define BATT_VOLT1_GPIO_Port GPIOA
#define BATT_VOLT2_Pin GPIO_PIN_1
#define BATT_VOLT2_GPIO_Port GPIOA
#define BATT_VOLT3_Pin GPIO_PIN_2
#define BATT_VOLT3_GPIO_Port GPIOA
#define BATT_VOLT4_Pin GPIO_PIN_3
#define BATT_VOLT4_GPIO_Port GPIOA
#define BATT_VOLT5_Pin GPIO_PIN_4
#define BATT_VOLT5_GPIO_Port GPIOA
#define BATT_VOLT6_Pin GPIO_PIN_5
#define BATT_VOLT6_GPIO_Port GPIOA
#define BATT_TOTAL_VOLT_Pin GPIO_PIN_7
#define BATT_TOTAL_VOLT_GPIO_Port GPIOA
#define BATT_CUR1_Pin GPIO_PIN_0
#define BATT_CUR1_GPIO_Port GPIOB
#define BATT_CUR2_Pin GPIO_PIN_1
#define BATT_CUR2_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOF
#define SW2_Pin GPIO_PIN_13
#define SW2_GPIO_Port GPIOF
#define SW3_Pin GPIO_PIN_14
#define SW3_GPIO_Port GPIOF
#define SW4_Pin GPIO_PIN_15
#define SW4_GPIO_Port GPIOF
#define LED_FLT_Pin GPIO_PIN_12
#define LED_FLT_GPIO_Port GPIOE
#define LED_COMM_Pin GPIO_PIN_14
#define LED_COMM_GPIO_Port GPIOE
#define LED_RUN_Pin GPIO_PIN_15
#define LED_RUN_GPIO_Port GPIOE
#define ETH_RST_Pin GPIO_PIN_3
#define ETH_RST_GPIO_Port GPIOD
#define DIN1_Pin GPIO_PIN_12
#define DIN1_GPIO_Port GPIOG
#define DIN2_Pin GPIO_PIN_13
#define DIN2_GPIO_Port GPIOG
#define DIN3_Pin GPIO_PIN_14
#define DIN3_GPIO_Port GPIOG
#define DIN4_Pin GPIO_PIN_15
#define DIN4_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
