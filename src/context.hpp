#include "buttons.cpp"
#include <Nintendo.h>
#include <bitset>
#include <string>
#include <vector>

#pragma once

class System;

class Context {
	private:
		const uint8_t maxDashBufferConsole = 2;
		const uint8_t maxDashBufferDolphin = maxDashBufferConsole * 4;
		const uint8_t stepIntervalConsole = 1;
		const uint8_t stepIntervalDolphin = 7;

	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data = defaultGamecubeData;
		bool enabled = true;
		bool isDolphin = false;
		bool meta = false;
		bool rumble = false;
		const uint8_t gridOffset = 129;
		uint8_t maxDashBuffer = maxDashBufferConsole;
		uint8_t stepInterval = stepIntervalConsole;
		std::bitset<Buttons::length> pressedButtons;
		std::bitset<Buttons::length> releasedButtons;
		unsigned long debug = 0;

		System* inputSystem;
		System* metaSystem;
		System* remapSystem;
		System* cardinalSystem;
		System* backdashSystem;
		System* anglesSystem;
		System* debugSystem;

		Context(uint8_t consolePin, uint8_t controllerPin): console(consolePin), controller(controllerPin) {}
		~Context() {}

		uint8_t get(Buttons button) { get(button, data.report); }
		uint8_t get(Buttons button, Gamecube_Report_t state);
		void set(Buttons button, uint8_t value);

		void press(Buttons button) { set(button, 1); }
		void release(Buttons button) { set(button, 0); }
		bool pressed(Buttons button);
		bool released(Buttons button);
		bool down(Buttons button) { return get(button, data.report) > 0; }

		void setState(Gamecube_Report_t state) { data.report = state; }

		// Profiler
		void begin() { debug = micros(); }
		void end() { debug = micros() - debug; }

		void dolphin(bool enabled) {
			isDolphin = enabled;
			stepInterval = (enabled) ? stepIntervalDolphin : stepIntervalConsole;
			maxDashBuffer = (enabled) ? maxDashBufferDolphin : maxDashBufferConsole;
		}
};
