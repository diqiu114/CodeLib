#ifndef __ADPD_APP_H__
#define __ADPD_APP_H__

#include <stdint.h>

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <time.h>

#include "AdpdDrv.h"

#include "Common.h"

#include "smoke_detect.h"

class Adpd_app
{
  public:
  Adpd_app();
  ~Adpd_app();
  bool get_data(dataADPD* data);
  void init();
  bool is_error();
  
  private:
  unsigned char error_times;
};





#endif
