#include "eng_transfer.h"

Eng_transfer::Eng_transfer(vector<Data_convert_if *> &_convert)
{
  convert = _convert;
}
Eng_transfer::~Eng_transfer()
{
}
/**
 * @brief 将输入值按照给定的公式计算得到对应的工程值
 * 
 * @param input_val 输入值
 * @param ch_idx 转换索引
 * @return float 返回得到的值
 */
float Eng_transfer::transfer(float input_val, unsigned int ch_idx)
{
  return (this->convert.at(ch_idx)->convert(input_val));
}

/**
 * @brief 得到对应索引的计算公式
 * 
 * @param _convert 接受公式的指针
 * @param idx 公式索引
 * @return true 存在索引对应的公式
 * @return false 不存在索引对应的公式
 */
bool Eng_transfer::get_rate(Data_convert_if *_convert, unsigned int idx)
{
  if (idx >= convert.size() || _convert == NULL)
  {
    return false;
  }

  _convert = convert.at(idx);

  return true;
}

/**
 * @brief 设置索引对应的公式
 * 
 * @param _convert 需要设置的公式指针
 * @param idx 公式索引
 * @return true 设置成功
 * @return false 设置失败
 */
bool Eng_transfer::set_rate(Data_convert_if *_convert, unsigned int idx)
{
  if (_convert == NULL || idx >= convert.size())
  {
    return false;
  }

  convert.at(idx) = _convert;

  return true;
}
