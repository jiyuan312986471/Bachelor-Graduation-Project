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
File        : WIDGET_NumPad.c
Purpose     : Shows how to use a numpad as input device on a touch screen
---------------------------END-OF-HEADER------------------------------
*/

#include "DIALOG.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/* Bitmap data for arrow keys */
static GUI_CONST_STORAGE GUI_COLOR _aColorsArrow[] = {
  0xFFFFFF, 0x000000
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalArrow = {
  2,	/* number of entries */
  1, 	/* No transparency */
  &_aColorsArrow[0]
};

static GUI_CONST_STORAGE unsigned char _acArrowRight[] = {
  ____XX__, ________,
  ____XXXX, ________,
  XXXXXXXX, XX______,
  ____XXXX, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE unsigned char _acArrowLeft[] = {
  ____XX__, ________,
  __XXXX__, ________,
  XXXXXXXX, XX______,
  __XXXX__, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowRight = {
  10,           /* XSize */
  5,            /* YSize */
  2,            /* BytesPerLine */
  1,            /* BitsPerPixel */
  _acArrowRight, /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowLeft = {
  10,           /* XSize */
  5,            /* YSize */
  2,            /* BytesPerLine */
  1,            /* BitsPerPixel */
  _acArrowLeft,  /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};

/* Array of keys */
static int _aKey[] = {GUI_KEY_DELETE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT};

#define BTN_WIDTH 40
#define BTN_HEIGHT 30
#define BTN_ORG_X 5
#define BTN_ORG_Y 5
#define BTN_ORG_IX 5
#define BTN_ORG_IY 5
#define BTN_LOC_X(col) BTN_ORG_X+(BTN_WIDTH+BTN_ORG_IX)*col
#define BTN_LOC_Y(row) BTN_ORG_Y+(BTN_HEIGHT+BTN_ORG_IY)*row
#define WIN_WIDTH (BTN_WIDTH+BTN_ORG_IX)*3 + BTN_ORG_X
#define WIN_HEIGHT (BTN_HEIGHT+BTN_ORG_IY)*5 + BTN_ORG_Y
/* Dialog resource of numpad */
static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
/*  Function                 Text      Id                 Px   Py   Dx   Dy */
  { WINDOW_CreateIndirect,   0,        0,                300, 60,  WIN_WIDTH, WIN_HEIGHT},
  { BUTTON_CreateIndirect,   "7",      GUI_ID_USER +  7, BTN_LOC_X(0), BTN_LOC_Y(0),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "8",      GUI_ID_USER +  8, BTN_LOC_X(1), BTN_LOC_Y(0),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "9",      GUI_ID_USER +  9, BTN_LOC_X(2), BTN_LOC_Y(0),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "4",      GUI_ID_USER +  4, BTN_LOC_X(0), BTN_LOC_Y(1),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "5",      GUI_ID_USER +  5, BTN_LOC_X(1), BTN_LOC_Y(1),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "6",      GUI_ID_USER +  6, BTN_LOC_X(2), BTN_LOC_Y(1),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "1",      GUI_ID_USER +  1, BTN_LOC_X(0), BTN_LOC_Y(2),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "2",      GUI_ID_USER +  2, BTN_LOC_X(1), BTN_LOC_Y(2),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "3",      GUI_ID_USER +  3, BTN_LOC_X(2), BTN_LOC_Y(2),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "0",      GUI_ID_USER +  0, BTN_LOC_X(0), BTN_LOC_Y(3),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10, BTN_LOC_X(1), BTN_LOC_Y(3),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11, BTN_LOC_X(2), BTN_LOC_Y(3),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   "Tab",    GUI_ID_USER + 12, BTN_LOC_X(0), BTN_LOC_Y(4),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 13, BTN_LOC_X(1), BTN_LOC_Y(4),  BTN_WIDTH,  BTN_HEIGHT},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 14, BTN_LOC_X(2), BTN_LOC_Y(4),  BTN_WIDTH,  BTN_HEIGHT},
};

/* Dialog resource of user dialog */
static const GUI_WIDGET_CREATE_INFO _aDialogUser[] = {
/*  Function                 Text      Id                 Px   Py   Dx   Dy */
  { FRAMEWIN_CreateIndirect, "Dialog", 0,                 40,  90, 140, 115, FRAMEWIN_CF_MOVEABLE},
  { EDIT_CreateIndirect,     0,        GUI_ID_EDIT0,      10,  10, 110,  20, 0, 12},
  { EDIT_CreateIndirect,     0,        GUI_ID_EDIT1,      10,  40, 110,  20, 0, 12},
  { BUTTON_CreateIndirect,   "Ok",     GUI_ID_OK,         10,  70,  50,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,     70,  70,  50,  20 },
};

/* Title of sample */
static char _aTitle[] = {"WIDGET_NumPad"};

/* Explanation of sample */
static char * _apExplain[] = {
  {"This sample shows how to use a numpad as input"},
  {"device. This can be usefull if no keyboard"},
  {"is available and the user should edit numeric"},
  {"values or text on a touch screen."},
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialogNumPad
*
* Purpose:
*   Callback function of the numpad.
*/
static void _cbDialogNumPad(WM_MESSAGE * pMsg) {
  GUI_RECT r;
  int i, NCode, Id, Pressed = 0;
  WM_HWIN hDlg, hItem;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetClientRect(&r);
    GUI_SetColor(0x000000);
    GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
    /* Draw the bright sides */
    GUI_SetColor(0xffffff);
    GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);   /* Draw top line */
    GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
    /* Draw the dark sides */
    GUI_SetColor(0x555555);
    GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
    GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
    break;
  case WM_INIT_DIALOG:
    for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i);
      BUTTON_SetFocussable(hItem, 0);                       /* Set all buttons non focussable */
//		BUTTON_SetSkin(hItem, BUTTON_SKIN_FLEX);
      switch (i) {
      case 13:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (pressed) */
        break;
      case 14:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (pressed) */
        break;
      }
    }
    hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + 12);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    switch (NCode) {
    case WM_NOTIFICATION_CLICKED:
      Pressed = 1;
    case WM_NOTIFICATION_RELEASED:
      if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
        int Key;
        if (Id < GUI_ID_USER + 11) {
          char acBuffer[10];
          BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
          Key = acBuffer[0];
        } else {
          Key = _aKey[Id - GUI_ID_USER - 11];                        /* Get the text from the array */
        }
        GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
      }
      break;
    }
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogUser
*
* Purpose:
*   Callback function of the user dialog.
*/
static void _cbDialogUser(WM_MESSAGE * pMsg) {
  int i, NCode, Id;
  WM_HWIN hDlg, hItem;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    for (i = 0; i < 2; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + i);  /* Get the handle of the edit widget */
      EDIT_SetText(hItem, "12345678");                   /* Set text */
    }
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    switch (NCode) {
      case WM_NOTIFICATION_RELEASED:      /* React only if released */
        if (Id == GUI_ID_OK) {            /* OK Button */
          GUI_EndDialog(hDlg, 0);
        }
        if (Id == GUI_ID_CANCEL) {        /* Cancel Button */
          GUI_EndDialog(hDlg, 1);
        }
        break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDesktop
*
* Purpose:
*   This routine handles the drawing of the desktop window.
*/
static void _cbDesktop(WM_MESSAGE * pMsg) {
  int i;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_RED);
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt(_aTitle, 160, 5);
    GUI_DispNextLine();
    GUI_SetFont(GUI_DEFAULT_FONT);
    GUI_DispNextLine();
    for (i = 0; i < GUI_COUNTOF(_apExplain); i++) {
      GUI_DispStringHCenterAt(_apExplain[i], 160, GUI_GetDispPosY());
      GUI_DispNextLine();
    }
    break;
  }
}

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
	WM_HWIN hNumPad;
	GUI_Init();
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	GUI_CURSOR_Show();
	WM_SetCallback(WM_HBKWIN, _cbDesktop);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, 
                                GUI_COUNTOF(_aDialogNumPad), 
                                _cbDialogNumPad, WM_HBKWIN, 0, 0); /* Create the numpad dialog */
	WM_SetStayOnTop(hNumPad, 1);
	while (1) {
    GUI_ExecDialogBox(_aDialogUser, 
                      GUI_COUNTOF(_aDialogUser), 
                      _cbDialogUser, WM_HBKWIN, 0, 0);             /* Execute the user dialog */
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/

