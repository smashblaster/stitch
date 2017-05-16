#include "system.hpp"
#include <Nintendo.h>

class Input: public System {
	using System::System;

	private:
		std::string buttons[12] = { "a", "b", "start", "x", "y", "l", "r", "z", "ddown", "dleft", "dright", "dup" };
		uint8_t value, prevValue;
		Gamecube_Origin_t origin;

	public:
		void init() {
			origin = ctx->controller.getOrigin();
			ctx->data = defaultGamecubeData;
		}

		void update() {
			// Zero out the controller
			ctx->data.origin = origin;
			// Get controller data
			ctx->state = ctx->controller.getReport();
			// Copy data
			memcpy(&ctx->data.report, &ctx->state, sizeof(ctx->state));

			ctx->pressedButtons.clear();
			ctx->releasedButtons.clear();

			for (auto &button : buttons) {
				value = ctx->get(button, ctx->state);
				prevValue = ctx->get(button, ctx->prevState);

				if (value == 1 && prevValue == 0) {
					ctx->pressedButtons.push_back(button);
				} else if (value == 0 && prevValue == 1) {
					ctx->releasedButtons.push_back(button);
				}
			}

			ctx->prevState = ctx->state;
		}
};
