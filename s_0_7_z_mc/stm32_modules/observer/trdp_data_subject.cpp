#include "trdp_data_subject.h"

bool Trdp_data_subject::register_observer(Trdp_data_observer *obj)
{
  if (obj != NULL)
  {
    obj_list.push_back(obj);
    return true;
  }
  else
  {
    return false;
  }
}

bool Trdp_data_subject::remove_observer(Trdp_data_observer *obj)
{
  if (obj != NULL)
  {
    obj_list.remove(obj);
    return true;
  }
  else
  {
    return false;
  }
}

void Trdp_data_subject::notify_observers(void)
{
  list<Trdp_data_observer *>::iterator it = obj_list.begin();
  while (it != obj_list.end())
  {
    (*it)->update(data);
    ++it;
  }
}
