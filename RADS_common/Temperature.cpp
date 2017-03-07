#include <sstream>
#include <string>

#include "Temperature.h"

using std::ostringstream;
using std::string;

namespace Readings {
	namespace Temperature {
		Temperature::Temperature(string sensor_name, double temperature)
		{
			this->sensor_name = sensor_name;
			this->temperature = temperature;
		}


		Temperature::~Temperature()
		{
		}

		string Temperature::to_string() {
			ostringstream stringStream;
			stringStream << "TMP " << this->sensor_name << "; " << this->temperature;
			return stringStream.str();
		}
	}
}