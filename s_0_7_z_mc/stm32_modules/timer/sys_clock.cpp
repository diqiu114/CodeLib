#include "sys_clock.h"


Sys_clock::Sys_clock()
{
  timestamp_ms = 0;
}

Sys_clock::~Sys_clock()
{
}

bool Sys_clock::add_timer_cb(Timer_callback* timer_obj)
{
  timer_cb_list.push_back(timer_obj);
  return true;
}

int Sys_clock::calc_timeout_ts(int timeout)
{
  // timestamp overflow. Recalculate all the timeouts.
  if(timestamp_ms + timeout < 0)
  {
    for (list<Timer_callback*>::iterator it = timer_cb_list.begin(); it != timer_cb_list.end(); ++it)
    {
      (*it)->timeout_timestamp -= timestamp_ms;
    }
    timestamp_ms = 0;
  }
  return timeout + timestamp_ms;
}

bool Sys_clock::reset_timer_cb(Timer_callback* timer_obj)
{
  for (list<Timer_callback*>::iterator it = timer_cb_list.begin(); it != timer_cb_list.end(); ++it)
  {
    if(*it == timer_obj)
    {
      (*it)->timeout_timestamp = calc_timeout_ts((*it)->timeout_ms);
    }
  }
  return true;
}

bool Sys_clock::remove_timer_cb(Timer_callback* timer_obj)
{
  for (list<Timer_callback*>::iterator it = timer_cb_list.begin(); it != timer_cb_list.end(); ++it)
  {
    if(*it == timer_obj)
    {
      timer_cb_list.erase(it);
    }
  }
  return true;
}

void Sys_clock::update()
{
  timestamp_ms++;
  for (list<Timer_callback*>::iterator it = timer_cb_list.begin(); it != timer_cb_list.end(); ++it)
  {
    if(timestamp_ms >= (*it)->timeout_timestamp)
    {
      (*it)->timeout_callback();
      (*it)->timeout_timestamp = calc_timeout_ts((*it)->timeout_ms);
    }
  }
}
