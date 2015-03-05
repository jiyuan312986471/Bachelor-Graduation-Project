// Packet driver functions for LPC1788 emac + LAN8700 Ethernet phy

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma diag_suppress 144

//#pragma diag_warning=144

#include "net_misc.h"
#include "PHY_LAN87XX.H"					  
#include "emacDrv.h"

#include "Console.h"
#include "sysBackup.h"

//#define LPCMAC_DEBUG_RX
//#define LPCMAC_DEBUG_TX
#define LPCMAC_DEBUG1
//#define SEARCH_PHY
//#define PKTDRV_VERBOSE

#define USE_RMII
#define ETH_MTU 1500		// MTU for Ethernet and WIFI (PPPoE will use this minus 8)
#define DEFINE_TCPBUFFER

#define PIN_NET_RESET (0x01<<13)	// P1.13

#define PHY_DEV_ADR		(0x1F<<8)	// PHY device address
#define PHY_DEV_ID		LAN8700_ID
 
#define Enable_Mac_irq 
#define Disable_Mac_irq
#define getPhyReg(r) read_PHY(r)
#define wrPhyReg(r, v) write_PHY(r, v)

#define NM_NC -1
#define NM_AN 0
#define NM_10M 1
#define NM_100M 2
#define NM_HDX 0
#define NM_FDX 1
 
_net_driver_table net_driver_table[]={
	LPC_MAC_TABLE
   { NULL, NULL, 0 }
};

// Local variables
// EMAC local DMA Descriptors.
static __align(8) RX_Stat Rx_Stat[EMAC_NUM_RX_FRAG]; // Must be 8-Byte alligned  
static            RX_Desc Rx_Desc[EMAC_NUM_RX_FRAG];
static            TX_Stat Tx_Stat[EMAC_NUM_TX_FRAG];
static            TX_Desc Tx_Desc[EMAC_NUM_TX_FRAG];

// EMAC local DMA buffers. 
static U32 eth_rx_buf[EMAC_NUM_RX_FRAG][EMAC_ETH_FRAG_SIZE>>2];
static U32 eth_tx_buf[EMAC_NUM_TX_FRAG][EMAC_ETH_FRAG_SIZE>>2];

#ifdef DEFINE_TCPBUFFER
__align(8) char tcp_buffer[8192];
#endif

int ifctl_ethernet(int iface, int up, int change);	// net.c
ll_prefix * _pktentry(int iface, ll_prefix * p, int pktlen);
//byte * _pktentry(int iface, byte * buf, int pktlen); 
void _pkt_finish(ll_prefix * p);

int eth_resetinterface(_LPC_Eth_Conf * nic, word instance, int iface);
int eth_receive(_LPC_Eth_Conf * nic);
int eth_sendpacket(_LPC_Eth_Conf * nic, ll_Gather * g);
int eth_ioctl(_LPC_Eth_Conf * nic, int cmd, ...);
#ifdef PKTDRV_VERBOSE
void eth_prt_nicreg(_LPC_Eth_Conf * nic);
#endif
int eth_ifctl(_LPC_Eth_Conf * nic, int up, int change);

int eth_powerup(_LPC_Eth_Conf * nic);
int eth_powerdown(_LPC_Eth_Conf * nic);
int eth_havelink(_LPC_Eth_Conf * nic);
int eth_sethwaddr(_LPC_Eth_Conf *  nic, char* hwa);
int eth_network_mode(_LPC_Eth_Conf * nic, int spd, int dup);
void emac_init(_LPC_Eth_Conf * nic, byte *EthAddress);

_LPC_Eth_Conf LPC_Eth_Conf[USING_LPC_ETH];
// Pointer to this is stored in IFTEntry.ncd field - basically, pointers to specific driver functions.
const NetControllerDevice LPC_Eth_Controller =
{
	sizeof(_LPC_Eth_Conf)		// sizeof_state
	,NCD_POLL				// flags (needs polling to ensure Rx buffer is ready)
	,6						// sizeof_hwa
	,USING_LPC_ETH			// instances
	,eth_receive			// receive()
	,eth_sendpacket			// sendpacket()
	,eth_ioctl 				// ioctl()
#ifdef PKTDRV_VERBOSE
	,eth_prt_nicreg			// prtregs()
#else
	,NULL
#endif
	,eth_ifctl					// ifctl()
};


static void write_PHY(U32 PhyReg, U16 Value) 
{
	// Write a data 'Value' to PHY register 'PhyReg'. 
	U32 tout;

	LPC_EMAC->MADR = PHY_DEV_ADR | PhyReg;
	LPC_EMAC->MWTD = Value;

	// Wait utill operation completed
	for (tout = 0; tout < EMAC_MII_WR_TOUT; tout++) {
		if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0) break;
	}
}

static U16 read_PHY(U32 PhyReg) 
{
	// Read a PHY register 'PhyReg'.
	U32 tout;

//	MAC_MADR = g_PhyAdress | PhyReg;
	LPC_EMAC->MADR = PHY_DEV_ADR | PhyReg;
	LPC_EMAC->MCMD = EMAC_MCMD_READ;

	// Wait until operation completed
	for (tout = 0; tout < EMAC_MII_RD_TOUT; tout++) {
		if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0) break;
	}
	LPC_EMAC->MCMD = 0;
	return (LPC_EMAC->MRDD);
}

#ifdef SEARCH_PHY
static void write_PHY_Ex(U8 adrr, U32 PhyReg, U16 Value) 
{
	// Write a data 'Value' to PHY register 'PhyReg'. 
	U32 tout;

	LPC_EMAC->MADR = (adrr<<8) | PhyReg;
	LPC_EMAC->MWTD = Value;

	// Wait utill operation completed
	for (tout = 0; tout < EMAC_MII_WR_TOUT; tout++) {
		if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0) break;
	}
}

static U16 read_PHY_Ex(U8 adrr, U32 PhyReg) 
{
	// Read a PHY register 'PhyReg'.
	U32 tout;

//	MAC_MADR = g_PhyAdress | PhyReg;
	LPC_EMAC->MADR = (adrr<<8) | PhyReg;
	LPC_EMAC->MCMD = EMAC_MCMD_READ;

	// Wait until operation completed
	for (tout = 0; tout < EMAC_MII_RD_TOUT; tout++) {
		if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0) break;
	}
	LPC_EMAC->MCMD = 0;
	return (LPC_EMAC->MRDD);
}
#endif

void eth_hardwarereset(_LPC_Eth_Conf * nic)
{
	LPC_IOCON->P1_14 = 0x08;	// Pull-down resistor enabled.
	LPC_GPIO1->DIR |= PIN_NET_RESET; 
	LPC_GPIO1->CLR |= PIN_NET_RESET; 
	mS_Delay(10);
	LPC_GPIO1->SET |= PIN_NET_RESET; 
}

