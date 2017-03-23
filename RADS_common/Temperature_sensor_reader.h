#pragma once

#include <string>
#include <map>

#include "Sensor_reader.h"

using std::map;
using std::string;

using Readings::Sensor_reader;

namespace Readings {
    ///
    /// <summary>Temperature sensor reader.</summary>
    ///
    namespace Temperature {
        class Temperature_sensor_reader :
            public Sensor_reader
        {
        public:
            Temperature_sensor_reader();

            ~Temperature_sensor_reader();

            ///
            /// <summary>Get sensor reader name.</summary>
            /// <returns><see cref="string" /> representation of sensor reader's title.</returns>
            ///
            string get_sensor_reader_name();

            ///
            /// <summary>Perform sensor reading.</summary>
            ///
            void read();

            ///
            /// <summary>Perform sensor reader's necessary set up before reading.</summary>
            ///
            void set_up();
        };
    }
}
