//==============================================================================================================================
#include "Global.h"
//==============================================================================================================================
//<USBFS.c>
//------------------------------------------------------------------------------------------------------------------------------
//<usb_desc.c>
/* USB Standard Device Descriptor */
const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize 64*/
    0x83,                       /*idVendor (0x0483)*/
    0x04,
    0x62,                       /*idProduct = 0x5762*/
    0x57,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                                  manufacturer */
    2,                          /*Index of string descriptor describing
                                                 product*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* CustomHID_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuation Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    CUSTOMHID_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration*/
    0xC0,		//ԭ���0xE0,         /*bmAttributes: bus powered */
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

    /************** Descriptor of CustomHID interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
    0x00,         /*bInterfaceNumber: Number of Interface*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x02,         /*bNumEndpoints*/
    0x03,         /*bInterfaceClass: HID*/
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,            /*iInterface: Index of string descriptor*/
    /******************** Descriptor of CustomHID HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
    0x10,		//ԭ���0x00,         /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,         /*bCountryCode: Hardware target country*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,         /*bDescriptorType*/
    CUSTOMHID_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
    0x00,
    /******************** Descriptor of CustomHID endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x82,      //ԭ�����0x81    /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,                        /* bmAttributes: Bulk */
    USB_EP1_Size,          /*wMaxPacketSize: 64 Byte max */
    0x00,
    0x01,          /*bInterval: Polling Interval (1 ms)*/
    /* 34 */

	0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
			/*	Endpoint descriptor type */
    0x01,	/* bEndpointAddress: */
			/*	Endpoint1 Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    USB_EP2_Size,//0x02,	/* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x01,	/* bInterval: Polling Interval (1 ms) */
    /* 41 */
  }
  ; /* CUSTOMHID_ConfigDescriptor */
const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] = 

{ 

        0x05, 0x8c, /* USAGE_PAGE (ST Page) */ 

        0x09, 0x01, /* USAGE (Demo Kit) */ 

        0xa1, 0x01, /* COLLECTION (Application) */ 

        

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


        0xc0 /* END_COLLECTION */ 
}; /* CustomHID_ReportDescriptor */ 

/* USB String Descriptors (optional) */
const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
  {
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

//�������ַ���

const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
  {
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "www.waveshare.net" */   		 
    'A', 0, 'I', 0, 'M', 0, 'Y', 0, 'U', 0, 'N', 0, 'I', 0, 'O', 0,
    'N', 0, 'T', 0, 'E', 0, 'C', 0, 'H', 0, 'N', 0, 'O', 0, 'L', 0,
    'O', 0, 'G', 0, 'Y',

  };

  //��Ʒ����
const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
  {
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */ 
	'A', 0, 'A', 0, 'M', 0, ' ', 0, 'X', 0, '-', 0, 'D', 0,
    'A', 0, 'N', 0, 'C', 0, 'E', 0, ' ', 0, 'H', 0, 'I', 0,
    'D', 0

  };

  //��Ʒ����
uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
  {
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	/* STM3210 */
    'A', 0, 'P', 0, 'M', 0,'3', 0,'2', 0, '1', 0, '0', 0
  };
	
//------------------------------------------------------------------------------------------------------------------------------
//<usb_prop.c>

uint32_t ProtocolValue;

DEVICE Device_Table ={USB_EPCount, 1 };

DEVICE_PROP Device_Property =
  {
    CustomHID_Init,
    CustomHID_Reset,
    CustomHID_Status_In,
    CustomHID_Status_Out,
    CustomHID_Data_Setup,
    CustomHID_NoData_Setup,
    CustomHID_Get_Interface_Setting,
    CustomHID_GetDeviceDescriptor,
    CustomHID_GetConfigDescriptor,
    CustomHID_GetStringDescriptor,
    0,
    0x80 //MAX PACKET SIZEMAX(USB_EP1_Size,USB_EP2_Size)
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    CustomHID_GetConfiguration,
    CustomHID_SetConfiguration, //�ǿ�
    CustomHID_GetInterface,
    CustomHID_SetInterface,
    CustomHID_GetStatus,
    CustomHID_ClearFeature,
    CustomHID_SetEndPointFeature,
    CustomHID_SetDeviceFeature,
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)CustomHID_DeviceDescriptor,
    CUSTOMHID_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)CustomHID_ConfigDescriptor,
    CUSTOMHID_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR CustomHID_Report_Descriptor =
  {
    (uint8_t *)CustomHID_ReportDescriptor,
    CUSTOMHID_SIZ_REPORT_DESC
  };

ONE_DESCRIPTOR CustomHID_Hid_Descriptor =							   //Mouse��Hid��������λ�ã�CUSTOM_OFF_HID_DESC��
															    	//�ͳ��ȣ�CUSTOM_SIZ_HID_DESC��
  {
    (UINT8*)CustomHID_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
    CUSTOMHID_SIZ_HID_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)CustomHID_StringLangID, CUSTOMHID_SIZ_STRING_LANGID},
    {(uint8_t*)CustomHID_StringVendor, CUSTOMHID_SIZ_STRING_VENDOR},
    {(uint8_t*)CustomHID_StringProduct, CUSTOMHID_SIZ_STRING_PRODUCT},
    {(uint8_t*)CustomHID_StringSerial, CUSTOMHID_SIZ_STRING_SERIAL}
  };
	
