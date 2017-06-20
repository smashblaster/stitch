#include <ArduinoJson.h>
#include <SD.h>
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

			Serial.print("Initializing SD card...");
			if (!SD.begin(selectPin)) {
				Serial.println("Card failed, or not present");
				return;
			}
			Serial.println("card initialized.");
		}

		~Config() = default;

		void init() {
			File profile = SD.open("00.txt");

			if (!profile) {
				Serial.println("Error opening profile");
				return;
			}

			while (profile.available()) {
				Serial.write(profile.read());
			}
			profile.close();
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
