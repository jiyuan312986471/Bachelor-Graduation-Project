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
File        : GUI_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <LPC177x_8x.h>
#include "system_LPC177x_8x.h"
#include "GUI.h"
//#include "I2C.h"
#include "TSC.h"
//#include "JOY.h"

volatile int tscPressure;

/*********************************************************************
*
*       Global data
*/
volatile int OS_TimeMS;

/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)

  Some timing dependent routines require a GetTime
  and delay function. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) { 
  return OS_TimeMS; 
}

void GUI_X_Delay(int ms) { 
  int tEnd = OS_TimeMS + ms;
  while ((tEnd - OS_TimeMS) > 0);
}

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) {
//	I2C_Init();
	TSC_Init();
//	JOY_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);  /* SysTick IRQ each 1 ms */
}

/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/

void GUI_X_ExecIdle(void) {}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()
*
* Note:
*   The following routines are required only if emWin is used in a
*   true multi task environment, which means you have more than one
*   thread using the emWin API.
*   In this case the
*                       #define GUI_OS 1
*  needs to be in GUIConf.h
*/

void GUI_X_InitOS(void)    {}
void GUI_X_Unlock(void)    {}
void GUI_X_Lock(void)      {}
U32  GUI_X_GetTaskId(void) { return 1; }

/*********************************************************************
*
*      Event driving (optional with multitasking)
*
*                 GUI_X_WaitEvent()
*                 GUI_X_WaitEventTimed()
*                 GUI_X_SignalEvent()
*/

void GUI_X_WaitEvent(void)            {}
void GUI_X_WaitEventTimed(int Period) {}
void GUI_X_SignalEvent(void)          {}

static int TouchPhysX;
static int TouchPhysY;
extern int TouchOrientation;
	
void TOUCH_Exec(void) 
{
	TSC_DATA tscd;
	static U8 PressedOld = 0;
/*	static int xOld = 0;
	static int yOld = 0;
	int x, y;
	int xDiff, yDiff;
	int xSize, ySize;
*/
	if (TSC_TouchDet()) {
    // Touch screen is pressed

    // Read current position
		TSC_GetData(&tscd);
		tscPressure = tscd.z;
		if ((tscd.z > 8000) || (tscd.z <= 0)) {
			PressedOld = 0;
			GUI_TOUCH_StoreState(-1, -1);
			return;  // No update
		}
		if (TouchOrientation & GUI_SWAP_XY) {
//			TouchPhysX = 0x0FFF - tscd.y;
//			TouchPhysY = 0x0FFF - tscd.x;
			TouchPhysX = tscd.y;
			TouchPhysY = tscd.x;
		} else {
//			TouchPhysX = 0x0FFF - tscd.x;
//			TouchPhysY = 0x0FFF - tscd.y;
			TouchPhysX = tscd.x;
			TouchPhysY = tscd.y;
		}
		PressedOld = 1;
		GUI_TOUCH_Exec();
/*		if (PressedOld == 1) {
      // Touch screen has already been pressed
			GUI_TOUCH_Exec();
		} else {
      // Touch screen was previously not pressed

      // Store state regardless of position
//			GUI_TOUCH_StoreState(x, y);
			GUI_TOUCH_Exec();
			PressedOld = 1;
		}*/
	} else {
    // Touch screen is not pressed

    // Store state if it was released recently
		if (PressedOld == 1) {
			PressedOld = 0;
			GUI_TOUCH_StoreState(-1, -1);
		}
	}
}

/*********************************************************************
*
*       Joystick support
*
*/

#ifdef  JOYSTICK_ROTATE
#define JOYSTICK_LEFT   JOY_DOWN
#define JOYSTICK_RIGHT  JOY_UP
#define JOYSTICK_UP     JOY_LEFT
#define JOYSTICK_DOWN   JOY_RIGHT
#define JOYSTICK_CENTER JOY_CENTER
#else
#define JOYSTICK_LEFT   JOY_LEFT
#define JOYSTICK_RIGHT  JOY_RIGHT
#define JOYSTICK_UP     JOY_UP
#define JOYSTICK_DOWN   JOY_DOWN
#define JOYSTICK_CENTER JOY_CENTER
#endif

/*static void Joystick_Exec (void) {
  GUI_PID_STATE state;
  static  U8    hold = 0;
  static  U8    prevkeys = 0;
          U32   keys;
          I32   diff, max;

  // Read Joystick keys
  keys = JOY_GetKeys();

  // Dynamic pointer acceleration
  if (keys == prevkeys) {
    if (hold < (40+3)) hold++;
    diff = (hold > 3) ? hold - 3 : 0; 
  } else {
    hold = 0;
    diff = 1;
  }

  // Change State if keys are pressed or have changed
  if (keys || (keys != prevkeys)) {
    GUI_PID_GetState(&state);
    if (keys & JOYSTICK_LEFT) {
      state.x -= diff;
      if (state.x < 0) state.x = 0;
    }
    if (keys & JOYSTICK_RIGHT) {
      state.x += diff;
      max = LCD_GetXSize() - 1;
      if (state.x > max) state.x = max; 
    }
    if (keys & JOYSTICK_UP) {
      state.y -= diff;
      if (state.y < 0) state.y = 0;
    }
    if (keys & JOYSTICK_DOWN) {
      state.y += diff;
      max = LCD_GetYSize() - 1;
      if (state.y > max) state.y = max; 
    } 
    state.Pressed = (keys & JOYSTICK_CENTER) ? 1 : 0;
    GUI_PID_StoreState(&state);
    prevkeys = keys;
  }
}
*/

/*********************************************************************
*
*       SysTick_Handler
*
* Function decription:
*   Systick Interrupt Handler which is called periodically each 1ms.
*/
void SysTick_Handler (void) {
	static U8 ttick = 0;	// Touch Screen time tick
	static U8 ytick = 0;	// Joystick time tick

	OS_TimeMS++;			// Increment 1ms time tick

	if (ttick++ >= 10) {	// Touch Screen update period is 20ms
		ttick = 0;
		__disable_irq();
		TOUCH_Exec();	// Execute Touch Screen function
		__enable_irq();
	}
	if (ytick++ == 50) {	// Joystick update period is 50ms
		ytick = 0;
//		Joystick_Exec();	// Execute Joystick function
	}
}

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateX()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on X-axis,
*   prepares measurement for Y-axis.
*   Voltage on Y-axis is switched off.
*/
void GUI_TOUCH_X_ActivateX(void) {
}

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateY()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on Y-axis,
*   prepares measurement for X-axis.
*   Voltage on X-axis is switched off.
*/
void GUI_TOUCH_X_ActivateY(void) {
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureX()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of X-axis.
*/
int  GUI_TOUCH_X_MeasureX(void) {
	return TouchPhysX;
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureY()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of Y-axis.
*/
int  GUI_TOUCH_X_MeasureY(void) {
	return TouchPhysY;
}
#endif

/*************************** End of file ****************************/
