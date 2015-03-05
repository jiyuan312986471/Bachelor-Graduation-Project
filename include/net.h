#ifndef __NET_H__
#define __NET_H__

#include "typeDef.h"
#include "net_Conf.h"

#ifdef MCOS
	#define MCOS_LOCKS
	#define NET_COARSELOCK
	#define NET_COMMON_DNS_LOCK
#endif

// basic configuration options
#ifndef MY_DOMAIN
	#define MY_DOMAIN			NULL
	#define MY_DOMAINNULL
#endif

// maximum size of any one domain name to be looked up, including any global domain concatenated to the requested domain.
#ifndef MAX_DOMAIN_LENGTH
	#define MAX_DOMAIN_LENGTH	128
#endif

// defines the input and output buffer sizes for a socket
// sockets connected to reserved ports can be closed without the 2MSL delay period
#ifndef TCP_FASTSOCKETS
	#define TCP_FASTSOCKETS 1
#endif

// This determines the size of the TCP buffers.  
// If not specified, but SOCK_BUF_SIZE is, then TCP_BUF_SIZE takes on the value of SOCK_BUF_SIZE.  
// It also has further backwards compatibility with tcp_MaxBufSize.
#ifndef TCP_BUF_SIZE
	#ifdef SOCK_BUF_SIZE
		#define TCP_BUF_SIZE SOCK_BUF_SIZE
	#else
		#ifdef tcp_MaxBufSize
			#define TCP_BUF_SIZE (tcp_MaxBufSize * 2)
		#else
			#define TCP_BUF_SIZE 4096
		#endif
	#endif
#endif

// Determines the maximum number of TCP sockets with preallocated buffers.
#ifndef MAX_TCP_SOCKET_BUFFERS
	#define MAX_TCP_SOCKET_BUFFERS 4
#endif


// This determines the size of the UDP buffers.  
// If not specified, but SOCK_BUF_SIZE is, then UDP_BUF_SIZE takes on the value of SOCK_BUF_SIZE.  
// It also has further backwards compatibility with tcp_MaxBufSize.
#ifndef UDP_BUF_SIZE
	#ifdef SOCK_BUF_SIZE
		#define UDP_BUF_SIZE SOCK_BUF_SIZE
	#else
		#ifdef tcp_MaxBufSize
			#define UDP_BUF_SIZE (tcp_MaxBufSize * 2)
		#else
			#define UDP_BUF_SIZE 4096
		#endif
	#endif
#endif

// Determines the maximum number of UDP sockets with preallocated buffers. Defaults to NO UDP buffers.  
// DHCP and/or SNMP allocate and manage their own buffers, so they need not be considered in this setting.
#ifndef MAX_UDP_SOCKET_BUFFERS
	#define MAX_UDP_SOCKET_BUFFERS 0
#endif

// Determines the number of socket locks that are allocated.  
// For uCOS/II, this effectively limits the number of sockets that can be allocated.
#ifndef MAX_SOCKET_LOCKS
	#define MAX_SOCKET_LOCKS (MAX_TCP_SOCKET_BUFFERS + MAX_UDP_SOCKET_BUFFERS)
#endif

#ifdef DISABLE_DNS
	#define ACTUAL_SOCKET_LOCKS	MAX_SOCKET_LOCKS
#else
	#define ACTUAL_SOCKET_LOCKS	(MAX_SOCKET_LOCKS+1)
#endif

#ifndef ETH_MTU
	#if WIFI_ONBOARD	// && R5000 == CPU_ID_MASK(_CPU_ID_)
		#define ETH_MTU 1489		// less 11 bytes for padding 5.5, 11 Mbps (_WIFI_SILKEN_DAC)
	#else
		#define ETH_MTU 1500		// MTU for Ethernet and WIFI (PPPoE will use this minus 8)
	#endif
#endif
#ifndef PPP_MTU
   #define PPP_MTU ETH_MTU		// MTU for serial PPP, default to same as ethernet
#endif

#if ETH_MTU > PPP_MTU
	#define MAX_MTU	ETH_MTU
	#define MIN_MTU	PPP_MTU
#else
	#define MAX_MTU	PPP_MTU
	#define MIN_MTU	ETH_MTU
#endif

/* This symbol specifies the total number of incoming and outgoing packets for
 all interfaces (not just ethernet, as the name implies).  These buffers
 are currently xalloc'd, and each buffer is typically about 1600 bytes.
 WifiG needs more to operate effectively. */
#ifndef ETH_MAXBUFS
	#if RAM_SIZE < 64		// Small board, less than 256K RAM, so economize
		#ifdef USE_WIFI
	   	// No wifi board known with small memory, but just in case...
			#define ETH_MAXBUFS       6
		#else
			#define ETH_MAXBUFS       4
		#endif
	#else
		#ifdef USE_WIFI
			#define ETH_MAXBUFS       32
		#else
			#define ETH_MAXBUFS       10
		#endif
	#endif
#endif


// Set up some defines for dealing with the automagic macros dealing with Ethernet that come from the system ID block.  These separate out the
// compile-time and run-time portions, and indicate if the given interface has multiple possible chipsets that must be resolved at run-time.
#define _DC_ETH_COMPILETIME_MASK		0x0000ffff
#define _DC_ETH_RUNTIME_MASK			0xf8000000
#define _DC_ETH_MULTI					0x00001000


#ifdef NET_ADD_ENTROPY
	// Use packet arrival times to help seed random number generators (see RAND.LIB)
	#ifndef RAND_H
		#use "rand.lib"
	#endif
#endif

/* If user defines VIRTUAL_ETH to a positive value, then he can create additional ethernet interfaces on the fly.  The additional interfaces 
use the IF_ETH hardware, but allow a different home address and netmask.  This is how "multi-homing" is now officially supported.  
VIRTUAL_ETH is only supported if at least one broadcast ethernet interface is selected (USE_ETHERNET > 0).  The virtual interface numbers
 get tacked on after the PPP's (if any).  A maximum of 16 total i/f's is supported. */
#ifndef VIRTUAL_ETH
	#define VIRTUAL_ETH		0
#endif

#ifndef USE_ETHERNET
	#define USE_ETHERNET 0
#endif

#ifndef USE_PPP_SERIAL
	#define USE_PPP_SERIAL 0
#endif

#ifndef USE_VSPD
	#define USE_VSPD 0
#endif

#ifndef USE_PPPOE
	#define USE_PPPOE 0
#endif

#ifndef USE_WIFI
   #define USE_WIFI 0
#endif

// If USE_PPPOE, then ensure USE_ETHERNET equal to it
#if USE_PPPOE
	#if (USE_PPPOE & USE_ETHERNET) != USE_PPPOE
   	#warns "If you define USE_PPPOE, then define USE_ETHERNET to be at least the same."
      #warns "...redefining USE_ETHERNET = USE_PPPOE, which may not be what you want."
      #undef USE_ETHERNET
      #define USE_ETHERNET USE_PPPOE
   #endif
#endif

#if USE_PPP_SERIAL & ~0x3FL
   #fatal "USE_PPP_SERIAL: invalid; use combination of 0x01,0x02,0x04,0x08,0x10,0x20 (SERA-F)"
#endif
// Maximum simultaneous PPP serial interfaces
#define MAX_PPP_SERIAL  6

#if USE_ETHERNET & ~0x3L
	#fatal "USE_ETHERNET: invalid ethernet device specified"
#endif

#if VIRTUAL_ETH && !USE_ETHERNET
	#fatal "If VIRTUAL_ETH non-zero, then must also define USE_ETHERNET non-zero"
#endif

#if USE_PPPOE & ~0x3L
	#fatal "USE_PPPOE: invalid PPPoE device specified"
#endif

#if USE_WIFI & ~0x3L
   #fatal "USE_WIFI: invalid WiFi device specified"
#endif

// This is rather ugly, but I can't think of a neater way to get the preprocessor to
// count the number of '1' bits in a constant.
#define USING_PPP_SERIAL	((USE_PPP_SERIAL & 1) + \
								 (USE_PPP_SERIAL>>1 & 1) + \
								 (USE_PPP_SERIAL>>2 & 1) + \
								 (USE_PPP_SERIAL>>3 & 1) + \
								 (USE_PPP_SERIAL>>4 & 1) + \
								 (USE_PPP_SERIAL>>5 & 1))

