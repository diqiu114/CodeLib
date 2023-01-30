//==============================================================================================================================
#include "Global.h"
//==============================================================================================================================
const UINT8             UG_COM_Head_LDY[4]={0x55,0xAA,0x00,0x00},UG_COM_Head_LS[4]={0x5A,0xA5,0x0D,0x0A},UG_COM_Head_YY[2]={0x7F,0x0A};
const UINT8             UG_CRLF[2]={13,10};
#if UG_LdyEXPLOG_On||UG_String_On
const double UG_Double_EXPT[]={//10^(1,2,...9),10^(10,20,...90),10^(100,200,...900),10^(1000,2000,...9000),10^(10000,20000,...90000)
                        1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,
                        1e10,1e20,1e30,1e40,1e50,1e60,1e70,1e80,1e90,
                        1e100,1e200,1e300
                        };
const double UG_Double_EXPE[]={//e^(1,2,...9),e^(10,20,...90),e^(100,200,...900),e^(1000,2000,...9000),e^(10000,20000,...90000)
                        2.7182818284590452353602874713527,7.389056098930650227230427460575,20.085536923187667740928529654582,
                        54.598150033144239078110261202861,148.41315910257660342111558004055,403.42879349273512260838718054339,
                        1096.6331584284585992637202382881,2980.9579870417282747435920994529,8103.0839275753840077099966894328,
                        22026.465794806716516957900645284,485165195.40979027796910683054154,10686474581524.462146990468650741,
                        235385266837019985.40789991074903,5184705528587072464087.4533229335,114200738981568428366295718.31448,
                        2515438670919167006265781174252.1,5.5406223843935100525711733958317e+34,1.2204032943178408020027100351364e+39,
                        2.68811714181613544841262555158e+43,7.2259737681257492581774770421893e+86,1.9424263952412559365842088360177e+130,
                        5.2214696897641439505887630066496e+173,1.4035922178528374107397703328409e+217,3.7730203009299398234014311934831e+260,
                        1.0142320547350045094553295952313e+304
                        };
#endif
#if UG_LdySin_On
const UINT16 UG_SinData[]={
                        0,    257,  514,  771,  1028, 1285, 1541, 1797, 2053, 2308,
                        2563, 2816, 3070, 3322, 3574, 3824, 4074, 4323, 4570, 4817,
                        5062, 5307, 5549, 5791, 6031, 6269, 6506, 6742, 6975, 7207,
                        7438, 7666, 7893, 8117, 8340, 8560, 8778, 8995, 9209, 9420,
                        9630, 9837, 10041,10243,10443,10640,10834,11026,11215,11401,
                        11585,11765,11943,12118,12289,12458,12624,12786,12945,13102,
                        13254,13404,13550,13693,13833,13969,14102,14231,14357,14479,
                        14598,14713,14824,14932,15036,15136,15233,15326,15415,15500,
                        15582,15659,15733,15803,15869,15931,15989,16043,16093,16140,
                        16182,16220,16254,16285,16311,16333,16351,16365,16375,16381,
                        16384,16381
                        };//SinData_N=100,SinData_D=PAI/2/SinData_N,KSin=16384(2^14)
