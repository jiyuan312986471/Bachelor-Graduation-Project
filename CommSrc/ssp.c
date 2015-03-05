/****************************************************************************
 *   $Id:: ssp.c 5761 2010-12-01 22:24:44Z usb00423                         $
 *   Project: NXP LPC17xx SSP example
 *
 *   Description:
 *     This file contains SSP code example which include SSP initialization, 
 *     SSP interrupt handler, and APIs for SSP access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "LPC177x_8x.h"			/* LPC13xx Peripheral Registers */
#include "ssp.h"

/* statistics of all the interrupts */
volatile uint32_t interrupt0RxStat = 0;
volatile uint32_t interrupt0OverRunStat = 0;
volatile uint32_t interrupt0RxTimeoutStat = 0;
volatile uint32_t interrupt1RxStat = 0;
volatile uint32_t interrupt1OverRunStat = 0;
volatile uint32_t interrupt1RxTimeoutStat = 0;
volatile uint32_t interrupt2RxStat = 0;
volatile uint32_t interrupt2OverRunStat = 0;
volatile uint32_t interrupt2RxTimeoutStat = 0;

/*****************************************************************************
** Function name:		SSP_IRQHandler
**
** Descriptions:		SSP port is used for SPI communication.
**						SSP interrupt handler
**						The algorithm is, if RXFIFO is at least half full, 
**						start receive until it's empty; if TXFIFO is at least
**						half empty, start transmit until it's full.
**						This will maximize the use of both FIFOs and performance.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP0_IRQHandler(void) 
{
  uint32_t regValue;

  regValue = LPC_SSP0->MIS;
  if ( regValue & SSPMIS_RORMIS )	/* Receive overrun interrupt */
  {
	interrupt0OverRunStat++;
	LPC_SSP0->ICR = SSPICR_RORIC;		/* clear interrupt */
  }
  if ( regValue & SSPMIS_RTMIS )	/* Receive timeout interrupt */
  {
	interrupt0RxTimeoutStat++;
	LPC_SSP0->ICR = SSPICR_RTIC;		/* clear interrupt */
  }

  /* please be aware that, in main and ISR, CurrentRxIndex and CurrentTxIndex
  are shared as global variables. It may create some race condition that main
  and ISR manipulate these variables at the same time. SSPSR_BSY checking (polling)
  in both main and ISR could prevent this kind of race condition */
  if ( regValue & SSPMIS_RXMIS )	/* Rx at least half full */
  {
	interrupt0RxStat++;		/* receive until it's empty */		
  }
  return;
}

/*****************************************************************************
** Function name:		SSP_IRQHandler
**
** Descriptions:		SSP port is used for SPI communication.
**						SSP interrupt handler
**						The algorithm is, if RXFIFO is at least half full, 
**						start receive until it's empty; if TXFIFO is at least
**						half empty, start transmit until it's full.
**						This will maximize the use of both FIFOs and performance.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP1_IRQHandler(void) 
{
  uint32_t regValue;

  regValue = LPC_SSP1->MIS;
  if ( regValue & SSPMIS_RORMIS )	/* Receive overrun interrupt */
  {
	interrupt1OverRunStat++;
	LPC_SSP1->ICR = SSPICR_RORIC;		/* clear interrupt */
  }
  if ( regValue & SSPMIS_RTMIS )	/* Receive timeout interrupt */
  {
	interrupt1RxTimeoutStat++;
	LPC_SSP1->ICR = SSPICR_RTIC;		/* clear interrupt */
  }

  /* please be aware that, in main and ISR, CurrentRxIndex and CurrentTxIndex
  are shared as global variables. It may create some race condition that main
  and ISR manipulate these variables at the same time. SSPSR_BSY checking (polling)
  in both main and ISR could prevent this kind of race condition */
  if ( regValue & SSPMIS_RXMIS )	/* Rx at least half full */
  {
	interrupt1RxStat++;		/* receive until it's empty */		
  }
  return;
}

