//==============================================================================================================================
#ifndef Common_V01_H
#define Common_V01_H
//==============================================================================================================================
#define PAI                     3.1415926535897932
#define EXP                     2.71828182845905
#define NULL                    0
//------------------------------------------------------------------------------------------------------------------------------
#define ARG_N(...)  ARG_N_(0, ##__VA_ARGS__, ARG_N_RESQ())//求参数个数
#define ARG_N_(...) ARG_N_M(__VA_ARGS__)
#define ARG_N_M( \
          _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N

#define ARG_N_RESQ() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0
//------------------------------------------------------------------------------------------------------------------------------
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
  #define __ARMCLIB_VERSION 5060044
  #ifndef __cplusplus //In C++, 'bool', 'true' and 'false' and keywords
    #define bool _Bool
    #define true 1
    #define false 0
  #else
    #ifdef __GNUC__
      //GNU C++ supports direct inclusion of stdbool.h to provide C99 compatibility by defining _Bool
      #define _Bool bool
    #endif
  #endif
#endif

#ifdef __clang__
  typedef __builtin_va_list va_list;
  #define va_start(ap, param) __builtin_va_start(ap, param)
  #define va_end(ap)          __builtin_va_end(ap)
  #define va_arg(ap, type)    __builtin_va_arg(ap, type)
  #if __STDC_VERSION__ >= 199900L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
  #define va_copy(dest, src)  __builtin_va_copy(dest, src)
  #endif
#else
  #ifdef __TARGET_ARCH_AARCH64
    typedef struct __va_list {
      void *__stack;
      void *__gr_top;
      void *__vr_top;
      int __gr_offs;
      int __vr_offs;
    } va_list;
  #else
    typedef struct __va_list { void *__ap; } va_list;
  #endif

  #define va_start(ap, parmN) __va_start(ap, parmN)

  #define va_arg(ap, type) __va_arg(ap, type)

  #define __va_copy(dest, src) ((void)((dest) = (src)))

  #if !defined(__STRICT_ANSI__) || (defined(__STDC_VERSION__) && 199901L <= __STDC_VERSION__) || (defined(__cplusplus) && 201103L <= __cplusplus)
    #define va_copy(dest, src) ((void)((dest) = (src)))
  #endif

  #define va_end(ap) __va_end(ap)
#endif     
//------------------------------------------------------------------------------------------------------------------------------
/*
#ifdef __cplusplus
  #define     __I     volatile                //defines 'read only' permissions
#else
  #define     __I     volatile const          //defines 'read only' permissions
#endif
#define     __O     volatile                  //defines 'write only' permissions
#define     __IO    volatile                  //defines 'read / write' permissions
*/
//------------------------------------------------------------------------------------------------------------------------------
typedef enum {FALSE = 0, TRUE = !FALSE} BOOL;

typedef float                   FLOAT32;
typedef double                  FLOAT64;//=long double
typedef signed char             INT8;
typedef signed short            INT16;//in 8bit MCU=signed int
typedef signed long             INT32;//in 32bit MCU=signed int
typedef signed long long        INT64;
typedef unsigned char           UINT8;
typedef unsigned short          UINT16;//in 8bit MCU=unsigned int
typedef unsigned long           UINT32;//in 32bit MCU=unsigned int
typedef unsigned long long      UINT64;
typedef void (*Function)(void);
//------------------------------------------------------------------------------------------------------------------------------
#define UCHAR           UINT8
//#define UINT            UINT16
#define ULONG           UINT32
#define ULONGLONG       UINT64
#define LONGLONG        INT64

#define int8            INT8
#define int16           INT16
#define int32           INT32
#define int64           INT64

#define uint8           UINT8
#define uint16          UINT16
#define uint32          UINT32
#define uint64          UINT64

#define int8_t          INT8
#define int16_t         INT16
#define int32_t         INT32
#define int64_t         INT64

#define uint8_t         uint8
#define uint16_t        uint16
#define uint32_t        uint32
#define uint64_t        uint64

typedef unsigned int    size_t;
typedef unsigned char	  BYTE;
//These types MUST be 16 bit
typedef short			      SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;
/* These types MUST be 16 bit or 32 bit */
typedef unsigned int	  UINT;
//These types MUST be 32 bit
typedef long			      LONG;
typedef unsigned long	  DWORD;
//------------------------------------------------------------------------------------------------------------------------------
#define FLOAT_MIN   0xFFFFFFFF
#define FLOAT_MAX   0x7FFFFFFF
#define DOUBLE_MIN  0xFFFFFFFFFFFFFFFF
#define DOUBLE_MAX  0x7FFFFFFFFFFFFFFF
//------------------------------------------------------------------------------------------------------------------------------
//minimum values of exact-width signed integer types
#define INT8_MIN                   -128
#define INT16_MIN                -32768
#define INT32_MIN          (~0x7fffffff)//-2147483648 is unsigned
#define INT64_MIN  __INT64_C(~0x7fffffffffffffff)//-9223372036854775808 is unsigned

