#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef null
#define null    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef false
#define false   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef true
#define true    (1)
#endif

typedef unsigned char BYTE;
typedef unsigned char byte;
typedef unsigned short WORD;
typedef unsigned short word;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;
typedef unsigned long longword;	// Unsigned 32 bit

typedef union {
	WORD W;
	struct {
		BYTE L;
		BYTE H;
	} WB;
} WORD_BYTE;

typedef signed char        s8;
typedef unsigned char      u8;
typedef signed short       s16;
typedef unsigned short     u16;
typedef signed int         s32;
typedef unsigned int       u32;
typedef signed long long   s64;
typedef unsigned long long u64;

typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;

#ifndef __RTL_EXT__
//#define __RTL_EXT__
typedef signed char        S8;
typedef unsigned char      U8;
typedef signed short       S16;
typedef unsigned short     U16;
typedef signed int         S32;
typedef unsigned int       U32;
typedef signed long long   S64;
typedef unsigned long long U64;
typedef unsigned char      BIT;
typedef unsigned int       BOOL;
#endif

#endif  /* __TYPE_H__ */
