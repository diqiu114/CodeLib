/**
  ******************************************************************************
  * @file    IAP_Main/Inc/flash_if.h 
  * @author  MCD Application Team
  * @brief   This file provides all the headers of the flash_if functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_F030_H
#define __FLASH_IF_F030_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Error code */
enum 
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR,
  FLASHIF_PROTECTION_ERRROR
};

/* protection type */  
enum{
  FLASHIF_PROTECTION_NONE         = 0,
  FLASHIF_PROTECTION_PCROPENABLED = 0x1,
  FLASHIF_PROTECTION_WRPENABLED   = 0x2,
  FLASHIF_PROTECTION_RDPENABLED   = 0x4,
};

/* protection update */
enum {
	FLASHIF_WRP_ENABLE,
	FLASHIF_WRP_DISABLE
};

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define FLASH_PAGE_STEP         FLASH_PAGE_SIZE           /* Size of page : 2 Kbytes */

/* Notable Flash addresses */
#define USER_FLASH_START_ADDRESS        ((uint32_t)0x08000000)      /* 用户flash起始地址，一般0x08000000 */
#define APPLICATION_START_ADDRESS       ((uint32_t)0x08006000)      /* 应用程序起始地址 */
#define APPLICATION_END_ADDRESS         ((uint32_t)0x08022FFF)      /* 应用程序结束地址 */
#define BACKUP_PROGRAM_START_ADDRESS    ((uint32_t)0x08023000)      /* 备份程序起始地址 */
#define BACKUP_PROGRAM_END_ADDRESS      ((uint32_t)0x0803FFFF)      /* 备份程序结束地址 */
#define USER_FLASH_END_ADDRESS          ((uint32_t)0x0803FFFF)      /* 用户flash结束地址 */

/* Define the user application size */
#define USER_FLASH_SIZE               (USER_FLASH_END_ADDRESS - USER_FLASH_START_ADDRESS + 1) /* Small default template application */

/* Define bitmap representing user flash area that could be write protected (check restricted to pages 8-39). */
#define FLASH_PAGE_TO_BE_PROTECTED (OB_WRP_PAGES8TO9 | OB_WRP_PAGES10TO11 | OB_WRP_PAGES12TO13 | OB_WRP_PAGES14TO15 | \
                                    OB_WRP_PAGES16TO17 | OB_WRP_PAGES18TO19 | OB_WRP_PAGES20TO21 | OB_WRP_PAGES22TO23 | \
                                    OB_WRP_PAGES24TO25 | OB_WRP_PAGES26TO27 | OB_WRP_PAGES28TO29 | OB_WRP_PAGES30TO31 | \
                                    OB_WRP_PAGES32TO33 | OB_WRP_PAGES34TO35 | OB_WRP_PAGES36TO37 | OB_WRP_PAGES38TO39  )  


/* Exported macro ------------------------------------------------------------*/
/* ABSoulute value */
#define ABS_RETURN(x,y)               (((x) < (y)) ? (y) : (x))

/* Get the number of sectors from where the user program will be loaded */
#define FLASH_SECTOR_NUMBER           ((uint32_t)(ABS_RETURN(APPLICATION_ADDRESS,FLASH_START_BANK1)-FLASH_START)>>12)

/* Compute the mask to test if the Flash memory, where the user program will be
  loaded, is write protected */
#define FLASH_PROTECTED_SECTORS       (~(uint32_t)((1 << FLASH_SECTOR_NUMBER) - 1))
/* Exported functions ------------------------------------------------------- */
void FLASH_If_Init(void);
uint32_t FLASH_If_Erase(uint32_t StartSector,uint32_t end);
uint32_t FLASH_If_GetWriteProtectionStatus(void);
uint32_t FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length);
uint32_t FLASH_If_WriteProtectionConfig(uint32_t protectionstate);

#endif  /* __FLASH_IF_F030_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
