#include "nand_driver.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

nand_attriute      nand_dev;     //nand重要参数结构体

//初始化NAND FLASH
//返回值:0,成功
//    其他,失败
unsigned char NAND_Init(void)
{
  NAND_MPU_Config();
  NAND_Reset();                                                          //复位NAND
  HAL_Delay(100);
  nand_dev.id = NAND_ReadID();                                           //读取ID
  NAND_ModeSet(4);
  if(nand_dev.id == MT29F16G08ABABA)                                     //NAND为MT29F16G08ABABA
  {
    nand_dev.page_totalsize = 4320;                                      //nand一个page的总大小（包括spare区）
    nand_dev.page_mainsize  = 4096;                                      //nand一个page的有效数据区大小
    nand_dev.page_sparesize = 224;                                       //nand一个page的spare区大小
    nand_dev.block_pagenum  = 128;                                       //nand一个block所包含的page数目
    nand_dev.plane_blocknum = 2048;                                      //nand一个plane所包含的block数目
    nand_dev.block_totalnum = 4096;                                      //nand的总block数目
  }
  else if(nand_dev.id == MT29F4G08ABADA)                                 //NAND为MT29F4G08ABADA
  {
    nand_dev.page_totalsize = 2112;                                      //nand一个page的总大小（包括spare区）
    nand_dev.page_mainsize  = 2048;                                      //nand一个page的有效数据区大小
    nand_dev.page_sparesize = 64;                                        //nand一个page的spare区大小
    nand_dev.block_pagenum  = 64;                                        //nand一个block所包含的page数目
    nand_dev.plane_blocknum = 2048;                                      //nand一个plane所包含的block数目
    nand_dev.block_totalnum = 4096;                                      //nand的总block数目
  }
  else if(nand_dev.id == MT29F2G08ABAEA)                                 //NAND为MT29F2G08ABAEA
  {
    nand_dev.page_totalsize = 2112;                                      //nand一个page的总大小（包括spare区）
    nand_dev.page_mainsize  = 2048;                                      //nand一个page的有效数据区大小
    nand_dev.page_sparesize = 64;                                        //nand一个page的spare区大小
    nand_dev.block_pagenum  = 64;                                        //nand一个block所包含的page数目
    nand_dev.plane_blocknum = 1024;                                      //nand一个plane所包含的block数目
    nand_dev.block_totalnum = 2048;                                      //nand的总block数目
  }
  else if(nand_dev.id == MT29F8G08ABACA)                                 //NAND为MT29F4G08ABADA
  {
    nand_dev.page_totalsize = 4320;                                      //nand一个page的总大小（包括spare区）
    nand_dev.page_mainsize  = 4096;                                      //nand一个page的有效数据区大小
    nand_dev.page_sparesize = 224;                                        //nand一个page的spare区大小
    nand_dev.block_pagenum  = 64;                                        //nand一个block所包含的page数目
    nand_dev.plane_blocknum = 2048;                                      //nand一个plane所包含的block数目
    nand_dev.block_totalnum = 4096;                                      //nand的总block数目
  }
  else
  {
    return 1;    //错误，返回
  }

  #if 0
  // 测试代码开始
  uint32_t testFlag = 0;
  if (testFlag) {
    if (testFlag == 0Xffffffff) {
        NAND_EraseChip();
        testFlag = 0;
    } else {
        NAND_EraseBlock(testFlag - 1);
        NAND_EraseBlock(testFlag + 1);
        testFlag -= 1;
    }
    uint16_t secSizePerPage = nand_dev.page_mainsize / NAND_ECC_SECTOR_SIZE;
    uint8_t *buf1  = new uint8_t[NAND_ECC_SECTOR_SIZE];
    uint8_t *buf2 = new uint8_t[NAND_ECC_SECTOR_SIZE];
    uint16_t i, j, index;
    for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++) {
        buf1[i] = 0xAA;
        buf2[i] = 0x55;
        // 为了ECC能生成非0值
        if (i == NAND_ECC_SECTOR_SIZE - 1) {
            buf1[i] += 33;
            buf2[i] += 33;
        }
    }
    for (i = 1; i < secSizePerPage - 1; i++) {
        if (i & 1) {
            NAND_WritePage(testFlag * nand_dev.block_pagenum, i * NAND_ECC_SECTOR_SIZE, buf1, NAND_ECC_SECTOR_SIZE);
        } else {
            NAND_WritePage(testFlag * nand_dev.block_pagenum, i * NAND_ECC_SECTOR_SIZE, buf2, NAND_ECC_SECTOR_SIZE);
        }
    }
    if (secSizePerPage % 1) {
        NAND_CopyPageWithWrite(testFlag * nand_dev.block_pagenum, (testFlag + 2)* nand_dev.block_pagenum, (secSizePerPage - 1) * NAND_ECC_SECTOR_SIZE, buf2, NAND_ECC_SECTOR_SIZE);
    } else {
        NAND_CopyPageWithWrite(testFlag * nand_dev.block_pagenum, (testFlag + 2)* nand_dev.block_pagenum, (secSizePerPage - 1) * NAND_ECC_SECTOR_SIZE, buf1, NAND_ECC_SECTOR_SIZE);
    }

    for (index = 0; index < 2;  index++) {
        for (i = 0; i < secSizePerPage; i++) {
            NAND_ReadPage(testFlag * nand_dev.block_pagenum, i * NAND_ECC_SECTOR_SIZE, buf1, NAND_ECC_SECTOR_SIZE);
            uint8_t compareValue = 0x55;
           if (i < 1) {
                compareValue = 0xFF;
           } else if (i == secSizePerPage - 1 && index == 0) {
                compareValue = 0xFF;
           } else if (i & 1) {
                compareValue = 0xAA;
            }
            for (j = 0; j < NAND_ECC_SECTOR_SIZE; j++) {
                if (j != NAND_ECC_SECTOR_SIZE - 1) {
                    if (buf1[j] != compareValue) {
                        buf1[j] = 0xA5;
                    }
                } else {
                    if (buf1[j] != compareValue && buf1[j] != compareValue + 33) {
                        buf1[j] = 0xA5;
                    }
                }
            }
        }
        testFlag += 2;
    }
    delete []buf1;
    delete []buf2;
  }
  // 测试代码结束
  #endif
  return 0;
}

