
#include "TypeDef.h"
#include "LPC177x_8x.h"
#include "Key.h"

#define KDLY1 50
#define KDLY2 10

#define P_KEY (0x0f)		// P0.0--3 used as Key 
//Key Scan Code define
#define SCAN_UPKEY (0x1<<0)
#define SCAN_DOWNKEY (0x1<<1)
#define SCAN_UPDOWNKEY (SCAN_UPKEY | SCAN_DOWNKEY)
#define SCAN_SETKEY (0x1<<2)
#define SCAN_ESCKEY (0x1<<3)

//#define SCAN_LEFTKEY 0x08
//#define SCAN_RIGHTKEY 0x10
//#define SCAN_LRKEY 0x18
#define P_KEY1 (0x01<<27)	// P0.27 used as upKey
#define P_KEY2 (0x01<<28)	// P0.28 used as dnKey
#define P_KEY3 (0x01<<10)	// P2.10 used as setKey(NMI)

extern void sysBeep(int mode, int rep, int itv);
void cb_KeyPressed(void);

extern void (*cb_Beep)();
void (*cb_Lcd)()=NULL;

unsigned int key_buff;
unsigned char key_cnt; 		//Bit 7-0 KCNT, Bit 15-8 Key port data, Bit 23-16 TKEY, Bit30 HAVEKEY  Bit31 DISABLE_KEY  Bit29 generate a key flag
unsigned char key_state;
//key_state define bit0..3 save a key temp. bit 4..7 define as follow
#define KF1 (0x01<<4)
#define KF2 (0x01<<5)
#define KF3 (0x01<<6)
#define KER (0x01<<7)
// unsigned int * pLcdControlState;
int longPress;

__asm int GetKey(U8 * pCtrl)
{
	PUSH {R1-R4}
	MOV R4, R0
	MOVS R3, #32
	LDR R2, =__cpp(&key_buff)
	LDR R1,[R2]
	SUBS R3, R3, #4
	BGE .+ 3*2
	POP {R1-R4}
	BX LR
	MOV R0, R1
	LSRS R0, R3
//	LSLS R0, #28	; R0 AND #0x0F
//	LSRS R0, #28
	BEQ .-6*2
	LSLS R0, R3
	BICS R1, R0
	LSRS R0, R3
	STR R1, [R2]

	MOVS R1, #0
	CMP R0, #0x0C			; the KeyValue be add 12 for Repeat key
	BLE .+3*2
	SUBS R0, #0x0C
	MOVS R1, #0x01
	CMP R4, #0
	BEQ .+2*2
	STRB R1, [R4]

	POP {R1-R4}
	BX LR
}


/*
__asm int keyPressed(void)
{
	LDR R0, =__cpp(&key_buff)
	LDR R0,[R0]
	CMP R0, #0x00
	BEQ .+8
	ADD R0, R0, #0x01
	BX LR
}

int keyPressed(void)
{
	if (key_aux & HAVEKEY) {
		key_aux &= ~HAVEKEY;
		return 1;
	}
	return 0;	
}

__asm void savTest(void)
{
	LDR R3, =__cpp(&key_test)
	MOV R1, R0, LSR #21
	AND R1, R1, #0x07
	STR R1, [R3]
	BX LR
}
*/

//Key Value define 
// Up	Down	UD 	Set	Left	Right	LR	ESC 
// 01	02		03	04	05		06		07	08
//__asm void CheckKey(void)
void CheckKey(int * key)
{
	key_state &= ~KER;
	if (*key==SCAN_UPKEY)
		*key = UPKEY;
	else if (*key==SCAN_DOWNKEY)
		*key = DOWNKEY;
 	else if (*key==SCAN_UPDOWNKEY)
		*key = UPDOWNKEY;
	else if (*key==SCAN_SETKEY)
		*key = SETKEY;
	else if (*key==SCAN_ESCKEY)
		*key = ESCKEY;
	else key_state |= KER;
 
/*	CMP R0, #SCAN_UPKEY
	BNE .+3*2 
	MOVS R0, #UPKEY
	BX LR
	CMP R0, #SCAN_DOWNKEY
 	BNE .+3*2 
	MOVS R0, #DOWNKEY
	BX LR
	CMP R0, #SCAN_UPDOWNKEY
	BNE .+3*2
	MOVS R0, #UPDOWNKEY
	BX LR
	CMP R0, #SCAN_SETKEY
	BNE .+3*2 
	MOVS R0, #SETKEY
	BX LR
//	ORRS R1, #KER
	BX LR*/
}

int rdKeyPort()
{
	int pVal = ~LPC_GPIO0->PIN & (P_KEY1 | P_KEY2);
	pVal >>= 27;
	pVal &= SCAN_UPDOWNKEY;	
	return pVal;
}
 
//This Routine called by interupt
//__asm void ScanKey(void)
void ScanKey(void)
{
	int key = rdKeyPort();

//	key = LPC_GPIO0->MASKED_ACCESS[P_KEY];

//	key = ~key;
//	key &= P_KEY;

	if (key_state & KF1) {
		if (key_state & KF2) {
			if (key) {
				CheckKey(&key);
				if ((key_state & KER) || (key != (key_state & 0x0f))) key_state = 0; 
				else {
					longPress++;
					if ((key==UPKEY) || (key==DOWNKEY)) {
						key_cnt++;
 						if (key_state & KF3) {
							if (key_cnt>=KDLY2) {
								key_cnt = 0;
								key_buff <<= 4;
								key_buff |= key;
								cb_KeyPressed();
							}
						} else {
							if (key_cnt>=KDLY1) {
								key_cnt = 0;
								key_state |= KF3;
								key_buff <<= 4;
								key_buff |= key;
								cb_KeyPressed();
							}
						}
					}	
				}
			} else {
				key_state = 0;
			}
		} else {
			if (key) {
				CheckKey(&key);
				if ((key_state & KER) || (key != (key_state & 0x0f))) key_state = 0; 
				else {
					key_state |= KF2;
					key_cnt =0;
					key_buff <<= 4;
					key_buff |= key;
					cb_KeyPressed();
				}
			} else {
				key_state = 0;
			}
		}
	} else {
		if (key) {
			CheckKey(&key);
			if (key_state & KER) key_state = 0; 
			else key_state = key | KF1;
			longPress =0;
		}  
	}
}

int GetStartKeyVal(void)
{
//	Wait200nS;
//	retVal = (~(IO0PIN >> 21)) & 0x07;
	return 0;
}

void cb_KeyPressed()
{
	if (cb_Beep) cb_Beep();
	if (cb_Lcd) cb_Lcd();
}

void Set_cb_Lcd(void (*fn)())
{
	cb_Lcd = fn;
}

/*void Set_cb_Beep(void (*fn)())
{
	cb_Beep = fn;
}*/
