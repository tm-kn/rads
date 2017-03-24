#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/GPS_position.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::GPS_position::GPS_position;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_GPS_position)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->gps_position = new GPS_position(float(76.2021), float(-55.1), float(32122));
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->gps_position;
        }

        TEST_METHOD(test_get_sensor_data) {
            Assert::AreEqual(string("76.2021;-55.1;32122"), gps_position->get_sensor_data());
        }

        TEST_METHOD(test_get_sensor_type_int) {
            Assert::AreEqual(GPS_POSITION_SENSOR, gps_position->get_sensor_type_int());
        }

        TEST_METHOD(test_get_sensor_type) {
            Assert::AreEqual(string("GPS"), gps_position->get_sensor_type());
        }
    private:
        GPS_position * gps_position;
    };
}