//配置MPU的region
void NAND_MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_Initure;

  HAL_MPU_Disable();                                       //配置MPU之前先关闭MPU,配置完成以后在使能MPU

  //配置RAM为region1，大小为256MB，此区域可读写
  MPU_Initure.Enable = MPU_REGION_ENABLE;                  //使能region
  MPU_Initure.Number = NAND_REGION_NUMBER;                 //设置region，NAND使用的region0
  MPU_Initure.BaseAddress = NAND_ADDRESS_START;            //region基地址
  MPU_Initure.Size   = NAND_REGION_SIZE;                   //region大小
  MPU_Initure.SubRegionDisable = 0X00;
  MPU_Initure.TypeExtField     = MPU_TEX_LEVEL0;
  MPU_Initure.AccessPermission = MPU_REGION_FULL_ACCESS;   //此region可读写
  MPU_Initure.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE; //允许读取此区域中的指令
  MPU_Initure.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_Initure.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_Initure.IsBufferable     = MPU_ACCESS_BUFFERABLE;
  HAL_MPU_ConfigRegion(&MPU_Initure);

  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT); //开启MPU
}

/**
 * @brief      设置模式
 *
 * @param[in]  mode
 *
 * @return     0,成功;其他,失败
 */
unsigned char NAND_ModeSet(unsigned char mode)
{
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_FEATURE; //发送设置特性命令
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = 0X01;         //地址为0X01,设置mode
  *(__IO unsigned char *)NAND_ADDRESS = mode;                         //P1参数,设置mode
  *(__IO unsigned char *)NAND_ADDRESS = 0;
  *(__IO unsigned char *)NAND_ADDRESS = 0;
  *(__IO unsigned char *)NANDATTR_ADDRESS = 0;
  if(NAND_WaitForReady() == NSTA_READY)
    return 0;    //成功
  else
    return 1;    //失败
}


/**
 * @brief      读取NAND FLASH的ID
 *                 不同的NAND略有不同，请根据自己所使用的NAND FALSH数据手册来编写函数
 *
 * @return     NAND FLASH的ID值
 */
unsigned int NAND_ReadID(void)
{
  unsigned char  deviceid[5];
  unsigned int id;

  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_READID; //发送读取ID命令
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = 0X00;
  //ID一共有5个字节
  deviceid[0] = *(__IO unsigned char *)NAND_ADDRESS;
  deviceid[1] = *(__IO unsigned char *)NAND_ADDRESS;
  deviceid[2] = *(__IO unsigned char *)NAND_ADDRESS;
  deviceid[3] = *(__IO unsigned char *)NAND_ADDRESS;
  deviceid[4] = *(__IO unsigned char *)NAND_ADDRESS;
  //镁光的NAND FLASH的ID一共5个字节，但是为了方便我们只取4个字节组成一个32位的ID值
  //根据NAND FLASH的数据手册，只要是镁光的NAND FLASH，那么一个字节ID的第一个字节都是0X2C
  //所以我们就可以抛弃这个0X2C，只取后面四字节的ID值。
  id = ((unsigned int)deviceid[1] ) << 24 | ((unsigned int)deviceid[2] ) << 16 | ((unsigned int)deviceid[3] ) << 8 | deviceid[4];
  return id;
}


