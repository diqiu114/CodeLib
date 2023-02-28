/**
  ******************************************************************************
  * @file    dl_model.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Apr 21 11:31:24 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "dl_model.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



/*
#define AI_TOOLS_VERSION_MAJOR 6
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0
#define AI_TOOLS_VERSION_EXTRA "RC6"

*/

/*
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 4
#define AI_TOOLS_API_VERSION_MICRO 0
*/

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_dl_model
 
#undef AI_DL_MODEL_MODEL_SIGNATURE
#define AI_DL_MODEL_MODEL_SIGNATURE     "7a6b95c896d408fe543c56c73a45d52d"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Apr 21 11:31:24 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_DL_MODEL_N_BATCHES
#define AI_DL_MODEL_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array input_0_output_array;   /* Array #0 */
AI_STATIC ai_array conv1d_1_output_array;   /* Array #1 */
AI_STATIC ai_array conv1d_2_output_array;   /* Array #2 */
AI_STATIC ai_array gru_1_output_array;   /* Array #3 */
AI_STATIC ai_array dense_1_output_array;   /* Array #4 */
AI_STATIC ai_array conv1d_1_weights_array;   /* Array #5 */
AI_STATIC ai_array conv1d_1_bias_array;   /* Array #6 */
AI_STATIC ai_array conv1d_2_weights_array;   /* Array #7 */
AI_STATIC ai_array conv1d_2_bias_array;   /* Array #8 */
AI_STATIC ai_array gru_1_kernel_array;   /* Array #9 */
AI_STATIC ai_array gru_1_recurrent_array;   /* Array #10 */
AI_STATIC ai_array gru_1_bias_array;   /* Array #11 */
AI_STATIC ai_array dense_1_weights_array;   /* Array #12 */
AI_STATIC ai_array dense_1_bias_array;   /* Array #13 */
AI_STATIC ai_array conv1d_1_scratch0_array;   /* Array #14 */
AI_STATIC ai_array gru_1_scratch0_array;   /* Array #15 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor input_0_output;   /* Tensor #0 */
AI_STATIC ai_tensor conv1d_1_output;   /* Tensor #1 */
AI_STATIC ai_tensor conv1d_2_output;   /* Tensor #2 */
AI_STATIC ai_tensor gru_1_output;   /* Tensor #3 */
AI_STATIC ai_tensor dense_1_output;   /* Tensor #4 */
AI_STATIC ai_tensor conv1d_1_weights;   /* Tensor #5 */
AI_STATIC ai_tensor conv1d_1_bias;   /* Tensor #6 */
AI_STATIC ai_tensor conv1d_2_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv1d_2_bias;   /* Tensor #8 */
AI_STATIC ai_tensor gru_1_kernel;   /* Tensor #9 */
AI_STATIC ai_tensor gru_1_recurrent;   /* Tensor #10 */
AI_STATIC ai_tensor gru_1_bias;   /* Tensor #11 */
AI_STATIC ai_tensor dense_1_weights;   /* Tensor #12 */
AI_STATIC ai_tensor dense_1_bias;   /* Tensor #13 */
AI_STATIC ai_tensor conv1d_1_scratch0;   /* Tensor #14 */
AI_STATIC ai_tensor gru_1_scratch0;   /* Tensor #15 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv1d_1_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv1d_2_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain gru_1_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_1_chain;   /* Chain #3 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv1d_1_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d conv1d_2_layer; /* Layer #1 */
AI_STATIC ai_layer_gru gru_1_layer; /* Layer #2 */
AI_STATIC ai_layer_dense dense_1_layer; /* Layer #3 */




