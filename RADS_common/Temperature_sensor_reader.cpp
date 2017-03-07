#include <chrono>
#include <string>
#include <thread>

#include "Temperature.h"
#include "Temperature_sensor_reader.h"

using std::chrono::seconds;
using std::string;
using std::this_thread::sleep_for;

using Readings::Temperature::Temperature;

namespace Readings {
	namespace Temperature {
		Temperature_sensor_reader::Temperature_sensor_reader()
		{
		}


		Temperature_sensor_reader::~Temperature_sensor_reader()
		{
		}

		void Temperature_sensor_reader::read() {
			for (int i = 0; i < 15; i++) {
				this->readings.push_back(new Temperature("1", i));
				sleep_for(seconds(1));
			}
 		}

		string Temperature_sensor_reader::get_sensor_reader_name() {
			return "Temperature Sensor Reader";
		}

		void Temperature_sensor_reader::set_up() {}
	}
}

