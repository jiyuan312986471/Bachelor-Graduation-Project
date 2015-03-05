#include <stdio.h>
#include "devIfApp.h"
#include "DIALOG.h"
#include "LCD_constdef.h"

extern __insidePlantBB chassisData;

 __insidePlantBB* pChassisData;
 
#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_TEXT_0     (GUI_ID_USER + 0x01)
#define ID_TEXT_1     (GUI_ID_USER + 0x02)
#define ID_TEXT_2     (GUI_ID_USER + 0x03)
#define ID_TEXT_3     (GUI_ID_USER + 0x04)
#define ID_TEXT_4     (GUI_ID_USER + 0x05)
#define ID_TEXT_5     (GUI_ID_USER + 0x07)
#define ID_TEXT_6     (GUI_ID_USER + 0x08)
#define ID_TEXT_7     (GUI_ID_USER + 0x09)
#define ID_TEXT_8     (GUI_ID_USER + 0x0A)
#define ID_TEXT_9     (GUI_ID_USER + 0x0B)
#define ID_BUTTON_0     (GUI_ID_USER + 0x0D)
#define ID_TEXT_10     (GUI_ID_USER + 0x0E)
#define ID_TEXT_11     (GUI_ID_USER + 0x0F)
#define ID_TEXT_12     (GUI_ID_USER + 0x10)
#define ID_TEXT_13     (GUI_ID_USER + 0x11)
#define ID_TEXT_14     (GUI_ID_USER + 0x12)
static int nSlot;

static const GUI_WIDGET_CREATE_INFO _aChassisCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 1, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 40, 115, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 40, 165, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 40, 215, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 40, 265, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 320, 65, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 320, 115, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 320, 215, 250, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 320, 165, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 320, 265, 250, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 500, 165, 120, 40, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 40, 315, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 40, 365, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 320, 315, 250, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 320, 365, 225, 40, 0, 100, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};


static void _cbChassis(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode,i;
  // USER START (Optionally insert additional variables)
  // USER END
	char buf[64];
  switch (pMsg->MsgId) {
		
	case WM_PAINT:
		GUI_SetColor(GUI_BLUE);
		i = 50;
		GUI_FillRect(20, i, 780, i+4);  //画线
		i = 425;
		GUI_FillRect(20, i, 780, i+4); 
//		GUI_SetDrawMode(GUI_DM_XOR);
//		GUI_DrawBitmap(&bmlogo_nhn, 0, 0);  
	
	 //变量在WM_PAINT中更新
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
	  sprintf(buf,"%d C",pChassisData->devTemp);
    TEXT_SetText(hItem, buf);	

		break;
	
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Text'
    //
	  //常量在WM_INIT中实现
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		sprintf(buf, "Platform C / Information");
		TEXT_SetText(hItem, buf);
	
	
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "Name:");
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Model:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Temperature:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Hardware Rev:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Firmware Rev:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Platform C");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "NHNOPPF40");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, 0x00000000);
    TEXT_SetText(hItem, "09013A-1233");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "27C");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "FW12013A1-1245");
		
		
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Normal");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_GREEN);

    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetText(hItem, "Software Rev:");
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "SerialNum:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "V4.4");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "201300001");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
			
		case GUI_ID_OK:
		case GUI_ID_CANCEL:
			switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					GUI_EndDialog(pMsg->hWin, 0);
					break;
			}
			break;
			
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				memcpy(buf,"Temperature",20);
			  hItem = CreateSetAP(pMsg->hWin, buf, -1 ,0);
			  WM_MakeModal(hItem);
			  GUI_ExecCreatedDialog(hItem);	
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
WM_HWIN CreateWin_Chassis(WM_HWIN hParant) {
	WM_HWIN hWin;
//	WM_HWIN hItem;

    pChassisData = &chassisData;

	  hWin = GUI_CreateDialogBox(_aChassisCreate, GUI_COUNTOF(_aChassisCreate), &_cbChassis, hParant, 0, 0);
		
	
///	hItem = EDIT_CreateEx(600, 2, 80, 40, hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	EDIT_SetText(hItem, "Add Man");
	
	return hWin;
}