/* Virtual serial packet driver.  This allows an ordinary serial port to look
 like a TCP stream.  It uses the PPPLINK driver, but without PPP.  The PPPLINK
 instance operates in raw mode only.  Incoming packets have the INBAND flag set,
 which causes pkt_received() to pass them to the interface's ioctl(..PD_INBAND..)
 handler.  The vspd_ioctl() passes these packets to a special TCP handler,
 tcp_stream_handler(). To the application, this looks just like a real TCP
 socket.  Other protocols (including UDP) are not currently supported. */
#define USING_VSPD		((USE_VSPD & 1) + \
								 (USE_VSPD>>1 & 1) + \
								 (USE_VSPD>>2 & 1) + \
								 (USE_VSPD>>3 & 1) + \
								 (USE_VSPD>>4 & 1) + \
								 (USE_VSPD>>5 & 1))

#define USING_PPPLINK (USING_PPP_SERIAL + USING_VSPD)

#define VSPD_LOCALHOST	0x7F000001		// localhost IP address for VSPD
													// interfaces (127.0.0.1)

#if USE_VSPD & USE_PPP_SERIAL
	#error "You cannot use the same serial port for PPP and VSPD."
   #fatal "Check your definitions of USE_PPP_SERIAL and USE_VSPD to make sure no bits overlap."
#endif

#define USING_PPPOE ((USE_PPPOE & 1) + (USE_PPPOE>>1 & 1))

// These are defined by pktdrv.lib, based on actual hardware available
#define USING_ETHERNET ((USE_ETHERNET & 1) + (USE_ETHERNET>>1 & 1))
#define USING_WIFI ((USE_WIFI & 1) + (USE_WIFI>>1 & 1))
// Work out any board-specific things.  This also may redefin "USING_ETHERNET"
// based on actual number of ethernets installed.
//#use "BOARD_DEPS.LIB"


#define PPP_OVERHEAD		6		// HDLC address, control, check fields, plus PPP
										//		protocol.
#define ETH_OVERHEAD		24		// Ethernet header (14 bytes plus 4 byte CRC), plus 6 for DMAETH100
#define PPPOE_OVERHEAD	32		// Ethernet, plus PPPoE header (6) plus PPP
										//		protocol (2)
//#if CPU_ID_MASK(_CPU_ID_) == R5000
//	#define WIFI_OVERHEAD	84		// sizeof(WiFiMacBuffer) plus SNAP header plus 10 extra for SILKEN_DAC
//#else
	#define WIFI_OVERHEAD	74
//#endif

#define MAX_OVERHEAD		WIFI_OVERHEAD
#define NET_BUFSIZE		(MAX_MTU+MAX_OVERHEAD)


// MULTI_IF is a bitmask of interfaces required.
#if USE_ETHERNET || USE_PPP_SERIAL || USE_PPPOE || USE_VSPD || USE_WIFI
	#define MULTI_IF  (USE_ETHERNET | USE_WIFI << 2 | USE_PPPOE << 4 | USE_PPP_SERIAL << 6 | USE_VSPD << 6)
	#if !VIRTUAL_ETH && (MULTI_IF & -MULTI_IF) == MULTI_IF
		// Go back to old-style definition if only zero or one interface after all
		#undef MULTI_IF
	#endif
	#define IF_ETHERMASK	0x000F	// Ethernet or PPPoE
	#define IF_SERIALMASK	0x03F0	// Serial link
	#define IF_PPPOEMASK	0x000C	// PPPoE link
	#define IF_PPPMASK		(0x03FC & ~(USE_VSPD<<6))	// Any PPP link
#endif

#ifdef MULTI_IF
	#ifdef PKTDRV
		#undef PKTDRV
	#endif
#endif

// Determine if not using any broadcast ethernet.  If so, can
// cut out a lot of ARP code.
#ifdef MULTI_IF
	#if !(MULTI_IF & 0x0F)
		#define ARP_MINIMAL
	#endif
#else
	#ifdef USING_PPP
		#define ARP_MINIMAL
	#endif
#endif


// Define buffer size (not including ll_prefix overhead).
// Definitions select in order of decreasing overhead size.
#if USING_WIFI
	#define ETH_BUFSIZE (MAX_MTU + WIFI_OVERHEAD)
#else
	#if USING_PPPOE
		#define ETH_BUFSIZE (MAX_MTU + PPPOE_OVERHEAD)
	#else
		#ifndef ARP_MINIMAL		// if not defined, assume using ethernet
			#define ETH_BUFSIZE (MAX_MTU + ETH_OVERHEAD)
		#else
			#define ETH_BUFSIZE (MAX_MTU + PPP_OVERHEAD)
		#endif
	#endif
#endif
// The following check is not necessary, and impedes use of wifi
#if ETH_BUFSIZE > 1536
	#error "MTU plus overhead exceeds the maximum buffer size of 1536 bytes. Set ETH_MTU and PPP_MTU less than or equal 1500"
#endif

// Set IF_PPPX to be the first PPP interface defined (in order PPPOE0,1 then SERA, B, ... F)
#if USE_PPPOE & 0x01
	#define IF_PPPX	IF_PPPOE0
#elif USE_PPPOE & 0x02
	#define IF_PPPX	IF_PPPOE1
#elif USE_PPP_SERIAL & 0x01
	#define IF_PPPX	IF_PPP0
#elif USE_PPP_SERIAL & 0x02
	#define IF_PPPX	IF_PPP1
#elif USE_PPP_SERIAL & 0x04
	#define IF_PPPX	IF_PPP2
#elif USE_PPP_SERIAL & 0x08
	#define IF_PPPX	IF_PPP3
#elif USE_PPP_SERIAL & 0x10
	#define IF_PPPX	IF_PPP4
#elif USE_PPP_SERIAL & 0x20
	#define IF_PPPX	IF_PPP5
#endif


// Determine whether the ppp driver is needed
#if USE_PPPOE||USE_PPP_SERIAL
	#ifndef PPP_PKTDRV_LIB
   	#define PPP_PKTDRV_LIB	"ppp.lib"
   #endif
#endif

// Needed for all interfaces.  This library provides basic packet buffering services,
// plus it includes the necessary packet driver(s) based on board type.
//#use "pktdrv.lib"

#ifndef MULTI_IF
// No multiple interface support.  Old-style compatibility.
	#define IF_MAX		1
	#define IF_DEFAULT	0
	#define IF_ETH_MAX	1
	#if USING_ETHERNET || USING_PPPOE || USING_PPP_SERIAL || USING_VSPD || USING_WIFI
		#define IF_SET	0x0001		// Bitmask of valid interfaces
	#else
		#define IF_SET	0
		#error "#no interfaces defined. Define one or more of USE_ETHERNET, USE_WIFI, USE_PPP_SERIAL, USE_PPPOE or USE_VSPD."
	#endif
	#if USING_ETHERNET
		#if USING_PPPOE
			#define IF_PPPOE0			0
			#define IF_USES_ETH(i)		0
			#define IF_PKT_ETH(i)		1
			#define IF_PKT_REAL_WIFI(i)	0 //Real WiFi Interface
			#define IF_PKT_SER(i)		0
			#define IF_P2P(i)			1
		#else
			#define IF_ETH0				0
			#define IF_USES_ETH(i)		1
			#define IF_PKT_ETH(i)		1
         	#define IF_PKT_REAL_WIFI(i)	0
			#define IF_PKT_SER(i)		0
			#define IF_P2P(i)			0
		#endif
   #elif USING_WIFI
			#define IF_WIFI0			0
			#define IF_USES_ETH(i)		1
			#define IF_PKT_ETH(i)		1
        	#define IF_PKT_REAL_WIFI(i)	1
			#define IF_PKT_SER(i)		0
			#define IF_P2P(i)			0
	#else
   	// Note: since PPP over serial and VSPD are not allowed to use the same serial port, we just use the IF_PPPn interface name for either type.
		#if USE_PPP_SERIAL & 0x01 || USE_VSPD & 0x01
			#define IF_PPP0			0	// PPP over serial port A
		#elif USE_PPP_SERIAL & 0x02 || USE_VSPD & 0x02
			#define IF_PPP1			0	// PPP over serial port B etc.
		#elif USE_PPP_SERIAL & 0x04 || USE_VSPD & 0x04
			#define IF_PPP2			0
		#elif USE_PPP_SERIAL & 0x08 || USE_VSPD & 0x08
			#define IF_PPP3			0
		#elif USE_PPP_SERIAL & 0x10 || USE_VSPD & 0x10
			#define IF_PPP4			0
		#elif USE_PPP_SERIAL & 0x20 || USE_VSPD & 0x20
			#define IF_PPP5			0
		#endif
		#define IF_USES_ETH(i)	0
		#define IF_PKT_ETH(i)	0
		#define IF_PKT_REAL_WIFI(i)	0
		#define IF_PKT_SER(i)	1
		#if USE_PPP_SERIAL
			#define IF_P2P(i)			1
      	#else
      		#define IF_P2P(i)			0
		#endif
	#endif
	#if USING_ETHERNET > 1
		#undef USING_ETHERNET
		#define USING_ETHERNET 1
	#elif USING_WIFI > 1
		#undef USING_WIFI
		#define USING_WIFI 1
	#endif
