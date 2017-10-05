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

			if (ctx->data.report.z) {
				// START+DUP => debug on
				if (ctx->data.report.start && ctx->data.report.dup) {
					ctx->release("z");
					ctx->release("dup");
					ctx->enableSystem("debug");
					ctx->rumble = true;
				}
				// START+DDOWN => debug off
				else if (ctx->data.report.start && ctx->data.report.ddown) {
					ctx->release("z");
					ctx->release("ddown");
					ctx->disableSystem("debug");
					ctx->rumble = true;
				}

				// DUP => on
				else if (ctx->data.report.dup) {
					ctx->release("z");
					ctx->release("dup");
					ctx->enabled = true;
					ctx->rumble = true;
				}
				// DDOWN => off
				else if (ctx->data.report.ddown) {
					ctx->release("z");
					ctx->release("ddown");
					ctx->enabled = false;
					ctx->rumble = true;
				}

				// DLEFT => vanilla
				else if (ctx->data.report.dleft) {
					ctx->release("z");
					ctx->release("dleft");
					ctx->dolphin(false);
					ctx->rumble = true;
				}
				// DRIGHT => dolphin
				else if (ctx->data.report.dright) {
					ctx->release("z");
					ctx->release("dright");
					ctx->dolphin(true);
					ctx->rumble = true;
				}
			}
		}
};
