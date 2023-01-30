//==============================================================================================================================
#ifndef UG_Common_V01_H
#define UG_Common_V01_H
//==============================================================================================================================
#include "APP_Common_V01.h"
//==============================================================================================================================
#define UG_Delay_On                1
#define UG_String_On               1
#define UG_LdyFunc_On              1
#define UG_DateTime_On             1

#define UG_LdySin_On               1
#define UG_SinData_K               16384
#define UG_SinData_Count           (sizeof(UG_SinData)/sizeof(UINT16))
#define UG_SinData_D               (PAI/2/(UG_SinData_Count-2))

#define UG_LdySqrt_On              0
#define UG_SqrtData_K              2048
#define UG_SqrtData_Count          (sizeof(UG_SqrtData)/sizeof(UINT16))
#define UG_SqrtData_D              (100.000/(UG_SqrtData_Count-1))

#define UG_LdyEXPLOG_On            1
//------------------------------------------------------------------------------------------------------------------------------
extern const UINT8 UG_COM_Head_LDY[],UG_COM_Head_LS[],UG_COM_Head_YY[];
extern const double UG_Double_EXPT[],UG_Double_EXPE[];
extern const UINT8 UG_CRLF[];
#if DateTime_On
extern const UINT8 UG_DateTime_MD[];
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if UG_Delay_On
void UG_Delay_US(unsigned int Time);//TimeUnit=us,Delay by instruction
void UG_Delay_MS(unsigned int Time);//TimeUnit=ms,Delay by instruction
void UG_Delay_TimerTime(unsigned int Time);//TimeUnit=ms,Delay by timer
void UG_Delay_Time(unsigned int Time,unsigned char IsStruction);//TimeUnit=ms
#endif

#if UG_String_On
  UINT16 UG_StrLen(UINT8 *s,UINT16 MaxLen);
	UINT8 UG_IsVarChar(UINT8 c,UINT8 IsFirst);
  UINT8 UG_StrCompareChar(UINT8 c1,UINT8 c2,UINT8 Mode);
  UINT8 UG_StrCompare(UINT8 *s1,UINT8 *s2,UINT16 Len,UINT8 Mode);// 0=(s1<s2),1=(s1=s2),2=(s1>s2)
  UINT16 UG_StrReplace(UINT8 *src, UINT16 *srcLen,UINT8 *std,UINT16 stdLen,UINT8 *srp,UINT16 srpLen,UINT8 Mode);
	UINT16 UG_StrReplacePos(UINT8 *src,UINT16 *srcLen,UINT16 stdPos,UINT16 stdLen,UINT8 *srp,UINT16 srpLen);//返回替换次数
  INT16 UG_StrFind(UINT8 *src,UINT16 srcLen, UINT8 *std, UINT16 stdLen,UINT8 Mode);//在src中查找std,found return [0,N-1],nofound return -1
  UINT8 UG_StrFindItem(UINT8 *src, UINT16 srcLen,UINT8 Flag,UINT16 Index,UINT16 *Pos,UINT16 *Len);
	UINT8 UG_StrFindItemStr(UINT8 *src, UINT16 srcLen, UINT8 Flag,UINT8 *std,UINT16 stdLen,UINT16 *stdIndex,UINT8 Mode);//查找s中以Flag隔开的std项
  void UG_StrSet(UINT8 *s,UINT16 Len,UINT8 c);
  void UG_StrCopy(UINT8 *std,UINT8 *src,UINT16 Len);
	UINT8 UG_StrLTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos);
	UINT8 UG_StrRTrim(UINT8 *src,UINT16 srcLen,UINT16 *RPos);
	UINT8 UG_StrTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos,UINT16 *RPos);
  void UG_StrCat(UINT8 *std,UINT16 *stdLen,UINT8 *src, UINT16 srcLen);
  void UG_StrAddItem(UINT8 *std,UINT16 *stdLen,UINT8 *src,UINT16 srcLen,UINT8 Flag);//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00   
  void UG_StrAddItemNum(UINT8 *std,UINT16 *stdLen,double Num,UINT8 NumPCount,UINT8 Flag);//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00 
  void UG_ValueToStr(UINT8 *s,UINT64 V,UINT8 Len);
  UINT64 UG_StrToValue(UINT8 *s,UINT8 Len);
	UINT64 UG_ByteToValue(UINT8 *s,UINT8 Len,UINT8 HighToLow);
  void UG_StrAddValue(UINT8 *s,UINT8 sLen,UINT64 V,UINT8 VLen);
  void UG_NumToStr(double Num,UINT8 NumPCount,UINT8 *s,UINT16 *Len);
	double UG_StrToNum(UINT8 *s,UINT16 Len);
#endif

#if UG_DateTime_On
UINT8 UG_IsLeapYear(INT16 Year);
UINT16 UG_YearDay(INT16 Year);
INT32 UG_YearDays(INT16 Year);
INT32 UG_DaysBetweenYear(INT16 Year1, INT16 Year2);
UINT16 UG_DaysBetweenMonth(INT16 Year, UINT8 Month1, UINT8 Month2);
UINT8 UG_MonthDay(INT16 Year, UINT8 Month);
UINT8 UG_YMDToWeek(INT16 Year, UINT8 Month, UINT8 Day);
UINT8 UG_DT_Compare(struct Data_DateTime DT1,struct Data_DateTime DT2);//0=(DT1<DT2),1=(DT1=DT2),2=(DT1>DT2)
UINT32 UG_DTToUINT32(struct Data_DateTime DT);//seconds of (Time-BaseDT)
void UG_UINT32ToDT(UINT32 SV,struct Data_DateTime *DT);//seconds of (Time-BaseDT)
void UG_DTToByte8(struct Data_DateTime DT,UINT8 *B,UINT8 Mode);
void UG_Byte8ToDT(UINT8* B,struct Data_DateTime *DT,UINT8 Mode);
void UG_DTToString(struct Data_DateTime DT,UINT8 *s,UINT16 *sLen,UINT8 Flag);
void UG_DT_RefreshMiniSecond(void);
void UG_DT_Timer(struct Data_DateTime *DT);//every 1s
#endif

#if UG_LdyFunc_On
  unsigned long UG_LdyRand(unsigned long Range);//Return a Number(0<=n<Range)
  double UG_LdyMod(double x,double y);
#endif
#if UG_LdySin_On
  float UG_LdySin(float x);
  float UG_LdyCos(float x);
  float UG_LdyASin(float x);
  float UG_LdyACos(float x);
  float UG_LdyTan(float x);
  float UG_LdyCtg(float x);
  float UG_LdyATan(float x);
  float UG_LdyACtg(float x);
#endif
#if UG_LdySqrt_On
  float UG_LdySqrt(float x);
#endif
#if UG_LdyEXPLOG_On||UG_String_On
double UG_LdyExpINT(int k);
double UG_LdyExp10INT(int k);
#endif
#if UG_LdyEXPLOG_On
double UG_LdyExp(double x);
double UG_LdyExp10(double x);
double UG_LdyLog(double x);
double UG_LdyLog10(double x);
double UG_LdyPow(double x,double y);
#endif
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------