//maximum values of exact-width signed integer types
#define INT8_MAX                    127
#define INT16_MAX                 32767
#define INT32_MAX            2147483647
#define INT64_MAX  __INT64_C(9223372036854775807)

//maximum values of exact-width unsigned integer types
#define UINT8_MAX                   255
#define UINT16_MAX                65535
#define UINT32_MAX           4294967295u
#define UINT64_MAX __UINT64_C(18446744073709551615)

//7.18.2.2
//minimum values of minimum-width signed integer types
#define INT_LEAST8_MIN                   -128
#define INT_LEAST16_MIN                -32768
#define INT_LEAST32_MIN          (~0x7fffffff)
#define INT_LEAST64_MIN  __INT64_C(~0x7fffffffffffffff)

//maximum values of minimum-width signed integer types
#define INT_LEAST8_MAX                    127
#define INT_LEAST16_MAX                 32767
#define INT_LEAST32_MAX            2147483647
#define INT_LEAST64_MAX  __INT64_C(9223372036854775807)

//maximum values of minimum-width unsigned integer types
#define UINT_LEAST8_MAX                   255
#define UINT_LEAST16_MAX                65535
#define UINT_LEAST32_MAX           4294967295u
#define UINT_LEAST64_MAX __UINT64_C(18446744073709551615)

//7.18.2.3
//minimum values of fastest minimum-width signed integer types
#define INT_FAST8_MIN           (~0x7fffffff)
#define INT_FAST16_MIN          (~0x7fffffff)
#define INT_FAST32_MIN          (~0x7fffffff)
#define INT_FAST64_MIN  __INT64_C(~0x7fffffffffffffff)

//maximum values of fastest minimum-width signed integer types
#define INT_FAST8_MAX             2147483647
#define INT_FAST16_MAX            2147483647
#define INT_FAST32_MAX            2147483647
#define INT_FAST64_MAX  __INT64_C(9223372036854775807)

//maximum values of fastest minimum-width unsigned integer types
#define UINT_FAST8_MAX            4294967295u
#define UINT_FAST16_MAX           4294967295u
#define UINT_FAST32_MAX           4294967295u
#define UINT_FAST64_MAX __UINT64_C(18446744073709551615)

//7.18.2.4
//minimum value of pointer-holding signed integer type
#if __sizeof_ptr == 8
#define INTPTR_MIN INT64_MIN
#else
#define INTPTR_MIN INT32_MIN
#endif

//maximum value of pointer-holding signed integer type
#if __sizeof_ptr == 8
#define INTPTR_MAX INT64_MAX
#else
#define INTPTR_MAX INT32_MAX
#endif

//maximum value of pointer-holding unsigned integer type
#if __sizeof_ptr == 8
#define UINTPTR_MAX UINT64_MAX
#else
#define UINTPTR_MAX UINT32_MAX
#endif

//7.18.2.5
//minimum value of greatest-width signed integer type
#define INTMAX_MIN  __ESCAPE__(~0x7fffffffffffffffll)

//maximum value of greatest-width signed integer type
#define INTMAX_MAX  __ESCAPE__(9223372036854775807ll)

//maximum value of greatest-width unsigned integer type
#define UINTMAX_MAX __ESCAPE__(18446744073709551615ull)

//7.18.3
//limits of ptrdiff_t
#if __sizeof_ptr == 8
#define PTRDIFF_MIN INT64_MIN
#define PTRDIFF_MAX INT64_MAX
#else
#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX
#endif

//limits of sig_atomic_t
#define SIG_ATOMIC_MIN (~0x7fffffff)
#define SIG_ATOMIC_MAX   2147483647

//limit of size_t
#if __sizeof_ptr == 8
#define SIZE_MAX UINT64_MAX
#else
#define SIZE_MAX UINT32_MAX
#endif

//limits of wchar_t, NB we have to undef and redef because they're defined in both stdint.h and wchar.h
#undef WCHAR_MIN
#undef WCHAR_MAX

#if defined(__WCHAR32) || (defined(__ARM_SIZEOF_WCHAR_T) && __ARM_SIZEOF_WCHAR_T == 4)
  #define WCHAR_MIN   0
  #define WCHAR_MAX   0xffffffffU
#else
  #define WCHAR_MIN   0
  #define WCHAR_MAX   65535
#endif

//limits of wint_t
#define WINT_MIN (~0x7fffffff)
#define WINT_MAX 2147483647
//------------------------------------------------------------------------------------------------------------------------------
#define __AT(Address)       __attribute__((at(Address)))
#define __INLINE            __inline
#define __STATIC_INLINE     static __inline
#define __ASM               __asm
#define __UNUSED            __attribute__((unused))
#define __BKPT(value)                    __breakpoint(value)
#define __BreakPoint(value)              __breakpoint(value)
#define __WEAK              __attribute__((weak))
#define __ALIGN(n)          __align(n)
#define __PACKED            __packed
//------------------------------------------------------------------------------------------------------------------------------
#if defined ( __CC_ARM   )
    #pragma anon_unions//enable no name for struct and union
