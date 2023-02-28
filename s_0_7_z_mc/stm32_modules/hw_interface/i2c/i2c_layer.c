/*
*********************************************************************************************************
*
*   ģ������ : i2c layer
*   �ļ����� : i2c_layer.c
*   ��    �� : V1.0
*   �޸ļ�¼ :
*       �汾��  ����        ����       ˵��
*       V1.0    2020-03-18  ouyangwei  ��ʼ�汾
*********************************************************************************************************
*/

#include <string.h>
#include <stdbool.h>
#include "i2c_layer.h"

static errStatus_t i2c_Start(i2c_device_t *device)
{
    device->sda_1();

    if(device->sda_out) {device->sda_out();}

    device->scl_1();
    device->delay();
    if(!device->sda_r) {
       return errErr;
    }
    device->sda_0();
    device->delay();
    if(!device->sda_r) {
       return errErr;
    }
    device->scl_0();
    device->delay();
    return errOK;
}

static void i2c_Stop(i2c_device_t *device)
{
	// ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� 
    if(device->sda_out) {device->sda_out();}
	device->sda_0();
	device->scl_1();
	device->delay();
	device->sda_1();
	device->delay();
}


static void i2c_SendByte(i2c_device_t *device,uint8_t _ucByte)
{
	uint8_t i;

	if(device->sda_out) {device->sda_out();}
	// �ȷ����ֽڵĸ�λbit7 
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			device->sda_1();
		}
		else
		{
			device->sda_0();
		}
		device->delay();
		device->scl_1();
		device->delay();
		device->scl_0();
		device->delay();
		if (i == 7)
		{
			 device->sda_1();// �ͷ�����
		}
		_ucByte <<= 1;
	}
}


static uint8_t i2c_ReadByte(i2c_device_t *device)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		device->scl_1();
		device->delay();
		if(device->sda_in) {device->sda_in();}
		device->delay();
		if (device->sda_r())
		{
			value++;
		}
		device->scl_0();
		device->delay();
	}
	return value;
}


static uint8_t i2c_WaitAck(i2c_device_t *device)
{
	uint8_t re;

	device->sda_1();/* CPU�ͷ�SDA���� */
	if(device->sda_out) {device->sda_out();}
	if(device->sda_in) {device->sda_in();}
	device->scl_1();/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	device->delay();
	//if(device->sda_in) {device->sda_in();}
	//device->delay();
	if (device->sda_r())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}

	device->scl_0();
	device->delay();
	return re;
}





static void i2c_Ack(i2c_device_t *device)
{
	device->sda_0(); /* CPU����SDA = 0 */
	if(device->sda_out) {device->sda_out();}

	device->delay();
	device->scl_1(); /* CPU����1��ʱ�� */
	device->delay();
	device->scl_0();
	device->delay();
	device->sda_1(); /* CPU�ͷ�SDA���� */
}

static void i2c_NAck(i2c_device_t *device)
{
	device->sda_1(); /* CPU����SDA = 1 */
	if(device->sda_out) {device->sda_out();}
	device->delay();
	device->scl_1(); /* CPU����1��ʱ�� */
	device->delay();
	device->scl_0();
	device->delay();
}

static bool i2c_ReadBytes(i2c_device_t *device,uint8_t sa,uint8_t *pdata,uint8_t cnt) {
	
	if(device->i2c_lock != NULL) {
        device->i2c_lock();
    }
    
	bool ret = false;
	
	uint8_t length = cnt;
	
	device->i2c_start(device);
		
	device->i2c_write_byte(device,sa << 1 | 1);
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;

	while(length--){
		*pdata++ = device->i2c_read_byte(device);
		length == 0 ? device->i2c_nack(device) : device->i2c_ack(device);
	}

	ret = true;
EXIT:
	
	device->i2c_stop(device);
    
    if(device->i2c_unlock != NULL) {
        device->i2c_unlock();
    }

	return ret;
}

