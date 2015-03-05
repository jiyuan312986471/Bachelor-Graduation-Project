#ifndef __TCP_H__
#define __TCP_H__

#include <ctype.h>
#include "typeDef.h"

typedef struct {
	word srcPort;
	word dstPort;
	longword seqnum;
	longword acknum;
	word flags;
	word window;
	word checksum;
	word urgentPointer;
} tcp_Header;

/* combination of headers and options */
typedef struct {
	in_Header in;
	tcp_Header tcp;
	word maxsegopt[2];
} tcp_pkt;

#ifndef TCP_MAXPENDING
	#define TCP_MAXPENDING 20
#endif

extern tcp_Pending tcp_pendingpool[TCP_MAXPENDING];
extern tcp_Pending * tcp_pendingbuffer[TCP_MAXPENDING+1];
extern int tcp_pendingbuffer_head;
extern int tcp_pendingbuffer_tail;
extern tcp_Pending * tcp_allpending;
extern tcp_Pending * tcp_pendingtail;
extern int tcp_pendingcount;
extern int tcp_pendingestab;

extern word retran_strat;
extern word _arp_tick_strat;	// Also does IGMP and DHCP
#ifdef TCP_STATS
extern long pkt_processed;
#endif

extern word next_tcp_port;
extern tcp_Socket *tcp_allsocs;

// TCP socket states.
#define tcp_StateLISTEN   0x0001      /* listening for connection */
#define tcp_StateARP      0x0002      /* waiting for ARP resolution */
#define tcp_StateSYNSENT  0x0004      /* syn sent, active open */
#define tcp_StateSYNREC   0x0008      /* syn received, synack+syn sent. */
#define tcp_StateESTAB    0x0010      /* established */
#define tcp_StateFINWT1   0x0020      /* sent FIN */
#define tcp_StateFINWT2   0x0040      /* sent FIN, received ACK of FIN */
#define tcp_StateCLOSWT   0x0080      /* received FIN waiting for close */
#define tcp_StateCLOSING  0x0100      /* sent FIN, received FIN (waiting for FINACK) */
#define tcp_StateLASTACK  0x0200      /* fin received, finack+fin sent */
#define tcp_StateTIMEWT   0x0400      /* dally after sending final FINACK */
#define tcp_StateCLOSED   0x8000      /* finack received */


// TCP data handler event type codes.  Note that TCP data handler functions are only performed if TCP_DATAHANDLER is defined.
#define TCP_DH_LISTEN		0				// Started passive open (listen)
#define TCP_DH_OPEN			1				// Started active open (sent SYN)
#define TCP_DH_ESTAB			2				// Connection established
#define TCP_DH_INDATA		3				// New incoming data
#define TCP_DH_OUTBUF		4				// Outgoing data acknowledged by peer, new buffer space available for tx.
#define TCP_DH_INCLOSE		5				// Received FIN, no more incoming data
#define TCP_DH_OUTCLOSE		6				// Sent FIN, no more outgoing data
#define TCP_DH_CLOSED		7				// Socket fully closed
#define TCP_DH_ABORT			8				// Socket aborted by application
#define TCP_DH_RESET			9				// Socket reset by peer
#define TCP_DH_ICMPMSG		10				// Incoming ICMP message

#ifndef RETRAN_STRAT_TIME
// This is used for several purposes.  It is the minimum time granularity of
// the retransmit process.  No timeout is set less than this value (ms).
#define RETRAN_STRAT_TIME  10
#endif

#define TCP_LOCAL 0x4000
#define TCP_SAWCR 0x2000

// Timeouts (in milliseconds) for various phases of open and close processing:
#ifndef TCP_OPENTIMEOUT
#define TCP_OPENTIMEOUT 31000L   // timeout for active opens
#endif
#ifndef TCP_CONNTIMEOUT
#define TCP_CONNTIMEOUT 13000L   // timeout during open or close negotiation
#endif
#ifndef TCP_SYNQTIMEOUT
#define TCP_SYNQTIMEOUT 90000L   // timeout for pending connection
#endif

// LSB reserved for "custom delimiter char".
#define DELIM_NULL	0x0100	// Allow null character delimiter (like C strings)
#define DELIM_CR	0x0200	// Bare carriage return \r delimiter
#define DELIM_LF	0x0400	// Bare line feed \n delimiter
#define DELIM_CRLF	0x0800	// \r\n delimiter (standard network line terminator)

