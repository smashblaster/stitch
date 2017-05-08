#include "system.hpp"

class Angles: public System {
	using System::System;

	// const float angleLeft = -164;
	const float angleLeft = -163.4465;
	const float angleLeftRad = angleLeft * M_PI / 180;
	const float angleRight = -16.5;
	// const float angleRight = -17.4180;
	const float angleRightRad = angleRight * M_PI / 180;
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

			// if (radius >= 98 && (angle - (angleLeft - angleThreshold)) <= ((angleLeft + angleThreshold) - (angleLeft - angleThreshold))) {
			if (radius >= 90 && angleLeft - angleThreshold <= angle && angle <= angleLeft + angleThreshold) {
				// Serial.println("left");
				// ctx->set("xAxis", -98 + gridOffset);
				// ctx->set("yAxis", -31 + gridOffset);
				setAngle(angleLeftRad, desiredRadius);
			// } else if (radius >= 98 && (angle - (angleRight - angleThreshold)) <= ((angleRight + angleThreshold) - (angleRight - angleThreshold))) {
			} else if (radius >= 90 && angleRight - angleThreshold <= angle && angle <= angleRight + angleThreshold) {
				// Serial.println("right");
				// ctx->set("xAxis", 102 + gridOffset);
				// ctx->set("yAxis", -33 + gridOffset);
				setAngle(angleRightRad, desiredRadius);
			}
		}

		float getAngle() {
			int x = ctx->state.xAxis - gridOffset;
			int y = ctx->state.yAxis - gridOffset;
			return atan2(y, x) * (180.0 / M_PI);
		}

		float getRadius() {
			int x = ctx->state.xAxis - gridOffset;
			int y = ctx->state.yAxis - gridOffset;
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		void setAngle(float angle, int r) {
			ctx->set("xAxis", round(r * cos(angle)) + gridOffset);
			ctx->set("yAxis", round(r * sin(angle)) + gridOffset);
		}
};
