#include "system.hpp"
#include <Nintendo.h>

class InputSystem: public System {
	using System::System;

	private:
		Gamecube_Report_t state, prevState;
		const char* buttons[12] = { "A", "B", "X", "Y", "Z", "L", "R", "START", "DDOWN", "DLEFT", "DRIGHT", "DUP" };

	public:
		void init() {
			// Zero out the controller
			ctx->data.origin = ctx->controller.getOrigin();
		}

		void update() {
			ctx->begin();

			// Get controller data
			state = ctx->controller.getReport();

			ctx->pressedButtons.clear();
			// ctx->releasedButtons.clear();

			for (auto &button : buttons) {
				uint8_t value = ctx->get(button, state);
				uint8_t prevValue = ctx->get(button, prevState);
				if (value == 1 && prevValue == 0) {
					ctx->pressedButtons.push_back(button);
				// } else if (value == 0 && prevValue == 1) {
				// 	ctx->releasedButtons.push_back(button);
				}
			}

			// // A
			// if (state.a == 1 && prevState.a == 0) ctx->pressedButtons.push_back("A");
			// else if (state.a == 0 && prevState.a == 1) ctx->releasedButtons.push_back("A");
			// // B
			// if (state.b == 1 && prevState.b == 0) ctx->pressedButtons.push_back("B");
			// else if (state.b == 0 && prevState.b == 1) ctx->releasedButtons.push_back("B");
			// // X
			// if (state.x == 1 && prevState.x == 0) ctx->pressedButtons.push_back("X");
			// else if (state.x == 0 && prevState.x == 1) ctx->releasedButtons.push_back("X");
			// // Y
			// if (state.y == 1 && prevState.y == 0) ctx->pressedButtons.push_back("Y");
			// else if (state.y == 0 && prevState.y == 1) ctx->releasedButtons.push_back("Y");
			// // Z
			// if (state.z == 1 && prevState.z == 0) ctx->pressedButtons.push_back("Z");
			// else if (state.z == 0 && prevState.z == 1) ctx->releasedButtons.push_back("Z");
			// // L
			// if (state.l == 1 && prevState.l == 0) ctx->pressedButtons.push_back("L");
			// else if (state.l == 0 && prevState.l == 1) ctx->releasedButtons.push_back("L");
			// // R
			// if (state.r == 1 && prevState.r == 0) ctx->pressedButtons.push_back("R");
			// else if (state.r == 0 && prevState.r == 1) ctx->releasedButtons.push_back("R");
			// // START
			// if (state.start == 1 && prevState.start == 0) ctx->pressedButtons.push_back("START");
			// else if (state.start == 0 && prevState.start == 1) ctx->releasedButtons.push_back("START");
			// // DDOWN
			// if (state.ddown == 1 && prevState.ddown == 0) ctx->pressedButtons.push_back("DDOWN");
			// else if (state.ddown == 0 && prevState.ddown == 1) ctx->releasedButtons.push_back("DDOWN");
			// // DLEFT
			// if (state.dleft == 1 && prevState.dleft == 0) ctx->pressedButtons.push_back("DLEFT");
			// else if (state.dleft == 0 && prevState.dleft == 1) ctx->releasedButtons.push_back("DLEFT");
			// // DRIGHT
			// if (state.dright == 1 && prevState.dright == 0) ctx->pressedButtons.push_back("DRIGHT");
			// else if (state.dright == 0 && prevState.dright == 1) ctx->releasedButtons.push_back("DRIGHT");
			// // DUP
			// if (state.dup == 1 && prevState.dup == 0) ctx->pressedButtons.push_back("DUP");
			// else if (state.dup == 0 && prevState.dup == 1) ctx->releasedButtons.push_back("DUP");

			prevState = state;
			ctx->setState(state);

			ctx->end();
		}
};
