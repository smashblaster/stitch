#include "module.cpp"
#include <Nintendo.h>

class Debug: public Module {
	public:
		void update(Context *ctx, CGamecubeController controller) {
			if (!ctx->enabled || !ctx->debug) return;

			if (ctx->pressed.find("a") != ctx->pressed.end()) Serial.println("pressed");
			else if (ctx->released.find("a") != ctx->released.end()) Serial.println("released");
			else Serial.println("no");

			// Serial.print(ctx->state.xAxis);
			// Serial.print("\t");
			// Serial.print(ctx->state.yAxis);
			// Serial.println("");
		}
};
