
#include "DIALOG.h"
#include "LCD_constdef.h"

#define ID_WIN     (GUI_ID_USER + 0x98)
#define ID_WIN_1   (GUI_ID_USER + 0x99)
#define ID_WIN_2   (GUI_ID_USER + 0x100)
#define ID_TEXT_0  (GUI_ID_USER + 0x101)
#define ID_TEST  	(GUI_ID_USER + 0x102)

#define ID_TEXT_1 (GUI_ID_USER + 0x103)
#define ID_TEXT_2 (GUI_ID_USER + 0x104)
#define ID_TEXT_3 (GUI_ID_USER + 0x105)
#define ID_TEXT_4 (GUI_ID_USER + 0x106)
#define ID_TEXT_5 (GUI_ID_USER + 0x107)
#define ID_TEXT_6 (GUI_ID_USER + 0x108)
#define ID_TEXT_7 (GUI_ID_USER + 0x109)
#define ID_TEXT_8 (GUI_ID_USER + 0x10A)
#define ID_TEXT_9 (GUI_ID_USER + 0x10B)
#define ID_TEXT_10 (GUI_ID_USER + 0x10C)
#define ID_TEXT_11 (GUI_ID_USER + 0x10D)
#define ID_TEXT_12 (GUI_ID_USER + 0x10E)
#define ID_TEXT_13 (GUI_ID_USER + 0x10F)
#define ID_TEXT_14 (GUI_ID_USER + 0x110)
#define ID_TEXT_15 (GUI_ID_USER + 0x111)
#define ID_TEXT_16 (GUI_ID_USER + 0x112)

//for sub page 2
#define ID_TEXT_17 (GUI_ID_USER + 0x113)
#define ID_TEXT_18 (GUI_ID_USER + 0x114)
#define ID_TEXT_19 (GUI_ID_USER + 0x115)
#define ID_TEXT_20 (GUI_ID_USER + 0x116)
#define ID_TEXT_21 (GUI_ID_USER + 0x117)
#define ID_TEXT_22 (GUI_ID_USER + 0x118)
#define ID_TEXT_23 (GUI_ID_USER + 0x119)
#define ID_TEXT_24 (GUI_ID_USER + 0x120)
#define ID_TEXT_25 (GUI_ID_USER + 0x121)
#define ID_TEXT_26 (GUI_ID_USER + 0x122)



#define ID_BUTTON_0 (GUI_ID_USER + 0x12D)
#define ID_BUTTON_1 (GUI_ID_USER + 0x12E)
#define ID_BUTTON_2 (GUI_ID_USER + 0x12F)
#define ID_BUTTON_3 (GUI_ID_USER + 0x130)
#define ID_BUTTON_MORE (GUI_ID_USER + 0x131)
#define ID_BUTTON_5 (GUI_ID_USER + 0x132)
#define ID_BUTTON_6 (GUI_ID_USER + 0x133)

//for sub page 2

#define ID_BUTTON_7 (GUI_ID_USER + 0x140)
#define ID_BUTTON_8 (GUI_ID_USER + 0x141)
#define ID_BUTTON_9 (GUI_ID_USER + 0x142)
#define ID_BUTTON_10 (GUI_ID_USER + 0x143)

#define ID_RADIO_0     (GUI_ID_USER + 0x145)

static WM_HWIN _hParentWin;
static int currentPage = 0; //0:默认页 1:分页1 2：分页2
static int nSlot;

//TX 默认页面，显示主要参数
static const GUI_WIDGET_CREATE_INFO _aFtxSlot[] = {
  { WINDOW_CreateIndirect, "Slot", ID_WIN, 0, 0, 800, 480, 0, 0, 0 },
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
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 500, 165, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 500, 215, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 500, 265, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_MORE, 407, 330, 215, 35, 0, 0, 0 },
//  { BUTTON_CreateIndirect, "Cancel", GUI_ID_CANCEL, 130, 161, 80, 20, 0, 0, 0 },
};

//分页1
static const GUI_WIDGET_CREATE_INFO _aFtxSlot_1[] = {
  { WINDOW_CreateIndirect, "Slot", ID_WIN_1, 0, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Next", ID_BUTTON_5, 550, 435, 100, 40, 0, 0, 0 }, //下一页

//第一列
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 40, 65, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 40, 110, 225, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 40, 155, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 40, 245, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 40, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 40, 335, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_15, 40, 380, 225, 40, 0, 100, 0 },
//第二列
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 320, 65, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 320, 110, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 320, 155, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 320, 200, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 320, 245, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 320, 290, 150, 40, 0, 100, 0 },  
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 320, 335, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_16, 320, 380, 150, 40, 0, 100, 0 },
//第三列
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 500, 110, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 500, 155, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 500, 200, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 500, 245, 120, 40, 0, 0, 0 },
 
//  { BUTTON_CreateIndirect, "Cancel", GUI_ID_CANCEL, 130, 161, 80, 20, 0, 0, 0 },
};


//分页2