/**
 * @brief      读NAND状态
 *
 * @return     NAND状态值
 *                 bit0:0,成功;1,错误(编程/擦除/READ)
 *                 bit6:0,Busy;1,Ready
 */
unsigned char NAND_ReadStatus(void)
{
  __IO unsigned char data = 0;

  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD ) = NAND_READSTA; //发送读状态命令
  data = *(__IO unsigned char *)NAND_ADDRESS; //读取状态值
  return data;
}


/**
 * @brief      等待NAND准备好
 *
 * @return     NSTA_TIMEOUT 等待超时了;NSTA_READY    已经准备好
 */
unsigned char NAND_WaitForReady(void)
{
  unsigned char status = 0;
  volatile unsigned int time = 0;

  while(1)                      //等待ready
  {
    status = NAND_ReadStatus(); //获取状态值
    if(status & NSTA_READY) {
        if (status & NSTA_ERROR)  
            return NSTA_ERROR;
        return NSTA_READY;
    } 
    time++;
    if(time >= 1000000)
      break;  //超时
  }
  return NSTA_TIMEOUT;        //准备好
}


/**
 * @brief      复位NAND
 *
 * @return     0,成功;其他,失败
 */
unsigned char NAND_Reset(void)
{
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD ) = NAND_RESET; //复位NAND
  if(NAND_WaitForReady() == NSTA_READY)
    return 0;                                                //复位成功
  else
    return 1;                                                //复位失败
}


/**
 * @brief      等待RB信号为某个电平
 *
 * @param[in]  rb    0,等待RB==0 1,等待RB==1
 *
 * @return     0,成功;1,超时
 */
unsigned char NAND_WaitRB(__IO unsigned char rb)
{
  volatile unsigned int time = 0;

  while(time < 1000000)
  {
    time++;
    if(NAND_RB == rb)
      return 0;
  }
  return 1;
}
//NAND延时
void NAND_Delay(volatile unsigned int i)
{
  while(i > 0)
    i--;
}


/**
 * @brief      读取NAND Flash的指定页指定列的数据(main区和spare区都可以使用此函数)
 *
 * @param[in]  PageNum        要读取的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum         要读取的列开始地址(也就是页内地址),范围:0~(page_totalsize-1)
 * @param      pBuffer        指向数据存储区
 * @param[in]  NumByteToRead  读取字节数(不能跨页读)
 *
 * @return     0,成功 ;其他,错误代码
 */
