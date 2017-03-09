#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "Server_controller.h"
#include "Observer.h"
#include "CLI_observer.h"
#include "File_writer_observer.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::this_thread::sleep_for;
using std::vector;

namespace RADS_server {
    Server_controller::Server_controller()
    {
        this->network_server = new Network_server();

        this->add_observer(new CLI_observer());
        this->add_observer(new File_writer_observer());
    }


    Server_controller::~Server_controller()
    {
    }

    void Server_controller::start_communication() {
        cout << "Server controller: Start communication" << endl;
        
        int result = 0;

        do {
            if (result != 0) {
                cout << "Server controller: Trying to establish communication again..." << endl;
            }

            sleep_for(seconds(5));

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

        if (this->network_server->receive_data(*this, &Server_controller::process_received_data) == 0) {
            this->notify_observers();
        }
    }

    /**
        Create Reading_data object for the packets and add it to the Server controler
    */
    void Server_controller::process_received_data(vector<Packet> packets) {
        cout << "Server controller: Processing received data" << endl;
        
        vector<Sensor*> sensor_data;

        time_t min_time = 0;
        time_t max_time = 0;

        string sender_id;

        for (Packet packet : packets) {
            if (min_time == 0 || packet.datetime < min_time) {
                min_time = packet.datetime;
            }

            if (max_time == 0 || packet.datetime > max_time) {
                max_time = packet.datetime;
            }
            
            sender_id = packet.sender_id;
            Sensor * sensor = Reading_data::convert_packet_to_sensor(packet);

            if (sensor != NULL) {
                sensor_data.push_back(sensor);
            }
        }

        Reading_data reading_data(min_time, max_time, sensor_data);

        this->add_to_reading_data(sender_id, reading_data);

        // Set last received date for this client
        this->last_reading_datetimes[sender_id] = time(NULL);

        cout << "Server controller: Processed received data" << endl;
    }

    void Server_controller::check_last_reading_datetimes()
    {
        long int warning = 5 * 60;
        long int severe = 15 * 60;
        long int critical = 25 * 60;

        for (pair<string, time_t> last_reading_pair : this->last_reading_datetimes) {
            long int time_elapsed = time(NULL) - last_reading_pair.second;

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
    map<string, time_t> Server_controller::get_last_reading_datetimes()
    {
        return this->last_reading_datetimes;
    }
}
