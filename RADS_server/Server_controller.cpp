#include <iostream>

#include "Server_controller.h"

using std::cout;

namespace RADS_server {
    Server_controller::Server_controller()
    {
    }


    Server_controller::~Server_controller()
    {
    }

    void Server_controller::start_communication() {
        cout << "Server controller: Start communication";

        while (true);
    }
}