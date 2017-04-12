#include "Nintendo.h"
#include "module.cpp"

int deadZone = 22;
int center = 128;
// int smashZone = 97;
int smashZone = 64;

// Zero the buffer and control stick
int dashBuffer = 0;
int maxDashBufferVanilla = 2;
int maxDashBufferDolphin = 8;
int maxDashBuffer = maxDashBufferVanilla;

class Dashback: public Module {
	public:
		void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
			// Reset x-axis
			center = state.xAxis;
		}

		void update(Gamecube_Report_t state, Gamecube_Data_t *data) {
			// If the x axis is between these two than set buffer to eight
			if (state.xAxis > center - deadZone - 1 && state.xAxis < center + deadZone - 1) {
				dashBuffer = maxDashBuffer;
			}

			if (state.xAxis < center - deadZone || state.xAxis > center + deadZone) {
				// Automatically dashes and skips all buffer if you enter running state
				if (state.xAxis > center + smashZone || state.xAxis < center - smashZone) {
					(*data).report.xAxis = state.xAxis;
					dashBuffer = 0;
				}
				if (dashBuffer > 0) {
					// Set x-axis to neutral
					(*data).report.xAxis = 128;
					dashBuffer = dashBuffer - 1;
				}
			}
		}
};
