#include <Nintendo.h>

#ifndef CONTEXT
#define CONTEXT

struct Context {
	Gamecube_Data_t data;
	Gamecube_Report_t state;
	bool debug;
	bool enabled;
	bool init;
	bool rumble;
};

#endif
