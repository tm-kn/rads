#pragma once

#include <string>
#include <vector>

#include "../RADS_common/Sensor.h"

using std::string;
using std::vector;

using Readings::Sensor;

namespace Readings {
    ///
    /// <summary>Abstract class that represents s ensor reader.</summary>
    ///
    class Sensor_reader
    {
    public:
        Sensor_reader();

        ~Sensor_reader();

        ///
        /// <summary>Get readings from the sensor reader.</summary>
        /// <returns><see cref="vector" /> of pointers to <see cref="Sensor" /> derviced classes' instances.</returns>
        ///
        vector<Sensor*> get_readings();

        ///
        /// <summary>Clear readings currently on the reader instance.</summary>
        ///
        void clear_readings();

        ///
        /// <summary>Read the sensor reader.</summary>
        ///
        virtual void read() = 0;

        ///
        /// <summary>Perform necessary set up for the sensor reader.</summary>
        ///
        virtual void set_up() = 0;

        ///
        /// <summary>Get sensor reader name.</summary>
        /// <returns>String representing the reader's title.</returns>
        ///
        virtual string get_sensor_reader_name() = 0;
    protected:
        ///
        /// <summary>Collection of sensor readings.</summary>
        ///
        vector<Sensor*> readings;
    };
}
