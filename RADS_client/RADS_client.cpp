#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "Client_controller.h"
#include "../RADS_common/Sensor_reader.h"
#include "../RADS_common/GPS_position_reader.h"
#include "../RADS_common/Fuel_level_reader.h"
#include "../RADS_common/Speed_reader.h"
#include "../RADS_common/Temperature_sensor_reader.h"

using std::cout;
using std::endl;
using std::rand;
using std::srand;
using std::string;
using std::to_string;
using std::time;
using std::vector;

using RADS_client::Client_controller;
using Readings::Sensor_reader;
using Readings::GPS_position::GPS_position_reader;
using Readings::Fuel_level::Fuel_level_reader;
using Readings::Speed::Speed_reader;
using Readings::Temperature::Temperature_sensor_reader;

// Default configuration.
const int DEFAULT_TRANSMISSION_FREQUENCY = 60;
const int DEFAULT_HOURLY_LIMIT = 5 * 1024 * 1024;
const string DEFAULT_IP = "127.0.0.1";
const int DEFAULT_PORT = 6881;

int main() {
    cout << "Remote Aeroplane Diagnostic System - Client" << endl << endl;

    // Instantiate sensor readers.
    vector<Sensor_reader*> sensor_readers;

    sensor_readers.push_back(new GPS_position_reader());
    sensor_readers.push_back(new Temperature_sensor_reader());
    sensor_readers.push_back(new Fuel_level_reader());
    sensor_readers.push_back(new Speed_reader());

    // Generate random ID
    srand(time(NULL));
    string id = to_string(rand() % 10000 + 1);

    // Create client controller instance.
    Client_controller* client_controller = new Client_controller(
        id,
        sensor_readers,
        DEFAULT_TRANSMISSION_FREQUENCY,
        DEFAULT_HOURLY_LIMIT,
        DEFAULT_IP,
        DEFAULT_PORT
    );

    // Client loop - read and send data until programme is terminated.
    while (true) {
        client_controller->start_reading();
        client_controller->start_communicating();
        cout << "RADS_client: Another iteration..." << endl << endl;
    }
}