#endif
#define offsetof(t, memb) ((size_t)(&(((t *)0)->memb)))
//屏蔽编译消息,在OPTION的C/C++的misc control中写入:--diag_suppress=177 （多个之间用","隔开)
//------------------------------------------------------------------------------------------------------------------------------
typedef union UINT32_BIT1_BIT
{
  struct
  {
    UINT32 V:1;         //00,
    UINT32 rsvd0:31;    //01,
  };
  struct
  {
    UINT32 B0:1;        //00,
  };
}Type_UINT32_BIT1,UINT32_BIT1_Type;
typedef union UINT32_BIT2_BIT
{
  struct
  {
    UINT32 V:2;         //00,
    UINT32 rsvd0:30;    //02,
  };
  struct
  {
    UINT32 B0:1;        //00,
    UINT32 B1:1;        //01,
  };
}Type_UINT32_BIT2,UINT32_BIT2_Type;

typedef union UINT32_BIT3_BIT
{
	struct
	{		
    UINT32 V:3;           //00,
    UINT32 Reserved0:29;  //03,
	};
	struct
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
	};
}Type_UINT32_BIT3,UINT32_BIT3_Type;

typedef union UINT32_BIT4_BIT
{
	struct
	{
    UINT32 V:4;           //00,
    UINT32 Reserved0:28;  //04,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
	};
}Type_UINT32_BIT4,UINT32_BIT4_Type;

typedef union UINT32_BIT5_BIT
{
	struct
	{
    UINT32 V:5;           //00,
    UINT32 Reserved0:27;  //05,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
	};
}Type_UINT32_BIT5,UINT32_BIT5_Type;

typedef union UINT32_BIT6_BIT
{
	struct
	{
    UINT32 V:6;           //00,
    UINT32 Reserved0:26;  //06,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
	};
}Type_UINT32_BIT6,UINT32_BIT6_Type;

typedef union UINT32_BIT7_BIT
{
	struct
	{
    UINT32 V:7;           //00,
    UINT32 Reserved0:25;  //07,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
	};
}Type_UINT32_BIT7,UINT32_BIT7_Type;

typedef union UINT32_BIT8_BIT
{
	struct
	{
    UINT32 V:8;           //00,
    UINT32 Reserved0:24;  //08,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
	};
}Type_UINT32_BIT8,UINT32_BIT8_Type;

typedef union UINT32_BIT9_BIT
{
	struct
	{
    UINT32 V:9;           //00,
    UINT32 Reserved0:23;  //09,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
	};
}Type_UINT32_BIT9,UINT32_BIT9_Type;

typedef union UINT32_BIT10_BIT
{
	struct
	{
    UINT32 V:10;          //00,
    UINT32 Reserved0:22;  //10,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
	};
}Type_UINT32_BIT10,UINT32_BIT10_Type;

typedef union UINT32_BIT11_BIT
{
	struct
	{
    UINT32 V:11;        //00,
    UINT32 Reserved0:21;//11,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
	};
}Type_UINT32_BIT11,UINT32_BIT11_Type;

typedef union UINT32_BIT12_BIT
{
	struct
	{
    UINT32 V:12;          //00,
    UINT32 Reserved0:20;  //12,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
	};
}Type_UINT32_BIT12,UINT32_BIT12_Type;

typedef union UINT32_BIT13_BIT
{
	struct
	{
    UINT32 V:13;          //00,
    UINT32 Reserved0:19;  //13,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
	};
}Type_UINT32_BIT13,UINT32_BIT13_Type;

typedef union UINT32_BIT14_BIT
{
	struct
	{
    UINT32 V:14;          //00,
    UINT32 Reserved0:18;  //14,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
	};
}Type_UINT32_BIT14,UINT32_BIT14_Type;

typedef union UINT32_BIT15_BIT
{
	struct
	{
    UINT32 V:15;          //00,
    UINT32 Reserved0:17;  //15,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
	};
}Type_UINT32_BIT15,UINT32_BIT15_Type;

typedef union UINT32_BIT16_BIT
{
	struct
	{
    UINT32 V:16;          //00,
    UINT32 Reserved0:16;  //16,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
	};
}Type_UINT32_BIT16,UINT32_BIT16_Type;

typedef union UINT32_BIT17_BIT
{
	struct
	{
    UINT32 V:17;        //00,
    UINT32 Reserved0:15;//17,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
	};
}Type_UINT32_BIT17,UINT32_BIT17_Type;

typedef union UINT32_BIT18_BIT
{
	struct
	{
    UINT32 V:18;        //00,
    UINT32 Reserved0:14;//18,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
	};
}Type_UINT32_BIT18,UINT32_BIT18_Type;

