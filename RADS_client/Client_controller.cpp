#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>

#include "Client_controller.h"
#include "Base_state.h"
#include "Connecting_state.h"
#include "Reading_state.h"
#include "Sending_state.h"

#include "../RADS_common/Sensor.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::logic_error;
using std::ostringstream;
using std::this_thread::sleep_for;
using std::time;

using Readings::Sensor;

namespace RADS_client {
    Client_controller::Client_controller(string id, vector<Sensor_reader*> sensor_readers,
            int transmission_frequency, int data_hourly_limit, string ip, int port
    ) {
        // Add sensor readers
        for (Sensor_reader * reader : sensor_readers) {
            this->sensor_readers.push_back(reader);
        }
        
        // Set transmission frequency
        this->transmission_frequency = transmission_frequency;
        
        // Set ID
        this->id = id;

        // Set data limitations
        this->data_hourly_limit = data_hourly_limit;
        this->data_period_start_datetime = time(NULL);
        this->data_sent_bytes = 0;

        // Set IP and port
        this->ip = ip;
        this->port = port;
          
        cout << "Client controller: Using IP Address " << this->ip << endl;
        cout << "Client controller: Using port " << this->port << endl;
        cout << "Client controller: Transmision frequency set to " << this->transmission_frequency << " seconds." << endl;
        cout << "Client Controller: Sender ID set to " << this->id << endl;
        cout << "Client Controller: Hourly data limitation set to " << this->data_hourly_limit << " bytes" << endl << endl;
    }

    Client_controller::~Client_controller() {}

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

        // Delete pointer to the state after it's done doing its job.
        delete state;
    }

    void Client_controller::start_communicating() {
        // Create new network client
        delete this->network_client;
        this->network_client = new Network_client(this->ip, this->port);

        // Wait for transmission.
        long int next_transmission = this->transmission_frequency + this->last_transmission;

        if (next_transmission > time(NULL)) {
            long int waiting_time = next_transmission - time(NULL);

            cout << "Client controller: Waiting " << waiting_time << " seconds for next transmission" << endl;
            sleep_for(seconds(waiting_time));
        }

        // Check data limits.
        int result = 0;
        int tries = 0;
        cout << "Client controller: So far sent " << this->data_sent_bytes << " bytes in the current period." << endl;

        do {
            result = this->check_data_limitation();

            if (tries > 0 && result != 0) {
                cout << "Client controller: Waiting until can send more data due to the hourly limitation (" << tries << " tries)." << endl;
                sleep_for(seconds(30));
            }

            tries++;
        } while (result != 0);

        // Set state to connecting and then sending.
        this->set_state(CONNECTING);
        this->perform();

        this->set_state(SENDING);
        this->perform();

        // Set last transmission time to now.
        this->last_transmission = time(NULL);
    }

    void Client_controller::clean_sensor_readers() {
        for (Sensor_reader *sensor_reader : this->sensor_readers) {
            sensor_reader->clear_readings();
        }

        cout << "Client controller: Cleared readings from the memory" << endl;
    }

    void Client_controller::start_reading() {
        this->set_state(READING);
        this->perform();
    }

    Network_client* Client_controller::get_network_client() {
        return this->network_client;
    }

    vector<Sensor_reader*> Client_controller::get_sensor_readers() {
        return this->sensor_readers;
    }

    void Client_controller::add_bytes_sent(int bytes) {
        this->data_sent_bytes += bytes;
    }

    Reading_data* Client_controller::get_reading_data() {
        // Construct vector of readings from all the sensors mixed all together.
        vector<Sensor*> data;

        // Variables for the first and last reading time.
        time_t min_time = 0;
        time_t max_time = 0;

        // Loop through all the sensor readers.
        for (Sensor_reader *sensor_reader : this->sensor_readers) {
            
            // Loop through all the readings for the particular sensor reader.
            for (Sensor *sensor : sensor_reader->get_readings()) {

                // Find out the minimum time of readings
                if (min_time == 0 || sensor->get_datetime() < min_time) {
                    min_time = sensor->get_datetime();
                }

                // Find out the maximum time of readings
                if (sensor->get_datetime() > max_time) {
                    max_time = sensor->get_datetime();
                }

                // Add data from the sensor to the vector containing all the types of readings.
                data.push_back(sensor);
            }
        }

        // Construct new Reading_data container with the current readings.
        return new Reading_data(min_time, max_time, data);
    }

    void Client_controller::set_state(Client_controller_state state) {
        this->current_state = state;
    }

    int Client_controller::check_data_limitation() {
        // Calculate time when the data limitations will be resetted.
        time_t reset_time = this->data_period_start_datetime + 60 * 60;

        // If it's time for data limit reset...
        if (time(NULL) >= reset_time) {
            cout << "Client controller: Reset data throotling" << endl;
            this->data_period_start_datetime = time(NULL);
            this->data_sent_bytes = 0;
            return 0;
        }

        // Return 1 if we are over limit.
        if (this->data_sent_bytes >= this->data_hourly_limit) {
            return 1;
        }

        // We are not over the limit so return 0.
        return 0;
    }

    string Client_controller::get_id() {
        return this->id;
    }
}