/*****************************************************************************
** Function name:		SSP_IRQHandler
**
** Descriptions:		SSP port is used for SPI communication.
**						SSP interrupt handler
**						The algorithm is, if RXFIFO is at least half full, 
**						start receive until it's empty; if TXFIFO is at least
**						half empty, start transmit until it's full.
**						This will maximize the use of both FIFOs and performance.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP2_IRQHandler(void) 
{
  uint32_t regValue;

  regValue = LPC_SSP2->MIS;
  if ( regValue & SSPMIS_RORMIS )	/* Receive overrun interrupt */
  {
	interrupt2OverRunStat++;
	LPC_SSP2->ICR = SSPICR_RORIC;		/* clear interrupt */
  }
  if ( regValue & SSPMIS_RTMIS )	/* Receive timeout interrupt */
  {
	interrupt2RxTimeoutStat++;
	LPC_SSP2->ICR = SSPICR_RTIC;		/* clear interrupt */
  }

  /* please be aware that, in main and ISR, CurrentRxIndex and CurrentTxIndex
  are shared as global variables. It may create some race condition that main
  and ISR manipulate these variables at the same time. SSPSR_BSY checking (polling)
  in both main and ISR could prevent this kind of race condition */
  if ( regValue & SSPMIS_RXMIS )	/* Rx at least half full */
  {
	interrupt2RxStat++;		/* receive until it's empty */		
  }
  return;
}

/*****************************************************************************
** Function name:		SSP0_SSELSetDirection
**
** Descriptions:		SSP0 CS manual set, direction is output, default is high 
**				
** parameters:			Location
** Returned value:		None
** 
*****************************************************************************/
void SSP_SSELSetDirection( uint32_t portnum, uint32_t location )
{
  if ( portnum == 0 )
  {
    switch ( location )
    {
	  case 0:
	    LPC_IOCON->P2_23 &= ~0x07;
	    LPC_GPIO2->DIR |= (0x1<<23);
        /* port2, bit 23(SSEL) is set to GPIO output and high */
	    LPC_GPIO2->SET |= (0x1<<23);
	  break;
	  case 1:
	    LPC_IOCON->P1_21 &= ~0x07;
	    LPC_GPIO1->DIR |= (0x1<<21);
	    /* port1, bit 21(SSEL) is set to GPIO output and high */
	    LPC_GPIO1->SET |= (0x1<<21);
	  break;
	  case 2:
        LPC_IOCON->P1_28 &= ~0x07;
        LPC_GPIO1->DIR |= (0x1<<28);
	    /* port1, bit 28(SSEL) is set to GPIO output and high */
	    LPC_GPIO1->SET |= (0x1<<28);
	  break;
	  case 3:
	    LPC_IOCON->P0_16 &= ~0x07;
	    LPC_GPIO0->DIR |= (0x1<<16);
	    /* port0, bit 16(SSEL) is set to GPIO output and high */
	    LPC_GPIO0->SET |= (0x1<<16);
	  break;
    }
  }
  else if ( portnum == 1 )
  {
    switch ( location )
    {
	  case 0:
	    LPC_IOCON->P0_14 &= ~0x07;
	    LPC_GPIO0->DIR |= (0x1<<14);
        /* port0, bit 14(SSEL) is set to GPIO output and high */
	    LPC_GPIO0->SET |= (0x1<<14);
	  break;
	  case 1:
	    LPC_IOCON->P0_6 &= ~0x07;
	    LPC_GPIO0->DIR |= (0x1<<6);
	    /* port0, bit 6(SSEL) is set to GPIO output and high */
	    LPC_GPIO0->SET |= (0x1<<6);
	  break;
	  case 2:
        LPC_IOCON->P4_21 &= ~0x07;
        LPC_GPIO4->DIR |= (0x1<<21);
	    /* port4, bit 21(SSEL) is set to GPIO output and high */
	    LPC_GPIO4->SET |= (0x1<<21);
	  break;
	  case 3:
	    LPC_IOCON->P0_6 &= ~0x07;
	    LPC_GPIO0->DIR |= (0x1<<6);
	    /* port0, bit 6(SSEL) is set to GPIO output and high */
	    LPC_GPIO0->SET |= (0x1<<6);
	  break;
    }
  }
  else if ( portnum == 2 )
  {
    switch ( location )
    {
	  case 0:
	    LPC_IOCON->P5_3 &= ~0x07;
	    LPC_GPIO5->DIR |= (0x1<<3);
        /* port5, bit 3(SSEL) is set to GPIO output and high */
	    LPC_GPIO5->SET |= (0x1<<3);
	  break;
	  case 1:
	    LPC_IOCON->P1_8 &= ~0x07;
	    LPC_GPIO1->DIR |= (0x1<<8);
	    /* port1, bit 8(SSEL) is set to GPIO output and high */
	    LPC_GPIO1->SET |= (0x1<<8);
	  break;
	  default:
	  break;
    }
  }
  return;
}

