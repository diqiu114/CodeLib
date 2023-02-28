#include "ds18b20.h"
#include "stdio.h"

Ds18b20::Ds18b20(Onewire *_ow, int _timeout_ms)
{
  ow = _ow;
  temperature = 0;
  timeout_ms = _timeout_ms;
  config();
  
  status = READY;
}

Ds18b20::~Ds18b20()
{
 if(ow != NULL)
 {
   delete ow;
   ow = NULL;
 }
}

void Ds18b20::config(void)
{
  ow->power();

  ow->reset();

  ow->write_byte(CMD_SKIP_ROM);
  DELAY_MS(CMD_DELAY);
  ow->write_byte(CMD_WRITE_SCRA);
  DELAY_MS(CMD_DELAY);

  //TH and TL temperature triggers
  ow->write_byte(0x7F);
  DELAY_MS(CMD_DELAY);

  ow->write_byte(0x00);
  DELAY_MS(CMD_DELAY);

  //temperature  config 12 bits resolution
  ow->write_byte(DS18b20_resolution_12bits);
  DELAY_MS(CMD_DELAY);
}

void Ds18b20::conv(void)
{
  ow->reset();

  ow->write_byte(CMD_SKIP_ROM);
  DELAY_MS(CMD_DELAY);

  ow->write_byte(CMD_TEMP_CONV);
  DELAY_MS(CMD_DELAY);

  ow->power();
}

void Ds18b20::read_cmd(void)
{

  ow->reset();

  ow->write_byte(CMD_SKIP_ROM);
  DELAY_MS(CMD_DELAY);

  //read Ds18b20 scratchpad data
  ow->write_byte(CMD_READ_SCRA);
  DELAY_MS(CMD_DELAY);
}

void Ds18b20::start(void)
{
  if (status == READY)
  {

//    config();

    conv();

    ow->power();

    status = BUSY;
  }
}

Temp_sensor_status Ds18b20::get_status(void)
{
  return status;
}

void Ds18b20::timeout_callback(void)
{
//  read_temp();
  status = READ_READY;
}

float Ds18b20::get_temp(void)
{
  if( status == READ_READY)
  {
    read_temp();
    status = READY;
  }
  return temperature;
}

bool Ds18b20::read_temp()
{
  char retry = 2;
  bool crc_correct = false;

  short temp = 0;

  while (retry)
  {
    read_cmd();

    // fixed return 9 bytes data
    memset(read_data, 0, sizeof(read_data));

    for (int i = 0; i < DS18B20_DATA_FIXED_LEN; i++)
    {
      read_data[i] = ow->read_byte();
    }

    unsigned char crc = crc8(read_data, DS18B20_DATA_FIXED_LEN - 1);

    crc_correct = (crc == read_data[DS18B20_DATA_FIXED_LEN - 1]);

    if (crc_correct)
    {
      break;
    }
    retry--;
  }

  if ((!crc_correct) || (retry == 0))
  {
    return false;
  }

  temp = (read_data[1] << 8) | read_data[0];

  // negative temperature
  if (temp & 0x8000)
  {
    temp = ~temp + 1;
    temp = -(temp * 0.625);
  }
  else
  {
    temp = temp * 0.625;
  }

  temperature = temp;

  return true;
}

/**
 * crc8 Calculates 8-bit CRC
 * @param addr Pointer to 8-bit array of data to calculate CRC
 * @param len Number of bytes to check
 * @return Calculated CRC from input data
 */
unsigned char Ds18b20::crc8(unsigned char *addr, unsigned char len)
{
  unsigned char crc = 0, inbyte, i, mix;
  unsigned char *p = addr;

  while (len--)
  {
    inbyte = *p++;
    for (i = 8; i; i--)
    {
      mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix)
      {
        crc ^= 0x8C;
      }
      inbyte >>= 1;
    }
  }

  return crc;
}

