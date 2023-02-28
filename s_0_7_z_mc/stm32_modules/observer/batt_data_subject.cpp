#include "batt_data_subject.h"

bool Batt_data_subject::register_observer(Batt_data_observer *obj)
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

bool Batt_data_subject::remove_observer(Batt_data_observer *obj)
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

void Batt_data_subject::notify_observers(void)
{
  list<Batt_data_observer *>::iterator it = obj_list.begin();
  while (it != obj_list.end())
  {
    (*it)->update(batt_data);
    ++it;
  }
}
