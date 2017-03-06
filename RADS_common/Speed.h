#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
	namespace Speed {
		class Speed :
			public Sensor
		{
		public:
			Speed(float speed);
			~Speed();
			string to_string();
		private:
			float speed;
		};
	}
}