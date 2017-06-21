#include "buttons.cpp"
#include <Nintendo.h>
#include <bitset>
#include <string>
#include <vector>

#pragma once

class System;

class Context {
	private:
		const int maxDashBufferConsole = 2;
		const int maxDashBufferDolphin = maxDashBufferConsole * 4;
		const int stepIntervalConsole = 1;
		const int stepIntervalDolphin = 7;

	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data = defaultGamecubeData;
		bool enabled = true;
		bool isDolphin = false;
		bool meta = false;
		bool rumble = false;
		const int gridOffset = 129;
		int maxDashBuffer = maxDashBufferConsole;
		int stepInterval = stepIntervalConsole;
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

		Context(int consolePin, int controllerPin): console(consolePin), controller(controllerPin) {}
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
