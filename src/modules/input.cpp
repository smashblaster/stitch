#include "module.cpp"
#include <Nintendo.h>

class Input: public Module {
	private:
		std::string buttons[12] = { "a", "b", "start", "x", "y", "l", "r", "z", "ddown", "dleft", "dright", "dup" };
		uint8_t value, prevValue;

	public:
		std::string const name() { return "input"; }

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
			}

			ctx->prevState = ctx->state;
		}
};