/*****************************************************************************
** Function name:		SSP0_SSELToggle
**
** Descriptions:		SSP0 CS manual set
**				
** parameters:			Location, toggle(1 is high, 0 is low)
** Returned value:		None
** 
*****************************************************************************/
void SSP_SSELToggle( uint32_t portnum, uint32_t location, uint32_t toggle )
{
  if ( portnum == 0 )
  {
    switch ( location )
    {
	  case 0:
	    if ( !toggle )
		  LPC_GPIO2->CLR |= (0x1<<23);
	    else
		  LPC_GPIO2->SET |= (0x1<<23);	  
	  break;
	  case 1:
	    if ( !toggle )
		  LPC_GPIO1->CLR |= (0x1<<21);
	    else
		  LPC_GPIO1->SET |= (0x1<<21);
	  break;
	  case 2:
	    if ( !toggle )
		  LPC_GPIO1->CLR |= (0x1<<28);
	    else
		  LPC_GPIO1->SET |= (0x1<<28);
	  break;
	  case 3:
	    if ( !toggle )
		  LPC_GPIO0->CLR |= (0x1<<16);
	    else
		  LPC_GPIO0->SET |= (0x1<<16);
	  break;
    }
  }
  else if ( portnum == 1 )
  {
	switch ( location )
    {
	  case 0:
	    if ( !toggle )
		  LPC_GPIO0->CLR |= (0x1<<14);
	    else
		  LPC_GPIO0->SET |= (0x1<<14);	  
	  break;
	  case 1:
	    if ( !toggle )
		  LPC_GPIO1->CLR |= (0x1<<26);
	    else
		  LPC_GPIO1->SET |= (0x1<<26);
	  break;
	  case 2:
	    if ( !toggle )
		  LPC_GPIO4->CLR |= (0x1<<21);
	    else
		  LPC_GPIO4->SET |= (0x1<<21);
	  break;
	  case 3:
	    if ( !toggle )
		  LPC_GPIO0->CLR |= (0x1<<6);
	    else
		  LPC_GPIO0->SET |= (0x1<<6);
	  break;
    }
  }
  else if ( portnum == 2 )
  {
	switch ( location )
    {
	  case 0:
	    if ( !toggle )
		  LPC_GPIO5->CLR |= (0x1<<3);
	    else
		  LPC_GPIO5->SET |= (0x1<<3);	  
	  break;
	  case 1:
	    if ( !toggle )
		  LPC_GPIO1->CLR |= (0x1<<8);
	    else
		  LPC_GPIO1->SET |= (0x1<<8);
	  break;
	  default:
	  break;
    }
  }  
  return;
}

