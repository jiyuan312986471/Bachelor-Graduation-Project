// JS28F128.h
#ifndef __JS28F128_H__
#define __JS28F128_H__

#define JS28F128_BASE_ADDR 0x80000000
#define GET_ADDR(addr) (volatile uint16_t *)(JS28F128_BASE_ADDR | (addr << 1))

void JS28F128_IF_Init(void);
int JS28F128_EraseBlock(uint32_t Addr);
int JS28F128_WriteWord(uint32_t Addr, uint16_t Data);

#endif /* __JS28F128_H__ */
