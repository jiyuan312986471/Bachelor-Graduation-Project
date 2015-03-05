#ifndef __GLCD_H__
#define __GLCD_H__

#include <stdint.h>                      /*!< standard types definitions                      */
#include "typeDef.h"

typedef struct _Point_t 
{
	uint16_t x, y;	
} Point_t, *pPoint_t;

typedef struct _Size_t 
{
	uint16_t szX, szY;	
} Size_t, *pSize_t;

typedef struct _Rect_t 
{
	uint16_t XL, XR, YU, YD;	
} Rect_t, *pRect_t;

typedef struct _Bmp_t 
{
	char *pPicDesc;
	uint16_t  szW, szH;
	uint16_t  BytesPP, BitsPP;
	void *pPicStream;
	uint16_t *pPalette;
} Bmp_t, *pBmp_t;

typedef struct _FontType_t 
{
	char *pFontDesc;
	uint16_t H_Size;
	uint16_t V_Size;
	uint16_t CharacterOffset;
	uint16_t CharactersNumber;
	const uint8_t *pFontStream;
} FontType_t, *pFontType_t;

typedef uint16_t Color_t, *pColor_t;
typedef uint16_t Brush_t, *pBrush_t;
typedef struct _Pen_t 
{
	uint8_t lineWidth, lineType;
	Color_t color;		
} Pen_t, *pPen_t;

typedef struct _Cursor_t 
{
	uint8_t H_Size, V_Size;
	uint8_t *pCursorData;		
} Cursor_t, *pCursor_t;

//typedef uint32_t LcdPixel_t, *pLcdPixel_t;

#define C_GLCD_REFRESH_FREQ     (50)	// Hz
#define C_GLCD_H_SIZE           480
#define C_GLCD_H_PULSE          2	//
#define C_GLCD_H_FRONT_PORCH    5	//
#define C_GLCD_H_BACK_PORCH     40 	//
#define C_GLCD_V_SIZE           272
#define C_GLCD_V_PULSE          2
#define C_GLCD_V_FRONT_PORCH    8
#define C_GLCD_V_BACK_PORCH     8

#define C_GLCD_PWR_ENA_DIS_DLY  10000
#define C_GLCD_ENA_DIS_DLY      10000

//Cursor 64x64 pixels
#define CURSOR_H_SIZE 64
#define CURSOR_V_SIZE 64
//
#define CIRCLE_R  18


#define CRSR_PIX_32     0
#define CRSR_PIX_64     1
#define CRSR_ASYNC      0
#define CRSR_FRAME_SYNC 2

#define TEXT_DEF_TAB_SIZE 5

#define TEXT_BEL1_FUNC()

#undef Bool
#define Bool unsigned long

#define RGB(r, g, b) (((b & 0x1F)<<12) | ((g & 0x3F)<<6) | ((r & 0x1F)))

// function protype
void GLCD_Cursor_Cfg(int Cfg);
void GLCD_Cursor_En(int cursor);
void GLCD_Cursor_Dis(void);
void GLCD_Move_Cursor(int x, int y);
void GLCD_Copy_Cursor (const pCursor_t pCursor, int cursor);
void GLCD_Init (const uint32_t *pPain, const uint32_t *pPallete);
void GLCD_SetPallet (const uint32_t * pPallete);
void GLCD_Ctrl (Bool bEna);
void GLCD_SetFont(pFontType_t pFont, Color_t Color, Color_t BackgndColor);
void GLCD_SetTxtColor(Color_t Color);
void GLCD_SetBakColor(Color_t BackgndColor);

void GLCD_SetWindow(uint32_t X_Left, uint32_t Y_Up, uint32_t X_Right, uint32_t Y_Down);
void GLCD_TextSetPos(uint32_t X, uint32_t Y);
void GLCD_TextSetTabSize(uint32_t Size);

int _putchar (int c);
void GLCD_LoadPic (uint32_t X_Left, uint32_t Y_Up, Bmp_t * pBmp, uint32_t Mask);
void GLCD_DrawText(int x, int y, char *str);

void GLCD_DrawLine(Point_t pt1, Point_t pt2, Pen_t pen);
void GLCD_DrawRect(Rect_t rc, Pen_t pen);
void GLCD_DrawFillRect(Rect_t rc, Brush_t br, Pen_t pen);
void GLCD_SaveRect(pRect_t pRect, void * p);
void GLCD_RestoreRect(pRect_t pRect, void * p);
int GLCD_PtInRect(Point_t pt, pRect_t pRect);
#endif /* __GLCD_H__ */
