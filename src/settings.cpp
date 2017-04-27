#include <ArduinoJson.h>
#include <string>

#ifndef SETTINGS
#define SETTINGS

class Settings {
	public:
		bool backdash = true;
		bool debug = false;
		bool remap = true;
		bool rumble = false;

		Settings(JsonObject& settings) {
			backdash = settings["backdash"];
			remap = settings["remap"];
			rumble = settings["rumble"];
		}

		~Settings() {}

		bool get(std::string path) {
			if (path == "backdash") return backdash;
			if (path == "debug") return debug;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}

		bool set(std::string path, bool value) {
			if (path == "backdash") backdash = value;
			if (path == "debug") debug = value;
			if (path == "remap") remap = value;
			if (path == "rumble") rumble = value;
		}
};

#endif
