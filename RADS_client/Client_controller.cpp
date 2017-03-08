#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>

#include "Client_controller.h"
#include "Base_state.h"
#include "Connecting_state.h"
#include "Reading_state.h"
#include "Sending_state.h"
#include "../RADS_common/Fuel_level_reader.h"
#include "../RADS_common/GPS_position_reader.h"
#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor.h"
#include "../RADS_common/Sensor_reader.h"
#include "../RADS_common/Speed_reader.h"
#include "../RADS_common/Temperature_sensor_reader.h"

using std::cout;
using std::endl;
using std::logic_error;
using std::ostringstream;

using Readings::Fuel_level::Fuel_level_reader;
using Readings::GPS_position::GPS_position_reader;
using Readings::Reading_data;
using Readings::Sensor;
using Readings::Sensor_reader;
using Readings::Speed::Speed_reader;
using Readings::Temperature::Temperature_sensor_reader;

namespace RADS_client {
    Client_controller::Client_controller()
    {
        // Add sensor readers
        this->sensor_readers.push_back(new GPS_position_reader());
        this->sensor_readers.push_back(new Temperature_sensor_reader());
        this->sensor_readers.push_back(new Fuel_level_reader());
        this->sensor_readers.push_back(new Speed_reader());

        // Generate random ID
        const void * address = static_cast<const void*>(this);
        ostringstream string_stream;
        string_stream << address;
        this->id = string_stream.str();

        cout << "Client Controller: Sender ID set to " << this->id << endl;
    }

    Client_controller::~Client_controller()
    {
    }

    void Client_controller::perform() {
        State::Base* state = NULL;

        switch (this->current_state) {
        case READING:
            state = new State::Reading();
            break;
        case CONNECTING:
            state = new State::Connecting();
            break;
        case SENDING:
            state = new State::Sending();
            break;
        default:
            throw logic_error("Client controller is in not-existent state");
        }

        state->set_client_controller(this);
        state->perform();

        delete state;
    }

    void Client_controller::start_communicating()
    {
        // Create new network client
        delete this->network_client;
        this->network_client = new Network_client();

        this->set_state(CONNECTING);
        this->perform();
   
        this->set_state(SENDING);
        this->perform();
    }

    void Client_controller::start_reading()
    {
        this->set_state(READING);
        this->perform();
    }

    Network_client* Client_controller::get_network_client() {
        return this->network_client;
    }

    vector<Sensor_reader*> Client_controller::get_sensor_readers() {
        return this->sensor_readers;
    }

    Reading_data* Client_controller::get_reading_data() {
        vector<Sensor*> data;
        time_t min_time = 0;
        time_t max_time = 0;

        for (Sensor_reader *sensor_reader : this->sensor_readers) {
            for (Sensor *sensor : sensor_reader->getReadings()) {
                if (!min_time || sensor->get_datetime() < min_time) {
                    min_time = sensor->get_datetime();
                }

                if (sensor->get_datetime() > max_time) {
                    max_time = sensor->get_datetime();
                }

                data.push_back(sensor);
            }
        }

        return new Reading_data(min_time, max_time, data);
    }

    void Client_controller::set_state(Client_controller_state state) {
        this->current_state = state;
    }

    string Client_controller::get_id() {
        return this->id;
    }
}
