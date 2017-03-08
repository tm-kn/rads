#include <ctime>
#include <sstream>
#include <string>
#include <iostream>

#include "Sensor.h"

using std::endl;
using std::ostringstream;
using std::string;
using std::time;
using std::time_t;

namespace Readings {
    Sensor::Sensor() {
        this->datetime = std::time(NULL);
    }

    string Sensor::to_string() {
        ostringstream string_stream;
        string_stream << "[" << this->get_sensor_type() << "]" << this->get_sensor_data() << endl;
        return string_stream.str();
    }

    time_t Sensor::get_datetime() {
        return this->datetime;
    }

    void Sensor::set_datetime(time_t datetime) {
        this->datetime = datetime;
    }
}
