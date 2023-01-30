//==============================================================================================================================
#ifndef UG_STM32F10X_USB_V01_H
#define UG_STM32F10X_USB_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
extern const UINT8 UG_CustomHID_DeviceDescriptor[];
extern const UINT8 UG_CustomHID_ConfigDescriptor[];
extern const UINT8 UG_CustomHID_ReportDescriptor[];
extern const UINT8 UG_CustomHID_StringLangID[];
extern const UINT8 UG_CustomHID_StringVendor[];
extern const UINT8 UG_CustomHID_StringProduct[];
extern UINT8 UG_CustomHID_StringSerial[];
extern ONE_DESCRIPTOR UG_Device_Descriptor;
extern ONE_DESCRIPTOR UG_Config_Descriptor;
extern ONE_DESCRIPTOR UG_CustomHID_Report_Descriptor;
extern ONE_DESCRIPTOR UG_CustomHID_Hid_Descriptor;
extern ONE_DESCRIPTOR UG_String_Descriptor[];
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *UG_Standard_GetConfiguration(UINT16 Length);
USB_RESULT UG_Standard_SetConfiguration(void);
UINT8 *UG_Standard_GetInterface(UINT16 Length);
USB_RESULT UG_Standard_SetInterface(void);
UINT8 *UG_Standard_GetDescriptorData(UINT16 Length, PONE_DESCRIPTOR pDesc);
UINT8 *UG_Standard_GetStatus(UINT16 Length);
USB_RESULT UG_Standard_ClearFeature(void);
USB_RESULT UG_Standard_SetEndPointFeature(void);
USB_RESULT UG_Standard_SetDeviceFeature(void);
UINT8 *UG_Standard_GetDescriptorData(UINT16 Length, ONE_DESCRIPTOR *pDesc);
//------------------------------------------------------------------------------------------------------------------------------
void UG_CustomHID_Init(void);
void UG_CustomHID_Reset(void);
void UG_CustomHID_SetConfiguration(void);
void UG_CustomHID_Status_In (void);
void UG_CustomHID_Status_Out (void);

USB_RESULT UG_CustomHID_Data_Setup(UINT8);
USB_RESULT UG_CustomHID_NoData_Setup(UINT8);
USB_RESULT UG_CustomHID_Get_Interface_Setting(UINT8 Interface, UINT8 AlternateSetting);
UINT8 *UG_CustomHID_GetDeviceDescriptor(UINT16 );
UINT8 *UG_CustomHID_GetConfigDescriptor(UINT16);
UINT8 *UG_CustomHID_GetStringDescriptor(UINT16);
USB_RESULT UG_CustomHID_SetProtocol(void);
UINT8 *UG_CustomHID_GetProtocolValue(UINT16 Length);
USB_RESULT UG_CustomHID_SetProtocol(void);
UINT8 *UG_CustomHID_GetReportDescriptor(UINT16 Length);
UINT8 *UG_CustomHID_GetHIDDescriptor(UINT16 Length);
//------------------------------------------------------------------------------------------------------------------------------
void UG_USB_IntToUnicode (UINT32 value , UINT8 *pbuf , UINT8 len);
void UG_USB_Get_SerialNum(void);

void UG_USB_DataStageOut(void);
void UG_USB_DataStageIn(void);
void UG_USB_NoData_Setup0(void);
void UG_USB_Data_Setup0(void);
UINT8 UG_USB_Setup0_Process(void);
UINT8 UG_USB_In0_Process(void);
UINT8 UG_USB_Out0_Process(void);
UINT8 UG_USB_Post0_Process(void);
void UG_USB_NOP_Process(void);
void UG_USB_SendZeroLength(void);
//------------------------------------------------------------------------------------------------------------------------------
void UG_USB_CTR_LP(void);//�˵�����ȼ��жϴ���
void UG_USB_CTR_HP(void);//�˵�����ȼ��жϴ���
void UG_USB_Control(UINT8 Index);
void UG_USB_PowerOn(void);
void UG_USB_PowerOff(void);
void UG_USB_Resume_Init(void);
void UG_USB_Resume(USB_RESUME_STATE eResumeSetVal);
//------------------------------------------------------------------------------------------------------------------------------
void UG_USB_ReadBUF(UINT8 EPIndex);
void UG_USB_SendBUF(UINT8 EPIndex);//����BUF���ж�������ã�
void UG_USB_WaitSend(void);//�ȴ�������ϣ��ж�����ã�,��ʱ1��
void UG_USB_HW_SendString(UINT8 *s,UINT16 Count);//���͵�Ӳ�����ж�����ã�
void UG_USB_TXTimeOut_Timer(void);//every 100us,send timeout control;���ж��ڵ��ã�
void UG_USB_Send_Timer(void);//���Ͷ�ʱ�¼�,every 1ms(�ж�������ã�
//==============================================================================================================================
#endif
//==============================================================================================================================
