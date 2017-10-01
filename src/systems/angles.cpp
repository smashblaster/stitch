#include "system.hpp"

// TODO: move angle methods to common place

#define isNearAngle(angle, target, threshold) ((target) - (threshold) <= (angle) && (angle) <= (target) + (threshold))

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

		const int cardinalThreshold = 5;
		const int desiredRadius = 110;
		const int sdThreshold = 4;
		const int wdThreshold = 12;

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
			const float angle = getAngle();
			const float radius = getRadius();

			if (90 <= radius) {
				// Wavedash
				if (isNearAngle(angle, wdAngleLeft, wdThreshold)) {
					setAngle(wdAngleLeftRad, desiredRadius);
				} else if (isNearAngle(angle, wdAngleRight, wdThreshold)) {
					setAngle(wdAngleRightRad, desiredRadius);
				}

				// Shield drop
				if (isNearAngle(angle, sdAngleLeft, sdThreshold)) {
					setAngle(sdAngleLeftRad, desiredRadius);
				} else if (isNearAngle(angle, sdAngleRight + 3, sdThreshold)) {
					setAngle(sdAngleRightRad, desiredRadius);
				}

				// Cardinals
				if (isNearAngle(angle, 90, cardinalThreshold)) {
					// UP
					ctx->data.report.xAxis = 128;
					ctx->data.report.yAxis = 233;
				} else if (isNearAngle(angle, -90, cardinalThreshold)) {
					// DOWN
					ctx->data.report.xAxis = 128;
					ctx->data.report.yAxis = 23;
				} else if (isNearAngle(angle, 180, cardinalThreshold) || isNearAngle(angle, -180, cardinalThreshold)) {
					// LEFT
					ctx->data.report.xAxis = 28;
					ctx->data.report.yAxis = 128;
				} else if (isNearAngle(angle, 0, cardinalThreshold)) {
					// RIGHT
					ctx->data.report.xAxis = 234;
					ctx->data.report.yAxis = 128;
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
