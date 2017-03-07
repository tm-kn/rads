#include <iostream>

#include "Server_controller.h"

using std::cout;

using RADS_server::Server_controller;

int main() {
    Server_controller* server_controller = new Server_controller();
    
    server_controller->start_communication();
}
