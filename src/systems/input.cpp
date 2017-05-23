#include "system.hpp"
#include <Nintendo.h>

class InputSystem: public System {
	using System::System;

	private:
		const char* buttons[12] = { "A", "B", "X", "Y", "Z", "L", "R", "START", "DDOWN", "DLEFT", "DRIGHT", "DUP" };
		uint8_t value, prevValue;

	public:
		void init() {
			// Zero out the controller
			ctx->data.origin = ctx->controller.getOrigin();
		}

		void update() {
			// Get controller data
			ctx->data.report = ctx->controller.getReport();

			ctx->pressedButtons.clear();
			// ctx->releasedButtons.clear();

			for (auto &button : buttons) {
				value = ctx->get(button, ctx->data.report);
				prevValue = ctx->get(button, ctx->prevState);

				if (value == 1 && prevValue == 0) {
					ctx->pressedButtons.push_back(button);
				} else if (value == 0 && prevValue == 1) {
					// TODO: Add back when actually used for something
					// ctx->releasedButtons.push_back(button);
				}
			}

			ctx->prevState = ctx->data.report;
		}
};
