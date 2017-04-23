#include "system.cpp"
#include <Nintendo.h>

class Debug: public System {
	public:
		void update(Context *ctx, CGamecubeController controller) {
			if (!ctx->debug) return;

			// Serial.print(ctx->state.xAxis);
			// Serial.print("\t");
			// Serial.print(ctx->state.yAxis);
			// Serial.println("");
		}
};
