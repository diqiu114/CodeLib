//==============================================================================================================================
#include "global.h"
//LDY程序模板，版权所有，违法必究！
//By LDY,mobile:15361844952,2022/7/23
//==============================================================================================================================
//Register Memory
volatile Type_ADC       ADC1    __attribute__((at(BASE_ADC1)));
volatile Type_ADC       ADC2    __attribute__((at(BASE_ADC2)));
volatile Type_ADC       ADC3    __attribute__((at(BASE_ADC3)));
volatile Type_ADC       *ADC[3]={&ADC1,&ADC2,&ADC3};//Array
volatile Type_BKP       BKP     __attribute__((at(BASE_BKP)));
volatile Type_CAN       CAN[2]  __attribute__((at(BASE_CAN1)));//array
volatile Type_CEC       CEC     __attribute__((at(BASE_CEC)));
volatile Type_CRC       CRC     __attribute__((at(BASE_CRC)));
volatile Type_DAC       DAC     __attribute__((at(BASE_DAC)));
volatile Type_DMA       DMA[2]  __attribute__((at(BASE_DMA1)));//array
volatile Type_ETH       ETH     __attribute__((at(BASE_ETH)));
volatile Type_EXTI      EXTI    __attribute__((at(BASE_EXTI)));
volatile Type_FLASH     FLASH   __attribute__((at(BASE_FLASHR)));
volatile Type_OB        OB      __attribute__((at(BASE_OB)));
volatile Type_FSMC      FSMC    __attribute__((at(BASE_FSMC)));
volatile Type_LCD       LCD     __attribute__((at(BASE_LCD)));//FSMC LCD
volatile Type_GPIO      GPIO[7] __attribute__((at(BASE_GPIOA)));//array
volatile Type_AFIO      AFIO    __attribute__((at(BASE_AFIO)));
volatile Type_I2C       I2C[2]  __attribute__((at(BASE_I2C1)));//array
volatile Type_WWDG      WWDG    __attribute__((at(BASE_WWDG)));
volatile Type_IWDG      IWDG    __attribute__((at(BASE_IWDG)));
volatile Type_PWR       PWR     __attribute__((at(BASE_PWR)));
volatile Type_RCC       RCC     __attribute__((at(BASE_RCC)));
volatile Type_RTC       RTC     __attribute__((at(BASE_RTC)));
volatile Type_SDIO      SDIO    __attribute__((at(BASE_SDIO)));
volatile Type_SPI       SPI1    __attribute__((at(BASE_SPI1)));
volatile Type_SPI       SPI2    __attribute__((at(BASE_SPI2)));
volatile Type_SPI       SPI3    __attribute__((at(BASE_SPI3)));
volatile Type_SPI       *SPI[3]={&SPI1,&SPI2,&SPI3};//array
volatile Type_TIM       TIM1    __attribute__((at(BASE_TIM1)));
volatile Type_TIM       TIM2    __attribute__((at(BASE_TIM2)));
volatile Type_TIM       TIM3    __attribute__((at(BASE_TIM3)));
volatile Type_TIM       TIM4    __attribute__((at(BASE_TIM4)));
volatile Type_TIM       TIM5    __attribute__((at(BASE_TIM5)));
volatile Type_TIM       TIM6    __attribute__((at(BASE_TIM6)));
volatile Type_TIM       TIM7    __attribute__((at(BASE_TIM7)));
volatile Type_TIM       TIM8    __attribute__((at(BASE_TIM8)));
volatile Type_TIM       TIM9    __attribute__((at(BASE_TIM9)));
volatile Type_TIM       TIM10   __attribute__((at(BASE_TIM10)));
volatile Type_TIM       TIM11   __attribute__((at(BASE_TIM11)));
volatile Type_TIM       TIM12   __attribute__((at(BASE_TIM12)));
volatile Type_TIM       TIM13   __attribute__((at(BASE_TIM13)));
volatile Type_TIM       TIM14   __attribute__((at(BASE_TIM14)));
volatile Type_TIM       TIM15   __attribute__((at(BASE_TIM15)));
volatile Type_TIM       TIM16   __attribute__((at(BASE_TIM16)));
volatile Type_TIM       TIM17   __attribute__((at(BASE_TIM17)));
volatile Type_TIM       *TIM[17]={&TIM1,&TIM2,&TIM3,&TIM4,&TIM5,&TIM6,&TIM7,&TIM8,&TIM9,&TIM10,&TIM11,&TIM12,&TIM13,&TIM14,&TIM15,&TIM16,&TIM17};//array
volatile Type_UART      UART1   __attribute__((at(BASE_UART1)));
volatile Type_UART      UART2   __attribute__((at(BASE_UART2)));
volatile Type_UART      UART3   __attribute__((at(BASE_UART3)));
volatile Type_UART      UART4   __attribute__((at(BASE_UART4)));
volatile Type_UART      UART5   __attribute__((at(BASE_UART5)));
volatile Type_UART      *UART[5]={&UART1,&UART2,&UART3,&UART4,&UART5};//array
volatile Type_USB       USB     __attribute__((at(BASE_USB)));
volatile Type_USBFS     USBFS   __attribute__((at(BASE_USBFS)));
volatile Type_DES       DES     __attribute__((at(BASE_DES)));
//------------------------------------------------------------------------------------------------------------------------------
volatile Type_ITM       M3ITM   __attribute__((at(BASE_ITM)));
volatile Type_DWT       M3DWT   __attribute__((at(BASE_DWT)));
volatile Type_FPB       M3FPB   __attribute__((at(BASE_FPB)));
volatile Type_SYS       M3SYS   __attribute__((at(BASE_SYS)));
volatile Type_TPI       M3TPI   __attribute__((at(BASE_TPI)));
volatile Type_ETM       M3ETM   __attribute__((at(BASE_ETM)));
volatile Type_DBG       M3DBG   __attribute__((at(BASE_DBG)));
volatile Type_TAB       M3TAB   __attribute__((at(BASE_TAB)));
//==============================================================================================================================
//const
UINT32 const            BASE_ADC[]={BASE_ADC1,BASE_ADC2,BASE_ADC3};
UINT32 const            BASE_SPI[]={BASE_SPI1,BASE_SPI2,BASE_SPI3};
UINT32 const            BASE_TIM[]={BASE_TIM1,BASE_TIM2,BASE_TIM3,BASE_TIM4,BASE_TIM5,BASE_TIM6,BASE_TIM7,BASE_TIM8,BASE_TIM9,\
                        BASE_TIM10,BASE_TIM11,BASE_TIM12,BASE_TIM13,BASE_TIM14,BASE_TIM15,BASE_TIM16,BASE_TIM17};
UINT32 const            BASE_UART[]={BASE_UART1,BASE_UART2,BASE_UART3,BASE_UART4,BASE_UART5};
//------------------------------------------------------------------------------------------------------------------------------
const UINT32 DTF_P_Count=8,DTF_P[32][2]={
                {(UINT32)&Init_SFR,7},{(UINT32)&Init_RCC,89},{(UINT32)&Init_SYS,101},{(UINT32)&Init_FLASH,11},  
                {(UINT32)&Init_GPIO,59},{(UINT32)&Init_EXTI,4},{(UINT32)&Init_SYSTICK,6},{(UINT32)&Init_RTC,4},
                {(UINT32)&Init_TIM,179},{(UINT32)&Init_ADC,85},{(UINT32)&Init_UART,117},{(UINT32)&Init_MEM,134},
                };
