#pragma once

#include <string>

using std::string;
using System::DateTime;

namespace Readings {
	class Sensor
	{
	public:
		Sensor();
		DateTime get_datetime();
		virtual string to_string() = 0;
	private:
		DateTime *datetime;
	};
}