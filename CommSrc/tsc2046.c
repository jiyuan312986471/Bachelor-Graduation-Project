// tsc2046.c

#include "typeDef.h"
#include "system_LPC177x_8x.h"
#include "net_misc.h"
#include "tsc2046.h"

#define TSC2046_DCLK 	(0x1<<19)	// P1.19(SCK1)
#define TSC2046_DIN 	(0x1<<12)	// P0.12(MOSI1)
#define TSC2046_DOUT 	(0x1<<13)	// P0.13(MISO1)


#define SSP_FIFOSIZE 8
/* SSP Status register */
#define SSPSR_TFE		(1 << 0)
#define SSPSR_TNF		(1 << 1) 
#define SSPSR_RNE		(1 << 2)
#define SSPSR_RFF		(1 << 3) 
#define SSPSR_BSY		(1 << 4)
/* SSP CR1 register */
#define SSPCR1_LBM		(1 << 0)
#define SSPCR1_SSE		(1 << 1)
#define SSPCR1_MS		(1 << 2)
#define SSPCR1_SOD		(1 << 3)

/* SSP Interrupt Mask Set/Clear register */
#define SSPIMSC_RORIM	(1 << 0)
#define SSPIMSC_RTIM	(1 << 1)
#define SSPIMSC_RXIM	(1 << 2)
#define SSPIMSC_TXIM	(1 << 3)

/* SSP0 Interrupt Status register */
#define SSPRIS_RORRIS	(1 << 0)
#define SSPRIS_RTRIS	(1 << 1)
#define SSPRIS_RXRIS	(1 << 2)
#define SSPRIS_TXRIS	(1 << 3)

/* SSP0 Masked Interrupt register */
#define SSPMIS_RORMIS	(1 << 0)
#define SSPMIS_RTMIS	(1 << 1)
#define SSPMIS_RXMIS	(1 << 2)
#define SSPMIS_TXMIS	(1 << 3)

/* SSP0 Interrupt clear register */
#define SSPICR_RORIC	(1 << 0)
#define SSPICR_RTIC		(1 << 1)

#define TSCAL_MINIMUM 0x600
#define TSCAL_MAXIMUM 0xA00

#define BTNRELEASE 0x80000000L
#define TS_ASSERT	20
#define TS_RELEASE	20
#define TS_RECHECK	2

typedef struct
{
	int x_offset;
	int y_offset;
	float x_gainfactor;
	float y_gainfactor;
} ts_cal;

volatile int interrupt1RxStat = 0;
volatile int interrupt1OverRunStat = 0;
volatile int interrupt1RxTimeoutStat = 0;
ts_cal tsCaldta;

byte tsCalMode = CAL_MODE;

void SSP1_IRQHandler(void) 
{
	uint32_t regValue;

	regValue = LPC_SSP1->MIS;
	if ( regValue & SSPMIS_RORMIS ) {	// Receive overrun interrupt
		interrupt1OverRunStat++;
		LPC_SSP1->ICR = SSPICR_RORIC;	// clear interrupt
	}
	if ( regValue & SSPMIS_RTMIS ) {	// Receive timeout interrupt
		interrupt1RxTimeoutStat++;
		LPC_SSP1->ICR = SSPICR_RTIC;		// clear interrupt
	}

  /* please be aware that, in main and ISR, CurrentRxIndex and CurrentTxIndex
  are shared as global variables. It may create some race condition that main
  and ISR manipulate these variables at the same time. SSPSR_BSY checking (polling)
  in both main and ISR could prevent this kind of race condition */
	if ( regValue & SSPMIS_RXMIS ) {	// Rx at least half full
		interrupt1RxStat++;				// receive until it's empty		
	}
	return;
}

// for tsc2046, the location should be 1
void TSC2046_init()
{
	int i;
	byte Dummy=Dummy;

	tsCaldta.x_offset = 157;
	tsCaldta.y_offset = 328;
	tsCaldta.x_gainfactor = 0.127389;
	tsCaldta.y_gainfactor = 0.076957;

	LPC_SC->PCONP |= (0x1<<10);	// Enable AHB clock to the SSP1.
	LPC_IOCON->P1_19 &= ~0x07;
	LPC_IOCON->P1_19 |= 0x05;		// SSP CLK
	LPC_IOCON->P0_12 &= ~0x07;
	LPC_IOCON->P0_12 |= 0x02;		// SSP MISO
	LPC_IOCON->P0_13 &= ~0x07;	
	LPC_IOCON->P0_13 |= 0x02;		// SSP MOSI
//	LPC_IOCON->P0_6 &= ~0x07;	
//	LPC_IOCON->P0_6 |= 0x05;		// SSP SSEL
	LPC_IOCON->P0_6 &= ~0x07;
	LPC_GPIO0->DIR |= (0x1<<6);
	LPC_GPIO0->SET |= (0x1<<6);

// Serial Clock Rate: the bit frequency is PCLK / (CPSDVSR*[SCR+1]).
// Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15
	LPC_SSP1->CR0 = 0x1F07;		// SCR=31, CPSDVSR =2, 60(pclk)/2/(31+1)=0.975Mhz 

// SSPCPSR clock prescale register, master mode, minimum divisor is 0x02
	LPC_SSP1->CPSR = 0x2;

	for ( i = 0; i < SSP_FIFOSIZE; i++ ) Dummy = LPC_SSP1->DR;	// clear the RxFIFO
  
	NVIC_EnableIRQ(SSP1_IRQn);	// Enable the SSP Interrupt

// Set SSPINMS registers to enable interrupts enable all error related interrupts
	LPC_SSP1->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
	LPC_SSP1->CR1 = SSPCR1_SSE;	// Master mode
}

