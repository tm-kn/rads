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
		static const int STATE_READING = 1;
		static const int STATE_CONNECTING = 2;
		static const int STATE_SENDING = 3;
		static const int STATE_ERROR = 4;

		Client_controller();
		~Client_controller();
		Reading_data* get_reading_data();
		vector<Sensor_reader*> get_sensor_readers();
		void start_communicating();
		void stop_communicating();
		void start_reading();
		void stop_reading();
		void perform();
	private:
		void set_state(int state);
		vector<Sensor_reader*> sensor_readers;
		int transmission_frequency;
		int current_state_id;
	};
}