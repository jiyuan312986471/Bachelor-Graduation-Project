#include <RTL.H>
#include "LPC177x_8x.h"
#include "net_misc.h"
#include "sysLed.h"

// #define BEEP_CTRL_USE_P2_9

#define SYSLED_FORCE_UPDATE 0x80
#define BEEP_CTRL (0x01<<19)	// P2.19
#define BEEP_CTRL_INIT() LPC_GPIO2->DIR |= BEEP_CTRL

#define SYSLED1_CTRL (0x01<<18)	// P1.18
#define SYSLED2_CTRL (0x01<<2)	// P5.2
#define SYSLED3_CTRL (0x01<<3)	// P5.3
#define SYSLED4_CTRL (0x01<<4)	// P5.4
//#define SYSLED_MASK (SYSLED1_CTRL | SYSLED2_CTRL | SYSLED3_CTRL | SYSLED4_CTRL)

#define LED_CTRL_INIT() LPC_GPIO1->DIR |= SYSLED1_CTRL; LPC_GPIO5->DIR |= SYSLED2_CTRL| SYSLED3_CTRL | SYSLED4_CTRL
#define sysBeep_On() LPC_GPIO2->SET |= BEEP_CTRL
#define sysBeep_Off() LPC_GPIO2->CLR |= BEEP_CTRL

#define LED_OUTPUT(x)  if (x & 0x01) LPC_GPIO1->CLR |= SYSLED1_CTRL; else LPC_GPIO1->SET |= SYSLED1_CTRL;\
						x <<= 1; x &= 0x1c; LPC_GPIO5->SET |= (~x & 0x1c); LPC_GPIO5->CLR |= x 

void beep_dealwith(void);

#define MAX_BEEP_MODE 3

void cb_KeyPressed_Beep(void);

_beep_delay beep_delay[] = {
	{10, 20},	//beep mode 1
	{40, 80},	//beep mode 2
	{40, 80},
	{40, 80},	//beep mode 3
	{40, 80},
	{40, 80},
	{40, 80}
};

_beep_pos beep_pos[] = {
	{0, 1},
	{1, 2},
	{3, 3}
};

U16 sysLed_DlyCnt[4];
char sysLed_Out;
char sysLed_Flu;
char sysLed_Set;
char sysLed_DlySte;

//Delay off mode control. bit1..0 for Led0, bit0=1 enable SysLed0 On delay off, bit1=1 enable SysLed0 Falsh delay off.
char sysLed_DlyMode0;
char sysLed_DlyMode1;

_beep_ctrl sysBeep_Ctrl;
void (*cb_Beep)()=0;

void Init_sysLed()
{
	LED_CTRL_INIT();
	sysLed_Set = 0;
	sysLed_Out = 0;
	sysLed_DlyMode0= 0;
	sysLed_DlyMode1= 0;
	sysLed_DlySte = 0;
	sysLed_Flu |= SYSLED_FORCE_UPDATE;
}

void sysLedUpdate_tick()
{
	int n, sysLedImg;

	for (n=0; sysLed_DlyMode0 && (n<4); n++) {
		sysLedImg = 0x01<<n;
		if (sysLed_DlyMode0 & sysLedImg) {
			if (((sysLed_Set ^ sysLed_DlySte) & sysLedImg) && _CHK_SHORT_TIMEOUT(sysLed_DlyCnt[n])) {
				sysLed_Set ^= sysLedImg;
				sysLed_DlyMode0 &= ~sysLedImg;
				sysLed_Flu |= SYSLED_FORCE_UPDATE;
			}
		}
	}
	for (n=0; sysLed_DlyMode1 && (n<4); n++) {
		sysLedImg = 0x01<<n;
		if (sysLed_DlyMode1 & sysLedImg) {
			if ((sysLed_Flu & sysLedImg) && _CHK_SHORT_TIMEOUT(sysLed_DlyCnt[n])) { 
				sysLed_Flu &= ~sysLedImg;
				sysLed_DlyMode1 &= ~sysLedImg;
				sysLed_Flu |= SYSLED_FORCE_UPDATE;
			}
		}
	}
	if (sysLed_Flu) {
		sysLed_Flu &= ~SYSLED_FORCE_UPDATE;
		sysLed_Out &= sysLed_Flu;
		sysLed_Out ^= sysLed_Flu;
		sysLed_Out |= (sysLed_Set & ~sysLed_Flu);
		sysLedImg = sysLed_Out;
		LED_OUTPUT(sysLedImg);
	}
//	beep_dealwith();
}

//控制系统LED亮、暗或闪烁
//led:		led编号
//onoff:	-1=不影响 0=暗， 其他=亮
//flash:	-1=不影响 0=不闪烁， 其他=闪烁	
void Set_sysLed(int led, int onoff, int flush)
{
	if (led<0 || led>3) return;
	led = 1<<led;
	if (onoff!=-1) {
		if (onoff) 
			sysLed_Set |= led;
		else
			sysLed_Set &= ~led;
	}
	if (flush!=-1) {
		if (flush) 
			sysLed_Flu |= led;
		else 
			sysLed_Flu &= ~led;
	}
	sysLed_Flu |= SYSLED_FORCE_UPDATE;
}

