#include "Nintendo.h"
#include "modules/backdasher.cpp"
#include "modules/debugger.cpp"
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
		Debugger debugger;
		Mapper mapper;
		Meta meta;
		Remapper remapper;

	public:
		WaveSine(int cons, int cont): console(cons), controller(cont) {}

		void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
			mapper.init(state, data, controller);
			debugger.init(state, data, controller);
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

			if (isInit == false) {
				init(state, &data);
				isInit = true;
			}

			mapper.update(state, &data, controller);
			meta.update(state, &data, controller);

			if (meta.isPassthrough == false) {
				// debugger.update(state, &data);
				remapper.update(state, &data, controller);
				backdasher.update(state, &data, controller);
			}

			// Sends the data to the console
			if (!console.write(data)) {
				delay(100);
				console.write(data);
			}

			controller.setRumble(data.status.rumble);
		};
};

#endif
