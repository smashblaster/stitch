#include "Nintendo.h"
#include "module.cpp"

class Meta: public Module {
	public:
		bool isPassthrough = false;
		bool rumble = false;

		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			rumble = false;

			// super = start
			if (state.start == 1) {
				(*data).report.start = 0;

				// a => start
				if (state.a == 1) {
					(*data).report.a = 0;
					(*data).report.start = 1;
				}

				if (state.b == 1) {
					(*data).report.b = 0;
					rumble = true;
				}

				// dleft => toggle noop
				if (state.ddown == 1) {
					(*data).report.ddown = 0;
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