int eth_resetinterface(_LPC_Eth_Conf * nic, word instance, int iface)
{
	if (instance >= USING_LPC_ETH) return -6;	// No such instance
//	xmemcpy(nic, LPC_Eth_Conf + instance, sizeof(*nic));
   	xmemcpy(nic->hwa, "\x00\x1c\xb4\x55\xaa\x55", 6);
	nic->iface = iface;

	eth_hardwarereset(nic);
//	eth_setupinterrupts(nic);
	emac_init(nic, nic->hwa);
	return 0;
}

int eth_ioctl(_LPC_Eth_Conf * nic, int cmd, ...)
{
	char * stack;

	stack = (char *)(&cmd + 1);
	switch (cmd) {
	case PD_HASFEATURE:
		cmd = *(int *)stack;
#ifdef USE_MULTICAST
		return cmd >= PD_HASFEATURE && cmd <= PD_REMOVEMULTICAST;
#else
		return cmd >= PD_HASFEATURE && cmd <= PD_GETHWA;
#endif
	case PD_INITIALIZE:
		return eth_resetinterface(nic, *(word *)stack, *(int *)(stack+sizeof(word)));
	case PD_HAVELINK:
		return eth_havelink(nic);
	case PD_POWER:
		if (*(int *)stack)
			return eth_powerup(nic);
		else
			return eth_powerdown(nic);
	case PD_POWERSTATUS:
		return (nic->netState & NET_STATE_IF_UP_DOWN)==NET_STATE_IF_UP_DOWN;
	case PD_SETHWA:
		eth_sethwaddr(nic, *(char **)stack);
		break;
	case PD_GETHWA:
		**(byte ***)stack = nic->hwa;
		return sizeof(nic->hwa);
#ifdef USE_MULTICAST
	case PD_ADDMULTICAST:
		return eth_addmulticast(nic, *(char **)stack, *(int **)(stack + sizeof(char *)));
	case PD_REMOVEMULTICAST:
		return eth_removemulticast(nic, *(char **)stack);
#endif
	case PD_NETWORK_MODE:
		return eth_network_mode(nic, *(int *)stack, *(int *) (stack+sizeof(word)));
	}
	return 0;
}

int eth_powerup(_LPC_Eth_Conf * nic)
{
//	write_PHY();
	nic->netState |= NET_STATE_IF_UP_DOWN;
	return 0;
}

int eth_powerdown(_LPC_Eth_Conf * nic)
{
//	write_PHY();
	nic->netState &= ~NET_STATE_IF_UP_DOWN;
	return 0;
}

int eth_havelink(_LPC_Eth_Conf * nic)
{
#ifndef USE_PHY_INT
	U16 regPHYCSR, regBMSR;

	regBMSR = read_PHY(PHY_REG_BMSR);
	if (regBMSR & 0x04) {	//Link is On
		if (!(nic->netState & NET_STATE_LINK_STATE)) {
			nic->netState &= ~(NET_STATE_LINK_STATE | NET_STATE_SPD_STATE | NET_STATE_DUP_STATE);
			regPHYCSR = read_PHY(LAN8700_PHY_REG_PHYCSR);
	#ifdef LPCMAC_DEBUG1
			printf("PHYCSR %04X\r\n", regPHYCSR);
	#endif
			regPHYCSR >>= 2;
			regPHYCSR &= 0x07;
			if (regPHYCSR==0x06) nic->netState |= (NET_STATE_LINK_STATE | NET_STATE_SPD_STATE | NET_STATE_DUP_STATE);
			else if (regPHYCSR==0x02) nic->netState |= (NET_STATE_LINK_STATE | NET_STATE_SPD_STATE); 
			else if (regPHYCSR==0x05) nic->netState |= (NET_STATE_LINK_STATE | NET_STATE_DUP_STATE); 
			else nic->netState |= NET_STATE_LINK_STATE;	// should be 0x01
			if (nic->netState & NET_STATE_DUP_STATE) {	// duplex mode bit
				LPC_EMAC->MAC2    |= EMAC_MAC2_FULL_DUP;	// Full duplex is enabled.
				LPC_EMAC->Command |= EMAC_CR_FULL_DUP;
				LPC_EMAC->IPGT     = EMAC_IPGT_FULL_DUP;
			} else {
				LPC_EMAC->MAC2    &= ~EMAC_MAC2_FULL_DUP;	// Full duplex is disabled.
				LPC_EMAC->Command &= ~EMAC_CR_FULL_DUP;
				LPC_EMAC->IPGT = EMAC_IPGT_HALF_DUP;		// Half duplex mode.
			}
			if (nic->netState & NET_STATE_SPD_STATE) {	//Spped bit
				LPC_EMAC->SUPP = EMAC_SUPP_SPEED;		// 100MBit mode.
			} else {
				LPC_EMAC->SUPP = 0;				// 10MBit mode.
			}
	#ifdef LPCMAC_DEBUG1
			printf("link change to ON [%s/%s]\r\n", 
				nic->netState & NET_STATE_SPD_STATE ? "100M":"10M",
				nic->netState & NET_STATE_DUP_STATE ? "FDX":"HDX");
	#endif
		}
	} else {
	#ifdef LPCMAC_DEBUG1
		if (nic->netState & NET_STATE_LINK_STATE) printf("link change to OFF\r\n");
	#endif
		nic->netState &= ~NET_STATE_LINK_STATE;
	}
#endif
	return (nic->netState & NET_STATE_LINK_STATE)==NET_STATE_LINK_STATE;
}

int eth_sethwaddr(_LPC_Eth_Conf *  nic, char* hwa)
{
	xmemcpy(nic->hwa, hwa, sizeof(nic->hwa));	// Keep shadow copy
	return 0;
}

// spd: 0=AN, 1= 10M, 2=100M, -1=No Change
// dup: 0=hdx, 1= fdx, -1=No Change
// ret: 0 on success
int eth_network_mode(_LPC_Eth_Conf * nic, int spd, int dup)
{
	if (spd == NM_AN) {
		write_PHY(PHY_REG_BMCR, PHY_AUTO_NEG);
	} else if (dup==NM_HDX) {	// HDX
		if (spd==NM_100M) {	//100M
			write_PHY(PHY_REG_BMCR, PHY_HALFD_100M);	// Connect at 100M/HDX 
			LPC_EMAC->SUPP = EMAC_SUPP_SPEED;			// 100MBit mode.
		} else if (spd==NM_10M) {   							//10M
			write_PHY(PHY_REG_BMCR, PHY_HALFD_10M);	// Connect at 100M/HDX 
			LPC_EMAC->SUPP = 0;
		}
		LPC_EMAC->MAC2    &= ~EMAC_MAC2_FULL_DUP;	// Full duplex is enabled.
		LPC_EMAC->Command &= ~EMAC_CR_FULL_DUP;
		LPC_EMAC->IPGT = EMAC_IPGT_HALF_DUP;		// Half duplex mode.
	} else if (dup==NM_FDX) {	// FDX
		if (spd==NM_100M) {	//100M
			write_PHY(PHY_REG_BMCR, PHY_FULLD_100M);	// Connect at 100M/FDX 
			LPC_EMAC->SUPP = EMAC_SUPP_SPEED;			// 100MBit mode.
		} else if (spd==NM_10M) {   							//10M
			write_PHY(PHY_REG_BMCR, PHY_FULLD_10M);	// Connect at 100M/FDX 
			LPC_EMAC->SUPP = 0;	 	
		}
		LPC_EMAC->MAC2    |= EMAC_MAC2_FULL_DUP;	// Full duplex is enabled.
		LPC_EMAC->Command |= EMAC_CR_FULL_DUP;
		LPC_EMAC->IPGT     = EMAC_IPGT_FULL_DUP;
	}
	return 0;
}

