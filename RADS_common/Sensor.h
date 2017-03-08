#pragma once

#include <ctime>
#include <string>

using std::string;
using std::time;
using std::time_t;

namespace Readings {
    class Sensor
    {
    public:
        Sensor();
        time_t get_datetime();
        virtual string to_string();
        virtual string get_sensor_type() = 0;
        virtual string get_sensor_data() = 0;
    private:
        time_t datetime;
    };
}
