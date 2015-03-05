/* snmp.h --Snmp Protocol function Header file. */

#ifndef __SNMP__
#define __SNMP__

#define SNMP_TRAPS
#define SNMP_MAX_TRAPS 8
#define SNMP_MAX_IPFLT 4
#define SNMP_MAX_COMMUNITIES 8
#define MAX_TRAP_SEND 2

#define SNMP_INTERFACE IF_ANY	// IF_DEFAULT
#define DEFAULT_TRAPIP "192.168.1.1"
#define SNMP_PORT 161
#define SNMP_TRAP_PORT 162
#define SNMP_TOS IPTOS_RELIABLE

// Configuration definitions
#define SNMP_MAX_DATA 2048

#ifndef OEM_AGENT_COMM
	#define OEM_AGENT_COMM "oem_comm"
#endif

#define SNMP_MAX_MONITOR 0 //turn off check original

// Define largest octet string which may be retrieved or set via SNMP. Making this larger only affects the amount of stack
// space used by the SNMP handler functions.  It does not limit internal storage of string values in the MIB tree.
//The largest practical size would be a few bytes less than SNMP_MAX_DATA.  The minimum allowable size is 2*SNMP_MAX_NAME.
#ifndef SNMP_MAX_STRING
	#define SNMP_MAX_STRING	128
#endif

// Define maximum string length of community names (i.e. passwords)
#ifndef SNMP_MAX_COMMUNITY_NAME
	#define SNMP_MAX_COMMUNITY_NAME	14
#endif

// Define maximum number of distinct community names
#ifndef SNMP_MAX_COMMUNITIES
	#ifdef SNMP_TRAPS
		#define SNMP_MAX_COMMUNITIES	3
	#else
		#define SNMP_MAX_COMMUNITIES	2
	#endif
#endif

// Minimum interval between transmission of trap messages, specified
// in milliseconds.  Helps prevent inadvertent network overload.
// Must not be more than 30,000 milliseconds.
#ifndef SNMP_MIN_TRAP_INTVL
	#define SNMP_MIN_TRAP_INTVL 1500
#endif

// Default communities.  Do not change these definitions.
#define SNMP_PUBLIC			0
#define SNMP_PUBLIC_MASK		0x01
#define SNMP_PRIVATE			1
#define SNMP_PRIVATE_MASK		0x02

//Added by Sch
#define SNMP_USERDEF0			2
#define SNMP_USERDEF1			3
#define SNMP_USERDEF2			4
#define SNMP_USERDEF3			5
#define SNMP_USERDEF4			6
#define SNMP_USERDEF5			7
#define SNMP_USERDEF0_MASK		0x04
#define SNMP_USERDEF1_MASK		0x08
#define SNMP_USERDEF2_MASK		0x10
#define SNMP_USERDEF3_MASK		0x20
#define SNMP_USERDEF4_MASK		0x40
#define SNMP_USERDEF5_MASK		0x80

//#define SNMP_TRAPDEST_MASK		0x04
//#define SNMP_TRAPDEST		2

#ifndef SNMP_DFLT_READMASK
	#define SNMP_DFLT_READMASK		(SNMP_PUBLIC_MASK|SNMP_PRIVATE_MASK)
#endif

#ifndef SNMP_DFLT_WRITEMASK
	#define SNMP_DFLT_WRITEMASK	SNMP_PRIVATE_MASK
#endif

#if SNMP_MAX_STRING < 2*SNMP_MAX_NAME
	#error "SNMP_MAX_STRING must be at least 2*SNMP_MAX_NAME"
#endif

//Snmp trap structure added by sch
typedef struct {
	U32 trap_ip;		// trap destination ip address
//	U16 c_index;		// Community index to use
	U16 state;		//Enable/Disable state about this trap ip
	char community[SNMP_MAX_COMMUNITY_NAME+1];
} snmp_trap_struc;

//Data structures
typedef struct {
	char name[SNMP_MAX_COMMUNITY_NAME+1];	// Name i.e. password
	U8 mask;				// This community access mask
} snmp_community;

// Global struct
typedef struct {
	U16	next_comm;	//Next free entry
	snmp_community comm[SNMP_MAX_COMMUNITIES];	
	U16	state;		//State as follows
#define SNMP_S_INIT	0	//Initial
#define SNMP_S_WAITING	1	//Active and waiting for datagrams
#define SNMP_S_PAUSED	2	//Active, but currently suspended
#define SNMP_IS_V2C		0x8000	//Active, but currently suspended
	char * outbuf;		//Buffer for assembling outgoing datagram

//These fields are for maintaining snmp timeticks, which (inconveniently) are 1/100th second ticks. 
//Rather than adding yet another counter to the periodic interrupt, we fake it by maintaining a 1/100 second count 
//which is periodically updated to forestall wrap-around problems.
//	longword	ms_ref;		// Reference MS_TIMER count
//	longword	tick_ref;	// Corresponding timetick counter at above ref. point
//	U16	upd_timeout;	// Update timeout value (ms)
	U16	monitor_timeout;	// Monitor time interval counter (ms)

//Various timetick epochs i.e. base timestamp values, to which timetick variables are referred.
//	longword	start_epoch;	// Time when SNMP started.
	udp_Socket	sock;	//SNMP socket
	S16 max_snmpVarBindings;
#ifdef SNMP_TRAPS
#if SNMP_MAX_MONITOR > 0
	snmp_monvar	mon[SNMP_MAX_MONITOR];	// Monitored variable information
#endif
#endif
} snmp_globals;

