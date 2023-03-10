/**
 ******************************************************************************
 * File Name          : TIM.c
 * Description        : This file provides code for the configuration
 *                      of the TIM instances.
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2017 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

// Includes ------------------------------------------------------------------
#include "tim.h"

// USER CODE BEGIN 0

// USER CODE END 0

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;

// TIM2 init function
void MX_TIM2_Init(uint32_t Prescaler, uint32_t Period)
{
  __HAL_RCC_TIM2_CLK_ENABLE();

  // initalize timer
  htim2.Instance           = TIM2;
  htim2.Init.Period        = Period;
  // Prescaler = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;
  htim2.Init.Prescaler     = Prescaler;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode   = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&htim2);

  //Set priority
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  HAL_NVIC_SetPriority(TIM2_IRQn, 0x5, 0x0);
  HAL_TIM_Base_Start_IT(&htim2); 
}

// TIM3 init function
void TIM3_Init(uint32_t Prescaler, uint32_t Period)
{
  __HAL_RCC_TIM2_CLK_ENABLE();

  // initalize timer
  htim3.Instance           = TIM3;
  htim3.Init.Period        = Period;
  // Prescaler = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;
  htim3.Init.Prescaler     = Prescaler;
  htim3.Init.ClockDivision = 0;
  htim3.Init.CounterMode   = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&htim3);

  //Set priority
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  HAL_NVIC_SetPriority(TIM3_IRQn, 0x5, 0x0);
}


// TIM5 init function
void MX_TIM5_Init(uint32_t Prescaler, uint32_t Period)
{
  __HAL_RCC_TIM5_CLK_ENABLE();

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef      sConfigOC;

  htim5.Instance           = TIM5;
  htim5.Init.Prescaler     = Prescaler;
  htim5.Init.CounterMode   = TIM_COUNTERMODE_UP;
  htim5.Init.Period        = Period;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_DeInit(&htim5);
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode     = TIM_OCMODE_PWM1;
  sConfigOC.Pulse      = Period+1 / 2;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  //start timer
  // HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
}


/**
 * HAL_TIM_Base_MspInit
 * @param tim_baseHandle TODO
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{
  if(tim_baseHandle->Instance == TIM2)
  {
    // USER CODE BEGIN TIM2_MspInit 0

    // USER CODE END TIM2_MspInit 0
    // Peripheral clock enable
    __HAL_RCC_TIM2_CLK_ENABLE();
    // USER CODE BEGIN TIM2_MspInit 1

    // USER CODE END TIM2_MspInit 1
  }
  else if(tim_baseHandle->Instance == TIM5)
  {
    __HAL_RCC_TIM5_CLK_ENABLE();
  }
}

/**
 * HAL_TIM_Base_MspDeInit
 * @param tim_baseHandle TODO
 */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{
  if(tim_baseHandle->Instance == TIM2)
  {
    // USER CODE BEGIN TIM2_MspDeInit 0

    // USER CODE END TIM2_MspDeInit 0
    // Peripheral clock disable
    __HAL_RCC_TIM2_CLK_DISABLE();
    // USER CODE BEGIN TIM2_MspDeInit 1

    // USER CODE END TIM2_MspDeInit 1
  }
  else if(tim_baseHandle->Instance == TIM5)
  {
    // USER CODE BEGIN TIM2_MspDeInit 0

    // USER CODE END TIM2_MspDeInit 0
    // Peripheral clock disable
    __HAL_RCC_TIM5_CLK_DISABLE();
  }
}

// USER CODE BEGIN 1

// USER CODE END 1

/**
 * @}
 */

/**
 * @}
 */

//*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE***
