#include <Nintendo.h>
#include <set>

#ifndef CONTEXT
#define CONTEXT

struct Context {
	Gamecube_Data_t data;
	Gamecube_Report_t state;
	bool debug = false;
	bool enabled = true;
	bool init = false;
	bool rumble = false;
	std::set<std::string> pressed;
	std::set<std::string> released;
};

#endif
