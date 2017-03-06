#include <sstream>
#include <string>

#include "Fuel_level.h"

using std::ostringstream;
using std::string;

namespace Readings {
	namespace Fuel_level {
		Fuel_level::Fuel_level(float fuel_level)
		{
			this->fuel_level = fuel_level;
		}


		Fuel_level::~Fuel_level()
		{
		}


		string Fuel_level::to_string()
		{
			ostringstream stringStream;
			stringStream << "FUEL " << this->fuel_level;
			return stringStream.str();
		}
	}
}