/*****************************************************************************
** Function name:		SSPInit
**
** Descriptions:		SSP port initialization routine
**				
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP0Init( uint32_t location )
{
  uint8_t i, regVal, Dummy=Dummy;

  /* Enable AHB clock to the SSP0. */
  LPC_SC->PCONP |= (0x1<<21);

  /* Further divider is needed on SSP clock. */
  regVal = LPC_SC->PCLKSEL;
  if ( regVal < 4 )
  {
    LPC_SC->PCLKSEL = 4;
  }

  switch ( location )
  {
	case 0:
	  LPC_IOCON->P2_22 &= ~0x07;
	  LPC_IOCON->P2_22 |= 0x02;		/* SSP CLK */
	  LPC_IOCON->P2_23 &= ~0x07;	
	  LPC_IOCON->P2_23 |= 0x02;		/* SSP SSEL */
	  LPC_IOCON->P2_26 &= ~0x07;
	  LPC_IOCON->P2_26 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P2_27 &= ~0x07;	
	  LPC_IOCON->P2_27 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP0_SSEL = 0x00;
//	  LPC_IOCON->LOC_SSP0_SCK  = 0x01;
//	  LPC_IOCON->LOC_SSP0_MOSI = 0x00;
//	  LPC_IOCON->LOC_SSP0_MISO = 0x00;
	break;

	case 1:
	  LPC_IOCON->P1_20 &= ~0x07;
	  LPC_IOCON->P1_20 |= 0x05;		/* SSP CLK */
	  LPC_IOCON->P1_21 &= ~0x07;	
	  LPC_IOCON->P1_21 |= 0x03;		/* SSP SSEL */
	  LPC_IOCON->P1_23 &= ~0x07;
	  LPC_IOCON->P1_23 |= 0x05;		/* SSP MISO */
	  LPC_IOCON->P1_24 &= ~0x07;	
	  LPC_IOCON->P1_24 |= 0x05;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP0_SSEL = 0x01;
//	  LPC_IOCON->LOC_SSP0_SCK  = 0x00;
//	  LPC_IOCON->LOC_SSP0_MOSI = 0x01;
//	  LPC_IOCON->LOC_SSP0_MISO = 0x01;
	break;

	case 2:
	  LPC_IOCON->P1_20 &= ~0x07;
	  LPC_IOCON->P1_20 |= 0x05;		/* SSP CLK */
	  LPC_IOCON->P1_28 &= ~0x07;	
	  LPC_IOCON->P1_28 |= 0x05;		/* SSP SSEL */
	  LPC_IOCON->P1_23 &= ~0x07;
	  LPC_IOCON->P1_23 |= 0x05;		/* SSP MISO */
	  LPC_IOCON->P1_24 &= ~0x07;	
	  LPC_IOCON->P1_24 |= 0x05;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP0_SSEL = 0x02;
//	  LPC_IOCON->LOC_SSP0_SCK  = 0x00;
//	  LPC_IOCON->LOC_SSP0_MOSI = 0x01;
//	  LPC_IOCON->LOC_SSP0_MISO = 0x01;
	break;

	case 3:
	  LPC_IOCON->P0_15 &= ~0x07;
	  LPC_IOCON->P0_15 |= 0x02;		/* SSP CLK */
	  LPC_IOCON->P0_16 &= ~0x07;	
	  LPC_IOCON->P0_16 |= 0x02;		/* SSP SSEL */
	  LPC_IOCON->P0_17 &= ~0x07;
	  LPC_IOCON->P0_17 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P0_18 &= ~0x07;	
	  LPC_IOCON->P0_18 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP0_SSEL = 0x03;
//	  LPC_IOCON->LOC_SSP0_SCK  = 0x02;
//	  LPC_IOCON->LOC_SSP0_MOSI = 0x02;
//	  LPC_IOCON->LOC_SSP0_MISO = 0x02;
	break;
  }
  
#if !USE_CS
  SSP_SSELSetDirection( 0, location );
#endif
		
  /* Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15 */
  LPC_SSP0->CR0 = 0x0707;

  /* SSPCPSR clock prescale register, master mode, minimum divisor is 0x02 */
  LPC_SSP0->CPSR = 0x2;

  for ( i = 0; i < FIFOSIZE; i++ )
  {
	Dummy = LPC_SSP0->DR;		/* clear the RxFIFO */
  }

  /* Enable the SSP Interrupt */
  NVIC_EnableIRQ(SSP0_IRQn);
	
  /* Device select as master, SSP Enabled */
#if LOOPBACK_MODE
  LPC_SSP0->CR1 = SSPCR1_LBM | SSPCR1_SSE;
#else
#if SSP_SLAVE
  /* Slave mode */
  if ( LPC_SSP0->CR1 & SSPCR1_SSE )
  {
	/* The slave bit can't be set until SSE bit is zero. */
	LPC_SSP0->CR1 &= ~SSPCR1_SSE;
  }
  LPC_SSP0->CR1 = SSPCR1_MS;		/* Enable slave bit first */
  LPC_SSP0->CR1 |= SSPCR1_SSE;	/* Enable SSP */
#else
  /* Master mode */
  LPC_SSP0->CR1 = SSPCR1_SSE;
#endif
#endif
  /* Set SSPINMS registers to enable interrupts */
  /* enable all error related interrupts */
  LPC_SSP0->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
  return;
}

