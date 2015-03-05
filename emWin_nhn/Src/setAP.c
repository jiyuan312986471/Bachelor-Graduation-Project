/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.16                          *
*        Compiled Jun  4 2012, 15:48:59                              *
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
#include "LCD_constdef.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_TEXT_0   (GUI_ID_USER + 0x01)
#define ID_TEXT_1   (GUI_ID_USER + 0x02)
#define ID_TEXT_2   (GUI_ID_USER + 0x03)
#define ID_TEXT_3   (GUI_ID_USER + 0x04)
#define ID_TEXT_4   (GUI_ID_USER + 0x05)
#define ID_TEXT_5   (GUI_ID_USER + 0x06)
#define ID_TEXT_6   (GUI_ID_USER + 0x07)
#define ID_TEXT_7   (GUI_ID_USER + 0x08)
#define ID_TEXT_8   (GUI_ID_USER + 0x09)
#define ID_TEXT_9   (GUI_ID_USER + 0x0A)
#define ID_TEXT_10   (GUI_ID_USER + 0x0B)
#define ID_TEXT_11   (GUI_ID_USER + 0x0C)
#define ID_TEXT_12   (GUI_ID_USER + 0x0D)
#define ID_TEXT_13   (GUI_ID_USER + 0x0E)
#define ID_TEXT_14   (GUI_ID_USER + 0x0F)
#define ID_BUTTON_0   (GUI_ID_USER + 0x11)
#define ID_RADIO_0   (GUI_ID_USER + 0x13)

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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 280, 50, 420, 350, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 10, 10, 200, 35, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 10, 51, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 10, 90, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 10, 130, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 10, 170, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 10, 210, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 170, 50, 80, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 170, 90, 60, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 170, 130, 60, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 170, 170, 60, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 170, 210, 60, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 240, 90, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 240, 130, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 240, 170, 150, 30, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 240, 210, 150, 30, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 250, 250, 120, 40, 0, 0, 0 },
///  { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 240, 9, 80, 60, 0, 5122, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
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
		
	  //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_16B_1);
    FRAMEWIN_SetTitleHeight(hItem, 20);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Output Power");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Current Value:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "HIHI:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "HI:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "LO:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "LOLO:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "0");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "100");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "80");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "30");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "10");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "AlarmEnable");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "AlarmDisable");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "AlarmEnable");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "AlarmDisable");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "OK");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
    //
    // Initialization of 'Radio'
    //
		//Radio 不一直创建
 ///   hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
 ///   RADIO_SetFont(hItem, GUI_FONT_20B_1);
 ///   RADIO_SetText(hItem, "mW", 0);
///    RADIO_SetText(hItem, "dBm", 1);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
					GUI_EndDialog(pMsg->hWin, 0);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_0: // Notifications sent by 'Radio'
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
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}


extern char slotType[];

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/

WM_HWIN CreateSetAP(WM_HWIN hParant, const char * pParam, int slot, int apIndex) {
  WM_HWIN hWin;
  WM_HWIN hItem;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
	FRAMEWIN_SetBorderSize(hWin, 5);
	FRAMEWIN_SetFont(hWin, GUI_FONT_20_1);
	FRAMEWIN_SetText(hWin, "Analog Property");
	FRAMEWIN_SetTitleHeight(hWin, 30);
	
//	FRAMEWIN_SetMoveable(hWin, 1);
//	FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
	if(slot==-1)//Chassis
	{
		
	}
	if(slotType[slot]==devID_DNOT1 || slotType[slot]==devID_DNOT2)
	{
		if(apIndex==0)//ot第一个为output power 
		{
			//显示 mw/dBm
			hItem = RADIO_CreateEx(240, 40, 100, 80, hWin, WM_CF_SHOW, 0, ID_RADIO_0, 2, 30);
      RADIO_SetFont(hItem, GUI_FONT_24B_1);
      RADIO_SetText(hItem, "mW", 0);
      RADIO_SetText(hItem, "dBm", 1);
		}
	}
	hItem = WM_GetDialogItem(hWin, ID_TEXT_0);
	TEXT_SetText(hItem, pParam);
	
	//Get from APSet
	//Set HH,H,L,LL,Alarm State TEXT 
	
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