#ifdef PKTDRV_VERBOSE
void eth_prt_nicreg(_LPC_Eth_Conf * nic);
{
}
#endif

int eth_ifctl(_LPC_Eth_Conf * nic, int up, int change)
{
	// Just a stub for the default ethernet interface control.
	return ifctl_ethernet(nic->iface, up, change);
}


//////////////////////////////////////////////////////////////////////
void rx_descr_init (void)
{
	unsigned int i;

	for (i = 0; i < EMAC_NUM_RX_FRAG; i++) {
		Rx_Desc[i].Packet  = (U32)&eth_rx_buf[i];
		Rx_Desc[i].Ctrl    = EMAC_RCTRL_INT | (EMAC_ETH_FRAG_SIZE-1);
		Rx_Stat[i].Info    = 0;
		Rx_Stat[i].HashCRC = 0;
	}

	// Set EMAC Receive Descriptor Registers.
	LPC_EMAC->RxDescriptor    = (U32)&Rx_Desc[0];
	LPC_EMAC->RxStatus        = (U32)&Rx_Stat[0];
	LPC_EMAC->RxDescriptorNumber = EMAC_NUM_RX_FRAG-1;

	LPC_EMAC->RxConsumeIndex  = 0;		// Rx Descriptors Point to 0 
}

void tx_descr_init(void)
{
	unsigned int i;

	for (i = 0; i < EMAC_NUM_TX_FRAG; i++) {
		Tx_Desc[i].Packet = (U32)&eth_tx_buf[i];
		Tx_Desc[i].Ctrl   = 0;
		Tx_Stat[i].Info   = 0;
	}

	// Set EMAC Transmit Descriptor Registers.
	LPC_EMAC->TxDescriptor    = (U32)&Tx_Desc[0];
	LPC_EMAC->TxStatus        = (U32)&Tx_Stat[0];
	LPC_EMAC->TxDescriptorNumber = EMAC_NUM_TX_FRAG-1;

	LPC_EMAC->TxProduceIndex  = 0;	 // Tx Descriptors Point to 0
}

#ifdef LPCMAC_DEBUG_RX
void prt_cIdx(U32 eIdx)
{
	U32 idx;
	U32 info, rxLen;

	if (++eIdx == EMAC_NUM_RX_FRAG) eIdx = 0;
	idx = LPC_EMAC->RxConsumeIndex;
	while (idx != eIdx){
		info = Rx_Stat[idx].Info;
		rxLen = (info & EMAC_RINFO_SIZE) +1;
		printf("    C=%d, L=%d, Info=%04X\r\n", idx, rxLen, (info>>16));
		if (++idx == EMAC_NUM_RX_FRAG) idx = 0;
	}
}
#endif

//0  ; success
//1  ; failure/nobuf
//int pd_receive(int nic)
int eth_receive(_LPC_Eth_Conf * nic)
{
	U32 idx, idxp;
	U32 info, rxLen;
	char *sp, *dp;
	ll_prefix * p;

	if (!eth_havelink(nic)) return 1;

	if (LPC_EMAC->RxConsumeIndex == LPC_EMAC->RxProduceIndex)	return 1;	// receive buffer is empty
	rxLen = 0;
	idx = LPC_EMAC->RxConsumeIndex;
	while (idx != LPC_EMAC->RxProduceIndex) {
		info = Rx_Stat[idx].Info;
		if (info & EMAC_RINFO_ERR_MASK) goto pd_rel;
		rxLen += (info & EMAC_RINFO_SIZE) +1;
		if (info & EMAC_RINFO_LAST_FLAG) break;
		if (++idx == EMAC_NUM_RX_FRAG) idx = 0;
	}
	if (!(info & EMAC_RINFO_LAST_FLAG)) return 1;	// receive frame is not complete
	rxLen -= 3;
	if (info & EMAC_RINFO_ALIGN_ERR) rxLen++;
	if (rxLen > ETH_MTU+14) goto pd_rel;
	p = _pktentry(0, NULL, rxLen);
	if (p) dp = (char*)(p+1);
	else dp = NULL;

	if (dp) {
#ifdef LPCMAC_DEBUG_RX
		printf("RX: P=%d, Cb=%d, Ce=%d, L=%d\r\n", LPC_EMAC->RxProduceIndex, LPC_EMAC->RxConsumeIndex, idx, rxLen);
		prt_cIdx(idx);
#endif
//		printf("RX: L=%d RSV_Len=%d\r\n", rxLen, MAC_RSV & 0xFFFF);
//		_pktentry(nic->iface+1, p, rxLen);
		p->iface = nic->iface;
		p->len = rxLen;
		p->net_offs = 14;
				
		idxp = LPC_EMAC->RxConsumeIndex;
		info = Rx_Stat[idxp].Info;
		rxLen = (info & EMAC_RINFO_SIZE) +1;
		if (info & EMAC_RINFO_LAST_FLAG) rxLen -= 3;
		if (info & EMAC_RINFO_ALIGN_ERR) rxLen++;
		//		printf("RXr: L=%d RSV_Len=%d %04X\r\n", rxLen, MAC_RSV & 0xFFFF, MAC_RSV>>16);
		sp = (char *)Rx_Desc[idxp].Packet;
		xmemcpy(dp, sp, rxLen);
		dp += rxLen;
		while (idxp != idx) {
			if (++idxp == EMAC_NUM_RX_FRAG) idxp = 0;
			info = Rx_Stat[idxp].Info;
			rxLen = (info & EMAC_RINFO_SIZE) +1;
			if (info & EMAC_RINFO_LAST_FLAG) rxLen -= 3;
			if (info & EMAC_RINFO_ALIGN_ERR) rxLen++;
			sp = (char *)Rx_Desc[idxp].Packet;
			if ((int)rxLen >0) xmemcpy(dp, sp, rxLen);
			dp += rxLen;
		}
		_pkt_finish(p);
	} else {
#ifdef LPCMAC_DEBUG_RX
		printf("RXN: P=%d, Cb=%d, Ce=%d, L=%d\r\n", LPC_EMAC->RxProduceIndex, LPC_EMAC->RxConsumeIndex, idx, rxLen);
		prt_cIdx(idx);
#endif
		return 1;
	}
	if (++idx == EMAC_NUM_RX_FRAG) idx = 0;
	LPC_EMAC->RxConsumeIndex = idx;
	nic->num_rx++;
	return 0;
pd_rel:
#ifdef LPCMAC_DEBUG_RX
	printf("RXE: P=%d, Cb=%d, Ce=%d, L=%d\r\n", LPC_EMAC->RxProduceIndex, LPC_EMAC->RxConsumeIndex, idx, rxLen);
	prt_cIdx(idx);
#endif
	if (++idx == EMAC_NUM_RX_FRAG) idx = 0;
	LPC_EMAC->RxConsumeIndex = idx;
	return 1;
}

