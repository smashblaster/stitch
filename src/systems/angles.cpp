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

		int cardUp[2] = { 128, 233 };
		int cardDown[2] = { 128, 23 };
		int cardLeft[2] = { 28, 128 };
		int cardRight[2] = { 234, 128 };

		const int cardThreshold = 10;
		const int desiredRadius = 110;
		const int sdThreshold = 6;
		const int wdThreshold = 12;

	public:
		void init() {
			// TODO: remove this temporary workaround once we figure out setting origin on dolphin
			if (ctx->isDolphin) {
				wdAngleLeft = -360 + 198;
				wdAngleLeftRad = wdAngleLeft * M_PI / 180;
				wdAngleRight = -360 + 343.5;
				wdAngleRightRad = wdAngleRight * M_PI / 180;

				sdAngleLeft = -360 + 223;
				sdAngleLeftRad = sdAngleLeft * M_PI / 180;
				sdAngleRight = -360 + 318;
				sdAngleRightRad = sdAngleRight * M_PI / 180;

				cardUp[0] = 131;
				cardUp[1] = 233;
				cardDown[0] = 131;
				cardDown[1] = 24;
				cardLeft[0] = 28;
				cardLeft[1] = 130;
				cardRight[0] = 234;
				cardRight[1] = 130;
			}
		}

		void update() {
			const float angle = getAngle();
			const float radius = getRadius();

			if (90 <= radius) {
				// Shield drop
				if (isNearAngle(angle, sdAngleLeft, sdThreshold)) {
					setAngle(sdAngleLeftRad, desiredRadius);
				} else if (isNearAngle(angle, sdAngleRight + 3, sdThreshold)) {
					setAngle(sdAngleRightRad, desiredRadius);
				}

				// Wavedash
				else if (isNearAngle(angle, wdAngleLeft, wdThreshold)) {
					setAngle(wdAngleLeftRad, desiredRadius);
				} else if (isNearAngle(angle, wdAngleRight, wdThreshold)) {
					setAngle(wdAngleRightRad, desiredRadius);
				}

				// Cardinals
				else if (isNearAngle(angle, 90, cardThreshold)) {
					// UP
					ctx->data.report.xAxis = cardUp[0];
					ctx->data.report.yAxis = cardUp[1];
				} else if (isNearAngle(angle, -90, cardThreshold)) {
					// DOWN
					ctx->data.report.xAxis = cardDown[0];
					ctx->data.report.yAxis = cardDown[1];
				} else if (isNearAngle(angle, 180, cardThreshold) || isNearAngle(angle, -180, cardThreshold)) {
					// LEFT
					ctx->data.report.xAxis = cardLeft[0];
					ctx->data.report.yAxis = cardLeft[1];
				} else if (isNearAngle(angle, 0, cardThreshold)) {
					// RIGHT
					ctx->data.report.xAxis = cardRight[0];
					ctx->data.report.yAxis = cardRight[1];
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
