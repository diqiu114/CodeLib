/**

    ***************************************************************************

      @file         adpd_app.c

      @author       DANFINSWE

      @version      V1.0.0

      @date         2020-08-10

      @brief        application layer to use ADI ADPD188.



*/


/* Includes -----------------------------------------------------------------*/


#include "adpd_app.h"
/*
                                 * Flow diagram of the code *
                                 ----------------------------
                                 | Hardware initializations |
                                 ----------------------------
                                 |  Data ready callback     |
                                 ----------------------------
                                 |Soft reset the ADPD device|
                                 |Initialize the ADPD driver|
                                 ----------------------------
                                 | Load the default config  |
                                 | and verify it            |
                                 ----------------------------
                                 | Write standard value of  |
                                 | clock registers          |
                                 ----------------------------
                                          while(1)
                                 ----------------------------
                                 |     Driver bring up      |
                                 ----------------------------
*/





/**

  *  @brief    Main program.

  *  @param    None

  *  @retval   None

*/

#define ERROR_TIMES 2
/* Macros -------------------------------------------------------------------*/

/*    Uncomment  the following macro to use LSB code as output */
#define ADPD188BI_PTR

/*    Uncomment  the following macro to use multi ceriteria read temperature and humidity */
//#define ADPD188BI_MULTICRITEERIA


float ratio_ptr;
float ratio_threshold = 1.5;  

float blue_window[5], ir_window[5];
#ifdef ADPD188BI_PTR
float blue_threshold = 1.7;  
float ir_threshold = 0.7;
float blue_value, ir_value;  
float blue_ptr_factor, ir_ptr_factor;
#else
  uint32_t blue_threshold, ir_threshold;
  uint32_t blue_value, ir_value; 
#endif

Adpd_app::Adpd_app(void)
{
  error_times = 0;
}

Adpd_app::~Adpd_app(void)
{

}

bool Adpd_app::get_data(dataADPD* sensorData)
{
  int gnAdpdDataReady = 0;
  /* Read the size of the data available in the FIFO */
  if (AdpdDrvGetParameter(ADPD_FIFOLEVEL, &(APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize)) != ADI_HAL_OK)
  {
    if (error_times <= ERROR_TIMES)
    {
      error_times ++;
    }
    return ADI_HAL_ERROR;
  }
  if(APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize >= APP_ADPD_STATE_NORMAL.nAdpdDataSetSize) 
  {
    error_times = 0;
    gnAdpdDataReady = 1;
  }
  else
  {
    if (error_times <= ERROR_TIMES)
    {
      error_times ++;
    }
  }
  if(gnAdpdDataReady==1)
  {
    gnAdpdDataReady = 0; 
    //      sampleIndex++;

    /* Read FIFO data */
    for(uint8_t times=0; times<APP_ADPD_STATE_NORMAL.nAdpdFifoLevelSize/APP_ADPD_STATE_NORMAL.nAdpdDataSetSize; times++)
    {
      *sensorData=AdpdDataRead(OPTICAL);

#ifdef ADPD188BI_PTR
      blue_value = GaussFilter(((*sensorData).dataSlotA-APP_ADPD_STATE_NORMAL.blueOffset)*blue_ptr_factor, blue_window);
      ir_value = GaussFilter(((*sensorData).dataSlotB-APP_ADPD_STATE_NORMAL.irOffset)*ir_ptr_factor, ir_window);        
      if((blue_value>0.5) && (ir_value>0.3))
      {
        ratio_ptr = blue_value/ir_value;
      }
      else
      {
      ratio_ptr = 1.0;
      }
  //printf("L,%d,%f,%f,%f\r\n",times, blue_value, ir_value, ratio_ptr );
#else
    blueValue = (*sensorData).dataSlotA;
    irValue = (*sensorData).dataSlotB;
    ratioPTR = (float)blueValue/(float)irValue;       
    //printf("L%d,%d,%f\r\n", (*sensorData).dataSlotA, (*sensorData).dataSlotB, ratioPTR);
#endif        
    }

    if( (blue_value>blue_threshold) && (ir_value>ir_threshold) && (ratio_ptr>ratio_threshold))
    {
      /*alarm operation here*/
      //PlayOne();
      //printf("alarm.");
    }

#ifdef ADPD188BI_MULTICRITEERIA 
    //if(sampleIndex==15)
    {
      // sampleIndex = 0;
      *sensorData=AdpdGetTHData();
      //printf("T%d,%d\r\n", (*sensorData).dataSlotA, (*sensorData).dataSlotB);
    }
#endif
  }
  return ADI_HAL_ERROR;
}
void Adpd_app::init(void)
{
  unsigned short check_id;
  AdpdConfiguration(OPTICAL);
  AdpdDrvSoftReset();
  AdpdDrvRegRead(0x08,&check_id);
  if(check_id == 0x0A16)
  {
    AdpdConfiguration(OPTICAL);
    AdpdClockCalibration();
    blue_ptr_factor = CodeToPTRFactor(SLOT_A); 
    ir_ptr_factor =  CodeToPTRFactor(SLOT_B);
    //printf("bluePTRFactor:%f,irPTRFactor:%f.",blue_ptr_factor,ir_ptr_factor);
    AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);
  }

}


bool Adpd_app::is_error()
{
  if(error_times > ERROR_TIMES)
  {   
    init();
    return true;
  }
  return false;
}


