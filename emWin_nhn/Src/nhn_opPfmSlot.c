/* slots information show routine for NHN HFC optical platform V3.0 
   filename: nhn_opPfmSlot.c
 */

#include <stddef.h>
#include <string.h>
#include "GUI.h"
#include "DIALOG.h"

#include "LISTVIEW.h"
#include "FRAMEWIN.h"
#include "nhnTxt.h"

WM_HWIN CreateApSet(WM_HWIN hParant, const char * pTitle);

#ifdef FONT_IN_FLASH
	#ifdef SLK_BOARD
		#define acST_GB231224 0x90000000
	#else
		#define acST_GB231224 0x90000000
		#define aclogo_jpg 0x90096691
	#endif
#else
	extern const unsigned char acST_GB231224[];
	extern const unsigned char aclogo[];
	extern const unsigned char aclogo_jpg[];
#endif

#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_LISTVIEW_0   (GUI_ID_USER + 0x01)
#define ID_BT_PRE   (GUI_ID_USER + 0x02)
#define ID_BT_NXT   (GUI_ID_USER + 0x03)
#define ID_BT_RET   (GUI_ID_USER + 0x04)
#define ID_TEXT_0   (GUI_ID_USER + 0x05)

#define ID_UPDATE_RC (GUI_ID_USER + 0x1111)

const GUI_ConstString strR1[] = {
	str_opPwr, "10mW"
};
const GUI_ConstString strR2[] = {
	str_nAlarm, "2"
};
const GUI_ConstString strR3[] = {
	str_outOP, "10.52mW"
};
const GUI_ConstString strR4[] = {
	str_laserBias, "58.2mA"
};
const GUI_ConstString strR5[] = {
	str_laserTemp, "25.1"
};
const GUI_ConstString strR6[] = {
	str_laserCool, "0.321A"
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
#ifdef SLK_BOARD
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 272, 0, 0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 0, 26, 473, 174, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_prePage, ID_BT_PRE, 205, 225, 80, 20, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_nextPage, ID_BT_NXT, 300, 225, 80, 20, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_return, ID_BT_RET, 389, 225, 80, 20, 0, 0, 0 },
  { TEXT_CreateIndirect, str_ModuleInfo, ID_TEXT_0, 0, 0, 480, 30, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
#else
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 800, 480, 0, 0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 10, 30, 780, 370, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_prePage, ID_BT_PRE, 450, 420, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_nextPage, ID_BT_NXT, 570, 420, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, str_return, ID_BT_RET, 680, 420, 100, 40, 0, 0, 0 },
  { TEXT_CreateIndirect, str_ModuleInfo, ID_TEXT_0, 0, 0, 800, 30, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
#endif
};

GUI_FONT ftSIF;
I32 rcFree, rcUsed;
int CurSel;

static void _MessageBox(const char* pText, const char* pCaption) {
  WM_HWIN hWin;
  hWin = MESSAGEBOX_Create(pText, pCaption, 0);
  WM_MakeModal(hWin);
  GUI_ExecCreatedDialog(hWin);
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	char swBuf[256];
	WM_HWIN hItem;
	HEADER_Handle lvHeader;
	int Id, NCode;
	int CurSel_bk, NumItems;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case ID_UPDATE_RC:
      WM_InvalidateWindow(pMsg->hWin);	  
	  break;
  case WM_PAINT:
	GUI_SetColor(GUI_BLUE);	  
	GUI_DispHexAt(rcFree, 0, 400, 8);	  
	GUI_DispHexAt(rcUsed, 120, 400, 8);	  
	break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	WM_EnableMemdev(hItem);
    LISTVIEW_AddColumn(hItem, 300, "Col 0", GUI_TA_LEFT | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 180, "Col 1", GUI_TA_LEFT | GUI_TA_VCENTER);
//	LISTVIEW_SetTextAlign(hItem, 0, GUI_TA_LEFT | GUI_TA_VCENTER);
//	LISTVIEW_SetTextAlign(hItem, 1, GUI_TA_LEFT | GUI_TA_VCENTER);
//    LISTVIEW_AddColumn(hItem, 30, "Col 2", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, strR1);
    LISTVIEW_AddRow(hItem, strR2);
    LISTVIEW_AddRow(hItem, strR3);
    LISTVIEW_AddRow(hItem, strR4);
    LISTVIEW_AddRow(hItem, strR5);
    LISTVIEW_AddRow(hItem, strR6);
    LISTVIEW_AddRow(hItem, strR1);
    LISTVIEW_AddRow(hItem, strR2);
    LISTVIEW_AddRow(hItem, strR3);
    LISTVIEW_AddRow(hItem, strR4);
    LISTVIEW_AddRow(hItem, strR5);
    LISTVIEW_AddRow(hItem, strR6);
    LISTVIEW_SetGridVis(hItem, 0);
	LISTVIEW_SetHeaderHeight(hItem, 0);
//    LISTVIEW_SetFont(hItem, GUI_FONT_24_1);
    LISTVIEW_SetFont(hItem, &ftSIF);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, &ftSIF);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
