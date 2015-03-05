// HY27UF1G.h
#ifndef __HY27UF1G_H__
#define __HY27UF1G_H__

 // 适用于A24连接ALE, A25连接CLE
#define HY271G_CLE   ((volatile uint8_t *)	0x92000000)
#define HY271G_ALE	((volatile uint8_t *)	0x91000000)
#define HY271G_DATA  ((volatile uint8_t *)	0x90000000)

#define NANDFLASH_BASE_ADDR			0x00000000

#define NANDFLASH_INVALIDBLOCK_CHECK_COLUMM			(2048+0)

// total 1024 blocks in a device
#define NANDFLASH_NUMOF_BLOCK		1024	// 1024

// total pages in a block
#define NANDFLASH_PAGE_PER_BLOCK	64

#define NANDFLASH_RW_PAGE_SIZE		2048	// bytes/page

#define NANDFLASH_SPARE_SIZE		64 		//bytes/page

#define NANDFLASH_PAGE_FSIZE		(NANDFLASH_RW_PAGE_SIZE + NANDFLASH_SPARE_SIZE)

#define NANDFLASH_BLOCK_RWSIZE	(NANDFLASH_RW_PAGE_SIZE * NANDFLASH_PAGE_PER_BLOCK)
#define NANDFLASH_BLOCK_FSIZE	(NANDFLASH_PAGE_FSIZE * NANDFLASH_PAGE_PER_BLOCK)


#define NANDFLASH_ADDR_COLUMM_POS		0
#define NANDFLASH_ADDR_ROW_POS			16

#define HY27_ID					0xADF11D80	/* Byte 3 and 2 only */

#define HY27_READ1            	0x00
#define HY27_READ1_2           	0x30

#define HY27_READ_ID           	0x90
#define HY27_RESET             	0xFF
#define HY27_PAGE_PROGRAM_1   	0x80
#define HY27_PAGE_PROGRAM_2   	0x10
#define HY27_BLOCK_ERASE_1     	0x60
#define HY27_BLOCK_ERASE_2     	0xD0
#define HY27_READ_STATUS       	0x70

#define HY27_BUSY              	(1 << 6)
#define HY27_OK                	(1 << 0)

#define FIO_BASE_ADDR		0x20098000
#define FIO2DIR        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x40))
#define FIO2MASK       (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x50))
#define FIO2PIN        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x54))
#define FIO2SET        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x58))
#define FIO2CLR        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x5C))


#define ERR_RETVAL_OK				(0)
#define ERR_RETVAL_ERROR			(-1)
#define ERR_RETVAL_WRONG_INPUT		(-2)

void HY271G_Init( void );
void HY271G_Reset( void );
void HY271G_WaitForReady( void );	/* same as CheckBusy, no time out */
uint32_t HY271G_ReadId( void );
int HY271G_ReadStatus( uint32_t Cmd );
int HY271G_BlockErase( uint32_t blockNum );
int HY271G_ValidBlockCheck( void );
int HY271G_PageProgram(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);
int HY271G_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr );

int HY271G_PageReadFromBeginning(uint32_t block, uint32_t page, uint8_t* bufPtr);
int HY271G_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum, uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);


#endif /* __HY27UF1G_H__ */
