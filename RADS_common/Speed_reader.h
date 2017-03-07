#pragma once

#include <string>

#include "Sensor_reader.h"

using std::string;

using Readings::Sensor_reader;

namespace Readings {
    namespace Speed {
        class Speed_reader :
            public Sensor_reader
        {
        public:
            Speed_reader();
            ~Speed_reader();
            string get_sensor_reader_name();
            void read();
            void set_up();
        };


    }
}
