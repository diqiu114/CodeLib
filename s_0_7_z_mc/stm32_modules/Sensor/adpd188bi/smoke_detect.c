#include "smoke_detect.h"
//#include "proj_incs.h"
//#include "app_USER_incs.h"


uint32_t dcfg_org_188[] = {
  0x00020005,
  0x00060400,
  0x00030000,
  0x00050000, 
  
  //0x000C000F,
  0x000D0000,
  0x00100000,
  0x001130A9,
  //  0x004F2090,
  //  0x000B0000,
  0x004F2090,
  0x000B0000,
  0x00500000,
  0x00510000,
  0x00520040,
  0x0053E400,
  0x00570000,
  0x005F0000,
  0x00460000,
  0x00470080,
  0x00480000,
  0x00490000,
  0x004A0000,
  0x00260000,
  0x00270800,
  0x00280000,
  0x0029A00A,
  0x00130190,
  0x002A9000,
  0x002B8F00,
  0x002C9400,
  0x002D9200,
  0x002E0000,
  0x002F0000,
  0x00320320,
  0x00330113,
  0x003A22D4,
  0x005C0000,
  
  0x001203EB,//sample rate
  0x00150330,//average
  
  0x0014011D,
  
  0x00180000,
  0x00193FFF,
  0x001A3FFF,
  0x001B3FFF,
  0x00300320,   // 2us, with 32us offset
  0x0031080e, 
  //0x0031040e, 
  0x003922DC,  
  0x00421C34,
  0x0043ADA5, 
  0x005E0808,
  0x00163000,
  0x00170009,
  
  0x001E0000,
  0x001F3FFF,
  0x00203FFF,
  0x00213FFF,
  0x00350320,
  0x0036080e,
 // 0x0036040e,
  0x003B22DC,  
  0x00441C34,   // Vref=1.265V
  0x0045ADA5,  
  0x00590808,
  0x001C3000,
  0x001D0009,
  
  0x00580544, 
  
  0x00223039,
  0x00233036,
  0x00241530,
  0x0025630C,
  0x00340000,
  
  0x003C3006,   // use 32M cmclk
  0x003D0000,
  0x00540AA0,
  0x00550000,
  0x005A0010,
  
  0x00401010,
  0x0041004C,
  0x004E7040,
  
  //    0x003F0320,
  
  //    0x005A0010,
  0xFFFFFFFF,    
  
};

/*uint32_t dcfg_temp_188[] = {
0x0001C0FF,
0x00020005,
0x00030000,
0x00050000,
0x00060400,
0x000C0000,
0x000D0000,
0x00100000,
0x001131B9,
//  0x004F2090,
//  0x000B0000,
0x004F20D0,
0x000B0700,
0x00500000,
0x00510000,
0x00520242,
0x0053E400,
0x00570000,
0x005F0000,
0x00460000,
0x00470080,
0x00480000,
0x00490000,
0x004A0000,
0x00260000,
0x00270800,
0x00280000,
0x0029A00A,
0x00130190,
0x002A9000,
0x002B8F00,
0x002C9400,
0x002D9200,
0x002E0000,
0x002F0000,
0x00320320,
0x00330113,
0x003A22D4,
0x005C0000,
0x00120014,//sample rate
0x00150440,//average
0x0014055D,
0x00180000,
0x00190000,
0x001A3FFF,
0x001B3FFF,
0x00300324,
0x0031041F,
0x003922D0,
0x00421CB6,
0x0043AE65,
0x005E0808,
0x00163000,
0x00170000,
0x001E0000,
0x001F0000,
0x00203FFF,
0x00213FFF,
0x00350320,
0x0036040E,
0x003B22E0,
0x00441C36,
0x0045AE65,
0x00590808,
0x001C3000,
0x001D0000,
0x00580080,
0x00223539,
0x00233536,
0x00241530,
0x0025630C,
0x00340000,
0x003C3006,
0x003D0000,
0x00540AA0,
0x00550000,
0x005A0010,
0x00401010,
0x0041004C,
0x004E7040,
0x004B269A,
0x004C0004,
0x004D0090,


//    0x003F0320,

//    0x005A0010,
0xFFFFFFFF,    

};*/

uint8_t value[16];
uint32_t readCodeBuffer[8];
uint8_t nLoopLim;

APP_ADPD_STATE_NORMAL_t  APP_ADPD_STATE_NORMAL;

