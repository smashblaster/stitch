#include <ArduinoJson.h>
#include <string>

#ifndef CONFIG
#define CONFIG

class Config {
	private:
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& config;

	public:
		bool backdash = true;
		bool remap = true;
		bool rumble = false;
		const bool debug = false;

		Config(char json[]): config(jsonBuffer.parseObject(json)) {
			backdash = config["backdash"];
			remap = config["remap"];
			rumble = config["rumble"];
		}

		~Config() {}

		bool get(std::string path) {
			if (path == "backdash") return backdash;
			if (path == "debug") return debug;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}
};

#endif