// BeginHeader sock_bufctl
typedef enum {
	// Note that setting a read buffer to less than 1 MSS is not permitted, since it can cause very poor performance.
	BCA_READSIZE,		// Set read buffer size (bytes), remainder for write
	BCA_WRITESIZE,		// Set write buffer size (bytes), remainder for read
	BCA_PROPORTION,		// Set read:write ratio as 1..255/256.  '1' gives 1 part read
	//  to 255 parts write; '128' gives equal read and write;
	//  '255' gives 255 parts read and 1 part write, etc.
	BCA_REASSIGN		// Reassign buffer to a new buffer address, maintaining
	//  current proportions.  Application is responsible for
	//  management of buffer memory!
} BufCtlAction;


void tcp_setstate(tcp_Socket * s, word newstate);
void tcp_sock_init(void);
byte * tcp_alloc_buffer(void* sockaddr);
int sock_preread( void *_s, byte *dp, int len );
int _tcp_open(tcp_Socket* s, int iface, word lport, longword ina, word port, dataHandler_t datahandler, byte * buffer, int buflen);
int sock_bufctl(void * s, BufCtlAction a, size_t amt, byte * addr);
#define tcp_open(s, lport, ina, port, datahandler)  (tcp_extopen(s, IF_DEFAULT, lport, ina, port, datahandler, 0, 0))
int tcp_find_vspd(word * ifacep, word * portp);
int tcp_extopen(tcp_Socket* s, int iface, word lport, longword ina, word port, dataHandler_t datahandler, byte * buffer, int buflen);
#define tcp_listen( s, lport, ina, port, datahandler, reserved ) (tcp_extlisten(s, IF_DEFAULT, lport, ina, port, datahandler, reserved, 0, 0))
int tcp_extlisten( tcp_Socket *s, int iface, word lport, longword ina, word port, dataHandler_t datahandler, word reserved, byte * buffer, int buflen );
int _tcp_pendcheck( tcp_Socket *s );
void tcp_close( tcp_Socket *s );
void tcp_abort( tcp_Socket *s );
void tcp_abortpending( tcp_Pending *p );
void tcp_removepending( tcp_Pending *p );
void tcp_Retransmitter( void );
void tcp_unthread( tcp_Socket *ds );
int tcp_tick(void* s);
int tcp_established( tcp_Socket *s );
void _tcp_notify(icmp_ip_t * icmp, byte msg, ll_prefix * LL);
int tcp_read( void *_s, void * datap, word maxlen );
int tcp_write( void *_s, const void * dp, int len );
void tcp_Flush( tcp_Socket *s );
int clamp16k(long x);
void tcp_reserveport(word port);
void tcp_initreserve(void);
void tcp_clearreserve(word port);
int tcp_stream_handler(ll_prefix * LL, word hisport);
int tcp_stream_ack(word diff, word hisport);
ll_prefix * tcp_handler(ll_prefix * LL);
word _tcp_process_options(tcp_Socket *s, tcp_Header *tp, word iface);
int tcp_ProcessData(tcp_Socket *s, tcp_Header *tp, int len, ll_prefix * LL, word *flagsp);
#ifdef TCP_VERBOSE
void _tcp_send( tcp_Socket *s, char * msg );
#else
void _tcp_send( tcp_Socket *s );
#endif
void tcp_rst(ll_prefix * LL, tcp_Header *oldtcpp );
void tcp_pendingpkt(tcp_Pending *p, word flags, int windowsize );
int tcp_send_keepalive(tcp_Socket * s);
void tcp_reset_keepalive(tcp_Socket *s);
int tcp_keepalive(tcp_Socket *s, long timeout);

int sock_read( void *_s, void *dp, int len );
int sock_fastread( void *s, void *dp, int len );
int sock_aread( void *_s, void *dp, int len );
int sock_chr(void *_s, word pos, int range, int chr);
int sock_cmp(void *_s, word pos, int range, void * mem, int * len);
int sock_write( void *_s, const void *dp, int len );
int sock_fastwrite( void *s, const void *dp, int len );
int sock_awrite( void *_s, const void *dp, int len );
void sock_noflush( void *s );
void sock_flush( void *s );
void sock_flushnext( void* s);
byte sock_putc( void *s, byte c );
int sock_getc( void *s );
int sock_puts( void *_s, const byte *dp );
void sock_update( tcp_Socket *s );
int sock_stringready(void *s, word * delim, word maxlen);
int sock_gets( void *_s, char *dp, int n );
int sock_established( void *s );
void sock_sturdy( tcp_Socket *s, int level );
tcp_Pending *tcp_pendingpoolget(void);
void tcp_pendingpoolreturn(tcp_Pending *p);
const char *sockstate( void *s );









#endif /* __TCP_H__ */
