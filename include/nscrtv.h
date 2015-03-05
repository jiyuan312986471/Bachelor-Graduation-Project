/* nscrtv.h-- HFC snmp manager Header file. */

#ifndef __NSCRTV_H__
#define __NSCRTV_H__

#include "net_misc.h"
#include "net.h"
#include "snmpMib.h"
#include "snmp.h"
#include "sysbackup.h"

#ifndef MAX_ALARM_LOG
#define MAX_ALARM_LOG 64
#endif

#define LOC_SNMPCOMM_BACKUP	4
#define LOC_SNMPTRAP_BACKUP	5

#define MAX_MULTICASTADDR 4

#define propertyIdent 	1
#define alarmsIdent 	2
#define commonIdent 	3
#define tvmodIdent 	4
#define qammodIdent 	5
#define otdIdent 	6
#define otxIdent 	7
#define uporIdent 	8
#define dorIdent 	9
#define fnIdent 	10
#define oaIdent 	11
#define addIdent 	12
#define cacIdent 	13
#define lineIdent 	14


#ifndef DEF_VENDOR
#define DEF_VENDOR "上海大学"
#endif
#ifndef DEF_VENDOR_INFO
#define DEF_VENDOR_INFO "上海大学电子物理研究所"
#endif
#ifndef DEF_FIREWARE
#define DEF_FIREWARE "SIPE general firmware V1.0"
#endif

#ifndef DEF_SYSNAME
#define DEF_SYSNAME "SPIE Snmp Agent"
#endif
#ifndef DEF_SYSCONTACT
#define DEF_SYSCONTACT "CH Shen SIPE Shanghai"
#endif
#ifndef DEF_SYSLOCATION
#define DEF_SYSLOCATION "Shanghai, China"
#endif

#define casNominal 1
#define casHIHI   2
#define casHI  3
#define casLO  4
#define casLOLO   5
#define casMajor 6
#define casMinor 7

#define DALARM_DISABLE 1
#define DALARM_MAJOR 2
#define DALARM_MINOR 3

//#ifndef __SNMP__
#define USE_SNMP	1		// This is necessary for all SNMP applications
#define SNMP_TRAPS			// This must be defined to support trap sending
#define SNMP_ENTERPRISE	17409
//#endif

//flags bit define
#define FLG_LOGED 	0x0001
#define FLG_CURALM	0x0002
#define FLG_TRAP	0x0004
#define FLG_VALID	0x0008
#define FLG_IS_AP	0x8000
#define FLG_IS_DP	0x4000

//Structure define
typedef struct {
	S16 ap_LoLo;
	S16 ap_Lo;
	S16 ap_Hi;
	S16 ap_HiHi;
	S16 ap_DB;
	U8 ap_EN;
	U8 ap_FIL;
} ap_Struc;

typedef struct {
	//Need save parameters 5*sizeof(S16)+4bytes+4bytes = 18 bytes
	S16 flags;
	S16 alarmState;
	S32 monVar;
	S16 *detectEnable;
	char *neStatus;
	char *pName;
	char *fmt;
	snmp_oid oid;
	word monIndex;	//MIB tree index of variable to monitor
	word noids;
	word indices[4];//binding variables indices when trap
	longword nextsend;	//Time at which to send next trap (ms rel. MS_TIMER)
	S16 trap_num;	//Trap number to send (enterprise-specific)
	word ntrans;		//Number of times message sent
	char *alarmText;

	ap_Struc ap;
//	S16 analogAlarmHIHI;
//	S16 analogAlarmHI;
//	S16 analogAlarmLO;
//	S16 analogAlarmLOLO;
//	S16 analogAlarmDeadband;
//	char alarmEnable;
//	byte spare;
	float ratio;
	byte alarmChange;
	byte EnSendTraps;
	S16 rsv16;
} __aProperty;

