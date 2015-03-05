/* snmpMib.h --Snmp Protocol MIB function Header file. */

#ifndef __SNMP_MIB__
#define __SNMP_MIB__

//typedef unsigned short word;
//typedef unsigned char byte;
//Configuration definitions
#ifndef USE_MIB
	#define USE_MIB
#endif

//Size of the xmem database tree structure.  Determines the maximum number of objects which may be managed.  
//The default allows for about 100 objects.
// #ifndef SNMP_MIB_SIZE
// 	#define SNMP_MIB_SIZE		0x4e20 // 0x8cA0	//0x9c40 //=2000mib_tree 
// #endif

//Maximum size of an encoded object identifier.
#ifndef SNMP_MAX_NAME
	#define SNMP_MAX_NAME		46
#endif

#ifndef SNMP_DFLT_READMASK
	#define SNMP_DFLT_READMASK	0x03
#endif

#ifndef SNMP_DFLT_WRITEMASK
	#define SNMP_DFLT_WRITEMASK	0x02
#endif

#ifndef SNMP_sysObjectID
//	#define SNMP_sysObjectID	_BOARD_TYPE_
#endif

#ifndef SNMP_MAX_PSTACK
	#define SNMP_MAX_PSTACK		3
#endif

typedef unsigned long oidlevel;

#ifndef offsetof
	#define offsetof(s, f) ((unsigned int)((char*)(&((s*)0)->f) - ((char*)0)))
#endif



/*
 * Macros for constructing MIB tree initialization lists (MIBTIL).NB: These macros DO NOT YET WORK; waiting 
 * for enhancement to Dynamic C to support arithmetic operations on address constants. For now, equivalent 
 * functionality is available via function calls.
 */

#define SNMP_I_NOP	0		// No-op
#define SNMP_I_APP1	1		// Append level (0.255)  +1 byte
#define SNMP_I_APP2	2		// Append level (256..65535) +2 bytes
#define SNMP_I_APP4	3		// Append level (>=65536) +4 bytes
#define SNMP_I_UP	4		// Up one level
#define SNMP_I_PUSH	5		// Push current state
#define SNMP_I_POP	6		// Restore most recent pushed state LIFO
#define SNMP_I_RD	7		// Set read access mask  +1 byte
#define SNMP_I_WR	8		// Set write access mask  +1 byte
#define SNMP_I_CB	9		// Set callback function address  +2 bytes
#define SNMP_I_NCB	10		// Cancel callback
#define SNMP_I_ADD	11		// Add root entry  +1 type, +2 addr, [+2 maxlen]
#define SNMP_I_XADD	12		// Add xmem entry  +1 type, +2 offset, [+2 maxlen]
#define SNMP_I_STIX	13		// Store result MIB tree index  +2 addr of word
#define SNMP_I_SAV	14		// Set saveable flag
#define SNMP_I_NSAV	15		// Clear saveable flag
#define SNMP_I_ADDI	16		// As for ADD, and autoincrement last level
#define SNMP_I_XADDI	17		// As for XADD, and autoincrement last level
#define SNMP_I_MAGIC	213		// Identifies start of MIBTIL
#define SNMP_I_END	255		// Identifies end of MIBTIL

#define SNMP_BEGIN(label) const char label[] = { SNMP_I_MAGIC
#define SNMP_END  , SNMP_I_END };

#define SNMP_APPEND(level) , SNMP_I_APP1, (char)(level)
#define SNMP_APPENDW(level) , SNMP_I_APP2, (char)(level), (char)((level)>>8)
#define SNMP_APPENDL(level) , SNMP_I_APP4, (char)(level), (char)((level)>>8), (char)((level)>>16), (char)((level)>>24)
#define SNMP_UP			, SNMP_I_UP
#define SNMP_PUSH		, SNMP_I_PUSH
#define SNMP_POP		, SNMP_I_POP
#define SNMP_RD(rd)		, SNMP_I_RD, (char)(rd)
#define SNMP_WR(wr)		, SNMP_I_WR, (char)(wr)
#define SNMP_CB(func)		, SNMP_I_CB, (char)(func), (char)((word)(func) >> 8)
#define SNMP_NCB		, SNMP_I_NCB
#define SNMP_ADD(type, addr)	, SNMP_I_ADD, (char)(type), (char)(addr), (char)((word)(addr) >> 8)
#define SNMP_XADD(type, offs)	, SNMP_I_XADD, (char)(type), (char)(offs), (char)((offs) >> 8)
#define SNMP_ADDL(type, addr, maxlen)	, SNMP_I_ADD, (char)(type), (char)(addr), \
							(char)((word)(addr) >> 8), (char)(maxlen), (char)((maxlen) >> 8)