//------------------------------------------------------------------------------------------------------------------------------
//<usb_core.c>
bool Data_Mul_MaxPacketSize = FALSE;
uint16_t_uint8_t StatusInfo;  
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *Standard_GetConfiguration(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = sizeof(pInformation->Current_Configuration);
    return 0;
  }
  pUser_Standard_Requests->User_GetConfiguration();
  return (uint8_t *)&pInformation->Current_Configuration;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetConfiguration(void)
{

  if ((pInformation->USBwValue0 <=
      Device_Table.Total_Configuration) && (pInformation->USBwValue1 == 0)
      && (pInformation->USBwIndex == 0)) /*call Back usb spec 2.0*/
  {
    pInformation->Current_Configuration = pInformation->USBwValue0;
    pUser_Standard_Requests->User_SetConfiguration();
    return USB_SUCCESS;
  }
  else
  {
    return USB_UNSUPPORT;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *Standard_GetInterface(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength =sizeof(pInformation->Current_AlternateSetting);
    return 0;
  }
  pUser_Standard_Requests->User_GetInterface();
  return (uint8_t *)&pInformation->Current_AlternateSetting;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetInterface(void)
{
  USB_RESULT Re;
  //Test if the specified Interface and Alternate Setting are supported by the application Firmware
  Re = (*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, pInformation->USBwValue0);

  if (pInformation->Current_Configuration != 0)
  {
    if ((Re != USB_SUCCESS) || (pInformation->USBwIndex1 != 0)
        || (pInformation->USBwValue1 != 0))
    {
      return  USB_UNSUPPORT;
    }
    else if (Re == USB_SUCCESS)
    {
      pUser_Standard_Requests->User_SetInterface();
      pInformation->Current_Interface = pInformation->USBwIndex0;
      pInformation->Current_AlternateSetting = pInformation->USBwValue0;
      return USB_SUCCESS;
    }

  }

  return USB_UNSUPPORT;
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *Standard_GetStatus(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 2;
    return 0;
  }

  /* Reset Status Information */
   StatusInfo.w = 0;//DUSB.StatusInfo.VAL =0;// 

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /*Get Device Status */
    uint8_t Feature = pInformation->Current_Feature;

    /* Remote Wakeup enabled */
    if (ValBit(Feature, 5))
    {
      SetBit(StatusInfo0, 1);//DUSB.StatusInfo.BIT.B1=1;//  
    }
    else
    {
      ClrBit(StatusInfo0, 1);//DUSB.StatusInfo.BIT.B1=0;//
    }      

    /* Bus-powered */
    if (ValBit(Feature, 6))
    {
      SetBit(StatusInfo0, 0);//DUSB.StatusInfo.BIT.B0=1;//
    }
    else /* Self-powered */
    {
      ClrBit(StatusInfo0, 0);//DUSB.StatusInfo.BIT.B0=0;//
    }
  }
  /*Interface Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    return  (uint8_t *)&StatusInfo;//DUSB.StatusInfo.Byte;//
  }
  /*Get EndPoint Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    uint8_t Related_Endpoint;
    uint8_t wIndex0 = pInformation->USBwIndex0;

    Related_Endpoint = (wIndex0 & 0x0f);
    if (ValBit(wIndex0, 7))
    {
      /* IN endpoint */
			if(USB.EPR_BIT[Related_Endpoint].TXSTAT==USB_EPR_STAT_STALL) 
      //if ( _GetTxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0);//DUSB.StatusInfo.BIT.B0=1;// /* IN Endpoint stalled */
      }
    }
    else
    {
      /* OUT endpoint */
			if(USB.EPR_BIT[Related_Endpoint].RXSTAT==USB_EPR_STAT_STALL) 
      //if (_GetRxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0);//DUSB.StatusInfo.BIT.B0=1;// /* OUT Endpoint stalled */
      }
    }

  }
  else
  {
    return NULL;
  }
  pUser_Standard_Requests->User_GetStatus();
  return  (uint8_t *)&StatusInfo;//DUSB.StatusInfo.Byte;//
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_ClearFeature(void)//Clear or disable a specific feature.
{
  uint32_t     Type_Rec = Type_Recipient;
  uint32_t     Status;


  if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {/*Device Clear Feature*/
    ClrBit(pInformation->Current_Feature, 5);
    return USB_SUCCESS;
  }
  else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {/*EndPoint Clear Feature*/
    DEVICE* pDev;
    uint32_t Related_Endpoint;
    uint32_t wIndex0;
    uint32_t rEP;

    if ((pInformation->USBwValue != ENDPOINT_STALL)
        || (pInformation->USBwIndex1 != 0))
    {
      return USB_UNSUPPORT;
    }

    pDev = &Device_Table;
    wIndex0 = pInformation->USBwIndex0;
    rEP = wIndex0 & ~0x80;
    Related_Endpoint = rEP;

    if (ValBit(pInformation->USBwIndex0, 7))
    {
      /*Get Status of endpoint & stall the request if the related_ENdpoint
      is Disabled*/
      Status =USB.EPR_BIT[Related_Endpoint].TXSTAT;
    }
    else
    {
      Status =USB.EPR_BIT[Related_Endpoint].RXSTAT;
    }

    if ((rEP >= pDev->Total_Endpoint) || (Status == 0)
        || (pInformation->Current_Configuration == 0))
    {
      return USB_UNSUPPORT;
    }


    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      //if (_GetTxStallStatus(Related_Endpoint ))
			if(USB.EPR_BIT[Related_Endpoint].TXSTAT==USB_EPR_STAT_STALL) 
      {
      #if !IsDensity(CL)
				if(USB.EPR_BIT[Related_Endpoint].TXDTOG)USB_ToggleDTOG(Related_Endpoint,USB_RXTXFlag_TX);
      #endif
        //_SetEPTxStatus(Related_Endpoint, EP_TX_VALID);
				USB_SetTXSTAT(Related_Endpoint,USB_EPR_STAT_VALID); 
      }
    }
    else
    {
      /* OUT endpoint */
      //if (_GetRxStallStatus(Related_Endpoint))
			if(USB.EPR_BIT[Related_Endpoint].RXSTAT==USB_EPR_STAT_STALL) 
      {
        if (Related_Endpoint == 0)
        {
					USB_SetRXCount(0,Device_Property.MaxPacketSize);//After clear the STALL, enable the default endpoint receiver
        }
        else
        {
        #if !IsDensity(CL)
					if(USB.EPR_BIT[Related_Endpoint].RXDTOG)USB_ToggleDTOG(Related_Endpoint,USB_RXTXFlag_RX);
        #endif
        }
				USB_SetRXSTAT(Related_Endpoint,USB_EPR_STAT_VALID); //_SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
      }
    }
    pUser_Standard_Requests->User_ClearFeature();
    return USB_SUCCESS;
  }

  return USB_UNSUPPORT;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT Standard_SetEndPointFeature(void)//Set or enable a specific feature of EndPoint
{
  uint32_t    wIndex0;
  uint32_t    Related_Endpoint;
  uint32_t    rEP;
  uint32_t    Status;

  wIndex0 = pInformation->USBwIndex0;
  rEP = wIndex0 & ~0x80;
  Related_Endpoint =  rEP;

  if (ValBit(pInformation->USBwIndex0, 7))
  {
    /* get Status of endpoint & stall the request if the related_ENdpoint
    is Disabled*/
    Status =USB.EPR_BIT[Related_Endpoint].TXSTAT;
  }
  else
  {
    Status =USB.EPR_BIT[Related_Endpoint].RXSTAT;
  }

  if (Related_Endpoint >= Device_Table.Total_Endpoint
      || pInformation->USBwValue != 0 || Status == 0
      || pInformation->Current_Configuration == 0)
  {
    return USB_UNSUPPORT;
  }
  else
  {
    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      //_SetEPTxStatus(Related_Endpoint, EP_TX_STALL);
			USB_SetTXSTAT(Related_Endpoint,USB_EPR_STAT_STALL);
    }

    else
    {
      /* OUT endpoint */
      //_SetEPRxStatus(Related_Endpoint, EP_RX_STALL);
			USB_SetRXSTAT(Related_Endpoint,USB_EPR_STAT_STALL); 
    }
  }
  pUser_Standard_Requests->User_SetEndPointFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_SetDeviceFeature.
* Description    : Set or enable a specific feature of Device.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
USB_RESULT Standard_SetDeviceFeature(void)
{
  SetBit(pInformation->Current_Feature, 5);
  pUser_Standard_Requests->User_SetDeviceFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_GetDescriptorData.
* Description    : Standard_GetDescriptorData is used for descriptors transfer.
*                : This routine is used for the descriptors resident in Flash
*                  or RAM
*                  pDesc can be in either Flash or RAM
*                  The purpose of this routine is to have a versatile way to
*                  response descriptors request. It allows user to generate
*                  certain descriptors with software or read descriptors from
*                  external storage part by part.
* Input          : - Length - Length of the data in this transfer.
*                  - pDesc - A pointer points to descriptor struct.
*                  The structure gives the initial address of the descriptor and
*                  its original size.
* Output         : None.
* Return         : Address of a part of the descriptor pointed by the Usb_
*                  wOffset The buffer pointed by this address contains at least
*                  Length bytes.
*******************************************************************************/
uint8_t *Standard_GetDescriptorData(uint16_t Length, ONE_DESCRIPTOR *pDesc)
{
  uint32_t  wOffset;

  wOffset = pInformation->Ctrl_Info.Usb_wOffset;
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
    return 0;
  }

  return pDesc->Descriptor + wOffset;
}

