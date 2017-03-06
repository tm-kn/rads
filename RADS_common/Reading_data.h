#pragma once

#include <ctime>
#include <vector>

#include "Sensor.h"

using std::time_t;
using std::vector;

using Readings::Sensor;

namespace Readings {
	class Reading_data
	{
	public:
		Reading_data(time_t start_datetime, time_t end_datetime, vector<Sensor*> sensor_data);
		~Reading_data();
		time_t get_reading_start_datetime();
		time_t get_reading_end_datetime();
	private:
		time_t reading_start_datetime;
		time_t reading_end_datetime;
		vector<Sensor*> sensor_data;
	};
}
