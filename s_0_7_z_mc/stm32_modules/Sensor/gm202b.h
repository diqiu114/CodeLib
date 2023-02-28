/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      纬盛科技 GM-202B 烟雾模块驱动程序
*
***********************************************************/
#ifndef _GM_202B_H_
#define _GM_202B_H_

#include <stdbool.h>
#include "..\adc\Mcp3221_adc\mcp3221_adc.h"

#define MV_PPM (24)//(24)
#define TEMP_COMPENSTAIN_K 55
#define TEMP_COMPENSTAIN_B 8956
#define TEMP_COMPENSTAIN_RATE 10000

class GM202B
{
public:
  GM202B(Mcp3221 *_mcp3221_adc);
  ~GM202B();

  bool init(void);
  int get_data(int temp_compensation);
  bool is_error();
  void set_base(int _base_val);
  int get_raw_data(void);

private:
  Mcp3221 *mcp3221_adc;
  int base_val;
  unsigned short error_times;
};

#endif // _GM_202B_H_