/*******************************************************************************
* Function Name  : DataStageOut.
* Description    : Data stage of a Control Write Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageOut(void)
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  uint32_t save_rLength;

  save_rLength = pEPinfo->Usb_rLength;

  if (pEPinfo->CopyData && save_rLength)
  {
    uint8_t *Buffer;
    uint32_t Length;

    Length = pEPinfo->PacketSize;
    if (Length > save_rLength)
    {
      Length = save_rLength;
    }

    Buffer = (*pEPinfo->CopyData)(Length);
    pEPinfo->Usb_rLength -= Length;
    pEPinfo->Usb_rOffset += Length;

  #if IsDensity(CL)
    PCD_EP_Read(ENDP0, Buffer, Length); 
  #else  
    USB_GetData(0,Buffer,Length);
  #endif
  }

  if (pEPinfo->Usb_rLength != 0)
  {
		USB.CH[0].TXCOUNT=0x0000;
		DUSB.RXSTAT=USB_EPR_STAT_VALID; DUSB.TXSTAT=USB_EPR_STAT_VALID;// re-enable for next data reception , Expect the host to abort the data OUT stage 
  }
  /* Set the next State*/
  if (pEPinfo->Usb_rLength >= pEPinfo->PacketSize)
  {
    pInformation->ControlState = OUT_DATA;
  }
  else
  {
    if (pEPinfo->Usb_rLength > 0)
    {
      pInformation->ControlState = LAST_OUT_DATA;
    }
    else if (pEPinfo->Usb_rLength == 0)
    {
      pInformation->ControlState = WAIT_STATUS_IN;
      SendZeroLength();
    }
  }
}

/*******************************************************************************
* Function Name  : DataStageIn.
* Description    : Data stage of a Control Read Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageIn(void)	 //���������������������׼��
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  uint32_t save_wLength = pEPinfo->Usb_wLength;
  uint32_t ControlState = pInformation->ControlState;

  uint8_t *DataBuffer;
  uint32_t Length;

  if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))
  {
    if(Data_Mul_MaxPacketSize == TRUE)//No more data to send and empty packet 
    {
      
      SendZeroLength();
      ControlState = LAST_IN_DATA;
      Data_Mul_MaxPacketSize = FALSE;
    }
    else //No more data to send so STALL the TX Status
    {
      ControlState = WAIT_STATUS_OUT;
    #if IsDensity(CL)
      PCD_EP_Read (ENDP0, 0, 0);
    #else
			DUSB.TXSTAT=USB_EPR_STAT_STALL;
    #endif
    }
    
    goto Expect_Status_Out;
  }

  Length = pEPinfo->PacketSize;		
  ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;

  if (Length > save_wLength)
  {
    Length = save_wLength;
  }

  DataBuffer = (*pEPinfo->CopyData)(Length);	 //������û�ȡ���û��������������ĵ�ַ�����ﹲ��18�ֽ�

#if IsDensity(CL)
  PCD_EP_Write (ENDP0, DataBuffer, Length);
#else   
	USB_SetData(0,DataBuffer,Length);//����������豸���������Ƶ��û��ķ��ͻ�����
#endif

	USB.CH[0].TXCOUNT=Length;//���÷����ֽڵ���Ŀ
  pEPinfo->Usb_wLength -= Length;		 //����0
  pEPinfo->Usb_wOffset += Length;		 //ƫ�Ƶ�18
  DUSB.TXSTAT=USB_EPR_STAT_VALID;	DUSB.RXSTAT=USB_EPR_STAT_VALID;//Expect the host to abort the data IN stage,�˵�ʹ�ܷ��ͣ���Ҫ������IN���ư�һ����SIE�ͻὫ���������ظ�����,ʵ���Ͻ���Ҳ��Ч��������ȡ��IN

Expect_Status_Out:
  pInformation->ControlState = ControlState;
}
//------------------------------------------------------------------------------------------------------------------------------
void NoData_Setup0(void)
{
  USB_RESULT Result = USB_UNSUPPORT;
  uint32_t RequestNo = pInformation->USBbRequest;
  uint32_t ControlState;

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /* Device Request*/
    /* SET_CONFIGURATION*/
    if (RequestNo == SET_CONFIGURATION)
    {
      Result = Standard_SetConfiguration();
    }

    /*SET ADDRESS*/
    else if (RequestNo == SET_ADDRESS)
    {
      if ((pInformation->USBwValue0 > 127) || (pInformation->USBwValue1 != 0)
          || (pInformation->USBwIndex != 0)
          || (pInformation->Current_Configuration != 0))
        /* Device Address should be 127 or less*/
      {
        ControlState = STALLED;
        goto exit_NoData_Setup0;
      }
      else
      {
        Result = USB_SUCCESS;

      #if IsDensity(CL)
				 USB_SetAddress(pInformation->USBwValue0);
      #endif
      }
    }
    /*SET FEATURE for Device*/
    else if (RequestNo == SET_FEATURE)
    {
      if ((pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP) \
          && (pInformation->USBwIndex == 0))
      {
        Result = Standard_SetDeviceFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }
    /*Clear FEATURE for Device */
    else if (RequestNo == CLEAR_FEATURE)
    {
      if (pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP
          && pInformation->USBwIndex == 0
          && ValBit(pInformation->Current_Feature, 5))
      {
        Result = Standard_ClearFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }

  }

  /* Interface Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    /*SET INTERFACE*/
    if (RequestNo == SET_INTERFACE)
    {
      Result = Standard_SetInterface();
    }
  }

  /* EndPoint Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    /*CLEAR FEATURE for EndPoint*/
    if (RequestNo == CLEAR_FEATURE)
    {
      Result = Standard_ClearFeature();
    }
    /* SET FEATURE for EndPoint*/
    else if (RequestNo == SET_FEATURE)
    {
      Result = Standard_SetEndPointFeature();
    }
  }
  else
  {
    Result = USB_UNSUPPORT;
  }


  if (Result != USB_SUCCESS)
  {
    Result = (*pProperty->Class_NoData_Setup)(RequestNo);
    if (Result == USB_NOT_READY)
    {
      ControlState = PAUSE;
      goto exit_NoData_Setup0;
    }
  }

  if (Result != USB_SUCCESS)
  {
    ControlState = STALLED;
    goto exit_NoData_Setup0;
  }

  ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */

  SendZeroLength();  //���ܹؼ���ʵ����׼���÷���0�ֽڵ�״̬���ݰ���Ȼ��ȴ�in���ư�

exit_NoData_Setup0:
  pInformation->ControlState = ControlState;
  return;
}

