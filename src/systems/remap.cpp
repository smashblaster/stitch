#include "system.hpp"

class Remap: public System {
	using System::System;

	public:
		void update() {
			// x => shield
			if (ctx->down("X")) {
				ctx->release("X");
				ctx->press("L");
			}
		}
};
