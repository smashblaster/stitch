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
		vector<Module> modules;

		CGamecubeConsole console;
		CGamecubeController controller;

		// TODO: read from config
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

		void init() {
			for (module = modules.begin(); module != modules.end(); ++module) {
				module->init(&ctx, controller);
			}
			ctx.init = true;
		}

		void update() {
			// Just stops the code if no controller is found
			if (!controller.read()) {
				ctx.init = false;
				delay(100);
				return;
			}

			// Gets the data of controller
			ctx.state = controller.getReport();
			ctx.data = defaultGamecubeData;

			if (!ctx.init) init();

			for (module = modules.begin(); module != modules.end(); ++module) {
				module->update(&ctx, controller);
			}

			// Sends the data to the console
			if (!console.write(ctx.data)) {
				delay(100);
				return;
			}

			controller.setRumble((rumbleSetting && ctx.data.status.rumble) || ctx.rumble);
		};
};

#endif
