// glcd.c
#include <stdlib.h>
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "net_misc.h"
//#include "lpc177x_8x_lcd.h"
#include "sdram.h"
#include "glcd7.h"

#define C_GLCD_CLK_PER_LINE     (C_GLCD_H_SIZE + C_GLCD_H_PULSE + C_GLCD_H_FRONT_PORCH + C_GLCD_H_BACK_PORCH)
#define C_GLCD_LINES_PER_FRAME  (C_GLCD_V_SIZE + C_GLCD_V_PULSE + C_GLCD_V_FRONT_PORCH + C_GLCD_V_BACK_PORCH)
#define C_GLCD_PIX_CLK          (C_GLCD_CLK_PER_LINE * C_GLCD_LINES_PER_FRAME * C_GLCD_REFRESH_FREQ)


#define LCD_VRAM_BASE_ADDR 	((unsigned long)SDRAM_BASE + 0x00000000)
#define LCD_CURSOR_BASE_ADDR 	((unsigned long)0x20088800)


static pFontType_t pCurrFont = NULL;
static Color_t TextColour, TextBackgndColour, transparentColor;

static int TextX_Pos = 0;
static int TextY_Pos = 0;

static int XL_Win = 0;
static int YU_Win = 0;
static int XR_Win = C_GLCD_H_SIZE-1;
static int YD_Win = C_GLCD_V_SIZE-1;

static int TabSize = TEXT_DEF_TAB_SIZE;

static int WindY_Size, WindX_Size;
static int CurrY_Size, CurrX_Size;
static int16_t *pWind;
static int16_t *pPix;

void GLCD_Cursor_Cfg(int Cfg)
{
  LPC_LCD->CRSR_CFG = Cfg;
}

// Enable Cursor. cursor - Cursor Number
void GLCD_Cursor_En(int cursor)
{
  LPC_LCD->CRSR_CTRL |= (cursor<<4);
  LPC_LCD->CRSR_CTRL |= 1;
}

// Disable Cursor
void GLCD_Cursor_Dis()
{
  LPC_LCD->CRSR_CTRL &= (1<<0);
}

// Moves cursor on position (x,y). Negativ values are posible.
// x - cursor x position, y - cursor y position
void GLCD_Move_Cursor(int x, int y)
{
	LPC_LCD->CRSR_CLIP = 0;
	LPC_LCD->CRSR_XY = 0;
	if(0 <= x) {	//no clipping
		LPC_LCD->CRSR_XY |= (x & 0x3FF);
	} else {		//clip x
		LPC_LCD->CRSR_CLIP |= -x;
	}

	if(0 <= y) {	//no clipping
		LPC_LCD->CRSR_XY |= (y << 16);
	} else {		//clip y
		LPC_LCD->CRSR_CLIP |= (-y << 8);
	}
}

// Copy Cursor from const image to LCD RAM image
// pCursor - pointer to cursor conts image,  
// cursor - cursor Number (0,1,2 or 3) for 64x64(size 256) pix cursor always use 0
// size - cursor size in words
void GLCD_Copy_Cursor (const uint32_t *pCursor, int cursor, int size)
{
	uint32_t i ;
   	uint32_t * pDst = (uint32_t *)LCD_CURSOR_BASE_ADDR;
   
   	pDst += cursor*64;

   	for(i = 0; i < size ; i++) {
//		*pDst++ = *pCursor++; 
		*pDst = *pCursor;
		pDst++;
		pCursor++;
	}
}

// GLCD controller init
extern const unsigned short ac480x272Pic01[];
extern const unsigned short acpic565[];
extern Bmp_t bmpic;

