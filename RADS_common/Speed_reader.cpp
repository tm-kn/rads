#include <string>

#include "Speed.h"
#include "Speed_reader.h"

using std::string;

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
			for (int i = 0; i <= 25; i++) {
				this->readings.push_back(new Speed(i));
			}

			for (int i = 25; i >= 0; i--) {
				this->readings.push_back(new Speed(i));
			}
		}

		void Speed_reader::set_up() {

		}
	}
}