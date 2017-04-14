#include "Arduino.h"
#include "Nintendo.h"
#include "module.cpp"

class Debugger: public Module {
	public:
		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			if (state.ddown == 1) {
				Serial.print(state.xAxis);
				Serial.print("\t");
				Serial.print(state.yAxis);
				Serial.println("");
			}
		}
};