void GLCD_Init (const uint32_t *pPain, const uint32_t * pPallete)
{
	uint32_t i; //, y;
	uint32_t *pDst = (uint32_t *)LCD_VRAM_BASE_ADDR;
	unsigned short *pDst16;
	const unsigned short *pBmp16 = pBmp16;
	// Assign pins
	LPC_IOCON->P2_9 = 0x06;	// VD3, 	R0
	LPC_IOCON->P2_6 = 0x07;	// VD4,		R1
	LPC_IOCON->P2_7 = 0x07;	// VD5,		R2
	LPC_IOCON->P4_28 = 0x05;	// VD6,		R3
	LPC_IOCON->P4_29 = 0x05;	// VD7,		R4

	LPC_IOCON->P1_20 = 0x07;	// VD10,	G0
	LPC_IOCON->P1_21 = 0x07;	// VD11,	G1
	LPC_IOCON->P1_22 = 0x07;	// VD12,	G2
	LPC_IOCON->P1_23 = 0x07;	// VD13,	G3
	LPC_IOCON->P1_24 = 0x07;	// VD14,	G4
	LPC_IOCON->P1_25 = 0x07;	// VD15,	G5
	
	LPC_IOCON->P2_13 = 0x07;	// VD19,	B0
	LPC_IOCON->P1_26 = 0x07;	// VD20,	B1
	LPC_IOCON->P1_27 = 0x07;	// VD21,	B2
	LPC_IOCON->P1_28 = 0x07;	// VD22,	B3
	LPC_IOCON->P1_29 = 0x07;	// VD23,	B4
	
	LPC_IOCON->P2_2	= 0x07;	// DCLK
	LPC_IOCON->P2_0	= 0x07;	// DSIP(power)
	LPC_IOCON->P2_5	= 0x07;	// HSYNC
	LPC_IOCON->P2_3	= 0x07;	// VSYNC
	LPC_IOCON->P2_4	= 0x07;	// DataEn

	LPC_IOCON->P2_1	= 0x00;	// Backlight
	
	/*Back light enable*/
	LPC_GPIO1->DIR = (1<<5);
	LPC_GPIO1->SET= (1<<5);

	//Turn on LCD clock
	LPC_SC->PCONP |= 1<<0;
	
	// Disable cursor
	LPC_LCD->CRSR_CTRL &=~(1<<0);
	
	// disable GLCD controller	
	LPC_LCD->CTRL = 0;
	
	LPC_LCD->CTRL &= ~(0x07 <<1);
	#ifndef __RAM__
	// RGB565
	LPC_LCD->CTRL |= (6<<1);
	#else
	// RGB888
	LPC_LCD->CTRL |= (5<<1);
	#endif
	
	// TFT panel
	LPC_LCD->CTRL |= (1<<5);
	// single panel
	LPC_LCD->CTRL &= ~(1<<7);
	// notmal output
	LPC_LCD->CTRL &= ~(1<<8);
	// little endian byte order
	LPC_LCD->CTRL &= ~(1<<9);
	// little endian pix order
	LPC_LCD->CTRL &= ~(1<<10);
	// disable power
	LPC_LCD->CTRL &= ~(1<<11);
	// init pixel clock
	LPC_SC->LCD_CFG = PeripheralClock / ((uint32_t) C_GLCD_PIX_CLK);
	// bypass inrenal clk divider
	LPC_LCD->POL |=(1<<26);
	// clock source for the LCD block is HCLK
	LPC_LCD->POL &= ~(1<<5);
	// LCDFP pin is active LOW and inactive HIGH
	LPC_LCD->POL |= (1<<11);
	// LCDLP pin is active LOW and inactive HIGH
	LPC_LCD->POL |= (1<<12);
	// data is driven out into the LCD on the falling edge
	LPC_LCD->POL &= ~(1<<13);
	// active high
	LPC_LCD->POL &= ~(1<<14);
	LPC_LCD->POL &= ~(0x3FF <<16);
	LPC_LCD->POL |= (C_GLCD_H_SIZE-1)<<16;
	
	// init Horizontal Timing
	LPC_LCD->TIMH = 0; //reset TIMH before set value
	LPC_LCD->TIMH |= (C_GLCD_H_BACK_PORCH - 1)<<24;
	LPC_LCD->TIMH |= (C_GLCD_H_FRONT_PORCH - 1)<<16;
	LPC_LCD->TIMH |= (C_GLCD_H_PULSE - 1)<<8;
	LPC_LCD->TIMH |= ((C_GLCD_H_SIZE/16) - 1)<<2;
	
	// init Vertical Timing
	LPC_LCD->TIMV = 0;  //reset TIMV value before setting
	LPC_LCD->TIMV |= (C_GLCD_V_BACK_PORCH)<<24;
	LPC_LCD->TIMV |= (C_GLCD_V_FRONT_PORCH)<<16;
	LPC_LCD->TIMV |= (C_GLCD_V_PULSE - 1)<<10;
	LPC_LCD->TIMV |= C_GLCD_V_SIZE - 1;
	// Frame Base Address doubleword aligned
	LPC_LCD->UPBASE = LCD_VRAM_BASE_ADDR & ~7UL ;
	LPC_LCD->LPBASE = LCD_VRAM_BASE_ADDR & ~7UL ;
        // init colour pallet

	if(NULL != pPallete) {
		GLCD_SetPallet(pPallete);
	}
	// SDRAMTest();
	if (NULL == pPain) {
		// clear display memory
		for( i = 0; (C_GLCD_H_SIZE * C_GLCD_V_SIZE) > i; i++) {
	  		*pDst++ = 0;
		}
	} else {
		pDst16 = (unsigned short *) LCD_VRAM_BASE_ADDR;
#ifndef __RAM__
		GLCD_LoadPic(0, 0, &bmpic, 0);
//		pBmp16 = acpic565;	 // ac480x272Pic01;
//		for( i = 0; (C_GLCD_H_SIZE * C_GLCD_V_SIZE) > i; i++) {
//	  		*pDst16++ = *pBmp16++;
//		}
#else	
		
		// set display memory				
		for (y=0; y<C_GLCD_V_SIZE / 2; y++) {
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = (i*256/160);
			}
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = (i*256/160) << 8;
			}
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = (i*256/160) << 16;
			}
		}
		for (y=0; y<C_GLCD_V_SIZE / 2; y++) {
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = ~(i*256/160);
			}
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = ~((i*256/160) << 8);
			}
			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
				*pDst++ = ~((i*256/160) << 16);
			}
		}
		pDst16 = (unsigned short *) pDst;
		for (y=0; y<C_GLCD_V_SIZE; y++) {
			for (i=0; i<C_GLCD_H_SIZE; i++) {
				*pDst16++ = 0xffff;
			}
		}
