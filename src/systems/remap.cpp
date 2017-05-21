#include "system.hpp"

class Remap: public System {
	using System::System;

	public:
		void update() {
			// x => shield
			ctx->data.report.l |= ctx->data.report.x;
			ctx->data.report.x = 0;
		}
};
