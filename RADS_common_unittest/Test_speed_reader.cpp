#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Speed_reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Speed::Speed_reader;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_speed_reader)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->speed_reader = new Speed_reader();
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->speed_reader;
        }

        ///
        /// <summary>Make sure that initially readings list is empty.</summary>
        ///
        TEST_METHOD(test_empty_readings_before_read) {
            Assert::IsTrue(this->speed_reader->get_readings().size() == 0);
        }

        ///
        /// <summary>Make sure <see cref="Speed_reader::read" /> generates readings.</summary>
        ///
        TEST_METHOD(test_read) {
            this->speed_reader->read();

            Assert::IsTrue(this->speed_reader->get_readings().size() > 0);
        }
    private:
        Speed_reader * speed_reader;
    };
}