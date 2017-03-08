#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
    namespace Temperature {
        class Temperature :
            public Sensor
        {
        public:
            Temperature(string sensor_name, double temperature);
            ~Temperature();
            string get_sensor_data();
            string get_sensor_type();
        private:
            double temperature;
            string sensor_name;
        };
    }
}
