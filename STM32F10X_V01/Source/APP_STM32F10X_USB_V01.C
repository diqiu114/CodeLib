//==============================================================================================================================
#include "Global.h"
//==============================================================================================================================
#if SDK_USB_COUNT
//------------------------------------------------------------------------------------------------------------------------------
const UINT8 CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC]=
        {
        0x12,                       //bLength
        USB_DEVICE_DESCRIPTOR,      //bDescriptorType
        0x00,                       //bcdUSB
        0x02,
        0x00,                       //bDeviceClass
        0x00,                       //bDeviceSubClass
        0x00,                       //bDeviceProtocol
        0x40,                       //bMaxPacketSize 64
        SDK_USB_VID&0xff,           //idVendor
        SDK_USB_VID>>8,
        SDK_USB_PID&0xff,           //idProduct
        SDK_USB_PID>>8,
        0x00,                       //bcdDevice rel. 2.00
        0x02,
        1,                          //Index of string descriptor describing manufacturer
        2,                          //Index of string descriptor describing product
        3,                          //Index of string descriptor describing the device serial number
        0x01                        //bNumConfigurations
        };

const UINT8 CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =//Len=0x29,All Descriptors (Configuration, Interface, Endpoint, Class, Vendor
        {
        0x09, //bLength: Configuation Descriptor size
        USB_CONFIG_DESCRIPTOR,//bDescriptorType: Configuration
        CUSTOMHID_SIZ_CONFIG_DESC,
        0x00,         //wTotalLength: Bytes returned
        0x01,         //bNumInterfaces: 1 interface
        0x01,         //bConfigurationValue: Configuration value
        0x00,         //iConfiguration: Index of string descriptor describing the configuration
        0xC0,		      //原鼠标0xE0,bmAttributes: bus powered
        0x32,         //MaxPower 100 mA: this current is used for detecting Vbus
        //Descriptor of CustomHID interface
        0x09,         //bLength: Interface Descriptor size
        USB_INTERFACE_DESCRIPTOR,//bDescriptorType: Interface descriptor type
        0x00,         //bInterfaceNumber: Number of Interface
        0x00,         //bAlternateSetting: Alternate setting
        0x02,         //bNumEndpoints
        0x03,         //bInterfaceClass: HID
        0x00,         //bInterfaceSubClass : 1=BOOT, 0=no boot
        0x00,         //nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
        0,            //iInterface: Index of string descriptor
        //Descriptor of CustomHID HID
        0x09,         //bLength: HID Descriptor size
        HID_DESCRIPTOR_TYPE, //bDescriptorType: HID
        0x10,		      //原鼠标0x00,bcdHID: HID Class Spec release number
        0x01,
        0x00,         //bCountryCode: Hardware target country
        0x01,         //bNumDescriptors: Number of HID class descriptors to follow
        0x22,         //bDescriptorType
        CUSTOMHID_SIZ_REPORT_DESC,//wItemLength: Total length of Report descriptor
        0x00,
        //Descriptor of CustomHID endpoint
        0x07,         //bLength: Endpoint Descriptor size
        USB_ENDPOINT_DESCRIPTOR, //bDescriptorType:
        0x82,         //原鼠标是0x81,bEndpointAddress: Endpoint Address (IN)
        0x03,         //bmAttributes: Bulk
        USB_EP1_Size, //wMaxPacketSize: 64 Byte max
        0x00,
        0x01,         //bInterval: Polling Interval (1 ms)
	      0x07,	        //bLength: Endpoint Descriptor size
        USB_ENDPOINT_DESCRIPTOR,	//bDescriptorType:	Endpoint descriptor type
        0x01,	        //bEndpointAddress:Endpoint1 Address (OUT)
        0x03,	        //bmAttributes: Interrupt endpoint
        USB_EP2_Size, //wMaxPacketSize: 64 Bytes max
        0x00,
        0x01,	        //bInterval: Polling Interval (1 ms)
        };
const UINT8 CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] = //Len=0x21
        { 
        0x05, 0x8c, //USAGE_PAGE (ST Page)
        0x09, 0x01, //USAGE (Demo Kit)
        0xa1, 0x01, //COLLECTION (Application)
        // The Input report 
        0x09,0x03, // USAGE ID - Vendor defined 
        0x15,0x00, // LOGICAL_MINIMUM (0) 
        0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
        0x75,0x08, // REPORT_SIZE (8bit) 
        0x95,0x40, // REPORT_COUNT (64Byte) 
        0x81,0x02, // INPUT (Data,Var,Abs) 
        // The Output report 
        0x09,0x04, // USAGE ID - Vendor defined 
        0x15,0x00, // LOGICAL_MINIMUM (0) 
        0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255) 
        0x75,0x08, // REPORT_SIZE (8bit) 
        0x95,0x40, // REPORT_COUNT (64Byte) 
        0x91,0x02, // OUTPUT (Data,Var,Abs) 
        0xc0       //END_COLLECTION
        }; //CustomHID_ReportDescriptor

//USB String Descriptors (optional)
const UINT8 CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =//Len=0x04
        {CUSTOMHID_SIZ_STRING_LANGID, USB_STRING_DESCRIPTOR, 0x09, 0x04};

//制造商字符串,Manufacturer: "www.waveshare.net"
const UINT8 CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =//Len=0x28
        {
        CUSTOMHID_SIZ_STRING_VENDOR, USB_STRING_DESCRIPTOR,
        'A', 0, 'I', 0, 'M', 0, 'Y', 0, 'U', 0, 'N', 0, 'I', 0, 'O', 0,
        'N', 0, 'T', 0, 'E', 0, 'C', 0, 'H', 0, 'N', 0, 'O', 0, 'L', 0,
        'O', 0, 'G', 0, 'Y',
        };
//产品名称
const UINT8 CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =//Len=0x20
       {
        CUSTOMHID_SIZ_STRING_PRODUCT,USB_STRING_DESCRIPTOR,
	      'A', 0, 'A', 0, 'M', 0, ' ', 0, 'X', 0, '-', 0, 'D', 0,
        'A', 0, 'N', 0, 'C', 0, 'E', 0, ' ', 0, 'H', 0, 'I', 0,
        'D', 0
        };
//产品名称
UINT8 CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =//Len=0x1A
        {CUSTOMHID_SIZ_STRING_SERIAL,USB_STRING_DESCRIPTOR,'A', 0, 'P', 0, 'M', 0,'3', 0,'2', 0, '1', 0, '0', 0 };
