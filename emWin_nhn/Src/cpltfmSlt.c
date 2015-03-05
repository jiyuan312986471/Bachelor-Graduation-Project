#include "LCD_constdef.h"
#include "DIALOG.h"


char slotType[19] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void set_slot_sim()
{
	slotType[0] = devID_DNOT1;
	slotType[1] = devID_DNOT2;
	slotType[2] = devID_DNOT1;
	slotType[3] = devID_DNOT2;
	slotType[4] = devID_UNK;
	slotType[5] = devID_DNOR;
	slotType[6] = devID_DNOR;
	slotType[7] = devID_UNK;
	slotType[8] = devID_UPOR;
	slotType[9] = devID_EDFA;
	slotType[10] = devID_EDFA;
	slotType[11] = devID_DNOT2;
	slotType[12] = devID_DNOR;
	slotType[13] = devID_NULL;
	slotType[14] = devID_UNK;
	slotType[15] = devID_DNOT2;
	
	slotType[16] = devID_PS;
	slotType[17] = devID_PS;
	slotType[18] = devID_FAN;
	
}
WM_HWIN CreateWinSlot(WM_HWIN hParent, int slt)
{
	switch(slotType[slt])
	{
		case devID_DNOT1:
		case devID_DNOT2:
			CreateWinSlot_Ftx(hParent, slt);
			break;
		
		case devID_DNOR:
		case devID_UPOR:
      CreateWinSlot_OR(hParent, slt);
		break;
		
		case devID_PS:
			CreateWinSlot_PS(hParent, slt);
		break;
		
		case devID_FAN:
			CreateWinSlot_Fan(hParent, slt);
		break;
		
		case devID_EDFA:
			CreateWinSlot_EDFA(hParent, slt);
		
		default:
			break;
	}
}
