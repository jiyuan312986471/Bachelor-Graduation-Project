/* userver.h --The server utility library function Header file. */
#ifndef __USERVER__
#define __USERVER__

//#define USE_SS_FORM

// Maximum length of the name of the data
#ifndef SSPEC_MAXNAME
	#define SSPEC_MAXNAME	20
#endif
// Maximum number of users per resource
#ifndef SSPEC_USERSPERRESOURCE
	#define SSPEC_USERSPERRESOURCE 1
#endif
// Maximum number of users
#ifndef SAUTH_MAXUSERS
#define SAUTH_MAXUSERS	10
#endif

// The FormVar structure, which holds a list of variables to be used in a form
#define HTML_FORM_TEXT 		1
#define HTML_FORM_PULLDOWN	2

#ifdef USE_SS_FORM
	#define FORM_ERROR_BUF 256
#endif

#define CHAR_BIT             8
#define UCHAR_MAX          255
#define CHAR_MIN             0
#define CHAR_MAX           255
#define MB_LEN_MAX           1
#define SHRT_MIN        -32767
#define SHRT_MAX         32767
#define USHRT_MAX        65535
#define INT_MIN         -32767
#define INT_MAX          32767
#define UINT_MAX         65535
#define LONG_MIN   -2147483647
#define LONG_MAX    2147483647
#define ULONG_MAX   4294967295

// The following are constants for the type member of the ServerSpec structure
#define SS_UNUSED		10	// Marks a ServerSpec unused
#define SS_VAR			12	// The data is a variable (for HTTP)
#define SS_FUNC			15	// The data is a function (for HTTP)
#define SS_FSFILE		21	// The data resides in a file system file
#define SS_FORM			22	// A set of modifiable variables
#define SS_FILE			30	// The data resides in a file
#define SS_ERROR			999	// Indicates an error condition

// #define SSPEC_ROOTVAR		13	// The data is a variable in root memory (for HTTP)
// #define SSPEC_XMEMVAR		14	// The data is a variable in xmem (for HTTP)
// #define SSPEC_ROOTFILE		20	// The data resides in root memory
// #define SSPEC_XMEMFILE		11	// The data resides in xmem

// Constants for the vartype member of the ServerSpec structure
#define INT8		1	// char
#define INT16		2	// int
#define PTR16		3	// any short pointer value
#define INT32		4	// long
#define FLOAT32		5	// float

// Bitmasks for the servermask member of the ServerSpec and ServerAuth structures
// these determine which servers are allowed to use a particular structure.  
// If any server can modify entity, bit-OR in SERVER_WRITABLE.
#define SERVER_HTTP			0x0001
#define SERVER_FTP			0x0002
#define SERVER_USER			0x0004	// for use with the flash file system
#define SERVER_WRITABLE 	0x8000  // can modify this file! (modifier)
#define SERVER_COMPRESSED	0x4000	// File is compressed

// The ServerSpec structure
typedef struct
{
	word type;					// Type of data
	word vartype;				// Type of variable (when "SSPEC_VARIABLE" is the type of data), or length of data (when "*FILE" is the type of data and the length is needed-- e.g., a root file)
	char name[SSPEC_MAXNAME];	// Name of data
	void *pDat;					// Location of data (when "*FILE" is the type of data), or maximum number of variables in a form (when "SSPEC_FORM" is the type of data)
//	void* addr;					// Address of function or variable (when "SSPEC_FUNCTION" or "SSPEC_VARIABLE" is the type of data)
//	char* location;				// Location of data (when "SSPEC_ROOTFILE" is the type of data), or title string (when "SSPEC_FORM" is the type of data)
	int uid[SSPEC_USERSPERRESOURCE];	// User ID array--indices into the server_auth array
	char realm[SSPEC_MAXNAME];	// HTTP realm, for HTTP security features, or format of the variable, when "SSPEC_VARIABLE" is the type of data
	word servermask;			// A bitmask that determines which servers a ServerSpec is used for--servers are disabled  by default
#ifdef FORM_ERROR_BUF
	int highvar;				// Next index into FormVar array to allocate (when "SSPEC_FORM" is the type of data)
	void* formfunc;				// Form generation function (when "SSPEC_FORM" is the type of data)
	void* preformfunc;			// Function to call just before a form is generated (when "SSPEC_FORM" is the type of data)
	int formepilog;				// Form epilog function (when "SSPEC_FORM" is the type of data)
	int formprolog;				// Form prolog function (when "SSPEC_FORM" is the type of data)
#endif
// Add something for a date here?
} ServerSpec;