/*****************************************************************************
** Function name:		SSPInit
**
** Descriptions:		SSP port initialization routine
**				
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP1Init( uint32_t location )
{
  uint8_t i, regVal, Dummy=Dummy;

  /* Enable AHB clock to the SSP1. */
  LPC_SC->PCONP |= (0x1<<10);

  /* Further divider is needed on SSP clock. */
  regVal = LPC_SC->PCLKSEL;
  if ( regVal < 4 )
  {
    LPC_SC->PCLKSEL = 4;
  }

  switch ( location )
  {
	case 0:
	  LPC_IOCON->P0_7  &= ~0x07;
	  LPC_IOCON->P0_7  |= 0x02;		/* SSP CLK */
	  LPC_IOCON->P0_14 &= ~0x07;	
	  LPC_IOCON->P0_14 |= 0x02;		/* SSP SSEL */
	  LPC_IOCON->P0_12 &= ~0x07;
	  LPC_IOCON->P0_12 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P0_13 &= ~0x07;	
	  LPC_IOCON->P0_13 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP1_SSEL = 0x00;
//	  LPC_IOCON->LOC_SSP1_SCK  = 0x03;
//	  LPC_IOCON->LOC_SSP1_MOSI = 0x00;
//	  LPC_IOCON->LOC_SSP1_MISO = 0x00;
	break;

	case 1:
	  LPC_IOCON->P1_19 &= ~0x07;
	  LPC_IOCON->P1_19 |= 0x05;		/* SSP CLK */
	  LPC_IOCON->P0_6 &= ~0x07;	
	  LPC_IOCON->P0_6 |= 0x05;		/* SSP SSEL */
	  LPC_IOCON->P0_12 &= ~0x07;
	  LPC_IOCON->P0_12 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P0_13 &= ~0x07;	
	  LPC_IOCON->P0_13 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP1_SSEL = 0x01;
//	  LPC_IOCON->LOC_SSP1_SCK  = 0x01;
//	  LPC_IOCON->LOC_SSP1_MOSI = 0x01;
//	  LPC_IOCON->LOC_SSP1_MISO = 0x01;
	break;

	case 2:
	  LPC_IOCON->P4_20 &= ~0x07;
	  LPC_IOCON->P4_20 |= 0x03;		/* SSP CLK */
	  LPC_IOCON->P4_21 &= ~0x07;	
	  LPC_IOCON->P4_21 |= 0x03;		/* SSP SSEL */
	  LPC_IOCON->P4_22 &= ~0x07;
	  LPC_IOCON->P4_22 |= 0x03;		/* SSP MISO */
	  LPC_IOCON->P4_23 &= ~0x07;	
	  LPC_IOCON->P4_23 |= 0x03;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP1_SSEL = 0x02;
//	  LPC_IOCON->LOC_SSP1_SCK  = 0x02;
//	  LPC_IOCON->LOC_SSP1_MOSI = 0x02;
//	  LPC_IOCON->LOC_SSP1_MISO = 0x02;
	break;

	case 3:
	  LPC_IOCON->P0_7 &= ~0x07;
	  LPC_IOCON->P0_7 |= 0x02;		/* SSP CLK */
	  LPC_IOCON->P0_6 &= ~0x07;	
	  LPC_IOCON->P0_6 |= 0x02;		/* SSP SSEL */
	  LPC_IOCON->P0_8 &= ~0x07;
	  LPC_IOCON->P0_8 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P0_9 &= ~0x07;	
	  LPC_IOCON->P0_9 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP1_SSEL = 0x03;
//	  LPC_IOCON->LOC_SSP1_SCK  = 0x03;
//	  LPC_IOCON->LOC_SSP1_MOSI = 0x03;
//	  LPC_IOCON->LOC_SSP1_MISO = 0x03;
	break;
  }
  
#if !USE_CS
  SSP_SSELSetDirection( 1, location );
#endif
		
  /* Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15 */
  LPC_SSP1->CR0 = 0x0707;

  /* SSPCPSR clock prescale register, master mode, minimum divisor is 0x02 */
  LPC_SSP1->CPSR = 0x2;

  for ( i = 0; i < FIFOSIZE; i++ )
  {
	Dummy = LPC_SSP1->DR;		/* clear the RxFIFO */
  }

  /* Enable the SSP Interrupt */
  NVIC_EnableIRQ(SSP1_IRQn);
	
  /* Device select as master, SSP Enabled */
#if LOOPBACK_MODE
  LPC_SSP1->CR1 = SSPCR1_LBM | SSPCR1_SSE;
#else
#if SSP_SLAVE
  /* Slave mode */
  if ( LPC_SSP1->CR1 & SSPCR1_SSE )
  {
	/* The slave bit can't be set until SSE bit is zero. */
	LPC_SSP1->CR1 &= ~SSPCR1_SSE;
  }
  LPC_SSP1->CR1 = SSPCR1_MS;		/* Enable slave bit first */
  LPC_SSP1->CR1 |= SSPCR1_SSE;	/* Enable SSP */
