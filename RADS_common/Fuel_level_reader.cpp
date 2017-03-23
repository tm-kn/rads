#include <chrono>
#include <random>
#include <string>
#include <thread>

#include "Fuel_level.h"
#include "Fuel_level_reader.h"

using std::chrono::seconds;
using std::rand;
using std::string;
using std::this_thread::sleep_for;

using Readings::Fuel_level::Fuel_level;

namespace Readings {
    namespace Fuel_level {
        // Set the first reading to be minimum 320000
        float Fuel_level_reader::last_reading = static_cast <float> ((rand() / static_cast <float> (RAND_MAX/100)) + 50000);

        Fuel_level_reader::Fuel_level_reader() {}

        Fuel_level_reader::~Fuel_level_reader() {}

        void Fuel_level_reader::read() {
            float random_reading = Fuel_level_reader::last_reading;

            // Generate random fuel level readings
            for (int i = 0; i < 10; i++) {
                random_reading -= static_cast <float> (rand() / static_cast <float> (RAND_MAX / 0.5)); // Decrease the fuel by max 0.5.
                
                if (random_reading < 0) {
                    random_reading = 0;
                }

                this->readings.push_back(new Fuel_level(random_reading));
                sleep_for(seconds(1));
            }

            Fuel_level_reader::last_reading = random_reading;
        }

        string Fuel_level_reader::get_sensor_reader_name() {
            return "Fuel level sensor reader";
        }

        void Fuel_level_reader::set_up() {}
    }
}
