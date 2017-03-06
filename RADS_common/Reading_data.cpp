#include <ctime>
#include <vector>

#include "Reading_data.h"
#include "Sensor.h"

using std::time_t;
using std::vector;

using Readings::Sensor;

namespace Readings {
	Reading_data::Reading_data(time_t start_datetime, time_t end_datetime, vector<Sensor*> sensor_data)
	{
		this->reading_start_datetime = start_datetime;
		this->reading_end_datetime = end_datetime;
		this->sensor_data = sensor_data;
	}


	Reading_data::~Reading_data()
	{
	}

	time_t Reading_data::get_reading_start_datetime() {
		return this->reading_start_datetime;
	}

	time_t Reading_data::get_reading_end_datetime() {
		return this->reading_end_datetime;
	}
}