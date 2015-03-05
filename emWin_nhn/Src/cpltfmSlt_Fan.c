#include <stdio.h>
#include "devIfApp.h"
#include "DIALOG.h"
#include "LCD_constdef.h"


#define ID_WINDOW_0      (GUI_ID_USER + 0xB00)
#define ID_TEXT_0 (GUI_ID_USER + 0xB01)

#define ID_TEXT_1 (GUI_ID_USER + 0xB02)
#define ID_TEXT_2 (GUI_ID_USER + 0xB03)
#define ID_TEXT_3 (GUI_ID_USER + 0xB04)
#define ID_TEXT_4 (GUI_ID_USER + 0xB05)
#define ID_TEXT_5 (GUI_ID_USER + 0xB06)
#define ID_TEXT_6 (GUI_ID_USER + 0xB07)
#define ID_TEXT_7 (GUI_ID_USER + 0xB08)
#define ID_TEXT_8 (GUI_ID_USER + 0xB09)
#define ID_TEXT_9 (GUI_ID_USER + 0xB0A)
#define ID_TEXT_10 (GUI_ID_USER + 0xB0B)
#define ID_TEXT_11 (GUI_ID_USER + 0xB0C)
#define ID_TEXT_12 (GUI_ID_USER + 0xB0D)
#define ID_TEXT_13 (GUI_ID_USER + 0xB0E)
#define ID_TEXT_14 (GUI_ID_USER + 0xB0F)
#define ID_TEXT_15 (GUI_ID_USER + 0xB10)
#define ID_TEXT_16 (GUI_ID_USER + 0xB11)

#define ID_TEXT_17 (GUI_ID_USER + 0xB12)
#define ID_TEXT_18 (GUI_ID_USER + 0xB13)
#define ID_TEXT_19 (GUI_ID_USER + 0xB14)
#define ID_TEXT_20 (GUI_ID_USER + 0xB15)
#define ID_TEXT_21 (GUI_ID_USER + 0xB16)
#define ID_TEXT_22 (GUI_ID_USER + 0xB17)
#define ID_TEXT_23 (GUI_ID_USER + 0xB18)
#define ID_TEXT_24 (GUI_ID_USER + 0xB19)
#define ID_TEXT_25 (GUI_ID_USER + 0xB1A)
#define ID_TEXT_26 (GUI_ID_USER + 0xB1B)
#define ID_TEXT_27 (GUI_ID_USER + 0xB1C)
#define ID_TEXT_28 (GUI_ID_USER + 0xB1D)
#define ID_TEXT_29 (GUI_ID_USER + 0xB1E)
#define ID_TEXT_30 (GUI_ID_USER + 0xB1F)
#define ID_TEXT_31 (GUI_ID_USER + 0xB20)
#define ID_TEXT_32 (GUI_ID_USER + 0xB21)


#define ID_BUTTON_NEXT (GUI_ID_USER + 0xB30)
#define ID_BUTTON_LAST (GUI_ID_USER + 0xB31)



extern __insidePlantScteFans fanData;

__insidePlantScteFans * pFanData;
static int nSlot;
static WM_HWIN _hParentWin;
static int currentPage = 0; //0:默认页 1:分页1 2：分页2

//fan subpage-1
static const GUI_WIDGET_CREATE_INFO _aFanSlot_1[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 1, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Next", ID_BUTTON_NEXT, 550, 435, 100, 40, 0, 0, 0 }, //下一页  

//column1
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 40, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 40, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 40, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 40, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 40, 335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 40, 380, 225, 40, 0, 100, 0 },

