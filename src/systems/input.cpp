#include "Arduino.h"
#include "system.hpp"
#include <Nintendo.h>

class InputSystem: public System {
	using System::System;

	public:
		void init() {
			ctx->setOrigin();
		}

		void update() {
			// Set controller data
			ctx->setState(ctx->controller.getReport());
		}
};
