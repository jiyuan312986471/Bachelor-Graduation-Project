#ifndef __NET_DEF_H__
#define __NET_DEF_H__

#include "typeDef.h"
#include "net_Conf.h"

#define USE_TELNET
//#define USE_MULTICAST


//#define NET_VERBOSE
//#define IP_VERBOSE
//#define ARP_VERBOSE
//#define ICMP_VERBOSE
//#define TCP_VERBOSE
//#define UDP_VERBOSE
//#define BOOTP_VERBOSE
//#define DNS_VERBOSE
//#define SNMP_VERBOSE
//#define MIB_VERBOSE
//#define HTTP_VERBOSE

// FRAGSUPPORT enables support for packet reassembly of fragmented packets
//#define FRAGSUPPORT			

#define SIMPLE_PREFIX
//#define TCP_REF_SEQ_ACK

//#define MAX_TCP_SOCKET_BUFFERS 4
#define USE_IF_CALLBACK

//the preloaded ethernet driver is deprecated
#define USE_ETH_PRELOADED_DRIVER		0

// Return values from ifpending() and linkpending()
#define IF_DOWN			0
#define IF_COMING_UP	1
#define IF_UP			2
#define IF_COMING_DOWN	3


#ifdef USE_DHCP
	#define NUM_DHCP_IF 1	// (ETHERNET_ONBOARD + WIFI_ONBOARD)
#endif
// Basic typedefs

#include "tbuf.h"

