#include "system.cpp"
#include <Nintendo.h>

class Input: public System {
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
				value = ctx->get(button, ctx->state);
				prevValue = ctx->get(button, ctx->prevState);

				if (value == 1 && prevValue == 0) {
					ctx->pressedButtons.push_back(button);
				} else if (value == 0 && prevValue == 1) {
					ctx->releasedButtons.push_back(button);
				}
			}

			ctx->prevState = ctx->state;
		}
};