typedef union UINT32_BIT19_BIT
{
	struct
	{
    UINT32 V:19;        //00,
    UINT32 Reserved0:13;//19,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
	};
}Type_UINT32_BIT19,UINT32_BIT19_Type;

typedef union UINT32_BIT20_BIT
{
	struct
	{
    UINT32 V:20;          //00,
    UINT32 Reserved0:12;  //20,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
		UINT32 B19:1;
	};	
}Type_UINT32_BIT20,UINT32_BIT20_Type;
typedef union UINT32_BIT21_BIT
{
	struct
	{
    UINT32 V:21;          //00,
    UINT32 Reserved0:11;  //21,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
		UINT32 B19:1;
		UINT32 B20:1;
	};		
}Type_UINT32_BIT21,UINT32_BIT21_Type;

typedef union UINT32_BIT22_BIT
{
	struct
	{
    UINT32 V:22;          //00,
    UINT32 Reserved0:10;  //22,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
		UINT32 B19:1;
		UINT32 B20:1;
		UINT32 B21:1;
	};		
}Type_UINT32_BIT22,UINT32_BIT22_Type;

typedef union UINT32_BIT23_BIT
{
	struct
	{
    UINT32 V:23;          //00,
    UINT32 Reserved0:9;   //23,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
		UINT32 B19:1;
		UINT32 B20:1;
		UINT32 B21:1;
		UINT32 B22:1;
	};		
}Type_UINT32_BIT23,UINT32_BIT23_Type;

typedef union UINT32_BIT24_BIT
{
	struct
	{
    UINT32 V:24;          //00,
    UINT32 Reserved0:8;   //24,
	};
	struct 
	{
		UINT32 B0:1;
		UINT32 B1:1;
		UINT32 B2:1;
		UINT32 B3:1;
		UINT32 B4:1;
		UINT32 B5:1;
		UINT32 B6:1;
		UINT32 B7:1;
		UINT32 B8:1;
		UINT32 B9:1;
		UINT32 B10:1;
		UINT32 B11:1;
		UINT32 B12:1;
		UINT32 B13:1;
		UINT32 B14:1;
		UINT32 B15:1;
		UINT32 B16:1;
		UINT32 B17:1;
		UINT32 B18:1;
		UINT32 B19:1;
		UINT32 B20:1;
		UINT32 B21:1;
		UINT32 B22:1;
		UINT32 B23:1;
	};		
}Type_UINT32_BIT24,UINT32_BIT24_Type;
//------------------------------------------------------------------------------------------------------------------------------
struct COMP_INT16
{
  INT16 r;
  INT16 i;
};
struct COMP_INT32
{
  INT32 r;
  INT32 i;
};
struct COMP_FLOAT32
{
  FLOAT32 r;
  FLOAT32 i;
};
//------------------------------------------------------------------------------------------------------------------------------
typedef struct UINT8_BIT
{
   UINT8 B0:1;
   UINT8 B1:1;
   UINT8 B2:1;
   UINT8 B3:1;
   UINT8 B4:1;
   UINT8 B5:1;
   UINT8 B6:1;
   UINT8 B7:1;
}Type_BIT8,BIT8_Type;
union UINT8_REG 
{
   UINT8             VAL;
   struct UINT8_BIT  BIT;
}; 
//------------------------------------------------------------------------------------------------------------------------------
typedef struct UINT16_BIT
{
  UINT16 B0:1;
  UINT16 B1:1;
  UINT16 B2:1;
  UINT16 B3:1;
  UINT16 B4:1;
  UINT16 B5:1;
  UINT16 B6:1;
  UINT16 B7:1;
  UINT16 B8:1;
  UINT16 B9:1;
  UINT16 B10:1;
  UINT16 B11:1;
  UINT16 B12:1;
  UINT16 B13:1;
  UINT16 B14:1;
  UINT16 B15:1;
}BIT16_Type,Type_BIT16;
struct UINT16_B2_BIT
{
  UINT16 B0_1   :2;
  UINT16 B2_3   :2;
  UINT16 B4_5   :2;
  UINT16 B6_7   :2;
  UINT16 B8_9   :2;
  UINT16 B10_11 :2;
  UINT16 B12_13 :2;
  UINT16 B14_15 :2;
};

struct UINT16_B2P_BIT
{
  UINT16 P0   :2;//bit0_1
  UINT16 P1   :2;//bit2_3
  UINT16 P2   :2;
  UINT16 P3   :2;
  UINT16 P4   :2;
  UINT16 P5   :2;
  UINT16 P6   :2;
  UINT16 P7   :2;
};
struct UINT16_B4_BIT
{
  UINT16 B0_3   :4;
  UINT16 B4_7   :4;
  UINT16 B8_11  :4;
  UINT16 B12_15 :4;
};
struct UINT16_B4P_BIT
{
  UINT16 P0   :4;
  UINT16 P1   :4;
  UINT16 P2   :4;
  UINT16 P3   :4;
};

