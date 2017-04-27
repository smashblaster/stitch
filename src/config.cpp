#include "settings.cpp"
#include <ArduinoJson.h>
#include <string>

#ifndef CONFIG
#define CONFIG

class Config {
	private:
		StaticJsonBuffer<200> jsonBuffer;
		Settings* settings_;

	public:
		Config(char json[]) {
			settings_ = new Settings(jsonBuffer.parseObject(json));
		}

		~Config() {}

		Settings* settings() const { return settings_; }
};

#endif
