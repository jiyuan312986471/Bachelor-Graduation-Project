/*FlashDrv.h --Flash operation function Header file. */

#ifndef __FLASHDRV__
#define __FLASHDRV__

#include "TypeDef.h"


int writeUserBlock(byte* addr, void *source, word numbytes);
int writeUserBlockArray(byte* addr, void* sources[], word numbytes[], int numsources);
int readUserBlock(void *dest, byte* addr, U32 numbytes);
int readUserBlockArray(void *dests[], word numbytes[], int numdests, byte* addr);
int ProgramOneSector(byte* addr, U16 *Src);
int ProgramOneBlock(byte* addr, U16 *Src);


#endif /* __FLASHDRV__ */
