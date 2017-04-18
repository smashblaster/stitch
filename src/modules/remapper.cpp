#include "module.cpp"
#include <Nintendo.h>

class Remapper: public Module {
	public:
		void update(Context *ctx, CGamecubeController controller) {
			if (!ctx->enabled) return;

			// Map x => shield
			if (ctx->state.x == 1) {
				ctx->data.report.x = 0;
				ctx->data.report.l = 1;
			}

			// // Map dright => toggle between vanilla / dolphin
			// if (ctx->state.dright == 1) {
			// 	ctx->data.report.dright = 0;
			// 	if (maxDashBuffer == maxDashBufferVanilla) {
			// 		maxDashBuffer = maxDashBufferDolphin;
			// 		digitalWrite(LED_BUILTIN, HIGH);
			// 	} else {
			// 		maxDashBuffer = maxDashBufferVanilla;
			// 		digitalWrite(LED_BUILTIN, LOW);
			// 	}
			// }

			// if (ctx->state.dup == 1) {
			// 	ctx->data.report.dup = 0;
			// 	ctx->data.report.xAxis = 138;
			// 	ctx->data.report.yAxis = 80;
			// 	// ctx->data.report.xAxis = 55;
			// 	// ctx->data.report.yAxis = 51;
			// }
		}
};
