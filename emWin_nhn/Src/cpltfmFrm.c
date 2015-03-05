
#include "DIALOG.h"

#include "LCD_constdef.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_WINDOW_0     (GUI_ID_USER + 0x09)
#define ID_BUTTON_0     (GUI_ID_USER + 0x0D)
#define ID_BUTTON_1     (GUI_ID_USER + 0x0E)
#define ID_BUTTON_2     (GUI_ID_USER + 0x0F)
#define ID_BUTTON_3     (GUI_ID_USER + 0x10)
#define ID_BUTTON_4     (GUI_ID_USER + 0x11)
#define ID_BUTTON_5     (GUI_ID_USER + 0x12)
#define ID_BUTTON_6     (GUI_ID_USER + 0x13)
#define ID_BUTTON_7     (GUI_ID_USER + 0x14)
#define ID_BUTTON_8     (GUI_ID_USER + 0x15)
#define ID_BUTTON_9     (GUI_ID_USER + 0x16)
#define ID_BUTTON_10    (GUI_ID_USER + 0x17)
#define ID_BUTTON_11    (GUI_ID_USER + 0x18)
#define ID_BUTTON_12    (GUI_ID_USER + 0x19)
#define ID_BUTTON_13    (GUI_ID_USER + 0x1A)
#define ID_BUTTON_14    (GUI_ID_USER + 0x1B)
#define ID_BUTTON_15    (GUI_ID_USER + 0x1C)
#define ID_BUTTON_16    (GUI_ID_USER + 0x1D)
#define ID_BUTTON_17    (GUI_ID_USER + 0x1E)
#define ID_BUTTON_18    (GUI_ID_USER + 0x1F)
#define ID_BUTTON_19    (GUI_ID_USER + 0x20)
#define ID_BUTTON_20    (GUI_ID_USER + 0x21)
#define ID_BUTTON_21    (GUI_ID_USER + 0x22)
#define ID_BUTTON_22    (GUI_ID_USER + 0x23)


#define ID_EDIT_0    (GUI_ID_USER + 0x30)
#define ID_EDIT_1    (GUI_ID_USER + 0x31)
#define ID_EDIT_2    (GUI_ID_USER + 0x32)
#define ID_EDIT_3    (GUI_ID_USER + 0x33)
#define ID_EDIT_4    (GUI_ID_USER + 0x34)
#define ID_EDIT_5    (GUI_ID_USER + 0x35)
#define ID_EDIT_6    (GUI_ID_USER + 0x36)
#define ID_EDIT_7    (GUI_ID_USER + 0x37)
#define ID_EDIT_8    (GUI_ID_USER + 0x38)
#define ID_EDIT_9    (GUI_ID_USER + 0x39)
#define ID_EDIT_10    (GUI_ID_USER + 0x3A)
#define ID_EDIT_11    (GUI_ID_USER + 0x3B)
#define ID_EDIT_12    (GUI_ID_USER + 0x3C)
#define ID_EDIT_13    (GUI_ID_USER + 0x3D)
#define ID_EDIT_14    (GUI_ID_USER + 0x3E)
#define ID_EDIT_15    (GUI_ID_USER + 0x3F)
#define ID_TEST		(GUI_ID_USER + 0x40)
#define ID_TEXT_1 (GUI_ID_USER + 0x41)


// USER START (Optionally insert additional defines)
// USER END

