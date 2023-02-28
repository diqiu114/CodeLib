#ifndef __FTL_H
#define __FTL_H
/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************** 
  * @copyright  (C) COPYRIGHT DANFINSWE
  * @version    V1.0.0
  * @author     liao<cs.liaow@gmail.com>
  * @date 　　    2016/8/16
  * @brief      NAND FLASH FTL层算法代码
  *             also see ALIENTEK Apollo Board ftl.h
***********************************************************/
#include "stm32f4xx_hal.h"
#include "ff.h" 
#include "nand_driver.h"
  
//坏块搜索控制
//如果设置为1,将在FTL_Format的时候,搜寻坏块,耗时久(512M,3分钟以上),且会导致RGB屏乱闪
#define FTL_USE_BAD_BLOCK_SEARCH        0       //定义是否使用坏块搜索



uint8_t FTL_Init(void); 
void FTL_BadBlockMark(uint32_t blocknum);
uint8_t FTL_CheckBadBlock(uint32_t blocknum); 
uint8_t FTL_UsedBlockMark(uint32_t blocknum);
uint32_t FTL_FindUnusedBlock(uint32_t sblock,uint8_t flag);
uint32_t FTL_FindSamePlaneUnusedBlock(uint32_t sblock);
uint8_t FTL_CopyAndWriteToBlock(uint32_t Source_PageNum,uint16_t ColNum,uint8_t *pBuffer,uint32_t NumByteToWrite);
uint16_t FTL_LBNToPBN(uint32_t LBNNum); 
uint8_t FTL_WriteSectors(uint8_t *pBuffer,uint32_t SectorNo,uint16_t SectorSize,uint32_t SectorCount);
uint8_t FTL_ReadSectors(uint8_t *pBuffer,uint32_t SectorNo,uint16_t SectorSize,uint32_t SectorCount);
uint8_t FTL_CreateLUT(uint8_t mode);
uint8_t FTL_BlockCompare(uint32_t blockx,uint32_t cmpval);
uint32_t FTL_SearchBadBlock(uint32_t *oddBlockNum, uint32_t *evenBlockNum);
uint8_t FTL_Format(void); 

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif //end __FTL_H

