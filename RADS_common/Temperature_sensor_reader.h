#pragma once

#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
	namespace Temperature {
		class Temperature_sensor_reader :
			public Sensor_reader
		{
		public:
			Temperature_sensor_reader();
			~Temperature_sensor_reader();
			string get_sensor_reader_name();
			void read();
			void set_up();
		};
	}
}