#define SNMP_XADDL(type, offs, maxlen)	, SNMP_I_XADD, (char)(type), (char)(offs), \
							(char)((offs) >> 8), (char)(maxlen), (char)((maxlen) >> 8)
#define SNMP_STIX(addr)		, SNMP_I_STIX, (char)(addr), (char)((word)(addr) >> 8)
#define SNMP_SAV		, SNMP_I_SAV
#define SNMP_NSAV		, SNMP_I_NSAV
#define SNMP_ADDI(type, addr)	, SNMP_I_ADDI, (char)(type), (char)(addr), (char)((word)(addr) >> 8)
#define SNMP_XADDI(type, offs)	, SNMP_I_XADDI, (char)(type), (char)(offs), (char)((offs) >> 8)
#define SNMP_ADDLI(type, addr, maxlen)	, SNMP_I_ADDI, (char)(type), (char)(addr), \
							(char)((word)(addr) >> 8), (char)(maxlen), (char)((maxlen) >> 8)
#define SNMP_XADDLI(type, offs, maxlen)	, SNMP_I_XADDI, (char)(type), (char)(offs), \
							(char)((offs) >> 8), (char)(maxlen), (char)((maxlen) >> 8)

										

//Object type representations
#ifndef POST_720
typedef word snmp_type;
#define SNMP_SHORT 	0
#define SNMP_LONG 	1
#define SNMP_STR 	2
#define SNMP_OCT 	3
#define SNMP_FOCT 	4
#define SNMP_OID 	5
#else
typedef enum {
	 SNMP_SHORT			// 2-byte signed integer
  	,SNMP_LONG			// 4-byte signed integer
  	,SNMP_STR			// Null-terminated ascii string
  	,SNMP_OCT			// Variable-length binary octet string
  	,SNMP_FOCT			// Fixed-length binary octet string
  	,SNMP_OID			// ISO object identifier
} snmp_type;
#endif


//These definitions really belong in SNMP.LIB, however we bring them in here just in case MIB.LIB is being used 
//stand-alone.  If so, then the SNMP_P_* values are basically meaningless.
 
// SNMP primitive data types
#define SNMP_P_INTEGER 		0x02
#define SNMP_P_OCTETSTR		0x04
#define SNMP_P_NULL		0x05
#define SNMP_P_OID		0x06
#define SNMP_P_SEQ		0x30

// SNMP abstract (derived) data types
#define SNMP_P_IPADDR		0x40
#define SNMP_P_COUNTER		0x41
#define SNMP_P_GAUGE		0x42
#define SNMP_P_TIMETICKS	0x43

//These values combine SNMP data type and internal type used by MIB.LIB, and are used as one of the parameters 
//of the general snmp_add/snmp_xadd functions. There may be more than one way of internally storing a
//particular data type e.g. IP addresses can be stored as 4-byte fixed-length octet, or as a longword integer.
#define SNMP_INTEGER_AS_SHORT	(SNMP_P_INTEGER<<4 | SNMP_SHORT)
#define SNMP_INTEGER_AS_LONG	(SNMP_P_INTEGER<<4 | SNMP_LONG)
#define SNMP_INTEGER		SNMP_INTEGER_AS_LONG
#define SNMP_OCTETSTR_VARIABLE	(SNMP_P_OCTETSTR<<4 | SNMP_OCT)
#define SNMP_OCTETSTR_NULLTERM	(SNMP_P_OCTETSTR<<4 | SNMP_STR)
#define SNMP_ASCIISTR		SNMP_OCTETSTR_NULLTERM
#define SNMP_OCTETSTR_FIXED	(SNMP_P_OCTETSTR<<4 | SNMP_FOCT)
#define SNMP_OBJECT_ID		(SNMP_P_OID<<4 | SNMP_OID)
#define SNMP_IPADDR_AS_OCT	(SNMP_P_IPADDR<<4 | SNMP_FOCT)
#define SNMP_IPADDR_AS_LONG	(SNMP_P_IPADDR<<4 | SNMP_LONG)
#define SNMP_COUNTER_AS_SHORT	(SNMP_P_COUNTER<<4 | SNMP_SHORT)
#define SNMP_COUNTER_AS_LONG	(SNMP_P_COUNTER<<4 | SNMP_LONG)
#define SNMP_COUNTER		SNMP_COUNTER_AS_LONG
#define SNMP_GAUGE_AS_SHORT	(SNMP_P_GAUGE<<4 | SNMP_SHORT)
#define SNMP_GAUGE_AS_LONG	(SNMP_P_GAUGE<<4 | SNMP_LONG)
#define SNMP_GAUGE		SNMP_GAUGE_AS_LONG
#define SNMP_TIMETICKS		(SNMP_P_TIMETICKS<<4 | SNMP_LONG)

