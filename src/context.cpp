#include "context.hpp"

uint8_t Context::get(Buttons button, Gamecube_Report_t state) {
	if (button == Buttons::A) return state.a;
	if (button == Buttons::B) return state.b;
	if (button == Buttons::X) return state.x;
	if (button == Buttons::Y) return state.y;
	if (button == Buttons::L) return state.l;
	if (button == Buttons::R) return state.r;
	if (button == Buttons::Z) return state.z;
	if (button == Buttons::START) return state.start;
	if (button == Buttons::DDOWN) return state.ddown;
	if (button == Buttons::DLEFT) return state.dleft;
	if (button == Buttons::DRIGHT) return state.dright;
	if (button == Buttons::DUP) return state.dup;
	if (button == Buttons::CXAXIS) return state.cxAxis;
	if (button == Buttons::CYAXIS) return state.cyAxis;
	if (button == Buttons::LEFT) return state.left;
	if (button == Buttons::RIGHT) return state.right;
	if (button == Buttons::XAXIS) return state.xAxis;
	if (button == Buttons::YAXIS) return state.yAxis;
	return 0;
}

void Context::set(Buttons button, uint8_t value) {
	if (button == Buttons::A) data.report.a = value;
	if (button == Buttons::B) data.report.b = value;
	if (button == Buttons::X) data.report.x = value;
	if (button == Buttons::Y) data.report.y = value;
	if (button == Buttons::L) data.report.l = value;
	if (button == Buttons::R) data.report.r = value;
	if (button == Buttons::Z) data.report.z = value;
	if (button == Buttons::START) data.report.start = value;
	if (button == Buttons::DDOWN) data.report.ddown = value;
	if (button == Buttons::DLEFT) data.report.dleft = value;
	if (button == Buttons::DRIGHT) data.report.dright = value;
	if (button == Buttons::DUP) data.report.dup = value;
	if (button == Buttons::CXAXIS) data.report.cxAxis = value;
	if (button == Buttons::CYAXIS) data.report.cyAxis = value;
	if (button == Buttons::LEFT) data.report.left = value;
	if (button == Buttons::RIGHT) data.report.right = value;
	if (button == Buttons::XAXIS) data.report.xAxis = value;
	if (button == Buttons::YAXIS) data.report.yAxis = value;
}

bool Context::pressed(Buttons button) {
	return pressedButtons.test(button);
}

bool Context::released(Buttons button) {
	return releasedButtons.test(button);
}