/* IPADDR
SYNTAX:	U32 IPADDR( byte a, byte b, byte c, byte d)
DESCRIPTION:	This MACRO converts four bytes into an unsigned long.
				For example:	IPADDR(192,168,1,1) is equivalent to 0xC0A80101
								IPADDR(255,255,255,0) is equivalent to 0xFFFFFF00
PARAMETERS:		4 parameters from 0 to 255, used as the octets of the IP address.
RETURN VALUE:	An unsigned long built using the 4 byte parameters, with a as the MSB and d as the LSB.
*/
#define IPADDR(a,b,c,d) (((unsigned long)(a) << 24) + ((unsigned long)(b) << 16) + ((unsigned long)(c) << 8) + (d))
#define LL_PREFIX 8
// Mapping of the prefix struct.
typedef struct ll_prefix_t {
	byte ll_flags;	// Flags.  All zeros means the entry is currently receiving. A non-zero value is interpreted as follows:
#define LL_ERROR		0x01	// This packet received in error e.g. a CRC test failed, or there was an overrun.  
								// When pkt_received() sees this flag, the packet is returned to the free pool.  
								// Note that ISR-based packet drivers need to set this flag rather than freeing the packet themselves.
#define LL_FRAGMENT		0x02	// This is a fragment
#define LL_BROADCAST	0x04	// Received on link-layer broadcast address
#define LL_MULTICAST	0x08	// Received on a link-layer multicast address
#define LL_PROMISC		0x0C	// Received on a mismatching address
#define LL_SCATTERED	0x10	// Data payload moved directly to transport layer buffer - not yet implemented, intended for data copy reduction.
#define LL_INBAND		0x20	// This packet is not a normal link-layer packet. Currently, this flag is only set for serial PPP data 
								// received in "raw" mode e.g. for modem control.
#define LL_OUTBUF		0x40	// This buffer in use for output.  Used by drivers where the output data needs to be retained for a substantial time.
#define LL_READY		0x80	// This flag is set when the packet driver has finished receiving the packet, and it is ready for processing by pkt_received().
	byte iface;		// Interface number.
	word seq;		// Received sequence number.  This is actually a timestamp from the RTC LSBs (32kHz).	Having a timestamp is useful
					// for timing packet arrivals.  Wrap-around is handled providing all packets are processed within 2 seconds of arrival. 
					// This field is used for returning packets in order of arrival.
	word len;		// Length of received packet (possibly including trailer/padding). This may be zero if not known, in which case the length
					// has to be deduced from the IP header or other information.

#ifndef SIMPLE_PREFIX
   // Buffer address fields.
	word len1;		// Length of first xmem section (starts at 0, incremented as data written)
	byte *data1;	// First xmem data extent (physical addr)  Following used for transmit packets only...
	word len2;		// Length of 2nd xmem section
	byte *data2;	// 2nd xmem data extent (physical addr)
	word len3;		// Length of 3rd xmem section
	byte *data3;	// 3rd xmem data extent (physical addr)

   // These fields indicate the same buffer(s), except that they are used
   // dynamically as the packet is being received.  The rlen* fields indicate
   // the remaining space in the buffer, and the seg* fields are the address of
   // the next byte.  Historical note: the 'seg' names refer to the old segmented
   // address style of access, however these are now ordinary far data pointers.
	word	rlen1;			// Starts at buffer size, decremented as data written.
	byte * seg1;		// Starts at start of buffer, incremented as data written.

   // These fields are set by the network stack as various header levels are
   // parsed out of an incoming packet.  This allows just the ll_prefix to be
   // passed around as a parameter, instead of increasing numbers of parameters
   // as new header levels are discovered.  Note that the link-layer header is
   // implicit: it is always offset 0. These are stored in pairs: *_offs is
   // offset from the start of the packet, *_proto is corresponding protocol of
   // that header.
#endif
   byte	net_offs;		// Network header offset.  This is word size since PPP uses this to index through the entire LCP/IPCP packet.
   byte	net_proto;		// Network protocol:
#define NET_PROTO_IP	0		// Internet Protocol
#define NET_PROTO_ARP	1		// Address Resolution Protocol (has no transport layer)
#ifndef SIMPLE_PREFIX
   byte	tport_offs;		// Transport header offset
   byte	tport_proto;	// Transport protocol:
#endif
#define UDP_PROTO       0x11
#define TCP_PROTO       0x06
#define ICMP_PROTO      0x01
#define IGMP_PROTO		0x02
#define SSL_PROTO       0xFF	// <- this is a dummy for our implementation of SSL sockets
#ifndef SIMPLE_PREFIX
	byte	payload;			// Offset to application data payload (if applicable)

	// Some drivers (DMAETH in particular) can compute an IP checksum over all or part of a packet.  
	// If so, the following fields are set (and chksum_flags is non-zero).
   byte  chksum_flags;			// Flags as follows (0 if no checksum available)
#define CHKSUM_FRAME	1		// chksum over entire frame (incl. CRC) except for dest hw addr field
#define CHKSUM_ETHPL	2		// chksum over ethernet payload (incl. CRC) i.e. excludes 14-byte eth header
#define CHKSUM_TPORT	3		// chksum over tport header thru end of IP payload (note that IP header checksum
								// will always be 0xFFFF for valid header, thus chksum is the same whether or not including a valid IP header).
	word chksum;				// Checksum over the above specified extent.
	// Note that a data buffer follows contiguously for ll_prefix's which are part of the main network buffer pool.
#endif
} ll_prefix;

/*
A static const instance of this struct is defined for each different network driver. It defines the appropriate function 
to call for interface-specific I/O. A pointer to this is maintained in the IFTEntry for the interface. The first parameter 
to each function is a 'void * state'.  This is a pointer to the dynamic state information which is maintained by each driver instance.
 */
typedef struct {
	byte sizeof_state;			// Length of state structure used by this driver.
	byte flags;
#define NCD_TXCOPY	0x01		// Driver cannot transmit all at once before returning
#define NCD_POLL	0x02		// Driver needs to be polled by calling receive() regularly
#define NCD_P2P		0x04		// This is a point-to-point device
	byte sizeof_hwa;			// Size of hardware address (6 for ethernet)
	byte instances;				// Number of device instances supported

	int (*receive)(void*);
	int (*sendpacket)(void*, ll_Gather*);
	int (*ioctl)(void*, int, ...);
	void (*prtregs)(void*);	// for debugging only
	int (*ifctl)(void*, int, int);	// May be NULL if interface is always up. Function called to make the specific interface come up/down.
									// 'up' is nonzero if bringing up. change is nonzero if this is the first call for a change of status.
									// Return value should be one of following:
#define IFCTL_OK	0		// Success, interface is in requested state.
#define IFCTL_FAIL	(-1)	// Failed, interface is opposite the requested state.
#define IFCTL_PEND	1		// Not in requested state, call back later to continue
} NetControllerDevice;

