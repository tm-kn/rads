#pragma once

#include <ctime>
#include <string>

using std::string;
using std::time;
using std::time_t;

///
/// <summary>Sensor type enumerable. Used when deserializing data to determine which sensor type the reading belongs to.</summary>
///
enum Sensor_type {
    GPS_POSITION_SENSOR = 1,
    FUEL_LEVEL_SENSOR = 2,
    SPEED_SENSOR = 3,
    TEMPERATURE_SENSOR = 4
};

namespace Readings {
    ///
    /// <summary>Base class for all the sensor readings. Represents a sensor reading.</summary>
    ///
    class Sensor
    {
    public:
        Sensor();

        ~Sensor();

        ///
        /// <summary>Get time of the reading.</summary>
        /// <returns><see cref="time_t" /> of the reading.</returns>
        ///
        time_t get_datetime();

        ///
        /// <summary>Set time of the reading, useful for serializing objects from packets.</summary>
        /// <param name="datetime"><see cref="time_t" /></param>
        ///
        void set_datetime(time_t datetime);

        ///
        /// <summary>Output sensor object to string. For visual representation.</summary>
        /// <returns>String representation of the sensor object.</returns>
        ///
        virtual string to_string();

        ///
        /// <summary>Get sensor type's textual representation.</summary>
        /// <returns>String of sensor type.</returns>
        ///
        virtual string get_sensor_type() = 0;

        ///
        /// <summary>Get sensor data.</summary>
        /// <returns>String with sensor data.</returns>
        virtual string get_sensor_data() = 0;

        ///
        /// <summary>Get sensor type integer that confroms with <see cref="Sensor_type" /> enumerable.</summary>
        /// <returns>Sensor type integer.</returns>
        ///
        virtual Sensor_type get_sensor_type_int() = 0;
    private:
        ///
        /// <summary>Reading time.</summary>
        ///
        time_t datetime;
    };
}
