#include "system.hpp"
#include <Nintendo.h>

class MetaSystem: public System {
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
				if (ctx->down(Inputs::DDOWN)) ctx->release(Inputs::DDOWN);
				if (ctx->pressed(Inputs::DDOWN)) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// dup => debug
				if (ctx->down(Inputs::DUP)) ctx->release(Inputs::DUP);
				if (ctx->pressed(Inputs::DUP)) {
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// l => vanilla
				if (ctx->down(Inputs::L)) ctx->release(Inputs::L);
				if (ctx->pressed(Inputs::L)) {
					ctx->dolphin(false);
					ctx->rumble = true;
				}

				// r => dolphin
				if (ctx->down(Inputs::R)) ctx->release(Inputs::R);
				if (ctx->pressed(Inputs::R)) {
					ctx->dolphin(true);
					ctx->rumble = true;
				}
			}
		}

		// meta = start + z
		bool isMeta() {
			// return ctx->down(Inputs::START) && ctx->down(Inputs::Z);
			return ctx->data.report.start & ctx->data.report.z;
		}

		void releaseMeta() {
			ctx->release(Inputs::START);
			ctx->release(Inputs::Z);
		}
};