//mode: Delay mode, 0=blink, then light after delay, other=light, then blink after delay. 
//mSDly: delay time(mS)
void Set_sysLed_dly(int led, char mode, U16 mSDly)
{
	if (led<0 || led>3) return;
	sysLed_DlyCnt[led] = _SET_SHORT_TIMEOUT(mSDly);
	led = 1<<led;
	if (mode) 
		sysLed_Set |= led;
	else
		sysLed_Set &= ~led;
	sysLed_DlySte = ~sysLed_Set;
	sysLed_DlyMode0 |= led;
	sysLed_Flu &= ~led;
	sysLed_Flu |= SYSLED_FORCE_UPDATE;
}

void Set_sysLed_flushdly(int led, U16 mSDly)
{
	if (led<0 || led>3) return;
	sysLed_DlyCnt[led] = _SET_SHORT_TIMEOUT(mSDly);
	led = 1<<led;
	sysLed_DlyMode1 |= led;
	sysLed_Flu |= (led | SYSLED_FORCE_UPDATE);
}

void Set_sysLedBit(int bLed)
{
	sysLed_Set = bLed;
	sysLed_Flu |= SYSLED_FORCE_UPDATE;
}

int TOnCnt,TOffCnt;
char beepStop;
void beep_dealwith(void)
{
	if (beepStop) {
		beepStop = 1;
		sysBeep_Off();
		sysBeep_Ctrl.rep = 0;
		return;
	}
	
	if ((int)(MS_TIMER-TOffCnt)>beep_delay[sysBeep_Ctrl.base].T_Off){
		sysBeep_Ctrl.state++;
		if (sysBeep_Ctrl.state<beep_pos[sysBeep_Ctrl.mode].num) {
			sysBeep_On();
			TOnCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base + sysBeep_Ctrl.state].T_On;
			TOffCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base + sysBeep_Ctrl.state].T_Off;
			if (sysBeep_Ctrl.state==beep_pos[sysBeep_Ctrl.mode].num-1) TOffCnt += sysBeep_Ctrl.itv;
		} else {
			sysBeep_Ctrl.rep--;
			if (sysBeep_Ctrl.rep) {
				sysBeep_On();
				TOnCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base].T_On;
				TOffCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base].T_Off;
				sysBeep_Ctrl.state = 0;
				if (sysBeep_Ctrl.state==beep_pos[sysBeep_Ctrl.mode].num-1) TOffCnt += sysBeep_Ctrl.itv;
			} else {
				beepStop = 1;
				sysBeep_Off();
			}
		}
	} else if ((int)(MS_TIMER-TOnCnt)>beep_delay[sysBeep_Ctrl.base].T_On)
		sysBeep_Off();

}


void sysBeep_Init()
{
	BEEP_CTRL_INIT();
	sysBeep_Off();
	memset(&sysBeep_Ctrl, 0, sizeof(_beep_ctrl));
	beepStop = 1;
	Set_cb_Beep(cb_KeyPressed_Beep);
	Set_BeepDealwith_Ptr(beep_dealwith);
}

void sysBeep(int mode, int rep, int itv)
{
	if (mode ==-1) {
		sysBeep_Off();
		beepStop = 1;
	} else if (mode < MAX_BEEP_MODE) {
		if (sysBeep_Ctrl.rep) return;
		sysBeep_Ctrl.mode = mode;
		sysBeep_Ctrl.state = 0;
		sysBeep_Ctrl.base = beep_pos[sysBeep_Ctrl.mode].ofst;
		if (rep>0) {
			sysBeep_Ctrl.rep = rep;
			sysBeep_Ctrl.itv = itv - beep_delay[sysBeep_Ctrl.base + beep_pos[sysBeep_Ctrl.mode].num-1].T_Off;
			if (sysBeep_Ctrl.itv<0) sysBeep_Ctrl.itv = 0;
		} else {
			sysBeep_Ctrl.rep = 1;
			sysBeep_Ctrl.itv = 0;
		}
		sysBeep_On();
		TOnCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base].T_On;
		TOffCnt = MS_TIMER+beep_delay[sysBeep_Ctrl.base].T_Off;
		if (sysBeep_Ctrl.state==beep_pos[sysBeep_Ctrl.mode].num-1) TOffCnt += sysBeep_Ctrl.itv;
		beepStop = 0; 
	}
}

void sysBeep_Set(int n1, int n2, int n3)
{
	beep_delay[n1].T_On = n2;
	beep_delay[n1].T_Off = n2+n3;
}

void sysBeep_Print(char *p)
{
	int i;

	p += sprintf(p, "T_on and T_off\r\n");
	for (i=0; i<7; i++) 
		p += sprintf(p, "%d, %d\r\n", beep_delay[i].T_On, beep_delay[i].T_Off);
	p += sprintf(p, "offset and num\r\n");
	for (i=0; i<MAX_BEEP_MODE; i++) 
		p += sprintf(p, "%d, %d\r\n", beep_pos[i].ofst, beep_pos[i].num);
}

void cb_KeyPressed_Beep()
{
	sysBeep(0,0,0);
}

void Set_cb_Beep(void (*fn)())
{
	cb_Beep = fn;
}

