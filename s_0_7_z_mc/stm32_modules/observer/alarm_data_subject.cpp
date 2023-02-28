#include "alarm_data_subject.h"

bool Alarm_data_subject::register_observer(Alarm_data_observer *obj)
{
  if( obj != NULL )
  {
    obj_list.push_back(obj);
    return true;
  }
  else
  {
    return false;
  }
  
}

bool Alarm_data_subject::remove_observer(Alarm_data_observer *obj)
{
  if( obj != NULL )
  {
    obj_list.remove(obj);
    return true;
  }
  else
  {
    return false;
  }
  
}

void Alarm_data_subject::notify_observers(void)
{
  list<Alarm_data_observer *>::iterator it = obj_list.begin();
  while (it != obj_list.end())
  {
    (*it)->update(alarm_data);
    ++it;
  }
}
