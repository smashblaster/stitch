#include "system.cpp"
#include <Nintendo.h>

class Meta: public System {
	using System::System;

	public:
		void update() {
			ctx->meta = false;
			ctx->rumble = false;

			// meta = start + z
			if (ctx->down("start") && ctx->down("z")) {
				ctx->meta = true;
				ctx->release("start");
				ctx->release("z");

				// ddown => toggle
				if (ctx->down("ddown")) ctx->release("ddown");
				if (ctx->pressed("ddown")) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// dup => debug
				if (ctx->down("dup")) ctx->release("dup");
				if (ctx->pressed("dup")) {
					ctx->settings->toggle("debug");
					ctx->rumble = true;
				}
			}
		}
};
