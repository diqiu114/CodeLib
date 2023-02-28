#include "batt_data.h"
#include <string.h>

Batt_data::Batt_data(void)
{
  state = NULL;
  cap = NULL;
}

void Batt_data::set_data(Batt_data_t *data, bool update)
{
  batt_data = data;
  
  notify_observers();
}

void Batt_data::set_state_handle(Batt_state *batt_state)
{
  state = batt_state;
}

void Batt_data::set_soc_handle(Batt_cap* batt_cap)
{
  cap = batt_cap;
}

Batt_data::~Batt_data(void)
{
}
