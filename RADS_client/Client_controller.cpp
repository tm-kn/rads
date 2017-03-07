#include <ctime>
#include <exception>
#include <unordered_map>
#include <iostream>
#include <thread>

#include "Client_controller.h"
#include "Base_state.h";
#include "Reading_state.h";
#include "../RADS_common/Fuel_level_reader.h"
#include "../RADS_common/GPS_position_reader.h"
#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor.h"
#include "../RADS_common/Sensor_reader.h"
#include "../RADS_common/Speed_reader.h"
#include "../RADS_common/Temperature_sensor_reader.h"

using std::cout;
using std::endl;
using std::logic_error;
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

	void Client_controller::perform() {
		State::Base* state = NULL;

		switch (this->current_state_id) {
		case STATE_READING:
			state = new State::Reading();
			break;
		default:
			throw logic_error("Client controller is in not-existent state");
		}

		state->set_client_controller(this);
		state->perform();
	}

	void Client_controller::start_communicating()
	{
		this->set_state(STATE_CONNECTING);
	}

	void Client_controller::stop_communicating()
	{
	}

	void Client_controller::start_reading()
	{
		this->set_state(STATE_READING);
		this->perform();
	}

	vector<Sensor_reader*> Client_controller::get_sensor_readers() {
		return this->sensor_readers;
	}

	void Client_controller::stop_reading()
	{
		
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

	void Client_controller::set_state(int state) {
		this->current_state_id = state;
	}
}