static bool i2c_ReadBytes2(i2c_device_t *device,uint8_t sa,uint8_t cmd,uint8_t *pdata,uint8_t cnt) {
    if(device->i2c_lock != NULL) {
        device->i2c_lock();
    }
    
	bool ret = false;
	uint8_t addr = sa;
	
	uint8_t length = cnt;
	
	device->i2c_start(device);
	
	addr = ((sa << 1) | 0);
	device->i2c_write_byte(device,addr);
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;
	
	device->i2c_write_byte(device,cmd);
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;

	device->i2c_start(device);
	
	addr = (sa << 1 | 1);
	device->i2c_write_byte(device,addr);
	if(device->i2c_wack(device) != 0) 
		goto EXIT;

//	device->i2c_start(device);

	while(length--){
		*pdata++ = device->i2c_read_byte(device);
		length == 0 ? device->i2c_nack(device) : device->i2c_ack(device);
	}

	ret = true;
EXIT:
	
	device->i2c_stop(device);

	if(!ret) {
	}
    
    if(device->i2c_unlock != NULL) {
        device->i2c_unlock();
    }
	return ret;
}

static bool i2c_WriteBytes2(i2c_device_t *device,uint8_t sa,uint8_t cmd,uint8_t *pdata,uint8_t cnt) {
	if(device->i2c_lock != NULL) {
        device->i2c_lock();
    }
        
	bool ret = false;

	uint8_t length = cnt;
	
	device->i2c_start(device);
		
	device->i2c_write_byte(device,((sa << 1) | 0));
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;
	
	device->i2c_write_byte(device,cmd);
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;
	
//	device->i2c_start(device);

	while(length--){
		device->i2c_write_byte(device,*pdata++);
		if(device->i2c_wack(device) != 0) {
			goto EXIT;
		}
	}

	ret = true;
EXIT:
	
	device->i2c_stop(device);

    
    if(device->i2c_unlock != NULL) {
        device->i2c_unlock();
    }
	return ret;
}

static bool i2c_WriteBytes(i2c_device_t *device,uint8_t sa,uint8_t *pdata,uint8_t cnt) {
    if(device->i2c_lock != NULL) {
        device->i2c_lock();
    }
	bool ret = false;
	
	uint8_t length = cnt;
	
	device->i2c_start(device);
		
	device->i2c_write_byte(device,sa << 1);
	
	if(device->i2c_wack(device) != 0) 
		goto EXIT;

	while(length--){
		device->i2c_write_byte(device,*pdata++);
		if(device->i2c_wack(device) != 0) {
			goto EXIT;
		}
	}

	ret = true;
EXIT:
	
	device->i2c_stop(device);
    
    if(device->i2c_unlock != NULL) {
        device->i2c_unlock();
    }

	return ret;

}

void i2c_device_init(i2c_device_t *device,
					 i2c_lock_  lock,
                     i2c_lock_  unlock,   
	                 i2c_init  init,
				     i2c_delay delay,
					 i2c_scl_0 scl_0,
					 i2c_scl_1 scl_1,
                     i2c_sda_0 sda_0,
					 i2c_sda_1 sda_1,
					 i2c_sda_r sda_r,
					 i2c_sda_in sda_in,
					 i2c_sda_out sda_out) {
					 
	if(device == NULL) {
		return;
	}
	
	device->init = init;
	device->delay = delay;
	device->scl_0 = scl_0;
	device->scl_1 = scl_1;
	device->sda_0 = sda_0;
	device->sda_1 = sda_1;
	device->sda_r = sda_r;
	device->sda_out = sda_out;
	device->sda_in = sda_in;
	
	device->i2c_start = i2c_Start;
	device->i2c_stop = i2c_Stop;
	
	device->i2c_ack = i2c_Ack;
	device->i2c_nack = i2c_NAck;
	device->i2c_wack = i2c_WaitAck;
	
	device->i2c_read_byte = i2c_ReadByte;
	device->i2c_write_byte = i2c_SendByte;
	
	device->i2c_read_bytes = i2c_ReadBytes;
	device->i2c_write_bytes = i2c_WriteBytes;
	device->i2c_read_bytes_2 = i2c_ReadBytes2;
	device->i2c_write_bytes_2 = i2c_WriteBytes2;
	
	device->i2c_lock = lock;
    device->i2c_unlock = unlock;
}

