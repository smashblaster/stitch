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

				// dleft => vanilla
				if (ctx->down("dleft")) ctx->release("dleft");
				if (ctx->pressed("dleft")) {
					ctx->isDolphin = false;
					ctx->rumble = true;
				}

				// dright => dolphin
				if (ctx->down("dright")) ctx->release("dright");
				if (ctx->pressed("dright")) {
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
