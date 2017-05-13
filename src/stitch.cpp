#include "config.hpp"
#include "context.hpp"
#include "systems/angles.cpp"
#include "systems/backdash.cpp"
#include "systems/debug.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include "systems/remap.cpp"
#include <Nintendo.h>
#include <vector>

class Stitch {
	private:
		Context* ctx;
		const Config* config;
		const int stepInterval = 1;

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
			for (auto &system : ctx->systems) {
				if (system->persistent || (system->enabled && ctx->enabled)) system->init();
			}
			ctx->init = true;
		}

		void update() {
			// Read from controller
			if (!ctx->controller.read()) {
				// Continue if no controller is found
				ctx->init = false;
				delay(100);
				return;
			}

			// Get controller data
			ctx->data = defaultGamecubeData;
			ctx->data.origin = ctx->controller.getOrigin();
			ctx->state = ctx->controller.getReport();
			memcpy(&ctx->data.report, &ctx->state, sizeof(ctx->state));

			if (!ctx->init) init();

			for (auto &system : ctx->systems) {
				if (system->persistent || (system->enabled && ctx->enabled)) system->update();
			}

			int step = 0;
			while (step < stepInterval) {
				// Write to console
				if (!ctx->console.write(ctx->data)) {
					ctx->init = false;
					delay(100);
					return;
				}
				step += 1;
			}

			ctx->controller.setRumble((config->get("rumble") && ctx->data.status.rumble) || ctx->rumble);
		}

		void addSystem(char* name, System* system, bool persistent = false) {
			ctx->addSystem(name, system, persistent, config->get(name));
		}
};
