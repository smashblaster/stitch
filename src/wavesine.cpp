#include "modules/backdash.cpp"
#include "modules/debug.cpp"
#include "modules/input.cpp"
#include "modules/meta.cpp"
#include "modules/module.cpp"
#include "modules/remap.cpp"
#include <Nintendo.h>
#include <vector>

#ifndef WAVESINE
#define WAVESINE

class WaveSine {
	private:
		std::vector<Module*> modules;
		std::vector<Module*>::iterator module;

		CGamecubeConsole console;
		CGamecubeController controller;

		// TODO: read from config
		bool rumbleSetting = false;

	public:
		Context ctx;

		WaveSine(int cons, int cont): console(cons), controller(cont) {
			modules.push_back(new Input());
			modules.push_back(new Meta());
			modules.push_back(new Remap());
			modules.push_back(new Debug());
			modules.push_back(new Backdash());
		}

		void init() {
			for (auto &module : modules) {
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
			ctx.data = defaultGamecubeData;
			ctx.state = controller.getReport();
			memcpy(&ctx.data.report, &ctx.state, sizeof(ctx.state));

			if (!ctx.init) init();

			for (auto &module : modules) {
				module->update(&ctx, controller);
			}

			// Sends the data to the console
			if (!console.write(ctx.data)) {
				ctx.init = false;
				delay(100);
				return;
			}

			controller.setRumble((rumbleSetting && ctx.data.status.rumble) || ctx.rumble);
		};
};

#endif
