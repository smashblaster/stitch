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
			if (ctx->data.report.r) {
				ctx->dolphin(true);
			}
		}

		void update() {
			ctx->meta = false;
			ctx->rumble = false;

			if (isMeta()) {
				ctx->meta = true;
				releaseMeta();

				// ddown => toggle
				if (ctx->down(Buttons::DDOWN)) ctx->release(Buttons::DDOWN);
				if (ctx->pressed(Buttons::DDOWN)) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// dup => debug
				if (ctx->down(Buttons::DUP)) ctx->release(Buttons::DUP);
				if (ctx->pressed(Buttons::DUP)) {
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// l => vanilla
				if (ctx->down(Buttons::L)) ctx->release(Buttons::L);
				if (ctx->pressed(Buttons::L)) {
					ctx->dolphin(false);
					ctx->rumble = true;
				}

				// r => dolphin
				if (ctx->down(Buttons::R)) ctx->release(Buttons::R);
				if (ctx->pressed(Buttons::R)) {
					ctx->dolphin(true);
					ctx->rumble = true;
				}
			}
		}

		// meta = start + z
		bool isMeta() {
			// return ctx->down(Buttons::START) && ctx->down(Buttons::Z);
			return ctx->data.report.start & ctx->data.report.z;
		}

		void releaseMeta() {
			ctx->release(Buttons::START);
			ctx->release(Buttons::Z);
		}
};
