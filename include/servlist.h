#ifndef __SERVLIST_H__
#define __SERVLIST_H__

#include "typeDef.h"

typedef struct {
	longword ip;	// Server or resource IP address
	void * data;	// Opaque data for application use
	word flags;		// Flags bits
} ServTableEntry;


// Header structure.  Application is responsible for initializing this struct.
typedef struct {
	word num;		// Current number of entries.  App inits to zero.
	word max;		// Max permissible entries.  App inits to array size of following.
	ServTableEntry * table;	// First element in table.  App inits to point to array of entries.
	// The array does not need to be initialized.
	// App defines the following, which should be constant for life of the table.
	word sources;	// "Source" bits of entry flags field
	word health;	// "Health" bits of entry flags field - mutex with "sources"
	word preference;	// "Preference" bits of entry flags field - may overlap either or both the above.
} ServTableDesc;


void _servlist_sort_preferences(ServTableDesc * std);
int servlist_add(ServTableDesc * std, longword ip, word source, void * data);
int servlist_delete(ServTableDesc * std, longword ip, word source);
int servlist_set_health(ServTableDesc * std, longword ip, word mask, word health);
word servlist_flags(ServTableDesc * std, longword ip);
longword servlist_first(ServTableDesc * std, word source, void ** data);
longword servlist_next(ServTableDesc * std, longword current, word source, void ** data);
void servlist_print(void * vp);
//void* servlist_getstd(void);

#endif /* __SERVLIST_H__ */
