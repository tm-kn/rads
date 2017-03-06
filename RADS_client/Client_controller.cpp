#include <iostream>

#include "Client_controller.h"
#include "../RADS_common/GPS_position_reader.h"
#include "../RADS_common/Sensor.h"
#include "../RADS_common/Sensor_reader.h"

using std::cout;
using std::endl;

using Readings::GPS_position::GPS_position_reader;
using Readings::Sensor;
using Readings::Sensor_reader;

namespace RADS_client {
	Client_controller::Client_controller()
	{
		this->sensor_readers.push_back(new GPS_position_reader());
	}


	Client_controller::~Client_controller()
	{
	}

	void Client_controller::start_communicating()
	{
	}

	void Client_controller::stop_communicating()
	{
	}

	void Client_controller::start_reading()
	{
		cout << "Client controller: Started reading" << endl;
		for (Sensor_reader *sensor_reader : this->sensor_readers) {
			sensor_reader->read();
		}
		
		cout << "Client controller: Stopped reading" << endl;
	}

	void Client_controller::stop_reading()
	{
		cout << "Client controller: Results" << endl;
		for (Sensor_reader *sensor_reader : this->sensor_readers) {
			cout << sensor_reader->get_sensor_reader_name() << endl;
			for (Sensor *sensor : sensor_reader->getReadings()) {
				cout << sensor->to_string() << endl;
			}
		}
	}
}