#else
// Support multiple interfaces.
	#if (USING_ETHERNET || USING_WIFI)
		#define IF_ETH0		0		// Ethernet NIC 0
		#define IF_ETH1		1		// Ethernet NIC 1 (only if dual port board)
		#define IF_WIFI0	2
		#define IF_WIFI1	3
		#define IF_PPPOE0	4		// PPP over ethernet (using NIC 0)
		#define IF_PPPOE1	5		// PPP over ethernet (using NIC 1)
		#define IF_PPP0		6		// PPP over serial
		#define IF_PPP1		7
		#define IF_PPP2		8
		#define IF_PPP3		9
      	#define IF_PPP4   	10
      	#define IF_PPP5   	11
      	#define IF_MAX    	12    // Maximum number of interfaces
		#define IF_ETH_MAX  (USING_ETHERNET+USING_WIFI)		// Maximum (pseudo-)ethernet NICs (1..4)
      	#if VIRTUAL_ETH
      		// Note that IF_MAX denotes the end of the real interfaces.  The virtual ones follow.
			// Test if interface uses ethernet NIC (we don't count PPPoE, even though it uses ethernet)
			#define IF_USES_ETH(i) ((word)(i) < USING_WIFI || (word)i >= IF_MAX)
			#define IF_PKT_ETH(i) ((word)(i) < IF_PPP0 || (word)i >= IF_MAX)
			#define IF_PKT_SER(i) ((word)(i) >= IF_PPP0 && (word)i < IF_MAX)
			// Test if i/f is a point-to-point link
			#define IF_P2P(i) ((i) >= IF_PPPOE0 && (word)i < IF_MAX)
		#else
			// Test if interface uses ethernet NIC (we don't count PPPoE, even though it uses ethernet)
			#define IF_USES_ETH(i) ((word)(i) < USING_WIFI)
			#define IF_PKT_ETH(i) ((word)(i) < IF_PPP0)
			// Test if i/f is a point-to-point link
			#define IF_P2P(i) (1u<<(i) & (USE_PPP_SERIAL<<IF_PPP0|USE_PPPOE<<IF_PPPOE0))
			// Test if i/f uses an async serial physical layer
			#define IF_PKT_SER(i) (1u<<(i) & (USE_PPP_SERIAL<<IF_PPP0|USE_VSPD<<IF_PPP0))
		#endif
		#define IF_PKT_REAL_WIFI(i) ((word)(i) == IF_WIFI0 || (word)i == IF_WIFI1)
		#define IF_SET MULTI_IF	// Bitmask of valid interfaces
	#else
		#define IF_PPP0	0		// PPP over serial
		#define IF_PPP1	1
		#define IF_PPP2	2
		#define IF_PPP3	3
      	#define IF_PPP4 4
      	#define IF_PPP5 5
      	#define IF_MAX  6     	// Maximum number of interfaces
		#define IF_ETH_MAX 1	// Max ethernet i/f.  This is 1 (not 0) to avoid code complications, however the table entry is not used.
		#define IF_USES_ETH(i) 0
		#define IF_PKT_ETH(i) 0
      	#define IF_PKT_REAL_WIFI(i) 0
		#define IF_PKT_SER(i) 1

      	#define IF_P2P(i)	(1u<<(i) & USE_PPP_SERIAL)
	 	#define IF_SET		(MULTI_IF>>6)	// Bitmask of valid interfaces
	#endif
#endif
#define IF_ANY		0xFF	// Any interface
#ifdef IF_WIFI1
	#define IF_IS_WIFI(i)	((i==IF_WIFI0)||(i==IF_WIFI1))
#else
	#ifdef IF_WIFI0
		#define IF_IS_WIFI(i)	(i==IF_WIFI0)
	#else
		#define IF_IS_WIFI(i)	0
	#endif
#endif

// Default primary network interface and hardware type code
#define IF_DEFAULT_IS_P2P	0
#ifndef IF_DEFAULT
	#ifdef USING_PPP
		#undef IF_DEFAULT_IS_P2P
		#define IF_DEFAULT_IS_P2P	1
		#define IF_DEFAULT			IF_PPPX
	#elif USING_ETHERNET
		#if USE_ETHERNET == 0x02
			#define IF_DEFAULT		IF_ETH1
		#else
			#define IF_DEFAULT		IF_ETH0
		#endif
   #else
		#if USE_WIFI == 0x02
			#define IF_DEFAULT		IF_WIFI1
		#else
			#define IF_DEFAULT		IF_WIFI0
		#endif
	#endif
#endif



/*
 * Macros for working with IP addresses.  Some of these macros expand to function
 * calls in order to reduce code size.  The macro expansions depend on MULTI_IF.
 * If no multiple interface support, code size is reduced.  The macros which take
 * an 'iface' parameter check for the specific interface, otherwise they test for
 * a match on any interface.
 *
 * The IS_* macros return a boolean indication of whether the given IP address
 * has a given property.
 *
 * The MY_* macros return IP addresses relevant to this host.
 *
 * Note that we do not really distinguish between "network" and "subnet" i.e. we
 * do not encode knowledge of the class A,B,C,D,E network address ranges, except
 * that class D (multicast) must be recognised.  One consequence of this is that
 * we neither generate nor accept "all subnets broadcast" addresses.
 *
 * If multiple interfaces are supported then they MUST be on distinct,
 * non-overlapping, subnets.
 */

#ifdef MULTI_IF
	#define IS_ANY_MY_ADDR(ip)					is_any_my_addr(ip)
	#define IS_NONLOCAL_SUBNET(ip, iface)		is_nonlocal_subnet(ip, iface)
	#define IS_ALL_NONLOCAL_SUBNET(ip)			is_all_nonlocal_subnet(ip)
	#define IS_SUBNET_BCAST_ADDR(ip, iface) 	is_subnet_bcast_addr(ip, iface)
	#define IS_SUBNET_NET_ADDR(ip, iface)		is_subnet_net_addr(ip, iface)
	#define MY_ADDR(iface)						_if_tab[iface].ipaddr
	#define MY_SUBNET_MASK(iface)				_if_tab[iface].mask

#else
	#define IS_ANY_MY_ADDR(ip)					IS_MY_ADDR(ip,IF_DEFAULT)
	#define IS_NONLOCAL_SUBNET(ip, iface)		is_nonlocal_subnet(ip, IF_DEFAULT)
	#define IS_ALL_NONLOCAL_SUBNET(ip)			IS_NONLOCAL_SUBNET(ip, IF_DEFAULT)
	#define IS_SUBNET_BCAST_ADDR(ip, iface) 	is_subnet_bcast_addr(ip, IF_DEFAULT)
	#define IS_SUBNET_NET_ADDR(ip, iface)		is_subnet_net_addr(ip, IF_DEFAULT)
	#define MY_ADDR(iface)						_if_tab[IF_DEFAULT].ipaddr
	#define MY_SUBNET_MASK(iface)				_if_tab[IF_DEFAULT].mask
#endif