/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 60, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 180, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 120, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  gru_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 50, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 160, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1600, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  gru_1_kernel_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3000, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  gru_1_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7500, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  gru_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 150, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 50, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_1_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 60, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  gru_1_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 300, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 30), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &input_0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_1_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 20, 1, 9), AI_STRIDE_INIT(4, 4, 4, 80, 80),
  1, &conv1d_1_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_2_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 20, 1, 6), AI_STRIDE_INIT(4, 4, 4, 80, 80),
  1, &conv1d_2_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  gru_1_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 50, 1, 1), AI_STRIDE_INIT(4, 4, 4, 200, 200),
  1, &gru_1_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_1_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_1_weights, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 2, 1, 4, 20), AI_STRIDE_INIT(4, 4, 8, 8, 32),
  1, &conv1d_1_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_1_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 20, 1, 1), AI_STRIDE_INIT(4, 4, 4, 80, 80),
  1, &conv1d_1_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_2_weights, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 20, 1, 4, 20), AI_STRIDE_INIT(4, 4, 80, 80, 320),
  1, &conv1d_2_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_2_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 20, 1, 1), AI_STRIDE_INIT(4, 4, 4, 80, 80),
  1, &conv1d_2_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  gru_1_kernel, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 20, 1, 1, 150), AI_STRIDE_INIT(4, 4, 80, 80, 80),
  1, &gru_1_kernel_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  gru_1_recurrent, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 50, 1, 1, 150), AI_STRIDE_INIT(4, 4, 200, 200, 200),
  1, &gru_1_recurrent_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  gru_1_bias, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 150, 1, 1), AI_STRIDE_INIT(4, 4, 4, 600, 600),
  1, &gru_1_bias_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_weights, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 50, 1, 1, 1), AI_STRIDE_INIT(4, 4, 200, 200, 200),
  1, &dense_1_weights_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_1_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_1_scratch0, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 20, 1, 3), AI_STRIDE_INIT(4, 4, 4, 80, 80),
  1, &conv1d_1_scratch0_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  gru_1_scratch0, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 300, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1200, 1200),
  1, &gru_1_scratch0_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv1d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv1d_1_weights, &conv1d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv1d_1_layer, 1,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &conv1d_1_chain,
  &AI_NET_OBJ_INSTANCE, &conv1d_2_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(1, 3), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 3), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv1d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv1d_2_weights, &conv1d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv1d_2_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &conv1d_2_chain,
  &AI_NET_OBJ_INSTANCE, &gru_1_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gru_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gru_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 5, &gru_1_kernel, &gru_1_recurrent, &gru_1_bias, NULL, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gru_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gru_1_layer, 3,
  GRU_TYPE, 0x0, NULL,
  gru, forward_gru,
  &gru_1_chain,
  &AI_NET_OBJ_INSTANCE, &dense_1_layer, AI_STATIC, 
  .n_units = 50, 
  .activation_nl = nl_func_relu_array_f32, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .reset_after = false, 
  .recurrent_nl = nl_func_hard_sigmoid_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gru_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_1_weights, &dense_1_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_layer, 4,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_1_chain,
  &AI_NET_OBJ_INSTANCE, &dense_1_layer, AI_STATIC, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 50004, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 1880, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DL_MODEL_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_DL_MODEL_OUT_NUM, &dense_1_output),
  &conv1d_1_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool dl_model_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv1d_1_output_array.data = AI_PTR(activations + 360);
    conv1d_1_output_array.data_start = AI_PTR(activations + 360);
    conv1d_2_output_array.data = AI_PTR(activations + 200);
    conv1d_2_output_array.data_start = AI_PTR(activations + 200);
    gru_1_output_array.data = AI_PTR(activations + 0);
    gru_1_output_array.data_start = AI_PTR(activations + 0);
    dense_1_output_array.data = AI_PTR(NULL);
    dense_1_output_array.data_start = AI_PTR(NULL);
    conv1d_1_scratch0_array.data = AI_PTR(activations + 120);
    conv1d_1_scratch0_array.data_start = AI_PTR(activations + 120);
    gru_1_scratch0_array.data = AI_PTR(activations + 680);
    gru_1_scratch0_array.data_start = AI_PTR(activations + 680);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool dl_model_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    conv1d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv1d_1_weights_array.data = AI_PTR(weights + 0);
    conv1d_1_weights_array.data_start = AI_PTR(weights + 0);
    conv1d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv1d_1_bias_array.data = AI_PTR(weights + 640);
    conv1d_1_bias_array.data_start = AI_PTR(weights + 640);
    conv1d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv1d_2_weights_array.data = AI_PTR(weights + 720);
    conv1d_2_weights_array.data_start = AI_PTR(weights + 720);
    conv1d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv1d_2_bias_array.data = AI_PTR(weights + 7120);
    conv1d_2_bias_array.data_start = AI_PTR(weights + 7120);
    gru_1_kernel_array.format |= AI_FMT_FLAG_CONST;
    gru_1_kernel_array.data = AI_PTR(weights + 7200);
    gru_1_kernel_array.data_start = AI_PTR(weights + 7200);
    gru_1_recurrent_array.format |= AI_FMT_FLAG_CONST;
    gru_1_recurrent_array.data = AI_PTR(weights + 19200);
    gru_1_recurrent_array.data_start = AI_PTR(weights + 19200);
    gru_1_bias_array.format |= AI_FMT_FLAG_CONST;
    gru_1_bias_array.data = AI_PTR(weights + 49200);
    gru_1_bias_array.data_start = AI_PTR(weights + 49200);
    dense_1_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_1_weights_array.data = AI_PTR(weights + 49800);
    dense_1_weights_array.data_start = AI_PTR(weights + 49800);
    dense_1_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_1_bias_array.data = AI_PTR(weights + 50000);
    dense_1_bias_array.data_start = AI_PTR(weights + 50000);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_dl_model_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_DL_MODEL_MODEL_NAME,
      .model_signature   = AI_DL_MODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 78811,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_dl_model_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_dl_model_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_dl_model_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_dl_model_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= dl_model_configure_weights(net_ctx, &params->params);
  ok &= dl_model_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_dl_model_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_dl_model_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_DL_MODEL_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

