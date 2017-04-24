#include "system.cpp"
#include <Nintendo.h>

class Remap: public System {
	public:
		void update(Context *ctx) {
			// Map x => shield
			if (ctx->down("x")) {
				ctx->release("x");
				ctx->press("l");
			}

			// // Map dright => toggle between vanilla / dolphin
			// if (ctx->pressed("dright") {
			// 	ctx->data.report.dright = 0;
			// 	if (maxDashBuffer == maxDashBufferVanilla) {
			// 		maxDashBuffer = maxDashBufferDolphin;
			// 		digitalWrite(LED_BUILTIN, HIGH);
			// 	} else {
			// 		maxDashBuffer = maxDashBufferVanilla;
			// 		digitalWrite(LED_BUILTIN, LOW);
			// 	}
			// }

			// if (ctx->pressed("dup") {
			// 	ctx->data.report.dup = 0;
			// 	ctx->data.report.xAxis = 138;
			// 	ctx->data.report.yAxis = 80;
			// 	// ctx->data.report.xAxis = 55;
			// 	// ctx->data.report.yAxis = 51;
			// }
		}
};
