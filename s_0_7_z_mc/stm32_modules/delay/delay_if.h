/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      delay interface
*
***********************************************************/

#ifndef _DELAY_IF_H_
#define _DELAY_IF_H_

class Delay_if
{
public:
  virtual void delay(unsigned int cnt) = 0;
  virtual ~Delay_if(){};
};

#endif // _DELAY_IF_H_
