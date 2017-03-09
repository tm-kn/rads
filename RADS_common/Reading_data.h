#pragma once

#include <ctime>
#include <vector>

#include "Sensor.h"
#include "Network_data.h"

using std::time_t;
using std::vector;

using Readings::Sensor;

namespace Readings {
    ///
    /// <summary>Container that stored data from one reading.</summary>
    ///
    class Reading_data
    {
    public:
        ///
        /// <summary>Instantiate object of <see cref="Reading_data" />.</summary>
        /// <param name="start_datetime">Time the reading started.</param>
        /// <param name="end_datetime">Time the reading ended.</param>
        /// <param name="sensor_data">List of sensor readings associated with this particular reading.</param>
        ///
        Reading_data(time_t start_datetime, time_t end_datetime, vector<Sensor*> sensor_data);

        ~Reading_data();

        ///
        /// <summary>Get sensor data associated with this reading.</summary>
        /// <returns>Vector of <see cref="Sensor" /> instances.</returns>
        ///
        vector<Sensor*> get_data();

        ///
        /// <summary>Get reading start time.</summary>
        /// <returns><see cref="time_t" /> readings start time.</returns>
        ///
        time_t get_reading_start_datetime();

        ///
        /// <summary>Get reading finish time.</summary>
        /// <returns><see cref="time_t" /> readings finish time.</returns>
        ///
        time_t get_reading_end_datetime();

        ///
        /// <summary>Statis helper used to convert packet to <see cref="Sensor" /> object.</summary>
        /// <param name="packet"><see cref="Packet" /> instance.</param>
        /// <returns><see cref="Sensor" /> instance. NULL if not possible to convert.</returns>
        ///
        static Sensor * convert_packet_to_sensor(Packet packet);
    private:
        ///
        /// <summary>Time the reading started.</summary>
        ///
        time_t reading_start_datetime;

        ///
        /// <summary>Time the reading ended.</summary>
        ///
        time_t reading_end_datetime;

        ///
        /// <summary>Associated sensor data - <see cref="vector" /> of <see cref="Sensor" /> instances.</summary>
        ///
        vector<Sensor*> sensor_data;
    };
}
