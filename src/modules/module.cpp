#include "Nintendo.h"

#ifndef MODULE
#define MODULE

class Module {
	public:
		virtual ~Module() {}
		virtual void init(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {}
		virtual void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {};
};

#endif
