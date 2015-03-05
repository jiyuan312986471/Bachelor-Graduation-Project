/* Console.h --Console function Header file. */

#ifndef __CONSOLE__
#define __CONSOLE__


#include<RTL.H>
#include "TypeDef.h"
#include "UartDrive.h"

//#include "oemDef.h"

#include "Condeam.h"

//ConsoleTCPBackupInfo structure
typedef struct {
	unsigned long ip;
	unsigned long netmask;
	unsigned long gateway;
	unsigned long nameserver;
} ConsoleTCPBackupInfo;

#ifndef PINGNUM
	#define PINGNUM 4
#endif

#ifndef PINGTIMEOUT
	#define PINGTIMEOUT 1
#endif

extern _SysAppConf SysAppConf;

int con_help(ConsoleState* state);
int con_echo(ConsoleState* state);
int con_show(ConsoleState* state);
int con_set_param(ConsoleState* state);
int con_Date(ConsoleState* state);
int con_Time(ConsoleState* state);
int con_loginpswd(ConsoleState* state);
int con_clear(ConsoleState* state);
int con_Ping(ConsoleState* state);
int con_set_ntp(ConsoleState* state);
int con_SaveParam(ConsoleState* state);
int con_prodID(ConsoleState* state);
int matchHw(unsigned char Type);

int conio_Uart0_puts(char *s);

void conio_telnet_open(word port);
void conio_telnet_close(word port);
int conio_telnet_tick(void);
int conio_telnet_puts(char *s);
int conio_telnet_rdUsed(void);
int conio_telnet_wrUsed(void);
int conio_telnet_wrFree(void);
int conio_telnet_read(void *data, int length, unsigned long tmout);
int conio_telnet_write(void *data, int length);


void con_netApp_postload(void* dataptr);
void con_netApp_presave(void* dataptr);
void con_backup_info_postload(void* dataptr);
void con_backup_info_presave(void* dataptr);
void con_tcp_backup_info_postload(void* dataptr);
void con_tcp_backup_info_presave(void* dataptr);
void load_NetMac(void);
int isInvalidMac(void);
void defNetSetting(char* strIp, char* strMask, char* strGateway, char* strDNS);

int con_ip(ConsoleState* state);
int con_mask(ConsoleState* state);
int con_gateway(ConsoleState* state);
int con_set_ip(ConsoleState* state);
int con_set_netmask(ConsoleState* state);
int con_set_gateway(ConsoleState* state);
int con_set_nameserver(ConsoleState* state);
int con_add_nameserver(ConsoleState* state);
int con_set_tcpip_debug(ConsoleState* state);
int __con_set_net_misc(ConsoleState* state, int set, char* msg, int param, int is_long, int reset_io);
int con_set_mtu(ConsoleState* state);
int con_set_icmp_config_reset(ConsoleState* state);
int __con_set_net_misc_onoff(ConsoleState* state, int set, char* msg, char* on, char* off, int reset_io);
int con_set_dhcp(ConsoleState* state);
int con_set_icmp_config(ConsoleState* state);
int __con_set_ip_misc(ConsoleState* state, int set, char* msg, int use_iface, int reset_io);
void con_tcp_multi_backup_info_postload(void* dataptr);
void con_tcp_multi_backup_info_presave(void* dataptr);


int con_Reboot(ConsoleState* state);
int con_factoryMode(ConsoleState* state);
int con_netMac(ConsoleState* state);
int con_statistic(ConsoleState* state);
int con_dumpMem(ConsoleState* state);

int con_communitymng(ConsoleState* state);
int con_trapmng(ConsoleState* state);
int con_paramInit(ConsoleState* state);

//hide function
int con_sysName(ConsoleState* state);

int con_prtARPTable(ConsoleState* state);
int con_prtRouter(ConsoleState* state);

int sendCmdToConsole(U32 conChannelMask, char * cmdStr);

extern const ConsoleIO console_io[];
extern ConsoleLogin console_login[4];
extern const ConsoleCommand console_commands[];
extern sndCmdStruc sentCommand;
extern char factoryMode;

//pre-defined console_io structs
#define CONSOLE_IO_UART0(param)	{ param, Uart0Open, Uart0Close, NULL, conio_Uart0_puts, Uart0rdUsed, Uart0wrUsed, Uart0wrFree, Uart0Read, Uart0Write }
#define CONSOLE_IO_UART1(param)	{ param, Uart1Open, Uart1Close, NULL, conio_Uart1_puts, Uart1rdUsed, Uart1wrUsed, Uart1wrFree, Uart1Read, Uart1Write }
#define CONSOLE_IO_TELNET(port)	{ port, conio_telnet_open, conio_telnet_close, conio_telnet_tick, conio_telnet_puts, conio_telnet_rdUsed, conio_telnet_wrUsed, conio_telnet_wrFree, conio_telnet_read, conio_telnet_write }

#endif /* __CONSOLE__ */
