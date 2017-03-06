#pragma once

#include <ctime>
#include <string>

using std::string;
using std::time;
using std::time_t;

namespace Readings {
	class Sensor
	{
	public:
		Sensor();
		time_t get_datetime();
		virtual string to_string() = 0;
	private:
		time_t datetime;
	};
}