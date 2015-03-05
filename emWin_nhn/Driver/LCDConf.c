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
File        : LCDConf.c
Purpose     : Display controller configuration

              Display:        Ampire 240320LG
              Controller:     Himax HX8347-D

              Display driver: GUIDRV_Lin
              Operation mode: 16bpp, 16-bit RGB interface with SPI

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_Lin.h"

#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "LCD_X_LPC177x_8x.h"

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/

//
// Video RAM Address
//
//
// Physical display size
//
#define XSIZE_PHYS C_GLCD_H_SIZE
#define YSIZE_PHYS C_GLCD_V_SIZE
//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565	// GUICC_M565

//
// Buffers / VScreens
//
#define NUM_BUFFERS   1
#define NUM_VSCREENS  1

//
// Display orientation
//
  #define DISPLAY_ORIENTATION 0
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_SWAP_XY | GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_SWAP_XY | GUI_MIRROR_X)

//
// Display driver
//
//#define DISPLAY_DRIVER GUIDRV_LIN_16
#if   (DISPLAY_ORIENTATION == (GUI_MIRROR_X))
  #define DISPLAY_DRIVER GUIDRV_LIN_OX_16
#elif (DISPLAY_ORIENTATION == (GUI_MIRROR_Y))
  #define DISPLAY_DRIVER GUIDRV_LIN_OY_16
#elif (DISPLAY_ORIENTATION == (GUI_MIRROR_X | GUI_MIRROR_Y))
  #define DISPLAY_DRIVER GUIDRV_LIN_OXY_16
#elif (DISPLAY_ORIENTATION == (GUI_SWAP_XY))
  #define DISPLAY_DRIVER GUIDRV_LIN_OS_16
#elif (DISPLAY_ORIENTATION == (GUI_SWAP_XY | GUI_MIRROR_X))
  #define DISPLAY_DRIVER GUIDRV_LIN_OSX_16
#elif (DISPLAY_ORIENTATION == (GUI_SWAP_XY | GUI_MIRROR_Y))
  #define DISPLAY_DRIVER GUIDRV_LIN_OSY_16
#else
  #define DISPLAY_DRIVER GUIDRV_LIN_16
#endif

//
// Touch screen
//
#define USE_TOUCH   1
//
// Touch screen calibration
//#define TOUCH_X_MIN 0x00E0
//#define TOUCH_X_MAX 0x0F40
//#define TOUCH_Y_MIN 0x00C0
//#define TOUCH_Y_MAX 0x0F60

#ifdef SLK_BOARD
#define TOUCH_X_MIN 200
#define TOUCH_X_MAX 3890
#define TOUCH_Y_MIN 3750
#define TOUCH_Y_MAX 300
#else
#define TOUCH_X_MIN  0x20F  //0x0CA	// 0x320
#define TOUCH_X_MAX  0xD39	//0xEB2	// 0xD80
#define TOUCH_Y_MIN  0xC7C  //0xDD0	// 0xC00
#define TOUCH_Y_MAX  0x2EE  //0x159	// 0x320
#endif
//
// Touch controller settings
//
/*
#define TOUCH_AD_RIGHT        3890
#define TOUCH_AD_LEFT         200
#define TOUCH_AD_TOP 		3750         
#define TOUCH_AD_BOTTOM       300
#define TOUCH_TIMER_INTERVAL  10
*/
/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION  0
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
#define LANDSCAPE   1
#else
#define LANDSCAPE   0
#endif

#if (LANDSCAPE == 1)
#define WIDTH       YSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      XSIZE_PHYS  /* Screen Hight (in pixels)         */
#else
#define WIDTH       XSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      YSIZE_PHYS  /* Screen Hight (in pixels)         */
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_TOP    TOUCH_X_MAX
    #define TOUCH_BOTTOM TOUCH_X_MIN
  #else
    #define TOUCH_TOP    TOUCH_X_MIN
    #define TOUCH_BOTTOM TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_LEFT   TOUCH_Y_MAX
    #define TOUCH_RIGHT  TOUCH_Y_MIN
  #else
    #define TOUCH_LEFT   TOUCH_Y_MIN
    #define TOUCH_RIGHT  TOUCH_Y_MAX
  #endif
#else
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_LEFT   TOUCH_X_MAX
    #define TOUCH_RIGHT  TOUCH_X_MIN
  #else
    #define TOUCH_LEFT   TOUCH_X_MIN
    #define TOUCH_RIGHT  TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_TOP    TOUCH_Y_MAX
    #define TOUCH_BOTTOM TOUCH_Y_MIN
  #else
    #define TOUCH_TOP    TOUCH_Y_MIN
    #define TOUCH_BOTTOM TOUCH_Y_MAX
  #endif
#endif


/*********************************************************************
*
*       Driver Port functions
*
**********************************************************************
*/
extern void LCD_X_Init(void);

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*static void delay (int cnt) {
  cnt <<= 15;
  while (cnt--);
}
*/

/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void) {
#ifndef WIN32
	LCD_X_Init();
#endif  /* WIN32 */
}

/*********************************************************************
*
*       _SetVRAMAddr
*
* Purpose:
*   Should set the frame buffer base address
*/
static void _SetVRAMAddr(void * pVRAM) {
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetOrg
*
* Purpose:
*   Should set the origin of the display typically by modifying the
*   frame buffer base address register
*/
static void _SetOrg(int xPos, int yPos) {
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetLUTEntry
*
* Purpose:
*   Should set the desired LUT entry
*/
static void _SetLUTEntry(LCD_COLOR Color, U8 Pos) {
  /* TBD by customer */
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
int TouchOrientation;
void LCD_X_Config(void) {
  
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
  LCD_SetVRAMAddrEx(0, (void *)LCD_VRAM_BASE_ADDR);

  #if (USE_TOUCH == 1)
    //
    // Set orientation of touch screen
    //
	TouchOrientation = DISPLAY_ORIENTATION;
    GUI_TOUCH_SetOrientation(TouchOrientation);
    //
    // Calibrate touch screen
    //
    GUI_TOUCH_Calibrate(GUI_COORD_X, 0, WIDTH  - 1, TOUCH_LEFT, TOUCH_RIGHT);
    GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, HEIGHT - 1, TOUCH_TOP,  TOUCH_BOTTOM);
  #endif
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - OK
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    return 0;
  }
  case LCD_X_SETVRAMADDR: {
    //
    // Required for setting the address of the video RAM for drivers
    // with memory mapped video RAM which is passed in the 'pVRAM' element of p
    //
    LCD_X_SETVRAMADDR_INFO * p;
    p = (LCD_X_SETVRAMADDR_INFO *)pData;
    _SetVRAMAddr(p->pVRAM);
    return 0;
  }
  case LCD_X_SETORG: {
    //
    // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
    //
    LCD_X_SETORG_INFO * p;
    p = (LCD_X_SETORG_INFO *)pData;
    _SetOrg(p->xPos, p->yPos);
    return 0;
  }
  case LCD_X_SETLUTENTRY: {
    //
    // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
    //
    LCD_X_SETLUTENTRY_INFO * p;
    p = (LCD_X_SETLUTENTRY_INFO *)pData;
    _SetLUTEntry(p->Color, p->Pos);
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
