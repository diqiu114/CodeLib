#include "class_init.h"
#include <map>
#include "paras.h"
#include "proj_usb_process.h"
#include "stdio.h"
//Eeprom_flag *Program_upgrade = NULL;
//Eeprom_flag *Program_upgrade_1 = NULL;
//Eeprom_flag *Nand_format = NULL;
bitset<8> complex_state;

Flag_t Promgram_update_flag =
    {
        PROGRAM_UPGRADE_ADDR,
        PROGRAM_UPGRADE_ADDR_CNT,
        PROGRAM_UPGRADE_VAL,
        PROGRAM_NOT_UPGRADE_VAL};

Flag_t Nand_format_flag =
    {
        NAND_FORMAT_ADDR,
        NAND_FORMAT_ADDR_ADDR_CNT,
        NAND_FORMAT_ADDR_VAL,
        NAND_FORMAT_ADDR_NOT_FORMAT_VAL};
    
Flag_t Promgram_ugrade_flag_1 =
    {
        PROGRAM_UPGRADE_ADDR_1,
        PROGRAM_UPGRADE_ADDR_CNT_1,
        PROGRAM_UPGRADE_VAL_1,
        PROGRAM_NOT_UPGRADE_VAL_1};

Usb_comm *Host_comm = NULL;
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int std::fputc(int ch, FILE *f)
#endif /* __GNUC__ */



/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
#if USE_485
  Rs485_comm->send((uint8_t *)&ch, 1); 
#endif
  return ch;
}

bool Class_init(void)
{
#if 0
  Program_upgrade = new Eeprom_flag(Promgram_update_flag, 0);
  if (Program_upgrade == NULL)
  {
    return false;
  }
#endif
  
  
#if USE_USB_DEBUG == 1
  Host_comm = new Usb_process(&hUsbDeviceFS, usb_comm_callback);
  if (Host_comm == NULL)
  {
    return false;
  }
#endif

  // project class initialize
  if (Proj_class_init() == false)
  {
    complex_state.set(POWER_ON_CHECK_SELF_FAIL);
    return false;
  }

  return true;
};
