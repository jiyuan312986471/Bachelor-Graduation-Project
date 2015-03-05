// main.c

#include <wm.h>
#include "GUI.h"
#include <stdio.h>
//#include "typeDef.h"

//#include "MX29LV640E_Drv.h"

#if 0
#include "nhnTxt.h"
//#define FONT_IN_FLASH

#ifdef FONT_IN_FLASH
const int GUI_Font24 = 0x8019970c;
#define acSTLITI 0x80000000
#define acST_GB231224 0x80000000
#define NumBytes_acSTLITI 0x3EBE59
#else
extern GUI_CONST_STORAGE GUI_FONT GUI_Font24;
extern const unsigned char acSTLITI[];
extern const int NumBytes_acSTLITI;
extern const unsigned char acST_GB231224[];
#endif

const unsigned short str[] = {
	0x4e00, 0x4e01, 0x4e02, 0x4e03, 0x4e04, 0x4e05, 0x4e06, 0x4e07
};

const char utf8Str[] = {
	"\xe4\xb8\x80\xe4\xb8\x81\xe4\xb8\x82\xe4\xb8\x83\xe4\xb8\x84\xe4\xb8\x85\xe4\xb8\x86\xe4\xb8\x87"
};

int fnState;

void MainTask(void) 
{
	GUI_FONT ttfFont0, ttfFont1, ftSIF;
	GUI_TTF_CS ttfCs0, ttfCs1;
	GUI_TTF_DATA ttfData;
	int xPos, yPos, xSize, ySize;
	GUI_TTF_CS       * pCS;
	int i = 0;

	GUI_Init();
	GUI_CURSOR_Show();
	GUI_SetBkColor(GUI_RED);
	GUI_Clear();
	GUI_Delay(300);
	GUI_SetBkColor(GUI_GREEN);
	GUI_Clear();
	GUI_Delay(300);
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_Delay(300);

	GUI_SetBkColor(GUI_GRAY);
	GUI_Clear();

/*
// Set parameters for accessing the font file
	ttfData.pData = (const void*)acSTLITI; // Address/
	ttfData.NumBytes = NumBytes_acSTLITI; // Size
// Set creation parameters of first font
	ttfCs0.pTTF = &ttfData; // Use address of GUI_TTF_DATA
	ttfCs0.PixelHeight = 24; // Pixel height
	ttfCs0.FaceIndex = 0; // Initialize to 0
// Set creation parameters of second font
	ttfCs1.pTTF = &ttfData; // Use address of GUI_TTF_DATA
	ttfCs1.PixelHeight = 48; // Pixel height
	ttfCs1.FaceIndex = 0; // Initialize to 0
// Create 2 fonts
	fnState = GUI_TTF_CreateFont(&ttfFont0, &ttfCs0);
	fnState = GUI_TTF_CreateFont(&ttfFont1, &ttfCs1);

// Draw something using the fonts
	GUI_SetFont(&ttfFont0);
	GUI_DispString("Hello world\n");
	GUI_SetFont(&ttfFont1);
	GUI_DispString("Hello world");
	GUI_Delay(5000);
*/
 	GUI_UC_SetEncodeUTF8();	
	GUI_SIF_CreateFont((const void*)acST_GB231224, &ftSIF, GUI_SIF_TYPE_PROP_EXT);
	GUI_DispString(str_ModuleInfo);
	GUI_DispNextLine();
	GUI_DispString(str_otModule);
	GUI_DispNextLine();
	GUI_DispString(str_opPwr);
	GUI_DispNextLine();
	GUI_DispString(str_nAlarm);
	GUI_DispNextLine();
	GUI_DispString(str_outOP);
	GUI_DispNextLine();
	GUI_DispString(str_laserBias);
	GUI_DispNextLine();
	GUI_DispString(str_laserTemp);
	GUI_Delay(5000);


	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();

//	GUI_SetFont(&GUI_FontComic24B_1);
//	GUI_SetFont((const GUI_FONT *)GUI_Font24);
//	GUI_SetFont(&GUI_Font24);
	GUI_SetColor(GUI_CYAN);
//	GUI_DispStringHCenterAt("\x4e\x2d\x56\xfd www.keil.com",   xSize / 2, 20);
	GUI_DispStringAt("\xe4\xb8\x87 ?www.keil.com",   xSize / 5, 20);
	GUI_DispChar(0x4e00);
	GUI_DispNextLine();
	GUI_DispString("\xe4\xb8\x80 www.keil.com");
	GUI_DispNextLine();
	GUI_UC_DispString(str);
	
	GUI_DispNextLine();
	GUI_DispString(utf8Str);
	
	GUI_SetColor(GUI_DARKBLUE);
	GUI_DispStringHCenterAt(utf8Str, xSize / 2, ySize - 40);
	
//	GUI_SetFont(&GUI_FontAlgerian24);
//	GUI_UC_SetEncodeUTF8();
//	GUI_UC_DispString((const U16*)"中国");
//	GUI_DispStringHCenterAt("中国", xSize / 2, 40);
	GUI_DispStringHCenterAt("www123456789", xSize / 2, 40);
	
	xPos = xSize / 2;
	yPos = ySize / 3;
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_REV);
	GUI_SetFont(GUI_FONT_20F_ASCII);
	GUI_DispStringHCenterAt("Hello world!", xPos, yPos);
	GUI_SetFont(GUI_FONT_D24X32);
	xSize = GUI_GetStringDistX("0000");
	xPos -= xSize / 2;
	yPos += 24 + 10;
	while (1) {
		GUI_DispDecAt(i++, xPos, yPos, 4);
		if (i > 9999) {
			i = 0;
		}
	    GUI_Delay(100);
	} 
}
#endif
int main (void) 
{
	sdram_init();
#ifdef SLK_BOARD
	JS28F128_IF_Init();
#else
	MX29LV640E_IF_Init();
#endif
	InitChassisData();
	InitPSData();
	InitFanData();
	MainTask();
	while(1);
}
