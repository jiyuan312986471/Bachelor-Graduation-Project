// heapDef.c

#define Heap_Size 0x70000

__asm void dummy_function(void)
{
	EXPORT __heap_base
	EXPORT __heap_limit

__heap_base
Heap_Mem	SPACE	1
__heap_limit

//__heap_base EQU HEAP_BASE
//__heap_limit EQU (HEAP_BASE + HEAP_SIZE)
}
