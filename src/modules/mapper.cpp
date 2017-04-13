#include "Nintendo.h"
#include "module.cpp"

class Mapper: public Module {
	public:
		void init(Gamecube_Report_t state, Gamecube_Data_t *data, CGamecubeController controller) {
			// Zero the controller out on startup
			(*data).origin = controller.getOrigin();
		}

		void update(Gamecube_Report_t state, Gamecube_Data_t *data) {
			(*data).report.a = state.a;
			(*data).report.b = state.b;
			(*data).report.start = state.start;
			(*data).report.x = state.x;
			(*data).report.y = state.y;

			(*data).report.ddown = state.ddown;
			(*data).report.dleft = state.dleft;
			(*data).report.dright = state.dright;
			(*data).report.dup = state.dup;

			(*data).report.l = state.l;
			(*data).report.r = state.r;
			(*data).report.z = state.z;

			(*data).report.cxAxis = state.cxAxis;
			(*data).report.cyAxis = state.cyAxis;
			(*data).report.left = state.left;
			(*data).report.right = state.right;
			(*data).report.xAxis = state.xAxis;
			(*data).report.yAxis = state.yAxis;
		}
};