typedef struct {
	S16 flags;
	S16 alarmState;
	S32 monVar;
	S16 *detectEnable;
	char *neStatus;
	char *pName;
	char *fmt;
	snmp_oid oid;
	word monIndex;	//MIB tree index of variable to monitor
	word noids;
	word indices[4];//binding variables indices when trap
	longword nextsend;	//Time at which to send next trap (ms rel. MS_TIMER)
	S16 trap_num;	//Trap number to send (enterprise-specific)
	word ntrans;		//Number of times message sent
	char *alarmText;

	//Need save parameters 3*sizeof(int)
	S16 discreteAlarmEnable;
 	S16 discreteAlarmValue;
	byte alarmChange;
	byte EnSendTraps;
	S16 rsv16;

	int (*usrCompareFunc)();
	void *modPtr;
} __dProperty;

typedef struct {
//	word *trapVarBinding3Ptr;
	__aProperty *pPtr;
	S16 alarmLogIndex;
	char alarmLogInformation[64];
	word Index[2];		//save index just inserted for used to delete
} __alarmLogTable;

typedef struct {
	char *LogicalID;
	char *Vendor;
	char *ModelNumber;
	char *SerialNumber;
	char *VendorInfo;
	U32 *pneAddr;
	char *TrapComStr;
	S16 *varBindings;
	snmp_oid *devOid;
	U32 devID;
	S16 neReset;
	S16 neAlarmDCon;
	U16 neCC;
	S16 TamperStatus;	//intact(1), compromised(2)
	S16 iTemp;
//	U32 comTime;
	S16 ResetCause;
	S16 CraftStatus;
	char neStatus;
} __commonAdminGroup;

//neStatus bit define
#define NESTATUS_MAJOR_ALARM 0x08
#define NESTATUS_MINOR_ALARM 0x10

typedef struct {
	byte commonMulticastAddressNumber[6];
} _commonMulticastAddressTable;

typedef struct {
	short commonBackoffPeriod;
	short commonACKTimeoutWindow;
	short commonMaximumMACLayerRetries;
	short commonBackoffMinimumExponent;
	short commonBackoffMaximumExponent;
	short commonMaxPayloadSize;
} _commonBackoffParams;

typedef struct {
	unsigned int commonReturnPathFrequency;
	unsigned int commonForwardPathFrequency;
	
	short commonProvisionedReturnPowerLevel;
	short commonMaxReturnPower;
	short commonForwardPathReceiveLevel;
} _commonRf;

typedef struct {
	word	maxmesgs;
	word	minintvl;
	word	maxintvl;
	S16 	comAgentBootWay;
} _agParam;

#define MAX_AP_ITEMS 12
#define MAX_DP_ITEMS 4

typedef struct {
	U32 devID;
	S16 slot;
	U16 devStatus;
	char devVendor[64];
	char devModel[32];
	char devSN[16];
	char devVenDorInfo[64];
	U16 devReset;
	U16 devAlarmDC;
	U32 devMAC;
	U16 devTamper;
	S16 devITemp;
	U16 devResetCause;
	U16 devCraft;
	U32 devAcct;
	char devName[32];
	char devMFD[12];
	char devFW[32];
	S16 maxItems;
	char apItems;
	char dpItems;
	char auxData[128];
	__aProperty analogPropertyTable[MAX_AP_ITEMS];
	__dProperty	discretePropertyTable[MAX_DP_ITEMS]; 
	snmp_oid devOid;
} __comDevInfoTable;	//insidePlant;

//function protype in nscrtv.c
int fldLen(char* p, int minLen);
void _snmp_code_oid_index(snmp_parms * p, snmp_oid * oid);
// int ResetCause(void);
// int ResetSystem(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
//void init_enterprise_oid(void);
void check_ap(__aProperty * mv);
void check_dp(__dProperty * mv);
void check_change(__dProperty * mv);

//routine for mibii.systemGroup implement in mibii.c
void insert_mibii(snmp_parms *p);

//routine for analogTable implement in property.c
void Set_MaxAPT(short v);
void Set_apSaveTo(void (*apSaveTo_fn)());
void Set_MaxDPT(short v);
void Set_dpSaveTo(void (*dpSaveTo_fn)());
void Set_mib2SaveTo(void (*mib2SaveTo_fn)()); 	// implement in mibii.c
void Set_agParamSaveTo(void (*agParamSaveTo_fn)()); 	// implement in commonAgentGroup.c
void Set_trapTabSaveTo(void (*trapTabSaveTo_fn)()); 	// implement in commonAgentGroup.c

