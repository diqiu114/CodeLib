/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      AD采样转换为工程值类
*
* 版本:
* V1.1 2018-11-29 将比例更改为kx+b的方式进行计算
* V1.0 2018-11-25 初始程序编写 
***********************************************************/

#ifndef _ENG_TRANSFER_H_
#define _ENG_TRANSFER_H_
#include "..\data_convert\data_convert_if.h"
#include <vector>

using namespace std;

class Eng_transfer
{
public:
  Eng_transfer(vector<Data_convert_if *> &_convert);
  virtual ~Eng_transfer();

  float transfer(float input_val, unsigned int ch_idx = 0);
  bool get_rate(Data_convert_if *convert, unsigned int idx);
  bool set_rate(Data_convert_if *convert, unsigned int idx);


private:
  vector<Data_convert_if *> convert;
};

#endif // _ENG_TRANSFER_H_
