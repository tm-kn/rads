#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
    namespace Speed {
        class Speed :
            public Sensor
        {
        public:
            Speed(float speed);
            ~Speed();
            string get_sensor_data();
            string get_sensor_type();
            int get_sensor_type_int();
        private:
            float speed;
        };
    }
}
