#ifndef __SDRAM_H__
#define __SDRAM_H__

// #define SDRAM_NO_INIT
// #define SDRAM_TEST
//#define SDRAM_CONFIG_16BIT			// 外接1颗16位SDRAM
#define SDRAM_CONFIG_32BIT				// 外接2颗16位SDRAM

#ifdef SDRAM_CONFIG_16BIT 
#define SDRAM_SIZE		0x2000000		// 256Mbit
#elif defined SDRAM_CONFIG_32BIT
#define SDRAM_SIZE		0x4000000		// 512Mbit
#else
	error Wrong SDRAM config!
#endif

#define SDRAM_BASE		0xA0000000	   // CS0
//#define SDRAM_BASE	0xB0000000
//#define SDRAM_BASE	0xC0000000
//#define SDRAM_BASE	0xD0000000

// function protype
void sdram_init(void);
#ifdef SDRAM_TEST
int sdram_test(void);
#endif

#endif /* __SDRAM_H__ */

