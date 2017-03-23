#pragma once

#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
    namespace Fuel_level {
        ///
        /// <summary>Represents fuel level sensor reader.</summary>
        ///
        class Fuel_level_reader :
            public Sensor_reader
        {
        public:
            Fuel_level_reader();
            ~Fuel_level_reader();

            ///
            /// <summary>Perform sensor reading.</summary>
            ///
            void read();

            ///
            /// <summary>Perform all necessary sensor reader's set up.</summary>
            ///
            void set_up();

            ///
            /// <summary>Get textual form of sensor reader's name.</summary>
            /// <returns>String with sensor reader's name.</returns>
            ///
            string get_sensor_reader_name();
        private:
            ///
            /// <summary>Last reading of the sensor.</summary>
            ///
            static float last_reading;
        };
    }
}