U32 freeTxBuffer()
{
	U32 freeSpace;

	freeSpace = (EMAC_NUM_TX_FRAG + LPC_EMAC->TxConsumeIndex - LPC_EMAC->TxProduceIndex -1) * EMAC_ETH_FRAG_SIZE;
	return freeSpace;
}

//int pd_sendpacket(int nic, char* packet, int length)
int eth_sendpacket(_LPC_Eth_Conf * nic, ll_Gather * g)
{
	U32 idx;
	char *dp;
	int freeSpace, nIdx, length;
#ifdef LPCMAC_DEBUG_TX
	int debug_len;
#endif

//	if (!isLinked) return 1;
	freeSpace = freeTxBuffer();
	if (!freeSpace) {
#ifdef LPCMAC_DEBUG_TX
		printf("TX: No Space P=%d, C=%d\r\n", LPC_EMAC->TxProduceIndex, LPC_EMAC->TxConsumeIndex);
#endif
		return 1;
	}
/*	idx = MAC_TXCONSUMEINDEX-1;
	if (idx>NUM_TX_FRAG) idx= 0;
	if (Tx_Stat[idx].Info & 0x80000000) {
		printf("C=%d P=%d Info=%08x\n", idx, MAC_TXPRODUCEINDEX, Tx_Stat[idx].Info); 
		printf("TSV0=%08x TSV1=%08x\n", MAC_TSV0, MAC_TSV1); 
	}*/
	Disable_Mac_irq;
	idx = LPC_EMAC->TxProduceIndex;
	length = g->len1 + g->len2 + g->len3;
	if (freeSpace < length) {
#ifdef LPCMAC_DEBUG_TX
		printf("TX: No enough Space P=%d, C=%d, Space=%d, SndLen=%d\r\n", 
			LPC_EMAC->TxProduceIndex, LPC_EMAC->TxConsumeIndex, freeSpace, length);
#endif
		Enable_Mac_irq;
		return 1;
	}
	nIdx = length / EMAC_ETH_FRAG_SIZE;
	freeSpace = length % EMAC_ETH_FRAG_SIZE;	// freeSpace used as remainder bytes
	if (freeSpace) nIdx++;
#ifdef LPCMAC_DEBUG_TX
	debug_len = length;
#endif
	while (nIdx) {
		dp = (char*)Tx_Desc[idx].Packet;
		if (nIdx==1) {
			if (g->len1) {
				xmemcpy(dp, g->data1, g->len1);
				dp += g->len1;
			} 
			if (g->len2) {
				xmemcpy(dp, g->data2, g->len2);
				dp += g->len2;
			} 
			if (g->len3) {
				xmemcpy(dp, g->data3, g->len3);
				dp += g->len3;
			} 
			Tx_Desc[idx].Ctrl = (freeSpace - 1)  | (EMAC_TCTRL_INT | EMAC_TCTRL_LAST | EMAC_TCTRL_CRC | EMAC_TCTRL_PAD);
		} else {
			if (g->len1) {
				if (g->len1>=EMAC_ETH_FRAG_SIZE) {
					g->len1 -= EMAC_ETH_FRAG_SIZE;
					xmemcpy(dp, g->data1, EMAC_ETH_FRAG_SIZE);
					g->data1 += EMAC_ETH_FRAG_SIZE;
				} else {
					length = EMAC_ETH_FRAG_SIZE-g->len1;
					xmemcpy(dp, g->data1, g->len1);
					dp += g->len1;
					g->len1 = 0;
					if (length) {
						if (g->len2) {
							if (g->len2>=length) {
								xmemcpy(dp, g->data2, length);
								g->len2 -= length;
								g->data2 += length;
							} else {
								xmemcpy(dp, g->data2, g->len2);
								dp += g->len2;
								length -= g->len2;
								g->len2 = 0;
								if (g->len3>length) {
									xmemcpy(dp, g->data3, length);
									g->data3 += length;
									dp += length;
									g->len3 -= length;
								} else {
#ifdef LPCMAC_DEBUG_TX
									printf("TX: Err 1\r\n");
#endif
									return 1;	//error
								}
							}
						} else {
							if (g->len3>length) {
								xmemcpy(dp, g->data3, length);
								g->data3 += length;
								dp += length;
								g->len3 -= length;
							} else {
#ifdef LPCMAC_DEBUG_TX
								printf("TX: Err 2\r\n");
#endif
								return 1;	//error
							}
						}
					}	// end if (length)
				}
			} else if (g->len2) {
				if (g->len2>=EMAC_ETH_FRAG_SIZE) {
					g->len2 -= EMAC_ETH_FRAG_SIZE;
					xmemcpy(dp, g->data2, EMAC_ETH_FRAG_SIZE);
					g->data2 += EMAC_ETH_FRAG_SIZE;
				} else {
					length = EMAC_ETH_FRAG_SIZE-g->len2;
					xmemcpy(dp, g->data2, g->len2);
					dp += g->len2;
					g->len2 = 0;
					if (length) {
						if (g->len3>length) {
							xmemcpy(dp, g->data3, length);
							g->data3 += length;
							dp += length;
							g->len3 -= length;
						} else {
#ifdef LPCMAC_DEBUG_TX
							printf("TX: Err 3\r\n");
#endif
							return 1;	//error
						}
					}
				}
			} else if (g->len3) {
				if (g->len3>=EMAC_ETH_FRAG_SIZE) {
					g->len3 -= EMAC_ETH_FRAG_SIZE;
					xmemcpy(dp, g->data3, EMAC_ETH_FRAG_SIZE);
					g->data3 += EMAC_ETH_FRAG_SIZE;
				} else {
#ifdef LPCMAC_DEBUG_TX
					printf("TX: Err 4\r\n");
#endif
					return 1;	//error
				}
			}
			Tx_Desc[idx].Ctrl = EMAC_ETH_FRAG_SIZE-1;
		}
		if (++idx==EMAC_NUM_TX_FRAG) idx = 0;
		nIdx--;
	}
// 		if (length<ETH_MIN)	{
// 			memset(dp, 0, ETH_MIN-length);
// 			length=ETH_MIN;
// 		}
#ifdef LPCMAC_DEBUG_TX
	printf("TX: Pb=%d, Pe=%d, C=%d, L=%d\r\n", LPC_EMAC->TxProduceIndex, idx, LPC_EMAC->TxConsumeIndex, debug_len);
#endif
//	uS_Delay(1);
	LPC_EMAC->TxProduceIndex = idx;
	Enable_Mac_irq;
	nic->num_tx++;
	return 0;
}

