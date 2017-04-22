#include "module.cpp"
#include <Nintendo.h>

class Debug: public Module {
	public:
		std::string const name() { return "debug"; }

		void update(Context *ctx, CGamecubeController controller) {
			if (!ctx->enabled || !ctx->debug) return;

			// Serial.print(ctx->state.xAxis);
			// Serial.print("\t");
			// Serial.print(ctx->state.yAxis);
			// Serial.println("");
		}
};
