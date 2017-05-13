#include "system.hpp"
#include <Nintendo.h>

class Remap: public System {
	using System::System;

	public:
		void update() {
			// Map x => shield
			if (ctx->down("X")) {
				ctx->release("X");
				ctx->press("L");
			}

			// // Map dright => toggle between vanilla / dolphin
			// if (ctx->pressed("DRIGHT") {
			// 	ctx->data.report.dright = 0;
			// 	if (maxDashBuffer == maxDashBufferVanilla) {
			// 		maxDashBuffer = maxDashBufferDolphin;
			// 		digitalWrite(LED_BUILTIN, HIGH);
			// 	} else {
			// 		maxDashBuffer = maxDashBufferVanilla;
			// 		digitalWrite(LED_BUILTIN, LOW);
			// 	}
			// }

			// if (ctx->pressed("DUP") {
			// 	ctx->data.report.dup = 0;
			// 	ctx->data.report.xAxis = 138;
			// 	ctx->data.report.yAxis = 80;
			// 	// ctx->data.report.xAxis = 55;
			// 	// ctx->data.report.yAxis = 51;
			// }
		}
};
