#include "alarm_state.h"
#include "paras.h"

Alarm_state::Alarm_state()
{

  alarm.reset();
  cell_volt_over = new bool[Dev_paras.volt_cnt];
  cell_volt_low = new bool[Dev_paras.volt_cnt];
  cell_temp_over = new bool[Dev_paras.temp_cnt];
  cell_comm_err = new bool[CELL_CNT];
  if(cell_volt_over != NULL)
    memset(cell_volt_over, 0, Dev_paras.volt_cnt);
  if(cell_volt_low != NULL)
    memset(cell_volt_low, 0, Dev_paras.volt_cnt);
  if(cell_temp_over != NULL)
    memset(cell_temp_over, 0, Dev_paras.temp_cnt);
  if(cell_comm_err != NULL)
    memset(cell_comm_err, 0, CELL_CNT);
}

void Alarm_state::update(Alarm_data_t* alm_data, unsigned char opt)
{
  if (alm_data == NULL)
  {
    return;
  } 
  
  int pos = 0;
  if(alm_data->alm_code == CELL_VOLT_HIGH)
  {
    if(alm_data->alm_status == ALARMED)
    {
      cell_volt_over[alm_data->id - 1] = true;
    }
    else if(alm_data->alm_status == ALARM_RESET)
    {
      cell_volt_over[alm_data->id - 1] = false;
    }
  }
  else if(alm_data->alm_code == CELL_VOLT_LOW)
  {
    if(alm_data->alm_status == ALARMED)
    {
      cell_volt_low[alm_data->id - 1] = true;
    }
    else if(alm_data->alm_status == ALARM_RESET)
    {
      cell_volt_low[alm_data->id - 1] = false;
    }
  }
  else if(alm_data->alm_code == TEMP_HIGH)
  {
    if(alm_data->alm_status == ALARMED)
    {
      cell_temp_over[alm_data->id - 1] = true;
    }
    else if(alm_data->alm_status == ALARM_RESET)
    {
      cell_temp_over[alm_data->id - 1] = false;
    }
  }
  else if(alm_data->alm_code == CELL_COMM_ERROR)
  {
    if(alm_data->alm_status == ALARMED)
    {
      cell_comm_err[alm_data->id - 1] = true;
    }
    else if(alm_data->alm_status == ALARM_RESET)
    {
      cell_comm_err[alm_data->id - 1] = false;
    }
  }
  
  if (alm_data->alm_status == ALARMED )
  {  
    pos = alarm_set_pos(alm_data->alm_code );
    if (pos != ALARM_POS_UNKNOW)
    {
      alarm.set(pos);
    }
  }// clear alarmed bits
  else if (alm_data->alm_status == ALARM_RESET)
  { 
    pos = alarm_reset_pos(alm_data->alm_code );
    if (pos != ALARM_POS_UNKNOW)
    {
      alarm.reset(pos);
    }
  }
}

