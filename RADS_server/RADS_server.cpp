#include <iostream>

#include "Server_controller.h"
#include "CLI_observer.h"
#include "File_writer_observer.h"

using std::cout;
using std::endl;

using RADS_server::Server_controller;
using RADS_server::Observer;
using RADS_server::CLI_observer;
using RADS_server::File_writer_observer;

// Default configuration
const string DEFAULT_IP = "0.0.0.0";
const int DEFAULT_PORT = 6881;

int main() {
    cout << "Remote Aeroplane Diagnostic System - Server" << endl << endl;

    // Add observer
    vector<Observer*> observers;
    observers.push_back(new CLI_observer());
    observers.push_back(new File_writer_observer());

    // Create new instance of server
    Server_controller* server_controller = new Server_controller(DEFAULT_IP, DEFAULT_PORT, observers);
    
    // Start server loop
    server_controller->start_communication();
}
