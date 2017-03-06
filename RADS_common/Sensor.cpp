#include <string>
#include <iostream>

#include "Sensor.h"

using std::string;
using System::DateTime;

namespace Readings {
	Sensor::Sensor() {
		this->datetime = &DateTime::UtcNow;
	}

	string Sensor::to_string() {
		return "Unknown sensor";
	}

	DateTime Sensor::get_datetime() {
		return *this->datetime;
	}
}