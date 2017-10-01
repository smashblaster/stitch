#include "system.hpp"
#include <Nintendo.h>

class MetaSystem: public System {
	using System::System;

	private:
		bool halt = false;

	public:
		void init() {
			if (ctx->data.report.ddown) {
				ctx->release(Buttons::DDOWN);
				ctx->enabled = false;
				halt = true;
				disable();
			}
			if (ctx->data.report.dright) {
				ctx->release(Buttons::DRIGHT);
				ctx->dolphin(true);
			}
		}

		void update() {
			ctx->rumble = false;

			if (halt) {
				ctx->release(Buttons::Z);
				if (!ctx->data.report.z) setPersistent(false);
				return;
			}

			if (ctx->data.report.z) {
				// DDOWN => toggle
				if (ctx->data.report.ddown) ctx->release(Buttons::DDOWN);
				if (ctx->pressed(Buttons::DDOWN)) {
					ctx->release(Buttons::Z);
					ctx->enabled = !ctx->enabled;
					ctx->rumble = true;
				}

				// DUP => debug
				if (ctx->data.report.dup) ctx->release(Buttons::DUP);
				if (ctx->pressed(Buttons::DUP)) {
					ctx->release(Buttons::Z);
					ctx->toggleSystem("debug");
					ctx->rumble = true;
				}

				// L => vanilla
				if (ctx->data.report.dleft) ctx->release(Buttons::DLEFT);
				if (ctx->pressed(Buttons::DLEFT)) {
					ctx->release(Buttons::Z);
					ctx->dolphin(false);
					ctx->rumble = true;
				}

				// R => dolphin
				if (ctx->data.report.dright) ctx->release(Buttons::DRIGHT);
				if (ctx->pressed(Buttons::DRIGHT)) {
					ctx->release(Buttons::Z);
					ctx->dolphin(true);
					ctx->rumble = true;
				}
			}
		}
};
