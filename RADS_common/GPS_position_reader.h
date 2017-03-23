#pragma once
#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
    namespace GPS_position {
        ///
        /// <summary>Represents GPS position reader.</summary>
        ///
        class GPS_position_reader :
            public Sensor_reader
        {
        public:
            GPS_position_reader();
            
            ~GPS_position_reader();

            ///
            /// <summary>Read data from the sensor.</summary>
            ///
            void read();

            ///
            /// <summary>Perform all the necessary set up before reading.</summary>
            ///
            void set_up();

            ///
            /// <summary>Get sensor reader name.</summary>
            /// <returns>String containing sensor reader's title.</returns>
            ///
            string get_sensor_reader_name();
        private:
            ///
            /// <summary>Last readings.</summary>
            ///
           static float last_lat, last_lng, last_alt;
        };
    }
}
