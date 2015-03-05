#ifndef __IGMP_H__
#define __IGMP_H__

#include "typeDef.h"

// Types that are used in the call to _igmp_sendreport()
#define _IGMP_MEMBERSHIP_REPORT	0
#define _IGMP_LEAVE_MESSAGE		1

void _igmp_init(void);
void _igmp_tick(void);
ll_prefix * _igmp_handler(ll_prefix * LL);
int multicast_iptohw(char* hwaddr, longword ipaddr);
int multicast_joingroup(int iface, longword ipaddr);
int _multicast_joingroup_userflag(int iface, longword ipaddr, byte useradded);
int _multicast_jg_userflag_iface(int iface, longword ipaddr, byte useradded);
int multicast_leavegroup(int iface, longword ipaddr);
int _multicast_leavegroup_userflag(int iface, longword ipaddr, byte userdeleted);
int multicast_ingroup(int iface, longword ipaddr);
int _igmp_sendreport(int iface, longword ipaddr, byte type);


#endif /* __IGMP_H__ */