#endif
	}
  	for(i = C_GLCD_ENA_DIS_DLY; i; i--);
}

// GLCD init colour pallete
void GLCD_SetPallet (const uint32_t * pPallete)
{
	uint32_t i;
	uint32_t * pDst = (uint32_t *)LPC_LCD->PAL;
	// assert(pPallete);
	for (i = 0; i < 128; i++) {
		*pDst++ = *pPallete++;
	}
}

// GLCD enable disabe sequence
void GLCD_Ctrl (Bool bEna)
{
	volatile uint32_t i;
	if (bEna) {
//		LCD_CTRL_bit.LcdEn = 1;
		LPC_LCD->CTRL |= (1<<0);
		for(i = C_GLCD_PWR_ENA_DIS_DLY; i; i--);
//		LCD_CTRL_bit.LcdPwr= 1;   // enable power
		LPC_LCD->CTRL |= (1<<11);
	} else {
//    LCD_CTRL_bit.LcdPwr= 0;   // disable power
		LPC_LCD->CTRL &= ~(1<<11);
		for(i = C_GLCD_PWR_ENA_DIS_DLY; i; i--);
//		LCD_CTRL_bit.LcdEn = 0;
		LPC_LCD->CTRL &= ~(1<<0);
	}
}

// Set current font, font color and background color
void GLCD_SetFont(pFontType_t pFont, Color_t Color, Color_t BackgndColor)
{
	pCurrFont = pFont;
	TextColour = Color;
	TextBackgndColour = BackgndColor;
}

void GLCD_SetTxtColor(Color_t Color)
{
	TextColour = Color;
}

void GLCD_SetBakColor(Color_t BackgndColor)
{
	TextBackgndColour = BackgndColor;
}

// Set draw window XY coordinate in pixels
void GLCD_SetWindow(uint32_t X_Left, uint32_t Y_Up, uint32_t X_Right, uint32_t Y_Down)
{
	// assert(X_Right < C_GLCD_H_SIZE);
	// assert(Y_Down < C_GLCD_V_SIZE);
	// assert(X_Left < X_Right);
	// assert(Y_Up < Y_Down);
	XL_Win = X_Left;
	YU_Win = Y_Up;
	XR_Win = X_Right;
	YD_Win = Y_Down;
}

// Set text X,Y coordinate in characters
void GLCD_TextSetPos(uint32_t X, uint32_t Y)
{
	TextX_Pos = X;
	TextY_Pos = Y;
}

// Set text tab size in characters
void GLCD_TextSetTabSize(uint32_t Size)
{
	TabSize = Size;
}

// Put char function
void LCD_SET_WINDOW(uint32_t X_Left, uint32_t X_Right, uint32_t Y_Up, uint32_t Y_Down)
{
	pPix = pWind = ((int16_t*)LCD_VRAM_BASE_ADDR) + X_Left + (Y_Up*C_GLCD_H_SIZE);
	WindX_Size = X_Right - X_Left;
	WindY_Size = Y_Down - Y_Up;
	CurrX_Size = CurrY_Size = 0;
}

// Put char function
void LCD_WRITE_PIXEL(uint32_t Pixel)
{
	*pPix++ = Pixel;
	if (++CurrX_Size > WindX_Size) {
		CurrX_Size = 0;
		if(++CurrY_Size > WindY_Size) {
			CurrY_Size = 0;
		}
		pPix = pWind + CurrY_Size * C_GLCD_H_SIZE;
	}
}