struct UINT16_BYTE
{
  UINT8 BT0:8;
  UINT8 BT1:8;
};
struct UINT16_LH
{
  UINT8 L:8;
  UINT8 H:8;
};

typedef union UINT16_REG
{
  UINT16                 VAL;
	UINT8                  B[2];
  struct UINT16_BIT      BIT;
	struct UINT16_B2_BIT   B2;
	struct UINT16_B4_BIT   B4;
  struct UINT16_B2P_BIT  B2P;
  struct UINT16_B4P_BIT  B4P;
  struct UINT16_BYTE     Bytes;
  struct UINT16_LH       LH;
}Type_UINT16;   
//------------------------------------------------------------------------------------------------------------------------------
typedef struct UINT32_BIT
{
  UINT32 B0  :1;
  UINT32 B1  :1;
  UINT32 B2  :1;
  UINT32 B3  :1;
  UINT32 B4  :1;
  UINT32 B5  :1;
  UINT32 B6  :1;
  UINT32 B7  :1;
  UINT32 B8  :1;
  UINT32 B9  :1;
  UINT32 B10 :1;
  UINT32 B11 :1;
  UINT32 B12 :1;
  UINT32 B13 :1;
  UINT32 B14 :1;
  UINT32 B15 :1;
  UINT32 B16 :1;
  UINT32 B17 :1;
  UINT32 B18 :1;
  UINT32 B19 :1;
  UINT32 B20 :1;
  UINT32 B21 :1;
  UINT32 B22 :1;
  UINT32 B23 :1;
  UINT32 B24 :1;
  UINT32 B25 :1;
  UINT32 B26 :1;
  UINT32 B27 :1;
  UINT32 B28 :1;
  UINT32 B29 :1;
  UINT32 B30 :1;
  UINT32 B31 :1;
} UINT32_BIT_Type,Type_UINT32_BIT,BIT32_Type,Type_BIT32;
typedef struct UINT32_B2_BIT
{
  UINT32 B0_1   :2;
  UINT32 B2_3   :2;
  UINT32 B4_5   :2;
  UINT32 B6_7   :2;
  UINT32 B8_9   :2;
  UINT32 B10_11 :2;
  UINT32 B12_13 :2;
  UINT32 B14_15 :2;
  UINT32 B16_17 :2;
  UINT32 B18_19 :2;
  UINT32 B20_21 :2;
  UINT32 B22_23 :2;
  UINT32 B24_25 :2;
  UINT32 B26_27 :2;
  UINT32 B28_29 :2;
  UINT32 B30_31 :2;
} UINT32_B2_Type,Type_UINT32_B2;
typedef struct UINT32_B2P_BIT
{
  UINT32 P0  :2;
  UINT32 P1  :2;
  UINT32 P2  :2;
  UINT32 P3  :2;
  UINT32 P4  :2;
  UINT32 P5  :2;
  UINT32 P6  :2;
  UINT32 P7  :2;
  UINT32 P8  :2;
  UINT32 P9  :2;
  UINT32 P10 :2;
  UINT32 P11 :2;
  UINT32 P12 :2;
  UINT32 P13 :2;
  UINT32 P14 :2;
  UINT32 P15 :2;
} UINT32_B2P_Type,Type_UINT32_B2P;
typedef struct UINT32_B3_BIT
{
  UINT32 B0_2   :3;
  UINT32 B3_5   :3;
  UINT32 B6_8   :3;
  UINT32 B9_11  :3;
  UINT32 B12_14 :3;
  UINT32 B15_17 :3;
  UINT32 B18_20 :3;
  UINT32 B21_23 :3;
  UINT32 B24_26 :3;
  UINT32 B27_29 :3;
  UINT32 Reserved0 :2;
} UINT32_B3_Type,Type_UINT32_B3;
typedef struct UINT32_B3P_BIT
{
  UINT32 P0  :3;
  UINT32 P1  :3;
  UINT32 P2  :3;
  UINT32 P3  :3;
  UINT32 P4  :3;
  UINT32 P5  :3;
  UINT32 P6  :3;
  UINT32 P7  :3;
  UINT32 P8  :3;
  UINT32 P9  :3;
  UINT32 Reserved0 :2;
} UINT32_B3P_Type,Type_UINT32_B3P;
typedef struct UINT32_B4_BIT
{
  UINT32 B0_3   :4;
  UINT32 B4_7   :4;
  UINT32 B8_11  :4;
  UINT32 B12_15 :4;
  UINT32 B16_19 :4;
  UINT32 B20_23 :4;
  UINT32 B24_27 :4;
  UINT32 B28_31 :4;
} UINT32_B4_Type,Type_UINT32_B4;
typedef struct UINT32_B4P_BIT
{
  UINT32 P0 :4;
  UINT32 P1 :4;
  UINT32 P2 :4;
  UINT32 P3 :4;
  UINT32 P4 :4;
  UINT32 P5 :4;
  UINT32 P6 :4;
  UINT32 P7 :4;
} UINT32_B4P_Type,Type_UINT32_B4P;
typedef struct UINT32_B5_BIT
{
  UINT32 B0_4   :5;
  UINT32 B5_9   :5;
  UINT32 B10_14 :5;
  UINT32 B15_19 :5;
  UINT32 B20_24 :5;
  UINT32 B25_29 :5;
  UINT32 Reserved0 :2;
} UINT32_B5_Type,Type_UINT32_B5;
typedef struct UINT32_B5P_BIT
{
  UINT32 P0 :5;
  UINT32 P1 :5;
  UINT32 P2 :5;
  UINT32 P3 :5;
  UINT32 P4 :5;
  UINT32 P5 :5;
  UINT32 Reserved0 :2;
} UINT32_B5P_Type,Type_UINT32_B5P;
typedef struct UINT32_B6_BIT
{
  UINT32 B0_5   :6;
  UINT32 B6_11  :6;
  UINT32 B12_17 :6;
  UINT32 B18_23 :6;
  UINT32 B24_29 :6;
  UINT32 Reserved0 :2;
} UINT32_B6_Type,Type_UINT32_B6;
typedef struct UINT32_B6P_BIT
{
  UINT32 P0 :6;
  UINT32 P1 :6;
  UINT32 P2 :6;
  UINT32 P3 :6;
  UINT32 P4 :6;
  UINT32 Reserved0 :2;
} UINT32_B6P_Type,Type_UINT32_B6P;
typedef struct UINT32_B8P_BIT
{
  UINT32 P0:8;
  UINT32 P1:8;
  UINT32 P2:8;
  UINT32 P3:8;
} UINT32_B8P_Type,Type_UINT32_B8P;
typedef struct UINT32_B16P_BIT
{
  UINT16 P0:16;
	UINT16 P1:16;
} UINT32_B16P_Type,Type_UINT32_B16P;
typedef struct UINT32_LH
{
  UINT16 L;
  UINT16 H;
} UINT32_LH_Type,Type_UINT32_LH;

