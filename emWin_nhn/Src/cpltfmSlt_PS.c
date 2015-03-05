#include <stdio.h>
#include "devIfApp.h"
#include "DIALOG.h"
#include "LCD_constdef.h"



extern __insidePlantSctePs   ps1Data;
extern __insidePlantSctePs   ps2Data;

__insidePlantSctePs *  pPsData;

#define ID_WINDOW_0 (GUI_ID_USER + 0xA00)
#define ID_TEXT_0 (GUI_ID_USER + 0xA01)
#define ID_TEXT_1 (GUI_ID_USER + 0xA02)
#define ID_TEXT_2 (GUI_ID_USER + 0xA03)
#define ID_TEXT_3 (GUI_ID_USER + 0xA04)
#define ID_TEXT_4 (GUI_ID_USER + 0xA05)
#define ID_TEXT_5 (GUI_ID_USER + 0xA07)
#define ID_TEXT_6 (GUI_ID_USER + 0xA08)
#define ID_TEXT_7 (GUI_ID_USER + 0xA09)
#define ID_TEXT_8 (GUI_ID_USER + 0xA0A)
#define ID_TEXT_9 (GUI_ID_USER + 0xA0B)
#define ID_TEXT_10 (GUI_ID_USER + 0xA0C)
#define ID_TEXT_11 (GUI_ID_USER + 0xA0D)
#define ID_TEXT_12 (GUI_ID_USER + 0xA0E)
#define ID_TEXT_13 (GUI_ID_USER + 0xA0F)
#define ID_TEXT_14 (GUI_ID_USER + 0xA10)
#define ID_BUTTON_0 (GUI_ID_USER + 0xA11)
#define ID_BUTTON_1 (GUI_ID_USER + 0xA12)
#define ID_BUTTON_2 (GUI_ID_USER + 0xA13)
#define ID_BUTTON_3 (GUI_ID_USER + 0xA14)

static int nSlot;

static const GUI_WIDGET_CREATE_INFO _aPSCreate[] = {
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
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 40, 315, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 40, 365, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 320, 315, 250, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 320, 365, 225, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 500, 65, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 500, 115, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 500, 165, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 500, 215, 120, 40, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//DNOT1
static void _cbPSSlot(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int Id, NCode, i;
	char buf[64];
	
	switch (pMsg->MsgId) {
	case WM_PAINT:
		GUI_SetColor(GUI_BLUE);
		i = 50;
		GUI_FillRect(20, i, 780, i+4);  //»­Ïß
		i = 425;
		GUI_FillRect(20, i, 780, i+4); 
//		GUI_SetDrawMode(GUI_DM_XOR);
//		GUI_DrawBitmap(&bmlogo_nhn, 0, 0);  
	
	    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
	  sprintf(buf,"%3.1f V",pPsData->hePsOutputVoltage[0]*0.1f);
    TEXT_SetText(hItem, buf);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
	  sprintf(buf,"%3.1f V",pPsData->hePsOutputVoltage[1]*0.1f);
    TEXT_SetText(hItem, buf);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
	  sprintf(buf,"%3.1f mA",pPsData->hePsOutputCurrent[0]);
    TEXT_SetText(hItem, buf);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
	  sprintf(buf,"%3.1f V",pPsData->hePsOutputVoltage[2]*0.1);
    TEXT_SetText(hItem, buf);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
	  sprintf(buf,"%d RPM",pPsData->hePsFanSpeed1);
    TEXT_SetText(hItem, buf);


    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
	  sprintf(buf,"%d RPM",pPsData->hePsFanSpeed2);
    TEXT_SetText(hItem, buf);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
	  sprintf(buf,"%d C",pPsData->hePsInterTemp);
    TEXT_SetText(hItem, buf);

	
	
		break;
	case WM_INIT_DIALOG:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		sprintf(buf, "Platform C / Slot %d: Power Supply", nSlot+1);
		TEXT_SetText(hItem, buf);
//		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
//		BUTTON_SetText(hItem, "S\r\nl\r\no\r\nt\r\n\r\n 1");


		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "DC Voltage 24V:");
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "DV Voltage -5V:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "DC Voltage 5V:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Current 24V:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Fan Speed1:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "24.2 V");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "-5.1 V");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, 0x00000000);
    TEXT_SetText(hItem, "125 mA");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "5.1 V");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "2000 RPM");

    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetText(hItem, "Fan Speed2:");
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Internal Temp");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "1900 RPM");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "27");

    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Normal");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);

    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Normal");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Warning");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Normal");
		break;

case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
/*		case ID_BUTTON_0: // Notifications sent by 'Power 1'
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;*/
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
				memcpy(buf,"DC Voltage 24V",20);
				hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,0);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);	 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				memcpy(buf,"DC Voltage -5V",20);
				hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,1);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);	 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				memcpy(buf,"DC Voltage 5V",20);
				hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,2);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);	 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				memcpy(buf,"Current 24V",20);
				hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,3);
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
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}


extern char slotType[];
WM_HWIN CreateWinSlot_PS(WM_HWIN hParant, int slt) {
	WM_HWIN hWin;
	WM_HWIN hItem;

		nSlot = slt;
    if(nSlot==16) pPsData = &ps1Data;
	  else pPsData = &ps2Data;
	  hWin = GUI_CreateDialogBox(_aPSCreate, GUI_COUNTOF(_aPSCreate), &_cbPSSlot, hParant, 0, 0);
		
	
///	hItem = EDIT_CreateEx(600, 2, 80, 40, hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	EDIT_SetText(hItem, "Add Man");
	
	return hWin;
}

