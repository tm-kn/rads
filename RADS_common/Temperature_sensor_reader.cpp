#include <string>

#include "Temperature.h"
#include "Temperature_sensor_reader.h"

using std::string;

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
			for (int i = 0; i < 100; i++) {
				this->readings.push_back(new Temperature("1", i));
			}
 		}

		string Temperature_sensor_reader::get_sensor_reader_name() {
			return "Temperature Sensor Reader";
		}

		void Temperature_sensor_reader::set_up() {}
	}
}

