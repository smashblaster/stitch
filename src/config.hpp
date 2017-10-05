#include <ArduinoJson.h>
#include <string>

#pragma once

class Config {
	private:
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& config;

	public:
		bool angles = false;
		bool backdash = true;
		bool debug = false;
		bool remap = false;
		bool rumble = false;

		Config(char json[]): config(jsonBuffer.parseObject(json)) {
			// TODO: add cardinal setting to angles
			angles = config["angles"];
			backdash = config["backdash"];
			debug = config["debug"];
			remap = config["remap"];
			rumble = config["rumble"];
		}

		~Config() = default;

		bool get(std::string path) const {
			if (path == "angles") return angles;
			if (path == "backdash") return backdash;
			if (path == "debug") return debug;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}
};
