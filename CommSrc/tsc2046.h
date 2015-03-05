#ifndef __TSC2046_H__
#define __TSC2046_H__

#include "LPC177x_8x.h"
#include "glcd.h"

#define LCD_XS 480
#define LCD_YS 272
#define RAW_MODE 0
#define CAL_MODE 1

#define TSC2046_CS	(0x1<<6)	// P0.6(SSEL1)
#define EN_TSC2046_CS()	(LPC_GPIO0->CLR |= TSC2046_CS)
#define DIS_TSC2046_CS()	(LPC_GPIO0->SET |= TSC2046_CS)
#define TSC2046_BUSY	(0x1<<14)	// P2.14
#define TSC2046_PINQ	(0x1<<15)	// P2.15
#define TSC2046_BUSY_STATE()	(LPC_GPIO2->PIN & TSC2046_BUSY)
#define TSC2046_PINQ_STATE()	(LPC_GPIO2->PIN & TSC2046_PINQ)

#define GET_X_POS (0x82 | (0x05<<4)) 
#define GET_Y_POS (0x82 | (0x01<<4))  
#define GET_Z1_POS (0x82 | (0x03<<4)) 
#define GET_Z2_POS (0x82 | (0x04<<4)) 

#define TS_WAIT_PRESS 		0
#define TS_CHANGE_PRESS 	1
#define TS_WAIT_RELEASE 	2
#define TS_CHANGE_RELEASE 	-1

void TSC2046_init(void);
int TsActive(void);
void TsXYvector(pPoint_t pPt);
int TSC2046_GetAdVal(byte cmd);
void Set_tsCalMode(int mode);
int Set_tsCalData(pRect_t pRect, pRect_t pRefRect);
int Get_CalOffset(int xy);
float Get_CalScale(int xy);

void TsScanState( void );
int TsScanState1(pPoint_t pPt);

#endif /* __TSC2046_H__ */
