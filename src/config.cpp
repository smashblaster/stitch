#include "settings.cpp"
#include <ArduinoJson.h>
#include <string>

#ifndef CONFIG
#define CONFIG

class Config {
	private:
		StaticJsonBuffer<200> jsonBuffer;

	public:
		Settings* settings;

		Config(char json[]) {
			settings = new Settings(jsonBuffer.parseObject(json));
		}

		~Config() {}
};

#endif
