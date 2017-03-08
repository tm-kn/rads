#include <sstream>
#include <string>

#include "Speed.h"

using std::ostringstream;
using std::string;

namespace Readings {
    namespace Speed {
        Speed::Speed(float speed)
        {
            this->speed = speed;
        }


        Speed::~Speed()
        {
        }

        string Speed::get_sensor_data() {
            ostringstream stringStream;
            stringStream << this->speed;
            return stringStream.str();
        }

        string Speed::get_sensor_type() {
            return "SPEED";
        }
        int Speed::get_sensor_type_int()
        {
            return SPEED_SENSOR;
        }
    }
}
