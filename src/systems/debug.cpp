#include "system.hpp"
#include <Nintendo.h>

class Debug: public System {
	using System::System;

	public:
		void update() {
			// TODO: remove
			if (!ctx->debug) return;

			// Serial.print(ctx->state.xAxis);
			// Serial.print("\t");
			// Serial.print(ctx->state.yAxis);
			// Serial.println("");
		}
};