typedef U16 snmp_errorcode;
#define SNMP_ERR_noError	0
#define SNMP_ERR_tooBig		1
#define SNMP_ERR_noSuchName	2
#define SNMP_ERR_badValue	3
#define SNMP_ERR_readOnly	4
#define SNMP_ERR_genErr		5

//Callback function type
typedef int (*snmp_callback)( /* snmp_parms * p, int wr, int commit, long * v, word * len, word maxlen */ );

/*
Structure of MIB tree nodes (internal).  Pointers within the tree are represented by indices, not addresses, 
which allows the table to be relocated.  A null index is represented by SNMP_NULL, not zero.  A maximum of 
32767 entries is allowed. Each entry is 20 bytes, so the largest possible table is 640kB. We divide tree 
elements into two types: "node" and "leaf".  Nodes have children, leaves do not, but contain object instance 
data. Each node and leaf in the tree points to its parent (which may be NULL for the topmost nodes). Each node
points to its lowest child in lexicographic order of OID.  Nodes and leaves may have siblings: the sib pointer
points to the next higher sibling in lex order. No two siblings may have OIDs starting with the same level 
i.e. all siblings strictly ascend in order of their first OID level.
Nodes may contain one or more OID levels (called an OID fragment).  Leaves contain only the least significant 
level of their complete OID.  Nodes and leaves may be siblings. Nodes must have at least one child.  A node 
which loses all its children is deleted.
Comparisons between OIDs are an important part of tree scanning.  Unfortunately, the standard Basic Encoding 
Rule (BER) for OIDs is not suitable for simple memcmp() comparisons.  E.g. 16383 is coded as 0xFF 0x7F whereas
65535 is coded as 0x83 0xFF 0x7F. So that memcmp() can be used, we use a slightly different encoding. Numbers
0-253 are coded as-is (in a single byte).  254 through 65535 are coded as 0xFE xx yy 0xFE where xx is the MSB
of the number, yy is the LSB. Numbers >= 65536 are encoded as 0xFF ww xx yy zz 0xFF where ww is the MSB etc. 
This preserves correct lexicographic order w.r.t. memcmp().  Since numbers > 253 are rare, there should even 
be a slight space-saving with this encoding. Numbers have tags at both ends to simplify backwards scanning.
This encoding scheme, known as RLER (Reversible Lexicographic Encoding Rule), is used throughout the MIB/SNMP 
implementation.  Conversion to BER is done only when reading/sending packets.
 */

//Object identifier ("variable name") type
typedef struct _snmp_oid {
	word	len;
	char	oid[SNMP_MAX_NAME];
} snmp_oid;

//the size of mib_tree = 20 bytes
typedef struct {
	word	sib;		// Next higher sibling node index (must be first field)
	word	parent;		// Parent node index
	union {
		struct {
			word	child;	//First child node index
			word	len;	//Length of following OID fragment - not that this field overlaps
//the flags field in the leaf variant, which is how the two variants are distinguished.
#define MIB_FRAG_LEN	12
			char	oid[MIB_FRAG_LEN];	//OID fragment (encoded as described above, not BER)
		} node;
		struct {
			byte	rdmask;		// Read access mask
			byte	wrmask;		// Write access mask
//			word	spare;		//leaf aux info node index
			word	flags;		//Flags as follows (plus the MIB_* flags of snmp_parms also used if leaf):
#define MIB_LEAF	0x8000	// Indicates this is leaf (else is node; should use node variant).
#define MIB_LEAFA	0x4000	// Indicates this is leaf auxiliary.
#define MIB_TYPEMASK	0x0007	// These bits contain snmp_type enum value if leaf node
#define MIB_SNMPMASK	0x0FF0	// These bits contain SNMP data type (see SNMP_P_* above).  This is a refinement of the basic snmp_type storage format. 
//			oidlevel id;		// Last level of OID
			word id;		// Last level of OID
			word 	maxlen;		// Maximum length of string or octet buffer
			union {
				short * i;
				long * L;
				char * s;
				long x;
				snmp_oid * o;
			} v;
			snmp_callback cb;	//Callback function (or null)
//			word 	maxlen;		// Maximum length of string or octet buffer
//			byte	rdmask;		// Read access mask
//			byte	wrmask;		// Write access mask
		} leaf;
	} u;
} mib_tree;