#define IS_MY_ADDR(ip, iface)		((ip) && (ip) == MY_ADDR(iface))
#define IS_LOCAL_SUBNET(ip, iface) 	(!IS_NONLOCAL_SUBNET(ip, iface))
#define IS_ANY_LOCAL_SUBNET(ip) 	(!IS_ANY_NONLOCAL_SUBNET(ip))
#define IS_ANY_BCAST_ADDR(ip)       is_subnet_bcast_addr(ip, IF_ANY)
#define IS_ANY_NET_ADDR(ip)         is_subnet_net_addr(ip, IF_ANY)
#define IS_MULTICAST_ADDR(ip)		(((ip) & 0xF0000000) == 0xE0000000)
#define IS_LOOPBACK_ADDR(ip)		(((ip) & 0xFF000000) == IPADDR(127,0,0,0))
#define IS_LINKLOCAL_ADDR(ip)		(((ip) & 0xFFFF0000) == IPADDR(169,254,0,0))

// Following also allow my own address(es) as valid.  The *_SOURCE macros check
// for proper source IP address in incoming datagrams.  The *_DEST macros check
// for valid destination addresses in outgoing datagrams.
#define IS_VALID_LOCAL_SOURCE(ip, iface)	is_valid_source(ip, iface, 1)
#define IS_ANY_VALID_LOCAL_SOURCE(ip)		is_valid_source(ip, IF_ANY, 1)
#define IS_VALID_SOURCE(ip, iface)			is_valid_source(ip, iface, 0)
#define IS_ANY_VALID_SOURCE(ip)				is_valid_source(ip, IF_ANY, 0)

#define MY_BCAST_ADDR(iface)				0xFFFFFFFF
#define MY_SUBNET_NET_ADDR(iface)			(MY_ADDR(iface) & MY_SUBNET_MASK(iface))
#define MY_SUBNET_BCAST_ADDR(iface)			(MY_ADDR(iface) | ~MY_SUBNET_MASK(iface))


// Number of entries in ARP cache table.  Must be between 1 and 199 inclusive. (The numbers 224-255 are reserved for special flags 
// such as broadcast, and 200-223 are reserved for future use).
// Should be set to the number of permanent entries, plus router entries, plus the number of simultaneously active TCP and UDP sockets.  
// For the majority of applications, the default should be more than enough.
#ifndef ARP_TABLE_SIZE
	#ifndef ARP_MINIMAL
		#define ARP_TABLE_SIZE				(5*(USING_ETHERNET+USING_WIFI)+IF_MAX)
	#else
		#define ARP_TABLE_SIZE				1
	#endif
#endif

// Number of entries in router table.  The default is set up for one router per interface, 
// plus an extra one for each broadcast (i.e. ethernet) interface, to handle possible redirections.
#ifndef ARP_ROUTER_TABLE_SIZE
	#define ARP_ROUTER_TABLE_SIZE		(IF_MAX+USING_ETHERNET+USING_WIFI)
#endif



/* Reserve ports ignores unlistened SYNs for specified ports */
#define USE_RESERVEDPORTS

#ifdef _DC10_LEGACY
	// These macros should not have been in use, will be removed in future release
	#define MAXINT 0x7fff   // Use stdc INT_MAX instead
	// Use functions (i_min, i_max, u_min, u_max,
	//				long_min, long_max, ulong_min, ulong_max)
	#define min(X,Y) (((X)<=(Y))?(X):(Y))
	#define max(X,Y) (((X)>=(Y))?(X):(Y))
	// Use xmemcpy()
	#define movmem(X,Y,Z) xmemcpy((Y),(X),(Z))
	#define FP_OFF(X) ((unsigned int)X)
	// These already defined
	#define TRUE            1
	#define true            TRUE
	#define FALSE           0
	#define false           FALSE
	/* these are visible for select routine return values */
	#define SOCKESTABLISHED 1
	#define SOCKDATAREADY   2
	#define SOCKCLOSED      4

	// These have been deprecated a long time
	#define my_ip_addr   _if_tab[IF_DEFAULT].ipaddr
	#define sin_mask     _if_tab[IF_DEFAULT].mask
	#define _mtu         _if_tab[IF_DEFAULT].mtu
	#define multihomes 0    // never did this (can use virtual ethernets)
#endif

//	Determine which libraries and functionality to include.
#ifdef  DISABLE_UDP
	#ifdef USE_DHCP
		#warning "Cannot set USE_DHCP if also DISABLE_UDP"
		#undef USE_DHCP
	#endif
	#ifndef DISABLE_DNS
		#warning "Disabling DNS because DISABLE_UDP"
		#define DISABLE_DNS
	#endif
#endif



// Network layer protocol field values in network order, as stored in the ethernet header
#define IP_TYPE				0x0008		// Really 0x0800
#define ARP_TYPE			0x0608		// Really 0x0806
#define IS_PPPOE_TYPE(t)	(((t)&0x00FF) == 0x88)		// High (network order) byte
																	// of type==0x88 -> is PPPoE.
#define PPPOE_TYPE			0x6488		// Really 0x8864 - PPPoE session data
#define PPPOE_DISC			0x6388		// Really 0x8863 - PPPoE link establishment

#ifndef MAX_STRING
	#define MAX_STRING      50			// Hostname strings are limited in length
#endif

#ifndef MAX_NAMESERVERS
	#define MAX_NAMESERVERS 2
#endif




// Separate spaces for TCP and UDP mode flags...

// TCP modes:
#define TCP_MODE_BINARY 0       /* default mode */
#define TCP_MODE_ASCII  1
#define TCP_MODE_NAGLE  0       /* Nagle algorithm */
#define TCP_MODE_NONAGLE 2
#define TCP_MODE_FULLCLOSE  0       /* Old style, do full close */
#define TCP_MODE_HALFCLOSE  4			/* Support half-close on this socket */
#define ALL_TCP_MODES (TCP_MODE_ASCII|TCP_MODE_NONAGLE|TCP_MODE_HALFCLOSE)

#define tcp_set_binary(s) ((s)->sock_mode &= ~TCP_MODE_ASCII)
#define tcp_set_ascii(s) ((s)->sock_mode |= TCP_MODE_ASCII)

#define tcp_set_nagle(s) ((s)->sock_mode &= ~TCP_MODE_NONAGLE)
#define tcp_set_nonagle(s) ((s)->sock_mode |= TCP_MODE_NONAGLE)

#define tcp_set_fullclose(s) ((s)->sock_mode &= ~TCP_MODE_HALFCLOSE)
#define tcp_set_halfclose(s) ((s)->sock_mode |= TCP_MODE_HALFCLOSE)

// UDP modes:
#define UDP_MODE_CHK    0       // default to having checksums
#define UDP_MODE_NOCHK  1
#define UDP_MODE_NOICMP 0       // default to not buffering ICMP error messages
#define UDP_MODE_ICMP   2
#define UDP_MODE_NODICMP 0      // default to not being the default ICMP message buffering socket
#define UDP_MODE_DICMP   4
#define UDP_MODE_CONTIG 0       // default to sending contiguous data to the UDP data handler
#define UDP_MODE_NOCONTIG   8
#define ALL_UDP_MODES (UDP_MODE_NOCHK|UDP_MODE_ICMP|UDP_MODE_DICMP|UDP_MODE_NOCONTIG)

#define udp_set_chk(s) ((s)->sock_mode &= ~UDP_MODE_NOCHK)
#define udp_set_nochk(s) ((s)->sock_mode |= UDP_MODE_NOCHK)

#define udp_set_noicmp(s) ((s)->sock_mode &= ~UDP_MODE_ICMP)
#define udp_set_icmp(s) ((s)->sock_mode |= UDP_MODE_ICMP)

#define udp_set_nodicmp(s) ((s)->sock_mode &= ~UDP_MODE_DICMP)
#define udp_set_dicmp(s) ((s)->sock_mode |= UDP_MODE_DICMP)

#define udp_set_contig(s) ((s)->sock_mode &= ~UDP_MODE_NOCONTIG)
#define udp_set_nocontig(s) ((s)->sock_mode |= UDP_MODE_NOCONTIG)

#define ALL_MODES (ALL_TCP_MODES|ALL_UDP_MODES)


