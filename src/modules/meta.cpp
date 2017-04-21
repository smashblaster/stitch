#include "module.cpp"
#include <Nintendo.h>

class Meta: public Module {
	public:
		void update(Context *ctx, CGamecubeController controller) {
			ctx->rumble = false;

			// super = start + z
			if (ctx->down("start") && ctx->down("z")) {
				ctx->release("start");
				ctx->release("z");

				// ddown => toggle
				if (ctx->pressed("ddown")) {
					ctx->release("ddown");
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// x => debug
				if (ctx->pressed("x")) {
					ctx->release("x");
					ctx->debug = !ctx->debug;
					ctx->rumble = true;
				}
			}
		}
};
