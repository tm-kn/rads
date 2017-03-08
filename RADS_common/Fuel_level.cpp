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

        string Fuel_level::get_sensor_data() {
            ostringstream stringStream;
            stringStream << this->fuel_level;
            return stringStream.str();
        }

        string Fuel_level::get_sensor_type() {
            return "FUEL";
        }
    }
}