#endif
#if UG_LdySqrt_On
const UINT16 UG_SqrtData[]={
                        0,647,915,1121,1295,1448,1586,1713,1831,1942,
                        2048,2147,2243,2335,2423,2508,2590,2670,2747,2822,
                        2896,2967,3037,3105,3172,3238,3302,3365,3426,3487,
                        3547,3605,3663,3720,3776,3831,3885,3939,3992,4044,
                        4095,4146,4197,4246,4295,4344,4392,4439,4486,4533,
                        4579,4625,4670,4714,4759,4802,4846,4889,4932,4974,
                        5016,5058,5099,5140,5181,5221,5261,5301,5340,5379,
                        5418,5457,5495,5533,5571,5608,5645,5682,5719,5756,
                        5792,5828,5864,5900,5935,5970,6005,6040,6075,6109,
                        6143,6178,6211,6245,6279,6312,6345,6378,6411,6443,
                        6476,6508,6540,6572,6604,6636,6667,6699,6730,6761,
                        6792,6823,6853,6884,6914,6945,6975,7005,7035,7064,
                        7094,7123,7153,7182,7211,7240,7269,7298,7327,7355,
                        7384,7412,7440,7468,7496,7524,7552,7580,7607,7635,
                        7662,7690,7717,7744,7771,7798,7825,7852,7878,7905,
                        7931,7958,7984,8010,8036,8062,8088,8114,8140,8166,
                        8192,8217,8243,8268,8293,8319,8344,8369,8394,8419,
                        8444,8468,8493,8518,8542,8567,8591,8616,8640,8664,
                        8688,8713,8737,8761,8784,8808,8832,8856,8879,8903,
                        8927,8950,8973,8997,9020,9043,9066,9089,9113,9136,
                        9158,9181,9204,9227,9250,9272,9295,9317,9340,9362,
                        9385,9407,9429,9451,9474,9496,9518,9540,9562,9584,
                        9605,9627,9649,9671,9692,9714,9736,9757,9779,9800,
                        9821,9843,9864,9885,9906,9928,9949,9970,9991,10012,
                        10033,10054,10074,10095,10116,10137,10157,10178,10198,10219,
                        10240,10260,10280,10301,10321,10341,10362,10382,10402,10422,
                        10442,10462,10482,10502,10522,10542,10562,10582,10602,10622,
                        10641,10661,10681,10700,10720,10739,10759,10778,10798,10817,
                        10837,10856,10875,10894,10914,10933,10952,10971,10990,11009,
                        11028,11047,11066,11085,11104,11123,11142,11161,11179,11198,
                        11217,11236,11254,11273,11291,11310,11328,11347,11365,11384,
                        11402,11421,11439,11457,11476,11494,11512,11530,11548,11567,
                        11585,11603,11621,11639,11657,11675,11693,11711,11729,11747,
                        11764,11782,11800,11818,11835,11853,11871,11888,11906,11924,
                        11941,11959,11976,11994,12011,12029,12046,12064,12081,12098,
                        12116,12133,12150,12167,12185,12202,12219,12236,12253,12270,
                        12288,12305,12322,12339,12356,12373,12389,12406,12423,12440,
                        12457,12474,12491,12507,12524,12541,12558,12574,12591,12608,
                        12624,12641,12657,12674,12690,12707,12723,12740,12756,12773,
                        12789,12806,12822,12838,12855,12871,12887,12904,12920,12936,
                        12952,12968,12985,13001,13017,13033,13049,13065,13081,13097,
                        13113,13129,13145,13161,13177,13193,13209,13225,13240,13256,
                        13272,13288,13304,13319,13335,13351,13367,13382,13398,13413,
                        13429,13445,13460,13476,13491,13507,13522,13538,13553,13569,
                        13584,13600,13615,13631,13646,13661,13677,13692,13707,13723,
                        13738,13753,13768,13784,13799,13814,13829,13844,13859,13875,
                        13890,13905,13920,13935,13950,13965,13980,13995,14010,14025,
                        14040,14055,14070,14085,14099,14114,14129,14144,14159,14174,
                        14188,14203,14218,14233,14247,14262,14277,14292,14306,14321,
                        14335,14350,14365,14379,14394,14408,14423,14438,14452,14467,
                        14481,14495,14510,14524,14539,14553,14568,14582,14596,14611,
                        14625,14639,14654,14668,14682,14697,14711,14725,14739,14754,
                        14768,14782,14796,14810,14824,14839,14853,14867,14881,14895,
                        14909,14923,14937,14951,14965,14979,14993,15007,15021,15035,
                        15049,15063,15077,15091,15105,15119,15133,15146,15160,15174,
                        15188,15202,15215,15229,15243,15257,15270,15284,15298,15312,
                        15325,15339,15353,15366,15380,15394,15407,15421,15434,15448,
                        15462,15475,15489,15502,15516,15529,15543,15556,15570,15583,
                        15597,15610,15623,15637,15650,15664,15677,15690,15704,15717,
                        15730,15744,15757,15770,15784,15797,15810,15823,15837,15850,
                        15863,15876,15890,15903,15916,15929,15942,15955,15969,15982,
                        15995,16008,16021,16034,16047,16060,16073,16086,16099,16112,
                        16125,16138,16151,16164,16177,16190,16203,16216,16229,16242,
                        16255,16268,16281,16294,16306,16319,16332,16345,16358,16371,
                        16383,16396,16409,16422,16435,16447,16460,16473,16486,16498,
                        16511,16524,16536,16549,16562,16574,16587,16600,16612,16625,
                        16637,16650,16663,16675,16688,16700,16713,16725,16738,16751,
                        16763,16776,16788,16801,16813,16825,16838,16850,16863,16875,
                        16888,16900,16912,16925,16937,16950,16962,16974,16987,16999,
                        17011,17024,17036,17048,17061,17073,17085,17097,17110,17122,
                        17134,17146,17159,17171,17183,17195,17208,17220,17232,17244,
                        17256,17268,17280,17293,17305,17317,17329,17341,17353,17365,
                        17377,17389,17401,17413,17425,17438,17450,17462,17474,17486,
                        17498,17510,17522,17533,17545,17557,17569,17581,17593,17605,
                        17617,17629,17641,17653,17665,17676,17688,17700,17712,17724,
                        17736,17747,17759,17771,17783,17795,17806,17818,17830,17842,
                        17853,17865,17877,17889,17900,17912,17924,17936,17947,17959,
                        17971,17982,17994,18006,18017,18029,18040,18052,18064,18075,
                        18087,18098,18110,18122,18133,18145,18156,18168,18179,18191,
                        18202,18214,18225,18237,18248,18260,18271,18283,18294,18306,
                        18317,18329,18340,18352,18363,18374,18386,18397,18409,18420,
                        18431,18443,18454,18466,18477,18488,18500,18511,18522,18534,
                        18545,18556,18567,18579,18590,18601,18613,18624,18635,18646,
                        18658,18669,18680,18691,18702,18714,18725,18736,18747,18758,
                        18770,18781,18792,18803,18814,18825,18837,18848,18859,18870,
                        18881,18892,18903,18914,18925,18936,18948,18959,18970,18981,
                        18992,19003,19014,19025,19036,19047,19058,19069,19080,19091,
                        19102,19113,19124,19135,19146,19157,19168,19179,19190,19200,
                        19211,19222,19233,19244,19255,19266,19277,19288,19298,19309,
                        19320,19331,19342,19353,19364,19374,19385,19396,19407,19418,
                        19428,19439,19450,19461,19472,19482,19493,19504,19515,19525,
                        19536,19547,19558,19568,19579,19590,19600,19611,19622,19632,
                        19643,19654,19664,19675,19686,19696,19707,19718,19728,19739,
                        19750,19760,19771,19781,19792,19803,19813,19824,19834,19845,
                        19856,19866,19877,19887,19898,19908,19919,19929,19940,19950,
                        19961,19971,19982,19992,20003,20013,20024,20034,20045,20055,
                        20066,20076,20087,20097,20107,20118,20128,20139,20149,20159,
                        20170,20180,20191,20201,20211,20222,20232,20243,20253,20263,
                        20274,20284,20294,20305,20315,20325,20336,20346,20356,20366,
                        20377,20387,20397,20408,20418,20428,20438,20449,20459,20469,
                        20479
                        };//SqrtData_N=1000,SqrtData_D=100/SqrtData_N,SqrtData_K=2048(2^11)