// returns the status of the touchscreen.
// RETURN VALUE:  0 = Touchscreen not being pressed. 1 = Touchscreen being pressed.
int TsActive()
{
	return TSC2046_PINQ_STATE() ? 0:1;
}

int TSC2046_GetAdVal(byte cmd)
{
	int iRet;
	byte Dummy;

	EN_TSC2046_CS();
	while ( (LPC_SSP1->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	LPC_SSP1->DR = cmd;
	while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP1->DR;

	LPC_SSP1->DR = 0x00;
	while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP1->DR;
	LPC_SSP1->DR = 0x00;
	iRet = Dummy &= 0x7F;
	iRet <<= 5;
	while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP1->DR;
	iRet |= (Dummy>>3);
	DIS_TSC2046_CS();
	return iRet;
}

void TsXYvector(pPoint_t pPt)
{
	int i, xLoc, yLoc;

	xLoc = yLoc = 0;
	for (i=0; i<8; i++) {
		xLoc += TSC2046_GetAdVal(GET_X_POS);
		yLoc += TSC2046_GetAdVal(GET_Y_POS);
	}
		xLoc /= 8;
		yLoc /=8;

	if(tsCalMode == CAL_MODE) {
		xLoc -= tsCaldta.x_offset;
		yLoc -= tsCaldta.y_offset;

		xLoc =  (int) (xLoc*tsCaldta.x_gainfactor);
		yLoc =  (int) (yLoc*tsCaldta.y_gainfactor);
		if(xLoc < 0) xLoc = 0;
		if(yLoc < 0) yLoc = 0;
		if(yLoc > LCD_YS) yLoc = LCD_YS-1;
		if(xLoc > LCD_XS) xLoc = LCD_XS-1;
		yLoc = LCD_YS-1 - yLoc;
	} 
	pPt->x = xLoc;
	pPt->y = yLoc;
}

void Set_tsCalMode(int mode)
{
	tsCalMode = mode;
}

int Set_tsCalData(pRect_t pRect, pRect_t pRefRect)
{
	if(pRect->XL > TSCAL_MINIMUM || pRect->YD > TSCAL_MINIMUM)
		return -1;
	if(pRect->XR < TSCAL_MAXIMUM || pRect->YU < TSCAL_MAXIMUM)
		return -1;
	if (pRefRect) {
		tsCaldta.x_gainfactor = (float)(pRefRect->XR-pRefRect->XL)/(float)(pRect->XR-pRect->XL);
		tsCaldta.y_gainfactor = (float)(pRefRect->YU-pRefRect->YD)/(float)(pRect->YU-pRect->YD);
		tsCaldta.x_offset = pRect->XL - (float)pRefRect->XL/tsCaldta.x_gainfactor;
		tsCaldta.y_offset = pRect->YD - (float)pRefRect->YD/tsCaldta.y_gainfactor;
	} else {
		tsCaldta.x_offset = pRect->XL;
		tsCaldta.y_offset = pRect->YD;
		tsCaldta.x_gainfactor = (float)LCD_XS/(float)(pRect->XR-pRect->XL);
		tsCaldta.y_gainfactor = (float)LCD_YS/(float)(pRect->YU-pRect->YD);
	}

	return 0;
}

int Get_CalOffset(int xy)
{
	if (xy) return tsCaldta.y_offset;
	return tsCaldta.x_offset;
}

float Get_CalScale(int xy)
{
	if (xy) return tsCaldta.y_gainfactor;
	return tsCaldta.x_gainfactor;
}


int btnSnapshot = 0;
long BtnOneKeyBuf = -1;
int btnpressed;
int _TsChangeState( long btnState ) 
{
	static Point_t pt1, pt2;
	static unsigned long debounce_period;
	static int ts_counter = 0;
	static int state = 0;
	char execDone;

//	#GLOBAL_INIT{btnSnapshot = 0;
//	             state       = 0;
//	             ts_counter  = 0;}

	execDone = TRUE;
	BtnOneKeyBuf  = -1;
	if(btnState == BTNRELEASE) {
		BtnOneKeyBuf = BTNRELEASE;
		btnpressed = 0;
		btnSnapshot = 1;
		state = 0;
		execDone = TRUE;
	} else {
		switch(state) {
		case 0:
			if(TsActive()) {
				TsXYvector(&pt1);
				debounce_period = MS_TIMER + TS_RECHECK;
				state = 1;
				execDone = FALSE;
			}
			break;

		case 1:
			if((long) (MS_TIMER-debounce_period) >= 0 ) {
				execDone = FALSE;
				state = 2;
			}
			break;

		case 2:
			if(TsActive()) {
				TsXYvector(&pt2);
				if(pt2.x >= (pt1.x - 10) && pt2.x <= (pt1.x + 10) && pt2.y >= (pt1.y - 10) && pt2.y <= (pt1.y + 10)) {
					ts_counter++;
					if(ts_counter > 0) {
						pt1.x = (pt1.x+pt2.x)/2;
						pt1.y = (pt1.y+pt2.y)/2;
						BtnOneKeyBuf = ((long)pt1.x<<16) | pt1.y;
						btnpressed = 1;
						btnSnapshot = 1;
						ts_counter = 0;
						state = 0;
						execDone = TRUE;
					} else {
						debounce_period = MS_TIMER + TS_RECHECK;
						execDone = FALSE;
					}
				} else {
					execDone = TRUE;
					ts_counter = 0;
					state = 0;
				}
			} else {
				execDone = TRUE;
				ts_counter = 0;
				state = 0;
			}
			break;

		default:
			execDone = TRUE;
			ts_counter = 0;
			state = 0;
			break;
		}
	}
	return(execDone);
}

void TsScanState( void )
{
	static int ScanState;
	static int StatusByte;
	static unsigned long debounce_period;
	static int TS_StartLow;

	switch(ScanState) {
	case 0:
		if(!(StatusByte = TsActive()))
			TS_StartLow  = TRUE;
		if (TS_StartLow && StatusByte && !btnpressed) {
			ScanState = 1;
			debounce_period = MS_TIMER + TS_ASSERT;
		} else if(!StatusByte && btnpressed) {
			ScanState = 3;
		}
		break;

	case 1:
		if((long) (MS_TIMER-debounce_period) >= 0 )
			ScanState = 2;
		break;

	case 2:
		if(_TsChangeState(!BTNRELEASE)) {
			ScanState = 0;
			if(btnpressed) TS_StartLow = FALSE;
		}
		break;

	case 3:
		_TsChangeState(BTNRELEASE);
		debounce_period = MS_TIMER + TS_RELEASE;
		ScanState = 4;
		TS_StartLow = TRUE;
		break;

	case 4:
		if((long) (MS_TIMER-debounce_period) >= 0 )
			ScanState = 0;
		break;

	default:
		ScanState = 0;
		TS_StartLow = FALSE;
		break;
	}
}

long TsXYBuffer( void )
{
	long tmp;

	tmp = BtnOneKeyBuf;
	BtnOneKeyBuf = -1;
	return tmp;
}

// return 	0:
//			1: pressed
//			2: wait release & update pt
//			-1: release
#define JITTER_LMT 40
int TsScanState1(pPoint_t pPt)
{
	int iRet;
	static Point_t pt;
	static short ScanState=0;

	iRet = TS_WAIT_PRESS;
	switch(ScanState) {
	case 0:
		if (TsActive()) {
			TsXYvector(&pt);
			ScanState++;	
		}
		break;
	case 1:
		if (TsActive()) {
			pPt->x = pt.x;
			pPt->y = pt.y;
			TsXYvector(&pt);
			ScanState++;
			iRet = TS_CHANGE_PRESS;
		} else {
			ScanState = 0;
		}
		break;
	case 2:
		pPt->x = pt.x;
		pPt->y = pt.y;
		if (TsActive()) {
			TsXYvector(&pt);
			if(pPt->x >= (pt.x - JITTER_LMT) && pPt->x <= (pt.x + JITTER_LMT) && 
			   pPt->y >= (pt.y - JITTER_LMT) && pPt->y <= (pt.y + JITTER_LMT)) {
				iRet = TS_WAIT_RELEASE;
			} else {
				iRet = TS_CHANGE_PRESS;
			}
		} else {
			iRet = TS_CHANGE_RELEASE;
			ScanState = 0;
		}
		break;
	default:
		ScanState = 0;
		break;
	}
	return iRet;
}