WM_HWIN CreateWinSlot(WM_HWIN hParant, int slt);

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
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 800, 480, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Supply", ID_BUTTON_17, 20, 70, 240, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Fan", ID_BUTTON_19, 280, 70, 240, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Supply", ID_BUTTON_18, 540, 70, 240, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Chassis", ID_BUTTON_0, 20, 116, 760, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 1", ID_BUTTON_1, 20, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 2", ID_BUTTON_2, 68, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 3", ID_BUTTON_3, 116, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 4", ID_BUTTON_4, 164, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 5", ID_BUTTON_5, 212, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 6", ID_BUTTON_6, 260, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 7", ID_BUTTON_7, 308, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 8", ID_BUTTON_8, 356, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 9", ID_BUTTON_9, 404, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 10", ID_BUTTON_10, 452, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 11", ID_BUTTON_11, 500, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 12", ID_BUTTON_12, 548, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 13", ID_BUTTON_13, 596, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 14", ID_BUTTON_14, 644, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 15", ID_BUTTON_15, 692, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Slot 16", ID_BUTTON_16, 740, 204, 40, 216, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Configuration", ID_BUTTON_20, 580, 435, 200, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Sim", ID_BUTTON_21, 400, 435, 110, 40, 0, 0, 0 },
///  { BUTTON_CreateIndirect, "17th", ID_BUTTON_22, 657, 21, 80, 30, 0, 0, 0 },
	
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 20, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 68, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 116, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 164, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 212, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_5, 260, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_6, 308, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_7, 356, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_8, 404, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_9, 452, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_10, 500, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_11, 548, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_12, 596, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_13, 644, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_14, 692, 160, 40, 40, 0, 100, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_15, 740, 160, 40, 40, 0, 100, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 58, 445, 45, 25, 0, 100, 0 },	
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
#define nEx_X 1
#define nEx_Y 1
void drawFrame(WM_HWIN hItem, GUI_COLOR color)
{
	GUI_POINT aPoints[4];
	GUI_RECT rc;
	
	WM_GetWindowRectEx(hItem, &rc);
	aPoints[0].x = rc.x0-nEx_X;
	aPoints[0].y = rc.y0-nEx_Y;
	aPoints[1].x = rc.x1+nEx_X;
	aPoints[1].y = aPoints[0].y;
	aPoints[2].x = aPoints[1].x;
	aPoints[2].y = rc.y1+nEx_Y;
	aPoints[3].x = aPoints[0].x;
	aPoints[3].y = aPoints[2].y;
	
	GUI_SetColor(color);
	GUI_DrawPolygon(aPoints, 4, 0, 0); 
}


extern char slotType[];
//刷新插槽模块
void showSlots(WM_HWIN hDialog)
{
	int i;
	WM_HWIN hItem;
	for(i=0;i<16;i++)//16个模块
	{
		hItem = WM_GetDialogItem(hDialog, ID_BUTTON_1+i);
		switch(slotType[i])
		{
			case devID_DNOT1:
			  BUTTON_SetFont(hItem, GUI_FONT_32B_1);
        BUTTON_SetText(hItem, LCD_DNOT1_TYPE);
		    WM_EnableWindow(hItem);					
				break;
			
			case devID_DNOT2:
			  BUTTON_SetFont(hItem, GUI_FONT_32B_1);
        BUTTON_SetText(hItem, LCD_DNOT2_TYPE);
		    WM_EnableWindow(hItem);				
			break;
			
			case devID_UPOR:
			  BUTTON_SetFont(hItem, GUI_FONT_32B_1);
        BUTTON_SetText(hItem, LCD_UPOR_TYPE);
		    WM_EnableWindow(hItem);				
				break;
			
			case devID_DNOR:
			  BUTTON_SetFont(hItem, GUI_FONT_32B_1);
        BUTTON_SetText(hItem, LCD_DNOR_TYPE);
		    WM_EnableWindow(hItem);				
				break;
			
			case devID_EDFA:
			  BUTTON_SetFont(hItem, GUI_FONT_32B_1);
        BUTTON_SetText(hItem, LCD_EDFA_TYPE);
		    WM_EnableWindow(hItem);				
				break;
		
			
			
			case devID_NULL:
			  BUTTON_SetFont(hItem, GUI_FONT_32_1);
        BUTTON_SetText(hItem, LCD_EMPTY_TYPE);
		    WM_DisableWindow(hItem);		 
				break;
			
			
			default: // devID_UNK:
				BUTTON_SetFont(hItem, GUI_FONT_32_1);
        BUTTON_SetText(hItem, LCD_UNK_TYPE);
		    WM_DisableWindow(hItem);					
				break;
		}
		
	}
  for(i=0;i<2;i++) //2个PS
	{
		 hItem = WM_GetDialogItem(hDialog, ID_BUTTON_17+i);
		 switch(slotType[i+16])
		 {
			  case devID_PS:
					BUTTON_SetFont(hItem, GUI_FONT_32B_1);
					BUTTON_SetText(hItem, LCD_PS_TYPE);
					WM_EnableWindow(hItem);				
				break;		

			  case devID_NULL:
					BUTTON_SetFont(hItem, GUI_FONT_32_1);
					BUTTON_SetText(hItem, "EMPTY");
					WM_DisableWindow(hItem);		 
				break;	
				
			 default:
				 BUTTON_SetFont(hItem, GUI_FONT_32_1);
         BUTTON_SetText(hItem, "UNK");
		     WM_DisableWindow(hItem);			
		 }
	}
	
	
		 hItem = WM_GetDialogItem(hDialog, ID_BUTTON_19);
		 switch(slotType[i+16])
		 {
			  case devID_FAN:
					BUTTON_SetFont(hItem, GUI_FONT_32B_1);
					BUTTON_SetText(hItem, LCD_FAN_TYPE);
					WM_EnableWindow(hItem);				
				break;	

			  case devID_NULL:
					BUTTON_SetFont(hItem, GUI_FONT_32_1);
					BUTTON_SetText(hItem, "EMPTY");
					WM_DisableWindow(hItem);		 
				break;	
				
			 default:
				 BUTTON_SetFont(hItem, GUI_FONT_32_1);
         BUTTON_SetText(hItem, "UNK");
		     WM_DisableWindow(hItem);			
		 }
	
}

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmlogo_nhn;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_pic;
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode, i;
	char buf[16];
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_PAINT:
	GUI_SetColor(GUI_BLUE);
	i = 64;
	GUI_FillRect(20, i, 780, i+4);  
	i = 425;
	GUI_FillRect(20, i, 780, i+4); 
