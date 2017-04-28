#include <ArduinoJson.h>
#include <string>

#ifndef SETTINGS
#define SETTINGS

class Settings {
	public:
		bool backdash = true;
		bool debug = false;
		bool input = true;
		bool meta = true;
		bool remap = true;
		bool rumble = false;

		Settings(JsonObject& settings) {
			backdash = settings["backdash"];
			input = settings["input"];
			meta = settings["meta"];
			remap = settings["remap"];
			rumble = settings["rumble"];
		}

		~Settings() {}

		bool get(std::string path) {
			if (path == "backdash") return backdash;
			if (path == "debug") return debug;
			if (path == "input") return input;
			if (path == "meta") return meta;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}

		void set(std::string path, bool value) {
			if (path == "backdash") backdash = value;
			if (path == "debug") debug = value;
			if (path == "input") input = value;
			if (path == "meta") meta = value;
			if (path == "remap") remap = value;
			if (path == "rumble") rumble = value;
		}

		void enable(std::string path) { set(path, true); }
		void disable(std::string path) { set(path, false); }
		void toggle(std::string path) { set(path, !get(path)); }
};

#endif