// Set the number of entries in the ServerSpec table. For compatibility's sake, make HTTP_MAXRAMSPEC override 
// SSPEC_MAXSPEC. If a user attempts to use both HTTP_MAXRAMSPEC and SSPEC_MAXSPEC, she may not get the desired results.  
// Hence, use of HTTP_MAXRAMSPEC should probably be deprecated.
#ifdef HTTP_MAXRAMSPEC
	#define SSPEC_MAXSPEC HTTP_MAXRAMSPEC
#endif
#ifndef SSPEC_MAXSPEC
	#define SSPEC_MAXSPEC	10
#endif

// Maximum length of strings in ServerAuth structure
#ifndef SAUTH_MAXNAME
	#define SAUTH_MAXNAME	20
#endif

typedef struct
{
	char username[SAUTH_MAXNAME];		// Name of user
	char password[SAUTH_MAXNAME];		// Password for user
	word writeaccess;						// Defines if user has write access
	word servermask;						// A bitmask that determines which servers a ServerAuth is used for--servers are disabled by default
} ServerAuth;

typedef struct
{
	short varspec;		// server_spec index that represents the variable
	short entrytype;		// Type of HTML form element for this variable (defaults to HTML_FORM_TEXT)
	union {
		struct {
			int high;		// Highest value (long int) allowed
			int low;		// Lowest value (long int) allowed
		} iLmt;
		struct {
			float fhigh;	// Highest value (float) allowed
			float flow;		// Lowest value (float) allowed
		} fLmt;
		struct {
			char **values;	// Pointer to list of values a string variable can take
			int valueslen;	// Length of values array
		} opt;
	} u;
	int (*varcheck)();	// Function pointer to variable integrity check function
	char *name;			// Name to display for the variable in the form (if not set, defaults to the name 
						// for the server_spec entry for the variable)
	char *desc;			// Description of form variable
	short varlen;		// Length of string (when a string is represented), or length of string representation 
						// (to limit form text field size)
	byte readonly;		// Indicates if the variable is read-only
	byte rangeset;		// Is the range set?
} FormVar;

#ifdef FS_RAM
	#define SSPEC_USEFS
#else
	#ifdef FS_FLASH
		#define SSPEC_USEFS
	#else
		#ifdef FS_FLASH_SINGLE
			#define SSPEC_USEFS
		#endif
	#endif
#endif

#ifdef __FS2_LIB
	#define SSPEC_USEFS
#endif

#define SSPEC_VERSION 1

typedef struct
{
	int sspec;		// Sspec entry of the open file
	long offset;	// Number of characters into the read process
#ifdef __ZIMPORT_LIB
	ZFILE zfile;	// File handle for a compressed file
#endif
} SSpecFileHandle;