// Generic IOCTL command words...	Parameters
//      --------------------------  -----------------------------------
#define PD_HASFEATURE		99		// int cmd - this test whether ioctl is supported
#define PD_INITIALIZE		100		// word instance, int iface
#define PD_HAVELINK			101		// <none>
#define PD_POWER			102		// int (0 for off, non-zero for on)
#define PD_SETHWA			103		// char*
#define PD_GETHWA			104		// char**
#define PD_ADDMULTICAST		105		// char*, int*   - requires USE_MULTICAST to be defined
#define PD_REMOVEMULTICAST	106		// char*         - requires USE_MULTICAST to be defined
#define PD_INBAND			107		// ll_prefix *
#define PD_DUMPREGS			108		// char* buffer must be large enough to hold all registers
#define PD_GETHWALEN		109		// <none> - only used for RabbitSys user mode programs
#define PD_NETWORK_MODE		110		// int, int (speed, duplex)
									// speed: 0 = Auto-Neg, 1 = 10Mbits, (if IF_X is capable) 2 = 100Mbits.
									// duplex: 0 = Half-Duplex, 1 = Full-Duplex.
									// Note: If speed is Auto-Neg then duplex is a don't care value.
#define PD_POWERSTATUS		111		// <none>


//*CUSTOM*
// When adding new ioctl() command words, it is best to have a unique numbering space for features which are highly specific 
// to the particular driver.  If a feature is expected to be widely supported, add to the end of the above list. For example: the XXX driver 
// has a magic function which enables IP firewalling. Call this option PD_XXX_FIREWALL and number it 200.  If XXX has a mode to set promiscuous 
// packet filtering, this is expected to be widely supported on Ethernet drivers, so call it PD_PROMISC and number it one greater than the
// highest numbered PD_* ioctl() command word in the above (1xx range) list.
// Note IOCTL command codes 300-399 are reserved for PPP drivers.  300-302 are generic PPP.
#define PD_PPP_SENDCTL		300	// char * packet, int len: Similar to sendpacket(),
								// except is used for prioritized sending of an LCP/PAP/IPCP control packet. Returns 1 iff success.
#define PD_PPP_SENDING 		301	// Returns non-zero if currently sending an IP packet
#define PD_PPP_SENDINGCTL	302	// Returns non-zero if currently sending a control packet
// Caution: Numbers 303-399 used by individual PPP drivers (such as PPPLINK.LIB).

// Customized DHCP configuration items.
#ifndef DHCP_NUM_ROUTERS
	#define DHCP_NUM_ROUTERS	1	// Number of routers to external subnets - default to 1
#endif
#ifndef DHCP_NUM_DNS
	#define DHCP_NUM_DNS		1	// Number of domain name servers - default to 1
#endif
#ifndef DHCP_NUM_SMTP
	#define DHCP_NUM_SMTP		0	// Number of SMTP (mail) servers
#endif
#ifndef DHCP_NUM_NTP	
	#define DHCP_NUM_NTP		0	// Number of network time protocol servers
#endif
#ifndef DHCP_NUM_QOTD
	#define DHCP_NUM_QOTD		0	// Number of cookie servers
#endif

/*
 * DHCP information.  DHCP/BOOTP can return numerous configuration items of interest.
 * This struct contains the most commonly used information.  It is pointed to by the
 * IFTEntry struct, and may be retrieved using ifconfig(...IFG_DHCP_INFO...).
 */
