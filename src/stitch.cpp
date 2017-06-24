#include "config.hpp"
#include "context.hpp"
#include "systems/angles.cpp"
#include "systems/backdash.cpp"
#include "systems/cardinal.cpp"
#include "systems/debug.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include "systems/remap.cpp"
#include <Nintendo.h>
#include <vector>

class Stitch {
	private:
		Context* ctx;
		bool isInit = false;
		const Config* config;
		uint8_t step;

	public:
		Stitch(uint8_t consolePin, uint8_t controllerPin, char json[]) {
			config = new Config(json);
			ctx = new Context(consolePin, controllerPin);

			ctx->inputSystem = new InputSystem("input", ctx, true);
			ctx->metaSystem = new MetaSystem("meta", ctx, true);
			ctx->remapSystem = new RemapSystem("remap", ctx);
			ctx->cardinalSystem = new CardinalSystem("cardinal", ctx);
			ctx->backdashSystem = new BackdashSystem("backdash", ctx);
			ctx->anglesSystem = new AnglesSystem("angles", ctx);
			ctx->debugSystem = new DebugSystem("debug", ctx);
		}

		~Stitch() = default;

		void init() {
			initSystem(ctx->inputSystem);
			initSystem(ctx->metaSystem);
			initSystem(ctx->remapSystem);
			initSystem(ctx->cardinalSystem);
			initSystem(ctx->backdashSystem);
			initSystem(ctx->anglesSystem);
			initSystem(ctx->debugSystem);
			isInit = true;
		}

		void update() {
			// Read from controller
			if (!ctx->controller.read()) {
				// Continue if no controller is found
				isInit = false;
				delay(100);
				return;
			}

			if (!isInit) init();

			updateSystem(ctx->inputSystem);
			updateSystem(ctx->metaSystem);
			updateSystem(ctx->remapSystem);
			updateSystem(ctx->cardinalSystem);
			updateSystem(ctx->backdashSystem);
			updateSystem(ctx->anglesSystem);
			updateSystem(ctx->debugSystem);

			if (ctx->isDolphin) delay(1);

			step = 0;
			while (step < ctx->stepInterval) {
				// Write to console
				if (!ctx->console.write(ctx->data)) {
					isInit = false;
					delay(100);
					return;
				}
				step += 1;
			}

			ctx->controller.setRumble((config->get("rumble") && ctx->data.status.rumble) || ctx->rumble);
		}

		void initSystem(System* system) {
			system->toggle(system->persistent || config->get(system->name));
			if (system->persistent || (system->enabled && ctx->enabled)) system->init();
		}

		void updateSystem(System* system) {
			if (system->persistent || (system->enabled && ctx->enabled)) system->update();
		}
};
