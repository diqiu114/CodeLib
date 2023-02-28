#include "wl433_data_tranceiver.h"

#define RF_PACKET_SIZE (32)
#define RF_SEND_TIMEOUT (300)

Wl433_data_tranceiver::Wl433_data_tranceiver(Cmt2300a_app *_wl433, unsigned int buffer_size)
{
  wl433 = _wl433;
  buffer = new unsigned char[buffer_size];
	send_ok = false;
  recv_ok = false;
}

Wl433_data_tranceiver::~Wl433_data_tranceiver()
{
}

unsigned int Wl433_data_tranceiver::get_data(unsigned char *data)
{
  unsigned int ret = 0;
  int retry = 0;
	while(ret == 0)
	{
		switch (wl433->process())
		{
			case RF_IDLE:
			{
				wl433->start_rx(buffer, RF_PACKET_SIZE, 300);
				break;
			}
			case RF_RX_DONE:
			{
				memcpy(data, buffer + 1, buffer[0]);
				ret = buffer[0] - 1;
				break;
			}
			default:
					break;
		}
		
		retry++;
		DELAY_MS(1);
		if( retry > 500)
		{
			if(recv_ok == false)
			{
				wl433->init();
			}
			return 0;
		}
	}
	recv_ok = true;
  return ret;
}

bool Wl433_data_tranceiver::send_data(unsigned char *data, unsigned int data_len)
{ 
	int retry = 0;
	while(wl433->process() != RF_IDLE)
	{
		retry++;
		DELAY_MS(1);
		if(retry > 300)
		{
			return false;
		}
	}
	retry = 0;
	wl433->start_tx(data, data_len, RF_SEND_TIMEOUT);
	while(wl433->process() != RF_TX_DONE)
	{
	  retry++;
		DELAY_MS(1);
		if(retry > 100)
		{
			if(send_ok == false)
			{
				wl433->init();
			}
			return false;
		}
	}
	send_ok = true;
  return true;
}