/*******************************************************************************
* Function Name  : Data_Setup0.
* Description    : Proceed the processing of setup request with data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Data_Setup0(void)		//��ȡ�������ĺ������豸�����á��ַ���������,���� *CopyRoutine
{
  uint8_t *(*CopyRoutine)(uint16_t);
  USB_RESULT Result;
  uint32_t Request_No = pInformation->USBbRequest;

  uint32_t Related_Endpoint, Reserved;
  uint32_t wOffset, Status;



  CopyRoutine = NULL;
  wOffset = 0;

  /*GET DESCRIPTOR*/
  if (Request_No == GET_DESCRIPTOR)				 //0x06
  {
    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
      uint8_t wValue1 = pInformation->USBwValue1;
      if (wValue1 == DEVICE_DESCRIPTOR)			 //0x01
      {
        CopyRoutine = pProperty->GetDeviceDescriptor;
      }
      else if (wValue1 == CONFIG_DESCRIPTOR)	 //0x02
      {
        CopyRoutine = pProperty->GetConfigDescriptor;
      }
      else if (wValue1 == STRING_DESCRIPTOR)	 //0x03
      {
        CopyRoutine = pProperty->GetStringDescriptor;
      }  /* End of GET_DESCRIPTOR */
    }
  }

  /*GET STATUS*/
  else if ((Request_No == GET_STATUS) && (pInformation->USBwValue == 0)
           && (pInformation->USBwLength == 0x0002)
           && (pInformation->USBwIndex1 == 0))
  {
    /* GET STATUS for Device*/
    if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        && (pInformation->USBwIndex == 0))
    {
      CopyRoutine = Standard_GetStatus;
    }

    /* GET STATUS for Interface*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
      if (((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS)
          && (pInformation->Current_Configuration != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }

    /* GET STATUS for EndPoint*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
      Related_Endpoint = (pInformation->USBwIndex0 & 0x0f);
      Reserved = pInformation->USBwIndex0 & 0x70;

      if (ValBit(pInformation->USBwIndex0, 7))
      {
        /*Get Status of endpoint & stall the request if the related_ENdpoint
        is Disabled*/
        Status =USB.EPR_BIT[Related_Endpoint].TXSTAT;
      }
      else
      {
        Status =USB.EPR_BIT[Related_Endpoint].RXSTAT;
      }

      if ((Related_Endpoint < Device_Table.Total_Endpoint) && (Reserved == 0)
          && (Status != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }

  }

  /*GET CONFIGURATION*/
  else if (Request_No == GET_CONFIGURATION)
  {
    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
      CopyRoutine = Standard_GetConfiguration;
    }
  }
  /*GET INTERFACE*/
  else if (Request_No == GET_INTERFACE)
  {
    if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        && (pInformation->Current_Configuration != 0) && (pInformation->USBwValue == 0)
        && (pInformation->USBwIndex1 == 0) && (pInformation->USBwLength == 0x0001)
        && ((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS))
    {
      CopyRoutine = Standard_GetInterface;
    }

  }
  
  if (CopyRoutine)
  {
    pInformation->Ctrl_Info.Usb_wOffset = wOffset;
    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    /* sb in the original the cast to word was directly */
    /* now the cast is made step by step */
    (*CopyRoutine)(0);	//�������������õ�Ŀ����������pimfomation�е���Ҫд����������ĳ���
    Result = USB_SUCCESS;
  }
  else
  {
    Result = (*pProperty->Class_Data_Setup)(pInformation->USBbRequest);
    if (Result == USB_NOT_READY)
    {
      pInformation->ControlState = PAUSE;
      return;
    }
  }

  if (pInformation->Ctrl_Info.Usb_wLength == 0xFFFF)
  {
    /* Data is not ready, wait it */
    pInformation->ControlState = PAUSE;
    return;
  }
  if ((Result == USB_UNSUPPORT) || (pInformation->Ctrl_Info.Usb_wLength == 0))
  {
    /* Unsupported request */
    pInformation->ControlState = STALLED;
    return;
  }


  if (ValBit(pInformation->USBbmRequestType, 7))	//��ʱӦΪ0x80 ��bmRequnest�ĵ���λ�ֱ���ѡ���豸���ӿڡ��˵��
  {
    /* Device ==> Host */
    volatile uint32_t wLength = pInformation->USBwLength;  //���һ�㶼��64
     
    /* Restrict the data length to be the one host asks for */
    if (pInformation->Ctrl_Info.Usb_wLength > wLength)
    {
      pInformation->Ctrl_Info.Usb_wLength = wLength;		 //����������18
    }
    
    else if (pInformation->Ctrl_Info.Usb_wLength < pInformation->USBwLength)
    {
      if (pInformation->Ctrl_Info.Usb_wLength < pProperty->MaxPacketSize)
      {
        Data_Mul_MaxPacketSize = FALSE;
      }
      else if ((pInformation->Ctrl_Info.Usb_wLength % pProperty->MaxPacketSize) == 0)
      {
        Data_Mul_MaxPacketSize = TRUE;
      }
    }   

    pInformation->Ctrl_Info.PacketSize = pProperty->MaxPacketSize;
    DataStageIn();		  //����Ҫ�ľ��ǵ������������������������׼��
  }
  else
  {
    pInformation->ControlState = OUT_DATA;
    //vSetEPRxStatus(EP_RX_VALID); 
		DUSB.RXSTAT=USB_EPR_STAT_VALID;// enable for next data reception 
  }

  return;
}

