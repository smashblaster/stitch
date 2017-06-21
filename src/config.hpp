#include "SdFat.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <string>

#pragma once

class Config {
	private:
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& config;

		const int selectPin = 10;

	public:
		bool angles = false;
		bool backdash = true;
		bool cardinal = true;
		bool debug = false;
		bool remap = false;
		bool rumble = false;

		Config(char json[]): config(jsonBuffer.parseObject(json)) {
			angles = config["angles"];
			backdash = config["backdash"];
			cardinal = config["cardinal"];
			debug = config["debug"];
			remap = config["remap"];
			rumble = config["rumble"];
		}

		~Config() = default;

		void load() {
			SdFat sd;
			if (!sd.begin(selectPin)) {
				Serial.println("Card failed, or not present");
				return;
			}

			File profile = sd.open("0.txt");

			if (!profile) {
				Serial.println("Error opening profile");
				return;
			}

			while (profile.available()) {
				Serial.write(profile.read());
			}
			profile.close();
		}

		void list() {
			SdFat sd;
			if (!sd.begin(selectPin)) {
				Serial.println("Card failed, or not present");
				return;
			}

			Serial.println("========");
			Serial.println("LS:");
			sd.ls(LS_R);
		}

		bool get(std::string path) const {
			if (path == "angles") return angles;
			if (path == "backdash") return backdash;
			if (path == "cardinal") return cardinal;
			if (path == "debug") return debug;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}
};
