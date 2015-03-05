#ifndef __UDP_H__
#define __UDP_H__

#include "typeDef.h"

typedef struct {
	word srcPort;
	word dstPort;
	word length;
	word checksum;
} udp_Header;

#define UDP_LENGTH sizeof(udp_Header)

// Default time-to-live of UDP datagrams.  This value from Internet STD0002
#ifndef UDP_TTL
#define UDP_TTL 64
#endif
// Default type-of-service
#ifndef UDP_TOS
#define UDP_TOS IPTOS_DEFAULT
#endif

// UDP data handler event type codes
#define UDP_DH_INDATA		3				// New inbound datagram received
#define UDP_DH_ICMPMSG		10				// Incoming ICMP message


// Data structure for a UDP datagram in the socket buffer.  See documentation under udp_peek().
typedef struct {
	longword remip;		// Peer's IP address
	word remport;		// Peer's port
	short len;			// Length of following datagram
	word flags;			// Flags as follows:
	// Received datagrams:
#define UDI_ICMP_ERROR		0x0001	// This is an ICMP error entry: data following is a _udp_icmp_message.
#define UDI_TOS_MASK		0x001E	// Mask for received TOS bits
#define UDI_HWA_VALID		0x0020	// Hardware address field is valid
#define UDI_BROADCAST_LL	0x0040	// Received on broadcast link-layer address (0xFFFFFFFFFFFF)
#define UDI_BROADCAST_IP	0x0080	// Received on broadcast IP address (local or all subnets or 0xFFFFFFFF)
#define UDI_MULTICAST_LL	0x0100	// Received on multicast link-layer address
#define UDI_MULTICAST_IP	0x0200	// Received on multicast IP address
	// Transmit (outgoing) datagrams
#define UDI_OFFSET_MASK		0x1FFF	// Offset (in units of 8 bytes).  If non-zero, is not first fragment.
#define UDI_WAIT_ARP		0x4000	// Transmit buffered because not resolved
#define UDI_TX_BUFFERED		0x8000	// Transmit buffered for any reason (incl ARP)
	// Note that when buffered, the UDI stored in the tx buffer has its
	// len field set to the length of the original datagram, however the length
	// of data that follows the UDI in the tx buffer is actually len-offset
	// where offset = (flags & UDI_OFFSET_MASK)<<3.
	byte hwa[6];		// Peer's hardware (ethernet) address, if applicable
	byte iface;			// Interface on which received
} _udp_datagram_info;

typedef struct {
	word myport;			// Local port from which issued
	byte icmp_type;			// One of the ICMPTYPE_* values (see ICMP.LIB)
	byte icmp_code;			// The corresponding ICMP code
} _udp_icmp_message;

extern udp_Socket *udp_allsocs;
extern word next_udp_port;

void udp_sock_init(void);
byte * udp_alloc_buffer(void* sockaddr);
#define udp_open( s, lport, remip, port, datahandler ) (udp_extopen(s, IF_DEFAULT, lport, remip, port, datahandler, 0, 0))
int udp_extopen(udp_Socket *s, int iface, word lport, longword remip, word port, dataHandler_t datahandler, byte * buffer,int buflen );
int udp_waitopen( udp_Socket *s, int iface, word lport, longword remip, word port, dataHandler_t datahandler, byte * buffer, int buflen, longword millisecs );
int udp_close( udp_Socket *ds );
ll_prefix * udp_handler(ll_prefix * LL);
#define udp_send(s, buffer, len) udp_sendto(s, buffer, len, 0, 0)
int udp_sendto(udp_Socket* s, void * buffer, int len, longword remip, word remport);
int udp_waitsend(udp_Socket* s, void * buffer, int len, longword remip, word remport, word millisecs);
#define udp_recv(s, buffer, len)  udp_recvfrom((s), (buffer), (len), NULL, NULL)
int udp_recvfrom(udp_Socket* s, void * buffer, int len, longword* remip, word* remport);
int udp_peek(udp_Socket* s, _udp_datagram_info * udi);
void udp_bypass_arp(udp_Socket *s, eth_address * eth);
int udp_Retransmitter(void);
int udp_write(udp_Socket *s, void * datap, word len, word offset, _udp_datagram_info * udi);
void _udp_notify(icmp_ip_t * icmp, byte msg, ll_prefix * LL);
int _udp_check_multicast_sockets(byte iface, longword ipaddr);







#endif /* __UDP_H__ */
