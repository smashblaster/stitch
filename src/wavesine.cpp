#include "systems/backdash.cpp"
#include "systems/debug.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include "systems/remap.cpp"
#include "systems/system.cpp"
#include <Nintendo.h>
#include <vector>

#ifndef WAVESINE
#define WAVESINE

class WaveSine {
	private:
		std::vector<System*> systems;
		std::vector<System*>::iterator system;

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
			for (auto &system : systems) {
				if (system->enabled) system->init(&ctx, controller);
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

			for (auto &system : systems) {
				if (system->enabled) system->update(&ctx, controller);
			}

			// Sends the data to the console
			if (!console.write(ctx.data)) {
				ctx.init = false;
				delay(100);
				return;
			}

			controller.setRumble((rumbleSetting && ctx.data.status.rumble) || ctx.rumble);
		};

		void addSystem(std::string name, System* system) {
			system->name = name;
			systems.push_back(system);
		};

		void enableSystem(std::string name) { toggleSystem(name, true); };
		void disableSystem(std::string name) { toggleSystem(name, false); };

		void toggleSystem(std::string name) {
			for (auto &system : systems) {
				if (system->name == name) {
					toggleSystem(system, !system->enabled);
					break;
				}
			}
		};

		void toggleSystem(std::string name, bool value) {
			for (auto &system : systems) {
				if (system->name == name) {
					toggleSystem(system, value);
					break;
				}
			}
		};

		void toggleSystem(System* system) { system->enabled = !system->enabled; };
		void toggleSystem(System* system, bool value) { system->enabled = value; };
};

#endif
