/* Condeam.h --Console Deamon function Header file. */

#ifndef __CONDEAM__
#define __CONDEAM__

#ifndef MAX_CONSOLES
	#define MAX_CONSOLES 2
#endif

//#define PSWD_NOECHO
#ifndef CON_MAX_PASSWORD
	#define CON_MAX_PASSWORD 10
#endif

#ifndef CON_MAX_NAME
	#define CON_MAX_NAME 11
#endif

#ifndef CON_CMD_SIZE
	#define CON_CMD_SIZE 128
#endif

#ifndef CON_BUF_SIZE
	#define CON_BUF_SIZE 256
#endif

#ifndef CON_CMD_DATA_SIZE
	#define CON_CMD_DATA_SIZE 16
#endif

#ifndef CON_VAR_BUF_SIZE
	#define CON_VAR_BUF_SIZE 1024
#endif

#ifndef CON_INIT_MESSAGE
	#define CON_INIT_MESSAGE "\r\nSPIE Console V1.0 2007/09/28\r\n\r\n"
#endif

#ifndef CON_TIMEOUT
	#define CON_TIMEOUT 60
#endif


#ifndef CON_SP_RDBUF_SIZE
	#define CON_SP_RDBUF_SIZE 255
#endif


#ifndef CON_HOSTNAME
	#define CON_HOSTNAME "SU Agent"
#endif

#ifndef CON_DHCP_ACQUIRE_RETRY_TIMEOUT
	#define CON_DHCP_ACQUIRE_RETRY_TIMEOUT 120
#endif

#if CON_MAX_NAME>CON_CMD_DATA_SIZE
	#error "CON_CMD_DATA_SIZE must be >= CON_MAX_NAME"
#endif

#define PROMPT_LOGINNAME "\rUserName>"
#define PROMPT_PASSWORD "\rPassword>"
//#ifndef PROMPT_COMMAND
//	#define PROMPT_COMMAND "\rSIPE>"
//#endif
extern const char PROMPT_COMMAND[];
#define PROMPT_ON "ON"
#define PROMPT_OFF "OFF"

//Error Code Define
#define CON_ERR_TIMEOUT		1
#define CON_ERR_BADCOMMAND	2
#define CON_ERR_BADPARAMETER	3
#define CON_ERR_NAMETOOLONG	4
#define CON_ERR_DUPLICATE	5
#define CON_ERR_BADFILESIZE	6
#define CON_ERR_SAVINGFILE	7
#define CON_ERR_READINGFILE	8
#define CON_ERR_FILENOTFOUND	9
#define CON_ERR_HOSTTOOLONG	10
#define CON_ERR_NODNSDEF	11
#define CON_ERR_BADPASSPHRASE	12
#define CON_ERR_CANCELRESET	13
#define CON_ERR_BADVARTYPE	14
#define CON_ERR_BADVARVALUE	15
#define CON_ERR_RSVHOSTFAIL	16
#define CON_ERR_VARNOTFOUND	17
#define CON_ERR_STRINGTOOLONG	18
#define CON_ERR_NOTAFILE	19
#define CON_ERR_NOTAVAR		20
#define CON_ERR_COMMANDTOOLONG	21
#define CON_ERR_BADIPADDRESS	22
#define CON_ERR_INVALIDPASSWORD	23
#define CON_ERR_BADIFACE	24
#define CON_ERR_BADNETWORKPARAM	25
#define CON_ERR_NOEXECAUTHORITY	26
#define CON_ERR_YEAR	27
#define CON_ERR_MONTH	28
#define CON_ERR_DAY		29
#define CON_ERR_DTFMT	30
#define CON_ERR_HOUR	31
#define CON_ERR_MIN		32
#define CON_ERR_SEC		33
#define CON_ERR_TMFMT	34
#define CON_ERR_WEEK	35

//ConsoleBackupInfo structure
typedef struct {
	unsigned short param[MAX_CONSOLES];
	short status[MAX_CONSOLES];
} ConsoleBackupInfo;


//ConsoleCommand structure
typedef struct {
	char* command;
	int (*cmdfunc)();
	const char *helptext;
	char authority;
} ConsoleCommand;

//ConsoleError structure
typedef struct {
	unsigned int code;
	char* message;
} ConsoleError;

//ConsoleIO structure
typedef struct {
	int param;
	void (*open)();
	void (*close)();
	int (*tick)();
	int (*puts)();
	int (*rdUsed)();
	int (*wrUsed)();
	int (*wrFree)();
	int (*read)();
	int (*write)();
} ConsoleIO;

#define B_CONSOLE (0x01)
#define B_TELNET  (0x01<<1)
typedef struct {
	char * cmdStr;
	U32 consoleChannelMask;
} sndCmdStruc;

#define B_SAWCR 0x01
#define B_PROMPT 0x02
#define B_ECHO 0x04
#define B_BKECHO 0x08
#define B_PSWD 0x10

//ConsoleState structure
typedef struct {
	ConsoleIO* conio;
	unsigned short console_number;
	short status;
	short state;
	short laststate;

	char command[CON_CMD_SIZE];
	char* cmdptr;
	char buffer[CON_BUF_SIZE];
	char* bufferend;

	ConsoleCommand* cmdspec;
	short sawesc;
	short substate;
	short numparams;
	short commandparams;
	char cmddata[CON_CMD_DATA_SIZE];
	int timeout;
	int timesout;
	const char * pOut;
	short logUser;
	unsigned short errno;
	short spec;
	char escCode[2];
	char cmdBuf[128];

} ConsoleState;

//ConsoleLogin structure
typedef struct {
	char name[CON_MAX_NAME+1];
	char password[CON_MAX_PASSWORD+1];
	char authority;
} ConsoleLogin;

extern char factoryMode;
extern ConsoleBackupInfo console_backup_info;

//Function protype
int console_init(void);
void console_tick(void);
void console_enable(int which);
void console_disable(int which);
void con_set_user_timeout(void (*funcptr)());
void con_set_user_idle(void (*funcptr)());
void con_reset_io(void);
void __conexec(ConsoleState* state);
int __con_inputstring(ConsoleState* state);
void __con_error(ConsoleState* state, unsigned int errcode);
int __con_nullify(char* buffer);
void __con_anti_nullify(char* begPtr, char* endPtr);
int __con_login(ConsoleState* state);
int con_logout(ConsoleState* state);
ConsoleCommand* __con_parsecmd(char* command, short numparams, short * commandparams);
char* con_getparam(char* buffer, int num);

unsigned long con_set_timeout(unsigned int seconds);
int con_chk_timeout(unsigned long timeout);
void console_login_init(void);
int con_loginmng(ConsoleState* state);

void Set_console_initEx(void (*funcptr)());

#define WAIT_OUTPUT_EMPTY while (state->conio->wrUsed()) {if (state->conio->tick) state->conio->tick();	os_dly_wait (1);}

#endif /* __CONDEAM__ */
