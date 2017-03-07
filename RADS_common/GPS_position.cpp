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

        string GPS_position::to_string()
        {
            ostringstream stringStream;
            stringStream << "LAT" << this->latitude << "; LNG " << this->longitude << "; ALT " << this->altitude;

            return stringStream.str();
        }
    }
}
