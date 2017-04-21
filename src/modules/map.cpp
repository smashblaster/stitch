#include "module.cpp"
#include <Nintendo.h>

class Map: public Module {
	private:
		std::string buttons[12] = { "a", "b", "start", "x", "y", "l", "r", "z", "ddown", "dleft", "dright", "dup" };
		uint8_t value, prevValue;

	public:
		void init(Context *ctx, CGamecubeController controller) {
			// Zero the controller out on startup
			ctx->data.origin = controller.getOrigin();
		}

		void update(Context *ctx, CGamecubeController controller) {
			ctx->pressedButtons.clear();
			ctx->releasedButtons.clear();

			for (auto &button : buttons) {
				value = ctx->getButton(button, ctx->state);
				prevValue = ctx->getButton(button, ctx->prevState);

				if (value == 1 && prevValue == 0) {
					ctx->pressedButtons.push_back(button);
				} else if (value == 0 && prevValue == 1) {
					ctx->releasedButtons.push_back(button);
				}

				ctx->setButton(button, value);
			}

			ctx->data.report.cxAxis = ctx->state.cxAxis;
			ctx->data.report.cyAxis = ctx->state.cyAxis;
			ctx->data.report.left = ctx->state.left;
			ctx->data.report.right = ctx->state.right;
			ctx->data.report.xAxis = ctx->state.xAxis;
			ctx->data.report.yAxis = ctx->state.yAxis;

			ctx->prevState = ctx->data.report;
		}
};
