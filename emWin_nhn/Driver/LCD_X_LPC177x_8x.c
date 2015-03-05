/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2011  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.12 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCD_X_LPC177x_8x.c
Purpose     : Port routines for LPC1800 SPI & RGB
----------------------------------------------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Hardware configuration
*
**********************************************************************
*/

#include <LPC177x_8x.h>
#include "system_LPC177x_8x.h"
#include "sdram.h"
#include "LCD_X_LPC177x_8x.h"

/* SPI Interface: SSP0
 
   PINS: 
   - CS  = PF_1 (GPIO7[16])
   - SCK = PF_0 (SCK0)
   - SDO = PF_2 (MISO0)
   - SDI = PF_3 (MOSI0)
*/

#define PIN_CS      (1 << 16)

/* SPI_SR - bit definitions */
#define TFE         0x01
#define RNE         0x04
#define BSY         0x10

/* SCU pin configuration definitions */
#define SPI_PIN_SET ((1 << 7) | (1 << 6) | (1 << 5))
#define LCD_PIN_SET ((1 << 7) | (1 << 6) | (1 << 5))
#define LCD_NPR_SET ((1 << 5) | (1 << 4))

/* Clock Control Unit register bits */
#define CCU_CLK_CFG_RUN   (1 << 0)
#define CCU_CLK_CFG_AUTO  (1 << 1)
#define CCU_CLK_STAT_RUN  (1 << 0)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Static code
*
*********************************************************************
*/

#define LCD_CS(x) ((x) ? (LPC_GPIO_PORT->SET[7] = PIN_CS) : (LPC_GPIO_PORT->CLR[7] = PIN_CS))

/*********************************************************************
*
*       SPI_Transfer
*
* Purpose:
*   Transfer (Write/Read) 1 byte, MSB first
*/
static unsigned char SPI_Transfer(unsigned char byte) {
  LPC_SSP0->DR = byte;
  while (!(LPC_SSP0->SR & RNE));        // Wait for send to finish
  return (LPC_SSP0->DR);
}

