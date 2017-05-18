#include "system.hpp"
#include <Nintendo.h>

class Input: public System {
	using System::System;

	private:
		std::string buttons[12] = { "A", "B", "START", "X", "Y", "L", "R", "Z", "DDOWN", "DLEFT", "DRIGHT", "DUP" };
		uint8_t value, prevValue;

	public:
		void init() {
			// Zero out the controller
			ctx->data.origin = ctx->controller.getOrigin();
		}

		void update() {
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
