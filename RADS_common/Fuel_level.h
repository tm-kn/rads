#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
    ///
    /// <summary>Represents a fuel level reading.</summary>
    ///
    namespace Fuel_level {
        class Fuel_level :
            public Sensor
        {
        public:
            ///
            /// <summary>Instantiate a fuel level reading as an object.</summary>
            /// <param name="fuel_level">Floating point representing the current fuel state.</param>
            ///
            Fuel_level(float fuel_level);

            ~Fuel_level();

            ///
            /// <summary>Get a textual representation of the sensor type.</summary>
            /// <returns>String with sensor type.</returns>
            ///
            string get_sensor_type();

            ///
            /// <summary>Get sensor data.</summary>
            /// <returns>String with all the sensor data.</returns>
            ///
            string get_sensor_data();

            ///
            /// <summary>Get sensor type integer, use <see cref="Sensor_type" /> enumerable for it.</summary>
            ///
            Sensor_type get_sensor_type_int();
        private:
            float fuel_level;
        };

    }
}