//int SaveAnalogTable(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
//int cb_apTable(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
void analogAlarmSetting(__aProperty* apPtr, char alarmEn, int LOLO, int LO, int HI, int HIHI, int DB, byte alarmChg, byte TrapEn);
void analogAlarmTrapSetting(__aProperty* apPtr, int trap_num, word noids, char *alarmText);
void analogAlarmTrapEnable(__aProperty* apPtr, byte En);
void filAp(__aProperty* apPtr, ap_Struc * ap, int ratio, byte alarmChg, byte TrapEn);
void saveApItem(ap_Struc * pLmt, __aProperty *aPtr, int item, int ratio);
void add_to_analogPropertyTable(__aProperty* apPtr, word index);
void add_to_analogPropertyTableFull(__aProperty* apPtr, word index, char * neStatus, S16 * detectEnable);
int get_analogPropertyTableRow(snmp_parms *p);
__aProperty * get_analogPropertyPtr(int apLoc);
//void insert_analogProperty(snmp_parms * const p, __aProperty* apPtr, snmp_callback cb);
void insert_analogProperty(snmp_parms * const p, __aProperty* apPtr);
void remove_analogProperty(snmp_parms * const p, __aProperty* apPtr);

//routine for discreteTable implement in property.c
//int SaveDiscreteTable(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
//int cb_dpTable(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
void discreteAlarmSetting(__dProperty * dpPtr, int alarmEn, int AlarmValue, byte alarmChg, byte TrapEn);
//void discreteAlarmSetting(__dProperty * dpPtr, int alarmEn, int AlarmValue, byte alarmChg, byte TrapEn, int (*fn)());
void discreteAlarmTrapSetting(__dProperty * dpPtr, int trap_num, word noids, char *alarmText);
void discreteAlarmTrapEnable(__dProperty * dpPtr, byte En);
void add_to_discretePropertyTable(__dProperty * dpPtr, word index);
void add_to_discretePropertyTableFull(__dProperty * dpPtr, word index, char * neStatus, S16 * detectEnable);
int get_discretePropertyTableRow(snmp_parms *p);
//void insert_discreteProperty(snmp_parms * const p, __dProperty * dpPtr, snmp_callback cb);
void insert_discreteProperty(snmp_parms * const p, __dProperty * dpPtr);
void remove_discreteProperty(snmp_parms * const p, __dProperty* dpPtr);

//routine for alarmsIdent implement in alarm.c
void init_alarmLogTable(void);
void insert_alarmsIdent(snmp_parms * const p);
//void add_to_alarmLogTable(char alarmState, char neStatus, snmp_oid *oid, int varVal, word *trapVarBinding3Ptr);
void add_to_alarmLogTable(__aProperty *pPtr);

//routine for commonIdent.commonAdminGroup implement in commonAdminGroup.c
void update_comLogicalID(longword * lwd);
void init_commonAdminGroup(snmp_oid* devOid, U32 devID);
void insert_commonAdminGroup(snmp_parms * const p);

//routine for commonIdent.commonAdminUseEthernet.commonAgentGroup implement in commonAgentGroup.c
void insert_commonAgentGroup(snmp_parms * p);

//routine for commonIdent.commonAdminUseEthernet.commonDeviceGroup implement in commonDeviceGroup.c
void init_commonDeviceInfoTable(oidlevel oidIdent, int dvType);
void insert_commonDeviceGroup(snmp_parms * const p, __comDevInfoTable * pDevInfoTable, __dProperty * dpPtr, int maxSlot);