/**
*  @brief    Load ADPD default configuration
*  @param    uint32_t *cfg
*  @retval   None
*/
void LoadDefaultConfig(const uint32_t *cfg)
{
  uint8_t regAddr, i;
  uint16_t regData;
  if (cfg == 0) {
    return;
  }
  
  /* Clear the FIFO */
  AdpdDrvRegWrite(0x10, 0);
  AdpdDrvRegWrite(0x5F, 1);
  AdpdDrvRegWrite(0x00, 0x80FF);
  AdpdDrvRegWrite(0x5F, 0);
  i = 0;
  while (1) {
    /* Read the address and data from the config */
    regAddr = (uint8_t)(cfg[i] >> 16);
    regData = (uint16_t)(cfg[i]);
    i++;
    if (regAddr == 0xFF) {
      break;
    }
    
    /* Load the data into the ADPD registers */
    if (AdpdDrvRegWrite(regAddr, regData) != ADPDDrv_SUCCESS) {
      break;
    }
  }
}

/**
*  @brief    Read default configuration parameters to verify
*  @param    uint32_t *cfg
*  @retval   None
*/
void VerifyDefaultConfig(const uint32_t *cfg)
{
  uint16_t def_val;
  uint8_t  i;
  uint8_t  regAddr;
  uint16_t regData;
  if (cfg == 0) {
    return;
  }
  i = 0;
  /* Read the address and data from the config */
  regAddr = (uint8_t)(cfg[0] >> 16);
  def_val = (uint16_t)(cfg[0]);
  
  /* Read the data from the ADPD registers and verify */
  while (regAddr != 0xFF) {
    if (AdpdDrvRegRead(regAddr, &regData) != ADPDDrv_SUCCESS) {
      //asm("nop");
      __nop();
      __nop();
      //asm("nop");
      return;
    } else if (regData != def_val) {
      __nop();
      __nop();
      //asm("nop");
      //asm("nop");
      return;
    }
    i++;
    regAddr = (uint8_t)(cfg[i] >> 16);
    def_val = (uint16_t)(cfg[i]);
  }
}

uint8_t  AdpdConfiguration(CONFIG_TYPE cType)
{
  uint8_t state;
  
  /* Soft reset the ADPD device */
  state=AdpdDrvSoftReset();
  if(state!=ADPDDrv_SUCCESS)
  {
    return 0;
  }
  /* Initialize the ADPD driver*/
  state=AdpdDrvOpenDriver();
  if(state!=ADPDDrv_SUCCESS)
  {
    return 0;
  }
  if(cType == OPTICAL){
    /* Load default configuration parameters */
    LoadDefaultConfig(dcfg_org_188);
    
    /* Read default configuration parameters from the device registers and verify */
    VerifyDefaultConfig(dcfg_org_188);
  }
  else{
    //LoadDefaultConfig(dcfg_temp_188);  
    // VerifyDefaultConfig(dcfg_temp_188);
  }
  
  AdpdDrvRegWrite(0x004B, 0x2695);
  AdpdDrvRegWrite(0x004D, 0x4272);
  
  /* APDP Clock Calibration */
  //  AdpdClockCalibration();
  
  if(cType == OPTICAL){
    /* Set the slot modes for slot A and slot B */
    state=AdpdDrvSetSlot(ADPDDrv_SUM_32, ADPDDrv_SUM_32);
    if(state!=ADPDDrv_SUCCESS)
    {
      return 0;
    }
    nLoopLim = APP_ADPD_STATE_NORMAL.nAdpdDataSetSize = 8; 
    
  }
  else{
    /* Set the slot modes for slot A and slot B */
    state=AdpdDrvSetSlot(ADPDDrv_4CH_16, ADPDDrv_4CH_16);
    if(state!=ADPDDrv_SUCCESS)
    {
      return 0;
    }
    nLoopLim = APP_ADPD_STATE_NORMAL.nAdpdDataSetSize = 16;   
  }  
  return 1;
}

/**
*  @brief    calibration 32k clock
*  @param    None
*  @retval   None
*/

uint32_t ticks_0;
uint32_t ticks_1;
uint32_t countnumber;
uint16_t clock32k;
uint16_t test_data;


