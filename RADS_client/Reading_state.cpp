#include <iostream>
#include <unordered_map>
#include <thread>

#include "Reading_state.h"
#include "../RADS_common/Sensor_reader.h"

using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using std::thread;

using Readings::Sensor_reader;

namespace RADS_client {
    namespace State {
        Reading::Reading() {}

        Reading::~Reading() {}

        void Reading::perform() {
            // First clear all the old readings from the sensor readers.
            this->get_client_controller()->clean_sensor_readers();

            // Create a map for all the threads.
            unordered_map<Sensor_reader*, thread*> threads;

            cout << "Client controller: Started reading" << endl;

            // Start a thread with each of the sensor's read() method.
            for (Sensor_reader *sensor_reader : this->get_client_controller()->get_sensor_readers()) {
                threads.insert(pair<Sensor_reader*, thread*>(sensor_reader, new thread(&Sensor_reader::read, sensor_reader)));
                cout << "Client controller: Thread for " << sensor_reader->get_sensor_reader_name() << " has started" << endl;
            }

            // Synchronise threads.
            for (pair<Sensor_reader*, thread*> sensor_thread_pair : threads) {
                sensor_thread_pair.second->join();
                cout << "Client controller: Thread for " << sensor_thread_pair.first->get_sensor_reader_name() << " has finished" << endl;
            }

            cout << "Client controller: Finished reading" << endl;

            cout << "Client controller: RESULTS START >>>>>>>>>>" << endl;

            // Output the readings.
            for (Sensor *sensor : this->get_client_controller()->get_reading_data()->get_data()) {
                cout << "[" << sensor->get_datetime() << "] " << sensor->to_string() << endl;
            }

            cout << "<<<<<<<<<<< Client controller: RESULTS END" << endl;
        }
    }
}
