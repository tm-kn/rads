#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "Server_controller.h"
#include "Observer.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::this_thread::sleep_for;
using std::vector;

namespace RADS_server {
    Server_controller::Server_controller(string ip, int port, vector<Observer*> observers) {
        // Set networking details
        this->ip = ip;
        this->port = port;
        this->network_server = new Network_server(ip, port);

        // Add observers
        for (Observer * observer : observers) {
            this->add_observer(observer);
        }

        cout << "Server controller: IP address set to " << this->ip << "." << endl;
        cout << "Server controller: Port number set to " << this->port << "." << endl << endl;
    }

    Server_controller::~Server_controller() {}

    void Server_controller::start_communication() {
        cout << "Server controller: Start communication" << endl;
        
        int result = 0;

        do {
            if (result != 0) {
                cout << "Server controller: Trying to establish communication again..." << endl;

                // Sleep for 5 seconds if can't establish connection
                sleep_for(seconds(5));
            }

            // Try to establish connection
            result = this->network_server->establish_server_communication();
        } while (result != 0);

        cout << "Server controller: Established server communication - ready to accept clients" << endl;

        // Server loop
        while (true) {
            this->update();
            sleep_for(seconds(1));
        }
    }

    void Server_controller::update() {
        this->network_server->accept_connections();
        this->check_last_reading_datetimes();

        // If new data has been received notify observers.
        if (this->network_server->receive_data(*this, &Server_controller::process_received_data) == 0) {
            this->notify_observers();
        }
    }

    void Server_controller::process_received_data(vector<Packet> packets) {
        cout << "Server controller: Processing received data" << endl;
        
        // Initialise vector for the values that will be converted into Sensor objects.
        vector<Sensor*> sensor_data;

        // Get minimum and maximum time of the readings.
        time_t min_time = 0;
        time_t max_time = 0;

        // String to store sender ID.
        string sender_id;

        for (Packet packet : packets) {
            // Find the minimum time of the readings.
            if (min_time == 0 || packet.datetime < min_time) {
                min_time = packet.datetime;
            }

            // Find the maximum time of the readings.
            if (max_time == 0 || packet.datetime > max_time) {
                max_time = packet.datetime;
            }
            
            // Get the sender ID.
            sender_id = packet.sender_id;

            // Convert packet data to the Sensor instance.
            Sensor * sensor = Reading_data::convert_packet_to_sensor(packet);
            
            // If sensor could be converted add the new data to the vector.
            if (sensor != NULL) {
                sensor_data.push_back(sensor);
            }
        }

        // Construct Reading_data object with received data.
        Reading_data reading_data(min_time, max_time, sensor_data);

        // Add that object to the map of that particular sender's readings.
        this->add_to_reading_data(sender_id, reading_data);

        // Set last received date for this client.
        this->last_reading_datetimes[sender_id] = time(NULL);

        cout << "Server controller: Processed received data" << endl;
    }

    void Server_controller::check_last_reading_datetimes() {
        // Set time required to pass without transmission for particular alarm states.
        long int warning = 5 * 60;
        long int severe = 15 * 60;
        long int critical = 25 * 60;

        // Loop through map containing last readings of particular senders.
        for (pair<string, time_t> last_reading_pair : this->last_reading_datetimes) {

            // Time elapsed since last reading.
            long int time_elapsed = time(NULL) - last_reading_pair.second;

            // Raise alarm accordingly.
            if (time_elapsed >= warning && time_elapsed < severe) {
                cout << "Server controller: Warning - no communication with " << last_reading_pair.first << " for 5 minutes" << endl;
            }
            else if (time_elapsed >= severe && time_elapsed < critical) {
                cout << "Server controller: Severe - no communication with " << last_reading_pair.first << " for 15 minutes" << endl;
            }
            else if (time_elapsed >= critical) {
                cout << "Server controller: Critical - no communication with " << last_reading_pair.first << " for 25 minutes" << endl;
            }
        }
    }

    void Server_controller::notify_observers() {
        cout << "Server controller: Notifying observers..." << endl;

        for (Observer * observer : this->observers) {
            observer->update();
        }
    }

    void Server_controller::add_to_reading_data(string sender_id, Reading_data reading_data) {
        map<string, vector<Reading_data>>::iterator it = this->reading_data.find(sender_id);

        // If sender does not exist in the readings map, just add it.
        // Otherwise append data to the existing vector.
        if (it != this->reading_data.end()) {

            it->second.push_back(reading_data);
        }
        else {
            vector <Reading_data> new_vector;
            new_vector.push_back(reading_data);
            this->reading_data.insert(make_pair(sender_id, new_vector));
        }
    }

    void Server_controller::add_observer(Observer * observer) {
        observer->set_server_controller(this);
        this->observers.push_back(observer);
    }

    map<string, vector<Reading_data>> Server_controller::get_reading_data() {
        return this->reading_data;
    }
    map<string, time_t> Server_controller::get_last_reading_datetimes() {
        return this->last_reading_datetimes;
    }
}
