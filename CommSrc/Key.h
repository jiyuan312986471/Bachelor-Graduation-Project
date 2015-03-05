/*Key.h --KeyBoard drive function Header file. */

#ifndef __KEY__
#define __KEY__
#include <RTL.H>

//Key Value define
#define UPKEY 0x01
#define DOWNKEY 0x02
#define UPDOWNKEY 0x03
#define SETKEY 0x04
#define LEFTKEY 0x05
#define RIGHTKEY 0x06
#define LRKEY 0x07
#define ESCKEY 0x08

#define REP_UPKEY (UPKEY+0x0C)
#define REP_DOWNKEY (DOWNKEY+0x0C)

#define HAVEKEY (0x01<<28)
#define DISABLE_KEY (0x01<<29)

void ScanKey(void);
int GetKey(U8 * pCtrl);
//int keyPressed(void);
int GetStartKeyVal(void);
void Set_cb_Lcd(void (*fn)());
void Set_cb_Beep(void (*fn)());

//extern unsigned int key_aux;
// extern unsigned int * pLcdControlState;

#endif /* __KEY__ */

