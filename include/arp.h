#ifndef __ARP_H__
#define __ARP_H__

#include "typeDef.h"
#include "net_def.h"

// ARP types, in network byte order
#define arp_TypeEther	0x0100

// ARP op codes, in network byte order
#define ARP_REQUEST		0x0100
#define ARP_REPLY			0x0200

// ARP packet structure
typedef struct {
	word hwType;
	word protType;
	word hwProtAddrLen;  // hw and prot addr lengths
	word opcode;
	eth_address srcEthAddr;
	__packed longword srcIPAddr;
	eth_address dstEthAddr;
	longword dstIPAddr;
} arp_Header;

#define ATH2INDEX(ath) ((ath) & 0x00FF)
#define ATH2SEQNO(ath) ((ath) >> 8)

// ARP cache table entry(ATE). Each ATE contains host-related information; most importantly the hardware address of the next hop to get to the host.
typedef struct _ATEntry {
	ATHandle ath;				// Handle for this entry (0 if not used)
	word flags;			// Flags as follows:
#define ATE_PERMANENT		0x0001	// Do not expire this entry
#define ATE_RESOLVING		0x0002	// In process of being resolved
#define ATE_ROUTER_ENT		0x0004	// This is a router entry
#define ATE_FLUSH			0x0008	// Upper layer requested flush
#define ATE_VOLATILE		0x0010	// Short timeout for this entry
#define ATE_GRACE			0x0020	// This entry in grace period i.e. known but being re-resolved
#define ATE_NOARP			0x0040	// Timeout with no ARP response
#define ATE_ROUTER_HOP		0x0080	// IP address not on this subnet - use "router_used"
#define ATE_PATHMTU_DISC	0x0100	// Path MTU discovery in progress
#define ATE_RESOLVED		0x0200	// HWA is valid (resolved)
#define ATE_MULTICAST		0x0400	// Represents a multicast address
#define ATE_RETRY_MASK		0x7000	// Retry count when resolving
#define ATE_RETRY_SHIFT		12			//   ...corresponding bit shift
#define ATE_REDIRECTED		0x8000	// This entry was ICMP redirected
	longword ip;			// IP address of destination host
	eth_address hwa;		// Corresponding hardware (ethernet or MAC) address
	byte iface;				// Interface number to use
	byte router_used;		// If ATE_ROUTER_HOP, then this refers to router table entry
	longword timestamp;		// Expiration time as ms value comapred to MS_TIMER.
	struct _ATEntry * nextto;		// Next entry to timeout.

#ifdef USE_MULTICAST
	union {
		struct {
			// Per-host information
			longword rtt_avg;			// Average round-trip time (if known, else 0)
			longword rtt_dev;			// RTT average deviation
			word path_mtu;		// Path MTU (if known, else 0)
		} perhost;
		struct {
			int slot;			// Value to which this group address hashes
			byte userflag;		// Has the user explicitly joined this group?
		} multicast;
	} u;
#endif
} ATEntry;


/*
 * Router table entry (RTE).  One or more of these for each router ("gateway") which
 * allows access to hosts not on the local subnet.
 */
typedef struct {
	ATHandle ath;				// Handle into ATE table for this router (the entry will
											// have ATE_ROUTER_ENT set).  0 if this entry not used.
											// May also be ATH_P2P+iface for a point-to-point route.
	word flags;			// Flag bits as follows:
#define RTE_TRANSIENT		0x0001	// This entry added by ICMP router discovery
#define RTE_DHCP			0x0002	// This entry added by DHCP
#define RTE_REDIRECT		0x0004	// This entry added by ICMP redirect
													//  - if not any of the above, was preconfigured.
#define RTE_DEAD			0x0008	// Router appears to be defunct
	union {
		struct {
// subnet and mask only valid for preconfigured routers, to try to select the best first hop based on the IP address.
			longword subnet;			// Subnet handled by this router entry
			longword mask;				// Subnet mask for the above
		} preconfig;

		struct {
			// preference and timestamp only valid for transient routers
			long preference;		// Relative preference as default router
			longword timestamp;		// Time at which this entry expires
		} transient;
	} u;
} RTEntry;

extern ATEntry _arp_data[ARP_TABLE_SIZE];
extern int _arp_seqnum;
extern ATHandle _arp_resolved;
extern ATEntry * _arp_towait;
extern RTEntry _arp_gate_data[ARP_ROUTER_TABLE_SIZE];
extern int _router_last_add;

void arp_dumpHeader(arp_Header *arp);
ATEntry *arp_getArpData(void);
RTEntry *arp_getArpGateData (void);
void _arp_add_gateway( char *data, longword ip );
void _arp_request(longword dstip, longword srcip, word iface);
void _arp_init(void);
void _arp_unlink_to(ATEntry * ate);
void _arp_sched_to(ATEntry * ate, longword msec);
void arpcache_purge_iface(word iface);
ATHandle arpcache_search(longword ipaddr, int virt);
ATHandle arpcache_search_iface(longword ipaddr, int virt, word iface);
ATHandle arpcache_hwa(ATHandle ath, void * hwa);
ATHandle arpcache_iface(ATHandle ath, word * iface);
ATHandle arpcache_ipaddr(ATHandle ath, longword * ipaddr);
ATHandle arpcache_flush(ATHandle ath);
ATHandle arpcache_create(longword ipaddr);
ATHandle arpcache_create_iface(longword ipaddr, word iface);
ATHandle arpcache_new(longword source, void * _hwa, word iface);
char * arpcache_printflags(char * buf, word flags);
void arpcache_print(word e);
void arpcache_printall(void);
ATHandle arpcache_load(ATHandle ath, void * _hwa, word iface, word flags, byte router_used);
ATHandle arpresolve_start(longword ipaddr);
ATHandle arpresolve_start_iface(longword ipaddr, word iface);
longword arpresolve_ipaddr(ATHandle ath);
ATHandle arpresolve_check(ATHandle ath, longword ipaddr);
longword router_ipaddr(RTEntry * rte);
ATHandle router_add(longword ipaddr, word iface, longword subnet, longword mask, word flags);
ATHandle router_delete(longword ipaddr);
void router_del_all(void);
int router_reachable_iface(longword rip, ATHandle ath, word iface);
ATHandle router_for_iface(longword ipaddr, word * router_used, word * r_iface, word siface);
#define router_for(p1, p2, p3) router_for_iface(p1, p2, p3, IF_ANY)
int router_print(word r);
int router_printall(void);
void _arp_tick(void);
int _arp_send_response( word iface, arp_Header *arp);
ll_prefix * _arp_handler(ll_prefix * LL);
int _arp_send_gratuitous(word iface);
int _arp_resolve( longword ina, eth_address *ethap, int nowait );
ATHandle _arpcache_multicast_setuserflag(ATHandle ath, byte userflag);
ATHandle _arpcache_multicast_getuserflag(ATHandle ath, byte* userflag);
ATHandle _arpcache_multicast_saveslot(ATHandle ath, int slot);
int _arpcache_mc_checkhashremove(ATHandle ath);
void _arpcache_delete(ATHandle ath);
void _arpcache_report_all_multicasts(word iface, int deciseconds);
void _arp_sched_to_multicast(ATHandle ath, byte deciseconds);
void _arp_sched_to_multicast_random(ATHandle ath, byte deciseconds);


#endif /* __ARP_H__ */
