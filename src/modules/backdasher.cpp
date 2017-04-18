#include "module.cpp"
#include <Nintendo.h>

class Backdasher: public Module {
	private:
		int deadZone = 22;
		int center = 128;
		// int smashZone = 97;
		int smashZone = 64;

		int dashBuffer = 0;
		int maxDashBufferVanilla = 2;
		int maxDashBufferDolphin = 8;
		int maxDashBuffer = maxDashBufferVanilla;

	public:
		void init(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			// Reset x-axis
			center = state.xAxis;
		}

		void update(Context *ctx, Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			if (!ctx->enabled) return;

			// If the x axis is between these two than set buffer to eight
			if (state.xAxis > center - deadZone - 1 && state.xAxis < center + deadZone - 1) {
				dashBuffer = maxDashBuffer;
			}

			if (state.xAxis < center - deadZone || state.xAxis > center + deadZone) {
				// Automatically dashes and skips all buffer if you enter running state
				if (state.xAxis > center + smashZone || state.xAxis < center - smashZone) {
					data->report.xAxis = state.xAxis;
					dashBuffer = 0;
				}
				if (dashBuffer > 0) {
					// Set x-axis to neutral
					data->report.xAxis = 128;
					dashBuffer = dashBuffer - 1;
				}
			}
		}
};