unsigned char NAND_ReadPage(unsigned int PageNum, unsigned short ColNum, unsigned char *pBuffer, unsigned short NumByteToRead)
{
  volatile unsigned short i = 0;
  unsigned char res = 0;
  unsigned char eccnum = 0;      //需要计算的ECC个数，每NAND_ECC_SECTOR_SIZE字节计算一个ecc
  unsigned char eccstart    = 0; //第一个ECC值所属的地址范围
  unsigned char errsta = 0;
  unsigned char *p;

  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_AREA_A;
  //发送地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)ColNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( ColNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 16 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_AREA_TRUE1;
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_TIMEOUT;
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_AREA_A;
  //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
  //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
  //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
  //闲状态，结果我们就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!大家也可以将下面两行
  //代码换成延时函数,只不过这里我们为了效率所以没有用延时函数。
  //res = NAND_WaitRB(0);                    //等待RB=0
  //if(res)
  //  return NSTA_TIMEOUT;                   //超时退出
  //NAND_Delay(10000);
  //下面2行代码是真正判断NAND是否准备好的
  //res = NAND_WaitRB(1);                    //等待RB=1
  //if(res)
  //  return NSTA_TIMEOUT;                   //超时退出
  //for (i = 0; i < 20; i++);
  //while( NAND_RB == 0);
  if(NumByteToRead % NAND_ECC_SECTOR_SIZE) //不是NAND_ECC_SECTOR_SIZE的整数倍，不进行ECC校验
  {
    //读取NAND FLASH中的值
    for(i = 0; i < NumByteToRead; i++)
    {
      *(__IO unsigned char *)pBuffer++ = *(__IO unsigned char *)NAND_ADDRESS;
      //printf("NAND_ReadPage NAND_ADDRESS=%2x\r\n",*(__IO unsigned char*)pBuffer);
    }
  }
  else
  {
    eccnum   = NumByteToRead / NAND_ECC_SECTOR_SIZE;          //得到ecc计算次数
    eccstart = ColNum / NAND_ECC_SECTOR_SIZE;
    p = pBuffer;
    for(res = 0; res < eccnum; res++)
    {
      FMC_NAND_DEVICE->PCR2 |= 1 << 6;              //使能ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, ENABLE);
      for(i = 0; i < NAND_ECC_SECTOR_SIZE; i++) //读取NAND_ECC_SECTOR_SIZE个数据
      {
        *(__IO unsigned char *)pBuffer++ = *(__IO unsigned char *)NAND_ADDRESS;
      }
      while(!( FMC_NAND_DEVICE->SR2 & ( 1 << 6 )))
        ;                                                                      //等待FIFO空
      //while(FMC_GetFlagStatus(FMC_Bank_NAND_USE, FMC_FLAG_FEMPT))
      nand_dev.ecc_hdbuf[res + eccstart] = FMC_NAND_DEVICE->ECCR2;                 //读取硬件计算后的ECC值
      //nand_dev.ecc_hdbuf[res+eccstart]= FMC_GetECC(FMC_Bank_NAND_USE);
      FMC_NAND_DEVICE->PCR2 &= ~( 1 << 6 );                                        //禁止ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, DISABLE);
    }
    i = nand_dev.page_mainsize + 0X10 + eccstart * 4;                          //从spare区的0X10位置开始读取之前存储的ecc值
    unsigned char readForDelay;
    *(__IO unsigned char *)&readForDelay = *(__IO unsigned char *)NANDATTR_ADDRESS;
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = 0X05;                      //随机读指令
    //发送地址
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)i;
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( i >> 8 );
    *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = 0XE0;                      //开始读数据
    pBuffer = (unsigned char *)&nand_dev.ecc_rdbuf[eccstart];
    for(i = 0; i < 4 * eccnum; i++)                                            //读取保存的ECC值
    {
      *(__IO unsigned char *)pBuffer++ = *(__IO unsigned char *)NAND_ADDRESS;
    }
    for(i = 0; i < eccnum; i++)                                                //检验ECC
    {
      // 擦除后，没写之前，没ECC码，计算的ECC码为0，此种场景直接判断正常
      if (nand_dev.ecc_rdbuf[i + eccstart] == 0xFFFFFFFF && nand_dev.ecc_hdbuf[i + eccstart] == 0) {
        continue;
      }
      if(nand_dev.ecc_rdbuf[i + eccstart] != nand_dev.ecc_hdbuf[i + eccstart]) //不相等,需要校正
      {
//                printf("err hd,rd:0x%x,0x%x\r\n",nand_dev.ecc_hdbuf[i+eccstart],nand_dev.ecc_rdbuf[i+eccstart]);
//                 printf("eccnum,eccstart:%d,%d\r\n",eccnum,eccstart);
//                printf("PageNum,ColNum:%d,%d\r\n",PageNum,ColNum);
        res = NAND_ECC_Correction(p + NAND_ECC_SECTOR_SIZE * i, nand_dev.ecc_rdbuf[i + eccstart], nand_dev.ecc_hdbuf[i + eccstart]); //ECC校验
        if(res)
          errsta = NSTA_ECC2BITERR;                                                                                                  //标记2BIT及以上ECC错误
        else
          errsta = NSTA_ECC1BITERR;                                                                                                  //标记1BIT ECC错误
      }
    }
  }
  return errsta;          //成功
}


/**
 * @brief      读取NAND Flash的指定页指定列的数据(main区和spare区都可以使用此函数),并对比(FTL管理时需要)
 *
 * @param[in]  PageNum        要读取的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum         要读取的列开始地址(也就是页内地址),范围:0~(page_totalsize-1)
 * @param      CmpVal         要对比的值,以unsigned int为单位
 * @param[in]  NumByteToRead  读取字节数(不能跨页读)
 * @param      NumByteEqual   从初始位置持续与CmpVal值相同的数据个数
 *
 * @return     0,成功 ;其他,错误代码
 */
