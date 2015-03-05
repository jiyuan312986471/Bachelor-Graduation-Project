/*-----------------------------------------------------------------------------
 * Name:    TSC_2046.c
 * Purpose: Touchscreen controller routines for the tsc2046
 *----------------------------------------------------------------------------*/

#include "LPC177x_8x.h"
#include <stdint.h> 
#include "TSC.h"
//#include "I2C.h"

#ifdef SLK_BOARD
#define TSC2046_CS	(0x1<<6)	// P0.6(SSEL1)
#define EN_TSC2046_CS()	(LPC_GPIO0->CLR |= TSC2046_CS)
#define DIS_TSC2046_CS()	(LPC_GPIO0->SET |= TSC2046_CS)
#define TSC2046_BUSY	(0x1<<14)	// P2.14
#define TSC2046_PINQ	(0x1<<15)	// P2.15
#define TSC2046_BUSY_STATE()	(LPC_GPIO2->PIN & TSC2046_BUSY)
#define TSC2046_PINQ_STATE()	(LPC_GPIO2->PIN & TSC2046_PINQ)

#define TSC2046_DCLK 	(0x1<<19)	// P1.19(SCK1)
#define TSC2046_DIN 	(0x1<<12)	// P0.12(MOSI1)
#define TSC2046_DOUT 	(0x1<<13)	// P0.13(MISO1)

#define GET_X_POS (0x82 | (0x05<<4)) 
#define GET_Y_POS (0x82 | (0x01<<4))  
#define GET_Z1_POS (0x82 | (0x03<<4)) 
#define GET_Z2_POS (0x82 | (0x04<<4)) 
#else
#define TSC2046_CS	(0x1<<23)	// P2.23(SSEL0)
#define EN_TSC2046_CS()	(LPC_GPIO2->CLR |= TSC2046_CS)
#define DIS_TSC2046_CS()	(LPC_GPIO2->SET |= TSC2046_CS)
#define TSC2046_BUSY	(0x1<<13)	// P1.13


#define TSC2046_PINQ	(0x1<<11)	// P2.11  -- NE2 C-A
//#define TSC2046_PINQ	(0x1<<24)	// P0.24

#define TSC2046_BUSY_STATE()	(LPC_GPIO1->PIN & TSC2046_BUSY)
#define TSC2046_PINQ_STATE()	(LPC_GPIO2->PIN & TSC2046_PINQ)  //-- NE2 C-A
//#define TSC2046_PINQ_STATE()	(LPC_GPIO0->PIN & TSC2046_PINQ)

#define TSC2046_DCLK 	(0x1<<22)	// P2.22(SCK0)
#define TSC2046_DIN 	(0x1<<27)	// P2.27(MOSI0)
#define TSC2046_DOUT 	(0x1<<26)	// P2.26(MISO0)

#define GET_X_POS (0x82 | (0x05<<4)) 
#define GET_Y_POS (0x82 | (0x01<<4))  
#define GET_Z1_POS (0x82 | (0x03<<4)) 
#define GET_Z2_POS (0x82 | (0x04<<4)) 
#endif



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


