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
		bool backdash = true;
		bool remap = true;
		bool rumble = false;

		Config(char json[]): config(jsonBuffer.parseObject(json)) {
			backdash = config["backdash"];
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

		bool get(std::string key) {
			if (key == "backdash") return backdash;
			if (key == "remap") return remap;
			if (key == "rumble") return rumble;
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
