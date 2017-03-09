#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
    namespace Temperature {
        ///
        /// <summary>Represents a temperature sensor reading.</summary>
        ///
        class Temperature :
            public Sensor
        {
        public:
            ///
            /// <summary>Instantiate a temperature reading.</summary>
            /// <param name="sensor_name">Temperature sensor name.</param>
            /// <param name="temperature">Floating point representing temperature.</param>
            ///
            Temperature(string sensor_name, double temperature);

            ~Temperature();

            ///
            /// <summary>Get sensor data.</summary>
            /// <returns>Sensor data represented as <see cref="string" />.</returns>
            ///
            string get_sensor_data();

            ///
            /// <summary>Get sensor type.</summary>
            /// <returns>Sensor type represented as <see cref="string" />.</returns>
            ///
            string get_sensor_type();

            ///
            /// <summary>Get sensor type conforming with <see cref="Sensor_type" /> enumerable.</summary>
            /// <returns>Integer representing sensor type.</returns>
            ///
            Sensor_type get_sensor_type_int();
        private:
            ///
            /// <summary>Floating point representation of temperature.</summary>
            ///
            double temperature;

            ///
            /// <summary>Temperature sensor ID.</summary>
            ///
            string sensor_name;
        };
    }
}
