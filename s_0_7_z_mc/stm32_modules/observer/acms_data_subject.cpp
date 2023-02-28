#include "acms_data_subject.h"

bool Acms_data_subject::register_observer(Acms_data_observer *obj)
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

bool Acms_data_subject::remove_observer(Acms_data_observer *obj)
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

void Acms_data_subject::notify_observers(void)
{
  list<Acms_data_observer *>::iterator it = obj_list.begin();
  while (it != obj_list.end())
  {
    (*it)->update(acms_data);
    ++it;
  }
}