bool Alarm_state::get_alarm_state()
{
  unsigned int alarm_bits = alarm.to_ulong();
  // except led bits and master controller init bits
  if ((alarm_bits & 0x1fff) == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

char Alarm_state::alarm_reset_pos(Alarm_code_t alarm_code  )
{
  int pos = ALARM_POS_UNKNOW;

  switch (alarm_code)
  {
    case TOTAL_VOLT_LOW:
      pos = alarm_code;//ALARM_POS_MC_TOTAL_VOLT_LOW;
      break;
#if S07S
		case TOTAL_VOLT_DEVIATE_HI:
      pos = alarm_code;//ALARM_POS_MC_TOTAL_VOLT_DEVIATE_HI;
      break;
    case SOH_LOW:
      pos = alarm_code;//ALARM_POS_MC_SOH_LOW;
      break;
#elif S07R
    case TOTAL_VOLT_HI:
      pos = ALARM_POS_MC_TOTAL_VOLT_HI;
      break;
    case DISCHARGE_CUR_HIGH:
      pos = ALARM_POS_MC_DISCHARGE_CUR_HI;
      break;
#endif
		case TEMP_HIGH:
      pos = (check_cell_temp_hig() == ALARM_POS_UNKNOW) ? alarm_code : ALARM_POS_UNKNOW;
      break;
    case CHARGE_CUR_HIGH:
      pos = alarm_code;//ALARM_POS_MC_CHARGE_CUR_HIGH;
      break;
    case SOC_LOW:
      pos = alarm_code;//ALARM_POS_MC_SOC_LOW;
      break;
    
    case CELL_VOLT_DIFF_HIGH:
      pos = alarm_code;//ALARM_POS_CELL_VOLT_DIFF_HIGH;
      break;
    case CELL_VOLT_HIGH:
      pos = (check_cell_volt_hig() == ALARM_POS_UNKNOW) ? alarm_code : ALARM_POS_UNKNOW;
      break;
    case CELL_VOLT_LOW:
      pos = (check_cell_volt_low() == ALARM_POS_UNKNOW) ? alarm_code : ALARM_POS_UNKNOW;
      break;
    case CELL_COMM_ERROR:
      pos = (check_cell_comm_error() == ALARM_POS_UNKNOW)? alarm_code : ALARM_POS_UNKNOW;
      break;
    default:
      pos = ALARM_POS_UNKNOW;
      break;
    }

  return (char)pos;
}
char Alarm_state::alarm_set_pos(Alarm_code_t alarm_code)
{
  int pos = ALARM_POS_UNKNOW;

  switch (alarm_code)
  {
    case TOTAL_VOLT_LOW:
      pos = alarm_code;//;
      break;
#if S07S
		case TOTAL_VOLT_DEVIATE_HI:
      pos = alarm_code;//;
      break;
     case SOH_LOW:
      pos = alarm_code;//;
      break;
		case TEMP_HIGH:
      pos = check_cell_temp_hig();
      break;
#elif S07R
     case TOTAL_VOLT_HI:
      pos = ALARM_POS_MC_TOTAL_VOLT_HI;
      break;
    case DISCHARGE_CUR_HIGH:
      pos = ALARM_POS_MC_DISCHARGE_CUR_HI;
      break;
#endif    
    case CHARGE_CUR_HIGH:
      pos = alarm_code;//;
      break;
    case SOC_LOW:
      pos = alarm_code;//;
      break;
    case CELL_VOLT_DIFF_HIGH:
      pos = alarm_code;//;
      break;
    case CELL_VOLT_HIGH:
      pos = check_cell_volt_hig();
      break;
    case CELL_VOLT_LOW:
      pos = check_cell_volt_low();
      break;
    case CELL_COMM_ERROR:
      pos = check_cell_comm_error();
      break;
    default:
      pos = ALARM_POS_UNKNOW;
      break;
  }

  return pos;
}
  
int Alarm_state:: check_cell_volt_low()
{
  for(int i = 0; i < Dev_paras.volt_cnt ; i++)
  {
    if(cell_volt_low[i])
    {
      return CELL_VOLT_LOW;//ALARM_POS_CELL_VOLT_LOW;
    }
  }
  return ALARM_POS_UNKNOW;
}

int Alarm_state::check_cell_volt_hig()
{
  for(int i = 0; i < Dev_paras.volt_cnt ; i++)
  {
    if(cell_volt_over[i])
    {
      return CELL_VOLT_HIGH;//ALARM_POS_CELL_VOLT_HIGH;
    }
  }
  return ALARM_POS_UNKNOW;
}


int Alarm_state::check_cell_comm_error()
{
  for(int i = 0; i < CELL_CNT ; i++)
  {
    if(cell_comm_err[i])
    {
      return CELL_COMM_ERROR;
    }
  }
  return ALARM_POS_UNKNOW;
}

int Alarm_state::check_cell_temp_hig( )
{
  for(int i = 0; i < Dev_paras.temp_cnt ; i++)
  {
    if(cell_temp_over[i])
    {
      return TEMP_HIGH;
    }
  }
  return ALARM_POS_UNKNOW;
}


Alarm_state::~Alarm_state()
{

}