// Calculate character window
Bool GLCD_TextCalcWindow(int *pXL, int *pXR, int *pYU, int *pYD, int *pH_Size, int *pV_Size)
{
	*pH_Size = pCurrFont->H_Size;
	*pV_Size = pCurrFont->V_Size;
	*pXL = XL_Win + (TextX_Pos*pCurrFont->H_Size);
	if(*pXL > XR_Win) {
		return(FALSE);
	}
	*pYU = YU_Win + (TextY_Pos*pCurrFont->V_Size);
	if(*pYU > YD_Win) {
		return(FALSE);
	}

	*pXR   = XL_Win + ((TextX_Pos+1)*pCurrFont->H_Size) - 1;
	if(*pXR > XR_Win) {
		*pH_Size -= *pXR - XR_Win;
		*pXR = XR_Win;
	}

	*pYD = YU_Win + ((TextY_Pos+1)*pCurrFont->V_Size) - 1;
	if(*pYD > YD_Win) {
		*pV_Size -= *pYD - YD_Win;
		*pYD = YD_Win;
	}
	return(TRUE);
}

// Put char function
int _putchar (int c)
{
	const uint8_t *pSrc;
	uint32_t H_Line;
	int xl,xr,yu,yd,Temp,V_Size, H_Size, SrcInc = 1;
	uint32_t WhiteSpaceNumb;
	uint32_t i, j, k;

	if(pCurrFont == NULL) {
		return(0);
	}
	H_Line = (pCurrFont->H_Size / 8) + ((pCurrFont->H_Size % 8)?1:0);
	switch(c) {
	case '\n':  // go to begin of next line (NewLine)
		++TextY_Pos;
		break;
	case '\r':  // go to begin of this line (Carriage Return)
// clear from current position to end of line
		while(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size)) {
			LCD_SET_WINDOW(xl,xr,yu,yd);
			for(i = 0; i < V_Size; ++i) {
				for(j = 0; j < H_Size; ++j) {
					LCD_WRITE_PIXEL(TextBackgndColour);
				}
			}
			++TextX_Pos;
		}
		TextX_Pos = 0;
		break;
	case '\b': // go back one position (BackSpace)
		if(TextX_Pos) {
			--TextX_Pos;
// del current position
			if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size)) {
				LCD_SET_WINDOW(xl,xr,yu,yd);
				for(i = 0; i < V_Size; ++i) {
					for(j = 0; j < H_Size; ++j) {
						LCD_WRITE_PIXEL(TextBackgndColour);
					}
				}
			}
		}
		break;
	case '\t':  // go to next Horizontal Tab stop
		WhiteSpaceNumb = TabSize - (TextX_Pos%TabSize);
		for(k = 0; k < WhiteSpaceNumb; ++k) {
			LCD_SET_WINDOW(xl,xr,yu,yd);
			if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size)) {
				for(i = 0; i < V_Size; ++i) {
					for(j = 0; j < H_Size; ++j) {
						LCD_WRITE_PIXEL(TextBackgndColour);
					}
				}
				++TextX_Pos;
			} else {
				break;
			}
		}
		break;
	case '\f':  // go to top of page (Form Feed)
// clear entire window
		H_Size = XR_Win - XL_Win;
		V_Size = YD_Win - YU_Win;
// set character window X left, Y right
		LCD_SET_WINDOW(XL_Win,XR_Win,YU_Win,YD_Win);
// Fill window with background font color
		for(i = 0; i <= V_Size; ++i) {
			for(j = 0; j <= H_Size; ++j) {
				LCD_WRITE_PIXEL(TextBackgndColour);
			}
		}

		TextX_Pos = TextY_Pos = 0;
		break;
	case '\a':  // signal an alert (BELl)
		TEXT_BEL1_FUNC();
		break;
	default:
// Calculate the current character base address from stream and the character position
		if((c <  pCurrFont->CharacterOffset) && (c >= pCurrFont->CharactersNumber)) {
			c = 0;
		} else {
			c -= pCurrFont->CharacterOffset;
		}
		pSrc = pCurrFont->pFontStream + (H_Line * pCurrFont->V_Size * c);
// Calculate character window and fit it in the text window
    	if(GLCD_TextCalcWindow(&xl,&xr,&yu,&yd,&H_Size,&V_Size)) {
// set character window X left, Y right
			LCD_SET_WINDOW(xl,xr,yu,yd);
// Send char data
			for(i = 0; i < V_Size; ++i) {
				SrcInc = H_Line;
				for(j = 0; j < H_Size; ++j) {
					Temp = (*pSrc & (1UL << ((7-j) & 0x7)))?TextColour:TextBackgndColour;
					LCD_WRITE_PIXEL(Temp);
					if((j&0x7) == 7) {
						++pSrc;
						--SrcInc;
					}
				}
// next line of character
				pSrc += SrcInc;
			}
		}
		++TextX_Pos;
	}
	return(c);
}

