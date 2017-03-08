#include <vector>

#include "Sensor.h"
#include "Sensor_reader.h"

using std::vector;
using Readings::Sensor;

namespace Readings {
    Sensor_reader::Sensor_reader()
    {
    }


    Sensor_reader::~Sensor_reader()
    {
    }

    vector<Sensor*> Sensor_reader::get_readings()
    {
        return this->readings;
    }

    void Sensor_reader::clear_readings() {
        this->readings.clear();
    }

    void Sensor_reader::read()
    {
    }

    void Sensor_reader::set_up()
    {
    }
}
