#include "main.h"
#include "i2c_layer.h"

#define GPIO_MODE_SWITCH   0

#define I2C_Gpio         GPIOB
#define I2C_Pin_SCL      GPIO_PIN_10//GPIO_PIN_8 //
#define I2C_Pin_SDA      GPIO_PIN_11//GPIO_PIN_9 //

#define SCL_H           HAL_GPIO_WritePin(I2C_Gpio,I2C_Pin_SCL,GPIO_PIN_SET)
#define SCL_L           HAL_GPIO_WritePin(I2C_Gpio,I2C_Pin_SCL,GPIO_PIN_RESET)
#define SDA_H           HAL_GPIO_WritePin(I2C_Gpio,I2C_Pin_SDA,GPIO_PIN_SET)
#define SDA_L           HAL_GPIO_WritePin(I2C_Gpio,I2C_Pin_SDA,GPIO_PIN_RESET)
#define SCL_read        HAL_GPIO_ReadPin(I2C_Gpio,I2C_Pin_SCL)
#define SDA_read        HAL_GPIO_ReadPin(I2C_Gpio,I2C_Pin_SDA)

#if GPIO_MODE_SWITCH == 1
#define SCL_out         //GPIOB_ModeCfg(I2C_Pin_SCL, GPIO_ModeOut_PP_5mA)
#define SCL_in          //GPIOB_ModeCfg(I2C_Pin_SCL, GPIO_ModeIN_PU)
#define SDA_out         //GPIOB_ModeCfg(I2C_Pin_SDA, GPIO_ModeOut_PP_5mA)
#define SDA_in          //GPIOB_ModeCfg(I2C_Pin_SDA, GPIO_ModeIN_PU)

static void I2C_SDA_IN(void) {
    SDA_in;
}

static void I2C_SDA_OUT(void) {
    SDA_out;
}
#endif

/* 定义读写SCL和SDA的宏 */
static void I2C_SCL_1(void) {
    SCL_H;
}      
static void  I2C_SCL_0(void) { 
    SCL_L;
}

static void I2C_SDA_1(void) {
    SDA_H;
}
static void I2C_SDA_0(void) { 
    SDA_L;
}

static uint8_t I2C_SDA_READ(void) { 
    return  (SDA_read > 0)  ? 1 : 0;
}
static void i2c_Delay(void)
{
	volatile uint16_t i;
	for (i = 0; i < 30; i++) {
        __nop();
	}
}

static i2c_device_t i2c = {0};
//static i2c_lock_t lock;
i2c_device_t * i2c_device1 = &i2c;

void i2c_device1_gpio_init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = I2C_Pin_SCL;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_Gpio, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = I2C_Pin_SDA;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_Gpio, &GPIO_InitStruct);
    
    //lock = osSemaphoreNew(1,1,NULL);
}

void i2c_device1_gpio_deinit(void) {

}

void i2c_device1_lock(void) {
    //osSemaphoreAcquire(lock,osWaitForever);
}

void i2c_device1_unlock(void) {
    //osSemaphoreRelease(lock);
}

void i2c_device1_init(void) {
//uint8_t abc[11];
//uint16_t length;
	i2c_device_init(i2c_device1,
					NULL,
                    NULL,
	                i2c_device1_gpio_init,
	                i2c_Delay,
				    I2C_SCL_0,
				    I2C_SCL_1,
					I2C_SDA_0,
					I2C_SDA_1,
					I2C_SDA_READ,
					NULL,
					NULL);
	
	i2c_device1->init();
	
	i2c_device1->i2c_stop(i2c_device1);
  
  //10010001
//  i2c_device1->i2c_read_bytes(i2c_device1,0x48,abc,3);
}


  
