#include "dl_method_discharge.h"
#include <stdlib.h>

/**
 * @brief Construct a new Dl_method_discharge::Dl_method_discharge object
 * 
 * @param _dl_model 深度学习模型接口
 */
Dl_method_discharge::Dl_method_discharge(Dl_model_if *_dl_model)
{
  dl_model = _dl_model;
  preprocess = NULL;
  postprocess = NULL;
}

/**
 * @brief Destroy the Dl_method_discharge::Dl_method_discharge object
 * 
 */
Dl_method_discharge::~Dl_method_discharge()
{
  if(dl_model != NULL)
  {
    delete dl_model;
  }
}

/**
 * @brief 设置数据前置处理(输入数据)回调函数
 * 
 * @param func 函数指针
 * @return true 处理成功
 * @return false 处理失败
 */
bool Dl_method_discharge::set_preprocess_callback(data_normalize func)
{
  preprocess = func;
  return true;
}

/**
 * @brief 设置数据后置处理(输出数据)回调函数
 * 
 * @param func 函数指针
 * @return true 处理成功
 * @return false 处理失败
 */
bool Dl_method_discharge::set_postprocess_callback(data_normalize func)
{
  postprocess = func;
  return true;
}

/**
 * @brief 放电处理函数
 * 
 * @param batt_data 电池数据
 * @param cur_cap 当前容量
 * @param update_clk_in_hours 处理间隔时间(深度学习类未使用)
 * @return float 返回处理后的容量值
 */
float Dl_method_discharge::discharge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours)
{
  float ret = 0;

  batt_feature[0] = batt_data.cur;
  batt_feature[1] = batt_data.volt;
  
//  batt_feature[2] = batt_data.temp;

  if(preprocess != NULL)
  {
    preprocess(batt_feature, BATT_FEATURE_CNT);
  }
  
  if ( dl_model->process((unsigned char*)batt_feature, sizeof(batt_feature), (unsigned char*)&ret) )
  {
    if (postprocess != NULL)
    {
      postprocess(&ret, sizeof(ret));
    }
    
    return ret;
  }
  else
  {
    return cur_cap;
  }
}
