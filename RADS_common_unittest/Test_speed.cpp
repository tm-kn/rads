#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Speed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Speed::Speed;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_speed)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->speed = new Speed(float(675.21));
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->speed;
        }

        TEST_METHOD(test_get_sensor_data) {
            Assert::AreEqual(string("675.21"), speed->get_sensor_data());
        }

        TEST_METHOD(test_get_sensor_type_int) {
            Assert::AreEqual(SPEED_SENSOR, speed->get_sensor_type_int());
        }

        TEST_METHOD(test_get_sensor_type) {
            Assert::AreEqual(string("SPEED"), speed->get_sensor_type());
        }
    private:
        Speed * speed;
    };
}