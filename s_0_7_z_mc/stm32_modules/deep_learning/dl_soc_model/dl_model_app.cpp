#include "dl_model_app.h"

/**
 * @brief Construct a new Dl_model_app::Dl_model_app object
 * 
 * @param input_buff_size_bytes 输入数据大小(bytes),一定要与模型本身的输入大小匹配
 * @param output_buff_size_bytes 输出数据大小(bytes),一定要与模型本身的输出大小匹配
 */
Dl_model_app::Dl_model_app(unsigned int _timeout, unsigned int input_buff_size_bytes, unsigned int output_buff_size_bytes)
{
  input_buffer = NULL;
  output_buffer = NULL;
  input_buff_size = input_buff_size_bytes;
  output_buff_size = output_buff_size_bytes;
  init_state = init();
  timeout_max = _timeout;
  timeout = 0;
}

/**
 * @brief Destroy the Dl_model_app::Dl_model_app object
 * 
 */
Dl_model_app::~Dl_model_app()
{
  if (input_buffer != NULL)
  {
    delete[] input_buffer;
    input_buffer = NULL;
  }

  if (output_buffer != NULL)
  {
    delete[] output_buffer;
    output_buffer = NULL;
  }

  if (!vector_buffer.empty())
  {
    vector_buffer.clear();
  }
}

/**
 * @brief 模型初始化以及输入输出buffer空间申请
 * 
 * @return true 初始化成功
 * @return false 初始化失败
 */
bool Dl_model_app::init(void)
{
  bool ret = true;

  ret = ret && MX_X_CUBE_AI_Init();

  input_buffer = new unsigned char[input_buff_size];
  ret = ret && (input_buffer != NULL);
  memset(input_buffer, 0, input_buff_size);

  output_buffer = new unsigned char[output_buff_size];
  ret = ret && (output_buffer != NULL);
  memset(output_buffer, 0, output_buff_size);

  if (ret)
  {
    init_state = true;
  }
  else
  {
    init_state = false;
  }

  return init_state;
}

/**
 * @brief 深度学习模型处理函数
 * 
 * @param input 输出数据指针
 * @param input_size 输入数据大小(必须与模型输入数据大小相匹配)
 * @param output 输出数据指针
 * @return true 处理成功
 * @return false 处理失败(失败通常是由于数据量未达到模型要求所致)
 */
bool Dl_model_app::process(unsigned char *input, unsigned int input_size, unsigned char *output)
{
  if (!init_state || input == NULL || output == NULL)
  {
    return false;
  }

  unsigned char *data = input;
  
  if( timeout > timeout_max)
  {
    vector_buffer.clear();
  }

  timeout = 0;

  // 将数据存储至vector中
  for (int i = 0; i < input_size; i++)
  {
    if (vector_buffer.size() >= input_buff_size)
    {
      vector_buffer.erase(vector_buffer.begin());
      vector_buffer.push_back(*data);
    }
    else
    {
      // 数据量不足时,返回false
      vector_buffer.push_back(*data);
    }
    data++;
  }

  if (vector_buffer.size() < input_buff_size)
  {
    return false;
  }

  // 数据量足够预测时,将数据放到input buffer中,再送给X-CUBE-AI中的函数进行预测
  memcpy(input_buffer, &vector_buffer[0], input_buff_size);

  if (MX_X_CUBE_AI_Process(input_buffer, output_buffer))
  {
    memcpy(output, output_buffer, output_buff_size);
    // test_ret = *((ai_float*)(output_buffer));
    return true;
  }
  else
  {
    return false;
  }
}

void Dl_model_app::time_count(void)
{
  timeout++;
}
