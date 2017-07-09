#include "system.hpp"
#include <Nintendo.h>

class InputSystem: public System {
	using System::System;

	private:
		Gamecube_Report_t state, prevState;

		bool started = false;
		const int boot = millis();
		int startup;
		int timer = 2;

	public:
		void init() {
			// Zero out the controller
			ctx->data.origin = ctx->controller.getOrigin();
			ctx->data.report = ctx->controller.getReport();

			// Set a consistent origin.
			ctx->data.origin.inititalData.xAxis = 128;
			ctx->data.origin.inititalData.yAxis = 128;

			startup = millis() - boot;
		}

		void update() {
			if (!started && timer-- == 0) {
				if (startup > 10) ctx->dolphin(true);
				started = true;
			}

			// Get controller data
			state = ctx->controller.getReport();

			ctx->pressedButtons.reset();
			ctx->releasedButtons.reset();

			// A
			if (state.a - prevState.a == 1) ctx->pressedButtons.set(Buttons::A);
			else if (state.a - prevState.a == -1) ctx->releasedButtons.set(Buttons::A);
			// B
			if (state.b - prevState.b == 1) ctx->pressedButtons.set(Buttons::B);
			else if (state.b - prevState.b == -1) ctx->releasedButtons.set(Buttons::B);
			// X
			if (state.x - prevState.x == 1) ctx->pressedButtons.set(Buttons::X);
			else if (state.x - prevState.x == -1) ctx->releasedButtons.set(Buttons::X);
			// Y
			if (state.y - prevState.y == 1) ctx->pressedButtons.set(Buttons::Y);
			else if (state.y - prevState.y == -1) ctx->releasedButtons.set(Buttons::Y);
			// Z
			if (state.z - prevState.z == 1) ctx->pressedButtons.set(Buttons::Z);
			else if (state.z - prevState.z == -1) ctx->releasedButtons.set(Buttons::Z);
			// L
			if (state.l - prevState.l == 1) ctx->pressedButtons.set(Buttons::L);
			else if (state.l - prevState.l == -1) ctx->releasedButtons.set(Buttons::L);
			// R
			if (state.r - prevState.r == 1) ctx->pressedButtons.set(Buttons::R);
			else if (state.r - prevState.r == -1) ctx->releasedButtons.set(Buttons::R);
			// START
			if (state.start - prevState.start == 1) ctx->pressedButtons.set(Buttons::START);
			else if (state.start - prevState.start == -1) ctx->releasedButtons.set(Buttons::START);
			// DDOWN
			if (state.ddown - prevState.ddown == 1) ctx->pressedButtons.set(Buttons::DDOWN);
			else if (state.ddown - prevState.ddown == -1) ctx->releasedButtons.set(Buttons::DDOWN);
			// DLEFT
			if (state.dleft - prevState.dleft == 1) ctx->pressedButtons.set(Buttons::DLEFT);
			else if (state.dleft - prevState.dleft == -1) ctx->releasedButtons.set(Buttons::DLEFT);
			// DRIGHT
			if (state.dright - prevState.dright == 1) ctx->pressedButtons.set(Buttons::DRIGHT);
			else if (state.dright - prevState.dright == -1) ctx->releasedButtons.set(Buttons::DRIGHT);
			// DUP
			if (state.dup - prevState.dup == 1) ctx->pressedButtons.set(Buttons::DUP);
			else if (state.dup - prevState.dup == -1) ctx->releasedButtons.set(Buttons::DUP);

			prevState = state;
			ctx->setState(state);
		}
};
