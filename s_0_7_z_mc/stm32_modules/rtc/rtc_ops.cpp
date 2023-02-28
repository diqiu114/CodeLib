#include "rtc_ops.h"

#define RTC_LEAP_YEAR(year)             (((( year ) % 4 == 0 ) && (( year ) % 100 != 0 )) || (( year ) % 400 == 0 ))
#define RTC_DAYS_IN_YEAR(x)             ( RTC_LEAP_YEAR(x) ? 366 : 365 )
#define RTC_OFFSET_YEAR                 ( 1970 )
#define RTC_SECONDS_PER_DAY             ( 86400 )
#define RTC_SECONDS_PER_HOUR            ( 3600 )
#define RTC_SECONDS_PER_MINUTE          ( 60 )
#define TIME_ZONE                       ( 8 )
#define TIME_ZONE_IN_SECONDS            ( RTC_SECONDS_PER_HOUR * TIME_ZONE )
// Days in a month
static unsigned char RTC_Months[2][12] =
{
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // Not leap year
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} // Leap year
};

Rtc_ops::Rtc_ops(RTC_HandleTypeDef* handle)
{
  hrtc = handle;
}

bool Rtc_ops::set_date(Rtc_date_t* date)
{
  rtc_date.Year = date->year;
  rtc_date.Month = date->month;
  rtc_date.Date = date->date;
  rtc_date.WeekDay = RTC_WEEKDAY_MONDAY;
  if( HAL_RTC_SetDate(hrtc, &rtc_date, RTC_FORMAT_BIN) == HAL_OK )
  {
    return true;
  } 
  else
  {
    return false;
  }
}

bool Rtc_ops::set_time(Rtc_time_t* time)
{
  rtc_time.Hours = time->hours;
  rtc_time.Minutes = time->minutes;
  rtc_time.Seconds = time->seconds;
  rtc_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  rtc_time.StoreOperation = RTC_STOREOPERATION_RESET;
  if( HAL_RTC_SetTime(hrtc, &rtc_time, RTC_FORMAT_BIN) == HAL_OK )
  {
    return true;
  } 
  else
  {
    return false;
  }
}

bool Rtc_ops::set_datetime(Rtc_t* date_time)
{
  return (set_time(&date_time->time) && set_date(&date_time->date));
}

bool Rtc_ops::get_date(Rtc_date_t* date)
{
  if( HAL_RTC_GetTime(hrtc, &rtc_time, RTC_FORMAT_BIN) != HAL_OK )
  {
    return false;
  }

  if( HAL_RTC_GetDate(hrtc, &rtc_date, RTC_FORMAT_BIN) == HAL_OK )
  {
    date->year = rtc_date.Year;
    date->month = rtc_date.Month;
    date->date = rtc_date.Date;
    return true;
  } 
  else
  {
    return false;
  }
}

bool Rtc_ops::get_time(Rtc_time_t* time)
{
  bool ret = false;
  if( HAL_RTC_GetTime(hrtc, &rtc_time, RTC_FORMAT_BIN) == HAL_OK )
  {
    time->hours = rtc_time.Hours;
    time->minutes = rtc_time.Minutes;
    time->seconds = rtc_time.Seconds;
    ret = true;
  }

  if( ret && (HAL_RTC_GetDate(hrtc, &rtc_date, RTC_FORMAT_BIN) == HAL_OK) )
  {
    return true;
  } 
  else
  {
    return false;
  }
}

bool Rtc_ops::get_datetime(Rtc_t* date_time)
{
  bool ret = false;
  if( HAL_RTC_GetTime(hrtc, &rtc_time, RTC_FORMAT_BIN) == HAL_OK )
  {
    date_time->time.hours = rtc_time.Hours;
    date_time->time.minutes = rtc_time.Minutes;
    date_time->time.seconds = rtc_time.Seconds;
    ret = true;
  }

  if( ret && (HAL_RTC_GetDate(hrtc, &rtc_date, RTC_FORMAT_BIN) == HAL_OK) )
  {
    date_time->date.year = rtc_date.Year;
    date_time->date.month = rtc_date.Month;
    date_time->date.date = rtc_date.Date;
    return true;
  } 
  else
  {
    return false;
  }
}


