/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2011  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.12 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : TOUCH_Sample.c
Purpose     : Shows how to access a touch panel without using buttons
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
void _WaitForPressedState(int Pressed) {
	GUI_PID_STATE State;
	do {
		GUI_TOUCH_GetState(&State);
		GUI_Delay(1);
		if (State.Pressed == Pressed) {
			int TimeStart = GUI_GetTime();
			if (!Pressed) return;
			do {
				GUI_TOUCH_GetState(&State);
				GUI_Delay(1);
				if (State.Pressed != Pressed) {
					break;
				} else if ((GUI_GetTime() - 300) > TimeStart) {
					return;
				}
			} while (1);
		}
	} while (1);
}

void _GetPhysValues(int LogX, int LogY, int * pPhysX, int * pPhysY/*, const char * pString*/) {
#if 0
	char acText[] = "Press here";
  GUI_RECT Rect;
  int FontSizeY, Align;
  FontSizeY = GUI_GetFontSizeY();
  GUI_Clear();
  GUI_SetColor(GUI_BLACK);
  _DispStringCentered("Runtime calibration,\n"
                      "please touch the screen\n"
                      "at the center of the ring."); /* Ask user to press the touch */
  /* Calculate the rectangle for the string */
  Rect.y0 = LogY - FontSizeY;
  Rect.y1 = LogY + FontSizeY;
  if (LogX < LCD_GetXSize() / 2) {
    Rect.x0 = LogX + 15;
    Rect.x1 = LCD_GetXSize();
    Align = GUI_TA_LEFT;
  } else {
    Rect.x0 = 0;
    Rect.x1 = LogX - 15;
    Align = GUI_TA_RIGHT;
  }
  /* Show the text nearby the ring */
  GUI_DispStringInRect(acText, &Rect, Align | GUI_TA_TOP);
  GUI_DispStringInRect(pString, &Rect, Align | GUI_TA_BOTTOM);
#endif
  /* Draw the ring */
  GUI_SetColor(GUI_RED);
  GUI_FillCircle(LogX, LogY, 10);
  GUI_SetColor(GUI_WHITE);
  GUI_FillCircle(LogX, LogY, 5);
  /* Wait until touch is pressed */
  _WaitForPressedState(1);
  *pPhysX = GUI_TOUCH_GetxPhys();
  *pPhysY = GUI_TOUCH_GetyPhys();
  /* Wait until touch is released */
  _WaitForPressedState(0);
  GUI_FillCircle(LogX, LogY, 10);
}
/*********************************************************************
*
*       MainTask
*/
#ifdef TSC_DBG
extern volatile int tcX,tcY,tcZ,tcZ1,tcZ2;
#endif

void MainTask(void) {
	int aPhysX[2], aPhysY[2], aLogX[2], aLogY[2], i;
	int needCal; 
	int xLoc, yLoc;
	
	GUI_Init();
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_CURSOR_Select(&GUI_CursorCrossL);
	GUI_CURSOR_Show();
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetColor(GUI_BLACK);
	GUI_Clear();
	GUI_DispString("Measurement of\nA/D converter values");
	
	GUI_DrawRect(20, 20, LCD_GetXSize()-20, LCD_GetYSize()-20);
	GUI_DrawRect(100, 100, LCD_GetXSize()-100, LCD_GetYSize()-100);
 	GUI_CURSOR_Show();
	needCal = 1;
 while (1) {
    GUI_PID_STATE TouchState;
    int xPhys, yPhys;
    GUI_TOUCH_GetState(&TouchState);  /* Get the touch position in pixel */
    xPhys = GUI_TOUCH_GetxPhys();     /* Get the A/D mesurement result in x */
    yPhys = GUI_TOUCH_GetyPhys();     /* Get the A/D mesurement result in y */
    /* Display the measurement result */
    GUI_SetColor(GUI_BLUE);
    GUI_DispStringAt("Analog input:\n", 0, 20);
    GUI_GotoY(GUI_GetDispPosY() + 2);
    GUI_DispString("x:");
    GUI_DispDec(xPhys, 4);
    GUI_DispString(", y:");
    GUI_DispDec(yPhys, 4);
    /* Display the according position */
    GUI_SetColor(GUI_RED);
    GUI_GotoY(GUI_GetDispPosY() + 4);
    GUI_DispString("\nPosition:\n");
    GUI_GotoY(GUI_GetDispPosY() + 2);
    GUI_DispString("x:");
    GUI_DispDec(TouchState.x,4);
    GUI_DispString(", y:");
    GUI_DispDec(TouchState.y,4);
	
#ifdef TSC_DBG
#ifdef SLK_BOARD
	xLoc = 300;
#else
	xLoc = 400;
#endif
    GUI_DispHexAt(tcX, xLoc, 10, 8);
    GUI_DispHexAt(tcY, xLoc, 30, 8);
    GUI_DispHexAt(tcZ, xLoc, 50, 8);
    GUI_DispHexAt(tcZ1, xLoc, 70, 8);
    GUI_DispHexAt(tcZ2, xLoc, 90, 8);
	
	if (TouchState.Pressed) GUI_DispStringAt("Pressed  ", 300, 240);
	else GUI_DispStringAt("Released", 300, 240);
#endif	

	if (needCal) {
		aLogX[0] = 100;
		aLogX[1] = LCD_GetXSize() - 100;
		aLogY[0] = 100;
		aLogY[1] = LCD_GetYSize() - 100;
		if (needCal == 1) {
			for (i = 0; i < 2; i++) {
				_GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i]/*, _acPos[i]*/);
			}
		} else {
			aPhysX[0]= 0x3D0;
			aPhysX[1]= 0xB70;
			aPhysY[0]= 0xA20;
			aPhysY[1]= 0x520;
		}
	
//		GUI_TOUCH_Calibrate(GUI_COORD_X, 0, WIDTH  - 1, TOUCH_LEFT, TOUCH_RIGHT);
//		GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, HEIGHT - 1, TOUCH_TOP,  TOUCH_BOTTOM);
		GUI_TOUCH_Calibrate(GUI_COORD_X, aLogX[0], aLogX[1], aPhysX[0], aPhysX[1]); /* Calibrate X-axis */
		GUI_TOUCH_Calibrate(GUI_COORD_Y, aLogY[0], aLogY[1], aPhysY[0], aPhysY[1]); /* Calibrate Y-axis */
		needCal = 0;
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringAt("Xl:", 300, 300); 
		GUI_DispHex(aPhysX[0], 8);
		GUI_DispString("Xr:");
		GUI_DispHex(aPhysX[1], 8);
		
		GUI_DispStringAt("Yt:", 300, 330); 
		GUI_DispHex(aPhysY[0], 8);
		GUI_DispString("Yb:");
		GUI_DispHex(aPhysY[1], 8);
	}
	
/*	xLoc = 100;
	yLoc = LCD_GetYSize()-100;
	GUI_SetColor(GUI_RED);
	GUI_FillCircle(xLoc, yLoc, 10);
	GUI_SetColor(GUI_WHITE);
	GUI_FillCircle(xLoc, yLoc, 5);

	xLoc = LCD_GetXSize()-100;
	yLoc = 100;
	GUI_SetColor(GUI_RED);
	GUI_FillCircle(xLoc, yLoc, 10);
	GUI_SetColor(GUI_WHITE);
	GUI_FillCircle(xLoc, yLoc, 5);
*/
    /* Wait a while */
    GUI_Delay(100);
  };
}

/*************************** End of file ****************************/

