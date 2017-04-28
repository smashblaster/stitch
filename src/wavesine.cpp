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
		const Config* config;
		Context* ctx;
		std::vector<System*> systems;

	public:
		WaveSine(int consolePin, int controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);
			memcpy(&ctx->settings, &config->settings, sizeof(config->settings));

			addSystem("input", new Input(ctx), true, true);
			addSystem("meta", new Meta(ctx), true, true);
			addSystem("remap", new Remap(ctx));
			addSystem("debug", new Debug(ctx));
			addSystem("backdash", new Backdash(ctx));

			for (auto &system : systems) {
				bool enabled = system->persistent || config->settings->get(system->name);
				ctx->settings->set(system->name, enabled);
			}
		}

		~WaveSine() {}

		void init() {
			for (auto &system : systems) {
				if (system->persistent || (ctx->settings->get(system->name) && ctx->enabled)) system->init();
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
				if (system->persistent || (ctx->settings->get(system->name) && ctx->enabled)) system->update();
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

		void addSystem(char* name, System* system, bool enabled = true, bool persistent = false) {
			system->name = name;
			ctx->settings->set(name, enabled);
			system->setPersistent(persistent);
			systems.push_back(system);
		};
};

#endif
