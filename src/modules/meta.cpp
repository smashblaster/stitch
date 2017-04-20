#include "module.cpp"
#include <Nintendo.h>

class Meta: public Module {
	public:
		void update(Context *ctx, CGamecubeController controller) {
			ctx->rumble = false;

			// super = start + z
			if (ctx->state.start == 1 && ctx->state.z == 1) {
				ctx->data.report.start = 0;
				ctx->data.report.z = 0;

				// ddown => toggle
				if (ctx->state.dup == 1 || ctx->state.ddown == 1) {
					ctx->data.report.dup = 0;
					ctx->data.report.ddown = 0;
					ctx->enabled = ctx->state.dup == 1;
					ctx->rumble = true;
				}

				// x => debug
				if (ctx->state.x == 1) {
					ctx->data.report.x = 0;
					ctx->rumble = true;
					ctx->debug = !ctx->debug;
				}
			}
		}
};
