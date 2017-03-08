#include <iostream>

#include "Server_controller.h"

using std::cout;
using std::endl;

using RADS_server::Server_controller;

int main() {
    cout << "Remote Aeroplane Diagnostic System - Server" << endl << endl;


    Server_controller* server_controller = new Server_controller();
    
    server_controller->start_communication();
}