typedef union UINT32_REG 
{
  UINT32                 VAL;
	UINT16                 W[2];
	UINT8                  B[4];
  struct UINT32_BIT      BIT;
	struct UINT32_B2_BIT   B2;
	struct UINT32_B4_BIT   B4;
  struct UINT32_B2P_BIT  B2P;
  struct UINT32_B4P_BIT  B4P;
  struct UINT32_B8P_BIT  B8P;
  struct UINT32_B16P_BIT B16P;
  struct UINT32_LH       LH;
}Type_UINT32;   
//------------------------------------------------------------------------------------------------------------------------------
typedef struct UINT64_BIT
{
  UINT64 B0  :1;
  UINT64 B1  :1;
  UINT64 B2  :1;
  UINT64 B3  :1;
  UINT64 B4  :1;
  UINT64 B5  :1;
  UINT64 B6  :1;
  UINT64 B7  :1;
  UINT64 B8  :1;
  UINT64 B9  :1;
  UINT64 B10 :1;
  UINT64 B11 :1;
  UINT64 B12 :1;
  UINT64 B13 :1;
  UINT64 B14 :1;
  UINT64 B15 :1;
  UINT64 B16 :1;
  UINT64 B17 :1;
  UINT64 B18 :1;
  UINT64 B19 :1;
  UINT64 B20 :1;
  UINT64 B21 :1;
  UINT64 B22 :1;
  UINT64 B23 :1;
  UINT64 B24 :1;
  UINT64 B25 :1;
  UINT64 B26 :1;
  UINT64 B27 :1;
  UINT64 B28 :1;
  UINT64 B29 :1;
  UINT64 B30 :1;
  UINT64 B31 :1;
  UINT64 B32  :1;
  UINT64 B33  :1;
  UINT64 B34  :1;
  UINT64 B35  :1;
  UINT64 B36  :1;
  UINT64 B37  :1;
  UINT64 B38  :1;
  UINT64 B39  :1;
  UINT64 B40  :1;
  UINT64 B41  :1;
  UINT64 B42 :1;
  UINT64 B43 :1;
  UINT64 B44 :1;
  UINT64 B45 :1;
  UINT64 B46 :1;
  UINT64 B47 :1;
  UINT64 B48 :1;
  UINT64 B49 :1;
  UINT64 B50 :1;
  UINT64 B51 :1;
  UINT64 B52 :1;
  UINT64 B53 :1;
  UINT64 B54 :1;
  UINT64 B55 :1;
  UINT64 B56 :1;
  UINT64 B57 :1;
  UINT64 B58 :1;
  UINT64 B59 :1;
  UINT64 B60 :1;
  UINT64 B61 :1;
  UINT64 B62 :1;
  UINT64 B63 :1;	
}BIT64_Type,Type_BIT64;
typedef struct UINT64_LH
{
  UINT32 L;
  UINT32 H;
} UINT64_LH_Type,Type_UINT64_LH;

