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
			// Get controller data
			state = ctx->controller.getReport();

			ctx->pressedButtons.clear();
			ctx->releasedButtons.clear();

			// A
			if (state.a - prevState.a == 1) ctx->pressedButtons.push_back(Inputs::A);
			else if (state.a - prevState.a == -1) ctx->releasedButtons.push_back(Inputs::A);
			// B
			if (state.b - prevState.b == 1) ctx->pressedButtons.push_back(Inputs::B);
			else if (state.b - prevState.b == -1) ctx->releasedButtons.push_back(Inputs::B);
			// X
			if (state.x - prevState.x == 1) ctx->pressedButtons.push_back(Inputs::X);
			else if (state.x - prevState.x == -1) ctx->releasedButtons.push_back(Inputs::X);
			// Y
			if (state.y - prevState.y == 1) ctx->pressedButtons.push_back(Inputs::Y);
			else if (state.y - prevState.y == -1) ctx->releasedButtons.push_back(Inputs::Y);
			// Z
			if (state.z - prevState.z == 1) ctx->pressedButtons.push_back(Inputs::Z);
			else if (state.z - prevState.z == -1) ctx->releasedButtons.push_back(Inputs::Z);
			// L
			if (state.l - prevState.l == 1) ctx->pressedButtons.push_back(Inputs::L);
			else if (state.l - prevState.l == -1) ctx->releasedButtons.push_back(Inputs::L);
			// R
			if (state.r - prevState.r == 1) ctx->pressedButtons.push_back(Inputs::R);
			else if (state.r - prevState.r == -1) ctx->releasedButtons.push_back(Inputs::R);
			// START
			if (state.start - prevState.start == 1) ctx->pressedButtons.push_back(Inputs::START);
			else if (state.start - prevState.start == -1) ctx->releasedButtons.push_back(Inputs::START);
			// DDOWN
			if (state.ddown - prevState.ddown == 1) ctx->pressedButtons.push_back(Inputs::DDOWN);
			else if (state.ddown - prevState.ddown == -1) ctx->releasedButtons.push_back(Inputs::DDOWN);
			// DLEFT
			if (state.dleft - prevState.dleft == 1) ctx->pressedButtons.push_back(Inputs::DLEFT);
			else if (state.dleft - prevState.dleft == -1) ctx->releasedButtons.push_back(Inputs::DLEFT);
			// DRIGHT
			if (state.dright - prevState.dright == 1) ctx->pressedButtons.push_back(Inputs::DRIGHT);
			else if (state.dright - prevState.dright == -1) ctx->releasedButtons.push_back(Inputs::DRIGHT);
			// DUP
			if (state.dup - prevState.dup == 1) ctx->pressedButtons.push_back(Inputs::DUP);
			else if (state.dup - prevState.dup == -1) ctx->releasedButtons.push_back(Inputs::DUP);

			prevState = state;
			ctx->setState(state);
		}
};
