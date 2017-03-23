#include <chrono>
#include <sstream>
#include <string>
#include <thread>

#include "Temperature.h"
#include "Temperature_sensor_reader.h"

using std::chrono::seconds;
using std::ostringstream;
using std::string;
using std::this_thread::sleep_for;

using Readings::Temperature::Temperature;

namespace Readings {
    namespace Temperature {
        Temperature_sensor_reader::Temperature_sensor_reader() {}

        Temperature_sensor_reader::~Temperature_sensor_reader() {}

        void Temperature_sensor_reader::read() {
            // Values from -10 to -15.
            const float initial_reading = static_cast <float> ((rand() / static_cast <float> (RAND_MAX / 5)) - 10);
            float random_reading = initial_reading;

            for (int i = 0; i < 15; i++) {
                if (i % 2 == 0) {
                    // Increase temperature by max 0.3 degrees.
                    random_reading += static_cast <float> (rand() / static_cast <float> (RAND_MAX / 0.3));
                }
                else {
                    // Decrease temperature by max 0.3 degrees.
                    random_reading -= static_cast <float> (rand() / static_cast <float> (RAND_MAX / 0.3));
                }

                ostringstream sensor_name;
                sensor_name << "Sensor " << (i % 3) + 1; // Have only 3 sensors

                this->readings.push_back(new Temperature(sensor_name.str(), random_reading));
                sleep_for(seconds(1));
            }
        }

        string Temperature_sensor_reader::get_sensor_reader_name() {
            return "Temperature Sensor Reader";
        }

        void Temperature_sensor_reader::set_up() {}
    }
}
