#include <stdio.h>
#include "devIfApp.h"
#include "DIALOG.h"
#include "LCD_constdef.h"



#define ID_WINDOW_0 (GUI_ID_USER + 0x10)
#define ID_WINDOW_1 (GUI_ID_USER + 0x11)
#define ID_WINDOW_2 (GUI_ID_USER + 0x12)

#define ID_TEXT_0 (GUI_ID_USER + 0x101)
#define ID_TEXT_1 (GUI_ID_USER + 0x102)
#define ID_TEXT_2 (GUI_ID_USER + 0x103)
#define ID_TEXT_3 (GUI_ID_USER + 0x104)
#define ID_TEXT_4 (GUI_ID_USER + 0x105)
#define ID_TEXT_5 (GUI_ID_USER + 0x107)
#define ID_TEXT_6 (GUI_ID_USER + 0x108)
#define ID_TEXT_7 (GUI_ID_USER + 0x109)
#define ID_TEXT_8 (GUI_ID_USER + 0x10A)
#define ID_TEXT_9 (GUI_ID_USER + 0x10B)
#define ID_TEXT_10 (GUI_ID_USER + 0x10C)
#define ID_TEXT_11 (GUI_ID_USER + 0x10D)
#define ID_TEXT_12 (GUI_ID_USER + 0x10E)
#define ID_TEXT_13 (GUI_ID_USER + 0x10F)


//for page2
#define ID_TEXT_14 (GUI_ID_USER + 0x110)
#define ID_TEXT_15 (GUI_ID_USER + 0x111)
#define ID_TEXT_16 (GUI_ID_USER + 0x112)
#define ID_TEXT_17 (GUI_ID_USER + 0x113)
#define ID_TEXT_18 (GUI_ID_USER + 0x114)
#define ID_TEXT_19 (GUI_ID_USER + 0x115)
#define ID_TEXT_20 (GUI_ID_USER + 0x116)
#define ID_TEXT_21 (GUI_ID_USER + 0x117)
#define ID_TEXT_22 (GUI_ID_USER + 0x118)
#define ID_TEXT_23 (GUI_ID_USER + 0x119)
#define ID_TEXT_24 (GUI_ID_USER + 0x120)
#define ID_TEXT_25 (GUI_ID_USER + 0x121)



#define ID_BUTTON_MORE (GUI_ID_USER + 0x1FD)
#define ID_BUTTON_NEXT (GUI_ID_USER + 0x1FE)
#define ID_BUTTON_LAST (GUI_ID_USER + 0x1FF)

#define ID_BUTTON_0 (GUI_ID_USER + 0x200)
#define ID_BUTTON_1 (GUI_ID_USER + 0x201)
#define ID_BUTTON_2 (GUI_ID_USER + 0x202)
#define ID_BUTTON_3 (GUI_ID_USER + 0x203)

//for page2
#define ID_BUTTON_4 (GUI_ID_USER + 0x204)
#define ID_BUTTON_5 (GUI_ID_USER + 0x205)
#define ID_BUTTON_6 (GUI_ID_USER + 0x206)
#define ID_BUTTON_7 (GUI_ID_USER + 0x207)




static int nSlot;
static WM_HWIN _hParentWin;
static int currentPage = 0; //0:默认页 1:分页1 2：分页2
extern __heSCTEOR orData;
__heSCTEOR * pORData;

static const GUI_WIDGET_CREATE_INFO _aORSlot[] = {
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
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 320, 215, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 320, 165, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 320, 265, 150, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 500, 115, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_MORE, 407, 330, 215, 35, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//OR subPage-1
static const GUI_WIDGET_CREATE_INFO _aORSlot_1[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_1, 1, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Next", ID_BUTTON_NEXT, 550, 435, 100, 40, 0, 0, 0 }, //下一页  
//Column 1
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 40, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 40, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 40, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 40,290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 40,335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 40,380, 225, 40, 0, 100, 0 },


//Column 2
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 320, 65, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 320, 110, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 320, 155, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 320, 200, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 320, 245, 150, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 320, 290, 120, 40, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 320, 335, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 320, 380, 120, 40, 0, 0, 0 },
	
//Column 3
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 500, 110, 120, 40, 0, 0, 0 },

  // USER START (Optionally insert additional widgets)
  // USER END
};


//OR subpage-2
static const GUI_WIDGET_CREATE_INFO _aORSlot_2[] = {
	
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_2, 1, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "LAST", ID_BUTTON_LAST, 550, 435, 100, 40, 0, 0, 0 }, //下一页  
//Column 1
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_15, 40, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_16, 40, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_17, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_18, 40, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_19, 40,290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_20, 40,335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_21, 40,380, 225, 40, 0, 100, 0 },

//Column 2
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 320, 65, 120, 40, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_22, 320, 110, 150, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 320, 155, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 320, 200, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 320, 245, 120, 40, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_23, 320, 290, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_24, 320, 335, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_25, 320, 380, 150, 40, 0, 100, 0 },


};