#define MIB_TREE_SIZE	20		// sizeof(mib_tree) - this is necessary for assembler code

//Structure used for navigating the MIB tree.
typedef struct {
	word	index;		//Current node index
	word	prevsib;	//Previous sibling index (or SNMP_NULL)
	word	nextsib;	//Sibling after prevsib, or 1st child if prevsib null.
	word	n_offs;		//OID offset in current node
	mib_tree *t;		//Cached copy of MIB tree element 'index'.
	word	s_offs;		//OID offset in search OID
	snmp_oid s_oid;		//Search OID
} mib_cursor;

// Return values from search functions, outlining the extent of match
#define MIB_MATCH	0x0001	//At least partial match in node and/or search OID
#define MIB_N_MATCH	0x0002	//Node fully matched
#define MIB_S_MATCH	0x0004	//Search OID fully matched
#define MIB_S_OFLO	0x0008	//Node fully matched was a leaf, but search OID not fully matched
#define MIB_NOT_LEAF	0x0010	//Search did not terminate at leaf node (_mib_find)
#define MIB_S_LOW	0x0020	//Search OID fragment lower than fragment in node (if not full match)

//Parameters passed to most mib functions
typedef struct _snmp_parms
{
	snmp_oid	stem;	//Must be 1st parameter, so can cast snmp_parms to snmp_oid
	word		flags;	//Only allowed to have bits matching 0x7008:
#define MIB_SAVEABLE	0x1000	//This object is saveable/restorable
#define MIB_FAR		0x2000	//Object is in xmem (else root)
//#define MIB_		0x4000
//#define MIB_		0x0008
	byte		rdmask;	//Read mask - specifies which communities can read this object
	byte		wrmask;	//Write mask
	snmp_callback 	fn;	//Callback function for when object accessed
	word		index;	//Index of last object added
//	snmp_type	type;	//Selector for the following
	word type;
	union {
		int *	i;	//Short integer
		long * L;	//Long integer
		char * s;	//String (null term or binary)
		long	x;	//Address of xmem object (string or octet or OID)
		snmp_oid * o;	//Pointer to object ID
	} u;
	mib_tree *last;	// Last MIB tree entry retrieved (snmp_get() etc.)
	word	maxlen;			// Maximum length of string or octet object i.e. buffer size, or length of fixed-length octet string.
} snmp_parms;

#define SNMP_NULL	0xFFFF	// Null value for index use

//Global structure.  One instance of this exists to collect all required global information.
typedef struct {
	mib_tree * buf;	// Physical address of start of xmem buffer.  Length of buffer is SNMP_MIB_SIZE.
			// xalloc() guarantees an even address, so it is safe to use LDP on word fields.
			// This must be 1st field (asm usage).
	mib_tree * pFixedMibTab;	//  Length of buffer is SNMP_MIB_SIZE.
	mib_tree * pDynMibTab;		// Length of buffer is SNMP_MIB_SIZE.
	word dynMibTab;
	word	Root;	// Index of tree root.
	word	free;	// Index of first free node in linked list (chained by sib field)
	word	freecount;	// Number of free nodes
	word max_mibs;
} mib_globals;

extern mib_globals _mib;
extern snmp_oid _snmp_enterprise_oid;
extern const short tableIndex[];


//function declare
mib_tree * _mib_get_ptr(word index);
snmp_oid * _mib_parse_oid(snmp_oid * oid, char * name, int append);
snmp_oid * _mib_binary_oid(snmp_oid * oid, word elen, char * bname, int append);
snmp_oid * _mib_append_oid(snmp_oid * oid, oidlevel n);
snmp_oid * _mib_cat_oid(snmp_oid * oid, word elen, char * eos);
snmp_oid * _mib_up(snmp_oid * oid, word levels);
int _mib_append_level(char ** p, word * len, oidlevel n);
snmp_parms * _mib_insert(snmp_parms * p);
word _mib_find_sib(mib_cursor * c);
word _mib_find(mib_cursor * c);
word _mib_new(void);
void _mib_freeup(word index);
void _mib_set_sib(word index, word sib);
word _mib_get_sib(word index);
word _mib_is_leaf(mib_cursor * c);
oidlevel _mib_get_level(char * eos, word * offs);
void _mib_reconstruct_stem(snmp_parms * p);
void _mib_print_tree(word Root, word indent);
snmp_parms * snmp_init_parms(snmp_parms * p);
snmp_parms * snmp_set_stem(snmp_parms * p, word len, char * eos);
snmp_oid * snmp_set_oid(snmp_oid * oid, word len, char * eos);
snmp_parms * snmp_append_stem(snmp_parms * p, word len, char * eos);
snmp_oid * snmp_append_oid(snmp_oid * oid, word len, char * eos);
snmp_parms * snmp_set_parse_stem(snmp_parms * p, char * name);
snmp_oid * snmp_set_parse_oid(snmp_oid * oid, char * name);
snmp_parms * snmp_append_parse_stem(snmp_parms * p, char * name);
snmp_oid * snmp_append_parse_oid(snmp_oid * oid, char * name);
snmp_parms * snmp_append_binary_stem(snmp_parms * p, word len, char * bname);
snmp_oid * snmp_append_binary_oid(snmp_oid * oid, word len, char * bname);
snmp_parms * snmp_up_stem(snmp_parms * p, word levels);
snmp_oid * snmp_up_oid(snmp_oid * oid, word levels);
snmp_parms * snmp_set_access(snmp_parms * p, byte rm, byte wm);
snmp_parms * snmp_set_callback(snmp_parms * p, snmp_callback cb);
snmp_parms * snmp_set_save(snmp_parms * p, int save);