//routine for commonIdent.commonAdminUseRf implement in commonAdminUseRf.c
void init_commonUseRf(void);
// int cb_SaveMultiAddrTable(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
// int cb_SaveBackoffParams(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
// int cb_SaveRfGroup(snmp_parms * p, int wr, int commit, char * v, word * len, word maxlen);
// void insert_commonMacAddress(snmp_parms * p);
// void insert_commonBackoffParams(snmp_parms * p);
// void insert_commonMacStatus(snmp_parms * p);
// void insert_commonRfGroup(snmp_parms * p);
void insert_commonUseRf(snmp_parms * p);
void insert_commonPhyAddress(snmp_parms * p);
void setApName(__aProperty* apPtr, char *apName);
void setApFmt(__aProperty* apPtr, char *fmtStr);
void setApRatio(__aProperty* apPtr, float ratio);
void setDpName(__dProperty* dpPtr, char *dpName);
void setDpFmt(__dProperty* dpPtr, char *fmtStr);


extern __commonAdminGroup commonAdminGroup;
extern __alarmLogTable alarmLogTable[MAX_ALARM_LOG];
extern __comDevInfoTable comDevInfoTable[];
extern __aProperty	analogPropertyTable[];
extern __dProperty	discretePropertyTable[];
extern _agParam agParam;

extern char sysContact[64];
extern char sysName[32];
extern char sysLocation[64];
extern char	comLogicalID[40];
extern S16	comCheckCode;
//extern S16 	comAgentBootWay;
//extern word	maxmesgs;
//extern word	minintvl;
//extern word	maxintvl;

extern short max_APT, max_DPT;
extern word trapindices[4];	//for Trap Variables binging
extern U32 posixTime;
extern char	alarmText[32];			//Alarm Text
extern unsigned short apMajorAlm, apMinorAlm, dpMajorAlm, dpMinorAlm;

//extern int cur_Alarm_Num;

#ifdef LOCAL_SAVE
extern const char defVendor[];
extern const char defVendorInfo[];
#else
extern char defVendor[];
extern char defVendorInfo[];
#endif
extern const char defFirmware[];
extern char ModelNumber[];
extern char SerialNumber[];

extern const short commonMaxMulticastAddresses;	// = MAX_MULTICASTADDR
extern _commonMulticastAddressTable commonMulticastAddressTable[MAX_MULTICASTADDR];
extern _commonBackoffParams commonBackoffParams;
extern unsigned int commonForwardPathLOSEvents;
extern unsigned int commonForwardPathFramingErrors;
extern unsigned int commonForwardPathCRCErrors;
extern unsigned int commonInvalidMacCmds;
extern unsigned int commonBackwardPathCollisionTimes;
extern _commonRf commonRf;
extern const char help_mctab_mng[];

//Predefined Backup parameter
#define BAKUP_ANALOG_TAB(row)	{ &analogPropertyTable[row].ap, 18}
#define BAKUP_DISCRETE_TAB(row)	{ &discretePropertyTable[row].discreteAlarmEnable, 6}
#define BAKUP_SYSNAME		{ (void*)sysName, sizeof(sysName)}
#define BAKUP_CONTACT		{ sysContact, sizeof(sysContact)}
#define BAKUP_LOCATION		{ sysLocation, sizeof(sysLocation)}
#define BAKUP_LOGICALID		{ comLogicalID, sizeof(comLogicalID)}
#define BAKUP_CHECK_CODE	{ &comCheckCode, sizeof(S16)}
//#define BAKUP_BOOTWAY		{ &comAgentBootWay, sizeof(S16)}
//#define BAKUP_MAXTRAPS		{ &maxmesgs, sizeof(word)}
//#define BAKUP_MININTVL		{ &minintvl, sizeof(word)}
//#define BAKUP_MAXINTVL		{ &maxintvl, sizeof(word)}
#define BAKUP_AGPARAM		{ &agParam, sizeof(agParam)}
#define BAKUP_MULTIADDRTAB	{ (void*)commonMulticastAddressTable, sizeof(commonMulticastAddressTable)}
#define BAKUP_BACKOFFPARAM	{ (void*)&commonBackoffParams, sizeof(commonBackoffParams)}
#define BAKUP_RFINTERFACE	{ (void*)&commonRf, sizeof(commonRf)}

#endif /* __NSCRTV_H__ */