//	lvHeader = LISTVIEW_GetHeader(hItem);
//	WM_HideWindow(lvHeader);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
		  
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		NumItems = LISTVIEW_GetNumRows(hItem);
		CurSel_bk = CurSel;
		CurSel   = LISTVIEW_GetSel(hItem);
		if (CurSel_bk!=CurSel) break;
		if ((CurSel >= 0) && (CurSel < NumItems)) {
			LISTVIEW_GetItemText(hItem, 0, CurSel, swBuf, sizeof(swBuf));
			hItem = CreateApSet(pMsg->hWin, swBuf);
			WM_MakeModal(hItem);
			GUI_ExecCreatedDialog(hItem);			
		}
//        WM_SetFocus(hItem);
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BT_PRE: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BT_NXT: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BT_RET: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
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

float outOpPwr;
void updateParam(WM_HWIN hWin)
{
	WM_HWIN hItem;
	char newVal[32];
	
    hItem = WM_GetDialogItem(hWin, ID_LISTVIEW_0);
	outOpPwr += 0.1;
	if (outOpPwr>15.0) outOpPwr = 10.0;
	sprintf(newVal, "%5.2fmW", outOpPwr);
	LISTVIEW_SetItemText(hItem, 1, 2, newVal);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN CreateWindow(void);
WM_HWIN CreateWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

void MainTask(void) 
{
	int count;
	WM_HWIN hWin;
	
	count =0;
	outOpPwr = 10.0;
	WM_EnableMemdev(WM_HBKWIN);
	WM_SetCreateFlags(WM_CF_MEMDEV);	// WM_CF_MEMDEV_ON_REDRAW
	GUI_Init();
	rcFree = GUI_ALLOC_GetNumFreeBytes();
	rcUsed = GUI_ALLOC_GetNumUsedBytes();
//	WM_EnableMemdev(WM_HBKWIN);
//	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
 	GUI_UC_SetEncodeUTF8();	
	GUI_SIF_CreateFont((const void*)acST_GB231224, &ftSIF, GUI_SIF_TYPE_PROP_EXT);
	
	GUI_CURSOR_Show();
	GUI_SetDefaultFont(&ftSIF);
	FRAMEWIN_SetDefaultFont(&ftSIF);
	BUTTON_SetDefaultFont(&ftSIF);
//	GUI_PNG_Draw(aclogo, 86765, 0, 0);
//	GUI_GIF_Draw(aclogo, 86765, 0, 0);
	GUI_JPEG_Draw((const void*)aclogo_jpg, 47538, 0, 0);
	GUI_Delay(2000);
	hWin = CreateWindow();
//	WM_EnableMemdev(hWin);
	while (1) {
		GUI_Delay(100);
		rcFree = GUI_ALLOC_GetNumFreeBytes();
		rcUsed = GUI_ALLOC_GetNumUsedBytes();
		if (count++ >5) {
			count =0;
			updateParam(hWin);
		}
		WM_InvalidateWindow(hWin);
	}		
}
