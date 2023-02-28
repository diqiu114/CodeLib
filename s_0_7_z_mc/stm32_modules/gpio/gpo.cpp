#include "gpo.h"
#include "string.h"

Gpo::Gpo(Gpo_Info* info, unsigned int cnt)
{  
  gpo_info = new Gpo_Info[cnt];
  pin_cnt = cnt;
  reverse_control = false;
  memcpy(gpo_info, info, sizeof(Gpo_Info)*cnt);
}

void Gpo::reverse(void)
{
  reverse_control = true;
}

void Gpo::on(unsigned int idx)
{
  if( reverse_control == true)
  {
    HAL_GPIO_WritePin(gpo_info[idx].port, gpo_info[idx].pin, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(gpo_info[idx].port, gpo_info[idx].pin, GPIO_PIN_SET);
  }
}

void Gpo::off(unsigned int idx)
{
  if( reverse_control == true)
  {
    HAL_GPIO_WritePin(gpo_info[idx].port, gpo_info[idx].pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(gpo_info[idx].port, gpo_info[idx].pin, GPIO_PIN_RESET);
  }
}

void Gpo::toggle(unsigned int idx)
{
  HAL_GPIO_TogglePin(gpo_info[idx].port, gpo_info[idx].pin);

}

Gpo::~Gpo()
{

}

