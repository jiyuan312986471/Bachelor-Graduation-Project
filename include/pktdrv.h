#ifndef __PKT_DRV_H__
#define __PKT_DRV_H__

#include "typeDef.h"

void tickwait(unsigned int tick);
void mswait(unsigned int ms);
void pd_getaddress(int iface, void* buffer);
int pd_getaddresslen(int iface);
int pd_sethwaddr(int iface, byte* hwa);
int pd_powerdown(int iface);
int pd_powerup(int iface);
int pd_powerstatus(int iface);
int pd_havelink(int iface);
int pd_networkmode(int iface, int netspeed, int netduplex);
int pd_addmulticast(int iface, char* EthAddress, int* slot);
int pd_removemulticast(int iface, char* EthAddress);
void prt_nicreg(int iface);

ll_prefix * _pb_reserve(word n);	// Initial reservation of buffer for Tx or Rx.  Allocates n bytes (0 <= n <= 1536) xmem buffers.  
// Since buffers are fixed size, the parameter is currently ignored, and a full MTU buffer is allocated.
ll_prefix * _pb_resv_send(ll_Gather * g);	// As above, but reserve for sending.  Application buffers in g are copied to xmem buffers if needed.
void _pb_finish(ll_prefix * LL, byte iface, word offset);	// Finish up a buffer, ready for packet driver to process.  
//Write interface and length of link-layer header.
void _pb_free(ll_prefix * LL);		// Return buffers to pool.
void _pb_root2buf(ll_prefix * LL, void * data, word len);	// Root mem to xmem buffer
void _pb_xmem2buf(ll_prefix * LL, char * data, word len);	// Xmem mem to xmem buffer
void _pb_ioe2buf(ll_prefix * LL, void * ioaddr, word len);	// External I/O to xmem buffer
void _pb_buf2xmem(ll_prefix * LL, char * data, word len, word offset);	// Xmem buffer to xmem mem

unsigned long pd_calc_crc(char b, unsigned long current_crc);


#endif /* __PKT_DRV_H__ */
