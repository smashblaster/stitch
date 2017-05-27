#include "system.hpp"

class RemapSystem: public System {
	using System::System;

	public:
		void update() {
			// x => shield
			ctx->data.report.l |= ctx->data.report.x;
			ctx->data.report.x = 0;
		}
};
