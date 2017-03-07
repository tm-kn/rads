#include <ctime>
#include <string>
#include <iostream>

#include "Sensor.h"

using std::string;
using std::time;
using std::time_t;

namespace Readings {
    Sensor::Sensor() {
        this->datetime = std::time(NULL);
    }

    string Sensor::to_string() {
        return "Unknown sensor";
    }

    time_t Sensor::get_datetime() {
        return this->datetime;
    }
}
