#ifndef __DNS_H__
#define __DNS_H__

#include "typeDef.h"
#include "servlist.h"

#ifndef DNS_MAX_NAME
	#ifdef MAX_DOMAIN_LENGTH
		#define DNS_MAX_NAME MAX_DOMAIN_LENGTH
	#else
		#define DNS_MAX_NAME 64
	#endif
#endif

// Return values for resolve_name_check()
#define RESOLVE_SUCCESS				 1
#define RESOLVE_AGAIN				 0
#define RESOLVE_FAILED				(-NETERR_RESOLVE_FAILED)
#define RESOLVE_TIMEDOUT			(-NETERR_RESOLVE_TIMEDOUT)
#define RESOLVE_HANDLENOTVALID		(-NETERR_RESOLVE_HANDLENOTVALID)
#define RESOLVE_NOENTRIES			(-NETERR_RESOLVE_NOENTRIES)
#define RESOLVE_LONGHOSTNAME		(-NETERR_RESOLVE_LONGHOSTNAME)
#define RESOLVE_NONAMESERVER		(-NETERR_RESOLVE_NONAMESERVER)

typedef struct {
	int16 id;
	word flags;
	longword resolved_ip;
	longword timeout;
	longword nameserver;		// IP addr of nameserver being tried
	int16 numretries;
	char name[DNS_MAX_NAME+1];
} _dns_table_type;

// Flags for ServList functions
#define DNS_PREDEFINED	0x0002	// This server is predefined (i.e. added using ifconfig(...IFS_NAMESERVER_ADD..)
#define DNS_PPP			0x0008	// Nameserver specified by IPCP when starting PPP interface
#define DNS_DHCP		0x0020	// Nameserver provided by DHCP server
#define DNS_ALL_SOURCES	(DNS_PREDEFINED|DNS_PPP|DNS_DHCP)
#define DNS_SRV_OK		0x0100   // Server OK last time we checked
#define DNS_ALL_HEALTH	(DNS_SRV_OK)

#ifdef USE_DHCP
	#define DNS_TABLE_SIZE	(MAX_NAMESERVERS+DHCP_NUM_DNS*NUM_DHCP_IF)
#else
	#define DNS_TABLE_SIZE	MAX_NAMESERVERS
#endif
extern ServTableEntry _dns_servers[DNS_TABLE_SIZE];	// Server table.  Sorted in order of descending preference.
extern ServTableDesc _dns_server_table;
extern char defaultdomain[DNS_MAX_NAME];
extern char* def_domain;	// Default domain.  Points to the above array, or points to const string, or may be NULL if there is no default domain.

typedef void (*dns_ptr_callback_type)(longword ip, char *hostname);

void _dns_init(void);
int resolve_name_start(const char * hostname);
int resolve_name_check(int handle, longword* resolved_ip);
int resolve_cancel(int handle);
int _send_resolve_req(const _dns_table_type * entry, const char * hostname);
int _dns_pack_name(char * dest, const char * src);
void _dns_tick(void);
void set_dns_ptr_callback( dns_ptr_callback_type user_handler );
void _dns_process_response(void);
void _dns_check_timeouts(void);
longword resolve(const char * name);
int resolve_ptr (longword ip, char *buffer, int buflen);



extern dns_ptr_callback_type dns_ptr_callback;


#endif /* __DNS_H__ */
