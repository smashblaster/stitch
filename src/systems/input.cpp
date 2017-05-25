#include "system.hpp"
#include <Nintendo.h>

class InputSystem: public System {
	using System::System;

	private:
		Gamecube_Report_t state, prevState;

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

			// A
			if (state.a - prevState.a == 1) ctx->pressedButtons.push_back("A");
			// else if (state.a - prevState.a == -1) ctx->releasedButtons.push_back("A");
			// B
			if (state.b - prevState.b == 1) ctx->pressedButtons.push_back("B");
			// else if (state.b - prevState.b == -1) ctx->releasedButtons.push_back("B");
			// X
			if (state.x - prevState.x == 1) ctx->pressedButtons.push_back("X");
			// else if (state.x - prevState.x == -1) ctx->releasedButtons.push_back("X");
			// Y
			if (state.y - prevState.y == 1) ctx->pressedButtons.push_back("Y");
			// else if (state.y - prevState.y == -1) ctx->releasedButtons.push_back("Y");
			// Z
			if (state.z - prevState.z == 1) ctx->pressedButtons.push_back("Z");
			// else if (state.z - prevState.z == -1) ctx->releasedButtons.push_back("Z");
			// L
			if (state.l - prevState.l == 1) ctx->pressedButtons.push_back("L");
			// else if (state.l - prevState.l == -1) ctx->releasedButtons.push_back("L");
			// R
			if (state.r - prevState.r == 1) ctx->pressedButtons.push_back("R");
			// else if (state.r - prevState.r == -1) ctx->releasedButtons.push_back("R");
			// START
			if (state.start - prevState.start == 1) ctx->pressedButtons.push_back("START");
			// else if (state.start - prevState.start == -1) ctx->releasedButtons.push_back("START");
			// DDOWN
			if (state.ddown - prevState.ddown == 1) ctx->pressedButtons.push_back("DDOWN");
			// else if (state.ddown - prevState.ddown == -1) ctx->releasedButtons.push_back("DDOWN");
			// DLEFT
			if (state.dleft - prevState.dleft == 1) ctx->pressedButtons.push_back("DLEFT");
			// else if (state.dleft - prevState.dleft == -1) ctx->releasedButtons.push_back("DLEFT");
			// DRIGHT
			if (state.dright - prevState.dright == 1) ctx->pressedButtons.push_back("DRIGHT");
			// else if (state.dright - prevState.dright == -1) ctx->releasedButtons.push_back("DRIGHT");
			// DUP
			if (state.dup - prevState.dup == 1) ctx->pressedButtons.push_back("DUP");
			// else if (state.dup - prevState.dup == -1) ctx->releasedButtons.push_back("DUP");

			prevState = state;
			ctx->setState(state);

			ctx->end();
		}
};
