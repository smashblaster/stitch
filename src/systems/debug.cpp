#include "system.cpp"
#include <Nintendo.h>

class Debug: public System {
	using System::System;

	public:
		void update() {
			if (!ctx->debug) return;

			// Serial.print(ctx->state.xAxis);
			// Serial.print("\t");
			// Serial.print(ctx->state.yAxis);
			// Serial.println("");
		}
};