//	GUI_SetDrawMode(GUI_DM_XOR);
	GUI_DrawBitmap(&bmlogo_nhn, 20, 0);
	GUI_DrawBitmap(&bmalarm_pic, 20, 435);
	
	showSlots(pMsg->hWin);
	
  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
	drawFrame(hItem, GUI_RED);
  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
	drawFrame(hItem, GUI_GREEN);
  hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
	drawFrame(hItem, GUI_YELLOW);
	break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Slot\r\n1'
    //
//	EDIT_CreateEx(Xo,Yo, Xs, Ys, pMsg->hWin, WM_CF_SHOW, 0, ID, Len);

	
	///	  hItem = EDIT_CreateEx(600, 2, 80, 40, pMsg->hWin, WM_CF_SHOW, 0, ID_TEST, 10);
///	  EDIT_SetText(hItem, "Add Man");
  
  //初始化为空模块
   for(i=0; i<16; i++){
	   hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1+i);
		 BUTTON_SetFont(hItem, GUI_FONT_32_1);
     BUTTON_SetText(hItem, LCD_EMPTY_TYPE);
		 WM_DisableWindow(hItem);		 
   }
//
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_20);
    BUTTON_SetText(hItem, "Configuration");

	 
	  //
    // Initialization of 'Text'
    //	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, 0x00FF0000);
		TEXT_SetFont(hItem, GUI_FONT_20B_1);
    TEXT_SetText(hItem, "18");
    //
    // Initialization of 'Edit'
    //
	buf[0] = '1';
	buf[1] = 0;
 	buf[2] = 0;
	for (i=0; i<16; i++) {
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0+i);
		EDIT_SetText(hItem, buf);
		if (i==8) { 
			buf[0] = '1';			
			buf[1] = '0';			
		} else if (i<9) buf[0]++;
		else buf[1]++;
		EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		EDIT_SetFont(hItem, GUI_FONT_32B_1);
		WM_DisableWindow(hItem);
	}

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Chassis'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = CreateWin_Chassis(pMsg->hWin);
		   	WM_MakeModal(hItem);
			  GUI_ExecCreatedDialog(hItem);		
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Slot1'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = CreateWinSlot(pMsg->hWin, 0);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Slot2'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = CreateWinSlot(pMsg->hWin, 1);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Slot3'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = CreateWinSlot(pMsg->hWin, 2);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Slot4'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
			hItem = CreateWinSlot(pMsg->hWin, 3);
			WM_MakeModal(hItem);
			GUI_ExecCreatedDialog(hItem);			
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Slot 2'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 4);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_6: // Notifications sent by 'Slot 3'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
		hItem = CreateWinSlot(pMsg->hWin, 5);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);			
         break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_7: // Notifications sent by 'Slot 4'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 6);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'Slot 5'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 7);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_9: // Notifications sent by 'Slot 6'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 8);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_10: // Notifications sent by 'Slot 7'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 9);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_11: // Notifications sent by 'Slot 8'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 10);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_12: // Notifications sent by 'Slot 9'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 11);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_13: // Notifications sent by 'Slot 10'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 12);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_14: // Notifications sent by 'Slot 11'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 13);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_15: // Notifications sent by 'Slot 12'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 14);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_16: // Notifications sent by 'Slot 13'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		hItem = CreateWinSlot(pMsg->hWin, 15);
		WM_MakeModal(hItem);
		GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_17: // Notifications sent by 'Slot 17' PS1
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = CreateWinSlot(pMsg->hWin, 16);
				WM_MakeModal(hItem);
				GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break; 
    case ID_BUTTON_18: // Notifications sent by 'Slot 18' PS2
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			hItem = CreateWinSlot(pMsg->hWin, 17);
			WM_MakeModal(hItem);
			GUI_ExecCreatedDialog(hItem);		
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_19: // Notifications sent by 'Slot 16'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			hItem = CreateWinSlot(pMsg->hWin, 18);
			WM_MakeModal(hItem);
			GUI_ExecCreatedDialog(hItem);		 
			// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_20: // Notifications sent by 'Button'
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
			
    case ID_BUTTON_21: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
				set_slot_sim();
