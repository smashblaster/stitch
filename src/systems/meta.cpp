#include "system.hpp"
#include <Nintendo.h>

class Meta: public System {
	using System::System;

	public:
		void init() {
			if (isMeta()) {
				ctx->enabled = false;
				releaseMeta();
			}
		}

		void update() {
			ctx->meta = false;
			ctx->rumble = false;

			if (isMeta()) {
				ctx->meta = true;
				releaseMeta();

				// ddown => toggle
				if (ctx->down("ddown")) ctx->release("ddown");
				if (ctx->pressed("ddown")) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// dup => debug
				if (ctx->down("dup")) ctx->release("dup");
				if (ctx->pressed("dup")) {
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// l => vanilla
				if (ctx->down("l")) ctx->release("l");
				if (ctx->pressed("l")) {
					ctx->isDolphin = false;
					ctx->rumble = true;
				}

				// r => dolphin
				if (ctx->down("r")) ctx->release("r");
				if (ctx->pressed("r")) {
					ctx->isDolphin = true;
					ctx->rumble = true;
				}
			}
		}

		// meta = start + z
		bool isMeta() {
			return ctx->down("start") && ctx->down("z");
		}

		void releaseMeta() {
			ctx->release("start");
			ctx->release("z");
		}
};
