#pragma once

#include <string>
#include <vector>

#include "../RADS_common/Sensor.h"

using std::string;
using std::vector;

using Readings::Sensor;

namespace Readings {
    class Sensor_reader
    {
    public:
        Sensor_reader();
        ~Sensor_reader();
        vector<Sensor*> get_readings();
        void clear_readings();
        virtual void read() = 0;
        virtual void set_up() = 0;
        virtual string get_sensor_reader_name() = 0;
    protected:
        vector<Sensor*> readings;
    };
}
