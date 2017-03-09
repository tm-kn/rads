#pragma once

#include <string>

#include "Sensor.h"

using Readings::Sensor;
using std::string;

namespace Readings {
    namespace GPS_position {
        ///
        /// <summary>Represents a GPS position reading.</summary>
        ///
        class GPS_position :
            public Sensor
        {
        public:
            ///
            /// <summary>Instantiate GPS position reading object.</summary>
            /// <param name="latitude">Floating point representing latitude.</param>
            /// <param name="longitude">Floating point representing longitude.</param>
            /// <param name="altitude">Floating point representing altitude.</param>
            ///
            GPS_position(float latitude, float longitude, float altitude);

            ~GPS_position();

            ///
            /// <summary>Get sensor data.</summary>
            /// <returns>String containing sensor data.</returns>
            ///
            string get_sensor_data();

            ///
            /// <summary>Get sensor type in a textual form.</summary>
            /// <returns>String representing sensor's type.</returns>
            ///
            string get_sensor_type();

            ///
            /// <summary>Get sensor type as <see cref="Sensor_type" /> enumerable.</summary>
            /// <returns><see cref="Sensor_type" /> enumerable representation of sensor type.</returns>
            ///
            Sensor_type get_sensor_type_int();
        private:
            ///
            /// <summary>Latitude.</summary>
            ///
            float latitude;

            ///
            /// <summary>Longitude.</summary>
            ///
            float longitude;

            /// <summary>Altitude.</summary>
            float altitude;
        };
    }
}

