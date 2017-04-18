#include "module.cpp"
#include <Nintendo.h>

class Remapper: public Module {
	public:
		void update(Context *ctx, Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			if (!ctx->enabled) return;

			// Map x => shield
			if (state.x == 1) {
				data->report.x = 0;
				data->report.l = 1;
			}

			// // Map dright => toggle between vanilla / dolphin
			// if (state.dright == 1) {
			// 	data->report.dright = 0;
			// 	if (maxDashBuffer == maxDashBufferVanilla) {
			// 		maxDashBuffer = maxDashBufferDolphin;
			// 		digitalWrite(LED_BUILTIN, HIGH);
			// 	} else {
			// 		maxDashBuffer = maxDashBufferVanilla;
			// 		digitalWrite(LED_BUILTIN, LOW);
			// 	}
			// }

			// if (state.dup == 1) {
			// 	data->report.dup = 0;
			// 	data->report.xAxis = 138;
			// 	data->report.yAxis = 80;
			// 	// data->report.xAxis = 55;
			// 	// data->report.yAxis = 51;
			// }
		}
};