//			  WM_InvalidateWindow(pMsg->hWin);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;			

		case ID_BUTTON_22: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        //模拟快速按钮17
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;		
			
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
    case ID_EDIT_5: // Notifications sent by 'Edit'
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
    case ID_EDIT_6: // Notifications sent by 'Edit'
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
    case ID_EDIT_7: // Notifications sent by 'Edit'
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
    case ID_EDIT_8: // Notifications sent by 'Edit'
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
    case ID_EDIT_9: // Notifications sent by 'Edit'
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
    case ID_EDIT_10: // Notifications sent by 'Edit'
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
    case ID_EDIT_11: // Notifications sent by 'Edit'
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
    case ID_EDIT_12: // Notifications sent by 'Edit'
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
    case ID_EDIT_13: // Notifications sent by 'Edit'
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
    case ID_EDIT_14: // Notifications sent by 'Edit'
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
    case ID_EDIT_15: // Notifications sent by 'Edit'
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

// USER START (Optionally insert additional public code)
// USER END
int rcFree, rcUsed, rcFree0, rcUsed0;
void MainTask(void) 
{
	int count;
	WM_HWIN hWin;
	
//	count =0;
//	outOpPwr = 10.0;
	
	WM_EnableMemdev(WM_HBKWIN);
	WM_SetCreateFlags(WM_CF_MEMDEV);	// WM_CF_MEMDEV_ON_REDRAW
	GUI_Init();
//	rcFree = GUI_ALLOC_GetNumFreeBytes();
//	rcUsed = GUI_ALLOC_GetNumUsedBytes();
//	WM_EnableMemdev(WM_HBKWIN);
//	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
// 	GUI_UC_SetEncodeUTF8();	
//	GUI_SIF_CreateFont((const void*)acST_GB231224, &ftSIF, GUI_SIF_TYPE_PROP_EXT);
	
//	GUI_CURSOR_Show();
//	GUI_SetDefaultFont(&ftSIF);
//	FRAMEWIN_SetDefaultFont(&ftSIF);
	BUTTON_SetDefaultFont(GUI_FONT_32B_1);
//	GUI_PNG_Draw(aclogo, 86765, 0, 0);
//	GUI_GIF_Draw(aclogo, 86765, 0, 0);
//	GUI_JPEG_Draw((const void*)aclogo_jpg, 47538, 0, 0);
//	GUI_Delay(2000);
	hWin = CreateWindow();
//	WM_EnableMemdev(hWin);
	while (1) {
		GUI_Delay(500);
		WM_InvalidateWindow(hWin);
		rcFree = GUI_ALLOC_GetNumFreeBytes();
		rcUsed = GUI_ALLOC_GetNumUsedBytes();
		if (rcFree!=rcFree0) {
			rcFree0 = rcFree;
		}
		if (rcUsed!=rcUsed0) {
			rcUsed0 = rcUsed;
		}
/*		if (count++ >5) {
			count =0;
			updateParam(hWin);
		}
		WM_InvalidateWindow(hWin);*/
	}		
}
/*************************** End of file ****************************/



