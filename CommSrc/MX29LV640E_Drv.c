#include "typeDef.h"
#include "LPC177x_8x.h"
#include "MX29LV640E_Drv.h"

void MX29LV640E_IF_Init()
{
    LPC_IOCON->P4_24 = 0x201; /* OEN @ P4.24 */
	LPC_IOCON->P4_27 = 0x201; /* BLSN[1] @ P4.27 */
	LPC_IOCON->P4_31 = 0x201; /* CSN[1] @ P4.31 */
	
	LPC_EMC->StaticConfig1   = 0x00000081;
	LPC_EMC->StaticWaitWen1  = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitOen1  = 0x00000000; /* ( n ) -> 0 clock cycles */
	LPC_EMC->StaticWaitRd1   = 0x00000006; /* ( n + 1 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitPage1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitWr1   = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitTurn1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
}

int Polling(unsigned long adr) 
{
	volatile uint16_t *ip;
	uint16_t q6, wtemp;

	ip  = GET_ADDR(adr);
	q6 = (*ip) & 0x40;
	do {
		wtemp = *ip;
		if ((wtemp & 0x40) == q6) return 0;  // Done
		q6 = wtemp & 0x40;
	} while ((wtemp & 0x20) == 0);           // Check for Timeout
	q6 = (*ip) & 0x40;
	wtemp = *ip;
	if ((wtemp & 0x40) == q6) return 0;		// Done
//	*ip = 0xF0;                 			// Reset Device
	return (1);                        		// Failed
}

int NORFLASHEraseBlock(uint32_t Addr ) 
{
	volatile uint16_t *ip;
	uint16_t wtemp=0;

//	ip  = GET_ADDR(0);
//	*ip = 0x0098;
//	ip  = GET_ADDR(0x31);
//	wtemp = *ip;
//	ip  = GET_ADDR(0x32);
//	wtemp = *ip;
//	ip  = GET_ADDR(0x33);
//	wtemp = *ip;
//	ip  = GET_ADDR(0x34);
//	wtemp = *ip;

	ip  = GET_ADDR(Addr);
	*ip = 0x0090;
	ip  = GET_ADDR(0x03);
	wtemp = *ip;

	// if locked, unlock
	if(wtemp & 0x01) {
		ip  = GET_ADDR(0);
		*ip = 0x0060;
		ip  = GET_ADDR(0);
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
	while(!(wtemp & (0x01 << 7))) {
		*ip = 0x0070;
		wtemp = *ip;
	}
	
	return 1;
}

int NORFLASHWriteWord( uint32_t Addr, uint16_t Data ) 
{
	volatile uint16_t *ip;
	uint16_t wtemp;

	ip = GET_ADDR(0x555);
	*ip = 0x00AA;
	ip = GET_ADDR(0x2AA);
	*ip = 0x0055;
	ip = GET_ADDR(0x555);
	*ip = 0x00A0;
	ip  = GET_ADDR(Addr);
	*ip = Data;
	return Polling(Addr);
}
