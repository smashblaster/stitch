#include "Nintendo.h"
#include "module.cpp"

class Meta: public Module {
	public:
		bool isPassthrough = false;
		bool rumble = false;

		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			rumble = false;

			// super = ddown
			if (state.ddown == 1) {
				(*data).report.ddown = 0;

				// z => ddown
				if (state.z == 1) {
					(*data).report.z = 0;
					(*data).report.ddown = 1;
				}

				if (state.x == 1) {
					(*data).report.x = 0;
					rumble = true;
				}

				// start => toggle noop
				if (state.start == 1) {
					(*data).report.start = 0;
					isPassthrough = (isPassthrough == true) ? false : true;
					rumble = true;
				}

				// dup => debug
				if (state.dup == 1) {
					Serial.print(state.xAxis);
					Serial.print("\t");
					Serial.print(state.yAxis);
					Serial.println("");
				}
			}
		}
};
