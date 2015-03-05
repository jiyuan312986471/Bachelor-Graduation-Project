#ifndef __LCD_CONST_H__
#define __LCD_CONST_H__

//模块型号
#define LCD_EMPTY_TYPE "E\r\nM\r\nP\r\nT\r\nY"   //EMPTY
#define LCD_DNOT1_TYPE "1\r\n3\r\n1\r\n0\r\nT\r\nX"  //1310TX
#define LCD_DNOT2_TYPE "1\r\n5\r\n5\r\n0\r\nT\r\nX"  //1550TX
#define LCD_DNOR_TYPE "R\r\nC\r\nV"  //RCV
#define LCD_UPOR_TYPE "R\r\nC\r\nV\r\n|\r\nR"  //RCV-R
#define LCD_AMP_TYPE　"A\r\nM\r\nP"　//AMP
#define LCD_RFSW_TYPE "R\r\nF\r\n|\r\nS\r\nW"  //RFSW
#define LCD_OPSW_TYPE "O\r\nP\r\n|\r\nS\r\nW"  //OPSW
#define LCD_EDFA_TYPE "E\r\nD\r\nF\r\nA" //EDFA
#define LCD_UNK_TYPE "\r\nU\r\nN\r\nK"

#define LCD_PS_TYPE "Supply"
#define LCD_FAN_TYPE "Fan"
#define LCD_CHASSIS_TYPE "Chassis"

#define devID_FRAME 0x03
#define devID_NULL 0
#define devID_UNK 0xFF
#define devID_FRAME 0x03
#define devID_DNOT1 0x01 //1310
#define devID_DNOT2 0x02 //1550
#define devID_UPOT 0x08 //1310
#define devID_DNOR 0x05  //双路切换
#define devID_UPOR 0x07
#define devID_RFAMP 0x09
#define devID_SW 0x0E
#define devID_PS	0x0A
#define devID_EDFA  0x04
#define devID_FAN 0x0F  //应为0x0F


typedef struct{

	char devID;
	
}slotMod;
#endif
