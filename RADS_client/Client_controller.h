#pragma once

#include <vector>

#include "../RADS_common/Sensor_reader.h"

namespace RADS_client {
	using std::vector;
	using Readings::Sensor_reader;

	class Client_controller
	{
	public:
		Client_controller();
		~Client_controller();
		void start_communicating();
		void stop_communicating();
		void start_reading();
		void stop_reading();
	private:
		vector<Sensor_reader*> sensor_readers;
	};
}