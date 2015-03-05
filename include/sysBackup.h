/* sysBackup.h --system backup function Header file. */

#ifndef __SYSBACKUP__
#define __SYSBACKUP__

#include "TypeDef.h"
#include "ConDeam.h"
//Do'nt edit The following define 
#define LOC_NETMAC_BACKUP	0
#define LOC_BASIC_BACKUP	1
#define LOC_TCP_BACKUP		2
#define LOC_LOGIN_BACKUP	3
//#define LOC_HTTP_BACKUP		4
#define LOC_TCP_MULTI_BACKUP	6
//#define LOC_SMTP_BACKUP		6
//#define LOC_FILES_BACKUP	7
//#define LOC_VARS_BACKUP		8

#define LOC_SNMPCOMM_BACKUP	4
#define LOC_SNMPTRAP_BACKUP	5
#define LOC_NTP_BACKUP	6
//#define LOC_SNMPIPTLT_BACKUP	6	//@added by QXJ
#define BACKUP_ALL -1

#ifdef DCRTCP
typedef struct {
	NetConfSave save;
} ConsoleTCPMultiBackupInfo;
#endif

//ConsoleHTTPBackupInfo structure
/*typedef struct {
	char top;
	unsigned int varstrlen[SSPEC_MAXSPEC];
	long varbuflen;
} ConsoleHTTPBackupInfo;*/

typedef struct {
	void* data;
	int len;
	void (*postload)();
	void (*presave)();
} ConsoleBackup;

typedef struct {
	void *ParamPtr;
	int ParamLen;
//	U16 ParamLen;
//	U16 paramID;
} param_backup;

void sys_backup_init(void);
int con_load_backup(int whitch);
int con_backup(int whitch);
int con_backup_size(void);
int con_load_param(void * paramPtr);
int con_backup_param(void * paramPtr);
int con_get_backup_param_loc(void* paramPtr);
int con_SaveParam(ConsoleState* state);

void SetDelaySaveMode(int mode);
void SetForceSaveMode(void);
int GetDelaySaveMode(void);

void Set_cb_backup(void (*cb_fn)());
void Set_cb_backup_param(void (*cb_fn)());


//extern ConsoleBackupInfo console_backup_info;
extern const ConsoleBackup console_backup[];
extern const param_backup params_backup[];
extern int last_Param, consoleBackupValid;
extern short nMaxConSoleBakups;
//extern short nMaxParamBakups;
extern int last_Param;		//Paramters save init flag

extern void (*cb_backup)(int);
extern void (*cb_backup_param)(void*);

//Predefined ConsoleBackup strutures
#define NET_MAC_BACKUP { &SysAppConf, sizeof(_SysAppConf), con_netApp_postload, con_netApp_presave }
#define CONSOLE_NTP_BACKUP { &ntp_server, sizeof(ntp_server), NULL, NULL }
#define CONSOLE_BASIC_BACKUP { &console_backup_info, sizeof(ConsoleBackupInfo), con_backup_info_postload, con_backup_info_presave }
#define CONSOLE_TCP_BACKUP { &console_tcp_backup_info, sizeof(ConsoleTCPBackupInfo), NULL /* con_tcp_backup_info_postload */, con_tcp_backup_info_presave }
#define CONSOLE_TCP_MULTI_BACKUP { &console_tcp_multi_backup_info, sizeof(ConsoleTCPMultiBackupInfo), con_tcp_multi_backup_info_postload, con_tcp_multi_backup_info_presave }
#define CONSOLE_HTTP_BACKUP { &console_http_backup_info, sizeof(ConsoleHTTPBackupInfo), con_http_backup_info_postload,  con_http_backup_info_presave }, { server_spec,  sizeof(server_spec), NULL,  NULL }
#define CONSOLE_LOGIN_BACKUP { &console_login, sizeof(console_login), NULL, NULL }
#define BAKUP_DEVICE_MAC(id,n)		{ &TBDevice[n].lastMAC, sizeof(U32), id+n }
#define CONSOLE_BACKUP_END {&consoleBackupValid, 4, NULL, NULL}, {0}
#define BACKUP_PARAM_END	{ (void*)&last_Param, sizeof(int)}, {NULL}
#endif /* __SYSBACKUP__ */
