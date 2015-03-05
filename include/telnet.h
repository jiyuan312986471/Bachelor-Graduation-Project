/* telnet.h--net telnet function Header file. */

#ifndef __TELNET__
#define __TELNET__

typedef struct {
	tcp_Socket	*s;
	byte state;
#define TELNET_COOKER_NORMAL		0
#define TELNET_COOKER_IAC			1
#define TELNET_COOKER_DO			2
#define TELNET_COOKER_DONT			3
#define TELNET_COOKER_WILL			4
#define TELNET_COOKER_WONT			5
#define TELNET_COOKER_CR			6

	// telnet state flags
	byte suppress_ga;
	byte local_echo;

	// other internal FSM flags
	byte send_nl;
	word user_options;
} _TelnetCooker;

#define TELNET_OPTION_GA    0x01  // disable GA messages
#define TELNET_OPTION_ECHO  0x02  // turn off local (client) echo



int telnet_init(_TelnetCooker *state, tcp_Socket *s, word options);
int telnet_fastread(_TelnetCooker *state, byte *dp, int len);
int telnet_fastwrite(_TelnetCooker *state, byte *dp, int len);
int telnet_rdUsed(_TelnetCooker *state);
int telnet_wrUsed(_TelnetCooker *state);
int telnet_wrFree(_TelnetCooker *state);

#endif	/* __TELNET__ */
