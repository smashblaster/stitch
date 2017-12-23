#include "system.hpp"
#include <Nintendo.h>

class MetaSystem: public System {
	using System::System;

	private:
		bool halt = false;

	public:
		void init() {
			if (ctx->data.report.ddown) {
				ctx->release("ddown");
				ctx->enabled = false;
				halt = true;
				disable();
			} else if (ctx->data.report.dright) {
				ctx->release("dright");
				ctx->dolphin(true);
			}
		}

		void update() {
			ctx->rumble = false;

			if (halt) {
				ctx->release("z");
				if (!ctx->data.report.z) setPersistent(false);
				return;
			}

			if (!ctx->data.report.z) return;

			// START+L => disable backdash
			else if (ctx->data.report.start && ctx->data.report.l) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("l");
				ctx->disableSystem("backdash");
				ctx->rumble = true;
			}
			// START+R => enable backdash
			else if (ctx->data.report.start && ctx->data.report.r) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("r");
				ctx->enableSystem("backdash");
				ctx->rumble = true;
			}

			// START+DDOWN => off
			else if (ctx->data.report.start && ctx->data.report.ddown) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("ddown");
				ctx->enabled = false;
				ctx->rumble = true;
			}
			// START+DUP => on
			else if (ctx->data.report.start && ctx->data.report.dup) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("dup");
				ctx->enabled = true;
				ctx->rumble = true;
			}

			// START+DLEFT => vanilla
			else if (ctx->data.report.start && ctx->data.report.dleft) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("dleft");
				ctx->dolphin(false);
				ctx->rumble = true;
			}
			// START+DRIGHT => dolphin
			else if (ctx->data.report.start && ctx->data.report.dright) {
				ctx->release("z");
				ctx->release("start");
				ctx->release("dright");
				ctx->dolphin(true);
				ctx->rumble = true;
			}
		}
};
