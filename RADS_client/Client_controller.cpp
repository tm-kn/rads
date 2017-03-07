#include <ctime>
#include <unordered_map>
#include <iostream>
#include <thread>

#include "Client_controller.h"
#include "../RADS_common/Fuel_level_reader.h"
#include "../RADS_common/GPS_position_reader.h"
#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor.h"
#include "../RADS_common/Sensor_reader.h"
#include "../RADS_common/Speed_reader.h"
#include "../RADS_common/Temperature_sensor_reader.h"

using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using std::thread;

using Readings::Fuel_level::Fuel_level_reader;
using Readings::GPS_position::GPS_position_reader;
using Readings::Reading_data;
using Readings::Sensor;
using Readings::Sensor_reader;
using Readings::Speed::Speed_reader;
using Readings::Temperature::Temperature_sensor_reader;

namespace RADS_client {
	Client_controller::Client_controller()
	{
		// Multiple readers of the same type allowed
		this->sensor_readers.push_back(new Speed_reader());
		this->sensor_readers.push_back(new GPS_position_reader());
		this->sensor_readers.push_back(new Temperature_sensor_reader());
		this->sensor_readers.push_back(new Fuel_level_reader());
		this->sensor_readers.push_back(new GPS_position_reader());
		this->sensor_readers.push_back(new Temperature_sensor_reader());
		this->sensor_readers.push_back(new Speed_reader());
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
		unordered_map<Sensor_reader*, thread*> threads;

		cout << "Client controller: Started reading" << endl;
		for (Sensor_reader *sensor_reader : this->sensor_readers) {
			threads.insert(pair<Sensor_reader*, thread*>(sensor_reader, new thread(&Sensor_reader::read, sensor_reader)));
			cout << "Client controller: Thread for " << sensor_reader->get_sensor_reader_name() << " has started" << endl;
		}

		for (pair<Sensor_reader*, thread*> sensor_thread_pair: threads) {
			sensor_thread_pair.second->join();
			cout << "Client controller: Thread for " << sensor_thread_pair.first->get_sensor_reader_name()  << " has finished" << endl;
		}
		
		cout << "Client controller: Finished reading" << endl;
	}

	void Client_controller::stop_reading()
	{
		cout << "Client controller: Stopped reading" << endl;
		cout << "Client controller: Results start" << endl;
		
		for (Sensor *sensor : this->get_reading_data()->get_data()) {
			cout << "["  << sensor->get_datetime() << "] " << sensor->to_string() << endl;
		}

		cout << "Client controller: Results end";
	}

	Reading_data* Client_controller::get_reading_data() {
		vector<Sensor*> data;
		time_t min_time = 0;
		time_t max_time = 0;

		for (Sensor_reader *sensor_reader : this->sensor_readers) {
			for (Sensor *sensor : sensor_reader->getReadings()) {
				if (!min_time || sensor->get_datetime() < min_time) {
					min_time = sensor->get_datetime();
				}

				if (sensor->get_datetime() > max_time) {
					max_time = sensor->get_datetime();
				}

				data.push_back(sensor);
			}
		}

		return new Reading_data(min_time, max_time, data);
	}
}