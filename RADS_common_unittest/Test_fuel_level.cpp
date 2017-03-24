#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Fuel_level.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Fuel_level::Fuel_level;

namespace RADS_common_unittest
{		
	TEST_CLASS(Test_fuel_level)
	{
	public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->fuel_level = new Fuel_level(float(10.123));
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->fuel_level;
        }

		TEST_METHOD(test_get_sensor_data) {
            Assert::AreEqual(string("10.123"), fuel_level->get_sensor_data());
		}

        TEST_METHOD(test_get_sensor_type_int) {
            Assert::AreEqual(FUEL_LEVEL_SENSOR, fuel_level->get_sensor_type_int());
        }

        TEST_METHOD(test_get_sensor_type) {
            Assert::AreEqual(string("FUEL"), fuel_level->get_sensor_type());
        }
    private:
        Fuel_level * fuel_level;
	};
}