unsigned int Rtc_ops::get_ts_with8zone(Rtc_t* date_time)
{
  unsigned int days = 0;
  unsigned int seconds = 0;
  unsigned short i = 0;
  unsigned short year = 0;

  year = (unsigned short) ( date_time->date.year + 2000 );
  // Year is below offset year
  if (year < RTC_OFFSET_YEAR)
  {
    return false;
  }

  // Days in back years
  for (i = RTC_OFFSET_YEAR; i < year; i++)
  {
    days += RTC_DAYS_IN_YEAR(i);
  }

  // Days in current year
  for (i = 1; i < date_time->date.month; i++)
  {
    days += RTC_Months[RTC_LEAP_YEAR(year)][i - 1];
  }

  // Day starts with 1
  days    += date_time->date.date - 1;
  seconds  = days * RTC_SECONDS_PER_DAY;
  seconds += ( date_time->time.hours) * RTC_SECONDS_PER_HOUR;
  seconds += date_time->time.minutes * RTC_SECONDS_PER_MINUTE;
  seconds += date_time->time.seconds;

  // seconds = days * 86400;
  return seconds;
}

uint32_t get_ts_1(Rtc_t* date_time) {
  unsigned int days = 0;
  unsigned int seconds = 0;
  unsigned short i = 0;
  unsigned short year = 0;

  year = (unsigned short) ( date_time->date.year + 2000 );
  // Year is below offset year
  if (year < RTC_OFFSET_YEAR)
  {
    return false;
  }

  // Days in back years
  for (i = RTC_OFFSET_YEAR; i < year; i++)
  {
    days += RTC_DAYS_IN_YEAR(i);
  }

  // Days in current year
  for (i = 1; i < date_time->date.month; i++)
  {
    days += RTC_Months[RTC_LEAP_YEAR(year)][i - 1];
  }

  // Day starts with 1
  days    += date_time->date.date - 1;
  seconds  = days * RTC_SECONDS_PER_DAY;
  seconds += ( date_time->time.hours - TIME_ZONE) * RTC_SECONDS_PER_HOUR;
  seconds += date_time->time.minutes * RTC_SECONDS_PER_MINUTE;
  seconds += date_time->time.seconds;

  // seconds = days * 86400;
  return seconds;
}

unsigned int Rtc_ops::get_ts(Rtc_t* date_time)
{
  unsigned int days = 0;
  unsigned int seconds = 0;
  unsigned short i = 0;
  unsigned short year = 0;

  year = (unsigned short) ( date_time->date.year + 2000 );
  // Year is below offset year
  if (year < RTC_OFFSET_YEAR)
  {
    return false;
  }

  // Days in back years
  for (i = RTC_OFFSET_YEAR; i < year; i++)
  {
    days += RTC_DAYS_IN_YEAR(i);
  }

  // Days in current year
  for (i = 1; i < date_time->date.month; i++)
  {
    days += RTC_Months[RTC_LEAP_YEAR(year)][i - 1];
  }

  // Day starts with 1
  days    += date_time->date.date - 1;
  seconds  = days * RTC_SECONDS_PER_DAY;
  seconds += ( date_time->time.hours - TIME_ZONE) * RTC_SECONDS_PER_HOUR;
  seconds += date_time->time.minutes * RTC_SECONDS_PER_MINUTE;
  seconds += date_time->time.seconds;

  // seconds = days * 86400;
  return seconds;
}

unsigned int Rtc_ops::get_ts(void)
{
  unsigned int ret = 0;
  Rtc_t rtc_date_time;

  if( get_datetime(&rtc_date_time) )
  {
    ret = get_ts(&rtc_date_time);
  }
  else
  {
    ret = 0;
  }

  return ret;
}

bool Rtc_ops::set_datetime(unsigned int ts)
{
  bool ret = false;
  Rtc_t datetime;

  if( ts_to_datetime(ts, &datetime) )
  {
    if( set_datetime(&datetime) )
    {
      ret = true;
    }
  }

  return ret;
}

// RTC_DateTypeDef date;
//   RTC_TimeTypeDef time;

//   RTC_get_datetime_from_unix(&date, &time, ts);

//   if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK)
//   {
//     return false;
//   }

//   if (HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK)
//   {
//     return false;
//   }

