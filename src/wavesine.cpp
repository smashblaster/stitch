#include "Nintendo.h"
#include "modules/backdasher.cpp"
#include "modules/debug.cpp"
#include "modules/mapper.cpp"
#include "modules/meta.cpp"
#include "modules/remapper.cpp"

#ifndef WAVESINE
#define WAVESINE

class WaveSine {
	private:
		bool isInit = false;

		CGamecubeConsole console;
		CGamecubeController controller;

		Backdasher backdasher;
		Debug debug;
		Mapper mapper;
		Meta meta;
		Remapper remapper;

		bool rumbleSetting = false;

	public:
		WaveSine(int cons, int cont): console(cons), controller(cont) {}

		void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
			mapper.init(state, data, controller);
			meta.init(state, data, controller);
			debug.init(state, data, controller);
			remapper.init(state, data, controller);
			backdasher.init(state, data, controller);
		}

		void update() {
			// Just stops the code if no controller is found
			if (!controller.read()) {
				isInit = false;
				delay(100);
				return;
			}

			// Gets the data of controller
			Gamecube_Report_t state = controller.getReport();
			Gamecube_Data_t data = defaultGamecubeData;

			if (!isInit) {
				init(state, &data);
				isInit = true;
			}

			mapper.update(state, &data, controller);
			meta.update(state, &data, controller);

			if (meta.isEnabled) {
				if (meta.isDebug) debug.update(state, &data, controller);
				remapper.update(state, &data, controller);
				backdasher.update(state, &data, controller);
			}

			// Sends the data to the console
			if (!console.write(data)) {
				delay(100);
				return;
			}

			controller.setRumble((rumbleSetting && data.status.rumble) || meta.rumble);
		};
};

#endif
