#include "cmt2300a_antenna_sw.h"

Cmt2300a_antenna_sw::Cmt2300a_antenna_sw(vector<Gpio_if *> &_sw_gpios, bool _reverse)
{
  sw_gpios = _sw_gpios;
  reverse = _reverse;
}

Cmt2300a_antenna_sw::~Cmt2300a_antenna_sw()
{
}

bool Cmt2300a_antenna_sw::set_rev_state(void)
{
  if(sw_gpios.size() == 1 )
  {
    if(!reverse)
    {
      sw_gpios[0]->set_low();
    }
    else
    {
      sw_gpios[0]->set_hi();
    }

    return true;
  }
  else if(sw_gpios.size() == 2)
  {
    if(!reverse)
    {
      sw_gpios[0]->set_low();
      sw_gpios[1]->set_hi();
    }
    else
    {
      sw_gpios[0]->set_hi();
      sw_gpios[1]->set_low();
    }

    return true;
  }
  else
  {
    return false;
  }
}

bool Cmt2300a_antenna_sw::set_send_state(void)
{
    if(sw_gpios.size() == 1 )
  {
    if(!reverse)
    {
      sw_gpios[0]->set_hi();
    }
    else
    {
      sw_gpios[0]->set_low();
    }

    return true;
  }
  else if(sw_gpios.size() == 2)
  {
    if(!reverse)
    {
      sw_gpios[0]->set_hi();
      sw_gpios[1]->set_low();
    }
    else
    {
      sw_gpios[0]->set_low();
      sw_gpios[1]->set_hi();
    }

    return true;
  }
  else
  {
    return false;
  }
}