//extern void Test_INS(void);
//==============================================================================================================================
int main(void)
{
  //Test_INS();
  register UINT32 R0 __asm("r0");
  register UINT32 R1 __asm("r1");
  __asm("  MRS     R0,MSP");
  __asm("  STR R1,[R0,#0x000E]");
	Init();
  while(1)
  {
    while(!SystemST.VAL);
		if(IMM_Event_On){IMM_Event_On=0;if(DAPP.INTF.IMM_Event)DAPP.INTF.IMM_Event();}
		if(INT_Event_On){INT_Event_On=0;if(DAPP.INTF.INT_Event)DAPP.INTF.INT_Event();}
		if(TMR_Event_On){TMR_Event_On=0;if(DAPP.INTF.TMR_Event)DAPP.INTF.TMR_Event();}
  }
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init(void)
{
  Init_MEM(0);
	Init_SFR();
	Init_RCC();
  Init_PWR();
	Init_SYS();
	Init_FLASH();
	Init_IWDG();
	Init_WWDG();
	Init_FSMC();
	Init_GPIO();
	Init_AFIO();
	Init_EXTI();
	Init_SYSTICK();
  Init_RTC();
	Init_TIM();
	Init_ADC();
	Init_DAC();
	Init_SPI();
  Init_I2S();
	Init_I2C();
	Init_SDIO();
	Init_UART();
	Init_CAN();
	Init_ETH();
	Init_USB();
  Init_USBFS();
	Init_MEM(1);
	Init_IEIP();
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_SFR(void)
{
  DIRQ();	DFIRQ();
	M3SYS.AIRCR=0x05FA0000|(SET_PRIGROUP<<8);
	FLASH_ACR=0x00000012;//72M
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_RCC(void)
{
	RCC_CR=(RCC_CR & 0x0001FFFF)|0x00010001;//PLLON=PLL2ON=PLL3ON=0,HSEON=HSION=1
	RCC_CIR=0x00FF0000;
  RCC.CFGR_BIT.SW=RCC_CFGR_SW_HSI;
	INT[0]=0x0000;while(!RCC.CR_BIT.HSIRDY && INT[0]<0x00ff)INT[0]++;if(INT[0]==0x00FF)RCC.CR_BIT.HSION=0;
	INT[0]=0x0000;while(!RCC.CR_BIT.HSERDY && INT[0]<0x00ff)INT[0]++;if(INT[0]==0x00FF)RCC.CR_BIT.HSEON=0;
  RCC_CFGR=SET_RCC_CFGR; //MCO=0,PLLMUL=7=*9,ADCPRE=0=PCLK2/2,PPRE2=4=HCLK/2,PPRE1=4=HCLK/2,HPRE=0=/1
  RCC.CR_BIT.PLLON=1;
  INT[0]=0x0000;while(!RCC.CR_BIT.PLLRDY && INT[0]<0x0400)INT[0]++;
  RCC.CFGR_BIT.SW=RCC_CFGR_SW_PLL;

#if IsDensity(CL)
	RCC_AHBRSTR=0x00000000;
#endif
#if IsDensity(CL)||IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  RCC_CFGR2 =SET_RCC_CFGR2;
#endif
	
  RCC_APB2RSTR=0x00000000;
  RCC_APB1RSTR=0x00000000;
  RCC_AHBENR=0x00000515;//SDIOEN=FSMCEN=FLITFEN=SRAMEN=DMA1EN=1
  RCC_APB2ENR=0x00005A7D;//AFIOEN=IOPAEN_IOPEEN=ADC1EN=TIM1EN=SPI1EN=UART1EN=1,TIM8_11=TIM15_17=ADC3EN=0
  RCC_APB1ENR=0x00FEC003;//TIM2_3=SPI2_3EN=USART2_5EN=I2C1_2EN=USBEN=1,  TIM5EN=TIM6EN=TIM7EN=USBEN=CAN1EN=DACEN=WWDGEN=0
  RCC_BDCR=0x00008101;//LSEON=RTCEN=1,RTCSEL=1(LSE)
  RCC_CSR=0x1C000000;//LSION=0,PINRSTF=PORRSTF=SFTRSTF=1,IWDGRSTF=WWDGRSTF=LPWRRSTF=0
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_PWR(void)
{
  RCC.APB1ENR_BIT.PWREN=1;PWR_CR=PWR_CSR=0x00;
}
//------------------------------------------------------------------------------------------------------------------------------
void 	Init_SYS(void)
{
	for(Var[0]=0;Var[0]<7;Var[0]++)
	{
	  SYS_ISER(Var[0])=0x00000000;
    SYS_ICER(Var[0])=0x00000000;
    SYS_ISPR(Var[0])=0x00000000;
    SYS_ICPR(Var[0])=0x00000000;
    SYS_IABR(Var[0])=0x00000000;
	}
	for(Var[0]=0;Var[0]<240;Var[0]++)SYS_IP(Var[0])=0x00;
//SCB_Start
  SYS_AIRCR=(SET_PRIGROUP<<8);
  SYS_SCR=0x00000000;
  SYS_CCR=0x00000000;
  for(Var[0]=0;Var[0]<12;Var[0]++)SYS_SHPR(Var[0])=0x00000000;
  SYS_SHCSR=0x00000000;
  SYS_CFSR=0x00000000;
  SYS_HFSR=0x00000000;
  SYS_DFSR=0x00000000;
  SYS_MMFAR=0x00000000;
  SYS_BFAR=0x00000000;
  SYS_AFSR=0x00000000;
  for(Var[0]=0;Var[0]<3;Var[0]++)SYS_PFR(Var[0])=0x00000000;
  SYS_DFR=0x00000000;
  SYS_AFR=0x00000000;
  for(Var[0]=0;Var[0]<4;Var[0]++)SYS_MMFR(Var[0])=0x00000000;
  for(Var[0]=0;Var[0]<5;Var[0]++)SYS_ISAR(Var[0])=0x00000000;

//MPU_Start
  SYS_TYPE=0x00000000;
  SYS_CTRL=0x00000000;
  SYS_RNR=0x00000000;
  SYS_RBAR=0x00000000;
  SYS_RASR=0x00000000;
  SYS_RBARA1=0x00000000;
  SYS_RASRA1=0x00000000;
  SYS_RBARA2=0x00000000;
  SYS_RASRA2=0x00000000;
  SYS_RBARA3=0x00000000;
  SYS_RASRA3=0x00000000;
//MPU_END	
//CDB_Start
  SYS_DHCSR=0x00000000;
  SYS_DCRSR=0x00000000;
  SYS_DCRDR=0x00000000;
  SYS_DEMCR=0x00000000;
//CDB_End
  SYS_SOFTTRIG=0x00000000;
//SCB End
  SYS_STIR=0x00000000;
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_FLASH(void)
{
	FLASH_SR=0x00000000;
	FLASH_AR=0x00000000;
	FLASH_OBR=0x00000000;
	FLASH_WRP=0x00000000;
	#if IsDensity(XL)
	FLASH_KEYR2=0x00000000;
	FLASH_SR2=0x00000000;
	FLASH_AR2=0x00000000;
	#endif
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_IWDG(void)
{
#if SDK_IWDG_ON  
  IWDG.KR=0x5555;
  IWDG.PR=SET_IWDG_PR_DIV;
  IWDG.RLR=0x0fff;
  IWDG.KR=0xAAAA;
#endif
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_WWDG(void)
{
#if SDK_WWDG_ON  
	RCC.APB1ENR_BIT.WWDGEN=1;
	WWDG.CFR =(SET_WWDG_CFR_WDGTB<<7)|SET_WWDG_CFR_W;
	WWDG.CR=0x007F;//WDGA=0,T=0x7F
	WWDG.SR_BIT.EWIF=0;
#endif  
}  
//-----------------------------------------------------------------------------------------------------------------------------
void Init_FSMC(void)
{
	RCC.AHBENR_BIT.FSMCEN=SDK_FSMC_ON;
#if SDK_FSMC_ON  
  //Bank1
  FSMC_BCR(0) =0x5011;//MBKEN=WREN=EXTMOD=1,MWID=1(16bit),MTYP(bit3_2)=0(SRAM)
	FSMC_BTR(0) =0x00000F01;//ADDSET=0x01,ADDHLD=0x00,DATAST=0x0f,BUSTURN=0x00,CLKDIV=DATLAT=ACCMOD(A)=0x00
	FSMC_BWTR(0)=0x00000300;//ADDSET=ADDHLD=0x00,DATAST=0x03,BUSTURN=0x00,ACCMOD(A)=0x00

	for(Var[0]=0;Var[0]<3;Var[0]++)
	{
    FSMC_PCR(Var[0]) =0x00000018;//PTYP=1(NAND FLASH),PWID=1(16 bits)
    FSMC_SR(Var[0])  =0x00000040;
    FSMC_PMEM(Var[0])=0x00000000;
    FSMC_PATT(Var[0])=0x00000000;
    FSMC_PIO4(Var[0])=0x00000000;
    FSMC_ECCR(Var[0])=0x00000000;
	}
#endif  
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_GPIO(void)
{
	RCC.APB2ENR|=((1<<SDK_GPIO_COUNT)-1)<<2;
	for(Var[0]=0;Var[0]<SDK_GPIO_COUNT;Var[0]++)
	{GPIO[Var[0]].CRL=SET_GPIO[Var[0]][0];GPIO[Var[0]].CRH=SET_GPIO[Var[0]][1];GPIO[Var[0]].ODR=SET_GPIO[Var[0]][2];}
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_AFIO(void)
{
	RCC.APB2ENR_BIT.AFIOEN=1;
  AFIO_EVCR=0x00000000;
  AFIO_MAPR=0x02005C10;//CANTXRX=(RB8,RB9),TIM3=3,TIM4=1,SPI1=PA4_7,UART1=PA9/PA10,UART2=PA2/PA3,UART3=PC10/PC11,SWJCFG=2(SW),4(debug disable for IO)
  for(Var[0]=0;Var[0]<4;Var[0]++)AFIO_EXTICR(Var[0])=0x00000000;
  AFIO_MAPR2=0x00000000;
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_EXTI(void)
{
#if SDK_EXT_COUNT 
  for(Var[0]=0;Var[0]<SDK_EXT_COUNT;Var[0]++)
  {
	  Var[1]=DEXT.Item[Var[0]].Setup.PN>>5;Var[2]=DEXT.Item[Var[0]].Setup.PN&0x0F;Var[3]=((DEXT.Item[Var[0]].Setup.PN&3)*4);
	  AFIO.EXTICR[Var[2]/4]&=0xFFFF-(0x0F<<Var[3]);
	  AFIO.EXTICR[Var[2]/4]|=Var[1]<<Var[3];
    if(DEXT.Item[Var[0]].Setup.EN)EXTI.IMR|=(1<<Var[2]);else EXTI.IMR&=~(1<<Var[2]);
	  EXTI.EMR=0x0000;
	  if(DEXT.Item[Var[0]].Setup.Rising)EXTI.RTSR|=(1<<Var[2]);else EXTI.RTSR&=~(1<<Var[2]);
	  if(DEXT.Item[Var[0]].Setup.Falling)EXTI.FTSR|=(1<<Var[2]);else EXTI.FTSR&=~(1<<Var[2]);
	  EXTI.SWIER=0x0000;
	  EXTI.PR=(1<<Var[2]);
	  EXTI_SetIRQ(Var[2]);
  }
#endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_SYSTICK(void)
{
  SYS_STCTRL=0x00000007;//ENABLE=TICKINT=CLKSOURCE=1
  SYS_STLOAD=CLK_AHB/1000-1;//Reload value,1ms
  SYS_STVAL=0x00000000;
	M3SYS.SHPR[((IRQN_SysTick & 0x0F)-4)&0x0f]= (15<<4);
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_RTC(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_TIM(void)
{
	//TIM2
	RCC.APB1ENR_BIT.TIM2EN=1;
	TIM_CR1(1)=0x0081;
	TIM_CR2(1)=0x0000;
	TIM_SMCR(1)=0x0000;
	TIM_DIER(1)=0x0001;
	TIM_SR(1)=0x0000;
	TIM_EGR(1)=0x0000;
	TIM_CCMR(1,0)=0x0000;
	TIM_CCMR(1,1)=0x0000;
	TIM_CCER(1)=0x0000;
	TIM_CNT(1)=0x0000;
	TIM_PSC(1)=(SET_PPRE1<4 ? 35:71);
	TIM_ARR(1)=TIM2_ReloadValue;
	TIM_RCR(1)=0x0000;
	TIM_CCR(1,0)=0x0000;
	TIM_CCR(1,1)=0x0000;
	TIM_CCR(1,2)=0x0000;
	TIM_CCR(1,3)=0x0000;
	TIM_BDTR(1)=0x0000;
	TIM_DCR(1)=0x0000;
	SETIRQ(IRQN_TIM2,0,0);
	//TIM3
	RCC.APB1ENR_BIT.TIM3EN=1;
	TIM_CR1(2)=0x0081;
	TIM_CR2(2)=0x0000;
	TIM_SMCR(2)=0x0000;
	TIM_DIER(2)=0x0000;
	TIM_SR(2)=0x0000;
	TIM_EGR(2)=0x0000;
	TIM_CCMR(2,0)=0x0068;
	TIM_CCMR(2,1)=0x0000;
	TIM_CCER(2)=0x0001;
	TIM_CNT(2)=0x0000;
	TIM_PSC(2)=(SET_PPRE1<4 ? 0:1);
	TIM_ARR(2)=0x0120;//8*36=8us
	TIM_RCR(2)=0x0000;
	TIM_CCR(2,0)=0x0090;//4*36=4us
	TIM_CCR(2,1)=0x0000;
	TIM_CCR(2,2)=0x0000;
	TIM_CCR(2,3)=0x0000;
	TIM_BDTR(2)=0x0000;
	TIM_DCR(2)=0x0000;
	//TIM4
	RCC.APB1ENR_BIT.TIM4EN=1;
	TIM_CR1(3)=0x0081;
	TIM_CR2(3)=0x0000;
	TIM_SMCR(3)=0x0000;
	TIM_DIER(3)=0x0001;
	TIM_SR(3)=0x0000;
	TIM_EGR(3)=0x0000;
	TIM_CCMR(3,0)=0x0068;
	TIM_CCMR(3,1)=0x0000;
	TIM_CCER(3)=0x0000;//0x0001=Open 38K PWM
	TIM_CNT(3)=0x0000;
	TIM_PSC(3)=(SET_PPRE1<4 ? 0:1);
	TIM_ARR(3)=0x03B3;//1/38kHz=26.316us,26.316us*36=0x3b3
	TIM_RCR(3)=0x0000;
	TIM_CCR(3,0)=0x01DA;//13.158us*36=474
	TIM_CCR(3,1)=0x0000;
	TIM_CCR(3,2)=0x0000;
	TIM_CCR(3,3)=0x0000;
	TIM_BDTR(3)=0x0000;
	TIM_DCR(3)=0x0000;
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_ADC(void)
{
	//ADC0
#if SDK_ADC_COUNT
	UINT32 *p;
#endif
  RCC.APB2ENR&=0xFFFF7DFF;//ADC12EN=ADC3EN=0
#if SDK_ADC_COUNT
  DADC.Count=SDK_ADC_COUNT; DADC.Item[0].HWIndex=0; Var[2]=DADC.Item[0].HWIndex; DADC.Item[0].V=(UINT32 *)&DADC.ADC1_V;
  ADC_SetClock(0);
	RCC.APB2RSTR_BIT.ADC1RST=0;
  ADC_SR(0)=0x00000000;
  ADC_CR1(0)=0x00066100;//EOCIE0=ADWIE=JEOCIE=0,SCAN=1,DISCEN=0,DISCNUM=3,DUALMOD=6
  ADC_CR2(0)=0x001E0101;//ADON=EXTTRIG=DMA=1,EXTSEL=7(SWSTART)
  ADC_SMPR(0,0)=0x0000FFFF;//SMP=7(239.5 cycles)
  ADC_SMPR(0,1)=0x00000000;
  ADC_JOFR(0,0)=0x00000000;
  ADC_JOFR(0,1)=0x00000000;
  ADC_JOFR(0,2)=0x00000000;
  ADC_JOFR(0,3)=0x00000000;
  ADC_HTR(0)=0x00000000;
  ADC_LTR(0)=0x00000000;
	
	//Set regular channel
  ADC_SQR(0,0)=0x00000000;
  ADC_SQR(0,1)=0x00000000;
  ADC_SQR(0,2)=0x00000000;	
	
	LNG[0]=0;Var[1]=0;TempFlag0=0;
	p=(UINT32 *)&(*ADC[0]).SQR[2];
	for(Var[0]=0;Var[0]<SDK_ADC1_CHCOUNT;Var[0]++)
	{LNG[0]+=(ADC1_CH[Var[0]]<<(5*Var[1]));Var[1]++;if(Var[1]>=6){*p=LNG[0];p--;LNG[0]=0;Var[1]=0;}}
	if(Var[1])*p=LNG[0];
	if(SDK_ADC1_CHCOUNT)(*ADC[0]).SQR_BIT[0].P4=SDK_ADC1_CHCOUNT-1;

  ADC_JSQR(0)=0x00000000;
  ADC_JDR(0,0)=0x00000000;
  ADC_JDR(0,1)=0x00000000;
  ADC_JDR(0,2)=0x00000000;
  ADC_JDR(0,3)=0x00000000;
  ADC_DR(0)=0x00000000;
	Var[0]=0x00;ADC_CR2_RSTCAL(0)=1;
	while(ADC_CR2_RSTCAL(0)==1&&Var[0]<0x80)Var[0]++;
	Var[0]=0x00;ADC_CR2_CAL(0)=1; 
	while(ADC_CR2_CAL(0)==1&&Var[0]<0x80)Var[0]++;
  //SETIRQ(IRQN_ADC12,0,0);
	
	RCC.AHBENR_BIT.DMA1EN=1;
	DMA[0].CH[0].CMAR=(UINT32)&DADC.ADC1_V;
	DMA[0].CH[0].CPAR=(UINT32)&ADC_DR(0);
	DMA[0].CH[0].CNDTR=SDK_ADC1_AVCOUNT*SDK_ADC1_CHCOUNT;
	DMA[0].CH[0].CCR=0x00002AA3;//TCIE=CIRC=MINC=1,PSIZE=MSIZE=2(32bits),PL=2(high)
	SETIRQ(IRQN_DMA1_CH1,0,0);
#endif  
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_DAC(void)
{
  RCC.APB1ENR_BIT.DACEN=(SDK_DAC_COUNT ? 1:0);
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_SPI(void)
{
  #if SDK_SPI_COUNT
  DSPI.Count=SDK_SPI_COUNT;Var[1]=0x00;
  for(Var[0]=0;Var[0]<SDK_SPI_COUNT;Var[0]++)
  {
    while((SDK_SPI_ON & (1<<Var[1]))==0x00 && Var[1]<SDK_SPI_MAXCOUNT)Var[1]++;
    DSPI.Item[Var[0]].HWIndex=Var[1];DSPI.Item[Var[0]].BaudIndex=9;Var[2]=Var[1];Var[1]++;
    SPI_SetClock(Var[2],1);
    SPI_CR1(Var[2])=(DSPI.Item[Var[0]].Setup.EN ? 0X0344|((DSPI.Item[Var[0]].Setup.BR)<<3)|(DSPI.Item[Var[0]].Setup.BIDMode ? 0xC000:0x0000)|DSPI.Item[Var[0]].Setup.CPHA|(DSPI.Item[Var[0]].Setup.CPOL<<1):0x0000);
    SPI_CR2(Var[2])=(DSPI.Item[Var[0]].Setup.EN ? 0X00C0:0x0000);//RXNEIE=TXEIE=1
    SPI_SR(Var[2])=(DSPI.Item[Var[0]].Setup.EN ? 0X0002:0x0000);//TXE=1
    SPI_CRCPR(Var[2])=(DSPI.Item[Var[0]].Setup.EN ? 0X0007:0x0000);
    SPI_RXCRCR(Var[2])=0X0000;
    SPI_TXCRCR(Var[2])=0X0000;
    SPI_I2SCFGR(Var[2])=0X0000;
    SPI_I2SPR(Var[2])=0X0000;
	  if(Var[2]==0)
	  {if(DSPI.Item[Var[0]].Setup.ALF)GPIO[1].CRL=(GPIO[1].CRL&0xFF0F0FFF)|(DSPI.Item[Var[0]].Setup.EN ? 0x00B0B000:0x00303000);else GPIO[0].CRL=(GPIO[0].CRL&0x0F0FFFFF)|(DSPI.Item[Var[0]].Setup.EN ? 0xB0B00000:0x30300000);}
	  else if(Var[2]==1)
	  {GPIO[1].CRH=(GPIO[1].CRH&0x0F0FFFFF)|(DSPI.Item[Var[0]].Setup.EN ? 0xB0B00000:0x30300000);}
	  else if(Var[2]==2)
	  {if(DSPI.Item[Var[0]].Setup.ALF)GPIO[2].CRH=(GPIO[2].CRH&0xFFF0F0FF)|(DSPI.Item[Var[0]].Setup.EN ? 0x000B0B00:0x00030300);else GPIO[1].CRL=(GPIO[1].CRL&0xFF0F0FFF)|(DSPI.Item[Var[0]].Setup.EN ? 0x00B0B000:0x00303000);}
	  if(!DSPI.Item[Var[0]].Setup.EN)SPI_SetClock(Var[2],0);
  }
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_I2S(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_I2C(void)
{
	//I2C2
	RCC.APB1ENR&=0xFF9FFFFF;//I2C1EN=I2C2EN=0
#if SDK_I2C_COUNT
  DI2C.Count=SDK_I2C_COUNT;Var[1]=0x00;
  for(Var[0]=0;Var[0]<SDK_I2C_COUNT;Var[0]++)
  {	
    while((SDK_I2C_ON & (1<<Var[1]))==0x00 && Var[1]<SDK_I2C_MAXCOUNT)Var[1]++;
    DI2C.Item[Var[0]].HWIndex=Var[1];DI2C.Item[Var[0]].BaudIndex=9;Var[2]=Var[1];Var[1]++;    
    I2C_SetClock(Var[2],1);
	  I2C[Var[2]].CR1_BIT.SWRST =1;I2C[Var[2]].CR1_BIT.SWRST =0;
	  I2C_CR1(Var[2])=0X00000409;//PE=0,ACK=1
    I2C_CR2(Var[2])=0X00000724;//ITBUFEN=ITEVTEN=ITERREN=1,FREQ=36M	
    I2C_OAR1(Var[2])=0X00004000;//ACKAddress=1
    I2C_OAR2(Var[2])=0X00000000;
    I2C_SR1(Var[2])=0X00000000;
    I2C_SR2(Var[2])=0X00000000;
    I2C_CCR(Var[2])=0X00000168;//32M/360/2=50K clock
    I2C_TRISE(Var[2])=0X00000025;//sm mode: 36M/1M+1=37
    SETIRQ(IRQN_I2C1_EV+2*Var[2] ,0,0);
    SETIRQ(IRQN_I2C1_ER+2*Var[2] ,0,0);
  }
#endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_SDIO(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_UART(void)
{
  RCC.APB2ENR_BIT.UART1EN=0;RCC.APB1ENR&=0xFFE1FFFF;
#if SDK_UART_COUNT
  DUART.Count=SDK_UART_COUNT;DUART.Index=SDK_UART_Index;
  for(Var[0]=0;Var[0]<SDK_UART_MAXCOUNT;Var[0]++)DUART.COMIndex[Var[0]]=SDK_COM_COUNT;Var[1]=0x00;
  for(Var[0]=0;Var[0]<SDK_UART_COUNT;Var[0]++)
  {
    while((SDK_UART_ON & (1<<Var[1]))==0x00 && Var[1]<SDK_UART_MAXCOUNT)Var[1]++;
    DUART.Item[Var[0]].HWIndex=Var[1];if(Var[1]<SDK_UART_MAXCOUNT)DUART.COMIndex[Var[1]]=SDK_UART_Index+Var[0];Var[1]++;
    DUART.Item[Var[0]].BaudIndex=(Var[0]==1 ? 3:9);
  }
  
	for(Var[0]=0;Var[0]<SDK_UART_COUNT;Var[0]++)
	{
    Var[1]=DUART.Item[Var[0]].HWIndex;
    Uart_SetClock(Var[1],1);
    Uart_SetBaud(Var[1]);
		UART_CR1(Var[1])=0x0000002C;//RE=TE=RXNEIE=1
		UART_CR2(Var[1])=0x00000000;
		UART_CR3(Var[1])=0x00000000;
		UART_GTPR(Var[1])=0x00000000;
		UART_SR(Var[1])=0x00000000;
    Uart_SetIRQ(Var[1]);
		(*UART[Var[1]]).CR1_BIT.UE=1;
	}
#endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_CAN(void)
{
	//CAN1
  RCC.APB1ENR_BIT.CAN1EN=0;RCC.APB1ENR_BIT.CAN2EN=0;
#if SDK_CAN_COUNT
  DCAN.Count=SDK_CAN_COUNT;DCAN.Index=SDK_CAN_Index;
  for(Var[0]=0;Var[0]<SDK_CAN_MAXCOUNT;Var[0]++)DCAN.COMIndex[Var[0]]=SDK_COM_COUNT; Var[1]=0x00;
  for(Var[0]=0;Var[0]<SDK_CAN_COUNT;Var[0]++)
  {
    DCAN.Item[Var[0]].SAD.VAL=0x12345678;DCAN.Item[Var[0]].TAD.VAL=0x12345678; CAN_RTR(Var[0])=0;CAN_IDE(Var[0])=1;
    while((SDK_CAN_ON & (1<<Var[1]))==0x00 && Var[1]<2)Var[1]++; 
    DCAN.Item[Var[0]].HWIndex=Var[1];DCAN.Item[Var[0]].BaudIndex=9;if(Var[1]<SDK_CAN_MAXCOUNT)DCAN.COMIndex[Var[1]]=SDK_CAN_Index+Var[0];Var[1]++;
  }
    
  for(Var[0]=0;Var[0]<SDK_CAN_COUNT;Var[0]++)
  {
    Var[2]=DCAN.Item[Var[0]].HWIndex;
    CAN_SetClock(Var[2],1);
    DCOM.Item[SDK_CAN_Index+Var[0]].RF.Index=0x0000;DCOM.Item[SDK_CAN_Index+Var[0]].RF.Count=0x0000;
    DCOM.Item[SDK_CAN_Index+Var[0]].TF.Index=0x0000;DCOM.Item[SDK_CAN_Index+Var[0]].TF.Count=0x0000;
    
    CAN_MCR(Var[2])=0x00010045;//INRQ=TXFP=ABOM=DBF=1
    Var[1]=0x00;while(CAN[Var[2]].MSR_BIT.INAK==0 && Var[1]<0x80)Var[1]++;//wait INAK
    if(CAN[Var[2]].MSR_BIT.INAK==0)return;//Fail
    CAN_TSR(Var[2])=0x1C000000;//TME=7
    CAN_RFR(Var[2],0)=0x00000020;//RFOM0=1
    CAN_RFR(Var[2],1)=0x00000020;//RFOM1=1
    CAN_IER(Var[2])=0x00000013;//TMEIE=FMPIE0=FMPIE1=1
    CAN_ESR(Var[2])=0x00000000;
    CAN_BTR(Var[2])=0x00320011|(((SDK_CAN_LoopBack>>Var[2])&1)<<30) ;//TS2=3(4TQ),TS1=2(3TQ),BRP=8[TQ=(BRP+1)*TPCLK],36M/(3+3+2)/(17+1)=250k
    CAN[Var[2]].MCR_BIT.INRQ=0;
    Var[1]=0x00;while(CAN[Var[2]].MSR_BIT.INAK==1 && Var[1]<0x80)Var[1]++;//wait INAK
    if(CAN[Var[2]].MSR_BIT.INAK==1)continue;//Fail
    for(Var[1]=0;Var[1]<3;Var[1]++) CAN_TIR(Var[2],Var[1])=0x00000000;
    for(Var[1]=0;Var[1]<2;Var[1]++) CAN_RIR(Var[2],Var[1])=0x00000000;
    CAN_FMR(Var[2])=0x2A1C0E01;//CAN2SB=0x0e,FINIT=1;
    CAN_FM1R(Var[2])=0x00000000;//Filter 0=Filter 1=0(Mask Mode)
    CAN_FS1R(Var[2])=0x00000003;//Filter scale:0=dual 16 bits, 1=32 bits
    CAN_FFA1R(Var[2])=0x00000002;//Filter 0=0(FIFO0),Filter 1=1(FIFO1)
    CAN_FA1R(Var[2])=0x00000003;//Filter active: 1=active
    CAN_FR1(Var[2],0)=CAN_GetID(Var[2],1,0);
    CAN_FR2(Var[2],0)=0xFFFFFFF0;
    CAN_FR1(Var[2],1)=CAN_GetID(Var[2],1,1);
    CAN_FR2(Var[2],1)=0xFFFC0000;
    CAN[Var[2]].FMR_BIT.FINIT=0;
    
    SETIRQ(IRQN_USB1HP_CAN1TX+44*Var[2],0,0);
    SETIRQ(IRQN_USB1LP_CAN1RX0+44*Var[2],0,0);
    SETIRQ(IRQN_CAN1RX1+44*Var[2],0,0);
  }
#endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_ETH(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_USB(void)
{
  RCC.APB1ENR_BIT.USBEN=(SDK_USB_COUNT ? 1:0);
#if SDK_USB_COUNT
  DUSB.Count=SDK_USB_COUNT;DUSB.Index=SDK_USB_Index;
	DUSB.RXADDR[0]=(UINT32)&USB.RXBUF0;DUSB.RXADDR[1]=(UINT32)&USB.RXBUF1;DUSB.RXADDR[2]=(UINT32)&USB.RXBUF2;
	DUSB.TXADDR[0]=(UINT32)&USB.TXBUF0;DUSB.TXADDR[1]=(UINT32)&USB.TXBUF1;DUSB.TXADDR[2]=(UINT32)&USB.TXBUF2;
	DUSB.EPSIZE[0]=USB_EP0_Size;DUSB.EPSIZE[1]=USB_EP1_Size;DUSB.EPSIZE[2]=USB_EP2_Size;
	DUSB.DEVState=USB_STATE_UNCONNECTED;DUSB.RXSTAT=0x00;DUSB.TXSTAT=0x00;DUSB.State.VAL=0x00;
	DCOM.Item[SDK_USB_Index].RF.Item=DUSB.RBUF[0];DCOM.Item[SDK_USB_Index].RF.Size=SIZE_USB_RBUF;DCOM.Item[SDK_USB_Index].RF.Index=0x0000;DCOM.Item[SDK_USB_Index].RF.Count=0x0000;
	DCOM.Item[SDK_USB_Index].TF.Item=DUSB.TBUF[0];DCOM.Item[SDK_USB_Index].TF.Size=SIZE_USB_TBUF;DCOM.Item[SDK_USB_Index].TF.Index=0x0000;DCOM.Item[SDK_USB_Index].TF.Count=0x0000;
	CustomHID_Init();
	SETIRQ(IRQN_USB1LP_CAN1RX0,2,0);
	SETIRQ(IRQN_USBWakeUp,1,0);
#endif
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_USBFS(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_MEM(UINT8 IsAfter)
{
  DAPP.INTF.Init=APP_Init;
  if(!IsAfter)
  {
	  for(Var[0]=0;Var[0]<3;Var[0]++){ADC[Var[0]]=(Type_ADC *)BASE_ADC[Var[0]];SPI[Var[0]]=(Type_SPI *)BASE_SPI[Var[0]];}
    for(Var[0]=0;Var[0]<17;Var[0]++)TIM[Var[0]]=(Type_TIM *)BASE_TIM[Var[0]];
	  for(Var[0]=0;Var[0]<5;Var[0]++)UART[Var[0]]=(Type_UART *)BASE_UART[Var[0]];

    for(Var[0]=0;Var[0]<4;Var[0]++){TMRCount[Var[0]]=DAPP.V.ST[Var[0]].VAL=0x00000000;}
    DDEV.Item[0].RunCount=DDEV.Item[0].RunTime=DDEV.Item[0].RunST.VAL=SystemST.VAL=0x000000000;
    DAPP.V.PSP = CPUGet_PSP();DAPP.V.MSP = CPUGet_MSP()+0x10;CPU_On=(DES.FLASHSIZE>0);
  }
  else
  {
    DDEV.Item[0].BAT.V=DDEV.Item[0].BAT.P=DDEV.Item[0].T.V=SysTimeCount=MicroTimeCount=0x00000000;
    Byte8ToDT((UINT8 *)Device_BaseDT,&DAPP.BaseDT,0);Byte8ToDT((UINT8 *)Device_MadeDT,&DAPP.MadeDT,0);StrCopy((UINT8*)&DAPP.DT,(UINT8 *)&DAPP.MadeDT,8);
    for(Var[0]=0;Var[0]<8;Var[0]++) *((UINT8 *)(&DDEV.Item[0].HS.ST)+Var[0])=*((UINT8 *)(&Device_HS)+Var[0]);
    DKEY.State.VAL=DKEY.Init_TimeCount=DLED.State.VAL=DADC.State.VAL=DDAC.State.VAL=0x00;
    #if SDK_COM_COUNT
    DDEV.Item[0].NSN.Size=SIZE_DC_NSN; DDEV.Item[0].NSN.Count=Device_NSN[0];LimitValue(DDEV.Item[0].NSN.Count,1,SIZE_DC_NSN);
    DDEV.Item[0].NSN.Item=DDEV.Item[0].NSNBUF; StrCopy(DDEV.Item[0].NSN.Item,(UINT8 *)((UINT32)&Device_NSN[1]),DDEV.Item[0].NSN.Count);
    DAPP.PF.Item=DAPP.PBUF;DAPP.PF.Size=SIZE_DC_PBUF; DAPP.TF.Item=DAPP.TBUF;DAPP.TF.Size=SIZE_DC_TBUF; DAPP.IRQTF.Item=DAPP.IRQTBUF;DAPP.IRQTF.Size =SIZE_DC_TBUF;
    DCOM.State.VAL=DCOM.Index=0x0000;DCOM.Count=SDK_COM_COUNT;
    for(Var[0]=0;Var[0]<SDK_COM_COUNT;Var[0]++)
    {
      DCOM.Item[Var[0]].State.VAL=0x0000;
      DCOM.Item[Var[0]].RF.Index=DCOM.Item[Var[0]].RF.Count=0x0000;
      DCOM.Item[Var[0]].TF.Index=DCOM.Item[Var[0]].TF.Count=0x0000;
      DCOM.Item[Var[0]].TF.MMT.Index=DCOM.Item[Var[0]].TF.MMT.Count=0x0000;
      DCOM.Item[Var[0]].BUS.Index=DCOM.Item[Var[0]].BUS.Count=0x0000;
      DCOM.Item[Var[0]].TF.TXI.TimeOut_Count=0x0000;
      DCOM.Item[Var[0]].PRTC.Index=DCOM.Item[Var[0]].PRTC.Count=0x0000;
    }
    
    #if SDK_UART_COUNT
    for(Var[0]=0;Var[0]<SDK_UART_COUNT;Var[0]++)  
    {
      DCOM.Item[SDK_UART_Index+Var[0]].RF.Item=(UINT8 *)&DUART.RBUF[Var[0]];DCOM.Item[SDK_UART_Index+Var[0]].RF.Size=SIZE_UART_RBUF;
      DCOM.Item[SDK_UART_Index+Var[0]].TF.Item=(UINT8 *)&DUART.TBUF[Var[0]];DCOM.Item[SDK_UART_Index+Var[0]].TF.Size=SIZE_UART_TBUF;
      DCOM.Item[SDK_UART_Index+Var[0]].PRTC.Count=(Var[0]==0x00 ? PRTC_UART1[0]:PRTC_UART2[0]);
      DCOM.Item[SDK_UART_Index+Var[0]].PRTC.Item=(UINT16 *)(Var[0]==0x00 ? (UINT32)&PRTC_UART1[1]:(UINT32)&PRTC_UART2[1]);
      DCOM.Item[SDK_UART_Index+Var[0]].PRTC.Index=0;COM_PRTC_Init(SDK_UART_Index+Var[0]);
    }
    #endif
    #if SDK_CAN_COUNT
    for(Var[0]=0;Var[0]<SDK_CAN_COUNT;Var[0]++)  
    {
      DCOM.Item[SDK_CAN_Index+Var[0]].RF.Item=(UINT8 *)&DCAN.RBUF[Var[0]];DCOM.Item[SDK_CAN_Index+Var[0]].RF.Size=SIZE_CAN_RBUF;
      DCOM.Item[SDK_CAN_Index+Var[0]].TF.Item=(UINT8 *)&DCAN.TBUF[Var[0]];DCOM.Item[SDK_CAN_Index+Var[0]].TF.Size=SIZE_CAN_TBUF;
      COM_BUS_On(SDK_CAN_Index+Var[0])=1;
    }
    #endif
    #if SDK_USB_COUNT
    for(Var[0]=0;Var[0]<SDK_USB_COUNT;Var[0]++)  
    {
      DCOM.Item[SDK_USB_Index+Var[0]].RF.Item=(UINT8 *)&DUSB.RBUF[Var[0]];DCOM.Item[SDK_USB_Index+Var[0]].RF.Size=SIZE_USB_RBUF;
      DCOM.Item[SDK_USB_Index+Var[0]].TF.Item=(UINT8 *)&DUSB.TBUF[Var[0]];DCOM.Item[SDK_USB_Index+Var[0]].TF.Size=SIZE_USB_TBUF;
      COM_BUSM_On(SDK_USB_Index+Var[0])=1;
    }
    #endif
    #endif
    if(!SYS_Dentify(Dentify)){while(1);}
  }
  DAPP.INTF.Init(IsAfter);
  DC_Inited=IsAfter;
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_IEIP(void)
{
  EIRQ();	EFIRQ();//WDT_Enable(1);
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_DisableAll(void)
{
  DIRQ();DFIRQ(); RCC_AHBENR=RCC_APB2ENR=RCC_APB1ENR=0x00000000;
}
//-----------------------------------------------------------------------------------------------------------------------------
void Init_JumpAPP(void)
{
  //Init_DisableAll(); M3SYS.VTOR=BASE_APP;CPUSet_PSP(DAPP.V.PSP);CPUSet_MSP(DAPP.V.MSP); UGMain();
}  
//==============================================================================================================================
//interrupt
void NMI_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void HardFault_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void MemManage_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void BusFault_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void UsageFault_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RSVD_N9_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RSVD_N8_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RSVD_N7_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RSVD_N6_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void SVC_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void DebugMon_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RSVD_N3_Handler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void PendSV_Handler(void)
{while(1);}	
//------------------------------------------------------------------------------------------------------------------------------
void SysTick_Handler(void)//1ms
{
	M3SYS.STCTRL_BIT.COUNTFLAG=0;	WDT_CLR();
  if(DAPP.INTF.TMR)DAPP.INTF.TMR(0);SysTimeCount++;MicroTimeCount=0x00; DAPP.DT.Second_BIT.M=(DAPP.DT.Second_BIT.M+1)%1000;
  TMRCount[0]++;	if(TMRCount[0]>=5){TMRCount[0]=0x00;TMR_Event_On=1;}
}
//==============================================================================================================================
void WWDG_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void PVD_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void TAMPER_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RTC_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void FLASH_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void RCC_IRQHandler(void)
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
	if(EXTI.IMR_BIT.B0 && EXTI.PR_BIT.B0)	EXTI_IRQ_Control(0);
}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI1_IRQHandler(void)
{
	if(EXTI.IMR_BIT.B1 && EXTI.PR_BIT.B1)	EXTI_IRQ_Control(1);
}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI2_IRQHandler(void)
{
	if(EXTI.IMR_BIT.B2 && EXTI.PR_BIT.B2)	EXTI_IRQ_Control(2);
}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI3_IRQHandler(void)
{
	if(EXTI.IMR_BIT.B3 && EXTI.PR_BIT.B3)	EXTI_IRQ_Control(3);
}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI4_IRQHandler(void)
{
	if(EXTI.IMR_BIT.B4 && EXTI.PR_BIT.B4)	EXTI_IRQ_Control(4);
}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel1_IRQHandler(void)
{DMA_IRQ_Control(0,0);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel2_IRQHandler(void)
{DMA_IRQ_Control(0,1);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel3_IRQHandler(void)
{DMA_IRQ_Control(0,2);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel4_IRQHandler(void)
{DMA_IRQ_Control(0,3);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel5_IRQHandler(void)
{DMA_IRQ_Control(0,4);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel6_IRQHandler(void)
{DMA_IRQ_Control(0,5);}
//------------------------------------------------------------------------------------------------------------------------------
void DMA1_Channel7_IRQHandler(void)
{DMA_IRQ_Control(0,6);}
//------------------------------------------------------------------------------------------------------------------------------
void ADC12_IRQHandler(void)// ADC12
{
	if((*ADC[0]).SR_BIT.EOC){(*ADC[0]).SR&=0xFFF8;ADC_IRQ_Control(0);} //AWD=EOC=JEOC=0
	if((*ADC[1]).SR_BIT.EOC){(*ADC[1]).SR&=0xFFF8;ADC_IRQ_Control(1);} //AWD=EOC=JEOC=0
}
//------------------------------------------------------------------------------------------------------------------------------
void USB1HP_CAN1TX_IRQHandler(void)//USB1 High Priority or CAN1 TX
{
  #if SDK_CAN_COUNT && (SDK_CAN_ON & 1)
	CAN_Write(0);
  #elif SDK_USB_COUNT && (SDK_USB_ON & 1)
  //USB_Control(0);
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void USB1LP_CAN1RX0_IRQHandler(void)//USB1 Low  Priority or CAN1 RX0
{
  #if SDK_CAN_COUNT && (SDK_CAN_ON & 1)
	CAN_Read(0,0);
  #elif SDK_USB_COUNT && (SDK_USB_ON & 1)
  USB_Control(0);
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN1RX1_IRQHandler(void)//CAN1 RX1
{
  #if SDK_CAN_COUNT && (SDK_CAN_ON & 1)
	CAN_Read(0,1);
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN1SCE_IRQHandler(void)//CAN1 SCE
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI9_5_IRQHandler(void)//EXTI Line 9..5
{
  if(EXTI.IMR_BIT.B5 && EXTI.PR_BIT.B5)	EXTI_IRQ_Control(5);
  if(EXTI.IMR_BIT.B6 && EXTI.PR_BIT.B6)	EXTI_IRQ_Control(6);
  if(EXTI.IMR_BIT.B7 && EXTI.PR_BIT.B7)	EXTI_IRQ_Control(7);
  if(EXTI.IMR_BIT.B8 && EXTI.PR_BIT.B8)	EXTI_IRQ_Control(8);
  if(EXTI.IMR_BIT.B9 && EXTI.PR_BIT.B9)	EXTI_IRQ_Control(9);
}
//------------------------------------------------------------------------------------------------------------------------------
void TIM1_BRK_IRQHandler(void)//TIM1 Break
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM1_UP_IRQHandler(void)//TIM1 Update
{TIM1.SR_BIT.UIF=0;if(DAPP.INTF.IRQ_TIM)DAPP.INTF.IRQ_TIM(0);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM1_TRGCOM_IRQHandler(void)//TIM1 Trigger and Commutation
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM1_CC_IRQHandler(void)//TIM1 Capture Compare
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler(void)//TIM2,100us
{TIM2.SR_BIT.UIF=0;if(DAPP.INTF.IRQ_TIM)DAPP.INTF.IRQ_TIM(1);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM3_IRQHandler(void)//TIM3
{TIM3.SR_BIT.UIF=0;if(DAPP.INTF.IRQ_TIM)DAPP.INTF.IRQ_TIM(2);}
//------------------------------------------------------------------------------------------------------------------------------
void TIM4_IRQHandler(void)//TIM4
{TIM4.SR_BIT.UIF=0;if(DAPP.INTF.IRQ_TIM)DAPP.INTF.IRQ_TIM(3);}
//------------------------------------------------------------------------------------------------------------------------------
void I2C1_EV_IRQHandler(void)//I2C1 Event
{I2C_Event_Control(0);}
//------------------------------------------------------------------------------------------------------------------------------
void I2C1_ER_IRQHandler(void)//I2C1 Error
{I2C_Error_Control(0);}
//------------------------------------------------------------------------------------------------------------------------------
void I2C2_EV_IRQHandler(void)//I2C2 Event
{I2C_Event_Control(1);}
//------------------------------------------------------------------------------------------------------------------------------
void I2C2_ER_IRQHandler(void)//I2C2 Error
{I2C_Error_Control(1);}
//------------------------------------------------------------------------------------------------------------------------------
void SPI1_IRQHandler(void)//SPI1
{SPI_IRQ_Control(0);}
//------------------------------------------------------------------------------------------------------------------------------
void SPI2_IRQHandler(void)//SPI2
{SPI_IRQ_Control(1);}
//------------------------------------------------------------------------------------------------------------------------------
void USART1_IRQHandler(void)//USART1
{Uart_IRQ_Control(0);}
//------------------------------------------------------------------------------------------------------------------------------
void USART2_IRQHandler(void)//USART2
{Uart_IRQ_Control(1);}
//------------------------------------------------------------------------------------------------------------------------------
void USART3_IRQHandler(void)//USART3
{Uart_IRQ_Control(2);}
//------------------------------------------------------------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)//EXTI Line 15..10
{
	if(EXTI.IMR_BIT.B10 && EXTI.PR_BIT.B10)	EXTI_IRQ_Control(10);
	if(EXTI.IMR_BIT.B11 && EXTI.PR_BIT.B11)	EXTI_IRQ_Control(11);
	if(EXTI.IMR_BIT.B12 && EXTI.PR_BIT.B12)	EXTI_IRQ_Control(12);
	if(EXTI.IMR_BIT.B13 && EXTI.PR_BIT.B13)	EXTI_IRQ_Control(13);
	if(EXTI.IMR_BIT.B14 && EXTI.PR_BIT.B14)	EXTI_IRQ_Control(14);
	if(EXTI.IMR_BIT.B15 && EXTI.PR_BIT.B15)	EXTI_IRQ_Control(15);
}
//------------------------------------------------------------------------------------------------------------------------------
void RTCAlarm_IRQHandler(void)//RTC Alarm through EXTI Line
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void USBWakeUp_IRQHandler(void)//USB Wakeup from suspend
{while(1);}
//------------------------------------------------------------------------------------------------------------------------------
void USB2HP_IRQHandler(void)
{
  #if SDK_USB_ON & 2
  //USB_Control(1);
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void USB2LP_IRQHandler(void)
{
  #if SDK_USB_ON & 2
  //USB_Control(1);
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void assert_failed(UINT8* file, UINT32 line)
{
  //printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  while(1);
}
//==============================================================================================================================
void ADC_SetClock(UINT8 Index)
{
  if(Index<=1) RCC.APB2ENR_BIT.ADC1EN=1; else RCC.APB2ENR_BIT.ADC3EN=1;
}
//------------------------------------------------------------------------------------------------------------------------------
void ADC_IRQ_Control(UINT8 Index)
{
  (*ADC[Index]).SR&=0xFFFFFFF9;//EOC=JEOC=0
  if(DAPP.INTF.ADC_Control)DAPP.INTF.ADC_Control(Index);
}
//==============================================================================================================================
void DMA_IRQ_Control(UINT8 Index,UINT8 CHIndex)
{
	DMA[Index].IFCR|=(0x07<<(CHIndex*4));//Clear GIF,TCIF,HTIF in CHIndex
  if(DAPP.INTF.DMA_Control)DAPP.INTF.DMA_Control(Index,CHIndex);
}
//==============================================================================================================================
void EXTI_IRQ_Control(UINT8 Index)//Index:Line Index=0_15
{
  if(DAPP.INTF.EXTI_Control)DAPP.INTF.EXTI_Control(Index);
	EXTI.PR=(1<<Index);
}
//==============================================================================================================================
void I2C_Error_Control(UINT16 Index)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void I2C_Event_Control(UINT16 Index)
{
}
//==============================================================================================================================
void SPI_IRQ_Control(UINT8 Index)
{
}
//==============================================================================================================================
void Uart_IRQ_Control(UINT16 Index)
{
#if SDK_UART_COUNT  
  if((*UART[Index]).SR_BIT.ORE){Uart_Reset(Index);return;}
	if((*UART[Index]).SR_BIT.RXNE)Uart_Read(Index);
  if((*UART[Index]).SR_BIT.TC)Uart_Write(Index);
#endif  
}
//------------------------------------------------------------------------------------------------------------------------------
#if SDK_UART_COUNT
//------------------------------------------------------------------------------------------------------------------------------
void Uart_Reset(UINT16 Index)
{
  Uart_SetClock(Index,0);NOP();NOP();NOP();Uart_SetClock(Index,1);
  UART_CR1(Index)=0x0000002C; UART_SR(Index)=0x00000000;
  Uart_EndSendItem(Index);if(DCOM.Item[DUART.COMIndex[Index]].TF.Count)Uart_StartSendItem(Index);
}
//------------------------------------------------------------------------------------------------------------------------------
void Uart_Read(UINT16 Index)
{
  UINT8 COMIndex;
  COMIndex=DUART.COMIndex[Index];(*UART[Index]).SR_BIT.RXNE=0; IRQINT[0]=(*UART[Index]).DR; COM_Bit9(COMIndex)=(IRQINT[0]&0x100 ? 1:0);
  if(DAPP.INTF.COM_ReadPacket)DAPP.INTF.COM_ReadPacket(COMIndex,(UINT8 *)IRQINT,1);
}
//-----------------------------------------------------------------------------------------------------------------------------
void Uart_Write(UINT16 Index)
{
  UINT8 COMIndex;
  COMIndex=DUART.COMIndex[Index]; (*UART[Index]).SR_BIT.TC=0; COM_TXChar_On(COMIndex)=0;
  if(DCOM.Item[COMIndex].TF.Count==0x00||!COM_TX_On(COMIndex)){COM_TX_On(COMIndex)=0;Uart_EndSendItem(Index);return;}
  Uart_SendBUF(Index);
}
//-----------------------------------------------------------------------------------------------------------------------------
void Uart_SendBUF(UINT16 Index)
{
  UINT8 F0,F1; UINT16 COMIndex,i,j;struct Data_COM_TXFrame *TF;
  COMIndex=DUART.COMIndex[Index]; F0=F1=0;TF=&DCOM.Item[COMIndex].TF;
  j=((*TF).Index+(*TF).Size-(*TF).Count) % (*TF).Size;

  if(!COM_TXItem_On(COMIndex))
  {if((*TF).MMT.Item[0].Time)return; COM_TXItem_On(COMIndex)=1;F1=1;}
  else if((*TF).TXI.Index<(*TF).TXI.Len)
  {F0=1;}
  else
  {
    if((*TF).MMT.Count>1 && j==(*TF).MMT.Item[1].Pos)
    {
      for(i=0;i<(*TF).MMT.Count-1;i++)(*TF).MMT.Item[i]=(*TF).MMT.Item[i+1];
      if((*TF).MMT.Item[0].Time){COM_EndSend(COMIndex);return;}
    }
    F1=1;
  }
  if(F1)
  {
    (*TF).TXI.Len=(*TF).Item[j];j=(j+1)% (*TF).Size; 
    (*TF).TXI.Len|=(UINT16)(*TF).Item[j]<<8;j=(j+1)% (*TF).Size;
    (*TF).TXI.Index=0x0000;(*TF).Count-=2; F0=1;
  }
  if(F0)
  {
    COM_TXChar_On(COMIndex)=1;(*TF).TXI.Index+=1;(*TF).Count-=1;
    if((*TF).Count==0x0000)(*TF).MMT.Count=0x00; 
    (*UART[Index]).DR=(*TF).Item[j];
  }
}
//-----------------------------------------------------------------------------------------------------------------------------
void Uart_StartSendItem(UINT16 Index)
{
  if(!COM_TXItem_On(DUART.COMIndex[Index])){(*UART[Index]).SR_BIT.TC=0;(*UART[Index]).CR1_BIT.TCIE=1;Uart_SendBUF(Index);}
}
//-----------------------------------------------------------------------------------------------------------------------------
void Uart_EndSendItem(UINT16 Index)
{
	COM_TXItem_On(DUART.COMIndex[Index])=0;(*UART[Index]).CR1_BIT.TCIE=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void Uart_WaitSend(UINT16 Index)//等待缓冲发送完毕(中断外调用)
{
  UINT8 COMIndex;
  COMIndex=DUART.COMIndex[Index]; while(DCOM.Item[COMIndex].TF.Count||COM_TXChar_On(COMIndex));
}
//------------------------------------------------------------------------------------------------------------------------------
void Uart_SetClock(UINT16 Index,UINT8 EN)//CLK=72M(Uart1) or 36M(Uart2_5)
{
  UINT32 i;
  if(Index==0)
  {RCC.APB2ENR_BIT.UART1EN=EN;}
  else if(Index<5)
  {i=(1<<(16+Index));if(EN)RCC.APB1ENR|=i;else RCC.APB1ENR&=~i;}
  else
  {i=(1<<(12+Index));if(EN)RCC.APB2ENR|=i;else RCC.APB2ENR&=~i;}
}
//------------------------------------------------------------------------------------------------------------------------------
void Uart_SetBaud(UINT16 Index)//CLK=72M(Uart1) or 36M(Uart2_5), BRR= CLK/Baud
{
	(*UART[Index]).BRR=(Index==0 ? CLK_APB2:CLK_APB1)/UART_BAUD[DUART.Item[DUART.COMIndex[Index]-SDK_UART_Index].BaudIndex];
}
//------------------------------------------------------------------------------------------------------------------------------
void Uart_SetIRQ(UINT16 Index)
{
  if(Index<3){SETIRQ(IRQN_USART1+Index,0,0);return;}
#if IsDensity(XL)
  if(Index<5){SETIRQ(IRQN_UART4+Index-3,0,0);return;}
#endif  
}
//------------------------------------------------------------------------------------------------------------------------------
#endif
//==============================================================================================================================
#if SDK_CAN_COUNT
//------------------------------------------------------------------------------------------------------------------------------
void CAN_Read(UINT16 Index,UINT8 FIFOIndex)
{
	IRQLNG[0]=CAN[Index].RXM[FIFOIndex].RIR>>(CAN[Index].RXM[FIFOIndex].RIR_BIT.IDE ? 3:21);//ID
	IRQTempFlag0=CAN[Index].RXM[FIFOIndex].RIR_BIT.RTR;//RTR
	IRQVar[0]=CAN[Index].RXM[FIFOIndex].RDTR_BIT.DLC%9;//DLC(0-8)
	IRQVar[1]=CAN[Index].RXM[FIFOIndex].RDTR_BIT.FMI;//FMI
  
	CAN[Index].RFR_BIT[FIFOIndex].FMP=0x00; CAN[Index].RFR_BIT[FIFOIndex].RFOM=1;
  DAPP.INTF.COM_ReadPacket(DCAN.COMIndex[Index],(UINT8 *)CAN[Index].RXM[FIFOIndex].RBUF.Item,IRQVar[0]);
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN_Write(UINT16 Index)
{
  UINT8 COMIndex;
  COMIndex=DCAN.COMIndex[Index];
	CAN[Index].TSR_BIT.TME=0;	COM_TXChar_On(COMIndex)=0;
	if(DCOM.Item[COMIndex].TF.Count==0x00||!COM_TX_On(COMIndex)){COM_TX_On(COMIndex)=0;CAN_EndSendItem(Index);return;}
	CAN_SendBUF(Index);
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN_SendBUF(UINT16 Index)
{
  UINT8 F0,F1,FIFOIndex;UINT16 COMIndex,i,j,k;struct Data_COM_TXFrame *TF;
  if(CAN[Index].TSR_BIT.TME==0)return;COMIndex=DCAN.COMIndex[Index];TF=&DCOM.Item[COMIndex].TF;
	F0=F1=0;FIFOIndex=CAN[Index].TSR_BIT.CODE%3; j=((*TF).Index+SIZE_CAN_TBUF-(*TF).Count)%(*TF).Size;
  
  if(!COM_TXItem_On(COMIndex))
  {if((*TF).MMT.Item[0].Time)return; COM_TXItem_On(COMIndex)=1;F1=1;}
  else if((*TF).TXI.Index<(*TF).TXI.Len)
  {F0=1;}
  else
  {
    if((*TF).MMT.Count>1 && j==(*TF).MMT.Item[1].Pos)
    {
      for(i=0;i<(*TF).MMT.Count-1;i++)(*TF).MMT.Item[i]=(*TF).MMT.Item[i+1];
      if((*TF).MMT.Item[0].Time){COM_EndSend(COMIndex);return;}
    }
    F1=1;
  }
  if(F1)
  {
    (*TF).TXI.Len=(*TF).Item[j];j=(j+1)%SIZE_CAN_TBUF; 
    (*TF).TXI.Len|=(UINT16)(*TF).Item[j]<<8;j=(j+1)%SIZE_UART_TBUF;
    (*TF).TXI.Index=0x0000;(*TF).Count-=2; F0=1;
  }
  if(F0)
  {
    COM_TXChar_On(COMIndex)=1; k=(*TF).TXI.Len-(*TF).TXI.Index;if(k>8)k=8;
    (*TF).TXI.Index+=k;(*TF).Count-=k;
    if((*TF).Count==0x0000)(*TF).MMT.Count=0x00;
    
	  CAN[Index].TXM[FIFOIndex].TIR=CAN_GetID(Index,0,0);
	  CAN[Index].TXM[FIFOIndex].TDTR_BIT.DLC=k;
	  CAN[Index].TXM[FIFOIndex].TBUF.LH.DLR=0x00000000;
	  CAN[Index].TXM[FIFOIndex].TBUF.LH.DHR=0x00000000;
	  for(i=0;i<k;i++){CAN[Index].TXM[FIFOIndex].TBUF.Item[i]=(*TF).Item[j];j=(j+1)%SIZE_CAN_TBUF;}
	  CAN[Index].TXM[FIFOIndex].TIR_BIT.TXRQ=1;
  }  
}
//-----------------------------------------------------------------------------------------------------------------------------
void CAN_StartSendItem(UINT16 Index)
{
  if(!COM_TXItem_On(DCAN.COMIndex[Index]))CAN_SendBUF(Index);
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN_EndSendItem(UINT16 Index)
{
	COM_TXItem_On(DCAN.COMIndex[Index])=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN_WaitSend(UINT16 Index)
{
  while(DCOM.Item[DCAN.COMIndex[Index]].TF.Count||COM_TXItem_On(DCAN.COMIndex[Index]));
}
//------------------------------------------------------------------------------------------------------------------------------
UINT32 CAN_GetID(UINT16 Index,UINT8 IsFilter,UINT8 IsBroadcast)
{
	UINT32 i;
  Index=DCAN.COMIndex[Index]-SDK_CAN_Index;
	if(IsFilter)
	{i=(IsBroadcast ? 0xFFFFFFFF:DCAN.Item[Index].SAD.VAL)<<(32-CAN_SAD_BitCount)| (DCAN.Item[Index].TAD.VAL&(((UINT32)1<<CAN_TAD_BitCount)-1))<<4;}
	else
  {i=(IsBroadcast ? 0xFFFFFFFF:DCAN.Item[Index].TAD.VAL)<<(32-CAN_TAD_BitCount)| (DCAN.Item[Index].SAD.VAL&(((UINT32)1<<CAN_SAD_BitCount)-1))<<4;}
	i=i|(CAN_RTR(Index)<<1)|(CAN_IDE(Index)<<2);
	return(i);
}
//------------------------------------------------------------------------------------------------------------------------------
void CAN_SetClock(UINT16 Index,UINT8 EN)
{
  if(Index==0x00) RCC.APB1ENR_BIT.CAN1EN=EN;else RCC.APB1ENR_BIT.CAN2EN=EN;	
}
//-----------------------------------------------------------------------------------------------------------------------------
#endif
//==============================================================================================================================
#if SDK_USB_COUNT
void USB_OVR_CallBack(void)
{
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_ERR_CallBack(void)
{
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SOF_CallBack(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Suspend(void)
{
  USB_On=0;USB.CNTR|=0x000C;//FSUSP=LPMODE=1
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetEPType(UINT8 EPIndex,UINT8 Type)
{
	USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x898F)|((UINT16)Type<<9);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetRXSTAT(UINT8 EPIndex,UINT8 RXSTAT)
{
  USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0xbf8f)^((UINT16)RXSTAT<<12);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetTXSTAT(UINT8 EPIndex,UINT8 TXSTAT)
{
  USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x8fbf)^((UINT16)TXSTAT<<4);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetRXTXSTAT(UINT8 EPIndex,UINT8 RXSTAT,UINT8 TXSTAT)
{
  USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0xbf8f)^((UINT16)RXSTAT<<12);
  USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x8fbf)^((UINT16)TXSTAT<<4);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_Clear_KIND(UINT8 EPIndex)
{
	USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x8E8F)|0x8080;
}	
//-----------------------------------------------------------------------------------------------------------------------------
void USB_Set_KIND(UINT8 EPIndex)
{
	USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x8F8F)|0x8180;
}	
//-----------------------------------------------------------------------------------------------------------------------------
void USB_ToggleDTOG(UINT8 EPIndex,UINT8 IsTX)
{
	USB.EPR[EPIndex]=(USB.EPR[EPIndex]&0x8F8F)|(IsTX ? 0x80C0:0xC080);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetRXCount(UINT8 EPIndex,UINT16 Count)
{
	USB.CH[EPIndex].RXCOUNT=USB_CountToRXCount(Count);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 USB_CountToRXCount(UINT16 Count)
{
  if(Count>62)
  { Count=(Count-1)>>5;return((Count<<10)|0x8000);}
	else
	{ Count=(Count+1)>>1;return(Count<<10);}
}	
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetEPAddress(UINT8 EPIndex,UINT8 EPAddr)
{
	USB.EPR[EPIndex]=(USB.EPR[EPIndex]|0x8080|EPAddr)&0x8F8F;
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetDeviceAddress(UINT8 DEVAddr)//0x00_0x7F
{
	USB_DADDR =DEVAddr|0x80;//EF=1, set device address and enable function
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetAddress(UINT8 DEVAddr)
{
  UINT32 i;
  for (i = 0; i < USB_EPCount; i++)USB_SetEPAddress(i,i);USB_SetDeviceAddress(DEVAddr);
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_SetData(UINT8 EPIndex,UINT8 *s,UINT16 Count)
{
  UINT16 i;
  if(EPIndex>=USB_EPCount||Count==0x0000)return;Count&=0x3FF;if(Count>DUSB.EPSIZE[EPIndex])Count=DUSB.EPSIZE[EPIndex];
  for(i=0;i<(Count+1)/2 ;i++,s+=2)*((UINT16 *)(DUSB.TXADDR[EPIndex]+i*4)) = *((UINT16 *)s);  
  USB.CH[EPIndex].TXCOUNT=Count;
}
//-----------------------------------------------------------------------------------------------------------------------------
void USB_GetData(UINT8 EPIndex,UINT8 *s,UINT16 Count)
{
  UINT16 i;
  if(EPIndex>=USB_EPCount||Count==0x0000)return;Count&=0x3FF;if(Count>DUSB.EPSIZE[EPIndex])Count=DUSB.EPSIZE[EPIndex];
  for(i=0;i<(Count+1)/2 ;i++,s+=2)*((UINT16 *)s)=*((UINT16 *)(DUSB.RXADDR[EPIndex]+i*4));  
  USB.CH[EPIndex].TXCOUNT=Count;
}
#endif
//==============================================================================================================================
#if SDK_COM_COUNT
//------------------------------------------------------------------------------------------------------------------------------
UINT16 COM_BUFSize(UINT16 Index,UINT8 IsTX)
{
	return(IsTX ? DCOM.Item[Index].TF.Size:DCOM.Item[Index].RF.Size);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_StartSend(UINT16 Index)
{
  COM_TX_On(Index)=1;COM_TXItem_On(Index)=0;COM_StartSendItem(Index);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_EndSend(UINT16 Index)
{
  COM_TX_On(Index)=0;COM_EndSendItem(Index);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_StartSendItem(UINT16 Index)//针对中断式发送(因为立即与定时都有各自进程)
{
  #if SDK_UART_COUNT
  if(Index>=DUART.Index && Index<DUART.Index+DUART.Count){Uart_StartSendItem(DUART.Item[Index-DUART.Index].HWIndex);return;}
  #endif
  #if SDK_CAN_COUNT
  if(Index>=DCAN.Index && Index<DCAN.Index+DCAN.Count){CAN_StartSendItem(DCAN.Item[Index-SDK_CAN_Index].HWIndex);return;}
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_EndSendItem(UINT16 Index)//针对中断式发送(因为立即与定时都有各自进程)
{
  #if SDK_UART_COUNT
  if(Index>=DUART.Index && Index<DUART.Index+DUART.Count){Uart_EndSendItem(DUART.Item[Index-DUART.Index].HWIndex);return;}
  #endif
  #if SDK_CAN_COUNT
  if(Index>=DCAN.Index && Index<DCAN.Index+DCAN.Count){CAN_EndSendItem(DCAN.Item[Index-DCAN.Index].HWIndex);return;}
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_SendString(UINT16 Index,UINT8 *s,UINT16 Count,UINT32 Time)//Uart+Can+USB,Time=延迟发送时间
{
  UINT16 i,j,k,k1,k2,Pos;  struct Data_COM_TXFrame *TF;
  if(Count==0||DCOM.Item[Index].TF.Count+Count+2>DCOM.Item[Index].TF.Size){COM_TXItem_On(Index)=0;COM_StartSendItem(Index); return;}//因为不知明原因硬件发送被挂起，需要重新触发
  TF=&DCOM.Item[Index].TF;k2=Count+2;
	for(i=0;i<(*TF).MMT.Count;i++)
  {
    if(Time<(*TF).MMT.Item[i].Time)
    {
      Pos=(*TF).MMT.Item[i].Pos;COM_TXContinue_On(Index)=0;
      for(j=(*TF).MMT.Count;j>i;j--){(*TF).MMT.Item[j]=(*TF).MMT.Item[j-1];(*TF).MMT.Item[j].Pos=((*TF).MMT.Item[j].Pos+Count+2)%(*TF).Size;}
      (*TF).MMT.Item[i].Time=Time;(*TF).MMT.Count++;
      k=((*TF).Index<(*TF).MMT.Item[i].Pos ? (*TF).Size:0)+ (*TF).Index-(*TF).MMT.Item[i].Pos; k1=(*TF).Index;
      for(j=0;j<k;j++){k1=(k1+(*TF).Size-1)%(*TF).Size; (*TF).Item[(k1+Count+2)%(*TF).Size]=(*TF).Item[k1];}
      break;
    }
    else if(Time==(*TF).MMT.Item[i].Time)
    {
      Pos=(i+1<(*TF).MMT.Count ? (*TF).MMT.Item[i+1].Pos:(*TF).Index);if(COM_TXContinue_On(Index))k2=Count;
      if(i+1<(*TF).MMT.Count)
      {
        k=((*TF).Index<(*TF).MMT.Item[i+1].Pos ? (*TF).Size:0)+ (*TF).Index-(*TF).MMT.Item[i+1].Pos; k1=(*TF).Index;
        for(j=0;j<k;j++){k1=(k1+(*TF).Size-1)%(*TF).Size; (*TF).Item[(k1+k2)%(*TF).Size]=(*TF).Item[k1];}
      }
      for(j=(*TF).MMT.Count-1;j>i;j--)(*TF).MMT.Item[j].Pos=((*TF).MMT.Item[j].Pos+k2)%(*TF).Size;
      break;
    }  
  }
  if(i==(*TF).MMT.Count){(*TF).MMT.Item[i].Time=Time;(*TF).MMT.Item[i].Pos=Pos=(*TF).Index;(*TF).MMT.Count++;}
  if(!COM_TXContinue_On(Index)){(*TF).Item[Pos]=Count&0xff;Pos=(Pos+1)%(*TF).Size;(*TF).Item[Pos]=Count>>8;Pos=(Pos+1)%(*TF).Size;}
  for(j=0;j<Count;j++){(*TF).Item[Pos]=s[j];Pos=(Pos+1)%(*TF).Size;}
  (*TF).Index=((*TF).Index+k2)%(*TF).Size;(*TF).Count+=k2;
  if(!COM_TXContinue_On(Index)){if(Time){COM_MMTTime_On=1;} else if(!COM_TX_On(Index)){COM_StartSend(Index);}}
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Printf(UINT16 Index,UINT32 Time,UINT8 *Data,...)
{ 
	const UINT8 *s;UINT8 Found,PCount,buf[20];UINT16 Len;double d;
  va_list ap; va_start(ap, Data);
  COM_TXContinue_On(Index)=0;
	while(*Data!=0)//判断是否到达字符串结束符
  {
		if(*Data=='\\')// '\'=0x5c
    {
		  switch (*++Data)
      {
				case 'r'://回车符
					buf[0]=0x0d;COM_SendString(Index, buf,1,Time);	   
					break;
				case 'n':							          //换行符
					buf[0]=0x0a;COM_SendString(Index,buf,1,Time);
					break;
				default:
				  break;
			} 		 
		}
		else if(*Data=='%')
    {
      Found=0;
			switch (*++Data)
      {				
				case 's'://字符串
         	Found=1;s = va_arg(ap, const UINT8 *);Len=StrLen((UINT8 *)s,255);
          COM_SendString(Index,(UINT8 *)s,Len,Time);
          break;
        case 'd'://十进制
        case 'f':
          Found=1;PCount=((*Data)=='d' ? 0:7);d = va_arg(ap,double); NumToStr(d,PCount, buf, &Len);
          COM_SendString(Index,buf,Len,Time);
        case 'l':
          if(*(Data+1)=='d'||*(Data+1)=='f')
          {
            Found=1;PCount=((*Data)=='d' ? 0:15);d = va_arg(ap,double); NumToStr(d,PCount, buf, &Len);
            COM_SendString(Index,buf,Len,Time);
          }
         	break;
				default:
				  break;
      }
      if(!Found){buf[0]='%';buf[1]=*(Data);COM_SendString(Index,buf,2,Time);}
		}
		else
    {buf[0]=*Data;COM_SendString(Index,buf,1,Time);}
    
		Data++;COM_TXContinue_On(Index)=1; 
	}
  COM_TXContinue_On(Index)=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Send_Timer(void)//Every 100us
{
  UINT16 i,j,k;
  if(!COM_MMTTime_On)return; IRQTempFlag0=0;
  for(i=0;i<SDK_COM_COUNT;i++)
  {
    k=0;IRQTempFlag1=0;
    for(j=0;j<DCOM.Item[i].TF.MMT.Count;j++)
    {if(DCOM.Item[i].TF.MMT.Item[j].Time){DCOM.Item[i].TF.MMT.Item[j].Time--;if(DCOM.Item[i].TF.MMT.Item[j].Time)IRQTempFlag0=1;else {k=j;if(j==0)IRQTempFlag1=1;}} else {k=j;} }
    if(k){for(j=1;j<DCOM.Item[i].TF.MMT.Count-k;j++)DCOM.Item[i].TF.MMT.Item[j]=DCOM.Item[i].TF.MMT.Item[j+k];DCOM.Item[i].TF.MMT.Count-=k;}
    if(IRQTempFlag1)COM_StartSend(i);
  }
  COM_MMTTime_On&=IRQTempFlag0;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT16 COM_PRTC_CodeToIndex(UINT16 PRTC_Code)
{
  UINT8 i;
  for(i=0;i<PRTC[0];i++)if(PRTC[i+1]==PRTC_Code)break; return(i);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_PRTC_Init(UINT16 Index)
{
  DCOM.Item[Index].PRTC.TimeIndex=COM_PRTC_CodeToIndex(DCOM.Item[Index].PRTC.Item[DCOM.Item[Index].PRTC.Index]);
  if(Index==0)
  {
    SETIRQEN(IRQN_USART1,0);RCC.APB2ENR_BIT.UART1EN=UART_CR1(0)=0;RCC.APB2ENR_BIT.UART1EN=1;
    DUART.Item[0].BitCount=(DCOM.Item[Index].PRTC.Item[DCOM.Item[Index].PRTC.Index]==COM_Protocol_DMX512 ? 9:8);
    DCOM.Item[Index].State.VAL=DCOM.Item[Index].RF.Index=DCOM.Item[Index].RF.Count=0x0000;
    DCOM.Item[Index].TF.Index=DCOM.Item[Index].TF.Count=DCOM.Item[Index].TF.MMT.Index=DCOM.Item[Index].TF.MMT.Count=0x0000;
    UART_CR1(0)=(DUART.Item[0].BitCount==8 ? 0x0000002C:0x0000102C);
    SETIRQEN(IRQN_USART1,1); (*UART[0]).CR1_BIT.UE=1;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_PRTC_Timer(void)//every 100ms
{
  UINT8 i,j;
  for(i=0;i<SDK_COM_COUNT;i++)
  {
    if((!COM_Connect_On(i) && DCOM.Item[i].PRTC.Count<=1) || DCOM.Item[i].PRTC.TimeIndex<PRTC[0])continue;
    j=PRTC_Time[DCOM.Item[i].PRTC.TimeIndex][COM_Connect_On(i)];
    DCOM.Item[i].PRTC.TimeCount++;
    if(DCOM.Item[i].PRTC.TimeCount>=j && DCOM.Item[i].TF.Count==0x0000) 
    {
      DCOM.Item[i].PRTC.TimeCount=0x00;
      if(COM_Connect_On(i))
      {COM_Connect_On(i)=0;}
      else if(DCOM.Item[i].PRTC.Count>1)
      {DCOM.Item[i].PRTC.Index=(DCOM.Item[i].PRTC.Index+1)%DCOM.Item[i].PRTC.Count;COM_PRTC_Init(i);}
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------
#endif
//==============================================================================================================================
void GPIO_SetPinMode(UINT16 PinNumber,UINT8 Mode)
{
	UINT8 Pos;UINT32 *P;
	P=(UINT32 *)(&GPIO[PinNumber>>5].CRL+(PinNumber&0x18 ? 4:0));Pos=(PinNumber&7)*4;
	(*P)=((*P)&~((UINT32)0x0F<<Pos))|((Mode&0x0F)<<Pos);
}
//------------------------------------------------------------------------------------------------------------------------------
void GPIO_SetMultiPinMode(UINT8 GPIOIndex,UINT32 PIN,UINT8 Mode)
{
	UINT8 i;UINT32 V,K,M;
	K=0x0F;M=Mode&0x0F;V=GPIO[GPIOIndex].CRL;
	for(i=0;i<8;i++){if(PIN&1)V=(V&(~K))|M;PIN>>=1;K<<=4;M<<=4;}
	GPIO[GPIOIndex].CRL=V;
	K=0x0F;M=Mode&0x0F;V=GPIO[GPIOIndex].CRH;
	for(i=0;i<8;i++){if(PIN&1)V=(V&(~K))|M;PIN>>=1;K<<=4;M<<=4;}
	GPIO[GPIOIndex].CRH=V;
}	
//------------------------------------------------------------------------------------------------------------------------------
void GPIO_Init(volatile Type_GPIO* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
        }
    }
    }
    GPIOx->CRL = tmpreg;
  }

  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}
//-----------------------------------------------------------------------------------------------------------------------------
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
   
  if (NVIC_InitStruct->NVIC_IRQChannelCmd !=0 )
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((M3SYS.AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
    
    M3SYS.IPR[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    M3SYS.ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    M3SYS.ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
} 
//==============================================================================================================================
void SPI_SetClock(UINT8 Index,UINT8 EN)
{
	if(Index==0x00)
	{RCC.APB2ENR_BIT.SPI1EN=EN;}//72MHz
	else if(Index==1)
	{RCC.APB1ENR_BIT.SPI2EN=EN;}//36MHz
	else
	{RCC.APB1ENR_BIT.SPI3EN=EN;} 
}
//------------------------------------------------------------------------------------------------------------------------------
Type_Setup_SPI SPI_SetupFrom(UINT8 EN,UINT8 CPHA,UINT8 CPOL,UINT8 BR, UINT8 ALF,UINT8 BIDMode)
{
	Type_Setup_SPI ST;ST.EN=EN;ST.CPHA =CPHA;ST.CPOL=CPOL;ST.BR =BR;ST.ALF=ALF;ST.BIDMode=BIDMode;
	return(ST);
}
//==============================================================================================================================
void I2C_SetClock(UINT8 Index,UINT8 EN)
{
  if(EN)RCC.APB1ENR|=(UINT32)(1<<(21+Index));else RCC.APB1ENR&=~(UINT32)(1<<(21+Index));
}
//==============================================================================================================================
void EXTI_SetIRQ(UINT8 Index)
{
	switch(Index)
	{
		case 0:
		  SETIRQ(IRQN_EXTI0,0,1);break;
		case 1:
		  SETIRQ(IRQN_EXTI1,0,1);break;
		case 2:
		  SETIRQ(IRQN_EXTI2,0,1);break;
		case 3:
		  SETIRQ(IRQN_EXTI3,0,1);break;
		case 4:
		  SETIRQ(IRQN_EXTI4,0,1);break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		  SETIRQ(IRQN_EXTI9_5,0,1);break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
	   	SETIRQ(IRQN_EXTI15_10,0,1); break;
		default:
			break;
	}
}
//------------------------------------------------------------------------------------------------------------------------------
Type_Setup_EXT EXTI_SetupFrom(UINT8 EN,UINT8 PN,UINT8 Rising,UINT8 Falling)
{
  Type_Setup_EXT ST;ST.EN=EN;ST.PN=PN;ST.Rising=Rising;ST.Falling =Falling;
  return(ST); 
}
//==============================================================================================================================
void Flash_UnLock(void)
{
	FLASH.KEYR=FLASH_KEY1;FLASH.KEYR=FLASH_KEY2;
#if IsDensity(XL)
  FLASH.KEYR2=FLASH_KEY1;FLASH.KEYR2=FLASH_KEY2;
#endif
}
//-----------------------------------------------------------------------------------------------------------------------------
void Flash_Lock(void)
{
	FLASH.CR_BIT.LOCK=1;//Bank1
#if IsDensity(XL)
  FLASH.CR2_BIT.LOCK=1;//Bank2
#endif
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_GetStatus(UINT8 IsBank2)
{
 #if IsDensity(XL)
  if(IsBank2)
  {
    if(FLASH.SR2_BIT.BSY) return(FLASH_BUSY);
    if(FLASH.SR2_BIT.PGERR)return(FLASH_ERROR_PG);
    if(FLASH.SR2_BIT.WRPRTERR)return(FLASH_ERROR_WRP);
  }
  else
 #endif
  {
    if(FLASH.SR_BIT.BSY) return(FLASH_BUSY);
    if(FLASH.SR_BIT.PGERR)return(FLASH_ERROR_PG);
    if(FLASH.SR_BIT.WRPRTERR)return(FLASH_ERROR_WRP);
  }
  return(FLASH_COMPLETE);
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_WaitForLastOperation(UINT8 IsBank2,UINT32 Timeout)
{ 
  Flash_Status status = FLASH_COMPLETE;
  do{status =Flash_GetStatus(IsBank2);Timeout--;} while((status == FLASH_BUSY) && Timeout );
  if(Timeout == 0x00 ) status = FLASH_TIMEOUT;
  return status;
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_ReadOutProtection(UINT8 IsBank2,UINT8 EN)
{
  Flash_Status status = FLASH_COMPLETE;
  status = Flash_WaitForLastOperation(IsBank2,FLASH_EraseTimeout);
  if(status != FLASH_COMPLETE)return(status);
  
  FLASH.OPTKEYR = FLASH_KEY1;FLASH.OPTKEYR = FLASH_KEY2;//Authorizes the small information block programming
  FLASH.CR_BIT.OPTER=1; FLASH.CR_BIT.STRT=1;
  status = Flash_WaitForLastOperation(IsBank2,FLASH_EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    FLASH.CR_BIT.OPTER=0; FLASH.CR_BIT.OPTPG=1; OB.RDP =(EN ? RDP_Key : 0x00);
    status = Flash_WaitForLastOperation(IsBank2,FLASH_EraseTimeout); 
  }
  if(status != FLASH_TIMEOUT)FLASH.CR_BIT.OPTER=0;
  return(status);       
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_EnableWriteProtection(UINT8 IsBank2,UINT32 FLASH_Pages)
{
  Flash_Status status = FLASH_COMPLETE;
  UINT8 i;union UINT32_REG WRP;
  WRP.VAL=~FLASH_Pages;
  status = Flash_WaitForLastOperation(IsBank2,FLASH_ProgramTimeout);
  if(status != FLASH_COMPLETE)return(status);
  
  FLASH.OPTKEYR = FLASH_KEY1; FLASH.OPTKEYR = FLASH_KEY2; FLASH.CR_BIT.OPTPG=1;
  for(i=0;i<4;i++)
  {if((status == FLASH_COMPLETE) && (WRP.B[i] != 0xFF)) {OB.WRP[i] = WRP.B[i];status = Flash_WaitForLastOperation(IsBank2,FLASH_ProgramTimeout);}}
  if(status != FLASH_TIMEOUT) FLASH.CR_BIT.OPTPG=0;
  return status;       
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_EraseAddress(UINT32 Address)
{
	Flash_Status status = FLASH_COMPLETE;
  if(Address<BASE_FLASH)return(status);
  if(Address < FLASH_BANK1_END_ADDRESS)  
  {
    status = Flash_WaitForLastOperation(0,FLASH_EraseTimeout);//Wait for last operation to be completed
    if(status == FLASH_COMPLETE)
    { 
      FLASH.CR_BIT.PER=1; FLASH.AR = Address;  FLASH.CR_BIT.STRT=1;;//if the previous operation is completed, proceed to erase the page
      status = Flash_WaitForLastOperation(0,FLASH_EraseTimeout);//Wait for last operation to be completed
      FLASH.CR_BIT.PER=0;//Disable the PER Bit
    }
  }
  #if IsDensity(XL)
  else if(Address<FLASH_BANK2_END_ADDRESS)
  {
    status = FLASH_WaitForLastOperation(1,FLASH_EraseTimeout);///Wait for last operation to be completed
    if(status == FLASH_COMPLETE)
    { 
      FLASH.CR2_BIT.PER=1; FLASH.AR2 = Address; FLASH.CR2_BIT.STRT=1;//if the previous operation is completed, proceed to erase the page
      status = FLASH_WaitForLastOperation(1,FLASH_EraseTimeout);//Wait for last operation to be completed
      FLASH.CR2_BIT.PER=0;//Disable the PER Bit
    }
  }
  #endif
  return(status);
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_ErasePage(UINT16 Page)//Page=0_127
{
  return (Flash_EraseAddress(BASE_FLASH+(Page&0x7F)*SIZE_FLASHPAGE)); 
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_EraseALL(void)
{
  Flash_Status status = FLASH_COMPLETE;
  status = Flash_WaitForLastOperation(0,FLASH_EraseTimeout);//Wait for last operation to be completed
  if(status == FLASH_COMPLETE)
  {
     FLASH.CR_BIT.MER=1; FLASH.CR_BIT.STRT=1;
      status = Flash_WaitForLastOperation(0,FLASH_EraseTimeout);//Wait for last operation to be completed
     FLASH.CR_BIT.MER=0;
  }
#if IsDensity(XL)
  if(status == FLASH_COMPLETE)
  {
     FLASH.CR2_BIT.MER=1; FLASH.CR2_BIT.STRT=1;
     status = FLASH_WaitForLastOperation(1,FLASH_EraseTimeout);//Wait for last operation to be completed
     FLASH.CR2_BIT.MER=0;
  }
#endif
  return(status);
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_EraseOptionBytes(UINT8 IsBank2)
{
  Flash_Status status = FLASH_COMPLETE;
  status = Flash_WaitForLastOperation(IsBank2,FLASH_EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    FLASH.OPTKEYR = FLASH_KEY1; FLASH.OPTKEYR = FLASH_KEY2;//Authorize the small information block programming
    FLASH.CR_BIT.OPTER =1; FLASH.CR_BIT.STRT=1;//f the previous operation is completed, proceed to erase the option bytes
    status = Flash_WaitForLastOperation(IsBank2,FLASH_EraseTimeout);//Wait for last operation to be completed
    if(status == FLASH_COMPLETE)
    {
      FLASH.CR_BIT.OPTER=0;//if the erase operation is completed, disable the OPTER Bit
      FLASH.CR_BIT.OPTPG=1;//Enable the Option Bytes Programming operation
      OB.RDP =(FLASH.OBR_BIT.RDPRT ? 0x00:0xA5); //Restore the last read protection Option Byte value
      status = Flash_WaitForLastOperation(IsBank2,FLASH_ProgramTimeout);//Wait for last operation to be completed
      if(status != FLASH_TIMEOUT)FLASH.CR_BIT.OPTPG=0;//if the program operation is completed, disable the OPTPG Bit
    }
    else
    {if(status != FLASH_TIMEOUT) FLASH.CR_BIT.OPTPG=0;}//Disable the OPTPG Bit
  }
  return(status);
}
//-----------------------------------------------------------------------------------------------------------------------------
Flash_Status Flash_UserOptionByteConfig(UINT16 OB_IWDG,UINT16 OB_STOP,UINT16 OB_STDBY)
{
  Flash_Status status = FLASH_COMPLETE; 

  FLASH.OPTKEYR = FLASH_KEY1; FLASH.OPTKEYR = FLASH_KEY2;//Authorize the small information block programming
  status = Flash_WaitForLastOperation(0,FLASH_ProgramTimeout);
  if(status == FLASH_COMPLETE)
  {  
    FLASH.CR_BIT.OPTPG=1;OB.USER = OB_IWDG| OB_STOP | OB_STDBY | 0xF8; //Enable the Option Bytes Programming operation
    status = Flash_WaitForLastOperation(0,FLASH_ProgramTimeout);
    if(status != FLASH_TIMEOUT) FLASH.CR_BIT.OPTPG=0;//if the program operation is completed, disable the OPTPG Bit
  }    
  return status;//Return the Option Byte program Status
}
//-----------------------------------------------------------------------------------------------------------------------------
void Flash_ReadString(UINT32 Address,UINT8 *s,UINT16 Len)
{
  UINT16 i;
  if(Len==0x0000)return; for(i=0;i<Len;i++)s[i]=*(UINT8 *)(Address+i);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 Flash_WriteString(UINT32 Address,UINT8 *s,UINT16 Len)//返回剩余字节数
{
  UINT16 i,SubPos,SubLen;
	if(DC_Inited)DIRQ(); SubPos=Address & (SIZE_FLASHPAGE-1);Address=(Address/SIZE_FLASHPAGE)*SIZE_FLASHPAGE;
  while(Len)
  {
		SubLen=(SubPos+Len<=SIZE_FLASHPAGE ? Len:SIZE_FLASHPAGE-SubPos);
    if(Flash_WriteCode_On)//写代码
    {
      if(SubPos==0)
      {if(Flash_EraseAddress(Address)!=FLASH_COMPLETE)break;}
      else
      {if(Flash_WaitForLastOperation(0,FLASH_ProgramTimeout)!= FLASH_COMPLETE)break;}
      FLASH.CR_BIT.PG=1;
      if(SubPos&1){*(volatile UINT16 *)(Address+SubPos-1)=(s[0]<<8)|(*(volatile UINT8 *)(Address+SubPos));SubPos++;SubLen--;s++;Len--;}
      for(i=0;i<SubLen/2;i++)*(volatile UINT16 *)(Address+SubPos+2*i)=s[2*i]|(s[2*i+1]<<8);
      if(SubLen&1)*(volatile UINT16 *)(Address+SubPos+2*i)=s[2*i]|((*(volatile UINT8 *)(Address+SubPos+2*i+1))<<8);
      FLASH.CR_BIT.PG=0;
    }
    else//写参数
    {      
      for(i=0;i<SubPos;i++)DFLA.Item[i]=*(UINT8 *)(Address+i);
      for(i=0;i<SubLen;i++)DFLA.Item[SubPos+i]=s[i];SubPos+=SubLen;
      if(SubPos<SIZE_FLASHPAGE)
      for(i=0;i<SIZE_FLASHPAGE-SubPos;i++)DFLA.Item[SubPos+i]=*(UINT8 *)(Address+SubPos+i);
      if(Flash_EraseAddress(Address)!=FLASH_COMPLETE)break;
      //Write
      FLASH.CR_BIT.PG=1;
      for(i=0;i<SIZE_FLASHPAGE/2;i++)*(volatile UINT16 *)(Address+2*i)=*(UINT16 *)(DFLA.Item+2*i);
      FLASH.CR_BIT.PG=0;
    }
    s+=SubLen;Len-=SubLen;SubPos=0x0000;Address+=SIZE_FLASHPAGE;
  }
  i=Flash_WaitForLastOperation(0,FLASH_ProgramTimeout);if(DC_Inited)EIRQ();
  return(Len);
}
//-----------------------------------------------------------------------------------------------------------------------------
void Flash_WriteItem(UINT32 Address,UINT8 *s,UINT16 Len)
{
  Flash_UnLock();Flash_WriteString(Address,s,Len);Flash_Lock();
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 Flash_IsNew(void)
{
  if(StrCompare((UINT8 *)Device_FirstRun,(UINT8 *)DC_FirstRun,StrLen((UINT8 *)DC_FirstRun,64),0)!=1)//首次运行
  {Flash_UnLock();Flash_WriteString((UINT32)Device_FirstRun,(UINT8 *)DC_FirstRun, StrLen((UINT8 *)DC_FirstRun,64));Flash_Lock();return(1);}  
  return(0);
}
//==============================================================================================================================
UINT8 SYS_Dentify(UINT64 DV)
{
  UINT32 i,j;UINT8 c;
  LNG[0]=CPUGet_MSP()+0x0014; LNG[0]=(*(UINT32 *)LNG[0])-((UINT32)Init_MEM); if(LNG[0]!=0x5C2)while(1);LNG[0]=0;
  for(i=0;i<8;i++)DAPP.TBUF[i]=0x00;
  for(i=0;i<DTF_P_Count;i++)
  {for(j=0;j<DTF_P[i][1]*4;j++){Flash_ReadString(DTF_P[i][0]-1+j,&c,1);DAPP.TBUF[j&7]^=c;}}
  i=0;for(j=0;j<8;j++){DAPP.TBUF[i]^=((Device_BaseDT[j]<<1)|(Device_BaseDT[j]>>7));i=(i+1)%8;};
  i=0;for(j=0;j<8;j++){DAPP.TBUF[i]^=((Device_MadeDT[j]<<2)|(Device_MadeDT[j]>>6));i=(i+1)%8;};
  i=0;for(j=0;j<24;j++){DAPP.TBUF[i]^=((Device_ID[j]<<3)||(Device_ID[j]>>5));i=(i+1)%8;};
  i=0;for(j=0;j<StrLen((UINT8 *)Device_CP,0x40);j++){c=Device_CP[j]+3;DAPP.TBUF[i]^=((c<<4)|(c>>4));i=(i+1)%8;};
  i=0;for(j=0;j<StrLen((UINT8 *)Device_NV,0x40);j++){c=Device_NV[j]+4;DAPP.TBUF[i]^=((c<<5)|(c>>3));i=(i+1)%8;};
  j=0;for(i=0;i<8;i++){if(DAPP.TBUF[i]==(DV&0xFF))j++;if(DAPP.V.ST[1].VAL!=0x012D5D48)DAPP.TBUF[i]=0x00; DV>>=8;}
  return(j==8 ? 1:0); 
}
//==============================================================================================================================
