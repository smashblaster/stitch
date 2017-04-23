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
			addSystem("input", new Input());
			addSystem("meta", new Meta());
			addSystem("remap", new Remap());
			addSystem("debug", new Debug());
			addSystem("backdash", new Backdash());
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

		void addSystem(std::string name, Module* module) {
			module->name = name;
			modules.push_back(module);
		};
};

#endif