extern snmp_globals _snmp;
extern snmp_trap_struc _snmp_traps[SNMP_MAX_TRAPS];
//extern snmp_ipflt_struc _snmp_ipflt[SNMP_MAX_IPFLT];		
extern U16 _snmp_traps_mask;
extern unsigned short uptimeIdx, trapOidIdx;
//extern U16 sysTraps;
//extern int commonAgentTraps;


//function protype
void snmp_community_init(void);
int snmp_community_add(char * cname, U8 mask);
//int snmp_communities_set_dflt(char * public, char * private, char * trapdest);
int snmp_community_set(U16 c_index, char * cname, U8 mask);
char * snmp_community_name(U16 c_index, int * length);
int snmp_community_mask(U16 c_index);
int snmp_community_existed(char *cname);
int snmp_community_delete(U16 c_index);

int snmp_stop(void);
int snmp_start(void);

longword snmp_timeticks(void);
longword snmp_time_since(longword epoch);
//int snmp_trap(longword ipaddr, U16 c_index, int trap_num, U16 noids, U16 * indices);
int snmp_trap(longword ipaddr, char * comm, int trap_num, word noids, word * indices, int ver);
int snmp_monitor( U16 index, long minval, long maxval, U16 minintvl, U16 maxintvl, U16 nmesg,
		 longword * ipaddr, U16 c_index, int trap_num, U16 noids, U16 * indices );
int snmp_unmonitor(U16 index);

char* _snmp_parselength(char* start, char* end, U16* length);
char* _snmp_parseunsigned(char* start, char* end, void* value, int valuebytes);
char* _snmp_parseoctetstr(char* start, char* end, char* value, int maxlen);
char* _snmp_parsesequence(char* start, char* end, char** startseq, int* length);
char* _snmp_parsenull(char* start, char* end);
int _snmp_ber2rler(snmp_oid * oid, char * name, U16 namelen);
//char* _snmp_parsevariable(char* start, char* end, snmp_message* msg);
//char* _snmp_parsevarbinding(char* start, char* end, snmp_message* msg);
//char* _snmp_parsevarbindings(char* start, char* end, snmp_message* msg);
//char* _snmp_parsepdu(char* start, char* end, snmp_message* msg);
//char* _snmp_parsemessage(char* start, char* end, snmp_message* msg);
char* _snmp_buildlength(char* start, char* end, U16 value);
char* _snmp_buildint(char* start, char* end, unsigned long value, int type);
char* _snmp_buildoctetstr(char* start, char* end, char* str, U16 length, int type);
char* _snmp_buildsequence(char* start, char* end, char** length_fixup, U16 length, int sequence_ch);
char* _snmp_fixupsequence(char* length_fixup, char* end);
char* _snmp_buildoid(char* start, char* end, char* name, U16 name_length);
U16 _snmp_rler2ber(snmp_oid * oid, char * name);
//int _snmp_setvars(snmp_parms * p, snmp_message * msg, int commit, char * buf, U16 buflen);
//char* _snmp_buildvariables(char* start, char* end, snmp_message* msg);
//char* _snmp_buildpdu(char* start, char* end, snmp_message* msg, int iface);

//char* _snmp_processmessage(char* start, char* end, snmp_message* msg, int iface);

void _snmp_check_mon(void);
void set_check_mon(void (*check_mon_fn)());

//int _snmp_handler(int event, udp_Socket * s, ll_Gather * g, _udp_datagram_info * udi);
int _snmp_tick(void);
void _snmp_init(void);
S16 Set_Max_SnmpVarBindings(S16 nVB);

void allowTraps(void);
int snmp_traps(int trap_num, U16 noids, U16 * indices);

//int con_trapmng(ConsoleState* state);
int __FindTrap(long ip);
void updateMib(int i);
int __snmpTraps(void);
void allowTraps(void);

void _comm_trap_init(void);
void ip_filter_init(void);
char* _buildlength(char* s, U16 v);
char* _buildint(char* s, long v, int t);
char* _buildoctetstr(char* s, char* str, U16 length, int type);
char* _buildoid(char* s, snmp_oid * oid);
U16 get_Oid_BERLen(snmp_oid * oid);
U16 get_Oid_FldLen(snmp_oid * oid);
void comm_postload(void* dataptr);

void Set_cbRxSnmp(void (*fn)());
void Set_cbTxSnmp(void (*fn)());
void Set_cbSnmpTrap(void (*fn)());
void Set_SnmpVer(int ver);

#define CONSOLE_COMM_BACKUP { &_snmp.comm, sizeof(_snmp.comm), comm_postload, NULL }
#define CONSOLE_TRAP_BACKUP { &_snmp_traps, sizeof(_snmp_traps), NULL, NULL }
#define CONSOLE_IPFLT_BACKUP { &_snmp_ipflt, sizeof(_snmp_ipflt), NULL, NULL }

#endif	/* __SNMP__ */
