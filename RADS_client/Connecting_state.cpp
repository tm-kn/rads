#include <chrono>
#include <iostream>
#include <thread>

#include "Connecting_state.h"
#include "../RADS_common/Network_client.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

namespace RADS_client {
    namespace State {
        Connecting::Connecting() {}

        Connecting::~Connecting() {}

        void Connecting::perform() {
            cout << "Client controller: Start connecting" << endl;
               
            Network_client *client = this->get_client_controller()->get_network_client();

            int result = 0;
            int tries = 0;

            do {
                if (result != 0) {
                    cout << "Client controller: Wait 5 seconds for another try(" << tries << ")..." << endl;
                    sleep_for(seconds(5));
                }

                cout << "Client controller: Trying to establish connection to the server" << endl;
                result = client->establish_client_connection();
                tries++;
            } while (result != 0);

            cout << "Client Controller: Established connection to the server" << endl;
        }
    }
}
