/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      工程值校准
*
* 版本:
* V1.0 2018-11-25 初始程序编写 
***********************************************************/

#ifndef _ENG_CALIB_H_
#define _ENG_CALIB_H_
#include "..\data_convert\data_convert_if.h"
#include <vector>

using namespace std;
class Eng_calib
{
  public:
    Eng_calib(vector<Data_convert_if *> &_convert);
    
    float calib(float input_val, unsigned int idx);
    Data_convert_if * get_calib(unsigned int idx);
    bool set_calib(Data_convert_if * _calib, unsigned int idx);

    ~Eng_calib();
  private:
    vector<Data_convert_if *> calib_para;
};


#endif // _ENG_CALIB_H_
