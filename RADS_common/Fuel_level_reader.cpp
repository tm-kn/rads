#include <chrono>
#include <string>
#include <thread>

#include "Fuel_level.h"
#include "Fuel_level_reader.h"

using std::chrono::seconds;
using std::string;
using std::this_thread::sleep_for;

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
			for (int i = 100; i >= 75; i--) {
				this->readings.push_back(new Fuel_level(i));
				sleep_for(seconds(1));
			}
		}

		string Fuel_level_reader::get_sensor_reader_name() {
			return "Fuel level sensor reader";
		}

		void Fuel_level_reader::set_up() {

		}
	}
}