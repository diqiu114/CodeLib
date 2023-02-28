#include "gm202b.h"
#include <string>

#define ERROR_TIMES (2)
GM202B::GM202B(Mcp3221 *_mcp3221_adc)
{  
  mcp3221_adc = _mcp3221_adc;
}

GM202B::~GM202B()
{

}

bool GM202B::init(void)
{
  mcp3221_adc->init(); 
}
void GM202B::set_base(int _base_val)
{
  base_val = _base_val;
}
int GM202B::get_data(int temp)
{
  int val;
  int temp_compensation;
  val = (int)mcp3221_adc->GetVoltage();
  if(val > base_val)
  {
    val -= base_val;
  }  
//  temp_compensation = temp * TEMP_COMPENSTAIN_K + TEMP_COMPENSTAIN_B;
//  val = val * TEMP_COMPENSTAIN_RATE / temp_compensation;

  val *= MV_PPM;
  return val;
}

int GM202B::get_raw_data(void)
{
  int val;
  val = mcp3221_adc->GetVoltage();
  return val;
}

bool GM202B::is_error()
{
  //zh03b没有重新初始化指令
 if(error_times > ERROR_TIMES)
 {   
    //mode_config(RSET_ENABLE);
//    set_passive_mode();
//    exit_sleep();
    return true;
 }
 return false;
}

