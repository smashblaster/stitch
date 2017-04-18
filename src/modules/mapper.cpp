#include "module.cpp"
#include <Nintendo.h>

class Mapper: public Module {
	public:
		void init(Context *ctx, CGamecubeController controller) {
			// Zero the controller out on startup
			ctx->data.origin = controller.getOrigin();
		}

		void update(Context *ctx, CGamecubeController controller) {
			ctx->data.report.a = ctx->state.a;
			ctx->data.report.b = ctx->state.b;
			ctx->data.report.start = ctx->state.start;
			ctx->data.report.x = ctx->state.x;
			ctx->data.report.y = ctx->state.y;

			ctx->data.report.ddown = ctx->state.ddown;
			ctx->data.report.dleft = ctx->state.dleft;
			ctx->data.report.dright = ctx->state.dright;
			ctx->data.report.dup = ctx->state.dup;

			ctx->data.report.l = ctx->state.l;
			ctx->data.report.r = ctx->state.r;
			ctx->data.report.z = ctx->state.z;

			ctx->data.report.cxAxis = ctx->state.cxAxis;
			ctx->data.report.cyAxis = ctx->state.cyAxis;
			ctx->data.report.left = ctx->state.left;
			ctx->data.report.right = ctx->state.right;
			ctx->data.report.xAxis = ctx->state.xAxis;
			ctx->data.report.yAxis = ctx->state.yAxis;
		}
};