void emac_init(_LPC_Eth_Conf * nic, byte *EthAddress)
{
	U32 regv, tout, phyid1, phyid2;
	int spd,dup;
#ifdef SEARCH_PHY
	unsigned phy_in_use = 0;
	unsigned phy_linkstatus_reg;
	unsigned phy_linkstatus_mask; 
	unsigned char addr; 
	byte phy_addr;
#endif

	LPC_SC->PCONP |= (0x1<<30);	// Power Up the EMAC controller.

#ifdef  USE_RMII
	LPC_IOCON->P1_0  &= ~0x07;		/*  ENET I/O config */
	LPC_IOCON->P1_0  |= 0x01;		/* ENET_TXD0 */
	LPC_IOCON->P1_1  &= ~0x07;	
	LPC_IOCON->P1_1  |= 0x01;		/* ENET_TXD1 */
	LPC_IOCON->P1_4  &= ~0x07;
	LPC_IOCON->P1_4  |= 0x01;		/* ENET_TXEN */
	LPC_IOCON->P1_8  &= ~0x07;	
	LPC_IOCON->P1_8  |= 0x01;		/* ENET_CRS */
	LPC_IOCON->P1_9  &= ~0x07;	
	LPC_IOCON->P1_9  |= 0x01;		/* ENET_RXD0 */
	LPC_IOCON->P1_10 &= ~0x07;	
	LPC_IOCON->P1_10 |= 0x01;		/* ENET_RXD1 */
	LPC_IOCON->P1_14 &= ~0x07;	
	LPC_IOCON->P1_14 |= 0x01;		/* ENET_RX_ER */
	LPC_IOCON->P1_15 &= ~0x07;	
	LPC_IOCON->P1_15 |= 0x01;		/* ENET_REF_CLK */
#else
	LPC_IOCON->P1_0  &= ~0x07;		/*  ENET I/O config */
	LPC_IOCON->P1_0  |= 0x01;		/* ENET_TXD0 */
	LPC_IOCON->P1_1  &= ~0x07;	
	LPC_IOCON->P1_1  |= 0x01;		/* ENET_TXD1 */
	LPC_IOCON->P1_2  &= ~0x07;
	LPC_IOCON->P1_2  |= 0x01;		/* ENET_TXD2 */
	LPC_IOCON->P1_3  &= ~0x07;	
	LPC_IOCON->P1_3  |= 0x01;		/* ENET_TXD3 */
	LPC_IOCON->P1_4  &= ~0x07;
	LPC_IOCON->P1_4  |= 0x01;		/* ENET_TXEN */
	LPC_IOCON->P1_5  &= ~0x07;	
	LPC_IOCON->P1_5  |= 0x01;		/* ENET_TXER */
	LPC_IOCON->P1_6  &= ~0x07;	
	LPC_IOCON->P1_6  |= 0x01;		/* ENET_TX_CLK */
	LPC_IOCON->P1_7  &= ~0x07;	
	LPC_IOCON->P1_7  |= 0x01;		/* ENET_COL */
	LPC_IOCON->P1_8  &= ~0x07;	
	LPC_IOCON->P1_8  |= 0x01;		/* ENET_CRS */
	LPC_IOCON->P1_9  &= ~0x07;	
	LPC_IOCON->P1_9  |= 0x01;		/* ENET_RXD0 */
	LPC_IOCON->P1_10 &= ~0x07;	
	LPC_IOCON->P1_10 |= 0x01;		/* ENET_RXD1 */
	LPC_IOCON->P1_11 &= ~0x07;	
	LPC_IOCON->P1_11 |= 0x01;		/* ENET_RXD2 */
	LPC_IOCON->P1_12 &= ~0x07;	
	LPC_IOCON->P1_12 |= 0x01;		/* ENET_RXD3 */
	LPC_IOCON->P1_13 &= ~0x07;	
	LPC_IOCON->P1_13 |= 0x01;		/* ENET_RX_DV */
	LPC_IOCON->P1_14 &= ~0x07;	
	LPC_IOCON->P1_14 |= 0x01;		/* ENET_RX_ER */
	LPC_IOCON->P1_15 &= ~0x07;	
	LPC_IOCON->P1_15 |= 0x01;		/* ENET_RX_CLK/ENET_REF_CLK */
#endif

#if 1
	LPC_IOCON->P2_8 &= ~0x07;		/* ENET/PHY I/O config */
	LPC_IOCON->P2_8 |= 0x04;		/* ENET_MDC */
	LPC_IOCON->P1_17 &= ~0x07;	
	LPC_IOCON->P1_17 |= 0x01;		/* ENET_MDIO */
#endif
#if 0
	LPC_IOCON->P1_16 &= ~0x07;		/* ENET/PHY I/O config */
	LPC_IOCON->P1_16 |= 0x01;		/* ENET_MDC */
	LPC_IOCON->P1_17 &= ~0x07;	
	LPC_IOCON->P1_17 |= 0x01;		/* ENET_MDIO */
//  LPC_IOCON->LOC_ENET_MDIO = 0x01;
#endif
#if 0
	LPC_IOCON->P2_8 &= ~0x07;		/* ENET/PHY I/O config */
	LPC_IOCON->P2_8 |= 0x04;		/* ENET_MDC */
	LPC_IOCON->P2_9 &= ~0x07;	
	LPC_IOCON->P2_9 |= 0x04;		/* ENET_MDIO */
//  LPC_IOCON->LOC_ENET_MDIO = 0x00;
#endif

	// Set up MAC Configuration Register 1 (0xCF00)
	LPC_EMAC->MAC1 = EMAC_MAC1_RES_TX | EMAC_MAC1_RES_MCS_TX | EMAC_MAC1_RES_RX | 
					 EMAC_MAC1_RES_MCS_RX | EMAC_MAC1_SIM_RES | EMAC_MAC1_SOFT_RES;

	// Set up MAC Command Register (0x78) 
	LPC_EMAC->Command = EMAC_CR_REG_RES | EMAC_CR_TX_RES | EMAC_CR_RX_RES | EMAC_CR_PASS_RUNT_FRM;
  
	for (tout = 100; tout; tout--);		// Short delay
	// Set up MAC Configuration Register 1 to pass all receive frames
	LPC_EMAC->MAC1 = EMAC_MAC1_PASS_ALL;  /* 0x02 */
  /* 执行完上面的命令, MDC上出现30MHz(3.3V)的时钟信号 */
	// Set up MAC Configuration Register 2 to append CRC and pad out frames
	LPC_EMAC->MAC2 = EMAC_MAC2_CRC_EN | EMAC_MAC2_PAD_EN;
	// Set Ethernet Maximum Frame Register
	LPC_EMAC->MAXF = EMAC_ETH_MAX_FLEN;
	// Set Collision Window / Retry Register
	LPC_EMAC->CLRT = EMAC_CLRT_DEF;
  // Set Non Back-to-Back Inter-Packet-Gap Register
	LPC_EMAC->IPGR = EMAC_IPGR_P2_DEF;	// EMAC_IPGR_DEF;

/* Enable Reduced MII interface. */  /* MDC_CLK=120MHz/64=1.875Mhz < 2.5MHz */
	LPC_EMAC->MCFG = 0x3C | EMAC_MCFG_RES_MII;	 /* 0x3C对应的分频系数是64,见UM */
	for (tout = 100; regv; regv--);
	// release reset
	LPC_EMAC->MCFG &= ~(EMAC_MCFG_RES_MII);
//	LPC_EMAC->MCFG = 0x3C;
/* 执行完上面的命令, MDC上出现1.875MHz(3.3V)的时钟信号 */

	// Set MAC Command Register to enable Reduced MII interface and prevent runt frames being filtered out
	LPC_EMAC->Command = EMAC_CR_RMII | EMAC_CR_PASS_RUNT_FRM | EMAC_CR_PASS_RX_FILT;

#if 0
	// Put PHY into reset mode
	WriteToPHY (PHY_REG_BMCR, 0x8000);
	for (tout = 0; tout < 0x100000; tout++) {	// Loop until hardware reset completes
		regv = read_PHY(PHY_REG_BMCR);
		if (!(regv & 0x8000)) {
			// Reset has completed
			break;
		}
	}
#endif
#ifdef SEARCH_PHY
  /* EA_LPC1788_32上搜索到的PHY地址是0x01 */ /* 在Manley_lpc1788上的PHY地址是0x1F */
	for (addr=30; addr<32; addr++) {  
		write_PHY_Ex(addr, PHY_REG_BMCR, 0x8000);	// Put PHY into reset mode
		for (tout = 0; tout < 0x1000; tout++) {
			regv = read_PHY_Ex(addr, PHY_REG_BMCR);
			if (!(regv & 0x8000)) { 	// Reset has completed
				phy_addr = addr;
		 		 goto search_end;		
			}
		}
	}
search_end:
	if (addr == 32) 
		while(1);
	// Just check this actually PHY
	phyid1 = read_PHY(PHY_REG_IDR1);
	phyid2 = read_PHY(PHY_REG_IDR2);

	if (((phyid1 << 16) | (phyid2 & 0xFFF0)) == DP83848C_ID) {
		phy_in_use =  DP83848C_ID;
	} else if (((phyid1 << 16) | (phyid2 & 0xFFF0)) == LAN8720_ID) {
		phy_in_use = LAN8720_ID;
	} else if (((phyid1 << 16) | (phyid2 & 0xFFF0)) == LAN8700_ID) {
		phy_in_use = LAN8700_ID;
	}		

	if (phy_in_use != 0) {		// Safe to configure the PHY device
		// Set PHY to autonegotiation link speed
		write_PHY(PHY_REG_BMCR, PHY_AUTO_NEG);
		// loop until autonegotiation completes
		for (tout = 0; tout < 0x100000; tout++) {
			regv = read_PHY(PHY_REG_BMSR);
			if (regv & EMAC_PHY_BMSR_AUTO_DONE) {		// Autonegotiation has completed(0x0020)
				break;
			}
		}
	}

	phy_linkstatus_reg = PHY_REG_STS;		// Default to DP83848C
	phy_linkstatus_mask = 0x0001; 
  
	if ((phy_in_use == LAN8720_ID) || (phy_in_use == LAN8700_ID)) {
		phy_linkstatus_reg = PHY_REG_BMSR;
		phy_linkstatus_mask = 0x0004;
	}

	// Now check the link status
	for (tout = 0; tout < 0x10000; tout++) {
		regv = read_PHY(phy_linkstatus_reg);
		if (regv & phy_linkstatus_mask) {	// The link is on
			break;
		}
	}

	// Now configure for full/half duplex mode 
	if (regv & 0x0004) {	// We are in full duplex is enabled mode
		LPC_EMAC->MAC2    |= EMAC_MAC2_FULL_DUP;
		LPC_EMAC->Command |= EMAC_CR_FULL_DUP;
		LPC_EMAC->IPGT     = EMAC_IPGT_FULL_DUP;
	} else {
		// Otherwise we are in half duplex mode
		LPC_EMAC->IPGT = EMAC_IPGT_HALF_DUP;
	}

	// Now configure 100MBit or 10MBit mode
	if (regv & 0x0002) {	// 10MBit mode
		LPC_EMAC->SUPP = 0;
	} else {				// 100MBit mode
		LPC_EMAC->SUPP = EMAC_SUPP_SPEED;
	}
#endif

	phyid1 = read_PHY(PHY_REG_IDR1);
	phyid2 = read_PHY(PHY_REG_IDR2);

	if (((phyid1 << 16) | (phyid2 & 0xFFF0)) == PHY_DEV_ID) {
//		write_PHY(PHY_REG_DSCR, 0x0D14);
		write_PHY (PHY_REG_BMCR, PHY_BMCR_RESET);	// Put PHY into reset mode(0x8000) 		
		for (tout = 0; tout < 0x100000; tout++) {	// Wait for hardware reset to end. 
			regv = read_PHY(PHY_REG_BMCR);
			if (!(regv & PHY_BMCR_RESET)) break;	// Reset complete
		}

//		write_PHY(PHY_REG_MICR, 0x00);		// allow interrupt.
//phyid1 used as spd, phyid2 used as dup
		spd = dup = NM_NC;
		if (SysAppConf.auxSet1 & 0x01) { //auto negotiation
			spd = NM_AN;
		} else if (SysAppConf.auxSet1 & 0x04) { //FDX
			if (SysAppConf.auxSet1 & 0x02) {	//100M
				spd = NM_100M;
			} else {   							//10M
				spd = NM_10M;
			}
			dup = NM_FDX;
		} else {
			if (SysAppConf.auxSet1 & 0x02) {	//100M
				spd = NM_100M;
			} else {   							//10M
				spd = NM_10M;
			}
			dup = NM_HDX;
		}
		eth_network_mode(nic, spd, dup);	// Speed = auto-negotiation, Duplex = No Change
	}

	// Set the Ethernet MAC Address registers.
	LPC_EMAC->SA0 = ((U32)nic->hwa[5] << 8) | (U32)nic->hwa[4]; // Station address 0 Reg
	LPC_EMAC->SA1 = ((U32)nic->hwa[3] << 8) | (U32)nic->hwa[2]; // Station address 1 Reg
	LPC_EMAC->SA2 = ((U32)nic->hwa[1] << 8) | (U32)nic->hwa[0]; // Station address 2 Reg

	// Initialize Tx and Rx DMA Descriptors
	rx_descr_init();
	tx_descr_init();

	// Receive Broadcast, Multicast and Perfect Match Packets 
 	LPC_EMAC->RxFilterCtrl = EMAC_RFC_MCAST_EN | EMAC_RFC_BCAST_EN | EMAC_RFC_PERFECT_EN;	// EMAC_RFC_MCAST_EN				 
 
	// Enable interrupts MAC Module Control Interrupt Enable Register
	LPC_EMAC->IntEnable = EMAC_INT_RX_DONE | EMAC_INT_TX_DONE;

	// Reset all ethernet interrupts in MAC module
	LPC_EMAC->IntClear  = 0xFFFF;

	// Enable receive and transmit mode of MAC Ethernet core
	LPC_EMAC->Command  |= (EMAC_CR_RX_EN | EMAC_CR_TX_EN);
	LPC_EMAC->MAC1     |= EMAC_MAC1_REC_EN;

//	NVIC_EnableIRQ(ENET_IRQn);
//	mac_irq_init();
}

