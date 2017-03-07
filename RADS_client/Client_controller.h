#pragma once

#include <vector>

#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor_reader.h"

using std::vector;
using Readings::Reading_data;
using Readings::Sensor_reader;

namespace RADS_client {
	class Client_controller
	{
	public:
		enum Client_controller_state { READING, CONNECTING, SENDING, ERROR };
		Client_controller();
		~Client_controller();
		Reading_data* get_reading_data();
		vector<Sensor_reader*> get_sensor_readers();
		void start_communicating();
		void start_reading();
		void perform();
	private:
		void set_state(Client_controller_state state);
		vector<Sensor_reader*> sensor_readers;
		int transmission_frequency;
		Client_controller_state current_state;
	};
}