//   return true;

bool ts_to_datetime_1(unsigned int ts, Rtc_t* datetime)
{
  unsigned short year;
  int timezone_unix = ts + TIME_ZONE_IN_SECONDS;
  
  // Get seconds from unix
  datetime->time.seconds = timezone_unix % 60;
  datetime->time.sub_seconds = 0;
  // Go to minutes
  timezone_unix /= 60;
  // Get minutes
  datetime->time.minutes = timezone_unix % 60;
  // Go to hours
  timezone_unix /= 60;
  // Get hours
  datetime->time.hours   = timezone_unix % 24;
  // Get daylightsaving
  // Get store operation
  // Go to days
  timezone_unix /= 24;

  // Get week day
  // Monday is day one
  // Get year
  year = 1970;
  while (1)
  {
    if (RTC_LEAP_YEAR(year))
    {
      if (timezone_unix >= 366)
      {
        timezone_unix -= 366;
      }
      else
      {
        break;
      }
    }
    else if (timezone_unix >= 365)
    {
      timezone_unix -= 365;
    }
    else
    {
      break;
    }
    year++;
  }
  // Get year in xx format
  datetime->date.year = (unsigned char) ( year - 2000 );
  // Get month
  for (datetime->date.month = 0; datetime->date.month < 12; datetime->date.month++)
  {
    if (RTC_LEAP_YEAR(year))
    {
      if (timezone_unix >= (unsigned int)RTC_Months[1][datetime->date.month])
      {
        timezone_unix -= RTC_Months[1][datetime->date.month];
      }
      else
      {
        break;
      }
    }
    else if (timezone_unix >= (unsigned int)RTC_Months[0][datetime->date.month])
    {
      timezone_unix -= RTC_Months[0][datetime->date.month];
    }
    else
    {
      break;
    }
  }
  // Get month
  // Month starts with 1
  datetime->date.month++;
  // Get date
  // Date starts with 1
  datetime->date.date = timezone_unix + 1;
  
  // Return OK
  return true;
}

/**
 * get_datetime_from_unix
 * @param date TODO
 * @param time TODO
 * @param unix TODO
 * @return TODO
 */
bool Rtc_ops::ts_to_datetime(unsigned int ts, Rtc_t* datetime)
{
  unsigned short year;
  int timezone_unix = ts + TIME_ZONE_IN_SECONDS;
  
  // Get seconds from unix
  datetime->time.seconds = timezone_unix % 60;
  datetime->time.sub_seconds = 0;
  // Go to minutes
  timezone_unix /= 60;
  // Get minutes
  datetime->time.minutes = timezone_unix % 60;
  // Go to hours
  timezone_unix /= 60;
  // Get hours
  datetime->time.hours   = timezone_unix % 24;
  // Get daylightsaving
  // Get store operation
  // Go to days
  timezone_unix /= 24;

  // Get week day
  // Monday is day one
  // Get year
  year = 1970;
  while (1)
  {
    if (RTC_LEAP_YEAR(year))
    {
      if (timezone_unix >= 366)
      {
        timezone_unix -= 366;
      }
      else
      {
        break;
      }
    }
    else if (timezone_unix >= 365)
    {
      timezone_unix -= 365;
    }
    else
    {
      break;
    }
    year++;
  }
  // Get year in xx format
  datetime->date.year = (unsigned char) ( year - 2000 );
  // Get month
  for (datetime->date.month = 0; datetime->date.month < 12; datetime->date.month++)
  {
    if (RTC_LEAP_YEAR(year))
    {
      if (timezone_unix >= (unsigned int)RTC_Months[1][datetime->date.month])
      {
        timezone_unix -= RTC_Months[1][datetime->date.month];
      }
      else
      {
        break;
      }
    }
    else if (timezone_unix >= (unsigned int)RTC_Months[0][datetime->date.month])
    {
      timezone_unix -= RTC_Months[0][datetime->date.month];
    }
    else
    {
      break;
    }
  }
  // Get month
  // Month starts with 1
  datetime->date.month++;
  // Get date
  // Date starts with 1
  datetime->date.date = timezone_unix + 1;
  
  // Return OK
  return true;
}

Rtc_ops::~Rtc_ops()
{

}
