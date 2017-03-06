#pragma once

#include <string>

#include "Sensor.h"

using std::string;

using Readings::Sensor;

namespace Readings {
	namespace Fuel_level {
		class Fuel_level :
			public Sensor
		{
		public:
			Fuel_level(float fuel_level);
			~Fuel_level();
		private:
			float fuel_level;
		public:
			string to_string();
		};

	}
}