unsigned char NAND_ReadPageComp(unsigned int PageNum, unsigned short ColNum, unsigned int CmpVal, unsigned short NumByteToRead, unsigned short *NumByteEqual)
{
  unsigned short i   = 0;

  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_AREA_A;
  //发送地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)ColNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( ColNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 16 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_AREA_TRUE1;
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_TIMEOUT;
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_AREA_A;
  //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
  //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
  //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
  //闲状态，结果我们就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!大家也可以将下面两行
  //代码换成延时函数,只不过这里我们为了效率所以没有用延时函数。
  //res = NAND_WaitRB(0);              //等待RB=0
  //if(res)
  //  return NSTA_TIMEOUT;             //超时退出
  //下面2行代码是真正判断NAND是否准备好的
  //res = NAND_WaitRB(1);              //等待RB=1
  //if(res)
  //  return NSTA_TIMEOUT;             //超时退出
  for(i = 0; i < NumByteToRead; i++) //读取数据,每次读4字节
  {
    if(*(volatile unsigned int *)NAND_ADDRESS != CmpVal)
      break;                         //如果有任何一个值,与CmpVal不相等,则退出.
  }
  *NumByteEqual = i;                 //与CmpVal值相同的个数
  return 0;                          //成功
}


/**
 * @brief      在NAND一页中写入指定个字节的数据(main区和spare区都可以使用此函数)
 *
 * @param[in]  PageNum         要写入的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum          要写入的列开始地址(也就是页内地址),范围:0~(page_totalsize-1)
 * @param      pBuffer         指向数据存储区
 * @param[in]  NumByteToWrite  要写入的字节数，该值不能超过该页剩余字节数
 *
 * @return     0,成功;其他,错误代码
 */
unsigned char NAND_WritePage(unsigned int PageNum, unsigned short ColNum, unsigned char *pBuffer, unsigned short NumByteToWrite)
{
  volatile unsigned short i = 0;
  unsigned char res = 0;
  unsigned char eccnum = 0;      //需要计算的ECC个数，每NAND_ECC_SECTOR_SIZE字节计算一个ecc
  unsigned char eccstart    = 0; //第一个ECC值所属的地址范围

  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_WRITE0;
  //发送地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)ColNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( ColNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 8 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 16 );
  if(NumByteToWrite % NAND_ECC_SECTOR_SIZE) //不是NAND_ECC_SECTOR_SIZE的整数倍，不进行ECC校验
  {
    for(i = 0; i < NumByteToWrite; i++)     //写入数据
    {
      *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
    }
  }
  else
  {
    eccnum   = NumByteToWrite / NAND_ECC_SECTOR_SIZE; //得到ecc计算次数
    eccstart = ColNum / NAND_ECC_SECTOR_SIZE;
    for(res = 0; res < eccnum; res++)
    {
      FMC_NAND_DEVICE->PCR2 |= 1 << 6;                    //使能ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, ENABLE);
      for(i = 0; i < NAND_ECC_SECTOR_SIZE; i++)       //写入NAND_ECC_SECTOR_SIZE个数据
      {
        *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
      }
      while(!( FMC_NAND_DEVICE->SR2 & ( 1 << 6 )))
        ;                                                      //等待FIFO空
      //while(FMC_GetFlagStatus(FMC_Bank_NAND_USE, FMC_FLAG_FEMPT))
      nand_dev.ecc_hdbuf[res + eccstart] = FMC_NAND_DEVICE->ECCR2; //读取硬件计算后的ECC值
      //nand_dev.ecc_hdbuf[res+eccstart]=FMC_GetECC(FMC_Bank_NAND_USE);
      FMC_NAND_DEVICE->PCR2 &= ~( 1 << 6 );                        //禁止ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, DISABLE);
    }
    i = nand_dev.page_mainsize + 0X10 + eccstart * 4;          //计算写入ECC的spare区地址
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = 0X85;      //随机写指令
    //发送地址
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)i;
    *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = (unsigned char)( i >> 8 );
    pBuffer = (unsigned char *)&nand_dev.ecc_hdbuf[eccstart];
    for(i = 0; i < eccnum; i++)                                //写入ECC
    {
      for(res = 0; res < 4; res++)
      {
        *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
      }
    }
  }
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD ) = NAND_WRITE_TURE1;
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;  //失败
  return 0;             //成功
}


/**
 * @brief      在NAND一页中的指定地址开始,写入指定长度的恒定数字
 *
 * @param[in]  PageNum         要写入的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum          要写入的列开始地址(也就是页内地址),范围:0~(page_totalsize-1)
 * @param[in]  cval            要写入的指定常数
 * @param[in]  NumByteToWrite  要写入的字数(以4字节为单位)
 *
 * @return     0,成功  其他,错误代码
 */
