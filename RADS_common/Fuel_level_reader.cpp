#include <string>

#include "Fuel_level.h"
#include "Fuel_level_reader.h"

using std::string;

using Readings::Fuel_level::Fuel_level;

namespace Readings {
	namespace Fuel_level {
		Fuel_level_reader::Fuel_level_reader()
		{
		}


		Fuel_level_reader::~Fuel_level_reader()
		{
		}
		
		void Fuel_level_reader::read() {
			for (int i = 100; i >= 50; i--) {
				this->readings.push_back(new Fuel_level(i));
			}
		}

		string Fuel_level_reader::get_sensor_reader_name() {
			return "Fuel level sensor reader";
		}

		void Fuel_level_reader::set_up() {

		}
	}
}