// Load picture in VRAM memory area
void GLCD_LoadPic (uint32_t X_Left, uint32_t Y_Up, Bmp_t * pBmp, uint32_t Mask)
{
	uint32_t i, j;
	uint16_t * pData = ((uint16_t *) LCD_VRAM_BASE_ADDR) + X_Left + (Y_Up * C_GLCD_H_SIZE);
	uint16_t * pSrc = pBmp->pPicStream;
	uint16_t X_LeftHold;
	for(i = 0; i < pBmp->szH; i++) {
		if(Y_Up++ >= C_GLCD_V_SIZE)
			break;
		for(j = 0; j < pBmp->szW; j++) {
			if(X_LeftHold++ >= C_GLCD_H_SIZE) {
				pSrc += pBmp->szH - j;
				break;
			}
			*(pData+j) = *pSrc++ ^ Mask;
		}
		X_LeftHold = X_Left;
		pData += C_GLCD_H_SIZE;
	}
}

void GLCD_DrawText(int x, int y, char *str)
{
	int ch;
	
	GLCD_TextSetPos(x, y);
	while (*str) {
		ch = *str++;
		_putchar(ch);
	}
}

void GLCD_DrawLine(Point_t pt1, Point_t pt2, Pen_t pen)
{
	int i;
	int16_t *p;
	int w;

	if (pt1.y==pt2.y) {	// 水平线
		if (pt1.x>pt2.x) {
			i = pt1.x; pt1.x=pt2.x; pt2.x=i;
		}
		p = ((int16_t*)LCD_VRAM_BASE_ADDR) + pt1.y*C_GLCD_H_SIZE + pt1.x;
		for (i=pt1.x; i<=pt2.x; i++) {
			*p++ = pen.color;
		}
		if (pen.lineWidth>1) {
			w = pen.lineWidth-1;
			while (w) {
				w--;
			}
		}
	} else if (pt1.x==pt2.x) {	// 垂直线
		if (pt1.y>pt2.y) {
			i = pt1.y; pt1.y=pt2.y; pt2.y=i;
		}
		p = ((int16_t*)LCD_VRAM_BASE_ADDR) + pt1.y*C_GLCD_H_SIZE + pt1.x;
		for (i=pt1.y; i<=pt2.y; i++) {
			*p = pen.color;
			p += C_GLCD_H_SIZE;
		}
	} else {
	}
}

void GLCD_DrawRect(Rect_t rc, Pen_t pen)
{
}

void GLCD_DrawFillRect(Rect_t rc, Brush_t br, Pen_t pen)
{
}

void GLCD_SaveRect(pRect_t pRect, void * p)
{	
	int x,y;
	uint16_t * pWnd, *bufPtr;

	if (!p) return;
	bufPtr = p;
	pWnd = ((uint16_t*)LCD_VRAM_BASE_ADDR) + pRect->YU * C_GLCD_H_SIZE +  pRect->XL;
	for (y=pRect->YU; y<=pRect->YD; y++) {
		for (x=pRect->XL; x<=pRect->XR; x++) {
			*bufPtr++ = *pWnd++;
		}
		pWnd += C_GLCD_H_SIZE;
	}
}

void GLCD_RestoreRect(pRect_t pRect, void * p)
{
	int x,y;
	uint16_t * pWnd, *bufPtr;

	if (!p) return;
	bufPtr = p;
	pWnd = ((uint16_t*)LCD_VRAM_BASE_ADDR) + pRect->YU * C_GLCD_H_SIZE +  pRect->XL;
	for (y=pRect->YU; y<=pRect->YD; y++) {
		for (x=pRect->XL; x<=pRect->XR; x++) {
			*pWnd++ = *bufPtr++;
		}
		pWnd += C_GLCD_H_SIZE;
	}
}

int GLCD_PtInRect(Point_t pt, pRect_t pRect)
{
	if (pRect->XL > pRect->XR) {
		if ((pt.x < pRect->XR) || (pt.x > pRect->XL)) return 0;
	} else {
		if ((pt.x < pRect->XL) || (pt.x > pRect->XR)) return 0;
	}
	if (pRect->YD > pRect->YU) {
		if ((pt.y < pRect->YU) || (pt.y > pRect->YD)) return 0;
	} else {
		if ((pt.y < pRect->YD) || (pt.y > pRect->YU)) return 0;
	}
	return 1;
}


