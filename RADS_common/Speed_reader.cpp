#include <chrono>
#include <random>
#include <string>
#include <thread>

#include "Speed.h"
#include "Speed_reader.h"

using std::chrono::seconds;
using std::rand;
using std::string;
using std::this_thread::sleep_for;

using Readings::Speed::Speed;

namespace Readings {
    namespace Speed {
        Speed_reader::Speed_reader() {}

        Speed_reader::~Speed_reader() {}

        string Speed_reader::get_sensor_reader_name() {
            return "Speed sensor reader";
        }

        void Speed_reader::read() {
            // Speeds of 120 - 200 for initial reading.
            const float initial_speed = static_cast <float> ((rand() / static_cast <float> (RAND_MAX/80)) + 120);
            float random_speed = initial_speed;

            // Add ten records
            for (int i = 0; i <= 10; i++) {
                if (i % 3 == 0) {
                    // Decrease by max 5
                    random_speed -= static_cast <float> (rand() / static_cast <float> (RAND_MAX / 5));
                }
                else {
                    // Increase max by 2
                    random_speed += static_cast <float> (rand() / static_cast <float> (RAND_MAX / 2));
                }

                this->readings.push_back(new Speed(random_speed));
                sleep_for(seconds(1));
            }
        }

        void Speed_reader::set_up() {}
    }
}