uint8_t Calibrate32KClock(void)
{
  //uint32_t countnumber = 0;
  uint8_t avgSlotA, avgSlotB;
  uint16_t rateSlot;
  //uint16_t clock32k;
  
  uint8_t counttimes = 0;
  dataADPD dataRead;
  uint32_t slotAtemp=0, slotBtemp=0;
  
  AdpdDrvGetSamplingFrequency(&rateSlot);
  AdpdDrvGetInternalAverage(&avgSlotA, SLOT_A);
  AdpdDrvGetInternalAverage(&avgSlotB, SLOT_B);
  //printf("rate: %x, avgA: %d, avgB: %d\r\n", rateSlot, avgSlotA, avgSlotB);
  
  while(1)
  {
    ticks_0=PORT_TICKS_GET_COUNT();
    // SysTick_Config(SystemCoreClock/1000);
    //将slota和slotb都设置成32字节
    AdpdDrvSetSlot(ADPDDrv_SUM_32, ADPDDrv_SUM_32);
    //清除slota和slotb的中断和fifo样本数
    AdpdDrvRegWrite(0x00, 0x80FF);
    //设置成采样模式
    AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);
    while(1)
    {
      //获取当前fifo深度
      AdpdDrvGetParameter(ADPD_FIFOLEVEL, (uint16_t*)&(APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize));
      //printf("fifo: %d\r\n", nAdpdFifoLevelSize);
      if(APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize == 8){
        //读取数据
        dataRead=AdpdDataRead(OPTICAL);
        //SMOKER_POWER.Make(IO_MODE_OUT_PP_LOW);
        counttimes++;
        slotAtemp = dataRead.dataSlotA;
        slotBtemp = dataRead.dataSlotB;
        //回到空闲状态
        AdpdDrvSetOperationMode(ADPDDrv_MODE_IDLE); 
        break;
      }
 
    }
    
    ticks_1=PORT_TICKS_GET_COUNT();
    //printf("times: %d count: %d\r\n", counttimes, countnumber);
    //SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
    countnumber=((uint32_t)(ticks_1-ticks_0));
    AdpdDrvRegRead(0x4B,&clock32k);
    printf("clock32k:%d",clock32k);
    if(countnumber<990)
    {
      clock32k++;
      AdpdDrvRegWrite(0x4B,clock32k);
    }
    else if(countnumber>1010)
    {
      clock32k--;
      AdpdDrvRegWrite(0x4B,clock32k);
    }
    else
    {
      break;
    }    
  }
  APP_ADPD_STATE_NORMAL.blueOffset = slotAtemp;//counttimes;
  APP_ADPD_STATE_NORMAL.irOffset = slotBtemp;//counttimes;
  //printf("blueOffset:%d, irOffset:%d\r\n", APP_ADPD_STATE_NORMAL.blueOffset, APP_ADPD_STATE_NORMAL.irOffset);
  
  AdpdDrvSetSamplingFrequency(rateSlot);
  
  AdpdDrvSetInternalAverage(avgSlotA, SLOT_A);
  AdpdDrvSetInternalAverage(avgSlotB, SLOT_B);

  return 1;
}

/**
*  @brief    ADPD clock calibration
*  @param    None
*  @retval   None
*/
uint8_t AdpdClockCalibration(void)
{
  if(Calibrate32KClock() == 0)
  {
    return 0;
  }
  Calibrate32MClock();
  
  return 1;
}
/**
*  @brief    calibration 32M clock
*  @param    None
*  @retval   None
*/
void Calibrate32MClock(void){
  uint16_t clkfifo, clk32m_en, clk32m;
  uint16_t clk32madj;
  uint32_t i;
  float clockerror=0;
  
  AdpdDrvSetSlot(ADPDDrv_SUM_32, ADPDDrv_SUM_32);
  AdpdDrvRegWrite(0x00, 0x80FF);
  AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);
  
  AdpdDrvRegRead(REG_FIFO_CLK, &clkfifo);
  AdpdDrvRegWrite(REG_FIFO_CLK, 1);
  AdpdDrvRegWrite(REG_FIFO_CLK, 1);
  AdpdDrvRegRead(REG_OSC32M_CAL, &clk32m_en);
  AdpdDrvRegWrite(REG_OSC32M_CAL, 0x20);
  for(i=0; i<2000; i++);
  AdpdDrvRegRead(REG_CLK_RATIO, &clk32m);
  //printf("32M count: %d\r\n", clk32m);
  
  clockerror = 32000000.0*(1-(float)clk32m/2000.0);
  //printf("32M clockerror: %f\r\n", clockerror);
  AdpdDrvRegRead(REG_OSC32M_ADJ, &clk32madj);
  clk32madj = clk32madj+(int)(clockerror/109000);
  //printf("32M clock adj: %d\r\n", clk32madj);
  
  AdpdDrvRegWrite(REG_OSC32M_ADJ, clk32madj);
  //for(i=0; i<2000; i++);
  //AdpdDrvRegRead(REG_CLK_RATIO, &clk32m);
  //printf("32M count: %d\r\n", clk32m);
  
  AdpdDrvRegWrite(REG_FIFO_CLK, 0);
  AdpdDrvRegWrite(REG_OSC32M_CAL, 0);
  
  AdpdDrvSetOperationMode(ADPDDrv_MODE_IDLE);
}

