#ifndef MEASURE_INTERFACES_H_H
#define MEASURE_INTERFACES_H_H

#include <vector>
#include "timer\sys_clock.h"
using namespace std;

enum Temp_sensor_status{
  READY = 0,
  READ_READY = 1,
  BUSY = 2,
};

class Temperature_sensor_if :public Timer_callback
{
public:
  virtual ~Temperature_sensor_if(){};
  virtual void start(void) = 0;
  virtual float get_temp(void) = 0;
  virtual Temp_sensor_status get_status(void) = 0;
};

class Voltage_sensor_if
{
public:
  virtual ~Voltage_sensor_if(){};
  virtual float get_volt() = 0;
};

class Res_sensor_if
{
public:
  virtual ~Res_sensor_if(){};
  virtual vector<float> *get_res() = 0;
  virtual unsigned int get_res_chn_cnt() = 0;
  virtual float get_drop_volt() = 0;   
  virtual float get_dis_curr() = 0; 
};
#endif
