#include <chrono>
#include <string>
#include <thread>

#include "Speed.h"
#include "Speed_reader.h"

using std::chrono::seconds;
using std::string;
using std::this_thread::sleep_for;

using Readings::Speed::Speed;

namespace Readings {
	namespace Speed {
		Speed_reader::Speed_reader()
		{
		}


		Speed_reader::~Speed_reader()
		{
		}

		string Speed_reader::get_sensor_reader_name() {
			return "Speed sensor reader";
		}

		void Speed_reader::read() {
			for (int i = 0; i <= 10; i++) {
				this->readings.push_back(new Speed(i));
				sleep_for(seconds(1));
			}
				
			for (int i = 10; i >= 0; i--) {
				this->readings.push_back(new Speed(i));
				sleep_for(seconds(1));
			}
		}

		void Speed_reader::set_up() {

		}
	}
}