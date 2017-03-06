#pragma once
#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
	namespace GPS_position {
		class GPS_position_reader :
			public Sensor_reader
		{
		public:
			GPS_position_reader();
			~GPS_position_reader();
			void read();
			void set_up();
			string get_sensor_reader_name();
		};
	}
}