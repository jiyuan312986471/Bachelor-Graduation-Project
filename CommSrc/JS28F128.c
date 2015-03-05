// JS28F128.c

#include "typeDef.h"
#include "LPC177x_8x.h"
#include "JS28F128.h"

void JS28F128_IF_Init()
{
	LPC_EMC->StaticConfig0   = 0x00000081;
	LPC_EMC->StaticWaitWen0  = 0x00000000; // ( n + 1 ) -> 1 clock cycles
	LPC_EMC->StaticWaitOen0  = 0x00000000; // ( n ) -> 0 clock cycles
	LPC_EMC->StaticWaitRd0   = 0x00000006; // ( n + 1 ) -> 7 clock cycles
	LPC_EMC->StaticWaitPage0 = 0x00000000; // ( n + 1 ) -> 1 clock cycles
	LPC_EMC->StaticWaitWr0   = 0x00000005; // ( n + 2 ) -> 7 clock cycles
	LPC_EMC->StaticWaitTurn0 = 0x00000000; // ( n + 1 ) -> 1 clock cycles

/*	LPC_EMC->StaticConfig1   = 0x00000081;
	LPC_EMC->StaticWaitWen1  = 0x00000000; // ( n + 1 ) -> 1 clock cycles
	LPC_EMC->StaticWaitOen1  = 0x00000000; // ( n ) -> 0 clock cycles
	LPC_EMC->StaticWaitRd1   = 0x00000006; // ( n + 1 ) -> 7 clock cycles
	LPC_EMC->StaticWaitPage1 = 0x00000000; // ( n + 1 ) -> 1 clock cycles
	LPC_EMC->StaticWaitWr1   = 0x00000005; // ( n + 2 ) -> 7 clock cycles
	LPC_EMC->StaticWaitTurn1 = 0x00000000; // ( n + 1 ) -> 1 clock cycles
*/
}

int JS28F128_EraseBlock(uint32_t Addr)
{
	volatile uint16_t *ip;
	uint16_t wtemp=0;

	ip  = GET_ADDR(Addr);
	*ip = 0x0090;
	ip  = GET_ADDR(0x03);
	wtemp = *ip;

	// if locked, unlock
	if(wtemp & 0x01) {
		ip  = GET_ADDR(0);
		*ip = 0x0060;
		*ip = 0x00d0;
		while(1) {
			ip  = GET_ADDR(2);
			wtemp = *ip;
			if(wtemp & (0x01 << 7)) break;
		}
	}

	// erase
	ip  = GET_ADDR(0);
	*ip = 0x0020;
	*ip = 0x00D0;
	*ip = 0x0070;
	wtemp = *ip;
	while(!(wtemp & (0x01 << 7)))
	{
		*ip = 0x0070;
		wtemp = *ip;
	}	
	return 1;
}

int JS28F128_WriteWord(uint32_t Addr, uint16_t Data)
{
	volatile uint16_t *ip;
	uint16_t wtemp;

	ip  = GET_ADDR(Addr);
	*ip = 0x0040;
	*ip = Data;

	ip  = GET_ADDR(0);
	*ip = 0x0070;
	wtemp = *ip;
	while(!(wtemp & (0x01 << 7))) {
		*ip = 0x0070;
		wtemp = *ip;
	}
	return 1;
}

