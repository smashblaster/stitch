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
				uint8_t value = ctx->getButton(button);
				if (value == 1 && !buttonState[button]) {
					ctx->pressed.insert(button);
				} else if (value == 0 && buttonState[button]) {
					ctx->released.insert(button);
				}

				ctx->setButton(button, value);
				buttonState[button] = value == 1;
			}
		}
};
