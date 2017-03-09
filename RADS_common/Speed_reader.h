#pragma once

#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
    namespace Speed {
        ///
        /// <summary>Speed reader.</summary>
        ///
        class Speed_reader :
            public Sensor_reader
        {
        public:
            Speed_reader();

            ~Speed_reader();

            ///
            /// <summary>Get sensor reader name</summary>
            /// <returns>String representation of sensor reader name.</returns>
            ///
            string get_sensor_reader_name();

            ///
            /// <summary>Perform reading.</summary>
            ///
            void read();

            ///
            /// <summary>Perform necessary set up for the reading.</summary>
            ///
            void set_up();
        };
    }
}