/**
*  @brief  ADPD Data Read.
*  @param  None
*  @retval dataADPD
*/
dataADPD AdpdDataRead(CONFIG_TYPE cType)
{
  uint32_t LoopCnt;
  uint16_t nRetValue = 0;
  
  dataADPD readsensor;
  
  /* Read the data from the FIFO and print them */
  
  if(cType == OPTICAL){
    nRetValue = AdpdDrvReadFifoData(&value[0], APP_ADPD_STATE_NORMAL.nAdpdDataSetSize);
    if (nRetValue == ADPDDrv_SUCCESS) 
    {
      for (LoopCnt = 0; LoopCnt < nLoopLim; LoopCnt += 4){
        
        /* Byte swapping is needed to print ADPD data in proper format */
        readCodeBuffer[LoopCnt>>2] = (value[LoopCnt] << 8) 
          | (value[LoopCnt+1] )
            |(value[LoopCnt+2] << 24)
              |value[LoopCnt + 3]<<16;
      }
      APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize = APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize - APP_ADPD_STATE_NORMAL.nAdpdDataSetSize;      
    }
    readsensor.dataSlotA = readCodeBuffer[0];
    readsensor.dataSlotB = readCodeBuffer[1];
  }
  else{
    nRetValue = AdpdDrvReadFifoData(&value[0], APP_ADPD_STATE_NORMAL.nAdpdDataSetSize);
    if (nRetValue == ADPDDrv_SUCCESS) 
    {
      for (LoopCnt = 0; LoopCnt < nLoopLim; LoopCnt += 2){
        
        /* Byte swapping is needed to print ADPD data in proper format */
        readCodeBuffer[LoopCnt>>1] = (value[LoopCnt] << 8) | value[LoopCnt + 1];
      }
      APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize =APP_ADPD_STATE_NORMAL. nAdpdFifoLevelSize - APP_ADPD_STATE_NORMAL.nAdpdDataSetSize;      
    }
    readsensor.dataSlotA = readCodeBuffer[0];
    readsensor.dataSlotB = readCodeBuffer[5];
  }
  
  return readsensor;
}

/**
*  @brief    read temperature and humidity data
*  @param    None
*  @retval   dataADPD
*/
dataADPD AdpdGetTHData(void)
{
  dataADPD readsensor;
  
  /* Change ADPD operation mode to idle mode to re-config */
  AdpdDrvSetOperationMode(ADPDDrv_MODE_IDLE);
  AdpdDrvRegWrite(0x00, 0x80FF);
  
  AdpdConfiguration(TEMP_HUMI);      
  
  /* Set the device operation to sample mode. The data can be collected now */
  AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);
  
  /* Read the size of the data available in the FIFO */
  do{
    AdpdDrvGetParameter(ADPD_FIFOLEVEL, (uint16_t*)&APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize);
  }while (APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize < APP_ADPD_STATE_NORMAL.nAdpdDataSetSize);
  
  /* Read FIFO data */
  readsensor=AdpdDataRead(TEMP_HUMI);
  
  /* Change ADPD operation mode to idle mode to re-config */
  AdpdDrvSetOperationMode(ADPDDrv_MODE_IDLE);
  AdpdDrvRegWrite(0x00, 0x80FF);
  
  AdpdConfiguration(OPTICAL);      
  /* Set the device operation to sample mode. The data can be collected now */
  AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE); 
  
  return readsensor;
}

