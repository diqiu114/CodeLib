#ifndef SYS_CLOCK_H_H
#define SYS_CLOCK_H_H
#include <list>
using namespace std;

class Timer_callback
{
public:
  int timeout_ms;
  int timeout_timestamp;
  virtual void timeout_callback() = 0;
};

class Sys_clock
{
public:
  Sys_clock();
  ~Sys_clock();
  void update();
  int calc_timeout_ts(int timetout);
  bool reset_timer_cb(Timer_callback* timer_obj);
  bool add_timer_cb(Timer_callback* timer_obj);
  bool remove_timer_cb(Timer_callback* timer_obj);
  int timestamp_ms;
private:
  list<Timer_callback*> timer_cb_list;
};

#endif
