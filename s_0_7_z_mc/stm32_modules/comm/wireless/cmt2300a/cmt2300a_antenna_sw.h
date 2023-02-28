/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-06-29
 * 
 * @brief CMT2300A 天线GPIO切换类
 * 引脚电平说明：如果控制引脚为2个gpio,则默认vector的第一个元素为低,第二个元素为高时天线为接收状态,反之则为发射状态
 *              如果控制引脚为1个gpio,则默认低电平为接收状态,高电平为发射状态
 * 如需要修改电平反向，将reverse参数修改为true即可
 * 
 * ***********************************************************
 */

#ifndef _CMT2300A_ANTENNA_SW_H_
#define _CMT2300A_ANTENNA_SW_H_
#include <vector>
#include "hw_interface\gpio\gpio_if.h"

using namespace std;

class Cmt2300a_antenna_sw
{
public:
  Cmt2300a_antenna_sw(vector<Gpio_if *> &_sw_gpios, bool _reverse = false);
  ~Cmt2300a_antenna_sw();
  bool set_rev_state(void);
  bool set_send_state(void);

private:
  vector<Gpio_if*> sw_gpios;
  bool reverse;
};

#endif // _CMT2300A_ANTENNA_SW_H_
