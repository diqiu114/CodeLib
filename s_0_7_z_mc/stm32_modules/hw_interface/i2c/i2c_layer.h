#ifndef __I2C_LAYER_H_
#define __I2C_LAYER_H_

#include <stdint.h>
#include <stdbool.h>



//#include "typedef.h"

typedef enum {
    errOK = 0,
    errErr,
    errBuzy,
   
}errStatus_t;

typedef void (*i2c_lock_)(void);
typedef void (*i2c_init)(void);
typedef void (*i2c_delay)(void);
typedef void (*i2c_scl_0)(void);
typedef void (*i2c_scl_1)(void);
typedef void (*i2c_sda_in)(void);
typedef void (*i2c_sda_out)(void);
typedef void (*i2c_sda_0)(void);
typedef void (*i2c_sda_1)(void);
typedef uint8_t (*i2c_sda_r)(void);


//#define i2c_lock_t  osSemaphoreId_t


typedef struct i2c_device {
	i2c_init        init;
	i2c_delay       delay;
	i2c_scl_0       scl_0;
	i2c_scl_1       scl_1;
	i2c_sda_in      sda_in;
	i2c_sda_out     sda_out;
	i2c_sda_0       sda_0;
	i2c_sda_1       sda_1;
	i2c_sda_r       sda_r;
	
	i2c_lock_        i2c_lock;
	i2c_lock_        i2c_unlock;
	errStatus_t (*i2c_start)(struct i2c_device *device);
	void (*i2c_stop)(struct i2c_device *device);
	void (*i2c_ack)(struct i2c_device *device);
	void (*i2c_nack)(struct i2c_device *device);
	uint8_t (*i2c_wack)(struct i2c_device *device);
	uint8_t (*i2c_read_byte)(struct i2c_device *device);
	void (*i2c_write_byte)(struct i2c_device *device,uint8_t data);
	bool (*i2c_read_bytes)(struct i2c_device *device,uint8_t sa,uint8_t* pdata,uint8_t cnt);
	bool (*i2c_read_bytes_2)(struct i2c_device *device,uint8_t sa,uint8_t cmd,uint8_t* pdata,uint8_t cnt);
	bool (*i2c_write_bytes)(struct i2c_device *device,uint8_t sa,uint8_t* pdata,uint8_t cnt);
	bool (*i2c_write_bytes_2)(struct i2c_device *device,uint8_t sa,uint8_t cmd,uint8_t* pdata,uint8_t cnt);
}i2c_device_t;



typedef void (*i2c_start)(struct i2c_device *device);
typedef void (*i2c_stop)(struct i2c_device *device);
typedef uint8_t (*i2c_read_byte)(struct i2c_device *device);
typedef bool (*i2c_read_bytes)(struct i2c_device *device,uint8_t sa,uint8_t* pdata,uint8_t cnt);
typedef bool (*i2c_read_bytes_2)(struct i2c_device *device,uint8_t sa,uint8_t cmd,uint8_t* pdata,uint8_t cnt);
typedef bool (*i2c_write_bytes_2)(struct i2c_device *device,uint8_t sa,uint8_t cmd,uint8_t* pdata,uint8_t cnt);
typedef void (*i2c_write_byte)(struct i2c_device *device,uint8_t data);
typedef bool (*i2c_write_bytes)(struct i2c_device *device,uint8_t sa,uint8_t* pdata,uint8_t cnt);
typedef void (*i2c_ack)(struct i2c_device *device);
typedef void (*i2c_nack)(struct i2c_device *device);
typedef void (*i2c_wack)(struct i2c_device *device);

void i2c_device_init(i2c_device_t *device,
					 i2c_lock_    lock,
                     i2c_lock_    unlock,
	                 i2c_init    init,
				     i2c_delay   delay,
					 i2c_scl_0   scl_0,
					 i2c_scl_1   scl_1,
                     i2c_sda_0   sda_0,
					 i2c_sda_1   sda_1,
					 i2c_sda_r   sda_r,
					 i2c_sda_in  sda_in,
					 i2c_sda_out sda_out) ;

#endif