unsigned char NAND_WritePageConst(unsigned int PageNum, unsigned short ColNum, unsigned int cval, unsigned short NumByteToWrite)
{
  unsigned short i = 0;

  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_WRITE0;
  //发送地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)ColNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( ColNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 8 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = (unsigned char)( PageNum >> 16 );
  for(i = 0; i < NumByteToWrite; i++) //写入数据,每次写4字节
  {
    *(volatile unsigned int *)NAND_ADDRESS = cval;
  }
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_WRITE_TURE1;
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;  //失败
  return 0;             //成功
}


/**
 * @brief      将一页数据拷贝到另一页,不写入新数据
 *
 * @param[in]  Source_PageNum  源页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  Dest_PageNum    目的页地址,范围:0~(block_pagenum*block_totalnum-1)
 *
 * @return     0,成功 其他,错误代码
 */
unsigned char NAND_CopyPageWithoutWrite(unsigned int Source_PageNum, unsigned int Dest_PageNum)
{
  unsigned short source_block = 0, dest_block = 0;

  //判断源页和目的页是否在同一个plane中
  source_block = Source_PageNum / nand_dev.block_pagenum;
  dest_block   = Dest_PageNum / nand_dev.block_pagenum;
  if(( source_block % 2 ) != ( dest_block % 2 ))
    return NSTA_ERROR;                                                //不在同一个plane内
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD0; //发送命令0X00
  //发送源页地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)Source_PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Source_PageNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Source_PageNum >> 16 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD1; //发送命令0X35
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;  //失败
  //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
  //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
  //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
  //闲状态，结果我们就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!大家也可以将下面两行
  //代码换成延时函数,只不过这里我们为了效率所以没有用延时函数。
  //res = NAND_WaitRB(0);                                               //等待RB=0
  //if(res)
  //  return NSTA_TIMEOUT;                                              //超时退出
  //下面2行代码是真正判断NAND是否准备好的
  //res = NAND_WaitRB(1);                                               //等待RB=1
  //if(res)
  //  return NSTA_TIMEOUT;                                              //超时退出
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD2; //发送命令0X85
  //发送目的页地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)Dest_PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Dest_PageNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Dest_PageNum >> 16 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD3; //发送命令0X10
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;                                                //NAND未准备好
  return 0;                                                           //成功
}


/**
 * @brief      将一页数据拷贝到另一页,并且可以写入数据
 *                 注意:源页和目的页要在同一个Plane内！
 *
 * @param[in]  Source_PageNum  源页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  Dest_PageNum    目的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum          页内列地址,范围:0~(page_totalsize-1)
 * @param      pBuffer         要写入的数据
 * @param[in]  NumByteToWrite  要写入的数据个数
 *
 * @return     0,成功 其他,错误代码
 */
