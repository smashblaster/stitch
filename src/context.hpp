#include <Nintendo.h>
#include <string>
#include <vector>

#pragma once

class System;

class Context {
	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data = defaultGamecubeData;
		Gamecube_Report_t prevState;
		bool enabled = true;
		bool init = false;
		bool isDolphin = false;
		bool meta = false;
		bool rumble = false;
		std::vector<System*> systems;
		std::vector<std::string> pressedButtons;
		std::vector<std::string> releasedButtons;

		Context(int consolePin, int controllerPin): console(consolePin), controller(controllerPin) {}
		~Context() {}

		uint8_t get(std::string button) { get(button, data.report); }
		uint8_t get(std::string button, Gamecube_Report_t state);
		void set(std::string button, uint8_t value);

		void press(std::string button) { set(button, 1); }
		void release(std::string button) { set(button, 0); }
		bool pressed(std::string button);
		bool released(std::string button);
		bool down(std::string button) { return get(button, data.report) > 0; }

		System* getSystem(std::string name);
		void addSystem(char* name, System* system, bool persistent = false, bool enabled = false);
		void enableSystem(std::string name) { toggleSystem(name, true); }
		void disableSystem(std::string name) { toggleSystem(name, false); }
		void toggleSystem(std::string name);
		void toggleSystem(std::string name, bool value);
		void toggleSystem(System* system);
		void toggleSystem(System* system, bool value);
};