typedef struct {
	// Commonly used data...
	word num_req_options;	// Number of option bytes in following list.
	byte *req_options;		// Requested DHCP options list (defaults to minimal list).
	int (*opt_callback)();	// Application callback function for option processing.
	void *data;				// User data for callback function etc. Initialized to NULL at power-up.
	word overall_timeout;	// Overall DHCP process timeout (seconds) from IFS_DHCP_TIMEOUT.
   // Internal fields for DHCP state machine...
	int state;			// DHCP state
	longword fallback_ip;	// Save fallback IP address here
	longword xid;			// Transaction ID
	longword starttime;		// SEC_TIMER value when first DHCP discover packet sent
	longword timeout;		// Current timeout (ms rel MS_TIMER)
	word tointvl;			// Next timeout interval (seconds)
	longword dhcppkt;		// UDP packet retained while waiting for ARP timeout
	word pktlen;			// Above packet length.  This field is overloaded during DHCP discovery phase: if non-zero,
   							// 	then a BOOTP response was received while waiting for DHCP offers.
	void * pktpref;			// Packet prefix (really ll_prefix *)
	char dhcp_hwa[6];	// MAC address of DHCP server.  Stored here to bypass ARP.

   // Optional data...
	longword tent_ip;		// Tentative IP address offered by server
	longword tent_subnet;	// Tentative subnet mask offered by server
	longword dhcp_server;	//	IP address of DHCP server last used, or 0 if none.
	longword bootp_host;	// IP address of 'next server' for e.g. getting boot file, or 0.
	longword lease;			// Absolute (SEC_TIMER) value of when current lease expires, or DHCP_PERMANENT if does not expire.
	longword t1, t2;		// Renew and rebind times (as above).
	long timezone;			// Seconds east of Greenwich, according to server, or DHCP_UNKNOWN_TIMEZONE.
#if DHCP_NUM_ROUTERS
	longword		router[DHCP_NUM_ROUTERS];	// Routers
#endif
#if DHCP_NUM_DNS
	longword		dns[DHCP_NUM_DNS];			// Domain name servers
#endif
#if DHCP_NUM_SMTP
	longword		smtp[DHCP_NUM_SMTP];		// Mail servers
#endif
#if DHCP_NUM_NTP
	longword		ntp[DHCP_NUM_NTP];			// Network Time Protocol servers
#endif
#if DHCP_NUM_QOTD
	longword		cookie[DHCP_NUM_QOTD];		// Cookie (Quote Of The Day) servers
#endif
} DHCPInfo;

#ifdef USE_LINKLOCAL
	// struct _ZC_LL_INFO defined later in linklocal.lib, declare as extern here so we can include a pointer to it in IFTEntry.
	extern struct _ZC_LL_INFO;
#endif

// Union which contains interface information which depends on the interface class (ethernet, pppoe or ppp over serial).
typedef union {
	struct {
		word eflags;		// Broadcast ethernet-specific flags...
#define EFLAG_VIRT	0x0001	// This is a virtual ethernet entry.  riface indicates the real i/f.
		word riface;		// Interface number (0, or 1 for 2nd ethernet chip). This is the 'real' interface number for a virtual ethernet interface.
	} eth;
	struct {
		word pflags;					// PPP/PPPOE-specific flags...
#define IFF_PPP_NOROUTE	0x0001			// Do not automatically add router entry when link comes up
		longword peeraddr;
		struct _PPPState * ppp_state;	// PPP state
	} ppp;
} IFTUnion;

