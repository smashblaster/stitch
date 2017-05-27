#include "../buttons.cpp"
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
			// ctx->releasedButtons.clear();

			// A
			if (state.a - prevState.a == 1) ctx->pressedButtons.push_back(Buttons::A);
			// else if (state.a - prevState.a == -1) ctx->releasedButtons.push_back(Buttons::A);
			// B
			if (state.b - prevState.b == 1) ctx->pressedButtons.push_back(Buttons::B);
			// else if (state.b - prevState.b == -1) ctx->releasedButtons.push_back(Buttons::B);
			// X
			if (state.x - prevState.x == 1) ctx->pressedButtons.push_back(Buttons::X);
			// else if (state.x - prevState.x == -1) ctx->releasedButtons.push_back(Buttons::X);
			// Y
			if (state.y - prevState.y == 1) ctx->pressedButtons.push_back(Buttons::Y);
			// else if (state.y - prevState.y == -1) ctx->releasedButtons.push_back(Buttons::Y);
			// Z
			if (state.z - prevState.z == 1) ctx->pressedButtons.push_back(Buttons::Z);
			// else if (state.z - prevState.z == -1) ctx->releasedButtons.push_back(Buttons::Z);
			// L
			if (state.l - prevState.l == 1) ctx->pressedButtons.push_back(Buttons::L);
			// else if (state.l - prevState.l == -1) ctx->releasedButtons.push_back(Buttons::L);
			// R
			if (state.r - prevState.r == 1) ctx->pressedButtons.push_back(Buttons::R);
			// else if (state.r - prevState.r == -1) ctx->releasedButtons.push_back(Buttons::R);
			// START
			if (state.start - prevState.start == 1) ctx->pressedButtons.push_back(Buttons::START);
			// else if (state.start - prevState.start == -1) ctx->releasedButtons.push_back(Buttons::START);
			// DDOWN
			if (state.ddown - prevState.ddown == 1) ctx->pressedButtons.push_back(Buttons::DDOWN);
			// else if (state.ddown - prevState.ddown == -1) ctx->releasedButtons.push_back(Buttons::DDOWN);
			// DLEFT
			if (state.dleft - prevState.dleft == 1) ctx->pressedButtons.push_back(Buttons::DLEFT);
			// else if (state.dleft - prevState.dleft == -1) ctx->releasedButtons.push_back(Buttons::DLEFT);
			// DRIGHT
			if (state.dright - prevState.dright == 1) ctx->pressedButtons.push_back(Buttons::DRIGHT);
			// else if (state.dright - prevState.dright == -1) ctx->releasedButtons.push_back(Buttons::DRIGHT);
			// DUP
			if (state.dup - prevState.dup == 1) ctx->pressedButtons.push_back(Buttons::DUP);
			// else if (state.dup - prevState.dup == -1) ctx->releasedButtons.push_back(Buttons::DUP);

			prevState = state;
			ctx->setState(state);
		}
};
