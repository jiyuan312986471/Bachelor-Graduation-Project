/* http.h --http Protocol function Header file. */

#ifndef __HTTP__
#define __HTTP__

// user changeable options
/* hours different from GMT */
#ifndef TIMEZONE
   #define TIMEZONE	         -8
#endif

#ifndef HTTP_MAXSERVERS
   #define HTTP_MAXSERVERS		2
#endif

#ifndef USE_HTTP_BASIC_AUTHENTICATION
	#define USE_HTTP_BASIC_AUTHENTICATION 1
#endif

#ifndef USE_HTTP_DIGEST_AUTHENTICATION
	#define USE_HTTP_DIGEST_AUTHENTICATION 0
#endif

#ifndef HTTP_DIGEST_NONCE_TIMEOUT
	#define HTTP_DIGEST_NONCE_TIMEOUT	900
#endif

// Max time (in seconds) that HTTP will remaining in any connected state.
//After timeout, the host will (force) close the connection.
#ifndef HTTP_TIMEOUT
   #define HTTP_TIMEOUT		16
#endif

#ifndef HTTP_PORT
#define HTTP_PORT 80
#endif


/* If main program defines HTTP_USERDATA_SIZE, then "char userdata[]" to be added to the HttpState structure.  
	If not defined, then it ain't there! Define your structure _before_ #use http.lib
 * 		struct UserStateData { char name[50]; int floor; int model; };
 * 		#define  HTTP_USERDATA_SIZE	(sizeof(struct UserStateData))
 * 		#use http.lib
 * 	Cleared to zero when structure initialized.  Otherwise it is not touched.
 * 	Value must be greater than zero. In your own code, access it like:
 * 			mystate = (struct UserStateData *) state->userdata;
 */
//improve code in the common case of 1 server.  This removes the  array indexing operations on the http_servers struct. 
#if (HTTP_MAXSERVERS == 1)
	#define HTTP_X
	#define HTTP_SERVNO 0
	#define HTTP_DECL_INDEX
	#define HTTP_FORALL_SERVERS
	#define HTTP_END_FORALL_SERVERS
#else
	#define HTTP_X [x]
	#define HTTP_SERVNO x
	#define HTTP_DECL_INDEX int x;
	#define HTTP_FORALL_SERVERS for (x=0; x < HTTP_MAXSERVERS; x++) {
	#define HTTP_END_FORALL_SERVERS }
#endif

/* internal server buffers (modify at your own risk) */
/*  Lynx V2 can send Accept: encoding strings of 250 to 600 bytes long! The TCP layer can buffer, but if you want to 
 	interoperate, make sure HTTP_MAXBUFFER is large.  It also affects POST methods.
	cgi_redirectto() uses about 200 chars during its processing. */
#ifndef HTTP_MAXBUFFER
   #define HTTP_MAXBUFFER     512
#endif

#ifndef HTTP_MAXURL
   #define HTTP_MAXURL        128
#endif

#ifndef HTTP_MAXNAME
   #define HTTP_MAXNAME       20
#endif

#ifndef MAX_CACHE_USER
#define MAX_CACHE_USER 4
#endif

/*#ifndef HTTP_NO_FLASHSPEC
	#define HTTP_MAXFLASHSPEC		(sizeof(http_flashspec)/sizeof(HttpSpec))
#endif*/

#ifndef HTTP_MAX_COND
   /* SJH - support for conditional SSI (error feedback etc) */
   #define HTTP_MAX_COND		4
#endif

#define HTTP_MAXTYPE          (sizeof(http_types)/sizeof(HttpType))

#define HS_UNUSED	0
#define HS_FILE		1
#define HS_VAR		2
#define HS_FUNC		3
#define HS_USED		4

// HttpState.state's
#define HTTP_INIT         		0
#define HTTP_LISTEN       		1
#define HTTP_GETREQ       		2
#define HTTP_GETHEAD      		3
#define HTTP_PROCESS      		4
#define HTTP_SENDPAGE     		5
#define HTTP_HANDLER      		6
#define HTTP_WAITCLOSE    		7
#define HTTP_FINISHWRITE  		8
#define HTTP_DIE          		9
#define HTTP_CGI          		10

#define HTTP_METHOD_GET   		1
#define HTTP_METHOD_HEAD  		2
#define HTTP_METHOD_POST  		3

#define HTTP_VER_09       		1
#define HTTP_VER_10       		2
#define HTTP_VER_11       		3

typedef struct {
   char extension[7];
   char use_cache;
   char type[HTTP_MAXNAME];
   int  (*fptr)(/* HttpState* */);
} HttpType;

typedef struct {
   char username[HTTP_MAXNAME];
   char password[HTTP_MAXNAME];
   char realm[HTTP_MAXNAME];
} HttpRealm;

typedef struct {
   word type;
   word vartype;
   char name[HTTP_MAXNAME];
   void *pDat;
//   void* addr;
   char* format;
   HttpRealm* realm;
} HttpSpec;

#define HTTP_IS_HS	0
#define HTTP_IS_SS	1
#define HTTP_IS_NOTFOUND	2

typedef struct {
	word type;
	short sspec;
	HttpSpec* hspec;
} HttpSpecAll;