// Structure which contains information for each interface - interface table entry:
typedef struct {
	void *state;		// Driver-specific run-time parameters.
	const NetControllerDevice * ncd;	// Pointer to driver functions for this interface
	word instance;		// Driver instance number (0, 1, ...)
	word up;			// 1 if active, 0 if inactive
	word lnk;			// Link status as reported by _net_notify_link() 1 if active, 0 if inactive
						// cf. pd_havelink() which tests real current status.  linkpending() returns AND of this with pd_havelink().
	word mtu;			// Max transmission unit (IP, transport headers plus data)
	longword ipaddr;	// Current IP address of this interface
	longword mask;		// Current subnet mask (or all 1's for PPP)
	longword static_ip;	// IP address configured via IFS_IPADDR
	longword static_mask;	// Netmask configured via IFS_NETMASK
	longword ldown_ipaddr;	// IP address when link last went down, 0 if not known or valid.
	longword ldown_mask;	// Subnet mask when link down
						// This state used when link comes up again to minimize disruption in higher layers.
	word flags;			// Flags as follows:
#define IFF_DHCP           0x0001	// Configure using DHCP
#define IFF_ICMP_CONFIG    0x0002	// Allow dynamic IP address assignment using "arp -s" (directed ping)
#define IFF_DHCP_OK        0x0004	// Set when DHCP successfully configured
#define IFF_ICMP_CFG_OK    0x0008	// Set when IP address set by directed ping
#define IFF_IGMP_V1_ROUTER 0x0010	// Set when an IGMPv1 router is present on this interface
#define IFF_DHCP_FELLBACK  0x0020	// DHCP failed, fell back to static IP
#define IFF_DHCP_QUALIFY   0x0040	// This interface qualifies for DHCP i.e. 'dhcp' pointer is not NULL.
                                 	// Note: if this interface does not qualify, then none of the related DHCP flags can be set.
#define IFF_DHCP_FALLBACK  0x0080	// DHCP fallback is OK if no DHCP server
#define IFF_DHCP_QUERY     0x0100	// DHCP uses INFORM message rather than full discovery.
#define IFF_DHCP_DOMAIN    0x0200	// Make use of domain/hostname returned by server.

#ifdef USE_IF_CALLBACK
	void (*ifcallback)(); 	// Function called when interface status changes. This function may be set by the application 
							// using ifconfig(...IFS_IF_CALLBACK...).  Parameters to this callback function are ifcallback(int iface, int up).  
							// 'up' is non- zero if the interface is now up.  If this function pointer is NULL there is no callback.
#endif
#ifdef USE_IGMP
	longword lastv1msg;	// Time of the last IGMPv1 router message
#endif
#ifdef USE_DHCP
	DHCPInfo *dhcp;			// DHCP state and other info.  NULL unless IFF_DHCP_QUALIFY is set.
#endif
#ifdef USE_LINKLOCAL
	// Link-local state and other info.  NULL if iface is not configured for link-local addressing.
	struct _ZC_LL_INFO	*linklocal;
#endif

	// A union of additional fields which are specific to ppp/pppoe or broadcast ethernet.
	IFTUnion u;
} IFTEntry;



typedef struct {
	byte eaddr[6];
} eth_address;

/* The Ethernet header */
typedef struct {
	eth_address destination;
	eth_address source;
	word type;
} eth_Header;



/*
 * A datahandler callback function type for tcp or udp sockets.
 * Parameters are:
 *  event - event type code (TCP_DH_* or UDP_DH_*)
 *  s - pointer to socket struct (tcp_Socket or udp_Socket)
 *  g - interface number and pointer(s) to received data
 *  info - for UDP, points to _udp_datagram_info; for TCP, currently NULL.
 * Return value is 0 to continue with normal datagram/segment handling, or
 * non-zero if some or all of the data has been processed by the callback
 * and should not be passed to the application.
 * The callback should return 0 for event types that it does not understand,
 * or is not interested in.
 */
typedef int (*dataHandler_t)(int event, void *s, ll_Gather * g, void * info);

/* A socket function for delay routines */
typedef int (*sockfunct_t)(void *s);

/*
 * Handle to an ARP table entry.  This is actually composed of 3 parts:
 *   bits 0-7:  entry index 0..(ARP_TABLE_SIZE-1) for normal entries;
 *              255 for "broadcast" entry which is not stored, but indicates
 *              use of the link-layer broadcast address.
 *   bits 8-14: Handle validity check (sequence).  1..127 for normal entries,
 *              or zero to indicate an unused or invalid entry.
 *   bit 15:    Sign bit: used to indicate error codes on return from
 *              functions which return an ATHandle.
 */
typedef short ATHandle;
#define ATH_UNUSED			0			// Unused table entry
#define ATH_NOENTRIES		(-1)		// No free entries in table
#define ATH_NOROUTER		(-2)		// No router configured
#define ATH_AGAIN			(-3)		// Resolve not yet completed
#define ATH_FAILED			(-4)		// Resolve failed
#define ATH_TIMEDOUT		(-5)		// Resolve timed out
#define ATH_INVALID			(-6)		// Invalid ATH or IP address passed
#define ATH_NOTFOUND		(-7)		// Table entry not found
#define ATH_OBSOLETE		(-8)		// ATH obsoleted by new entry
#define ATH_MISMATCH		(-9)		// IP address mismatch in arpresolve_check()
// The following are "virtual" ARP table entries...
#define ATH_LOOPBACK		240		// Refers to the "this host" entry
#define ATH_BROADCAST		241		// Refers to the broadcast entry
#define ATH_P2P				242		// Numbers 242-255 refers to point-to-point links (i.e. no ARP resolve required).
									// 	The actual ATH number is ATH_P2P + iface where iface is the interface number.
									// 	Thus up to 14 interfaces are supported.
