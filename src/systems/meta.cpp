#include "system.hpp"
#include <Nintendo.h>

class MetaSystem: public System {
	using System::System;

	private:
		bool halt = false;

	public:
		void init() {
			if (isMeta()) {
				releaseMeta();
				ctx->enabled = false;
				halt = true;
				disable();
			}
			if (ctx->data.report.r) {
				ctx->release(Buttons::R);
				ctx->dolphin(true);
			}
		}

		void update() {
			ctx->meta = false;
			ctx->rumble = false;

			if (halt) {
				releaseMeta();
				if (!ctx->data.report.start && !ctx->data.report.z) setPersistent(false);
				return;
			}

			if (isMeta()) {
				releaseMeta();
				ctx->meta = true;

				// DDOWN => toggle
				if (ctx->data.report.ddown) ctx->release(Buttons::DDOWN);
				if (ctx->pressed(Buttons::DDOWN)) {
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// DUP => debug
				if (ctx->data.report.dup) ctx->release(Buttons::DUP);
				if (ctx->pressed(Buttons::DUP)) {
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// L => vanilla
				if (ctx->data.report.l) ctx->release(Buttons::L);
				if (ctx->pressed(Buttons::L)) {
					ctx->dolphin(false);
					ctx->rumble = true;
				}

				// R => dolphin
				if (ctx->data.report.r) ctx->release(Buttons::R);
				if (ctx->pressed(Buttons::R)) {
					ctx->dolphin(true);
					ctx->rumble = true;
				}
			}
		}

		// META = START + Z
		bool isMeta() {
			return ctx->data.report.start & ctx->data.report.z;
		}

		void releaseMeta() {
			ctx->release(Buttons::START);
			ctx->release(Buttons::Z);
		}
};
