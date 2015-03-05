/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.12                          *
*        Compiled Jun 29 2011, 15:28:47                              *
*        (c) 2011 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "nhnTxt.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x80)
#define ID_TEXT_0   (GUI_ID_USER + 0x81)
#define ID_TEXT_1   (GUI_ID_USER + 0x82)
#define ID_TEXT_2   (GUI_ID_USER + 0x83)
#define ID_TEXT_3   (GUI_ID_USER + 0x84)
#define ID_TEXT_4   (GUI_ID_USER + 0x85)
#define ID_TEXT_5   (GUI_ID_USER + 0x86)
#define ID_TEXT_6   (GUI_ID_USER + 0x87)
#define ID_EDIT_0   (GUI_ID_USER + 0x88)
#define ID_EDIT_1   (GUI_ID_USER + 0x89)
#define ID_EDIT_2   (GUI_ID_USER + 0x8A)
#define ID_EDIT_3   (GUI_ID_USER + 0x8B)
#define ID_EDIT_4   (GUI_ID_USER + 0x8C)
#define ID_CHECKBOX_0   (GUI_ID_USER + 0x8D)
#define ID_CHECKBOX_1   (GUI_ID_USER + 0x8E)
#define ID_CHECKBOX_2   (GUI_ID_USER + 0x8F)
#define ID_CHECKBOX_3   (GUI_ID_USER + 0x90)

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
//模拟属性设置
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
#ifdef SLK_BOARD
  { FRAMEWIN_CreateIndirect, "apSet", ID_FRAMEWIN_0, 1, 0, 254, 213, 0, 0, 0 },
  { TEXT_CreateIndirect, "paramName", ID_TEXT_0, 0, 0, 100, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Current Value", ID_TEXT_1, 104, 0, 134, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtHiHi", ID_TEXT_2, 0, 32, 80, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtHi", ID_TEXT_3, 0, 57, 80, 20, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtLo", ID_TEXT_4, 3, 81, 80, 20, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtLoLo", ID_TEXT_5, 0, 103, 80, 20, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtDB", ID_TEXT_6, 0, 130, 80, 20, 0, 0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 54, 32, 80, 20, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 54, 53, 80, 20, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 54, 79, 80, 20, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 54, 104, 80, 20, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 54, 128, 80, 20, 0, 100, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_0, 145, 32, 80, 20, 0, 0, 0 },
/*  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_1, 145, 58, 80, 20, 0, 0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_2, 142, 78, 80, 20, 0, 0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_3, 144, 106, 80, 20, 0, 0, 0 },*/
  { BUTTON_CreateIndirect, "OK", GUI_ID_OK, 38, 162, 80, 20, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Cancel", GUI_ID_CANCEL, 130, 161, 80, 20, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
#else
  { FRAMEWIN_CreateIndirect, "apSet", ID_FRAMEWIN_0, 400, 90, 260, 300, FRAMEWIN_CF_MOVEABLE, 0, 0 },
  { TEXT_CreateIndirect, "paramName", ID_TEXT_0, 0, 0, 100, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Current Value", ID_TEXT_1, 104, 0, 134, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtHiHi", ID_TEXT_2, 5, 40, 80, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtHi", ID_TEXT_3, 5, 75, 80, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtLo", ID_TEXT_4, 5, 110, 80, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtLoLo", ID_TEXT_5, 5, 145, 80, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "lmtDB", ID_TEXT_6, 5, 180, 80, 30, 0, 0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 60, 40, 80, 30, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 60, 75, 80, 30, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 60, 110, 80, 30, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 60, 145, 80, 30, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 60, 180, 80, 30, 0, 100, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_0, 150, 46, 30, 30, 0, 0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_1, 150, 82, 30, 30, 0, 0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_2, 150, 117, 30, 30, 0, 0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_3, 150, 152, 30, 30, 0, 0, 0 },
  { BUTTON_CreateIndirect, "OK", GUI_ID_OK, 10, 225, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Cancel", GUI_ID_CANCEL, 136, 225, 100, 40, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
#endif
};
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
//	hItem = pMsg->hWin;
//	FRAMEWIN_SetFont(hItem, GUI_FONT_24B_ASCII);
   //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "123");
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "456");
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, "123");
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EDIT_SetText(hItem, "123");
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_4);
    EDIT_SetText(hItem, "123");
    //
    // Initialization of 'Checkbox'
    //
/*	hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "Check");
    //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "Check");
    //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
    CHECKBOX_SetText(hItem, "Check");
    //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
    CHECKBOX_SetText(hItem, "Check");*/
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_3: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_4: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_0: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_1: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_2: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_3: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
	case GUI_ID_OK:
	case GUI_ID_CANCEL:
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
		GUI_EndDialog(pMsg->hWin, 0);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
	}
	break;
 // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       Create模拟属性设置
*/
WM_HWIN CreateApSet(WM_HWIN hParant, const char * pTitle) 
{
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, hParant, 1, 0); //WM_HBKWIN
	FRAMEWIN_SetText(hWin, "Analog Property");
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
