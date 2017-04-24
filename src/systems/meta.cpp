#include "system.cpp"
#include <Nintendo.h>

class Meta: public System {
	public:
		void update(Context *ctx) {
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
					ctx->debug = !ctx->debug;
					ctx->rumble = true;
				}
			}
		}
};