// Parameter identifiers ("tags") for ifconfig().
// **** MAINTAINER NOTES *****
//      . Tag values must be >= 256 (0x100) and < 0xFF00.
//
//      *** Do not alter numbers after DC10.60 release, since persistent ***
//      *** and backward-compatible network settings depend on these     ***
//      *** tags having consistent meaning over releases.                ***
//
//      . Try to keep total numeric ranges "compact".
#define IFS_END							300		// End of parameter list
#define IFS_NOP							301		// do nothing, used for padding
#define IFS_IPADDR						302		// Set IP address [longword]
#define IFG_IPADDR						303		// Get IP address [longword *]
#define IFS_NETMASK						304		// Set netmask [longword]
#define IFG_NETMASK						305		// Get netmask [longword *]
#define IFS_MTU							306		// Set maximum transmission unit [word]
#define IFG_MTU							307		// Get MTU [word *]
#define IFS_UP							308		// Bring up interface [no parameter]
#define IFS_DOWN						310		// Bring down interface [no parameter]
#define IFS_ROUTER_SET					312		// Delete all rounters, then set this one [longword]
#define IFS_ROUTER_SET_STATIC			313		// Set restricted router [longword,longword,longword]
#define IFS_ROUTER_ADD					314		// Add rounter [longword]
#define IFS_ROUTER_ADD_STATIC			315		// Add restricted router [longword,longword,longword]
#define IFS_ROUTER_DEL					318		// Delete router [longword].  If 0 parm, delete all routers.
#define IFG_ROUTER_DEFAULT				321		// Get default router [longword *]
#define IFS_HWA							322		// Set hardware address [byte[6]]
#define IFG_HWA							323		// Get hardware address [byte[6]]
#define IFS_NAMESERVER_SET				326		// Delete all nameservers, then set this one [longword]
#define IFS_NAMESERVER_ADD				328		// Add nameserver [longword]
#define IFS_DHCP						332		// Use DHCP to configure this interface, or not [int]
#define IFG_DHCP						333		// Get whether DHCP to be used [int *]
#define IFS_ICMP_CONFIG					334		// Use "arp -s" ping to configure IP address, or not [int]
#define IFG_ICMP_CONFIG					335		// Get whether ping configure [int *]
#define IFS_DEBUG						336		// Set debug level [int]
#define IFG_DEBUG						337		// Get debug level [int *]
#define IFS_PPP_SPEED					340		// Set PPP speed in bits/sec [longword]
#define IFG_PPP_SPEED					341		// Get PPP speed in bits/sec [longword *]
#define IFG_DHCP_OK						343		// Get whether DHCP actually OK [int *]
#define IFS_ICMP_CONFIG_RESET			344		// After ping configured OK, allow new ping configure [no parameter]
#define IFG_ICMP_CONFIG_OK				345		// Get whether ping configured OK [int *]
#define IFS_DHCP_TIMEOUT				346		// Set DHCP timeout seconds [int]
#define IFG_DHCP_TIMEOUT				347		// Get DHCP timeout seconds [int *]
#define IFS_DHCP_FALLBACK				348		// Set DHCP fallback [int]
#define IFG_DHCP_FALLBACK				349		// Get DHCP fallback [int *]
#define IFS_PPP_ACCEPTIP				352		// Accept peer's idea of our local IP address
#define IFG_PPP_ACCEPTIP				353
#define IFS_PPP_REMOTEIP				354		// Try to set peer's IP address
#define IFG_PPP_REMOTEIP				355
#define IFS_PPP_SETREMOTEIP			IFS_PPP_REMOTEIP
#define IFS_PPP_ACCEPTDNS				356		// Accept a DNS server IP address from peer
#define IFG_PPP_ACCEPTDNS				357
#define IFS_PPP_REMOTEDNS				358		// Set DNS server IP address for peer
#define IFG_PPP_REMOTEDNS				359
#define IFS_PPP_SETREMOTEDNS			IFS_PPP_REMOTEDNS
#define IFS_PPP_AUTHCALLBACK			360		// Called when a peer attempts to authenticate
#define IFS_PPP_INIT					362		// Sets up PPP with default parameters
#define IFS_PPP_REMOTEAUTH				363		// Sets username and password to give to peer
#define IFG_PPP_REMOTEAUTH				364
#define IFS_PPP_LOCALAUTH				365		// Required username and password for incoming peer
#define IFG_PPP_LOCALAUTH				366
#define IFS_PPP_RTSPIN					367		// Define the RTS pin [int, char *, int]
#define IFG_PPP_RTSPIN					368
#define IFS_PPP_CTSPIN					369		// Define the CTS pin [int, int]
#define IFG_PPP_CTSPIN					370
#define IFS_PPP_FLOWCONTROL				371		// Turn hardware flow control on/off (1/0) [int]
#define IFG_PPP_FLOWCONTROL				372
#define IFS_PPP_SENDEXPECT				373		// Sequence of send/expect strings separated by '\r' [char *]
#define IFG_PPP_SENDEXPECT				374
#define IFS_PPP_USEMODEM				375		// Turn on/off modem handling step [int]
#define IFG_PPP_USEMODEM				376
#define IFS_PPP_HANGUP					377		// string to send to the modem when shutting down
#define IFG_PPP_HANGUP					378
#define IFS_PPP_MODEMESCAPE				379		// Send a standard escape sequence '+++' before SENDEXPECT or HANGUP
#define IFG_PPP_MODEMESCAPE				380
#define IFS_PPP_USEPORTD				382		// Use parallel port D pins for serial ports A,B (IF_PPP0,1) -
#define IFG_PPP_USEPORTD				383		//   otherwise uses the normal parallel port C pins.
#define IFG_PPP_PEERADDR				385		// Return the PPP peer IP address
#define IFS_IF_CALLBACK					390		// Set interface up/down callback [void (*)()]
#define IFG_DHCP_INFO					393		// Get DHCP goodies [DHCPInfo **]
#define IFG_DHCP_FELLBACK				395		// Get DHCP fallback status [int *]
#define IFS_DHCP_OPTIONS				396    // Set DHCP custom options  [int] [char *] [int (*)()]
#define IFG_DHCP_OPTIONS				397    // Get DHCP custom options  [int *] [char **]
#define IFS_DHCP_QUERY					398    // Set DHCP query  [int]
#define IFG_DHCP_QUERY					399    // Get DHCP query  [int *]
#define IFS_DHCP_DOMAIN					400   // Set DHCP 'get host & domain name' flag  [int]
#define IFG_DHCP_DOMAIN					401   // Get DHCP host/domain flag  [int *]
#define IFS_NAMESERVER_DEL				402	// Delete nameserver [longword]
#define IFS_DHCP_FB_IPADDR				404   // Set DHCP fallback IP address [longword]
#define IFG_DHCP_FB_IPADDR				405   // Get DHCP fallback IP address [longword *]
#define IFS_PPP_PASSIVE					406	// Set PPP passive mode [bool]
#define IFG_PPP_PASSIVE					407	// Get PPP passive mode [bool *]
#define IFS_USE_DMA						408	// Rabbit 4000: use DMA to serial port
#define IFS_USE_SERIAL					410	// Rabbit 4000: use serial port directly
#define IFS_PPP_USEPORTE				412	// Rabbit 4000: Use parallel port E pins for serial ports E,F
#define IFG_PPP_USEPORTE				413	// 	(IF_PPP0,1) - See also IFS_USEPORTD


#if USING_WIFI
	// these options can only be used if Wi-Fi is enabled, reserve 512-1023
#define IFX_WIFI_MIN					512	// ifconfig() exits if option is between _MIN
#define IFX_WIFI_MAX					700	// and _MAX and the given interface is not Wi-Fi

#define IFS_WIFI_SSID					512	// Set Wi-Fi SSID [int, byte *]
#define IFG_WIFI_SSID					513	// Get Wi-Fi SSID [int *, byte *]
#define IFS_WIFI_MULTI_DOMAIN			514	// Enable Multi-Domain [bool]
#define IFG_WIFI_MULTI_DOMAIN			515	// Status of Multi-Domain enable [bool *]
#define IFS_WIFI_REGION					516	// Set Wi-Fi region id [int]
#define IFG_WIFI_REGION					517	// Get Wi-Fi region id [int *]
#define IFG_WIFI_REGION_INFO			518	// Get Wi-Fi region info [wifi_region *]

