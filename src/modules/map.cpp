#include "module.cpp"
#include <Nintendo.h>
#include <map>

class Map: public Module {
	private:
		std::string buttons[12] = { "a", "b", "start", "x", "y", "l", "r", "z", "ddown", "dleft", "dright", "dup" };
		std::map<std::string, bool> buttonState;

	public:
		void init(Context *ctx, CGamecubeController controller) {
			// Zero the controller out on startup
			ctx->data.origin = controller.getOrigin();
		}

		void update(Context *ctx, CGamecubeController controller) {
			ctx->pressed.clear();
			ctx->released.clear();

			for (auto &button : buttons) {
				uint8_t value = getButton(ctx, button);
				if (value == 1 && !buttonState[button]) {
					ctx->pressed.insert(button);
				} else if (value == 0 && buttonState[button]) {
					ctx->released.insert(button);
				}

				buttonState[button] = value == 1;
			}

			ctx->data.report.a = ctx->state.a;
			ctx->data.report.b = ctx->state.b;
			ctx->data.report.x = ctx->state.x;
			ctx->data.report.y = ctx->state.y;
			ctx->data.report.start = ctx->state.start;
			ctx->data.report.dleft = ctx->state.dleft;
			ctx->data.report.dright = ctx->state.dright;
			ctx->data.report.ddown = ctx->state.ddown;
			ctx->data.report.dup = ctx->state.dup;
			ctx->data.report.z = ctx->state.z;
			ctx->data.report.l = ctx->state.l;
			ctx->data.report.r = ctx->state.r;
			ctx->data.report.cxAxis = ctx->state.cxAxis;
			ctx->data.report.cyAxis = ctx->state.cyAxis;
			ctx->data.report.left = ctx->state.left;
			ctx->data.report.right = ctx->state.right;
			ctx->data.report.xAxis = ctx->state.xAxis;
			ctx->data.report.yAxis = ctx->state.yAxis;
		}

		uint8_t getButton(Context *ctx, std::string button) {
			if (button == "a") return ctx->state.a;
			if (button == "b") return ctx->state.b;
			if (button == "x") return ctx->state.x;
			if (button == "y") return ctx->state.y;
			if (button == "l") return ctx->state.l;
			if (button == "r") return ctx->state.r;
			if (button == "z") return ctx->state.z;
			if (button == "start") return ctx->state.start;
			if (button == "ddown") return ctx->state.ddown;
			if (button == "dleft") return ctx->state.dleft;
			if (button == "dright") return ctx->state.dright;
			if (button == "dup") return ctx->state.dup;
			return 0;
		}

		void setButton(Context *ctx, std::string button, uint8_t value) {
			if (button == "a") ctx->data.report.a = value;
			if (button == "b") ctx->data.report.b = value;
			if (button == "x") ctx->data.report.x = value;
			if (button == "y") ctx->data.report.y = value;
			if (button == "l") ctx->data.report.l = value;
			if (button == "r") ctx->data.report.r = value;
			if (button == "z") ctx->data.report.z = value;
			if (button == "start") ctx->data.report.start = value;
			if (button == "ddown") ctx->data.report.ddown = value;
			if (button == "dleft") ctx->data.report.dleft = value;
			if (button == "dright") ctx->data.report.dright = value;
			if (button == "dup") ctx->data.report.dup = value;
		}
};
