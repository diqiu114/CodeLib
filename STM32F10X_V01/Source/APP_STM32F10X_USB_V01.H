//==============================================================================================================================
#ifndef APP_STM32F10X_USB_V01_H
#define APP_STM32F10X_USB_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
extern const UINT8 CustomHID_DeviceDescriptor[];
extern const UINT8 CustomHID_ConfigDescriptor[];
extern const UINT8 CustomHID_ReportDescriptor[];
extern const UINT8 CustomHID_StringLangID[];
extern const UINT8 CustomHID_StringVendor[];
extern const UINT8 CustomHID_StringProduct[];
extern UINT8 CustomHID_StringSerial[];
extern ONE_DESCRIPTOR Device_Descriptor;
extern ONE_DESCRIPTOR Config_Descriptor;
extern ONE_DESCRIPTOR CustomHID_Report_Descriptor;
extern ONE_DESCRIPTOR CustomHID_Hid_Descriptor;
extern ONE_DESCRIPTOR String_Descriptor[];
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *Standard_GetConfiguration(UINT16 Length);
USB_RESULT Standard_SetConfiguration(void);
UINT8 *Standard_GetInterface(UINT16 Length);
USB_RESULT Standard_SetInterface(void);
UINT8 *Standard_GetDescriptorData(UINT16 Length, PONE_DESCRIPTOR pDesc);
UINT8 *Standard_GetStatus(UINT16 Length);
USB_RESULT Standard_ClearFeature(void);
USB_RESULT Standard_SetEndPointFeature(void);
USB_RESULT Standard_SetDeviceFeature(void);
UINT8 *Standard_GetDescriptorData(UINT16 Length, ONE_DESCRIPTOR *pDesc);
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Init(void);
void CustomHID_Reset(void);
void CustomHID_SetConfiguration(void);
void CustomHID_Status_In(void);
void CustomHID_Status_Out(void);

USB_RESULT CustomHID_Data_Setup(UINT8);
USB_RESULT CustomHID_NoData_Setup(UINT8);
USB_RESULT CustomHID_Get_Interface_Setting(UINT8 Interface, UINT8 AlternateSetting);
UINT8 *CustomHID_GetDeviceDescriptor(UINT16 );
UINT8 *CustomHID_GetConfigDescriptor(UINT16);
UINT8 *CustomHID_GetStringDescriptor(UINT16);
USB_RESULT CustomHID_SetProtocol(void);
UINT8 *CustomHID_GetProtocolValue(UINT16 Length);
USB_RESULT CustomHID_SetProtocol(void);
UINT8 *CustomHID_GetReportDescriptor(UINT16 Length);
UINT8 *CustomHID_GetHIDDescriptor(UINT16 Length);
//------------------------------------------------------------------------------------------------------------------------------
void USB_IntToUnicode (UINT32 value , UINT8 *pbuf , UINT8 len);
void USB_Get_SerialNum(void);

void USB_DataStageOut(void);
void USB_DataStageIn(void);
void USB_NoData_Setup0(void);
void USB_Data_Setup0(void);
UINT8 USB_Setup0_Process(void);
UINT8 USB_In0_Process(void);
UINT8 USB_Out0_Process(void);
UINT8 USB_Post0_Process(void);
void USB_NOP_Process(void);
void USB_SendZeroLength(void);
//------------------------------------------------------------------------------------------------------------------------------
void USB_CTR_LP(void);//????????????????????
void USB_CTR_HP(void);//????????????????????
void USB_Control(UINT8 Index);
void USB_PowerOn(void);
void USB_PowerOff(void);
void USB_Resume_Init(void);
void USB_Resume(USB_RESUME_STATE eResumeSetVal);
//------------------------------------------------------------------------------------------------------------------------------
void USB_ReadBUF(UINT8 EPIndex);
void USB_SendBUF(UINT8 EPIndex);//????BUF????????????????
void USB_WaitSend(void);//??????????????????????????,????1??
void USB_HW_SendString(UINT8 *s,UINT16 Count);//????????????????????????
void USB_TXTimeOut_Timer(void);//every 100us,send timeout control;??????????????
void USB_Send_Timer(void);//????????????,every 1ms(??????????????
//==============================================================================================================================
#endif
//==============================================================================================================================