// regions for IFS_WIFI_REGION and IFG_WIFI_REGION
// see wifi_wln_api.lib for definitions of each region
enum {
	IFPARAM_WIFI_REGION_AMERICAS,
	IFPARAM_WIFI_REGION_MEXICO_INDOORS,
	IFPARAM_WIFI_REGION_MEXICO_OUTDOORS,
	IFPARAM_WIFI_REGION_CANADA,
	IFPARAM_WIFI_REGION_EMEA,
	IFPARAM_WIFI_REGION_FRANCE,
	IFPARAM_WIFI_REGION_ISRAEL,
	IFPARAM_WIFI_REGION_CHINA,
	IFPARAM_WIFI_REGION_JAPAN,
	IFPARAM_WIFI_REGION_AUSTRALIA,

   IFPARAM_WIFI_REGION_END_OF_LIST
};

#define IFS_WIFI_MODE					519	// Set Infrastructure or Ad-Hoc [int]
#define IFG_WIFI_MODE					520	// Get Infrastructure or Ad-Hoc setting [int *]

// options for IFS_WIFI_MODE and IFG_WIFI_MODE
enum {
	IFPARAM_WIFI_ADHOC,
	IFPARAM_WIFI_INFRASTRUCTURE
};

#define IFS_WIFI_CHANNEL				521	// Set Wi-Fi channel [int]
#define IFG_WIFI_CHANNEL				522	// Get Wi-Fi channel setting [int *]
#define IFS_WIFI_TX_RATE				523	// Set max Wi-Fi transmit rate [int]
#define IFG_WIFI_TX_RATE				524	// Get max Wi-Fi transmit rate [int *]

// rates for IFS_WIFI_TX_RATE and IFG_WIFI_TX_RATE
enum {
	IFPARAM_WIFI_TX_RATE_ANY	= 0,
	IFPARAM_WIFI_TX_RATE_1		= 10,
	IFPARAM_WIFI_TX_RATE_2		= 20,
	IFPARAM_WIFI_TX_RATE_5_5	= 55,
	IFPARAM_WIFI_TX_RATE_6		= 60,
	IFPARAM_WIFI_TX_RATE_9		= 90,
	IFPARAM_WIFI_TX_RATE_11		= 110,
	IFPARAM_WIFI_TX_RATE_12		= 120,
	IFPARAM_WIFI_TX_RATE_18		= 180,
	IFPARAM_WIFI_TX_RATE_24		= 240,
	IFPARAM_WIFI_TX_RATE_36		= 360,
	IFPARAM_WIFI_TX_RATE_48		= 480,
	IFPARAM_WIFI_TX_RATE_54		= 540,
};

#define IFS_WIFI_TX_POWER			525	// Set max Wi-Fi transmit power [int]
#define IFG_WIFI_TX_POWER			526	// Get max Wi-Fi transmit power [int *]
#define IFS_WIFI_FRAG_THRESHOLD		527	// Set Wi-Fi fragment threshold [int]
#define IFG_WIFI_FRAG_THRESHOLD		528	// Get Wi-Fi fragment threshold [int *]
#define IFS_WIFI_RTS_THRESHOLD		529	// Set Wi-Fi RTS threshold [int]
#define IFG_WIFI_RTS_THRESHOLD		530	// Get Wi-Fi RTS threshold [int *]

#define IFS_WIFI_ENCRYPTION			540	// Set Wi-Fi encryption types [word]
#define IFG_WIFI_ENCRYPTION			541	// Get Wi-Fi encryption types [word *]

// encryption types for IFS_WIFI_ENCRYPTION and IFG_WIFI_ENCRYPTION.  user can select one or more by ORing multiple options
#define IFPARAM_WIFI_ENCR_ANY		((word) WLN_ENCR_ANY)
#define IFPARAM_WIFI_ENCR_NONE		((word) WLN_ENCR_OPEN)
#define IFPARAM_WIFI_ENCR_WEP		((word) WLN_ENCR_WEP)
#define IFPARAM_WIFI_ENCR_TKIP		((word) WLN_ENCR_TKIP)
#define IFPARAM_WIFI_ENCR_CCMP		((word) WLN_ENCR_CCMP)

#define IFS_WIFI_AUTHENTICATION		542	// Set Wi-Fi Authentication types [word]
#define IFG_WIFI_AUTHENTICATION		543	// Get Wi-Fi Authentication types [word *]

// authentication types for IFS_WIFI_AUTHENTICATION and IFG_WIFI_AUTHENTICATION
#define IFPARAM_WIFI_AUTH_ANY		((word) WLN_AUTH_ANY)	// Don't use with EAP
#define IFPARAM_WIFI_AUTH_OPEN		((word) WLN_AUTH_OPEN)
#define IFPARAM_WIFI_AUTH_SHAREDKEY	((word) WLN_AUTH_SHAREDKEY)
#define IFPARAM_WIFI_AUTH_WPA_PSK	((word) WLN_AUTH_WPA_PSK)
#define IFPARAM_WIFI_AUTH_WPA_8021X	((word) WLN_AUTH_WPA_8021X)
// methods below aren't supported by the Wi-Fi driver
#define IFPARAM_WIFI_AUTH_WEP_8021X	((word) WLN_AUTH_WEP_8021X)
#define IFPARAM_WIFI_AUTH_LEAP		((word) WLN_AUTH_LEAP)

#define IFS_WIFI_WEP_KEYNUM			550	// Set Wi-Fi WEP key number (0-3) [int]
#define IFG_WIFI_WEP_KEYNUM			551	// Get Wi-Fi WEP key number (0-3) [int *]
#define IFS_WIFI_WEP_KEY_BIN		552	// Set Wi-Fi WEP key (5 or 13 bytes) [int, int, byte *]
#define IFG_WIFI_WEP_KEY_BIN		553	// Get Wi-Fi WEP key [int, int *, byte *]

// sizes for IFS_WIFI_WEP_KEY_BIN and IFG_WIFI_WEP_KEY_BIN
enum{
	IFPARAM_WIFI_WEP_KEY40	= WLN_WEP40_SIZE,		// 5
   IFPARAM_WIFI_WEP_KEY104	= WLN_WEP104_SIZE		// 13
};

#define IFS_WIFI_WEP_KEY_HEXSTR		554	// Set Wi-Fi WEP key (10 or 26 char hex string) [int, char *]
#define IFG_WIFI_WEP_KEY_HEXSTR		555	// Get Wi-Fi WEP key as hex string [int, char *]

#ifdef WIFI_USE_WPA						// Options only valid if WPA is enabled
#define IFS_WIFI_WPA_PSK_PASSPHRASE	560	// Set Wi-Fi WPA PSK using passphrase [char *]
#define IFS_WIFI_WPA_PSK_HEXSTR		561	// Set Wi-Fi WPA PSK using 64-char hex string [char *]
#define IFG_WIFI_WPA_PSK_HEXSTR		562	// Get Wi-Fi WPA PSK as 64-char hex string [char *]
#define IFS_WIFI_WPA_PSK_BIN		563	// Set Wi-Fi WPA PSK using 32-byte array [byte *]
#define IFG_WIFI_WPA_PSK_BIN		564	// Get Wi-Fi WPA PSK as 32-byte array [byte *]
#endif	// #ifdef WIFI_USE_WPA

#define IFG_WIFI_STATUS				570	// Get Wi-Fi status [wifi_status *]
#define IFS_WIFI_SCAN				571	// Initiate Wi-Fi Scan with callback [void (*)()]

	// Wi-Fi options related to roaming
#define IFS_WIFI_BSSID					580	// Set address of AP (byte[6])
#define IFG_WIFI_BSSID					581	// Get address of AP (byte[6])
#define IFS_WIFI_ROAM_ENABLE			582	// Enable/disable roaming (bool)
#define IFG_WIFI_ROAM_ENABLE			583	// Get roaming enabled state (bool *)
#define IFS_WIFI_ROAM_BEACON_MISS		584	// Set number of lost beacons to trigger roaming event (int)
#define IFG_WIFI_ROAM_BEACON_MISS		585	// Get number of lost beacons to trigger roaming event(int *)

	// Wi-Fi options for WPA Enterprise/WPA2
#define IFS_WIFI_WPA_PROTOCOL				600	// Set acceptable WPA protocol(s) [word]
#define IFG_WIFI_WPA_PROTOCOL				601	// Get acceptable WPA protocol(s) [word *]
#define IFPARAM_WIFI_WPA_PROTOCOL_WPA	 ((word)WPA_PROTO_WPA)			// WPA/IEEE 802.11i/D3.0
#define IFPARAM_WIFI_WPA_PROTOCOL_WPA2  ((word)WPA_PROTO_RSN)			// WPA2/IEEE 802.11i
#define IFPARAM_WIFI_WPA_PROTOCOL_RSN   IFPARAM_WIFI_WPA_PROTOCOL_WPA2
#define IFPARAM_WIFI_WPA_PROTOCOL_ALL   ((word)0xFFFF)

