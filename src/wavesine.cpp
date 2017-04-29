#include "config.cpp"
#include "context.hpp"
#include "systems/backdash.cpp"
#include "systems/debug.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include "systems/remap.cpp"
#include <Nintendo.h>
#include <vector>

#ifndef WAVESINE
#define WAVESINE

class WaveSine {
	private:
		const Config* config;
		Context* ctx;

	public:
		WaveSine(int consolePin, int controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);

			addSystem("input", new Input(ctx), true);
			addSystem("meta", new Meta(ctx), true);
			addSystem("remap", new Remap(ctx));
			addSystem("debug", new Debug(ctx));
			addSystem("backdash", new Backdash(ctx));
		}

		~WaveSine() {}

		void init() {
			for (auto &system : ctx->systems) {
				if (system->persistent || (system->enabled && ctx->enabled)) system->init();
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

			for (auto &system : ctx->systems) {
				if (system->persistent || (system->enabled && ctx->enabled)) system->update();
			}

			// Sends the data to the console
			if (!ctx->console.write(ctx->data)) {
				ctx->init = false;
				delay(100);
				return;
			}

			ctx->controller.setRumble((config->get("rumble") && ctx->data.status.rumble) || ctx->rumble);
		}

		void addSystem(char* name, System* system, bool persistent = false) {
			ctx->addSystem(name, system, persistent, config->get(name));
		}
};

#endif
