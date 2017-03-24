#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/GPS_position_reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::GPS_position::GPS_position_reader;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_GPS_position_reader)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->gps_position_reader = new GPS_position_reader();
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->gps_position_reader;
        }

        ///
        /// <summary>Make sure that initially readings list is empty.</summary>
        ///
        TEST_METHOD(test_empty_readings_before_read) {
            Assert::IsTrue(this->gps_position_reader->get_readings().size() == 0);
        }

        ///
        /// <summary>Make sure <see cref="GPS_position_reader::read" /> generates readings.</summary>
        ///
        TEST_METHOD(test_read) {
            this->gps_position_reader->read();

            Assert::IsTrue(this->gps_position_reader->get_readings().size() > 0);
        }
    private:
        GPS_position_reader * gps_position_reader;
    };
}