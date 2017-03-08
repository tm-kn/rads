#include <iostream>

#include "Client_controller.h"

using std::cout;
using std::endl;

using RADS_client::Client_controller;

int main() {
    cout << "Remote Aeroplane Diagnostic System - Client" << endl << endl;

    Client_controller* client_controller = new Client_controller();

    while (true) {
        client_controller->start_reading();
        client_controller->start_communicating();
        cout << "Client Controller: Another iteration..." << endl << endl;
    }
}
