#include <chrono>
#include <random>
#include <string>
#include <thread>

#include "GPS_position_reader.h"
#include "GPS_position.h"

using std::chrono::seconds;
using std::string;
using std::this_thread::sleep_for;
using std::rand;

using Readings::GPS_position::GPS_position;

namespace Readings {
    namespace GPS_position {
        float GPS_position_reader::last_lat = 0.0;
        float GPS_position_reader::last_lng = 0.0;
        float GPS_position_reader::last_alt = 0.0;

        GPS_position_reader::GPS_position_reader() {}

        GPS_position_reader::~GPS_position_reader() {}

        void GPS_position_reader::read() {
            // Generate random GPS readings.
            const float initial_reading_lat = static_cast<float> (rand() / static_cast<float> (RAND_MAX/180));
            const float initial_reading_lng = static_cast<float> (rand() / static_cast<float> (RAND_MAX/180));
            const float initial_reading_alt = static_cast<float> (rand() / static_cast<float> (RAND_MAX/180));

            // Assign current reading to the initial ones.
            float random_lat = initial_reading_lat;
            float random_lng = initial_reading_lng;
            float random_alt = initial_reading_alt;

            // If there are any reading saved on the static properties of the class, use them as the current ones.
            if (GPS_position_reader::last_lat) {
                random_lat = GPS_position_reader::last_lat;
            }

            if (GPS_position_reader::last_lng) {
                random_lng = GPS_position_reader::last_lng;
            }

            if (GPS_position_reader::last_alt) {
                random_alt = GPS_position_reader::last_alt;
            }
             
            // Add 10 readings
            for (int i = 0; i < 10; i++) {
                this->readings.push_back(new GPS_position(random_lat, random_lng, random_alt));
                sleep_for(seconds(1));

                // Generate random decimal number from and add it to the previous readings.
                random_lat += static_cast<float> (rand() / static_cast<float> (RAND_MAX/0.5)); // Add 0 - 0.5 for latitude
                random_lng += static_cast<float> (rand() / static_cast<float> (RAND_MAX/0.5)); // Add 0 - 0.5 for longitude
                random_alt += static_cast<float> (rand() / static_cast<float> (RAND_MAX/0.001));  // Add 0 - 0.001 for altitude
            }

            // Assign last readings to the static variables so they're kept for the next readings
            GPS_position_reader::last_lat = random_lat;
            GPS_position_reader::last_lng = random_lng;
            GPS_position_reader::last_alt = random_alt;
        }

        void GPS_position_reader::set_up() {}

        string GPS_position_reader::get_sensor_reader_name() {
            return "GPS Position Sensor Reader";
        }
    }
}