#else
  /* Master mode */
  LPC_SSP1->CR1 = SSPCR1_SSE;
#endif
#endif
  /* Set SSPINMS registers to enable interrupts */
  /* enable all error related interrupts */
  LPC_SSP1->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
  return;
}

/*****************************************************************************
** Function name:		SSPInit
**
** Descriptions:		SSP port initialization routine
**				
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP2Init( uint32_t location )
{
  uint8_t i, regVal, Dummy=Dummy;

  /* Enable AHB clock to the SSP2. */
  LPC_SC->PCONP |= (0x1<<20);

  /* Further divider is needed on SSP clock. */
  regVal = LPC_SC->PCLKSEL;
  if ( regVal < 4 )
  {
    LPC_SC->PCLKSEL = 4;
  }

  switch ( location )
  {
	case 0:
#if 0
      /* This function is no longer a valid option per design engineer. */
	  LPC_IOCON->P5_2 &= ~0x07;
	  LPC_IOCON->P5_2 |= 0x02;		/* SSP CLK */
	  LPC_IOCON->P5_3 &= ~0x07;	
	  LPC_IOCON->P5_3 |= 0x02;		/* SSP SSEL */
	  LPC_IOCON->P5_1 &= ~0x07;
	  LPC_IOCON->P5_1 |= 0x02;		/* SSP MISO */
	  LPC_IOCON->P5_0 &= ~0x07;	
	  LPC_IOCON->P5_0 |= 0x02;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP2_SSEL = 0x00;
//	  LPC_IOCON->LOC_SSP2_SCK  = 0x00;
//	  LPC_IOCON->LOC_SSP2_MOSI = 0x00;
//	  LPC_IOCON->LOC_SSP2_MISO = 0x00;
#endif
	break;

	case 1:
	  LPC_IOCON->P1_0 &= ~0x07;
	  LPC_IOCON->P1_0 |= 0x04;		/* SSP CLK */
	  LPC_IOCON->P1_8 &= ~0x07;	
	  LPC_IOCON->P1_8 |= 0x04;		/* SSP SSEL */
	  LPC_IOCON->P1_4 &= ~0x07;
	  LPC_IOCON->P1_4 |= 0x04;		/* SSP MISO */
	  LPC_IOCON->P1_1 &= ~0x07;	
	  LPC_IOCON->P1_1 |= 0x04;		/* SSP MOSI */
//	  LPC_IOCON->LOC_SSP2_SSEL = 0x01;
//	  LPC_IOCON->LOC_SSP2_SCK  = 0x01;
//	  LPC_IOCON->LOC_SSP2_MOSI = 0x01;
//	  LPC_IOCON->LOC_SSP2_MISO = 0x01;
	break;

	default:
	break;
  }
  
#if !USE_CS
  SSP_SSELSetDirection( 2, location );
#endif
		
  /* Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15 */
  LPC_SSP2->CR0 = 0x0707;

  /* SSPCPSR clock prescale register, master mode, minimum divisor is 0x02 */
  LPC_SSP2->CPSR = 0x2;

  for ( i = 0; i < FIFOSIZE; i++ )
  {
	Dummy = LPC_SSP2->DR;		/* clear the RxFIFO */
  }

  /* Enable the SSP Interrupt */
  NVIC_EnableIRQ(SSP2_IRQn);
	
  /* Device select as master, SSP Enabled */
#if LOOPBACK_MODE
  LPC_SSP2->CR1 = SSPCR1_LBM | SSPCR1_SSE;
#else
#if SSP_SLAVE
  /* Slave mode */
  if ( LPC_SSP2->CR1 & SSPCR1_SSE )
  {
	/* The slave bit can't be set until SSE bit is zero. */
	LPC_SSP2->CR1 &= ~SSPCR1_SSE;
  }
  LPC_SSP2->CR1 = SSPCR1_MS;		/* Enable slave bit first */
  LPC_SSP2->CR1 |= SSPCR1_SSE;	/* Enable SSP */
#else
  /* Master mode */
  LPC_SSP2->CR1 = SSPCR1_SSE;
#endif
#endif
  /* Set SSPINMS registers to enable interrupts */
  /* enable all error related interrupts */
  LPC_SSP2->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
  return;
}

