#include "context.hpp"
#include "systems/system.hpp"

uint8_t Context::get(Inputs input, Gamecube_Report_t state) {
	if (input == Inputs::A) return state.a;
	if (input == Inputs::B) return state.b;
	if (input == Inputs::X) return state.x;
	if (input == Inputs::Y) return state.y;
	if (input == Inputs::L) return state.l;
	if (input == Inputs::R) return state.r;
	if (input == Inputs::Z) return state.z;
	if (input == Inputs::START) return state.start;
	if (input == Inputs::DDOWN) return state.ddown;
	if (input == Inputs::DLEFT) return state.dleft;
	if (input == Inputs::DRIGHT) return state.dright;
	if (input == Inputs::DUP) return state.dup;
	if (input == Inputs::CXAXIS) return state.cxAxis;
	if (input == Inputs::CYAXIS) return state.cyAxis;
	if (input == Inputs::LEFT) return state.left;
	if (input == Inputs::RIGHT) return state.right;
	if (input == Inputs::XAXIS) return state.xAxis;
	if (input == Inputs::YAXIS) return state.yAxis;
	return 0;
}

void Context::set(Inputs input, uint8_t value) {
	if (input == Inputs::A) data.report.a = value;
	if (input == Inputs::B) data.report.b = value;
	if (input == Inputs::X) data.report.x = value;
	if (input == Inputs::Y) data.report.y = value;
	if (input == Inputs::L) data.report.l = value;
	if (input == Inputs::R) data.report.r = value;
	if (input == Inputs::Z) data.report.z = value;
	if (input == Inputs::START) data.report.start = value;
	if (input == Inputs::DDOWN) data.report.ddown = value;
	if (input == Inputs::DLEFT) data.report.dleft = value;
	if (input == Inputs::DRIGHT) data.report.dright = value;
	if (input == Inputs::DUP) data.report.dup = value;
	if (input == Inputs::CXAXIS) data.report.cxAxis = value;
	if (input == Inputs::CYAXIS) data.report.cyAxis = value;
	if (input == Inputs::LEFT) data.report.left = value;
	if (input == Inputs::RIGHT) data.report.right = value;
	if (input == Inputs::XAXIS) data.report.xAxis = value;
	if (input == Inputs::YAXIS) data.report.yAxis = value;
}

bool Context::pressed(Inputs input) {
	return pressedButtons.test(input);
}

bool Context::released(Inputs input) {
	return releasedButtons.test(input);
}

System* Context::getSystem(std::string name) {
	for (auto &system : systems) {
		if (system->name == name) return system;
	}
}

void Context::addSystem(char* name, System* system, bool persistent, bool enabled) {
	system->name = name;
	system->toggle(persistent || enabled);
	system->setPersistent(persistent);
	systems.push_back(system);
}

void Context::toggleSystem(std::string name) {
	System* system = getSystem(name);
	toggleSystem(system, !system->enabled);
}

void Context::toggleSystem(std::string name, bool value) {
	System* system = getSystem(name);
	toggleSystem(system, value);
}

void Context::toggleSystem(System* system) { system->enabled = !system->enabled; }
void Context::toggleSystem(System* system, bool value) { system->enabled = value; }