#define ATH_IS_P2P(a) ((a) >= ATH_P2P && (a) < 256)

//#use "TBUF.LIB"

// UDP socket definition
typedef struct _udp_socket {
	/*-----------------------------------------------*
	 * Start of fields common to TCP and UDP sockets *
	 *-----------------------------------------------*/
	struct _udp_socket * next;
	byte ip_type;				// always set to UDP_PROTO
	byte iface;					// Bindable interface, also for bypass ARP - specifies interface
	word err_msg;				// Up to 2 most recent error codes (LSB most recent)
	ATHandle sath;				// ARP Table Handle
	byte tos;					// IP Type Of Service
	byte ttl;					// IP Time To Live
	void (*usr_yield)(void);
	byte rigid;
	byte stress;
	word sock_mode;				// a logical OR of bits
	longword usertimer;			// ip_timer_set, ip_timer_timeout
	dataHandler_t dataHandler;
	longword hisaddr;			// peer's internet address
	word hisport;				// peer's UDP port
	word myport;

#ifdef MCOS_LOCKS
	OS_EVENT *lock;				// the semaphore
	char lock_count;			// how many times we grabbed the semaphore
#endif

	_tbuf rd;					// Read circular buffer
	/* For UDP sockets, the write buffer is optional.  Without a write buffer,
	   the disadvantage is that datagrams may be dropped before reaching the
	   network.  The usual reason for this is that the hardware address of the
	   next hop is not yet resolved by ARP.  Another reason is that the
	   application is generating too many datagrams for the hardware to keep up,
	   especially with PPP, 10MBit ethernet or Wifi which are relatively slow.
	   With the write buffer, ARP resolution should never result in dropped
	   packets, and bursts of packets are more likely to succeed.  In particular,
	   datagrams which need to be fragmented at the UDP level are more likely
	   to be successfully received by the peer.
	*/
	_tbuf wr;					// Write circular buffer
	/*-----------------------------------------------*
	 * End of fields common to TCP and UDP sockets   *
	 *-----------------------------------------------*/

	eth_address	*hisethaddr;	// For bypass ARP if not NULL - otherwise, use sath (ARP cache).
} udp_Socket;

/*
 * TCP Socket definition
 */
