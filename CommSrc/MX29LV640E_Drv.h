// MX29LV640E_Drv.h
#ifndef __MX29LV640E_H__ 
#define __MX29LV640E_H__

#define NORFLASH_SIZE 0x800000
#define NORFLASH_BASE 0x90000000

#define GET_ADDR(addr) (volatile uint16_t *)(NORFLASH_BASE | (addr << 1))

extern void MX29LV640E_IF_Init(void);
extern int NORFLASHEraseBlock( uint32_t Addr );
extern int NORFLASHWriteWord( uint32_t Addr, uint16_t Data );

#endif /* __MX29LV640E_H__ */
