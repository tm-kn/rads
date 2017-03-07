#include <algorithm>
#include <ctime>
#include <vector>

#include "Reading_data.h"
#include "Sensor.h"

using std::sort;
using std::time_t;
using std::vector;

using Readings::Sensor;

namespace Readings {
    /**
        Sort sensors by their reading date ascendingly.
    */
    bool way_to_sort(Sensor* sensor_one, Sensor* sensor_two) {
        return sensor_one->get_datetime() < sensor_two->get_datetime();
    }

    Reading_data::Reading_data(time_t start_datetime, time_t end_datetime, vector<Sensor*> sensor_data)
    {
        this->reading_start_datetime = start_datetime;
        this->reading_end_datetime = end_datetime;
        this->sensor_data = sensor_data;

        sort(this->sensor_data.begin(), this->sensor_data.end(), way_to_sort);
    }


    Reading_data::~Reading_data()
    {
    }

    vector<Sensor*> Reading_data::get_data() {
        return this->sensor_data;
    }

    time_t Reading_data::get_reading_start_datetime() {
        return this->reading_start_datetime;
    }

    time_t Reading_data::get_reading_end_datetime() {
        return this->reading_end_datetime;
    }
}