/**
*  @brief    change read count code to PTR
*  @param    None
*  @retval   float PTR factor
*/
float CodeToPTRFactor(uint8_t nSlotId)
{
  float valuePTR = 1.0;
  float pdResolution = 0.41;
  float currentSetting = 100.0;
  
  uint8_t nPulse;
  float pdAmpPerWatt, ledWattPerAmp, nomialWattPerAmp, derateFactor;
  
  uint16_t pulseWidth = 0;
  if( nSlotId == SLOT_A ){
    AdpdDrvRegRead(REG_AFE_CTRL_A, &pulseWidth);
  }
  else{
    AdpdDrvRegRead(REG_AFE_CTRL_B, &pulseWidth);
  }
  
  uint8_t tiaGain;  
  AdpdDrvGetAfeTiaGain(&tiaGain, nSlotId);
  if( (pulseWidth>>11) == 4){
    switch (tiaGain) {
    case 0:
      pdResolution = 0.41;
      break;
    case 1:
      pdResolution = 0.82;
      break;
    case 2:
      pdResolution = 1.64;
      break;
    case 3:
      pdResolution = 3.27;
      break;
    default:
      break;
    }
  }
  else{
    switch (tiaGain) {
    case 0:
      pdResolution = 0.58;
      break;
    case 1:
      pdResolution = 1.15;
      break;
    case 2:
      pdResolution = 2.31;
      break;
    case 3:
      pdResolution = 4.62;
      break;
    default:
      break;    
    }
  }
  
  AdpdDrvGetNumPulses(&nPulse, nSlotId);
  
  //  uint8_t currentLED;
  uint16_t currentTemp1, currentTemp2;
  float coarseLED, scaleLED, fineLED;
  AdpdDrvRegRead(REG_LED_TRIM, &currentTemp2);
  if( nSlotId == SLOT_A ){
    //    AdpdDrvGetLedCurrent(&currentLED, LED_1);
    AdpdDrvRegRead(REG_LED1_DRV, &currentTemp1);  
    fineLED = 0.74 + 0.022 *(currentTemp2&0x1F);
  }
  else{
    //    AdpdDrvGetLedCurrent(&currentLED, LED_3);
    AdpdDrvRegRead(REG_LED3_DRV, &currentTemp1);
    fineLED = 0.74 + 0.022 *(currentTemp2>>11);
  }
  
  
  coarseLED = 50.3 + 19.8 * (currentTemp1&0x000F);
  if( (currentTemp1&0x2000) == 0){
    scaleLED = 0.1;
  }
  else{
    scaleLED = 1.0;
  }
  
  currentSetting = coarseLED*scaleLED*fineLED;
  
  if( nSlotId == SLOT_A ){
    pdAmpPerWatt = 0.26;
    nomialWattPerAmp = 0.38;
    float a0, a1, a2, a3;
    a0 = 9.8976e-1;
    a1 = -5.1448e-3;
    a2 = 2.0287e-5;
    a3 = -2.9645e-8;    
    derateFactor = a0 + a1 * currentSetting + 
      a2 * currentSetting * currentSetting + 
        a3* currentSetting * currentSetting * currentSetting;
  }
  else{
    pdAmpPerWatt = 0.41;
    nomialWattPerAmp = 0.22;
    derateFactor = 1.0;
  }
  
  ledWattPerAmp = nomialWattPerAmp * derateFactor;
  
  valuePTR = pdResolution/(float)nPulse/currentSetting/pdAmpPerWatt/ledWattPerAmp;
  return valuePTR;
}

float GaussFilter(float point, float *w)
{
  float a[5] = {0.328955706,0.22608773,0.199521721,0.22608773,0.328955706};
  float filtered = 0;
  float weight = a[0] + a[1] + a[2] + a[3] + a[4];
  
  for(uint8_t i=0; i<4; i++)
  {
    w[i] = w[i+1];
  }
  w[4] = point;
  
  for(uint8_t i=0; i<5; i++)
  {
    filtered = filtered + a[i] * w[i];
  }
  filtered = filtered/weight;
  
  return filtered;
}

//float MedianFilter(float point, float *w)
//{
//  float filtered = 0;
//  for(uint8_t i=0; i<4; i++)
//  {
//    w[i] = w[i+1];
//  }
//  w[4] = point; 
//  
//  float a[5];
//  for(uint8_t i=0; i<5; i++)
//  {
//    a[i] = w[i];
//  }
//  
//  uint8_t k,j;
//  float temp;
//  for (k = 0; k < 5; k++){
//    for (j = k+1; j < 5; j++){
//      if (a[k] > a[j]){
//        temp = a[k];
//        a[k] = a[j];
//        a[j] = temp;
//      }
//    }
//  }
//  filtered = a[2];
//  
//  return filtered;
//}
