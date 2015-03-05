/* ntp.h--net time service function Header file. */

#ifndef __NTP__
#define __NTP__

typedef struct {
	longword ntp_server_IP[2];
	U32 time_update_itv;
	U32 auto_update;
	//	char ntp_server_name[28];
} _ntp_server;

typedef struct {
	char	state;
	char	ntpServerNo;
	short	errno;
	U32		timeout;
	U32		update_itv;
	int		delaySecond;
	U32		newSecond;
	short	delayFSecond;
	short	newFSecond;
} _ntp_state;

extern _ntp_server ntp_server;
extern _ntp_state ntp_state;

/* Function ProtoTypes */
void _ntp_init(void);
void _ntp_tick(void);
void ntp_update_now(void);

#endif	/* __NTP__ */

