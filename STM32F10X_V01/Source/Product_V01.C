//------------------------------------------------------------------------------------------------------------------------------
#include "Global.h"
//------------------------------------------------------------------------------------------------------------------------------
void APP_IMM_Event(void)
{
  Key_DoEvent_IMM();
  if(!IMM_Event_On)DT_RefreshMiniSecond();
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_INT_Event(void)
{
  #if SDK_COM_COUNT
  if(Read_DPStr_On)Read_DPStr();
	if(SendState_On)Send_State();
	if(Device_PWSet_On)SetPWState();
  if(Write_BaseDT_On)Write_BaseDT();  
  if(Write_MadeDT_On)Write_MadeDT();
  if(Write_HS_On)Write_HS();
  if(Write_NSN_On)Write_NSN();
  if(COM_Frame_Received){COM_Frame_Received=DLED.TimeCount[0]=0;LED_RX_On=PO_LED_RX=1;}
  if(COM_Frame_Sended){COM_Frame_Sended=DLED.TimeCount[1]=0;LED_TX_On=PO_LED_TX=1;}  
  #endif
	if(Device_Reset_On)Device_Reset();
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_TMR_Event(void)
{
  TMR_Event_On=0;
  APP_TMR(1);TMRCount[1]++;if(TMRCount[1]<2) return;TMRCount[1]=0x00;
  APP_TMR(2);TMRCount[2]++;if(TMRCount[2]<10)return;TMRCount[2]=0x00;
  APP_TMR(3);TMRCount[3]++;if(TMRCount[3]<10)return;TMRCount[3]=0x00;
  APP_TMR(4);
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_TMR(UINT8 Index)
{
  switch(Index)
  {
    case 0://1ms
      #if SDK_COM_COUNT
      COM_LED_Timer();
      COM_Packet_Timer();
      #if SDK_USB_COUNT
      USB_Send_Timer();
      #endif
      #endif
      PVR_RX_Timer();
      break;
    case 1://5ms
      Key_RX_Timer();
      break;
    case 2://10ms
      #if SDK_COM_COUNT
	    COM_Connect_Timer();
      #endif
      break;
    case 3://100ms
      break;
    case 4://1000ms
	    DT_Timer(&DAPP.DT);
      break;
    default:
      break;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_Init(UINT8 IsAfter)
{
  if(!IsAfter)
  {Dentify=0;}
  else
  {
	  Init_Chips();
    Para_Default();
    Para_Read();
    PowerOn();
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void Para_WriteItem(UINT16 Offset,UINT8 *s,UINT16 sLen)
{
  if(Offset+sLen>AppPara_Len)return;
  Flash_WriteItem((UINT32)&AppPara+Offset,s,sLen); 
}  
//------------------------------------------------------------------------------------------------------------------------------
void Para_ReadItem(UINT16 Offset,UINT8 *s,UINT16 sLen)
{
  if(Offset+sLen>AppPara_Len)return;
  if(!DC_Inited&& Flash_IsNew())Para_Write();Flash_ReadString((UINT32)&AppPara+Offset,s,sLen);  
}
//------------------------------------------------------------------------------------------------------------------------------
void Para_Default(void)
{
  DAPP.INTF.IMM_Event=APP_IMM_Event;
  DAPP.INTF.INT_Event=APP_INT_Event;
  DAPP.INTF.TMR_Event=APP_TMR_Event;
  DAPP.INTF.TMR=APP_TMR;
  DAPP.INTF.Init=APP_Init;
  DAPP.INTF.IRQ_TIM=APP_IRQ_TIM;
  DAPP.INTF.ADC_Control=APP_ADC_Control;
  DAPP.INTF.DMA_Control=APP_DMA_Control;
  DAPP.INTF.EXTI_Control=APP_EXTI_Control;
  #if SDK_COM_COUNT
  DAPP.INTF.COM_ReadPacket=COM_ReadPacket;
  DAPP.INTF.COM_ReadParameter=COM_ReadParameter;
  #endif
  Device_On=1;
}
//------------------------------------------------------------------------------------------------------------------------------
void Para_Write(void)
{
  ValueToStr(DAPP.TBUF+AppPara_RunTime,DDEV.Item[0].RunTime,4);
  ValueToStr(DAPP.TBUF+AppPara_RunCount,DDEV.Item[0].RunCount,4);
  Para_WriteItem(0,DAPP.TBUF,AppPara_Len);
}
//------------------------------------------------------------------------------------------------------------------------------
void Para_Read(void)
{
  Para_ReadItem(0,DAPP.TBUF,AppPara_Len);
  DDEV.Item[0].RunTime=StrToValue(DAPP.TBUF+AppPara_RunTime,4);
  DDEV.Item[0].RunCount=StrToValue(DAPP.TBUF+AppPara_RunCount,4);  
}
//------------------------------------------------------------------------------------------------------------------------------
void Init_Chips(void)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void PowerOn(void)
{
  DDEV.Item[0].RunCount++;ValueToStr(DAPP.TBUF,DDEV.Item[0].RunCount,4); Para_WriteItem(AppPara_RunCount,DAPP.TBUF,4); 
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_IRQ_TIM(UINT8 Index)
{
  switch(Index)
  {
    case 1://TIM2=100us
      if(MicroTimeCount<9)MicroTimeCount++;
      #if SDK_COM_COUNT
      COM_Send_Timer();
      #if SDK_USB_COUNT
      USB_TXTimeOut_Timer();
      #endif
      #endif
      break;
    case 2:break;
    case 3:break;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void APP_ADC_Control(UINT8 Index)
{
}  
//------------------------------------------------------------------------------------------------------------------------------
void APP_DMA_Control(UINT8 Index,UINT8 CHIndex)
{
}  
//------------------------------------------------------------------------------------------------------------------------------
void APP_EXTI_Control(UINT8 Index)
{
}
//==============================================================================================================================
void Para_Save_Timer(void)//every 100ms
{
  if(!Para_Save_On)return;
  Para_Save_TimeCount++;if(Para_Save_TimeCount>=AppPara_Area_DelayTime[AppPara_Area]){Para_Save_On=0;Para_Write();}//10s
}
//==============================================================================================================================
void SetSleepOn(UINT8 EN)
{
  SleepTimeCount=0x00;if(Sleep_On==EN)return;Sleep_On=EN;//  PO_LCD_LED=!Sleep_On;
}
//------------------------------------------------------------------------------------------------------------------------------
void Sleep_Timer(void)//every 100ms
{
  if(Sleep_On)return;  SleepTimeCount++; if(SleepTimeCount>=100)SetSleepOn(1);
}
//==============================================================================================================================
void Key_GetState(void)
{
	DKEY.TempState =0x0000;
	if(PI_KEY1)DKEY.TempState|=1;
  if(PI_KEY2)DKEY.TempState|=2;
  if(PI_KEY3)DKEY.TempState|=4;
  if(PI_KEY4)DKEY.TempState|=8;
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 Key_KB_GetCode(unsigned char ScanState)
{
  #if SDK_KB_On
  for(Var[0]=0;Var[0]<SDK_KB_RowCount;Var[0]++){if(ScanState&(1<<Var[0]))break;}
  for(Var[1]=0;Var[1]<SDK_KB_ColCount;Var[1]++){if(ScanState&(1<<(Var[1]+SDK_KB_RowCount)))break;}
  TempFlag0=(Var[0]<SDK_KB_RowCount && Var[1]<SDK_KB_ColCount ? 1:0); DKEY.KB_Code=(TempFlag0 ? Var[0]*SDK_KB_ColCount+Var[1]:0xFF);
  #endif
  return TempFlag0;
}
//------------------------------------------------------------------------------------------------------------------------------
void Key_RX_Timer(void)//every 5ms
{
	Key_GetState();
	if(Key_Inited==0)
  {
    DKEY.Init_TimeCount++;if(DKEY.Init_TimeCount<100)return;
    #if SDK_Key_Count    
	  for(Var[0]=0;Var[0]<SDK_Key_Count;Var[0]++)
    {DKEY.TimeCount[Var[0]]=DKEY.RepeatTimeCount[Var[0]]=DKEY.LongTimeCount[Var[0]]=0x0000;}
	  DKEY.DownState=DKEY.RepeatState=DKEY.LongDowned=DKEY.LongDownState=0x0000;DKEY.ScanState=DKEY.TempState;DKEY.UpState=DKEY.TempState;
    #endif
    #if Key_CC_Count
    for(Var[0]=0;Var[0]<Key_CC_Count;Var[0]++)
    {DKEY.LongTimeIndex[Var[0]]=DKEY.CTimeCount[Var[0]]=0x0000;DKEY.CEN[Var[0]]=0x03; }
    #endif
    #if SDK_KB_On
    DKEY.KB_UpState=DKEY.KB_TempState;DKEY.KB_TimeCount=Key_KB_Down_On=0;
    #endif
    Key_Inited=1; return;
  }
  #if SDK_Key_Count
  INT[1]=DKEY.TempState^DKEY.ScanState;INT[0]=1;
	for(Var[0]=0;Var[0]<SDK_Key_Count;Var[0]++)
	{
		DKEY.Code=Var[0];
		if(INT[1]&INT[0])
		{
			DKEY.TimeCount[Var[0]]++;
			if(DKEY.TimeCount[Var[0]]>=Key_DebounceTime)
			{
				DKEY.ScanState^=INT[0];
				if((DKEY.ScanState^DKEY.UpState)&INT[0])
				{
					DKEY.DownState|=INT[0];
					if(Key_LongTime_Count && (Key_LongDown_EN&INT[0])){DKEY.LongDownState|=INT[0];DKEY.LongDowned&=~INT[0];DKEY.LongTimeIndex[Var[0]]=0x00; DKEY.LongTimeCount[Var[0]]=DKEY.TimeCount[Var[0]];}
					if(Key_Repeat_EN&INT[0]){DKEY.RepeatState|=INT[0]; DKEY.RepeatTimeCount[Var[0]]=DKEY.TimeCount[Var[0]];}
          Key_Save(Var[0],Key_EV_Down);
				}
        else
        {
					if(DKEY.DownState&INT[0])
          {
					  DKEY.DownState^=INT[0];
						if(!((Key_LongDown_EN&INT[0]) && (DKEY.LongDownState&INT[0])==0) && !((Key_Repeat_EN&INT[0]) &&  (DKEY.RepeatState&INT[0])==0))	Key_Save(Var[0],Key_EV_Press);
					}
					Key_Save(Var[0],(DKEY.LongDowned & INT[0] ? Key_EV_LongUp:Key_EV_Up));
        }
        DKEY.TimeCount[Var[0]]=0x00;
			}				
		}
		else if(DKEY.DownState&INT[0])
		{
			if(DKEY.LongDownState&INT[0])
			{
			  DKEY.LongTimeCount[Var[0]]++;
			  if(DKEY.LongTimeCount[Var[0]]>=Key_LongTime[DKEY.LongTimeIndex[Var[0]]])
        {
          DKEY.LongDowned|=INT[0];Key_Save(Var[0],Key_EV_LongDown+DKEY.LongTimeIndex[Var[0]]);DKEY.LongTimeIndex[Var[0]]++;
          if(DKEY.LongTimeIndex[Var[0]]>=Key_LongTime_Count)DKEY.LongDownState^=INT[0];
        }
			}
			if(Key_Repeat_EN&INT[0])
			{
				DKEY.RepeatTimeCount[Var[0]]++;
				if(DKEY.RepeatTimeCount[Var[0]]>=(DKEY.RepeatState&INT[0] ? Key_Repeat_FirstTime:Key_Repeat_Time)){DKEY.RepeatTimeCount[Var[0]]=0x0000;Key_Save(Var[0],Key_EV_Press);}		
			}
		}
		INT[0]<<=1;
	}
  #endif

  #if Key_CC_Count
  for(Var[0]=0;Var[0]<Key_CC_Count;Var[0]++)
  {
    INT[0]=(DKEY.TempState^DKEY.UpState)&Key_CC[Var[0]];
    if(INT[0]==Key_CC[Var[0]])
    {
      DKEY.CTimeCount[Var[0]]++;
      if((DKEY.CEN[Var[0]]&1) && (DKEY.CTimeCount[Var[0]]>=Key_DebounceTime))
      {Key_Save(Var[0]+SDK_Key_Count,Key_EV_CDown);DKEY.CEN[Var[0]]=(DKEY.CEN[Var[0]]&0xFE)|0x04;}
      else if(Key_LongTime_Count && (DKEY.CEN[Var[0]]&2) )//LongPress
      {
        if(DKEY.CTimeCount[Var[0]]>=Key_LongTime[DKEY.CLongTimeIndex[Var[0]]])
        {
          Key_Save(Var[0]+SDK_Key_Count,Key_EV_LongDown+DKEY.CLongTimeIndex[Var[0]]);DKEY.CLongTimeIndex[Var[0]]++;
          if(DKEY.CLongTimeIndex[Var[0]]>=Key_LongTime_Count)DKEY.CEN[Var[0]]&=0xFD;
        }
      }
    }
    else
    {
      DKEY.CTimeCount[Var[0]]=0x00;
      if(DKEY.CEN[Var[0]]&4){Key_Save(Var[0]+SDK_Key_Count,Key_EV_CUp);DKEY.CEN[Var[0]]=0x00;}
      if(INT[0]==0x0000){DKEY.CEN[Var[0]]=0x01|(Key_CC_LongDown_EN&(1<<Var[0]) ? 2:0);DKEY.CLongTimeIndex[Var[0]]=0x00;}
    }
  }
  #endif
  #if SDK_KB_On
  INT[1]=DKEY.KB_TempState^DKEY.KB_ScanState;
  if(INT[1]&(0xFFFF>>(16-SDK_KB_RowCount)) && INT[1]&(((1<<SDK_KB_ColCount)-1)<<SDK_KB_RowCount))
  {
    DKEY.KB_TimeCount++;
    if(DKEY.KB_TimeCount>=Key_DebounceTime)
    {
      DKEY.KB_ScanState^=INT[1];
      if(Key_KB_GetCode(INT[1]))
      {
        TempFlag0=((DKEY.KB_ScanState^DKEY.KB_UpState)&INT[1] ? 1:0);Key_KB_Down_On=TempFlag0;
        if(TempFlag0)
        {
          if(Key_LongTime_Count && SDK_KB_LongDown_EN ){DKEY.KB_LongTimeCount=DKEY.KB_TimeCount;Key_KB_LongDown_On=1;}
          if(SDK_KB_Repeat_EN){Key_KB_Repeat_State=1;DKEY.KB_RepeatTimeCount=DKEY.KB_TimeCount;}Key_KB_LongDowned=0;
        }  
        Key_Save(SDK_Key_Count+Key_CC_Count+DKEY.KB_Code,(TempFlag0 ? Key_EV_Down:(Key_KB_LongDowned ? Key_EV_LongUp:Key_EV_Up)));
      }
      else
      {Key_KB_Down_On=0;}
      DKEY.KB_TimeCount=0x00;
    }
  }
  else
  {
    DKEY.KB_TimeCount=0x00;
    if(Key_KB_Down_On)
    {
			if(Key_KB_LongDown_On)
			{
			  DKEY.KB_LongTimeCount++;
			  if(DKEY.KB_LongTimeCount>=Key_LongTime[DKEY.KB_LongTimeIndex])
        {
          Key_KB_LongDowned=1;Key_Save(SDK_Key_Count+Key_CC_Count+DKEY.KB_Code,Key_EV_LongDown+DKEY.KB_LongTimeIndex);DKEY.KB_LongTimeIndex++;
          if(DKEY.KB_LongTimeIndex>=Key_LongTime_Count)Key_KB_LongDown_On=0;
        }
			}
			if(SDK_KB_Repeat_EN)
			{
				DKEY.KB_RepeatTimeCount++;
				if(DKEY.KB_RepeatTimeCount>=(Key_KB_Repeat_State ? Key_Repeat_FirstTime:Key_Repeat_Time)){DKEY.KB_RepeatTimeCount=0x00;Key_Save(SDK_Key_Count+Key_CC_Count+DKEY.KB_Code,Key_EV_Press);}		
			}      
    }
  }   
  #endif
}
//------------------------------------------------------------------------------------------------------------------------------
void PVR_RX_Timer(void)//every 1ms
{
  #if SDK_PVR_Count
  DKEY.PVR_TempState=(PI_PVR1_DEC ? 1:0)|(PI_PVR1_ADC ? 2:0)|(PI_PVR2_DEC ? 4:0)|(PI_PVR2_ADC ? 8:0);
  if(!Key_PVR_Inited)
  {
    for(IRQVar[0]=0;IRQVar[0]<SDK_PVR_Count;IRQVar[0]++){DKEY.PVR_State[IRQVar[0]]=DKEY.PVR_TimeCount[IRQVar[0]]=0x00;}
    DKEY.PVR_AllState=DKEY.PVR_TempState;Key_PVR_Inited=1;return;
  }
  DKEY.PVR_TempState=DKEY.PVR_TempState^DKEY.PVR_AllState;if(DKEY.PVR_TempState==0x00)return;IRQINT[0]=3;
  for(IRQVar[0]=0;IRQVar[0]<SDK_PVR_Count;IRQVar[0]++)
  {
    if(DKEY.PVR_TempState&IRQINT[0])
    {
      DKEY.PVR_AllState^=(DKEY.PVR_TempState&IRQINT[0]); DKEY.PVR_State[IRQVar[0]]=(DKEY.PVR_State[IRQVar[0]]<<2)|((DKEY.PVR_AllState>>(2*IRQVar[0])) &3);
      for(IRQVar[1]=0;IRQVar[1]<SDK_PVR_UDCount;IRQVar[1]++){if((PVR_UD[IRQVar[0]][IRQVar[1]]&0xFF)==DKEY.PVR_State[IRQVar[0]])break;}
      if(IRQVar[1]<SDK_PVR_UDCount) Key_Save(IRQVar[0]+SDK_Key_Count-SDK_PVR_Count,(PVR_UD[IRQVar[0]][IRQVar[1]]&0x100 ? Key_EV_ScrollDown:Key_EV_ScrollUp));
    }
    IRQINT[0]<<=2;
  }
  #endif  
}
//------------------------------------------------------------------------------------------------------------------------------
void Key_Save(UINT8 Code,UINT8 EV)
{
  DKEY.Item[DKEY.Index].Code=Code;DKEY.Item[DKEY.Index].EV =EV;
  DKEY.Index=(DKEY.Index+1)%SIZE_SDK_KeyEV; if(DKEY.Count<SIZE_SDK_KeyEV)DKEY.Count++; IMM_Event_On=1;
}	
//------------------------------------------------------------------------------------------------------------------------------
void Key_DoEvent_IMM(void)
{
  if(DKEY.Count==0x00)return;
  
  DKEY.Count--;if(DKEY.Count)IMM_Event_On=1;
}  
//==============================================================================================================================
void SetDeviceOn(UINT8 EN)
{
  if(Device_On==EN)return;Device_On=EN;
}
//------------------------------------------------------------------------------------------------------------------------------
void ChangeDeviceOn(void)
{
  SetDeviceOn(!Device_On);
}

//==============================================================================================================================
#if SDK_COM_COUNT
void COM_Connect_TurnOn(UINT16 Index)
{
	if(!COM_Connect_On(Index)){COM_Connect_On(Index)=1;Event_Clear();} 
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Connect_TurnOff(UINT16 Index)
{
	if(COM_Connect_On(Index)){COM_Connect_On(Index)=0;Event_Clear();}
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Connect_Timer(void)//every 10ms
{
  for(Var[0]=0;Var[0]<DCOM.Count;Var[0]++)
  {if(COM_Connect_On(Var[0]) && SysTimeCount-DCOM.Item[Var[0]].RXTime>=1000){COM_Connect_On(Var[0])=0;Event_Clear();}}
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_VerifySend(void)
{
	DAPP.TF.Verify=0x00;for(Var[0]=6;Var[0]<DAPP.TF.Count;Var[0]++)DAPP.TF.Verify+=DAPP.TF.Item[Var[0]];
	DAPP.TF.Item[DAPP.TF.Count++]=DAPP.TF.Verify;COM_SendString(DAPP.TF.PortIndex,DAPP.TF.Item,DAPP.TF.Count,0);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Save_BUS(UINT16 Index)//保存绑定
{
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_LED_Timer(void)//every 1ms
{
  if(LED_RX_On)
  {DLED.TimeCount[0]++;if(DLED.TimeCount[0]>=3){LED_RX_On=PO_LED_RX=0;}}
  if(LED_TX_On)
  {DLED.TimeCount[1]++;if(DLED.TimeCount[1]>=3){LED_TX_On=PO_LED_TX=0;}}
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_Packet_Timer(void)//every 1ms
{
  UINT8 i;
  if(!COM_Head_On)return;
  IRQTempFlag0=0;
  for(i=0;i<SDK_COM_COUNT;i++)
  {
    if(!COM_RBUF_HeadOn(i))continue;
    DCOM.Item[i].RF.PacketTimeCount++;
    if(DCOM.Item[i].RF.PacketTimeCount>=COM_Packet_TimeOut)
    {if(DCOM.Item[i].PRTC.Count==0){COM_ReadParameter_EMPTY(i,1);} COM_ClearRX(i,true);}
    else
    {IRQTempFlag0=1;}
  }
  COM_Head_On=IRQTempFlag0;
}
//==============================================================================================================================
void COM_ReadPacket(UINT16 Index,UINT8* s,UINT16 Count)
{
	DCOM.Item[Index].RF.PacketTimeCount=0x00;
  if(DCOM.Item[Index].PRTC.Count==0)//无协议通讯
  {
    COM_ReadPacket_EMPTY(Index,s,Count);
  }
  else
  {
    switch(DCOM.Item[Index].PRTC.Item[DCOM.Item[Index].PRTC.Index])
    {
      case COM_Protocol_LDY_V2: COM_ReadPacket_LDY_V2(Index,s,Count);break;
      case COM_Protocol_DMX512: COM_ReadPacket_DMX512(Index,s,Count);break;
      default:COM_ReadPacket_EMPTY(Index,s,Count);break;
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_ReadPacket_EMPTY(UINT16 Index,UINT8 *s,UINT16 Count)
{
  UINT16 i;
  if(!COM_RBUF_HeadOn(Index)){DCOM.Item[Index].RF.Index=0x0000;DCOM.Item[Index].RF.PacketIndex=0x00;COM_RBUF_HeadOn(Index)=COM_Head_On=1;}//数据包超时计数
  for(i=0;i<Count;i++)
	{
		DCOM.Item[Index].RF.Item[DCOM.Item[Index].RF.Index]=s[i];
    DCOM.Item[Index].RF.Index=(DCOM.Item[Index].RF.Index+1)%DCOM.Item[Index].RF.Size;
    if(DCOM.Item[Index].RF.Count<DCOM.Item[Index].RF.Size) DCOM.Item[Index].RF.Count++;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_ReadPacket_DMX512(UINT16 Index,UINT8* s,UINT16 Count)
{
  UINT16 i;
  for(i=0;i<Count;i++)
	{
    if(COM_Bit9(Index)==1)
    {
      DCOM.Item[Index].RF.Item[DCOM.Item[Index].RF.Index]=s[i];	DCOM.Item[Index].RF.Index=(DCOM.Item[Index].RF.Index+1)%DCOM.Item[Index].RF.Size;if(DCOM.Item[Index].RF.Count<DCOM.Item[Index].RF.Size) DCOM.Item[Index].RF.Count++;
      if(DCOM.Item[Index].RF.Count>=512){COM_ReadParameter_DMX512(Index,DCOM.Item[Index].RF.Item,DCOM.Item[Index].RF.Count);COM_ClearRX(Index,true);}
    }
    else if(DCOM.Item[Index].RF.Count)
    {COM_ReadParameter_DMX512(Index,DCOM.Item[Index].RF.Item,DCOM.Item[Index].RF.Count);COM_ClearRX(Index,true);}
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_ReadPacket_LDY_V2(UINT16 Index,UINT8* s,UINT16 Count)
{
  UINT16 i;Type_COM_RXFrame *RF;
  RF=&DCOM.Item[Index].RF;
	if(COM_HPacket_On(Index))//有硬件打包器
	{
		if(!(s[0]==COM_Head_LDY[0] && s[1]==COM_Head_LDY[1])){COM_RXNoise(Index,0,Count);return;}
		(*RF).Control=s[2];(*RF).Command =s[3];(*RF).ParaCount=(Count==4 ? 0:(s[4]|(UINT16)s[5]<<8));
    if((s[2]&Control_SF) && Count==4){COM_ReadParameter_LDY_V2(Index,s+6,(*RF).ParaCount);return;}
    if(Count>=(*RF).ParaCount+7)	(*RF).Verify=0x00; else return;
		for(i=0;i<(*RF).ParaCount;i++){(*RF).Verify+=s[6+i];}
		if((*RF).Verify==s[6+i])COM_ReadParameter_LDY_V2(Index,s+6,(*RF).ParaCount); else COM_RXNoise(Index,0,Count);
	}
	else//无硬件打包
	{
		for(i=0;i<Count;i++)
		{
			(*RF).Item[(*RF).Index]=s[i];(*RF).Index=((*RF).Index+1)%(*RF).Size; if((*RF).Count<(*RF).Size) (*RF).Count++;
      
			if(COM_RBUF_HeadOn(Index)==0)
			{
				if(COM_IsHead(Index,DCOM.Item[Index].RF.Index,(UINT8 *)COM_Head_LDY,SIZE_COM_HeadF_LDY))
				{
					COM_RXNoise(Index,((*RF).Index +(*RF).Size - SIZE_COM_HeadF_LDY ) % (*RF).Size, (*RF).Count - SIZE_COM_HeadF_LDY );
					COM_RBUF_HeadOn(Index)=COM_Head_On=1;
					COM_RBUF_ParaCountOn(Index) =COM_RBUF_LFOn(Index)=0;
					COM_ClearRX(Index,false);
				}
			}
			else if(!COM_RBUF_ParaCountOn(Index))
			{
				if((*RF).Count==2)//Control+Command(2 bytes)
				{
					(*RF).Control=(*RF).Item[0];(*RF).Command=(*RF).Item[1];
					if((*RF).Control&Control_SF)
					{(*RF).ParaCount =0;COM_ReadParameter_LDY_V2(Index,(*RF).Item,(*RF).ParaCount);COM_ClearRX(Index,true);}
				}
				else if((*RF).Count==4)//ParaCount(2 bytes)
				{
					COM_RBUF_ParaCountOn(Index)=1;
					(*RF).ParaCount =(*RF).Item[2]+((UINT16)(*RF).Item[3]<<8);
					(*RF).Verify=0x00;DCOM.Item[Index].TPW.Index=0x00;
					COM_RBUF_AddrOn(Index)= ((*RF).Control & Control_AD ? 1:0);
					if((*RF).ParaCount<4){COM_RBUF_AddrOn(Index)=0;(*RF).Control &=(~Control_AD);}
          if(COM_RBUF_AddrOn(Index)){(*RF).ADR.Len=0x00;COM_RBUF_AddrHeadOn(Index)=COM_RBUF_LocalEN(Index)=0;}
          COM_RBUF_LocalOn(Index)=!COM_RBUF_AddrOn(Index);
					COM_RBUF_LFOn(Index)=((*RF).ParaCount >=(*RF).Size ? 1:0);
          if(COM_RBUF_LFOn(Index))(*RF).LFSubParaCount =0;
          (*RF).LFParaCount =0;
					COM_ClearRX(Index,false);
				}
			}
			else if(COM_RBUF_AddrOn(Index))//总层数=DCOM.Item[Index].RF.ADR.Item[1]+2
			{
        (*RF).ADR.Item[(*RF).ADR.Len++]=(*RF).Item[(*RF).Index-1];
				if(!COM_RBUF_AddrHeadOn(Index))
				{
					if((*RF).Count ==4)
					{
						COM_RBUF_AddrHeadOn(Index)=1;COM_RBUF_AddrLenOn(Index)=0;
            (*RF).ADR.Layer=(*RF).ADR.LayerAddrIndex=(*RF).ADR.AddrIndex=0x00;//层与地址个数清零
            (*RF).ADR.LocalAP.Len=(*RF).ADR.LocalAP.Addr=0x00;//中继位置清零
						if((*RF).ADR.Item[0]+(*RF).ADR.Item[1]+(*RF).ADR.Item[2]==0x00)//无地址异常处理
						{(*RF).Control &=(~Control_AD);	COM_RBUF_LocalOn(Index)=1;COM_RBUF_AddrOn(Index)=0; (*RF).ParaCount-=4;}
            else if((*RF).ADR.Item[0]==0x00)
            {(*RF).ADR.Layer++; (*RF).ADR.LayerAddrCount=((*RF).ADR.Item[1] ? 1:(*RF).ADR.Item[2]);}
            else
            {(*RF).ADR.LayerAddrCount=(*RF).ADR.Item[0];}
            //中继处理
            (*RF).ADR.Item[3]+=((*RF).Control&Control_BG ? -1:1);//Local
            (*RF).ADR.RelayLayer=(*RF).ADR.Item[3]+((*RF).Control&Control_BG ? -1:1);//Next
            COM_RBUF_LocalEN(Index)=((*RF).ADR.Layer==(*RF).ADR.Item[3] ? 1:0);
            COM_RBUF_NextOn(Index)=0;
						COM_ClearRX(Index,false);
					}
				}
				else if(!COM_RBUF_AddrLenOn(Index))
        {
          COM_RBUF_AddrLenOn(Index)=1;COM_RBUF_LocalEN(Index)=0;
          (*RF).ADR.LayerLen[0]=(*RF).Item[0]&0x0F;(*RF).ADR.LayerLen[1]=(*RF).Item[0]>>4; //提取地址长度
          if((*RF).ADR.Layer==(*RF).ADR.Item[3])
          {(*RF).ADR.LocalAP.Len=(*RF).ADR.Len-1;if((*RF).ADR.LayerLen[1]==DDEV.Item[0].NSN.Count)COM_RBUF_LocalEN(Index)=1;}//提取中继长度位置
          COM_ClearRX(Index,false);
        }
        else
        {
          if(COM_RBUF_LocalEN(Index) && (*RF).Index>(*RF).ADR.LayerLen[0] && (*RF).Index<=(*RF).ADR.LayerLen[0]+(*RF).ADR.LayerLen[1])
          {if(DDEV.Item[0].NSN.Item[(*RF).Index-1-(*RF).ADR.LayerLen[0]]!=(*RF).ADR.Item[(*RF).ADR.Len-1]) COM_RBUF_LocalEN(Index)=0;}
          if((*RF).Index>=(*RF).ADR.LayerLen[0]+(*RF).ADR.LayerLen[1])
          {
            (*RF).ADR.AddrIndex++;(*RF).ADR.LayerAddrIndex++; 
            if(COM_RBUF_LocalEN(Index))
            {
              (*RF).ADR.LocalAP.Port=(*RF).ADR.Len-(*RF).ADR.LayerLen[0]-(*RF).ADR.LayerLen[1];
              (*RF).ADR.LocalAP.Addr=(*RF).ADR.LocalAP.Port+(*RF).ADR.LayerLen[0]; COM_RBUF_LocalOn(Index)=1;
              COM_SetPort((*RF).ADR.Item+(*RF).ADR.LocalAP.Port,(*RF).ADR.LayerLen[0],Index,0);
            }
            if((*RF).ADR.AddrIndex>=(*RF).ADR.Item[0]+(*RF).ADR.Item[1]+(*RF).ADR.Item[2])
            {COM_RBUF_AddrOn(Index)=0;(*RF).ParaCount-=(*RF).ADR.Len;}
            else if((*RF).ADR.LayerAddrIndex>=(*RF).ADR.LayerAddrCount)
            {
              (*RF).ADR.Layer++;(*RF).ADR.LayerAddrIndex=0x00;COM_RBUF_AddrLenOn(Index)=0;
              (*RF).ADR.LayerAddrCount=((*RF).ADR.Layer==(*RF).ADR.Item[1]+1 ? (*RF).ADR.Item[2]:1);
            }
            if((*RF).ADR.Layer==(*RF).ADR.Item[3])
            {COM_RBUF_LocalEN(Index)=(!COM_RBUF_LocalOn(Index) && (*RF).ADR.LayerLen[1]==DDEV.Item[0].NSN.Count ? 1:0);}
          }
        }    
			}	
			else if(COM_RBUF_LocalOn(Index)) //is myself packet(自己的包，包含中继包与非中继包)
			{
				if( !((*RF).Control&Control_AD) || (*RF).ADR.Item[3]==((*RF).Control&Control_BG ? 0:(*RF).ADR.Item[1]+1) )//非中继
				{
					IRQTempFlag0=0;//是否是实参数据
					if(COM_RBUF_LFOn(Index))
					{(*RF).LFSubParaCount += 1;if((*RF).LFParaCount + (*RF).LFSubParaCount <= (*RF).ParaCount) IRQTempFlag0 =1;}
					else if((*RF).Count<=(*RF).ParaCount)
					{IRQTempFlag0 =1;}
          
					if(IRQTempFlag0)
					{					
						(*RF).Verify+= (*RF).Item[(*RF).Index - 1];//加密后的校验和
						if (COM_RBUF_TPWOn(Index) && DCOM.Item[Index].TPW.Count  && ((*RF).Control & Control_PW))//传输解密
						{
							(*RF).Item[(*RF).Index-1] ^=  DCOM.Item[Index].TPW.Item[DCOM.Item[Index].TPW.Index];
							DCOM.Item[Index].TPW.Index = (DCOM.Item[Index].TPW.Index + 1) % DCOM.Item[Index].TPW.Count;
						}
					}
					if(COM_RBUF_LFOn(Index))
					{
						if((*RF).LFParaCount + (*RF).LFSubParaCount > (*RF).ParaCount)
						{
							if((*RF).Item[(*RF).Index -1]==(*RF).Verify) {(*RF).LFSubParaCount -= 1;COM_RXSubFrame(Index,true);}//长帧校验 OK
							COM_ClearRX(Index,true);
						}
						else if ((*RF).LFSubParaCount >= (*RF).Size)
						{
							COM_RXSubFrame(Index,false);(*RF).LFParaCount += (*RF).LFSubParaCount;(*RF).LFSubParaCount = 0;COM_ClearRX(Index,false);
						}
					}			
					else if((*RF).Count>(*RF).ParaCount)
					{
						if((*RF).Item[(*RF).Index -1]==(*RF).Verify)COM_ReadParameter_LDY_V2(Index,(*RF).Item,(*RF).ParaCount);//普通校验 OK
						COM_ClearRX(Index,true);
					}

				}
				else//'中继包
				{		
					if(COM_RBUF_LFOn(Index))//中继长包
					{
						(*RF).LFSubParaCount+=0x01;
						if((*RF).LFParaCount+(*RF).LFSubParaCount>(*RF).ParaCount)
						{COM_TXRelayFrame(Index,true);COM_ClearRX(Index,true);}
						else if((*RF).Count >=(*RF).Size)
						{COM_TXRelayFrame(Index,false);COM_ClearRX(Index,false);(*RF).LFParaCount+=(*RF).LFSubParaCount;(*RF).LFSubParaCount=0x00;}
					}
					else if(DCOM.Item[Index].RF.Count>DCOM.Item[Index].RF.ParaCount)//中继普通包
					{(*RF).LFSubParaCount=(*RF).Count;COM_TXRelayFrame(Index,true);COM_ClearRX(Index,true);}
				}//中继与非中继结束	
			}			
			else //other frame （别人的包，旁路)
			{(*RF).LFParaCount +=0x01;	if((*RF).LFParaCount > (*RF).ParaCount ) COM_ClearRX(Index,true);}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 COM_IsHead(UINT16 Index,UINT8 BUFIndex,UINT8 *Head,UINT8 HeadLen)
{
  if(DCOM.Item[Index].RF.Count<HeadLen)return(0);
	IRQVar[1]=(BUFIndex+DCOM.Item[Index].RF.Size-HeadLen)%DCOM.Item[Index].RF.Size;
	for(IRQVar[2]=0;IRQVar[2]<HeadLen;IRQVar[2]++)
	  if(DCOM.Item[Index].RF.Item[IRQVar[1]]!=Head[IRQVar[2]])break; else IRQVar[1]=(IRQVar[1]+1)%DCOM.Item[Index].RF.Size;
	return (IRQVar[2]==HeadLen ? 1:0);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_ClearRX(UINT16 Index,UINT8 ClearHead)
{
	DCOM.Item[Index].RF.Index=DCOM.Item[Index].RF.Count=0x0000;	if(ClearHead)COM_RBUF_HeadOn(Index)=0;
}
//------------------------------------------------------------------------------------------------------------------------------
UINT16 COM_AddrToPort(UINT16 Index)//根据目标地址求端口（必须针对产品修改此函数),一般可以用高位表示端口编码地址，针对这种情况，可以处理此函数；当然也可以把端口号当成单独的地址，路径就会多一级。
{
  return(0);
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 COM_SetPort(UINT8 *s,UINT8 PortLen,UINT16 PortIndex,UINT8 IsOutput)
{
  UINT8 Found=(PortLen>0 && PortLen<5 ? 1:0);
  if(PortLen==0)return(Found); if(PortLen&1)s[(PortLen-1)/2]&=(IsOutput ? 0x0F:0xF0);
  if(PortLen==1)
  {s[0]|=(IsOutput ? PortIndex<<4:PortIndex&0x0F);}
  else if(PortLen==2)
  {s[IsOutput ? 1:0]=PortIndex;}
  else if(PortLen==3)
  {if(IsOutput){s[1]|=PortIndex<<4;s[2]=PortIndex>>4;} else s[0]=PortIndex;s[1]|=PortIndex>>8;}
  else if(PortLen==4)
  {if(IsOutput){s[2]=PortIndex&0xff;s[3]=PortIndex>>8;}else{s[0]=PortIndex&0xff;s[1]=PortIndex>>8;}}
  return(Found);
}
//------------------------------------------------------------------------------------------------------------------------------
UINT8 COM_GetPort(UINT8 *s,UINT8 PortLen,UINT16 *PortIndex,UINT8 IsOutput)
{
  UINT8 Found=(PortLen>0 && PortLen<5 ? 1:0);
  if(PortLen==0)return(Found);
  if(PortLen==1)
  {*PortIndex=(IsOutput ? s[0]>>4:s[0]&0x0F);}
  else if(PortLen==2)
  {*PortIndex=s[IsOutput ? 1:0];}
  else if(PortLen==3)
  {*PortIndex=(IsOutput ? (s[1]>>4)+((UINT16)s[2]<<4) : s[0]+(((UINT16)s[1]&0x0F)<<8) );}
  else if(PortLen==4)
  {*PortIndex=(IsOutput ? s[2]+((UINT16)s[3]<<8) : s[0]+((UINT16)s[1]<<8));}
  return(Found);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_TXRelayFrame(UINT16 Index,UINT8 IsEnd)//中继发送(中继不存在校验和解密,数据直接转发)
{
  DAPP.IRQTF.Time=0x00000000;
  if(DCOM.Item[Index].RF.LFParaCount==0x00)
	{
		COM_Frame_Received=1;COM_Frame_Sended =1; INT_Event_On=1;COM_RelayPortOn(Index)=0;
    IRQVar[1]=DCOM.Item[Index].RF.ADR.Item[DCOM.Item[Index].RF.ADR.LocalAP.Len]&0x0F;
    if(COM_GetPort(DCOM.Item[Index].RF.ADR.Item+DCOM.Item[Index].RF.ADR.LocalAP.Port,IRQVar[1],&DCOM.Item[Index].PORT.O,(DCOM.Item[Index].RF.Control&Control_BG ? 0:1)))
    {COM_RelayPortOn(Index)=1;}
    else if(DC_MainPort_On)
    {if(Index==DDEV.Item[0].MainPort){COM_RelayPortOn(Index)=COM_AddrToPort(Index);} else {DCOM.Item[Index].PORT.O =DDEV.Item[0].MainPort;COM_RelayPortOn(Index)=1;}}
    if(!COM_RelayPortOn(Index))return;
    
    IRQINT[0]=DCOM.Item[Index].RF.ParaCount + DCOM.Item[Index].RF.ADR.Len;
		DAPP.IRQTF.Item[0]=COM_Head_LDY[0];DAPP.IRQTF.Item[1]=COM_Head_LDY[1];
    DAPP.IRQTF.Item[2]=DCOM.Item[Index].RF.Control; DAPP.IRQTF.Item[3] = DCOM.Item[Index].RF.Command;
    DAPP.IRQTF.Item[4]=IRQINT[0]&0xff;
    DAPP.IRQTF.Item[5]=IRQINT[0]>> 8;
    
    DAPP.IRQTF.Count =6;DAPP.IRQTF.Time=0x00;
    COM_SendString(DCOM.Item[Index].PORT.O,DAPP.IRQTF.Item, DAPP.IRQTF.Count,DAPP.IRQTF.Time);//Head
    COM_SendString(DCOM.Item[Index].PORT.O,DCOM.Item[Index].RF.ADR.Item,DCOM.Item[Index].RF.ADR.Len,DAPP.IRQTF.Time);//Address List
	}
  else if(!COM_RelayPortOn(Index))
  {return;}
  COM_SendString(DCOM.Item[Index].PORT.O,DCOM.Item[Index].RF.Item, DCOM.Item[Index].RF.LFSubParaCount,DAPP.IRQTF.Time);
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_RXNoise(UINT16 Index,UINT8 Pos,UINT16 Count)
{
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_RXSubFrame(UINT16 Index,UINT8 IsEnd)//长帧子包，Payload subframe,(SP.RXBA.Item, SP.RXFM.SubParaCount)
{
	if(IsEnd) {COM_Connect_On(Index)=COM_Frame_Received=INT_Event_On=1;}
}
//==============================================================================================================================
void COM_ReadParameter(UINT16 Index,UINT8 *s,UINT16 Count)
{
  if(DCOM.Item[Index].PRTC.Count==0)//无协议通讯
  {
    COM_ReadParameter_EMPTY(Index,1);
  }
  else
  {
    switch(DCOM.Item[Index].PRTC.Item[DCOM.Item[Index].PRTC.Index])
    {
      case COM_Protocol_LDY_V2: COM_ReadParameter_LDY_V2(Index,s,Count);break;
      case COM_Protocol_DMX512: COM_ReadParameter_DMX512(Index,s,Count);break;
      default:COM_ReadParameter_EMPTY(Index,1);break;
    }
  }
}
//==============================================================================================================================
void COM_ReadParameter_EMPTY(UINT16 Index,UINT8 IsEnd)//中断内调用
{
  DCOM.Item[Index].RF.Count=0x0000;DCOM.Item[Index].RF.PacketIndex++;
}  
//==============================================================================================================================
void COM_ReadParameter_DMX512(UINT16 Index,UINT8 *s,UINT16 Count)
{
  if(!Device_On||Count<10)return;SetSleepOn(0);
}
//==============================================================================================================================
void COM_ReadParameter_LDY_V2(UINT16 Index,UINT8 *s,UINT16 Count)//普通包，payload=(s, Count), 
{
  UINT8 RW;UINT16 ParaPos;
  DCOM.Item[Index].RXTime=SysTimeCount;COM_Connect_On(Index)=COM_Frame_Received=INT_Event_On=1;
  DCOM.Item[Index].PRTC.TimeCount=DAPP.IRQTF.ParaCount=DAPP.IRQTF.Time=0x0000; DAPP.TF.PortIndex=Index;ParaPos=6;
	RW =DCOM.Item[Index].RF.Control_BIT.RW;IRQTempFlag1=0;//读写，是否返回
  if(DCOM.Item[Index].RF.Control&Control_AppPort)
  {DCOM.Item[Index].PORT.App=ByteToValue(s,2,0);DAPP.IRQTF.Item[ParaPos++]=s[0];DAPP.IRQTF.Item[ParaPos++]=s[1];s+=2;Count-=2;}//Control.bit5=1, 实参前两个字节为App端口号
	
	if(DCOM.Item[Index].RF.Control & Control_BG)//返回
	{
		switch(DCOM.Item[Index].RF.Command)
		{
			case Command_HS:
				break;
			case Command_ADC:
				break;
			default:
				break;
		}
	}
	else//接收
	{
		switch(DCOM.Item[Index].RF.Command)
		{
			case Command_HS://握手
				IRQTempFlag1 =1;
				break;
			case Command_DP://设备属性
				if(DCOM.Item[Index].RF.ParaCount<1)break;
				DAPP.IRQTF.Item[ParaPos++]=s[0];
				switch(s[0])
				{
					case Command_DP_STR:
						Read_DPStr_On=1;INT_Event_On =1;
            break;
					case Command_DP_ST:
						if(RW!=Control_R)break;
						for(IRQVar[0]=0;IRQVar[0]<4;IRQVar[0]++) DAPP.IRQTF.Item[ParaPos+IRQVar[0]]=DDEV.Item[0].RunST.Byte[IRQVar[0]];
					  DAPP.IRQTF.ParaCount=4;IRQTempFlag1=1;
            break;						
					case Command_DP_ID://DCCL+DCID+DCSN+DCCP+CPUCP+CPUID
						if(RW!=Control_R)break;
					  for(IRQVar[0]=0;IRQVar[0]<24;IRQVar[0]++)DAPP.IRQTF.Item[ParaPos+IRQVar[0]]=Device_ID[IRQVar[0]]; 
					  DAPP.IRQTF.ParaCount=24;IRQTempFlag1=1;
						break;
					case Command_DP_CP:
					  if(RW!=Control_R)break;
						DAPP.IRQTF.ParaCount=StrLen((UINT8 *)Device_CP,64);for(IRQVar[0]=0;IRQVar[0]<DAPP.IRQTF.ParaCount;IRQVar[0]++)DAPP.IRQTF.Item[ParaPos+IRQVar[0]]=Device_CP[IRQVar[0]];IRQTempFlag1=1;
						break;
					case Command_DP_NV:
				    if(RW!=Control_R)break;
            DAPP.IRQTF.ParaCount=StrLen((UINT8 *)Device_NV,64);for(IRQVar[0]=0;IRQVar[0]<DAPP.IRQTF.ParaCount;IRQVar[0]++)DAPP.IRQTF.Item[ParaPos+IRQVar[0]]=Device_NV[IRQVar[0]];IRQTempFlag1=1;
            break;
					case Command_DP_NSN:
						if(RW==Control_R)
          	{DAPP.IRQTF.Item[ParaPos]=DDEV.Item[0].NSN.Size;for(IRQVar[0]=0;IRQVar[0]<DDEV.Item[0].NSN.Count;IRQVar[0]++) DAPP.IRQTF.Item[ParaPos+1+IRQVar[0]]=DDEV.Item[0].NSN.Item[IRQVar[0]]; DAPP.IRQTF.ParaCount=1+DDEV.Item[0].NSN.Count;IRQTempFlag1=1;}
						else if(Count>1 && Count<=SIZE_DC_NSN+1)
						{DDEV.Item[0].NSN.Count=Count-1;for(IRQVar[0]=0;IRQVar[0]<DDEV.Item[0].NSN.Count;IRQVar[0]++)DDEV.Item[0].NSN.Item[IRQVar[0]]=s[1+IRQVar[0]];Write_NSN_On=INT_Event_On=IRQTempFlag1=1;}
						break;
          case Command_DP_POS:
            break;
          case Command_DP_PW:
            break;
					case Command_DP_BATPercent:
						if(RW==Control_R){DAPP.IRQTF.Item[ParaPos]=DDEV.Item[0].BAT.P&0xff;DAPP.IRQTF.Item[ParaPos+1]=DDEV.Item[0].BAT.P>>8; DAPP.IRQTF.ParaCount=2;IRQTempFlag1=1;}
					  break;						
					case Command_DP_Temprature:
						if(RW==Control_R){DAPP.IRQTF.Item[ParaPos]=DDEV.Item[0].T.V&0xff;DAPP.IRQTF.Item[ParaPos+1]=DDEV.Item[0].T.V>>8; DAPP.IRQTF.ParaCount=2;IRQTempFlag1=1;}
						break;
					case Command_DP_FrameSize:
						if(RW!=Control_R)break;
            IRQINT[0]=COM_BUFSize(Index,0);IRQINT[1]=COM_BUFSize(Index,1);
            DAPP.IRQTF.Item[ParaPos+0]=IRQINT[0]&0xff;DAPP.IRQTF.Item[ParaPos+1]=IRQINT[0]>>8;DAPP.IRQTF.Item[ParaPos+2]=IRQINT[1]&0xff;DAPP.IRQTF.Item[ParaPos+3]=IRQINT[1]>>8;DAPP.IRQTF.ParaCount=4;IRQTempFlag1=1;
            break;
          case Command_DP_DT:
            if(DCOM.Item[Index].RF.ParaCount<2)break;
				    DAPP.IRQTF.Item[ParaPos++]=s[1];
				    switch(s[1])
            {
              case Command_DP_DT_BDT:
								if(RW==Control_R)
								{DTToByte8(DAPP.BaseDT,DAPP.IRQTF.Item+ParaPos,DateTime_Mode_Struct);DAPP.IRQTF.ParaCount=8;IRQTempFlag1=1;}								
								else if(Count==10)
								{Byte8ToDT(s+2,&DAPP.BaseDT,DateTime_Mode_Struct);IRQTempFlag1=1;Write_BaseDT_On=INT_Event_On=1;}
								break;                
   					  case Command_DP_DT_MDT:
								if(RW==Control_R)
								{DTToByte8(DAPP.MadeDT,DAPP.IRQTF.Item+ParaPos,DateTime_Mode_Struct);DAPP.IRQTF.ParaCount =8;IRQTempFlag1=1;}
								else if(Count==10)
								{Byte8ToDT(s+2,&DAPP.MadeDT,DateTime_Mode_Struct);IRQTempFlag1=1;Write_MadeDT_On=INT_Event_On=1;}
								break;							
					    case Command_DP_DT_CDT:
						    if(RW==Control_R)
						    {DTToByte8(DAPP.DT,DAPP.IRQTF.Item+ParaPos,DateTime_Mode_Struct); DAPP.IRQTF.ParaCount=8;IRQTempFlag1=1;}
						    else if(Count==10)
					      {Byte8ToDT(s+2,&DAPP.DT,DateTime_Mode_Struct);DT_RefreshMiniSecond(); IRQTempFlag1=1;DTSync_On=1;}
                break;
              default:
                break;
            }
					  break;
          case Command_DP_HW:
						DAPP.IRQTF.Item[ParaPos++]=s[1];
					  switch(s[1])
						{
							case Command_DP_HW_G0:
								if(RW==Control_R)
								{
                  for(IRQVar[0]=0;IRQVar[0]<4;IRQVar[0]++)DAPP.IRQTF.Item[ParaPos+IRQVar[0]]=DDEV.Item[0].HS.ST.Byte[IRQVar[0]];
                  DAPP.IRQTF.ParaCount=4;IRQTempFlag1=1;
                }
								else if(Count>=8)
								{
                  DDEV.Item[0].HS.ST.Byte[0]=(DDEV.Item[0].HS.ST.Byte[0]&(~s[6]))|(s[2]&s[6]); if(s[7]&2) DDEV.Item[0].HS.ST.Byte[2]=s[4]; if(s[7]&4) DDEV.Item[0].HS.ST.Byte[3]=s[5];
                  Write_HS_On=INT_Event_On=1;
								}
								break;
							case Command_DP_HW_G1:
                break;
							case Command_DP_HW_G2:
                break;
						  default:
								break;
					  }
						break;	
          case Command_DP_BUS://总线，包括联机前后
            if(!COM_BUS_On(Index)||COM_BUSM_On(Index))break;
            switch(s[1])
            {
              case Command_DP_BUS_ClrJoin://清除Join(广播)
                if(RW==Control_R || COM_BUSL_On(Index))break;
                COM_BUS_Joined(Index)=0;
                break;
              case Command_DP_BUS_SetJoin://设置Join
                if(RW==Control_R || COM_BUSL_On(Index))break;
                for(IRQVar[0]=0;IRQVar[0]<(Count-2)/DDEV.Item[0].NSN.Count;IRQVar[0]++)
                {if(StrCompare(DDEV.Item[0].NSN.Item,s+2+IRQVar[0]*DDEV.Item[0].NSN.Count,DDEV.Item[0].NSN.Count,1)==1){COM_BUS_Joined(Index)=1;break;}}
                break;
              case Command_DP_BUS_ClrRel://BUS可以存盘或不存盘[COM_BUS_Changed(Index)]
                if(!COM_BUSL_On(Index)||DDEV.Item[0].NSN.Count==0x00)break;
                if(!(DCOM.Item[Index].RF.ADR.Item[4]==DCOM.Item[Index].BUS.NSNLen && StrCompare(DCOM.Item[Index].BUS.NSN,DCOM.Item[Index].RF.ADR.Item+5,DCOM.Item[Index].BUS.NSNLen,1)==1))  break;//只有绑定该节点的主节点才能对它解绑
                for(IRQVar[0]=0;IRQVar[0]<(Count-2)/DDEV.Item[0].NSN.Count;IRQVar[0]++)
                {if(StrCompare(DDEV.Item[0].NSN.Item,s+2+IRQVar[0]*DDEV.Item[0].NSN.Count,DDEV.Item[0].NSN.Count,1)==1){COM_BUSL_On(Index)=0;COM_BUS_Changed(Index)=1;INT_Event_On=1;break;}}
                break;
              case Command_DP_BUS_SetRel://绑定总线下自由节点，子节点获得平行节点个数及本节点在子节点列表中的索引,子节点可以不存储平行子节点，总节点必须存储子节点。
                if(RW==Control_R||COM_BUSL_On(Index)||Count<=2||DDEV.Item[0].NSN.Count==0x00||(DCOM.Item[Index].RF.Control&Control_AD)==0x00)break;
                DCOM.Item[Index].BUS.Count=Count-2;
                for(IRQVar[0]=0;IRQVar[0]<Count-2;IRQVar[0]++)
                { 
                  if(IRQVar[0]<DCOM.Item[Index].BUS.Size) DCOM.Item[Index].BUS.Item[IRQVar[0]]=s[2+IRQVar[0]];//存储节点
                  if((IRQVar[0]%DDEV.Item[0].NSN.Count)==0x00 && StrCompare(DDEV.Item[0].NSN.Item,s+2+IRQVar[0],DDEV.Item[0].NSN.Count,1)==1)
                  {StrCopy(DCOM.Item[Index].BUS.NSN,DCOM.Item[Index].RF.ADR.Item+5,DCOM.Item[Index].RF.ADR.Item[4]);DCOM.Item[Index].BUS.Index=IRQVar[0]/DDEV.Item[0].NSN.Count;COM_BUSL_On(Index)=1;}//获取本节点绑定索引
                }
                COM_BUS_Changed(Index)=1;INT_Event_On=1;
                break;
              case Command_DP_BUS_GetFree://查询总线下自由节点，准备重新绑定子集
                if(RW==Control_R||COM_BUSL_On(Index)||COM_BUS_Joined(Index)||Count<=2||Count>6||DDEV.Item[0].NSN.Count==0)break;//1<=bytes of MaxSubOBCount <=4
                IRQLNG[0]=ByteToValue(s+2,Count-2,0);//存储主节点，提取最大子节点个数
                DCOM.Item[Index].RF.ADR.Item[DCOM.Item[Index].RF.ADR.Len++]=DDEV.Item[0].NSN.Count;
                for(IRQVar[0]=0;IRQVar[0]<DDEV.Item[0].NSN.Count;IRQVar[0]++)DCOM.Item[Index].RF.ADR.Item[DCOM.Item[Index].RF.ADR.Len++]=DDEV.Item[0].NSN.Item[IRQVar[0]];
                DAPP.IRQTF.Time=LdyRand(IRQLNG[0])*3;IRQTempFlag1=1;
                break;
              default:
                break;
            }
            break;
					case Command_DP_AT:
						if(RW==Control_R||Count<2)break;
						DAPP.IRQTF.Item[ParaPos++]=s[1];
						switch(s[1])
						{
							case Command_DP_AT_Reset:
							  Device_Reset_On=1;INT_Event_On=1; IRQTempFlag1=1;
								break;
							case Command_DP_AT_PW:
								if(Count !=3)break;
							  DAPP.PF.Item[0]=s[2];DAPP.PF.Count=1; DAPP.IRQTF.Item[ParaPos]=s[2];DAPP.IRQTF.ParaCount=1;IRQTempFlag1=1;Device_PWSet_On=1;INT_Event_On=1; 
								break;
							default:
								break;
						}							
						break;
          default:
            break;						
				}					
				break;
			case Command_UG://升级
			  break;			
			case Command_DISK://磁盘
				break;
      case Command_KEY:
        break;
      case Command_ADC:
        break;
			default:
				break;
		}		
	}
	if (IRQTempFlag1)
	{
    DAPP.IRQTF.ParaCount+=ParaPos-6;DAPP.IRQTF.PortIndex=Index; 
		DAPP.IRQTF.Control =DCOM.Item[Index].RF.Control;	DAPP.IRQTF.Command =DCOM.Item[Index].RF.Command;
    if(DAPP.IRQTF.ParaCount && COM_RBUF_TPWOn(Index) && DCOM.Item[Index].TPW.Count && (DCOM.Item[Index].RF.Control&Control_PW) )//Encode,传输加密
    {
      IRQVar[1]=0x00;
      for(IRQVar[0]=0;IRQVar[0]<DAPP.IRQTF.ParaCount;IRQVar[0]++)
      {DAPP.IRQTF.Item[6+IRQVar[0]] ^= DCOM.Item[Index].TPW.Item[IRQVar[1]]; IRQVar[1]=(IRQVar[1]+0x01) % DCOM.Item[Index].TPW.Count ;}
    }
    else
    {DAPP.IRQTF.Control&=(~Control_PW);}//Cancel Password
    COM_SetBack(Index); DCOM.Item[Index].TXTime=SysTimeCount;COM_Frame_Sended=INT_Event_On=1;
  }
}
//------------------------------------------------------------------------------------------------------------------------------
void COM_SetBack(UINT16 Index)
{
	if(DAPP.IRQTF.ParaCount==0) DAPP.IRQTF.Control|=Control_SF; else DAPP.IRQTF.Control &=(~Control_SF);
	DAPP.IRQTF.Control|=Control_BG;	COM_TX_InIRQ(Index)=1;
	DAPP.IRQTF.Item[0]=COM_Head_LDY[0x00];DAPP.IRQTF.Item[1]=COM_Head_LDY[0x01];
	DAPP.IRQTF.Item[2]=DAPP.IRQTF.Control;DAPP.IRQTF.Item[3]=DAPP.IRQTF.Command;
  if(DAPP.IRQTF.Control&Control_SF){COM_SendString(DAPP.IRQTF.PortIndex,DAPP.IRQTF.Item,4,DAPP.IRQTF.Time); COM_TX_InIRQ(Index)=0;return;}
	IRQVar[2]=0x00; for(IRQVar[1]=0;IRQVar[1]<DAPP.IRQTF.ParaCount;IRQVar[1]++) IRQVar[2]+=DAPP.IRQTF.Item[6+IRQVar[1]];DAPP.IRQTF.Item[6+DAPP.IRQTF.ParaCount]=IRQVar[2];//Verify
	
  if(DAPP.IRQTF.Control & Control_AD && DCOM.Item[Index].RF.ADR.Item[2]!=1)
  {
    DCOM.Item[Index].RF.ADR.Item[2]=1;DCOM.Item[Index].RF.ADR.Item[DCOM.Item[Index].RF.ADR.LocalAP.Len]=DDEV.Item[0].NSN.Count;
    DCOM.Item[Index].RF.ADR.Len+=(DCOM.Item[Index].RF.ADR.Item[2] ? -(DCOM.Item[Index].RF.ADR.Item[2]-1):1)*DDEV.Item[0].NSN.Count;
    if(DCOM.Item[Index].RF.ADR.LocalAP.Len+1!= DCOM.Item[Index].RF.ADR.LocalAP.Addr)
		{for(IRQVar[1]=0;IRQVar[1]<DDEV.Item[0].NSN.Count;IRQVar[1]++)DCOM.Item[Index].RF.ADR.Item[DCOM.Item[Index].RF.ADR.LocalAP.Len+IRQVar[1]]=DDEV.Item[0].NSN.Item[IRQVar[1]];}
	}
	
	IRQINT[0]=DAPP.IRQTF.ParaCount+DCOM.Item[Index].RF.ADR.Len;DAPP.IRQTF.Item[4]=IRQINT[0]&0xff;DAPP.IRQTF.Item[5]=IRQINT[0]>>8;
	if(DAPP.IRQTF.Control & Control_AD)
	{
	  COM_SendString(DAPP.IRQTF.PortIndex,DAPP.IRQTF.Item,6,DAPP.IRQTF.Time);
    COM_TXContinue_On(DAPP.IRQTF.PortIndex)=1; 
    COM_SendString(DAPP.IRQTF.PortIndex,DCOM.Item[Index].RF.ADR.Item,DCOM.Item[Index].RF.ADR.Len,DAPP.IRQTF.Time);//Address
	  COM_SendString(DAPP.IRQTF.PortIndex,DAPP.IRQTF.Item+6,DAPP.IRQTF.ParaCount+1,DAPP.IRQTF.Time);
    COM_TXContinue_On(DAPP.IRQTF.PortIndex)=0;
	}
	else
	{COM_SendString(DAPP.IRQTF.PortIndex,DAPP.IRQTF.Item,DAPP.IRQTF.ParaCount+7,DAPP.IRQTF.Time);}
  COM_TX_InIRQ(Index)=0;
}
//==============================================================================================================================
void Read_DPStr(void)
{
  Read_DPStr_On=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void SetPWState(void)
{
  Device_PWSet_On=0;SetDeviceOn(DAPP.PF.Item[0]);
}
//------------------------------------------------------------------------------------------------------------------------------
void Event_Clear(void)
{
	Write_BaseDT_On=0;Write_MadeDT_On=0;Read_DPStr_On=0;
}
//------------------------------------------------------------------------------------------------------------------------------
void Send_State(void)
{
	SendState_On=0;
	DAPP.TF.Item[0]=COM_Head_LDY[0];	DAPP.TF.Item[1]=COM_Head_LDY[1];	DAPP.TF.Item[2]=0x00;	DAPP.TF.Item[3]=Command_DP;
	DAPP.TF.Item[4]=5;DAPP.TF.Item[5]=0;DAPP.TF.Item[6]=Command_DP_ST;
  for(Var[0]=0;Var[0]<4;Var[0]++)	DAPP.TF.Item[Var[0]+7]=DDEV.Item[0].RunST.Byte[Var[0]];
	DAPP.TF.Count=11;	COM_VerifySend();
}
//------------------------------------------------------------------------------------------------------------------------------
void Write_BaseDT(void)
{
  Write_BaseDT_On=0; DTToByte8(DAPP.BaseDT,DAPP.TF.Item,DateTime_Mode_Simple);
  Flash_WriteItem((UINT32)(Device_BaseDT),DAPP.TF.Item,8);
}
//------------------------------------------------------------------------------------------------------------------------------
void Write_MadeDT(void)
{
  Write_MadeDT_On=0; DTToByte8(DAPP.MadeDT,DAPP.TF.Item,DateTime_Mode_Simple);
  Flash_WriteItem((UINT32)(Device_MadeDT),DAPP.TF.Item,8);
}
//------------------------------------------------------------------------------------------------------------------------------
void Write_HS(void)
{
  Write_HS_On=0;
  Flash_WriteItem((UINT32)(Device_HS),DDEV.Item[0].HS.ST.Byte,4);
}
//------------------------------------------------------------------------------------------------------------------------------
void Write_NSN(void)
{
  Write_NSN_On=0;
  Flash_WriteItem((UINT32)(Device_NSN),DDEV.Item[0].NSN.Item,DDEV.Item[0].NSN.Count);
}
#endif
//==============================================================================================================================
