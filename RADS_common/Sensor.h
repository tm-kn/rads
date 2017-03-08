#pragma once

#include <ctime>
#include <string>

using std::string;
using std::time;
using std::time_t;

enum Sensor_type { GPS_POSITION_SENSOR = 1, FUEL_LEVEL_SENSOR = 2, SPEED_SENSOR = 3, TEMPERATURE_SENSOR = 4 };

namespace Readings {
    class Sensor
    {
    public:
        Sensor();
        time_t get_datetime();
        void set_datetime(time_t datetime);
        virtual string to_string();
        virtual string get_sensor_type() = 0;
        virtual string get_sensor_data() = 0;
        virtual int get_sensor_type_int() = 0;
    private:
        time_t datetime;
    };
}
