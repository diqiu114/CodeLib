/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-07-15
 * 
 * @brief RN8302b 寄存器定义
 * 
 * ***********************************************************
 */

#ifndef _RN8302B_REG_H_
#define _RN8302B_REG_H_

// bank 0 参数寄存器区
#define UAWAV 0x0000
#define UBWAV 0x0001
#define UCWAV 0x0002

#define IAWAV 0x0003
#define IBWAV 0x0004
#define ICWAV 0x0005
#define INWAV 0x0006

// 三相电压有效值
#define UA 0x0007
#define UB 0x0008
#define UC 0x0009
#define USUM 0x000A

// 三相电流有效值
#define IA 0x000B
#define IB 0x000C
#define IC 0x000D
#define IN 0x000E
#define ISUM 0x0010

#define IA_NVM1 0x0011
#define IB_NVM1 0x0012
#define IC_NVM1 0x0013

// 三相有功功率
#define PA 0x0014
#define PB 0x0015
#define PC 0x0016
#define PT 0x0017

// 三相无功功率
#define QA 0x0018
#define QB 0x0019
#define QC 0x001A
#define QT 0x001B

// 三相视在功率
#define SA 0x001C
#define SB 0x001D
#define SC 0x001E
#define STA 0x001F

#define PfA 0x0020
#define PfB 0x0021
#define PfC 0x0022
#define PfTA 0x0023

#define PAFCnt 0x0024
#define PBFCnt 0x0025
#define PCFCnt 0x0026
#define PTFCnt 0x0027

#define QAFCnt 0x0028
#define QBFCnt 0x0029
#define QCFCnt 0x002A
#define QTFCnt 0x002B

#define SAFCnt 0x002C
#define SBFCnt 0x002D
#define SCFCnt 0x002E
#define STFACnt 0x002F

// 三相有功能量寄存器
#define EPA 0x0030
#define EPB 0x0031
#define EPC 0x0032
#define EPT 0x0033

#define PosEPA 0x0034
#define PosEPB 0x0035
#define PosEPC 0x0036
#define PosEPT 0x0037

#define NegEPA 0x0038
#define NegEPB 0x0039
#define NegEPC 0x003A
#define NegEPT 0x003B

#define EQA 0x003C
#define EQB 0x003D
#define EQC 0x003E
#define EQT 0x003F

#define PosEQA 0x0040
#define PosEQB 0x0041
#define PosEQC 0x0042
#define PosEQT 0x0043

#define NegEQA 0x0044
#define NegEQB 0x0045
#define NegEQC 0x0046
#define NegEQT 0x0047

#define ESA 0x0048
#define ESB 0x0049
#define ESC 0x004A
#define ESTA 0x004B

#define STV 0x004C
#define PfTV 0x004D
#define STFVCnt 0x004E
#define ESTV 0x004F

#define YUA 0x0050
#define YUB 0x0051
#define YUC 0x0052

#define YIA 0x0053
#define YIB 0x0054
#define YIC 0x0055
#define YIN 0x0056

// 电压线频率
#define UFreq 0x0057

#define FUA 0x0058
#define FUB 0x0059
#define FUC 0x005A

#define FIA 0x005B
#define FIB 0x005C
#define FIC 0x005D

#define FPA 0x005E
#define FPB 0x005F
#define FPC 0x0060
#define FPT 0x0061

#define FQA 0x0062
#define FQB 0x0063
#define FQC 0x0064
#define FQT 0x0065

#define FSA 0x0066
#define FSB 0x0067
#define FSC 0x0068
#define FSTA 0x0069

#define FPfA 0x006A
#define FPfB 0x006B
#define FPfC 0x006C
#define FPfTA 0x006D

#define FPAFCnt 0x006E
#define FPBFCnt 0x006F
#define FPCFCnt 0x0070
#define FPTFCnt 0x0071

#define FQAFCnt 0x0072
#define FQBFCnt 0x0073
#define FQCFCnt 0x0074
#define FQTFCnt 0x0075

#define FSAFCnt 0x0076
#define FSBFCnt 0x0077
#define FSCFCnt 0x0078
#define FSTAFCnt 0x0079

#define FEPA 0x007A
#define FEPB 0x007C
#define FEPC 0x007B
#define FEPT 0x007D

#define PosFEPA 0x007E
#define PosFEPB 0x007F
#define PosFEPC 0x0080
#define PosFEPT 0x0081

#define NegFEPA 0x0082
#define NegFEPB 0x0083
#define NegFEPC 0x0084
#define NegFEPT 0x0085

#define FEQA 0x0086
#define FEQB 0x0087
#define FEQC 0x0088
#define FEQT 0x0089

#define PosFEQA 0x008A
#define PosFEQB 0x008B
#define PosFEQC 0x008C
#define PosFEQT 0x008D

#define NegFEQA 0x008E
#define NegFEQB 0x008F
#define NegFEQC 0x0090
#define NegFEQT 0x0091

#define FESA 0x0092
#define FESB 0x0093
#define FESC 0x0094
#define FESTA 0x0095

#define HUA 0x0096
#define HUB 0x0097
#define HUC 0x0098

#define HIA 0x0099
#define HIB 0x009A
#define HIC 0x009B

#define FSTV 0x009C
#define FPfTV 0x009D
#define FSTVFcnt 0x009E
#define FESTV 0x009F

// bank 1 配置和状态寄存器
// 高频脉冲读数寄存器
#define HFCONST1 0x0100
#define HFCONST2 0x0101

