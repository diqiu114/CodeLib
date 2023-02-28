/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      深度学习模型应用类
* 依赖于dl_model.h/.c 及dl_model_data.h/.c(宏定义名称绑定)
*
***********************************************************/

#ifndef _DL_MODEL_APP_H_
#define _DL_MODEL_APP_H_
#include "..\dl_model_if.h"
#include "app_x-cube-ai.h"
#include <queue>
using namespace std;

// 超时时间,记录数据输入的最大间隔次数, 具体每次的间隔由外部定义
// 比如外部1S间隔,那么默认为30S未接收到数据,就自动清空vector buffer内容
#define DL_MODEL_TIMEOUT (30)

class Dl_model_app : public Dl_model_if
{
public:
  Dl_model_app(unsigned int _timeout = DL_MODEL_TIMEOUT, unsigned int input_buff_size_bytes = AI_DL_MODEL_IN_1_SIZE_BYTES, unsigned int output_buff_size_bytes = AI_DL_MODEL_OUT_1_SIZE_BYTES);
  virtual ~Dl_model_app();
  virtual bool init(void);
  virtual bool process(unsigned char *input, unsigned int input_size, unsigned char *output);
  void time_count(void);
private:
  bool init_state;
  vector<unsigned char> vector_buffer;
  unsigned char *input_buffer;
  unsigned char *output_buffer;
  unsigned int input_buff_size;
  unsigned int output_buff_size;
  unsigned int timeout_max;
  unsigned int timeout;
};

#endif // _DL_MODEL_APP_H_
