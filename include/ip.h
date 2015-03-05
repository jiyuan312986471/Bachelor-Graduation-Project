#ifndef __IP_H__
#define __IP_H__

#include "typeDef.h"

// Flags for return if information from custom packet handlers
#define CUSTOM_PKT_FLAG_PROCESS	0x0001

/* The Internet Header: */
typedef struct {
	byte ver_hdrlen;
	byte tos;
	word length;
	word identification;
	word frags;
	byte ttl;
	byte proto;
	word checksum;
	longword source;
	longword destination;
} in_Header;

typedef struct {
	longword s_addr;
} in_addr_t;

// Following flags in network order (in the frags field)
#define IP_DF 0x0040	// Don't fragment
#define IP_MF 0x0020	// Not the last fragment
#define IP_OFFSET_N	0xFF1F	// Mask for the offset bits

#define in_GetVersion(ip) ((ip)->ver_hdrlen>>4)
#define in_GetHdrlen(ip)  ((ip)->ver_hdrlen&0x0f)  /* 32 bit word size */
#define in_GetHdrlenBytes(ip)  (in_GetHdrlen(ip) << 2) /* 8 bit byte size */
#define in_GetTos(ip)      ((ip)->tos)
#define in_GetTTL(ip)      ((ip)->ttl)
#define in_GetProtocol(ip) ((ip)->proto)

/*
 * Type-of-Service (TOS) definitions (see RFC1349).  You should set _one_ of
 * these values in any one packet (not OR them together).  The precedence field (3 MSBs)
 * and MBZ field (LSB) must be zero.
 */
#define IPTOS_DEFAULT	0x00
#define IPTOS_CHEAP		0x02	// Minimize monetary cost
#define IPTOS_RELIABLE	0x04	// Maximize reliability
#define IPTOS_CAPACIOUS	0x08	// Maximize throughput
#define IPTOS_FAST		0x10	// Minimize delay
#define IPTOS_SECURE	0x1E	// Maximize security

#ifndef ICMP_TOS
	#define ICMP_TOS IPTOS_DEFAULT
#endif


extern word ip_id;				// packet number

typedef struct {
	byte iface;					// Destination interface
	union {
		struct {				// This also used for wifi
   		byte dest[6];			// Destination ethernet address
   		byte src[6];			// Source ethernet address
   		word type;				// Network protocol number
   		byte data[MAX_MTU];		// Data payload
   	} ether;
		struct {
   		byte dest[6];			// Destination access concentrator address
   		byte src[6];			// Source ethernet address
   		word type;				// Network protocol number (0x8864 for PPPoE)
   		byte ver;				// Version field (set to 0x11)
   		byte code;				// Code (0x00)
   		word session_id;		// Session ID
   		word len;				// Length of data payload
   		word protocol;			// PPP protocol field (0x00C1 for IP)
   		byte data[MAX_MTU];		// Data payload
   	} pppoe;
   	struct {
   		word addctl;			// Address/control field (0xFF03)
   		word protocol;			// PPP protocol field (0x00C1)
   		byte data[MAX_MTU];		// Data payload
   	} pppserial;
   	byte data[MAX_MTU];			// Payload for non-ethernet
   } u;
} eth_Packet;


// This is THE outgoing packet.  Use is deprecated: using gather for transmit
// to avoid the need for this buffer.  No memory will be allocated for it
// unless the deprecated _eth_* functions are used.
extern eth_Packet outbuf;

#define ETH_MIN	60              // Minimum Ethernet packet size 

// Link layer protocol numbers
#define PD_ETHER        1
#define PD_SLIP         6

/*
 * This is the global root packet receive buffer pool.
 * This is a linked pool, and is used to manage the ll_prefix structs.  This struct points
 * to one or more buffers in the xmem pool (which is not linked)
 */
//extern Pool_t _pbuf_pool;

#define IP_HEADER_SIZE  20

// Lengths of IP options
#define IP_OPT_ROUTERALERT_LEN	4
#define IP_MAX_LL_HDR	 (MAX_OVERHEAD+1)			// Largest supported link-layer header size, plus 1.
#define IP_MAX_PKT_HDR  (IP_MAX_LL_HDR + IP_HEADER_SIZE + 24)
#define IP_MAX_TCP_HDR  (IP_MAX_LL_HDR + IP_HEADER_SIZE + 24)	// 24 is TCP header plus MSS oftion for SYN-- this is the largest we send currently.
#define IP_MAX_UDP_HDR  (IP_MAX_LL_HDR + IP_HEADER_SIZE + 8)	// UDP always has 8-byte header
#define IP_MAX_IP_HDR   (IP_MAX_LL_HDR + IP_HEADER_SIZE)

int is_valid_source(longword ipaddr, int iface, int local_only);
int is_nonlocal_subnet(longword ipaddr, byte iface);
int is_subnet_bcast_addr(longword ipaddr, byte iface);
int is_subnet_net_addr(longword ipaddr, byte iface);
int is_any_my_addr(longword ipaddr);
int is_all_nonlocal_subnet(longword ipaddr);

longword gethostid_iface(word iface);
#define gethostid() gethostid_iface(IF_DEFAULT)
word ip_iface(longword ipaddr, int local_only);
void ip_print_ifs(void);



int pkt_init( void );
int pkt_gather(ll_Gather * g);
void pkt_buf_release(ll_prefix *LL);
void _pkt_dump(ll_prefix *p);

ll_prefix *pkt_received(void);
ll_prefix *ip_handler(ll_prefix *LL);

in_Header * pkt_reply_ip(ll_prefix *LL, eth_Packet * base, ll_Gather * g, eth_address *e);
in_Header * pkt_make_ip(ATHandle ath, eth_Packet * base, ll_Gather * g);

word fchecksum(void * data, word len);

word gchecksum(ll_Gather * g);
word lchecksum(ll_prefix *LL, word offs, word len);
//word _f_checksum(char *buf, word len, word initial, int * odd);




#endif  /* __IP_H__ */
