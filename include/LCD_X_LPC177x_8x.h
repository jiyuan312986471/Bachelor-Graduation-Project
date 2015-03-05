// LCD_X_LPC177x_8x.h
#ifndef __LCD_X_LPC177X_8X_H__
#define __LCD_X_LPC177X_8X_H__

#include "sdram.h"

#define C_GLCD_REFRESH_FREQ     (50)	// Hz
#ifdef SLK_BOARD
#define C_GLCD_H_SIZE           480
#define C_GLCD_V_SIZE           272

#define C_GLCD_H_PULSE          2	//
#define C_GLCD_H_FRONT_PORCH    5	//
#define C_GLCD_H_BACK_PORCH     40 	//
#define C_GLCD_V_PULSE          2
#define C_GLCD_V_FRONT_PORCH    8
#define C_GLCD_V_BACK_PORCH     8

#else
#define C_GLCD_H_SIZE           800
#define C_GLCD_V_SIZE           480

#define C_GLCD_H_PULSE          3	//
#define C_GLCD_H_FRONT_PORCH    1	//
#define C_GLCD_H_BACK_PORCH     88 	//
#define C_GLCD_V_PULSE          3
#define C_GLCD_V_FRONT_PORCH    1
#define C_GLCD_V_BACK_PORCH     32
#endif



//#define SDRAM_BASE_ADDR 0x28000000
#define C_GLCD_CLK_PER_LINE     (C_GLCD_H_SIZE + C_GLCD_H_PULSE + C_GLCD_H_FRONT_PORCH + C_GLCD_H_BACK_PORCH)
#define C_GLCD_LINES_PER_FRAME  (C_GLCD_V_SIZE + C_GLCD_V_PULSE + C_GLCD_V_FRONT_PORCH + C_GLCD_V_BACK_PORCH)
#define C_GLCD_PIX_CLK          (C_GLCD_CLK_PER_LINE * C_GLCD_LINES_PER_FRAME * C_GLCD_REFRESH_FREQ)

#define C_GLCD_PWR_ENA_DIS_DLY  10000
#define C_GLCD_ENA_DIS_DLY      10000

#define LCD_VRAM_BASE_ADDR 	((unsigned long)SDRAM_BASE+ 0x0000000)	//  + 0x00010000

#endif /* __LCD_X_LPC177X_8X_H__ */
