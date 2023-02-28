#ifndef __SMOKEDETECT__H
#define __SMOKEDETECT__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "AdpdDrv.h"
#include "Common.h"
#define UTIL_TICKS_PER_SEC    1000
  
//#define FOUR_HZ_FOUR_MEAN_FOR_PULESE         //4Hz采样率、平均数4、AB槽输出4脉冲
#define TWO_HZ_TWO_MEAN_TWO_PULESE           //2Hz采样率、平均数2、AB槽输出2脉冲           
//#define EIGHT_HZ_EIGHT_MEAN_EIGHT_PULESE     //8Hz采样率、平均数8、AB槽输出8脉冲 

typedef enum {
  BLUE_LED = 0x00,
  IR_LED = 0x01
}LED_WAVELENGTH;

typedef enum {
  OPTICAL = 0x00,
  TEMP_HUMI = 0x01
}CONFIG_TYPE;

typedef struct
{
  uint32_t dataSlotA;
  uint32_t dataSlotB;
}dataADPD;

typedef struct
{
  uint32_t blueOffset;
  uint32_t irOffset;
  uint32_t nAdpdDataSetSize;
  uint16_t nAdpdFifoLevelSize;
  
} APP_ADPD_STATE_NORMAL_t;


extern APP_ADPD_STATE_NORMAL_t  APP_ADPD_STATE_NORMAL;

extern uint32_t dcfg_org_188[];


uint8_t  AdpdConfiguration(CONFIG_TYPE cType);
void LoadDefaultConfig(const uint32_t *cfg);
void VerifyDefaultConfig(const uint32_t *cfg);


uint8_t Calibrate32KClock(void);
void Calibrate32MClock(void);
uint8_t AdpdClockCalibration(void);

dataADPD AdpdDataRead(CONFIG_TYPE cType);
dataADPD AdpdGetTHData(void);

float CodeToPTRFactor(uint8_t nSlotId);

float GaussFilter(float point, float *w);
float MedianFilter(float point, float *w);
#ifdef __cplusplus
}
#endif

#endif


