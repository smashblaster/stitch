#include "module.cpp"
#include <Nintendo.h>

class Meta: public Module {
	public:
		void update(Context *ctx, Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			ctx->rumble = false;

			// super = start + z
			if (state.start == 1 && state.z == 1) {
				data->report.start = 0;
				data->report.z = 0;

				// ddown => toggle
				if (state.dup == 1 || state.ddown == 1) {
					data->report.dup = 0;
					data->report.ddown = 0;
					ctx->enabled = state.dup == 1;
					ctx->rumble = true;
				}

				// x => debug
				if (state.x == 1) {
					data->report.x = 0;
					ctx->rumble = true;
					ctx->debug = true;
				}
			}
		}
};
