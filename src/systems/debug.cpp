#include "system.hpp"
#include <MemoryFree.h>

class DebugSystem: public System {
	using System::System;

	public:
		void update() {
			if (ctx->pressed("X")) {
				Serial.println(freeMemory());
			}
		}
};
