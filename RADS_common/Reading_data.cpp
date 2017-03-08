#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "Reading_data.h"
#include "Sensor.h"
#include "Fuel_level.h"
#include "Speed.h"
#include "Temperature.h"
#include "GPS_position.h"

using std::cout;
using std::endl;
using std::sort;
using std::string;
using std::time_t;
using std::vector;

namespace Readings {
    /**
        Sort sensors by their reading date ascendingly.
    */
    bool way_to_sort(Sensor* sensor_one, Sensor* sensor_two) {
        return sensor_one->get_datetime() < sensor_two->get_datetime();
    }

    Reading_data::Reading_data(time_t start_datetime, time_t end_datetime, vector<Sensor*> sensor_data)
    {
        this->reading_start_datetime = start_datetime;
        this->reading_end_datetime = end_datetime;
        this->sensor_data = sensor_data;

        sort(this->sensor_data.begin(), this->sensor_data.end(), way_to_sort);
    }


    Reading_data::~Reading_data()
    {
    }

    vector<Sensor*> Reading_data::get_data() {
        return this->sensor_data;
    }

    time_t Reading_data::get_reading_start_datetime() {
        return this->reading_start_datetime;
    }

    time_t Reading_data::get_reading_end_datetime() {
        return this->reading_end_datetime;
    }

    Sensor * Reading_data::convert_packet_to_sensor(Packet packet) {
        string data_string(packet.data);

        if (string(packet.data_type) == "GPS") {
            vector<string> tokens;

            size_t pos = 0;
            std::string token;
            while ((pos = data_string.find(';')) != std::string::npos) {
                tokens.push_back(data_string.substr(0, pos));
                data_string.erase(0, pos + 1);
            }

            tokens.push_back(data_string);

            GPS_position::GPS_position * gps_pos = new GPS_position::GPS_position(stof(tokens[0]), stof(tokens[1]), stof(tokens[2]));
            gps_pos->set_datetime(packet.datetime);
            return gps_pos;
        }
        else if (string(packet.data_type) == "FUEL") {
            Fuel_level::Fuel_level * fuel = new Fuel_level::Fuel_level(stof(data_string));
            fuel->set_datetime(packet.datetime);
            return fuel;
;        }
        else if (string(packet.data_type) == "TMP") {
            vector<string> tokens;

            size_t pos = 0;
            std::string token;
            while ((pos = data_string.find(';')) != std::string::npos) {
                tokens.push_back(data_string.substr(0, pos));
                data_string.erase(0, pos + 1);
            }

            tokens.push_back(data_string);

            Temperature::Temperature * temperature = new Temperature::Temperature(tokens[0], stof(tokens[1]));
            temperature->set_datetime(packet.datetime);
            return temperature;
        }
        else if (string(packet.data_type) == "SPEED") {
            Speed::Speed * speed = new Speed::Speed(stof(data_string));
            speed->set_datetime(packet.datetime);
            return speed;
        }
        else {
            cout << "Reading Data: Unknown packet data type " << packet.data_type << endl;
            return NULL;
        }
    }
}
