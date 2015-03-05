#ifndef __NET_CONFIG_H__
#define __NET_CONFIG_H__

#define MY_IP_ADDRESS "192.168.1.88"
#define MY_NETMASK "255.255.255.0"
#define MY_GATEWAY "192.168.1.1"
#define MY_DNS "0.0.0.0"

#define USE_ETHERNET      0x01
//#define USE_PPP_SERIAL    0x04
//#define USE_PPPOE         0x01
//#define USE_WIFI          0x01
#define USE_DHCP
#define USE_SNMP 1
//#define USE_IGMP  2
#define VIRTUAL_ETH		2


#ifdef USE_IGMP
	#ifndef USE_MULTICAST
		#define USE_MULTICAST
	#endif
#endif

//#define PPPOE
//#define DISABLE_ARP
//#define DISABLE_DNS
//#define USE_SNMP  1
//#define DISABLE_UDP
//#define DISABLE_TCP

//#define IFCONFIG_ETH0	IFS_IPADDR,aton(MY_IP_ADDRESS),  IFS_NETMASK,aton(MY_NETMASK),  IFS_UP
// Dynamic configuration of single ethernet interface using DHCP. No fallbacks.
#define IFCONFIG_ETH0	IFS_DHCP, 1, IFS_UP
// DHCP Config with fallback to static address.
//#define IFCONFIG_ETH0	IFS_DHCP, 1, IFS_IPADDR,aton(_ETH_STATIC_IP),  IFS_NETMASK,aton(_ETH_NETMASK), \ 
//						IFS_DHCP_FALLBACK, 1, IFS_UP

#endif /* __NET_CONFIG_H__ */

