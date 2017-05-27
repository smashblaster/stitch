#include "system.hpp"

class AnglesSystem: public System {
	using System::System;

	// const float wdAngleLeft = -163.4465;
	const float wdAngleLeft = -161;
	const float wdAngleLeftRad = wdAngleLeft * M_PI / 180;
	// const float wdAngleRight = -16.5;
	const float wdAngleRight = -17.5;
	const float wdAngleRightRad = wdAngleRight * M_PI / 180;

	const float sdAngleLeft = -135;
	const float sdAngleLeftRad = sdAngleLeft * M_PI / 180;
	const float sdAngleRight = -43;
	const float sdAngleRightRad = sdAngleRight * M_PI / 180;

	const int desiredRadius = 110;
	const int angleThreshold = 12;
	const int gridOffset = 129;
	int i = 0;

	public:
		void init() {
		}

		void update() {
			float angle = getAngle();
			float radius = getRadius();

			// Wavedash
			if (90 <= radius) {
				// if (radius >= 98 && (angle - (wdAngleLeft - angleThreshold)) <= ((wdAngleLeft + angleThreshold) - (wdAngleLeft - angleThreshold))) {
				if (wdAngleLeft - angleThreshold <= angle && angle <= wdAngleLeft + angleThreshold) {
					// Serial.println("left");
					// ctx->set(Inputs::XAXIS, -98 + gridOffset);
					// ctx->set(Inputs::YAXIS, -31 + gridOffset);
					setAngle(wdAngleLeftRad, desiredRadius);
				// } else if (radius >= 98 && (angle - (wdAngleRight - angleThreshold)) <= ((wdAngleRight + angleThreshold) - (wdAngleRight - angleThreshold))) {
				} else if (wdAngleRight - angleThreshold <= angle && angle <= wdAngleRight + angleThreshold) {
					// Serial.println("right");
					// ctx->set(Inputs::XAXIS, 102 + gridOffset);
					// ctx->set(Inputs::YAXIS, -33 + gridOffset);
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
			int x = ctx->data.report.xAxis - gridOffset;
			int y = ctx->data.report.yAxis - gridOffset;
			return atan2(y, x) * (180.0 / M_PI);
		}

		float getRadius() {
			int x = ctx->data.report.xAxis - gridOffset;
			int y = ctx->data.report.yAxis - gridOffset;
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		void setAngle(float angle, int r) {
			ctx->set(Inputs::XAXIS, round(r * cos(angle)) + gridOffset);
			ctx->set(Inputs::YAXIS, round(r * sin(angle)) + gridOffset);
		}
};
