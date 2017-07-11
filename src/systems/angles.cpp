#include "system.hpp"

// TODO: move angle methods to common place

class AnglesSystem: public System {
	using System::System;

	private:
		float wdAngleLeft = -360 + 197.5;
		float wdAngleLeftRad = wdAngleLeft * M_PI / 180;
		float wdAngleRight = -360 + 342;
		float wdAngleRightRad = wdAngleRight * M_PI / 180;

		float sdAngleLeft = -360 + 223;
		float sdAngleLeftRad = sdAngleLeft * M_PI / 180;
		float sdAngleRight = -360 + 316;
		float sdAngleRightRad = sdAngleRight * M_PI / 180;

		const int desiredRadius = 110;
		const int angleThreshold = 12;

	public:
		void init() {
			// TODO: remove this temporary workaround once we figure out setting origin on dolphin
			if (ctx->isDolphin) {
				wdAngleLeft = -360 + 199;
				wdAngleLeftRad = wdAngleLeft * M_PI / 180;
				wdAngleRight = -360 + 341.75;
				wdAngleRightRad = wdAngleRight * M_PI / 180;

				sdAngleLeft = -360 + 225;
				sdAngleLeftRad = sdAngleLeft * M_PI / 180;
				sdAngleRight = -360 + 318;
				sdAngleRightRad = sdAngleRight * M_PI / 180;
			}
		}

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
			int x = ctx->data.report.xAxis - ctx->gridOffset;
			int y = ctx->data.report.yAxis - ctx->gridOffset;
			return atan2(y, x) * (180.0 / M_PI);
		}

		float getRadius() {
			int x = ctx->data.report.xAxis - ctx->gridOffset;
			int y = ctx->data.report.yAxis - ctx->gridOffset;
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		void setAngle(float angle, int r) {
			ctx->data.report.xAxis = round(r * cos(angle)) + ctx->gridOffset;
			ctx->data.report.yAxis = round(r * sin(angle)) + ctx->gridOffset;
		}
};