unsigned char NAND_CopyPageWithWrite(unsigned int Source_PageNum, unsigned int Dest_PageNum, unsigned short ColNum, unsigned char *pBuffer, unsigned short NumByteToWrite)
{
  unsigned char  res          = 0;
  volatile unsigned short i   = 0;
  unsigned short source_block = 0, dest_block = 0;
  unsigned char  eccnum       = 0; //需要计算的ECC个数，每NAND_ECC_SECTOR_SIZE字节计算一个ecc
  unsigned char  eccstart     = 0; //第一个ECC值所属的地址范围

  //判断源页和目的页是否在同一个plane中
  source_block = Source_PageNum / nand_dev.block_pagenum;
  dest_block   = Dest_PageNum / nand_dev.block_pagenum;
  if(( source_block % 2 ) != ( dest_block % 2 ))
    return NSTA_ERROR;                                                //不在同一个plane内
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD0; //发送命令0X00
  //发送源页地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)0;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)Source_PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Source_PageNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Source_PageNum >> 16 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD1; //发送命令0X35
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;                                                //NAND未准备好
  //下面两行代码是等待R/B引脚变为低电平，其实主要起延时作用的，等待NAND操作R/B引脚。因为我们是通过
  //将STM32的NWAIT引脚(NAND的R/B引脚)配置为普通IO，代码中通过读取NWAIT引脚的电平来判断NAND是否准备
  //就绪的。这个也就是模拟的方法，所以在速度很快的时候有可能NAND还没来得及操作R/B引脚来表示NAND的忙
  //闲状态，结果我们就读取了R/B引脚,这个时候肯定会出错的，事实上确实是会出错!大家也可以将下面两行
  //代码换成延时函数,只不过这里我们为了效率所以没有用延时函数。
  //res = NAND_WaitRB(0);                                               //等待RB=0
  //if(res)
  //  return NSTA_TIMEOUT;                                              //超时退出
  //下面2行代码是真正判断NAND是否准备好的
  //res = NAND_WaitRB(1);                                               //等待RB=1
  //if(res)
  //  return NSTA_TIMEOUT;                                              //超时退出
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_MOVEDATA_CMD2; //发送命令0X85
  //发送目的页地址
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)ColNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( ColNum >> 8 );
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)Dest_PageNum;
  *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( Dest_PageNum >> 8 );
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = (unsigned char)( Dest_PageNum >> 16 );
  //发送页内列地址
  if(NumByteToWrite % NAND_ECC_SECTOR_SIZE) //不是NAND_ECC_SECTOR_SIZE的整数倍，不进行ECC校验
  {
    for(i = 0; i < NumByteToWrite; i++)     //写入数据
    {
      *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
    }
  }
  else
  {
    eccnum   = NumByteToWrite / NAND_ECC_SECTOR_SIZE; //得到ecc计算次数
    eccstart = ColNum / NAND_ECC_SECTOR_SIZE;
    for(res = 0; res < eccnum; res++)
    {
      FMC_NAND_DEVICE->PCR2 |= 1 << 6;                    //使能ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, ENABLE);
      for(i = 0; i < NAND_ECC_SECTOR_SIZE; i++)       //写入NAND_ECC_SECTOR_SIZE个数据
      {
        *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
      }
      while(!( FMC_NAND_DEVICE->SR2 & ( 1 << 6 )))
        ;                                                      //等待FIFO空
      //while(FMC_GetFlagStatus(FMC_Bank_NAND_USE, FMC_FLAG_FEMPT))
      nand_dev.ecc_hdbuf[res + eccstart] = FMC_NAND_DEVICE->ECCR2; //读取硬件计算后的ECC值
      //nand_dev.ecc_hdbuf[res+eccstart]=FMC_GetECC(FMC_Bank_NAND_USE);//FMC_Bank2_3->ECCR3;
      FMC_NAND_DEVICE->PCR2 &= ~( 1 << 6 );                        //禁止ECC校验
      //FMC_NANDECCCmd(FMC_Bank_NAND_USE, DISABLE);
    }
    i = nand_dev.page_mainsize + 0X10 + eccstart * 4;          //计算写入ECC的spare区地址
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = 0X85;      //随机写指令
    //发送地址
    *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)i;
    *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_ADDR ) = (unsigned char)( i >> 8 );
    pBuffer = (unsigned char *)&nand_dev.ecc_hdbuf[eccstart];
    for(i = 0; i < eccnum; i++)                                //写入ECC
    {
      for(res = 0; res < 4; res++)
      {
        *(__IO unsigned char *)NAND_ADDRESS = *(__IO unsigned char *)pBuffer++;
      }
    }
  }
  *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD ) = NAND_MOVEDATA_CMD3; //发送命令0X10
  if(NAND_WaitForReady() != NSTA_READY)
    return NSTA_ERROR;                                               //失败
  return 0;                                                          //成功
}


/**
 * @brief      读取spare区中的数据
 *
 * @param[in]  PageNum        要写入的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum         要写入的spare区地址(spare区中哪个地址),范围:0~(page_sparesize-1)
 * @param      pBuffer        接收数据缓冲区
 * @param[in]  NumByteToRead  要读取的字节数(不大于page_sparesize)
 *
 * @return     0,成功 其他,错误代码
 */
unsigned char NAND_ReadSpare(unsigned int PageNum, unsigned short ColNum, unsigned char *pBuffer, unsigned short NumByteToRead)
{
  unsigned char temp = 0;
  unsigned char remainbyte = 0;

  remainbyte = nand_dev.page_sparesize - ColNum;
  if(NumByteToRead > remainbyte)
    NumByteToRead = remainbyte;                                                           //确保要写入的字节数不大于spare剩余的大小
  temp = NAND_ReadPage(PageNum, ColNum + nand_dev.page_mainsize, pBuffer, NumByteToRead); //读取数据
  return temp;
}


/**
 * @brief      向spare区中写数据
 *
 * @param[in]  PageNum         要写入的页地址,范围:0~(block_pagenum*block_totalnum-1)
 * @param[in]  ColNum          要写入的spare区地址(spare区中哪个地址),范围:0~(page_sparesize-1)
 * @param      pBuffer         要写入的数据首地址
 * @param[in]  NumByteToWrite  要写入的字节数(不大于page_sparesize)
 *
 * @return     { description_of_the_return_value }
 */
