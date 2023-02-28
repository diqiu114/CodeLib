/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      数据转换接口

***********************************************************/

#ifndef _DATA_CONVERT_H_
#define _DATA_CONVERT_H_

class Data_convert_if
{
public:
  virtual float convert(float value1, float value2 = 0, float value3 = 0) = 0;
  virtual ~Data_convert_if(){};
};

#endif //_DATA_CONVERT_H_
