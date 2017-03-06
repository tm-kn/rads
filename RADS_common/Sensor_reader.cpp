#include <vector>

#include "Sensor.h"
#include "Sensor_reader.h"

using std::vector;
using Readings::Sensor;

namespace Readings {
	Sensor_reader::Sensor_reader()
	{
	}


	Sensor_reader::~Sensor_reader()
	{
	}

	vector<Sensor*> Sensor_reader::getReadings()
	{
		return this->readings;
	}

	void Sensor_reader::read()
	{
	}

	void Sensor_reader::set_up()
	{
	}
}