typedef struct _tcp_socket {
	/*-----------------------------------------------*
	 * Start of fields common to TCP and UDP sockets *
	 *-----------------------------------------------*/
	struct _tcp_socket * next;
	byte ip_type;				// always set to TCP_PROTO
	byte iface;					// Bindable interface (or IF_ANY)
	word err_msg;				// Up to 2 most recent error codes (LSB most recent)
	ATHandle sath;				// ARP Table Handle
	byte tos;					// IP Type Of Service
	byte ttl;					// IP Time To Live
	void (*usr_yield)(void);
	byte rigid;
	byte stress;
	word sock_mode;				// a logical OR of bits
	longword usertimer;			// ip_timer_set, ip_timer_timeout
	dataHandler_t dataHandler;
	longword hisaddr;			// peer's internet address
	word hisport;				// peer's UDP port
	word myport;

#ifdef MCOS_LOCKS
	OS_EVENT * lock;			// the semaphore
	char lock_count;			// how many times we grabbed the semaphore
#endif

	_tbuf	rd;					// Read circular buffer
// In the tx buffer, bytes [0..unacked-1] have been sent at least once,  bytes [unacked..datalen-1] have not yet been sent.
	_tbuf	wr;					// Write circular buffer
	/*-----------------------------------------------*
	 * End of fields common to TCP and UDP sockets   *
	 *-----------------------------------------------*/

	longword acknum;	// Latest acknowledgment of peer's data
	longword seqnum;	// Sequence number of first (unacknowledged) byte in tx buffer
	long timeout;		// timeout, in milliseconds/
	word window;		// Peer's receive window right edge, relative to the start of our tx buffer (seqnum).
   						// We assume the peer only advances window edge.
	short advwindow;	// Our receive window which we last advertised to the peer.  This is relative to acknum.
						// Note that this is signed, in case the peer actually	pushes data beyond the window we advertised.

	// Some protocols (SSL or TLS in particular) do some processing on the data before the application sees it.  
	// The following pointers refer to the application-side data.  If there is no processing, then the pointers will simply point to 
	// the rd and wr members of this struct.  Otherwise,they point to different buffers provided by the implementation.
	_tbuf *app_rd;
	_tbuf *app_wr;

	word unacked;       // bytes of data we transmitted, but not yet acknowledged.unacked is always <= datalen, and never decreases.
	word frunack;		// Fast restart unack point - value of unacked saved at 3rd duplicate ack
	word startpt;		// Starting point for next send data.  Less than or equal to unacked.  If less than unacked, then data is being retransmitted.
	word cwnd;       	// Congestion avoidance send window (byte count)
	word ssthresh;		// Congestion avoidance slow-start threshold (byte count)
	word state;         // connection state

   longword vj_sa;		// VJ's alg, average round-trip time, 1/8ms units
   longword vj_sd;      // VJ's alg, mean deviation of RTT, 1/8ms units
   longword vj_last;	// last transmit timestamp for RTT estimator purposes
   longword vj_seq;		// Sequence number of data being timed 
   longword rto;		// Current retransmit timeout, ms units
   longword rtt_time;	// time of next transmission

   word kflags;    		// Retransmit flags as follows:
#define TCP_KF_SENDSOON		0x0001	// Scheduling transmit in __near future. rtt_time primed with timeout. 
#define TCP_KF_RETRANSMIT	0x0002	// Retransmit of old data required.  Set in tcp_Retransmitter() if timeout, reset in tcp_send() on next transmission. 
#define TCP_KF_UNHAPPY		0x0004	// Expecting a response from peer.  rtt_time field is primed with timeout. 
#define TCP_KF_UPDRTT		0x0008	// Update RTT estimators using Van Jacobson algo.
#define TCP_KF_TIMERTT		0x0010	// Currently timing a RTT for new data. 
#define TCP_KF_DUPACK		0x0020	// Retransmit requested because of duplicate acks
#define TCP_KF_PROBING		0x0040	// Currently probing peer's window
#define TCP_KF_FIN			0x0080	// Unacked FIN in transmit sequence. 
#define TCP_KF_SYN			0x0100	// Unacked SYN in transmit sequence.
#define TCP_KF_WANTFIN		0x0200	// Want to put FIN in transmit sequence ASAP. This gets reset as soon as we actually send it (i.e. TCP_KF_FIN gets set)
#define TCP_KF_SENDRST		0x0400	// Send a RST segment (aborting connection)
#define TCP_KF_GAP			0x0800	// There is an out-of-order segment (gap) in the receive buffer
#define TCP_KF_KEEPALIVE	0x1000	// Currently in keepalive timeout mode
#define TCP_KF_SEGCHAIN		0x2000	// Currently transmitting a segment chain
#define TCP_KF_NOARP		0x4000	// Suspended due to out-of-date ARP cache entry
#define TCP_KF_DUPACK_SS	0x8000	// "dupack sendsoon".  This set on every rx duplicate ack, and indicates we should retransmit the missing pkt after a timeout.
	short ackdupct;		// Count of duplicate acks received. Incremented when an ack arrives that equals the start of unacked data.  Reset to 0 when ack advances.
#define TCP_DUPACKS	3				// Number of duplicate acks required to trigger retransmission
	longword inactive_to;   // for the inactive flag
	longword datatimer;     // note broken connections
	longword ooosstart;  	// Peer's sequence number of start and (end+1) of out-of-order segment.  This is only valid
	longword ooosend;		// if KF_GAP is set. 

	longword keepalive_time;	// timeout between sending keepalives, 0 to turn off
	longword keepalive_timeout;	// actual timeout for the above
	word mss;
	byte keepalive_state;		// Number of keepalives pending
	byte buffer_flags;
#define TCP_BF_DYNALLOC	0x01	// Tx/Rx buffer dynamically allocated
#ifdef TCP_DATAHANDLER
	void * user_data;		// Application-specific data.  Useful for data handler callbacks
#endif

#ifdef TCP_STATS
	longword rtbytes;		// Total retransmitted bytes 
	longword rtsegments;	// Number of retransmitted segments
	longword txbytes;		// Total tx bytes (new + retransmit)
	longword txsegments;	// Total tx segments (new + retransmit)
	longword timeouts;		// Total real timeouts
	longword sendsoons;		// Total sendsoon timeouts
	longword dupacks;		// Number of times dup ack processing triggered
	longword txetherr;		// Number of ethernet transmit errors
#endif
	byte reservedport_flag;	// socket is on a reserved port
#ifdef TCP_REF_SEQ_ACK
	longword rxRefID;
	longword txRefID;
#endif
} tcp_Socket;