/*********************************************************************
*
*       Exported code
*
*********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Init
*
* Purpose:
*   This routine should be called from your application program
*   to set port pins to their initial values
*/
void LCD_X_Init(void) {
	int  i;
	uint32_t *pDst = (uint32_t *)LCD_VRAM_BASE_ADDR;

	// Assign pins
#ifdef SLK_BOARD
	LPC_IOCON->P2_9 = 0x06;		// VD3, 	R0
	LPC_IOCON->P2_6  = 0x07;	// VD4,		R1
	LPC_IOCON->P2_7  = 0x07;	// VD5,		R2
	LPC_IOCON->P4_28 = 0x05;	// VD6,		R3
	LPC_IOCON->P4_29 = 0x05;	// VD7,		R4
#else
	LPC_IOCON->P4_29 = 0x07;	// VD3, 	R0 (LPC_IOCON->P2_9 = 0x06)
	LPC_IOCON->P2_6  = 0x07;	// VD4,		R1
	LPC_IOCON->P2_7  = 0x07;	// VD5,		R2
	LPC_IOCON->P2_8	 = 0x07;	// VD6,		R3 (LPC_IOCON->P4_28 = 0x05)
	LPC_IOCON->P2_9  = 0x07;	// VD7,		R4 (LPC_IOCON->P4_29 = 0x05)
#endif
	LPC_IOCON->P1_20 = 0x07;	// VD10,	G0
	LPC_IOCON->P1_21 = 0x07;	// VD11,	G1
	LPC_IOCON->P1_22 = 0x07;	// VD12,	G2
	LPC_IOCON->P1_23 = 0x07;	// VD13,	G3
	LPC_IOCON->P1_24 = 0x07;	// VD14,	G4
	LPC_IOCON->P1_25 = 0x07;	// VD15,	G5
	
	LPC_IOCON->P2_13 = 0x07;	// VD19,	B0
	LPC_IOCON->P1_26 = 0x07;	// VD20,	B1
	LPC_IOCON->P1_27 = 0x07;	// VD21,	B2
	LPC_IOCON->P1_28 = 0x07;	// VD22,	B3
	LPC_IOCON->P1_29 = 0x07;	// VD23,	B4
	
	LPC_IOCON->P2_2	= 0x07;	// DCLK
	LPC_IOCON->P2_0	= 0x07;	// DSIP(power)
	LPC_IOCON->P2_5	= 0x07;	// HSYNC
	LPC_IOCON->P2_3	= 0x07;	// VSYNC
	LPC_IOCON->P2_4	= 0x07;	// DataEn

	LPC_IOCON->P2_1	= 0x00;	// Backlight

	/*Back light enable*/
#ifdef SLK_BOARD
	LPC_GPIO2->DIR = (1<<1);
	LPC_GPIO2->SET= (5<<1);
#else
	LPC_GPIO1->DIR = (1<<5);
	LPC_GPIO1->SET= (1<<5);
#endif
	//Turn on LCD clock
	LPC_SC->PCONP |= 1<<0;
	
	// Disable cursor
	LPC_LCD->CRSR_CTRL &=~(1<<0);
	
	// disable GLCD controller	
	LPC_LCD->CTRL = 0;
	
	LPC_LCD->CTRL &= ~(0x07 <<1);
	#ifndef __RAM__
	// RGB565
	LPC_LCD->CTRL |= (6<<1);
	#else
	// RGB888
	LPC_LCD->CTRL |= (5<<1);
	#endif
	
	// TFT panel
	LPC_LCD->CTRL |= (1<<5);
	// single panel
	LPC_LCD->CTRL &= ~(1<<7);
	// notmal output
	LPC_LCD->CTRL &= ~(1<<8);
	// little endian byte order
	LPC_LCD->CTRL &= ~(1<<9);
	// little endian pix order
	LPC_LCD->CTRL &= ~(1<<10);
	// disable power
	LPC_LCD->CTRL &= ~(1<<11);
	// init pixel clock
//	LPC_SC->LCD_CFG = PeripheralClock / ((uint32_t) C_GLCD_PIX_CLK);
	LPC_SC->LCD_CFG = (SystemCoreClock / ((unsigned long) C_GLCD_PIX_CLK))-1;
	// bypass inrenal clk divider
	LPC_LCD->POL |=(1<<26);
	// clock source for the LCD block is HCLK
	LPC_LCD->POL &= ~(1<<5);
	// LCDFP pin is active LOW and inactive HIGH
	LPC_LCD->POL |= (1<<11);
	// LCDLP pin is active LOW and inactive HIGH
	LPC_LCD->POL |= (1<<12);
	// data is driven out into the LCD on the falling edge
	LPC_LCD->POL &= ~(1<<13);
	// active high
	LPC_LCD->POL &= ~(1<<14);
	LPC_LCD->POL &= ~(0x3FF <<16);
	LPC_LCD->POL |= (C_GLCD_H_SIZE-1)<<16;
	
	// init Horizontal Timing
	LPC_LCD->TIMH = 0; //reset TIMH before set value
	LPC_LCD->TIMH |= (C_GLCD_H_BACK_PORCH - 1)<<24;
	LPC_LCD->TIMH |= (C_GLCD_H_FRONT_PORCH - 1)<<16;
	LPC_LCD->TIMH |= (C_GLCD_H_PULSE - 1)<<8;
	LPC_LCD->TIMH |= ((C_GLCD_H_SIZE/16) - 1)<<2;
	
	// init Vertical Timing
	LPC_LCD->TIMV = 0;  //reset TIMV value before setting
	LPC_LCD->TIMV |= (C_GLCD_V_BACK_PORCH)<<24;
	LPC_LCD->TIMV |= (C_GLCD_V_FRONT_PORCH)<<16;
	LPC_LCD->TIMV |= (C_GLCD_V_PULSE - 1)<<10;
	LPC_LCD->TIMV |= C_GLCD_V_SIZE - 1;
	// Frame Base Address doubleword aligned
	LPC_LCD->UPBASE = (unsigned long)LCD_VRAM_BASE_ADDR & ~7UL ;
	LPC_LCD->LPBASE = (unsigned long)LCD_VRAM_BASE_ADDR & ~7UL ;
        // init colour pallet
	LPC_LCD->CTRL   |= (1 <<  0);                 // Enable LCD signals
	LPC_LCD->CTRL   |= (1 << 11);                 // Enable LCD power

//	if(NULL != pPallete) {
//		GLCD_SetPallet(pPallete);
//	}

//	if (NULL == pPain) {
		// clear display memory
		for( i = 0; (C_GLCD_H_SIZE * C_GLCD_V_SIZE) > i; i++) {
	  		*pDst++ = 0;
		}
//	} else {
//		pDst16 = (unsigned short *) LCD_VRAM_BASE_ADDR;
//#ifndef __RAM__
//		pBmp16 = bmpic.pPicStream;	 // ac480x272Pic01;
//		for( i = 0; (C_GLCD_H_SIZE * C_GLCD_V_SIZE) > i; i++) {
//	  		*pDst16++ = *pBmp16++;
//		}
//#else	
		
		// set display memory				
//		for (y=0; y<C_GLCD_V_SIZE / 2; y++) {
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = (i*256/160);
//			}
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = (i*256/160) << 8;
//			}
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = (i*256/160) << 16;
//			}
//		}
//		for (y=0; y<C_GLCD_V_SIZE / 2; y++) {
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = ~(i*256/160);
//			}
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = ~((i*256/160) << 8);
//			}
//			for (i=0; i<C_GLCD_H_SIZE/3; i++) {
//				*pDst++ = ~((i*256/160) << 16);
//			}
//		}
//		pDst16 = (unsigned short *) pDst;
//		for (y=0; y<C_GLCD_V_SIZE; y++) {
//			for (i=0; i<C_GLCD_H_SIZE; i++) {
//				*pDst16++ = 0xffff;
//			}
//		}
//#endif
//	}
  	for(i = C_GLCD_ENA_DIS_DLY; i; i--);
}


/*************************** End of file ****************************/