static void _cbORSlot(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int Id, NCode, i;
	char buf[64];
	
	switch (pMsg->MsgId) {
	case WM_PAINT:
		GUI_SetColor(GUI_BLUE);
		i = 50;
		GUI_FillRect(20, i, 780, i+4);  
		i = 425;
		GUI_FillRect(20, i, 780, i+4); 
//		GUI_SetDrawMode(GUI_DM_XOR);
//		GUI_DrawBitmap(&bmlogo_nhn, 0, 0);  
	if(currentPage ==0 || currentPage==1)
	{
					//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);//nominal power
      sprintf(buf, "%d mW", 10);
			TEXT_SetText(hItem, buf);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7); //output power
      sprintf(buf, "%d mW", pORData->heOpRxOutputPower[0]); 
			TEXT_SetText(hItem, buf);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);//wave length
      sprintf(buf, "%d nm", pORData->heOpRxInputWavelengthControl[0]);
			TEXT_SetText(hItem, buf);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9); //output att
      sprintf(buf,"%d dB", 1);
			TEXT_SetText(hItem, buf);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10); //agc/mgc
      sprintf(buf,"%s", (pORData->heOpRxOutputGainType[0]==1)?"AGC":"MGC");
			TEXT_SetText(hItem, buf);
		
	}
	
	if(currentPage == 1)
	{
	}
	else if(currentPage ==2)
	{
	}
	
	
	
		break;
	case WM_INIT_DIALOG:
		
		if(currentPage ==0 || currentPage==1)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			sprintf(buf, "Platform C / Slot %d: RCV", nSlot+1);
			TEXT_SetText(hItem, buf);
	//		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
	//		BUTTON_SetText(hItem, "S\r\nl\r\no\r\nt\r\n\r\n 1");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetText(hItem, "Nominal Power:");
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Output Power:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Wave Length");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Output Att:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "AGC/MGC:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "11 mW");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "11.4 mW");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetTextColor(hItem, 0x00000000);
			TEXT_SetText(hItem, "2 dB");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "1310 nm");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "AGC");
		}	
		if(currentPage==1){
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Output Switch:");

    //
    // Initialization of 'Text'
    //
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "3State:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "EQ:");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "On");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "1");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "2 dB");
	  }
		if(currentPage==2){
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Output Bias:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_15);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "AB Sw State:");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_16);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "AB Sw Control:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Help:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_18);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Restore Default:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_19);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Serial Num:");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_20);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Hardware Rev:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_21);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Firmware Rev:");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_22);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "On");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_23);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "20130001");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_24);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "V1.0");
			
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "FW13001A-1391");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
			
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
		}
		//
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Normal");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MORE);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "More...");
		

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END		
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
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
			
    case ID_BUTTON_4: // Notifications sent by 'Button'
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

    case ID_BUTTON_5: // Notifications sent by 'Button'
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
			
    case ID_BUTTON_NEXT: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:

        // USER START (Optionally insert code for reacting on notification message)
			  //进入OR详细页面，第二页
					GUI_EndDialog(pMsg->hWin, 0);
			    currentPage = 2;
			    hItem  = GUI_CreateDialogBox(_aORSlot_2, GUI_COUNTOF(_aORSlot_2), &_cbORSlot, _hParentWin, 0, 0);
//			    WM_MakeModal(hItem);
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
			  //进入OR详细页面，第二页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 1;
			    hItem  = GUI_CreateDialogBox(_aORSlot_1, GUI_COUNTOF(_aORSlot_1), &_cbORSlot, _hParentWin, 0, 0);
//			    WM_MakeModal(hItem);
//				WM_SetFocus(hItem);
			    GUI_ExecCreatedDialog(hItem);	
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
			break;
			
    case ID_BUTTON_6: // Notifications sent by 'Button'
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
			
    case ID_BUTTON_MORE: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER START (Optionally insert code for reacting on notification message)
			  //进入OR详细页面，第一页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 1;
			    hItem  = GUI_CreateDialogBox(_aORSlot_1, GUI_COUNTOF(_aORSlot_1), &_cbORSlot, _hParentWin, 0, 0);
//			    WM_MakeModal(hItem);
			    GUI_ExecCreatedDialog(hItem);
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;			
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}




extern char slotType[];
WM_HWIN CreateWinSlot_OR(WM_HWIN hParant, int slt) {
	WM_HWIN hWin;
	WM_HWIN hItem;

	_hParentWin = hParant;
	nSlot = slt;
	currentPage = 0;
	hWin = GUI_CreateDialogBox(_aORSlot, GUI_COUNTOF(_aORSlot), &_cbORSlot, hParant, 0, 0);

	pORData = &orData;
///	hItem = EDIT_CreateEx(600, 2, 80, 40, hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	EDIT_SetText(hItem, "Add Man");
	
	return hWin;
}