// The TCP/UDP Pseudo Header - used for the purpose of computing/verifying checksums
typedef struct {
	longword src;
	longword dst;
	byte mbz;
	byte protocol;
	word length;
	word checksum;
} tcp_PseudoHeader;



/* sock_type used for socket io */
//FIXME: we can get rid of this define
#define _generic_sock_type sock_type

typedef union {
	struct {
		// Map the first 2 fields common to all socket-like structures
		void * next;	// Generic 'next' pointer for linked lists.  For SSL sockets, this points to underlying TCP socket.
		byte type;		// currently one of TCP_PROTO, UDP_PROTO or SSL_PROTO
	} common;
	udp_Socket udp;
	tcp_Socket tcp;
} _generic_sock_type;

// Macros to determine specific type of a given generic socket, and other things
#define _SOCK_TYPE(g) (((_generic_sock_type *)(g))->common.type)
#define _SOCK_NEXT(g) ((_generic_sock_type *)(((_generic_sock_type *)(g))->common.next))
#define _TCP_SOCK(g)  ((tcp_Socket *)(g))
#define _UDP_SOCK(g)  ((udp_Socket *)(g))
#define _SSL_SOCK(g)  ((ssl_Socket *)(g))
#define _TCP_SOCK_OF_SSL(g) ((tcp_Socket *)(((_generic_sock_type *)(g))->common.next))
#define _IS_TCP_SOCK(g) (_SOCK_TYPE(g) == TCP_PROTO)
#define _IS_UDP_SOCK(g) (_SOCK_TYPE(g) == UDP_PROTO)
#define _IS_SSL_SOCK(g) (_SOCK_TYPE(g) == SSL_PROTO)
#define _TCP_FIELD(g, f) (_TCP_SOCK(g)->f)
#define _UDP_FIELD(g, f) (_UDP_SOCK(g)->f)
#define _SSL_FIELD(g, f) (_SSL_SOCK(g)->f)



/* similar to UNIX */
typedef struct {
	word s_type;
	word s_port;
	longword s_ip;
	byte s_spares[6];      // unused in TCP realm
} sockaddr;

typedef struct
{
	int tcp_socks;
	int tcp_numbufs;
	int tcp_bsize;
	long tcp_BufferMemory;

	int udp_socks;
	int udp_numbufs;
	int udp_bsize;
	long udp_BufferMemory;
} sock_init_config_t;

//holds a connection waiting to be handled by the application
typedef struct _tcp_Pending {
	struct _tcp_Pending *prev;
	struct _tcp_Pending *next;
	long hisaddr;
	word hisport;
	//long	myaddr;
	word myport;
	long seqnum;
	long acknum;
	word mss;
	//eth_address hisethaddress;
	ATHandle ppath;
	unsigned long persist_timeout;
	short open;
} tcp_Pending;

extern void (*system_yield)();
extern void (*dcrtcpd)();
/* user initialization file */
extern void (*usr_init)(char *name, char *value);

typedef const struct {
	const NetControllerDevice * ncd;
	void * state;
	word instance;
	word ifMask;
} _net_driver_table;
extern _net_driver_table net_driver_table[];
#endif	//#ifndef __NET_DEFS_H__


