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
		int step;

	public:
		Stitch(int consolePin, int controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);

			addSystem("input", new InputSystem(ctx), true);
			addSystem("meta", new MetaSystem(ctx), true);

			addSystem("remap", new RemapSystem(ctx));
			addSystem("backdash", new BackdashSystem(ctx));
			addSystem("angles", new AnglesSystem(ctx));
			addSystem("debug", new DebugSystem(ctx));
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

			if (!ctx->init) init();

			for (auto &system : ctx->systems) {
				if (system->persistent || (system->enabled && ctx->enabled)) system->update();
			}

			delay(1);

			step = 0;
			while (step < ctx->stepInterval) {
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
