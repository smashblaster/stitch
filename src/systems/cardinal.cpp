#include "system.hpp"

class CardinalSystem: public System {
	using System::System;

	private:
		const int threshold = 8;

	public:
		void update() {
			if (getRadius() < 100) return false;
			int x = ctx->data.report.xAxis - ctx->gridOffset;
			int y = ctx->data.report.yAxis - ctx->gridOffset;

			if (abs(x) <= threshold) {
				ctx->data.report.xAxis = 131;
				ctx->data.report.yAxis = (y < 0) ? 0 : 255;
			}
			if (abs(y) <= threshold) {
				ctx->data.report.xAxis = (x < 0) ? 0 : 255;
				ctx->data.report.yAxis = 129;
			}
		}

		float getRadius() {
			int x = ctx->data.report.xAxis - ctx->gridOffset;
			int y = ctx->data.report.yAxis - ctx->gridOffset;
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		// TODO: move to common place
		bool isCardinal() {
			if (getRadius() < 100) return false;
			int x = ctx->data.report.xAxis - ctx->gridOffset;
			int y = ctx->data.report.yAxis - ctx->gridOffset;
			return (abs(x) <= threshold || abs(y) <= threshold);
		}
};
