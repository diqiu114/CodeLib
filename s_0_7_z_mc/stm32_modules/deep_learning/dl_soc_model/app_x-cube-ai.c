
#ifdef __cplusplus
extern "C"
{
#endif
  /**
  ******************************************************************************
  * @file           : app_x-cube-ai.c
  * @brief          : AI program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
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
  /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\6.0.0
  */
/* Includes ------------------------------------------------------------------*/
/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
// #include "main.h"
#include "ai_datatypes_defines.h"

/* USER CODE BEGIN includes */
/* USER CODE END includes */
/* Global AI objects */
static ai_handle dl_model = AI_HANDLE_NULL;
static ai_network_report dl_model_info;

/* Global c-array to handle the activations buffer */
AI_ALIGNED(4)
static ai_u8 activations[AI_DL_MODEL_DATA_ACTIVATIONS_SIZE];

/*  In the case where "--allocate-inputs" option is used, memory buffer can be
 *  used from the activations buffer. This is not mandatory.
 */
// #if !defined(AI_DL_MODEL_INPUTS_IN_ACTIVATIONS)
//   /* Allocate data payload for input tensor */
//   AI_ALIGNED(4)
//   static ai_u8 in_data_s[AI_DL_MODEL_IN_1_SIZE_BYTES];
// #endif

// /*  In the case where "--allocate-outputs" option is used, memory buffer can be
//  *  used from the activations buffer. This is no mandatory.
//  */
// #if !defined(AI_DL_MODEL_OUTPUTS_IN_ACTIVATIONS)
//   /* Allocate data payload for the output tensor */
//   AI_ALIGNED(4)
//   static ai_u8 out_data_s[AI_DL_MODEL_OUT_1_SIZE_BYTES];
// #endif

static int ai_boostrap(ai_handle w_addr, ai_handle act_addr)
{
  ai_error err;

  /* 1 - Create an instance of the model */
  err = ai_dl_model_create(&dl_model, AI_DL_MODEL_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE)
  {
    return -1;
  }

  /* 2 - Initialize the instance */
  const ai_network_params params = {
      AI_DL_MODEL_DATA_WEIGHTS(w_addr),
      AI_DL_MODEL_DATA_ACTIVATIONS(act_addr)};

  if (!ai_dl_model_init(dl_model, &params))
  {
    err = ai_dl_model_get_error(dl_model);
    return -1;
  }

  /* 3 - Retrieve the network info of the created instance */
  if (!ai_dl_model_get_info(dl_model, &dl_model_info))
  {
    err = ai_dl_model_get_error(dl_model);
    ai_dl_model_destroy(dl_model);
    dl_model = AI_HANDLE_NULL;
    return -3;
  }

  return 0;
}

static int ai_run(void *data_in, void *data_out)
{
  ai_i32 batch;

  ai_buffer *ai_input = dl_model_info.inputs;
  ai_buffer *ai_output = dl_model_info.outputs;

  ai_input[0].data = AI_HANDLE_PTR(data_in);
  ai_output[0].data = AI_HANDLE_PTR(data_out);

  batch = ai_dl_model_run(dl_model, ai_input, ai_output);
  if (batch != 1)
  {
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
int acquire_and_process_data(void *data)
{
  return 0;
}

int post_process(void *data)
{
  return 0;
}
/* USER CODE END 2 */

/*************************************************************************
*
*/
bool MX_X_CUBE_AI_Init(void)
{
  /* USER CODE BEGIN 5 */
  return (ai_boostrap(ai_dl_model_data_weights_get(), activations) == 0);
  /* USER CODE END 5 */
}

bool MX_X_CUBE_AI_Process(ai_u8 *input, ai_u8 *output)
{
  if ((!input) || (!output))
  {
    return false;
  }

  /* USER CODE BEGIN 6 */
  uint8_t *in_data = NULL;
  uint8_t *out_data = NULL;

  if (dl_model)
  {

    if ((dl_model_info.n_inputs != 1) || (dl_model_info.n_outputs != 1))
    {
      return false;
    }

    in_data = input;
    out_data = output;

    return (ai_run(in_data, out_data) == 0);
  }

  return false;
}

#ifdef __cplusplus
}
#endif
