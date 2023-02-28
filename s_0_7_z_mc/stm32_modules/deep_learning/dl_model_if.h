/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      深度学习模型接口
*
***********************************************************/

#ifndef _DL_MODEL_IF_H_
#define _DL_MODEL_IF_H_

class Dl_model_if
{
public:
  virtual bool init(void) = 0;
  virtual bool process(unsigned char *input, unsigned int input_size, unsigned char *output) = 0;
  virtual ~Dl_model_if(){};
};

#endif // _DL_MODEL_IF_H_
