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
				if (ctx->down("DDOWN")) ctx->release("DDOWN");
				if (ctx->pressed("DDOWN")) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// dup => debug
				if (ctx->down("DUP")) ctx->release("DUP");
				if (ctx->pressed("DUP")) {
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// l => vanilla
				if (ctx->down("L")) ctx->release("L");
				if (ctx->pressed("L")) {
					ctx->isDolphin = false;
					ctx->rumble = true;
				}

				// r => dolphin
				if (ctx->down("R")) ctx->release("R");
				if (ctx->pressed("R")) {
					ctx->isDolphin = true;
					ctx->rumble = true;
				}
			}
		}

		// meta = start + z
		bool isMeta() {
			return ctx->down("START") && ctx->down("Z");
		}

		void releaseMeta() {
			ctx->release("START");
			ctx->release("Z");
		}
};
