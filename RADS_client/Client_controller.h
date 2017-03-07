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
		Client_controller();
		~Client_controller();
		Reading_data* get_reading_data();
		void start_communicating();
		void stop_communicating();
		void start_reading();
		void stop_reading();
	private:
		vector<Sensor_reader*> sensor_readers;
		int transmission_frequency;
		int current_state_id;
	};
}