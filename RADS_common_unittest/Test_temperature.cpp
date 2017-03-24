#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Temperature.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Temperature::Temperature;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_temperature)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->temperature = new Temperature(string("Example sensor"), float(-10.21));
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->temperature;
        }

        TEST_METHOD(test_get_sensor_data) {
            Assert::AreEqual(string("Example sensor;-10.21"), temperature->get_sensor_data());
        }

        TEST_METHOD(test_get_sensor_type_int) {
            Assert::AreEqual(TEMPERATURE_SENSOR, temperature->get_sensor_type_int());
        }

        TEST_METHOD(test_get_sensor_type) {
            Assert::AreEqual(string("TMP"), temperature->get_sensor_type());
        }
    private:
        Temperature * temperature;
    };
}