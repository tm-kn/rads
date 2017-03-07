#pragma once

#include <string>

#include "Sensor.h"

using Readings::Sensor;
using std::string;

namespace Readings {
    namespace GPS_position {
        class GPS_position :
            public Sensor
        {
        public:
            GPS_position(float latitude, float longitude, float altitude);
            ~GPS_position();
            string to_string();
        private:
            float latitude;
            float longitude;
            float altitude;
        };
    }
}