unsigned char NAND_WriteSpare(unsigned int PageNum, unsigned short ColNum, unsigned char *pBuffer, unsigned short NumByteToWrite)
{
  unsigned char temp = 0;
  unsigned char remainbyte = 0;

  remainbyte = nand_dev.page_sparesize - ColNum;
  if(NumByteToWrite > remainbyte)
    NumByteToWrite = remainbyte;                                                            //确保要读取的字节数不大于spare剩余的大小
  temp = NAND_WritePage(PageNum, ColNum + nand_dev.page_mainsize, pBuffer, NumByteToWrite); //读取
  return temp;
}

/**
 * @brief      擦除一个块
 *
 * @param[in]  BlockNum  要擦除的BLOCK编号,范围:0-(block_totalnum-1)
 *
 * @return     0,擦除成功 其他,擦除失败
 */
unsigned char NAND_EraseBlock(unsigned int BlockNum)
{
  if(nand_dev.id == MT29F16G08ABABA)
    BlockNum <<= 7;        //将块地址转换为页地址
  else if(nand_dev.id == MT29F4G08ABADA || nand_dev.id == MT29F8G08ABACA || nand_dev.id == MT29F2G08ABAEA)
    BlockNum <<= 6;
  else 
    return NSTA_ERROR;
  for (unsigned char i = 0; i < 3; i++) {
      *(__IO unsigned char *)( NAND_ADDRESS | NAND_CMD )  = NAND_ERASE0;
      //发送块地址
      *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)BlockNum;
      *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( BlockNum >> 8 );
      *(__IO unsigned char *)( NAND_ADDRESS | NAND_ADDR ) = (unsigned char)( BlockNum >> 16 );
      *(__IO unsigned char *)( NANDATTR_ADDRESS | NAND_CMD )  = NAND_ERASE1;
      if(NAND_WaitForReady() == NSTA_READY) {
        return 0;  //成功
      }
  }
  return NSTA_ERROR;             //失败
}

/**
 * @brief      全片擦除NAND FLASH
 */
void NAND_EraseChip(void)
{
//    unsigned char status;
  unsigned short i = 0;

  for(i = 0; i < nand_dev.block_totalnum; i++) //循环擦除所有的块
  {
//        status=NAND_EraseBlock(i);
    NAND_EraseBlock(i);
//        if(status)
//            printf("Erase %d block fail!，错误码为%d\r\n",i,status);//擦除失败
  }
}


/**
 * @brief      获取ECC的奇数位/偶数位
 *
 * @param[in]  oe      0偶数  1奇数位
 * @param[in]  eccval  输入ecc值
 *
 * @return     计算后的ecc 最后16位
 */
unsigned short NAND_ECC_Get_OE(unsigned char oe, unsigned int eccval)
{
  unsigned char  i;
  unsigned short ecctemp = 0;

  for(i = 0; i < 24; i++)
  {
    if(( i % 2 ) == oe)
    {
      if(( eccval >> i ) & 0X01)
        ecctemp += 1 << ( i >> 1 );
    }
  }
  return ecctemp;
}


/**
 * @brief      ECC校正函数
 *
 * @param      data_buf  读取出来,
 * @param[in]  eccrd     读取出来,原来保存的ECC值
 * @param[in]  ecccl     读取数据时,硬件计算的ECC只
 *
 * @return     0,错误已修正;其他,ECC错误(有大于2个bit的错误,无法恢复)
 */
unsigned char NAND_ECC_Correction(unsigned char *data_buf, unsigned int eccrd, unsigned int ecccl)
{
  unsigned short eccrdo, eccrde, eccclo, ecccle;
  unsigned short eccchk   = 0;
  unsigned short errorpos = 0;
  unsigned int bytepos  = 0;

  eccrdo = NAND_ECC_Get_OE(1, eccrd); //获取eccrd的奇数位
  eccrde = NAND_ECC_Get_OE(0, eccrd); //获取eccrd的偶数位
  eccclo = NAND_ECC_Get_OE(1, ecccl); //获取ecccl的奇数位
  ecccle = NAND_ECC_Get_OE(0, ecccl); //获取ecccl的偶数位
  eccchk = eccrdo ^ eccrde ^ eccclo ^ ecccle;
  if(eccchk == 0XFFF)                 //全1,说明只有1bit ECC错误
  {
    errorpos = eccrdo ^ eccclo;
//        printf("errorpos:%d\r\n",errorpos);
    bytepos  = errorpos / 8;
    data_buf[bytepos] ^= 1 << ( errorpos % 8 );
  }
  else                   //不是全1,说明至少有2bit ECC错误,无法修复
  {
//        printf("2bit ecc error or more\r\n");
    return 1;
  }
  return 0;
}
