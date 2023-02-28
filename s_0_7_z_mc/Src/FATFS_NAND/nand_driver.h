/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      NAND FLASH MT29FxxABA驱动
*
* 版本:
* V1.0 2019-04-23 初始版本程序移植 
***********************************************************/
#ifndef _NAND_DRIVER_H_
#define _NAND_DRIVER_H_

/* USER CODE BEGIN Prototypes */
#define NAND_MAX_PAGE_SIZE      4096    //定义NAND FLASH的最大的PAGE大小（不包括SPARE区），默认4096字节
#define NAND_ECC_SECTOR_SIZE    256     //执行ECC计算的单元大小，默认512字节

  
//NAND属性结构体
typedef struct
{
    unsigned short page_totalsize;       //每页总大小，main区和spare区总和
    unsigned short page_mainsize;        //每页的main区大小
    unsigned short page_sparesize;       //每页的spare区大小
    unsigned char  block_pagenum;        //每个块包含的页数量
    unsigned short plane_blocknum;       //每个plane包含的块数量
    unsigned short block_totalnum;       //总的块数量
    unsigned short good_blocknum;        //好块数量    
    unsigned short valid_blocknum;       //有效块数量(供文件系统使用的好块数量)
    unsigned int id;                   //NAND FLASH ID
    unsigned short *lut;                 //LUT表，用作逻辑块-物理块转换   
    unsigned int ecc_hard;             //硬件计算出来的ECC值
    unsigned int ecc_hdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];//ECC硬件计算值缓冲区    
    unsigned int ecc_rdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];//ECC读取的值缓冲区
}nand_attriute;      

extern nand_attriute nand_dev;        //nand重要参数结构体 

//#define NAND_RB          PDin(6)     //NAND Flash的闲/忙引脚 
#define NAND_RB            HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)
/* 需要根据原理图NCE引脚编号调整 */
#define NAND_ADDRESS          0x70000000  //nand flash的访问地址,接NCE2,地址为:0X7000 0000
#define NANDATTR_ADDRESS      0x78000000  //nand flash的属性空间访问地址,接NCE2,地址为:0X7800 0000

#define NAND_CMD              1<<16   //发送命令
#define NAND_ADDR             1<<17   //发送地址

//#define NAND_CMD              1<<17   //发送命令
//#define NAND_ADDR             1<<16   //发送地址


//NAND FLASH命令
#define NAND_READID           0X90      //读ID指令
#define NAND_FEATURE          0XEF      //设置特性指令
#define NAND_RESET            0XFF      //复位NAND
#define NAND_READSTA          0X70      //读状态
#define NAND_AREA_A           0X00   
#define NAND_AREA_TRUE1       0X30  
#define NAND_WRITE0           0X80
#define NAND_WRITE_TURE1      0X10
#define NAND_ERASE0           0X60      //擦除Block #1
#define NAND_ERASE1           0XD0      //擦除Block #2
#define NAND_MOVEDATA_CMD0    0X00      //read for internal data move #1
#define NAND_MOVEDATA_CMD1    0X35
#define NAND_MOVEDATA_CMD2    0X85      //program for internal data move #1
#define NAND_MOVEDATA_CMD3    0X10

//NAND FLASH状态
#define NSTA_READY            0X40    //nand已经准备好
#define NSTA_ERROR            0X01    //nand错误
#define NSTA_TIMEOUT          0X02    //超时
#define NSTA_ECC1BITERR       0X03    //ECC 1bit错误
#define NSTA_ECC2BITERR       0X04    //ECC 2bit以上错误


//NAND FLASH型号和对应的ID号
#define MT29F4G08ABADA      0XDC909556  //MT29F4G08ABADA
#define MT29F16G08ABABA     0X48002689  //MT29F16G08ABABA
#define MT29F2G08ABAEA      0xDA909506  //MT29F2G08ABAEA
#define MT29F8G08ABACA      0xD390A664  //MT29F8G08ABACA

//MPU相关设置
#define NAND_REGION_NUMBER      MPU_REGION_NUMBER3      //NAND FLASH使用region0
#define NAND_ADDRESS_START      0X70000000              //NAND FLASH区的首地址
#define NAND_REGION_SIZE        MPU_REGION_SIZE_256MB   //NAND FLASH区大小

unsigned char NAND_Init(void);
unsigned char NAND_ModeSet(unsigned char mode);
unsigned int NAND_ReadID(void);
unsigned char NAND_ReadStatus(void);
unsigned char NAND_WaitForReady(void);
unsigned char NAND_Reset(void);
unsigned char NAND_WaitRB(volatile unsigned char rb);
void NAND_Delay(volatile unsigned int i);
void NAND_MPU_Config(void);
unsigned char NAND_ReadPage(unsigned int PageNum,unsigned short ColNum,unsigned char *pBuffer,unsigned short NumByteToRead);
unsigned char NAND_ReadPageComp(unsigned int PageNum,unsigned short ColNum,unsigned int CmpVal,unsigned short NumByteToRead,unsigned short *NumByteEqual);
unsigned char NAND_WritePage(unsigned int PageNum,unsigned short ColNum,unsigned char *pBuffer,unsigned short NumByteToWrite);
unsigned char NAND_WritePageConst(unsigned int PageNum,unsigned short ColNum,unsigned int cval,unsigned short NumByteToWrite);
unsigned char NAND_CopyPageWithoutWrite(unsigned int Source_PageNum,unsigned int Dest_PageNum);
unsigned char NAND_CopyPageWithWrite(unsigned int Source_PageNum,unsigned int Dest_PageNum,unsigned short ColNum,unsigned char *pBuffer,unsigned short NumByteToWrite);
unsigned char NAND_ReadSpare(unsigned int PageNum,unsigned short ColNum,unsigned char *pBuffer,unsigned short NumByteToRead);
unsigned char NAND_WriteSpare(unsigned int PageNum,unsigned short ColNum,unsigned char *pBuffer,unsigned short NumByteToRead);
unsigned char NAND_EraseBlock(unsigned int BlockNum);
void NAND_EraseChip(void);

unsigned short NAND_ECC_Get_OE(unsigned char oe,unsigned int eccval);
unsigned char NAND_ECC_Correction(unsigned char* data_buf,unsigned int eccrd,unsigned int ecccl);

#endif // _NAND_DRIVER_H_
