/*UartDrive.h --Serial port drive function Header file. */
#ifndef __UARTDRIVE__
#define __UARTDRIVE__



#ifndef MAX_UART0RX
#define MAX_UART0RX 256
#endif
#ifndef MAX_UART0TX
#define MAX_UART0TX 1024
#endif

#ifndef MAX_UART1RX
#define MAX_UART1RX 256
#endif
#ifndef MAX_UART1TX
#define MAX_UART1TX 256
#endif

#ifndef MAX_UART2RX
#define MAX_UART2RX 256
#endif
#ifndef MAX_UART2TX
#define MAX_UART2TX 256
#endif

#ifndef MAX_UART3RX
#define MAX_UART3RX 256
#endif
#ifndef MAX_UART3TX
#define MAX_UART3TX 256
#endif

//Function protype
void Uart0Open(int baudrate);
void Uart0Close(void);
int Uart0Read(char * pBuf, int n);
int Uart0Write(char * pDat, int n);
int Uart0rdUsed(void);
int Uart0wrUsed(void);
int Uart0wrFree(void);

int getBaudSet(int baudrate);

void Uart1Open(int baudrate);
void Uart1Close(void);
int Uart1Read(char * pBuf, int n);
int Uart1Write(char * pDat, int n);
int Uart1rdUsed(void);
int Uart1wrUsed(void);
int Uart1wrFree(void);
void SetUart1PreSend(void (*preSend_fn)());
void SetUart1PostSend(void (*postSend_fn)());

void Uart2Open(int baudrate);
void Uart2Close(void);
int Uart2Read(char * pBuf, int n);
int Uart2Write(char * pDat, int n);
int Uart2rdUsed(void);
int Uart2wrUsed(void);
int Uart2wrFree(void);
void SetUart2PreSend(void (*preSend_fn)());
void SetUart2PostSend(void (*postSend_fn)());

void Uart3Open(int baudrate);
void Uart3Close(void);
int Uart3Read(char * pBuf, int n);
int Uart3Write(char * pDat, int n);
int Uart3rdUsed(void);
int Uart3wrUsed(void);
int Uart3wrFree(void);
void SetUart3PreSend(void (*preSend_fn)());
void SetUart3PostSend(void (*postSend_fn)());

#define SYNCODE 0xA5
#define FRAME_DATA_CONTINUE	0x80000000

#define U0RxFull 0x00000001
#define U1RxFull 0x00000002
#define U2RxFull 0x00000004
#define U3RxFull 0x00000008

#define U0Opened 0x00010000
#define U1Opened 0x00020000
#define U2Opened 0x00040000
#define U3Opened 0x00080000

extern int UartStatus;

#endif /* __UARTDRIVE__ */
