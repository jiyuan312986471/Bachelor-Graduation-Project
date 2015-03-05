#ifndef __T_BUF_H__
#define __T_BUF_H__

#include "typeDef.h"

typedef struct {
	byte iface;		// Dest interface
	byte flags;
	// These flags indicate the sections which need to be copied to the packet
	// transmit buffer.  Copy can be avoided for TCP sockets, since the data is
	// not going to move or disappear.  The headers (in root) will generally need
	// to be copied since they are usually in auto variables.
#define	LLG_STAT_DATA1	0x01		// data1 static, no need to copy
#define	LLG_STAT_DATA2	0x02		// data2 static, no need to copy
#define	LLG_STAT_DATA3	0x04		// data3 static, no need to copy
#define  LLG_STAT_MASK	0x07		// Mask of all the above
	// Note: the only combinations above which are allowed are:
	//   data1   data2   data3
	//   ------- ------- -------
	//   copy    static  static    (used for TCP - data1 must be <= 512 bytes)
	//   copy    copy    static    (used for non-TCP, data3 not actually used.
	//											data1+data2 must be <= 1024 bytes if data3
	//											area is used.  If data3 not used,
	//											data1+data2 can total up to 1536 bytes)
	//   copy    copy    copy      (not currently used - total up to 1536 bytes)
	// Data sections which are not used must be set to 'static'.
	// The division into "header" and "payload" extents is somewhat arbitrary.
	// In many cases, the first extent will contain header and payload.
	word len1;			// Length of "header" section
	byte *data1;		// Header data (e.g. link, IP and transport headers)
	byte *data2;		// First data extent
	word len2;			// Length of first "payload" section
	word len3;			// Length of second "payload" section
	byte *data3;		// Second data extent
} ll_Gather;

/*
 * Circular buffer definition.
 * Manipulation routines are:
 *  _tbuf_xread()
 *  _tbuf_xwrite()
 *  _tbuf_delete()
 *  _tbuf_init()
 *  _tbuf_ref()
 *  _tbuf_findchar()
 */

typedef struct {
	byte *buf;		// Base addr. of buffer
	word len;		// Current total data length
	word maxlen;	// Size of buffer
	word begin;		// Offset of start of data (circular wrap-around)
	word fill;
} _tbuf;

#define _tbuf_remain(cb) ((cb)->maxlen - (cb)->len)


word _tbuf_xread(void * dest, _tbuf * cb, word offset, word len);
word _tbuf_extract(void * dest, _tbuf * cb, word len);
word _tbuf_xwrite(_tbuf * cb, word offset, void * src, word len);
word _tbuf_append(_tbuf * cb, void * src, word len);

#ifdef __NET_DEFS_LIB__
// Only useful if tcp/ip networking
struct ll_prefix_t;
word _tbuf_bxwrite(_tbuf * cb, word offset, struct ll_prefix_t * LL, word src, word len);
word _tbuf_bxwrite_noadj(_tbuf * cb, word offset, struct ll_prefix_t * LL, word src, word len);
word _tbuf_bappend(_tbuf * cb,  struct ll_prefix_t * LL, word src, word len);
#endif

word _tbuf_delete(_tbuf * cb, word len);
void _tbuf_reset(_tbuf * cb);
int _tbuf_findchar(_tbuf * cb, byte ch, word len, word ioffs);
int _tbuf_findmem(_tbuf * cb, byte * str, word * slenp, word len, word ioffs);
void _tbuf_ref(_tbuf * cb, ll_Gather * g, word offset, word len);
void _tbuf_writeref(_tbuf * cb, ll_Gather * g);
void _tbuf_move(_tbuf * cb_dst, _tbuf * cb_src, word len, int copy, word offset);
void _tbuf_remove(_tbuf * cb, word offset, word len);
void _tbuf_overlay(_tbuf * New, _tbuf * Old, word offset, word len);








#endif /* __T_BUF_H__ */
