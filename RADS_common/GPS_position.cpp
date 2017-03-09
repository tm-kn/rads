#include <sstream>
#include <string>

#include "GPS_position.h"

using std::ostringstream;
using std::string;

namespace Readings {
    namespace GPS_position {
        GPS_position::GPS_position(float latitude, float longitude, float altitude)
        {
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
        }

        GPS_position::~GPS_position()
        {
        }

        string GPS_position::get_sensor_data() {
            ostringstream stringStream;
            stringStream << this->latitude << ";" << this->longitude << ";" << this->altitude;

            return stringStream.str();
        }

        string GPS_position::get_sensor_type() {
            return "GPS";
        }
        Sensor_type GPS_position::get_sensor_type_int()
        {
            return GPS_POSITION_SENSOR;
        }
    }
}
