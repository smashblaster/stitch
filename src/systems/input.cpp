#include "system.hpp"

class InputSystem: public System {
	using System::System;

	public:
		void init() {
			// Zero out the controller
			ctx->data.origin = ctx->controller.getOrigin();
		}

		void update() {
			// Get controller data
			ctx->data.report = ctx->controller.getReport();

			ctx->pressedButtons.clear();
			ctx->releasedButtons.clear();

			// A
			if (ctx->data.report.a == 1 && ctx->prevState.a == 0) ctx->pressedButtons.push_back("A");
			else if (ctx->data.report.a == 0 && ctx->prevState.a == 1) ctx->releasedButtons.push_back("A");
			// B
			if (ctx->data.report.b == 1 && ctx->prevState.b == 0) ctx->pressedButtons.push_back("B");
			else if (ctx->data.report.b == 0 && ctx->prevState.b == 1) ctx->releasedButtons.push_back("B");
			// X
			if (ctx->data.report.x == 1 && ctx->prevState.x == 0) ctx->pressedButtons.push_back("X");
			else if (ctx->data.report.x == 0 && ctx->prevState.x == 1) ctx->releasedButtons.push_back("X");
			// Y
			if (ctx->data.report.y == 1 && ctx->prevState.y == 0) ctx->pressedButtons.push_back("Y");
			else if (ctx->data.report.y == 0 && ctx->prevState.y == 1) ctx->releasedButtons.push_back("Y");
			// Z
			if (ctx->data.report.z == 1 && ctx->prevState.z == 0) ctx->pressedButtons.push_back("Z");
			else if (ctx->data.report.z == 0 && ctx->prevState.z == 1) ctx->releasedButtons.push_back("Z");
			// L
			if (ctx->data.report.l == 1 && ctx->prevState.l == 0) ctx->pressedButtons.push_back("L");
			else if (ctx->data.report.l == 0 && ctx->prevState.l == 1) ctx->releasedButtons.push_back("L");
			// R
			if (ctx->data.report.r == 1 && ctx->prevState.r == 0) ctx->pressedButtons.push_back("R");
			else if (ctx->data.report.r == 0 && ctx->prevState.r == 1) ctx->releasedButtons.push_back("R");
			// START
			if (ctx->data.report.start == 1 && ctx->prevState.start == 0) ctx->pressedButtons.push_back("START");
			else if (ctx->data.report.start == 0 && ctx->prevState.start == 1) ctx->releasedButtons.push_back("START");
			// DDOWN
			if (ctx->data.report.ddown == 1 && ctx->prevState.ddown == 0) ctx->pressedButtons.push_back("DDOWN");
			else if (ctx->data.report.ddown == 0 && ctx->prevState.ddown == 1) ctx->releasedButtons.push_back("DDOWN");
			// DLEFT
			if (ctx->data.report.dleft == 1 && ctx->prevState.dleft == 0) ctx->pressedButtons.push_back("DLEFT");
			else if (ctx->data.report.dleft == 0 && ctx->prevState.dleft == 1) ctx->releasedButtons.push_back("DLEFT");
			// DRIGHT
			if (ctx->data.report.dright == 1 && ctx->prevState.dright == 0) ctx->pressedButtons.push_back("DRIGHT");
			else if (ctx->data.report.dright == 0 && ctx->prevState.dright == 1) ctx->releasedButtons.push_back("DRIGHT");
			// DUP
			if (ctx->data.report.dup == 1 && ctx->prevState.dup == 0) ctx->pressedButtons.push_back("DUP");
			else if (ctx->data.report.dup == 0 && ctx->prevState.dup == 1) ctx->releasedButtons.push_back("DUP");

			ctx->prevState = ctx->data.report;
		}
};