typedef union UINT64_REG
{
	UINT64                 VAL;
	UINT8                  B[8];
	UINT16                 W[4];
  struct UINT64_BIT      BIT;
	struct UINT64_LH       LH;
}Type_UINT64;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Data_Array_UINT8
{
	UINT8  *Item;
	UINT16 Size,Count,Index;
} Type_UINT8_Array;
typedef struct Data_Array_UINT16
{
	UINT16  *Item;
	UINT16 Size,Count,Index;
} Type_UINT16_Array;
typedef struct Data_Array_UINT32
{
	UINT32  *Item;
	UINT16 Size,Count,Index;
} Type_UINT32_Array;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct Data_Array_INT8
{
	INT8  *Item;
	UINT16 Size,Count,Index;
} Type_INT8_Array;
typedef struct Data_Array_INT16
{
	INT16  *Item;
	UINT16 Size,Count,Index;
} Type_INT16_Array;
typedef struct Data_Array_INT32
{
	INT32  *Item;
	UINT16 Size,Count,Index;
} Type_INT32_Array;
//------------------------------------------------------------------------------------------------------------------------------
#define DateTime_Mode_Simple    0//将时间转化成简易字节,不需要相对时间(RSTV_BaseDT)
#define DateTime_Mode_Struct    1//将时间转化成结构字节,不需要相对时间(Data_DateTime)
#define DateTime_Mode_Value     2//将时间转化成数值,需要相对时间（DDEV.BaseDT)

typedef struct DateTime_Second_BIT
{
	UINT16 M:10;//0,毫秒
  UINT16 V:6;//10,秒
}Type_DateTime_Second_BIT;

typedef struct Data_DateTime
{
	INT16  Year;
  UINT8  Month,Day,Hour,Minute;
  union{UINT16 Second;Type_DateTime_Second_BIT Second_BIT;};
} Type_DateTime;
//------------------------------------------------------------------------------------------------------------------------------
#define LdyRandPip              0x05
#define Str_Flag_AddD           0x01//加逗号
#define Str_Flag_AddY           0x02//加引号
#define Str_Flag_AddJ           0x04//加结束
//------------------------------------------------------------------------------------------------------------------------------
#define MAX(a,b)                ((a)>(b) ? (a):(b))
#define MIN(a,b)                ((a)<(b) ? (a):(b))
#define ABS(x)                  (x<0 ? -x:x)
#define DIS(x,y)                (x>=y ? x-y : y-x)
#define INV(x,POS,D)            (x>=POS && x<POS+D)
#define SWAP(x,y,t)             {t=x;x=y;y=t;}
#define LimitMin(V,Min)         {if(V<Min)V=Min;}
#define LimitMax(V,Max)         {if(V>Max)V=Max;}
#define LimitValue(V,Min,Max)   {if(V<Min)V=Min;else if(V>Max)V=Max;}
#define Between(a,b,x)          a+(b-a)*x
//------------------------------------------------------------------------------------------------------------------------------
#define Delay_On                1
#define String_On               1
#define LdyFunc_On              1
#define DateTime_On             1

#define LdySin_On               1
#define SinData_K               16384
#define SinData_Count           (sizeof(SinData)/sizeof(UINT16))
#define SinData_D               (PAI/2/(SinData_Count-2))

#define LdySqrt_On              0
#define SqrtData_K              2048
#define SqrtData_Count          (sizeof(SqrtData)/sizeof(UINT16))
#define SqrtData_D              (100.000/(SqrtData_Count-1))

#define LdyEXPLOG_On            1
//------------------------------------------------------------------------------------------------------------------------------
extern const UINT8 COM_Head_LDY[],COM_Head_LS[],COM_Head_YY[];
extern const double Double_EXPT[],Double_EXPE[];
extern const UINT8 CRLF[];
#if DateTime_On
extern const UINT8 DateTime_MD[];
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if Delay_On
void Delay_US(unsigned int Time);//TimeUnit=us,Delay by instruction
void Delay_MS(unsigned int Time);//TimeUnit=ms,Delay by instruction
void Delay_TimerTime(unsigned int Time);//TimeUnit=ms,Delay by timer
void Delay_Time(unsigned int Time,unsigned char IsStruction);//TimeUnit=ms
#endif