//column2   
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 320, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 320, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 320, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 320, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 320, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 320, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_15, 320, 335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_16, 320, 380, 225, 40, 0, 100, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//fan subpage-2
static const GUI_WIDGET_CREATE_INFO _aFanSlot_2[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 1, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Last", ID_BUTTON_LAST, 550, 435, 100, 40, 0, 0, 0 }, //下一页  

//column1
  { TEXT_CreateIndirect, "Text", ID_TEXT_17, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_18, 40, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_19, 40, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_20, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_21, 40, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_22, 40, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_23, 40, 335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_24, 40, 380, 225, 40, 0, 100, 0 },

//column2   
  { TEXT_CreateIndirect, "Text", ID_TEXT_25, 320, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_26, 320, 110, 225, 40, 0, 100, 40},
  { TEXT_CreateIndirect, "Text", ID_TEXT_27, 320, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_28, 320, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_29, 320, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_30, 320, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_31, 320, 335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_32, 320, 380, 225, 40, 0, 100, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};


//DNOT1
static void _cbFanSlot(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
	int i;
	char buf[64];
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
	  case WM_PAINT:
		GUI_SetColor(GUI_BLUE);
		i = 50;
		GUI_FillRect(20, i, 780, i+4);  //画线
		i = 425;
		GUI_FillRect(20, i, 780, i+4); 
//		GUI_SetDrawMode(GUI_DM_XOR);
//		GUI_DrawBitmap(&bmlogo_nhn, 0, 0);  
		
		if(currentPage==1)
		{
			for(i=0;i<8;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9+i);
				sprintf(buf,"%d RPM",pFanData->heFanSpeed[i]);
			  TEXT_SetText(hItem, buf);
			}
		}
		if(currentPage==2)
		{
			for(i=0;i<8;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25+i);
				sprintf(buf,"%d mA",pFanData->heFanCurrent[i]);
			  TEXT_SetText(hItem, buf);				
			}
		}
		
		break;
		case WM_INIT_DIALOG:
    //
    // Initialization of 'Text'
    //
		

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		sprintf(buf, "Platform C / Fan");
		TEXT_SetText(hItem, buf);
		
		if(currentPage==1){
			for(i=0;i<8;i++){		
				//column1
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1+i);
				sprintf(buf,"#%d Fan Speed:",i+1);
				TEXT_SetText(hItem, buf);
				TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				TEXT_SetFont(hItem, GUI_FONT_32B_1);
				//column2
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9+i);
				TEXT_SetText(hItem, "0 RPM");
				TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				TEXT_SetFont(hItem, GUI_FONT_32B_1);
				
				
			}		
		}

		if(currentPage==2){
			for(i=0;i<8;i++){		
				//column1
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17+i);
				sprintf(buf,"#%d Fan Current:",i+1);
				TEXT_SetText(hItem, buf);
				TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				TEXT_SetFont(hItem, GUI_FONT_32B_1);
				//column2
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25+i);
				TEXT_SetText(hItem, "0 mA");
				TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				TEXT_SetFont(hItem, GUI_FONT_32B_1);
			}		
		}		
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
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
			
    case ID_BUTTON_NEXT: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:

        // USER START (Optionally insert code for reacting on notification message)
			  //进入Fan页面，第二页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 2;
			    hItem  = GUI_CreateDialogBox(_aFanSlot_2, GUI_COUNTOF(_aFanSlot_2), &_cbFanSlot, _hParentWin, 0, 0);

			    WM_MakeModal(hItem);
			    GUI_ExecCreatedDialog(hItem);	
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
			break;

    case ID_BUTTON_LAST: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:

        // USER START (Optionally insert code for reacting on notification message)
			  //进入Fan详细页面，第一页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 1;
			    hItem  = GUI_CreateDialogBox(_aFanSlot_1, GUI_COUNTOF(_aFanSlot_1), &_cbFanSlot, _hParentWin, 0, 0);

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
WM_HWIN CreateWinSlot_Fan(WM_HWIN hParant, int slt) {
	WM_HWIN hWin;
	WM_HWIN hItem;

		_hParentWin = hParant;
		nSlot = slt;
		currentPage = 1;
    pFanData = &fanData;
	  hWin = GUI_CreateDialogBox(_aFanSlot_1, GUI_COUNTOF(_aFanSlot_1), &_cbFanSlot, hParant, 0, 0);
	
///	hItem = EDIT_CreateEx(600, 2, 80, 40, hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	EDIT_SetText(hItem, "Add Man");
	
	return hWin;
}

