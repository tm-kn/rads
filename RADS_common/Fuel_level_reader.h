#pragma once

#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
	namespace Fuel_level {
		class Fuel_level_reader :
			public Sensor_reader
		{
		public:
			Fuel_level_reader();
			~Fuel_level_reader();
			void read();
			void set_up();
			string get_sensor_reader_name();
		};
	}
}
