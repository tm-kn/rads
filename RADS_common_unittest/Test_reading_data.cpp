#include "stdafx.h"
#include "CppUnitTest.h"
#include <ctime>
#include <string>
#include <vector>

#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Fuel_level.h"
#include "../RADS_common/Speed.h"
#include "../RADS_common/Temperature.h"
#include "../RADS_common/GPS_position.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::time;
using std::time_t;
using std::vector;

using Readings::GPS_position::GPS_position;
using Readings::Reading_data;
using Readings::Speed::Speed;
using Readings::Fuel_level::Fuel_level;
using Readings::Temperature::Temperature;

namespace RADS_common_unittest
{
    TEST_CLASS(Test_reading_data)
    {
    public:
        TEST_METHOD(test_reading_data_new_instance) {
            time_t start_time = time(NULL);

            vector <Sensor*> readings;

            time_t end_time = time(NULL);

            Reading_data reading_data(start_time, end_time, readings);

            Assert::IsTrue(start_time == reading_data.get_reading_start_datetime());
            Assert::IsTrue(end_time == reading_data.get_reading_end_datetime());
            Assert::IsTrue(reading_data.get_data().size() == 0);
        }

        TEST_METHOD(test_reading_data_add_new_readings) {
            time_t start_time = time(NULL);

            vector <Sensor*> readings;

            for (int i = 0; i < 40; i++) {
                if (i % 2 == 0) {
                    readings.push_back(new Fuel_level(float(i)));
                }
                else {
                    readings.push_back(new Speed(float(i*100)));
                }
            }

            time_t end_time = time(NULL);

            Reading_data reading_data(start_time, end_time, readings);

            Assert::IsTrue(start_time == reading_data.get_reading_start_datetime());
            Assert::IsTrue(end_time == reading_data.get_reading_end_datetime());
            Assert::IsTrue(reading_data.get_data().size() == 40);
        }

        TEST_METHOD(test_convert_packet_to_fuel_sensor) {
            Fuel_level fuel_level(float(1232.2));

            Packet packet;
            packet.datetime = fuel_level.get_datetime();
            packet.data_type = fuel_level.get_sensor_type_int();
            packet.packet_type = DATA_EVENT;

            strcpy_s(packet.data, sizeof packet.data, fuel_level.get_sensor_data().c_str());
            strcpy_s(packet.sender_id, sizeof packet.sender_id, string("ABC213123").c_str());

            Sensor* deserialized_sensor = Reading_data::convert_packet_to_sensor(packet);

            Assert::AreEqual(fuel_level.get_sensor_data(), deserialized_sensor->get_sensor_data());
            Assert::IsTrue(fuel_level.get_datetime() == deserialized_sensor->get_datetime());
        }

        TEST_METHOD(test_convert_packet_to_speed_sensor) {
            Speed speed(float(560.2));

            Packet packet;
            packet.datetime = speed.get_datetime();
            packet.data_type = speed.get_sensor_type_int();
            packet.packet_type = DATA_EVENT;

            strcpy_s(packet.data, sizeof packet.data, speed.get_sensor_data().c_str());
            strcpy_s(packet.sender_id, sizeof packet.sender_id, string("ABC213123").c_str());

            Sensor* deserialized_sensor = Reading_data::convert_packet_to_sensor(packet);

            Assert::AreEqual(speed.get_sensor_data(), deserialized_sensor->get_sensor_data());
            Assert::IsTrue(speed.get_datetime() == deserialized_sensor->get_datetime());
        }

        TEST_METHOD(test_convert_packet_to_temperature_sensor) {
            Temperature temperature(string("Sensor sample 1"), float(560.2));

            Packet packet;
            packet.datetime = temperature.get_datetime();
            packet.data_type = temperature.get_sensor_type_int();
            packet.packet_type = DATA_EVENT;

            strcpy_s(packet.data, sizeof packet.data, temperature.get_sensor_data().c_str());
            strcpy_s(packet.sender_id, sizeof packet.sender_id, string("ABC213123").c_str());

            Sensor* deserialized_sensor = Reading_data::convert_packet_to_sensor(packet);

            Assert::AreEqual(temperature.get_sensor_data(), deserialized_sensor->get_sensor_data());
            Assert::IsTrue(temperature.get_datetime() == deserialized_sensor->get_datetime());
        }
    };
}