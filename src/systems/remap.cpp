#include "system.hpp"

class RemapSystem: public System {
	using System::System;

	public:
		void update() {
			// x => shield
			// if (ctx->down("X")) {
			// 	ctx->release("X");
			// 	ctx->press("L");
			// }
			ctx->data.report.l |= ctx->data.report.x;
			ctx->data.report.x = 0;
		}
};