//function protype
void sspec_init(void);
int sspec_findunused(char *name, word servermask);
int sspec_save(void);
int sspec_setsavedata(char* data, unsigned long len, void* fptr);
int sspec_restore(void);
int sspec_addmemfile(char* name, void* fileloc, word servermask);
int sspec_addfsfile(char* name, byte filenum, word servermask);
int sspec_addvariable(char* name, void* variable, word type, char* format, word servermask);
int sspec_addfunction(char* name, void (*fptr)(), word servermask);
int sspec_addform(char* name, FormVar* form, int formsize, word servermask);
int sspec_aliasspec(int sspec, char* name);
int sspec_resizerootfile( int spec_index, int new_size );
int sspec_addfv(int form, int var);
int sspec_setuser(int sspec, int userid);
int sspec_adduser(int sspec, int userid);
int sspec_removeuser(int sspec, int userid);
int sspec_setrealm(int sspec, char* realm);
int sspec_findname(char* name, word server);
int sspec_findfsname(byte filenum, word server);
int sspec_findnextfile(int start, word server);
long sspec_getfileloc(int sspec);
word sspec_getfiletype(int sspec);
int sspec_findfv(int form, char* varname);
int sspec_checkfv(int form, int var, char* value);
int sspec_changefv(int form, int var, char* value);
long sspec_getlength(int sspec);
int sspec_readfile(int sspec, char* buffer, long offset, int len);
int sspec_openfilehandle(SSpecFileHandle *handle, int sspec);
int sspec_readfilehandle(SSpecFileHandle *handle, char *buffer, int len);
int sspec_closefilehandle(SSpecFileHandle *handle);
int sspec_readvariable(int sspec, char* buffer);
void* sspec_getvaraddr(int sspec);
word sspec_getvarkind(int sspec);
word sspec_getvartype(int sspec);
int sspec_getservermask(int sspec, word *servermask);
long sspec_getxvaraddr(int sspec);
void* sspec_getfunction(int sspec);
int sspec_remove(int sspec);
int sspec_removebytype(word type);
int sspec_needsauthentication(int sspec);
int sspec_checkaccess(int sspec, int userid);
char* sspec_getrealm(int sspec);
char* sspec_getusername(int sspec);
int sspec_getuserid(int sspec, int index);
word sspec_gettype(int sspec);
char* sspec_getname(int sspec);
int sspec_setfvcheck(int form, int var, int (*varcheck)());
int sspec_setfvname(int form, int var, char* name);
int sspec_setfvdesc(int form, int var, char* desc);
char* sspec_getfvdesc(int form, int var);
int sspec_setfventrytype(int form, int var, int entrytype);
int sspec_getfventrytype(int form, int var);
int sspec_setfvlen(int form, int var, int len);
int sspec_getfvlen(int form, int var);
int sspec_setfvoptlist(int form, int var, char* list[], int listlen);
int sspec_setfvrange(int form, int var, long low, long high);
int sspec_setfvfloatrange(int form, int var, float low, float high);
int sspec_setfvreadonly(int form, int var, int readonly);
int sspec_getfvreadonly(int form, int var);
int sspec_setformtitle(int form, char* title);
char* sspec_getformtitle(int form);
int sspec_setformfunction(int form, void (*fptr)());
int sspec_setpreformfunction(int form, void (*fptr)());
int sspec_setformprolog(int form, int function);
int sspec_getfvnum(int form);
int sspec_getfvspec(int form, int var);
char* sspec_getfvname(int form, int var);
char* sspec_getfvopt(int form, int var, int option);
int sspec_getfvoptlistlen(int form, int var);
void sauth_init(void);
int sauth_findunused(char *username, word servermask);
int sauth_adduser(char* username, char* password, word servermask);
int sauth_setwriteaccess(int sauth, int writeaccess);
int sauth_getwriteaccess(int sauth);
int sauth_authenticate(char* username, char* password, word server);
char* sauth_getusername(int sauth);
int sauth_getuserid(char* username, word server);
int sauth_setpassword(int userid, char* password);
char* sauth_getpassword(int userid);
int sauth_removeuser(int userid);
void* sspec_getpreformfunction(int form);

//int sspec_addxmemvar(char* name, long variable, word type, char* format, word servermask);
//int sspec_addrootfile(char* name, char* fileloc, int len, word servermask);

extern ServerSpec server_spec[SSPEC_MAXSPEC];

#endif /* __USERVER__ */