#define IFS_WIFI_PAIRWISE_ENCRYPTION	604	// Set Wi-Fi pairwise encryption types [word]
#define IFG_WIFI_PAIRWISE_ENCRYPTION	605	// Get Wi-Fi pairwise encryption types [word *]
// For acceptable values, see description for IFS_WIFI_ENCRYPTION.  Only NONE, TKIP or CCMP are allowed:
// CCMP = AES in Counter mode with CBC-MAC [RFC 3610, IEEE 802.11i/D7.0]
// TKIP = Temporal Key Integrity Protocol [IEEE 802.11i/D7.0]
// NONE = Use only Group Keys (deprecated, should not be included if APs support pairwise keys)

#define IFS_WIFI_EAP_METHODS				606	// Set acceptable EAP methods. [longword]
#define IFG_WIFI_EAP_METHODS				607	// Get acceptable EAP methods [longword *]
// The parameter for above is a bitmask with one or more of the following ORed together.
// Note that methods which do not have compiled-in support via the WPA_USE_EAP
// macro will be ignored.  Currently, we only support EAP_TYPE_TLS and EAP_TYPE_PEAP.
// #define WPA_USE_EAP		(WPA_USE_EAP_TLS|WPA_USE_EAP_PEAP) would be required.
#define IFPARAM_EAP_PEAP					WLN_EAP_PEAP
#define IFPARAM_EAP_TLS						WLN_EAP_TLS
//#define IFPARAM_EAP_ANY					WLN_EAP_ANY				// Any method
//#define IFPARAM_EAP_INNER_ANY				WLN_EAP_INNER_ANY		// Any wrapped method


#define IFS_WIFI_IDENTITY				608	// Set identity string for EAP [char *]
#define IFG_WIFI_IDENTITY				609	// Get identity string for EAP [char **]
#define IFS_WIFI_ANONYMOUS_IDENTITY		610	// Set anonymous identity string for "outer" EAP [char *]
#define IFG_WIFI_ANONYMOUS_IDENTITY		611	// Get anonymous identity string for "outer" EAP [char **]
#define IFS_WIFI_PASSWORD				612	// Set password string for EAP [char *]
#define IFG_WIFI_PASSWORD				613	// Get password string for EAP [char **]
#define IFS_WIFI_CA_CERT				614	// Set CA certificate [SSL_Cert_t *].  If no CA cert provided, then the access server is not
											// verified, which introduces risk of 'access server spoofing'.
#define IFG_WIFI_CA_CERT				615	// Get CA certificate [SSL_Cert_t **]
#define IFS_WIFI_CA_CERT2				616	// Set "inner" CA certificate [SSL_Cert_t *]
#define IFG_WIFI_CA_CERT2				617	// Get "inner" CA certificate [SSL_Cert_t **]
#define IFS_WIFI_CA_CERT_PATH			618	// Set CA certificate as a Zserver resource path [char *]
#define IFS_WIFI_CA_CERT2_PATH			620	// Set "inner" CA certificate Zserver path [char *]
#define IFS_WIFI_CLIENT_CERT			622	// Set client certificate [SSL_Cert_t *]
#define IFG_WIFI_CLIENT_CERT			623	// Get client certificate [SSL_Cert_t **]
#define IFS_WIFI_CLIENT_CERT2			624	// Set "inner" client certificate [SSL_Cert_t *]
#define IFG_WIFI_CLIENT_CERT2			625	// Get "inner" client certificate [SSL_Cert_t **]
#define IFS_WIFI_CLIENT_CERT_PATH		626	// Set client certificate as Zserver file [char *,char *]
											// 1st parm is for cert, 2nd parm for private key. If 1st parm NULL, then delete resources.
#define IFS_WIFI_CLIENT_CERT2_PATH		628	// Set "inner" client certificate as Zserver file [char *,char *]
#define IFS_WIFI_EAP_PSK_PASSPHRASE		630	// Set Wi-Fi EAP PSK using passphrase [char *]
#define IFS_WIFI_EAP_PSK_HEXSTR			632	// Set Wi-Fi EAP PSK using 64-char hex string [char *]
#define IFG_WIFI_EAP_PSK_HEXSTR			633	// Get Wi-Fi EAP PSK as 64-char hex string [char *]
#define IFS_WIFI_EAP_PSK_BIN			634	// Set Wi-Fi EAP PSK using 32-byte array [byte *]
#define IFG_WIFI_EAP_PSK_BIN			635	// Get Wi-Fi EAP PSK as 32-byte array [byte *]
#define IFS_WIFI_SUBJECT_MATCH			638	// Set substring to be matched against the subject of the authentication server certificate [char *]
//The subject string is in following format (for example):
// 	/C=US/ST=CA/L=Davis/CN=Test1-AS/emailAddress=test1_as@digi.com
// so this parameter string could be set to "/L=Davis/CN=Test" to allow all access servers with a
// location of "Davis" and a common name starting with "Test".
#define IFS_WIFI_SUBJECT_MATCH2			640	// Set "inner" subject match substring [char *]
#define IFS_WIFI_ALTSUBJECT_MATCH		642	// Set semicolon separated string of entries to be matched against
											// the alternative subject name of the authentication server certificate [char *]
//	If this string is set, the server sertificate is only accepted if it
//	contains one of the entries in an alternative subject name extension.
//	altSubjectName string is in following format: TYPE:VALUE
//	Example: EMAIL:server@example.com
//	Example: DNS:server.example.com;DNS:server2.example.com
//	Following types are supported: EMAIL, DNS, URI
#define IFS_WIFI_ALTSUBJECT_MATCH2			644	// Set "inner" altsubject match [char *]
// The following are for convenience when "hard-coding" certificates (e.g. from #ximported files).
// Pass a zero longword as the parameter in order to delete any resources which were allocated
// on a previous call (since the library manages the SSL_Cert_t structures which are created).
#define IFS_WIFI_CA_CERT_XIM				650	// Set CA certificate as #ximport DER/PEM format [longword]
#define IFS_WIFI_CA_CERT2_XIM				652	// Set CA certificate 2 as #ximport DER/PEM format [longword]
#define IFS_WIFI_CLIENT_CERT_XIM			654	// Set client certificate and private key as two #ximport
															// DER/PEM format files [longword, longword]
															// 1st parm is for certificate itself, 2nd for private key.
#define IFS_WIFI_CLIENT_CERT2_XIM		656	// Set client certificate/key 2 [longword, longword]



#endif	// #if USING_WIFI

// These are used only for the default interface.
#ifndef USE_DHCP
	#ifndef MY_IP_ADDRESS
		#define MY_IP_ADDRESS	"169.254.0.0"
	#endif
	#ifndef MY_NETMASK
		#define MY_NETMASK		"255.255.0.0"
	#endif
#endif

// Set up default interface initializations.
// IFCONFIG_ALL : all items not specific to any particular interface
// IFCONFIG_DEFAULT : all items for the default interface (IF_DEFAULT).
// If not defined, these definitions are compatible with previous releases. The user can also define IFCONFIG_ETH0, IFCONFIG_PPP0 etc., 
// in which case those definitions will be used for the specified interface instead of the defaults.
#ifndef IFCONFIG_ALL
	#ifdef MY_GATEWAY
		#define _MY_GATEWAY IFS_ROUTER_SET,aton(MY_GATEWAY),
	#else
		#define _MY_GATEWAY
	#endif
	#ifdef MY_NAMESERVER
		#define _MY_NAMESERVER IFS_NAMESERVER_SET,aton(MY_NAMESERVER),
	#else
		#define _MY_NAMESERVER
	#endif
	#define IFCONFIG_ALL _MY_GATEWAY _MY_NAMESERVER IFS_END
#endif

