#ifndef __BOOTP_H__
#define __BOOTP_H__

#include "typeDef.h"

// Client DHCP state machine states, private to our implementation but mostly taken from RFC2131 suggestions.
// Odd numbered states are 'transient'.
#define DHCP_ST_IBOOT		0	// INIT_REBOOT (remember previous IP address over reboot.  Not implemented)
#define DHCP_ST_BOOT		2	// REBOOTING (as above, but sent initial request)
#define DHCP_ST_INFORM_SEND 3	// Transient state, sending DHCP INFORM
#define DHCP_ST_INFORM		4	// Waiting for INFORM response
#define DHCP_ST_BOOTP_INIT	6	// Initial state for BOOTP
#define DHCP_ST_BOOTP_SEND 	7	// Transient state for sending BOOTP request
#define DHCP_ST_BOOTP_WAIT 	8	// Waiting for BOOTP response
#define DHCP_ST_TOBINIT		10	// Timeout before INIT (after sent DECLINE)
#define DHCP_ST_INIT		12	// INIT (normal initial state for DHCP) - may go to INFORM_SEND or SEL_SEND.
#define DHCP_ST_SEL_SEND 	13	// Transient state, sending DISCOVER
#define DHCP_ST_SEL			16	// SELECTING
#define DHCP_ST_REQ_SEND 	17	// Transient state, sending REQ after OFFER
#define DHCP_ST_REQ			20	// REQUESTING
#define DHCP_ST_ARP_SEND 	23	// Start checking for address already in use via ARP
#define DHCP_ST_ARP     	24	// Wait for ARP timeout
#define DHCP_ST_BOUND		28	// BOUND -- this state and greater indicate DHCP OK
#define DHCP_ST_RENEW_SEND	29	// Transient state, sending REQ (unicast)
#define DHCP_ST_RENEW		32	// RENEWING
#define DHCP_ST_REBIND_SEND	33	// Transient state, sending REQ (broadcast)
#define DHCP_ST_REBIND		36	// REBINDING
#define DHCP_ST_RELEASE		40	// Send DHCPRELEASE.
#define DHCP_ST_TIMEOUT		101	// Transient state indicating overall timeout during acquisition
#define DHCP_ST_EXPIRED		103	// Transient state indicating lease expired and could not rebind, 
								// or server NAK'd renew or rebind.
#define DHCP_ST_WRETRY		105	// Waiting to retry acquiring IP after timeout


// UDP port numbers, server and client.
#define	IPPORT_BOOTPS		67
#define	IPPORT_BOOTPC		68

extern DHCPInfo _dhcp_info[NUM_DHCP_IF];

int dhcp_init(word iface);
int dhcp_tick(word iface);
int dhcp_acquire( void );
int dhcp_release( void );
int dhcp_get_timezone(long * seconds);
int dhcp_handler(_udp_datagram_info * udi, ll_prefix * LL, in_Header * ip, udp_Header * up, byte * data);
void dhcp_handle_arp(word iface, longword his_ip);


#endif /* __BOOTP_H__ */
