#include "system.hpp"
#include <Nintendo.h>

class Backdash: public System {
	using System::System;

	private:
		int deadZone = 22;
		int center = 128;
		// int smashZone = 97;
		int smashZone = 64;

		int dashBuffer = 0;
		int maxDashBufferVanilla = 2;
		int maxDashBufferDolphin = 8;
		int maxDashBuffer = maxDashBufferVanilla;

	public:
		void init() {
			// Reset x-axis
			center = ctx->state.xAxis;
		}

		void update() {
			maxDashBuffer = (ctx->isDolphin) ? maxDashBufferDolphin : maxDashBufferVanilla;

			// If the x axis is between these two than set buffer to eight
			if (ctx->state.xAxis > center - deadZone - 1 && ctx->state.xAxis < center + deadZone - 1) {
				dashBuffer = maxDashBuffer;
			}

			if (ctx->state.xAxis < center - deadZone || ctx->state.xAxis > center + deadZone) {
				// Automatically dashes and skips all buffer if you enter running state
				if (ctx->state.xAxis > center + smashZone || ctx->state.xAxis < center - smashZone) {
					ctx->data.report.xAxis = ctx->state.xAxis;
					dashBuffer = 0;
				}
				if (dashBuffer > 0) {
					// Set x-axis to neutral
					ctx->data.report.xAxis = 128;
					dashBuffer = dashBuffer - 1;
				}
			}
		}
};