static const GUI_WIDGET_CREATE_INFO _aFtxSlot_2[] = {
  { WINDOW_CreateIndirect, "Window", ID_WIN_2, 0, 0, 800, 480, 0, 0, 0 },
  { TEXT_CreateIndirect, "Txt", ID_TEXT_0, 20, 10, 780, 32, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Return", GUI_ID_OK, 670, 435, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 550, 435, 100, 40, 0, 0, 0 }, //上一页
  { TEXT_CreateIndirect, "Text", ID_TEXT_17, 180, 65, 180, 40, 0, 100, 40 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_18, 180, 110, 180, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_19, 180, 155, 180, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_20, 40, 200, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_21, 380, 65, 150, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_22, 380, 290, 250, 40, 0, 100, 0 },

  { TEXT_CreateIndirect, "Text", ID_TEXT_23, 40, 245, 320, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_24, 40, 290, 225, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_25, 380, 335, 250, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_26, 40, 335, 225, 40, 0, 100, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 380, 109, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_8, 380, 154, 120, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_9, 380, 200, 50, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_10, 380, 245, 50, 40, 0, 0, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 40, 110, 80, 60, 0, 8962, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};
//DNOT2



//DNOT
static void _cbOTSlot(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int Id, NCode, i;
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
		break;
	case WM_INIT_DIALOG:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		sprintf(buf, "Platform C / Slot %d: 1550TX", nSlot+1);
		TEXT_SetText(hItem, buf);


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
    TEXT_SetText(hItem, "Bias Current:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "Laser Temp:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "TEC Current:");
		
		
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Input Power");		
		

		
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
    TEXT_SetText(hItem, "27 C");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "50.5 mA");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "125 mA");
		
		
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "82 dBuV");


		
	
		
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Normal");
		BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_GREEN);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "Warning");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);		
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "Warning");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);		
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "Normal");
		BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_GREEN);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MORE);
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
    BUTTON_SetText(hItem, "More...");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
		
		if(currentPage==1)
		{

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Drive Level");		

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "60 dBuV");		
				
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_15);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "Wave Length:");			


			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_16);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "1310 nm");	
				//
				// Initialization of 'Button'
				//
				 hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
				 BUTTON_SetFont(hItem, GUI_FONT_32B_1);
				 BUTTON_SetText(hItem, "Next");
		}
    if(currentPage==2){
		  //
			// Initialization of 'Button'
			//
			 hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
       BUTTON_SetFont(hItem, GUI_FONT_32B_1);
       BUTTON_SetText(hItem, "Last");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "AGC Level:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_18);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Channels:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_19);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Gain:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_20);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Help:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_21);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "80 dBuV");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_22);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "201309125733");

			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_23);
			TEXT_SetText(hItem, "Restore default settings:");
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_24);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "SerialNum:");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, "FW12013A1-1201");
			//
			// Initialization of 'Text'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_26);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32B_1);
			TEXT_SetText(hItem, "Firmware Rev:");


			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
			BUTTON_SetText(hItem, "60");
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);

			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "100dB");


			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_9);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
			//
			// Initialization of 'Button'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_10);
			BUTTON_SetFont(hItem, GUI_FONT_32B_1);
			BUTTON_SetText(hItem, "...");
			//
			// Initialization of 'Radio'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
			RADIO_SetFont(hItem, GUI_FONT_32B_1);
			RADIO_SetText(hItem, "AGC", 0);
			RADIO_SetText(hItem, "MGC", 1);
		}
		
		
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
			memcpy(buf,"Output Power",20);
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
        // USER END
			memcpy(buf,"Bias Current",20);
			hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,1);
			WM_MakeModal(hItem);
			GUI_ExecCreatedDialog(hItem);			
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
      	memcpy(buf,"Laser Temp",20);
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
				memcpy(buf,"TEC Current",20);
				hItem = CreateSetAP(pMsg->hWin, buf, nSlot ,3);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);	 
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
			  //进入Tx详细页面，第一页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 1;
			    hItem  = GUI_CreateDialogBox(_aFtxSlot_1, GUI_COUNTOF(_aFtxSlot_1), &_cbOTSlot, _hParentWin, 0, 0);

			    WM_MakeModal(hItem);
			    GUI_ExecCreatedDialog(hItem);	
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
			  //进入Tx详细页面，第二页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 2;
			    hItem  = GUI_CreateDialogBox(_aFtxSlot_2, GUI_COUNTOF(_aFtxSlot_2), &_cbOTSlot, _hParentWin, 0, 0);

			    WM_MakeModal(hItem);
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
        // USER START (Optionally insert code for reacting on notification message)
			  //进入Tx详细页面，第一页
					GUI_EndDialog(pMsg->hWin, 0);	
			    currentPage = 1;
			    hItem  = GUI_CreateDialogBox(_aFtxSlot_1, GUI_COUNTOF(_aFtxSlot_1), &_cbOTSlot, _hParentWin, 0, 0);

			    WM_MakeModal(hItem);
			    GUI_ExecCreatedDialog(hItem);				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
			
    case ID_BUTTON_7: // Notifications sent by 'Button'
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
    case ID_BUTTON_8: // Notifications sent by 'Button'
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
    case ID_BUTTON_9: // Notifications sent by 'Button'
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
    case ID_BUTTON_10: // Notifications sent by 'Button'
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
		}
	break;		
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}


extern char slotType[];
WM_HWIN CreateWinSlot_Ftx(WM_HWIN hParant, int slt) {
	WM_HWIN hWin;
	WM_HWIN hItem;
  
	_hParentWin = hParant;
		nSlot = slt;
	  hWin = GUI_CreateDialogBox(_aFtxSlot, GUI_COUNTOF(_aFtxSlot), &_cbOTSlot, hParant, 0, 0);
		currentPage = 0;
	
///	hItem = EDIT_CreateEx(600, 2, 80, 40, hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	EDIT_SetText(hItem, "Add Man");
	
	return hWin;
}

