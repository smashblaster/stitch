#include "config.hpp"
#include "context.hpp"
#include "systems/angles.cpp"
#include "systems/backdash.cpp"
#include "systems/debug.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include "systems/remap.cpp"
#include <Nintendo.h>

class Stitch {
	private:
		const Config* config;
		Context* ctx;

	public:
		Stitch(int consolePin, int controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);

			addSystem("angles", new Angles(ctx));
			addSystem("backdash", new Backdash(ctx));
			addSystem("debug", new Debug(ctx));
			addSystem("input", new Input(ctx), true);
			addSystem("meta", new Meta(ctx), true);
			addSystem("remap", new Remap(ctx));
		}

		~Stitch() {}

		void init() {
			config->init();
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
			ctx->data.origin = ctx->controller.getOrigin();
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
