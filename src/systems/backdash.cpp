#include "system.hpp"
#include <Nintendo.h>

class BackdashSystem: public System {
	using System::System;

	private:
		uint8_t center = 128;
		uint8_t dashBuffer = 0;
		uint8_t deadZone = 22;
		// uint8_t smashZone = 97;
		uint8_t smashZone = 64;
		uint8_t xAxis;

	public:
		void init() {
			// Reset x-axis
			center = ctx->data.report.xAxis;
		}

		void update() {
			xAxis = ctx->data.report.xAxis;

			// If the x axis is between these two than set buffer to eight
			if (xAxis > center - deadZone - 1 && xAxis < center + deadZone - 1) {
				dashBuffer = ctx->maxDashBuffer;
			}

			if (xAxis < center - deadZone || xAxis > center + deadZone) {
				// Automatically dashes and skips all buffer if you enter running state
				if (xAxis > center + smashZone || xAxis < center - smashZone) {
					ctx->data.report.xAxis = xAxis;
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
