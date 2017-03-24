#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../RADS_common/Fuel_level_reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

using Readings::Fuel_level::Fuel_level_reader;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_fuel_level_reader)
    {
    public:
        TEST_METHOD_INITIALIZE(initialize) {
            this->fuel_level_reader = new Fuel_level_reader();
        }

        TEST_METHOD_CLEANUP(cleanup) {
            delete this->fuel_level_reader;
        }

        ///
        /// <summary>Make sure that initially readings list is empty.</summary>
        ///
        TEST_METHOD(test_empty_readings_before_read) { 
            Assert::IsTrue(this->fuel_level_reader->get_readings().size() == 0);
        }

        ///
        /// <summary>Make sure <see cref="Fuel_level_reader::read" /> generates readings.</summary>
        ///
        TEST_METHOD(test_read) {
            this->fuel_level_reader->read();
             
            Assert::IsTrue(this->fuel_level_reader->get_readings().size() > 0);
        }
    private:
        Fuel_level_reader * fuel_level_reader;
    };
}   