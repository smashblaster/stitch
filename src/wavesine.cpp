#include "config.cpp"
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
		Config* config;
		Context* ctx;
		std::vector<System*> systems;

	public:
		WaveSine(int consolePin, int controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);

			addSystem("input", new Input(), true, true);
			addSystem("meta", new Meta(), true, true);
			addSystem("remap", new Remap());
			addSystem("debug", new Debug());
			addSystem("backdash", new Backdash());

			for (auto &system : systems) {
				if (!system->persistent) system->toggle(config->settings->get(system->name));
			}
		}

		~WaveSine() {}

		void init() {
			for (auto &system : systems) {
				if (system->enabled && (ctx->enabled || system->persistent)) system->init(ctx);
			}

			ctx->init = true;
		}

		void update() {
			// Just stops the code if no controller is found
			if (!ctx->controller.read()) {
				ctx->init = false;
				delay(100);
				return;
			}

			// Gets the data of controller
			ctx->data = defaultGamecubeData;
			ctx->state = ctx->controller.getReport();
			memcpy(&ctx->data.report, &ctx->state, sizeof(ctx->state));

			if (!ctx->init) init();

			for (auto &system : systems) {
				if (system->enabled && (ctx->enabled || system->persistent)) system->update(ctx);
			}

			// Sends the data to the console
			if (!ctx->console.write(ctx->data)) {
				ctx->init = false;
				delay(100);
				return;
			}

			ctx->controller.setRumble((config->settings->get("rumble") && ctx->data.status.rumble) || ctx->rumble);
		};

		System* getSystem(std::string name) {
			for (auto &system : systems) {
				if (system->name == name) return system;
			}
		};

		void addSystem(std::string name, System* system, bool enabled = true, bool persistent = false) {
			system->name = name;
			system->toggle(enabled);
			system->setPersistent(persistent);
			systems.push_back(system);
		};

		void enableSystem(std::string name) { toggleSystem(name, true); };
		void disableSystem(std::string name) { toggleSystem(name, false); };

		void toggleSystem(std::string name) {
			System* system = getSystem(name);
			toggleSystem(system, !system->enabled);
		};

		void toggleSystem(std::string name, bool value) {
			System* system = getSystem(name);
			toggleSystem(system, value);
		};

		void toggleSystem(System* system) { system->enabled = !system->enabled; };
		void toggleSystem(System* system, bool value) { system->enabled = value; };
};

#endif
