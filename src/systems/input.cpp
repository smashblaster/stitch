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

			ctx->pressedButtons.reset();
			ctx->releasedButtons.reset();

			// A
			if (state.a - prevState.a == 1) ctx->pressedButtons.set(Inputs::A);
			else if (state.a - prevState.a == -1) ctx->releasedButtons.set(Inputs::A);
			// B
			if (state.b - prevState.b == 1) ctx->pressedButtons.set(Inputs::B);
			else if (state.b - prevState.b == -1) ctx->releasedButtons.set(Inputs::B);
			// X
			if (state.x - prevState.x == 1) ctx->pressedButtons.set(Inputs::X);
			else if (state.x - prevState.x == -1) ctx->releasedButtons.set(Inputs::X);
			// Y
			if (state.y - prevState.y == 1) ctx->pressedButtons.set(Inputs::Y);
			else if (state.y - prevState.y == -1) ctx->releasedButtons.set(Inputs::Y);
			// Z
			if (state.z - prevState.z == 1) ctx->pressedButtons.set(Inputs::Z);
			else if (state.z - prevState.z == -1) ctx->releasedButtons.set(Inputs::Z);
			// L
			if (state.l - prevState.l == 1) ctx->pressedButtons.set(Inputs::L);
			else if (state.l - prevState.l == -1) ctx->releasedButtons.set(Inputs::L);
			// R
			if (state.r - prevState.r == 1) ctx->pressedButtons.set(Inputs::R);
			else if (state.r - prevState.r == -1) ctx->releasedButtons.set(Inputs::R);
			// START
			if (state.start - prevState.start == 1) ctx->pressedButtons.set(Inputs::START);
			else if (state.start - prevState.start == -1) ctx->releasedButtons.set(Inputs::START);
			// DDOWN
			if (state.ddown - prevState.ddown == 1) ctx->pressedButtons.set(Inputs::DDOWN);
			else if (state.ddown - prevState.ddown == -1) ctx->releasedButtons.set(Inputs::DDOWN);
			// DLEFT
			if (state.dleft - prevState.dleft == 1) ctx->pressedButtons.set(Inputs::DLEFT);
			else if (state.dleft - prevState.dleft == -1) ctx->releasedButtons.set(Inputs::DLEFT);
			// DRIGHT
			if (state.dright - prevState.dright == 1) ctx->pressedButtons.set(Inputs::DRIGHT);
			else if (state.dright - prevState.dright == -1) ctx->releasedButtons.set(Inputs::DRIGHT);
			// DUP
			if (state.dup - prevState.dup == 1) ctx->pressedButtons.set(Inputs::DUP);
			else if (state.dup - prevState.dup == -1) ctx->releasedButtons.set(Inputs::DUP);

			prevState = state;
			ctx->setState(state);
		}
};
