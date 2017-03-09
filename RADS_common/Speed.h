#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
    namespace Speed {
        ///
        /// <summary>Represents a speed reading.</summary>
        ///
        class Speed :
            public Sensor
        {
        public:
            ///
            /// <summary>Instantiate a speed reading.</summary>
            /// <param name="speed">Floating point representation of the speed value.</param>
            ///
            Speed(float speed);

            ~Speed();

            ///
            /// <summary>Get sensor data.</summary>
            /// <returns>String of sensor data.</returns>
            ///
            string get_sensor_data();

            ///
            /// <summary>Get textual representation of sensor type.</summary>
            /// <returns>String containing sensor type.</returns>
            ///
            string get_sensor_type();

            ///
            /// <summary>Get sensor type conforting with <see cref="Sensor_type" /> enumerable.</summary>
            /// <returns>Sensor type integer.</returns>
            ///
            Sensor_type get_sensor_type_int();
        private:
            ///
            /// <summary>Floating point representation of the speed value.</summary>
            ///
            float speed;
        };
    }
}
