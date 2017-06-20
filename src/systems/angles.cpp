#include "system.hpp"

// TODO: move angle methods to common place

class AnglesSystem: public System {
	using System::System;

	private:
		const float wdAngleLeft = -360 + 198.5;
		const float wdAngleLeftRad = wdAngleLeft * M_PI / 180;
		const float wdAngleRight = -360 + 342;
		const float wdAngleRightRad = wdAngleRight * M_PI / 180;

		const float sdAngleLeft = -360 + 225;
		const float sdAngleLeftRad = sdAngleLeft * M_PI / 180;
		const float sdAngleRight = -360 + 318;
		const float sdAngleRightRad = sdAngleRight * M_PI / 180;

		const uint8_t desiredRadius = 110;
		const uint8_t angleThreshold = 12;

	public:
		void update() {
			float angle = getAngle();
			float radius = getRadius();

			// Wavedash
			if (90 <= radius) {
				// if (98 <= radius && (angle - (wdAngleLeft - angleThreshold)) <= ((wdAngleLeft + angleThreshold) - (wdAngleLeft - angleThreshold))) {
				if (wdAngleLeft - angleThreshold <= angle && angle <= wdAngleLeft + angleThreshold) {
					setAngle(wdAngleLeftRad, desiredRadius);
				// } else if (98 <= radius && (angle - (wdAngleRight - angleThreshold)) <= ((wdAngleRight + angleThreshold) - (wdAngleRight - angleThreshold))) {
				} else if (wdAngleRight - angleThreshold <= angle && angle <= wdAngleRight + angleThreshold) {
					setAngle(wdAngleRightRad, desiredRadius);
				}

				// Shield drop
				if (sdAngleLeft - 4 <= angle && angle <= sdAngleLeft + 4) {
					setAngle(sdAngleLeftRad, desiredRadius);
				} else if ((sdAngleRight + 3) - 4 <= angle && angle <= (sdAngleRight + 3) + 4) {
					setAngle(sdAngleRightRad, desiredRadius);
				}
			}

			// Perfect shield drop
			// setAngle(-134 * M_PI / 180, 75);
		}

		float getAngle() {
			int8_t x = ctx->data.report.xAxis - ctx->gridOffset;
			int8_t y = ctx->data.report.yAxis - ctx->gridOffset;
			return atan2(y, x) * (180.0 / M_PI);
		}

		float getRadius() {
			int8_t x = ctx->data.report.xAxis - ctx->gridOffset;
			int8_t y = ctx->data.report.yAxis - ctx->gridOffset;
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		void setAngle(float angle, uint8_t r) {
			ctx->data.report.xAxis = round(r * cos(angle)) + ctx->gridOffset;
			ctx->data.report.yAxis = round(r * sin(angle)) + ctx->gridOffset;
		}
};
