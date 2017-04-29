#include "system.hpp"
#include <Nintendo.h>

class Debug: public System {
	using System::System;

	public:
		void update() {
			Serial.print(ctx->state.xAxis);
			Serial.print("\t");
			Serial.print(ctx->state.yAxis);
			Serial.println("");
		}
};