//options define
#define BIT_LOGIN 0x0001
#define BIT_SETCOOK 0x0002
#define BIT_OPTION1 0x0004
#define BIT_OPTION2 0x0008
#define BIT_OPTION3 0x0010
#define BIT_OPTION4 0x0020
typedef struct {
	longword userIp;
	longword tmOut;
	word options;
	char auth;
	char rsv;
} _userCache;

#ifdef USE_WEB_AUTHENTICATION
extern _userCache userCache[MAX_CACHE_USER];
#endif

typedef struct {
	tcp_Socket s;

   /* state information */
	char state, nextstate, laststate, spare;  // spare is fill field
	short substate, subsubstate;

   /* File refrenced */
	HttpSpecAll spec, subspec;
	HttpType *type;
	int (*handler)();		  //, (*exec)()

   /* rx/tx state variables */
	long offset;
	long length;
	long filelength, subfilelength;
	long pos, subpos;
	long timeout, main_timeout;
//	char buffer[HTTP_MAXBUFFER];
	char *p;
	char peek[7];
	char peeklen;

   /* http request and header info */
	long content_length;
	long content_count;
	char url[HTTP_MAXURL];
	char method;
	char version;
	char connection;       	// Keep-Alive ???
	char has_form;			// 1 == has a GET style form, after the \0 byte in url[]
	char finish_form;		// after _form_error_buf lock released, just finishing up form processing
	char abort_notify;		// indicates if a function needs to be called on abort 
	char cancel;			// will be 1 when formepilog function is called on cancel, 0 otherwise

	char authenticated;

	char buffer[HTTP_MAXBUFFER];
	char content_type[40];
	char cookie[HTTP_MAXNAME];	// store the cookie value */
	char username[HTTP_MAXNAME];
	char password[HTTP_MAXNAME];

   /* SJH - support for conditional SSI (error feedback etc) */
//	int cond[HTTP_MAX_COND];		/* Condition numbers (default 0) */
 
   /* other - don't touch */
	int headerlen;
	int headeroff;
	char tag[HTTP_MAXNAME];    /* storage for tag/value in SSI */
	char value[HTTP_MAXNAME];

/* ZImport state structure -- Only included if zimport.lib has been #use'd */
	union {
		SSpecFileHandle s;
#ifdef __ZIMPORT_LIB
		ZFILE z;
#endif
	} file;	
	char close_needed;
	char uCacheNo;
/*  Optional User Data.  Cleared on every new connection. */
#ifdef HTTP_USERDATA_SIZE
	char 	userdata[ HTTP_USERDATA_SIZE];
#endif
} HttpState;

extern const HttpSpec http_flashspec[];
extern const char last_modeify_date[];
extern const int Http_MaxFlashSpec;

//function protypes
char *http_date_str(char *buf);
char *ofs_Year_DateStr(char *buf, int ofs);
unsigned char base64char(char c);
void unbase64(char *dest, char *src);
int http_getline(HttpState* state);
int http_parseget(HttpState* state);
int http_parsehead(HttpState* state);
char* http_getheaderoption(char* src);
int http_checknonce(char* nonce, char* nc);
int http_parsedigesthead(HttpState* state, char** nonce, char** nc, char** cnonce, char** response);
int http_setcookie(char *buf, char *value);
void http_send_304(HttpState* state);
void http_send_404(HttpState* state);
void http_send_401(HttpState* state);
int http_findnonceslot(unsigned long time);
char* http_makenonce(void);
int http_sendfile(HttpState* state);
int http_sendbuffer(HttpState* state);
HttpType *http_findtype(char *name);
void http_expandhash(char* dest, char* src, int len);
int http_basicauthentication(HttpState* state);
int http_digestauthentication(HttpState* state, char* nonce, char* nc, char* cnonce, char* response);
int http_setauthentication(int auth);
int http_needsauthentication(HttpState* state);
int http_process(HttpState* state);
int http_init(void);
void http_handler(void);
HttpSpecAll http_findname(char* name);
HttpSpecAll http_findnameram(char* name);
HttpSpecAll http_findnameflash(char* name);
int http_addfile(char* name, void* location);
int http_delfile(char* name);
int http_readfromfile(HttpState *state, char *buf, int len);
void http_unpeekfromfile(HttpState *state, char *buf, int len);
int shtml_handler(HttpState* state);
int shtml_addvariable(char* name, void* variable, word type, char* format);
int shtml_delvariable(char* name);
int shtml_addfunction(char* name, void (*fptr)(/* HttpState* */));
int shtml_delfunction(char* name);
void _http_abort(int x);
void cgi_redirectto(HttpState* state, char* url);
void cgi_sendstring(HttpState* state, char* str);
char *http_urldecode(char *dest, /*const*/char *src, int len);
char *http_contentencode(char *dest, /*const*/char *src, int max_dest_len);
int http_scanpost(char* tag, char* buffer, char* dest, int maxlen);
int http_generateform(int form, HttpState *state, int error);
char* http_finderrbuf(char* name);
void http_nextfverr(char* start, char** name, char** value, int* errno, char** next);
void http_setfverror(char* var);
int http_parseform(int form, HttpState *state);
int http_idle(void);
int cacheUser(HttpState *state);
int isLogin(HttpState *state);
char* getSSIParamPtr(char* buffer, int num);
void flushHeaderLen(HttpState *state);



#endif /* __HTTP__ */
