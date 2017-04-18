#include "module.cpp"
#include <Nintendo.h>

class Debug: public Module {
	public:
		void update(Context *ctx, Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			if (!ctx->enabled || !ctx->debug) return;

			Serial.print(state.xAxis);
			Serial.print("\t");
			Serial.print(state.yAxis);
			Serial.println("");
		}
};