/*******************************************************************************
* Function Name  : Setup0_Process
* Description    : Get the device request data and dispatch to individual process.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Setup0_Process(void)
{
#if IsDensity(CL)
  union
  {
    uint8_t* b;
    uint16_t* w;
  } pBuf;

  USB_OTG_EP *ep;
  uint16_t offset = 0;
 
  ep = PCD_GetOutEP(ENDP0);
  pBuf.b = ep->xfer_buff;
#endif

  if (pInformation->ControlState != PAUSE)
  {
		pInformation->USBbmRequestType=USB.RXBUF0[0];// bmRequestType�������ͣ���������ͽ��ն����豸���ӿڡ��˵㣩����ʱӦ��0x80�������豸������
		pInformation->USBbRequest=(USB.RXBUF0[0]>>8);//bRequest ������룬��һ��Ӧ����0x06����������Ҫ��ȡ�豸������
		pInformation->USBwValue=(USB.RXBUF0[1]>>8)|(USB.RXBUF0[1]<<8); // wValue   �����8λ�͵�8λ������λ�� 
		pInformation->USBwIndex=(USB.RXBUF0[2]>>8)|(USB.RXBUF0[2]<<8);// wIndex   �����8λ�͵�8λ������λ��  
		pInformation->USBwLength=USB.RXBUF0[3];// word not accessed because of 32 bits addressing 
  }
  pInformation->ControlState = SETTING_UP;
  if (pInformation->USBwLength == 0) NoData_Setup0(); else  Data_Setup0();//Setup with data stage,��ȡ�������ĺ������豸�����á��ַ���������
  
  return Post0_Process();
}

/*******************************************************************************
* Function Name  : In0_Process
* Description    : Process the IN token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t In0_Process(void)
{
  uint32_t ControlState = pInformation->ControlState;

  if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))	  //  ControlState״̬����������Ϊ���״̬������ʶ����ʲô״̬
  {
    DataStageIn();			 //���������������������׼��
    /* ControlState may be changed outside the function */
    ControlState = pInformation->ControlState;
  }

  else if (ControlState == WAIT_STATUS_IN)
  {
    if ((pInformation->USBbRequest == SET_ADDRESS) &&					  //��������õ�ַ
        (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
    {
      USB_SetAddress(pInformation->USBwValue0);
			DUSB.DEVState=USB_STATE_ADDRESSED;
    }
    (*pProperty->Process_Status_IN)();	   //����һ���պ���
    ControlState = STALLED;
  }

  else
  {
    ControlState = STALLED;
  }

  pInformation->ControlState = ControlState;

  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Out0_Process
* Description    : Process the OUT token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Out0_Process(void)
{
  uint32_t ControlState = pInformation->ControlState;

  if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  {
    /* host aborts the transfer before finish */
    ControlState = STALLED;
  }
  else if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA))
  {
    DataStageOut();
    ControlState = pInformation->ControlState; /* may be changed outside the function */
  }

  else if (ControlState == WAIT_STATUS_OUT)
  {
    (*pProperty->Process_Status_OUT)();		  //���Ǹ��պ�����ʲô��������
  #if !IsDensity(CL)
    ControlState = STALLED;
  #endif
  }

  /* Unexpect state, STALL the endpoint */
  else
  {
    ControlState = STALLED;
  }

  pInformation->ControlState = ControlState;

  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Post0_Process
* Description    : Stall the Endpoint 0 in case of error.
* Input          : None.
* Output         : None.
* Return         : - 0 if the control State is in PAUSE
*                  - 1 if not.
*******************************************************************************/
uint8_t Post0_Process(void)
{
#if IsDensity(CL)
  USB_OTG_EP *ep;
#endif
      
  USB_SetRXCount(0, Device_Property.MaxPacketSize);		  //���˵�0�Ļ�������С����

  if (pInformation->ControlState == STALLED)
  {
    //vSetEPRxStatus(EP_RX_STALL);vSetEPTxStatus(EP_TX_STALL);		  
		DUSB.RXSTAT=USB_EPR_STAT_STALL; DUSB.TXSTAT=USB_EPR_STAT_STALL;//���˵�ķ��ͺͽ��ն����óɣ�STALL������״̬��ֻ����SETUP���ư�
  }

#if IsDensity(CL)
  else if ((pInformation->ControlState == OUT_DATA) ||
      (pInformation->ControlState == WAIT_STATUS_OUT))
  {
    ep = PCD_GetInEP(0);
    ep->is_in = 0;
    OTGD_FS_EP0StartXfer(ep);
    
    //vSetEPTxStatus(EP_TX_VALID);
	  DUSB.TXSTAT=USB_EPR_STAT_VALID;
  }
  
  else if ((pInformation->ControlState == IN_DATA) || 
      (pInformation->ControlState == WAIT_STATUS_IN))
  {
    ep = PCD_GetInEP(0);
    ep->is_in = 1;
    OTGD_FS_EP0StartXfer(ep);    
  }  
#endif

  return (pInformation->ControlState == PAUSE);
}


void NOP_Process(void)
{
}

//------------------------------------------------------------------------------------------------------------------------------
//<usb_init.c>
DEVICE_INFO *pInformation;
DEVICE_PROP *pProperty;
DEVICE_INFO	Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;
//------------------------------------------------------------------------------------------------------------------------------
void USB_Init(void)
{
 	USB.MDL=USB_MDL_USB1;
  pInformation = &Device_Info;
  pInformation->ControlState = 2;	   	// IN_DATA
  pProperty = &Device_Property;			//ָ�뺯��
  pUser_Standard_Requests = &User_Standard_Requests;
  pProperty->Init();
}
//------------------------------------------------------------------------------------------------------------------------------
//<usb_int.c>
//------------------------------------------------------------------------------------------------------------------------------
#if !IsDensity(CL)
void CTR_LP(void)//�˵�����ȼ��жϴ���
{
	while(USB.ISTR_BIT.CTR)	
  {
    DUSB.EPIndex =USB.ISTR_BIT.EPID;
    if (DUSB.EPIndex == 0)
    {
			DUSB.RXSTAT=USB.EPR_BIT[0].RXSTAT; DUSB.TXSTAT=USB.EPR_BIT[0].TXSTAT;USB_SetRXTXSTAT(0,USB_EPR_STAT_NAK,USB_EPR_STAT_NAK);			
			if(!USB.ISTR_BIT.DIR)//���DIR��0����Ӧ�˵��CTR_TXλ����λ����־һ��IN����(���ݴ�USBģ�鴫�䵽PC����)
		  {
				USB.EPR[0]&=0x8F0F;In0_Process();
      }
      else//���DIR��1����Ӧ�˵��CTR_RXλ����λ����־һ��OUT����(���ݴ�PC�������䵽USBģ��)�Ĵ�����ɡ�
      {
        USB.EPR[0]&=0x0F8F;if(USB.EPR_BIT[0].SETUP){Setup0_Process();} else {if (USB.EPR_BIT[0].RXCTR)Out0_Process(); else return;}
      }
		  USB_SetRXTXSTAT(0,DUSB.RXSTAT,DUSB.TXSTAT);
    }
    else//EPindex ��= 0
    {
			if(USB.EPR_BIT[DUSB.EPIndex].RXCTR)
      {USB.EPR[DUSB.EPIndex]&=0x0F8F; if(DUSB.EPIndex==USB_RXEPIndex)USB_ReadBUF(DUSB.EPIndex); USB_SetRXSTAT(DUSB.EPIndex,USB_EPR_STAT_VALID);}
			if(USB.EPR_BIT[DUSB.EPIndex].TXCTR)
      {USB.EPR[DUSB.EPIndex]&=0x8F0F; if(DUSB.EPIndex==USB_TXEPIndex){COM_TXItem_On(SDK_USB_Index)=0;DCOM[SDK_USB_Index].TF.TXItem_ErrorCount=0x00;if(DCOM[SDK_USB_Index].TF.Count==0x0000)COM_TX_On(SDK_USB_Index)=0;}}
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void CTR_HP(void)//�˵�����ȼ��жϴ���
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
#endif
//------------------------------------------------------------------------------------------------------------------------------
//==============================================================================================================================
//<USB>
//<hw_config.c>
bool HSEStartUpStatus;
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
//------------------------------------------------------------------------------------------------------------------------------
void Set_System(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	  RCC.APB2ENR_BIT.IOPAEN=1; RCC.APB2ENR_BIT.IOPCEN=1;RCC.APB2ENR_BIT.IOPFEN=1;
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//?????????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PT_GPIOA, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------------------------------------------------------
void Set_USBClock(void)
{
	RCC.APB1ENR_BIT.USBEN=0;  
	RCC.CFGR_BIT.USBPRE=0;//72/1.5=48MHz
	RCC.APB1ENR_BIT.USBEN=1;  
}
//------------------------------------------------------------------------------------------------------------------------------
void Enter_LowPowerMode(void)
{
  USB_On=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void Leave_LowPowerMode(void)
{
  DUSB.DEVState = USB_STATE_SUSPENDED;//Set the device state to suspend
  USB_On=0;//�������ڼ���Ƿ��ʼ����ɵĴ��� 
  USB_Init(); //���ڰβ�����³�ʼ��USB�˿�,�ͷű�ռ�õĶ˿ںͻ�����
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Interrupts_Config(unsigned char UsbModule)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	M3SYS.AIRCR_BIT.PRIGROUP=PRIGROUP_2;//NVIC_PriorityGroup_2
  SETIRQ(IRQN_USB1LP_CAN1RX0,2,0); 	
  SETIRQ(IRQN_USBWakeUp,1,0);
	
	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd =1;
	NVIC_Init(&NVIC_InitStructure); 	 
}   
/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(volatile uint32_t*)(0x1FFFF7E8);
  Device_Serial1 = *(volatile uint32_t*)(0x1FFFF7EC);
  Device_Serial2 = *(volatile uint32_t*)(0x1FFFF7F0);

  Device_Serial0 += Device_Serial2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &CustomHID_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &CustomHID_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[ 2* idx + 1] = 0;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
//<usb_istr.c>

volatile uint8_t bIntPackSOF = 0;//SOFs received between 2 consecutive packets

#if !IsDensity(CL)
//------------------------------------------------------------------------------------------------------------------------------
void USB_Istr(void)				 //�жϴ���������������ʼ������λ��������ȷ���롢���
{
  if(USB.ISTR_BIT.CTR && USB.CNTR_BIT.CTRM){USB.ISTR_BIT.CTR=0;CTR_LP();}
  if(USB.ISTR_BIT.RST && USB.CNTR_BIT.RSTM){USB.ISTR_BIT.RST=0;CustomHID_Reset();}
  if(USB.ISTR_BIT.DOVR && USB.CNTR_BIT.DOVRM){USB.ISTR_BIT.DOVR=0;USB_OVR_CallBack();}
  if(USB.ISTR_BIT.ERR && USB.CNTR_BIT.ERRM){USB.ISTR_BIT.ERR=0;USB_ERR_CallBack();}
  if(USB.ISTR_BIT.WKUP && USB.CNTR_BIT.WKUPM){USB.ISTR_BIT.WKUP=0;USB_Resume(USB_RESUME_EXTERNAL);}
  if(USB.ISTR_BIT.SUSP && USB.CNTR_BIT.SUSPM){USB.ISTR_BIT.SUSP=0; if(USB_Suspend_EN)USB_Suspend();else  USB_Resume(USB_RESUME_LATER);}
  if(USB.ISTR_BIT.SOF && USB.CNTR_BIT.SOFM){USB.ISTR_BIT.SOF=0; USB_SOF_CallBack();}
  if(USB.ISTR_BIT.ESOF && USB.CNTR_BIT.ESOFM){USB.ISTR_BIT.ESOF=0; USB_Resume(USB_RESUME_ESOF);} // request without change of the machine state 
}
#else 

/*******************************************************************************
* Function Name  : STM32_PCD_OTG_ISR_Handler
* Description    : Handles all USB Device Interrupts
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
u32 STM32_PCD_OTG_ISR_Handler (void)
{
  USB_OTG_GINTSTS_TypeDef gintr_status;
  u32 retval = 0;

  if (USBD_FS_IsDeviceMode()) /* ensure that we are in device mode */
  {
    gintr_status.d32 = OTGD_FS_ReadCoreItr();

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    
    /* If there is no interrupt pending exit the interrupt routine */
    if (!gintr_status.d32)
    {
      return 0;
    }

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Early Suspend interrupt */ 
#ifdef INTR_ERLYSUSPEND
    if (gintr_status.b.erlysuspend)
    {
      retval |= OTGD_FS_Handle_EarlySuspend_ISR();
    }
#endif /* INTR_ERLYSUSPEND */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* End of Periodic Frame interrupt */
#ifdef INTR_EOPFRAME    
    if (gintr_status.b.eopframe)
    {
      retval |= OTGD_FS_Handle_EOPF_ISR();
    }
#endif /* INTR_EOPFRAME */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Non Periodic Tx FIFO Emty interrupt */
#ifdef INTR_NPTXFEMPTY    
    if (gintr_status.b.nptxfempty)
    {
      retval |= OTGD_FS_Handle_NPTxFE_ISR();
    }
#endif /* INTR_NPTXFEMPTY */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Wakeup or RemoteWakeup interrupt */
#ifdef INTR_WKUPINTR    
    if (gintr_status.b.wkupintr)
    {   
      retval |= OTGD_FS_Handle_Wakeup_ISR();
    }
#endif /* INTR_WKUPINTR */   
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Suspend interrupt */
#ifdef INTR_USBSUSPEND
    if (gintr_status.b.usbsuspend)
    { 
      /* check if SUSPEND is possible */
      if (fSuspendEnabled)
      {
        Suspend();
      }
      else
      {
        /* if not possible then resume after xx ms */
        Resume(RESUME_LATER); /* This case shouldn't happen in OTG Device mode because 
        there's no ESOF interrupt to increment the ResumeS.bESOFcnt in the Resume state machine */
      }
            
      retval |= OTGD_FS_Handle_USBSuspend_ISR();
    }
#endif /* INTR_USBSUSPEND */

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Start of Frame interrupt */
#ifdef INTR_SOFINTR    
    if (gintr_status.b.sofintr)
    {
      /* Update the frame number variable */
      bIntPackSOF++;
      
      retval |= OTGD_FS_Handle_Sof_ISR();
    }
#endif /* INTR_SOFINTR */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Receive FIFO Queue Status Level interrupt */
#ifdef INTR_RXSTSQLVL
    if (gintr_status.b.rxstsqlvl)
    {
      retval |= OTGD_FS_Handle_RxStatusQueueLevel_ISR();
    }
#endif /* INTR_RXSTSQLVL */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Enumeration Done interrupt */
#ifdef INTR_ENUMDONE
    if (gintr_status.b.enumdone)
    {
      retval |= OTGD_FS_Handle_EnumDone_ISR();
    }
#endif /* INTR_ENUMDONE */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* Reset interrutp */
#ifdef INTR_USBRESET
    if (gintr_status.b.usbreset)
    {
      retval |= OTGD_FS_Handle_UsbReset_ISR();
    }    
#endif /* INTR_USBRESET */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    /* IN Endpoint interrupt */
#ifdef INTR_INEPINTR
    if (gintr_status.b.inepint)
    {
      retval |= OTGD_FS_Handle_InEP_ISR();
    }
#endif /* INTR_INEPINTR */
    
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* OUT Endpoint interrupt */
#ifdef INTR_OUTEPINTR
    if (gintr_status.b.outepintr)
    {
      retval |= OTGD_FS_Handle_OutEP_ISR();
    }
#endif /* INTR_OUTEPINTR */    
 
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Mode Mismatch interrupt */
#ifdef INTR_MODEMISMATCH
    if (gintr_status.b.modemismatch)
    {
      retval |= OTGD_FS_Handle_ModeMismatch_ISR();
    }
#endif /* INTR_MODEMISMATCH */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Global IN Endpoints NAK Effective interrupt */
#ifdef INTR_GINNAKEFF
    if (gintr_status.b.ginnakeff)
    {
      retval |= OTGD_FS_Handle_GInNakEff_ISR();
    }
#endif /* INTR_GINNAKEFF */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Global OUT Endpoints NAK effective interrupt */
#ifdef INTR_GOUTNAKEFF
    if (gintr_status.b.goutnakeff)
    {
      retval |= OTGD_FS_Handle_GOutNakEff_ISR();
    }
#endif /* INTR_GOUTNAKEFF */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Isochrounous Out packet Dropped interrupt */
#ifdef INTR_ISOOUTDROP
    if (gintr_status.b.isooutdrop)
    {
      retval |= OTGD_FS_Handle_IsoOutDrop_ISR();
    }
#endif /* INTR_ISOOUTDROP */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Endpoint Mismatch error interrupt */
#ifdef INTR_EPMISMATCH
    if (gintr_status.b.epmismatch)
    {
      retval |= OTGD_FS_Handle_EPMismatch_ISR();
    }
#endif /* INTR_EPMISMATCH */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Incomplete Isochrous IN tranfer error interrupt */
#ifdef INTR_INCOMPLISOIN
    if (gintr_status.b.incomplisoin)
    {
      retval |= OTGD_FS_Handle_IncomplIsoIn_ISR();
    }
#endif /* INTR_INCOMPLISOIN */  

   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/    
    /* Incomplete Isochrous OUT tranfer error interrupt */
#ifdef INTR_INCOMPLISOOUT
    if (gintr_status.b.outepintr)
    {
      retval |= OTGD_FS_Handle_IncomplIsoOut_ISR();
    }
#endif /* INTR_INCOMPLISOOUT */  
  
  }
  return retval;
}
#endif
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Init(void)
{

  /* Update the serial number string descriptor with the data from the unique
  ID*/
  Get_SerialNum();

  pInformation->Current_Configuration = 0;				 //configuration=0��ʲô���ã�
  /* Connect the device */
  USB_PowerOn();
#if !IsDensity(CL)
	USB_ISTR=0x0000;USB_CNTR=0xBF00;//clear pending interrupts
#else
  OTG_DEV_Init();//Perform OTG Device initialization procedure (including EP0 init)
#endif

  DUSB.DEVState = USB_STATE_UNCONNECTED;
}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Reset(void)
{
  /* Set CustomHID_DEVICE as not configured */
  pInformation->Current_Configuration = 0;
  pInformation->Current_Interface = 0;/*the default Interface*/

  /* Current Feature initialization */
  pInformation->Current_Feature = CustomHID_ConfigDescriptor[7];

#if IsDensity(CL)
  /* EP0 is already configured in DFU_Init() by USB_SIL_Init() function */
  
  /* Init EP1 IN as Interrupt endpoint */
  OTG_DEV_EP_Init(EP1_IN, OTG_DEV_EP_TYPE_INT, 4);
#else 
  USB_BUFTAB=USB_BUFTAB_Value&0xFFF8;
	//Initialize Endpoint 0
	USB_SetEPType(0,USB_EPR_TYPE_CONTROL);
	USB_SetTXSTAT(0,USB_EPR_STAT_STALL);
	USB.CH[0].RXADDR=(DUSB.RXADDR[0]-BASE_USBRAM)>>1;
	USB.CH[0].TXADDR=(DUSB.TXADDR[0]-BASE_USBRAM)>>1;
	USB_Clear_KIND(0);
	USB_SetRXCount(0,DUSB.EPSIZE[0]);//  Device_Property.MaxPacketSize
	USB_SetRXSTAT(0,USB_EPR_STAT_VALID);

  //Initialize Endpoint 1 �ӻ���
	USB_SetEPType(1,USB_EPR_TYPE_BULK);
  USB.CH[1].RXADDR =(DUSB.RXADDR[1]-BASE_USBRAM)/2;
	USB_SetRXCount(1,DUSB.EPSIZE[1]);//�������ݳ��Ȳ�����Ϊ������ֻ���ǳ���
	USB_SetRXSTAT(1, USB_EPR_STAT_VALID);

  //Initialize Endpoint 2 �ӻ���
  USB_SetEPType(2,USB_EPR_TYPE_BULK);
  USB.CH[2].TXADDR=(DUSB.TXADDR[2]-BASE_USBRAM)/2;
	USB.CH[2].TXCOUNT=DUSB.EPSIZE[2];//������Ϊ�����������ˣ�ʹ��ÿ�����ݳ��ȶ����ܳ������õ���
  USB_SetTXSTAT(2,USB_EPR_STAT_DIS);
	USB_SetTXSTAT(2,USB_EPR_STAT_NAK);
  // Set this device to response on default address
  USB_SetAddress(0);
#endif

  DUSB.DEVState = USB_STATE_ATTACHED;
}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    DUSB.DEVState = USB_STATE_CONFIGURED;
  }
}

//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Status_In(void)
{}
//------------------------------------------------------------------------------------------------------------------------------
void CustomHID_Status_Out (void)
{}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;
  if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndex0 == 0))
  {

    if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
    {
      CopyRoutine = CustomHID_GetReportDescriptor;
      USB_On=1;//�������ڼ���Ƿ��ʼ����ɵĴ���
    }
    else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
    {
      CopyRoutine = CustomHID_GetHIDDescriptor;
    }

  } /* End of GET_DESCRIPTOR */

  /*** GET_PROTOCOL ***/
  else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
  {
    CopyRoutine = CustomHID_GetProtocolValue;
  }


  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_NoData_Setup(uint8_t RequestNo)
{
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return CustomHID_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetReportDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetHIDDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
USB_RESULT CustomHID_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}
//------------------------------------------------------------------------------------------------------------------------------
uint8_t *CustomHID_GetProtocolValue(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}
//------------------------------------------------------------------------------------------------------------------------------
//<usb_pwr.c>
//------------------------------------------------------------------------------------------------------------------------------
void USB_PowerOn(void)
{
  GPIO[0].ODR_BIT.B10=0;//Enable pushpull 1.5k
	USB.CNTR_BIT.FRES =1;USB_CNTR=0x0000;USB_ISTR=0x0000;USB_CNTR=0x1C00;//Force Reset;clear interrup;clear pending;RSTM=SUSPM=WKUPM=1
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_PowerOff(void)
{
	USB_CNTR=0x0001;USB_ISTR=0x0000;USB_CNTR=0x0003;	
	GPIO[0].ODR_BIT.B10=1;//Disable pushpull 1.5k
}
//------------------------------------------------------------------------------------------------------------------------------
void Resume_Init(void)
{
  USB_On=0;DUSB.DEVState = USB_STATE_SUSPENDED;
  USB.CNTR_BIT.LPMODE=0;
  USB_Init(); //���ڰβ�����³�ʼ��USB�˿�,�ͷű�ռ�õĶ˿ںͻ�����	
	USB_CNTR=0xBF00;//CTRM=WKUPM=SUSPM=ERRM=SOFM=ESOFM=RESETM=1
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Resume(USB_RESUME_STATE eResumeSetVal)
{
  if (eResumeSetVal != USB_RESUME_ESOF)  DUSB.ResumeS.eState = eResumeSetVal;
  switch (DUSB.ResumeS.eState)
  {
    case USB_RESUME_EXTERNAL:
      Resume_Init(); DUSB.ResumeS.eState = USB_RESUME_OFF;
      break;
    case USB_RESUME_INTERNAL:
      Resume_Init(); DUSB.ResumeS.eState = USB_RESUME_START;
      break;
    case USB_RESUME_LATER:
      DUSB.ResumeS.bESOFcnt = 2; DUSB.ResumeS.eState = USB_RESUME_WAIT;
      break;
    case USB_RESUME_WAIT:
      DUSB.ResumeS.bESOFcnt--; if (DUSB.ResumeS.bESOFcnt == 0) DUSB.ResumeS.eState = USB_RESUME_START;
      break;
    case USB_RESUME_START:
		  USB.CNTR_BIT.RESUME=1; DUSB.ResumeS.bESOFcnt = 10; DUSB.ResumeS.eState = USB_RESUME_ON;
      break;
    case USB_RESUME_ON:
      DUSB.ResumeS.bESOFcnt--; if (DUSB.ResumeS.bESOFcnt == 0){USB.CNTR_BIT.RESUME=0; DUSB.ResumeS.eState = USB_RESUME_OFF;}
      break;
    case USB_RESUME_OFF:
    case USB_RESUME_ESOF:
    default:
      DUSB.ResumeS.eState = USB_RESUME_OFF;
      break;
  }
}
//==============================================================================================================================
//<ProtocolStack_USB.c>
//------------------------------------------------------------------------------------------------------------------------------
void USB_ReadBUF(UINT8 EPIndex)
{
	volatile UINT32 *P;UINT16 *PUser;
  P=(volatile UINT32 *)DUSB.RXADDR[EPIndex];PUser=(UINT16 *)DCOM[SDK_USB_Index].RF.Item;
	DCOM[SDK_USB_Index].RF.Index=0x0000;DCOM[SDK_USB_Index].RF.Verify=0x00;IRQINT[1]=USB.CH[1].RXCOUNT&0x3FF;	if(IRQINT[1]<4)return;
	for(IRQINT[0]=0;IRQINT[0]<(IRQINT[1]+1)/2;IRQINT[0]++)
	{
	  (*PUser)=(*P);
		if(IRQINT[0]==0)
		{ if(((*P)&0xFFFF)!=0xAA55)return;}
		else if(IRQINT[0]==1)
		{ 
			DCOM[SDK_USB_Index].RF.Control=DCOM[SDK_USB_Index].RF.Item[2];DCOM[SDK_USB_Index].RF.Command=DCOM[SDK_USB_Index].RF.Item[3];
		  if(DCOM[SDK_USB_Index].RF.Control&Control_SF){DCOM[SDK_USB_Index].RF.ParaCount=0x0000;break;}
			if(IRQINT[1]<7)break;
		} 
		else if(IRQINT[0]==2)
    { DCOM[SDK_USB_Index].RF.ParaCount=(*P)&0xFFFF;PUser=(UINT16 *)DCOM[SDK_USB_Index].RF.Item;IRQINT[1]=DCOM[SDK_USB_Index].RF.ParaCount+7;
		  if(IRQINT[1]>DUSB.EPSIZE[EPIndex]||IRQINT[1]>USB.CH[1].RXCOUNT)return;
		}
		else 
		{ DCOM[SDK_USB_Index].RF.Verify+=(USB.RXBUF1[IRQINT[0]]+(USB.RXBUF1[IRQINT[0]]>>8));}
		P++;PUser++;
	}
	if(DCOM[SDK_USB_Index].RF.ParaCount)
	{
	  for(IRQINT[0]=0;IRQINT[0]<DCOM[SDK_USB_Index].RF.ParaCount;IRQINT[0]++) DCOM[SDK_USB_Index].RF.Verify+=DCOM[SDK_USB_Index].RF.Item[IRQINT[0]];
		if(DCOM[SDK_USB_Index].RF.Verify!=DCOM[SDK_USB_Index].RF.Item[DCOM[SDK_USB_Index].RF.Index-1])return;
	}
	USB_On=1;DUSB.RXPACKCount++;	DAPP.IRQ_ReadParameter(SDK_UART_Index,DCOM[SDK_USB_Index].RF.Item,DCOM[SDK_USB_Index].RF.ParaCount);
}	
//------------------------------------------------------------------------------------------------------------------------------
void USB_SendBUF(UINT8 EPIndex)
{
	UINT16 i,j,Len,Temp,*P;
	P=(UINT16 *)DUSB.TXADDR[EPIndex];
	j=(DCOM[SDK_USB_Index].TF.Index+SIZE_USB_TBUF-DCOM[SDK_USB_Index].TF.Count)%SIZE_USB_TBUF;
	Len=DCOM[SDK_USB_Index].TF.Item[j];j=(j+1)%SIZE_USB_TBUF; Len+=((UINT16)DCOM[SDK_USB_Index].TF.Item[j]<<8);j=(j+1)%SIZE_USB_TBUF;
	for(i=0; i <(Len+1)/2; i++)
  {Temp=DCOM[SDK_USB_Index].TF.Item[j];j=(j+1)%SIZE_USB_TBUF;	Temp+=((UINT16)DCOM[SDK_USB_Index].TF.Item[j]<<8);j=(j+1)%SIZE_USB_TBUF;*P=Temp;P+=2;}
	DCOM[SDK_USB_Index].TF.Count-=(Len+2);USB.CH[EPIndex].TXCOUNT=(USB_DMLenth_EN ? Len:DUSB.EPSIZE[USB_TXEPIndex]);	USB_SetTXSTAT(EPIndex, USB_EPR_STAT_VALID);
	DCOM[SDK_USB_Index].TF.TXItem_TimeCount=0x00;DCOM[SDK_USB_Index].TF.TXItem_Time=50; COM_TXItem_On(SDK_USB_Index)=1;//Tx Timeout minitor=50*100us=5ms
	DUSB.TXPACKCount++; 
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_StartSend(void)
{
	COM_TX_On(SDK_USB_Index) =1;COM_TXItem_On(SDK_USB_Index)=0;IMM_Event_On=1; USB_SendBUF(USB_TXEPIndex);
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_EndSend(void)
{
	COM_TXItem_On(SDK_USB_Index)=0;COM_TX_On(SDK_USB_Index)=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_WaitSend(void)//�ȴ�������ϣ��ж�����ã�,��ʱ1��
{
	UINT32 T;
	T=DDEV.TimeCount;
	while(USB_On && (COM_TX_On(SDK_USB_Index)||COM_TXItem_On(SDK_USB_Index)) && DDEV.TimeCount-T<1000)USB_Send_IMM();
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_SendString_HW(UINT8 *s,UINT16 Len)//���͵�Ӳ�����ж�����ã�
{
	UINT16 i;
	if(!USB_On||Len==0x0000||Len>DUSB.EPSIZE[USB_TXEPIndex])return;
	for(i=0; i <(Len+1)/2; i++){*(UINT16 *)(DUSB.TXADDR[USB_TXEPIndex]+4*i)=*(UINT16 *)s;s+=2;}
	USB.CH[USB_TXEPIndex].TXCOUNT=(USB_DMLenth_EN ? Len:DUSB.EPSIZE[USB_TXEPIndex]);USB_SetTXSTAT(USB_TXEPIndex, USB_EPR_STAT_VALID);
	DCOM[SDK_USB_Index].TF.TXItem_TimeCount=0x00;DCOM[SDK_USB_Index].TF.TXItem_Time=45;COM_TX_On(SDK_USB_Index)=1;COM_TXItem_On(SDK_USB_Index)=1;//Tx Timeout minitor=45*100us=4.5ms
	DUSB.TXPACKCount++;
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_SendString(UINT8 *s,UINT16 Len)//���͵����У��ж�����ã�
{
	UINT16 i;
	if(!USB_On||Len==0x0000||Len>DUSB.EPSIZE[USB_TXEPIndex])return;//�����ȼ��
	if(!COM_TX_On(SDK_USB_Index) && DCOM[SDK_USB_Index].TF.Count==0x0000){COM_TX_On(SDK_USB_Index) =1;USB_SendString_HW(s,Len);return;}//�������ͼ��
	while(DCOM[SDK_USB_Index].TF.Count+Len+2>SIZE_USB_TBUF && USB_On){if(!COM_TXItem_On(SDK_USB_Index))USB_SendBUF(USB_TXEPIndex);}//�����������
	COM_TXString_On(SDK_USB_Index)=1;
	DCOM[SDK_USB_Index].TF.Item[DCOM[SDK_USB_Index].TF.Index]=Len&0xFF;DCOM[SDK_USB_Index].TF.Index=(DCOM[SDK_USB_Index].TF.Index+1)%SIZE_USB_TBUF;
	DCOM[SDK_USB_Index].TF.Item[DCOM[SDK_USB_Index].TF.Index]=Len>>8;DCOM[SDK_USB_Index].TF.Index=(DCOM[SDK_USB_Index].TF.Index+1)%SIZE_USB_TBUF;
	for(i=0;i<Len;i++){DCOM[SDK_USB_Index].TF.Item[DCOM[SDK_USB_Index].TF.Index]=s[i];DCOM[SDK_USB_Index].TF.Index=(DCOM[SDK_USB_Index].TF.Index+1)%SIZE_USB_TBUF;};
	DCOM[SDK_USB_Index].TF.Count+=(Len+2);COM_TXString_On(SDK_USB_Index)=0;
	if(!COM_TX_On(SDK_USB_Index))USB_StartSend();else IMM_Event_On=1;
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_TXTimeOut_Timer(void)//every 100us,send timeout control
{
	if(!COM_TXItem_On(SDK_USB_Index))return;
	DCOM[SDK_USB_Index].TF.TXItem_TimeCount++; 
  if(DCOM[SDK_USB_Index].TF.TXItem_TimeCount>DCOM[SDK_USB_Index].TF.TXItem_Time)
  {
		COM_TXItem_On(SDK_USB_Index)=0;if(DCOM[SDK_USB_Index].TF.Count==0x0000)COM_TX_On(SDK_USB_Index)=0;
	  DCOM[SDK_USB_Index].TF.TXItem_ErrorCount++;if(DCOM[SDK_USB_Index].TF.TXItem_ErrorCount>=5){USB_Reset_On=1;INT_Event_On=1;}
	}
}
//------------------------------------------------------------------------------------------------------------------------------
void USB_Send_IMM(void)//���������¼�
{
	if(!USB_On||!COM_TX_On(SDK_USB_Index))return;
  if(COM_TXItem_On(SDK_USB_Index)){IMM_Event_On=1; return;} 
	if(DCOM[SDK_USB_Index].TF.Count){IMM_Event_On=1; USB_SendBUF(USB_TXEPIndex);}	else USB_EndSend();
}
//==============================================================================================================================
