#include "system.hpp"
#include <MemoryFree.h>

class DebugSystem: public System {
	using System::System;

	public:
		void update() {
			ctx->end();
			if (Serial.available()) {
				String cmd = Serial.readString();
				usage();
			}
		}

		void usage() {
			Serial.print("mem: ");
			Serial.print(freeMemory());
			Serial.print("\t");
			Serial.print("cpu: ");
			Serial.print(ctx->debug);
			Serial.println("");
		}
};
