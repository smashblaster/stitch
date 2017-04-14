#include "Nintendo.h"
#include "module.cpp"

class Meta: public Module {
	public:
		bool isPassthrough = false;

		void update(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			// super = start
			if (state.start == 1) {
				(*data).report.start = 0;

				// a => start
				if (state.a == 1) (*data).report.start = 1;

				// dleft => toggle noop
				if (state.dleft == 1) {
					(*data).report.dleft = 0;
					isPassthrough = (isPassthrough == true) ? false : true;
					(*data).report.start = 1;
					controller.setRumble(true);
				}
			}
		}
};
