// commRes.c common resource file
#include "commRes.h"

//#define RESOURCE_IN_NORFLASH


#ifdef RESOURCE_IN_NORFLASH
#define Courier12_data 0x8004fd58 
#define LogoStream 0x80051d58 
#define gc_CursorData 0x80051958 
#else
extern const uint8_t Courier12_data[];
extern const unsigned long LogoStream[];
extern const unsigned char gc_CursorData[(CURSOR_H_SIZE/4)*CURSOR_H_SIZE];
#endif

const FontType_t Courier12 = {
	"Courier (12pt,Bold)",
	11, 16, 0x20, 0xFF,
	(const uint8_t*)Courier12_data
};

Cursor_t gc_Cursor = 
{
	64, 64,
	(void*)gc_CursorData
};

Bmp_t LogoPic =
{
	"Logos picture",
	480, 272, 24, 4,
	(void*)LogoStream,
	NULL
};
