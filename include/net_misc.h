#ifndef __NET_MISC_H__
#define __NET_MISC_H__

#include "typeDef.h"

#define min(X,Y) (((X)<=(Y))?(X):(Y))
#define max(X,Y) (((X)>=(Y))?(X):(Y))
#define movmem(X,Y,Z) xmemcpy((Y),(X),(Z))
#define FP_OFF(X) ((unsigned int)X)
#define _SET_TIMEOUT(x) (MS_TIMER + (x))
#define _CHK_TIMEOUT(x) chk_timeout(x)
#define _SET_SHORT_TIMEOUT(x) ((word)MS_TIMER + (x))
#define _CHK_SHORT_TIMEOUT(x) ((int)((word)MS_TIMER - (x)) >= 0)


extern volatile U32 TICK_TIMER, MS_TIMER, SEC_TIMER;
extern volatile char  updateDateTimeFlg;

typedef struct {
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short week;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned short fsecond;
} DATETIME;

//prodID format SUTTYYMMDDSSSS X
typedef struct {
	unsigned char prodID[16];
	unsigned char macAddr[6];
	unsigned char auxSet1;
	unsigned char auxSet2;
	unsigned char rsv[8];
} _SysAppConf;


/* Function Prototypes */
void Set_StartAD_Ptr(void (*fn)());
void Set_ScanKey_Ptr(void (*fn)());
void Set_BeepDealwith_Ptr(void (*fn)());
void Set_ScanShow_Ptr(void (*fn)());

void exception(int v);
void global_Init(void);
void tickwait(unsigned int tick);
void mswait(unsigned int ms);
void TIMER0_Init(void);
void TIMER3_Init(void);
void RTC_Init(void);

void mS_Delay(unsigned int ms);
unsigned long intel(unsigned long in);
unsigned short intel16(unsigned short in);

unsigned long set_timeout(unsigned int seconds);
int chk_timeout(unsigned long timeout);
word GetTimeStamp(void);
void mem_dump(const void * pblock, word len);
void xmemcpy(void * desPtr, void * srcPtr, int num);
void xmemset(void * desPtr, char ch, int num);
int strcmpi(const char *str1, const char *str2);
int strncmpi(const char *str1, const char *str2, unsigned int n);
void toUpperCase(char *str);
int HexStrToNum(char *hexStr, char * resStr, int nLen);
void Get_DateTime(DATETIME * dt);
void Set_DateTime(DATETIME * dt, int flag);
unsigned int GetDateTimeUTC(unsigned short * fsec, int tzAdj);
void SetDateTimeUTC(unsigned int second, unsigned int fsecond, int tzAdj);
unsigned int GetDatePosixTime(unsigned short * fsec, int tzAdj);
void SetDatePosixTime(unsigned int sec, unsigned int fsec, int tzAdj);
int CalcWeek(int y, int m, int d);
int GetWeekNum(char * week);
const char * GetWeekStr(int w); 
int getRInt(void * p);
word getRWord(void * p);
void store4bytes(void* p, int v);
void Set_notify_timeChg_Ptr(void (*fn)());
char *inet_ntoa( char *s, longword x );
char * inet_ethtoa(char * s, const byte * hwa);
#define aton inet_addr		// Macro alias for historical reasons
longword aton2(char **textp, int * bad, word * port);
longword _f_aton2(char **textp, int *bad, word *port);
longword _aton2(int *offset, const char *text, int *bad, word *port);
int isaddr(const char *text);
longword inet_addr(const char *s);

void __svc(1) 	Disable_Int(void);       /*  关中断                      */
void __svc(2) 	Enable_Int(void);        /*  开中断                      */
//void forceSoftReset(void);
void __svc(3) 	forceSoftReset(void);
void __svc(4) 	SetPrivilegeMode(void);
void __svc(5) 	SetUnPrivilegeMode(void);

#endif /* __NET_MISC_H__ */
