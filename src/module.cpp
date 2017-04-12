#include "Nintendo.h"

class Module {
	public:
		virtual ~Module() {}
		virtual void init(Gamecube_Report_t state, Gamecube_Data_t *data) {};
		virtual void update(Gamecube_Report_t state, Gamecube_Data_t *data) {};
};
