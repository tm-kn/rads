#include <string>

#include "Sensor.h"

using std::string;

namespace Readings {
	Sensor::Sensor() {}

	string Sensor::to_string() {
		return "Unknown sensor";
	}
}