#include <string.h>
#include "main.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"

#define RS485_RE_RESET()   HAL_GPIO_WritePin(USART6_DE_GPIO_Port, USART6_DE_Pin, GPIO_PIN_RESET)
#define RS485_DE_SET()     HAL_GPIO_WritePin(USART6_DE_GPIO_Port, USART6_DE_Pin, GPIO_PIN_SET)


void Bsp_Rs485Init(void) {
    RS485_RE_RESET();
}

void Bsp_Rs485SendBytes(uint8_t *pdata,uint16_t length) {
    
    RS485_DE_SET();
    
    osDelay(2);
    
    while(length--) {
        while((USART6->SR & 0X40) == 0);
        USART6->DR = *pdata++;
    }
    
    osDelay(2);
    
    RS485_RE_RESET();
}