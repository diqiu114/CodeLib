#include "gpi.h"
#include "string.h"

Gpi::Gpi(Gpi_Info* info, unsigned int cnt)
{  
  gpi_info = new Gpi_Info[cnt];
  pin_cnt = cnt;
  reverse_ret = false;
  memcpy(gpi_info, info, sizeof(Gpi_Info)*cnt);
}

void Gpi::reverse(void)
{
  reverse_ret = true;
}

unsigned int Gpi::read(void)
{
  unsigned int ret = 0;
  int idx = 0;
  for(idx=0; idx < pin_cnt; idx++)
  {
    ret |= ( read(idx) << idx );
  }

  return ret;
}

unsigned char Gpi::read(unsigned char idx)
{
  if( idx >= pin_cnt )
  {
    return 0;
  }

  if( reverse_ret )
  {
    unsigned char state = (unsigned char)(HAL_GPIO_ReadPin(gpi_info[idx].port, gpi_info[idx].pin));
    return ( !state & (1<<0) );
  }
  else
  {
    return (unsigned char)(HAL_GPIO_ReadPin(gpi_info[idx].port, gpi_info[idx].pin));
  }
}

Gpi::~Gpi()
{

}