snmp_parms * snmp_add(snmp_parms * p, char * n, word type, void * v, word maxlen);
#define snmp_add_int(p,n,i) snmp_add(p, n, SNMP_INTEGER_AS_SHORT, i, 2)
#define snmp_add_uint(p,n,i) snmp_add(p, n, SNMP_GAUGE_AS_SHORT, i, 2)
#define snmp_add_long(p,n,i) snmp_add(p, n, SNMP_INTEGER_AS_LONG, i, 4)
#define snmp_add_ipaddr(p,n,i) snmp_add(p, n, SNMP_IPADDR_AS_LONG, i, 4)
#define snmp_add_timeticks(p,n,i) snmp_add(p, n, SNMP_TIMETICKS, i, 4)
#define snmp_add_ulong(p,n,i) snmp_add(p, n, SNMP_GAUGE_AS_LONG, i, 4)
#define snmp_add_str(p,n,s,m) snmp_add(p, n, SNMP_ASCIISTR, s, m)
#define snmp_add_oct(p,n,s,m) snmp_add(p, n, SNMP_OCTETSTR_VARIABLE, s, m)
#define snmp_add_foct(p,n,s,m) snmp_add(p, n, SNMP_OCTETSTR_FIXED, s, m)
#define snmp_add_objectID(p,n,s) snmp_add(p, n, SNMP_OBJECT_ID, s, sizeof(snmp_oid))
#define snmp_add_counter32(p,n,i) snmp_add(p, n, SNMP_COUNTER_AS_LONG, i, 4)
#define snmp_add_gauge32(p,n,i) snmp_add(p, n, SNMP_GAUGE_AS_LONG, i, 4)

snmp_parms * snmp_delete(snmp_parms * p);
snmp_parms * snmp_get(snmp_parms * p);
snmp_parms * snmp_set_int(snmp_parms * p, int i);
snmp_parms * snmp_set_long(snmp_parms * p, long L);
snmp_parms * snmp_set_str(snmp_parms * p, char * s);
snmp_parms * snmp_set_foct(snmp_parms * p, char * s);
snmp_parms * snmp_set_oct(snmp_parms * p, word len, char * s);
snmp_parms * snmp_set_objectID(snmp_parms * p, snmp_oid * oid);
snmp_parms * snmp_get_indexed(snmp_parms * p, word i);
word snmp_last_index(snmp_parms * p);
snmp_parms * snmp_get_next(snmp_parms * p);
snmp_oid * snmp_copy_oid(snmp_parms * p, snmp_oid * n);
snmp_type snmp_last_type(snmp_parms * p);
word snmp_last_snmp_type(snmp_parms * p);
word snmp_last_maxlen(snmp_parms * p);
word snmp_last_len(snmp_parms * p);
int snmp_last_int(snmp_parms * p);
long snmp_last_long(snmp_parms * p);
char * snmp_last_mem(snmp_parms * p);
long snmp_last_xmem(snmp_parms * p);
snmp_parms * snmp_last_objectID(snmp_parms * p, snmp_oid * oid);
long snmp_used(void);
long snmp_max_mibs(void);
//snmp_parms * snmp_create(snmp_parms * p, char * til, long xaddbase);

char * snmp_format_oid(snmp_oid * oid);
void snmp_print_tree(void);
void _mib_init(void);
void _snmp_init_enterpriseOid(U32 snmp_enterprise);
BOOL Set_Mibs(int NumOfMibs);
BOOL snmp_var_rebinding(word index, void* newVarPtr);

#define ASSERT(result) if (!result) while (1)

#endif	/* __SNMP_MIB__ */

