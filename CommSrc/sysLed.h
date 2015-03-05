/*sysLed.h --sys LED control Header file. */

#ifndef __SYSLED_CTRL__
#define __SYSLED_CTRL__

#include "typeDef.h"

typedef struct {
	char mode;
	char state;
	char base;
	char rep;
	int itv;
} _beep_ctrl;

typedef struct {
	unsigned short T_On;
	unsigned short T_Off;
} _beep_delay;

typedef struct {
	unsigned char ofst;
	unsigned char num;
} _beep_pos;

extern _beep_delay beep_delay[];
extern _beep_pos beep_pos[];

void Init_sysLed(void);
void sysLedUpdate_tick(void);
void Set_sysLed(int led, int onoff, int flush);
void Set_sysLed_dly(int led, char mode, U16 mSDly);
void Set_sysLed_flushdly(int led, U16 mSDly);
void Set_sysLedBit(int bLed);

void sysBeep_Init(void);
void sysBeep(int mode, int rep, int itv);
void sysBeep_Set(int n1, int n2, int n3);
void sysBeep_Print(char *p);
void Set_cb_Beep(void (*fn)());

#endif /* __SYSLED_CTRL__ */
