#include "stm32f4xx_hal.h"
#include "defines.h"
#include "class_init.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if USE_485
  if (huart == Cell_node_uart )
  {
    Rs485_comm->rev_data_handle();
  }
#endif
  
#if USE_MVB
  if (huart == Mvb_uart_handle)
  {
    Mvb_uart->rev_data_handle();
  }
#endif
	
#if USE_ETH
  else if (huart == Eth_uart)
  {
    Trdp_uart->rev_data_handle();
  }
#endif
	
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (tb_handle == hadc)
  {
    tb_adc->stop_acq();
  }
	else if(Pt1000_handle == hadc)
	{
		Pt1000_adc->stop_acq();
	}
}
