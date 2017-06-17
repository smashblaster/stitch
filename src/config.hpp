#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <string>

#pragma once

class Config {
	private:
		JsonObject& config;
		StaticJsonBuffer<200> jsonBuffer;
		const int chipSelect = 10;

	public:
		bool angles = false;
		bool backdash = true;
		bool cardinal = false;
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

		~Config() {}

		void init() {
			Serial.println("config init");
			if (SD.begin(chipSelect)) {
				Serial.println("Woo");
			} else {
				Serial.println("initialization failed!");
			}
		}

		bool get(std::string path) {
			if (path == "angles") return angles;
			if (path == "backdash") return backdash;
			if (path == "cardinal") return cardinal;
			if (path == "debug") return debug;
			if (path == "remap") return remap;
			if (path == "rumble") return rumble;
		}

		std::vector<char*> list() { list("/"); }

		std::vector<char*> list(char* path) {
			File dir = SD.open(path);
			dir.rewindDirectory();

			while(true) {
				File entry =  dir.openNextFile();
				if (!entry) break;
				Serial.print("\t\t");
				Serial.print(entry.name());
				Serial.print("\t\t");
				Serial.println(entry.size(), DEC);
				entry.close();
			}
		}
};
