#include <chrono>
#include <iostream>
#include <thread>

#include "Server_controller.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

namespace RADS_server {
    Server_controller::Server_controller()
    {
        this->client_id = 0;
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

            int result = this->network_server.etablish_server_communication();
        } while (result != 0);

        cout << "Server controller: Established server communication - ready to accept clients" << endl;

        // Server loop
        while (true) {
            this->update();
            sleep_for(seconds(1));
        }
    }

    void Server_controller::update() {
        if (this->network_server.accept_connection(this->client_id) == 0) {
            printf("Server Controller: Accepted connection to the server (client %d)\n", this->client_id);
            this->client_id++;
       }
    }
}