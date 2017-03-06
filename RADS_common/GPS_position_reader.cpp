#include <string>

#include "GPS_position_reader.h"
#include "GPS_position.h"

using std::string;

using Readings::GPS_position::GPS_position;

namespace Readings {
	namespace GPS_position {
		GPS_position_reader::GPS_position_reader()
		{
		}


		GPS_position_reader::~GPS_position_reader()
		{
		}

		void GPS_position_reader::read() {
			for (int i = 0; i < 10; i++) {
				this->readings.push_back(new GPS_position(i % 180, i % 180, i % 180));
			}
		}

		void GPS_position_reader::set_up() {}
		
		string GPS_position_reader::get_sensor_reader_name() {
			return "GPS Position Sensor Reader";
		}
	}
}