volatile int interrupt1RxStat = 0;
volatile int interrupt1OverRunStat = 0;
volatile int interrupt1RxTimeoutStat = 0;
#ifdef SLK_BOARD
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
#else
void SSP0_IRQHandler(void) 
{
	uint32_t regValue;

	regValue = LPC_SSP0->MIS;
	if ( regValue & SSPMIS_RORMIS ) {	// Receive overrun interrupt
		interrupt1OverRunStat++;
		LPC_SSP0->ICR = SSPICR_RORIC;	// clear interrupt
	}
	if ( regValue & SSPMIS_RTMIS ) {	// Receive timeout interrupt
		interrupt1RxTimeoutStat++;
		LPC_SSP0->ICR = SSPICR_RTIC;		// clear interrupt
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
#endif

int TSC2046_GetAdVal(uint8_t cmd)
{
	int iRet;
	uint8_t Dummy;

#ifdef SLK_BOARD
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
#else
	EN_TSC2046_CS();
	while ( (LPC_SSP0->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
//	for (iRet=0; iRet<1000; iRet++);
	LPC_SSP0->DR = cmd;
	while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP0->DR;

//	while(TSC2046_BUSY_STATE());
//	for (iRet=0; iRet<1000; iRet++);
	LPC_SSP0->DR = 0x00;
	while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP0->DR;
	LPC_SSP0->DR = 0x00;
	iRet = Dummy &= 0x7F;
	iRet <<= 5;
	while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	Dummy = LPC_SSP0->DR;
	iRet |= (Dummy>>3);
	DIS_TSC2046_CS();
#endif
return iRet;
}

/*-----------------------------------------------------------------------------
 *      TSC_Init:  Initialize touchscreen controller
 *
 *  Parameter:  (none)
 *  Return:     0 on success, nonzero on error
 *----------------------------------------------------------------------------*/
uint32_t TSC_Init (void) 
{
	int i;
	uint8_t Dummy=Dummy;

#ifdef SLK_BOARD
	LPC_SC->PCONP |= (0x1<<10);	// Enable AHB clock to the SSP1.
	LPC_IOCON->P1_19 &= ~0x07;
	LPC_IOCON->P1_19 |= 0x05;		// SSP CLK
	LPC_IOCON->P0_12 &= ~0x07;
	LPC_IOCON->P0_12 |= 0x02;		// SSP MISO
	LPC_IOCON->P0_13 &= ~0x07;	
	LPC_IOCON->P0_13 |= 0x02;		// SSP MOSI
	LPC_IOCON->P0_6 &= ~0x07;	
//	LPC_IOCON->P0_6 |= 0x05;		// SSP SSEL
	LPC_GPIO0->DIR |= TSC2046_CS;
//	LPC_GPIO0->SET |= (0x1<<6);
	DIS_TSC2046_CS();

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
#else
	LPC_SC->PCONP |= (0x1<<21);	// Enable AHB clock to the SSP0.
	LPC_IOCON->P2_22 &= ~0x07;
	LPC_IOCON->P2_22 |= 0x02;		// SSP CLK
	LPC_IOCON->P2_26 &= ~0x07;
	LPC_IOCON->P2_26 |= 0x02;		// SSP MISO
	LPC_IOCON->P2_27 &= ~0x07;	
	LPC_IOCON->P2_27 |= 0x02;		// SSP MOSI
	LPC_IOCON->P2_23 &= ~0x07;	
//	LPC_IOCON->P2_23 |= 0x02;		// SSP SSEL

	LPC_GPIO2->DIR |= TSC2046_CS;
//	LPC_GPIO2->SET |= (0x1<<23);
	DIS_TSC2046_CS();

// Serial Clock Rate: the bit frequency is PCLK / (CPSDVSR*[SCR+1]).
// Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15
	LPC_SSP0->CR0 = 0x1F07;		// SCR=31, CPSDVSR =2, 60(pclk)/2/(31+1)=0.975Mhz 

// SSPCPSR clock prescale register, master mode, minimum divisor is 0x02
	LPC_SSP0->CPSR = 0x2;

	for ( i = 0; i < SSP_FIFOSIZE; i++ ) Dummy = LPC_SSP0->DR;	// clear the RxFIFO
  
	NVIC_EnableIRQ(SSP0_IRQn);	// Enable the SSP Interrupt

// Set SSPINMS registers to enable interrupts enable all error related interrupts
	LPC_SSP0->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
	LPC_SSP0->CR1 = SSPCR1_SSE;	// Master mode
#endif
return (0);
}

/*-----------------------------------------------------------------------------
 *      TSC_TouchDet: Check if touch of the screen is detected
 *
 * Parameters: (none)
 *
 * Return:     0 if touch not detected, nonzero otherwise
 *----------------------------------------------------------------------------*/
uint32_t TSC_TouchDet (void) 
{
	return TSC2046_PINQ_STATE() ? 0:1;
}

/*-----------------------------------------------------------------------------
 * TSC_GetData: Read coordinates from registers and write them into TSC_DATA structure.
 * Parameters: tscd - pointer to TSC_DATA structure
 * Return:     0 on success, nonzero on error
 *----------------------------------------------------------------------------*/
#define TS_DEBOUNCE_MAX                10
#define TS_DEBOUNCE_TOL                3
#ifndef   ABS
  #define ABS(x)                       (((int32_t)(x)) < 0 ? (-x) : (x))
#endif

#ifdef TSC_DBG
volatile int tcX,tcY,tcZ,tcZ1,tcZ2;
#endif
uint32_t TSC_GetData (TSC_DATA *tscd) 
{
	int i;

#if 0	
	tscd->x = 0;
	for (i=0; i<8; i++)	tscd->x += TSC2046_GetAdVal(GET_X_POS);
	tscd->x /= 8;
	tscd->y = 0;
	for (i=0; i<8; i++)	tscd->y += TSC2046_GetAdVal(GET_Y_POS);;
	tscd->y /= 8;
	tscd->z = TSC2046_GetAdVal(GET_Z1_POS);
#endif
#if 1
	int tmp, z1, z2;
	tscd->y = TSC2046_GetAdVal(GET_Y_POS);
	for (i=1; i<8; i++)	tscd->y += TSC2046_GetAdVal(GET_Y_POS);;
	tscd->y /= 8;
	tscd->x = TSC2046_GetAdVal(GET_X_POS);
	for (i=1; i<8; i++)	tscd->x += TSC2046_GetAdVal(GET_X_POS);
	tscd->x /= 8;
	z1 = TSC2046_GetAdVal(GET_Z1_POS);
	z2 = TSC2046_GetAdVal(GET_Z2_POS);
#ifdef TSC_DBG
	tcX=tscd->x;
	tcY=tscd->y;
	tcZ1=z1;
	tcZ2=z2;
#endif
/*	for (i = 0; i < TS_DEBOUNCE_MAX; i++) {
		tmp = TSC2046_GetAdVal(GET_X_POS);
		if (ABS(tmp - tscd->x) <= TS_DEBOUNCE_TOL) break;
		tscd->x = tmp;
	}
	for (i = 0; i < TS_DEBOUNCE_MAX; i++) {
		tmp = TSC2046_GetAdVal(GET_Y_POS);
		if (ABS(tmp - tscd->y) <= TS_DEBOUNCE_TOL) break;
		tscd->y = tmp;
	}*/
	tscd->z = tscd->x*(z2-z1)/z1;
#ifdef TSC_DBG
	tcZ=tscd->z;
#endif
	
#endif
	
	return 0;
}

/*-----------------------------------------------------------------------------
 * End of file
 *----------------------------------------------------------------------------*/
