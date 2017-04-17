#include "Nintendo.h"
#include "module.cpp"

class Meta: public Module {
	public:
		bool isEnabled = false;
		bool rumble = false;

		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			rumble = false;

			// super = start + z
			if (state.start == 1 && state.z == 1) {
				(*data).report.start = 0;
				(*data).report.z = 0;

				// ddown => toggle
				if (state.dup == 1 || state.ddown == 1) {
					(*data).report.dup = 0;
					(*data).report.ddown = 0;
					isEnabled = state.dup == 1;
					rumble = true;
				}

				// x => debug
				if (state.x == 1) {
					(*data).report.x = 0;
					rumble = true;

					Serial.print(state.xAxis);
					Serial.print("\t");
					Serial.print(state.yAxis);
					Serial.println("");
				}
			}
		}
};