//------------------------------------------------------------------------------------------------------------------------------
ONE_DESCRIPTOR Device_Descriptor ={(UINT8*)CustomHID_DeviceDescriptor, CUSTOMHID_SIZ_DEVICE_DESC };
ONE_DESCRIPTOR Config_Descriptor ={(UINT8*)CustomHID_ConfigDescriptor, CUSTOMHID_SIZ_CONFIG_DESC};
ONE_DESCRIPTOR CustomHID_Report_Descriptor ={(UINT8 *)CustomHID_ReportDescriptor, CUSTOMHID_SIZ_REPORT_DESC};
ONE_DESCRIPTOR CustomHID_Hid_Descriptor ={(UINT8*)CustomHID_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,CUSTOMHID_SIZ_HID_DESC};
ONE_DESCRIPTOR String_Descriptor[4] =
        {
          {(UINT8*)CustomHID_StringLangID, CUSTOMHID_SIZ_STRING_LANGID},{(UINT8*)CustomHID_StringVendor, CUSTOMHID_SIZ_STRING_VENDOR},
          {(UINT8*)CustomHID_StringProduct, CUSTOMHID_SIZ_STRING_PRODUCT},{(UINT8*)CustomHID_StringSerial, CUSTOMHID_SIZ_STRING_SERIAL}
        };
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *Standard_GetConfiguration(UINT16 Length)
{
  if (Length == 0){DUSB.Device_Info.Ctrl_Info.Usb_wLength = sizeof(DUSB.Device_Info.Current_Configuration); return 0;}
  USB_NOP_Process();
  return (UINT8 *)&DUSB.Device_Info.Current_Configuration;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetConfiguration(void)
{
  if ((DUSB.Device_Info.USBwValues.LH.L <=1) && (DUSB.Device_Info.USBwValues.LH.H ==0x00)  && (DUSB.Device_Info.USBwIndexs.VAL == 0x0000)) //call Back usb spec 2.0
  {
    DUSB.Device_Info.Current_Configuration = DUSB.Device_Info.USBwValues.LH.L;
    CustomHID_SetConfiguration();
    return USB_SUCCESS;
  }
  else
  {return USB_UNSUPPORT;}
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *Standard_GetInterface(UINT16 Length)
{
  if (Length == 0)
  {DUSB.Device_Info.Ctrl_Info.Usb_wLength =sizeof(DUSB.Device_Info.Current_AlternateSetting); return 0;}
  USB_NOP_Process();
  return (UINT8 *)&DUSB.Device_Info.Current_AlternateSetting;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetInterface(void)
{
  USB_RESULT Re;
  //Test if the specified Interface and Alternate Setting are supported by the application Firmware
  Re =CustomHID_Get_Interface_Setting(DUSB.Device_Info.USBwIndexs.LH.L,DUSB.Device_Info.USBwValues.LH.L);
  if(DUSB.Device_Info.Current_Configuration != 0)
  {
    if ((Re != USB_SUCCESS) || DUSB.Device_Info.USBwIndexs.LH.H  || DUSB.Device_Info.USBwValues.LH.H)
    {return  USB_UNSUPPORT;}
    else if(Re == USB_SUCCESS)
    {USB_NOP_Process();DUSB.Device_Info.Current_Interface = DUSB.Device_Info.USBwIndexs.LH.L;DUSB.Device_Info.Current_AlternateSetting = DUSB.Device_Info.USBwValues.LH.L; return USB_SUCCESS;}
  }
  return USB_UNSUPPORT;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *Standard_GetStatus(UINT16 Length)
{
  if (Length == 0){DUSB.Device_Info.Ctrl_Info.Usb_wLength = 2;return 0;}
  DUSB.StatusInfo.VAL = 0;
  if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT))
  {
    DUSB.StatusInfo.BIT.B1=(DUSB.Device_Info.Current_Feature&0x20 ? 1:0);//Remote Wakeup enabled 
    DUSB.StatusInfo.BIT.B0=(DUSB.Device_Info.Current_Feature&0x40 ? 1:0);
  }
  else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_INTERFACE_RECIPIENT))//Interface Status
  {return (UINT8 *)&DUSB.StatusInfo.VAL;}
  else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_ENDPOINT_RECIPIENT))//Get EndPoint Status
  {
    if (DUSB.Device_Info.USBwIndexs.BIT.B7)// IN endpoint
    {if(USB.EPR_BIT[DUSB.Device_Info.USBwIndexs.B4P.P0].TXSTAT==USB_EPR_STAT_STALL) DUSB.StatusInfo.LH.L|=0x01;} //IN Endpoint stalled        
    else//OUT endpoint
    {if(USB.EPR_BIT[DUSB.Device_Info.USBwIndexs.B4P.P0].RXSTAT==USB_EPR_STAT_STALL) DUSB.StatusInfo.LH.L|=0x01;}//OUT Endpoint stalled 
  }
  else
  {return NULL;}
  USB_NOP_Process();
  return (UINT8 *)&DUSB.StatusInfo;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_ClearFeature(void)//Clear or disable a specific feature.
{
  if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT))
  {DUSB.Device_Info.Current_Feature&=0xDF; return USB_SUCCESS;}
  else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_ENDPOINT_RECIPIENT))
  {
    if ((DUSB.Device_Info.USBwValues.VAL != 0x0000) || (DUSB.Device_Info.USBwIndexs.LH.H != 0x0000))  return USB_UNSUPPORT;
    DUSB.REP =  DUSB.Device_Info.USBwIndexs.LH.L&0x7F;
    if ((DUSB.REP >=USB_EPCount) || ((DUSB.Device_Info.USBwIndexs.BIT.B7 ? USB.EPR_BIT[DUSB.REP].TXSTAT:USB.EPR_BIT[DUSB.REP].RXSTAT) == 0) || (DUSB.Device_Info.Current_Configuration == 0))
    {return USB_UNSUPPORT;}

    if ( DUSB.Device_Info.USBwIndexs.LH.L & 0x80)
    {
			if(USB.EPR_BIT[DUSB.REP].TXSTAT==USB_EPR_STAT_STALL) 
      {
				if(USB.EPR_BIT[DUSB.REP].TXDTOG)USB_ToggleDTOG(DUSB.REP,1);
				USB_SetTXSTAT(DUSB.REP,USB_EPR_STAT_VALID); 
      }
    }
    else
    {
			if(USB.EPR_BIT[DUSB.REP].RXSTAT==USB_EPR_STAT_STALL) 
      {
        if (DUSB.REP == 0)
        {USB_SetRXCount(0,DUSB.EPSIZE[0]);}//After clear the STALL, enable the default endpoint receiver
        else
        {if(USB.EPR_BIT[DUSB.REP].RXDTOG)USB_ToggleDTOG(DUSB.REP,0);}
				USB_SetRXSTAT(DUSB.REP,USB_EPR_STAT_VALID); 
      }
    }
    USB_NOP_Process();
    return USB_SUCCESS;
  }
  return USB_UNSUPPORT;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetEndPointFeature(void)//Set or enable a specific feature of EndPoint
{
  DUSB.REP = DUSB.Device_Info.USBwIndexs.LH.L & 0x7F;
  if (DUSB.REP >= USB_EPCount || DUSB.Device_Info.USBwValues.VAL || (DUSB.Device_Info.USBwIndexs.BIT.B7 ? USB.EPR_BIT[DUSB.REP].TXSTAT:USB.EPR_BIT[DUSB.REP].RXSTAT) == 0x00 || DUSB.Device_Info.Current_Configuration == 0x00)
  {return USB_UNSUPPORT;}
  else
  {if (DUSB.Device_Info.USBwIndexs.LH.L & 0x80){USB_SetTXSTAT(DUSB.REP,USB_EPR_STAT_STALL);} else {USB_SetRXSTAT(DUSB.REP,USB_EPR_STAT_STALL);}}
  USB_NOP_Process();
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetDeviceFeature(void)
{
  DUSB.Device_Info.Current_Feature|=0x20; USB_NOP_Process();
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *Standard_GetDescriptorData(UINT16 Length, ONE_DESCRIPTOR *pDesc)
{
  if (Length == 0){DUSB.Device_Info.Ctrl_Info.Usb_wLength =pDesc->Descriptor_Size- DUSB.Device_Info.Ctrl_Info.Usb_wOffset; return 0;}
  return pDesc->Descriptor+DUSB.Device_Info.Ctrl_Info.Usb_wOffset;
}
//==============================================================================================================================
void CustomHID_Init(void)
{
	USB.MDL=0x00; DUSB.Device_Info.ControlState=2; DUSB.Device_Info.Current_Configuration = 0;//configuration=0是什么配置？
  USB_Get_SerialNum();//Update the serial number string descriptor with the data from the unique ID
  USB_PowerOn();//Connect the device
	USB_ISTR=0x0000;USB_CNTR=0xBF00;//clear pending interrupts
  DUSB.DEVState = USB_STATE_UNCONNECTED;
}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Reset(void)
{
  DUSB.Device_Info.Current_Configuration = 0;//Set CustomHID_DEVICE as not configured 
  DUSB.Device_Info.Current_Interface = 0;//the default Interface
  DUSB.Device_Info.Current_Feature = CustomHID_ConfigDescriptor[7];//Current Feature initialization
  USB_BUFTAB=USB_BUFTAB_Value&0xFFF8;
	//Initialize Endpoint 0
	USB_SetEPType(0,USB_EPR_TYPE_CONTROL);
	USB_SetTXSTAT(0,USB_EPR_STAT_STALL);
	USB.CH[0].RXADDR=(DUSB.RXADDR[0]-BASE_USBRAM)>>1;
	USB.CH[0].TXADDR=(DUSB.TXADDR[0]-BASE_USBRAM)>>1;
	USB_Clear_KIND(0);
	USB_SetRXCount(0,DUSB.EPSIZE[0]);
	USB_SetRXSTAT(0,USB_EPR_STAT_VALID);
  //Initialize Endpoint 1 从机收
	USB_SetEPType(1,USB_EPR_TYPE_BULK);
  USB.CH[1].RXADDR =(DUSB.RXADDR[1]-BASE_USBRAM)/2;
	USB_SetRXCount(1,DUSB.EPSIZE[1]);//这里数据长度不能设为变量，只能是常量
	USB_SetRXSTAT(1, USB_EPR_STAT_VALID);
  //Initialize Endpoint 2 从机发
  USB_SetEPType(2,USB_EPR_TYPE_BULK);
  USB.CH[2].TXADDR=(DUSB.TXADDR[2]-BASE_USBRAM)/2;
	USB.CH[2].TXCOUNT=DUSB.EPSIZE[2];//就是因为在这里设置了，使得每次数据长度都不能超过设置的数
  USB_SetTXSTAT(2,USB_EPR_STAT_DIS);
	USB_SetTXSTAT(2,USB_EPR_STAT_NAK);
  // Set this device to response on default address
  USB_SetAddress(0);
  DUSB.DEVState = USB_STATE_ATTACHED;
}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_SetConfiguration(void)
{
  if (DUSB.Device_Info.Current_Configuration != 0)  DUSB.DEVState = USB_STATE_CONFIGURED;
}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Status_In(void)
{}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Status_Out (void)
{}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_Data_Setup(UINT8 RequestNo)
{
  UINT8 *(*CopyRoutine)(UINT16);

  CopyRoutine = NULL;
  if ((RequestNo == USB_GET_DESCRIPTOR) && (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_INTERFACE_RECIPIENT)) && (DUSB.Device_Info.USBwIndexs.LH.L == 0))
  {
    if (DUSB.Device_Info.USBwValues.LH.H == USB_REPORT_DESCRIPTOR)
    {CopyRoutine = CustomHID_GetReportDescriptor;}
    else if (DUSB.Device_Info.USBwValues.LH.H == HID_DESCRIPTOR_TYPE)
    {CopyRoutine = CustomHID_GetHIDDescriptor;}
  }
  else if ((USB_Type_Recipient == (USB_CLASS_REQUEST | USB_INTERFACE_RECIPIENT)) && RequestNo == USB_GET_PROTOCOL)
  { CopyRoutine = CustomHID_GetProtocolValue; }

  if (CopyRoutine == NULL) return USB_UNSUPPORT;
  DUSB.Device_Info.Ctrl_Info.CopyData = CopyRoutine;
  DUSB.Device_Info.Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_NoData_Setup(UINT8 RequestNo)
{
  return ((USB_Type_Recipient == (USB_CLASS_REQUEST | USB_INTERFACE_RECIPIENT))  && (RequestNo == USB_SET_PROTOCOL) ? CustomHID_SetProtocol():USB_UNSUPPORT);
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetDeviceDescriptor(UINT16 Length)
{
  return Standard_GetDescriptorData(Length,&Device_Descriptor); 
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetConfigDescriptor(UINT16 Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetStringDescriptor(UINT16 Length)
{
  return (DUSB.Device_Info.USBwValues.LH.L > 4 ? NULL:Standard_GetDescriptorData(Length, &String_Descriptor[DUSB.Device_Info.USBwValues.LH.L]));
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetReportDescriptor(UINT16 Length)
{
  return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetHIDDescriptor(UINT16 Length)
{
  return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_Get_Interface_Setting(UINT8 Interface, UINT8 AlternateSetting)
{
  return (AlternateSetting||Interface  ? USB_UNSUPPORT:USB_SUCCESS);
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_SetProtocol(void)
{
  DUSB.ProtocolValue = DUSB.Device_Info.USBwValues.LH.L; return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 *CustomHID_GetProtocolValue(UINT16 Length)
{
  if (Length == 0){DUSB.Device_Info.Ctrl_Info.Usb_wLength = 1;  return NULL;}  else  {return (UINT8 *)(&DUSB.ProtocolValue);}
}
//==============================================================================================================================
void USB_IntToUnicode (UINT32 value , UINT8 *pbuf , UINT8 len)
{
  for(Var[0] = 0 ; Var[0] < len ; Var[0] ++)
  {pbuf[ 2* Var[0]]=(value >> 28) + ( (value >> 28) < 0xA ?  '0': 'A' - 10 );  value = value << 4; pbuf[ 2* Var[0] + 1] = 0;}
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Get_SerialNum(void)
{
  if((DES.UID[0]+DES.UID[2])==0x00000000)return;
  USB_IntToUnicode (DES.UID[0]+DES.UID[2], &CustomHID_StringSerial[2] , 8);
  USB_IntToUnicode (DES.UID[1], &CustomHID_StringSerial[18], 4);
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_DataStageOut(void)
{
  UINT8 *Buffer;
  if (DUSB.Device_Info.Ctrl_Info.CopyData && DUSB.Device_Info.Ctrl_Info.Usb_wLength)
  {
    if (DUSB.Device_Info.Ctrl_Info.PacketSize > DUSB.Device_Info.Ctrl_Info.Usb_wLength)
    { DUSB.Device_Info.Ctrl_Info.PacketSize = DUSB.Device_Info.Ctrl_Info.Usb_wLength;}

    Buffer = (*DUSB.Device_Info.Ctrl_Info.CopyData)(DUSB.Device_Info.Ctrl_Info.PacketSize);
    DUSB.Device_Info.Ctrl_Info.Usb_wLength -= DUSB.Device_Info.Ctrl_Info.PacketSize; DUSB.Device_Info.Ctrl_Info.Usb_wOffset += DUSB.Device_Info.Ctrl_Info.PacketSize;
    USB_GetData(0,Buffer,DUSB.Device_Info.Ctrl_Info.PacketSize);
  }

  if (DUSB.Device_Info.Ctrl_Info.Usb_wLength != 0)
  {
		USB.CH[0].TXCOUNT=0x0000;
		DUSB.RXSTAT=USB_EPR_STAT_VALID; DUSB.TXSTAT=USB_EPR_STAT_VALID;// re-enable for next data reception , Expect the host to abort the data OUT stage 
  }
  /* Set the next State*/
  if (DUSB.Device_Info.Ctrl_Info.Usb_wLength >= DUSB.Device_Info.Ctrl_Info.PacketSize)
  {
    DUSB.Device_Info.ControlState = OUT_DATA;
  }
  else
  {
    if (DUSB.Device_Info.Ctrl_Info.Usb_wLength > 0)
    {
      DUSB.Device_Info.ControlState = LAST_OUT_DATA;
    }
    else if (DUSB.Device_Info.Ctrl_Info.Usb_wLength == 0)
    {
      DUSB.Device_Info.ControlState = WAIT_STATUS_IN;
      USB_SendZeroLength();
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_DataStageIn(void)	 //这个函数完成描述符的输出准备
{
  UINT8 *DataBuffer;
  UINT32 Length;

  if ((DUSB.Device_Info.Ctrl_Info.Usb_wLength == 0) && (DUSB.Device_Info.ControlState == LAST_IN_DATA))
  {
    if(USB_MulMaxPacketSize ==1)//No more data to send and empty packet 
    {USB_SendZeroLength(); DUSB.Device_Info.ControlState = LAST_IN_DATA;USB_MulMaxPacketSize = 0;}
    else //No more data to send so STALL the TX Status
    {
      DUSB.Device_Info.ControlState = WAIT_STATUS_OUT;
			DUSB.TXSTAT=USB_EPR_STAT_STALL;
    }
    return;
  }

  Length = DUSB.Device_Info.Ctrl_Info.PacketSize;		
  DUSB.Device_Info.ControlState = (DUSB.Device_Info.Ctrl_Info.Usb_wLength <= Length) ? LAST_IN_DATA : IN_DATA;

  if (Length > DUSB.Device_Info.Ctrl_Info.Usb_wLength) Length = DUSB.Device_Info.Ctrl_Info.Usb_wLength;
  DataBuffer = (*DUSB.Device_Info.Ctrl_Info.CopyData)(Length);	 //这个是用户取得用户描述符缓冲区的地址，这里共有18字节

	USB_SetData(0,DataBuffer,Length);//这个函数将设备描述符复制到用户的发送缓冲区

	USB.CH[0].TXCOUNT=Length;//设置发送字节的数目
  DUSB.Device_Info.Ctrl_Info.Usb_wLength -= Length;		 //等于0
  DUSB.Device_Info.Ctrl_Info.Usb_wOffset += Length;		 //偏移到18
  DUSB.TXSTAT=USB_EPR_STAT_VALID;	DUSB.RXSTAT=USB_EPR_STAT_VALID;//Expect the host to abort the data IN stage,端点使能发送，主要主机的IN令牌包一来，SIE就会将描述符返回给主机,实际上接收也有效，主机可取消IN
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_NoData_Setup0(void)
{
  USB_RESULT Result = USB_UNSUPPORT;

  if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT))
  {
    if (DUSB.Device_Info.USBbRequest == USB_SET_CONFIGURATION)
    {Result = Standard_SetConfiguration();}
    else if (DUSB.Device_Info.USBbRequest == USB_SET_ADDRESS)//SET ADDRESS,Device Address should be 127 or less
    {
      if ((DUSB.Device_Info.USBwValues.VAL > 127) || (DUSB.Device_Info.USBwIndexs.VAL != 0x0000) || (DUSB.Device_Info.Current_Configuration != 0x00))
      {DUSB.Device_Info.ControlState = STALLED;  return;}
      else
      {
        Result = USB_SUCCESS;
      }
    }
    else if (DUSB.Device_Info.USBbRequest == USB_SET_FEATURE)//SET FEATURE for Device
    {
      if ((DUSB.Device_Info.USBwValues.LH.L == USB_DEVICE_REMOTE_WAKEUP) && (DUSB.Device_Info.USBwIndexs.VAL == 0x0000))
      {Result = Standard_SetDeviceFeature();}
      else
      {Result = USB_UNSUPPORT;}
    }
    else if (DUSB.Device_Info.USBbRequest == USB_CLEAR_FEATURE)//Clear FEATURE for Device
    {
      if (DUSB.Device_Info.USBwValues.LH.L == USB_DEVICE_REMOTE_WAKEUP && DUSB.Device_Info.USBwIndexs.VAL == 0x0000 && DUSB.Device_Info.Current_Feature&0x20)
      {Result = Standard_ClearFeature();}
      else
      {Result = USB_UNSUPPORT;}
    }
  }
  else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_INTERFACE_RECIPIENT))//Interface Request
  {if (DUSB.Device_Info.USBbRequest == USB_SET_INTERFACE) Result = Standard_SetInterface();}//SET INTERFACE
  else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_ENDPOINT_RECIPIENT))//EndPoint Request
  {
    if (DUSB.Device_Info.USBbRequest == USB_CLEAR_FEATURE)/*CLEAR FEATURE for EndPoint*/
    {Result = Standard_ClearFeature();}
    else if (DUSB.Device_Info.USBbRequest == USB_SET_FEATURE)/* SET FEATURE for EndPoint*/
    {Result = Standard_SetEndPointFeature();}
  }
  else
  {Result = USB_UNSUPPORT;}

  if (Result != USB_SUCCESS)
  {
    Result =CustomHID_NoData_Setup(DUSB.Device_Info.USBbRequest);
    if(Result == USB_NOT_READY) {DUSB.Device_Info.ControlState = PAUSE; return;}
  }

  if(Result != USB_SUCCESS){DUSB.Device_Info.ControlState = STALLED;return;}

  DUSB.Device_Info.ControlState = WAIT_STATUS_IN;//After no data stage SETUP
  USB_SendZeroLength();  //这句很关键，实际在准备好发送0字节的状态数据包。然后等待in令牌包
  return;
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Data_Setup0(void)//获取描述符的函数：设备、配置、字符串描述符,放在 *CopyRoutine
{
  UINT8 *(*CopyRoutine)(UINT16);
  USB_RESULT Result;
  CopyRoutine = NULL;

  if (DUSB.Device_Info.USBbRequest == USB_GET_DESCRIPTOR)				 //0x06
  {
    if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT))
    {
      if (DUSB.Device_Info.USBwValues.LH.H == USB_DEVICE_DESCRIPTOR)			 //0x01
      {CopyRoutine = CustomHID_GetDeviceDescriptor;}
      else if (DUSB.Device_Info.USBwValues.LH.H == USB_CONFIG_DESCRIPTOR)	 //0x02
      {CopyRoutine =CustomHID_GetConfigDescriptor;}
      else if (DUSB.Device_Info.USBwValues.LH.H == USB_STRING_DESCRIPTOR)	 //0x03
      {CopyRoutine = CustomHID_GetStringDescriptor;}
    }
  }
  else if ((DUSB.Device_Info.USBbRequest == USB_GET_STATUS) && (DUSB.Device_Info.USBwValues.VAL == 0x0000)  && (DUSB.Device_Info.USBwLengths.VAL == 0x0002) && (DUSB.Device_Info.USBwIndexs.LH.H == 0x00))
  {
    if ((USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT)) && (DUSB.Device_Info.USBwIndexs.VAL == 0x0000))
    {CopyRoutine = Standard_GetStatus;}
    else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_INTERFACE_RECIPIENT))
    {if ((CustomHID_Get_Interface_Setting(DUSB.Device_Info.USBwIndexs.LH.L, 0) == USB_SUCCESS)  && DUSB.Device_Info.Current_Configuration)CopyRoutine = Standard_GetStatus;}
    else if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_ENDPOINT_RECIPIENT))
    {
      DUSB.REP = (DUSB.Device_Info.USBwIndexs.LH.L & 0x0f);
      if ((DUSB.Device_Info.USBwIndexs.B4P.P0 < USB_EPCount) && (DUSB.Device_Info.USBwIndexs.LH.L&0x70) == 0 && (DUSB.Device_Info.USBwIndexs.BIT.B7 ? USB.EPR_BIT[DUSB.REP].TXSTAT:USB.EPR_BIT[DUSB.REP].RXSTAT))
      {CopyRoutine = Standard_GetStatus;}
    }
  }
  else if (DUSB.Device_Info.USBbRequest == USB_GET_CONFIGURATION)
  {if (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT))CopyRoutine = Standard_GetConfiguration; }
  else if (DUSB.Device_Info.USBbRequest == USB_GET_INTERFACE)
  {
    if ((USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_INTERFACE_RECIPIENT)) && DUSB.Device_Info.Current_Configuration  && (DUSB.Device_Info.USBwValues.VAL == 0x0000)
    && (DUSB.Device_Info.USBwIndexs.LH.H == 0) && (DUSB.Device_Info.USBwLengths.VAL == 0x0001) && (CustomHID_Get_Interface_Setting(DUSB.Device_Info.USBwIndexs.LH.L, 0) == USB_SUCCESS))
    {CopyRoutine = Standard_GetInterface;}
  }
  
  if (CopyRoutine)
  {DUSB.Device_Info.Ctrl_Info.Usb_wOffset = 0x0000; DUSB.Device_Info.Ctrl_Info.CopyData = CopyRoutine;(*CopyRoutine)(0);Result = USB_SUCCESS;}	//这个函数这里调用的目的是设置了pimfomation中的需要写入的描述符的长度
  else
  {Result =CustomHID_Data_Setup(DUSB.Device_Info.USBbRequest);  if(Result == USB_NOT_READY){DUSB.Device_Info.ControlState = PAUSE; return;}}

  if (DUSB.Device_Info.Ctrl_Info.Usb_wLength == 0xFFFF){DUSB.Device_Info.ControlState = PAUSE; return;}//Data is not ready, wait it
  if ((Result == USB_UNSUPPORT) || (DUSB.Device_Info.Ctrl_Info.Usb_wLength == 0)){DUSB.Device_Info.ControlState = STALLED;return;}//Unsupported request

  if (DUSB.Device_Info.USBbmRequestType&0x80)	//此时应为0x80 ，bmRequnest的第四位分别是选择设备、接口、端点的
  {
    if (DUSB.Device_Info.Ctrl_Info.Usb_wLength > DUSB.Device_Info.USBwLengths.VAL)//Restrict the data length to be the one host asks for
    {DUSB.Device_Info.Ctrl_Info.Usb_wLength = DUSB.Device_Info.USBwLengths.VAL;} //描述符长度18
    else if (DUSB.Device_Info.Ctrl_Info.Usb_wLength < DUSB.Device_Info.USBwLengths.VAL)
    {
      if (DUSB.Device_Info.Ctrl_Info.Usb_wLength < DUSB.EPSIZE[0])
      {USB_MulMaxPacketSize = 0;}
      else if ((DUSB.Device_Info.Ctrl_Info.Usb_wLength % DUSB.EPSIZE[0]) == 0)
      {USB_MulMaxPacketSize = 1;}
    }   
    DUSB.Device_Info.Ctrl_Info.PacketSize = DUSB.EPSIZE[0];
    USB_DataStageIn();		  //最主要的就是调用这个函数完成描述符的输出准备
  }
  else
  {DUSB.Device_Info.ControlState = OUT_DATA;	DUSB.RXSTAT=USB_EPR_STAT_VALID;}// enable for next data reception 
  return;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 USB_Setup0_Process(void)
{
  if (DUSB.Device_Info.ControlState != PAUSE)
  {
		DUSB.Device_Info.USBbmRequestType=USB.RXBUF0[0];// bmRequestType请求类型，表明方向和接收对象（设备、接口、端点），此时应是0x80，表明设备到主机
		DUSB.Device_Info.USBbRequest=(USB.RXBUF0[0]>>8);//bRequest 请求代码，第一次应该是0x06，表明主机要获取设备描述符
		DUSB.Device_Info.USBwValues.VAL=USB.RXBUF0[1];  //wValue
		DUSB.Device_Info.USBwIndexs.VAL=USB.RXBUF0[2];  //wIndex   这里高8位和低8位调换了位置  
		DUSB.Device_Info.USBwLengths.VAL=USB.RXBUF0[3]; // word not accessed because of 32 bits addressing 
  }
  DUSB.Device_Info.ControlState = SETTING_UP;
  if (DUSB.Device_Info.USBwLengths.VAL)  USB_Data_Setup0(); else  USB_NoData_Setup0();//Setup with data stage,获取描述符的函数：设备、配置、字符串描述符
  
  return USB_Post0_Process();
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 USB_In0_Process(void)
{
  if ((DUSB.Device_Info.ControlState == IN_DATA) || (DUSB.Device_Info.ControlState == LAST_IN_DATA)) //  ControlState状态机，就是因为这个状态机才能识别是什么状态//这个函数完成描述符的输出准备
  {USB_DataStageIn();}
  else if (DUSB.Device_Info.ControlState == WAIT_STATUS_IN)
  {
    if ((DUSB.Device_Info.USBbRequest == USB_SET_ADDRESS) &&  (USB_Type_Recipient == (USB_STANDARD_REQUEST | USB_DEVICE_RECIPIENT)))			  //如果是设置地址
    {USB_SetAddress(DUSB.Device_Info.USBwValues.LH.L);	DUSB.DEVState=USB_STATE_ADDRESSED;}
    CustomHID_Status_In();
    DUSB.Device_Info.ControlState = STALLED;
  }
  else
  {DUSB.Device_Info.ControlState = STALLED;}
  return USB_Post0_Process();
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 USB_Out0_Process(void)
{
  if ((DUSB.Device_Info.ControlState == IN_DATA) || (DUSB.Device_Info.ControlState == LAST_IN_DATA))
  {DUSB.Device_Info.ControlState = STALLED;}//host aborts the transfer before finish
  else if ((DUSB.Device_Info.ControlState == OUT_DATA) || (DUSB.Device_Info.ControlState == LAST_OUT_DATA))
  {USB_DataStageOut();}
  else if (DUSB.Device_Info.ControlState == WAIT_STATUS_OUT)//这是个空函数，什么都不用做
  {CustomHID_Status_Out();
  }
  else//Unexpect state, STALL the endpoint
  {DUSB.Device_Info.ControlState = STALLED;}
  return USB_Post0_Process();
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 USB_Post0_Process(void)
{
  USB_SetRXCount(0, DUSB.EPSIZE[0]);//将端点0的缓冲区大小设置
  if (DUSB.Device_Info.ControlState == STALLED)
  {DUSB.RXSTAT=USB_EPR_STAT_STALL; DUSB.TXSTAT=USB_EPR_STAT_STALL;}//将端点的发送和接收都设置成：STALL，这种状态下只接收SETUP令牌包
  return (DUSB.Device_Info.ControlState == PAUSE);
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_NOP_Process(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_SendZeroLength(void)
{
  USB.CH[0].TXCOUNT=0x00; DUSB.TXSTAT=USB_EPR_STAT_VALID;//SaveTState=EP_TX_VALID;
}
//------------------------------------------------------------------------------------------------------------------------------

void USB_CTR_LP(void)//端点低优先级中断处理
{
	while(USB.ISTR_BIT.CTR)	
  {
    DUSB.EPIndex =USB.ISTR_BIT.EPID; USB_On=1;
    if (DUSB.EPIndex == 0)
    {
			DUSB.RXSTAT=USB.EPR_BIT[0].RXSTAT; DUSB.TXSTAT=USB.EPR_BIT[0].TXSTAT;USB_SetRXTXSTAT(0,USB_EPR_STAT_NAK,USB_EPR_STAT_NAK);			
			if(!USB.ISTR_BIT.DIR)//如果DIR＝0，相应端点的CTR_TX位被置位，标志一个IN分组(数据从USB模块传输到PC主机)
		  {USB.EPR[0]&=0x8F0F;USB_In0_Process();}
      else//如果DIR＝1，相应端点的CTR_RX位被置位，标志一个OUT分组(数据从PC主机传输到USB模块)的传输完成。
      {USB.EPR[0]&=0x0F8F;if(USB.EPR_BIT[0].SETUP){USB_Setup0_Process();} else {if (USB.EPR_BIT[0].RXCTR)USB_Out0_Process(); else return;}}
		  USB_SetRXTXSTAT(0,DUSB.RXSTAT,DUSB.TXSTAT);
    }
    else//EPindex ！= 0
    {
			if(USB.EPR_BIT[DUSB.EPIndex].RXCTR)
      {USB.EPR[DUSB.EPIndex]&=0x0F8F; if(DUSB.EPIndex==USB_RXEPIndex)USB_ReadBUF(DUSB.EPIndex);USB_SetRXSTAT(DUSB.EPIndex,USB_EPR_STAT_VALID);}
			if(USB.EPR_BIT[DUSB.EPIndex].TXCTR)
      {USB.EPR[DUSB.EPIndex]&=0x8F0F; if(DUSB.EPIndex==USB_TXEPIndex){COM_TXItem_On(SDK_USB_Index)=0;DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Count=0x00;if(DCOM.Item[SDK_USB_Index].TF.Count==0x0000)COM_TX_On(SDK_USB_Index)=0;}}
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_CTR_HP(void)//端点高优先级中断处理
{
	while(USB.ISTR_BIT.CTR)
  {
		USB.ISTR_BIT.CTR=0; DUSB.EPIndex =USB.ISTR_BIT.EPID;
		if(USB.EPR_BIT[DUSB.EPIndex].RXCTR)
    {USB.EPR[DUSB.EPIndex]&=0x0F8F; if(DUSB.EPIndex==USB_RXEPIndex)USB_ReadBUF(DUSB.EPIndex);USB_SetRXSTAT(DUSB.EPIndex,USB_EPR_STAT_VALID);}
		else if(USB.EPR_BIT[DUSB.EPIndex].TXCTR)
    {USB.EPR[DUSB.EPIndex]&=0x8F0F; if(DUSB.EPIndex==USB_TXEPIndex)COM_TXItem_On(SDK_USB_Index)=0;}
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Control(UINT8 Index)
{
  if(USB.ISTR_BIT.CTR && USB.CNTR_BIT.CTRM){USB.ISTR_BIT.CTR=0;USB_CTR_LP();}
  if(USB.ISTR_BIT.RST && USB.CNTR_BIT.RSTM){USB.ISTR_BIT.RST=0;CustomHID_Reset();}
  if(USB.ISTR_BIT.DOVR && USB.CNTR_BIT.DOVRM){USB.ISTR_BIT.DOVR=0;USB_OVR_CallBack();}
  if(USB.ISTR_BIT.ERR && USB.CNTR_BIT.ERRM){USB.ISTR_BIT.ERR=0;USB_ERR_CallBack();}
  if(USB.ISTR_BIT.WKUP && USB.CNTR_BIT.WKUPM){USB.ISTR_BIT.WKUP=0;USB_Resume(USB_RESUME_EXTERNAL);}
  if(USB.ISTR_BIT.SUSP && USB.CNTR_BIT.SUSPM){USB.ISTR_BIT.SUSP=0;if(USB_Suspend_EN){USB_Suspend();} else {USB.CNTR_BIT.SUSPM=0;USB_Resume(USB_RESUME_LATER);}}
  if(USB.ISTR_BIT.SOF && USB.CNTR_BIT.SOFM){USB.ISTR_BIT.SOF=0;USB.CNTR_BIT.SOFM=0;USB_Resume(USB_RESUME_SOF);}
  if(USB.ISTR_BIT.ESOF && USB.CNTR_BIT.ESOFM){USB.ISTR_BIT.ESOF=0;USB.CNTR_BIT.ESOFM=0;USB_Resume(USB_RESUME_ESOF);} // request without change of the machine state 
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_PowerOn(void)
{
  PO_USB_CONN=0;
  USB.CNTR_BIT.FRES =1;USB_CNTR=0x0000;USB_ISTR=0x0000;USB_CNTR=0x1C00;//Force Reset;clear interrup;clear pending;RSTM=SUSPM=WKUPM=1
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_PowerOff(void)
{
	USB_CNTR=0x0001;USB_ISTR=0x0000;USB_CNTR=0x0003;PO_USB_CONN=1;
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Resume_Init(void)
{
  USB_On=0;DUSB.DEVState = USB_STATE_SUSPENDED; USB.CNTR_BIT.LPMODE=0;USB_CNTR=0xBF00;//CTRM=WKUPM=SUSPM=ERRM=SOFM=ESOFM=RESETM=1
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Resume(USB_RESUME_STATE eResumeSetVal)
{
  if (eResumeSetVal != USB_RESUME_ESOF)DUSB.ResumeS.eState = eResumeSetVal;
  switch (DUSB.ResumeS.eState)//
  {
    case USB_RESUME_EXTERNAL:
      USB_Resume_Init(); DUSB.ResumeS.eState = USB_RESUME_OFF; break;
    case USB_RESUME_INTERNAL:
      USB_Resume_Init(); DUSB.ResumeS.eState = USB_RESUME_START; break;
    case USB_RESUME_LATER:
      DUSB.ResumeS.bESOFcnt = 2; DUSB.ResumeS.eState = USB_RESUME_WAIT; break;
    case USB_RESUME_WAIT:
      DUSB.ResumeS.bESOFcnt--; if (DUSB.ResumeS.bESOFcnt == 0) DUSB.ResumeS.eState = USB_RESUME_START; break;
    case USB_RESUME_START:
		  USB.CNTR_BIT.RESUME=1; DUSB.ResumeS.bESOFcnt = 10; DUSB.ResumeS.eState = USB_RESUME_ON; break;
    case USB_RESUME_ON:
      DUSB.ResumeS.bESOFcnt--; if (DUSB.ResumeS.bESOFcnt == 0){USB.CNTR_BIT.RESUME=0; DUSB.ResumeS.eState = USB_RESUME_OFF;}  break;
    case USB_RESUME_OFF:
    case USB_RESUME_SOF:
    case USB_RESUME_ESOF:
    default:
      DUSB.ResumeS.eState = USB_RESUME_OFF;
      break;
  }
}
//==============================================================================================================================
void USB_ReadBUF(UINT8 EPIndex)
{
	volatile UINT32 *P;UINT16 *PUser;
  P=(volatile UINT32 *)DUSB.RXADDR[EPIndex];PUser=(UINT16 *)DCOM.Item[SDK_USB_Index].RF.Item;
	DCOM.Item[SDK_USB_Index].RF.Index=0x0000;DCOM.Item[SDK_USB_Index].RF.Verify=0x00;IRQINT[1]=USB.CH[1].RXCOUNT&0x3FF;	if(IRQINT[1]<4)return;
	for(IRQINT[0]=0;IRQINT[0]<(IRQINT[1]+1)/2;IRQINT[0]++)
	{
	  (*PUser)=(*P);
		if(IRQINT[0]==0)
		{ if(((*P)&0xFFFF)!=0xAA55)return;}
		else if(IRQINT[0]==1)
		{ 
			DCOM.Item[SDK_USB_Index].RF.Control=DCOM.Item[SDK_USB_Index].RF.Item[2];DCOM.Item[SDK_USB_Index].RF.Command=DCOM.Item[SDK_USB_Index].RF.Item[3];
		  if(DCOM.Item[SDK_USB_Index].RF.Control&Control_SF){DCOM.Item[SDK_USB_Index].RF.ParaCount=0x0000;break;}
			if(IRQINT[1]<7)break;
		} 
		else if(IRQINT[0]==2)
    { DCOM.Item[SDK_USB_Index].RF.ParaCount=(*P)&0xFFFF;PUser=(UINT16 *)DCOM.Item[SDK_USB_Index].RF.Item;IRQINT[1]=DCOM.Item[SDK_USB_Index].RF.ParaCount+7;
		  if(IRQINT[1]>DUSB.EPSIZE[EPIndex]||IRQINT[1]>USB.CH[1].RXCOUNT)return;
		}
		else 
		{ DCOM.Item[SDK_USB_Index].RF.Verify+=(USB.RXBUF1[IRQINT[0]]+(USB.RXBUF1[IRQINT[0]]>>8));}
		P++;PUser++;
	}
	if(DCOM.Item[SDK_USB_Index].RF.ParaCount)
	{
	  for(IRQINT[0]=0;IRQINT[0]<DCOM.Item[SDK_USB_Index].RF.ParaCount;IRQINT[0]++) DCOM.Item[SDK_USB_Index].RF.Verify+=DCOM.Item[SDK_USB_Index].RF.Item[IRQINT[0]];
		if(DCOM.Item[SDK_USB_Index].RF.Verify!=DCOM.Item[SDK_USB_Index].RF.Item[DCOM.Item[SDK_USB_Index].RF.Index-1])return;
	}
  if(DAPP.INTF.COM_ReadParameter)DAPP.INTF.COM_ReadParameter(SDK_USB_Index,DCOM.Item[SDK_USB_Index].RF.Item,DCOM.Item[SDK_USB_Index].RF.ParaCount);
}	
//------------------------------------------------------------------------------------------------------------------------------
void USB_SendBUF(UINT8 EPIndex)//发送BUF（中断内外调用）
{
	UINT16 i,j,Len,Temp,*P;
  i=0x0000;while(USB.EPR_BIT[USB_TXEPIndex].TXSTAT!=USB_EPR_STAT_NAK && i<0x200)i++;
	P=(UINT16 *)DUSB.TXADDR[EPIndex];	j=(DCOM.Item[SDK_USB_Index].TF.Index+SIZE_USB_TBUF-DCOM.Item[SDK_USB_Index].TF.Count)%SIZE_USB_TBUF;
	Len=DCOM.Item[SDK_USB_Index].TF.Item[j];j=(j+1)%SIZE_USB_TBUF; Len+=((UINT16)DCOM.Item[SDK_USB_Index].TF.Item[j]<<8);j=(j+1)%SIZE_USB_TBUF;
	for(i=0; i <(Len+1)/2; i++)
  {Temp=DCOM.Item[SDK_USB_Index].TF.Item[j];j=(j+1)%SIZE_USB_TBUF;	Temp+=((UINT16)DCOM.Item[SDK_USB_Index].TF.Item[j]<<8);j=(j+1)%SIZE_USB_TBUF;*P=Temp;P+=2;}
	DCOM.Item[SDK_USB_Index].TF.Count-=(Len+2);
    
  if(DCOM.Item[SDK_USB_Index].TF.Count==0)
  {DCOM.Item[SDK_USB_Index].TF.MMT.Count=0;}
  else if(DCOM.Item[SDK_USB_Index].TF.MMT.Count>1 && j==DCOM.Item[SDK_USB_Index].TF.MMT.Item[1].Pos)
  {for(i=0;i<DCOM.Item[SDK_USB_Index].TF.MMT.Count-2;i++)DCOM.Item[SDK_USB_Index].TF.MMT.Item[i]=DCOM.Item[SDK_USB_Index].TF.MMT.Item[i+1];DCOM.Item[SDK_USB_Index].TF.MMT.Count--;}
    
	DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_TimeCount=0x00;DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Time=30; COM_TXItem_On(SDK_USB_Index)=1;//Tx Timeout minitor=30*100us=3ms
	USB.CH[EPIndex].TXCOUNT=(USB_DMLenth_EN ? Len:DUSB.EPSIZE[USB_TXEPIndex]);	USB_SetTXSTAT(EPIndex, USB_EPR_STAT_VALID);
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_WaitSend(void)//等待发送完毕（中断外调用）,超时1秒
{
	UINT32 T;
	T=SysTimeCount;	while((COM_TX_On(SDK_USB_Index)||COM_TXItem_On(SDK_USB_Index)) && SysTimeCount-T<1000);
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_HW_SendString(UINT8 *s,UINT16 Count)//发送到硬件（中断内外调用）
{
	UINT16 i;UINT32 T;
	if(Count==0x0000||Count>DUSB.EPSIZE[USB_TXEPIndex])return;
  T=SysTimeCount;while(USB.EPR_BIT[USB_TXEPIndex].TXSTAT!=USB_EPR_STAT_NAK && SysTimeCount-T<2); 
	for(i=0; i <(Count+1)/2; i++){*(UINT16 *)(DUSB.TXADDR[USB_TXEPIndex]+4*i)=*(UINT16 *)s;s+=2;}
	USB.CH[USB_TXEPIndex].TXCOUNT=(USB_DMLenth_EN ? Count:DUSB.EPSIZE[USB_TXEPIndex]);USB_SetTXSTAT(USB_TXEPIndex, USB_EPR_STAT_VALID);
	DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_TimeCount=0x00;DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Time=30;
  COM_TX_On(SDK_USB_Index)=COM_TXItem_On(SDK_USB_Index)=1;//Tx Timeout minitor=30*100us=3ms
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_TXTimeOut_Timer(void)//every 100us,send timeout control
{
	if(!COM_TXItem_On(SDK_USB_Index))return;
	DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_TimeCount++; 
  if(DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_TimeCount>DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Time)
  {
		COM_TXItem_On(SDK_USB_Index)=0;if(DCOM.Item[SDK_USB_Index].TF.Count==0x0000)COM_TX_On(SDK_USB_Index)=0;
	  DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Count++;if(DCOM.Item[SDK_USB_Index].TF.TXI.TimeOut_Count>=5){USB_Reset_On=1;INT_Event_On=1;}
	}
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Send_Timer(void)//发送定时事件,every 1ms(中断内外调用）
{
	if(!COM_TX_On(SDK_USB_Index)||COM_TXItem_On(SDK_USB_Index))return;
  if(DCOM.Item[SDK_USB_Index].TF.Count==0x00||DCOM.Item[SDK_USB_Index].TF.MMT.Item[0].Time)COM_EndSend(SDK_USB_Index); else USB_SendBUF(USB_TXEPIndex);
}
//------------------------------------------------------------------------------------------------------------------------------
#endif
//==============================================================================================================================