#if String_On
  UINT16 StrLen(UINT8 *s,UINT16 MaxLen);
	UINT8 IsVarChar(UINT8 c,UINT8 IsFirst);
  UINT8 StrCompareChar(UINT8 c1,UINT8 c2,UINT8 Mode);
  UINT8 StrCompare(UINT8 *s1,UINT8 *s2,UINT16 Len,UINT8 Mode);// 0=(s1<s2),1=(s1=s2),2=(s1>s2)
  UINT16 StrReplace(UINT8 *src, UINT16 *srcLen,UINT8 *std,UINT16 stdLen,UINT8 *srp,UINT16 srpLen,UINT8 Mode);
	UINT16 StrReplacePos(UINT8 *src,UINT16 *srcLen,UINT16 stdPos,UINT16 stdLen,UINT8 *srp,UINT16 srpLen);//返回替换次数
  INT16 StrFind(UINT8 *src,UINT16 srcLen, UINT8 *std, UINT16 stdLen,UINT8 Mode);//在src中查找std,found return [0,N-1],nofound return -1
  UINT8 StrFindItem(UINT8 *src, UINT16 srcLen,UINT8 Flag,UINT16 Index,UINT16 *Pos,UINT16 *Len);
	UINT8 StrFindItemStr(UINT8 *src, UINT16 srcLen, UINT8 Flag,UINT8 *std,UINT16 stdLen,UINT16 *stdIndex,UINT8 Mode);//查找s中以Flag隔开的std项
  void StrSet(UINT8 *s,UINT16 Len,UINT8 c);
  void StrCopy(UINT8 *std,UINT8 *src,UINT16 Len);
	UINT8 StrLTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos);
	UINT8 StrRTrim(UINT8 *src,UINT16 srcLen,UINT16 *RPos);
	UINT8 StrTrim(UINT8 *src,UINT16 srcLen,UINT16 *LPos,UINT16 *RPos);
  void StrCat(UINT8 *std,UINT16 *stdLen,UINT8 *src, UINT16 srcLen);
  void StrAddItem(UINT8 *std,UINT16 *stdLen,UINT8 *src,UINT16 srcLen,UINT8 Flag);//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00   
  void StrAddItemNum(UINT8 *std,UINT16 *stdLen,double Num,UINT8 NumPCount,UINT8 Flag);//Flag.bit0=Add ','; Flag.bit1=Add '"' ; Flag.bit2=Add 0x00 
  void ValueToStr(UINT8 *s,UINT64 V,UINT8 Len);
  UINT64 StrToValue(UINT8 *s,UINT8 Len);
	UINT64 ByteToValue(UINT8 *s,UINT8 Len,UINT8 HighToLow);
  void StrAddValue(UINT8 *s,UINT8 sLen,UINT64 V,UINT8 VLen);
  void NumToStr(double Num,UINT8 NumPCount,UINT8 *s,UINT16 *Len);
	double StrToNum(UINT8 *s,UINT16 Len);
#endif

#if DateTime_On
UINT8 IsLeapYear(INT16 Year);
UINT16 YearDay(INT16 Year);
INT32 YearDays(INT16 Year);
INT32 DaysBetweenYear(INT16 Year1, INT16 Year2);
UINT16 DaysBetweenMonth(INT16 Year, UINT8 Month1, UINT8 Month2);
UINT8 MonthDay(INT16 Year, UINT8 Month);
UINT8 YMDToWeek(INT16 Year, UINT8 Month, UINT8 Day);
UINT8 DT_Compare(struct Data_DateTime DT1,struct Data_DateTime DT2);//0=(DT1<DT2),1=(DT1=DT2),2=(DT1>DT2)
UINT32 DTToUINT32(struct Data_DateTime DT);//seconds of (Time-BaseDT)
void UINT32ToDT(UINT32 SV,struct Data_DateTime *DT);//seconds of (Time-BaseDT)
void DTToByte8(struct Data_DateTime DT,UINT8 *B,UINT8 Mode);
void Byte8ToDT(UINT8* B,struct Data_DateTime *DT,UINT8 Mode);
void DTToString(struct Data_DateTime DT,UINT8 *s,UINT16 *sLen,UINT8 Flag);
void DT_RefreshMiniSecond(void);
void DT_Timer(struct Data_DateTime *DT);//every 1s
#endif

#if LdyFunc_On
  unsigned long LdyRand(unsigned long Range);//Return a Number(0<=n<Range)
  double LdyMod(double x,double y);
#endif
#if LdySin_On
  float LdySin(float x);
  float LdyCos(float x);
  float LdyASin(float x);
  float LdyACos(float x);
  float LdyTan(float x);
  float LdyCtg(float x);
  float LdyATan(float x);
  float LdyACtg(float x);
#endif
#if LdySqrt_On
  float LdySqrt(float x);
#endif
#if LdyEXPLOG_On||String_On
double LdyExpINT(int k);
double LdyExp10INT(int k);
#endif
#if LdyEXPLOG_On
double LdyExp(double x);
double LdyExp10(double x);
double LdyLog(double x);
double LdyLog10(double x);
double LdyPow(double x,double y);
#endif
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------