// 有功视在启动电流阈值寄存器
#define IStart_PS 0x0102
// 无功启动电流阈值寄存器
#define IStart_Q 0x0103
// 失压阈值寄存器
#define LostVoltT 0x0104
// 过零阈值寄存器
#define ZXOT 0x0105

// 相位分段校正电流阈值
#define PRTH1L 0x0106
#define PRTH1H 0x0107
#define PRTH2L 0x0108
#define PRTH2H 0x0109

// 电流阈值3上下限
#define IRegion3L 0x010A
#define IRegion3H 0x010B

// 三相采样通道电压、电流相位校正寄存器
#define PHSUA 0x010C
#define PHSUB 0x010D
#define PHSUC 0x010E
#define PHSIA 0x010F
#define PHSIB 0x0110
#define PHSIC 0x0111
#define PHSIN 0x0112

// 三相采样通道电压增益
#define GSUA 0x0113
#define GSUB 0x0114
#define GSUC 0x0115

// 三相采样通道电流增益
#define GSIA 0x0116
#define GSIB 0x0117
#define GSIC 0x0118
#define GSIN 0x0119

// 三相采样通道电压直流OFFSET校正
#define DCOS_UA 0x011A
#define DCOS_UB 0x011B
#define DCOS_UC 0x011C

// 三相采样通道电流直流OFFSET校正
#define DCOS_IA 0x011D
#define DCOS_IB 0x011E
#define DCOS_IC 0x011F
#define DCOS_IN 0x0120

// 三相电压有效值OFFSET
#define UA_OS 0x0121
#define UB_OS 0x0122
#define UC_OS 0x0123

// 三相电流有效值OFFSET
#define IA_OS 0x0124
#define IB_OS 0x0125
#define IC_OS 0x0126
#define IN_OS 0x0127

// 三相有功功率增益
#define GPA 0x0128
#define GPB 0x0129
#define GPC 0x012A

// 三相无功功率增益
#define GQA 0x012B
#define GQB 0x012C
#define GQC 0x012D

// 三相视在功率增益
#define GSA 0x012E
#define GSB 0x012F
#define GSC 0x0130

// 三相有功分段相位校正寄存器
#define PA_PHSL 0x0131
#define PB_PHSL 0x0132
#define PC_PHSL 0x0133

// 三相无功分段相位校正寄存器
#define QA_PHSL 0x0134
#define QB_PHSL 0x0135
#define QC_PHSL 0x0136

// 三相有功功率 Offset
#define PA_OS 0x0137
#define PB_OS 0x0138
#define PC_OS 0x0139

// 三相无功功率 Offset
#define QA_OS 0x013A
#define QB_OS 0x013B
#define QC_OS 0x013C

#define FUA_OS 0x013D
#define FUB_OS 0x013E
#define FUC_OS 0x013F

#define FIA_OS 0x0140
#define FIB_OS 0x0141
#define FIC_OS 0x0142

#define GFPA 0x0143
#define GFPB 0x0144
#define GFPC 0x0145

#define GFQA 0x0146
#define GFQB 0x0147
#define GFQC 0x0148

#define GFSA 0x0149
#define GFSB 0x014A
#define GFSC 0x014B

#define FPA_PHS 0x014C
#define FPB_PHS 0x014D
#define FPC_PHS 0x014E

#define FQA_PHS 0x014F
#define FQB_PHS 0x0150
#define FQC_PHS 0x0151

#define FPA_OS 0x0152
#define FPB_OS 0x0153
#define FPC_OS 0x0154

#define FQA_OS 0x0155
#define FQB_OS 0x0156
#define FQC_OS 0x0157

#define SAGCFG 0x0158
#define OVLVL 0x0159
#define OILVL 0x015A

//EMM 配置和状态寄存器
#define CFCFG 0x0160
#define EMUCFG 0x0161
#define EMUCON 0x0162
#define WSAVECON 0x0163
#define EMMIE 0x0164
#define EMMIF 0x0165
#define PQSign 0x0166
#define Noload 0x0167
#define IRegionS 0x0168
#define PHASES 0x0169
// EMM校表和状态寄存器
#define CheckSum1 0x016A

#define NVM1CFG 0x0170
#define NVM1IF 0x0171

#define NVM2CFG 0x0172
#define NVM2CMPA 0x0173
#define NVM2CMPB 0x0174
#define NVM2CMPC 0x0175
#define NVM2IF 0x0176

// 系统配置寄存器
// 写使能
#define WREN 0x0180
// 工作模式切换
#define WMSW 0x0181
// 软件复位
#define SOFTRST 0x0182
// ADC配置
#define ADCCFG 0x0183
// 三相三线/四线切换
#define MODSEL 0x0186

// 系统状态寄存器
#define SYSSR 0x018A
#define CheckSum2 0x018B
// 上一次SPI读出数据
#define RData 0x018C
// 上一次SPI写入数据
#define WData 0x018D
#define LRBufAddr 0x018E
// 设备ID
#define DeviceID 0x018F

// EMM校表寄存器 2
#define ZXOTU 0x0190
#define AUOTDC_EN 0x0191
#define ZXOTCFG 0x0192
#define IN_WaveEN 0x0194
#define PA_PHSM 0x01B0
#define PA_PHSH 0x01B1
#define PB_PHSM 0x01B2
#define PB_PHSH 0x01B3
#define PC_PHSM 0x01B4
#define PC_PHSH 0x01B5
#define QA_PHSM 0x01B6
#define QA_PHSH 0x01B7
#define QB_PHSM 0x01B8
#define QB_PHSH 0x01B9
#define QC_PHSM 0x01BA
#define QC_PHSH 0x01BB

#endif // _RN8302B_REG_H_
