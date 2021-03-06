#include "Arduino.h"
#include "config.hpp"
#include "context.hpp"
#include "systems/angles.cpp"
#include "systems/backdash.cpp"
#include "systems/input.cpp"
#include "systems/meta.cpp"
#include <Nintendo.h>

#define pinLed LED_BUILTIN

const int baud = 9600;
const int consolePin = 3;
const int controllerPin = 4;

Context* ctx;
const Config* config;
int step;

void addSystem(char* name, System* system, bool persistent = false) {
	ctx->addSystem(name, system, persistent, config->get(name));
}

void setup() {
	Serial.begin(baud);
	pinMode(pinLed, OUTPUT);

	char json[] = "{"
		"\"angles\": \"true\","
		"\"backdash\": \"true\","
		"\"remap\": \"false\","
		"\"rumble\": \"false\""
	"}";

	config = new Config(json);
	ctx = new Context(consolePin, controllerPin);

	addSystem("input", new InputSystem(ctx), true);
	addSystem("meta", new MetaSystem(ctx), true);

	// addSystem("remap", new RemapSystem(ctx));
	addSystem("backdash", new BackdashSystem(ctx));
	addSystem("angles", new AnglesSystem(ctx));
}

void init2() {
	for (auto &system : ctx->systems) {
		if (system->persistent || (system->enabled && ctx->enabled)) system->init();
	}
	ctx->init = true;
}

void loop() {
	// Read from controller
	if (!ctx->controller.read()) {
		// Continue if no controller is found
		ctx->init = false;
		delay(100);
		return;
	}

	if (!ctx->init) init2();

	for (auto &system : ctx->systems) {
		if (system->persistent || (system->enabled && ctx->enabled)) system->update();
	}

	step = 0;
	while (step < ctx->stepInterval) {
		// Write to console
		ctx->console.write(ctx->data);
		step += 1;
	}

	ctx->controller.setRumble((config->get("rumble") && ctx->data.status.rumble) || ctx->rumble);
}
