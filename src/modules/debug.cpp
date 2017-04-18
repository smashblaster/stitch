#include "Nintendo.h"
#include "module.cpp"

class Debug: public Module {
	public:
		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			Serial.print(state.xAxis);
			Serial.print("\t");
			Serial.print(state.yAxis);
			Serial.println("");
		}
};