//Usage: lpcMac MAC|CTRL|RXFLT|MC|PHY|PHYEXT|WRMAC|WRPHY|TXSTAT
int con_lpcMac(ConsoleState* state)
{
	char * CmdPtr;
	unsigned int reg[5];
	if(state->commandparams < 1) {
		state->errno = CON_ERR_BADPARAMETER;
		return -1;
	}
	CmdPtr = con_getparam(state->command, 1);
	if (strcmpi(CmdPtr,"MAC") == 0) {
		reg[0] = LPC_EMAC->MAC1;
		reg[1] = LPC_EMAC->MAC2;
		sprintf(state->buffer,"\r\nMAC1=0x%08X, MAC2=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->IPGT;
		reg[1] = LPC_EMAC->IPGR;
		reg[2] = LPC_EMAC->CLRT;
		reg[3] = LPC_EMAC->MAXF;
		sprintf(state->buffer,"IPGT=0x%08X, IPGR=0x%08X, CLRT=0x%08X, MAXF=0x%08X\r\n", reg[0], reg[1], reg[2], reg[3]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->SUPP;
		reg[1] = LPC_EMAC->TEST;
		reg[2] = LPC_EMAC->MCFG;
		reg[3] = LPC_EMAC->MCMD;
		sprintf(state->buffer,"SUPP=0x%08X, TEST=0x%08X, MCFG=0x%08X, MCMD=0x%08X\r\n", reg[0], reg[1], reg[2], reg[3]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->MADR;
		//		reg[1] = MAC_MWTD;
		reg[2] = LPC_EMAC->MRDD;
		reg[3] = LPC_EMAC->MIND;
		sprintf(state->buffer,"MADR=0x%08X, MRDD=0x%08X, MIND=0x%08X\r\n", reg[0], reg[2], reg[3]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->SA0;
		reg[1] = LPC_EMAC->SA1;
		reg[2] = LPC_EMAC->SA2;
		sprintf(state->buffer,"SA0=0x%08X, SA1=0x%08X, SA2=0x%08X\r\n", reg[0], reg[1], reg[2]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"CTRL") == 0) {
		reg[0] = LPC_EMAC->Command;
		reg[1] = LPC_EMAC->Status;
		sprintf(state->buffer,"\r\nCOMMAND=0x%08X, STATUS=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->RxDescriptor;
		reg[1] = LPC_EMAC->RxStatus;
		reg[2] = LPC_EMAC->RxDescriptorNumber;
		reg[3] = LPC_EMAC->RxProduceIndex;
		reg[4] = LPC_EMAC->RxConsumeIndex;
		sprintf(state->buffer,"RX pDesc=%08X, st=%08X, n=%08X, pIdx=%08X, cIdx=%08X\r\n", reg[0], reg[1], reg[2], reg[3], reg[4]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->TxDescriptor;
		reg[1] = LPC_EMAC->TxStatus;
		reg[2] = LPC_EMAC->TxDescriptorNumber;
		reg[3] = LPC_EMAC->TxProduceIndex;
		reg[4] = LPC_EMAC->TxConsumeIndex;
		sprintf(state->buffer,"TX pDesc=%08X, st=%08X, n=%08X, pIdx=%08X, cIdx=%08X\r\n", reg[0], reg[1], reg[2], reg[3], reg[4]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->TSV0;
		reg[1] = LPC_EMAC->TSV1;
		reg[2] = LPC_EMAC->RSV;
		sprintf(state->buffer,"TSV0=0x%08X, TSV1=0x%08X, RSV=0x%08X\r\n", reg[0], reg[1], reg[2]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->FlowControlCounter;
		reg[1] = LPC_EMAC->FlowControlStatus;
		sprintf(state->buffer,"FC_Counter=0x%08X, FC_Status=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"RXFLT") == 0) {
		reg[0] = LPC_EMAC->RxFilterCtrl;
		reg[1] = LPC_EMAC->RxFilterWoLStatus;
		//		reg[2] = MAC_RXFILTERWOLCLR;
		sprintf(state->buffer,"\r\nRxFlt_Ctrl=0x%08X, RxFlt_Status=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->HashFilterL;
		reg[1] = LPC_EMAC->HashFilterH;
		sprintf(state->buffer,"Hash_FltL=0x%08X, Hash_FltH=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"MC") == 0) {
		reg[0] = LPC_EMAC->IntStatus;
		reg[1] = LPC_EMAC->IntEnable;
		//		reg[2] = MAC_INTCLEAR;
		//		reg[2] = MAC_INTSET;
		sprintf(state->buffer,"\r\n INT st=0x%08X, en=0x%08X\r\n", reg[0], reg[1]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = LPC_EMAC->PowerDown;
		sprintf(state->buffer,"PowerDown=0x%08X\r\n", reg[0]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"PHY") == 0) {
		reg[0] = getPhyReg(0);
		reg[1] = getPhyReg(1);
		reg[2] = getPhyReg(2);
		reg[3] = getPhyReg(3);
		sprintf(state->buffer,"\r\n PHY 0x%04X, 0x%04X, 0x%04X, 0x%04X, ", reg[0], reg[1], reg[2], reg[3]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = getPhyReg(4);
		reg[1] = getPhyReg(5);
		reg[2] = getPhyReg(6);
		sprintf(state->buffer,"0x%04X, 0x%04X, 0x%04X\r\n", reg[0], reg[1], reg[2]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"PHYEXT") == 0) {
		reg[0] = getPhyReg(16);
		reg[1] = getPhyReg(17);
		reg[2] = getPhyReg(18);
		reg[3] = getPhyReg(19);
		reg[4] = getPhyReg(20);
		sprintf(state->buffer,"\r\nPHYE16 0x%04X, 0x%04X, 0x%04X, 0x%04X, 0x%04X\r\n", reg[0], reg[1], reg[2], reg[3], reg[4]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
		reg[0] = getPhyReg(27);
		reg[1] = getPhyReg(28);
		reg[2] = getPhyReg(29);
		reg[3] = getPhyReg(30);
		reg[4] = getPhyReg(31);
		sprintf(state->buffer,"PHYE27 0x%04X, 0x%04X, 0x%04X, 0x%04X, 0x%04X\r\n", reg[0], reg[1], reg[2], reg[3], reg[4]);
		state->conio->puts(state->buffer);
		WAIT_OUTPUT_EMPTY;
	} else if (strcmpi(CmdPtr,"WRMAC") == 0) {
		CmdPtr = con_getparam(state->command, 2);
		reg[0] = strtol(CmdPtr, NULL, 16);
		CmdPtr = con_getparam(state->command, 3);
		reg[1] = strtol(CmdPtr, NULL, 16);
		reg[0] += 0xFFE00000;
		*((U32*)reg[0]) = reg[1];
	} else if (strcmpi(CmdPtr,"WRPHY") == 0) {
		CmdPtr = con_getparam(state->command, 2);
		reg[0] = strtol(CmdPtr, NULL, 16);
		CmdPtr = con_getparam(state->command, 3);
		reg[1] = strtol(CmdPtr, NULL, 16);
		wrPhyReg(reg[0], reg[1]);
	} else if (strcmpi(CmdPtr,"TXSTAT") == 0) {
		WAIT_OUTPUT_EMPTY;
		CmdPtr = state->buffer;
		for (reg[4] =0; reg[4]<13; reg[4]++) {
			sprintf(CmdPtr, "%04X  ", Tx_Stat[reg[4]].Info>>16);
			CmdPtr +=6;
		}
		sprintf(CmdPtr, "\r\n");
		CmdPtr +=2;
		for (reg[4] =0; reg[4]<13; reg[4]++) {
			sprintf(CmdPtr, "%01X-%03X ", Tx_Desc[reg[4]].Ctrl>>28, Tx_Desc[reg[4]].Ctrl&0x7FF);
			CmdPtr +=6;
		}
		sprintf(CmdPtr, "\r\n");
		state->conio->puts(state->buffer);
	} else if (strcmpi(CmdPtr,"RXTX") == 0) {
		WAIT_OUTPUT_EMPTY;
		CmdPtr = state->buffer;
		sprintf(CmdPtr, "Package Rx=%d Tx=%d\r\n", LPC_Eth_Conf[0].num_rx, LPC_Eth_Conf[0].num_tx);
		state->conio->puts(state->buffer);
	} else {
		state->errno = CON_ERR_BADPARAMETER;
		return -1;
	}
	return 1;
}


int con_setNif(ConsoleState* state)
{
	char * CmdPtr;
	int cmdParams;
	char tmpCh;
	int nm_spd, nm_dup;

	if(state->commandparams>2) {
		state->errno = CON_ERR_BADPARAMETER;
		return -1;
	} else if (state->commandparams==0) {
		if (SysAppConf.auxSet1 & 0x01) {
			state->conio->puts("NetIF Setting: AutoNegotiation.\r\n");
		} else {
			if (SysAppConf.auxSet1 & 0x04) {
				if (SysAppConf.auxSet1 & 0x02) {
					state->conio->puts("NetIF Setting: 100M/FDX.\r\n");
				} else {
					state->conio->puts("NetIF Setting: 10M/FDX.\r\n");
				}
			} else {
				if (SysAppConf.auxSet1 & 0x02) {
					state->conio->puts("NetIF Setting: 100M/HDX.\r\n");
				} else {
					state->conio->puts("NetIF Setting: 10M/HDX.\r\n");
				}
			}
		}
		cmdParams = getPhyReg(0x01);  //PHY_REG_BMSR
		cmdParams = getPhyReg(0x01);  //PHY_REG_BMSR
		if (cmdParams & 0x0004) {
			state->conio->puts("Current Link is: ON.\r\n");
			cmdParams = getPhyReg(0x00);  //PHY_REG_BMCR
			sprintf(state->buffer,"Current Status is: %s/%s\r\n", cmdParams&0x2000 ? "100M" : "10M", cmdParams&0x0100 ? "FDX" : "HDX");
			state->conio->puts(state->buffer);
		} else {
			state->conio->puts("Current Link is: OFF.\r\n");
		}
		if (SysAppConf.auxSet1 & 0x10) {
			state->conio->puts("\r\nNet Start use: Static Conf.\r\n");
		} else {
			if (SysAppConf.auxSet1 & 0x20)
				state->conio->puts("\r\nNet Start use: DHCP(if fail, use Static Conf.)\r\n");
			else
				state->conio->puts("\r\nNet Start use: DHCP.\r\n");
		}
	} else {
		tmpCh = SysAppConf.auxSet1;
		for (cmdParams =1;  cmdParams<=state->commandparams; cmdParams++) {
			CmdPtr = con_getparam(state->command, cmdParams+1);
			if (strcmpi(CmdPtr,"AN") == 0) {
				SysAppConf.auxSet1 |= 0x01;
				break;	
			} else if (strcmpi(CmdPtr,"100M") == 0) {
				SysAppConf.auxSet1 &= ~0x01;
				SysAppConf.auxSet1 |= 0x02;
			} else if (strcmpi(CmdPtr,"10M") == 0) {
				SysAppConf.auxSet1 &= ~0x03;
			} else if (strcmpi(CmdPtr,"FDX") == 0) {
				SysAppConf.auxSet1 &= ~0x01;
				SysAppConf.auxSet1 |= 0x04;
			} else if (strcmpi(CmdPtr,"HDX") == 0) {
				SysAppConf.auxSet1 &= ~0x05;
			} else if (strcmpi(CmdPtr,"STATIC") == 0) {
				SysAppConf.auxSet1 |= 0x30;
			} else if (strcmpi(CmdPtr,"DHCP1") == 0) {
				SysAppConf.auxSet1 &= ~0x10;
				SysAppConf.auxSet1 |= 0x20;
			} else if (strcmpi(CmdPtr,"DHCP2") == 0) {
				SysAppConf.auxSet1 &= ~0x30;
			} else {
				state->errno = CON_ERR_BADPARAMETER;
				return -1;
			}
		}
		con_backup(LOC_NETMAC_BACKUP);
		if ((SysAppConf.auxSet1 ^ tmpCh) & 0x07) {
			nm_spd = nm_dup = NM_NC;
			if (SysAppConf.auxSet1 & 0x01) { //auto negotiation
				nm_spd = NM_AN;
			} else if (SysAppConf.auxSet1 & 0x04) { //FDX
				if (SysAppConf.auxSet1 & 0x02) {	//100M
					nm_spd = NM_100M;
				} else {   							//10M
					nm_spd = NM_10M;
				}
				nm_dup = NM_FDX;
			} else {
				if (SysAppConf.auxSet1 & 0x02) {	//100M
					nm_spd = NM_100M;
				} else {   							//10M
					nm_spd = NM_10M;
				}
				nm_dup = NM_HDX;
			}
			eth_network_mode(&LPC_Eth_Conf[0], nm_spd, nm_dup);	// Speed = auto-negotiation, Duplex = No Change
		}
	}
	return 1;
}

void Set_NifDefault_10M_STATIC() 
{
	SysAppConf.auxSet1 &= ~0x07; // 10M HDX
	SysAppConf.auxSet1 |= 0x30; // Static
//	con_backup(LOC_NETMAC_BACKUP);
}