#endif
#if UG_DateTime_On
const UINT8 UG_DateTime_MD[12]={31,28,31,30,31,30,31,31,30,31,30,31};
#endif
//==============================================================================================================================
#if UG_Delay_On
void UG_Delay_US(unsigned int Time)//TimeUnit=us,Delay by instruction
{
  UINT32 i,j;
	if(!CPU_On)return; 
  for (i=0x00;i<Time;i++){if(CPU_On){for(j=0x00;j<0x08;j++)NOP();}}
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_Delay_MS(unsigned int Time) //TimeUnit=ms,Delay by instruction
{
  UINT32 i,j;
	if(!CPU_On)return;
  for (i=0x00;i<Time;i++){if(CPU_On){for(j=0x00;j<0x1F00;j++)NOP();}}
}
//------------------------------------------------------------------------------------------------------------------------------
void UG_Delay_TimerTime(unsigned int Time)//TimeUnit=ms,Delay by timer
{                             
	UINT32 i;
  i=SysTimeCount;while(SysTimeCount-i<Time);
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_Delay_Time(unsigned int Time,unsigned char IsStruction) //TimeUnit=ms
{
  if(IsStruction) UG_Delay_MS(Time); else UG_Delay_TimerTime(Time);
}
#endif
//==============================================================================================================================
#if UG_String_On
UINT16 UG_StrLen(UINT8 *s,UINT16 MaxLen)
{
  UINT16 i=0;
  while(s[i]!=0x00 && i<MaxLen) i++;
  return(i);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_IsVarChar(UINT8 c,UINT8 IsFirst)
{
	if((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_') return(1);
	if(IsFirst==0 && c>='0' && c<='9')return(1);
	return(0);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrCompareChar(UINT8 c1,UINT8 c2,UINT8 Mode)
{
  if(Mode==0){if(c1>='a' && c1<='z')c1=c1+'A'-'a';  if(c2>='a' && c2<='z')c2=c2+'A'-'a';}
  return(c1==c2 ? 1:(c1<c2 ? 0:2));
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrCompare(UINT8 *s1,UINT8 *s2,UINT16 Len,UINT8 Mode)// 0=(s1<s2),1=(s1=s2),2=(s1>s2),Mode=1区分大小写
{
	UINT16 i;UINT8 c;
	for(i=0;i<Len;i++){c=UG_StrCompareChar(s1[i],s2[i],Mode); if(c!=1)break;}
	return(c);
}
//-----------------------------------------------------------------------------------------------------------------------------
INT16 UG_StrFind(UINT8 *src,UINT16 srcLen, UINT8 *std, UINT16 stdLen,UINT8 Mode)//在src中查找std,found return [0,N-1],nofound return -1
{
  UINT16 i=0x0000,j=0x0000;UINT8 c;
  if(stdLen==0x00||srcLen<stdLen)return(-1);
  while(i+stdLen<=srcLen)
  {for(j=0;j<stdLen;j++){c=UG_StrCompareChar(src[i+j],std[j],Mode);if(c!=1)break;} if(j==stdLen) return(i); i++;}
  return(-1);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrFindItem(UINT8 *src, UINT16 srcLen, UINT8 Flag,UINT16 Index,UINT16 *Pos,UINT16 *Len)//查找s中以Flag隔开的,第Index项的位置与长度
{
  UINT16 i=0,j=0;INT16 k[3]={0x00,0x00,0x00};UINT8 StringOn=0,Found=0;
  if(Index==0){Found=1;*Pos=i;}
  for(i=0;i<srcLen;i++)
  {
    if(src[i]=='"')
    {StringOn=!StringOn;}
    else if(!StringOn)
    {
      if(src[i]=='('||src[i]==')')
      { k[0]+=(src[i]=='(' ? 1:-1);}
      else if(src[i]=='['||src[i]==']')
      { k[1]+=(src[i]=='[' ? 1:-1);}
      else if(src[i]=='<'||src[i]=='>')
      { k[2]+=(src[i]=='<' ? 1:-1);}
      else if(k[0]==0x00 && k[1]==0x00 && k[2]==0x00 && src[i]==Flag)
      {j++;if(Found){*Len=i-(*Pos); return(Found);} else if(Index==j){Found=1;*Pos=i+1;}} 
    }
  }
  if(Found)*Len=i-(*Pos);
  return(Found);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrFindItemStr(UINT8 *src, UINT16 srcLen, UINT8 Flag,UINT8 *std,UINT16 stdLen,UINT16 *stdIndex,UINT8 Mode)//查找s中以Flag隔开的std项
{
  UINT16 i,Len,Index=0;INT16 k[3]={0x00,0x00,0x00};UINT8 StringOn=0,ItemErr=0,ItemFirstOn=0;
	if (UG_StrTrim(std,stdLen,&i,&Len)){std+=i;stdLen=Len-i+1;} else return(0);
  for(i=0;i<srcLen;i++)
  {
    if(src[i]=='"')
    {StringOn=!StringOn;}
    else if(!StringOn)
    {
      if(src[i]=='('||src[i]==')')
      { k[0]+=(src[i]=='(' ? 1:-1);}
      else if(src[i]=='['||src[i]==']')
      { k[1]+=(src[i]=='[' ? 1:-1);}
      else if(src[i]=='<'||src[i]=='>')
      { k[2]+=(src[i]=='<' ? 1:-1);}
      else if(k[0]==0x00 && k[1]==0x00 && k[2]==0x00)
      {
				if(src[i]==Flag)
				{if(!ItemErr && Len==stdLen){*stdIndex=Index;return(1);} Index++;ItemErr=ItemFirstOn=Len=0x00;}
				else if(!ItemErr)
				{
					if(!ItemFirstOn && src[i]!=' '){ItemFirstOn=1;Len=0;}
    			if(ItemFirstOn)
					{if(Len<stdLen){if(UG_StrCompareChar(src[i],std[Len++],Mode)!=1)ItemErr=1;} else	{if( src[i]!=' ')ItemErr=1;}}
				}
			} 
    }
  }
	if(!ItemErr && Len==stdLen){*stdIndex=Index;return(1);} else return(0);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 UG_StrReplace(UINT8 *src, UINT16 *srcLen,UINT8 *std,UINT16 stdLen,UINT8 *srp,UINT16 srpLen,UINT8 Mode)//返回替换次数
{
  UINT16 i=0,j=0,Count=0;
  while(i+stdLen<=*srcLen)
  {
    for(j=0;j<stdLen;j++){if(UG_StrCompareChar(src[i+j],std[j],Mode)!=1)break;}
    if(j==stdLen)
    {
      if(stdLen!=srpLen)
      {
        for(j=0;j<*srcLen-(i+stdLen);j++)
        {if(srpLen<stdLen)src[srpLen+i+j]=src[stdLen+i+j]; else src[*srcLen-1+srpLen-stdLen-j]=src[*srcLen-1-j];}
      }
      for(j=0;j<srpLen;j++)src[i+j]=srp[j]; (*srcLen)+=srpLen-stdLen; i+=srpLen;Count++;
    }
    else
    {i++;}
  }
  return(Count);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 UG_StrReplacePos(UINT8 *src,UINT16 *srcLen,UINT16 stdPos,UINT16 stdLen,UINT8 *srp,UINT16 srpLen)//返回替换次数
{
  UINT16 j;
  if(stdPos+stdLen<=*srcLen)
  {
    if(stdLen!=srpLen)
    {
      for(j=0;j<*srcLen-(stdPos+stdLen);j++)
      {if(srpLen<stdLen)src[srpLen+stdPos+j]=src[stdPos+stdLen+j]; else src[*srcLen-1-j+srpLen-stdLen]=src[*srcLen-1-j];}
    }
    for(j=0;j<srpLen;j++)src[stdPos+j]=srp[j]; (*srcLen)+=srpLen-stdLen; return(1);
  }
  return(0);	
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_StrSet(UINT8 *s,UINT16 Len,UINT8 c)
{
  UINT16 i;
  for(i=0;i<Len;i++)s[i]=c;
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_StrCopy(UINT8 *std,UINT8 *src,UINT16 Len)
{
	UINT16 i;
	if(std==src)return;
	for(i=0;i<Len;i++)std[i]=src[i];
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrLTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos)
{
	UINT16 i;
	for(i=0;i<srcLen;i++){if(src[i]!=' ')(*LPos)=i;return(1);}
	return(0);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrRTrim(UINT8 *src,UINT16 srcLen,UINT16 *RPos)
{
	UINT16 i;
	for(i=0;i<srcLen;i++) if(src[srcLen-1-i]!=' '){(*RPos)=srcLen-1-i;return(1);}
	return(0);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_StrTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos,UINT16 *RPos)
{
	return(UG_StrLTrim(src,srcLen,LPos) && UG_StrRTrim(src,srcLen,RPos));
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_StrCat(UINT8 *std,UINT16 *stdLen,UINT8 *src, UINT16 srcLen)
{
  UINT16 i;
	for(i=0;i<srcLen;i++)std[(*stdLen)++]=src[i];
}
//------------------------------------------------------------------------------------------------------------------------------
void UG_StrAddItem(UINT8 *std,UINT16 *stdLen,UINT8 *src,UINT16 srcLen,UINT8 Flag)//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00 
{
  if(*stdLen && Flag&Str_Flag_AddD)std[(*stdLen)++]=',';if(Flag&Str_Flag_AddY)std[(*stdLen)++]='"';
  UG_StrCat(std,stdLen,src,srcLen);if(Flag&Str_Flag_AddY)std[(*stdLen)++]='"';if(Flag&Str_Flag_AddJ)std[(*stdLen)++]=0x00;
}
//------------------------------------------------------------------------------------------------------------------------------
void UG_StrAddItemNum(UINT8 *std,UINT16 *stdLen,double Num,UINT8 NumPCount,UINT8 Flag)//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00 
{
  UINT8 buf[20];UINT16 bufLen;
  UG_NumToStr(Num,NumPCount,buf,&bufLen);UG_StrAddItem(std,stdLen,buf,bufLen,Flag);
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_ValueToStr(UINT8 *s,UINT64 V,UINT8 Len)
{
  if(Len>0 && Len<=8)UG_StrCopy(s,(UINT8 *)&V,Len);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT64 UG_StrToValue(UINT8 *s,UINT8 Len)
{
  UINT64 V=0;
  if(Len>0 && Len<=8)UG_StrCopy((UINT8 *)&V,s,Len);return(V);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT64 UG_ByteToValue(UINT8 *s,UINT8 Len,UINT8 HighToLow)
{
	UINT8 i;union UINT64_REG U64;
	for(i=0;i<8;i++){if(i<Len)U64.B[(HighToLow ? Len-1-i:i)]=s[i];else U64.B[i]=0x00;}
	return(U64.VAL);
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_StrAddValue(UINT8 *s,UINT8 sLen,UINT64 V,UINT8 VLen)
{
  UINT8 i;UINT16 k=0;
  for(i=0;i<sLen;i++){k+=s[i]+(V&0xFF);s[i]=k&0xFF;k>>=8;V>>=8;if(k==0 && i>=VLen-1)break;}
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_NumToStr(double Num,UINT8 NumPCount,UINT8 *s,UINT16 *Len)
{
	UINT8 i,kp,Sign=0,c,PCount;int Temp;
  if(Num<0){Num=-Num;Sign=1; *s++='-';} Temp=Num;Num-=Temp;(*Len)=0x00;
	while(Temp||(*Len)==0){s[(*Len)++]=(Temp%10)+'0';Temp/=10;}
	for(i=0;i<(*Len)/2;i++){c=s[i];s[i]=s[(*Len)-1-i];s[(*Len)-1-i]=c;};
  PCount=(NumPCount>=*Len ? NumPCount-*Len:0);  i=0x00;
  while(i<PCount && Num>=(double)1.0/UG_LdyExp10INT(PCount-i))
  {if(i==0){kp=(*Len);s[(*Len)++]='.';} Num*=10;Temp=Num;Num-=Temp;s[(*Len)++]=(Temp%10)+'0';i++;}
  if(Num*10>=5 && i==PCount){c=0x00;for(i=*Len-1;i>kp;i--){if(s[i]=='9'){c++;} else {if(c>=3){s[i]++;*Len=i+1;} break;}}}
  s[*Len]=0x00;(*Len)+=Sign;
}
//-----------------------------------------------------------------------------------------------------------------------------
double UG_StrToNum(UINT8 *s,UINT16 Len)
{
	UINT16 i,pos;UINT8 Sign=0,SignOn=0,PointOn=0,EXPOn=0;double V=0;int VE=0;
	for(i=0;i<Len;i++)
  {
    if(s[i]>='0' && s[i]<='9')
    {if(EXPOn){VE=VE*10+(s[i]-'0');} else if(PointOn) V=V+(s[i]-'0')/UG_LdyExp10INT(i-pos); else V=V*10+(s[i]-'0');}
    else if(s[i]=='+'||s[i]=='-')
    {if(SignOn==0){if(s[i]=='-')Sign=1;}else break;}
    else if(s[i]=='.' )
    {if(PointOn==0){PointOn=1;pos=i;} else break;}
    else if(s[i]=='e'||s[i]=='E')
    {if(EXPOn==0){if(Sign)V=-V;EXPOn=1;SignOn=0;Sign=0;pos=i;}else break;}
    else if(s[i]!=' ')
    {break;}
  }
  if(Sign){if(EXPOn)VE=-VE; else V=-V;} 
  for(i=0;i<ABS(VE);i++)V*=(VE>0 ? 10:0.1);
	return(V);
}
#endif
//==============================================================================================================================
#if UG_DateTime_On
UINT8 UG_IsLeapYear(INT16 Year)
{
	if(Year<=0)Year=-Year;
	return(((Year%4) == 0 && (Year%100)!=0) || ((Year % 400)== 0) ? 1:0);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 UG_YearDay(INT16 Year)
{
  return (365 + (UG_IsLeapYear(Year) ? 1:0));
}
//-----------------------------------------------------------------------------------------------------------------------------
INT32 UG_YearDays(INT16 Year)
{
	INT32 DBY;
	DBY=(Year<=0 ? -Year:Year-1);DBY=DBY*365+DBY/4-DBY/100+DBY/400;if(Year<=0)DBY=-DBY-366;
	return(DBY);
}
//-----------------------------------------------------------------------------------------------------------------------------
INT32 UG_DaysBetweenYear(INT16 Year1, INT16 Year2)
{
	return(UG_YearDays(Year2)-UG_YearDays(Year1));
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT16 UG_DaysBetweenMonth(INT16 Year, UINT8 Month1, UINT8 Month2)
{
	UINT16 i,DBM=0x0000;
  if(Month1 >= 1 && Month2 >= Month1 && Month2 <= 12)
  for(i=Month1;i<Month2;i++) {DBM+=UG_DateTime_MD[i - 1];if(i == 2 && UG_IsLeapYear(Year))DBM++;}
	return(DBM);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_MonthDay(INT16 Year, UINT8 Month)
{ 
  return((Month >= 1 && Month <= 12 ? UG_DateTime_MD[Month - 1]+(Month == 2 && UG_IsLeapYear(Year) ? 1:0):0) );	
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_YMDToWeek(INT16 Year, UINT8 Month, UINT8 Day)
{
  UINT32 i,W;
  W=(Year<=0 ? -Year:Year-1);W=W+(W/4)-(W/100)+(W/400); if(Year<=0)W=12-W%7;else W=W%7;
  for(i=1;i<Month;i++)W+=UG_DateTime_MD[i-1]%7;W+=Day;W%=7;
  return(W);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT8 UG_DT_Compare(struct Data_DateTime DT1,struct Data_DateTime DT2)//0=(DT1<DT2),1=(DT1=DT2),2=(DT1>DT2)
{
	if(DT1.Year<DT2.Year) return(0); else {if(DT1.Year>DT2.Year)return(2);}
	if(DT1.Month<DT2.Month)return(0); else {if(DT1.Month>DT2.Month)return(2);}
	if(DT1.Day<DT2.Day)return(0);else {if(DT1.Day>DT2.Day) return(2);}
	if(DT1.Hour<DT2.Hour)return(0);else {if(DT1.Hour>DT2.Hour)return(2);}
	if(DT1.Minute<DT2.Minute)return(0);else {if(DT1.Minute>DT2.Minute)return(2);}
	if(DT1.Second_BIT.V<DT2.Second_BIT.V)return(0);else {if(DT1.Second_BIT.V>DT2.Second_BIT.V)return(2);}
	if(DT1.Second_BIT.M<DT2.Second_BIT.M)return(0);else {if(DT1.Second_BIT.M>DT2.Second_BIT.M)return(2);}
	return(1);
}
//-----------------------------------------------------------------------------------------------------------------------------
UINT32 UG_DTToUINT32(struct Data_DateTime DT)//seconds of (Time-BaseDT)
{
  UINT32 SV=0;
  if(UG_DT_Compare(DT,DAPP.BaseDT))
	{
    SV= UG_DaysBetweenYear(DAPP.BaseDT.Year, DT.Year)+ (UG_DaysBetweenMonth(DT.Year, 1, DT.Month)+DT.Day)-(UG_DaysBetweenMonth(DAPP.BaseDT.Year,1,DAPP.BaseDT.Month)+DAPP.BaseDT.Day);
    SV= SV* 24 * 3600 + (DT.Hour * 3600 + DT.Minute * 60 + DT.Second_BIT.V)-(DAPP.BaseDT.Hour*3600+DAPP.BaseDT.Minute*60+DAPP.BaseDT.Second_BIT.V);
  }
  return(SV);
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_UINT32ToDT(UINT32 SV,struct Data_DateTime *DT)//seconds of (Time-BaseDT)
{
	UINT32 DBY;
  SV+=(DAPP.BaseDT.Hour*3600+DAPP.BaseDT.Minute*60+DAPP.BaseDT.Second_BIT.V);
  (*DT).Second_BIT.M=0;(*DT).Second_BIT.V=SV%60;SV/=60;(*DT).Minute=SV%60;SV/=60;(*DT).Hour=SV%24;SV/=24;
  SV+=(UG_DaysBetweenMonth(DAPP.BaseDT.Year,1,DAPP.BaseDT.Month)+DAPP.BaseDT.Day-1);
	(*DT).Year=DAPP.BaseDT.Year+SV/365;
	DBY=UG_DaysBetweenYear(DAPP.BaseDT.Year,(*DT).Year);
  while(DBY>SV){(*DT).Year--;DBY-=UG_YearDay((*DT).Year);}
	SV-=DBY;(*DT).Month=1+SV/29;
  DBY=UG_DaysBetweenMonth((*DT).Year,1,(*DT).Month);
	while(DBY>SV){(*DT).Month--;DBY-=UG_MonthDay((*DT).Year,(*DT).Month);}
	SV-=DBY;(*DT).Day=1+SV;
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_DTToByte8(struct Data_DateTime DT,UINT8 *B,UINT8 Mode)//0=Simple,1=Struct,2=Value
{
  UINT8 i,F=0;union UINT64_REG U64;
  if(Mode==DateTime_Mode_Simple)
  {
	  B[0]=DT.Second_BIT.M/10;B[1]=DT.Second_BIT.V;B[6]=DT.Year%100;B[7]=DT.Year/100;F=1;
  }
  else if(Mode==DateTime_Mode_Struct)
  {
    B[0]=DT.Second&0xff;B[1]=DT.Second>>8;B[6]=(UINT16)DT.Year&0xff;B[7]=(UINT16)DT.Year>>8;F=1;
  }
  else if(Mode==DateTime_Mode_Value)//miniseconds of (Time-BaseDT)
  {
    U64.VAL=UG_DaysBetweenYear(DAPP.BaseDT.Year, DT.Year)+(UG_DaysBetweenMonth(DT.Year, 1, DT.Month)+DT.Day)-(UG_DaysBetweenMonth(DAPP.BaseDT.Year,1,DAPP.BaseDT.Month)+DAPP.BaseDT.Day);
    U64.VAL=U64.VAL*24*3600+(DT.Hour*3600+DT.Minute*60+DT.Second_BIT.V)-(DAPP.BaseDT.Hour*3600+DAPP.BaseDT.Minute*60+DAPP.BaseDT.Second_BIT.V);
    U64.VAL=U64.VAL*1000+DT.Second_BIT.M-DAPP.BaseDT.Second_BIT.M;
    for(i=0;i<8;i++)B[i]=U64.B[i];
  }    
  if(F){B[2]=DT.Minute;B[3]=DT.Hour;B[4]=DT.Day;B[5]=DT.Month;}
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_Byte8ToDT(UINT8* B,struct Data_DateTime *DT,UINT8 Mode)//0=Simple,1=Struct,2=Value
{
	UINT8 i,F=0;union UINT64_REG U64;UINT32 DBY;
  if(Mode==DateTime_Mode_Simple)
  {
    if(B[0]>99)B[0]=99;if(B[1]>59)B[1]=59;if(B[6]>99)B[6]=99;if(B[7]>99)B[7]=99;
    (*DT).Year=B[6]+B[7]*100;(*DT).Second_BIT.M=B[0]*10;(*DT).Second_BIT.V=B[1];F=1;
  }
  else if(Mode==DateTime_Mode_Struct)
  {    
    (*DT).Second=B[0]|(UINT16)B[1]<<8;if((*DT).Second_BIT.V>59) (*DT).Second_BIT.V=59;if((*DT).Second_BIT.M>999)(*DT).Second_BIT.M=999;
    (*DT).Year=B[6]|(UINT16)B[7]<<8;F=1;
  }
  else if(Mode==DateTime_Mode_Value)//miniseconds of (Time-BaseDT)
  {
	  for(i=0;i<8;i++)U64.B[i]=B[i];U64.VAL+=DAPP.BaseDT.Second_BIT.M;
    (*DT).Second_BIT.M=(U64.VAL)%1000;U64.VAL/=1000;
    U64.VAL+=(DAPP.BaseDT.Hour*3600+DAPP.BaseDT.Minute*60+DAPP.BaseDT.Second_BIT.V);
    (*DT).Second_BIT.V=U64.VAL%60;U64.VAL/=60; (*DT).Minute=U64.VAL%60;U64.VAL/=60; (*DT).Hour=U64.VAL%24;U64.VAL/=24;
    U64.VAL+=(UG_DaysBetweenMonth(DAPP.BaseDT.Year,1,DAPP.BaseDT.Month)+DAPP.BaseDT.Day-1);
	  (*DT).Year=DAPP.BaseDT.Year+U64.VAL/365;
	  DBY=UG_DaysBetweenYear(DAPP.BaseDT.Year,(*DT).Year);
    while(DBY>U64.VAL){(*DT).Year--;DBY-=UG_YearDay((*DT).Year);}
	  U64.VAL-=DBY;(*DT).Month=1+U64.VAL/29;
    DBY=UG_DaysBetweenMonth((*DT).Year,1,(*DT).Month);
	  while(DBY>U64.VAL){(*DT).Month--;DBY-=UG_MonthDay((*DT).Year,(*DT).Month);}
	  U64.VAL-=DBY;(*DT).Day=1+U64.VAL;
  }
  if(F)
  {    
	  if(B[2]>59)B[2]=59;if(B[3]>23)B[3]=23;
	  if(B[4]<1)B[4]=1;i=UG_MonthDay(B[6]+B[7]*100,B[5]);if(B[4]>i)B[4]=i;
	  if(B[5]<1)B[5]=1;if(B[5]>12)B[5]=12;
    (*DT).Minute=B[2];(*DT).Hour=B[3];(*DT).Day=B[4];(*DT).Month=B[5];
  }
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_DTToString(struct Data_DateTime DT,UINT8 *s,UINT16 *sLen,UINT8 Flag)
{
	*sLen=0x00;
	if(Flag&1)
	{
	  s[*sLen+0]=((DT.Year/1000)%10)+'0';s[*sLen+1]=((DT.Year/100)%10)+'0';s[*sLen+2]=((DT.Year/10)%10)+'0';s[*sLen+3]=(DT.Year%10)+'0';s[*sLen+4]='/';
	  s[*sLen+5]=((DT.Month/10)%10)+'0';s[*sLen+6]=(DT.Month%10)+'0';s[*sLen+7]='/';  s[*sLen+8]=((DT.Day/10)%10)+'0';s[*sLen+9]=(DT.Day%10)+'0';
		(*sLen)+=10;
	}
  if(Flag&2)
  {
    if(*sLen){s[*sLen]=' ';(*sLen)++;}
	  s[*sLen+0]=((DT.Hour/10)%10)+'0';s[*sLen+1]=(DT.Hour%10)+'0';s[*sLen+2]=':';
	  s[*sLen+3]=((DT.Minute/10)%10)+'0';s[*sLen+4]=(DT.Minute%10)+'0';s[*sLen+5]=':';
	  s[*sLen+6]=((DT.Second_BIT.V/10)%10)+'0';s[*sLen+7]=(DT.Second_BIT.V%10)+'0';s[*sLen+8]=':';
		s[*sLen+9]=((DT.Second_BIT.M/100)%10)+'0';s[*sLen+10]=((DT.Second_BIT.M/10)%10)+'0';s[*sLen+11]=(DT.Second_BIT.M%10)+'0';
		(*sLen)+=12;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_DT_RefreshMiniSecond(void)
{
  TMRCount[0]=(DAPP.DT.Second_BIT.M%5);
  TMRCount[1]=(DAPP.DT.Second_BIT.M/5) % 2;
  TMRCount[2]=(DAPP.DT.Second_BIT.M/10) %10;
  TMRCount[3]=(DAPP.DT.Second_BIT.M/100) % 10;
}
//-----------------------------------------------------------------------------------------------------------------------------
void UG_DT_Timer(struct Data_DateTime *DT)//every 1s
{
	(*DT).Second_BIT.V++;	if((*DT).Second_BIT.V<60)return; else (*DT).Second_BIT.V=0;
	(*DT).Minute++; if((*DT).Minute<60)return; else (*DT).Minute=0;
	(*DT).Hour++;   if((*DT).Hour<24)return; else (*DT).Hour=0;
	(*DT).Day++;    if((*DT).Day<=UG_MonthDay((*DT).Year,(*DT).Month)) return; else (*DT).Day=1;
	(*DT).Month++;  if((*DT).Month<=12)return; else (*DT).Month=1;
	(*DT).Year++;
}
#endif
//==============================================================================================================================
#if UG_LdyFunc_On
UINT32 UG_LdyRand(UINT32 Range)
{
  static unsigned long i,j;
  if (Range==0) return(0);
  j++; i=((i+LdyRandPip)*(i+LdyRandPip)+j) % (Range+1);
  return(i);
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyMod(double x,double y)
{
  double z;
  z=x/y; if(z!=(int)z)z=(z<0 ? -1:0)+(int)z;
  return(y==0 ? x:x-z*y);
}
#endif
//==============================================================================================================================
#if UG_LdySin_On
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdySin(float x)//查表
{
  unsigned char Sign=0x00;
  long  k,ksin;
  float y,z,dx;
 
  if(x<0){x=-x;Sign=1;}
  k=x/(PAI/2.0);
  y=x-(float)k *(PAI/2);
  if(y<0)
    {y=y+PAI/2;k--;}
  else if (y>PAI/2)
    {y=y-PAI/2;k++;}
  ksin=y/UG_SinData_D;ksin=ksin%UG_SinData_Count;
  dx=(y - (float)ksin*UG_SinData_D);
  if ((k % 2)==0)
  {
    z=UG_SinData[ksin]+dx*UG_SinData[UG_SinData_Count-ksin];
    if ((k % 4)==2) z=-z;
  }
  else
  {
    z=UG_SinData[UG_SinData_Count-ksin-1]-dx*UG_SinData[ksin+1];
    if ((k % 4)==3) z=-z;
  }
  LimitValue(z,-UG_SinData_K,UG_SinData_K); if (Sign)z=-z;
  return(z/SinData_K);    
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyCos(float x)//查表
{
  long k,ksin;
  float y,z,dx;
  k=x/(PAI/2.0);
  y=x-(float)k *(PAI/2);
  if(y<0)
    {y=y+PAI/2;k--;}
  else if (y>PAI/2)
    {y=y-PAI/2;k++;}
  ksin=y/UG_SinData_D ;ksin=ksin % UG_SinData_Count;
  dx=(y - ksin*UG_SinData_D);
  if ((k % 2)==0)
  {
    if (dx < 0) {ksin = ksin - 1; dx = dx + UG_SinData_D;}
    z=UG_SinData[UG_SinData_Count-ksin-1]-dx*UG_SinData[ksin+1];
    if ((k % 4)==2) z=-z;
  }
  else
  {
    z=UG_SinData[ksin]+dx*UG_SinData[UG_SinData_Count-ksin] ;
    if ((k % 4)==1) z=-z;
  }
  LimitValue(z,-UG_SinData_K,UG_SinData_K);
  return(z/UG_SinData_K);    
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyASin(float x)//查表
{
  int M1, M2, M3;
  unsigned char Sign=0, Found=0;
  float z;
  if (x< 0) {x = -x; Sign = 1;}
  if (x> 1) x = 1;
  M1 = 0 ; M3 = UG_SinData_Count - 1;M2 = (M3 + M1) / 2;
  while (Found==0)
  {
    if ( M2 == M1 || M2 == M3 )
      Found = 1;
    else if (UG_SinData_K*x > UG_SinData[M2])
      {M1 = M2; M2 = (M3 + M2) / 2;}
    else if (UG_SinData_K*x < UG_SinData[M2])
      {M3 = M2; M2 = (M2 + M1) / 2;}
    else
      Found = 1;
  }
  z =M2 * UG_SinData_D;
  if (M2 < UG_SinData_Count - 1) z = z + (UG_SinData_K*x - UG_SinData[M2]) / UG_SinData[UG_SinData_Count - M2 - 1];
  if (Sign) z = -z;
  return (z);
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyACos(float x)//查表
{
  int M1, M2, M3;
  int Sign=0, Found=0;
  float z;
  if (x < 0) {x = -x; Sign = 1;} 
  if (x > 1) x = 1;
  M1 = 0 ; M3 = UG_SinData_Count - 1;M2 = (M3 + M1) / 2;
  while (Found==0)
  {
    if ( M2 == M1 || M2 == M3 )
      Found =1;
    else if (UG_SinData_K*x > UG_SinData[M2])
      {M1 = M2; M2 = (M3 + M2) / 2;}
    else if (UG_SinData_K*x < UG_SinData[M2])
      {M3 = M2; M2 = (M2 + M1) / 2;}
    else
      Found =1;
  }
  z = (UG_SinData_Count-1-M2) * UG_SinData_D;
  if (M2 > 0) z = z + (UG_SinData_K*x - UG_SinData[UG_SinData_Count - M2 - 1]) / UG_SinData[M2];
  if (Sign) z = (float)PAI-z;
  return (z);
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyTan(float x)//查表
{
  float y1,y2;
  y1=UG_LdySin(x);y2=UG_LdyCos(x);
  if(y2==0)
    {if (y1>0) return(16777215); else  return(-16777216);}
  else
    return (y1/y2);
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyCtg(float x)//查表
{
  float y1,y2;
  y1=UG_LdySin(x);y2=UG_LdyCos(x);
  if(y1==0)
    {if (y2>0) return(16777215); else  return(-16777216);}
  else
    return (y2/y1);
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyATan(float x)//查表
{
  int M1, M2, M3;
  int Sign=0, Found=0;
  float y1,y2,z;
  if (x==0) return(0);
  if (x < 0) {x = -x; Sign = 1;}

  M1 = 0 ; M3 = UG_SinData_Count - 1;M2 = (M3 + M1) / 2;
  while (Found==0)
  {
    y1= UG_SinData[M2];y2=UG_SinData[UG_SinData_Count-M2-1];
    if ( M2 == M1 || M2 == M3 )
      Found = 1;
    else if (y2*x >y1)
      {M1 = M2; M2 = (M3 + M2) / 2;}
    else if (y2*x <y1)
      {M3 = M2; M2 = (M2 + M1) / 2;}
    else
      Found = 1;
  }
  z = M2 * UG_SinData_D;
  if (Sign) z = -z;
  return (z);
}
//------------------------------------------------------------------------------------------------------------------------------
float UG_LdyACtg(float x)//查表
{
  int M1, M2, M3;
  int Sign=0, Found=0;
  float y1,y2,z;
  
  if (x==0) return(PAI/2);
  if (x < 0) {x = -x; Sign = 1;}

  M1 = 0 ; M3 = UG_SinData_Count - 1;M2 = (M3 + M1) / 2;
  while (Found==0)
    {
    y1= UG_SinData[M2];y2=UG_SinData[UG_SinData_Count-M2-1];
    if ( M2 == M1 || M2 == M3 )
      Found = 1;
    else if (y1*x <y2)
      {M1 = M2; M2 = (M3 + M2) / 2;}
    else if (y1*x >y2)
      {M3 = M2; M2 = (M2 + M1) / 2;}
    else
      Found = 1;
    }
  z = M2 * UG_SinData_D;
  if (Sign) z = -z;
  return (z);
}
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if UG_LdySqrt_On
float UG_LdySqrt(float x)//查表
{
  INT16 k,ke=0;
  float z,d,x0,y0;
  if(x<=0||x==1)return(x);
  while(x>100){x=x/10;ke++;}
  while(x<1){x=x*10;ke--;}
  if(ke & 1){if(x<10){x=x*10;ke--;}else{x=x/10;ke++;}};
  k=x/UG_SqrtData_D;x0=UG_SqrtData_D*k;d=x-x0;y0=(float)UG_SqrtData[k]/UG_SqrtData_K;
  z=y0+d/2/y0-d*d/8/y0/x0*(1-d/2/x0);
  ke/=2;while(ke>0){z*=10;ke--;} while(ke<0){z/=10;ke++;}
  return(z);
}
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if UG_LdyEXPLOG_On||UG_String_On
double UG_LdyExpINT(int k)
{
  UINT8 Sign=0;double z=(double)1.0;
  if(k==0){return((double)1.0);} else if(k<0){Sign=1;k=-k;}
  if(k>709){*(UINT64 *)&z=(Sign ? 0x01:0x7FFFFFFFFFFFFFFF);return(z);}
  if(k>=100){z*=UG_Double_EXPE[18+k/100-1];k%=100;}
  if(k>=10){z*=UG_Double_EXPE[9+k/10-1];k%=10;}
  if(k>=1)z*=UG_Double_EXPE[k-1];
  return(Sign ? (double)1.0/z:z);
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyExp10INT(int k)
{
  UINT8 Sign=0;double z=(double)1.0;
  if(k==0){return((double)1.0);} else if(k<0){Sign=1;k=-k;}
  if(k>308){*(UINT64 *)&z=(Sign ? 0x01:0x7FFFFFFFFFFFFFFF);return(z);}
  if(k>=100){z*=UG_Double_EXPT[18+k/100-1];k%=100;}
  if(k>=10){z*=UG_Double_EXPT[9+k/10-1];k%=10;}
  if(k>=1)z*=UG_Double_EXPT[k-1];
  return(Sign ? (double)1.0/z:z);
}
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if UG_LdyEXPLOG_On
double UG_LdyExp(double x)//泰勒级数+查表
{
  int i,k1=0,k2=0;UINT8 Sign=0; double z=(double)1.0,Item=(double)1.0;
  if(x==0)return(1); else if(x<0){Sign=1;x=-x;};
  if(x>709){*(UINT64 *)&z=(Sign ? 0x01:0x7FFFFFFFFFFFFFFF);return(z);}//float=[128*ln(2)]=88,double=[1024*ln(2)]=709
  k1=(int)x;x-=k1;
  if(x>0){while(x>=(double)0.1){k2++;x/=(double)2.0;} for(i=1;i<15;i++){Item*=(x/i);z+=Item;}  for(i=0;i<k2;i++)z=z*z;}
  z*=UG_LdyExpINT(k1); if(Sign)z=(double)1.0/z;
  return(z);  
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyLog(double x)//泰勒级数
{
  int i,k1=0,k2=0; double z=(double)0.0,Item=(double)1.0;
  if(x<=0.0 || x==1.0)return(0);//while x<=0,is error enter
  while(x<1){k1--;x*=(double)2.0;}; while(x>=2){k1++;x/=2;};//提取2^K1系数
  while(x>(double)1.1){k2++;x*=(double).9375;};//提取(15/16)^k2系数
  for(i=1;i<15;i++){Item=Item*(x-1); z=z+Item/i*(i&1 ? 1:-1);}
  z+=k2*(double)0.06453852113757117167292391568399;//ln(16/15)
  z+=k1*(double)0.69314718055994530941723212145818;//ln(2)
  return(z);
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyExp10(double x)
{
  return(UG_LdyExp(x*(double)2.3025850929940456840179914546844));//ln(10)
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyLog10(double x)
{
  return(UG_LdyLog(x)/(double)2.3025850929940456840179914546844);//ln(10)
}
//------------------------------------------------------------------------------------------------------------------------------
double UG_LdyPow(double x,double y)
{
  UINT8 i,Sign=0,SignExp=0,Found=0; double z=1;INT32 ky;
  if(x==0||x==1||y==1)return(x);if(y==0)return(1); ky=y; 
  if(x<0){x=-x; if(y==ky && (ky&1)==1)Sign=1;};
  if(y==ky)
  {
    if(ky<0){SignExp=1;ky=-ky;}
    if(x==10)
    {z=UG_LdyExp10INT(ky);Found=1;}
    else if(x==EXP)
    {z=UG_LdyExpINT(ky);Found=1;}
    else if(ky<10)
    {for(i=0;i<ky;i++)z*=x;Found=1;}
    if(Found){if(SignExp) z=1/z;if(Sign)z=-z; return(z);}
  }
  z=UG_LdyExp(y*UG_LdyLog(x)); if(Sign)z=-z;
  return(z);
}
#endif
//------------------------------------------------------------------------------------------------------------------------------
