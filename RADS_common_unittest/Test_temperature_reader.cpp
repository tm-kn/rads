#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Temperature_sensor_reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Temperature::Temperature_sensor_reader;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_temperature_reader)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->temperature_reader = new Temperature_sensor_reader();
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->temperature_reader;
        }

        ///
        /// <summary>Make sure that initially readings list is empty.</summary>
        ///
        TEST_METHOD(test_empty_readings_before_read) {
            Assert::IsTrue(this->temperature_reader->get_readings().size() == 0);
        }

        ///
        /// <summary>Make sure <see cref="Temperature_sensor_reader::read" /> generates readings.</summary>
        ///
        TEST_METHOD(test_read) {
            this->temperature_reader->read();

            Assert::IsTrue(this->temperature_reader->get_readings().size() > 0);
        }
    private:
        Temperature_sensor_reader * temperature_reader;
    };
}