/*****************************************************************************
** Function name:		SSPSend
**
** Descriptions:		Send a block of data to the SSP port, the 
**						first parameter is the buffer pointer, the 2nd 
**						parameter is the block length.
**
** parameters:			buffer pointer, and the block length
** Returned value:		None
** 
*****************************************************************************/
void SSPSend( uint32_t portnum, uint8_t *buf, uint32_t Length )
{
  uint32_t i;
  uint8_t Dummy = Dummy;
    
  for ( i = 0; i < Length; i++ )
  {
    if ( portnum == 0 )
	{
      /* Move on only if NOT busy and TX FIFO not full. */
	  while ( (LPC_SSP0->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	  LPC_SSP0->DR = *buf;
	  buf++;
#if !LOOPBACK_MODE
	  while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	  /* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
	  on MISO. Otherwise, when SSP0Receive() is called, previous data byte
	  is left in the FIFO. */
	  Dummy = LPC_SSP0->DR;
#else
	  /* Wait until the Busy bit is cleared. */
	  while ( LPC_SSP0->SR & SSPSR_BSY );
#endif
    }
    else if ( portnum == 1 )
	{
	  /* Move on only if NOT busy and TX FIFO not full. */
	  while ( (LPC_SSP1->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	  LPC_SSP1->DR = *buf;
	  buf++;
#if !LOOPBACK_MODE
	  while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	  /* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
	  on MISO. Otherwise, when SSP0Receive() is called, previous data byte
	  is left in the FIFO. */
	  Dummy = LPC_SSP1->DR;
#else
	  /* Wait until the Busy bit is cleared. */
	  while ( LPC_SSP1->SR & SSPSR_BSY );
#endif
    }
	else if ( portnum == 2 )
	{
      /* Move on only if NOT busy and TX FIFO not full. */
	  while ( (LPC_SSP2->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	  LPC_SSP2->DR = *buf;
	  buf++;
#if !LOOPBACK_MODE
	  while ( (LPC_SSP2->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	  /* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
	  on MISO. Otherwise, when SSP0Receive() is called, previous data byte
	  is left in the FIFO. */
	  Dummy = LPC_SSP2->DR;
#else
	  /* Wait until the Busy bit is cleared. */
	  while ( LPC_SSP2->SR & SSPSR_BSY );
#endif
	}
  }
  return; 
}

/*****************************************************************************
** Function name:		SSPReceive
** Descriptions:		the module will receive a block of data from 
**						the SSP, the 2nd parameter is the block 
**						length.
** parameters:			buffer pointer, and block length
** Returned value:		None
** 
*****************************************************************************/
void SSPReceive( uint32_t portnum, uint8_t *buf, uint32_t Length )
{
  uint32_t i;
 
  for ( i = 0; i < Length; i++ )
  {
	/* As long as Receive FIFO is not empty, I can always receive. */
	/* If it's a loopback test, clock is shared for both TX and RX,
	no need to write dummy byte to get clock to get the data */
	/* if it's a peer-to-peer communication, SSPDR needs to be written
	before a read can take place. */
    if ( portnum == 0 )
    {
#if !LOOPBACK_MODE
#if SSP_SLAVE
	  while ( !(LPC_SSP0->SR & SSPSR_RNE) );
#else
	  LPC_SSP0->DR = 0xFF;
	  /* Wait until the Busy bit is cleared */
	  while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
#endif
#else
	  while ( !(LPC_SSP0->SR & SSPSR_RNE) );
#endif
	  *buf++ = LPC_SSP0->DR;
    }
	else if ( portnum == 1 )
	{
#if !LOOPBACK_MODE
#if SSP_SLAVE
	  while ( !(LPC_SSP1->SR & SSPSR_RNE) );
#else
	  LPC_SSP1->DR = 0x00;
	  /* Wait until the Busy bit is cleared */
	  while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
#endif
#else
	  while ( !(LPC_SSP1->SR & SSPSR_RNE) );
#endif
	  *buf++ = LPC_SSP1->DR;
	}
	else if ( portnum == 2 )
	{
#if !LOOPBACK_MODE
#if SSP_SLAVE
	  while ( !(LPC_SSP2->SR & SSPSR_RNE) );
#else
	  LPC_SSP2->DR = 0xFF;
	  /* Wait until the Busy bit is cleared */
	  while ( (LPC_SSP2->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
#endif
#else
	  while ( !(LPC_SSP2->SR & SSPSR_RNE) );
#endif
	  *buf++ = LPC_SSP2->DR;
	} 	
  }
  return; 
}

/******************************************************************************
**                            End Of File
******************************************************************************/

