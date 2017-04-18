#include "modules/backdasher.cpp"
#include "modules/debug.cpp"
#include "modules/mapper.cpp"
#include "modules/meta.cpp"
#include "modules/module.cpp"
#include "modules/remapper.cpp"
#include <Nintendo.h>
#include <vector>
using namespace std;

#ifndef WAVESINE
#define WAVESINE

class WaveSine {
	private:
		vector<Module>::iterator module;

		CGamecubeConsole console;
		CGamecubeController controller;

		vector<Module> modules;

		bool rumbleSetting = false;

	public:
		Context ctx;

		WaveSine(int cons, int cont): console(cons), controller(cont) {
			modules.push_back(Mapper());
			modules.push_back(Meta());
			modules.push_back(Debug());
			modules.push_back(Remapper());
			modules.push_back(Backdasher());
		}

		void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
			for (module = modules.begin(); module != modules.end(); ++module) {
				module->init(state, data, controller);
			}
		}

		void update() {
			// Just stops the code if no controller is found
			if (!controller.read()) {
				ctx.init = false;
				delay(100);
				return;
			}

			// Gets the data of controller
			Gamecube_Report_t state = controller.getReport();
			Gamecube_Data_t data = defaultGamecubeData;

			if (!ctx.init) {
				init(state, &data);
				ctx.init = true;
			}

			for (module = modules.begin(); module != modules.end(); ++module) {
				module->update(&ctx, state, &data, controller);
			}

			// Sends the data to the console
			if (!console.write(data)) {
				delay(100);
				return;
			}

			// controller.setRumble((rumbleSetting && data.status.rumble) || meta.rumble);
		};
};

#endif