#ifndef IFCONFIG_DEFAULT
	#ifdef USE_DHCP
		#define _USE_DHCP IFS_DHCP,1,
	#else
		#define _USE_DHCP
	#endif
	#if IF_DEFAULT_IS_P2P
		#ifndef PPP_SPEED
			#define PPP_SPEED 19200
		#endif
		#define _PPP_STUFF IFS_PPP_SPEED,(longword)PPP_SPEED,IFS_PPP_INIT,
	#else
		#define _PPP_STUFF
	#endif
	#define IFCONFIG_DEFAULT IFS_IPADDR,aton(MY_IP_ADDRESS), \
				IFS_NETMASK,aton(MY_NETMASK),_USE_DHCP _PPP_STUFF IFS_UP
#endif

#define sockaddr_in sockaddr

// Include published structures and typedefs
#include "net_def.h"

// Include published variable/state information
// The interface table.  Contains what used to be known as my_ip_addr and sin_mask, but one for each interface.
extern IFTEntry _if_tab[IF_MAX+VIRTUAL_ETH];
// Table of ethernet addresses.  These are pointers to ethernet addresses:
// may be NULL for ppp serial interfaces.  Maps interface number to eth addr.
extern eth_address * my_eth_addr[IF_MAX+VIRTUAL_ETH];
extern char _done_pkt_init;	// Set 1 when pkt_init() has been run.
extern word debug_on/* = 0*/;
extern int _survivebootp;
extern char _initialized;
extern char _hostname[MAX_STRING+1];
extern word sock_inactive/* = 0*/;  /* defaults to forever */
// Variables containing mask of bits (1 bit per i/f)
extern word _if_request;		// Requested state (1 bit = requested up)
extern word _if_prequest;		// Previously requested state
extern word _if_actual;			// Actual current state (1 bit = up)
extern word _if_dhcp;			// Currently performing DHCP acquisition
extern word _if_dhcp_lease; 	// DHCP acquired OK, and lease is NOT permanent (hence need to keep checking)
extern longword sock_data_timeout;  	// MilliSeconds until we give up (default 120,000)
extern word sock_delay;
// Backward compatibility macro
#define _eth_addr  (*my_eth_addr[IF_DEFAULT])

//Locks for use in a reentrant environment
#ifdef MCOS_LOCKS
	INT8U InitSocketLock(sock_type *s);
	typedef struct {
		OS_EVENT *lock;
		sock_type *s;
	} socket_lock_block;
	extern socket_lock_block sock_lock_array[ACTUAL_SOCKET_LOCKS];
// the actual lock funcitons 
	void IPSemPend(OS_EVENT *lock, char *lock_count);
	void IPSemPost(OS_EVENT *lock, char *lock_count);
// an individual socket lock, for use on sock rx/tx buffers, and the sock structure itself
	#ifndef NET_COARSELOCK
	#define LOCK_SOCK(s) /*printf("%d Lock sock: %x (%d)\n",(int)OSPrioCur, s, (int)((udp_Socket *)(s))->lock_count);*/ \
				IPSemPend( ((udp_Socket *)(s))->lock, &(((udp_Socket *)(s))->lock_count) )
	#define UNLOCK_SOCK(s) /*printf("%d UnLock sock: %x (%d)\n",(int)OSPrioCur, s, (int)((udp_Socket *)(s))->lock_count);*/ \
				IPSemPost( ((udp_Socket *)(s))->lock, &(((udp_Socket *)(s))->lock_count) )
	#endif
// global locks, for use on global vars/lists, and global tasks like DNS
	typedef struct {
		OS_EVENT *lock;		// the actual semaphore
		char lock_count;	// how many times we grabbed the semaphore
	} GlobalLock;
	#define LOCK_GLOBAL(l)		IPSemPend((l).lock, &((l).lock_count))
	#define UNLOCK_GLOBAL(l)	IPSemPost((l).lock, &((l).lock_count))

// Some conditional locking, for routines which do not need lock if not yet called sock_init().
	#define LOCK_GLOBAL_IF_INIT(l)	if (_initialized) IPSemPend((l).lock, &((l).lock_count))
	#define UNLOCK_GLOBAL_IF_INIT(l)	if (_initialized) IPSemPost((l).lock, &((l).lock_count))
	#ifdef NET_COARSELOCK
	#define LOCK_SOCK(s) LOCK_GLOBAL(TCPGlobalLock)
	#define UNLOCK_SOCK(s) UNLOCK_GLOBAL(TCPGlobalLock)
	#endif
	#ifdef NET_COMMON_DNS_LOCK
	extern GlobalLock TCPGlobalLock;
	#define LOCK_DNS() LOCK_GLOBAL(TCPGlobalLock)
	#define UNLOCK_DNS() UNLOCK_GLOBAL(TCPGlobalLock)
	#else
	extern GlobalLock TCPGlobalLock, DNSGlobalLock;
	#define LOCK_DNS() LOCK_GLOBAL(DNSGlobalLock)
	#define UNLOCK_DNS() UNLOCK_GLOBAL(DNSGlobalLock)
	#endif
// a quick lock, usualy implemented by turning off interrupts; this should NOT stay locked for long!
	#define LOCK_QUICK()	OS_ENTER_CRITICAL()
	#define UNLOCK_QUICK()	OS_EXIT_CRITICAL()
#else
// no multitasker - locks are not necessary
	#define LOCK_DNS()
	#define UNLOCK_DNS()
	#define LOCK_SOCK(s)
	#define UNLOCK_SOCK(s)
	#define LOCK_GLOBAL(l)
	#define UNLOCK_GLOBAL(l)
	#define LOCK_GLOBAL_IF_INIT(l)
	#define UNLOCK_GLOBAL_IF_INIT(l)
	#define LOCK_QUICK()
	#define UNLOCK_QUICK()
#endif
// End of locks section


#define sock_wait_established( s, seconds, fn, statusptr )  if (_ip_delay0( (sock_type*)s, seconds, fn, statusptr )) goto sock_err;
#define sock_wait_input( s, seconds, fn , statusptr )  if (_ip_delay1( (sock_type*)s, seconds, fn, statusptr )) goto sock_err;
#define sock_tick( s, statusptr ) \
	if ( !tcp_tick(s)) { \
	if (statusptr != NULL) *(int *)statusptr = 1 ; goto sock_err; } \
	else { if (statusptr != NULL) *(int *)statusptr = 0; }
#define sock_wait_closed(s, seconds, fn, statusptr ) if (_ip_delay2( (sock_type*)s, seconds, fn, statusptr )) goto sock_err;

int sock_init (void);

#ifndef ntohs
#define ntohs intel16
#define htons intel16
#define ntohl intel
#define htonl intel
#endif
int sock_rbsize(void *s );
int sock_rbused(void *s );
int sock_rbleft(void *s );
int sock_tbsize(void *s );
int sock_tbused(void *s );
int sock_tbleft(void *s );

word if_max_mtu(int iface);
int ifctl_tick(int iface);
int ifctl_ethernet(int iface, int up, int change);
int ifpending(int iface);
int linkpending(int iface);
int ifup(int iface);
int ifdown(int iface);
int ifconfig(int iface,...);
int vifconfig(int iface, char * p);
int is_valid_iface(int iface);
void _net_notify_link(word iface, int up);
int virtual_eth(word real_iface, longword ipaddr, longword netmask, void * resv);
void virtual_set(word real_iface, int up);
char *_inet_atoeth( char *src, byte *eth );
void tcp_config_defaults(void);
int sock_yield( void *s, void (*fn)( /*void*/ ) );
word sock_mode( void *s, word mode );
int sock_alive(void * s);
int sock_waiting(void * s);
int sock_writable(void * s);
int sock_readable(void * s);

void ip_timer_init( void *s , int delayseconds );
int ip_timer_expired( void *s );
word findfreeport( word oldport, word proto_tcp );
void sock_abort( void *s );
int _abort_socks(word reason, byte iface);
int sock_dataready( void *s );
int sock_bytesready(void *s);
void sock_close( void *s );
void sock_set_ttl(void* s, byte ttl);
void sock_set_tos(void* s, byte tos);
byte sock_iface(void* s);
int sock_resolved(void * s);

int _ip_delay0( sock_type *s, int timeoutseconds, sockfunct_t fn, int *statusptr);
int _ip_delay1( sock_type *s, int timeoutseconds, sockfunct_t fn, int *statusptr);
int _ip_delay2( sock_type *s, int timeoutseconds, sockfunct_t fn, int *statusptr);

int ifstatus (int iface);
void init_System(void);

#endif /* __NET_H__ */
