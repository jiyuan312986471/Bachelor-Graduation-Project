#ifndef __ICMP_H__
#define __ICMP_H__

#include "typeDef.h"


#ifndef ICMP_TOS
#define ICMP_TOS IPTOS_DEFAULT
#endif
#ifndef ICMP_TTL
#define ICMP_TTL 64
#endif

#ifdef ICMP_PING_SEND_BUFFER
#ifdef ICMP_PING_SEND_LEN
#define ICMP_USE_PINGDATA 1
#endif
#endif
#ifndef ICMP_USE_PINGDATA
#define ICMP_USE_PINGDATA 0
#endif
// If the above is non-zero, then you'll probably want to define the following
// macro to be the name of a callback function.  See function description
// of _send_ping_iface() for details.
//#define ICMP_PINGDATA_CALLBACK pingdata_callback

// backward compatibility
#define _ping(h, c) _send_ping_iface((h), (c), 250, 0, NULL, IF_ANY)

#define ICMP_REFLECT_HEADER		8		// Size of TCP/UDP header to echo in unreachable etc.

typedef struct icmp_unused {
	byte    type;
	byte code;
	word checksum;
	longword   unused;
	in_Header  ip;
	byte spares[ ICMP_REFLECT_HEADER ];
} icmp_unused_t;

typedef struct icmp_pointer {
	byte type;
	byte code;
	word checksum;
	byte pointer;
	byte unused[ 3 ];
	in_Header  ip;
} icmp_pointer_t;

typedef struct icmp_ip {
	byte type;
	byte code;
	word checksum;
	longword   ipaddr;
	in_Header  ip;
} icmp_ip_t;

typedef struct icmp_echo {
	byte type;
	byte code;
	word checksum;
	longword identifier;  // Actually, this is identifier plus sequence
	//word sequence;
	longword index;
} icmp_echo_t;

typedef struct icmp_timestamp {
	byte type;
	byte code;
	word checksum;
	word identifier;
	word sequence;
	longword   original; /* original timestamp */
	longword   receive;  /* receive timestamp */
	longword   transmit; /* transmit timestamp */
} icmp_timestamp_t;

typedef struct icmp_info {
	byte type;
	byte code;
	word checksum;
	word identifier;
	word sequence;
} icmp_info_t;

typedef struct icmp_redirect {
	byte type;
	byte code;
	word checksum;
	longword new_router;
} icmp_redirect_t;

#ifdef ICMP_ROUTER_DISCOVERY
typedef struct icmp_router_adv {
	byte type;
	byte code;
	word checksum;
	byte num_addrs;
	byte addr_size;
	word lifetime;
} icmp_router_adv_t;

typedef struct icmp_router_sol {
	byte type;
	byte code;
	word checksum;
	longword reserved;
} icmp_router_sol_t;
#endif

typedef union {
	struct icmp_unused unused;
	struct icmp_pointer pointer;
	struct icmp_ip ip;
	struct icmp_echo echo;
	struct icmp_timestamp timestamp;
	struct icmp_info info;
	struct icmp_redirect redirect;
#ifdef ICMP_ROUTER_DISCOVERY
	struct icmp_router_adv radv;
	struct icmp_router_sol rsol;
#endif
} icmp_pkt;

typedef struct _pkt {
	in_Header in;
	icmp_pkt icmp;
} _pkt_t;

#define ICMPTYPE_ECHOREPLY       0
#define ICMPTYPE_UNREACHABLE     3
#define ICMPTYPE_SOURCE_QUENCH   4
#define ICMPTYPE_REDIRECT        5
#define ICMPTYPE_ECHO_REQ        8
#define ICMPTYPE_ROUTER_ADV      9
#define ICMPTYPE_ROUTER_SOL		10
#define ICMPTYPE_TIMEEXCEEDED    11
#define ICMPTYPE_PARAM_PROBLEM   12
#define ICMPTYPE_TIMESTAMP_REQ   13
#define ICMPTYPE_TIMESTAMP_REP   14
#define ICMPTYPE_INFO_REQ        15
#define ICMPTYPE_INFO_REP        16

#define ICMP_UNREACH_NET 				0
#define ICMP_UNREACH_HOST 				1
#define ICMP_UNREACH_PROTO				2
#define ICMP_UNREACH_PORT 				3
#define ICMP_UNREACH_FRAGNEEDED 		4
#define ICMP_UNREACH_SRCROUTEFAILED	5

#define ICMP_EXCEEDED_TTL 				0
#define ICMP_EXCEEDED_FRAGREASM 		1


// a user-installed ICMP handler
typedef int (*icmp_handler_type)(in_Header *ip);
// a user-installed ICMP echo handler
typedef int (*icmp_echohandler_type)(longword icmp_dest_addr, byte iface, int bcastdest, in_Header * ip);



int _send_ping( longword host, longword countnum, byte ttl, byte tos, longword *theid );
int _send_ping_iface( longword host, longword countnum, byte ttl, byte tos, longword *theid, word iface );
longword _chk_ping( longword host, longword *ptr );
void icmp_Reply(struct _pkt *p, longword src, longword dest, int icmp_length, byte tos, ll_Gather * g);
void icmp_Unreach(ll_prefix * LL, int what);
void set_icmp_handler( icmp_handler_type user_handler );
ll_prefix * icmp_handler(ll_prefix * LL);
void setICMPEchoHandler( icmp_echohandler_type user_handler );



extern icmp_echohandler_type ICMPEchoHandler;


#endif /* __ICMP_H__ */
